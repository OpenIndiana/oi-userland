/*
 * $XConsortium: Mailbox.c,v 1.35 89/10/09 16:51:44 jim Exp $
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
 * I recommend that you use the new mailfull and mailempty bitmaps instead of
 * the ugly mailboxes:
 *
 *         XBiff*fullPixmap:  mailfull
 *         XBiff*emptyPixmap:  mailempty
 */

#include <stdio.h>			/* for printing error messages */
#include <pwd.h>			/* for getting username */

#include <X11/cursorfont.h>		/* for cursor constants */
#include <X11/StringDefs.h>		/* for useful atom names */
#include <X11/Intrinsic.h>		/* for XtTimerCallbackProc */
#include <X11/IntrinsicP.h>		/* for toolkit stuff */
#include <sys/stat.h>			/* for stat() ** needs types.h ***/

#include <X11/bitmaps/mailfull>		/* for flag up (mail present) bits */
#include <X11/bitmaps/mailempty>	/* for flag down (mail not here) */

#include <./Xaw3_1XawInit.h>
#include <./Xaw3_1MailboxP.h>		/* for implementation mailbox stuff */

#include <X11/Xmu/Converters.h>		/* for XmuCvtStringToBitmap */

#ifdef SHAPE
#include <X11/extensions/shape.h>
#endif

/*
 * The default user interface is to have the mailbox turn itself off whenever
 * the user presses a button in it.  Expert users might want to make this 
 * happen on EnterWindow.  It might be nice to provide support for some sort of
 * exit callback so that you can do things like press q to quit.
 */

static char defaultTranslations[] = 
  "<ButtonPress>:  unset()";

static void Check(), Set(), Unset();

static XtActionsRec actionsList[] = { 
    { "check",	Check },
    { "unset",	Unset },
    { "set",	Set },
};


/* Initialization of defaults */

#define offset(field) XtOffset(MailboxWidget,mailbox.field)
#define goffset(field) XtOffset(Widget,core.field)

static Dimension defDim = 48;
static Pixmap nopix = None;

static XtResource resources[] = {
    { XtNwidth, XtCWidth, XtRDimension, sizeof (Dimension), 
	goffset (width), XtRDimension, (caddr_t)&defDim },
    { XtNheight, XtCHeight, XtRDimension, sizeof (Dimension),
	goffset (height), XtRDimension, (caddr_t)&defDim },
    { XtNupdate, XtCInterval, XtRInt, sizeof (int),
	offset (update), XtRString, "30" },
    { XtNforeground, XtCForeground, XtRPixel, sizeof (Pixel),
	offset (foreground_pixel), XtRString, "black" },
    { XtNbackground, XtCBackground, XtRPixel, sizeof (Pixel),
	goffset (background_pixel), XtRString, "white" },
    { XtNreverseVideo, XtCReverseVideo, XtRBoolean, sizeof (Boolean),
	offset (reverseVideo), XtRString, "FALSE" },
    { XtNfile, XtCFile, XtRString, sizeof (String),
	offset (filename), XtRString, NULL },
    { XtNcheckCommand, XtCCheckCommand, XtRString, sizeof(char*),
	offset (check_command), XtRString, NULL},
    { XtNvolume, XtCVolume, XtRInt, sizeof(int),
	offset (volume), XtRString, "33"},
    { XtNonceOnly, XtCBoolean, XtRBoolean, sizeof(Boolean),
	offset (once_only), XtRImmediate, (caddr_t)False },
    { XtNfullPixmap, XtCPixmap, XtRBitmap, sizeof(Pixmap),
	offset (full.bitmap), XtRString, "flagup" },
    { XtNfullPixmapMask, XtCPixmapMask, XtRBitmap, sizeof(Pixmap),
	offset (full.mask), XtRBitmap, (caddr_t) &nopix },
    { XtNemptyPixmap, XtCPixmap, XtRBitmap, sizeof(Pixmap),
	offset (empty.bitmap), XtRString, "flagdown" },
    { XtNemptyPixmapMask, XtCPixmapMask, XtRBitmap, sizeof(Pixmap),
	offset (empty.mask), XtRBitmap, (caddr_t) &nopix },
    { XtNflip, XtCFlip, XtRBoolean, sizeof(Boolean),
	offset (flipit), XtRString, "true" },
#ifdef SHAPE
    { XtNshapeWindow, XtCShapeWindow, XtRBoolean, sizeof(Boolean),
        offset (shapeit), XtRString, "false" },
#endif
};

#undef offset
#undef goffset

static void GetMailFile(), CloseDown();
static void check_mailbox(), redraw_mailbox(), beep();
static void ClassInitialize(), Initialize(), Realize(), Destroy(), Redisplay();
static Boolean SetValues();

MailboxClassRec mailboxClassRec = {
    { /* core fields */
    /* superclass		*/	&widgetClassRec,
    /* class_name		*/	"Mailbox",
    /* widget_size		*/	sizeof(MailboxRec),
    /* class_initialize		*/	ClassInitialize,
    /* class_part_initialize	*/	NULL,
    /* class_inited		*/	FALSE,
    /* initialize		*/	Initialize,
    /* initialize_hook		*/	NULL,
    /* realize			*/	Realize,
    /* actions			*/	actionsList,
    /* num_actions		*/	XtNumber(actionsList),
    /* resources		*/	resources,
    /* resource_count		*/	XtNumber(resources),
    /* xrm_class		*/	NULL,
    /* compress_motion		*/	TRUE,
    /* compress_exposure	*/	TRUE,
    /* compress_enterleave	*/	TRUE,
    /* visible_interest		*/	FALSE,
    /* destroy			*/	Destroy,
    /* resize			*/	NULL,
    /* expose			*/	Redisplay,
    /* set_values		*/	SetValues,
    /* set_values_hook		*/	NULL,
    /* set_values_almost	*/	XtInheritSetValuesAlmost,
    /* get_values_hook		*/	NULL,
    /* accept_focus		*/	NULL,
    /* version			*/	XtVersion,
    /* callback_private		*/	NULL,
    /* tm_table			*/	defaultTranslations,
    /* query_geometry		*/	XtInheritQueryGeometry,
    /* display_accelerator	*/	XtInheritDisplayAccelerator,
    /* extension		*/	NULL
    }
};

WidgetClass mailboxWidgetClass = (WidgetClass) &mailboxClassRec;


/*
 * widget initialization
 */

static void ClassInitialize ()
{
    static XtConvertArgRec screenConvertArg[] = {
    { XtWidgetBaseOffset, (caddr_t) XtOffset(Widget, core.screen), sizeof(Screen *) }
    };

    XawInitializeWidgetSet();
    XtAddConverter (XtRString, XtRBitmap, XmuCvtStringToBitmap,
		    screenConvertArg, XtNumber(screenConvertArg));
    return;
}

static GC get_mailbox_gc (w)
    MailboxWidget w;
{
    XtGCMask valuemask;
    XGCValues xgcv;

    valuemask = GCForeground | GCBackground | GCFunction | GCGraphicsExposures;
    xgcv.foreground = w->mailbox.foreground_pixel;
    xgcv.background = w->core.background_pixel;
    xgcv.function = GXcopy;
    xgcv.graphics_exposures = False;	/* this is Bool, not Boolean */
    return (XtGetGC ((Widget) w, valuemask, &xgcv));
}


/* ARGSUSED */
static void Initialize (request, new)
    Widget request, new;
{
    MailboxWidget w = (MailboxWidget) new;
#ifdef SHAPE
    int shape_event_base, shape_error_base;
#endif

    if (!w->mailbox.filename) GetMailFile (w);

    if (w->core.width <= 0) w->core.width = 1;
    if (w->core.height <= 0) w->core.height = 1;

    if (w->mailbox.reverseVideo) {
	Pixel tmp;

	tmp = w->mailbox.foreground_pixel;
	w->mailbox.foreground_pixel = w->core.background_pixel;
	w->core.background_pixel = tmp;
    }

#ifdef SHAPE
    if (w->mailbox.shapeit && !XShapeQueryExtension (XtDisplay (w),
						     &shape_event_base,
						     &shape_error_base))
      w->mailbox.shapeit = False;
    w->mailbox.shape_cache.mask = None;
#endif

    w->mailbox.gc = get_mailbox_gc (w);
    w->mailbox.interval_id = (XtIntervalId) 0;
    w->mailbox.full.pixmap = None;
    w->mailbox.empty.pixmap = None;

    return;
}


/*
 * action procedures
 */

/*
 * pretend there is new mail; put widget in flagup state
 */

/* ARGSUSED */
static void Set (gw, event, params, nparams)
    Widget gw;
    XEvent *event;
    String *params;
    Cardinal *nparams;
{
    MailboxWidget w = (MailboxWidget) gw;

    w->mailbox.last_size = -1;

    check_mailbox (w, TRUE, FALSE);	/* redraw, no reset */

    return;
}


/*
 * ack the existing mail; put widget in flagdown state
 */

/* ARGSUSED */
static void Unset (gw, event, params, nparams)
    Widget gw;
    XEvent *event;
    String *params;
    Cardinal *nparams;
{
    MailboxWidget w = (MailboxWidget) gw;

    check_mailbox (w, TRUE, TRUE);	/* redraw, reset */

    return;
}


/*
 * look to see if there is new mail; if so, Set, else Unset
 */

/* ARGSUSED */
static void Check (gw, event, params, nparams)
    Widget gw;
    XEvent *event;
    String *params;
    Cardinal *nparams;
{
    MailboxWidget w = (MailboxWidget) gw;

    check_mailbox (w, TRUE, FALSE);	/* redraw, no reset */

    return;
}


/* ARGSUSED */
static XtTimerCallbackProc clock_tic (client_data, id)
    caddr_t client_data;
    XtIntervalId *id;
{
    MailboxWidget w = (MailboxWidget) client_data;

    check_mailbox (w, FALSE, FALSE);	/* no redraw, no reset */

    /*
     * and reset the timer
     */

    w->mailbox.interval_id = XtAddTimeOut (w->mailbox.update * 1000,
					   (XtTimerCallbackProc)clock_tic,
					   (caddr_t) w);

    return;
}

static Pixmap make_pixmap (dpy, w, bitmap, depth, flip, widthp, heightp)
    Display *dpy;
    MailboxWidget w;
    Pixmap bitmap;
    Boolean flip;
    int depth;
    int *widthp, *heightp;
{
    Window root;
    int x, y;
    unsigned int width, height, bw, dep;
    unsigned long fore, back;

    if (!XGetGeometry (dpy, bitmap, &root, &x, &y, &width, &height, &bw, &dep))
      return None;

    *widthp = (int) width;
    *heightp = (int) height;
    if (flip) {
	fore = w->core.background_pixel;
	back = w->mailbox.foreground_pixel;
    } else {
	fore = w->mailbox.foreground_pixel;
	back = w->core.background_pixel;
    }
    return XmuCreatePixmapFromBitmap (dpy, w->core.window, bitmap, 
				      width, height, depth, fore, back);
}

static void Realize (gw, valuemaskp, attr)
    Widget gw;
    XtValueMask *valuemaskp;
    XSetWindowAttributes *attr;
{
    MailboxWidget w = (MailboxWidget) gw;
    register Display *dpy = XtDisplay (w);
    int depth = w->core.depth;

    *valuemaskp |= (CWBitGravity | CWCursor);
    attr->bit_gravity = ForgetGravity;
    attr->cursor = XCreateFontCursor (dpy, XC_top_left_arrow);

    XtCreateWindow (gw, InputOutput, (Visual *) CopyFromParent,
		    *valuemaskp, attr);

    /*
     * build up the pixmaps that we'll put into the image
     */
    if (w->mailbox.full.bitmap == None) {
	w->mailbox.full.bitmap = 
	  XCreateBitmapFromData (dpy, w->core.window,
	  			 (const char *)mailfull_bits,
				 mailfull_width, mailfull_height);
    }
    if (w->mailbox.empty.bitmap == None) {
	w->mailbox.empty.bitmap =
	  XCreateBitmapFromData (dpy, w->core.window,
	  			 (const char *)mailempty_bits,
				 mailempty_width, mailempty_height);
    }

    w->mailbox.empty.pixmap = make_pixmap (dpy, w, w->mailbox.empty.bitmap,
					   depth, False,
					   &w->mailbox.empty.width,
					   &w->mailbox.empty.height);
    w->mailbox.full.pixmap = make_pixmap (dpy, w, w->mailbox.full.bitmap,
					  depth, w->mailbox.flipit,
					  &w->mailbox.full.width,
					  &w->mailbox.full.height);
			 
#ifdef SHAPE
    if (w->mailbox.empty.mask == None && w->mailbox.full.mask == None)
      w->mailbox.shapeit = False;
#endif

    w->mailbox.interval_id = XtAddTimeOut (w->mailbox.update * 1000,
					   (XtTimerCallbackProc)clock_tic,
					   (caddr_t) w);

#ifdef SHAPE
    w->mailbox.shape_cache.mask = None;
#endif

    return;
}


static void Destroy (gw)
    Widget gw;
{
    MailboxWidget w = (MailboxWidget) gw;
    Display *dpy = XtDisplay (gw);

    XtFree (w->mailbox.filename);
    if (w->mailbox.interval_id) XtRemoveTimeOut (w->mailbox.interval_id);
    XtDestroyGC (w->mailbox.gc);
#define freepix(p) if (p) XFreePixmap (dpy, p)
    freepix (w->mailbox.full.bitmap);		/* until cvter does ref cnt */
    freepix (w->mailbox.full.mask);		/* until cvter does ref cnt */
    freepix (w->mailbox.full.pixmap);
    freepix (w->mailbox.empty.bitmap);		/* until cvter does ref cnt */
    freepix (w->mailbox.empty.mask);		/* until cvter does ref cnt */
    freepix (w->mailbox.empty.pixmap);
#ifdef SHAPE
    freepix (w->mailbox.shape_cache.mask);
#endif
#undef freepix
    return;
}


static void Redisplay (gw)
    Widget gw;
{
    MailboxWidget w = (MailboxWidget) gw;

    check_mailbox (w, TRUE, FALSE);
}


static void check_mailbox (w, force_redraw, reset)
    MailboxWidget w;
    Boolean force_redraw, reset;
{
    long mailboxsize = 0;

    if (w->mailbox.check_command != NULL) {
	switch (system(w->mailbox.check_command)) {
	  case 0:
	    mailboxsize = w->mailbox.last_size + 1;
	    break;
	  /* case 1 is no change */
	  case 2:
	    mailboxsize = 0;
	  /* treat everything else as no change */
	}
    }
    else {
	struct stat st;

	if (stat (w->mailbox.filename, &st) == 0) {
	    mailboxsize = st.st_size;
	}
    }

    /*
     * Now check for changes.  If reset is set then we want to pretent that
     * there is no mail.  If the mailbox is empty then we want to turn off
     * the flag.  Otherwise if the mailbox has changed size then we want to
     * put the flag up.
     *
     * The cases are:
     *    o  forced reset by user                        DOWN
     *    o  no mailbox or empty (zero-sized) mailbox    DOWN
     *    o  same size as last time                      no change
     *    o  bigger than last time                       UP
     *    o  smaller than last time but non-zero         UP
     *
     * The last two cases can be expressed as different from last
     * time and non-zero.
     */

    if (reset) {			/* forced reset */
	w->mailbox.flag_up = FALSE;
	force_redraw = TRUE;
    } else if (mailboxsize == 0) {	/* no mailbox or empty */
	w->mailbox.flag_up = FALSE;
	if (w->mailbox.last_size > 0) force_redraw = TRUE;  /* if change */
    } else if (mailboxsize != w->mailbox.last_size) {  /* different size */
	if (!w->mailbox.once_only || !w->mailbox.flag_up)
	    beep(w); 
	w->mailbox.flag_up = TRUE;
	force_redraw = TRUE;
    } 

    w->mailbox.last_size = mailboxsize;
    if (force_redraw) redraw_mailbox (w);
    return;
}

/*
 * get user name for building mailbox
 */

static void GetMailFile (w)
    MailboxWidget w;
{
    char *getlogin();
    char *username;

    username = getlogin ();
    if (!username) {
	struct passwd *pw = getpwuid (getuid ());

	if (!pw) {
	    fprintf (stderr, "%s:  unable to find a username for you.\n",
		     "Mailbox widget");
	    CloseDown (w, 1);
	}
	username = pw->pw_name;
    }
    w->mailbox.filename = (String) XtMalloc (strlen (MAILBOX_DIRECTORY) + 1 +
				   	     strlen (username) + 1);
    strcpy (w->mailbox.filename, MAILBOX_DIRECTORY);
    strcat (w->mailbox.filename, "/");
    strcat (w->mailbox.filename, username);
    return;
}

static void CloseDown (w, status)
    MailboxWidget w;
    int status;
{
    Display *dpy = XtDisplay (w);

    XtDestroyWidget ((Widget)w);
    XCloseDisplay (dpy);
    exit (status);
}


/* ARGSUSED */
static Boolean SetValues (gcurrent, grequest, gnew)
    Widget gcurrent, grequest, gnew;
{
    MailboxWidget current = (MailboxWidget) gcurrent;
    MailboxWidget new = (MailboxWidget) gnew;
    Boolean redisplay = FALSE;

    if (current->mailbox.update != new->mailbox.update) {
	if (current->mailbox.interval_id) 
	  XtRemoveTimeOut (current->mailbox.interval_id);
	new->mailbox.interval_id = XtAddTimeOut (new->mailbox.update * 1000,
						 (XtTimerCallbackProc)clock_tic,
						 (caddr_t) gnew);
    }

    if (current->mailbox.foreground_pixel != new->mailbox.foreground_pixel ||
	current->core.background_pixel != new->core.background_pixel) {
	XtDestroyGC (current->mailbox.gc);
	new->mailbox.gc = get_mailbox_gc (new);
	redisplay = TRUE;
    }

    return (redisplay);
}


/*
 * drawing code
 */

static void redraw_mailbox (w)
    MailboxWidget w;
{
    register Display *dpy = XtDisplay (w);
    register Window win = XtWindow (w);
    register int x, y;
    GC gc = w->mailbox.gc;
    Pixel back = w->core.background_pixel;
    struct _mbimage *im;

    /* center the picture in the window */

    if (w->mailbox.flag_up) {		/* paint the "up" position */
	im = &w->mailbox.full;
	if (w->mailbox.flipit) back = w->mailbox.foreground_pixel;
    } else {				/* paint the "down" position */
	im = &w->mailbox.empty;
    }
    x = (((int)w->core.width) - im->width) / 2;
    y = (((int)w->core.height) - im->height) / 2;

    XSetWindowBackground (dpy, win, back);
    XClearWindow (dpy, win);
    XCopyArea (dpy, im->pixmap, win, gc, 0, 0, im->width, im->height, x, y);

#ifdef SHAPE
    /*
     * XXX - temporary hack; walk up widget tree to find top most parent (which
     * will be a shell) and mash it to have our shape.  This will be replaced
     * by a special shell widget.
     */
    if (w->mailbox.shapeit) {
	Widget parent;

	for (parent = (Widget) w; XtParent(parent);
	     parent = XtParent(parent)) {
	    x += parent->core.x + parent->core.border_width;
	    y += parent->core.y + parent->core.border_width;
	}

	if (im->mask != w->mailbox.shape_cache.mask ||
	    x != w->mailbox.shape_cache.x || y != w->mailbox.shape_cache.y) {
	    XShapeCombineMask (XtDisplay(parent), XtWindow(parent),
			       ShapeBounding, x, y, im->mask, ShapeSet);
	    w->mailbox.shape_cache.mask = im->mask;
	    w->mailbox.shape_cache.x = x;
	    w->mailbox.shape_cache.y = y;
	}
    }
#endif

    return;
}


static void beep (w)
    MailboxWidget w;
{
    XBell (XtDisplay (w), w->mailbox.volume);
    return;
}
