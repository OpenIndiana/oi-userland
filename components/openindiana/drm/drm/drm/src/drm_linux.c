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

#include "drm_linux.h"

void
kref_init(struct kref *kref)
{
	atomic_set(&kref->refcount, 1);
}

void
kref_get(struct kref *kref)
{
	atomic_inc(&kref->refcount);
}

void
kref_put(struct kref *kref, void (*release)(struct kref *kref))
{
	if (!atomic_dec_uint_nv(&kref->refcount))
		release(kref);
}

unsigned int
hweight16(unsigned int w)
{
	w = (w & 0x5555) + ((w >> 1) & 0x5555);
	w = (w & 0x3333) + ((w >> 2) & 0x3333);
	w = (w & 0x0F0F) + ((w >> 4) & 0x0F0F);
	w = (w & 0x00FF) + ((w >> 8) & 0x00FF);
	return (w);
}

long
IS_ERR(const void *ptr)
{
	return ((unsigned long)ptr >= (unsigned long)-255);
}

#ifdef NEVER
/*
 * kfree wrapper to Solaris VM.
 */
void
kfree(void *buf, size_t size) {
}
#endif
