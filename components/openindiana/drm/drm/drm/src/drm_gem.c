/*
 * Copyright (c) 2006, 2015, Oracle and/or its affiliates. All rights reserved.
 */

/*
 * Copyright (c) 2009, 2013, Intel Corporation.
 * All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 *
 * Authors:
 *    Eric Anholt <eric@anholt.net>
 *
 */

#include "drmP.h"
#include <vm/seg_kmem.h>

/** @file drm_gem.c
 *
 * This file provides some of the base ioctls and library routines for
 * the graphics memory manager implemented by each device driver.
 *
 * Because various devices have different requirements in terms of
 * synchronization and migration strategies, implementing that is left up to
 * the driver, and all that the general API provides should be generic --
 * allocating objects, reading/writing data with the cpu, freeing objects.
 * Even there, platform-dependent optimizations for reading/writing data with
 * the CPU mean we'll likely hook those out to driver-specific calls.  However,
 * the DRI2 implementation wants to have at least allocate/mmap be generic.
 *
 * The goal was to have swap-backed object allocation managed through
 * struct file.  However, file descriptors as handles to a struct file have
 * two major failings:
 * - Process limits prevent more than 1024 or so being used at a time by
 *   default.
 * - Inability to allocate high fds will aggravate the X Server's select()
 *   handling, and likely that of many GL client applications as well.
 *
 * This led to a plan of using our own integer IDs (called handles, following
 * DRM terminology) to mimic fds, and implement the fd syscalls we need as
 * ioctls.  The objects themselves will still include the struct file so
 * that we can transition to fds if the required kernel infrastructure shows
 * up at a later date, and as our interface with shmfs for memory allocation.
 */

/*
 * We make up offsets for buffer objects so we can recognize them at
 * mmap time.
 */
#define DRM_FILE_PAGE_OFFSET_START ((0xFFFFFFFFUL >> PAGE_SHIFT) + 1)
#define DRM_FILE_PAGE_OFFSET_SIZE ((0xFFFFFFFFUL >> PAGE_SHIFT) * 16)

int drm_use_mem_pool = 0;
/* memory pool is used for all platforms now */
#define	HAS_MEM_POOL(gen)	((gen > 30) && (drm_use_mem_pool))

/**
 * Initialize the GEM device fields
 */

int
drm_gem_init(struct drm_device *dev)
{

	spin_lock_init(&dev->object_name_lock);
	idr_list_init(&dev->object_name_idr);

	gfxp_mempool_init();

	return 0;
}

void
/* LINTED */
drm_gem_destroy(struct drm_device *dev)
{
}

static void
drm_gem_object_free_internal(struct drm_gem_object *obj, int gen)
{
	if (obj->pfnarray != NULL)
		kmem_free(obj->pfnarray, btopr(obj->real_size) * sizeof (pfn_t));
	if (HAS_MEM_POOL(gen)) {
		gfxp_free_mempool(&obj->mempool_cookie, obj->kaddr, obj->real_size);
	} else {
		(void) ddi_dma_unbind_handle(obj->dma_hdl);
		ddi_dma_mem_free(&obj->acc_hdl);
		ddi_dma_free_handle(&obj->dma_hdl);
	}
	obj->kaddr = NULL;
}

static ddi_dma_attr_t old_dma_attr = {
	DMA_ATTR_V0,
	0xff000U,			/* dma_attr_addr_lo */
	0xffffffffU,			/* dma_attr_addr_hi */
	0xffffffffU,			/* dma_attr_count_max */
	4096,				/* dma_attr_align */
	0x1fffU,			/* dma_attr_burstsizes */
	1,				/* dma_attr_minxfer */
	0xffffffffU,			/* dma_attr_maxxfer */
	0xffffffffU,			/* dma_attr_seg */
	1,				/* dma_attr_sgllen, variable */
	4,				/* dma_attr_granular */
	DDI_DMA_FLAGERR,		/* dma_attr_flags */
};

static ddi_device_acc_attr_t old_acc_attr = {
	DDI_DEVICE_ATTR_V0,
	DDI_NEVERSWAP_ACC,
	DDI_MERGING_OK_ACC,
	DDI_FLAGERR_ACC
};

static int
drm_gem_object_alloc_internal_normal(struct drm_device *dev, struct drm_gem_object *obj,
				size_t size, int flag)
{
	ddi_dma_cookie_t cookie;
	uint_t cookie_cnt;
	pgcnt_t real_pgcnt, pgcnt = btopr(size);
	uint64_t paddr, cookie_end;
	int i, n;
	int (*cb)(caddr_t);
	ddi_device_acc_attr_t *acc_attr;
	ddi_dma_attr_t* dma_attr;
	uint_t mode_flag;

	acc_attr = &old_acc_attr;
	dma_attr = &old_dma_attr;
	mode_flag = IOMEM_DATA_UC_WR_COMBINE;

	cb = (flag == 0) ? DDI_DMA_DONTWAIT : DDI_DMA_SLEEP;
	dma_attr->dma_attr_sgllen = (int)pgcnt;

	if (ddi_dma_alloc_handle(dev->devinfo, dma_attr,
	    cb, NULL, &obj->dma_hdl)) {
		DRM_ERROR("ddi_dma_alloc_handle failed");
		goto err1;
	}
	if (ddi_dma_mem_alloc(obj->dma_hdl, ptob(pgcnt), acc_attr,
	    mode_flag, cb, NULL,
	    &obj->kaddr, &obj->real_size, &obj->acc_hdl)) {
		DRM_ERROR("ddi_dma_mem_alloc failed");
		goto err2;
	}
	if (ddi_dma_addr_bind_handle(obj->dma_hdl, NULL,
	    obj->kaddr, obj->real_size, DDI_DMA_RDWR,
	    cb, NULL, &cookie, &cookie_cnt)
	    != DDI_DMA_MAPPED) {
		DRM_ERROR("ddi_dma_addr_bind_handle failed");
		goto err3;
	}

	real_pgcnt = btopr(obj->real_size);

	obj->pfnarray = kmem_zalloc(real_pgcnt * sizeof (pfn_t), KM_NOSLEEP);
	if (obj->pfnarray == NULL) {
		DRM_DEBUG("pfnarray == NULL");
		goto err4;
	}

	for (n = 0, i = 1; ; i++) {
		for (paddr = cookie.dmac_laddress,
		    cookie_end = cookie.dmac_laddress + cookie.dmac_size;
		    paddr < cookie_end;
		    paddr += PAGESIZE) {
			obj->pfnarray[n++] = btop(paddr);
			if (n >= real_pgcnt)
				return (0);
		}
		if (i >= cookie_cnt)
			break;
		ddi_dma_nextcookie(obj->dma_hdl, &cookie);
	}

err4:
	(void) ddi_dma_unbind_handle(obj->dma_hdl);
err3:
	ddi_dma_mem_free(&obj->acc_hdl);
err2:
	ddi_dma_free_handle(&obj->dma_hdl);
err1:
	return (-1);

}

/* Alloc GEM object by memory pool */
static int
drm_gem_object_alloc_internal_mempool(struct drm_gem_object *obj,
				size_t size, int flag)
{
	int ret;
	pgcnt_t pgcnt = btopr(size);

	obj->pfnarray = kmem_zalloc(pgcnt * sizeof (pfn_t), KM_NOSLEEP);
	if (obj->pfnarray == NULL) {
		DRM_ERROR("Failed to allocate pfnarray ");
		return (-1);
	}

	ret = gfxp_alloc_from_mempool(&obj->mempool_cookie, &obj->kaddr,
					obj->pfnarray, pgcnt, flag);
	if (ret) {
		DRM_ERROR("Failed to alloc pages from memory pool");
		kmem_free(obj->pfnarray, pgcnt * sizeof (pfn_t));
		return (-1);
	}

	obj->real_size = size;
	return (0);
}

static int
drm_gem_object_internal(struct drm_device *dev, struct drm_gem_object *obj,
			size_t size, int gen)
{
	pfn_t tmp_pfn;
	int ret, num = 0;

alloc_again:
	if (HAS_MEM_POOL(gen)) {
		uint32_t mode;
		if (gen >= 60)
			mode = GFXP_MEMORY_CACHED;
		else
			mode = GFXP_MEMORY_WRITECOMBINED;
		ret = drm_gem_object_alloc_internal_mempool(obj, size, mode);
                if (ret)
                        return (-1);
	} else {
		ret = drm_gem_object_alloc_internal_normal(dev, obj, size, 0);
		if (ret)
			return (-1);
	}
	tmp_pfn = hat_getpfnum(kas.a_hat, obj->kaddr);
	if (tmp_pfn != obj->pfnarray[0]) {
		DRM_ERROR("obj %p map incorrect 0x%lx != 0x%lx",
		    (void *)obj, tmp_pfn, obj->pfnarray[0]);
		drm_gem_object_free_internal(obj, gen);
		udelay(150);

		if (num++ < 5)
			goto alloc_again;
		else
			return (-1);
	}

	return (0);
}
/*
 * Initialize an already allocate GEM object of the specified size with
 * shmfs backing store.
 */
int
drm_gem_object_init(struct drm_device *dev, struct drm_gem_object *obj,
				size_t size, int gen)
{
	drm_local_map_t *map;
	int ret;

	if (size == 0) {
		DRM_DEBUG("size == 0");
		return (-1);
	}

	obj->dev = dev;
	obj->size = size;

	ret = drm_gem_object_internal(dev, obj, size, gen);
	if (ret)
		return (-1);

	map = drm_alloc(sizeof (struct drm_local_map), DRM_MEM_MAPS);
	if (map == NULL) {
		DRM_DEBUG("map == NULL");
		goto err5;
	}

	map->handle = obj;
	map->offset = (uintptr_t)map->handle;
	map->offset &= 0xffffffffUL;
	map->size = obj->real_size;
	map->type = _DRM_GEM;
	map->callback = 0;
	map->flags = _DRM_WRITE_COMBINING | _DRM_REMOVABLE;
	map->umem_cookie =
	    gfxp_umem_cookie_init(obj->kaddr, obj->real_size);
	if (map->umem_cookie == NULL) {
		DRM_DEBUG("umem_cookie == NULL");
		goto err6;
	}

	obj->maplist.map = map;
	if (drm_map_handle(dev, &obj->maplist)) {
		DRM_DEBUG("drm_map_handle failed");
		goto err7;
	}

	kref_init(&obj->refcount);
	atomic_set(&obj->handle_count, 0);

	if (MDB_TRACK_ENABLE) {
		INIT_LIST_HEAD(&obj->track_list);
		spin_lock(&dev->track_lock);
		list_add_tail(&obj->track_list, &dev->gem_objects_list, (caddr_t)obj);
		spin_unlock(&dev->track_lock);

		INIT_LIST_HEAD(&obj->his_list);
		drm_gem_object_track(obj, "obj init", 0, 0, NULL);
	}

	INIT_LIST_HEAD(&obj->seg_list);

	return (0);

err7:
	gfxp_umem_cookie_destroy(map->umem_cookie);
err6:
	drm_free(map, sizeof (struct drm_local_map), DRM_MEM_MAPS);
err5:
	drm_gem_object_free_internal(obj, gen);
	return (-1);
}

/**
 * Initialize an already allocated GEM object of the specified size with
 * no GEM provided backing store. Instead the caller is responsible for
 * backing the object and handling it.
 */
int drm_gem_private_object_init(struct drm_device *dev,
			struct drm_gem_object *obj, size_t size)
{
	BUG_ON((size & (PAGE_SIZE - 1)) != 0);

	obj->dev = dev;

	kref_init(&obj->refcount);
	atomic_set(&obj->handle_count, 0);
	obj->size = size;

	return 0;
}

/**
 * Allocate a GEM object of the specified size with shmfs backing store
 */
struct drm_gem_object *
drm_gem_object_alloc(struct drm_device *dev, size_t size)
{
	struct drm_gem_object *obj;

	obj = kzalloc(sizeof(*obj), GFP_KERNEL);
	if (!obj)
		goto free;

	if (drm_gem_object_init(dev, obj, size, 0) != 0) {
		kmem_free(obj, sizeof (struct drm_gem_object));
		return NULL;
	}

	if (dev->driver->gem_init_object != NULL &&
	    dev->driver->gem_init_object(obj) != 0) {
		goto fput;
	}
	return obj;
fput:
	/* Object_init mangles the global counters - readjust them. */
	drm_gem_object_release(obj);
	kfree(obj, sizeof(*obj));
free:
	return NULL;
}

/**
 * Removes the mapping from handle to filp for this object.
 */
int
drm_gem_handle_delete(struct drm_file *filp, u32 handle)
{
	struct drm_device *dev;
	struct drm_gem_object *obj;

	/* This is gross. The idr system doesn't let us try a delete and
	 * return an error code.  It just spews if you fail at deleting.
	 * So, we have to grab a lock around finding the object and then
	 * doing the delete on it and dropping the refcount, or the user
	 * could race us to double-decrement the refcount and cause a
	 * use-after-free later.  Given the frequency of our handle lookups,
	 * we may want to use ida for number allocation and a hash table
	 * for the pointers, anyway.
	 */
	spin_lock(&filp->table_lock);

	/* Check if we currently have a reference on the object */
	obj = idr_list_find(&filp->object_idr, handle);
	if (obj == NULL) {
		spin_unlock(&filp->table_lock);
		return -EINVAL;
	}
	dev = obj->dev;

	/* Release reference and decrement refcount. */
	(void) idr_list_remove(&filp->object_idr, handle);
	spin_unlock(&filp->table_lock);

	if (dev->driver->gem_close_object)
		dev->driver->gem_close_object(obj, filp);
	drm_gem_object_handle_unreference_unlocked(obj);

	return 0;
}

/**
 * Create a handle for this object. This adds a handle reference
 * to the object, which includes a regular reference count. Callers
 * will likely want to dereference the object afterwards.
 */
int
drm_gem_handle_create(struct drm_file *file_priv,
		       struct drm_gem_object *obj,
		       u32 *handlep)
{
	struct drm_device *dev = obj->dev;
	int	ret;

	/*
	 * Get the user-visible handle using idr.
	 */
again:
	/* ensure there is space available to allocate a handle */
	if (idr_list_pre_get(&file_priv->object_idr, GFP_KERNEL) == 0)
		return -ENOMEM;

	/* do the allocation under our spinlock */
	spin_lock(&file_priv->table_lock);
	ret = idr_list_get_new_above(&file_priv->object_idr, (void *)obj, (int *)handlep);
	spin_unlock(&file_priv->table_lock);
	if (ret == -EAGAIN)
		goto again;

	if (ret != 0)
		return ret;

	drm_gem_object_handle_reference(obj);

	if (dev->driver->gem_open_object) {
		ret = dev->driver->gem_open_object(obj, file_priv);
		if (ret) {
			(void) drm_gem_handle_delete(file_priv, *handlep);
			return ret;
		}
	}

	return 0;
}

/** Returns a reference to the object named by the handle. */
struct drm_gem_object *
/* LINTED */
drm_gem_object_lookup(struct drm_device *dev, struct drm_file *filp,
		      u32 handle)
{
	struct drm_gem_object *obj;

	spin_lock(&filp->table_lock);

	/* Check if we currently have a reference on the object */
	obj = idr_list_find(&filp->object_idr, handle);
	if (obj == NULL) {
		spin_unlock(&filp->table_lock);
		return NULL;
	}

	drm_gem_object_reference(obj);

	spin_unlock(&filp->table_lock);

	return obj;
}

/**
 * Releases the handle to an mm object.
 */
int
/* LINTED */
drm_gem_close_ioctl(DRM_IOCTL_ARGS)
{
	struct drm_gem_close *args = data;
	int ret;

	if (!(dev->driver->driver_features & DRIVER_GEM))
		return -ENODEV;

	ret = drm_gem_handle_delete(file, args->handle);

	return ret;
}

/**
 * Create a global name for an object, returning the name.
 *
 * Note that the name does not hold a reference; when the object
 * is freed, the name goes away.
 */
int
/* LINTED */
drm_gem_flink_ioctl(DRM_IOCTL_ARGS)
{
	struct drm_gem_flink *args = data;
	struct drm_gem_object *obj;
	int ret;

	if (!(dev->driver->driver_features & DRIVER_GEM))
		return -ENODEV;

	obj = drm_gem_object_lookup(dev, file, args->handle);
	if (obj == NULL)
		return -ENOENT;

again:
	if (idr_list_pre_get(&dev->object_name_idr, GFP_KERNEL) == 0) {
		ret = -ENOMEM;
		goto err;
	}

	spin_lock(&dev->object_name_lock);
	if (!obj->name) {
		ret = idr_list_get_new_above(&dev->object_name_idr, (void *) obj,
					&obj->name);
		args->name = (uint64_t) obj->name;
		spin_unlock(&dev->object_name_lock);

		if (ret == -EAGAIN)
			goto again;

		if (ret != 0)
			goto err;

		/* Allocate a reference for the name table.  */
		drm_gem_object_reference(obj);
	} else {
		args->name = (uint64_t) obj->name;
		spin_unlock(&dev->object_name_lock);
		ret = 0;
	}

err:
	drm_gem_object_unreference_unlocked(obj);
	return ret;
}

/**
 * Open an object using the global name, returning a handle and the size.
 *
 * This handle (of course) holds a reference to the object, so the object
 * will not go away until the handle is deleted.
 */
int
/* LINTED */
drm_gem_open_ioctl(DRM_IOCTL_ARGS)
{
	struct drm_gem_open *args = data;
	struct drm_gem_object *obj;
	int ret;
	u32 handle;

	if (!(dev->driver->driver_features & DRIVER_GEM))
		return -ENODEV;

	spin_lock(&dev->object_name_lock);
	obj = idr_list_find(&dev->object_name_idr, (int) args->name);
	if (obj)
		drm_gem_object_reference(obj);
	spin_unlock(&dev->object_name_lock);
	if (!obj)
		return -ENOENT;

	ret = drm_gem_handle_create(file, obj, &handle);
	drm_gem_object_unreference_unlocked(obj);
	if (ret)
		return ret;

	args->handle = handle;
	args->size = obj->size;

	return 0;
}

/**
 * Called at device open time, sets up the structure for handling refcounting
 * of mm objects.
 */
void
/* LINTED */
drm_gem_open(struct drm_device *dev, struct drm_file *file_private)
{
	idr_list_init(&file_private->object_idr);
	spin_lock_init(&file_private->table_lock);
}

/**
 * Called at device close to release the file's
 * handle references on objects.
 */
static int
/* LINTED */
drm_gem_object_release_handle(int id, void *ptr, void *data)
{
	struct drm_file *file_priv = data;
	struct drm_gem_object *obj = ptr;
	struct drm_device *dev = obj->dev;

	if (dev->driver->gem_close_object)
		dev->driver->gem_close_object(obj, file_priv);

	drm_gem_object_handle_unreference_unlocked(obj);

	return 0;
}

/**
 * Called at close time when the filp is going away.
 *
 * Releases any remaining references on objects by this filp.
 */
void
/* LINTED E_FUNC_ARG_UNUSED */
drm_gem_release(struct drm_device *dev, struct drm_file *file_private)
{
	struct idr_list  *entry;
	struct drm_gem_object *obj;

	idr_list_for_each(entry, &file_private->object_idr) {
		obj = (struct drm_gem_object *)entry->obj;
		(void) drm_gem_object_release_handle(obj->name, obj, (void *)file_private);
	}
	idr_list_free(&file_private->object_idr);
}

void
drm_gem_object_release(struct drm_gem_object *obj)
{
	struct drm_device *dev = obj->dev;
	struct drm_local_map *map = obj->maplist.map;

	if (MDB_TRACK_ENABLE) {
		spin_lock(&dev->track_lock);
		list_del(&obj->track_list);
		spin_unlock(&dev->track_lock);

		struct drm_history_list *r_list, *list_temp;
		list_for_each_entry_safe(r_list, list_temp, struct drm_history_list, &obj->his_list, head) {
			list_del(&r_list->head);
			drm_free(r_list, sizeof (struct drm_history_list), DRM_MEM_MAPS);
		}
		list_del(&obj->his_list);
	}

	(void) idr_remove(&dev->map_idr, obj->maplist.user_token >> PAGE_SHIFT);
	gfxp_umem_cookie_destroy(map->umem_cookie);
	drm_free(map, sizeof (struct drm_local_map), DRM_MEM_MAPS);

	kmem_free(obj->pfnarray, btopr(obj->real_size) * sizeof (pfn_t));

	if (obj->dma_hdl == NULL) {
		gfxp_free_mempool(&obj->mempool_cookie, obj->kaddr, obj->real_size);
	} else {
		(void) ddi_dma_unbind_handle(obj->dma_hdl);
		ddi_dma_mem_free(&obj->acc_hdl);
		ddi_dma_free_handle(&obj->dma_hdl);
	}
	obj->kaddr = NULL;
}

/**
 * Called after the last reference to the object has been lost.
 *
 * Frees the object
 */
void
drm_gem_object_free(struct kref *kref)
{
	/* LINTED */
	struct drm_gem_object *obj = (struct drm_gem_object *) kref;
	struct drm_device *dev = obj->dev;

//	BUG_ON(!mutex_is_locked(&dev->struct_mutex));

	if (dev->driver->gem_free_object != NULL)
		dev->driver->gem_free_object(obj);
}

/* LINTED E_FUNC_ARG_UNUSED */
static void drm_gem_object_ref_bug(struct kref *list_kref)
{
	BUG_ON(1);
}

/**
 * Called after the last handle to the object has been closed
 *
 * Removes any name for the object. Note that this must be
 * called before drm_gem_object_free or we'll be touching
 * freed memory
 */
void
drm_gem_object_handle_free(struct drm_gem_object *obj)
{
	struct drm_device *dev = obj->dev;

	/* Remove any name for this object */
	spin_lock(&dev->object_name_lock);
	if (obj->name) {
		(void) idr_list_remove(&dev->object_name_idr, obj->name);
		obj->name = 0;
		spin_unlock(&dev->object_name_lock);
		/*
		 * The object name held a reference to this object, drop
		 * that now.
		*
		* This cannot be the last reference, since the handle holds one too.
		 */
		kref_put(&obj->refcount, drm_gem_object_ref_bug);
	} else
		spin_unlock(&dev->object_name_lock);

}

int
drm_gem_create_mmap_offset(struct drm_gem_object *obj)
{
	obj->gtt_map_kaddr = gfxp_alloc_kernel_space(obj->real_size);
	if (obj->gtt_map_kaddr == NULL) {
		return -ENOMEM;
	}
	return 0;
}

void
drm_gem_mmap(struct drm_gem_object *obj, pfn_t pfn)
{
	gfxp_load_kernel_space(pfn, obj->real_size, GFXP_MEMORY_WRITECOMBINED, obj->gtt_map_kaddr);
}

void
drm_gem_release_mmap(struct drm_gem_object *obj)
{
	gfxp_unload_kernel_space(obj->gtt_map_kaddr, obj->real_size);
}

void
drm_gem_free_mmap_offset(struct drm_gem_object *obj)
{
	struct ddi_umem_cookie *umem_cookie = obj->maplist.map->umem_cookie;
	umem_cookie->cvaddr = obj->kaddr;

	if (obj->maplist.map->gtt_mmap == 0) {
		gfxp_free_kernel_space(obj->gtt_map_kaddr, obj->real_size);
		DRM_DEBUG("already freed, don't free more than once!");
	}

	if (obj->maplist.map->gtt_mmap == 1) {
		gfxp_unmap_kernel_space(obj->gtt_map_kaddr, obj->real_size);
		obj->maplist.map->gtt_mmap = 0;
	}

	obj->gtt_map_kaddr = NULL;
}

void
drm_gem_object_track(struct drm_gem_object *obj, const char *name,
                        uint32_t cur_seq, uint32_t last_seq, void* ptr)
{
	struct drm_history_list *list;
	list = drm_alloc(sizeof (struct drm_history_list), DRM_MEM_MAPS);
	if (list != NULL) {
		(void) memcpy(list->info, name, (strlen(name) * sizeof(char)));
		list->cur_seq = cur_seq;
		list->last_seq = last_seq;
		list->ring_ptr = ptr;
		list_add_tail(&list->head, &obj->his_list, (caddr_t)list);
	}
}
