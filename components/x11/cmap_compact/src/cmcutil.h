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


/*
** Definitions shared between several Workspace Color operations
*/

#ifndef CMCUTIL_INCLUDE
#define CMCUTIL_INCLUDE

#include <stdio.h>

/*
** Symbols
*/

#define COUNT_PROP_NAME		"XA_COMPACTED_COLORS_COUNT"
#define RETAIN_PROP_NAME	"XA_COMPACTED_COLORS_XID"

/* 
** Note: if you change these, you must also change it in 
** server/cscript/cs_cmap.c.
*/
#define COMPACTED_COLORS_FILE	".owcolors"
#define CMC_MAGIC		0xb0f0
#define CMC_VERSION		0



/*
** Macros
*/

#define WHITE(c)\
	((c)->red == (c)->green && \
	 (c)->red == (c)->blue  && \
	 (c)->red == 0xffff)

#define BLACK(c)\
	((c)->red == (c)->green && \
	 (c)->red == (c)->blue  && \
	 (c)->red == 0x0)

/*
** Types
*/

typedef unsigned long Pixel;


/*
** External Functions
*/

extern void		fatal_error(const char *format, ...)
				_X_ATTRIBUTE_PRINTF(1,2) _X_NORETURN;
extern void		warning(const char *format, ...)
				_X_ATTRIBUTE_PRINTF(1,2);
extern Display		*open_display(const char *dpyname);
extern int		dynamic_indexed_default_visual(Screen *screen);
extern const char *	comp_colors_filename(const char *);
extern int		cmc_write(FILE *f, int scr_num,
				  int ncolors, XColor *colors);
extern int		cmc_read(FILE *f, int *scr_num,
				 int *ncolors, XColor **colors);
extern void		cmc_header_write(FILE *f);
extern void		cmc_header_test(FILE *f);
extern void		resource_preserve(Display *dpy);
extern void		resource_discard(Display *dpy);
extern void		prop_update(Display *dpy, Window w, const char *name,
				    Atom type, int format, int data, int nelem);

#endif /* !CMCUTIL_INCLUDE */
