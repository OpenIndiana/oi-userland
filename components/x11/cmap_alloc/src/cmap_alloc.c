/*
*
* cmap_alloc.c 1.x
*
* Copyright (c) 1991, 2015, Oracle and/or its affiliates. All rights reserved.
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


#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <X11/Xatom.h>
#include <stdio.h>
#include <stdlib.h>

#define All	-1
#define DYNAMIC_VISUAL(class)	(((class) % 2) ? True : False)

char	       *prog_name;
char	       *display_name = NULL;
int		force = False;
int		all_screens = False;
int		depth = All;
int		visual_class = All;
int		verbose = False;

int			 created_colormap = False;
XStandardColormap	*allocated_cmaps;
int			 num_cmaps;
XVisualInfo		*available_visuals;
int			 num_visuals;

static void	alloc_cmaps_for_screen(Display *display, int screen);
static void	alloc_cmap_for_visual(Display *display, int screen,
				      XVisualInfo *vinfo);
static void	create_colormap(Display *display, XVisualInfo *vinfo,
				XStandardColormap *std_colormap);
static char    *visual_class_name(int class);
static void	parse_cmdline(int argc, char **argv);
static int	string_to_depth(const char *str);
static int	string_to_visual(const char *str);
static void	usage(void) _X_NORETURN;


int
main(
    int         argc,
    char      **argv)
{
    Display *display;
    int screen;

    /* Take care of command line options */
    parse_cmdline(argc, argv);
    
    /* Try to open the display */
    if ((display = XOpenDisplay(display_name)) == NULL) {
	(void)fprintf(stderr, "Error %s: can't open display \"%s\".\n",
		      argv[0], XDisplayName(display_name));
	exit(0);
    }

    /* Handle all necessary screens */
    if (all_screens)
      for (screen = 0; screen < ScreenCount(display); screen++)
	alloc_cmaps_for_screen(display, screen);
    else
      alloc_cmaps_for_screen(display, DefaultScreen(display));

    /* If we created any colormaps, we need to ensure 
     * that they live after the program exits.
     */
    if (created_colormap)
      XSetCloseDownMode(display, RetainPermanent);
    
    XCloseDisplay(display);
    return (1);
}


static void
alloc_cmaps_for_screen(
    Display *display,
    int	     screen)
{
    XVisualInfo vinfo_template;
    XVisualInfo *vinfo;
    VisualID	 default_visualid;
    int v;
    
    if (verbose)
      (void)printf("Creating colormaps for screen #%d:\n", screen);
    
    /* Find out if any colormaps already exist in the property */
    if (!XGetRGBColormaps(display, RootWindow(display, screen), 
			  &allocated_cmaps, &num_cmaps, XA_RGB_DEFAULT_MAP))
      num_cmaps = 0;
    
    /* Find the available visuals on the screen */
    vinfo_template.screen = screen;
    available_visuals = XGetVisualInfo(display, VisualScreenMask, &vinfo_template, &num_visuals);

    default_visualid = XVisualIDFromVisual(DefaultVisual(display, screen));

    /* Only try the specified visual */
    if ((visual_class != All) && (depth != All)) {
	v = 0;
	vinfo = NULL;
	while (!vinfo && (v < num_visuals))
	  if ((available_visuals[v].class == visual_class) &&
	      (available_visuals[v].depth == depth))
	    vinfo = &available_visuals[v];
	  else
	    v++;
	if (vinfo)
	  if (vinfo->visualid == default_visualid) {
	      fprintf(stderr, "%s: no need to create a colormap for the default visual\n",
		      prog_name);
	      exit(0);
	  } else 
	    alloc_cmap_for_visual(display, screen, vinfo);
    }   
    
    /* Try all visuals of visual_class with any depth */
    else if (visual_class != All) {
	for (v = 0; v < num_visuals; v++)
	  if ((visual_class == available_visuals[v].class) &&
	      (available_visuals[v].visualid != default_visualid))
	    alloc_cmap_for_visual(display, screen, &available_visuals[v]);
    }
    
    /* Try all visuals of depth and any dynamic class */
    else if (depth != All) {
	for (v = 0; v < num_visuals; v++)
	  if ((depth == available_visuals[v].depth) &&
	      DYNAMIC_VISUAL(available_visuals[v].class) &&
	      (available_visuals[v].visualid != default_visualid))
	    alloc_cmap_for_visual(display, screen, &available_visuals[v]);
    }

    /* Try all visuals */
    else 
      for (v = 0; v < num_visuals; v++)
	if (DYNAMIC_VISUAL(available_visuals[v].class) &&
	    (available_visuals[v].visualid != default_visualid))
	  alloc_cmap_for_visual(display, screen, &available_visuals[v]);
}


static void
alloc_cmap_for_visual(
    Display *display,
    int screen,
    XVisualInfo *vinfo)
{
    int c = 0;
    XStandardColormap *std_cmap = NULL;
    XStandardColormap new_cmap;
    
    if (verbose)
      (void)printf("  Creating a colormap for the %s %d bit visual...",
		   visual_class_name(vinfo->class), vinfo->depth);

    /* Check to see if one already exists */
    while (!std_cmap && (c < num_cmaps))
      if ((allocated_cmaps[c].visualid == vinfo->visualid) &&
	  (allocated_cmaps[c].red_max == 0) &&
	  (allocated_cmaps[c].red_mult == 0) &&
	  (allocated_cmaps[c].green_max == 0) &&
	  (allocated_cmaps[c].green_mult == 0) &&
	  (allocated_cmaps[c].blue_max == 0) &&
	  (allocated_cmaps[c].blue_mult == 0))
	std_cmap = &allocated_cmaps[c];
      else
	c++;

    if (std_cmap && !force && verbose)
      (void)printf("one already exists\n");
    else if (!std_cmap || force) {
	/* Create the colormap */
	create_colormap(display, vinfo, &new_cmap);

	/* append it to the property on the root window */
	XChangeProperty(display, RootWindow(display, screen),
			XA_RGB_DEFAULT_MAP, XA_RGB_COLOR_MAP,
			32, PropModeAppend, (unsigned char *)(&new_cmap),
			10);
	if (verbose) 
	  (void)printf("done\n    new colormap id = 0x%lx\n", new_cmap.colormap);
    }
}


static void
create_colormap(
    Display		*display,
    XVisualInfo		*vinfo,
    XStandardColormap	*std_colormap	/* RETURN */
    )
{
    Colormap colormap;
    XColor color;

    colormap = XCreateColormap(display, RootWindow(display, vinfo->screen),
			       vinfo->visual, AllocNone);

    /* Allocate black from the colormap */
    color.red = color.green = color.blue = 0;
    XAllocColor(display, colormap, &color);

    /* Fill out the standard colormap information */
    std_colormap->colormap = colormap;
    std_colormap->red_max = 0;
    std_colormap->red_mult = 0;
    std_colormap->green_max = 0;
    std_colormap->green_mult = 0;
    std_colormap->blue_max = 0;
    std_colormap->blue_mult = 0;
    std_colormap->base_pixel = color.pixel;
    std_colormap->visualid = vinfo->visualid;

    /* We don't want anybody pulling the colormap out from
     * under running clients, so set the killid to 0.
     */
    std_colormap->killid = 0;
    
    created_colormap = True;
}


static char *
visual_class_name(
    int         class)
{
    char *name;
    
    switch (class) {
      case StaticGray:
	name = "StaticGray";
	break;
      case GrayScale:
	name = "GrayScale";
	break;
      case StaticColor:
	name = "StaticColor";
	break;
      case PseudoColor:
	name = "PseudoColor";
	break;
      case TrueColor:
	name = "TrueColor";
	break;
      case DirectColor:	
	name = "DirectColor";
	break;
      default:
	name = "";
	break;
    }
    return name;
}


static void
parse_cmdline(
    int         argc,
    char      **argv)
{
    int option = 1;
    
    if (argc)
      prog_name = argv[0];
    
    while (option < argc) {
	if (!strcmp(argv[option], "-display"))
	  if (++option < argc)
	    display_name = argv[option];
	  else
	    usage();

	else if (!strcmp(argv[option], "-force"))
	  force = True;

	else if (!strcmp(argv[option], "-allscreens"))
	  all_screens = True;

	else if (!strcmp(argv[option], "-depth"))
	  if (++option < argc) {
	      depth = string_to_depth(argv[option]);
	      if (depth == All) {
		  fprintf(stderr, "%s: unknown depth %s\n", prog_name, argv[option]);
		  usage();
	      }
	  } else
	    usage();

	else if (!strcmp(argv[option], "-visual"))
	  if (++option < argc) {
	      visual_class = string_to_visual(argv[option]);
	      if (visual_class == All) {
		  fprintf(stderr, "%s: unknown visual class %s\n", prog_name, argv[option]);
		  usage();
	      } else if (!DYNAMIC_VISUAL(visual_class)) {
		  fprintf(stderr, "%s: no need to create a colormap for a static visual\n", prog_name);
		  exit(0);
	      }
	  } else
	    usage();

	else if (!strcmp(argv[option], "-verbose"))
	  verbose = True;

	else if (!strcmp(argv[option], "-help"))
	  usage();

	else {
	    (void)fprintf(stderr, "%s: unknown command line option \"%s\"\n", 
			  prog_name, argv[option]);
	    usage();
	}
	option++;
    }
}


static int
string_to_depth(const char *str)
{
    int depth;
    
    if ((sscanf(str, "%d", &depth) != 1) || (depth < 1))
      depth = All;

    return depth;
}


static int
string_to_visual(const char *str)
{
    int visual_class;
    
    if (!strcmp(str, "StaticGray"))
      visual_class = StaticGray;
    else if (!strcmp(str, "GrayScale"))
      visual_class = GrayScale;
    else if (!strcmp(str, "StaticColor"))
      visual_class = StaticColor;
    else if (!strcmp(str, "PseudoColor"))
      visual_class = PseudoColor;
    else if (!strcmp(str, "TrueColor"))
      visual_class = TrueColor;
    else if (!strcmp(str, "DirectColor"))
      visual_class = DirectColor;
    else 
      visual_class = All;

    return visual_class;
}


static void
usage(void)
{
    (void)fprintf(stderr, "Usage: %s [-display <display:n.screen>]\n", prog_name);
    (void)fprintf(stderr, "\t\t[-force] [-allscreens]\n");
    (void)fprintf(stderr, "\t\t[-depth <n>] [-visual <class>]\n");
    (void)fprintf(stderr, "\t\t[-verbose] [-help]\n");
    exit(0);
}

