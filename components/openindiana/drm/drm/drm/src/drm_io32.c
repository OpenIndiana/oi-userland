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
#include "drm_io32.h"

#ifdef _MULTI_DATAMODEL

int
copyin32_drm_map(void *dest, void *src)
{
	struct drm_map *dest64 = dest;
	struct drm_map_32 dest32;

	DRM_COPYFROM_WITH_RETURN(&dest32, (void *)src, sizeof(dest32));

	dest64->offset = dest32.offset;
	dest64->size = dest32.size;
	dest64->type = dest32.type;
	dest64->flags = dest32.flags;
	dest64->handle = dest32.handle;
	dest64->mtrr = dest32.mtrr;

	return (0);
}

int
copyout32_drm_map(void *dest, void *src)
{
	struct drm_map *src64 = src;
	struct drm_map_32 src32;

	src32.offset = src64->offset;
	src32.size = (uint32_t)src64->size;
	src32.type = src64->type;
	src32.flags = src64->flags;
	src32.handle = src64->handle;
	src32.mtrr = src64->mtrr;

	DRM_COPYTO_WITH_RETURN((void *)dest, &src32, sizeof(src32));

	return (0);
}

int
copyin32_drm_buf_desc(void *dest, void *src)
{
	struct drm_buf_desc *dest64 = dest;
	struct drm_buf_desc_32 dest32;

	DRM_COPYFROM_WITH_RETURN(&dest32, (void *)src, sizeof(dest32));

	dest64->count = dest32.count;
	dest64->size = dest32.size;
	dest64->low_mark = dest32.low_mark;
	dest64->high_mark = dest32.high_mark;
	dest64->flags = dest32.flags;
	dest64->agp_start = dest32.agp_start;

	return (0);
}

int
copyout32_drm_buf_desc(void *dest, void *src)
{
	struct drm_buf_desc *src64 = src;
	struct drm_buf_desc_32 src32;

	src32.count = src64->count;
	src32.size = (uint32_t)src64->size;
	src32.low_mark = src64->low_mark;
	src32.high_mark = src64->high_mark;
	src32.flags = src64->flags;
	src32.agp_start = (uint32_t)src64->agp_start;

	DRM_COPYTO_WITH_RETURN((void *)dest, &src32, sizeof(src32));

	return (0);
}

int
copyin32_drm_buf_free(void *dest, void *src)
{
	struct drm_buf_free *dest64 = dest;
	struct drm_buf_free_32 dest32;

	DRM_COPYFROM_WITH_RETURN(&dest32, (void *)src, sizeof(dest32));

	dest64->count = dest32.count;
	dest64->list = (int *)(uintptr_t)dest32.list;

	return (0);
}

int
copyin32_drm_buf_map(void *dest, void *src)
{
	struct drm_buf_map *dest64 = dest;
	struct drm_buf_map_32 dest32;

	DRM_COPYFROM_WITH_RETURN(&dest32, (void *)src, sizeof(dest32));

	dest64->count = dest32.count;
	dest64->virtual = (void *)(uintptr_t)dest32.virtual;
	dest64->list = (drm_buf_pub_t *)(uintptr_t)dest32.list;
	dest64->fd = dest32.fd;

	return (0);
}

int
copyout32_drm_buf_map(void *dest, void *src)
{
	struct drm_buf_map *src64 = src;
	struct drm_buf_map_32 src32;

	src32.count = src64->count;
	src32.virtual = (caddr32_t)(uintptr_t)src64->virtual;

	DRM_COPYTO_WITH_RETURN((void *)dest, &src32, sizeof(src32));

	return (0);
}

int
copyin32_drm_ctx_priv_map(void *dest, void *src)
{
	struct drm_ctx_priv_map *dest64 = dest;
	struct drm_ctx_priv_map_32 dest32;

	DRM_COPYFROM_WITH_RETURN(&dest32, (void *)src, sizeof(dest32));

	dest64->ctx_id = dest32.ctx_id;
	dest64->handle = (void *)(uintptr_t)dest32.handle;

	return (0);
}

int
copyout32_drm_ctx_priv_map(void *dest, void *src)
{
	struct drm_ctx_priv_map *src64 = src;
	struct drm_ctx_priv_map_32 src32;

	src32.ctx_id = src64->ctx_id;
	src32.handle = (caddr32_t)(uintptr_t)src64->handle;

	DRM_COPYTO_WITH_RETURN((void *)dest, &src32, sizeof(src32));

	return (0);
}

int
copyin32_drm_ctx_res(void *dest, void *src)
{
	struct drm_ctx_res *dest64 = dest;
	struct drm_ctx_res_32 dest32;

	DRM_COPYFROM_WITH_RETURN(&dest32, (void *)src, sizeof(dest32));

	dest64->count = dest32.count;
	dest64->contexts = (struct drm_ctx *)(uintptr_t)dest32.contexts;

	return (0);
}

int
copyout32_drm_ctx_res(void *dest, void *src)
{
	struct drm_ctx_res *src64 = src;
	struct drm_ctx_res_32 src32;

	src32.count = src64->count;
	src32.contexts = (caddr32_t)(uintptr_t)src64->contexts;

	DRM_COPYTO_WITH_RETURN((void *)dest, &src32, sizeof(src32));

	return (0);
}

int
copyin32_drm_unique(void *dest, void *src)
{
	struct drm_unique *dest64 = dest;
	struct drm_unique_32 dest32;

	DRM_COPYFROM_WITH_RETURN(&dest32, (void *)src, sizeof(dest32));

	dest64->unique_len = dest32.unique_len;
	dest64->unique = (char __user *)(uintptr_t)dest32.unique;

	return (0);
}

int
copyout32_drm_unique(void *dest, void *src)
{
	struct drm_unique *src64 = src;
	struct drm_unique_32 src32;

	src32.unique_len = src64->unique_len;
	src32.unique = (caddr32_t)(uintptr_t)src64->unique;

	DRM_COPYTO_WITH_RETURN((void *)dest, &src32, sizeof(src32));

	return (0);
}

int
copyin32_drm_client(void *dest, void *src)
{
	struct drm_client *dest64 = dest;
	struct drm_client_32 dest32;

	DRM_COPYFROM_WITH_RETURN(&dest32, (void *)src, sizeof(dest32));

	dest64->idx = dest32.idx;
	dest64->auth = dest32.auth;
	dest64->pid = dest32.pid;
	dest64->uid = dest32.uid;
	dest64->magic = dest32.magic;
	dest64->iocs = dest32.iocs;

	return (0);
}

int
copyout32_drm_client(void *dest, void *src)
{
	struct drm_client *src64 = src;
	struct drm_client_32 src32;

	src32.idx = src64->idx;
	src32.auth = src64->auth;
	src32.pid = (uint32_t)src64->pid;
	src32.uid = (uint32_t)src64->uid;
	src32.magic = (uint32_t)src64->magic;
	src32.iocs = (uint32_t)src64->iocs;

	DRM_COPYTO_WITH_RETURN((void *)dest, &src32, sizeof(src32));

	return (0);
}

int
copyout32_drm_stats(void *dest, void *src)
{
	struct drm_stats *src64 = src;
	struct drm_stats_32 src32;
	int i;

	src32.count = (uint32_t)src64->count;
	for (i = 0; i < 15; i++) {
		src32.data[i].value = src64->data[i].value;
		src32.data[i].type = src64->data[i].type;
	}

	DRM_COPYTO_WITH_RETURN((void *)dest, &src32, sizeof(src32));

	return (0);
}

int
copyin32_drm_version(void *dest, void *src)
{
	struct drm_version *dest64 = dest;
	struct drm_version_32 dest32;

	DRM_COPYFROM_WITH_RETURN(&dest32, (void *)src, sizeof(dest32));

	dest64->name_len = dest32.name_len;
	dest64->name = (char *)(uintptr_t)dest32.name;
	dest64->date_len = dest32.date_len;
	dest64->date = (char *)(uintptr_t)dest32.date;
	dest64->desc_len = dest32.desc_len;
	dest64->desc = (char *)(uintptr_t)dest32.desc;

	return (0);
}

int
copyout32_drm_version(void *dest, void *src)
{
	struct drm_version *src64 = src;
	struct drm_version_32 src32;

	src32.version_major = src64->version_major;
	src32.version_minor = src64->version_minor;
	src32.version_patchlevel = src64->version_patchlevel;
	src32.name_len = (uint32_t)src64->name_len;
	src32.name = (caddr32_t)(uintptr_t)src64->name;
	src32.date_len = (uint32_t)src64->date_len;
	src32.date = (caddr32_t)(uintptr_t)src64->date;
	src32.desc_len = (uint32_t)src64->desc_len;
	src32.desc = (caddr32_t)(uintptr_t)src64->desc;

	DRM_COPYTO_WITH_RETURN((void *)dest, &src32, sizeof(src32));

	return (0);
}

int
copyin32_drm_wait_vblank(void *dest, void *src)
{
	union drm_wait_vblank *dest64 = dest;
	union drm_wait_vblank_32 dest32;

	DRM_COPYFROM_WITH_RETURN(&dest32, (void *)src, sizeof(dest32));

	dest64->request.type = dest32.request.type;
	dest64->request.sequence = dest32.request.sequence;
	dest64->request.signal = dest32.request.signal;

	return (0);
}

int
copyout32_drm_wait_vblank(void *dest, void *src)
{
	union drm_wait_vblank *src64 = src;
	union drm_wait_vblank_32 src32;

	src32.reply.type = src64->reply.type;
	src32.reply.sequence = src64->reply.sequence;
	src32.reply.tval_sec = (int32_t)src64->reply.tval_sec;
	src32.reply.tval_usec = (int32_t)src64->reply.tval_usec;

	DRM_COPYTO_WITH_RETURN((void *)dest, &src32, sizeof(src32));

	return (0);
}

int
copyin32_drm_scatter_gather(void *dest, void *src)
{
	struct drm_scatter_gather *dest64 = dest;
	struct drm_scatter_gather_32 dest32;

	DRM_COPYFROM_WITH_RETURN(&dest32, (void *)src, sizeof(dest32));

	dest64->size = dest32.size;
	dest64->handle = dest32.handle;

	return (0);
}

int
copyout32_drm_scatter_gather(void *dest, void *src)
{
	struct drm_scatter_gather *src64 = src;
	struct drm_scatter_gather_32 src32;

	src32.size = (uint32_t)src64->size;
	src32.handle = (uint32_t)src64->handle;

	DRM_COPYTO_WITH_RETURN((void *)dest, &src32, sizeof(src32));

	return (0);
}

#endif
