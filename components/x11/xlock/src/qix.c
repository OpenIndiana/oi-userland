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
 * Copyright (c) 1989, 2015, Oracle and/or its affiliates. All rights reserved.
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
 * qix.c - Vector swirl for xlock, the X Window System lockscreen.
 *
 * Copyright (c) 1991 by Patrick J. Naughton.
 *
 * See xlock.c for copying information.
 *
 * Revision History:
 * 29-Jul-90: support for multiple screens.
 *	      made check_bounds_?() a macro.
 *	      fixed initial parameter setup.
 * 15-Dec-89: Fix for proper skipping of {White,Black}Pixel() in colors.
 * 08-Oct-89: Fixed bug in memory allocation in initqix().
 *	      Moved seconds() to an extern.
 * 23-Sep-89: Switch to random() and fixed bug w/ less than 4 lines.
 * 20-Sep-89: Lint.
 * 24-Mar-89: Written.
 */

#include "xlock.h"

typedef struct {
    int         x;
    int         y;
}           point;

typedef struct {
    long        startTime;
    uint_t      pix;
    uint_t      first;
    uint_t      last;
    int         dx1;
    int         dy1;
    int         dx2;
    int         dy2;
    int         x1;
    int         y1;
    int         x2;
    int         y2;
    int         offset;
    int         delta;
    uint_t      width;
    uint_t      height;
    uint_t      nlines;
    point      *lineq;
}           qixstruct;

static qixstruct qixs[MAXSCREENS];

void
initqix(Window      win)
{
    XWindowAttributes xgwa;
    qixstruct  *qp = &qixs[screen];

    qp->startTime = seconds();
    if ((batchcount < 1) || (batchcount > 1024))
	batchcount = 64;
    qp->nlines = (batchcount + 1) * 2;
    if (!qp->lineq) {
	qp->lineq = calloc(qp->nlines, sizeof(point));
	if (qp->lineq == NULL)
	    error("allocation failed, unable to get our qix\n");
    }

    XGetWindowAttributes(dsp, win, &xgwa);
    qp->width = xgwa.width;
    qp->height = xgwa.height;
    qp->delta = 16;

    if (qp->width < 100) {	/* icon window */
	qp->nlines /= 4;
	qp->delta /= 4;
    }
    qp->offset = qp->delta / 3;
    qp->last = 0;
    qp->pix = 0;
    qp->dx1 = (int) random() % qp->delta + qp->offset;
    qp->dy1 = (int) random() % qp->delta + qp->offset;
    qp->dx2 = (int) random() % qp->delta + qp->offset;
    qp->dy2 = (int) random() % qp->delta + qp->offset;
    qp->x1 = (int) random() % qp->width;
    qp->y1 = (int) random() % qp->height;
    qp->x2 = (int) random() % qp->width;
    qp->y2 = (int) random() % qp->height;
    XSetForeground(dsp, Scr[screen].gc, ssblack[screen].pixel);
    XFillRectangle(dsp, win, Scr[screen].gc, 0, 0, qp->width, qp->height);
}

#define check_bounds(qp, val, del, max)				\
{								\
    if ((val) < 0) {						\
	*(del) = ((int)random() % (qp)->delta) + (qp)->offset;	\
    } else if ((val) > (max)) {					\
	*(del) = -((int)random() % (qp)->delta) - (qp)->offset;	\
    }								\
}

void
drawqix(Window      win)
{
    qixstruct  *qp = &qixs[screen];

    qp->first = (qp->last + 2) % qp->nlines;

    qp->x1 += qp->dx1;
    qp->y1 += qp->dy1;
    qp->x2 += qp->dx2;
    qp->y2 += qp->dy2;
    check_bounds(qp, qp->x1, &qp->dx1, qp->width);
    check_bounds(qp, qp->y1, &qp->dy1, qp->height);
    check_bounds(qp, qp->x2, &qp->dx2, qp->width);
    check_bounds(qp, qp->y2, &qp->dy2, qp->height);
    XSetForeground(dsp, Scr[screen].gc, ssblack[screen].pixel);
    XDrawLine(dsp, win, Scr[screen].gc,
	      qp->lineq[qp->first].x, qp->lineq[qp->first].y,
	      qp->lineq[qp->first + 1].x, qp->lineq[qp->first + 1].y);
    if (!mono && Scr[screen].npixels > 2) {
	XSetForeground(dsp, Scr[screen].gc, Scr[screen].pixels[qp->pix]);
	if (++qp->pix >= Scr[screen].npixels)
	    qp->pix = 0;
    } else
	XSetForeground(dsp, Scr[screen].gc, sswhite[screen].pixel);

    XDrawLine(dsp, win, Scr[screen].gc, qp->x1, qp->y1, qp->x2, qp->y2);

    qp->lineq[qp->last].x = qp->x1;
    qp->lineq[qp->last].y = qp->y1;
    qp->last++;
    if (qp->last >= qp->nlines)
	qp->last = 0;

    qp->lineq[qp->last].x = qp->x2;
    qp->lineq[qp->last].y = qp->y2;
    qp->last++;
    if (qp->last >= qp->nlines)
	qp->last = 0;
}
