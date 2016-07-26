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
 * Copyright (c) 1991, 2015, Oracle and/or its affiliates. All rights reserved.
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
 * flame.c - recursive fractal cosmic dust.
 *
 * Copyright (c) 1991 by Patrick J. Naughton.
 *
 * See xlock.c for copying information.
 *
 * Revision History:
 * 24-Jun-91: fixed portability problem with integer mod (%).
 * 06-Jun-91: Written. (received from Spot, spot@cs.cmu.edu).
 */

#include "xlock.h"
#include <math.h>

#define MAXTOTAL	10000
#define MAXBATCH	10

typedef struct {
    double      f[2][3][20];	/* three non-homogeneous transforms */
    int         max_levels;
    int         cur_level;
    int         SNUM;
    int         ANUM;
    int         width, height;
    int         num_points;
    int         total_points;
    int         pixcol;
    Window      win;
    XPoint      pts[MAXBATCH];
}           flamestruct;

static flamestruct flames[MAXSCREENS];

static short
halfrandom(int mv)
{
    static short lasthalf = 0;
    unsigned long r;

    if (lasthalf) {
	r = (unsigned long) lasthalf;
	lasthalf = 0;
    } else {
	r = (unsigned long) random();
	lasthalf = (short) (r >> 16);
    }
    return (short) (r % mv);
}

void
initflame(Window      win)
{
    flamestruct *fs = &flames[screen];
    XWindowAttributes xwa;

    srandom((uint_t) time((long *) 0));

    if ((batchcount < 1) || (batchcount > 64))
	batchcount = 20;

    XGetWindowAttributes(dsp, win, &xwa);
    fs->width = xwa.width;
    fs->height = xwa.height;

    fs->max_levels = batchcount;
    fs->win = win;

    XSetForeground(dsp, Scr[screen].gc, ssblack[screen].pixel);
    XFillRectangle(dsp, win, Scr[screen].gc, 0, 0, fs->width, fs->height);

    if (Scr[screen].npixels > 2) {
	fs->pixcol = halfrandom(Scr[screen].npixels);
	XSetForeground(dsp, Scr[screen].gc, Scr[screen].pixels[fs->pixcol]);
    } else {
	XSetForeground(dsp, Scr[screen].gc, sswhite[screen].pixel);
    }
}

static      Bool
recurse(
    flamestruct *fs,
    double x,
    double y,
    int l
    )
{
    if (l == fs->max_levels) {
	fs->total_points++;
	if (fs->total_points > MAXTOTAL)	/* how long each fractal runs */
	    return False;

	if (x > -1.0 && x < 1.0 && y > -1.0 && y < 1.0) {
	    fs->pts[fs->num_points].x = (short) ((fs->width / 2) * (x + 1.0));
	    fs->pts[fs->num_points].y = (short) ((fs->height / 2) * (y + 1.0));
	    fs->num_points++;
	    if (fs->num_points > MAXBATCH) {	/* point buffer size */
		XDrawPoints(dsp, fs->win, Scr[screen].gc, fs->pts,
			    fs->num_points, CoordModeOrigin);
		fs->num_points = 0;
	    }
	}
    } else {
	int i;
	for (i = 0; i < fs->SNUM; i++) {
	    double      nx, ny;
	    nx = fs->f[0][0][i] * x + fs->f[0][1][i] * y + fs->f[0][2][i];
	    ny = fs->f[1][0][i] * x + fs->f[1][1][i] * y + fs->f[1][2][i];
	    if (i < fs->ANUM) {
		nx = sin(nx);
		ny = sin(ny);
	    }
	    if (!recurse(fs, nx, ny, l + 1))
		return False;
	}
    }
    return True;
}


void
drawflame(Window win)
{
    flamestruct *fs = &flames[screen];

    int         i, j, k;
    static int  alt = 0;

    if (!(fs->cur_level++ % fs->max_levels)) {
	XClearWindow(dsp, fs->win);
	alt = !alt;
    } else {
 	if (Scr[screen].npixels > 2) {
  	    XSetForeground(dsp, Scr[screen].gc,
 			   Scr[screen].pixels[fs->pixcol]);
	    if (--fs->pixcol < 0)
 		fs->pixcol = Scr[screen].npixels - 1;
 	}
    }

    /* number of functions */
    fs->SNUM = 2 + (fs->cur_level % 3);

    /* how many of them are of alternate form */
    if (alt)
	fs->ANUM = 0;
    else
	fs->ANUM = halfrandom(fs->SNUM) + 2;

    /* 6 coefs per function */
    for (k = 0; k < fs->SNUM; k++) {
	for (i = 0; i < 2; i++)
	    for (j = 0; j < 3; j++)
		fs->f[i][j][k] = ((double) (random() & 1023) / 512.0 - 1.0);
    }
    fs->num_points = 0;
    fs->total_points = 0;
    (void) recurse(fs, 0.0, 0.0, 0);
    XDrawPoints(dsp, win, Scr[screen].gc,
		fs->pts, fs->num_points, CoordModeOrigin);
}
