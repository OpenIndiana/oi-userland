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

#ifndef __DRM_TIMER_H__
#define __DRM_TIMER_H__

#include <sys/types.h>
#include <sys/conf.h>
#include <sys/ksynch.h>
#include "drm_linux_list.h"
#include "drm_linux.h"

#define del_timer_sync del_timer

struct timer_list {
	struct list_head *head;
	void (*func)(void *);
	void *arg;
	clock_t expires;
	unsigned long expired_time;
	timeout_id_t timer_id;
	kmutex_t lock;
};

extern void init_timer(struct timer_list *timer);
extern void destroy_timer(struct timer_list *timer);
extern void setup_timer(struct timer_list *timer, void (*func)(void *), void *arg);
extern void mod_timer(struct timer_list *timer, clock_t expires);
extern void del_timer(struct timer_list *timer);
extern void test_set_timer(struct timer_list *timer, clock_t expires);

#endif /* __DRM_TIMER_H__ */
