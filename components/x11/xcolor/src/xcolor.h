/*
 * Copyright (c) 2011, Oracle and/or its affiliates. All rights reserved.
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

#ifndef _XCOLOR_H
#define _XCOLOR_H

#include <sys/types.h>
#include <X11/X.h>
#include <X11/Xlib.h>

extern void HSBramp(
    double      h1,
    double      s1,
    double      b1,
    double      h2,
    double      s2,
    double      b2,
    int         start,
    int         end,
    u_char     *red,
    u_char     *green,
    u_char     *blue);

extern Status XCreateDynamicColormap(
    Display    *dsp,
    int		screen,
    Colormap   *cmap,		/* return */
    Visual    **visual,		/* return */
    XColor     *colors,
    int 	count,
    u_char     *red,
    u_char     *green,
    u_char     *blue);

extern Status XCreateHSBColormap(
    Display    *dsp,
    int         screen,
    Colormap   *cmap,		/* colormap return value */
    int         count,		/* number of entries to use */
    double      h1,		/* starting hue */
    double      s1,		/* starting saturation */
    double      b1,		/* starting brightness */
    double      h2,		/* ending hue */
    double      s2,		/* ending saturation */
    double      b2,		/* ending brightness */
    int         bw,		/* Boolean: True = save black and white */
    Visual    **visual);

#endif /* _XCOLOR_H */
