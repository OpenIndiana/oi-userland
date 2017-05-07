/*-
 * XCrDynCmap.c - X11 library routine to create dynamic colormaps.
 *
 * Copyright (c) 1990, 2011, Oracle and/or its affiliates. All rights reserved.
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
#include <X11/Xutil.h>
#include "xcolor.h"

Status
XCreateDynamicColormap(
    Display    *dsp,
    int		screen,
    Colormap   *cmap,		/* return */
    Visual    **visual,		/* return */
    XColor     *colors,
    int 	count,
    u_char     *red,
    u_char     *green,
    u_char     *blue)
{
    XVisualInfo vinfo;
    unsigned long pixels[256];
    int		i,
		ncolors,
		planes;
    unsigned long pmasks;
    Status	allocReturn;

    planes = DisplayPlanes(dsp, screen);
    if (!XMatchVisualInfo(dsp, screen, planes, PseudoColor, &vinfo)) 
        if (!XMatchVisualInfo(dsp, screen, planes, GrayScale, &vinfo)) 
            if (!XMatchVisualInfo(dsp, screen, planes, DirectColor, &vinfo)) 
	        return BadMatch;

    {
	*visual = vinfo.visual;
	*cmap = XCreateColormap(dsp, RootWindow(dsp, screen),
				*visual, AllocNone);
	ncolors = vinfo.colormap_size;

	if (count > ncolors)
	    return BadValue;

	allocReturn = XAllocColorCells(dsp, *cmap,
				       False, &pmasks, 0,
				       pixels, ncolors);

/*	This should return Success, but it doesn't... Xlib bug?
 *	(I'll ignore the return value for now...)
 */
#ifdef NOTDEF
	if (allocReturn != Success)
	    return allocReturn;
#endif				/* NOTDEF */

	for (i = 0; i < ncolors - count; i++) {
	    colors[i].pixel = pixels[i];
	    XQueryColor(dsp, DefaultColormap(dsp, screen), &colors[i]);
	}
	for (i = ncolors - count; i < ncolors; i++) {
	    colors[i].pixel = pixels[i];
	    colors[i].red = *red++ << 8;
	    colors[i].green = *green++ << 8;
	    colors[i].blue = *blue++ << 8;
	    colors[i].flags = DoRed | DoGreen | DoBlue;
	}
	XStoreColors(dsp, *cmap, colors, ncolors);
	return Success;
    }
}
