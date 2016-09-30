/*
 * Copyright (c) 2006, 2012, Oracle and/or its affiliates. All rights reserved.
 */

/*
 * Copyright (c) 2012 Intel Corporation.  All rights reserved.
 */

/**
 * \file drm_scatter.c
 * IOCTLs to manage scatter/gather memory
 *
 * \author Gareth Hughes <gareth@valinux.com>
 */

/*
 * Created: Mon Dec 18 23:20:54 2000 by gareth@valinux.com
 *
 * Copyright 2000 VA Linux Systems, Inc., Sunnyvale, California.
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
 * PRECISION INSIGHT AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#include "drmP.h"
#include "drm_io32.h"

#define DEBUG_SCATTER 0

void drm_sg_cleanup(struct drm_sg_mem *entry)
{
	int pages = entry->pages;

	if (entry->busaddr) {
		kmem_free(entry->busaddr, sizeof (*entry->busaddr) * pages);
		entry->busaddr = NULL;
	}

	ASSERT(entry->umem_cookie == NULL);

	if (entry->dmah_sg) {
		drm_pci_free(entry->dmah_sg);
		entry->dmah_sg = NULL;
	}

	if (entry->dmah_gart) {
		drm_pci_free(entry->dmah_gart);
		entry->dmah_gart = NULL;
	}

	kfree(entry, sizeof (struct drm_sg_mem));
}

#ifdef	_LP64
#define	ScatterHandle(x) (unsigned int)((x >> 32) + (x & ((1L << 32) - 1)))
#else
#define	ScatterHandle(x) (unsigned int)(x)
#endif

int drm_sg_alloc(struct drm_device *dev, struct drm_scatter_gather * request)
{
	struct drm_sg_mem *entry;
	unsigned long pages;
	drm_dma_handle_t *dmah;

	DRM_DEBUG("\n");

	if (!drm_core_check_feature(dev, DRIVER_SG))
		return -EINVAL;

	if (dev->sg)
		return -EINVAL;

	entry = kmalloc(sizeof(*entry), GFP_KERNEL);
	if (!entry)
		return -ENOMEM;

	(void) memset(entry, 0, sizeof(*entry));
	pages = (request->size + PAGE_SIZE - 1) / PAGE_SIZE;
	DRM_DEBUG("size=%ld pages=%ld\n", request->size, pages);

	entry->pages = (int)pages;
	dmah = drm_pci_alloc(dev, ptob(pages), 4096, 0xfffffffful, pages);
	if (dmah == NULL)
		goto err_exit;
	entry->busaddr = (void *)kmem_zalloc(sizeof (*entry->busaddr) *
	    pages, KM_SLEEP);

	entry->handle = ScatterHandle((unsigned long)dmah->vaddr);
	entry->virtual = (void *)dmah->vaddr;
	request->handle = entry->handle;
	entry->dmah_sg = dmah;

	dev->sg = entry;

	return 0;

err_exit:
	drm_sg_cleanup(entry);
	return -ENOMEM;
}

/* LINTED */
int drm_sg_alloc_ioctl(DRM_IOCTL_ARGS)
{
	struct drm_scatter_gather *request = data;

	return drm_sg_alloc(dev, request);

}

/* LINTED */
int drm_sg_free(DRM_IOCTL_ARGS)
{
	struct drm_scatter_gather *request = data;
	struct drm_sg_mem *entry;

	if (!drm_core_check_feature(dev, DRIVER_SG))
		return -EINVAL;

	entry = dev->sg;
	dev->sg = NULL;

	if (!entry || entry->handle != request->handle)
		return -EINVAL;

	DRM_DEBUG("virtual  = %p\n", entry->virtual);

	drm_sg_cleanup(entry);

	return 0;
}
