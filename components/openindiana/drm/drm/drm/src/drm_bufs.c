/*
 * Copyright (c) 2006, 2013, Oracle and/or its affiliates. All rights reserved.
 */

/**
 * \file drm_bufs.c
 * Generic buffer template
 *
 * \author Rickard E. (Rik) Faith <faith@valinux.com>
 * \author Gareth Hughes <gareth@valinux.com>
 */

/*
 * Created: Thu Nov 23 03:10:50 2000 by gareth@valinux.com
 *
 * Copyright 1999, 2000 Precision Insight, Inc., Cedar Park, Texas.
 * Copyright 2000 VA Linux Systems, Inc., Sunnyvale, California.
 * Copyright (c) 2009, 2012, Intel Corporation.
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
 * VA LINUX SYSTEMS AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#include "drmP.h"
#include "drm_io32.h"

#ifdef _LP64
extern caddr_t smmap64(caddr_t, size_t, int, int, int, off_t);
#define	drm_smmap smmap64
#elif defined(_SYSCALL32_IMPL) || defined(_ILP32)
extern caddr_t smmap32(caddr32_t, size32_t, int, int, int, off32_t);
#define	drm_smmap smmap32
#else
#error "No define for _LP64, _SYSCALL32_IMPL or _ILP32"
#endif

#define	PAGE_MASK	(~(PAGE_SIZE - 1))
#define	round_page(x)	(((x) + (PAGE_SIZE - 1)) & PAGE_MASK)

static struct drm_map_list *drm_find_matching_map(struct drm_device *dev,
						  struct drm_local_map *map)
{
	struct drm_map_list *entry;
	list_for_each_entry(entry, struct drm_map_list, &dev->maplist, head) {
		/*
		 * Because the kernel-userspace ABI is fixed at a 32-bit offset
		 * while PCI resources may live above that, we ignore the map
		 * offset for maps of type _DRM_FRAMEBUFFER or _DRM_REGISTERS.
		 * It is assumed that each driver will have only one resource of
		 * each type.
		 */
		if (!entry->map ||
		    map->type != entry->map->type ||
		    entry->master != dev->primary->master)
			continue;
		switch (map->type) {
		case _DRM_SHM:
			if (map->flags != _DRM_CONTAINS_LOCK)
				break;
			return entry;
		case _DRM_REGISTERS:
		case _DRM_FRAME_BUFFER:
			if ((entry->map->offset & 0xffffffff) ==
			    (map->offset & 0xffffffff))
			return entry;
		default: /* Make gcc happy */
			;
		}
		if (entry->map->offset == map->offset)
			return entry;
	}

	return NULL;
}

int drm_map_handle(struct drm_device *dev, struct drm_map_list *list)
{
	int newid, ret;

	ret = idr_get_new_above(&dev->map_idr, list, 1, &newid);
	if (ret < 0)
		return ret;

	list->user_token = newid << PAGE_SHIFT;
	return 0;
}

/**
 * Core function to create a range of memory available for mapping by a
 * non-root process.
 *
 * Adjusts the memory offset to its absolute value according to the mapping
 * type.  Adds the map to the map list drm_device::maplist. Adds MTRR's where
 * applicable and if supported by the kernel.
 */
static int drm_addmap_core(struct drm_device *dev, unsigned long offset,
			   unsigned long size, enum drm_map_type type,
			   enum drm_map_flags flags,
			   struct drm_map_list ** maplist)
{
	struct drm_local_map *map;
	struct drm_map_list *list;
	/* LINTED */
	unsigned long user_token;
	int ret;

	map = kmalloc(sizeof(*map), GFP_KERNEL);
	if (!map)
		return -ENOMEM;

	map->offset = offset;
	map->size = size;
	map->flags = flags;
	map->type = type;

	/* Only allow shared memory to be removable since we only keep enough
	 * book keeping information about shared memory to allow for removal
	 * when processes fork.
	 */
	if ((map->flags & _DRM_REMOVABLE) && map->type != _DRM_SHM) {
		kfree(map, sizeof(*map));
		return -EINVAL;
	}
	DRM_DEBUG("offset = 0x%08llx, size = 0x%08lx, type = %d\n",
		  (unsigned long long)map->offset, map->size, map->type);

	/* page-align _DRM_SHM maps. They are allocated here so there is no security
	 * hole created by that and it works around various broken drivers that use
	 * a non-aligned quantity to map the SAREA. --BenH
	 */
	if (map->type == _DRM_SHM)
		map->size = PAGE_ALIGN(map->size);

	if ((map->offset & (~(resource_size_t)PAGE_MASK)) || (map->size & (~PAGE_MASK))) {
		kfree(map, sizeof(*map));
		return -EINVAL;
	}

	if (map->offset + map->size < map->offset) {
		kfree(map, sizeof(*map));
		return -EINVAL;
	}

	map->mtrr = -1;
	map->handle = NULL;

	switch (map->type) {
	case _DRM_REGISTERS:
	case _DRM_FRAME_BUFFER:
		/* Some drivers preinitialize some maps, without the X Server
		 * needing to be aware of it.  Therefore, we just return success
		 * when the server tries to create a duplicate map.
		 */
		list = drm_find_matching_map(dev, map);
		if (list != NULL) {
			if (list->map->size != map->size) {
				DRM_DEBUG("Matching maps of type %d with "
					  "mismatched sizes, (%ld vs %ld)\n",
					  map->type, map->size,
					  list->map->size);
				list->map->size = map->size;
			}

			kfree(map, sizeof(struct drm_local_map));
			*maplist = list;
			return 0;
		}

		if (map->type == _DRM_REGISTERS) {
			map->handle = ioremap(map->offset, map->size);
			if (!map->handle) {
				kfree(map, sizeof(struct drm_local_map));
				return -ENOMEM;
			}
		}

		break;
	case _DRM_SHM:
		list = drm_find_matching_map(dev, map);
		if (list != NULL) {
			if(list->map->size != map->size) {
				DRM_DEBUG("Matching maps of type %d with "
					  "mismatched sizes, (%ld vs %ld)\n",
					  map->type, map->size, list->map->size);
				list->map->size = map->size;
			}

			kfree(map, sizeof(struct drm_local_map));
			*maplist = list;
			return 0;
		}
		map->handle = ddi_umem_alloc(map->size, DDI_UMEM_NOSLEEP, &map->umem_cookie);
		DRM_DEBUG("%lu %p\n",
			  map->size, map->handle);
		if (!map->handle) {
			kfree(map, sizeof(struct drm_local_map));
			return -ENOMEM;
		}
		map->offset = (uintptr_t)map->handle;
		if (map->flags & _DRM_CONTAINS_LOCK) {
			/* Prevent a 2nd X Server from creating a 2nd lock */
			if (dev->primary->master->lock.hw_lock != NULL) {
				ddi_umem_free(map->umem_cookie);
				kfree(map, sizeof(struct drm_local_map));
				return -EBUSY;
			}
			dev->primary->master->lock.hw_lock = map->handle; /* Pointer to lock */
		}
		break;
	case _DRM_AGP: {
		caddr_t kvaddr;

		if (!drm_core_has_AGP(dev)) {
			kfree(map, sizeof(struct drm_local_map));
			return -EINVAL;
		}

		map->offset += dev->agp->base;
		kvaddr = gfxp_alloc_kernel_space(map->size);
		if (!kvaddr) {
			DRM_ERROR("failed to alloc AGP aperture");
			kfree(map, sizeof(struct drm_local_map));
			return -EPERM;
		}
		gfxp_load_kernel_space(map->offset, map->size,
		    GFXP_MEMORY_WRITECOMBINED, kvaddr);
		map->handle = (void *)(uintptr_t)kvaddr;
		map->umem_cookie = gfxp_umem_cookie_init(map->handle, map->size);
		if (!map->umem_cookie) {
			DRM_ERROR("gfxp_umem_cookie_init() failed");
			gfxp_unmap_kernel_space(map->handle, map->size);
			kfree(map, sizeof(struct drm_local_map));
			return (-ENOMEM);
		}
		break;
	}
	case _DRM_GEM:
		DRM_ERROR("tried to addmap GEM object\n");
		break;
	case _DRM_SCATTER_GATHER:
		if (!dev->sg) {
			kfree(map, sizeof(struct drm_local_map));
			return -EINVAL;
		}
		map->offset += (uintptr_t)dev->sg->virtual;
		map->handle = (void *)map->offset;
		map->umem_cookie = gfxp_umem_cookie_init(map->handle, map->size);
		if (!map->umem_cookie) {
			DRM_ERROR("gfxp_umem_cookie_init() failed");
			kfree(map, sizeof(struct drm_local_map));
			return (-ENOMEM);
		}
		break;
	case _DRM_CONSISTENT:
		DRM_ERROR("%d DRM_AGP_CONSISTENT", __LINE__);
		kfree(map, sizeof(struct drm_local_map));
		return -ENOTSUP;
	default:
		kfree(map, sizeof(struct drm_local_map));
		return -EINVAL;
	}

	list = kmalloc(sizeof(*list), GFP_KERNEL);
	if (!list) {
		if (map->type == _DRM_REGISTERS)
			iounmap(map->handle);
		kfree(map, sizeof(struct drm_local_map));
		return -EINVAL;
	}
	(void) memset(list, 0, sizeof(*list));
	list->map = map;

	mutex_lock(&dev->struct_mutex);
	list_add(&list->head, &dev->maplist, (caddr_t)list);

	/* Assign a 32-bit handle */
	/* We do it here so that dev->struct_mutex protects the increment */
	user_token = (map->type == _DRM_SHM) ? (unsigned long)map->handle :
		map->offset;
	ret = drm_map_handle(dev, list);
	if (ret) {
		if (map->type == _DRM_REGISTERS)
			iounmap(map->handle);
		kfree(map, sizeof(struct drm_local_map));
		kfree(list, sizeof(struct drm_map_list));
		mutex_unlock(&dev->struct_mutex);
		return ret;
	}

	mutex_unlock(&dev->struct_mutex);

	if (!(map->flags & _DRM_DRIVER))
		list->master = dev->primary->master;
	*maplist = list;
	return 0;
}

int drm_addmap(struct drm_device *dev, unsigned long offset,
	       unsigned long size, enum drm_map_type type,
	       enum drm_map_flags flags, struct drm_local_map ** map_ptr)
{
	struct drm_map_list *list;
	int rc;

	rc = drm_addmap_core(dev, offset, size, type, flags, &list);
	if (!rc)
		*map_ptr = list->map;
	return rc;
}

/**
 * Ioctl to specify a range of memory that is available for mapping by a
 * non-root process.
 *
 * \param inode device inode.
 * \param file_priv DRM file private.
 * \param cmd command.
 * \param arg pointer to a drm_map structure.
 * \return zero on success or a negative value on error.
 *
 */
/* LINTED */
int drm_addmap_ioctl(DRM_IOCTL_ARGS)
{
	struct drm_map *map = data;
	struct drm_map_list *maplist;
	int err;

	if (!(DRM_SUSER(credp) || map->type == _DRM_AGP || map->type == _DRM_SHM))
		return -EPERM;

	err = drm_addmap_core(dev, map->offset, map->size, map->type,
			      map->flags, &maplist);

	if (err)
		return err;

	/* avoid a warning on 64-bit, this casting isn't very nice, but the API is set so too late */
	map->handle = maplist->user_token;
	return 0;
}

/**
 * Remove a map private from list and deallocate resources if the mapping
 * isn't in use.
 *
 * Searches the map on drm_device::maplist, removes it from the list, see if
 * its being used, and free any associate resource (such as MTRR's) if it's not
 * being on use.
 *
 * \sa drm_addmap
 */
int drm_rmmap_locked(struct drm_device *dev, struct drm_local_map *map)
{
	struct drm_map_list *r_list = NULL, *list_t;
	/* LINTED */
	drm_dma_handle_t dmah;
	int found = 0;
	/* LINTED */
	struct drm_master *master;

	/* Find the list entry for the map and remove it */
	list_for_each_entry_safe(r_list, list_t, struct drm_map_list, &dev->maplist, head) {
		if (r_list->map == map) {
			master = r_list->master;
			list_del(&r_list->head);
			(void) idr_remove(&dev->map_idr,
					  r_list->user_token >> PAGE_SHIFT);
			kfree(r_list, sizeof(struct drm_map_list));
			found = 1;
			break;
		}
	}

	if (!found)
		return -EINVAL;

	switch (map->type) {
	case _DRM_REGISTERS:
		iounmap(map->handle);
		/* FALLTHROUGH */
	case _DRM_FRAME_BUFFER:
		break;
	case _DRM_SHM:
		ddi_umem_free(map->umem_cookie);
		break;
	case _DRM_AGP:
		gfxp_umem_cookie_destroy(map->umem_cookie);
		gfxp_unmap_kernel_space(map->handle, map->size);
		break;
	case _DRM_SCATTER_GATHER:
		gfxp_umem_cookie_destroy(map->umem_cookie);
		break;
	case _DRM_CONSISTENT:
		break;
	case _DRM_GEM:
		DRM_ERROR("tried to rmmap GEM object\n");
		break;
	}
	kfree(map, sizeof(struct drm_local_map));

	return 0;
}

int drm_rmmap(struct drm_device *dev, struct drm_local_map *map)
{
	int ret;

	mutex_lock(&dev->struct_mutex);
	ret = drm_rmmap_locked(dev, map);
	mutex_unlock(&dev->struct_mutex);

	return ret;
}

/* The rmmap ioctl appears to be unnecessary.  All mappings are torn down on
 * the last close of the device, and this is necessary for cleanup when things
 * exit uncleanly.  Therefore, having userland manually remove mappings seems
 * like a pointless exercise since they're going away anyway.
 *
 * One use case might be after addmap is allowed for normal users for SHM and
 * gets used by drivers that the server doesn't need to care about.  This seems
 * unlikely.
 *
 * \param inode device inode.
 * \param file_priv DRM file private.
 * \param cmd command.
 * \param arg pointer to a struct drm_map structure.
 * \return zero on success or a negative value on error.
 */
/* LINTED */
int drm_rmmap_ioctl(DRM_IOCTL_ARGS)
{
	struct drm_map *request = data;
	struct drm_local_map *map = NULL;
	struct drm_map_list *r_list;
	int ret;

	mutex_lock(&dev->struct_mutex);
	list_for_each_entry(r_list, struct drm_map_list, &dev->maplist, head) {
		if (r_list->map &&
		    r_list->user_token == (unsigned long)request->handle &&
		    r_list->map->flags & _DRM_REMOVABLE) {
			map = r_list->map;
			break;
		}
	}

	/* List has wrapped around to the head pointer, or its empty we didn't
	 * find anything.
	 */
	if (list_empty(&dev->maplist) || !map) {
		mutex_unlock(&dev->struct_mutex);
		return -EINVAL;
	}

	/* Register and framebuffer maps are permanent */
	if ((map->type == _DRM_REGISTERS) || (map->type == _DRM_FRAME_BUFFER)) {
		mutex_unlock(&dev->struct_mutex);
		return 0;
	}

	ret = drm_rmmap_locked(dev, map);

	mutex_unlock(&dev->struct_mutex);

	return ret;
}

/**
 * Cleanup after an error on one of the addbufs() functions.
 *
 * \param dev DRM device.
 * \param entry buffer entry where the error occurred.
 *
 * Frees any pages and buffers associated with the given entry.
 */
/* LINTED */
static void drm_cleanup_buf_error(struct drm_device * dev,
				  struct drm_buf_entry * entry)
{
	int i;

	if (entry->seg_count) {
		for (i = 0; i < entry->seg_count; i++) {
			if (entry->seglist[i]) {
				DRM_ERROR(
				    "drm_cleanup_buf_error: not implemented");
			}
		}
		kfree(entry->seglist, entry->seg_count * sizeof (*entry->seglist));

		entry->seg_count = 0;
	}

	if (entry->buf_count) {
		for (i = 0; i < entry->buf_count; i++) {
			if (entry->buflist[i].dev_private) {
				kfree(entry->buflist[i].dev_private,
				    entry->buflist[i].dev_priv_size);
			}
		}
		kfree(entry->buflist, entry->buf_count * sizeof (*entry->buflist));

		entry->buf_count = 0;
	}
}

/**
 * Add AGP buffers for DMA transfers.
 *
 * \param dev struct drm_device to which the buffers are to be added.
 * \param request pointer to a struct drm_buf_desc describing the request.
 * \return zero on success or a negative number on failure.
 *
 * After some sanity checks creates a drm_buf structure for each buffer and
 * reallocates the buffer list of the same size order to accommodate the new
 * buffers.
 */
/* LINTED */
int drm_addbufs_agp(struct drm_device * dev, struct drm_buf_desc * request, cred_t *credp)
{
	struct drm_device_dma *dma = dev->dma;
	struct drm_buf_entry *entry;
	struct drm_buf *buf;
	unsigned long offset;
	unsigned long agp_offset;
	int count;
	int order;
	int size;
	int alignment;
	int page_order;
	int total;
	int byte_count;
	int i;
	struct drm_buf **temp_buflist;

	if (!dma)
		return -EINVAL;

	count = request->count;
	order = drm_order(request->size);
	size = 1 << order;

	alignment = (request->flags & _DRM_PAGE_ALIGN)
	    ? round_page(size) : size;
	page_order = order - PAGE_SHIFT > 0 ? order - PAGE_SHIFT : 0;
	total = PAGE_SIZE << page_order;

	byte_count = 0;
	agp_offset = dev->agp->base + request->agp_start;

	DRM_DEBUG("count:      %d\n", count);
	DRM_DEBUG("order:      %d\n", order);
	DRM_DEBUG("size:       %d\n", size);
	DRM_DEBUG("agp_offset: %lx\n", agp_offset);
	DRM_DEBUG("alignment:  %d\n", alignment);
	DRM_DEBUG("page_order: %d\n", page_order);
	DRM_DEBUG("total:      %d\n", total);

	if (order < DRM_MIN_ORDER || order > DRM_MAX_ORDER)
		return -EINVAL;

	spin_lock(&dev->count_lock);
	if (dev->buf_use) {
		spin_unlock(&dev->count_lock);
		return -EBUSY;
	}
	atomic_inc(&dev->buf_alloc);
	spin_unlock(&dev->count_lock);

	mutex_lock(&dev->struct_mutex);
	entry = &dma->bufs[order];
	if (entry->buf_count) {
		mutex_unlock(&dev->struct_mutex);
		atomic_dec(&dev->buf_alloc);
		return -ENOMEM;	/* May only call once for each order */
	}

	if (count < 0 || count > 4096) {
		mutex_unlock(&dev->struct_mutex);
		atomic_dec(&dev->buf_alloc);
		return -EINVAL;
	}

	entry->buflist = kmalloc(count * sizeof(*entry->buflist), GFP_KERNEL);
	if (!entry->buflist) {
		mutex_unlock(&dev->struct_mutex);
		atomic_dec(&dev->buf_alloc);
		return -ENOMEM;
	}
	(void) memset(entry->buflist, 0, count * sizeof(*entry->buflist));

	entry->buf_size = size;
	entry->page_order = page_order;

	offset = 0;

	while (entry->buf_count < count) {
		buf = &entry->buflist[entry->buf_count];
		buf->idx = dma->buf_count + entry->buf_count;
		buf->total = alignment;
		buf->order = order;
		buf->used = 0;

		buf->offset = (dma->byte_count + offset);
		buf->bus_address = agp_offset + offset;
		buf->address = (void *)(agp_offset + offset);
		buf->next = NULL;
		buf->pending = 0;
		buf->file_priv = NULL;

		buf->dev_priv_size = dev->driver->buf_priv_size;
		buf->dev_private = kmalloc(buf->dev_priv_size, GFP_KERNEL);
		if (!buf->dev_private) {
			/* Set count correctly so we free the proper amount. */
			entry->buf_count = count;
			drm_cleanup_buf_error(dev, entry);
			mutex_unlock(&dev->struct_mutex);
			atomic_dec(&dev->buf_alloc);
			return -ENOMEM;
		}
		(void) memset(buf->dev_private, 0, buf->dev_priv_size);

		DRM_DEBUG("buffer %d @ %p\n", entry->buf_count, buf->address);

		offset += alignment;
		entry->buf_count++;
		byte_count += PAGE_SIZE << page_order;
	}

	DRM_DEBUG("byte_count: %d\n", byte_count);

	temp_buflist = kmalloc(
				(dma->buf_count + entry->buf_count) *
				sizeof(*dma->buflist), GFP_KERNEL);
	if (!temp_buflist) {
		/* Free the entry because it isn't valid */
		drm_cleanup_buf_error(dev, entry);
		mutex_unlock(&dev->struct_mutex);
		atomic_dec(&dev->buf_alloc);
		return -ENOMEM;
	}
	bcopy(temp_buflist, dma->buflist,
	    dma->buf_count * sizeof (*dma->buflist));
	kmem_free(dma->buflist, dma->buf_count *sizeof (*dma->buflist));
	dma->buflist = temp_buflist;

	for (i = 0; i < entry->buf_count; i++) {
		dma->buflist[i + dma->buf_count] = &entry->buflist[i];
	}

	dma->buf_count += entry->buf_count;
	dma->seg_count += entry->seg_count;
	dma->page_count += byte_count >> PAGE_SHIFT;
	dma->byte_count += byte_count;

	DRM_DEBUG("dma->buf_count : %d\n", dma->buf_count);
	DRM_DEBUG("entry->buf_count : %d\n", entry->buf_count);

	mutex_unlock(&dev->struct_mutex);

	request->count = entry->buf_count;
	request->size = size;

	dma->flags = _DRM_DMA_USE_AGP;

	atomic_dec(&dev->buf_alloc);
	return 0;
}

static int drm_addbufs_sg(struct drm_device * dev, struct drm_buf_desc * request, cred_t *credp)
{
	struct drm_device_dma *dma = dev->dma;
	struct drm_buf_entry *entry;
	struct drm_buf *buf;
	unsigned long offset;
	unsigned long agp_offset;
	int count;
	int order;
	int size;
	int alignment;
	int page_order;
	int total;
	int byte_count;
	int i;
	struct drm_buf **temp_buflist;

	if (!drm_core_check_feature(dev, DRIVER_SG))
		return -EINVAL;

	if (!dma)
		return -EINVAL;

	if (!DRM_SUSER(credp))
		return -EPERM;

	count = request->count;
	order = drm_order(request->size);
	size = 1 << order;

	alignment = (request->flags & _DRM_PAGE_ALIGN)
	    ? round_page(size) : size;
	page_order = order - PAGE_SHIFT > 0 ? order - PAGE_SHIFT : 0;
	total = PAGE_SIZE << page_order;

	byte_count = 0;
	agp_offset = request->agp_start;

	DRM_DEBUG("count:      %d\n", count);
	DRM_DEBUG("order:      %d\n", order);
	DRM_DEBUG("size:       %d\n", size);
	DRM_DEBUG("agp_offset: %lu\n", agp_offset);
	DRM_DEBUG("alignment:  %d\n", alignment);
	DRM_DEBUG("page_order: %d\n", page_order);
	DRM_DEBUG("total:      %d\n", total);

	if (order < DRM_MIN_ORDER || order > DRM_MAX_ORDER)
		return -EINVAL;

	spin_lock(&dev->count_lock);
	if (dev->buf_use) {
		spin_unlock(&dev->count_lock);
		return -EBUSY;
	}
	atomic_inc(&dev->buf_alloc);
	spin_unlock(&dev->count_lock);

	mutex_lock(&dev->struct_mutex);
	entry = &dma->bufs[order];
	if (entry->buf_count) {
		mutex_unlock(&dev->struct_mutex);
		atomic_dec(&dev->buf_alloc);
		return -ENOMEM;	/* May only call once for each order */
	}

	if (count < 0 || count > 4096) {
		mutex_unlock(&dev->struct_mutex);
		atomic_dec(&dev->buf_alloc);
		return -EINVAL;
	}

	entry->buflist = kmalloc(count * sizeof(*entry->buflist),
				GFP_KERNEL);
	if (!entry->buflist) {
		mutex_unlock(&dev->struct_mutex);
		atomic_dec(&dev->buf_alloc);
		return -ENOMEM;
	}
	(void) memset(entry->buflist, 0, count * sizeof(*entry->buflist));

	entry->buf_size = size;
	entry->page_order = page_order;

	offset = 0;

	while (entry->buf_count < count) {
		buf = &entry->buflist[entry->buf_count];
		buf->idx = dma->buf_count + entry->buf_count;
		buf->total = alignment;
		buf->order = order;
		buf->used = 0;

		buf->offset = (dma->byte_count + offset);
		buf->bus_address = agp_offset + offset;
		buf->address = (void *)(agp_offset + offset + dev->sg->handle);
		buf->next = NULL;
		buf->pending = 0;
		buf->file_priv = NULL;

		buf->dev_priv_size = dev->driver->buf_priv_size;
		buf->dev_private = kmalloc(buf->dev_priv_size, GFP_KERNEL);
		if (!buf->dev_private) {
			/* Set count correctly so we free the proper amount. */
			entry->buf_count = count;
			drm_cleanup_buf_error(dev, entry);
			mutex_unlock(&dev->struct_mutex);
			atomic_dec(&dev->buf_alloc);
			return -ENOMEM;
		}

		(void) memset(buf->dev_private, 0, buf->dev_priv_size);

		DRM_DEBUG("buffer %d @ %p\n", entry->buf_count, buf->address);

		offset += alignment;
		entry->buf_count++;
		byte_count += PAGE_SIZE << page_order;
	}

	DRM_DEBUG("byte_count: %d\n", byte_count);

	temp_buflist = drm_realloc(dma->buflist,
	    dma->buf_count * sizeof (*dma->buflist),
	    (dma->buf_count + entry->buf_count)
	    * sizeof (*dma->buflist), DRM_MEM_BUFS);
	if (!temp_buflist) {
		/* Free the entry because it isn't valid */
		drm_cleanup_buf_error(dev, entry);
		mutex_unlock(&dev->struct_mutex);
		atomic_dec(&dev->buf_alloc);
		return -ENOMEM;
	}
	dma->buflist = temp_buflist;

	for (i = 0; i < entry->buf_count; i++) {
		dma->buflist[i + dma->buf_count] = &entry->buflist[i];
	}

	dma->buf_count += entry->buf_count;
	dma->byte_count += byte_count;

	DRM_DEBUG("dma->buf_count : %d\n", dma->buf_count);
	DRM_DEBUG("entry->buf_count : %d\n", entry->buf_count);

	mutex_unlock(&dev->struct_mutex);

	request->count = entry->buf_count;
	request->size = size;

	dma->flags = _DRM_DMA_USE_SG;

	atomic_dec(&dev->buf_alloc);
	return 0;
}

/**
 * Add buffers for DMA transfers (ioctl).
 *
 * \param inode device inode.
 * \param file_priv DRM file private.
 * \param cmd command.
 * \param arg pointer to a struct drm_buf_desc request.
 * \return zero on success or a negative number on failure.
 *
 * According with the memory type specified in drm_buf_desc::flags and the
 * build options, it dispatches the call either to addbufs_agp(),
 * addbufs_sg() or addbufs_pci() for AGP, scatter-gather or consistent
 * PCI memory respectively.
 */
/* LINTED */
int drm_addbufs(DRM_IOCTL_ARGS)
{
	struct drm_buf_desc *request = data;
	int ret = -EINVAL;

	if (!drm_core_check_feature(dev, DRIVER_HAVE_DMA))
		return -EINVAL;

	if (request->flags & _DRM_AGP_BUFFER)
		ret = drm_addbufs_agp(dev, request, credp);
	else
	if (request->flags & _DRM_SG_BUFFER)
		ret = drm_addbufs_sg(dev, request, credp);

	return ret;
}

/**
 * Get information about the buffer mappings.
 *
 * This was originally mean for debugging purposes, or by a sophisticated
 * client library to determine how best to use the available buffers (e.g.,
 * large buffers can be used for image transfer).
 *
 * \param inode device inode.
 * \param file_priv DRM file private.
 * \param cmd command.
 * \param arg pointer to a drm_buf_info structure.
 * \return zero on success or a negative number on failure.
 *
 * Increments drm_device::buf_use while holding the drm_device::count_lock
 * lock, preventing of allocating more buffers after this call. Information
 * about each requested buffer is then copied into user space.
 */
/* LINTED */
int drm_infobufs(DRM_IOCTL_ARGS)
{
	struct drm_device_dma *dma = dev->dma;
	struct drm_buf_info *request = data;
	int i;
	int count;

	if (!drm_core_check_feature(dev, DRIVER_HAVE_DMA))
		return -EINVAL;

	if (!dma)
		return -EINVAL;

	spin_lock(&dev->count_lock);
	if (atomic_read(&dev->buf_alloc)) {
		spin_unlock(&dev->count_lock);
		return -EBUSY;
	}
	++dev->buf_use;		/* Can't allocate more after this call */
	spin_unlock(&dev->count_lock);

	for (i = 0, count = 0; i < DRM_MAX_ORDER + 1; i++) {
		if (dma->bufs[i].buf_count)
			++count;
	}

	DRM_DEBUG("count = %d\n", count);

	if (request->count >= count) {
		for (i = 0, count = 0; i < DRM_MAX_ORDER + 1; i++) {
			if (dma->bufs[i].buf_count) {
				struct drm_buf_desc __user *to =
				    &request->list[count];
				struct drm_buf_entry *from = &dma->bufs[i];
				struct drm_freelist *list = &dma->bufs[i].freelist;
				if (copy_to_user(&to->count,
						 &from->buf_count,
						 sizeof(from->buf_count)) ||
				    copy_to_user(&to->size,
						 &from->buf_size,
						 sizeof(from->buf_size)) ||
				    copy_to_user(&to->low_mark,
						 &list->low_mark,
						 sizeof(list->low_mark)) ||
				    copy_to_user(&to->high_mark,
						 &list->high_mark,
						 sizeof(list->high_mark)))
					return -EFAULT;

				DRM_DEBUG("%d %d %d %d %d\n",
					  i,
					  dma->bufs[i].buf_count,
					  dma->bufs[i].buf_size,
					  dma->bufs[i].freelist.low_mark,
					  dma->bufs[i].freelist.high_mark);
				++count;
			}
		}
	}
	request->count = count;

	return 0;
}

/**
 * Specifies a low and high water mark for buffer allocation
 *
 * \param inode device inode.
 * \param file_priv DRM file private.
 * \param cmd command.
 * \param arg a pointer to a drm_buf_desc structure.
 * \return zero on success or a negative number on failure.
 *
 * Verifies that the size order is bounded between the admissible orders and
 * updates the respective drm_device_dma::bufs entry low and high water mark.
 *
 * \note This ioctl is deprecated and mostly never used.
 */
/* LINTED */
int drm_markbufs(DRM_IOCTL_ARGS)
{
	struct drm_device_dma *dma = dev->dma;
	struct drm_buf_desc *request = data;
	int order;
	struct drm_buf_entry *entry;

	if (!drm_core_check_feature(dev, DRIVER_HAVE_DMA))
		return -EINVAL;

	if (!dma)
		return -EINVAL;

	DRM_DEBUG("%d, %d, %d\n",
		  request->size, request->low_mark, request->high_mark);
	order = drm_order(request->size);
	if (order < DRM_MIN_ORDER || order > DRM_MAX_ORDER)
		return -EINVAL;
	entry = &dma->bufs[order];

	if (request->low_mark < 0 || request->low_mark > entry->buf_count)
		return -EINVAL;
	if (request->high_mark < 0 || request->high_mark > entry->buf_count)
		return -EINVAL;

	entry->freelist.low_mark = request->low_mark;
	entry->freelist.high_mark = request->high_mark;

	return 0;
}

/**
 * Unreserve the buffers in list, previously reserved using drmDMA.
 *
 * \param inode device inode.
 * \param file_priv DRM file private.
 * \param cmd command.
 * \param arg pointer to a drm_buf_free structure.
 * \return zero on success or a negative number on failure.
 *
 * Calls free_buffer() for each used buffer.
 * This function is primarily used for debugging.
 */
/* LINTED */
int drm_freebufs(DRM_IOCTL_ARGS)
{
	struct drm_device_dma *dma = dev->dma;
	struct drm_buf_free *request = data;
	int i;
	int idx;
	struct drm_buf *buf;

	if (!drm_core_check_feature(dev, DRIVER_HAVE_DMA))
		return -EINVAL;

	if (!dma)
		return -EINVAL;

	DRM_DEBUG("%d\n", request->count);
	for (i = 0; i < request->count; i++) {
		if (DRM_COPY_FROM_USER(&idx, &request->list[i], sizeof (idx)))
			return -EFAULT;
		if (idx < 0 || idx >= dma->buf_count) {
			DRM_ERROR("Index %d (of %d max)\n",
				  idx, dma->buf_count - 1);
			return -EINVAL;
		}
		buf = dma->buflist[idx];
		if (buf->file_priv != file) {
			DRM_ERROR("Process %d freeing buffer not owned\n",
			    DRM_CURRENTPID);
			return -EINVAL;
		}
		drm_free_buffer(dev, buf);
	}

	return 0;
}

/**
 * Maps all of the DMA buffers into client-virtual space (ioctl).
 *
 * \param inode device inode.
 * \param file_priv DRM file private.
 * \param cmd command.
 * \param arg pointer to a drm_buf_map structure.
 * \return zero on success or a negative number on failure.
 *
 * Maps the AGP, SG or PCI buffer region with do_mmap(), and copies information
 * about each buffer into user space. For PCI buffers, it calls do_mmap() with
 * offset equal to 0, which drm_mmap() interpretes as PCI buffers and calls
 * drm_mmap_dma().
 */
/* LINTED */
int drm_mapbufs(DRM_IOCTL_ARGS)
{
	struct drm_device_dma *dma = dev->dma;
	int retcode = 0;
	const int zero = 0;
	unsigned long virtual;
	unsigned long address;
	struct drm_buf_map *request = data;
	int i;
	uint_t size, foff;

#ifdef _MULTI_DATAMODEL
	struct drm_buf_pub_32 *list32;
	uint_t address32;
#endif

	if (!drm_core_check_feature(dev, DRIVER_HAVE_DMA))
		return -EINVAL;

	if (!dma)
		return -EINVAL;

	spin_lock(&dev->count_lock);
	if (atomic_read(&dev->buf_alloc)) {
		spin_unlock(&dev->count_lock);
		return -EBUSY;
	}
	dev->buf_use++;		/* Can't allocate more after this call */
	spin_unlock(&dev->count_lock);

	if (request->count >= dma->buf_count) {
		if ((drm_core_has_AGP(dev) && (dma->flags & _DRM_DMA_USE_AGP))
		    || (drm_core_check_feature(dev, DRIVER_SG)
		    && (dma->flags & _DRM_DMA_USE_SG))) {
			struct drm_local_map *map = dev->agp_buffer_map;

			if (!map) {
				retcode = -EINVAL;
				goto done;
			}
			size = round_page(map->size);
			foff = (uintptr_t)map->handle;
		} else {
			size = round_page(dma->byte_count);
			foff = 0;
		}
		request->virtual = drm_smmap(NULL, size, PROT_READ | PROT_WRITE,
		    MAP_SHARED, request->fd, foff);
		if (request->virtual == NULL) {
			DRM_ERROR("request->virtual is NULL");
			retcode = -EINVAL;
			goto done;
		}

		virtual = (unsigned long) request->virtual;

#ifdef _MULTI_DATAMODEL
		if (ddi_model_convert_from(ioctl_mode & FMODELS) == DDI_MODEL_ILP32) {
			list32 = (drm_buf_pub_32_t *)(uintptr_t)request->list;
			for (i = 0; i < dma->buf_count; i++) {
				if (DRM_COPY_TO_USER(&list32[i].idx,
				    &dma->buflist[i]->idx,
				    sizeof (list32[0].idx))) {
					retcode = -EFAULT;
					goto done;
				}
				if (DRM_COPY_TO_USER(&list32[i].total,
				    &dma->buflist[i]->total,
				    sizeof (list32[0].total))) {
					retcode = -EFAULT;
					goto done;
				}
				if (DRM_COPY_TO_USER(&list32[i].used,
				    &zero, sizeof (zero))) {
					retcode = -EFAULT;
					goto done;
				}
				address32 = virtual + dma->buflist[i]->offset; /* *** */
				if (DRM_COPY_TO_USER(&list32[i].address,
				    &address32, sizeof (list32[0].address))) {
					retcode = -EFAULT;
					goto done;
				}
			}
		} else {
#endif
			for (i = 0; i < dma->buf_count; i++) {
				if (DRM_COPY_TO_USER(&request->list[i].idx,
				    &dma->buflist[i]->idx,
				    sizeof (request->list[0].idx))) {
					retcode = -EFAULT;
					goto done;
				}
				if (DRM_COPY_TO_USER(&request->list[i].total,
				    &dma->buflist[i]->total,
				    sizeof (request->list[0].total))) {
					retcode = -EFAULT;
					goto done;
				}
				if (DRM_COPY_TO_USER(&request->list[i].used, &zero,
				    sizeof (zero))) {
					retcode = -EFAULT;
					goto done;
				}
				address = virtual + dma->buflist[i]->offset; /* *** */

				if (DRM_COPY_TO_USER(&request->list[i].address,
				    &address, sizeof (address))) {
					retcode = -EFAULT;
					goto done;
				}
			}
#ifdef _MULTI_DATAMODEL
		}
#endif
	}
      done:
	request->count = dma->buf_count;
	DRM_DEBUG("%d buffers, retcode = %d\n", request->count, retcode);

	return retcode;
}

/**
 * Compute size order.  Returns the exponent of the smaller power of two which
 * is greater or equal to given number.
 *
 * \param size size.
 * \return order.
 *
 * \todo Can be made faster.
 */
int drm_order(unsigned long size)
{
	int order;
	unsigned long tmp;

	for (order = 0, tmp = size >> 1; tmp; tmp >>= 1, order++) ;

	if (size & (size - 1))
		++order;

	return order;
}
