/*
 * Copyright (c) 2006, 2012, Oracle and/or its affiliates. All rights reserved.
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
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

/*
 * Copyright (c) 2012 Intel Corporation.  All rights reserved.
 */

#include "drm.h"
#include "drmP.h"
#include "i915_drm.h"

int
copyin32_i915_batchbuffer(void * dest, void * src)
{
	struct drm_i915_batchbuffer *dest64 = dest;
	struct drm_i915_batchbuffer32 dest32;

	DRM_COPYFROM_WITH_RETURN(&dest32, (void *)src, sizeof (dest32));

	dest64->start = dest32.start;
	dest64->used = dest32.used;
	dest64->DR1 = dest32.DR1;
	dest64->DR4 = dest32.DR4;
	dest64->num_cliprects = dest32.num_cliprects;
	dest64->cliprects = (drm_clip_rect_t __user *)(uintptr_t)dest32.cliprects;

	return (0);
}

int
copyin32_i915_irq_emit(void *dest, void *src)
{
	struct drm_i915_irq_emit *dest64 = dest;
	struct drm_i915_irq_emit32 dest32;

	DRM_COPYFROM_WITH_RETURN(&dest32, (void *)src, sizeof (dest32));

	dest64->irq_seq = (int __user *)(uintptr_t)dest32.irq_seq;

	return (0);
}

int
copyin32_i915_getparam(void *dest, void *src)
{
	struct drm_i915_getparam *dest64 = dest;
	struct drm_i915_getparam32 dest32;

	DRM_COPYFROM_WITH_RETURN(&dest32, (void *)src, sizeof (dest32));

	dest64->param = dest32.param;
	dest64->value = (int __user *)(uintptr_t)dest32.value;

	return (0);
}

int
copyin32_i915_cmdbuffer(void * dest, void * src)
{
	struct _drm_i915_cmdbuffer *dest64 = dest;
	struct drm_i915_cmdbuffer32 dest32;

	DRM_COPYFROM_WITH_RETURN(&dest32, (void *)src, sizeof (dest32));

	dest64->buf = (char __user *)(uintptr_t)dest32.buf;
	dest64->sz = dest32.sz;
	dest64->DR1 = dest32.DR1;
	dest64->DR4 = dest32.DR4;
	dest64->num_cliprects = dest32.num_cliprects;
	dest64->cliprects = (drm_clip_rect_t __user *)(uintptr_t)dest32.cliprects;

	return (0);
}

int
copyin32_i915_mem_alloc(void *dest, void *src)
{
	struct drm_i915_mem_alloc *dest64 = dest;
	struct drm_i915_mem_alloc32 dest32;

	DRM_COPYFROM_WITH_RETURN(&dest32, (void *)src, sizeof (dest32));

	dest64->region = dest32.region;
	dest64->alignment = dest32.alignment;
	dest64->size = dest32.size;
	dest64->region_offset = (int *)(uintptr_t)dest32.region_offset;

	return (0);
}
