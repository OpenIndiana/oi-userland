/*
 * xmag - simple magnifying glass application
 *
 * $XConsortium: xmag.c,v 1.29 89/12/10 17:23:58 rws Exp $
 *
 * Copyright 1988 Massachusetts Institute of Technology
 *
 * Permission to use, copy, modify, and distribute this software and its
 * documentation for any purpose and without fee is hereby granted, provided
 * that the above copyright notice appear in all copies and that both that
 * copyright notice and this permission notice appear in supporting
 * documentation, and that the name of M.I.T. not be used in advertising or
 * publicity pertaining to distribution of the software without specific,
 * written prior permission.  M.I.T. makes no representations about the
 * suitability of this software for any purpose.  It is provided "as is"
 * without express or implied warranty.
 *
 * Author:  Jim Fulton, MIT X Consortium
 *
 * Revision History:
 * 11-15-90  MultiVis changes made by: Milind M. Pansare
 *		                       milind@Eng.Sun.COM
 *
 */

/*
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
 */


#include <X11/Xos.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/cursorfont.h>
#include <X11/Xatom.h>
#include <stdio.h>
#include <stdlib.h>
#ifdef ALLPLANES
# include <X11/extensions/allplanes.h>
#endif
#include "multivis.h"

#ifdef __SUNPRO_C
/* prevent "Function has no return statement" error for shhh() */
#pragma does_not_return(exit)
#endif

#define DEFAULT_BORDER_SIZE 2
#define DEFAULT_CURSOR_SIZE 64
#define DEFAULT_MAGNIFICATION 5
#define DEFAULT_PIX_FONT "fixed"

int Argc;				/* copy of argc */
char **Argv;				/* copy of argv */

char *ProgramName;			/* name of program being executed */
Display *dpy = NULL;			/* X server being used */
int screen;				/* screen being used */
int pixmap_format;			/* XYPixmap or ZPixmap */
Colormap cmap;				/* colormap to use for drawing */
Visual   *visual;			/* This is to fix the bug for TrueColor */
int npixelvalues;			/* number of pixel values */
Window w, w1, mw;			/* enlargement window */
					/* w1 is TrueColor 24 bit */
					/* mw is the window that is finally
					   mapped , w or w1 */
Window root;				/* root window of screen */
GC fillGC = (GC) NULL;			/* for drawing enlargement */
GC fillGC1 = (GC) NULL;			/* for drawing enlargement */
GC fGC = (GC) NULL;			/* either fillGC or fillGC1 */
Bool do_grab = False;			/* grab server */
char *pix_font = NULL;			/* for displaying pixel value */

/* start MultiVisual Fix */
int num_vis;
XVisualInfo vinfo_template, *vlist, *def_vis;
int def_vis_is_ok = 0;			/* is def visual 24bit TrueColor */

int wd, ht;				/* request width & height */
XVisualInfo vis;			/* The TrueColor 24 bit one..
					   We'll use this for output */

XImage *FinalImage;			/* XImage corresponding to Img */

int multiVis=0;				/* if (multiVis), MultiVisual kludge */
int red_shift, blue_shift, green_shift, rgb_shift;
static XImage *CreateImageFromImg(void);
#ifdef ALLPLANES
int allplanes;                          /* Is the SUN_ASLLPLANES extension present ? */
#endif /* ALLPLANES */
Atom wm_delete_window;

/* end MultiVisual Fix */

static void magnify (char *window_geometry, char *source_geometry,
		     int magnification, char *border_color, int border_width,
		     char *back_color);
static void get_source (XSizeHints *shp);
static void repaint_image (XImage *image, XEvent *eventp, int magnification,
			   unsigned long back_pixel);

static Bool do_magnify (XSizeHints *shp, XSizeHints *whp, int magnification,
			unsigned long back_pixel);

static int IsMultiVis (int multivisFromMvLib);
static void MapPixWindow (Window wind, int bot);
static void DrawPixWindow (char *str);
static void UnmapPixWindow (void);
static int shhh(Display *dsp, XErrorEvent *err); /* quiet IO error handler */

static void
Exit (int status)
{
    if (dpy) {
	XCloseDisplay (dpy);
	dpy = NULL;
    }
    (void) exit (status);
}

static void
Usage (void)
{
    static const char *help_message[] = {
"where options include:",
"    -display displaystring        X server to contact",
"    -geometry geomstring          size and location of enlargement",
"    -source geomstring            size and location of area to be enlarged",
"    -mag magfactor                integral amount by which area is enlarged",
"    -bw pixels                    border width in pixels",
"    -bd color                     border color",
"    -bg colororpixelvalue         background color or %pixel number",
"    -fn fontname                  name of font for examining enlarged pixels",
"    -z                            grab server during dynamics and XGetImage",
"",
"Options may be abbreviated to the shortest unambiguous prefix.",
"",
NULL
    }, **cpp;

    fprintf (stderr, "usage:\n        %s [-options ...]\n\n", ProgramName);
    for (cpp = help_message; *cpp; cpp++) {
	fprintf (stderr, "%s\n", *cpp);
    }
    Exit (1);
}


int
main (int argc, char **argv)
{
    int i;				/* iterator variable */
    char *displayname = NULL;		/* name of X server to contact */
    char *source_geometry = NULL;	/* size of square tracking pointer */
    char *geometry = NULL;		/* size and location of enlarged */
    int magnification = 0;		/* enlarged image will be m by m */
    char *border_color = NULL;		/* border color name */
    char *back_color = NULL;		/* background of enlargement */
    int border_width = -1;		/* border width in pixels */

    ProgramName = argv[0];
    Argc = argc;
    Argv = argv;

    for (i = 1; i < argc; i++) {
	char *arg = argv[i];

	if (arg[0] == '-') {		/* process command line switches */
	    switch (arg[1]) {
	      case 'd':			/* -display displaystring */
		if (++i >= argc) Usage ();
		displayname = argv[i];
		continue;
	      case 'g':			/* -geometry geomstring */
		if (++i >= argc) Usage ();
		geometry = argv[i];
		continue;
	      case 's':			/* -source geomstring */
		if (++i >= argc) Usage ();
		source_geometry = argv[i];
		continue;
	      case 'm':			/* -mag magnification */
		if (++i >= argc) Usage ();
		magnification = atoi (argv[i]);
		continue;
	      case 'b':
		switch (arg[2]) {
		  case 'w':		/* -bw pixels */
		    if (++i >= argc) Usage ();
		    border_width = atoi (argv[i]);
		    continue;
		  case 'd':		/* -bd color */
		    if (++i >= argc) Usage ();
		    border_color = argv[i];
		    continue;
		  case 'g':		/* -bg colororpixel*/
		    if (++i >= argc) Usage ();
		    back_color = argv[i];
		    continue;
		}			/* end switch */
		Usage ();
		/* NOTREACHED */
	      case 'z':			/* -z */
		do_grab = True;
		continue;
	      case 'f':			/* -font fontname */
		if (++i >= argc) Usage ();
		pix_font = argv[i];
		continue;
	      default:
		Usage ();
		/* NOTREACHED */
	    }				/* end switch */
	} else {			/* any command line parameters */
	    Usage ();
	    /* NOTREACHED */
	}				/* end if else */
    }					/* end for */

    dpy = XOpenDisplay (displayname);
    if (!dpy) {
	fprintf (stderr, "%s:  unable to open display \"%s\".\n",
		 ProgramName, XDisplayName (displayname));
	Exit (1);
    }
     /*
      * set the fatal error handler to be an innocuous wimp that
      * exits quietly
     */
     /*
     XSetIOErrorHandler(shhh);
     */
#ifdef ALLPLANES
    {  
    int tmp;
    allplanes = XAllPlanesQueryExtension(dpy, &tmp, &tmp);
    }
#endif /* ALLPLANES */

     wm_delete_window = XInternAtom(dpy, "WM_DELETE_WINDOW", False);


    /*
     * get defaults (would be nice to use the resource manager instead)
     */

    if (!pix_font) pix_font = XGetDefault (dpy, ProgramName, "font");
    if (!pix_font) pix_font = XGetDefault (dpy, ProgramName, "Font");

    if (!geometry) geometry = XGetDefault (dpy, ProgramName, "geometry");
    if (!geometry) geometry = XGetDefault (dpy, ProgramName, "Geometry");

    if (!source_geometry)
      source_geometry = XGetDefault (dpy, ProgramName, "source");
    if (!source_geometry)
      source_geometry = XGetDefault (dpy, ProgramName, "Source");

    if (magnification < 1) {
	char *tmp = XGetDefault (dpy, ProgramName, "magnification");
	if (!tmp) tmp = XGetDefault (dpy, ProgramName, "Magnification");

	if (tmp) magnification = atoi (tmp);
    }

    if (border_width < 0) {
	char *tmp = XGetDefault (dpy, ProgramName, "borderWidth");
	if (!tmp) tmp = XGetDefault (dpy, ProgramName, "BorderWidth");

	border_width = tmp ? atoi (tmp) : DEFAULT_BORDER_SIZE;
    }

    if (!border_color) 
      border_color = XGetDefault (dpy, ProgramName, "borderColor");
    if (!border_color) 
      border_color = XGetDefault (dpy, ProgramName, "BorderColor");

    if (!back_color)
      back_color = XGetDefault (dpy, ProgramName, "background");
    if (!back_color) 
      back_color = XGetDefault (dpy, ProgramName, "Background");

    /*
     * set up globals
     */

    screen = DefaultScreen (dpy);
    cmap = DefaultColormap (dpy, screen);
    visual = DefaultVisual(dpy,screen) ;
    vinfo_template.visualid = XVisualIDFromVisual(visual) ;
    vinfo_template.screen = screen;
    if (((def_vis = XGetVisualInfo(dpy,VisualIDMask|VisualScreenMask,
       &vinfo_template,&num_vis))
       == NULL) || num_vis > 1)
      Exit(1);
    if ((def_vis->class == DirectColor) || (def_vis->class == TrueColor)) {
      npixelvalues  = (def_vis->red_mask | def_vis->green_mask  |
				         def_vis->blue_mask) + 1 ;
/* start MultiVisual fix */
      if (def_vis->class == TrueColor && def_vis->depth == 24) { 
	/* The default visual is TrueColor, 24 bit... */ 
	def_vis_is_ok = 1;
      }
/* end MultiVisual fix */
    }
    else
      npixelvalues = DisplayCells (dpy, screen);

/* start MultiVisual Fix */
    vinfo_template.screen = screen; /* Who cares about the other screens ? */
    if ((vlist=XGetVisualInfo(dpy,VisualScreenMask,&vinfo_template,&num_vis))
	== NULL)
      Exit(1); /* Duh ? */
    
/* end MultiVisual Fix */

    root = RootWindow (dpy, screen);
    pixmap_format = (DisplayPlanes (dpy, screen) > 1 ? ZPixmap : XYPixmap);

    /*
     * do the work
     */

    magnify (geometry, source_geometry, magnification,
	     border_color, border_width, back_color);

    Exit (0);
}


/*
 * Do the setup for the magnification.  Use the geometry, source_geometry,
 * and magnification to figure out how big of an area to magnify, and by
 * how much it should be enlarged according to the following relations:
 *
 *         magnification = window.geometry.width / source_geometry.width 
 *         magnification = window.geometry.height / source_geometry.height
 *
 * Thus, only two of the three values may be specified by the user.  The
 * following values are used to indicate that the default should be taken:
 *
 *        Variable         blank value    default value
 *
 *        magnification        0                5
 *        window             NULL       "320x320-0-0"
 *        source               NULL          "64x64"
 *
 * If a location is not specified for the source, a square centered on the 
 * pointer will be displayed that can be dragged around the screen.
 */

void 
magnify(
    char *window_geometry,		/* size and location of enlargement */
    char *source_geometry,		/* size and location of area */
    int magnification,			/* enlargement ratio */
    char *border_color,			/* name of color to use for border */
    int border_width,			/* width of border */
    char *back_color)			/* color name or pixel value */
{
    XTextProperty windowName, iconName;
    XWMHints wmHints;
    XClassHint classHints;
    XSizeHints source_hints, window_hints;  /* for sizes and locations */
    int source_geom_mask, window_geom_mask;  /* for XParseGeometry results */
    int params;				/* for which arguments present */
    unsigned long border_pixel;		/* pixel value for border */
    int tmp;				/* work variable */
    XColor cdef;			/* for parsing border color name */
    unsigned long valuemask;		/* for window attributes */
    XSetWindowAttributes attr;		/* for creating window */
    XGCValues gcv;			/* for creating GC */
    unsigned long back_pixel;		/* background of enlargement */

    bzero ((char *) &source_hints, sizeof source_hints);
    bzero ((char *) &window_hints, sizeof window_hints);
    source_geom_mask = window_geom_mask = 0;

#define SizeValues (WidthValue | HeightValue)
#define valNothing 0
#define valMagnification 1
#define valWindow 2
#define valSource 4
#define valAll 7

    params = valNothing;

    if (magnification > 0) params |= valMagnification;

    if (window_geometry) {
	window_geom_mask = XParseGeometry (window_geometry,
					   &window_hints.x, &window_hints.y, 
					   (unsigned int *)&window_hints.width,
					   (unsigned int *)&window_hints.height);
	tmp = (window_geom_mask & SizeValues);
	if (tmp) {
	    if (tmp == SizeValues)
	      params |= valWindow;
	    else
	      window_geom_mask &= ~SizeValues;
	}
    }

    if (source_geometry) {
	source_geom_mask = XParseGeometry (source_geometry,
					   &source_hints.x, &source_hints.y, 
					   (unsigned int *)&source_hints.width,
					   (unsigned int *)&source_hints.height);
	tmp = (source_geom_mask & SizeValues);
	if (tmp) {
	    if (tmp == SizeValues)
	      params |= valSource;
	    else
	      source_geom_mask &= ~SizeValues;
	}
    }

    /*
     * Check to make sure that user didn't give -geometry, -source, and -mag
     */

    if (params == valAll) {
	fprintf (stderr, "%s:  magnifier size over specified, ignoring -mag\n",
		 ProgramName);
	magnification = 0;
	params &= ~valMagnification;
    }

    /*
     * Verify the input and compute the appropriate sizes
     */

    if ((params & valMagnification) && magnification <= 0) {
	fprintf (stderr, "%s:  bad magnification %d.\n",
		 ProgramName, magnification);
	Exit (1);
    }
    if ((params & valWindow) && (window_hints.width <= 0 ||
				 window_hints.height <= 0)) {
	fprintf (stderr, "%s:  bad window size %dx%d.\n",
		 ProgramName, window_hints.width, window_hints.height);
	Exit (1);
    }
    if ((params & valSource) && (source_hints.width <= 0 ||
				 source_hints.height <= 0)) {
	fprintf (stderr, "%s:  bad source size %dx%d.\n",
		 ProgramName, source_hints.width, source_hints.height);
	Exit (1);
    }

    switch (params) {
      case valMagnification:
	source_hints.width = source_hints.height = DEFAULT_CURSOR_SIZE;
	goto mag_and_cur;

      case valWindow:
	magnification = DEFAULT_MAGNIFICATION;
	/* fall through */
      case valMagnification|valWindow:
	source_hints.width = window_hints.width / magnification;
	source_hints.height = window_hints.height / magnification;
	break;

      case valNothing:
	source_hints.width = source_hints.height = DEFAULT_CURSOR_SIZE;
	/* fall through */
      case valSource:
	magnification = DEFAULT_MAGNIFICATION;
	/* fall through */
      case valMagnification|valSource:
      mag_and_cur:
	window_hints.width = source_hints.width * magnification;
	window_hints.height = source_hints.height * magnification;
	break;

      case valWindow|valSource:
	magnification = window_hints.width / source_hints.width;
	tmp = window_hints.height / source_hints.height;
	if (tmp < magnification) magnification = tmp;
	break;
    }

    /*
     * At this point, both hints structures contain the appropriate width
     * and height fields.  Now we need to do the placement calculations.
     */

    if ((window_geom_mask & XValue) && (window_geom_mask & XNegative))
      window_hints.x = DisplayWidth (dpy, screen) + window_hints.x - 
	window_hints.width - border_width * 2;

    if ((window_geom_mask & YValue) && (window_geom_mask & YNegative))
      window_hints.y = DisplayHeight (dpy, screen) + window_hints.y -
	window_hints.height - border_width * 2;

    if ((source_geom_mask & XValue) && (source_geom_mask & XNegative))
      source_hints.x = DisplayWidth (dpy, screen) + source_hints.x - 
	source_hints.width;

    if ((source_geom_mask & YValue) && (source_geom_mask & YNegative))
      source_hints.y = DisplayHeight (dpy, screen) + source_hints.y -
	source_hints.height;

    /*
     * Set the flags entries so that we know what we have 
     */

    source_hints.flags = 0;
    source_hints.flags |= USSize;
    if ((source_geom_mask & XValue) && (source_geom_mask & YValue)) 
      source_hints.flags |= USPosition;

    window_hints.flags = 0;
    window_hints.flags |= USSize;
    if ((window_geom_mask & XValue) && (window_geom_mask & YValue)) 
      window_hints.flags |= USPosition;

    if (border_color && XParseColor (dpy, cmap, border_color, &cdef) &&
	XAllocColor (dpy, cmap, &cdef)) {
	border_pixel = cdef.pixel;
    } else {
	border_pixel = BlackPixel (dpy, screen);
    }

    window_hints.flags |= (PResizeInc | PBaseSize | PWinGravity);
    window_hints.width_inc = window_hints.height_inc = magnification;
    window_hints.base_width = window_hints.base_height = 0;
    switch (window_geom_mask & (XNegative | YNegative)) {
      case 0:
        window_hints.win_gravity = NorthWestGravity;
	break;
      case XNegative:
        window_hints.win_gravity = NorthEastGravity;
	break;
      case YNegative:
        window_hints.win_gravity = SouthWestGravity;
	break;
      default:
        window_hints.win_gravity = SouthEastGravity;
	break;
    }

    back_pixel = BlackPixel (dpy, screen);
    if (back_color) {
	XColor cdef;

	if (back_color[0] == '%') {	/* pixel specifier */
	    const char *fmt = "%lu";
	    register char *s = back_color + 1;

	    if (!*s) Usage ();
	    if (*s == '0') {
		s++;
		fmt = "%lo";
	    }
	    if (*s == 'x' || *s == 'X') {
		s++;
		fmt = "%lx";
	    }
	    if (sscanf (s, fmt, &back_pixel) != 1) Usage ();
	} else if (XParseColor (dpy, cmap, back_color, &cdef) &&
		   XAllocColor (dpy, cmap, &cdef)) {
	    back_pixel = cdef.pixel;
	}
    }

    /*
     * Make the enlargment window, but don't map it
     */

    attr.background_pixel = back_pixel;
    attr.border_pixel = border_pixel;
    attr.event_mask = (ExposureMask|ButtonPressMask|ButtonReleaseMask|KeyPressMask);
    attr.cursor = XCreateFontCursor (dpy, XC_top_left_arrow);
    valuemask = (CWBackPixel | CWBorderPixel | CWEventMask | CWCursor);

/* start MultiVisual Fix */
/*
 * If the worst has happened, and we have a mix of Visuals to
 * work from, then we insist on a TrueColor 24 bit Visual.
 *This makes life (a bit) simpler.
*/

  if ((num_vis) > 1 && (XMatchVisualInfo(dpy, screen, 24, TrueColor, &vis))) {
    wd = source_hints.width;
    ht = source_hints.height;
    FinalImage = XCreateImage(dpy, vis.visual, vis.depth, ZPixmap, 0, 
		       (char *)malloc(wd*ht*sizeof(unsigned long)),
		       wd, ht, 32, 0);
    if (def_vis_is_ok) {
      w1 = XCreateWindow(dpy, root, 
		       window_hints.x, window_hints.y, 
		       window_hints.width, window_hints.height,
		       border_width, 24, 
		       InputOutput, def_vis->visual, valuemask, &attr);
    }
    else {
      /* The default visual is not 24 bit True Color, 
	 Create a colormap for this visual */
	 Colormap c = XCreateColormap(dpy, root, vis.visual, AllocNone);
	 attr.colormap = c;
	 valuemask |= CWColormap;
         w1 = XCreateWindow(dpy, root, 
		       window_hints.x, window_hints.y, 
		       window_hints.width, window_hints.height,
		       border_width, 24, 
		       InputOutput, vis.visual, valuemask, &attr);
    }

    /* We assume that there's going to be a 24 bit TrueColor Visual
     to display the Image we create. Also, that each of R,G,B
     masks will be 8 bits. We now need to calculate the
     R, G, B offsets & order in the pixel.
     CAUTION: We also assume that the upper 8 bits of each of RGB in the 
     XColor are the significant 8 bits, and discard the lower
     8 bits */
    if (mvOnes(vis.red_mask) != 8 ||
      mvOnes(vis.blue_mask) != 8 ||
      mvOnes(vis.green_mask) != 8) {
      /* This visual is no good for us */
      if (w1) {
        XDestroyWindow(dpy, w1);
	w1 = NULL;
      }
    }
    else {
      red_shift = mvShifts(vis.red_mask);
      blue_shift = mvShifts(vis.blue_mask);
      green_shift = mvShifts(vis.green_mask);
      rgb_shift = 16-vis.bits_per_rgb;
    }
  }

/* At this moment, create both windows.. later decide which one to map */

/* end MultiVisual Fix */
    valuemask = (CWBackPixel | CWBorderPixel | CWEventMask | CWCursor);
    w = XCreateWindow (dpy, root, 
		       window_hints.x, window_hints.y, 
		       window_hints.width, window_hints.height,
		       border_width, DefaultDepth (dpy, screen),
		       CopyFromParent, CopyFromParent, valuemask, &attr);

    windowName.encoding = XA_STRING;
    windowName.format = 8;
    windowName.value = (unsigned char *) "Magnifying Glass";
    windowName.nitems = strlen ((char *)(windowName.value));
    iconName.encoding = XA_STRING;
    iconName.format = 8;
    iconName.value = (unsigned char *) "xmag";
    iconName.nitems = strlen ((char *)(iconName.value));
    wmHints.input = True;
    wmHints.flags = InputHint;
    classHints.res_name = NULL;
    classHints.res_class = "Magnifier";
    XSetWMProperties (dpy, w, &windowName, &iconName, Argv, Argc,
		      &window_hints, &wmHints, &classHints);
/* start MultiVisual Fix */
    if (w1) {
      XSetWMProperties (dpy, w1, &windowName, &iconName, Argv, Argc,
		      &window_hints, &wmHints, &classHints);
    }
/* end MultiVisual Fix */

    /*
     * Make up a dummy GC
     */
    gcv.function = GXcopy;
    gcv.plane_mask = AllPlanes;
    gcv.fill_style = FillSolid;
    /* repaint_image fills in foreground */

    fillGC = XCreateGC (dpy, w, (GCFunction | GCPlaneMask | GCFillStyle),
			&gcv);
/* start MultiVisual Fix */
    if (w1)
      fillGC1 = XCreateGC (dpy, w1, (GCFunction | GCPlaneMask | GCFillStyle),
			  &gcv);
/* end MultiVisual Fix */

    /*
     * Do the work.  If the user specified the location of the source,
     * then just that one spot, otherwise do some dynamics.
     */

    if (source_hints.flags & USPosition) {
	if (do_grab) {
	    XGrabServer (dpy);		/* ungrab is in do_magnify */
	    XSync (dpy, 0);
	}
	(void) do_magnify (&source_hints, &window_hints, magnification,
			   back_pixel);
    } else {
	do {
	    if (do_grab) {
		XGrabServer (dpy);	/* ungrab is in do_magnify */
	    }
	    XSync (dpy, 1);
	    get_source (&source_hints);
	} while (do_magnify (&source_hints, &window_hints, magnification,
			     back_pixel));
    }

    return;
}

#define NITERATIONS 6
#define NPOINTS (1 + (NITERATIONS * 2 * 4))  /* 1 move, 2 inverts, 4 sides */

static void
get_source (XSizeHints *shp)
{
    register int x, y;
    int width = shp->width, height = shp->height;
    int dw = DisplayWidth (dpy, screen), dh = DisplayHeight (dpy, screen);
    Window root_window, child_window;
    int root_x, root_y, win_x, win_y;
    int xoff = width / 2, yoff = height / 2;
    XPoint box[NPOINTS];
    int lastx, lasty;
    unsigned int mask;
    Bool done;
    static GC invGC = (GC) NULL;	/* for drawing source region outline */
    static Cursor invCursor;

    if (!invGC) {			/* make it the first time */
	XGCValues gcv;

	gcv.function = GXxor;
	gcv.subwindow_mode = IncludeInferiors;
	gcv.foreground = BlackPixel (dpy, screen);

	invGC = XCreateGC (dpy, root, (GCFunction | GCSubwindowMode |
				       GCForeground), &gcv);
	if (!invGC) {
	    fprintf (stderr, "%s:  unable to create invert GC.\n",
		     ProgramName);
	    Exit (1);
	}
	invCursor = XCreateFontCursor (dpy, XC_crosshair);
    }


    if (XGrabPointer (dpy, root, False, ButtonReleaseMask,
		      GrabModeAsync, GrabModeAsync, root,
		      invCursor, CurrentTime) != GrabSuccess) {
	fprintf (stderr, "%s:  unable to grab pointer\n", ProgramName);
	Exit (1);
    }

    /*
     * Do the loop looking for a button press, drawing the image each time;
     * since other clients may be running, make sure that the xor segments all
     * get drawn at the same time.  
     */

#define FAROFFSCREEN -9999

    for (done = False, lastx = lasty = FAROFFSCREEN; !done; ) {
	if (XPending (dpy) != 0) {
	    XEvent event;

	    XNextEvent (dpy, &event);

	    switch (event.type) {
	      case ButtonRelease:
		root_x = event.xbutton.x_root;
		root_y = event.xbutton.y_root;
		done = True;
		break;
	      default:
		fprintf (stderr, "%s:  warning unhandled event %u = 0x%x\n",
			 ProgramName, event.type, event.type);
		continue;
	    }				/* end switch */
	} else if (!XQueryPointer (dpy, root, &root_window, &child_window,
				   &root_x, &root_y, &win_x, &win_y, &mask)) {
	    fprintf (stderr, "%s:  unable to QueryPointer on root window.\n",
		     ProgramName);
	    Exit (1);
	}
	if (root_x != lastx || root_y != lasty) {
	    register int i;

	    /* clip to screen */

	    x = root_x - xoff;
	    y = root_y - yoff;
	    if (x < 0) x = 0;
	    if (y < 0) y = 0;
	    if (x + width > dw) x = dw - width;
	    if (y + height > dh) y = dh - height;

	    /* fill in the outline box */

	    for (i = 0; i < NPOINTS; i += 4) {
		box[i].x = x; box[i].y = y;	 /* u.l. */
		if (i == (NPOINTS - 1)) break;
		box[i+1].x = x + width; box[i+1].y = y;  /* u.r. */
		box[i+2].x = box[i+1].x; box[i+2].y = y + height;  /* l.r. */
		box[i+3].x = x; box[i+3].y = box[i+2].y;  /* l.l. */
	    }
	    lastx = root_x;
	    lasty = root_y;
	}

#ifdef ALLPLANES
	if (allplanes) {
	    XAllPlanesDrawLines (dpy, root, box, NPOINTS, CoordModeOrigin);
	}
	else {
#endif /* ALLPLANES */
	    XDrawLines (dpy, root, invGC, box, NPOINTS, CoordModeOrigin);
#ifdef ALLPLANES
	}
#endif /* ALLPLANES */
    }
    XUngrabPointer (dpy, CurrentTime);
    XFlush (dpy);

    shp->x = x;
    shp->y = y;

    return;
}

static Bool 
do_magnify (
    XSizeHints *shp,
    XSizeHints *whp,
    int magnification,
    unsigned long back_pixel)
{
    int x = shp->x, y = shp->y, width = shp->width, height = shp->height;
    int dw = DisplayWidth (dpy, screen), dh = DisplayHeight (dpy, screen);
    XImage *image;
    Bool done, domore;
    int i;

    /* 
     * Don't get bits that are off the edges of the screen
     */

    if (x < 0) x = 0;
    if (y < 0) y = 0;
    if (x + width > dw) x = dw - width;
    if (y + height > dh) y = dh - height;

/* start MultiVisual Fix */

    if (num_vis > 1) { /* Fire, Walk with me */
        /* Initialise the MultiVisual Routines */
        mvInit(dpy, screen, vlist, num_vis);
	/* Get a list of intersecting windows, with their visual details */
#ifdef SHAPE
	mvWalkTree(root, 0, 0, x, y, width, height, False, NULL);
#else /* ! SHAPE */
	mvWalkTree(root, 0, 0, x, y, width, height);
#endif /* SHAPE */
	/* Check if we have a multiVis on our hands */
	multiVis = IsMultiVis(mvIsMultiVis());
	if (multiVis) { 
	  /* Creat an Image where mvDoWindows.. will operate */
	  if (!mvCreatImg(wd,ht,x,y)) {
	    printf("mvCreatImg failed\n");
	    Exit(1);
	  }
	  mvDoWindowsFrontToBack();
	  /* Convert the map into an XImage */
	  image = CreateImageFromImg();
	}
	else {
	    image = XGetImage (dpy, root, x, y, width, height, 
    		       AllPlanes, pixmap_format);
	    if (multiVis == 2) /* Warn the user .... */
		fprintf(stderr, 
		"%s: Warning -- source windows differ in VisualClass or ColorMap\n",
		ProgramName);
	}

    }
    else if (num_vis == 1) { 
      image = XGetImage (dpy, root, x, y, width, height, 
	       AllPlanes, pixmap_format);
    }
    else { /* Duh ? */
      printf("Where are all the visuals ? \n");
      Exit(1);
    }
/* end MultiVisual Fix */

    if (do_grab) {
	XUngrabServer (dpy);
	XSync (dpy, 0);
    }

if (!image) { /* clean up */
/* start MultiVisual fix */
/* Nothing to do, as we assume that the program will exit when we return */
/* end MultiVisual fix */
  return (False);
}

    /*
     * Map the window and do the work.  Space means do another;
     * Button1 press displays pixel value.
     * q, Q, or ^C mean quit.
     */

    domore = False;			/* ButtonRelease will override */

/* start MultiVisual Fix */
    if (multiVis) {
      if (!w1) { /* But we *insisted* on a TrueColor Window ! */
	printf("Couldn't get a TrueColor 24 bit window...\n");
	Exit(1);
      }
      mw = w1;
      fGC=fillGC1;
    }
    else { 
      mw = w;
      fGC=fillGC;
    }
    XMapWindow (dpy, mw);
    (void)XSetWMProtocols(dpy, mw, &wm_delete_window, 1);
/* end MultiVisual Fix */
    for (done = False; !done; ) {
	XEvent event;
        XButtonEvent *buttonevent;
        XColor def;
	int len,first;
	char keybuffer[10];

	XNextEvent (dpy, &event);
	switch (event.type) {
	  case ClientMessage:
	    if (event.xclient.data.l[0] == wm_delete_window) {
	      XCloseDisplay(dpy);
	      exit(0);
	    }
	    break;
	  case Expose:
	    repaint_image (image, &event, magnification, back_pixel);
	    break;

	  case ButtonRelease:
            buttonevent = (XButtonEvent *) &event;
            if (buttonevent->button != Button1)
		domore = done = True;
	    break;

	  case ButtonPress:
            buttonevent = (XButtonEvent *) &event;
            if (buttonevent->button != Button1)
		continue;
            first = 1;
	    MapPixWindow (mw, (buttonevent->y/magnification < height/2));
            while (1) {     /* loop until button released */
                Window rootW,childW;
                int rx,ry,x,y,lx,ly;
                unsigned int mask;
                char str[64];

                if (XQueryPointer(dpy,mw,&rootW,&childW,&rx,&ry,&x,&y,&mask)) {
                    if (!(mask & Button1Mask)) break;    /* button released */
                    
                    x /= magnification;  y /= magnification;

		    /* look for new pixel */
                    if ((first || x != lx || y != ly) && 
			(x >= 0 && x < width && y >= 0 && y < height)) {
/* start MultiVisual Fix */
			if (multiVis) {
			  XColor *col = mvFindColorInColormap(x, y);
		          sprintf (str, 
			     "Pixel at (%d,%d):  %3lx   (%04x, %04x, %04x)",
			     x, y, col->pixel, col->red, col->green, col->blue);
			}
/* end MultiVisual Fix */
			else { 
                        def.pixel = XGetPixel (image, x, y);
			 if (def.pixel >= 0 && def.pixel < npixelvalues) {
			     XQueryColor (dpy, cmap, &def);
			     sprintf (str, 
			         "Pixel at (%d,%d):  %3lx   (%04x, %04x, %04x)",
			         x, y, def.pixel, def.red, def.green, def.blue);
			 } else {
			     def.red = def.green = def.blue = 0;
			     sprintf (str, "Pixel at (%d,%d):  %3ld",
				      x, y, def.pixel);
			 }
			}
                        DrawPixWindow (str);
                        first = 0;  lx = x;  ly = y;
		    }
		} else
		  break;
	    }
            UnmapPixWindow ();
	    break;

	  case KeyPress:
	    len = XLookupString (&event.xkey, keybuffer, sizeof keybuffer,
				 NULL, NULL);
	    if (len == 1 && (keybuffer[0] == 'q' || keybuffer[0] == 'Q' ||
			     keybuffer[0] == '\003')) {
		domore = False;		/* q, Q, or ^C to quit */
		done = True;
	    } else if (len == 1 && keybuffer[0] == ' ') {
		domore = True;		/* space to continue */
		done = True;
	    }				/* else ignore */
	    break;
	}
    }
    XUnmapWindow (dpy, mw);
    whp->flags |= (USPosition | USSize);
    XSetWMNormalHints (dpy, mw, whp);

    /*
     * free the image and return
     */

/* start MultiVisual Fix */
    if (num_vis > 1) {
      /* Reset the mvLib */
      mvReset();
    }
    if (!multiVis) {
      XDestroyImage (image);
    }
/* end MultiVisual Fix */
    return (domore);
}

static void
repaint_image (
    XImage *image,
    XEvent *eventp,
    int magnification,
    unsigned long back_pixel)
{
    XExposeEvent *ev = &eventp->xexpose;  /* to get repaint section */
    int e_row, e_column;		/* expose dimensions */
    int r_x, r_y, r_width, r_height;	/* filled rectangle dimensions */
    XGCValues gcv;			/* for doing filled rectangles */
    int row, column;			/* iterators */
    int initialx, maxrow, maxcolumn;	/* avoid recomputation */
    unsigned long pixel;		/* image pixel values */
    unsigned long prev_pixel;		/* last pixel set with XChangeGC */

    gcv.foreground = prev_pixel = back_pixel;
    XChangeGC (dpy, fGC, GCForeground, &gcv);

    /*
     * figure out where in the image we have to start and end
     */

    e_row = ev->y / magnification;
    e_column = ev->x / magnification;
    initialx = e_column * magnification;
    maxrow = e_row +
      ((ev->y + ev->height + magnification - 1) / magnification) - 1;
    maxcolumn = e_column +
      ((ev->x + ev->width + magnification - 1) / magnification) - 1;

    /*
     * clip to image size
     */

    if (maxcolumn >= image->width) maxcolumn = image->width - 1;
    if (maxrow >= image->height) maxrow = image->height - 1;

    /*
     * Repaint the image; be somewhat clever by only drawing when the pixel
     * changes or when we run out of lines.  
     */

    r_y = e_row * magnification;	/* to start */
    r_height = magnification;		/* always doing just 1 line */

    /*
     * iterate over scanlines (rows)
     */

    for (row = e_row; row <= maxrow; row++) {
	r_x = initialx;			/* start at beginning */
	r_width = 0;			/* have done nothing so far */

	/*
	 * iterate over pixels in scanline (columns)
	 */

	for (column = e_column; column <= maxcolumn; column++) {
	    pixel = XGetPixel (image, column, row);

	    /*
	     * If the current pixel is different from the previous pixel,
	     * then we need to set the drawing color and do the previous
	     * rectangle.  We can also avoid extra calls to XChangeGC by
	     * keeping track of the last value we set (note that this may
	     * be different from gcv.foreground if the latter is the same
	     * as back_pixel).  This is most useful when magnifying the
	     * background stipple pattern on monochrome displays.
	     */
	    if (pixel != gcv.foreground) {
		/*
		 * We only need to draw the rectangle if it isn't background.
		 */
		if (gcv.foreground != back_pixel && r_width > 0) {
		    if (gcv.foreground != prev_pixel) {
			XChangeGC (dpy, fGC, GCForeground, &gcv);
			prev_pixel = gcv.foreground;
		    }
		    XFillRectangle (dpy, mw, fGC,
				    r_x, r_y, r_width, r_height);
		}			/* end if */
		r_x += r_width;
		gcv.foreground = pixel;
		r_width = 0;
	    }				/* end if */
	    r_width += magnification;
	}				/* end for */
	/*
	 * draw final rectangle on line
	 */
	if (gcv.foreground != back_pixel && r_width > 0) {
	    if (gcv.foreground != prev_pixel) {
		XChangeGC (dpy, fGC, GCForeground, &gcv);
		prev_pixel = gcv.foreground;
	    }
	    XFillRectangle (dpy, mw, fGC, r_x, r_y, r_width, r_height);
	}				/* end if */

	r_y += magnification;		/* advance to next scanline */
    }					/* end for */

    XFlush (dpy);
    return;
}


static Window pixwind = None;
static XFontStruct *pixfinfo = NULL;
GC pixGC = (GC) NULL;

static void
MapPixWindow (
    Window wind,
    int bot)
{

    /* creates a small window inside of 'wind', at the top or bottom,
       suitable for displaying one line of text.  Also loads in a font 
       if necessary; John Bradley, University of Pennsylvania */

    Window rootW;
    int x,y;
    unsigned int w,h,bwide,depth,thigh;

    XGetGeometry (dpy, wind, &rootW, &x, &y, &w, &h, &bwide, &depth);

    if (!pixfinfo) {
	if (!pix_font) pix_font = DEFAULT_PIX_FONT;
	pixfinfo = XLoadQueryFont (dpy, pix_font);
	if (!pixfinfo) {
	    fprintf (stderr, "%s:  unable to load font '%s'\n",
		     ProgramName, pix_font);
	    Exit (1);
	}
    }

    thigh = pixfinfo->ascent + pixfinfo->descent + 4;
    y = (bot ? (h - thigh) : 0);

    if (pixwind == None) {
      XGCValues gcv;			/* for creating GC */
      XSetWindowAttributes xsw;
	XSetFont (dpy, fGC, pixfinfo->fid);
/* start MultiVisual fix */
	/**** don't use CreateSimpleWindow when there is the possibility
	 of Multiple visuals ......
	pixwind = XCreateSimpleWindow (dpy, wind, 0, y, w, thigh, 
				       0, None, BlackPixel (dpy, screen));
	******/
	/*
	 * Note that all these fileds need to be set, as the
	 * default CopyFromParent values may cause BadMatch
	 * errors, if the depth of the parent is different.
	*/
	xsw.background_pixel = BlackPixel(dpy, screen);
	/* We don't care for the border pixel, but must set it
	 * anyways, to any value at all, for the above reasons.
	 */
	xsw.border_pixel = BlackPixel(dpy, screen);
	xsw.colormap = DefaultColormap(dpy, screen);
	pixwind = XCreateWindow(dpy, wind, 0, y, w, thigh, 0, 
				DefaultDepth(dpy, screen), InputOutput,
				DefaultVisual(dpy, screen), 
				CWBackPixel|CWColormap|CWBorderPixel, &xsw);
	/* Make a GC ... */
        gcv.function = GXcopy;
        gcv.plane_mask = AllPlanes;
        gcv.fill_style = FillSolid;
    
        pixGC = XCreateGC (dpy,pixwind,(GCFunction | GCPlaneMask | GCFillStyle),
			&gcv);
/* End MultiVisual Fix */
    } else {
	XMoveWindow (dpy, pixwind, 0, y);
    }

    XMapWindow (dpy, pixwind);
}


static void
DrawPixWindow (char *str)
{
    XClearWindow (dpy, pixwind);
    XSetForeground (dpy, pixGC, WhitePixel(dpy, screen));
    XDrawString (dpy, pixwind, pixGC, 4, 2 + pixfinfo->ascent,
		 str, strlen (str));
}


static void
UnmapPixWindow(void)
{
    XUnmapWindow (dpy, pixwind);
/* start MultiVisual Fix */
    XDestroyWindow(dpy, pixwind);
    pixwind = None;
    XFreeGC(dpy, pixGC);
/* end MultiVisual Fix */
}

/* start MultiVisual Fix */

/*
 * Create an XImage from the Img we have. 
 * Note that this routine has nothing to 
 * do with the MultiVisual Mechanism.
 * It is a matter of policy that XMag chooses to
 * do all output to a 24 bit true color visual.
 * Selecting the best visual to display Img
 * is a totally distinct problem. XMag
 * solves it simplistically, by insisting on 24bit TrueColor.
 * The TrueColor visual is assumed to provide a 
 * linear ramp in each primary.
*/
static XImage *
CreateImageFromImg(void)
{
  XImage *image = FinalImage;
  int x, y;

  for (y = 0; y < ht; y++) {
    for (x=0; x < wd; x++) {
      unsigned long pixel;
      XColor *col = mvFindColorInColormap(x, y);
      pixel = ((unsigned long)((unsigned short)(col->red) >> rgb_shift)
		<<red_shift)
	     |((unsigned long)((unsigned short)(col->blue) >> rgb_shift)
		<<blue_shift) 
	     |((unsigned long)((unsigned short)(col->green) >> rgb_shift)
		<<green_shift);
      XPutPixel(image, x, y, pixel);
    }
  }
  return image;
}

static int
shhh(
    Display *dsp,
    XErrorEvent *err)
{
  /* be quiet */
  exit(1);
}


/*
 * Based on what mvLib returns, determine the best thing to do ...
*/
int 
IsMultiVis(int multivisFromMvLib)
{
  switch (multivisFromMvLib) {
    case 0: /* No multiVis problems, do it the simple way */
      return 0;	
    case 1: /* Definitely a multidepth problem */
      return 1;
    case 2: /* no depth problem , but colormap or visual class mismatch */
      /* do a best effort... if 24bit window exists, use the mvLib
	 else do a simple GetImage, and warn user that displayed image
	 may not show true colors. */
      if (w1)  /* have TrueColor capability */
	return 1;
      /* else , best effort */
      fprintf(stderr, 
             "%s: Warning - source window has different colormap or visual than root\n Image displayed using colormap and visual of root\n",
	      ProgramName);
      return 0;
  }
  return 0;
}
/* end MultiVisual Fix */
