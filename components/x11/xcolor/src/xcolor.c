/*-
 * xcolor.c - X11 client to display all colors in current colormap.
 *
 * Copyright (c) 1989, 2011, Oracle and/or its affiliates. All rights reserved.
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
 * naughton@wind.sun.com
 */


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <X11/X.h>
#include <X11/Xos.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/keysym.h>
#include "xcolor.h"

#define DEFX 256
#define DEFY 256
#define DEFW 128
#define DEFH 128

#define ICON_WIDTH 48
#define ICON_HEIGHT 48

Display    	   *dsp = NULL;		/* current display (must be inited) */
static int	    screen;
static Visual	   *visual;
static Window	    win;		/* window used to cover screen */
static GC	    gc;			/* graphics context */
static int	    height = 0,
	            width = 0;
static Colormap	    cmap;
static Atom	    ATOM_WM_PROTOCOLS;
static Atom	    ATOM_WM_DELETE_WINDOW;

static int    	    cmap_size;

#define error(...) do { fprintf(stderr, __VA_ARGS__) ; exit(1); } while (0)

static void
dumpCmap(void)
{
    register int i;
    XColor      color[256];

    for (i = 0; i < 256; i++)
	color[i].pixel = i;
    XQueryColors(dsp, DefaultColormap(dsp, screen), color, 256);
    for (i = 0; i < 256; i++) {
	printf("/name%02x	%3d %3d %3d RGBcolor def\n",
	      i, color[i].red >> 8, color[i].green >> 8, color[i].blue >> 8);
    }
}

static void
redisplay_indexed(Window window)
{
    int		 max;
    register int i,
                 j;
    register float fw;
    register float fh;

    switch (cmap_size) {
        case   2:   max = 2;   break;
        case  16:   max = 4;   break; 
        case 256:   max = 16;  break;
        default:    max = (int)sqrt((double)cmap_size);
    }

    if (window == win) {
	fw = (float) width / (float)max;
	fh = (float) height / (float)max;
    } else {
	fw = (float) ICON_WIDTH / (float)max;
	fh = (float) ICON_HEIGHT / (float)max;
    }

    for (i = 0; i < max; i++) {
	register int y = (int) (i * fh);
	register int h = (i + 1) * fh - y;
	for (j = 0; j < max; j++) {
	    register int x = (int) (j * fw);
	    register int w = (j + 1) * fw - x;
	    XSetForeground(dsp, gc, i * max + j);
	    XFillRectangle(dsp, window, gc, x, y, w, h);
	}
    }
}

static void
redisplay_direct(Window window)
{
    register int i,
                j, k;
    register float fw;
    register float fh;
    static int roffset, goffset, boffset;
    static int got_offsets = 0;

    if (window == win) {
	fw = (float) width / 16.0;
	fh = (float) height / (3 * 16.0);
    } else {
	fw = (float) ICON_WIDTH / 16.0;
	fh = (float) ICON_HEIGHT / (3 * 16.0);
    }

    if (!got_offsets) {
	got_offsets = 1;
	roffset = ffs(visual->red_mask)-1;
	goffset = ffs(visual->green_mask)-1;
	boffset = ffs(visual->blue_mask)-1;
    }

    /* red channel */
    k = 0;
    for (i = 0; i < 16; i++, k++) {
	register int y = (int) (k * fh);
	register int h = (k + 1) * fh - y;
	for (j = 0; j < 16; j++) {
	    register int x = (int) (j * fw);
	    register int w = (j + 1) * fw - x;
	    XSetForeground(dsp, gc, (i * 16 + j)<<roffset);
	    XFillRectangle(dsp, window, gc, x, y, w, h);
	}
    }

    /* green channel */
    for (i = 0; i < 16; i++, k++) {
	register int y = (int) (k * fh);
	register int h = (k + 1) * fh - y;
	for (j = 0; j < 16; j++) {
	    register int x = (int) (j * fw);
	    register int w = (j + 1) * fw - x;
	    XSetForeground(dsp, gc, (i * 16 + j)<<goffset);
	    XFillRectangle(dsp, window, gc, x, y, w, h);
	}
    }

    /* blue channel */
    for (i = 0; i < 16; i++, k++) {
	register int y = (int) (k * fh);
	register int h = (k + 1) * fh - y;
	for (j = 0; j < 16; j++) {
	    register int x = (int) (j * fw);
	    register int w = (j + 1) * fw - x;
	    XSetForeground(dsp, gc, (i * 16 + j)<<boffset);
	    XFillRectangle(dsp, window, gc, x, y, w, h);
	}
    }
}

static void
redisplay (Window w)
{
    if (visual->class == TrueColor || visual->class == DirectColor)
	    redisplay_direct(w);
    else
	    redisplay_indexed(w);
}

static void
HandleEvents(void)
{
    XEvent      event;
    XConfigureEvent *xce = (XConfigureEvent *) & event;
    XKeyEvent  *xke = (XKeyEvent *) & event;

    while (1) {
	XNextEvent(dsp, &event);
	switch (event.type) {
	case Expose:
	    redisplay(event.xexpose.window);
	    continue;
	case GraphicsExpose:
	case NoExpose:
	case MapNotify:
	case UnmapNotify:
	    continue;
	case ConfigureNotify:
	    if ((height == xce->height) && (width == xce->width))
		continue;
	    height = xce->height;
	    width = xce->width;
	    redisplay(event.xconfigure.window);
	    continue;
	case KeyPress:
	    switch (XLookupKeysym(xke, 0)) {
	    case XK_Escape:
		return;
	    default:
		continue;
	    }
	case ClientMessage:
	    if (event.xclient.message_type == ATOM_WM_PROTOCOLS &&
		event.xclient.format == 32 &&
		event.xclient.data.l[0] == ATOM_WM_DELETE_WINDOW)
	    {
		return;
	    }
	    continue;
	}
    }
}

int
main(
    int         argc,
    char       *argv[]
    )
{
    XSetWindowAttributes xswa;
    XGCValues   xgcv;
    XSizeHints  size_hints;
    XWMHints	wmhints;
    int         i;
    int         geomStat;
    char       *geom = NULL;
    char       *displayName = NULL;
    Status      stat;
    int         dump = 0;
    int		nobw = 0;
    int		half = 0;
    int		install = 1;
    int		mask;
    int		useiconwin = 0;
    const char *pname;

    if (getenv("_SYNC")) { 
	extern int _Xdebug;
	_Xdebug = 1;
    }

    pname = argv[0];
    for (i = 1; i < argc; i++) {
	if (!strcmp(argv[i], "-geometry"))
	    geom = argv[++i];
	else if (!strcmp(argv[i], "-display"))
	    displayName = argv[++i];
	else if (!strcmp(argv[i], "-dump"))
	    dump = 1;
	else if (!strcmp(argv[i], "-nobw"))
	    nobw = 1;
	else if (!strcmp(argv[i], "-half"))
	    half = 1;
	else if (!strcmp(argv[i], "-noinst"))
	    install = 0;
	else if (!strcmp(argv[i], "-iconwin"))
	    useiconwin = 1;
	else
	    error("usage:  %s [-display dpystr] [-geometry geomstr]\n"
		  "\t[-dump] [-nobw] [-half] [-noinst] [-iconwin]\n", pname);
    }

    if (!(dsp = XOpenDisplay(displayName))) {
	error("%s: unable to open display, %s.\n", pname,
	      displayName ? displayName : "no display specified");
    }

    screen = DefaultScreen(dsp);
    visual = DefaultVisualOfScreen(DefaultScreenOfDisplay(dsp));
    cmap_size = visual->map_entries;

    ATOM_WM_PROTOCOLS = XInternAtom(dsp, "WM_PROTOCOLS", False);
    ATOM_WM_DELETE_WINDOW = XInternAtom(dsp, "WM_DELETE_WINDOW", False);

    if (dump)
	dumpCmap();

    if (install)  {
	    stat = XCreateHSBColormap(dsp, screen, &cmap, half 
					? (cmap_size>>1) : cmap_size,
				      0.0, 1.0, 1.0,
				      1.0, 1.0, 1.0, !nobw, &visual);
	    if (stat != Success)
		error("%s: unable to create colormap (%d).\n", pname, stat);
    }

    size_hints.x = DEFX;
    size_hints.y = DEFY;
    size_hints.width = DEFW;
    size_hints.height = DEFH;

    size_hints.flags = 0;
    if (geom) {
	geomStat = XParseGeometry(geom, &(size_hints.x),
				  &(size_hints.y),
				  (unsigned int *) &(size_hints.width),
				  (unsigned int *) &(size_hints.height));
	if (geomStat & (XValue | YValue)) {
	    size_hints.flags |= USPosition;
	}
	if (geomStat & (WidthValue | HeightValue)) {
	    size_hints.flags |= USSize;
	}
    }

    width = size_hints.width;
    height = size_hints.height;

    xswa.event_mask = ExposureMask | KeyPressMask | StructureNotifyMask;
    mask = CWEventMask;

    if (install) {
	    xswa.colormap = cmap;
	    mask |= CWColormap;
    }
   
    win = XCreateWindow(
			dsp,
			DefaultRootWindow(dsp),
			size_hints.x,
			size_hints.y,
			size_hints.width,
			size_hints.height,
			1,	/* borderwidth */

			DefaultDepth(dsp, screen),	/* depth */
			InputOutput,	/* class */
			visual,	/* visual */
			mask,	/* window attribute mask */
			&xswa	/* the attributes */
	);

    XSetStandardProperties(dsp, win, " XColor ", " XCOLOR ",
			   None, argv, argc, &size_hints);

    wmhints.flags = InputHint;
    wmhints.input = True;

    if (useiconwin) {
	Window	    icon;

	xswa.event_mask = ExposureMask;
	mask = CWEventMask;

	if (install) {
	    xswa.colormap = cmap;
	    mask |= CWColormap;
	}

	icon = XCreateWindow(dsp, DefaultRootWindow(dsp),
	    0, 0, ICON_WIDTH, ICON_HEIGHT, 0, DefaultDepth(dsp, screen),
	    InputOutput, visual, mask, &xswa);

	wmhints.flags |= IconWindowHint;
	wmhints.icon_window = icon;

	if (install) {
	    Window cmapwins[2];

	    cmapwins[0] = icon;
	    cmapwins[1] = win;
	    XSetWMColormapWindows(dsp, win, cmapwins, 2);
	}
    }

    XSetWMHints(dsp, win, &wmhints);
    XSetWMProtocols(dsp, win, &ATOM_WM_DELETE_WINDOW, 1);

    xgcv.foreground = BlackPixel(dsp, screen);
    xgcv.background = WhitePixel(dsp, screen);
    gc = XCreateGC(dsp, win, GCForeground | GCBackground, &xgcv);

    XMapWindow(dsp, win);

    HandleEvents();

    XUnmapWindow(dsp, win);
    XDestroyWindow(dsp, win);
    XFlush(dsp);
    XCloseDisplay(dsp);
    exit(0);
}
