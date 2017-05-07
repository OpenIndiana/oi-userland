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


#include <stdio.h>
#include <X11/Xlib.h>
#include "cmc.h"
#include "cmcutil.h"


/*
** For each screen, generates NeWS PostScript commands on stdio
** capable of doing X11/NeWS-specific initialization when executed.
**
** Output is of the form:
**
** 	<scr_num> <ncolors> cmap_compact_rearrange_scr
** 	<scr_num> <ncolors> cmap_compact_rearrange_scr
**	...
**
** where <scr_num> is the screen index of each screen,
** <ncolors> is the number of saved colors, and 'cmap_compact_rearrange_scr'
** is a NeWS routine which performs rearrangement of various predefined
** colors to further reduce colormap flashing with other X11/NeWS
** programs.
*/

void
cmc_NeWSinit (void)

{
	const char *filename;
	FILE	*f;

	filename = comp_colors_filename(basename_arg);
	if ((f = fopen(filename, "r")) == NULL)
		exit(0);

	/* Check magic number and version */
	cmc_header_test(f);

	for (;;) {
		int	scr_num;
		int	ncolors;
		XColor	*colors;

		if (!cmc_read(f, &scr_num, &ncolors, &colors))
			break;

		printf("%d %d cmap_compact_rearrange_scr\n", scr_num, ncolors);

		free((char *)colors);
	}
}


