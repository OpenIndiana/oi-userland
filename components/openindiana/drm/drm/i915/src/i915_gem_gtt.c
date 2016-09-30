/*
 * Copyright (c) 2012, 2013, Oracle and/or its affiliates. All rights reserved.
 */

/*
 * Copyright (c) 2012, 2013, Intel Corporation.  All rights reserved.
 */

/*
 * Copyright © 2010 Daniel Vetter
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
 */

#include "drmP.h"
#include "drm.h"
#include "i915_drm.h"
#include "i915_drv.h"
#include "intel_drv.h"

typedef uint32_t gtt_pte_t;

/* PPGTT stuff */
#define GEN6_GTT_ADDR_ENCODE(addr)	((addr) | (((addr) >> 28) & 0xff0))

#define GEN6_PDE_VALID			(1 << 0)
/* gen6+ has bit 11-4 for physical addr bit 39-32 */
#define GEN6_PDE_ADDR_ENCODE(addr)	GEN6_GTT_ADDR_ENCODE(addr)

#define GEN6_PTE_VALID			(1 << 0)
#define GEN6_PTE_UNCACHED		(1 << 1)
#define HSW_PTE_UNCACHED		(0)
#define GEN6_PTE_CACHE_LLC		(2 << 1)
#define GEN6_PTE_CACHE_LLC_MLC		(3 << 1)
#define GEN6_PTE_ADDR_ENCODE(addr)	GEN6_GTT_ADDR_ENCODE(addr)

static gen6_gtt_pte_t gen6_pte_encode(struct drm_device *dev,
				   uint64_t addr,
				   enum i915_cache_level level)
{
	gen6_gtt_pte_t pte = GEN6_PTE_VALID;
	pte |= GEN6_PTE_ADDR_ENCODE(addr);

	switch (level) {
	case I915_CACHE_LLC_MLC:
			pte |= GEN6_PTE_CACHE_LLC_MLC;
		break;
	case I915_CACHE_LLC:
		pte |= GEN6_PTE_CACHE_LLC;
		break;
	case I915_CACHE_NONE:
		pte |= GEN6_PTE_UNCACHED;
		break;
	default:
		BUG();
	}

	return pte;
}

#define BYT_PTE_WRITEABLE		(1 << 1)
#define BYT_PTE_SNOOPED_BY_CPU_CACHES	(1 << 2)

static gen6_gtt_pte_t byt_pte_encode(struct drm_device *dev,
				     uint64_t addr,
				     enum i915_cache_level level)
{
	gen6_gtt_pte_t pte = GEN6_PTE_VALID;
	pte |= GEN6_PTE_ADDR_ENCODE(addr);

	/* Mark the page as writeable.  Other platforms don't have a
	 * setting for read-only/writable, so this matches that behavior.
	 */
	pte |= BYT_PTE_WRITEABLE;

	if (level != I915_CACHE_NONE)
		pte |= BYT_PTE_SNOOPED_BY_CPU_CACHES;

	return pte;
}

static gen6_gtt_pte_t hsw_pte_encode(struct drm_device *dev,
				     uint64_t addr,
				     enum i915_cache_level level)
{
	gen6_gtt_pte_t pte = GEN6_PTE_VALID;
	pte |= GEN6_PTE_ADDR_ENCODE(addr);

	if (level != I915_CACHE_NONE)
		pte |= GEN6_PTE_CACHE_LLC;

	return pte;
}

static ddi_dma_attr_t ppgt_dma_attr = {
	DMA_ATTR_V0,
	0xff000U, 			/* dma_attr_addr_lo */
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
static ddi_device_acc_attr_t ppgt_acc_attr = {
	DDI_DEVICE_ATTR_V0,
	DDI_NEVERSWAP_ACC,
	DDI_MERGING_OK_ACC,
	DDI_FLAGERR_ACC
};

static int
i915_ppgtt_page_alloc(struct drm_device *dev, struct i915_hw_ppgtt *ppgtt,
					int pgcnt)
{
	ddi_dma_cookie_t cookie;
	uint_t cookie_cnt;
	pgcnt_t real_pgcnt;
	uint32_t paddr, cookie_end;
	int i, n;

	ppgt_dma_attr.dma_attr_sgllen = (int)pgcnt;

	if (ddi_dma_alloc_handle(dev->devinfo, &ppgt_dma_attr,
	    DDI_DMA_DONTWAIT, NULL, &ppgtt->dma_hdl)) {
		DRM_ERROR("i915_ppgtt_page_alloc: "
		    "ddi_dma_alloc_handle failed");
		goto err1;
	}
	if (ddi_dma_mem_alloc(ppgtt->dma_hdl, ptob(pgcnt), &ppgt_acc_attr,
	    IOMEM_DATA_UC_WR_COMBINE, DDI_DMA_DONTWAIT, NULL,
	    &ppgtt->kaddr, &ppgtt->real_size, &ppgtt->acc_hdl)) {
		DRM_ERROR("drm_gem_object_alloc: "
		    "ddi_dma_mem_alloc failed");
		goto err2;
	}
	if (ddi_dma_addr_bind_handle(ppgtt->dma_hdl, NULL,
	    ppgtt->kaddr, ppgtt->real_size, DDI_DMA_RDWR,
	    DDI_DMA_DONTWAIT, NULL, &cookie, &cookie_cnt)
	    != DDI_DMA_MAPPED) {
		DRM_ERROR("drm_gem_object_alloc: "
		    "ddi_dma_addr_bind_handle failed");
		goto err3;
	}

	real_pgcnt = btopr(ppgtt->real_size);

	ppgtt->pt_pages = kmem_zalloc(real_pgcnt * sizeof (pfn_t), KM_NOSLEEP);
	if (ppgtt->pt_pages == NULL) {
		DRM_DEBUG("pfnarray == NULL");
		goto err4;
	}

	for (n = 0, i = 1; ; i++) {
		for (paddr = cookie.dmac_address,
		    cookie_end = cookie.dmac_address + cookie.dmac_size;
		    paddr < cookie_end;
		    paddr += PAGESIZE) {
			ppgtt->pt_pages[n++] = btop(paddr);
			if (n >= real_pgcnt)
				return (0);
		}
		if (i >= cookie_cnt)
			break;
		ddi_dma_nextcookie(ppgtt->dma_hdl, &cookie);
	}

err4:
	(void) ddi_dma_unbind_handle(ppgtt->dma_hdl);
err3:
	ddi_dma_mem_free(&ppgtt->acc_hdl);
err2:
	ddi_dma_free_handle(&ppgtt->dma_hdl);
err1:
	return (-1);

}

static void gen6_write_pdes(struct i915_hw_ppgtt *ppgtt)
{
	struct drm_i915_private *dev_priv = ppgtt->dev->dev_private;
	gen6_gtt_pte_t *pd_addr;
	uint32_t pt_addr;
	uint32_t pd_entry;
	int i;

	WARN_ON(ppgtt->pd_offset & 0x3f);
	for (i = 0; i < ppgtt->num_pd_entries; i++) {
		pd_addr = (gen6_gtt_pte_t *)(uintptr_t)((caddr_t)dev_priv->gtt.virtual_gtt
					+ ppgtt->pd_offset + i * sizeof(gtt_pte_t));


		pt_addr = ppgtt->pt_pages[i] << PAGE_SHIFT;
		pd_entry = GEN6_PDE_ADDR_ENCODE(pt_addr);
		pd_entry |= GEN6_PDE_VALID;

		ddi_put32(dev_priv->gtt.gtt_mapping.acc_handle,
			pd_addr, pd_entry);

	}
	(void) ddi_get32(dev_priv->gtt.gtt_mapping.acc_handle,
			(gen6_gtt_pte_t *)(uintptr_t)((caddr_t)dev_priv->gtt.virtual_gtt +  ppgtt->pd_offset));
}

static int gen6_ppgtt_enable(struct drm_device *dev)
{
	drm_i915_private_t *dev_priv = dev->dev_private;
	uint32_t pd_offset;
	struct intel_ring_buffer *ring;
	struct i915_hw_ppgtt *ppgtt = dev_priv->mm.aliasing_ppgtt;
	int i;

	BUG_ON(ppgtt->pd_offset & 0x3f);

	gen6_write_pdes(ppgtt);

	pd_offset = ppgtt->pd_offset;
	pd_offset /= 64; /* in cachelines, */
	pd_offset <<= 16;

	if (INTEL_INFO(dev)->gen == 6) {
		uint32_t ecochk, gab_ctl, ecobits;

		ecobits = I915_READ(GAC_ECO_BITS);
		I915_WRITE(GAC_ECO_BITS, ecobits | ECOBITS_SNB_BIT |
					 ECOBITS_PPGTT_CACHE64B);

		gab_ctl = I915_READ(GAB_CTL);
		I915_WRITE(GAB_CTL, gab_ctl | GAB_CTL_CONT_AFTER_PAGEFAULT);

		ecochk = I915_READ(GAM_ECOCHK);
		I915_WRITE(GAM_ECOCHK, ecochk | ECOCHK_SNB_BIT |
				       ECOCHK_PPGTT_CACHE64B);
		I915_WRITE(GFX_MODE, _MASKED_BIT_ENABLE(GFX_PPGTT_ENABLE));
	} else if (INTEL_INFO(dev)->gen >= 7) {
		uint32_t ecochk, ecobits;

		ecobits = I915_READ(GAC_ECO_BITS);
		I915_WRITE(GAC_ECO_BITS, ecobits | ECOBITS_PPGTT_CACHE64B);

		ecochk = I915_READ(GAM_ECOCHK);
		if (IS_HASWELL(dev)) {
			ecochk |= ECOCHK_PPGTT_WB_HSW;
		} else {
			ecochk |= ECOCHK_PPGTT_LLC_IVB;
			ecochk &= ~ECOCHK_PPGTT_GFDT_IVB;
		}
		I915_WRITE(GAM_ECOCHK, ecochk);
		/* GFX_MODE is per-ring on gen7+ */
	}

	for_each_ring(ring, dev_priv, i) {
		if (INTEL_INFO(dev)->gen >= 7)
			I915_WRITE(RING_MODE_GEN7(ring),
				   _MASKED_BIT_ENABLE(GFX_PPGTT_ENABLE));

		I915_WRITE(RING_PP_DIR_DCLV(ring), PP_DIR_DCLV_2G);
		I915_WRITE(RING_PP_DIR_BASE(ring), pd_offset);
	}
	return 0;
}

/* PPGTT support for Sandybdrige/Gen6 and later */
static void gen6_ppgtt_clear_range(struct i915_hw_ppgtt *ppgtt,
				   unsigned first_entry,
				   unsigned num_entries)
{
	gen6_gtt_pte_t *pt_vaddr, scratch_pte;
	unsigned act_pt = first_entry / I915_PPGTT_PT_ENTRIES;
	unsigned first_pte = first_entry % I915_PPGTT_PT_ENTRIES;
	unsigned last_pte, i;

	scratch_pte = ppgtt->pte_encode(ppgtt->dev,
				      ppgtt->scratch_page_paddr,
				 I915_CACHE_LLC);

	while (num_entries) {
		last_pte = first_pte + num_entries;
		if (last_pte > I915_PPGTT_PT_ENTRIES)
			last_pte = I915_PPGTT_PT_ENTRIES;

		pt_vaddr = (uint32_t*)(uintptr_t)(ppgtt->kaddr + act_pt*PAGE_SIZE);

		for (i = first_pte; i < last_pte; i++)
			pt_vaddr[i] = scratch_pte;

		num_entries -= last_pte - first_pte;
		first_pte = 0;
		act_pt++;
	}
}

static void gen6_ppgtt_insert_entries(struct i915_hw_ppgtt *ppgtt,
				    unsigned first_entry, unsigned num_entries,
				    pfn_t *pages, enum i915_cache_level cache_level)
{
	gen6_gtt_pte_t *pt_vaddr;
	unsigned act_pt = first_entry / I915_PPGTT_PT_ENTRIES;
	unsigned act_pte = first_entry % I915_PPGTT_PT_ENTRIES;
	unsigned i, j;

	pt_vaddr = (gen6_gtt_pte_t *)(uintptr_t)(ppgtt->kaddr + act_pt*PAGE_SIZE);
	for (i = first_entry, j = 0; i < ( first_entry + num_entries); i++, j++) {

		pt_vaddr[act_pte] = ppgtt->pte_encode(ppgtt->dev, pages[j] << PAGE_SHIFT,
						      cache_level);
		if (++act_pte == I915_PPGTT_PT_ENTRIES) {
			act_pt++;
			pt_vaddr = (gen6_gtt_pte_t *)(uintptr_t)(ppgtt->kaddr + act_pt*PAGE_SIZE);
			act_pte = 0;

		}
	}
}

static void gen6_ppgtt_cleanup(struct i915_hw_ppgtt *ppgtt)
{
	kmem_free(ppgtt->pt_pages, btopr(ppgtt->real_size) * sizeof (pfn_t));

	(void) ddi_dma_unbind_handle(ppgtt->dma_hdl);
	ddi_dma_mem_free(&ppgtt->acc_hdl);
	ddi_dma_free_handle(&ppgtt->dma_hdl);
	kfree(ppgtt, sizeof(*ppgtt));
}

static int gen6_ppgtt_init(struct i915_hw_ppgtt *ppgtt)
{
	struct drm_device *dev = ppgtt->dev;
	struct drm_i915_private *dev_priv = dev->dev_private;
	unsigned first_pd_entry_in_global_pt;
	int ret = -ENOMEM;

	/* ppgtt PDEs reside in the global gtt pagetable, which has 512*1024
	 * entries. For aliasing ppgtt support we just steal them at the end for
	 * now. */
       first_pd_entry_in_global_pt = gtt_total_entries(dev_priv->gtt);

	if (IS_HASWELL(dev)) {
		ppgtt->pte_encode = hsw_pte_encode;
	} else if (IS_VALLEYVIEW(dev)) {
		ppgtt->pte_encode = byt_pte_encode;
	} else {
		ppgtt->pte_encode = gen6_pte_encode;
	}
	ppgtt->num_pd_entries = I915_PPGTT_PD_ENTRIES;
	ppgtt->enable = gen6_ppgtt_enable;
	ppgtt->clear_range = gen6_ppgtt_clear_range;
	ppgtt->insert_entries = gen6_ppgtt_insert_entries;
	ppgtt->cleanup = gen6_ppgtt_cleanup;
	ret = i915_ppgtt_page_alloc(dev, ppgtt, ppgtt->num_pd_entries);
	if (ret)
		return (-ENOMEM);

	ppgtt->clear_range(ppgtt, 0,
			   ppgtt->num_pd_entries*I915_PPGTT_PT_ENTRIES);

	ppgtt->pd_offset = first_pd_entry_in_global_pt * sizeof(gen6_gtt_pte_t);

	return 0;

}

static int i915_gem_init_aliasing_ppgtt(struct drm_device *dev)
{
	struct drm_i915_private *dev_priv = dev->dev_private;
	struct i915_hw_ppgtt *ppgtt;
	int ret = -EINVAL;

	ppgtt = kzalloc(sizeof(*ppgtt), GFP_KERNEL);
	if (!ppgtt)
		return -ENOMEM;

	ppgtt->dev = dev;
	ppgtt->scratch_page_paddr = ptob(dev_priv->gtt.scratch_page->pfnarray[0]);

	if (INTEL_INFO(dev)->gen < 8)
		ret = gen6_ppgtt_init(ppgtt);
	else {
		BUG();
		DRM_ERROR("ppgtt is not supported");
	}

	if (ret)
		kfree(ppgtt, sizeof(*ppgtt));
	else
		dev_priv->mm.aliasing_ppgtt = ppgtt;

	return ret;
}

void i915_gem_cleanup_aliasing_ppgtt(struct drm_device *dev)
{
	struct drm_i915_private *dev_priv = dev->dev_private;
	struct i915_hw_ppgtt *ppgtt = dev_priv->mm.aliasing_ppgtt;

	if (!ppgtt)
		return;

	ppgtt->cleanup(ppgtt);
	dev_priv->mm.aliasing_ppgtt = NULL;
}

void i915_ppgtt_bind_object(struct i915_hw_ppgtt *ppgtt,
			    struct drm_i915_gem_object *obj,
			    enum i915_cache_level cache_level)
{

	ppgtt->insert_entries(ppgtt,
				obj->gtt_space->start >> PAGE_SHIFT,
				obj->base.size >> PAGE_SHIFT,
				obj->base.pfnarray,
				cache_level);
}

void i915_ppgtt_unbind_object(struct i915_hw_ppgtt *ppgtt,
			      struct drm_i915_gem_object *obj)
{
	ppgtt->clear_range(ppgtt,
			       obj->gtt_space->start >> PAGE_SHIFT,
			       obj->base.size >> PAGE_SHIFT);
}

void i915_gem_restore_gtt_mappings(struct drm_device *dev)
{
	struct drm_i915_private *dev_priv = dev->dev_private;
	struct drm_i915_gem_object *obj;

	/* First fill our portion of the GTT with scratch pages */
/*
	i915_ggtt_clear_range(dev_priv->mm.gtt_start / PAGE_SIZE,
			      (dev_priv->mm.gtt_end - dev_priv->mm.gtt_start) / PAGE_SIZE);
*/

	list_for_each_entry(obj, struct drm_i915_gem_object, &dev_priv->mm.bound_list, global_list) {
		i915_gem_clflush_object(obj);
		i915_gem_gtt_bind_object(obj, obj->cache_level);
	}

	i915_gem_chipset_flush(dev);
}

int i915_gem_gtt_prepare_object(struct drm_i915_gem_object *obj)
{
#if 0
	if (obj->has_dma_mapping)
		return 0;

	if (!dma_map_sg(&obj->base.dev->pdev->dev,
			obj->pages->sgl, obj->pages->nents,
			PCI_DMA_BIDIRECTIONAL))
		return -ENOSPC;

#endif
	return 0;
}

/*
 * Binds an object into the global gtt with the specified cache level. The object
 * will be accessible to the GPU via commands whose operands reference offsets
 * within the global GTT as well as accessible by the GPU through the GMADR
 * mapped BAR (dev_priv->mm.gtt->gtt).
 */
static void gen6_ggtt_insert_entries(struct drm_i915_gem_object *obj,
				  enum i915_cache_level level)
{
	struct drm_device *dev = obj->base.dev;
	struct drm_i915_private *dev_priv = dev->dev_private;
	unsigned first_entry = obj->gtt_offset >> PAGE_SHIFT;
	unsigned num_entries = obj->base.size / PAGE_SIZE;
	/* LINTED */
	const int max_entries = gtt_total_entries(dev_priv->gtt);
	uint64_t page_addr;
	gtt_pte_t *gtt_addr;
	int i, j;

	for (i = first_entry, j = 0; i < ( first_entry + num_entries); i++, j++) {
		gtt_addr = (gtt_pte_t *)(uintptr_t)((caddr_t)dev_priv->gtt.virtual_gtt + i * sizeof(gtt_pte_t));
		page_addr = obj->base.pfnarray[j] << PAGE_SHIFT;
		ddi_put32(dev_priv->gtt.gtt_mapping.acc_handle,
			    gtt_addr,
			    dev_priv->gtt.pte_encode(dev, page_addr, level));
	}

	BUG_ON(i > max_entries);
	BUG_ON(j != obj->base.size / PAGE_SIZE);

	/* XXX: This serves as a posting read to make sure that the PTE has
	 * actually been updated. There is some concern that even though
	 * registers and PTEs are within the same BAR that they are potentially
	 * of NUMA access patterns. Therefore, even with the way we assume
	 * hardware should work, we must keep this posting read for paranoia.
	 */
	if (i != 0) {
		gtt_addr = (gtt_pte_t *)(uintptr_t)((caddr_t)dev_priv->gtt.virtual_gtt + (i-1)*sizeof(gtt_pte_t));
		page_addr = obj->base.pfnarray[j-1] << PAGE_SHIFT;
		WARN_ON(ddi_get32(dev_priv->gtt.gtt_mapping.acc_handle, gtt_addr) !=
			dev_priv->gtt.pte_encode(dev, page_addr, level));
	}

	/* This next bit makes the above posting read even more important. We
	 * want to flush the TLBs only after we're certain all the PTE updates
	 * have finished.
	 */
	I915_WRITE(GFX_FLSH_CNTL_GEN6, GFX_FLSH_CNTL_EN);
	POSTING_READ(GFX_FLSH_CNTL_GEN6);
}

static void gen6_ggtt_clear_range(struct drm_device *dev,
				 struct drm_i915_gem_object *obj,
				 uint32_t type)
{
	struct drm_i915_private *dev_priv = dev->dev_private;
	gtt_pte_t scratch_pte;
	unsigned first_entry = obj->gtt_offset >> PAGE_SHIFT;
	unsigned num_entries = obj->base.size / PAGE_SIZE;
	const int max_entries = gtt_total_entries(dev_priv->gtt) - first_entry;
	uint64_t scratch_page_addr = dev_priv->gtt.scratch_page->pfnarray[0] << PAGE_SHIFT;
	gtt_pte_t *gtt_addr;
	int i;

	if (num_entries > max_entries) {
		 DRM_ERROR("First entry = %d; Num entries = %d (max=%d)\n",
		 first_entry, num_entries, max_entries);
		num_entries = max_entries;
	}

	for (i = first_entry ; i < ( first_entry + num_entries); i++) {
		gtt_addr = (gtt_pte_t *)(uintptr_t)((caddr_t)dev_priv->gtt.virtual_gtt + i * sizeof(gtt_pte_t));
		scratch_pte = dev_priv->gtt.pte_encode(dev, scratch_page_addr, I915_CACHE_LLC);
		ddi_put32(dev_priv->gtt.gtt_mapping.acc_handle,
			    gtt_addr, scratch_pte);
	}
}

void i915_ggtt_insert_entries(struct drm_i915_gem_object *obj,
				enum i915_cache_level cache_level)
{
	struct drm_device *dev = obj->base.dev;

	unsigned int flags = (cache_level == I915_CACHE_NONE) ?
			AGP_USER_MEMORY : AGP_USER_CACHED_MEMORY;

	(void) drm_agp_bind_pages(dev,
				obj->base.pfnarray,
				obj->base.size >> PAGE_SHIFT,
				obj->gtt_offset,
				flags);
}

static void i915_ggtt_clear_range(struct drm_device *dev,
				 struct drm_i915_gem_object *obj,
				 uint32_t type)
{
	struct drm_i915_private *dev_priv = dev->dev_private;

	if (!obj->agp_mem) {
		(void) drm_agp_unbind_pages(dev, obj->base.pfnarray,
						(obj->base.size / PAGE_SIZE), obj->gtt_offset,
						dev_priv->gtt.scratch_page->pfnarray[0], type);
		obj->agp_mem = -1;
	}
	return;

}

void i915_gem_gtt_bind_object(struct drm_i915_gem_object *obj,
			      enum i915_cache_level cache_level)
{
	struct drm_device *dev = obj->base.dev;
	struct drm_i915_private *dev_priv = dev->dev_private;

	dev_priv->gtt.gtt_insert_entries(obj, cache_level);
	obj->has_global_gtt_mapping = 1;
}

void i915_gem_gtt_unbind_object(struct drm_i915_gem_object *obj, uint32_t type)
{
	struct drm_device *dev = obj->base.dev;
	struct drm_i915_private *dev_priv = dev->dev_private;

	dev_priv->gtt.gtt_clear_range(dev, obj, type);

	obj->has_global_gtt_mapping = 0;
}

void i915_gem_gtt_finish_object(struct drm_i915_gem_object *obj)
{
}

static void i915_gtt_color_adjust(struct drm_mm_node *node,
				  unsigned long color,
				  unsigned long *start,
				  unsigned long *end)
{
	if (node->color != color)
		*start += 4096;

	if (!list_empty(&node->node_list)) {
		node = list_entry(node->node_list.next,
				  struct drm_mm_node,
				  node_list);
		if (node->allocated && node->color != color)
			*end -= 4096;
	}
}

void i915_gem_setup_global_gtt(struct drm_device *dev,
			      unsigned long start,
			      unsigned long mappable_end,
			      unsigned long end)
{
	/* Let GEM Manage all of the aperture.
	 *
	 * However, leave one page at the end still bound to the scratch page.
	 * There are a number of places where the hardware apparently prefetches
	 * past the end of the object, and we've seen multiple hangs with the
	 * GPU head pointer stuck in a batchbuffer bound at the last page of the
	 * aperture.  One page should be enough to keep any prefetching inside
	 * of the aperture.
	 */
	drm_i915_private_t *dev_priv = dev->dev_private;
	struct drm_i915_gem_object *obj;

	/* Substract the guard page ... */
	drm_mm_init(&dev_priv->mm.gtt_space, start, end - start - PAGE_SIZE);
	if (!HAS_LLC(dev))
		dev_priv->mm.gtt_space.color_adjust = i915_gtt_color_adjust;

	/* Mark any preallocated objects as occupied */
	list_for_each_entry(obj, struct drm_i915_gem_object,
				&dev_priv->mm.bound_list, global_list) {
		DRM_DEBUG_KMS("reserving preallocated space: %x + %zx\n",
			      obj->gtt_offset, obj->base.size);

		BUG_ON(obj->gtt_space != I915_GTT_RESERVED);
		obj->gtt_space = drm_mm_create_block(&dev_priv->mm.gtt_space,
						     obj->gtt_offset,
						     obj->base.size,
						     false);
		obj->has_global_gtt_mapping = 1;
	}

	dev_priv->gtt.start = start;
	dev_priv->gtt.total = end - start;
}

static bool
intel_enable_ppgtt(struct drm_device *dev)
{
	if (i915_enable_ppgtt >= 0)
		return i915_enable_ppgtt;

	/* Disable ppgtt on SNB if VT-d is on. */
	if (INTEL_INFO(dev)->gen == 6)
		return false;

	return true;
}

void i915_gem_init_global_gtt(struct drm_device *dev)
{
	struct drm_i915_private *dev_priv = dev->dev_private;
	unsigned long gtt_size, mappable_size;

	gtt_size = dev_priv->gtt.total;
	mappable_size = dev_priv->gtt.mappable_end;

	if (intel_enable_ppgtt(dev) && HAS_ALIASING_PPGTT(dev)) {

		if (INTEL_INFO(dev)->gen <= 7) {
			/* PPGTT pdes are stolen from global gtt ptes, so shrink the
			 * aperture accordingly when using aliasing ppgtt. */
			gtt_size -= I915_PPGTT_PD_ENTRIES*PAGE_SIZE;
		}
	}
	i915_gem_setup_global_gtt(dev, 0, mappable_size, gtt_size);

	setup_scratch_page(dev);

	if (intel_enable_ppgtt(dev) && HAS_ALIASING_PPGTT(dev)) {
		int ret;
		ret = i915_gem_init_aliasing_ppgtt(dev);
		if (!ret)
			return;
		DRM_ERROR("Aliased PPGTT setup failed %d\n", ret);
		drm_mm_takedown(&dev_priv->mm.gtt_space);
		gtt_size += I915_PPGTT_PD_ENTRIES*PAGE_SIZE;
	}

}

int setup_scratch_page(struct drm_device *dev)
{
	struct drm_i915_private *dev_priv = dev->dev_private;
	int gen;

	/* setup scratch page */
	dev_priv->gtt.scratch_page = kzalloc(sizeof(struct drm_gem_object), GFP_KERNEL);
	if (dev_priv->gtt.scratch_page == NULL)
		return (-ENOMEM);

	if (IS_G33(dev))
		gen = 33;
	else
		gen = INTEL_INFO(dev)->gen * 10;

	if (drm_gem_object_init(dev, dev_priv->gtt.scratch_page, DRM_PAGE_SIZE, gen) != 0) {
		kmem_free(dev_priv->gtt.scratch_page, sizeof (struct drm_gem_object));
		return (-ENOMEM);
	}
	(void) memset(dev_priv->gtt.scratch_page->kaddr, 0, DRM_PAGE_SIZE);

	return 0;
}

void teardown_scratch_page(struct drm_device *dev)
{
	struct drm_i915_private *dev_priv = dev->dev_private;

	drm_gem_object_release(dev_priv->gtt.scratch_page);
	kmem_free(dev_priv->gtt.scratch_page, sizeof (struct drm_gem_object));
}

static inline unsigned int gen6_get_total_gtt_size(u16 snb_gmch_ctl)
{
	snb_gmch_ctl >>= SNB_GMCH_GGMS_SHIFT;
	snb_gmch_ctl &= SNB_GMCH_GGMS_MASK;
	return snb_gmch_ctl << 20;
}

static inline size_t gen6_get_stolen_size(u16 snb_gmch_ctl)
{
	snb_gmch_ctl >>= SNB_GMCH_GMS_SHIFT;
	snb_gmch_ctl &= SNB_GMCH_GMS_MASK;
	return snb_gmch_ctl << 25; /* 32 MB units */
}

static ddi_device_acc_attr_t gtt_attr = {
	DDI_DEVICE_ATTR_V0,
	DDI_NEVERSWAP_ACC,
	DDI_STRICTORDER_ACC,
};

#define GEN6_GTTMMADR	1
#define GEN6_GTT_OFFSET	0x200000

static void i915_gen6_gtt_ioremap(struct drm_local_map *map, struct drm_device *dev)
{
	caddr_t base;
	int ret;

	ret = ddi_regs_map_setup(dev->devinfo, GEN6_GTTMMADR,
			(caddr_t *)&base, 0, 0,
			&gtt_attr, &map->acc_handle);

	if (ret != DDI_SUCCESS) {
		DRM_ERROR("failed to map GTT");
	}

	map->handle = (void *)(base + GEN6_GTT_OFFSET);
}

static int gen6_gmch_probe(struct drm_device *dev,
			   size_t *gtt_total,
			   size_t *stolen)
{
	struct drm_i915_private *dev_priv = dev->dev_private;
	unsigned int gtt_size;
	u16 snb_gmch_ctl;

	dev_priv->gtt.mappable_end = pci_resource_len(dev->pdev, 1);

	/* 64/512MB is the current min/max we actually know of, but this is just
	 * a coarse sanity check.
	 */
	if ((dev_priv->gtt.mappable_end < (64<<20) ||
	     (dev_priv->gtt.mappable_end > (512<<20)))) {
		DRM_ERROR("Unknown GMADR size (%lx)\n",
			  dev_priv->gtt.mappable_end);
		return -ENXIO;
	}

	pci_read_config_word(dev->pdev, SNB_GMCH_CTRL, &snb_gmch_ctl);
	gtt_size = gen6_get_total_gtt_size(snb_gmch_ctl);

	*stolen = gen6_get_stolen_size(snb_gmch_ctl);

	*gtt_total = (gtt_size / sizeof(gen6_gtt_pte_t)) << PAGE_SHIFT;

	/* For GEN6+ the PTEs for the ggtt live at 2MB + BAR0 */
	dev_priv->gtt.gtt_mapping.offset = dev->agp_aperbase;
	dev_priv->gtt.gtt_mapping.size = gtt_size;
	dev_priv->gtt.gtt_mapping.type = 0;
	dev_priv->gtt.gtt_mapping.flags = 0;
	dev_priv->gtt.gtt_mapping.mtrr = 0;

	i915_gen6_gtt_ioremap(&dev_priv->gtt.gtt_mapping, dev);

	if (dev_priv->gtt.gtt_mapping.handle == NULL) {
		DRM_ERROR("Failed to map the gtt page table");
		return -ENOMEM;
	}
	dev_priv->gtt.virtual_gtt = (caddr_t)dev_priv->gtt.gtt_mapping.handle;

	dev_priv->gtt.gtt_clear_range = gen6_ggtt_clear_range;
	dev_priv->gtt.gtt_insert_entries = gen6_ggtt_insert_entries;

	return 0;
}

static void gen6_gmch_remove(struct drm_device *dev)
{
	struct drm_i915_private *dev_priv = dev->dev_private;
	drm_core_ioremapfree(&dev_priv->gtt.gtt_mapping, dev);
}

static unsigned int
intel_gtt_stolen_size(struct drm_device *dev)
{
	u16 gmch_ctrl;
	u8 rdct;
	int local = 0;
	static const int ddt[4] = { 0, 16, 32, 64 };
	unsigned int stolen_size = 0;
	drm_i915_private_t *dev_priv = dev->dev_private;

	if ( INTEL_INFO(dev)->gen == 1)
		return 0; /* no stolen mem on i81x */

	if (i915_bridge_dev_read_config_word(&dev_priv->bridge_dev, INTEL_GMCH_CTRL, &gmch_ctrl))
		return 0;

	if (dev->pdev->device == PCI_DEVICE_ID_INTEL_82830_HB ||
	    dev->pdev->device == PCI_DEVICE_ID_INTEL_82845G_HB) {
		switch (gmch_ctrl & I830_GMCH_GMS_MASK) {
		case I830_GMCH_GMS_STOLEN_512:
			stolen_size = KB(512);
			break;
		case I830_GMCH_GMS_STOLEN_1024:
			stolen_size = MB(1);
			break;
		case I830_GMCH_GMS_STOLEN_8192:
			stolen_size = MB(8);
			break;
		case I830_GMCH_GMS_LOCAL:
			rdct = I915_READ8(I830_RDRAM_CHANNEL_TYPE);
			stolen_size = (I830_RDRAM_ND(rdct) + 1) *
					MB(ddt[I830_RDRAM_DDT(rdct)]);
			local = 1;
			break;
		default:
			stolen_size = 0;
			break;
		}
	} else {
		switch (gmch_ctrl & INTEL_GMCH_GMS_MASK) {
		case INTEL_855_GMCH_GMS_STOLEN_1M:
			stolen_size = MB(1);
			break;
		case INTEL_855_GMCH_GMS_STOLEN_4M:
			stolen_size = MB(4);
			break;
		case INTEL_855_GMCH_GMS_STOLEN_8M:
			stolen_size = MB(8);
			break;
		case INTEL_855_GMCH_GMS_STOLEN_16M:
			stolen_size = MB(16);
			break;
		case INTEL_855_GMCH_GMS_STOLEN_32M:
			stolen_size = MB(32);
			break;
		case INTEL_915G_GMCH_GMS_STOLEN_48M:
			stolen_size = MB(48);
			break;
		case INTEL_915G_GMCH_GMS_STOLEN_64M:
			stolen_size = MB(64);
			break;
		case INTEL_GMCH_GMS_STOLEN_128M:
			stolen_size = MB(128);
			break;
		case INTEL_GMCH_GMS_STOLEN_256M:
			stolen_size = MB(256);
			break;
		case INTEL_GMCH_GMS_STOLEN_96M:
			stolen_size = MB(96);
			break;
		case INTEL_GMCH_GMS_STOLEN_160M:
			stolen_size = MB(160);
			break;
		case INTEL_GMCH_GMS_STOLEN_224M:
			stolen_size = MB(224);
			break;
		case INTEL_GMCH_GMS_STOLEN_352M:
			stolen_size = MB(352);
			break;
		default:
			stolen_size = 0;
			break;
		}
	}

	if (stolen_size > 0) {
		DRM_INFO("detected %dK %s memory\n",
		       stolen_size / KB(1), local ? "local" : "stolen");
	} else {
		DRM_INFO("no pre-allocated video memory detected\n");
		stolen_size = 0;
	}

	return stolen_size;
}

static unsigned int
intel_gtt_mappable_entries(struct drm_device *dev)
{
	unsigned int aperture_size;
	drm_i915_private_t *dev_priv = dev->dev_private;

	if (INTEL_INFO(dev)->gen == 1) {
		u32 smram_miscc;

		pci_read_config_dword(dev->pdev,
				      I810_SMRAM_MISCC, &smram_miscc);

		if ((smram_miscc & I810_GFX_MEM_WIN_SIZE)
				== I810_GFX_MEM_WIN_32M)
			aperture_size = MB(32);
		else
			aperture_size = MB(64);
	} else if (INTEL_INFO(dev)->gen == 2) {
		u16 gmch_ctrl;

		if (i915_bridge_dev_read_config_word(&dev_priv->bridge_dev, INTEL_GMCH_CTRL, &gmch_ctrl))
			return 0;

		if ((gmch_ctrl & INTEL_GMCH_MEM_MASK) == INTEL_GMCH_MEM_64M)
			aperture_size = MB(64);
		else
			aperture_size = MB(128);
	} else {
		/* 9xx supports large sizes, just look at the length */
		aperture_size = pci_resource_len(dev->pdev,
			(IS_G33(dev) || IS_I945GM(dev)) ? 2 : 1);  /* OSOL_i915 */
		DRM_DEBUG("aperture_size=%d", aperture_size);
	}

	return aperture_size >> PAGE_SHIFT;
}

static void
i965_adjust_pgetbl_size(struct drm_device *dev, unsigned int size_flag)
{
	u32 pgetbl_ctl, pgetbl_ctl2;
	drm_i915_private_t *dev_priv = dev->dev_private;

	/* ensure that ppgtt is disabled */
	pgetbl_ctl2 = I915_READ(I965_PGETBL_CTL2);
	pgetbl_ctl2 &= ~I810_PGETBL_ENABLED;
	I915_WRITE(pgetbl_ctl2, I965_PGETBL_CTL2);

	/* write the new ggtt size */
	pgetbl_ctl = I915_READ(I810_PGETBL_CTL);
	pgetbl_ctl &= ~I965_PGETBL_SIZE_MASK;
	pgetbl_ctl |= size_flag;
	I915_WRITE(pgetbl_ctl, I810_PGETBL_CTL);
}

static unsigned int
i965_gtt_total_entries(struct drm_device *dev)
{
	int size;
	u32 pgetbl_ctl;
	u16 gmch_ctl;
	drm_i915_private_t *dev_priv = dev->dev_private;

	if (i915_bridge_dev_read_config_word(&dev_priv->bridge_dev, INTEL_GMCH_CTRL, &gmch_ctl))
		return 0;

	if (INTEL_INFO(dev)->gen == 5) {
		switch (gmch_ctl & G4x_GMCH_SIZE_MASK) {
		case G4x_GMCH_SIZE_1M:
		case G4x_GMCH_SIZE_VT_1M:
			i965_adjust_pgetbl_size(dev, I965_PGETBL_SIZE_1MB);
			break;
		case G4x_GMCH_SIZE_VT_1_5M:
			i965_adjust_pgetbl_size(dev, I965_PGETBL_SIZE_1_5MB);
			break;
		case G4x_GMCH_SIZE_2M:
		case G4x_GMCH_SIZE_VT_2M:
			i965_adjust_pgetbl_size(dev, I965_PGETBL_SIZE_2MB);
			break;
		}
	}

	pgetbl_ctl = I915_READ(I810_PGETBL_CTL);

	switch (pgetbl_ctl & I965_PGETBL_SIZE_MASK) {
	case I965_PGETBL_SIZE_128KB:
		size = KB(128);
		break;
	case I965_PGETBL_SIZE_256KB:
		size = KB(256);
		break;
	case I965_PGETBL_SIZE_512KB:
		size = KB(512);
		break;
	/* GTT pagetable sizes bigger than 512KB are not possible on G33! */
	case I965_PGETBL_SIZE_1MB:
		size = KB(1024);
		break;
	case I965_PGETBL_SIZE_2MB:
		size = KB(2048);
		break;
	case I965_PGETBL_SIZE_1_5MB:
		size = KB(1024 + 512);
		break;
	default:
		DRM_DEBUG("unknown page table size, assuming 512KB");
		size = KB(512);
	}

	return size/4;
}

static unsigned int
intel_gtt_total_entries(struct drm_device *dev)
{
	drm_i915_private_t *dev_priv = dev->dev_private;

	if (IS_G33(dev) || INTEL_INFO(dev)->gen == 4 || INTEL_INFO(dev)->gen == 5)
		return i965_gtt_total_entries(dev);
	else {
		/* On previous hardware, the GTT size was just what was
		 * required to map the aperture.
		 */
		return (dev_priv->gtt.mappable_end >> PAGE_SHIFT);
	}
}

static int i915_gmch_probe(struct drm_device *dev,
			   size_t *gtt_total,
			   size_t *stolen)
{
	struct drm_i915_private *dev_priv = dev->dev_private;

	dev_priv->gtt.mappable_end = intel_gtt_mappable_entries(dev) << PAGE_SHIFT;
	*gtt_total = intel_gtt_total_entries(dev) << PAGE_SHIFT;
	*stolen = intel_gtt_stolen_size(dev);

	dev_priv->gtt.gtt_clear_range = i915_ggtt_clear_range;
	dev_priv->gtt.gtt_insert_entries = i915_ggtt_insert_entries;

	return 0;
}

static void i915_gmch_remove(struct drm_device *dev)
{

}

int i915_gem_gtt_init(struct drm_device *dev)
{
	struct drm_i915_private *dev_priv = dev->dev_private;
	struct i915_gtt *gtt = &dev_priv->gtt;
	int ret;

	gtt->mappable_base = dev->agp_aperbase;

	if (INTEL_INFO(dev)->gen <= 5) {
		dev_priv->gtt.gtt_probe = i915_gmch_probe;
		dev_priv->gtt.gtt_remove = i915_gmch_remove;
	} else {
		dev_priv->gtt.gtt_probe = gen6_gmch_probe;
		dev_priv->gtt.gtt_remove = gen6_gmch_remove;
		if (IS_HASWELL(dev)) {
			dev_priv->gtt.pte_encode = hsw_pte_encode;
		} else if (IS_VALLEYVIEW(dev)) {
			dev_priv->gtt.pte_encode = byt_pte_encode;
		} else {
			dev_priv->gtt.pte_encode = gen6_pte_encode;
		}
	}

	ret = dev_priv->gtt.gtt_probe(dev, &dev_priv->gtt.total,
				     &dev_priv->gtt.stolen_size);
	if (ret)
		return ret;

	/* GMADR is the PCI mmio aperture into the global GTT. */
	DRM_INFO("Memory usable by graphics device = %dM\n",
		 dev_priv->gtt.total >> 20);
	DRM_DEBUG_DRIVER("GMADR size = %ldM\n",
			 dev_priv->gtt.mappable_end >> 20);
	DRM_DEBUG_DRIVER("GTT stolen size = %dM\n",
			 dev_priv->gtt.stolen_size >> 20);

	return 0;
}

void
intel_rw_gtt(struct drm_device *dev,
	size_t size,
	uint32_t gtt_offset,
	void *gttp,
	uint32_t type)
{
	struct drm_i915_private *dev_priv = dev->dev_private;
	unsigned first_entry = gtt_offset >> PAGE_SHIFT;
	unsigned num_entries = size / PAGE_SIZE;
	uint32_t *gtt_addr;
	uint32_t *old_gtt = (uint32_t *)gttp;
	int i, j;

	if (INTEL_INFO(dev)->gen <= 5) {
		(void) drm_agp_rw_gtt(dev, size/PAGE_SIZE, gtt_offset,
					gttp, type);
	} else {
		if (type) {
			for (i = first_entry, j = 0; i < ( first_entry + num_entries); i++, j++) {
				gtt_addr = (uint32_t *)(uintptr_t)((caddr_t)dev_priv->gtt.virtual_gtt
							+ i * sizeof(uint32_t));
				ddi_put32(dev_priv->gtt.gtt_mapping.acc_handle,
						gtt_addr, old_gtt[j]);
			}
		} else {
			for (i = first_entry; i < ( first_entry + num_entries); i++) {
				gtt_addr = (uint32_t *)(uintptr_t)((caddr_t)dev_priv->gtt.virtual_gtt
							+ i * sizeof(uint32_t));
				old_gtt[i] = ddi_get32(dev_priv->gtt.gtt_mapping.acc_handle,gtt_addr);
			}
		}
	}
}

void
i915_clean_gtt(struct drm_device *dev, size_t offset)
{
	struct drm_i915_private *dev_priv = dev->dev_private;
	unsigned first_entry = offset >> PAGE_SHIFT;
	unsigned num_entries = (dev_priv->gtt.total - offset - PAGE_SIZE) >> PAGE_SHIFT;
	uint64_t scratch_page_addr = dev_priv->gtt.scratch_page->pfnarray[0] << PAGE_SHIFT;
	gtt_pte_t *gtt_addr, scratch_pte;
	int i;

	if (INTEL_INFO(dev)->gen <= 5) {
		(void) drm_agp_unbind_pages(dev, NULL, num_entries,
			offset, dev_priv->gtt.scratch_page->pfnarray[0] ,1);
	} else {
		for (i = first_entry ; i < ( first_entry + num_entries); i++) {
			gtt_addr = (gtt_pte_t *)(uintptr_t)((caddr_t)dev_priv->gtt.virtual_gtt
							+ i * sizeof(gtt_pte_t));
			scratch_pte = gen6_pte_encode(dev, scratch_page_addr, I915_CACHE_LLC);
			ddi_put32(dev_priv->gtt.gtt_mapping.acc_handle,
					gtt_addr, scratch_pte);
		}
	}
}
