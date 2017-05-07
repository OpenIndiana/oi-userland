/* Copyright (c) 1993, 1994, Oracle and/or its affiliates. All rights reserved.
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


#ifndef	_DGA_EXTERNALDEFS_H
#define	_DGA_EXTERNALDEFS_H

/*
** External defines for libdga.
*/

#define DGA_DRAW_WINDOW			0
#define DGA_DRAW_PIXMAP			1
#define DGA_DRAW_OVERLAY		2

#define DGA_MBACCESS_NONE		0
#define DGA_MBACCESS_SINGLEADDR		1
#define DGA_MBACCESS_MULTIADDR		2

#define DGA_SITE_NULL			0
#define DGA_SITE_DEVICE			1
#define DGA_SITE_SYSTEM			2

#define DGA_SITECHG_UNKNOWN		0
#define DGA_SITECHG_INITIAL		1
#define DGA_SITECHG_ZOMBIE		2
#define DGA_SITECHG_ALIAS		3
#define DGA_SITECHG_CACHE		4
#define DGA_SITECHG_MB			5

#define DGA_MBCHG_UNKNOWN		0
#define DGA_MBCHG_ACTIVATION		1
#define DGA_MBCHG_DEACTIVATION		2
#define DGA_MBCHG_REPLACEMENT	        3

#define DGA_VIS_UNOBSCURED		0
#define DGA_VIS_PARTIALLY_OBSCURED	1
#define DGA_VIS_FULLY_OBSCURED		2

#define DGA_OVLSTATE_SAFE		0
#define DGA_OVLSTATE_MULTIWID		1
#define DGA_OVLSTATE_CONFLICT		2

#define DGA_MAX_GRABBABLE_BUFS       16

#endif /* _DGA_EXTERNALDEFS_H */
