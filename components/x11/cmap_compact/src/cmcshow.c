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
*
*/

#include <stdio.h>
#include <X11/Xlib.h>
#include "cmc.h"
#include "cmcutil.h"


static void print_xcolors(XColor *colors, int ncolors);


/*
** Print contents of workspace colors file in human readable form.
*/

void
cmc_show (void)

{
	const char *filename;
	FILE	*f;

	filename = comp_colors_filename(basename_arg);
	if ((f = fopen(filename, "r")) == NULL)
		fatal_error("cannot open file '%s' for reading\n", filename);

	/* Check magic number and version */
	cmc_header_test(f);

	for (;;) {
		int	scr_num;
		int	ncolors;
		XColor	*colors;

		if (!cmc_read(f, &scr_num, &ncolors, &colors))
			break;

		printf("Screen %s.%d\n", XDisplayName(display_name), scr_num);	
		printf("%d saved colors\n", ncolors);

		print_xcolors(colors, ncolors);
		printf("\n");

		free((char *)colors);
	}
}


static void
print_xcolors (XColor *colors, int ncolors)

{
	register XColor	*c;
	register int	i;
	int		planes;

	for (c = colors; c < colors + ncolors; c++) {
            planes = c->red | c->green | c->blue;
            for(i = 4; i > 1 && (planes&0xf)==0; i--) {
                c->red >>= 4;
                c->green >>= 4;
                c->blue >>= 4;
                planes >>= 4;
            }
            printf("#%0*x%0*x%0*x\n", i, c->red, i, c->green, i, c->blue);
	}
}	
