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
#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include "cmcutil.h"
#include "cmc.h"


/*
** Common utility routines shared by the Workspace Colors programs
** cmcsave, cmcshow, cmcinit.
*/

/*ARGSUSED*/
static int 
disp_err_handler (Display *dpy)

{
	fatal_error("cannot open display \"%s\"", display_name);
}

/*
** Open display and handle any errors.
*/

Display *
open_display (const char *dpyname)
{
	Display *dpy;

	/*
	**  Catch errors opening display so user doesn't
	**  get confusing 'XIOError: Broken Pipe' message.
	*/
	XSetIOErrorHandler(disp_err_handler); 

	display_name = XDisplayName(dpyname);
	if (!(dpy = XOpenDisplay(dpyname))) 
		return NULL;

	XSync(dpy, 0);
	XSetIOErrorHandler(NULL); 

	return dpy;
}


/*
** Return true if default visual of screen is dynamic.
*/

int
dynamic_indexed_default_visual (Screen *screen)
{
	int class = DefaultVisualOfScreen(screen)->class;

	return (class == GrayScale 	||
	        class == PseudoColor);
}

/*
** If file name is not already absolute, make absolute
** relative to home directory.
*/

static const char *
fn_absolutize (const char *relname)

{
	static char 	filename[256];
	const char	*homedir;

	if (*relname == '/') 
		return relname;

	if (!(homedir = (char *) getenv("HOME")))
		homedir = "/";
	sprintf(filename, "%s/%s", homedir, relname);
	return filename;
}


const char *
comp_colors_filename (const char *basename)

{
	if (!basename)
		basename = COMPACTED_COLORS_FILE;
	return fn_absolutize(basename);

}

int
cmc_write (
    FILE	*f,
    int		scr_num,
    int		ncolors,
    XColor	*colors)

{
	(void)fwrite(&scr_num, sizeof(int), 1, f);
	(void)fwrite(&ncolors, sizeof(int), 1, f);
	(void)fwrite(colors, sizeof(XColor), ncolors, f);

	return 1;
}


/*
** 0 is returned on EOF; 1 otherwise
*/

int
cmc_read (
    FILE	*f,
    int		*scr_num,
    int		*ncolors,
    XColor	**colors)

{
	if (!fread(scr_num, sizeof(int), 1, f)) 
		return 0;

	if (!fread(ncolors, sizeof(int), 1, f)) {
		fprintf(stderr, "error: premature end-of-file\n");
		fatal_error("cannot read number of saved colors");
	}

	if (!(*colors = (XColor *) malloc(*ncolors * sizeof(XColor)))) 
		fatal_error("not enough memory");

	if (!fread(*colors, sizeof(XColor), *ncolors, f)) {
		fprintf(stderr, "error: premature end-of-file\n");
		fatal_error("cannot read saved colors");
	}

	return 1;
}


void
cmc_header_write (
    FILE	*f)

{
	int	value;
	
	/* write magic number and version */
	value = CMC_MAGIC;
	(void)fwrite(&value, sizeof(int), 1, f);
	value = CMC_VERSION;
	(void)fwrite(&value, sizeof(int), 1, f);
}


void
cmc_header_test (
    FILE	*f)

{
	int	value;
	
	/* check magic number */
	if (!fread(&value, sizeof(int), 1, f) ||
	    value != CMC_MAGIC)
		fatal_error("Unrecognized colors file.  Expected magic number = %x,  \
Actual = %x", CMC_MAGIC, value);

	/* check version number */
	if (!fread(&value, sizeof(int), 1, f) ||
	    value != CMC_VERSION)
		fatal_error("Unrecognized colors file.  Expected version number = %x,  \
Actual = %x", CMC_VERSION, value);
}


void
prop_update (
    Display	*dpy,
    Window	w,
    const char	*name,
    Atom	type,
    int		format,
    int		data,
    int		nelem)

{
	/* intern the property name */
	Atom	atom = XInternAtom(dpy, name, 0);

	/* create or replace the property */
	XChangeProperty(dpy, w, atom, type, format, PropModeReplace, 
		(unsigned char *)&data, nelem);
}


/*
** Sets the close-down mode of the cmc client to 'RetainPermanent'
** so all client resources will be preserved after the client
** exits.  Puts a property on the default root window containing
** an XID of the client so that the resources can later be killed.
*/

void
resource_preserve (
    Display	*dpy)

{
	Window	w = DefaultRootWindow(dpy);

	/* create dummy resource */
	Pixmap	pm = XCreatePixmap(dpy, w, 1, 1, 1);
	
	/* create/replace the property */
	prop_update(dpy, w, RETAIN_PROP_NAME, XA_PIXMAP, 32, (int)pm, 1);
	
	/* retain all client resources until explicitly killed */
	XSetCloseDownMode(dpy, RetainPermanent);
}


/*
** Flushes any resources previously retained by a cmc client,
** if any exist.
*/

void
resource_discard (
    Display	*dpy)

{
	Pixmap	*pm;			
	Atom	actual_type;		/* NOTUSED */
	int	format;
	unsigned long	nitems;
	unsigned long	bytes_after;

	/* intern the property name */
	Atom	atom = XInternAtom(dpy, RETAIN_PROP_NAME, 0);

	/* look for existing resource allocation */
	if (XGetWindowProperty(dpy, DefaultRootWindow(dpy), atom, 0, 1,
		1/*delete*/, AnyPropertyType, &actual_type, &format, &nitems,
		&bytes_after, (unsigned char **) &pm) == Success
	    && nitems == 1) {

		if (actual_type == XA_PIXMAP && format == 32 &&
		    nitems == 1 && bytes_after == 0) {
			/* blast it away */
			XKillClient(dpy, *pm);
			XFree(pm);
		} else if (actual_type != None) {
		    extern char *program;
		    fprintf(stderr, "%s: warning: invalid format encountered for property %s\n",
				 RETAIN_PROP_NAME, program);
		}
	}
}




