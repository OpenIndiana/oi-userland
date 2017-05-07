/*
 * Copyright (c) 1988-91 by Patrick J. Naughton.
 *
 * Permission to use, copy, modify, and distribute this software and its
 * documentation for any purpose and without fee is hereby granted,
 * provided that the above copyright notice appear in all copies and that
 * both that copyright notice and this permission notice appear in
 * supporting documentation.
 *
 * This file is provided AS IS with no warranties of any kind.  The author
 * shall have no liability with respect to the infringement of copyrights,
 * trade secrets or any patents by this file or any part thereof.  In no
 * event will the author be liable for any lost revenue or profits or
 * other special, indirect and consequential damages.
 */

/*
 * Copyright (c) 1990, 2015, Oracle and/or its affiliates. All rights reserved.
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

/*-
 * image.c - image bouncer for xlock, the X Window System lockscreen.
 *
 * Copyright (c) 1991 by Patrick J. Naughton.
 *
 * See xlock.c for copying information.
 *
 * Revision History:
 * 29-Jul-90: Written.
 */

#include "xlock.h"
#include "sunlogo.bit"

static XImage logo = {
    0, 0,			/* width, height */
    0, XYBitmap, 0,		/* xoffset, format, data */
    LSBFirst, 8,		/* byte-order, bitmap-unit */
    LSBFirst, 8, 1		/* bitmap-bit-order, bitmap-pad, depth */
};

#define MAXICONS 1024

typedef struct {
    int         x;
    int         y;
}           point;

typedef struct {
    int         width;
    int         height;
    int         nrows;
    int         ncols;
    int         xb;
    int         yb;
    int         iconmode;
    int         iconcount;
    point       icons[MAXICONS];
    long        startTime;
}           imagestruct;

static imagestruct ims[MAXSCREENS];

void
drawimage(Window      win)
{
    imagestruct *ip = &ims[screen];
    int         i;

    XSetForeground(dsp, Scr[screen].gc, ssblack[screen].pixel);
    for (i = 0; i < ip->iconcount; i++) {
	if (!ip->iconmode)
	    XFillRectangle(dsp, win, Scr[screen].gc,
			   ip->xb + sunlogo_width * ip->icons[i].x,
			   ip->yb + sunlogo_height * ip->icons[i].y,
			   sunlogo_width, sunlogo_height);

	ip->icons[i].x = (int) random() % ip->ncols;
	ip->icons[i].y = (int) random() % ip->nrows;
    }
    if (Scr[screen].npixels == 2)
	XSetForeground(dsp, Scr[screen].gc, sswhite[screen].pixel);
    for (i = 0; i < ip->iconcount; i++) {
	if (Scr[screen].npixels > 2)
	    XSetForeground(dsp, Scr[screen].gc,
			 Scr[screen].pixels[random() % Scr[screen].npixels]);

	XPutImage(dsp, win, Scr[screen].gc, &logo,
		  0, 0,
		  ip->xb + sunlogo_width * ip->icons[i].x,
		  ip->yb + sunlogo_height * ip->icons[i].y,
		  sunlogo_width, sunlogo_height);
    }
}

void
initimage(Window      win)
{
    XWindowAttributes xgwa;
    imagestruct *ip = &ims[screen];

    ip->startTime = seconds();

    logo.data = (char *) sunlogo_bits;
    logo.width = sunlogo_width;
    logo.height = sunlogo_height;
    logo.bytes_per_line = (sunlogo_width + 7) / 8;

    XGetWindowAttributes(dsp, win, &xgwa);
    ip->width = xgwa.width;
    ip->height = xgwa.height;
    ip->ncols = ip->width / sunlogo_width;
    ip->nrows = ip->height / sunlogo_height;
    ip->iconmode = (ip->ncols < 2 || ip->nrows < 2);
    if (ip->iconmode) {
	ip->xb = 0;
	ip->yb = 0;
	ip->iconcount = 1;	/* icon mode */
    } else {
	ip->xb = (ip->width - sunlogo_width * ip->ncols) / 2;
	ip->yb = (ip->height - sunlogo_height * ip->nrows) / 2;
	ip->iconcount = batchcount;
	if ((ip->iconcount) >  MAXICONS)
		ip->iconcount = MAXICONS;
    }
    XSetForeground(dsp, Scr[screen].gc, ssblack[screen].pixel);
    XFillRectangle(dsp, win, Scr[screen].gc, 0, 0, ip->width, ip->height);
}
