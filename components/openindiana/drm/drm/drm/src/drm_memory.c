/*
 * Copyright (c) 2006, 2013, Oracle and/or its affiliates. All rights reserved.
 */

/*
 * drm_memory.h -- Memory management wrappers for DRM -*- linux-c -*-
 * Created: Thu Feb  4 14:00:34 1999 by faith@valinux.com
 */
/*
 * Copyright 1999 Precision Insight, Inc., Cedar Park, Texas.
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
 *
 * Authors:
 *    Rickard E. (Rik) Faith <faith@valinux.com>
 *    Gareth Hughes <gareth@valinux.com>
 *
 */

#include "drmP.h"
#ifdef __x86
#include "drm_linux_list.h"
#endif

/* Device memory access structure */

typedef struct drm_device_iomap {
	uint_t paddr;		/* physical address */
	uint_t size;		/* size of mapping */
	caddr_t kvaddr;		/* kernel virtual address */
	ddi_acc_handle_t acc_handle; 	/* data access handle */
} drm_device_iomap_t;

void *
drm_alloc(size_t size, int area)
{
	_NOTE(ARGUNUSED(area))

	return (kmem_zalloc(1 * size, KM_NOSLEEP));
}

void *
drm_calloc(size_t nmemb, size_t size, int area)
{
	_NOTE(ARGUNUSED(area))

	return (kmem_zalloc(size * nmemb, KM_NOSLEEP));
}

void *
drm_realloc(void *oldpt, size_t oldsize, size_t size, int area)
{
	_NOTE(ARGUNUSED(area))

	void *pt;

	pt = kmem_zalloc(1 * size, KM_NOSLEEP);
	if (pt == NULL) {
		DRM_ERROR("pt is NULL strange");
		return (NULL);
	}
	if (oldpt && oldsize) {
		bcopy(oldpt, pt, min(oldsize, size));
		kmem_free(oldpt, oldsize);
	}
	return (pt);
}

void
drm_free(void *pt, size_t size, int area)
{
	_NOTE(ARGUNUSED(area))

	if (pt)
		kmem_free(pt, size);
}

int
drm_get_pci_index_reg(dev_info_t *dip, uint_t paddr, uint_t size, off_t *off)
{
	_NOTE(ARGUNUSED(size))

	pci_regspec_t *regs = NULL;
	int len;
	uint_t regbase, regsize;
	int nregs, i;
	int regnum;

	regnum = -1;

	if (ddi_dev_nregs(dip, &nregs) == DDI_FAILURE) {
		DRM_ERROR("ddi_dev_nregs() failed");
		return (-1);
	}

	if (ddi_getlongprop(DDI_DEV_T_ANY, dip, DDI_PROP_DONTPASS,
	    "assigned-addresses", (caddr_t)&regs, &len) != DDI_PROP_SUCCESS) {
		DRM_ERROR("ddi_getlongprop() failed");
		if (regs)
			kmem_free(regs, (size_t)len);
		return (-1);
	}

	for (i = 0; i < nregs; i ++) {
		regbase = (uint_t)regs[i].pci_phys_low;
		regsize = (uint_t)regs[i].pci_size_low;
		if ((uint_t)paddr >= regbase &&
		    (uint_t)paddr < (regbase + regsize)) {
			regnum = i + 1;
			*off = (off_t)(paddr - regbase);
			break;
		}
	}

	if (regs)
		kmem_free(regs, (size_t)len);
	return (regnum);
}

/* data access attributes structure for register access */
static ddi_device_acc_attr_t dev_attr = {
	DDI_DEVICE_ATTR_V0,
#ifdef _BIG_ENDIAN
	DDI_STRUCTURE_LE_ACC,
#else
	DDI_NEVERSWAP_ACC,
#endif
	DDI_STRICTORDER_ACC,
	DDI_FLAGERR_ACC
};

static int
__ioremap(dev_info_t *dip, drm_device_iomap_t *iomap)
{
	off_t offset;
	int regnum;
	int ret;

	regnum = drm_get_pci_index_reg(
	    dip, iomap->paddr, iomap->size, &offset);
	if (regnum < 0) {
		DRM_ERROR("can not find register entry: "
		    "paddr=0x%x, size=0x%x", iomap->paddr, iomap->size);
		return -ENXIO;
	}

	ret = ddi_regs_map_setup(dip, regnum,
	    (caddr_t *)&(iomap->kvaddr), (offset_t)offset,
	    (offset_t)iomap->size, &dev_attr, &iomap->acc_handle);
	if (ret != DDI_SUCCESS) {
		DRM_ERROR("failed to map regs: "
		    "regnum=%d, offset=0x%lx", regnum, offset);
		iomap->acc_handle = NULL;
		return -EFAULT;
	}

	return 0;
}

int
drm_ioremap(struct drm_device *dev, struct drm_local_map *map)
{
	struct drm_device_iomap iomap;
	int ret;

	DRM_DEBUG("\n");

	iomap.paddr = map->offset;
	iomap.size = map->size;

	ret = __ioremap(dev->devinfo, &iomap);
	if (ret) {
		DRM_ERROR("__ioremap failed: paddr=0x%lx, size=0x%lx",
		    map->offset, map->size);
		return (ret);
	}

	map->handle = (void *)iomap.kvaddr;
	map->acc_handle = iomap.acc_handle;

	DRM_DEBUG(
	    "map->handle=%p, map->size=%lx",
	    (void *)map->handle, map->size);

	return (0);
}

void
drm_ioremapfree(struct drm_local_map *map)
{
	if (map->acc_handle)
		ddi_regs_map_free(&map->acc_handle);
}

#ifdef __x86
struct drm_iomem {
	void *addr;
	size_t size;
	struct list_head head;
};

struct list_head drm_iomem_list;

void *
drm_sun_ioremap(uint64_t paddr, size_t size, uint32_t mode)
{
	struct drm_iomem *iomem;
	void *addr;

	if (mode == DRM_MEM_CACHED)
		mode = GFXP_MEMORY_CACHED;
	else if (mode == DRM_MEM_UNCACHED)
		mode = GFXP_MEMORY_UNCACHED;
	else if (mode == DRM_MEM_WC)
		mode = GFXP_MEMORY_WRITECOMBINED;
	else
		return (NULL);

	addr = (void *)gfxp_alloc_kernel_space(size);
	if(!addr)
		return (NULL);
	gfxp_load_kernel_space(paddr, size, mode, addr);
	iomem = kmem_zalloc(sizeof(*iomem), KM_NOSLEEP);
	if(!iomem){
		gfxp_unmap_kernel_space(addr, size);
		return (NULL);
	}
	iomem->addr = addr;
	iomem->size = size;

	INIT_LIST_HEAD(&iomem->head);
	list_add(&iomem->head, &drm_iomem_list, (caddr_t)iomem);

	return (addr);
}

void
drm_sun_iounmap(void *addr)
{
	struct drm_iomem *iomem;

	list_for_each_entry(iomem, struct drm_iomem, &drm_iomem_list, head) {
		if (iomem->addr == addr) {
			gfxp_unmap_kernel_space(addr, iomem->size);
			list_del(&iomem->head);
			kmem_free(iomem, sizeof(*iomem));
			break;
		}
	}
}
#endif /* x86 */
