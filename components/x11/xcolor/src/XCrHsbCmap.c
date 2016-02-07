/*-
 * XCrHsbCmap.c - X11 library routine to create an HSB ramp colormaps.
 *
 * Copyright (c) 1991, 2011, Oracle and/or its affiliates. All rights reserved.
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
 *
 * Author: Patrick J. Naughton
 * naughton@sun.com
 */

#include <X11/X.h>
#include <X11/Xos.h>
#include <X11/Xlib.h>
#include "xcolor.h"

Status
XCreateHSBColormap(
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
    Visual    **visual)
{
    u_char      red[256];
    u_char      green[256];
    u_char      blue[256];
    unsigned long pixel;
    Status      status;
    XColor      xcolors[256];

    if (count > 256)
	return BadValue;

    HSBramp(h1, s1, b1, h2, s2, b2, 0, count - 1, red, green, blue);

    if (bw) {
	pixel = WhitePixel(dsp, screen);
	if (pixel < 256)
	    red[pixel] = green[pixel] = blue[pixel] = 0xff;

	pixel = BlackPixel(dsp, screen);
	if (pixel < 256)
	    red[pixel] = green[pixel] = blue[pixel] = 0;
    }
    status = XCreateDynamicColormap(dsp, screen, cmap, visual, xcolors,
				    count, red, green, blue);

    return status;
}
