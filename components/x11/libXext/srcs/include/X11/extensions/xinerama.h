/* Copyright (c) 2000, 2009, Oracle and/or its affiliates. All rights reserved.
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

/* Header file for Sun-created Xinerama APIs in libXext & libdga
   Mostly deprecated in favor of X.Org standard libXinerama API. */

#ifndef _XINERAMA_H_
#define _XINERAMA_H_

#include <X11/Xfuncproto.h>
#include <X11/extensions/panoramiXext.h>

#define MAXFRAMEBUFFERS       MAXSCREEN

/* in libXext.so */
_X_DEPRECATED
Bool XineramaGetState(Display*, int);
_X_DEPRECATED
Status XineramaGetInfo(Display*, int, XRectangle*, unsigned char*, int*);
Status XineramaGetCenterHint(Display*, int, int*, int*);

/* in libdga.so */
Bool XDgaGetXineramaInfo(Display *, int, XID, XineramaInfo *);

#endif /* _XINERAMA_H_ */
