#ifndef _MULTIVIS_H
#define _MULTIVIS_H
/*-
 * multivis.h - Header file for Mechanism for GetImage across Multiple Visuals
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
 * Original author:
 *		       Milind M. Pansare
 *		       Window Systems Group
 *		       Sun Microsystems, Inc.
 *
 * Revision History:
 * 11-15-90 Written
 */

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <stdio.h>
/*
 * Data Structures used ...
*/

typedef struct _colmap {		/* Colormap Information */
    Colormap cmap;			/* X Colormap ID */
    XColor *Colors;			/* Actual list of RGB values */
    struct _colmap *next;			/* link in chain */
    int doComposite;			/* True for Direct & TrueColor */
    unsigned long red_mask, 		/* All these valid only for */
                  green_mask, 		/* Direct & TrueColor */
		  blue_mask;
    unsigned long rmax, 		/* Max indices into each primary */
		  gmax, 
		  bmax;	
    int rshft, 				/* Quick calcs for later */
	gshft, 
	bshft, 
	rgbshft;
} MVColmap;

typedef struct _winVisInfo {		/* A window & it's VisualInfo */
    Window window;			
    int depth;
    XVisualInfo *visinfo;
    MVColmap *colmap;			/* Colormap information */
    int x, y, width, height;  		/* GetImage, in window space */
    int x1, y1;				/* Top left of image in root space */
#ifdef SHAPE
    Region region;                      /* Computed effective bounding region */
#endif /* SHAPE */
} MVWinVisInfo;

typedef struct _winVisInfoList {	/* An Array of winVisInfo */
    unsigned long allocated, used;
    MVWinVisInfo *wins;
} MVWinVisInfoList; 

typedef struct _pel {			/* One for each pixel position */
    MVColmap *colmap;			/* cmap used for this position */
    unsigned long pixel;		/* pixel value */
} MVPel;

/*
 * CAUTION: There will be one _pel for each pixel position in the
 * requested dump area. This could potentially explode the data space.
 * There are 2 remedies for this.
 * 1. Dump small areas at a time
 * 2. Change this data structure to contain only the final RGB value,
 *    if the pixel value is not of consequence to the application.
 * Pixel Examination type of clients (eg. XMag) require the
 * pixel value, and operate on a relatively small dump area, so this
 * is not a problem.
*/


/*
 * Defines & macros ...
*/

/* Return MVPel * for this pixel position */
#define mvFindPel(x,y) ((mvImg+((y)*request_width))+(x))
#define max(a,b) ((a) > (b) ? (a) : (b))
#define min(a,b) ((a) < (b) ? (a) : (b))

/* This is the number of windows we typically expect on a desktop */
#define MV_WIN_TUNE1 20
/* If not, this is a likely multiplier ... */
#define MV_WIN_TUNE2 2

#ifdef UPDATE_HACK
typedef void (*mvCallbackFunc)(void *);
#endif /* UPDATE_HACK */

/*
 * extern declarations ... These are the mvLib's PUBLIC routines
 * There are no other PUBLIC interfaces to mvLib.
 * None of the Data Structures are PUBLIC.
*/
#if defined(__cplusplus) || defined(c_plusplus)
extern "C" {
#endif /* __cplusplus */

#if defined(__STDC__) || defined(__cplusplus) || defined(c_plusplus)
int mvShifts(unsigned long mask);
int mvOnes(unsigned long mask);

#ifdef UPDATE_HACK
void mvInit(Display *display, int screen, XVisualInfo *visuals, int numVisual,
	    void *callbackFunction, mvCallbackFunc cbFunction);
#else
void mvInit(Display *display, int screen, XVisualInfo *visuals, int numVisual);
#endif /* UPDATE_HACK */

void mvReset(void);
void mvWalkTree(Window window, int parentX, int parentY, 
		int requestX, int requestY, int requestWidth, int requestHeight
#ifdef SHAPE
		, Bool ancestorShaped, Region ancestorRegion
#endif /* SHAPE */
		);
int mvIsMultiVis(void);
int mvCreatImg(int width, int height, int x, int y);
void mvDoWindowsFrontToBack(void);
XColor *mvFindColorInColormap(int x, int y);
#else /* ! __STDC__ */
extern int mvShifts();
extern int mvOnes();
extern void mvInit();
extern void mvReset();
extern void mvWalkTree();
extern int mvIsMultiVis();
extern int mvCreatImg();
extern void mvDoWindowsFrontToBack();
extern XColor *mvFindColorInColormap();
#endif /* __STDC__ */

#if defined(__cplusplus) || defined(c_plusplus)
}
#endif /* __cplusplus */
#endif /* _MULTIVIS_H */
