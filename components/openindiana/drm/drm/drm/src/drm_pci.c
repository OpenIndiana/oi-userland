/*
 * Copyright (c) 2006, 2013, Oracle and/or its affiliates. All rights reserved.
 */

/*
 * Copyright (c) 2012 Intel Corporation.  All rights reserved.
 */

/**
 * \file drm_pci.h
 * \brief PCI consistent, DMA-accessible memory functions.
 *
 * \author Eric Anholt <anholt@FreeBSD.org>
 */

/*-
 * Copyright 2003 Eric Anholt.
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
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
 * AUTHOR BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/**********************************************************************/
/** \name PCI memory */
/*@{*/

#include "drmP.h"
#include <vm/seg_kmem.h>

typedef struct drm_pci_resource {
	uint_t regnum;
	unsigned long offset;
	unsigned long size;
} drm_pci_resource_t;

void
drm_core_ioremap(struct drm_local_map *map, struct drm_device *dev)
{
	if ((map->type == _DRM_AGP) && dev->agp) {
		/*
		 * During AGP mapping initialization, we map AGP aperture
		 * into kernel space. So, when we access the memory which
		 * managed by agp gart in kernel space, we have to go
		 * through two-level address translation: kernel virtual
		 * address --> aperture address --> physical address. For
		 * improving this, here in opensourced code, agp_remap()
		 * gets invoking to dispose the mapping between agp aperture
		 * and kernel space, and directly map the actual physical
		 * memory which is allocated to agp gart to kernel space.
		 * After that, access to physical memory managed by agp gart
		 * hardware in kernel space doesn't go through agp hardware,
		 * it will be: kernel virtual ---> physical address.
		 * Obviously, it is more efficient. But in Solaris operating
		 * system, the ioctl AGPIOC_ALLOCATE of agpgart driver does
		 * not return physical address. We are unable to create the
		 * direct mapping between kernel space and agp memory. So,
		 * we remove the calling to agp_remap().
		 */
		DRM_DEBUG("drm_core_ioremap: skipping agp_remap\n");
	} else {
		(void) drm_ioremap(dev, map);

	}
}

void
drm_core_ioremapfree(struct drm_local_map *map, struct drm_device *dev)
{
	_NOTE(ARGUNUSED(dev))

	if (map->type != _DRM_AGP) {
		if (map->handle && map->size)
			drm_ioremapfree(map);
	} else {
		/*
		 * Refer to the comments in drm_core_ioremap() where we removed
		 * the calling to agp_remap(), correspondingly, we remove the
		 * calling to agp_remap_free(dev, map);
		 */
		DRM_DEBUG("drm_core_ioremap: skipping agp_remap_free\n");
	}
}

/*
 * pci_alloc_consistent()
 */
static ddi_dma_attr_t	hw_dma_attr = {
		DMA_ATTR_V0,		/* version */
		0,			/* addr_lo */
		0xffffffff,	/* addr_hi */
		0xffffffff,	/* count_max */
		4096, 			/* alignment */
		0xfff,			/* burstsize */
		1,			/* minxfer */
		0xffffffff,		/* maxxfer */
		0xffffffff,		/* seg */
		1,			/* sgllen */
		4,			/* granular */
		DDI_DMA_FLAGERR,	/* flags */
};

static ddi_device_acc_attr_t hw_acc_attr = {
	DDI_DEVICE_ATTR_V0,
	DDI_NEVERSWAP_ACC,
	DDI_STRICTORDER_ACC,
	DDI_FLAGERR_ACC
};

void *
drm_pci_alloc(struct drm_device *dev, size_t size,
    size_t align, dma_addr_t maxaddr, int segments)
{
	struct drm_dma_handle *dmah;
	uint_t count;

	/* allocate continous physical memory for hw status page */
	hw_dma_attr.dma_attr_align = (!align) ? 1 : align;

	hw_dma_attr.dma_attr_addr_hi = maxaddr;
	hw_dma_attr.dma_attr_sgllen = segments;

	dmah = kmem_zalloc(sizeof(struct drm_dma_handle), KM_SLEEP);

	if (ddi_dma_alloc_handle(dev->devinfo, &hw_dma_attr,
	    DDI_DMA_SLEEP, NULL, &dmah->dma_hdl) != DDI_SUCCESS) {
		DRM_ERROR("ddi_dma_alloc_handle() failed");
		goto err3;
	}

	if (ddi_dma_mem_alloc(dmah->dma_hdl, size, &hw_acc_attr,
	    DDI_DMA_CONSISTENT | IOMEM_DATA_UNCACHED,
	    DDI_DMA_SLEEP, NULL, (caddr_t *)&dmah->vaddr,
	    &dmah->real_sz, &dmah->acc_hdl) != DDI_SUCCESS) {
		DRM_ERROR("ddi_dma_mem_alloc() failed\n");
		goto err2;
	}

	if (ddi_dma_addr_bind_handle(dmah->dma_hdl, NULL,
	    (caddr_t)dmah->vaddr, dmah->real_sz,
	    DDI_DMA_RDWR|DDI_DMA_CONSISTENT, DDI_DMA_SLEEP,
	    NULL, &dmah->cookie, &count) != DDI_DMA_MAPPED) {
		DRM_ERROR("ddi_dma_addr_bind_handle() failed");
		goto err1;
	}

	if (count > segments) {
		(void) ddi_dma_unbind_handle(dmah->dma_hdl);
		goto err1;
	}

	dmah->cookie_num = count;
	if (count == 1)
		dmah->paddr = dmah->cookie.dmac_address;

	return (dmah);

err1:
	ddi_dma_mem_free(&dmah->acc_hdl);
err2:
	ddi_dma_free_handle(&dmah->dma_hdl);
err3:
	kmem_free(dmah, sizeof (*dmah));
	return (NULL);
}

void
drm_pci_free(drm_dma_handle_t *dmah)
{
	ASSERT(dmah != NULL);

	(void) ddi_dma_unbind_handle(dmah->dma_hdl);
	ddi_dma_mem_free(&dmah->acc_hdl);
	ddi_dma_free_handle(&dmah->dma_hdl);
	kmem_free(dmah, sizeof (drm_dma_handle_t));
}

int
do_get_pci_res(struct drm_device *dev, drm_pci_resource_t *resp)
{
	int length;
	pci_regspec_t	*regs;

	if (ddi_getlongprop(
	    DDI_DEV_T_ANY, dev->devinfo, DDI_PROP_DONTPASS,
	    "assigned-addresses", (caddr_t)&regs, &length) !=
	    DDI_PROP_SUCCESS) {
		DRM_ERROR("do_get_pci_res: ddi_getlongprop failed!\n");
		return (EFAULT);
	}
	resp->offset =
	    (unsigned long)regs[resp->regnum].pci_phys_low;
	resp->size =
	    (unsigned long)regs[resp->regnum].pci_size_low;
	kmem_free(regs, (size_t)length);

	return (0);
}

unsigned long
drm_get_resource_start(struct drm_device *dev, unsigned int regnum)
{
	drm_pci_resource_t res;
	int ret;

	res.regnum = regnum;

	ret = do_get_pci_res(dev, &res);

	if (ret != 0) {
		DRM_ERROR("drm_get_resource_start: ioctl failed");
		return (0);
	}

	return (res.offset);

}

unsigned long
drm_get_resource_len(struct drm_device *softstate, unsigned int regnum)
{
	drm_pci_resource_t res;
	int ret;

	res.regnum = regnum;

	ret = do_get_pci_res(softstate, &res);

	if (ret != 0) {
		DRM_ERROR("drm_get_resource_len: ioctl failed");
		return (0);
	}

	return (res.size);
}
