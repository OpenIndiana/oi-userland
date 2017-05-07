/*-
 * multivis.c - Mechanism for GetImage across Multiple Visuals
 *
 * Original author:
 *		       Milind M. Pansare
 *		       Window Systems Group
 *		       Sun Microsystems, Inc.
 *
 * Revision History:
 * 11-15-90 Written
 */
 
/* Copyright (c) 1990, 2011, Oracle and/or its affiliates. All rights reserved.
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

#include <stdlib.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#ifdef SHAPE
#include <X11/extensions/shape.h>
#endif /* SHAPE */
#include "multivis.h"

static MVColmap *mvFindColormap(Colormap cmap);
static XVisualInfo *mvMatchVisual(VisualID vid);
static void mvGetColormap(MVWinVisInfo *pWI);
static void mvCalculateComposite(MVWinVisInfo *pWI);
static unsigned long mvCompositePixel(unsigned long i, MVColmap *pCmp);

static Display *mvDpy; 			/* Display */
static int mvScreen;			/* Screen */
static XVisualInfo *mvVlist;		/* List of Visuals */
static int mvNumVis;			/* Number of visuals in list */
#ifdef SHAPE
static Bool mvShape;                    /* Shape extension ? */
#endif /* SHAPE */

static MVWinVisInfoList winList;	/* Here we'll grow a list of windows
					   Sorted back to front */

static MVColmap *colMaps;		/* list of colormaps we encounter */
static MVPel *mvImg;			/* mvImg is what we compose the image
					   into */

static int request_width, 
	   request_height;		/* size of requested rectangle */
static int request_x, request_y;	/* The top left of requested
					   rectangle in Root Space */

#ifdef UPDATE_HACK
static void *mvCallbackData;
static mvCallbackFunc mvCallbackFunction;
#endif /* UPDATE_HACK */


/*
 * Initialise the mvLib routines ...
*/

void
#ifdef UPDATE_HACK
mvInit(
    Display *dpy,
    int screen,
    XVisualInfo *vlist,
    int num_vis,
    void *callbackData,
    mvCallbackFunc callbackFunction)
#else
mvInit(
    Display *dpy,
    int screen,
    XVisualInfo *vlist,
    int num_vis)
#endif /* UPDATE_HACK */
{
#ifdef SHAPE
  int tmp;
#endif /* SHAPE */
  /* Initialise screen info */
  mvDpy = dpy;
  mvScreen = screen;
  mvVlist = vlist;
  mvNumVis = num_vis;
#ifdef SHAPE
  mvShape = XShapeQueryExtension(dpy, &tmp, &tmp);
#endif /* SHAPE */

#ifdef UPDATE_HACK
  mvCallbackData = callbackData;
  mvCallbackFunction = callbackFunction;
#endif /* UPDATE_HACK */
}

/*
 * Create an Img.. Cleared to zeros.
 * returns 0 if failure, non-zero for success.
 * Note that it is the reponsibility of the caller
 * to verify that any resulting XGetImage will
 * be within the bounds of the screen.
 * i.e, x, y, wd, ht must be such that the rectangle
 * is fully within the bounds of the screen.
*/
int
mvCreatImg(int wd, int ht, int x, int y)
{
  /* Create mvImg */
  request_width = wd;
  request_height = ht;
  request_x = x;
  request_y = y;
  if ((mvImg = (MVPel *) calloc(sizeof(MVPel), request_width * request_height))
      != NULL) {
    return 1;
  }
  return 0;
}

/* 
 * Reset the mvLib routines
*/
void
mvReset(void)
{
#ifdef SHAPE
  int i;
#endif /* SHAPE */
  /* Free mvImg */
  if (mvImg)
    free(mvImg);
  /* Clean winList */
  if (winList.wins) {
#ifdef SHAPE
    i = winList.used;
    while (i--) {
	if (winList.wins[i].region)
	    XDestroyRegion(winList.wins[i].region);
    }
#endif /* SHAPE */
    free(winList.wins);
    winList.wins = NULL;
    winList.used = winList.allocated = 0;
  }
  /* Clean colmap list */
  while (colMaps) {
    MVColmap *pCmap;
    pCmap = colMaps;
    colMaps = pCmap->next;
    if (pCmap->Colors)
      free(pCmap->Colors);
    free(pCmap);
  }
}

/*
 * Recursively walk the window tree.
 * Find windows that intersect the requested region.
 * Create a list of such windows in global winList.
 * Assumes winList was cleared beforehand.
*/
void
mvWalkTree(
    Window win,		/* This window */
    int px, int py,	/* parent's origin in root space */
    int x, int y,	/* Top left of requested rectangle in root space */
    int wi, int hi, 	/* size of requested rectangle */
#ifdef SHAPE
    Bool ancestorShaped, /* ancestor was a Shaped window */
    Region ancestorRegion /* parent rel. effective Bounding region of ancestors */
#endif /* SHAPE */
    )
{
  XWindowAttributes xwa;
  int width, height, x1, y1;
  Window root, parent, *children;
  int  n;
  unsigned int nchild;
  MVWinVisInfo *pWinInfo;
#ifdef SHAPE
  Bool isShaped = False;
  Bool bdg, clp;
  int xb, yb, xc, yc;
  unsigned int wb, hb, wc, hc;
  int count, ordering;
  Region tmpancestorRegion, tmpreg;
  XRectangle *rects, *rect, tmprct;
#endif /* SHAPE */

  if (!XGetWindowAttributes(mvDpy, win, &xwa) 
      || xwa.map_state != IsViewable 
      || xwa.class == InputOnly) {
    return;
  }

  /* compute top-left of image in root space */
  x1 = max(x, xwa.x+px);
  y1 = max(y, xwa.y+py);
  width = min(x+wi, xwa.x+xwa.width+2*xwa.border_width+px)-x1;
  height=min(y+hi, xwa.y+xwa.height+2*xwa.border_width+py)-y1;

  if (width <=0 || height <= 0) {
    return;
  }

  /* We're interested ... */

  if (winList.used >= winList.allocated) { /* expand or create the array */
    winList.allocated = (winList.allocated?winList.allocated*MV_WIN_TUNE2:
				       MV_WIN_TUNE1);
    winList.wins = (MVWinVisInfo *)(winList.wins ?
	      realloc(winList.wins,winList.allocated*sizeof(MVWinVisInfo)):
	      malloc(winList.allocated*sizeof(MVWinVisInfo)));
  }

  pWinInfo = &(winList.wins[winList.used++]);
  pWinInfo->window = win;
  pWinInfo->depth = xwa.depth;
  pWinInfo->visinfo = mvMatchVisual(XVisualIDFromVisual(xwa.visual));
  pWinInfo->colmap = mvFindColormap(xwa.colormap);
  pWinInfo->x = x1-xwa.border_width-xwa.x-px; 
  pWinInfo->y = y1-xwa.border_width-xwa.y-py;
  pWinInfo->width = width;
  pWinInfo->height = height;
  pWinInfo->x1 = x1;
  pWinInfo->y1 = y1;
#ifdef SHAPE
  pWinInfo->region = NULL;
  /* Is it a Shaped Window ? Help ! */
  if ((XShapeQueryExtents(mvDpy, win, &bdg, &xb, &yb, &wb, &hb, 
      &clp, &xc, &yc, &wc, &hc)) && bdg) {  

    if ((wb == 0) || (hb == 0) || (wb > 2000) || (hb > 2000)) {
	/* Empty shape, ignore it */
	winList.used--;
	return;
    }	

    isShaped = True;
    pWinInfo->region = XCreateRegion();
    rect = rects = 
      XShapeGetRectangles(mvDpy, win, ShapeBounding, &count, &ordering);
    
    while (count--) {
	XUnionRectWithRegion(rect++, pWinInfo->region, pWinInfo->region);
    }
    if (rects != NULL) {
      XFree((caddr_t)rects);
    }

    tmpreg = XCreateRegion();
    tmprct.x = pWinInfo->x; tmprct.y = pWinInfo->y;
    tmprct.width = pWinInfo->width; tmprct.height = pWinInfo->height;
    XUnionRectWithRegion(&tmprct, tmpreg, tmpreg);
    XIntersectRegion(pWinInfo->region, tmpreg, pWinInfo->region);
    XDestroyRegion(tmpreg);
  }
  if (ancestorShaped) { 
      /* make a local copy */
      tmpancestorRegion = XCreateRegion();
      XUnionRegion(tmpancestorRegion, ancestorRegion, tmpancestorRegion);
      /* Translate from relative parent's origin to this window's origin */
      XOffsetRegion(tmpancestorRegion, -(xwa.x + xwa.border_width),
				       -(xwa.y + xwa.border_width));
      if (isShaped) { /* Compute effective bdg shape */
	XIntersectRegion(tmpancestorRegion, pWinInfo->region, pWinInfo->region);
      }
      else {
        pWinInfo->region = XCreateRegion();
        XUnionRegion(tmpancestorRegion, pWinInfo->region, pWinInfo->region);
        tmpreg = XCreateRegion();
        tmprct.x = pWinInfo->x; tmprct.y = pWinInfo->y;
        tmprct.width = pWinInfo->width; tmprct.height = pWinInfo->height;
        XUnionRectWithRegion(&tmprct, tmpreg, tmpreg);
        XIntersectRegion(pWinInfo->region, tmpreg, pWinInfo->region);
        XDestroyRegion(tmpreg);
      }
      XDestroyRegion(tmpancestorRegion);
  }
#endif /* SHAPE */

  /* Find children, back to front */
  if (XQueryTree(mvDpy, win, &root, &parent, &children, &nchild)) {

#ifdef SHAPE
    tmpreg = pWinInfo->region;
#endif /* SHAPE */

    for (n=0; n<nchild; n++) {
#ifdef SHAPE
      mvWalkTree(children[n], px+xwa.x+xwa.border_width,
			    py+xwa.y+xwa.border_width, 
			    x1, y1, width, height, (ancestorShaped || isShaped),  
			    tmpreg);
#else /* !SHAPE */
      mvWalkTree(children[n], px+xwa.x+xwa.border_width,
			    py+xwa.y+xwa.border_width, 
			    x1, y1, width, height);
#endif /* SHAPE */
    }
    /* free children */
    if (nchild > 0)
      XFree((caddr_t)children);
  }
  return;
}

/*
 * CHANGE
 * Returns 0 if no problems,
 * Returns 1 if depths differ
 * returns 2 if colormap or visinfo differ
 * NOTE that this chenge & the previous change are reprehensible hacks,
 * to let xmag work with pageview, and xcolor respectively.
 * USED TO BE...
	 * CHANGE
	 * Returns 0 if no problems, 
	 * Returns 1 if visinfo or depth differ
	 * returns 2 if colormap only differ
	 * USED TO BE...
	 * Returns non-zero if the winList created by mvWalkTree
	 * might potentially have windows of different Visuals
	 * else returns 0
*/
int 
mvIsMultiVis(void)
{
  int retcode = 0;
  int i = winList.used;

  while (i--) {
    if(winList.wins[i].depth != winList.wins[0].depth)
	 return 1;
    if (winList.wins[i].visinfo != winList.wins[0].visinfo)
      retcode = 2;
    if (winList.wins[i].colmap != winList.wins[0].colmap)
      retcode = 2;
  }
  return retcode;
}

/*
 * Traverse the window list front to back. Get the entire Image
 * from each window, but only Label a pixel in the Img once.
 * That is, once a pixel has been Labeled, any more fetches
 * from the same pixel position are discarded. Once all pixels
 * positions have been fetched, we're done. This will eliminate
 * windows that have nothing to contibute to the requested region,
 * but will nevertheless have the problem of the painters
 * algorithm, where more pixels were fetched from a
 * window than were essential.
 * Assumes that winList has been filled beforehand, and Img was cleared.
*/

void
mvDoWindowsFrontToBack(void)
{
  int i;
  MVWinVisInfo *pWI;
  XImage *xim;
  int xi, yi;
  int nPixelsUnLabeled = request_width*request_height;

   for (i=winList.used-1; ((nPixelsUnLabeled > 0) && i >= 0); i--) {
    pWI = &(winList.wins[i]);
    if (!(xim = XGetImage(mvDpy, pWI->window, pWI->x, pWI->y, pWI->width,
			 pWI->height, (~0), ZPixmap))) {
      return;
    }
    mvGetColormap(pWI);
    /* For each pixel in the returned Image */
    for (yi = 0; yi < pWI->height; yi++) {
#ifdef UPDATE_HACK
      if ((yi % 128) == 0) {
	  (*mvCallbackFunction)(mvCallbackData);
      }
#endif /* UPDATE_HACK */
      for (xi = 0; xi < pWI->width; xi++) {
	MVPel *pPel = mvFindPel(xi+pWI->x1-request_x, yi+pWI->y1-request_y);
	/* If the pixel hasn't been labelled before */
	if (!pPel->colmap) { /* pPel->colmap serves as a 'Label' */
	  /* label the pixel in the map with this window's cmap */
	  /* 
	   * If Pixel value can be discarded, this is where
	   * you get the RGB value instead. 
	   * Call a routine like mvFindColorInColormap() with the pixel
	   * value, and Colormap as parameters.
	   * The 'Label', instead of pPel->colmap could be a scratch bit ?
	   * But if its a full 32 bit pixel, and there are no
	   * free bits, you need to hang in extra bits somewhere.
	   * Maybe a bitmask associated with Img ?
	  */
#ifdef SHAPE
	  if (!(pWI->region) || 
	  (pWI->region && (XPointInRegion(pWI->region, xi+pWI->x, yi+pWI->y))
#ifdef XNEWS
	   && (XPointInRegion(pWI->region, xi+pWI->x+1, yi+pWI->y))
	   && (XPointInRegion(pWI->region, xi+pWI->x, yi+pWI->y+1))
	   && (XPointInRegion(pWI->region, xi+pWI->x+1, yi+pWI->y+1))
#endif /* XNEWS */
	   )
	  ) {
#endif /* SHAPE */
	    pPel->colmap = pWI->colmap;
	    /* and pixel value */
	    pPel->pixel = XGetPixel(xim, xi, yi);
	    nPixelsUnLabeled--;
#ifdef SHAPE
	  }
#endif /* SHAPE */
	}
      }
    }
    /* free image */
    XDestroyImage(xim);
  }
}

/*
 * Get all the colors from this window's colormap.
 * That's slightly complicated when we hit
 * a true color or direct color visual.
 * Assumes that a global list of colmaps is present, and
 * that the Colors field was NULLed beforehand.
*/

static void
mvGetColormap(MVWinVisInfo *pWI)
{
  if (!pWI->colmap->Colors) { /* This is the first time we're visiting */
    MVColmap *pCmp = pWI->colmap;
    XVisualInfo *pVis = pWI->visinfo;
    XColor *pCol;
    int size = pVis->colormap_size;

    /* Allocate enough memory */
    pCmp->Colors = pCol = (XColor *)calloc((sizeof(XColor)), size);
    if (pVis->class == TrueColor || pVis->class == DirectColor) {
      unsigned long i;
      /* We have to create a composite pixel value */
      mvCalculateComposite(pWI);
      for (i = 0; i < (unsigned long)(size);i++, pCol++) {
	pCol->pixel = mvCompositePixel(i, pCmp);
      }
    }
    else {
      unsigned long i;
      /* Fill in the pixel values by hand */
      for (i = 0; i < (unsigned long)(size);) {
	pCol++->pixel = i++;
      }
    }
    XQueryColors(mvDpy, pCmp->cmap, pCmp->Colors, size);
  }
}

/* 
 * Given a VisualID, return a pointer to the VisualInfo structure.
 * Assumes that a global mvVlist for this screen has already
 * been created. Uses globals mvNumVis, and mvVlist.
 * Returns NULL if the vid is not matched.
*/
static XVisualInfo *
mvMatchVisual(VisualID vid)
{
  XVisualInfo *pVis = mvVlist;
  while (pVis < (mvVlist+mvNumVis)) {
    if (vid == pVis->visualid) {
      return pVis;
    }
    pVis++;
  }
  return NULL;
}

/*
 * Calculate a composite pixel value that indexes into all
 * three primaries . Assumes Composite Calcs have been performed 
 * already on the colmap.
*/
static unsigned long
mvCompositePixel(unsigned long i, MVColmap *pCmp)
{
  unsigned long val = 0;

  if (i < pCmp->rmax) val |= i << pCmp->rshft;
  if (i < pCmp->gmax) val |= i << pCmp->gshft;
  if (i < pCmp->bmax) val |= i << pCmp->bshft;
  return val;
}

/*
 * Calculate the offsets used to composite a pixel value for
 * the TrueColor & DirectColor cases
 * Assumes its called only on a True or DirectColor visual.
*/
static void
mvCalculateComposite(MVWinVisInfo *pWI)
{
  MVColmap *pCmp = pWI->colmap;
  XVisualInfo *pVis = pWI->visinfo;
  /* Check if this has been done before */
  if (!pCmp->doComposite) {
    pCmp->doComposite = True;
    /* These are the sizes of each primary map ... */
    pCmp->red_mask = pVis->red_mask;
    pCmp->green_mask = pVis->green_mask;
    pCmp->blue_mask = pVis->blue_mask;
    pCmp->rmax = 1 << mvOnes(pVis->red_mask);
    pCmp->gmax = 1 << mvOnes(pVis->green_mask);
    pCmp->bmax = 1 << mvOnes(pVis->blue_mask);
    pCmp->rshft = mvShifts(pVis->red_mask);
    pCmp->gshft = mvShifts(pVis->green_mask);
    pCmp->bshft = mvShifts(pVis->blue_mask);
    pCmp->rgbshft = (16 - pVis->bits_per_rgb);
  }
}

/*
 * Calculate number of 1 bits in mask
 * Classic hack not written by this author.
*/
int
mvOnes(unsigned long mask)
{
  unsigned long y;

  y = (mask >> 1) &033333333333;
  y = mask - y - ((y >> 1) & 033333333333);
  return (((y + (y >> 3)) & 030707070707) % 077);
}

/*
 * Calculate the number of shifts till we hit the mask
*/
int 
mvShifts(unsigned long mask)
{
  int y = 0;

  if (mask) {
    while(!(mask&0x1)) {
      mask = mask >> 1;
      y++;
    }
  }
  return y;
}

/*
 * find & creat a colmap struct for this cmap 
 * Assumes that colMaps was cleared before the first time
 * it is called.
*/
static MVColmap *
mvFindColormap(Colormap cmap)
{
  MVColmap *pCmap;
  /* if we've seen this cmap before, return its struct colmap */
  for (pCmap = colMaps; pCmap; pCmap = pCmap->next) {
    if (cmap == pCmap->cmap)
      return pCmap;
  }
  /* First time for this cmap, creat & link */
  pCmap = (MVColmap *) calloc(sizeof(MVColmap), 1);
  pCmap->next = colMaps;
  pCmap->cmap = cmap;
  colMaps = pCmap;
  return pCmap;
}

/*
 * Use pixel value at x, y as an index into 
 * the colmap's list of Colors.
 * If the pixel value were not important, this would be called
 * in mvDoWindowsFrontToBack(), with the pixel value
 * and colmap as parameters, to get RGB values directly.
*/
XColor *
mvFindColorInColormap(int x, int y)
{
  MVPel *pPel = mvFindPel(x, y);
  MVColmap *pCmap = pPel->colmap;
  static XColor scratch;

  if (pCmap->doComposite) { /* This is either True or DirectColor */
    /* Treat the pixel value as 3 separate indices, composite
       the color into scratch, return a pointer to scratch */
    unsigned long pix = pPel->pixel;
    unsigned long index = (pix & pCmap->red_mask) >> pCmap->rshft; 
    scratch.red=pCmap->Colors[(pix & pCmap->red_mask)>>pCmap->rshft].red;
    scratch.green=pCmap->Colors[(pix & pCmap->green_mask)>>pCmap->gshft].green;
    scratch.blue=pCmap->Colors[(pix & pCmap->blue_mask)>>pCmap->bshft].blue;
    scratch.pixel=pix;
    return(&scratch);
  }
  else { /* This is simple */
    return &(pCmap->Colors[pPel->pixel]);
  }
}
