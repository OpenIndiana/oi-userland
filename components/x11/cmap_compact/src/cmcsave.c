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
#include <X11/Xlibint.h>
#include "cmc.h"
#include "cmcutil.h"

#define CELL_IGNORE	0
#define CELL_READONLY	1


/*
**  Handle I/O errors when opening display
*/

static int badaccess_error;

/*
**  Handle X request errors.
**  Just set a flag to let the routine making an X
**  call know that the call resulted in a BadAccess error.
**  Any other errors are processed normally.
*/

static int
bad_handler (
    Display 	*dpy,
    XErrorEvent	*err)
{
    if (err->error_code == BadAccess)
        badaccess_error = 1;
    else
        return _XDefaultError(dpy,err);
    return 0;
}


/*
** Examines the given colormap to determine the number of
** read-only cells, their locations, and their color values.
**
** All non-read-only cells (privately allocated, unallocated
** or reserved) are ignored.
*/

static void
cmc_record (
    Screen	*screen,
    int		*ncolors,
    XColor	**colors)
{
	register Colormap cmap = DefaultColormapOfScreen(screen);
	register int 	i, nalloc;
	register int	*p;
	register XColor *c;
	int		totalpix;
	unsigned long	masks;		/* NOTUSED */
	Pixel		*pixels;
	int		*pixtype;
	XColor		color;

	/* start out assuming all are read-only */
	totalpix = 1<<PlanesOfScreen(screen);

	/* allocate local scratch memory */
#ifdef SYSV
	if (!(pixels = (Pixel *) malloc(totalpix * sizeof(Pixel)))) 
		fatal_error("cannot allocate memory ");
	if (!(pixtype = (int *) malloc(totalpix * sizeof(Pixel)))) 
		fatal_error("cannot allocate memory ");
#else
	if (!(pixels = (Pixel *) alloca(totalpix * sizeof(Pixel)))) 
		fatal_error("cannot allocate memory on stack");
	if (!(pixtype = (int *) alloca(totalpix * sizeof(Pixel)))) 
		fatal_error("cannot allocate memory on stack");
#endif
	for (i=0, p=pixtype; i<totalpix; i++, p++)
		*p = CELL_READONLY;
	*ncolors = totalpix;

	/*
	** First, find the free cells by allocating them all private.
	** We allocate by decreasing powers of 2 so the allocation
	** time will be proportional to the number of display planes
	** instead of the number of display cells.
	**
	** Mark the free cells we find.  These allocations will
	** be freed when the connection is closed.
	*/
	for (nalloc=totalpix; nalloc > 0; nalloc >>= 1) {
	    if(!XAllocColorCells(DisplayOfScreen(screen), cmap, 0, &masks, 0, 
			pixels, nalloc))
	        continue;
	    for (i=0; i<nalloc; i++) {
	        pixtype[pixels[i]] = CELL_IGNORE;
	    }
	    *ncolors -= nalloc;
	}
	
	/*
	** Find the read-only cells (excluding white/black).
	**
	** Get the Hardware color for the color of each allocated cell.
	**      This can only work if the returned color is a previously
	**      allocated r/o cell (we have all cells allocated).
	*/
	XSetErrorHandler(bad_handler);
	for(i=0, p=pixtype; i<totalpix; i++, p++) {
	    if(*p != CELL_IGNORE) {
	        color.pixel = i;

		/* Eliminate reserved cells */
	        badaccess_error = 0;
	        XQueryColor(DisplayOfScreen(screen), cmap, &color);
	        XSync(DisplayOfScreen(screen), 0); /* make sure any error is reported */
	        if      (badaccess_error) {
			pixtype[color.pixel] = CELL_IGNORE;
			(*ncolors)--;
	        } else {
			badaccess_error = 0;
			XStoreColor(DisplayOfScreen(screen), cmap, &color);
			if (!badaccess_error) {
				/* Eliminate read/write cells */
			   	pixtype[color.pixel] = CELL_IGNORE;
				(*ncolors)--;
			} else if (WHITE(&color) || BLACK(&color)) {
				/* Eliminate white/black cells */
			   	pixtype[color.pixel] = CELL_IGNORE;
				(*ncolors)--;
			}
			/* else if alloc succeeded, it must be read-only */
		}
	    }
	}
	XSync(DisplayOfScreen(screen), 0);
	XSetErrorHandler(NULL);

	/* allocate the memory for the read-only cells */
	if (!(*colors = (XColor *) calloc(*ncolors, sizeof(XColor)))) 
		fatal_error("not enough memory");

	/* 
	** Get the color values for the read-only cells, ignoring private
	** cells, reserved cells, and white/black.
	*/
	for (i=0, c=*colors; i<totalpix; i++) {
	    if (pixtype[i] != CELL_IGNORE) {
	        (c++)->pixel = i;
	    }
	}
        XQueryColors(DisplayOfScreen(screen), cmap, *colors, *ncolors);
#ifdef SYSV
	free(pixels);
	free(pixtype);
#endif
}


/*
** Examines the default colormap with the server grabbed
** to prevent changes during the examination process.
*/

static void
cmc_record_protected (
    Screen	*screen,
    int		*ncolors,
    XColor	**colors)
{
	XGrabServer(DisplayOfScreen(screen));
	cmc_record(screen, ncolors, colors);
	XUngrabServer(DisplayOfScreen(screen));
}


/*
** For each screen for which the default colormap is dynamic indexed 
** record all read-only color cells in the default colormap. 
*/

void
cmc_save (void)
{
	register int 	scr_num;
	Display 	*dpy;
	FILE		*f;
	const char	*filename;

	/* Open display */
	if (!(dpy = open_display(display_name))) 
		fatal_error("cannot open display '%s'", display_name);

	/* For some strange reason, colorscells_get_protected fails if not
	   run synchronously */
	XSynchronize(dpy, 1); 

	/* Open file to save in */
	filename = comp_colors_filename(basename_arg);
	if ((f = fopen(filename, "w")) == NULL)
		fatal_error("cannot open file '%s' for writing", filename);

	/* Save magic number and version */
	cmc_header_write(f);

	/* For each screen of display ... */
	for (scr_num = 0; scr_num < ScreenCount(dpy); scr_num++) {
		Screen  *screen = ScreenOfDisplay(dpy, scr_num);
		int	ncolors;
		XColor	*colors;

		/* Do nothing if default visual is not dynamic */
		if (!dynamic_indexed_default_visual(screen)) {
			if (warn_flag) {
			    warning("default visual for screen %d is not dynamic indexed",
					scr_num);
			    warning("no colors saved for screen %d", scr_num );
			}
			continue;
		}

		/* 
		** Discover what read-only cells are in the default colormap.
		** 
		** These will be considered the "workspace colors."
		*/
		cmc_record_protected(screen, &ncolors, &colors);

		/* Save read-only cells for screen in workspace color file */
		if (!cmc_write(f, scr_num, ncolors, colors))
			fatal_error("cannot write to file %s", filename);

		free((char *)colors);
	}

	XCloseDisplay(dpy);
}



