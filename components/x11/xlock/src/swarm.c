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
 * swarm.c - swarm of bees for xlock, the X Window System lockscreen.
 *
 * Copyright (c) 1991 by Patrick J. Naughton.
 *
 * Revision History:
 * 31-Aug-90: Adapted from xswarm by Jeff Butterworth. (butterwo@ncsc.org)
 */

#include "xlock.h"

#define TIMES	4		/* number of time positions recorded */
#define BEEACC	3		/* acceleration of bees */
#define WASPACC 5		/* maximum acceleration of wasp */
#define BEEVEL	11		/* maximum bee velocity */
#define WASPVEL 12		/* maximum wasp velocity */
#define BORDER	50		/* wasp won't go closer than this to the edge */

/* Macros */
#define X(t,b)	(sp->x[(t)*sp->beecount+(b)])
#define Y(t,b)	(sp->y[(t)*sp->beecount+(b)])
#define RAND(v)	((random()%(v))-((v)/2))	/* random number around 0 */

typedef struct {
    int         pix;
    long        startTime;
    int         width;
    int         height;
    uint_t      beecount;	/* number of bees */
    XSegment   *segs;		/* bee lines */
    XSegment   *old_segs;	/* old bee lines */
    short      *x;
    short      *y;		/* bee positions x[time][bee#] */
    short      *xv;
    short      *yv;		/* bee velocities xv[bee#] */
    short       wx[3];
    short       wy[3];
    short       wxv;
    short       wyv;
}           swarmstruct;

static swarmstruct swarms[MAXSCREENS];

void
initswarm(Window      win)
{
    XWindowAttributes xgwa;
    swarmstruct *sp = &swarms[screen];
    uint_t       b;

    sp->startTime = seconds();
    if ((batchcount < 1) || (batchcount > 1024))
	batchcount = 100;
    sp->beecount = (uint_t) batchcount;

    XGetWindowAttributes(dsp, win, &xgwa);
    sp->width = xgwa.width;
    sp->height = xgwa.height;

    /* Clear the background. */
    XSetForeground(dsp, Scr[screen].gc, ssblack[screen].pixel);
    XFillRectangle(dsp, win, Scr[screen].gc, 0, 0, sp->width, sp->height);

    /* Allocate memory. */

    if (!sp->segs) {
	sp->segs = malloc(sizeof(XSegment) * sp->beecount);
	sp->old_segs = malloc(sizeof(XSegment) * sp->beecount);
	sp->x = malloc(sizeof(short) * sp->beecount * TIMES);
	sp->y = malloc(sizeof(short) * sp->beecount * TIMES);
	sp->xv = malloc(sizeof(short) * sp->beecount);
	sp->yv = malloc(sizeof(short) * sp->beecount);

	if ((sp->segs == NULL) || (sp->old_segs == NULL) ||
	    (sp->x == NULL) || (sp->y == NULL) ||
	    (sp->xv  == NULL) || (sp->yv == NULL)) {
	    error("allocation failed, colony collapsed, no bees left in the swarm\n");
	}
    }
    /* Initialize point positions, velocities, etc. */

    /* wasp */
    sp->wx[0] = (short) (BORDER + random() % (sp->width - 2 * BORDER));
    sp->wy[0] = (short) (BORDER + random() % (sp->height - 2 * BORDER));
    sp->wx[1] = sp->wx[0];
    sp->wy[1] = sp->wy[0];
    sp->wxv = 0;
    sp->wyv = 0;

    /* bees */
    for (b = 0; b < sp->beecount; b++) {
	X(0, b) = (short) (random() % sp->width);
	X(1, b) = X(0, b);
	Y(0, b) = (short) (random() % sp->height);
	Y(1, b) = Y(0, b);
	sp->xv[b] = (short) RAND(7);
	sp->yv[b] = (short) RAND(7);
    }
}



void
drawswarm(Window      win)
{
    swarmstruct *sp = &swarms[screen];
    uint_t       b;

    /* <=- Wasp -=> */
    /* Age the arrays. */
    sp->wx[2] = sp->wx[1];
    sp->wx[1] = sp->wx[0];
    sp->wy[2] = sp->wy[1];
    sp->wy[1] = sp->wy[0];
    /* Accelerate */
    sp->wxv += (short) RAND(WASPACC);
    sp->wyv += (short) RAND(WASPACC);

    /* Speed Limit Checks */
    if (sp->wxv > WASPVEL)
	sp->wxv = WASPVEL;
    if (sp->wxv < -WASPVEL)
	sp->wxv = -WASPVEL;
    if (sp->wyv > WASPVEL)
	sp->wyv = WASPVEL;
    if (sp->wyv < -WASPVEL)
	sp->wyv = -WASPVEL;

    /* Move */
    sp->wx[0] = (short) (sp->wx[1] + sp->wxv);
    sp->wy[0] = (short) (sp->wy[1] + sp->wyv);

    /* Bounce Checks */
    if ((sp->wx[0] < BORDER) || (sp->wx[0] > sp->width - BORDER - 1)) {
	sp->wxv = -sp->wxv;
	sp->wx[0] += sp->wxv;
    }
    if ((sp->wy[0] < BORDER) || (sp->wy[0] > sp->height - BORDER - 1)) {
	sp->wyv = -sp->wyv;
	sp->wy[0] += sp->wyv;
    }
    /* Don't let things settle down. */
    sp->xv[random() % sp->beecount] += (short) RAND(3);
    sp->yv[random() % sp->beecount] += (short) RAND(3);

    /* <=- Bees -=> */
    for (b = 0; b < sp->beecount; b++) {
	int         distance,
	            dx,
	            dy;
	/* Age the arrays. */
	X(2, b) = X(1, b);
	X(1, b) = X(0, b);
	Y(2, b) = Y(1, b);
	Y(1, b) = Y(0, b);

	/* Accelerate */
	dx = sp->wx[1] - X(1, b);
	dy = sp->wy[1] - Y(1, b);
	distance = abs(dx) + abs(dy);	/* approximation */
	if (distance == 0)
	    distance = 1;
	sp->xv[b] += (dx * BEEACC) / distance;
	sp->yv[b] += (dy * BEEACC) / distance;

	/* Speed Limit Checks */
	if (sp->xv[b] > BEEVEL)
	    sp->xv[b] = BEEVEL;
	if (sp->xv[b] < -BEEVEL)
	    sp->xv[b] = -BEEVEL;
	if (sp->yv[b] > BEEVEL)
	    sp->yv[b] = BEEVEL;
	if (sp->yv[b] < -BEEVEL)
	    sp->yv[b] = -BEEVEL;

	/* Move */
	X(0, b) = X(1, b) + sp->xv[b];
	Y(0, b) = Y(1, b) + sp->yv[b];

	/* Fill the segment lists. */
	sp->segs[b].x1 = X(0, b);
	sp->segs[b].y1 = Y(0, b);
	sp->segs[b].x2 = X(1, b);
	sp->segs[b].y2 = Y(1, b);
	sp->old_segs[b].x1 = X(1, b);
	sp->old_segs[b].y1 = Y(1, b);
	sp->old_segs[b].x2 = X(2, b);
	sp->old_segs[b].y2 = Y(2, b);
    }

    XSetForeground(dsp, Scr[screen].gc, ssblack[screen].pixel);
    XDrawLine(dsp, win, Scr[screen].gc,
	      sp->wx[1], sp->wy[1], sp->wx[2], sp->wy[2]);
    XDrawSegments(dsp, win, Scr[screen].gc, sp->old_segs, (int) sp->beecount);

    XSetForeground(dsp, Scr[screen].gc, sswhite[screen].pixel);
    XDrawLine(dsp, win, Scr[screen].gc,
	      sp->wx[0], sp->wy[0], sp->wx[1], sp->wy[1]);
    if (!mono && Scr[screen].npixels > 2) {
	XSetForeground(dsp, Scr[screen].gc, Scr[screen].pixels[sp->pix]);
	if (++sp->pix >= Scr[screen].npixels)
	    sp->pix = 0;
    }
    XDrawSegments(dsp, win, Scr[screen].gc, sp->segs, (int) sp->beecount);
}
