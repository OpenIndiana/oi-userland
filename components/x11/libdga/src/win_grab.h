/* Copyright (c) 1993, Oracle and/or its affiliates. All rights reserved.
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
 * win_grab.h - DGA Window Grabber definitions
 */

#ifndef _WIN_GRAB_H
#define _WIN_GRAB_H


/****
 *
 * WIN_GRAB.H Window Grabber
 *
 * MACROS: These return info from the client page.
 *
 *	wx_infop(clientp)	the info page.
 *	wx_devname_c(clientp)	returns the w_devname field.
 *	wx_version_c(clientp)	the version
 *	wx_lock_c(clientp)	locks the info page.
 *	wx_unlock_c(clientp)	unlocks the info page.
 *
 * These return info from the info page.
 *
 *	wx_devname(infop)	returns the w_devname field.
 *	wx_version(infop)	the version
 *
 *	wx_shape_flags(infop)	Shapes flag
 *
 ****/



#define	DGA_SH_RECT_FLAG	1
#define	DGA_SH_EMPTY_FLAG	128


/*
 *  Window grabber info macros
 */

#define	wx_infop(clientp)	((WXINFO *) (clientp)->w_info)

#define	wx_version(infop)	((infop)->w_version)

#define wx_shape_flags(infop)			\
	(((struct class_SHAPE_vn *)		\
	    ((char *)(infop) +			\
	     (infop)->u.vn.w_shapeoff))->SHAPE_FLAGS)	\


#endif /* _WIN_GRAB_H */
