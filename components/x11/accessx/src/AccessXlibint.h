/*
 * Copyright (c) 1993, 2004, Oracle and/or its affiliates. All rights reserved.
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
/************************************************************************/
/*									*/
/*		Copyright 1987, 1988, 1989, 1990, 1991, 1992, 1993	*/
/*		by Digital Equipment Corp., Maynard, MA			*/
/*									*/
/*	Permission to use, copy, modify, and distribute this software	*/
/*	and its documentation for any purpose and without fee is hereby	*/
/*	granted, provided that the above copyright notice appear in all	*/
/*	copies and that both that copyright notice and this permission 	*/
/*	notice appear in supporting documentation, and that the name of	*/
/*	Digital not be used in advertising or publicity pertaining to	*/
/*	distribution of the software without specific, written prior 	*/
/*	permission.  							*/
/*									*/
/*	DIGITAL DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE,	*/
/*	INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND 	*/
/*	FITNESS, IN NO EVENT SHALL DIGITAL BE LIABLE FOR ANY SPECIAL,	*/
/*	INDIRECT OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER 	*/
/*	RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN 	*/
/*	ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, 	*/
/*	ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE 	*/
/*	OF THIS SOFTWARE.						*/
/*									*/
/************************************************************************/

/************************************************************************/
/*									*/
/* AccessXlibint   						        */
/* 									*/
/* 	This module provides private definitions for the client library */
/*	of the server extension.					*/
/*									*/
/* Revision History:							*/
/*									*/
/*	11-Jun-1993	WDW & MEN					*/
/*			Develop sample implementation.			*/
/*									*/
/************************************************************************/
#ifndef ACCESSX_LIBINT_H
#define ACCESSX_LIBINT_H

#include "AccessXlib.h"

/* ExtGetReq
 *
 *   Very similar to GetReq in Xlibint.h, but sets the major and minor 
 *   opcodes the way an extension would do it.
 */

/*
#if __STDC__  && !defined(UNIXCPP)
*/

#define ExtGetReq(opcode, name, req) \
        WORD64ALIGN\
        if ((dpy->bufptr + SIZEOF(x##name##Req)) > dpy->bufmax)\
                _XFlush(dpy);\
        req = (x##name##Req *)(dpy->last_req = dpy->bufptr);\
        req->majorOpcode = opcode;\
        req->minorOpcode = X_##name;\
        req->length = (SIZEOF(x##name##Req))>>2;\
        dpy->bufptr += SIZEOF(x##name##Req);\
        dpy->request++

#if 0
/* #else */
/* non-ANSI C uses empty comment instead of "##" for token concatenation 
 */
#define ExtGetReq(opcode, name, req) \
        WORD64ALIGN\
        if ((dpy->bufptr + SIZEOF(x/**/name/**/Req)) > dpy->bufmax)\
                _XFlush(dpy);\
        req = (x/**/name/**/Req *)(dpy->last_req = dpy->bufptr);\
        req->majorOpcode = opcode;\
        req->minorOpcode = X_/**/name;\
        req->length = (SIZEOF(x/**/name/**/Req))>>2;\
        dpy->bufptr += SIZEOF(x/**/name/**/Req);\
        dpy->request++
#endif

/* The following definitions can be used for locking requests in multi-threaded
 * address spaces.
 */
#define LockDisplay(dis)
#define UnlockDisplay(dis)

#endif /* ACCESSX_LIBINT_H */
