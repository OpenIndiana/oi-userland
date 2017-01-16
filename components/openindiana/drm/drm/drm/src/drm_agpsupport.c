/*
 * Copyright (c) 2006, 2013, Oracle and/or its affiliates. All rights reserved.
 */

/**
 * \file drm_agpsupport.c
 * DRM support for AGP/GART backend
 *
 * \author Rickard E. (Rik) Faith <faith@valinux.com>
 * \author Gareth Hughes <gareth@valinux.com>
 */

/*
 * Copyright 1999 Precision Insight, Inc., Cedar Park, Texas.
 * Copyright 2000 VA Linux Systems, Inc., Sunnyvale, California.
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
 * VA LINUX SYSTEMS AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#include "drm.h"
#include "drmP.h"

#ifndef	AGP_PAGE_SIZE
#define	AGP_PAGE_SIZE 4096
#define	AGP_PAGE_SHIFT 12
#endif

/*
 * The agpa_key field of struct agp_allocate_t actually is
 * an index to an array. It can be zero. But we will use
 * this agpa_key as a handle returned to userland. Generally,
 * 0 is not a valid value for a handle, so we add an offset
 * to the key to get a handle.
 */
#define	DRM_AGP_KEY_OFFSET	8

void drm_agp_cleanup(struct drm_device *dev)
{
	struct drm_agp_head *agp = dev->agp;

	(void) ldi_close(agp->agpgart_lh, FEXCL, kcred);
	ldi_ident_release(agp->agpgart_li);
}

/**
 * Get AGP information.
 *
 * \param inode device inode.
 * \param file_priv DRM file private.
 * \param cmd command.
 * \param arg pointer to a (output) drm_agp_info structure.
 * \return zero on success or a negative number on failure.
 *
 * Verifies the AGP device has been initialized and acquired and fills in the
 * drm_agp_info structure with the information in drm_agp_head::agp_info.
 */
int drm_agp_info(struct drm_device *dev, struct drm_agp_info *info)
{
	agp_info_t *agpinfo;

	if (!dev->agp || !dev->agp->acquired)
		return -EINVAL;

	agpinfo = &dev->agp->agp_info;
	info->agp_version_major = agpinfo->agpi_version.agpv_major;
	info->agp_version_minor = agpinfo->agpi_version.agpv_minor;
	info->mode = agpinfo->agpi_mode;
	info->aperture_base = agpinfo->agpi_aperbase;
	info->aperture_size = agpinfo->agpi_apersize * 1024 * 1024;
	info->memory_allowed = agpinfo->agpi_pgtotal << PAGE_SHIFT;
	info->memory_used = agpinfo->agpi_pgused << PAGE_SHIFT;
	info->id_vendor = agpinfo->agpi_devid & 0xffff;
	info->id_device = agpinfo->agpi_devid >> 16;

	return 0;
}

/* LINTED */
int drm_agp_info_ioctl(DRM_IOCTL_ARGS)
{
	struct drm_agp_info *info = data;
	int err;

	err = drm_agp_info(dev, info);
	if (err)
		return err;

	return 0;
}

/**
 * Acquire the AGP device.
 *
 * \param dev DRM device that is to acquire AGP.
 * \return zero on success or a negative number on failure.
 *
 * Verifies the AGP device hasn't been acquired before and calls
 * \c agp_backend_acquire.
 */
int drm_agp_acquire(struct drm_device * dev)
{
	if (!dev->agp)
		return -ENODEV;
	if (dev->agp->acquired)
		return -EBUSY;
	{
		int ret, rval;
		if (ret = ldi_ioctl(dev->agp->agpgart_lh, AGPIOC_ACQUIRE,
		    (uintptr_t)0, FKIOCTL, kcred, &rval)) {
			DRM_ERROR("AGPIOC_ACQUIRE failed");
			return -ret;
		}
	}
	dev->agp->acquired = 1;
	return 0;
}

/**
 * Acquire the AGP device (ioctl).
 *
 * \param inode device inode.
 * \param file_priv DRM file private.
 * \param cmd command.
 * \param arg user argument.
 * \return zero on success or a negative number on failure.
 *
 * Verifies the AGP device hasn't been acquired before and calls
 * \c agp_backend_acquire.
 */
/* LINTED */
int drm_agp_acquire_ioctl(DRM_IOCTL_ARGS)
{
	return drm_agp_acquire((struct drm_device *) file->minor->dev);
}

/**
 * Release the AGP device.
 *
 * \param dev DRM device that is to release AGP.
 * \return zero on success or a negative number on failure.
 *
 * Verifies the AGP device has been acquired and calls \c agp_backend_release.
 */
int drm_agp_release(struct drm_device * dev)
{
	if (!dev->agp || !dev->agp->acquired)
		return -EINVAL;
	{
		int ret, rval;
		if (ret = ldi_ioctl(dev->agp->agpgart_lh, AGPIOC_RELEASE,
		    (intptr_t)0, FKIOCTL, kcred, &rval)) {
			DRM_ERROR("AGPIOC_RELEASE failed");
			return -ret;
		}
	}
	dev->agp->acquired = 0;
	return 0;
}

/* LINTED */
int drm_agp_release_ioctl(DRM_IOCTL_ARGS)
{
	return drm_agp_release(dev);
}

/**
 * Enable the AGP bus.
 *
 * \param dev DRM device that has previously acquired AGP.
 * \param mode Requested AGP mode.
 * \return zero on success or a negative number on failure.
 *
 * Verifies the AGP device has been acquired but not enabled, and calls
 * \c agp_enable.
 */
int drm_agp_enable(struct drm_device * dev, struct drm_agp_mode mode)
{
	if (!dev->agp || !dev->agp->acquired)
		return -EINVAL;

	dev->agp->mode = mode.mode;
	{
		agp_setup_t setup;
		int ret, rval;
		setup.agps_mode = (uint32_t)mode.mode;
		if (ret = ldi_ioctl(dev->agp->agpgart_lh, AGPIOC_SETUP,
		    (intptr_t)&setup, FKIOCTL, kcred, &rval)) {
			DRM_ERROR("AGPIOC_SETUP failed");
			return -ret;
		}
	}
	dev->agp->enabled = 1;
	return 0;
}

/* LINTED */
int drm_agp_enable_ioctl(DRM_IOCTL_ARGS)
{
	struct drm_agp_mode *mode = data;

	return drm_agp_enable(dev, *mode);
}

/**
 * Allocate AGP memory.
 *
 * \param inode device inode.
 * \param file_priv file private pointer.
 * \param cmd command.
 * \param arg pointer to a drm_agp_buffer structure.
 * \return zero on success or a negative number on failure.
 *
 * Verifies the AGP device is present and has been acquired, allocates the
 * memory via alloc_agp() and creates a drm_agp_mem entry for it.
 */
int drm_agp_alloc(struct drm_device *dev, struct drm_agp_buffer *request)
{
	struct drm_agp_mem *entry;
	agp_allocate_t alloc;
	unsigned long pages;
	int ret, rval;

	if (!dev->agp || !dev->agp->acquired)
		return -EINVAL;
	if (!(entry = kmalloc(sizeof(*entry), GFP_KERNEL)))
		return -ENOMEM;

	(void) memset(entry, 0, sizeof(*entry));

	pages = (request->size + PAGE_SIZE - 1) / PAGE_SIZE;

	alloc.agpa_pgcount = (uint32_t) pages;
	alloc.agpa_type = AGP_NORMAL;
	ret = ldi_ioctl(dev->agp->agpgart_lh, AGPIOC_ALLOCATE,
	    (intptr_t)&alloc, FKIOCTL, kcred, &rval);
	if (ret) {
		DRM_ERROR("AGPIOC_ALLOCATE failed");
		kfree(entry, sizeof (*entry));
		return -ret;
	}

	entry->handle = alloc.agpa_key + DRM_AGP_KEY_OFFSET;
	entry->bound = 0;
	entry->pages = (int) pages;
	list_add(&entry->head, &dev->agp->memory, (caddr_t)entry);

	request->handle = entry->handle;
	request->physical = alloc.agpa_physical;

	return 0;
}

/* LINTED */
int drm_agp_alloc_ioctl(DRM_IOCTL_ARGS)
{
	struct drm_agp_buffer *request = data;

	return drm_agp_alloc(dev, request);
}

/**
 * Search for the AGP memory entry associated with a handle.
 *
 * \param dev DRM device structure.
 * \param handle AGP memory handle.
 * \return pointer to the drm_agp_mem structure associated with \p handle.
 *
 * Walks through drm_agp_head::memory until finding a matching handle.
 */
static struct drm_agp_mem *drm_agp_lookup_entry(struct drm_device * dev,
					   unsigned long handle)
{
	struct drm_agp_mem *entry;

	list_for_each_entry(entry, struct drm_agp_mem, &dev->agp->memory, head) {
		if (entry->handle == handle)
			return entry;
	}
	return NULL;
}

/**
 * Unbind AGP memory from the GATT (ioctl).
 *
 * \param inode device inode.
 * \param file_priv DRM file private.
 * \param cmd command.
 * \param arg pointer to a drm_agp_binding structure.
 * \return zero on success or a negative number on failure.
 *
 * Verifies the AGP device is present and acquired, looks-up the AGP memory
 * entry and passes it to the unbind_agp() function.
 */
int drm_agp_unbind(struct drm_device *dev, struct drm_agp_binding *request)
{
	struct drm_agp_mem *entry;
	int ret;

	if (!dev->agp || !dev->agp->acquired)
		return -EINVAL;
	if (!(entry = drm_agp_lookup_entry(dev, request->handle)))
		return -EINVAL;
	if (!entry->bound)
		return -EINVAL;
	{
		agp_unbind_t unbind;
		int rval;
		unbind.agpu_pri = 0;
		unbind.agpu_key = (uintptr_t)entry->handle - DRM_AGP_KEY_OFFSET;
		if (ret = ldi_ioctl(dev->agp->agpgart_lh, AGPIOC_UNBIND,
		    (intptr_t)&unbind, FKIOCTL, kcred, &rval)) {
			DRM_ERROR("AGPIOC_UNBIND failed");
			return -ret;
		}
	}
		entry->bound = 0;
	return ret;
}

/* LINTED */
int drm_agp_unbind_ioctl(DRM_IOCTL_ARGS)
{
	struct drm_agp_binding *request = data;

	return drm_agp_unbind(dev, request);
}

/**
 * Bind AGP memory into the GATT (ioctl)
 *
 * \param inode device inode.
 * \param file_priv DRM file private.
 * \param cmd command.
 * \param arg pointer to a drm_agp_binding structure.
 * \return zero on success or a negative number on failure.
 *
 * Verifies the AGP device is present and has been acquired and that no memory
 * is currently bound into the GATT. Looks-up the AGP memory entry and passes
 * it to bind_agp() function.
 */
int drm_agp_bind(struct drm_device *dev, struct drm_agp_binding *request)
{
	struct drm_agp_mem *entry;
	int retcode;
	int page;

	if (!dev->agp || !dev->agp->acquired)
		return -EINVAL;
	if (!(entry = drm_agp_lookup_entry(dev, request->handle)))
		return -EINVAL;
	if (entry->bound)
		return -EINVAL;
	page = (request->offset + PAGE_SIZE - 1) / PAGE_SIZE;
	{
		uint_t key = (uintptr_t)entry->handle - DRM_AGP_KEY_OFFSET;
		if (retcode = drm_agp_bind_memory(key, page, dev)) {
			DRM_ERROR("failed key=0x%x, page=0x%x, "
			    "agp_base=0x%lx", key, page, dev->agp->base);
			return retcode;
		}
	}
	entry->bound = dev->agp->base + (page << PAGE_SHIFT);
	DRM_DEBUG("base = 0x%lx entry->bound = 0x%lx\n",
		  dev->agp->base, entry->bound);
	return 0;
}

/* LINTED */
int drm_agp_bind_ioctl(DRM_IOCTL_ARGS)
{
	struct drm_agp_binding *request = data;

	return drm_agp_bind(dev, request);
}

/**
 * Free AGP memory (ioctl).
 *
 * \param inode device inode.
 * \param file_priv DRM file private.
 * \param cmd command.
 * \param arg pointer to a drm_agp_buffer structure.
 * \return zero on success or a negative number on failure.
 *
 * Verifies the AGP device is present and has been acquired and looks up the
 * AGP memory entry. If the memory it's currently bound, unbind it via
 * unbind_agp(). Frees it via free_agp() as well as the entry itself
 * and unlinks from the doubly linked list it's inserted in.
 */
int drm_agp_free(struct drm_device *dev, struct drm_agp_buffer *request)
{
	struct drm_agp_mem *entry;

	if (!dev->agp || !dev->agp->acquired)
		return -EINVAL;
	if (!(entry = drm_agp_lookup_entry(dev, request->handle)))
		return -EINVAL;
	if (entry->bound)
		(void) drm_agp_unbind_memory(request->handle, dev);

	list_del(&entry->head);
	{
		int agpu_key = (uintptr_t)entry->handle - DRM_AGP_KEY_OFFSET;
		int ret, rval;
		ret = ldi_ioctl(dev->agp->agpgart_lh, AGPIOC_DEALLOCATE,
		    (intptr_t)agpu_key, FKIOCTL, kcred, &rval);
		if (ret) {
			DRM_ERROR("AGPIOC_DEALLOCATE failed,"
			    "akey=%d, ret=%d", agpu_key, ret);
			return -ret;
		}
	}
	kfree(entry, sizeof (*entry));
	return 0;
}

/* LINTED */
int drm_agp_free_ioctl(DRM_IOCTL_ARGS)
{
	struct drm_agp_buffer *request = data;

	return drm_agp_free(dev, request);
}

/**
 * Initialize the AGP resources.
 *
 * \return pointer to a drm_agp_head structure.
 *
 * Gets the drm_agp_t structure which is made available by the agpgart module
 * via the inter_module_* functions. Creates and initializes a drm_agp_head
 * structure.
 */
struct drm_agp_head *drm_agp_init(struct drm_device *dev)
{
	struct drm_agp_head *head = NULL;
	int ret, rval;

	if (!(head = kmalloc(sizeof(*head), GFP_KERNEL)))
		return NULL;
	(void) memset((void *)head, 0, sizeof(*head));
	ret = ldi_ident_from_dip(dev->devinfo, &head->agpgart_li);
	if (ret) {
		DRM_ERROR("failed to get layerd ident, ret=%d", ret);
		goto err_1;
	}

	ret = ldi_open_by_name(AGP_DEVICE, FEXCL, kcred,
	    &head->agpgart_lh, head->agpgart_li);
	if (ret) {
		DRM_ERROR("failed to open %s, ret=%d", AGP_DEVICE, ret);
		goto err_2;
	}

	ret = ldi_ioctl(head->agpgart_lh, AGPIOC_INFO,
	    (intptr_t)&head->agp_info, FKIOCTL, kcred, &rval);
	if (ret) {
		DRM_ERROR("failed to get agpinfo, ret=%d", ret);
		goto err_3;
	}
	INIT_LIST_HEAD(&head->memory);
	head->base = head->agp_info.agpi_aperbase;
	return head;

err_3:
	(void) ldi_close(head->agpgart_lh, FEXCL, kcred);
err_2:
	ldi_ident_release(head->agpgart_li);
err_1:
	kfree(head, sizeof(*head));
	return NULL;
}

/* LINTED */
void *drm_agp_allocate_memory(size_t pages, uint32_t type, struct drm_device *dev)
{
	return NULL;
}

/* LINTED */
int drm_agp_free_memory(agp_allocate_t *handle, struct drm_device *dev)
{
	return 1;
}

int drm_agp_bind_memory(unsigned int key, uint32_t start, struct drm_device *dev)
{
	agp_bind_t bind;
	int ret, rval;

	bind.agpb_pgstart = start;
	bind.agpb_key = key;
	if (ret = ldi_ioctl(dev->agp->agpgart_lh, AGPIOC_BIND,
	    (intptr_t)&bind, FKIOCTL, kcred, &rval)) {
		DRM_DEBUG("AGPIOC_BIND failed");
		return -ret;
	}
	return 0;
}

int drm_agp_unbind_memory(unsigned long handle, struct drm_device *dev)
{
	struct drm_agp_mem *entry;
	agp_unbind_t unbind;
	int ret, rval;

	if (!dev->agp || !dev->agp->acquired)
		return -EINVAL;

	entry = drm_agp_lookup_entry(dev, handle);
	if (!entry || !entry->bound)
		return -EINVAL;

	unbind.agpu_pri = 0;
	unbind.agpu_key = (uintptr_t)entry->handle - DRM_AGP_KEY_OFFSET;
	if (ret = ldi_ioctl(dev->agp->agpgart_lh, AGPIOC_UNBIND,
	    (intptr_t)&unbind, FKIOCTL, kcred, &rval)) {
		DRM_ERROR("AGPIO_UNBIND failed");
		return -ret;
	}
	entry->bound = 0;
	return 0;
}

/**
 * Binds a collection of pages into AGP memory at the given offset, returning
 * the AGP memory structure containing them.
 *
 * No reference is held on the pages during this time -- it is up to the
 * caller to handle that.
 */
int
drm_agp_bind_pages(struct drm_device *dev,
		    pfn_t *pages,
		    unsigned long num_pages,
		    uint32_t gtt_offset,
		    unsigned int agp_type)
{
	agp_gtt_info_t bind;
	int ret, rval;

	bind.agp_pgstart = gtt_offset / AGP_PAGE_SIZE;
	bind.agp_npage = num_pages;
	bind.agp_phyaddr = pages;
	bind.agp_flags = agp_type;

	ret = ldi_ioctl(dev->agp->agpgart_lh, AGPIOC_PAGES_BIND,
	    (intptr_t)&bind, FKIOCTL, kcred, &rval);
	if (ret) {
		DRM_ERROR("AGPIOC_PAGES_BIND failed ret %d", ret);
		return -ret;
	}
	return 0;
}

int
drm_agp_unbind_pages(struct drm_device *dev,
		    pfn_t *pages,
		    unsigned long num_pages,
		    uint32_t gtt_offset,
		    pfn_t scratch,
		    uint32_t type)
{
	agp_gtt_info_t unbind;
	int ret, rval;

	unbind.agp_pgstart = gtt_offset / AGP_PAGE_SIZE;
	unbind.agp_npage = num_pages;
	unbind.agp_type = type;
	unbind.agp_phyaddr = pages;
	unbind.agp_scratch = scratch;

	ret = ldi_ioctl(dev->agp->agpgart_lh, AGPIOC_PAGES_UNBIND,
	    (intptr_t)&unbind, FKIOCTL, kcred, &rval);
	if (ret) {
		DRM_ERROR("AGPIOC_PAGES_UNBIND failed %d", ret);
		return -ret;
	}
	return 0;
}

void drm_agp_chipset_flush(struct drm_device *dev)
{
	int ret, rval;

	ret = ldi_ioctl(dev->agp->agpgart_lh, AGPIOC_FLUSHCHIPSET,
	    (intptr_t)0, FKIOCTL, kcred, &rval);
	if (ret)
		DRM_ERROR("AGPIOC_FLUSHCHIPSET failed, ret=%d", ret);
}

int
drm_agp_rw_gtt(struct drm_device *dev,
		    unsigned long num_pages,
		    uint32_t gtt_offset,
		    void *gttp,
		    uint32_t type)
{
	agp_rw_gtt_t gtt_info;
	int ret, rval;

	gtt_info.pgstart = gtt_offset / AGP_PAGE_SIZE;
	gtt_info.pgcount = num_pages;
	gtt_info.addr = gttp;
	/* read = 0 write = 1 */
	gtt_info.type = type;
	ret = ldi_ioctl(dev->agp->agpgart_lh, AGPIOC_RW_GTT,
	    (intptr_t)&gtt_info, FKIOCTL, kcred, &rval);
	if (ret) {
		DRM_ERROR("AGPIOC_RW_GTT failed %d", ret);
		return -ret;
	}
	return 0;
}
