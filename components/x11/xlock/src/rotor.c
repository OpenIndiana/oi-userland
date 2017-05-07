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
 * rotor.c - A swirly rotor for xlock, the X Window System lockscreen.
 *
 * Copyright (c) 1991 by Patrick J. Naughton.
 *
 * See xlock.c for copying information.
 *
 * Revision History:
 * 11-Nov-90: put into xlock (by Steve Zellers, zellers@sun.com)
 * 16-Oct-90: Received from Tom Lawrence (tcl@cs.brown.edu: 'flight' simulator)
 */

/*
 * A 'batchcount' of 3 or 4 works best!
 */

#include <stdio.h>
#include <math.h>
#include "xlock.h"

#define SAVE 		100	/* this is a good constant to tweak */
#define REPS  		50

#define MAXANGLE	10000.0	/* irrectangular */
#define DEFAULTCOUNT	3

typedef unsigned char Boolean;

#define IDENT(X)	X
#ifdef __STDC__
#define CAT(X,Y)	X##Y
#else
#define CAT(X,Y)	IDENT(X)Y
#endif

struct elem {
    float       angle;
    float       radius;
    float       start_radius;
    float       end_radius;
    float       radius_drift_max;
    float       radius_drift_now;

    float       ratio;
    float       start_ratio;
    float       end_ratio;
    float       ratio_drift_max;
    float       ratio_drift_now;
};

typedef struct flightstruct {
    struct elem *elements;
    int         pix;
    int         lastx,
                lasty;
    int         num,
                rotor,
                prev;
    int         savex[SAVE],
                savey[SAVE];
    float       angle;
    int         centerx,
                centery;
    Boolean     firsttime;
    Boolean     smallscreen;	/* for iconified view */
    Boolean     forward;
    Boolean     unused;
}           flightstruct;


static flightstruct flights[MAXSCREENS];

void
initrotor(Window      win)
{
    flightstruct *fs = &flights[screen];
    XWindowAttributes xgwa;
    int         x;
    struct elem *pelem;
    Boolean     wassmall;

    XGetWindowAttributes(dsp, win, &xgwa);
    fs->centerx = xgwa.width / 2;
    fs->centery = xgwa.height / 2;

    /*
     * sometimes, you go into small view, only to see a really whizzy pattern
     * that you would like to look more closely at. Normally, clicking in the
     * icon reinitializes everything - but I don't, cuz I'm that kind of guy.
     * HENCE, the wassmall stuff you see here.
     */

    wassmall = fs->smallscreen;
    fs->smallscreen = (Boolean) (xgwa.width < 100);

    if (wassmall && !fs->smallscreen)
	fs->firsttime = True;
    else {
	if ((batchcount < 1) || (batchcount > 12))
	    batchcount = DEFAULTCOUNT;
	fs->num = batchcount;

	if (fs->elements == NULL) {
	    fs->elements = calloc(fs->num, sizeof(struct elem));
	    if (fs->elements == NULL)
		error("allocation failed, unable to motor our rotor\n");
	}
	memset(fs->savex, 0, sizeof(fs->savex));

	pelem = fs->elements;

	for (x = fs->num; --x >= 0; pelem++) {
	    pelem->radius_drift_max = 1.0;
	    pelem->radius_drift_now = 1.0;

	    pelem->end_radius = 100.0;

	    pelem->ratio_drift_max = 1.0;
	    pelem->ratio_drift_now = 1.0;
	    pelem->end_ratio = 10.0;
	}

	fs->rotor = 0;
	fs->prev = 1;
	fs->lastx = fs->centerx;
	fs->lasty = fs->centery;
	fs->angle = (random() % (long) MAXANGLE) / 3;
	fs->forward = fs->firsttime = True;
    }
    XSetForeground(dsp, Scr[screen].gc, ssblack[screen].pixel);
    XFillRectangle(dsp, win, Scr[screen].gc, 0, 0, xgwa.width, xgwa.height);
}

void
drawrotor(Window      win)
{
    register flightstruct *fs = &flights[screen];
    register struct elem *pelem;
    int         thisx,
                thisy;
    int         i,
                rp;
    int         x1,
                y1,
                x2,
                y2;


#define SCALE(W,N)	CAT(W,N)/=12; CAT(W,N)+=(CAT(fs->center,W)-2)
#define SCALEIFSMALL()    if (fs->smallscreen) { 	\
                              SCALE(x,1); SCALE(x,2);	\
			      SCALE(y,1); SCALE(y,2);	\
			  }

    for (rp = 0; rp < REPS; rp++) {
	thisx = fs->centerx;
	thisy = fs->centery;

	for (i = fs->num, pelem = fs->elements; --i >= 0; pelem++) {
	    if (pelem->radius_drift_max <= pelem->radius_drift_now) {
		pelem->start_radius = pelem->end_radius;
		pelem->end_radius =
		    (float) (random() % 40000) / 100.0 - 200.0;
		pelem->radius_drift_max =
		    (float) (random() % 100000) + 10000.0;
		pelem->radius_drift_now = 0.0;
	    }
	    if (pelem->ratio_drift_max <= pelem->ratio_drift_now) {
		pelem->start_ratio = pelem->end_ratio;
		pelem->end_ratio =
		    (float) (random() % 2000) / 100.0 - 10.0;
		pelem->ratio_drift_max =
		    (float) (random() % 100000) + 10000.0;
		pelem->ratio_drift_now = 0.0;
	    }
	    pelem->ratio = pelem->start_ratio +
		(pelem->end_ratio - pelem->start_ratio) /
		pelem->ratio_drift_max * pelem->ratio_drift_now;
	    pelem->angle = fs->angle * pelem->ratio;
	    pelem->radius = pelem->start_radius +
		(pelem->end_radius - pelem->start_radius) /
		pelem->radius_drift_max * pelem->radius_drift_now;

	    thisx += (int) (cos(pelem->angle) * pelem->radius);
	    thisy += (int) (sin(pelem->angle) * pelem->radius);

	    pelem->ratio_drift_now += 1.0;
	    pelem->radius_drift_now += 1.0;
	}
	if (fs->firsttime)
	    fs->firsttime = False;
	else {
	    XSetForeground(dsp, Scr[screen].gc, ssblack[screen].pixel);

	    x1 = (int) fs->savex[fs->rotor];
	    y1 = (int) fs->savey[fs->rotor];
	    x2 = (int) fs->savex[fs->prev];
	    y2 = (int) fs->savey[fs->prev];

	    SCALEIFSMALL();

	    XDrawLine(dsp, win, Scr[screen].gc, x1, y1, x2, y2);

	    if (!mono && Scr[screen].npixels > 2) {
		XSetForeground(dsp, Scr[screen].gc,
			       Scr[screen].pixels[fs->pix]);
		if (++fs->pix >= Scr[screen].npixels)
		    fs->pix = 0;
	    } else
		XSetForeground(dsp, Scr[screen].gc, sswhite[screen].pixel);

	    x1 = fs->lastx;
	    y1 = fs->lasty;
	    x2 = thisx;
	    y2 = thisy;

	    SCALEIFSMALL();

	    XDrawLine(dsp, win, Scr[screen].gc, x1, y1, x2, y2);
	}
	fs->savex[fs->rotor] = fs->lastx = thisx;
	fs->savey[fs->rotor] = fs->lasty = thisy;

	++fs->rotor;
	fs->rotor %= SAVE;
	++fs->prev;
	fs->prev %= SAVE;
	if (fs->forward) {
	    fs->angle += 0.01;
	    if (fs->angle >= MAXANGLE) {
		fs->angle = MAXANGLE;
		fs->forward = False;
	    }
	} else {
	    fs->angle -= 0.1;
	    if (fs->angle <= 0) {
		fs->angle = 0.0;
		fs->forward = True;
	    }
	}
    }
}
