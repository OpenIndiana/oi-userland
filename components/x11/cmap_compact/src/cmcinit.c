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
*
*/


#include <stdio.h>
#ifndef SYSV
#include <alloca.h>
#endif
#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include "cmc.h"
#include "cmcutil.h"

#define MIN(a,b)	((a)<(b)?(a):(b))


static void
cmc_alloc (
    Screen	*screen,
    int		ncolors,
    XColor	*colors)

{
	register Colormap cmap = DefaultColormapOfScreen(screen);
	register Pixel  *p;
	register XColor	*c;
	register int	nalloc;
	register int	total_alloc = 0;
	register int	ntotal;
	unsigned long	mask;
	Pixel		*pixels;
	int		nc;

	ntotal = 1<<PlanesOfScreen(screen);
#ifdef SYSV
	pixels = (Pixel *) malloc(ntotal * sizeof(Pixel));
#else
	pixels = (Pixel *) alloca(ntotal * sizeof(Pixel));
#endif

	/* Grab as many private cells as we can */
	for (nalloc=ntotal, p=pixels;  nalloc > 0; nalloc>>=1) {
		if (!XAllocColorCells(DisplayOfScreen(screen), cmap, 0, &mask, 0, 
				p, nalloc))
		        continue;
		p += nalloc;
		total_alloc += nalloc;
	}

	/* 
	** May not be able to get as many colors as requested.
	*/	
	nc = MIN(ncolors, total_alloc);
	if (nc != ncolors) {
	    (void) fprintf(stderr, "Warning: can only allocate %d of the requested %d colors.\n", nc, ncolors);
	    (void) fprintf(stderr, "Continuing anyway.\n");
        }
	ncolors = nc;

	/* Free enough space for workspace colors */
	nalloc = total_alloc - ncolors;
	XFreeColors(DisplayOfScreen(screen), cmap, pixels+nalloc, ncolors, 0);

	/* Allocate the workspace colors */
	for (c=colors+ncolors-1; c>=colors; c--)
		if (!XAllocColor(DisplayOfScreen(screen), cmap, c)) 
			fatal_error("attempt to allocate color failed");

	/* Free placeholder pixels */
	XFreeColors(DisplayOfScreen(screen), cmap, pixels, nalloc, 0);

	/* 
	** Tell everybody how many workspace colors there are.
	** Be sure to include white/black if they're at the
	** high end.
	*/
	{ Visual *vis = DefaultVisualOfScreen(screen);
	  int    cmap_size = vis->map_entries;
	  if (WhitePixelOfScreen(screen) == cmap_size-1 ||
	      WhitePixelOfScreen(screen) == cmap_size-2)
		ncolors++;
	  if (BlackPixelOfScreen(screen) == cmap_size-1 ||
	      BlackPixelOfScreen(screen) == cmap_size-2)
		ncolors++;
	  prop_update(DisplayOfScreen(screen), RootWindowOfScreen(screen), 
			COUNT_PROP_NAME, XA_INTEGER, 32, ncolors, 1);
	}
#ifdef SYSV
	free(pixels);
#endif
}


static void
cmc_alloc_protected (
    Screen	*screen,
    int		ncolors,
    XColor	*colors)
{
	XGrabServer(DisplayOfScreen(screen));
	cmc_alloc(screen, ncolors, colors);
	XUngrabServer(DisplayOfScreen(screen));
}


/*
** For each screen for which there is saved workspace colors,
** allocates these colors as high as possible in the default
** colormap of the screen.
*/

void
cmc_init (void)

{
	Display		*dpy;
	FILE		*f;
	const char	*filename;

	/* Open display */
	if (!(dpy = open_display(display_name))) 
		fatal_error("cannot open display '%s'\n", display_name);

	/* For some strange reason, cmc_alloc_protected fails if not
	   run synchronously */
	XSynchronize(dpy, 1);

	/* Open file where workspace colors are stored */
	filename = comp_colors_filename(basename_arg);	
	if ((f = fopen(filename, "r")) == NULL) 
		/* Do nothing if not found */
		return;
		
	/* Check magic number and version */
	cmc_header_test(f);

	/* Abandon any previously allocated workspace colors (all screens) */
	resource_discard(dpy);

	/* For each screen of display ... */
	for (;;) {
		Screen  *screen;
		int	scr_num;
		int	ncolors;
		XColor	*colors;

		if (!cmc_read(f, &scr_num, &ncolors, &colors))
			break;

		/* See if screen is still present */
		if (scr_num >= ScreenCount(dpy)) {
			warning("Warning: cannot allocated saved colors for screen %d because\nthe display no longer has this many screens\n", scr_num);
			continue;
		}
		screen = ScreenOfDisplay(dpy, scr_num);

		/* 
		** Existence of workspace colors for the screen implies
		** that its default visual was dynamic indexed.   Make sure
		** it still is.
		*/
		if (!dynamic_indexed_default_visual(screen)) {
			warning("default visual for screen %d is no longer dynamic indexed\nsaved colors not allocated for screen %d", scr_num, scr_num);
			continue;
		}

		/* Allocate workspace colors at high end of colormap */
		cmc_alloc_protected(screen, ncolors, colors);
		free((char *)colors);
	}

	/* Preserve newly allocated client resources */
	resource_preserve(dpy);

	XCloseDisplay(dpy);
}
