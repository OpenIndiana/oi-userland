/*
 * Copyright (c) 2006, 2013, Oracle and/or its affiliates. All rights reserved.
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

#ifndef __DRM_IDR_H__
#define __DRM_IDR_H__

#include <sys/avl.h>

struct idr_used_id {
	struct avl_node link;
	uint32_t id;
	void *obj;
};

struct idr_free_id {
	struct idr_free_id *next;
	uint32_t id;
};

struct idr_free_id_range {
	struct idr_free_id_range *next;
	uint32_t start;
	uint32_t end;
	uint32_t min_unused_id;
	struct idr_free_id *free_ids;
};

struct idr {
	struct avl_tree used_ids;
	struct idr_free_id_range *free_id_ranges;
	kmutex_t lock;
};

extern void idr_init(struct idr *idrp);
extern int idr_get_new_above(struct idr *idrp, void *obj, int start, int *newid);
extern void* idr_find(struct idr *idrp, uint32_t id);
extern int idr_remove(struct idr *idrp, uint32_t id);
extern void* idr_replace(struct idr *idrp, void *obj, uint32_t id);
extern int idr_pre_get(struct idr *idrp, int flag);
extern int idr_for_each(struct idr *idrp, int (*fn)(int id, void *obj, void *data), void *data);
extern void idr_remove_all(struct idr *idrp);
extern void idr_destroy(struct idr* idrp);

#define DRM_GEM_OBJIDR_HASHNODE 1024

struct idr_list {
	struct idr_list *next, *prev;
	void *obj;
	uint32_t	handle;
	caddr_t	contain_ptr;
};

#define	idr_list_for_each(entry, head) \
	for (int key = 0; key < DRM_GEM_OBJIDR_HASHNODE; key++) \
		list_for_each(entry, &(head)->next[key])

extern int idr_list_pre_get(struct idr_list *head, int flag);
extern void idr_list_init(struct idr_list *head);
extern int idr_list_get_new_above(struct idr_list *head,
				void *obj,
				int *handlep);
extern void *idr_list_find(struct idr_list *head, uint32_t name);
extern int idr_list_remove(struct idr_list *head, uint32_t name);
extern void idr_list_free(struct idr_list *head);
extern int idr_list_empty(struct idr_list *head);
#endif /* __DRM_IDR_H__ */
