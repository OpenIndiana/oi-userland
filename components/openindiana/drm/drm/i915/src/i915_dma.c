/*
 * Copyright (c) 2006, 2014, Oracle and/or its affiliates. All rights reserved.
 */

/* i915_dma.c -- DMA support for the I915 -*- linux-c -*-
 */
/*
 * Copyright 2003 Tungsten Graphics, Inc., Cedar Park, Texas.
 * Copyright (c) 2009, 2013, Intel Corporation.
 * All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sub license, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice (including the
 * next paragraph) shall be included in all copies or substantial portions
 * of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT.
 * IN NO EVENT SHALL TUNGSTEN GRAPHICS AND/OR ITS SUPPLIERS BE LIABLE FOR
 * ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#include "drmP.h"
#include "drm.h"
#include "drm_crtc_helper.h"
#include "drm_fb_helper.h"
#include "drm_linux.h"
#include "drm_mm.h"
#include "intel_drv.h"
#include "i915_drm.h"
#include "i915_drv.h"
#include "i915_io32.h"
#include "agptarget_io.h"

#define USE_PCI_DMA_API 0

#define LP_RING(d) (&((struct drm_i915_private *)(d))->ring[RCS])

#define BEGIN_LP_RING(n) \
	intel_ring_begin(LP_RING(dev_priv), (n))

#define OUT_RING(x) \
	intel_ring_emit(LP_RING(dev_priv), x)

#define ADVANCE_LP_RING() \
	intel_ring_advance(LP_RING(dev_priv))

/**
 * Lock test for when it's just for synchronization of ring access.
 *
 * In that case, we don't need to do it when GEM is initialized as nobody else
 * has access to the ring.
 */
#define RING_LOCK_TEST_WITH_RETURN(dev, file) do {			\
	if (LP_RING(dev->dev_private)->obj == NULL)			\
		LOCK_TEST_WITH_RETURN(dev, file);			\
} while (__lintzero)

static inline u32
intel_read_legacy_status_page(struct drm_i915_private *dev_priv, int reg)
{
	if (I915_NEED_GFX_HWS(dev_priv->dev)) {
		u32 *regs = (u32 *)dev_priv->dri1.gfx_hws_cpu_addr.handle;
		return regs[reg];
	} else
		return intel_read_status_page(LP_RING(dev_priv), reg);
}

#define READ_HWSP(dev_priv, reg) intel_read_legacy_status_page(dev_priv, reg)
#define READ_BREADCRUMB(dev_priv) READ_HWSP(dev_priv, I915_BREADCRUMB_INDEX)
#define I915_BREADCRUMB_INDEX		0x21

void i915_update_dri1_breadcrumb(struct drm_device *dev)
{
	drm_i915_private_t *dev_priv = dev->dev_private;
	struct drm_i915_master_private *master_priv;

	if (dev->primary->master) {
		master_priv = dev->primary->master->driver_priv;
		if (master_priv->sarea_priv)
			master_priv->sarea_priv->last_dispatch =
				READ_BREADCRUMB(dev_priv);
	}
}

static void i915_write_hws_pga(struct drm_device *dev)
{
	drm_i915_private_t *dev_priv = dev->dev_private;
	u32 addr;

	addr = dev_priv->status_page_dmah->paddr;
	if (INTEL_INFO(dev)->gen >= 4)
		addr |= (dev_priv->status_page_dmah->paddr >> 28) & 0xf0;
	I915_WRITE(HWS_PGA, addr);
}

/**
 * Frees the hardware status page, whether it's a physical address or a virtual
 * address set up by the X Server.
 */
static void i915_free_hws(struct drm_device *dev)
{
	drm_i915_private_t *dev_priv = dev->dev_private;
	struct intel_ring_buffer *ring = LP_RING(dev_priv);

	if (dev_priv->status_page_dmah) {
		drm_pci_free(dev_priv->status_page_dmah);
		dev_priv->status_page_dmah = NULL;
	}

	if (ring->status_page.gfx_addr) {
		ring->status_page.gfx_addr = 0;
		drm_core_ioremapfree(&dev_priv->dri1.gfx_hws_cpu_addr, dev);
	}

	/* Need to rewrite hardware status page */
	I915_WRITE(HWS_PGA, 0x1ffff000);
}

void i915_kernel_lost_context(struct drm_device * dev)
{
	drm_i915_private_t *dev_priv = dev->dev_private;
	struct drm_i915_master_private *master_priv;
	struct intel_ring_buffer *ring = LP_RING(dev_priv);

	/*
	 * We should never lose context on the ring with modesetting
	 * as we don't expose it to userspace
	 */
	if (drm_core_check_feature(dev, DRIVER_MODESET))
		return;

	ring->head = I915_READ_HEAD(ring) & HEAD_ADDR;
	ring->tail = I915_READ_TAIL(ring) & TAIL_ADDR;
	ring->space = ring->head - (ring->tail + I915_RING_FREE_SPACE);
	if (ring->space < 0)
		ring->space += ring->size;

	if (!dev->primary->master)
		return;

	master_priv = dev->primary->master->driver_priv;
	if (ring->head == ring->tail && master_priv->sarea_priv)
		master_priv->sarea_priv->perf_boxes |= I915_BOX_RING_EMPTY;
}

static int i915_dma_cleanup(struct drm_device * dev)
{
	drm_i915_private_t *dev_priv = dev->dev_private;
	int i;

	/* Make sure interrupts are disabled here because the uninstall ioctl
	 * may not have been called from userspace and after dev_private
	 * is freed, it's too late.
	 */
	if (dev->irq_enabled)
		(void) drm_irq_uninstall(dev);

	mutex_lock(&dev->struct_mutex);
	for (i = 0; i < I915_NUM_RINGS; i++)
		intel_cleanup_ring_buffer(&dev_priv->ring[i]);
	mutex_unlock(&dev->struct_mutex);

	/* Clear the HWS virtual address at teardown */
	if (I915_NEED_GFX_HWS(dev))
		i915_free_hws(dev);

	return 0;
}

static int i915_initialize(struct drm_device * dev, drm_i915_init_t * init)
{
	drm_i915_private_t *dev_priv = dev->dev_private;
	struct drm_i915_master_private *master_priv = dev->primary->master->driver_priv;
	int ret;

	master_priv->sarea = drm_getsarea(dev);
	if (master_priv->sarea) {
		master_priv->sarea_priv = (drm_i915_sarea_t *)(uintptr_t)
			((u8 *)master_priv->sarea->handle + init->sarea_priv_offset);
	} else {
		DRM_DEBUG_DRIVER("sarea not found assuming DRI2 userspace\n");
	}

	if (init->ring_size != 0) {
		if (LP_RING(dev_priv)->obj != NULL) {
			(void) i915_dma_cleanup(dev);
			DRM_ERROR("Client tried to initialize ringbuffer in "
				  "GEM mode\n");
			return -EINVAL;
		}

		ret = intel_render_ring_init_dri(dev,
						 init->ring_start,
						 init->ring_size);
		if (ret) {
			(void) i915_dma_cleanup(dev);
			return ret;
		}
	}

	dev_priv->dri1.cpp = init->cpp;
	dev_priv->dri1.back_offset = init->back_offset;
	dev_priv->dri1.front_offset = init->front_offset;
	dev_priv->dri1.current_page = 0;
	if (master_priv->sarea_priv)
		master_priv->sarea_priv->pf_current_page = 0;

	/* Allow hardware batchbuffers unless told otherwise.
	 */
	dev_priv->dri1.allow_batchbuffer = 1;

	return 0;
}

static int i915_dma_resume(struct drm_device * dev)
{
	drm_i915_private_t *dev_priv = (drm_i915_private_t *) dev->dev_private;
	struct intel_ring_buffer *ring = LP_RING(dev_priv);

	DRM_DEBUG_DRIVER("%s\n", __func__);

	if (ring->virtual_start == NULL) {
		DRM_ERROR("can not ioremap virtual address for"
			  " ring buffer\n");
		return -ENOMEM;
	}

	/* Program Hardware Status Page */
	if (!ring->status_page.page_addr) {
		DRM_ERROR("Can not find hardware status page\n");
		return -EINVAL;
	}
	DRM_DEBUG_DRIVER("hw status page @ %p\n",
				ring->status_page.page_addr);
	if (ring->status_page.gfx_addr != 0)
		intel_ring_setup_status_page(ring);
	else
		i915_write_hws_pga(dev);
	DRM_DEBUG_DRIVER("Enabled hardware status page\n");

	return 0;
}
/* LINTED */
static int i915_dma_init(DRM_IOCTL_ARGS)
{
	drm_i915_init_t *init = data;
	int retcode = 0;

	if (drm_core_check_feature(dev, DRIVER_MODESET))
		return -ENODEV;

	switch (init->func) {
	case I915_INIT_DMA:
		retcode = i915_initialize(dev, init);
		break;
	case I915_CLEANUP_DMA:
		retcode = i915_dma_cleanup(dev);
		break;
	case I915_RESUME_DMA:
		retcode = i915_dma_resume(dev);
		break;
	default:
		retcode = -EINVAL;
		break;
	}

	return retcode;
}

/* Implement basically the same security restrictions as hardware does
 * for MI_BATCH_NON_SECURE.  These can be made stricter at any time.
 *
 * Most of the calculations below involve calculating the size of a
 * particular instruction.  It's important to get the size right as
 * that tells us where the next instruction to check is.  Any illegal
 * instruction detected will be given a size of zero, which is a
 * signal to abort the rest of the buffer.
 */
static int validate_cmd(int cmd)
{
	switch (((cmd >> 29) & 0x7)) {
	case 0x0:
		switch ((cmd >> 23) & 0x3f) {
		case 0x0:
			return 1;	/* MI_NOOP */
		case 0x4:
			return 1;	/* MI_FLUSH */
		default:
			return 0;	/* disallow everything else */
		}
#ifndef __SUNPRO_C
		break;
#endif
	case 0x1:
		return 0;	/* reserved */
	case 0x2:
		return (cmd & 0xff) + 2;	/* 2d commands */
	case 0x3:
		if (((cmd >> 24) & 0x1f) <= 0x18)
			return 1;

		switch ((cmd >> 24) & 0x1f) {
		case 0x1c:
			return 1;
		case 0x1d:
			switch ((cmd >> 16) & 0xff) {
			case 0x3:
				return (cmd & 0x1f) + 2;
			case 0x4:
				return (cmd & 0xf) + 2;
			default:
				return (cmd & 0xffff) + 2;
			}
		case 0x1e:
			if (cmd & (1 << 23))
				return (cmd & 0xffff) + 1;
			else
				return 1;
		case 0x1f:
			if ((cmd & (1 << 23)) == 0)	/* inline vertices */
				return (cmd & 0x1ffff) + 2;
			else if (cmd & (1 << 17))	/* indirect random */
				if ((cmd & 0xffff) == 0)
					return 0;	/* unknown length, too hard */
				else
					return (((cmd & 0xffff) + 1) / 2) + 1;
			else
				return 2;	/* indirect sequential */
		default:
			return 0;
		}
	default:
		return 0;
	}

#ifndef __SUNPRO_C
	return 0;
#endif
}

static int i915_emit_cmds(struct drm_device * dev, int *buffer, int dwords)
{
	drm_i915_private_t *dev_priv = dev->dev_private;
	int i, ret;

	if ((dwords+1) * sizeof(int) >= LP_RING(dev_priv)->size - 8)
		return -EINVAL;

	for (i = 0; i < dwords;) {
		int sz = validate_cmd(buffer[i]);
		if (sz == 0 || i + sz > dwords)
			return -EINVAL;
		i += sz;
	}

	ret = BEGIN_LP_RING((dwords+1)&~1);
	if (ret)
		return ret;

	for (i = 0; i < dwords; i++)
		OUT_RING(buffer[i]);
	if (dwords & 1)
		OUT_RING(0);

	ADVANCE_LP_RING();

	return 0;
}

int
i915_emit_box(struct drm_device *dev,
	      struct drm_clip_rect *box,
	      int DR1, int DR4)
{
	struct drm_i915_private *dev_priv = dev->dev_private;
	int ret;

	if (box->y2 <= box->y1 || box->x2 <= box->x1 ||
	    (unsigned) box->y2 <= 0 || (unsigned) box->x2 <= 0) {
		DRM_ERROR("Bad box %d,%d..%d,%d\n",
			  box->x1, box->y1, box->x2, box->y2);
		return -EINVAL;
	}

	if (INTEL_INFO(dev)->gen >= 4) {
		ret = BEGIN_LP_RING(4);
		if (ret)
			return ret;

		OUT_RING(GFX_OP_DRAWRECT_INFO_I965);
		OUT_RING((box->x1 & 0xffff) | (box->y1 << 16));
		OUT_RING(((box->x2 - 1) & 0xffff) | ((box->y2 - 1) << 16));
		OUT_RING(DR4);
	} else {
		ret = BEGIN_LP_RING(6);
		if (ret)
			return ret;

		OUT_RING(GFX_OP_DRAWRECT_INFO);
		OUT_RING(DR1);
		OUT_RING((box->x1 & 0xffff) | (box->y1 << 16));
		OUT_RING(((box->x2 - 1) & 0xffff) | ((box->y2 - 1) << 16));
		OUT_RING(DR4);
		OUT_RING(0);
	}
	ADVANCE_LP_RING();

	return 0;
}

/* XXX: Emitting the counter should really be moved to part of the IRQ
 * emit. For now, do it in both places:
 */

static void i915_emit_breadcrumb(struct drm_device *dev)
{
	drm_i915_private_t *dev_priv = dev->dev_private;
	struct drm_i915_master_private *master_priv = dev->primary->master->driver_priv;

	dev_priv->dri1.counter++;
	if (dev_priv->dri1.counter > 0x7FFFFFFFUL)
		dev_priv->dri1.counter = 0;
	if (master_priv->sarea_priv)
		master_priv->sarea_priv->last_enqueue = dev_priv->dri1.counter;

	if (BEGIN_LP_RING(4) == 0) {
		OUT_RING(MI_STORE_DWORD_INDEX);
		OUT_RING(I915_BREADCRUMB_INDEX << MI_STORE_DWORD_INDEX_SHIFT);
		OUT_RING(dev_priv->dri1.counter);
		OUT_RING(0);
		ADVANCE_LP_RING();
	}
}

static int i915_dispatch_cmdbuffer(struct drm_device * dev,
				   drm_i915_cmdbuffer_t *cmd,
				   struct drm_clip_rect *cliprects,
				   void *cmdbuf)
{
	int nbox = cmd->num_cliprects;
	int i = 0, count, ret;

	if (cmd->sz & 0x3) {
		DRM_ERROR("alignment");
		return -EINVAL;
	}

	i915_kernel_lost_context(dev);

	count = nbox ? nbox : 1;

	for (i = 0; i < count; i++) {
		if (i < nbox) {
			ret = i915_emit_box(dev, &cliprects[i],
					    cmd->DR1, cmd->DR4);
			if (ret)
				return ret;
		}

		ret = i915_emit_cmds(dev, cmdbuf, cmd->sz / 4);
		if (ret)
			return ret;
	}

	i915_emit_breadcrumb(dev);
	return 0;
}

static int i915_dispatch_batchbuffer(struct drm_device * dev,
				     drm_i915_batchbuffer_t * batch,
				     struct drm_clip_rect *cliprects)
{
	struct drm_i915_private *dev_priv = dev->dev_private;
	int nbox = batch->num_cliprects;
	int i, count, ret;

	if ((batch->start | batch->used) & 0x7) {
		DRM_ERROR("alignment");
		return -EINVAL;
	}

	i915_kernel_lost_context(dev);

	count = nbox ? nbox : 1;
	for (i = 0; i < count; i++) {
		if (i < nbox) {
			ret = i915_emit_box(dev, &cliprects[i],
						batch->DR1, batch->DR4);
			if (ret)
				return ret;
		}

		if (!IS_I830(dev) && !IS_845G(dev)) {
			ret = BEGIN_LP_RING(2);
			if (ret)
				return ret;

			if (INTEL_INFO(dev)->gen >= 4) {
				OUT_RING(MI_BATCH_BUFFER_START | (2 << 6) | MI_BATCH_NON_SECURE_I965);
				OUT_RING(batch->start);
			} else {
				OUT_RING(MI_BATCH_BUFFER_START | (2 << 6));
				OUT_RING(batch->start | MI_BATCH_NON_SECURE);
			}
		} else {
			ret = BEGIN_LP_RING(4);
			if (ret)
				return ret;

			OUT_RING(MI_BATCH_BUFFER);
			OUT_RING(batch->start | MI_BATCH_NON_SECURE);
			OUT_RING(batch->start + batch->used - 4);
			OUT_RING(0);
		}
		ADVANCE_LP_RING();
	}


	if (IS_G4X(dev) || IS_GEN5(dev)) {
		if (BEGIN_LP_RING(2) == 0) {
			OUT_RING(MI_FLUSH | MI_NO_WRITE_FLUSH | MI_INVALIDATE_ISP);
			OUT_RING(MI_NOOP);
			ADVANCE_LP_RING();
		}
	}

	i915_emit_breadcrumb(dev);
	return 0;
}

static int i915_dispatch_flip(struct drm_device * dev)
{
	drm_i915_private_t *dev_priv = dev->dev_private;
	struct drm_i915_master_private *master_priv =
		dev->primary->master->driver_priv;
	int ret;

	if (!master_priv->sarea_priv)
		return -EINVAL;

	DRM_DEBUG_DRIVER("%s: page=%d pfCurrentPage=%d\n",
			  __func__,
			 dev_priv->dri1.current_page,
			 master_priv->sarea_priv->pf_current_page);

	i915_kernel_lost_context(dev);

	ret = BEGIN_LP_RING(10);
	if (ret)
		return ret;

	OUT_RING(MI_FLUSH | MI_READ_FLUSH);
	OUT_RING(0);

	OUT_RING(CMD_OP_DISPLAYBUFFER_INFO | ASYNC_FLIP);
	OUT_RING(0);
	if (dev_priv->dri1.current_page == 0) {
		OUT_RING(dev_priv->dri1.back_offset);
		dev_priv->dri1.current_page = 1;
	} else {
		OUT_RING(dev_priv->dri1.front_offset);
		dev_priv->dri1.current_page = 0;
	}
	OUT_RING(0);

	OUT_RING(MI_WAIT_FOR_EVENT | MI_WAIT_FOR_PLANE_A_FLIP);
	OUT_RING(0);

	ADVANCE_LP_RING();

	master_priv->sarea_priv->last_enqueue = dev_priv->dri1.counter++;

	if (BEGIN_LP_RING(4) == 0) {
		OUT_RING(MI_STORE_DWORD_INDEX);
		OUT_RING(I915_BREADCRUMB_INDEX << MI_STORE_DWORD_INDEX_SHIFT);
		OUT_RING(dev_priv->dri1.counter);
		OUT_RING(0);
		ADVANCE_LP_RING();
	}

	master_priv->sarea_priv->pf_current_page = dev_priv->dri1.current_page;
	return 0;
}

static int i915_quiescent(struct drm_device * dev)
{
	i915_kernel_lost_context(dev);
	return intel_ring_idle(LP_RING(dev->dev_private));
}

/* LINTED */
static int i915_flush_ioctl(DRM_IOCTL_ARGS)
{
	int ret;

	if (drm_core_check_feature(dev, DRIVER_MODESET))
		return -ENODEV;

	RING_LOCK_TEST_WITH_RETURN(dev, file);

	mutex_lock(&dev->struct_mutex);
	ret = i915_quiescent(dev);
	mutex_unlock(&dev->struct_mutex);

	return ret;
}

/* LINTED */
static int i915_batchbuffer(DRM_IOCTL_ARGS)
{
	drm_i915_private_t *dev_priv = (drm_i915_private_t *) dev->dev_private;
	struct drm_i915_master_private *master_priv = dev->primary->master->driver_priv;
	drm_i915_sarea_t *sarea_priv = (drm_i915_sarea_t *)
	    master_priv->sarea_priv;
	drm_i915_batchbuffer_t *batch = data;
	int ret;
	struct drm_clip_rect *cliprects = NULL;

	if (drm_core_check_feature(dev, DRIVER_MODESET))
		return -ENODEV;

	if (!dev_priv->dri1.allow_batchbuffer) {
		DRM_ERROR("Batchbuffer ioctl disabled\n");
		return -EINVAL;
	}

	DRM_DEBUG_DRIVER("i915 batchbuffer, start %x used %d cliprects %d\n",
			batch->start, batch->used, batch->num_cliprects);

	RING_LOCK_TEST_WITH_RETURN(dev, file);

	if (batch->num_cliprects < 0)
		return -EINVAL;

	if (batch->num_cliprects) {
		cliprects = kcalloc(batch->num_cliprects,
				    sizeof(struct drm_clip_rect),
				    GFP_KERNEL);
		if (cliprects == NULL)
			return -ENOMEM;

		ret = copy_from_user(cliprects, batch->cliprects,
				     batch->num_cliprects *
				     sizeof(struct drm_clip_rect));
		if (ret != 0) {
			ret = -EFAULT;
			goto fail_free;
		}
	}

	mutex_lock(&dev->struct_mutex);
	ret = i915_dispatch_batchbuffer(dev, batch, cliprects);
	mutex_unlock(&dev->struct_mutex);

	if (sarea_priv)
		sarea_priv->last_dispatch = READ_BREADCRUMB(dev_priv);

fail_free:
	kfree(cliprects, batch->num_cliprects * sizeof(struct drm_clip_rect));

	return ret;
}

/* LINTED */
static int i915_cmdbuffer(DRM_IOCTL_ARGS)
{
	drm_i915_private_t *dev_priv = (drm_i915_private_t *) dev->dev_private;
	struct drm_i915_master_private *master_priv = dev->primary->master->driver_priv;
	drm_i915_sarea_t *sarea_priv = (drm_i915_sarea_t *)
	    master_priv->sarea_priv;
	drm_i915_cmdbuffer_t *cmdbuf = data;
	struct drm_clip_rect *cliprects = NULL;
	void *batch_data;
	int ret;

	DRM_DEBUG_DRIVER("i915 cmdbuffer, buf %p sz %d cliprects %d\n",
			(void *)cmdbuf->buf, cmdbuf->sz, cmdbuf->num_cliprects);

	if (drm_core_check_feature(dev, DRIVER_MODESET))
		return -ENODEV;

	RING_LOCK_TEST_WITH_RETURN(dev, file);

	if (cmdbuf->num_cliprects < 0)
		return -EINVAL;

	batch_data = kmalloc(cmdbuf->sz, GFP_KERNEL);
	if (batch_data == NULL)
		return -ENOMEM;

	ret = copy_from_user(batch_data, cmdbuf->buf, cmdbuf->sz);
	if (ret != 0) {
		ret = -EFAULT;
		goto fail_batch_free;
	}

	if (cmdbuf->num_cliprects) {
		cliprects = kcalloc(cmdbuf->num_cliprects,
				    sizeof(struct drm_clip_rect), GFP_KERNEL);
		if (cliprects == NULL) {
			ret = -ENOMEM;
			goto fail_batch_free;
		}

		ret = copy_from_user(cliprects, cmdbuf->cliprects,
				     cmdbuf->num_cliprects *
				     sizeof(struct drm_clip_rect));
		if (ret != 0) {
			ret = -EFAULT;
			goto fail_clip_free;
		}
	}

	mutex_lock(&dev->struct_mutex);
	ret = i915_dispatch_cmdbuffer(dev, cmdbuf, cliprects, batch_data);
	mutex_unlock(&dev->struct_mutex);
	if (ret) {
		DRM_ERROR("i915_dispatch_cmdbuffer failed\n");
		goto fail_clip_free;
	}

	if (sarea_priv)
		sarea_priv->last_dispatch = READ_BREADCRUMB(dev_priv);

fail_clip_free:
	kfree(cliprects, cmdbuf->num_cliprects * sizeof(struct drm_clip_rect));
fail_batch_free:
	kfree(batch_data, cmdbuf->sz);

	return ret;
}

static int i915_emit_irq(struct drm_device * dev)
{
	drm_i915_private_t *dev_priv = dev->dev_private;
	struct drm_i915_master_private *master_priv = dev->primary->master->driver_priv;

	i915_kernel_lost_context(dev);

	DRM_DEBUG_DRIVER("\n");

	dev_priv->dri1.counter++;
	if (dev_priv->dri1.counter > 0x7FFFFFFFUL)
		dev_priv->dri1.counter = 1;
	if (master_priv->sarea_priv)
		master_priv->sarea_priv->last_enqueue = dev_priv->dri1.counter;

	if (BEGIN_LP_RING(4) == 0) {
		OUT_RING(MI_STORE_DWORD_INDEX);
		OUT_RING(I915_BREADCRUMB_INDEX << MI_STORE_DWORD_INDEX_SHIFT);
		OUT_RING(dev_priv->dri1.counter);
		OUT_RING(MI_USER_INTERRUPT);
		ADVANCE_LP_RING();
	}

	return dev_priv->dri1.counter;
}

static int i915_wait_irq(struct drm_device * dev, int irq_nr)
{
	drm_i915_private_t *dev_priv = (drm_i915_private_t *) dev->dev_private;
	struct drm_i915_master_private *master_priv = dev->primary->master->driver_priv;
	int ret = 0;
	struct intel_ring_buffer *ring = LP_RING(dev_priv);

	DRM_DEBUG_DRIVER("irq_nr=%d breadcrumb=%d\n", irq_nr,
		  READ_BREADCRUMB(dev_priv));

	if (READ_BREADCRUMB(dev_priv) >= irq_nr) {
		if (master_priv->sarea_priv)
			master_priv->sarea_priv->last_dispatch = READ_BREADCRUMB(dev_priv);
		return 0;
	}

	if (master_priv->sarea_priv)
		master_priv->sarea_priv->perf_boxes |= I915_BOX_WAIT;

	if (ring->irq_get(ring)) {
		DRM_WAIT_ON(ret, &ring->irq_queue, 3 * DRM_HZ,
			    READ_BREADCRUMB(dev_priv) >= irq_nr);
		ring->irq_put(ring);
	} else if (wait_for(READ_BREADCRUMB(dev_priv) >= irq_nr, 3000))
		ret = -EBUSY;

	if (ret == -EBUSY) {
		DRM_ERROR("EBUSY -- rec: %d emitted: %d\n",
			  READ_BREADCRUMB(dev_priv), (int)dev_priv->dri1.counter);
	}

	return ret;
}

/* Needs the lock as it touches the ring.
 */
/* LINTED */
int i915_irq_emit(DRM_IOCTL_ARGS)
{
	drm_i915_private_t *dev_priv = dev->dev_private;
	drm_i915_irq_emit_t *emit = data;
	int result;

	if (drm_core_check_feature(dev, DRIVER_MODESET))
		return -ENODEV;

	if (!dev_priv || !LP_RING(dev_priv)->virtual_start) {
		DRM_ERROR("called with no initialization\n");
		return -EINVAL;
	}

	RING_LOCK_TEST_WITH_RETURN(dev, file);

	mutex_lock(&dev->struct_mutex);
	result = i915_emit_irq(dev);
	mutex_unlock(&dev->struct_mutex);

	if (DRM_COPY_TO_USER(emit->irq_seq, &result, sizeof(int))) {
		DRM_ERROR("copy_to_user\n");
		return -EFAULT;
	}

	return 0;
}

/* Doesn't need the hardware lock.
 */
/* LINTED */
int i915_irq_wait(DRM_IOCTL_ARGS)
{
	drm_i915_private_t *dev_priv = dev->dev_private;
	drm_i915_irq_wait_t *irqwait = data;

	if (drm_core_check_feature(dev, DRIVER_MODESET))
		return -ENODEV;

	if (!dev_priv) {
		DRM_ERROR("called with no initialization\n");
		return -EINVAL;
	}

	return i915_wait_irq(dev, irqwait->irq_seq);
}

/* LINTED */
int i915_vblank_pipe_get(DRM_IOCTL_ARGS)
{
	drm_i915_private_t *dev_priv = dev->dev_private;
	drm_i915_vblank_pipe_t *pipe = data;

	if (drm_core_check_feature(dev, DRIVER_MODESET))
		return -ENODEV;

	if (!dev_priv) {
		DRM_ERROR("called with no initialization\n");
		return -EINVAL;
	}

	pipe->pipe = DRM_I915_VBLANK_PIPE_A | DRM_I915_VBLANK_PIPE_B;

	return 0;
}

/**
 * Schedule buffer swap at given vertical blank.
 */
/* LINTED */
int i915_vblank_swap(DRM_IOCTL_ARGS)
{
	/* The delayed swap mechanism was fundamentally racy, and has been
	 * removed.  The model was that the client requested a delayed flip/swap
	 * from the kernel, then waited for vblank before continuing to perform
	 * rendering.  The problem was that the kernel might wake the client
	 * up before it dispatched the vblank swap (since the lock has to be
	 * held while touching the ringbuffer), in which case the client would
	 * clear and start the next frame before the swap occurred, and
	 * flicker would occur in addition to likely missing the vblank.
	 *
	 * In the absence of this ioctl, userland falls back to a correct path
	 * of waiting for a vblank, then dispatching the swap on its own.
	 * Context switching to userland and back is plenty fast enough for
	 * meeting the requirements of vblank swapping.
	 */
	return -EINVAL;
}

/* LINTED */
static int i915_flip_bufs(DRM_IOCTL_ARGS)
{
	int ret;

	if (drm_core_check_feature(dev, DRIVER_MODESET))
		return -ENODEV;

	DRM_DEBUG_DRIVER("%s\n", __func__);

	RING_LOCK_TEST_WITH_RETURN(dev, file);

	mutex_lock(&dev->struct_mutex);
	ret = i915_dispatch_flip(dev);
	mutex_unlock(&dev->struct_mutex);

	return ret;
}

/* LINTED */
static int i915_getparam(DRM_IOCTL_ARGS)
{
	drm_i915_private_t *dev_priv = dev->dev_private;
	drm_i915_getparam_t *param = data;
	int value;

	if (!dev_priv) {
		DRM_ERROR("called with no initialization\n");
		return -EINVAL;
	}

	switch (param->param) {
	case I915_PARAM_IRQ_ACTIVE:
		value = dev->pdev->irq ? 1 : 0;
		break;
	case I915_PARAM_ALLOW_BATCHBUFFER:
		value = dev_priv->dri1.allow_batchbuffer ? 1 : 0;
		break;
	case I915_PARAM_LAST_DISPATCH:
		value = READ_BREADCRUMB(dev_priv);
		break;
	case I915_PARAM_CHIPSET_ID:
		value = dev->pci_device;
		break;
	case I915_PARAM_HAS_GEM:
		value = 1;
		break;
	case I915_PARAM_NUM_FENCES_AVAIL:
		value = dev_priv->num_fence_regs - dev_priv->fence_reg_start;
		break;
	case I915_PARAM_HAS_OVERLAY:
		value = dev_priv->overlay ? 1 : 0;
		break;
	case I915_PARAM_HAS_PAGEFLIPPING:
		value = 1;
		break;
	case I915_PARAM_HAS_EXECBUF2:
		/* depends on GEM */
		value = 1;
		break;
	case I915_PARAM_HAS_BSD:
		value = intel_ring_initialized(&dev_priv->ring[VCS]);
		break;
	case I915_PARAM_HAS_BLT:
		value = intel_ring_initialized(&dev_priv->ring[BCS]);
		break;
	case I915_PARAM_HAS_VEBOX:
		value = intel_ring_initialized(&dev_priv->ring[VECS]);
		break;
	case I915_PARAM_HAS_RELAXED_FENCING:
		value = 1;
		break;
	case I915_PARAM_HAS_COHERENT_RINGS:
		value = 1;
		break;
	case I915_PARAM_HAS_EXEC_CONSTANTS:
		value = INTEL_INFO(dev)->gen >= 4;
		break;
	case I915_PARAM_HAS_RELAXED_DELTA:
		value = 1;
		break;
	case I915_PARAM_HAS_GEN7_SOL_RESET:
		value = 1;
		break;
	case I915_PARAM_HAS_LLC:
		value = HAS_LLC(dev);
		break;
	case I915_PARAM_HAS_ALIASING_PPGTT:
		value = dev_priv->mm.aliasing_ppgtt ? 1 : 0;
		break;
	case I915_PARAM_HAS_WAIT_TIMEOUT:
		value = 1;
		break;
	case I915_PARAM_HAS_SEMAPHORES:
		value = i915_semaphore_is_enabled(dev);
		break;
	case I915_PARAM_HAS_PRIME_VMAP_FLUSH:
		value = 1;
		break;
	case I915_PARAM_HAS_SECURE_BATCHES:
		/* not support yet */
		value = 0;
		break;
	case I915_PARAM_HAS_PINNED_BATCHES:
		value = 1;
		break;
	case I915_PARAM_HAS_EXEC_NO_RELOC:
		value = 1;
		break;
	case I915_PARAM_HAS_EXEC_HANDLE_LUT:
		value = 1;
		break;
	default:
		DRM_DEBUG_DRIVER("Unknown parameter %d\n",
				 param->param);
		return -EINVAL;
	}

	if (DRM_COPY_TO_USER(param->value, &value, sizeof(int))) {
		DRM_ERROR("DRM_COPY_TO_USER failed\n");
		return -EFAULT;
	}

	return 0;
}

/* LINTED */
static int i915_setparam(DRM_IOCTL_ARGS)
{
	drm_i915_private_t *dev_priv = dev->dev_private;
	drm_i915_setparam_t *param = data;

	if (!dev_priv) {
		DRM_ERROR("called with no initialization\n");
		return -EINVAL;
	}

	switch (param->param) {
	case I915_SETPARAM_USE_MI_BATCHBUFFER_START:
		break;
	case I915_SETPARAM_TEX_LRU_LOG_GRANULARITY:
		break;
	case I915_SETPARAM_ALLOW_BATCHBUFFER:
		dev_priv->dri1.allow_batchbuffer = param->value ? 1 : 0;
		break;
	case I915_SETPARAM_NUM_USED_FENCES:
		if (param->value > dev_priv->num_fence_regs ||
		    param->value < 0)
			return -EINVAL;
		/* Userspace can use first N regs */
		dev_priv->fence_reg_start = param->value;
		break;
	default:
		DRM_DEBUG_DRIVER("unknown parameter %d\n",
					param->param);
		return -EINVAL;
	}

	return 0;
}

/* LINTED */
static int i915_set_status_page(DRM_IOCTL_ARGS)
{
	drm_i915_private_t *dev_priv = dev->dev_private;
	drm_i915_hws_addr_t *hws = data;
	struct intel_ring_buffer *ring;

	if (drm_core_check_feature(dev, DRIVER_MODESET))
		return -ENODEV;

	if (!I915_NEED_GFX_HWS(dev))
		return -EINVAL;

	if (!dev_priv) {
		DRM_ERROR("called with no initialization\n");
		return -EINVAL;
	}

	if (drm_core_check_feature(dev, DRIVER_MODESET)) {
		DRM_ERROR("tried to set status page when mode setting active\n");
		return 0;
	}

	DRM_DEBUG_DRIVER("set status page addr 0x%08x\n", (u32)hws->addr);

	ring = LP_RING(dev_priv);
	ring->status_page.gfx_addr = hws->addr & (0x1ffff<<12);

	dev_priv->dri1.gfx_hws_cpu_addr.offset = (u_offset_t)dev->agp_aperbase + hws->addr;
	dev_priv->dri1.gfx_hws_cpu_addr.size = 4*1024;
	dev_priv->dri1.gfx_hws_cpu_addr.type = 0;
	dev_priv->dri1.gfx_hws_cpu_addr.flags = 0;
	dev_priv->dri1.gfx_hws_cpu_addr.mtrr = 0;

	drm_core_ioremap(&dev_priv->dri1.gfx_hws_cpu_addr, dev);
	if (dev_priv->dri1.gfx_hws_cpu_addr.handle == NULL) {
		(void) i915_dma_cleanup(dev);
		ring->status_page.gfx_addr = 0;
		DRM_ERROR("can not ioremap virtual address for"
				" G33 hw status page\n");
		return -ENOMEM;
	}

	(void) memset(dev_priv->dri1.gfx_hws_cpu_addr.handle, 0, PAGE_SIZE);
	I915_WRITE(HWS_PGA, ring->status_page.gfx_addr);

	DRM_DEBUG_DRIVER("load hws HWS_PGA with gfx mem 0x%x\n",
			 ring->status_page.gfx_addr);
	DRM_DEBUG_DRIVER("load hws at %p\n",
			 ring->status_page.page_addr);
	return 0;
}

static int i915_get_bridge_dev(struct drm_device *dev)
{
	struct drm_i915_private *dev_priv = dev->dev_private;

	/* OSOL_i915 Begin */
	struct drm_i915_bridge_dev *bridge_dev = &dev_priv->bridge_dev;
	char name[32];
	int i, err;

	if (INTEL_INFO(dev)->gen >= 6)
		return 0;

	if (bridge_dev->ldi_id) {
		DRM_DEBUG("end");
		return 0;
	}

	if (ldi_ident_from_dip(dev->devinfo, &bridge_dev->ldi_id)) {
		bridge_dev->ldi_id = NULL;
		DRM_DEBUG("failed");
		return -1;
	};

	/* Workaround here:
	 * agptarget0 is not always linked to the right device
	 * try agptarget1 if failed at agptarget0
	 */
	for (i = 0; i < 16; i++) {
		(void) sprintf(name, "/dev/agp/agptarget%d", i);
		err = ldi_open_by_name(name, 0, kcred,
		    &bridge_dev->bridge_dev_hdl, bridge_dev->ldi_id);
		if (err == 0) {
			break;
		}
		DRM_INFO("can't open agptarget%d", i);
	}

	if (err) {
		ldi_ident_release(bridge_dev->ldi_id);
		bridge_dev->ldi_id = NULL;
		bridge_dev->bridge_dev_hdl = NULL;
		return -1;
	}
	/* OSOL_i915 End */

	return 0;
}

int i915_bridge_dev_read_config_word(struct drm_i915_bridge_dev *bridge_dev, int where, u16 *val)
{
	u16 data = (u16)where;

	if (ldi_ioctl(bridge_dev->bridge_dev_hdl,
	    AGP_TARGET_PCICONFIG_GET16, (intptr_t)&data, FKIOCTL, kcred, 0))
		return -1;

	*val = data;
	return 0;
}

int i915_bridge_dev_write_config_word(struct drm_i915_bridge_dev *bridge_dev, int where, u16 val)
{
	u32 data = (u16)where << 16 | val;

	if (ldi_ioctl(bridge_dev->bridge_dev_hdl,
	    AGP_TARGET_PCICONFIG_SET16, (intptr_t)&data, FKIOCTL, kcred, 0))
		return -1;

	return 0;
}

/* true = enable decode, false = disable decoder */
/* LINTED */
static unsigned int i915_vga_set_decode(void *cookie, bool state)
{
	struct drm_device *dev = cookie;

	(void) intel_modeset_vga_set_state(dev, state);
	if (state)
		return VGA_RSRC_LEGACY_IO | VGA_RSRC_LEGACY_MEM |
		       VGA_RSRC_NORMAL_IO | VGA_RSRC_NORMAL_MEM;
	else
		return VGA_RSRC_NORMAL_IO | VGA_RSRC_NORMAL_MEM;
}


static int i915_load_modeset_init(struct drm_device *dev)
{
	struct drm_i915_private *dev_priv = dev->dev_private;
	int ret;

	ret = intel_parse_bios(dev);
	if (ret)
		DRM_INFO("failed to find VBIOS tables\n");

	/* Initialise stolen first so that we may reserve preallocated
	 * objects for the BIOS to KMS transition.
	 */
	ret = i915_gem_init_stolen(dev);
	if (ret)
		goto out;

	/* clear interrupt related bits */
	if (dev->driver->irq_uninstall)
		dev->driver->irq_uninstall(dev);

	ret = drm_irq_install(dev);
	if (ret)
		goto cleanup_gem_stolen;

	/* Important: The output setup functions called by modeset_init need
	 * working irqs for e.g. gmbus and dp aux transfers. */
	intel_modeset_init(dev);

	ret = i915_gem_init(dev);
	if (ret)
		goto cleanup_irq;


	intel_modeset_gem_init(dev);

	/* Always safe in the mode setting case. */
	/* FIXME: do pre/post-mode set stuff in core KMS code */
	dev->vblank_disable_allowed = 1;
	if (INTEL_INFO(dev)->num_pipes == 0) {
		dev_priv->mm.suspended = 0;
		return 0;
	}

	if (dev_priv->fbcon_obj != NULL) {
		ret = intel_fbdev_init(dev);
		if (ret)
		goto cleanup_gem;

		drm_register_fbops(dev);
	}

	/* Only enable hotplug handling once the fbdev is fully set up. */
	intel_hpd_init(dev);

	/*
	 * Some ports require correctly set-up hpd registers for detection to
	 * work properly (leading to ghost connected connector status), e.g. VGA
	 * on gm45.  Hence we can only set up the initial fbdev config after hpd
	 * irqs are fully enabled. Now we should scan for the initial config
	 * only once hotplug handling is enabled, but due to screwed-up locking
	 * around kms/fbdev init we can't protect the fdbev initial config
	 * scanning against hotplug events. Hence do this first and ignore the
	 * tiny window where we will loose hotplug notifactions.
	 */
	if (dev_priv->fbcon_obj != NULL)
		intel_fbdev_initial_config(dev);

	/* Only enable hotplug handling once the fbdev is fully set up. */
	dev_priv->enable_hotplug_processing = true;

	drm_kms_helper_poll_init(dev);

	/* We're off and running w/KMS */
	dev_priv->mm.suspended = 0;

	return 0;

cleanup_gem:
	mutex_lock(&dev->struct_mutex);
	i915_gem_cleanup_ringbuffer(dev);
	i915_gem_context_fini(dev);
	mutex_unlock(&dev->struct_mutex);
	i915_gem_cleanup_aliasing_ppgtt(dev);
	drm_mm_takedown(&dev_priv->mm.gtt_space);
cleanup_irq:
	drm_irq_uninstall(dev);
cleanup_gem_stolen:
	i915_gem_cleanup_stolen(dev);
out:
	return ret;
}

/* LINTED */
int i915_master_create(struct drm_device *dev, struct drm_master *master)
{
	struct drm_i915_master_private *master_priv;

	master_priv = kzalloc(sizeof(*master_priv), GFP_KERNEL);
	if (!master_priv)
		return -ENOMEM;

	master->driver_priv = master_priv;
	return 0;
}

/* LINTED */
void i915_master_destroy(struct drm_device *dev, struct drm_master *master)
{
	struct drm_i915_master_private *master_priv = master->driver_priv;

	if (!master_priv)
		return;

	kfree(master_priv, sizeof(struct drm_i915_master_private));

	master->driver_priv = NULL;
}


/* OSOL_i915 Begin */
#define pci_dev_put(d) do_pci_dev_put(&(d))

void do_pci_dev_put(struct drm_i915_bridge_dev *bridge_dev)
{
	if (bridge_dev->bridge_dev_hdl) {
		(void) ldi_close(bridge_dev->bridge_dev_hdl, 0, kcred);
		bridge_dev->bridge_dev_hdl = NULL;
	}

	if (bridge_dev->ldi_id) {
		ldi_ident_release(bridge_dev->ldi_id);
		bridge_dev->ldi_id = NULL;
	}
}
/* OSOL_i915 End */

/**
 * intel_early_sanitize_regs - clean up BIOS state
 * @dev: DRM device
 *
 * This function must be called before we do any I915_READ or I915_WRITE. Its
 * purpose is to clean up any state left by the BIOS that may affect us when
 * reading and/or writing registers.
 */
static void intel_early_sanitize_regs(struct drm_device *dev)
{
	struct drm_i915_private *dev_priv = dev->dev_private;

	if (HAS_FPGA_DBG_UNCLAIMED(dev))
		I915_WRITE_NOTRACE(FPGA_DBG, FPGA_DBG_RM_NOCLAIM);
}

/**
 * i915_driver_load - setup chip and create an initial config
 * @dev: DRM device
 * @flags: startup flags
 *
 * The driver load routine has to do several things:
 *   - drive output discovery via intel_modeset_init()
 *   - initialize the memory manager
 *   - allocate initial config memory
 *   - setup the DRM framebuffer with the allocated memory
 */
int i915_driver_load(struct drm_device *dev, unsigned long flags)
{
	struct drm_i915_private *dev_priv;
	struct intel_device_info *info;
	resource_size_t base, size;
	int ret = 0, mmio_bar;

	info = (struct intel_device_info *) flags;

	/* Refuse to load on gen6+ without kms enabled. */
	if (info->gen >= 6 && !drm_core_check_feature(dev, DRIVER_MODESET))
		return -ENODEV;

	/* i915 has 4 more counters */
	dev->counters += 4;
	dev->types[6] = _DRM_STAT_IRQ;
	dev->types[7] = _DRM_STAT_PRIMARY;
	dev->types[8] = _DRM_STAT_SECONDARY;
	dev->types[9] = _DRM_STAT_DMA;

	dev_priv = kzalloc(sizeof(drm_i915_private_t), GFP_KERNEL);
	if (dev_priv == NULL)
		return -ENOMEM;

	dev->dev_private = (void *)dev_priv;
	dev_priv->dev = dev;
	dev_priv->info = info;

	dev_priv->info = (struct intel_device_info *) flags;

	/* Add register map (needed for suspend/resume) */
	mmio_bar = IS_GEN2(dev) ? 1 : 0;
	base = drm_get_resource_start(dev, mmio_bar);
	size = drm_get_resource_len(dev, mmio_bar);

	dev_priv->regs = drm_alloc(sizeof (drm_local_map_t), DRM_MEM_MAPS);
	dev_priv->regs->offset = base;
	dev_priv->regs->size = size;
	dev_priv->regs->type = _DRM_REGISTERS;
	dev_priv->regs->flags = _DRM_REMOVABLE;
	if (drm_ioremap(dev, dev_priv->regs)) {
		ret = -EIO;
		goto put_bridge;
	}

	DRM_DEBUG("mmio paddr=%lx, kvaddr=%p", dev_priv->regs->offset, dev_priv->regs->handle);

	intel_early_sanitize_regs(dev);
	/* The i915 workqueue is primarily used for batched retirement of
	 * requests (and thus managing bo) once the task has been completed
	 * by the GPU. i915_gem_retire_requests() is called directly when we
	 * need high-priority retirement, such as waiting for an explicit
	 * bo.
	 *
	 * It is also used for periodic low-priority events, such as
	 * idle-timers and hangcheck.
	 *
	 * All tasks on the workqueue are expected to acquire the dev mutex
	 * so there is no point in running more than one instance of the
	 * workqueue at any time: max_active = 1 and NON_REENTRANT.
	 */
	dev_priv->wq = create_workqueue(dev->devinfo, "i915");
	if (dev_priv->wq == NULL) {
		DRM_ERROR("Failed to create i915 workqueue.\n");
		ret = -ENOMEM;
		goto out_rmmap;
	}

	/* The i915 workqueue is primarily used for page_flip and fbc */
	dev_priv->other_wq = create_workqueue(dev->devinfo, "i915_other");
	if (dev_priv->other_wq == NULL) {
		DRM_ERROR("Failed to create i915_other workqueue.\n");
		ret = -ENOMEM;
		goto out_mtrrfree;
	}

	/* This must be called before any calls to HAS_PCH_* */
	intel_detect_pch(dev);

	intel_irq_init(dev);
	intel_pm_init(dev);
	intel_gt_sanitize(dev);
	intel_gt_init(dev);

	if (intel_setup_gmbus(dev) != 0)
		goto out_mtrrfree;

	/* Make sure the bios did its job and set up vital registers */
	intel_setup_bios(dev);

	i915_gem_load(dev);

	/* On the 945G/GM, the chipset reports the MSI capability on the
	 * integrated graphics even though the support isn't actually there
	 * according to the published specs.  It doesn't appear to function
	 * correctly in testing on 945G.
	 * This may be a side effect of MSI having been made available for PEG
	 * and the registers being closely associated.
	 *
	 * According to chipset errata, on the 965GM, MSI interrupts may
	 * be lost or delayed, but we use them anyways to avoid
	 * stuck interrupts on some machines.
	 */
	/* Fix me: Failed to get interrupts after resume, when enable msi */
	/*
	if (!IS_I945G(dev) && !IS_I945GM(dev))
		pci_enable_msi(dev->pdev);
	*/
	spin_lock_init(&dev_priv->irq_lock);
	spin_lock_init(&dev_priv->gpu_error.lock);
	spin_lock_init(&dev_priv->rps.lock);
	spin_lock_init(&dev_priv->dpio_lock);

	spin_lock_init(&dev_priv->rps.hw_lock);
	spin_lock_init(&dev_priv->modeset_restore_lock);

	dev_priv->num_plane = 1;
	if (IS_VALLEYVIEW(dev))
		dev_priv->num_plane = 2;

	if (INTEL_INFO(dev)->num_pipes) {
		ret = drm_vblank_init(dev, INTEL_INFO(dev)->num_pipes);
		if (ret)
			goto out_gem_unload;
	}

	/* Start out suspended */
	dev_priv->mm.suspended = 1;

	if (HAS_POWER_WELL(dev))
		i915_init_power_well(dev);

	if (IS_GEN7(dev))
		i915_try_reset = true;

	dev_priv->gpu_hang = 0;

	init_timer(&dev_priv->gpu_top_timer);
	setup_timer(&dev_priv->gpu_top_timer, gpu_top_handler,
			(void *) dev);

	if (MDB_TRACK_ENABLE)
		INIT_LIST_HEAD(&dev_priv->batch_list);

	return 0;

out_gem_unload:
	destroy_workqueue(dev_priv->other_wq);
out_mtrrfree:
	destroy_workqueue(dev_priv->wq);
out_rmmap:
	drm_ioremapfree(dev_priv->regs);
put_bridge:
free_priv:
	kfree(dev_priv, sizeof(struct drm_i915_private));
	return ret;
}

int i915_driver_unload(struct drm_device *dev)
{
	struct drm_i915_private *dev_priv = dev->dev_private;
	int ret;

	if (HAS_POWER_WELL(dev))
		i915_remove_power_well(dev);

	mutex_lock(&dev->struct_mutex);
	ret = i915_gpu_idle(dev);
	if (ret)
		DRM_ERROR("failed to idle hardware: %d\n", ret);
	i915_gem_retire_requests(dev);
	mutex_unlock(&dev->struct_mutex);

	destroy_workqueue(dev_priv->other_wq);
	destroy_workqueue(dev_priv->wq);

	del_timer_sync(&dev_priv->gpu_top_timer);
	destroy_timer(&dev_priv->gpu_top_timer);
	del_timer_sync(&dev_priv->gpu_error.hangcheck_timer);
	destroy_timer(&dev_priv->gpu_error.hangcheck_timer);

/* XXXX rebracket after this is tested */
	/*
	 * Uninitialized GTT indicates that i915 never opens.
	 * So we should not try to release the resources
	 * which are only allocated in i915_driver_firstopen.
	 */
	if (dev_priv->gtt.total !=0) {

	if (drm_core_check_feature(dev, DRIVER_MODESET)) {
		(void) drm_irq_uninstall(dev);
		/* XXX FIXME vga_client_register(dev->pdev, NULL, NULL, NULL); */
	}

	if (dev->pdev->msi_enabled)
		pci_disable_msi(dev->pdev);

	i915_free_hws(dev);//XXX should still be here ??

	if (drm_core_check_feature(dev, DRIVER_MODESET)) {
		if (dev_priv->fbcon_obj != NULL)
			intel_fbdev_fini(dev);
		intel_modeset_cleanup(dev);

		mutex_lock(&dev->struct_mutex);
		i915_gem_free_all_phys_object(dev);
		i915_gem_cleanup_ringbuffer(dev);
		i915_gem_context_fini(dev);
		mutex_unlock(&dev->struct_mutex);

		i915_gem_cleanup_aliasing_ppgtt(dev);
		i915_gem_cleanup_stolen(dev);
		if (!I915_NEED_GFX_HWS(dev))
			i915_free_hws(dev);
		i915_gem_lastclose(dev);
		if (dev_priv->gtt.scratch_page)
			teardown_scratch_page(dev);
		if (dev_priv->fbcon_obj != NULL) {
			i915_gem_free_object(&dev_priv->fbcon_obj->base);
			dev_priv->fbcon_obj = NULL;
		}
	}
	}
	drm_mm_takedown(&dev_priv->mm.gtt_space);
	dev_priv->gtt.gtt_remove(dev);

	if (dev_priv->regs != NULL)
		(void) drm_rmmap(dev, dev_priv->regs);

	mutex_destroy(&dev_priv->irq_lock);

	pci_dev_put(dev_priv->bridge_dev);

	if (MDB_TRACK_ENABLE) {
		struct batch_info_list *r_list, *list_temp;
		list_for_each_entry_safe(r_list, list_temp, struct batch_info_list, &dev_priv->batch_list, head) {
			list_del(&r_list->head);
			drm_free(r_list->obj_list, r_list->num * sizeof(caddr_t), DRM_MEM_MAPS);
			drm_free(r_list, sizeof (struct batch_info_list), DRM_MEM_MAPS);
		}
		list_del(&dev_priv->batch_list);
	}
	kfree(dev->dev_private, sizeof(drm_i915_private_t));
	dev->dev_private = NULL;

	return 0;
}

int
i915_driver_firstopen(struct drm_device *dev)
{
	static bool first_call = true;
	struct drm_i915_private *dev_priv = dev->dev_private;
	struct pci_dev *pdev = dev->pdev;
	u32 aperbase;
	int ret = 0;

	if (first_call) {
		/* OSOL_i915: moved from i915_driver_load */

		if (i915_get_bridge_dev(dev)) {
			DRM_ERROR("i915_get_bridge_dev() failed.");
			return -EIO;
		}

		/*
		 * AGP has been removed for GEN6+,
		 * So we read the agp base and size here.
		 */
		if (INTEL_INFO(dev)->gen >= 6) {
			pci_read_config_dword(pdev, GEN6_CONF_GMADR, &aperbase);
			dev->agp_aperbase = aperbase & GEN6_GTT_BASE_MASK;
		} else {
			dev->agp_aperbase = dev->agp->agp_info.agpi_aperbase;
		}

		ret = i915_gem_gtt_init(dev);
		if (ret) {
			DRM_ERROR("Failed to initialize GTT\n");
			pci_dev_put(dev_priv->bridge_dev);
			ret = -ENODEV;
			return ret;
		}

		if (drm_core_check_feature(dev, DRIVER_MODESET)) {
			ret = i915_load_modeset_init(dev);
			if (ret < 0) {
				DRM_ERROR("failed to init modeset\n");
				pci_dev_put(dev_priv->bridge_dev);
				return ret;
			}
		}
	}

	dev_priv->isX = 1;
	first_call = false;
	return ret;
}

/* LINTED */
int i915_driver_open(struct drm_device *dev, struct drm_file *file_priv)
{
	struct drm_i915_file_private *i915_file_priv;

	DRM_DEBUG_DRIVER("\n");
	i915_file_priv = (struct drm_i915_file_private *)
	    kmalloc(sizeof(*i915_file_priv), GFP_KERNEL);

	if (!i915_file_priv)
		return -ENOMEM;

	spin_lock_init(&i915_file_priv->mm.lock);
	INIT_LIST_HEAD(&i915_file_priv->mm.request_list);

	idr_init(&i915_file_priv->context_idr);

	i915_file_priv->status = 1;
	file_priv->driver_priv = i915_file_priv;

	return 0;
}

/**
 * i915_driver_lastclose - clean up after all DRM clients have exited
 * @dev: DRM device
 *
 * Take care of cleaning up after all DRM clients have exited.  In the
 * mode setting case, we want to restore the kernel's initial mode (just
 * in case the last client left us in a bad state).
 *
 * Additionally, in the non-mode setting case, we'll tear down the AGP
 * and DMA structures, since the kernel won't be using them, and clea
 * up any GEM state.
 */
void i915_driver_lastclose(struct drm_device * dev)
{
	drm_i915_private_t *dev_priv = dev->dev_private;

	/* On gen6+ we refuse to init without kms enabled, but then the drm core
	 * goes right around and calls lastclose. Check for this and don't clean
	 * up anything. */
	if (!dev_priv)
		return;
	dev_priv->isX = 0;
	if (drm_core_check_feature(dev, DRIVER_MODESET)) {
		intel_fb_restore_mode(dev);
		return;
	}

	i915_gem_lastclose(dev);

	(void) i915_dma_cleanup(dev);
}

void i915_driver_preclose(struct drm_device * dev, struct drm_file *file_priv)
{
	i915_gem_context_close(dev, file_priv);
	i915_gem_release(dev, file_priv);
}

void i915_driver_entervt(struct drm_device *dev)
{
	struct drm_i915_private *dev_priv = dev->dev_private;

	/* Do nothing when coming back from high-res mode (VESA)*/
	if (dev_priv->fbcon_obj)
		return;

	/* Need to do full modeset from VGA TEXT mode */
	if (dev_priv->vt_holding > 0) {
		(void) i915_restore_state(dev);
		if (IS_HASWELL(dev))
			intel_modeset_setup_hw_state(dev, false);
		else
			intel_modeset_setup_hw_state(dev, true);
	}
	dev_priv->vt_holding = 0;
}

void i915_driver_leavevt(struct drm_device *dev)
{
	drm_i915_private_t *dev_priv = dev->dev_private;

	if (dev_priv->fbcon_obj)
		return;

	(void) i915_save_state(dev);

	if (IS_HASWELL(dev))
		intel_modeset_disable(dev);

	dev_priv->vt_holding = 1;
}

/* LINTED */
void i915_driver_postclose(struct drm_device *dev, struct drm_file *file_priv)
{
	struct drm_i915_file_private *i915_file_priv = file_priv->driver_priv;
	kfree(i915_file_priv, sizeof(*i915_file_priv));
	file_priv->driver_priv = NULL;
}

struct drm_ioctl_desc i915_ioctls[] = {
	I915_IOCTL_DEF(DRM_IOCTL_I915_INIT, i915_dma_init, DRM_AUTH|DRM_MASTER|DRM_ROOT_ONLY, NULL, NULL),
	I915_IOCTL_DEF(DRM_IOCTL_I915_FLUSH, i915_flush_ioctl, DRM_AUTH, NULL, NULL),
	I915_IOCTL_DEF(DRM_IOCTL_I915_FLIP, i915_flip_bufs, DRM_AUTH, NULL, NULL),
	I915_IOCTL_DEF(DRM_IOCTL_I915_BATCHBUFFER, i915_batchbuffer, DRM_AUTH, copyin32_i915_batchbuffer, NULL),
	I915_IOCTL_DEF(DRM_IOCTL_I915_IRQ_EMIT, i915_irq_emit, DRM_AUTH, copyin32_i915_irq_emit, NULL),
	I915_IOCTL_DEF(DRM_IOCTL_I915_IRQ_WAIT, i915_irq_wait, DRM_AUTH, NULL, NULL),
	I915_IOCTL_DEF(DRM_IOCTL_I915_GETPARAM, i915_getparam, DRM_AUTH, copyin32_i915_getparam, NULL),
	I915_IOCTL_DEF(DRM_IOCTL_I915_SETPARAM, i915_setparam, DRM_AUTH|DRM_MASTER|DRM_ROOT_ONLY, NULL, NULL),
	I915_IOCTL_DEF(DRM_IOCTL_I915_ALLOC, drm_noop, DRM_AUTH, copyin32_i915_mem_alloc, NULL),
	I915_IOCTL_DEF(DRM_IOCTL_I915_FREE, drm_noop, DRM_AUTH, NULL, NULL),
	I915_IOCTL_DEF(DRM_IOCTL_I915_INIT_HEAP, drm_noop, DRM_AUTH|DRM_MASTER|DRM_ROOT_ONLY, NULL, NULL),
	I915_IOCTL_DEF(DRM_IOCTL_I915_CMDBUFFER, i915_cmdbuffer, DRM_AUTH, copyin32_i915_cmdbuffer, NULL),
	I915_IOCTL_DEF(DRM_IOCTL_I915_DESTROY_HEAP,  drm_noop, DRM_AUTH|DRM_MASTER|DRM_ROOT_ONLY, NULL, NULL),
	I915_IOCTL_DEF(DRM_IOCTL_I915_GET_VBLANK_PIPE,  i915_vblank_pipe_get, DRM_AUTH, NULL, NULL),
	I915_IOCTL_DEF(DRM_IOCTL_I915_VBLANK_SWAP, i915_vblank_swap, DRM_AUTH, NULL, NULL),
	I915_IOCTL_DEF(DRM_IOCTL_I915_HWS_ADDR, i915_set_status_page, DRM_AUTH|DRM_MASTER|DRM_ROOT_ONLY, NULL, NULL),
	I915_IOCTL_DEF(DRM_IOCTL_I915_GEM_INIT, i915_gem_init_ioctl, DRM_AUTH|DRM_MASTER|DRM_ROOT_ONLY|DRM_UNLOCKED, NULL, NULL),
	I915_IOCTL_DEF(DRM_IOCTL_I915_GEM_EXECBUFFER, i915_gem_execbuffer, DRM_AUTH|DRM_UNLOCKED, NULL, NULL),
	I915_IOCTL_DEF(DRM_IOCTL_I915_GEM_EXECBUFFER2, i915_gem_execbuffer2, DRM_AUTH|DRM_UNLOCKED, NULL, NULL),
	I915_IOCTL_DEF(DRM_IOCTL_I915_GEM_PIN, i915_gem_pin_ioctl, DRM_AUTH|DRM_ROOT_ONLY|DRM_UNLOCKED, NULL, NULL),
	I915_IOCTL_DEF(DRM_IOCTL_I915_GEM_UNPIN, i915_gem_unpin_ioctl, DRM_AUTH|DRM_ROOT_ONLY|DRM_UNLOCKED, NULL, NULL),
	I915_IOCTL_DEF(DRM_IOCTL_I915_GEM_BUSY, i915_gem_busy_ioctl, DRM_AUTH|DRM_UNLOCKED, NULL, NULL),
	I915_IOCTL_DEF(DRM_IOCTL_I915_GEM_SET_CACHING, i915_gem_set_caching_ioctl, DRM_UNLOCKED, NULL, NULL),
	I915_IOCTL_DEF(DRM_IOCTL_I915_GEM_GET_CACHING, i915_gem_get_caching_ioctl, DRM_UNLOCKED, NULL, NULL),
	I915_IOCTL_DEF(DRM_IOCTL_I915_GEM_THROTTLE, i915_gem_throttle_ioctl, DRM_AUTH|DRM_UNLOCKED, NULL, NULL),
	I915_IOCTL_DEF(DRM_IOCTL_I915_GEM_ENTERVT, i915_gem_entervt_ioctl, DRM_AUTH|DRM_MASTER|DRM_ROOT_ONLY|DRM_UNLOCKED, NULL, NULL),
	I915_IOCTL_DEF(DRM_IOCTL_I915_GEM_LEAVEVT, i915_gem_leavevt_ioctl, DRM_AUTH|DRM_MASTER|DRM_ROOT_ONLY|DRM_UNLOCKED, NULL, NULL),
	I915_IOCTL_DEF(DRM_IOCTL_I915_GEM_CREATE, i915_gem_create_ioctl, DRM_UNLOCKED, NULL, NULL),
	I915_IOCTL_DEF(DRM_IOCTL_I915_GEM_PREAD, i915_gem_pread_ioctl, DRM_UNLOCKED, NULL, NULL),
	I915_IOCTL_DEF(DRM_IOCTL_I915_GEM_PWRITE, i915_gem_pwrite_ioctl, DRM_UNLOCKED, NULL, NULL),
	I915_IOCTL_DEF(DRM_IOCTL_I915_GEM_MMAP, i915_gem_mmap_ioctl, DRM_UNLOCKED, NULL, NULL),
	I915_IOCTL_DEF(DRM_IOCTL_I915_GEM_MMAP_GTT, i915_gem_mmap_gtt_ioctl, DRM_UNLOCKED, NULL, NULL),
	I915_IOCTL_DEF(DRM_IOCTL_I915_GEM_SET_DOMAIN, i915_gem_set_domain_ioctl, DRM_UNLOCKED, NULL, NULL),
	I915_IOCTL_DEF(DRM_IOCTL_I915_GEM_SW_FINISH, i915_gem_sw_finish_ioctl, DRM_UNLOCKED, NULL, NULL),
	I915_IOCTL_DEF(DRM_IOCTL_I915_GEM_SET_TILING, i915_gem_set_tiling, DRM_UNLOCKED, NULL, NULL),
	I915_IOCTL_DEF(DRM_IOCTL_I915_GEM_GET_TILING, i915_gem_get_tiling, DRM_UNLOCKED, NULL, NULL),
	I915_IOCTL_DEF(DRM_IOCTL_I915_GEM_GET_APERTURE, i915_gem_get_aperture_ioctl, DRM_UNLOCKED, NULL, NULL),
	I915_IOCTL_DEF(DRM_IOCTL_I915_GET_PIPE_FROM_CRTC_ID, intel_get_pipe_from_crtc_id, DRM_UNLOCKED, NULL, NULL),
	I915_IOCTL_DEF(DRM_IOCTL_I915_GEM_MADVISE, i915_gem_madvise_ioctl, DRM_UNLOCKED, NULL, NULL),
	I915_IOCTL_DEF(DRM_IOCTL_I915_OVERLAY_PUT_IMAGE, intel_overlay_put_image, DRM_MASTER|DRM_CONTROL_ALLOW|DRM_UNLOCKED, NULL, NULL),
	I915_IOCTL_DEF(DRM_IOCTL_I915_OVERLAY_ATTRS, intel_overlay_attrs, DRM_MASTER|DRM_CONTROL_ALLOW|DRM_UNLOCKED, NULL, NULL),
	I915_IOCTL_DEF(DRM_IOCTL_I915_SET_SPRITE_COLORKEY, intel_sprite_set_colorkey, DRM_MASTER|DRM_CONTROL_ALLOW|DRM_UNLOCKED, NULL, NULL),
	I915_IOCTL_DEF(DRM_IOCTL_I915_GET_SPRITE_COLORKEY, intel_sprite_get_colorkey, DRM_MASTER|DRM_CONTROL_ALLOW|DRM_UNLOCKED, NULL, NULL),
	I915_IOCTL_DEF(DRM_IOCTL_I915_GEM_WAIT, i915_gem_wait_ioctl, DRM_AUTH|DRM_UNLOCKED, NULL, NULL),
	I915_IOCTL_DEF(DRM_IOCTL_I915_GEM_CONTEXT_CREATE, i915_gem_context_create_ioctl, DRM_UNLOCKED, NULL, NULL),
	I915_IOCTL_DEF(DRM_IOCTL_I915_GEM_CONTEXT_DESTROY, i915_gem_context_destroy_ioctl, DRM_UNLOCKED, NULL, NULL),
	I915_IOCTL_DEF(DRM_IOCTL_I915_REG_READ, i915_reg_read_ioctl, DRM_UNLOCKED, NULL, NULL),
};

int i915_max_ioctl = DRM_ARRAY_SIZE(i915_ioctls);

/**
 * Determine if the device really is AGP or not.
 *
 * All Intel graphics chipsets are treated as AGP, even if they are really
 */
/* LINTED */
int i915_driver_device_is_agp(struct drm_device * dev)
{
	return 1;
}
