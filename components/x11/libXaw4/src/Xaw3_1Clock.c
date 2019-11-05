#ifndef lint
static char Xrcsid[] = "$XConsortium: Clock.c,v 1.50 89/12/06 15:23:24 kit Exp $";
#endif /* lint */


/***********************************************************
Copyright 1987, 1988 by Digital Equipment Corporation, Maynard, Massachusetts,
and the Massachusetts Institute of Technology, Cambridge, Massachusetts.

                        All Rights Reserved

Permission to use, copy, modify, and distribute this software and its 
documentation for any purpose and without fee is hereby granted, 
provided that the above copyright notice appear in all copies and that
both that copyright notice and this permission notice appear in 
supporting documentation, and that the names of Digital or MIT not be
used in advertising or publicity pertaining to distribution of the
software without specific, written prior permission.  

DIGITAL DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING
ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO EVENT SHALL
DIGITAL BE LIABLE FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR
ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,
ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS
SOFTWARE.

******************************************************************/

#include <time.h>

#include <X11/Xlib.h>
#include <X11/StringDefs.h>
#include <X11/IntrinsicP.h>
#include <./Xaw3_1XawInit.h>
#include <./Xaw3_1ClockP.h>

extern long time();
static void clock_tic(), DrawHand(), DrawSecond(), SetSeg(), DrawClockFace();
static void erase_hands();
static      round();
	
/* Private Definitions */

#define VERTICES_IN_HANDS	6	/* to draw triangle */
#define PI			3.14159265358979
#define TWOPI			(2. * PI)

#define SECOND_HAND_FRACT	90
#define MINUTE_HAND_FRACT	70
#define HOUR_HAND_FRACT		40
#define HAND_WIDTH_FRACT	7
#define SECOND_WIDTH_FRACT	5
#define SECOND_HAND_TIME	30

#define ANALOG_SIZE_DEFAULT	164

#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))
#define abs(a) ((a) < 0 ? -(a) : (a))


/* Initialization of defaults */

#define offset(field) XtOffset(ClockWidget,clock.field)
#define goffset(field) XtOffset(Widget,core.field)

static XtResource resources[] = {
    {XtNwidth, XtCWidth, XtRDimension, sizeof(Dimension),
	goffset(width), XtRImmediate, (caddr_t) 0},
    {XtNheight, XtCHeight, XtRDimension, sizeof(Dimension),
	goffset(height), XtRImmediate, (caddr_t) 0},
    {XtNbackground, XtCBackground, XtRPixel, sizeof(Pixel),
	goffset(background_pixel), XtRString, "XtdefaultBackground"},
    {XtNupdate, XtCInterval, XtRInt, sizeof(int), 
        offset(update), XtRImmediate, (caddr_t) 60 },
    {XtNforeground, XtCForeground, XtRPixel, sizeof(Pixel),
        offset(fgpixel), XtRString, "XtdefaultForeground"},
    {XtNhand, XtCForeground, XtRPixel, sizeof(Pixel),
        offset(Hdpixel), XtRString, "XtdefaultForeground"},
    {XtNhighlight, XtCForeground, XtRPixel, sizeof(Pixel),
        offset(Hipixel), XtRString, "XtdefaultForeground"},
    {XtNanalog, XtCBoolean, XtRBoolean, sizeof(Boolean),
        offset(analog), XtRImmediate, (caddr_t) TRUE},
    {XtNchime, XtCBoolean, XtRBoolean, sizeof(Boolean),
	offset(chime), XtRImmediate, (caddr_t) FALSE },
    {XtNpadding, XtCMargin, XtRInt, sizeof(int),
        offset(padding), XtRImmediate, (caddr_t) 8},
    {XtNfont, XtCFont, XtRFontStruct, sizeof(XFontStruct *),
        offset(font), XtRString, "fixed"},
    {XtNreverseVideo, XtCReverseVideo, XtRBoolean, sizeof (Boolean),
	offset (reverse_video), XtRImmediate, (caddr_t) FALSE},
    {XtNbackingStore, XtCBackingStore, XtRBackingStore, sizeof (int),
    	offset (backing_store), XtRString, "default"},
};

#undef offset
#undef goffset

static void ClassInitialize();
static void Initialize(), Realize(), Destroy(), Resize(), Redisplay();
static Boolean SetValues();

ClockClassRec clockClassRec = {
    { /* core fields */
    /* superclass		*/	&widgetClassRec,
    /* class_name		*/	"Clock",
    /* widget_size		*/	sizeof(ClockRec),
    /* class_initialize		*/	ClassInitialize,
    /* class_part_initialize	*/	NULL,
    /* class_inited		*/	FALSE,
    /* initialize		*/	Initialize,
    /* initialize_hook		*/	NULL,
    /* realize			*/	Realize,
    /* actions			*/	NULL,
    /* num_actions		*/	0,
    /* resources		*/	resources,
    /* resource_count		*/	XtNumber(resources),
    /* xrm_class		*/	NULL,
    /* compress_motion		*/	TRUE,
    /* compress_exposure	*/	TRUE,
    /* compress_enterleave	*/	TRUE,
    /* visible_interest		*/	FALSE,
    /* destroy			*/	Destroy,
    /* resize			*/	Resize,
    /* expose			*/	Redisplay,
    /* set_values		*/	SetValues,
    /* set_values_hook		*/	NULL,
    /* set_values_almost	*/	XtInheritSetValuesAlmost,
    /* get_values_hook		*/	NULL,
    /* accept_focus		*/	NULL,
    /* version			*/	XtVersion,
    /* callback_private		*/	NULL,
    /* tm_table			*/	NULL,
    /* query_geometry           */	XtInheritQueryGeometry,
    /* display_accelerator      */	XtInheritDisplayAccelerator,
    /* extension                */	NULL
    }
};

WidgetClass clockWidgetClass = (WidgetClass) &clockClassRec;

/****************************************************************
 *
 * Private Procedures
 *
 ****************************************************************/

static void ClassInitialize()
{
    XawInitializeWidgetSet();
    XtAddConverter( XtRString, XtRBackingStore, XmuCvtStringToBackingStore,
		    NULL, 0 );
}

/* ARGSUSED */
static void Initialize (request, new)
    Widget request, new;
{
    ClockWidget w = (ClockWidget)new;
    XtGCMask		valuemask;
    XGCValues	myXGCV;
    int min_height, min_width;

    valuemask = GCForeground | GCBackground | GCFont | GCLineWidth;
    if (w->clock.font != NULL)
        myXGCV.font = w->clock.font->fid;
    else
        valuemask &= ~GCFont;	/* use server default font */

    min_width = min_height = ANALOG_SIZE_DEFAULT;
    if(!w->clock.analog) {
       char *str;
       struct tm tm;
       long time_value;
       (void) time(&time_value);
       tm = *localtime(&time_value);
       str = asctime(&tm);
       if (w->clock.font == NULL)
          w->clock.font = XQueryFont( XtDisplay(w),
				      XGContextFromGC(
					   DefaultGCOfScreen(XtScreen(w))) );
       min_width = XTextWidth(w->clock.font, str, strlen(str)) +
	  2 * w->clock.padding;
       min_height = w->clock.font->ascent +
	  w->clock.font->descent + 2 * w->clock.padding;
    }
    if (w->core.width == 0)
	w->core.width = min_width;
    if (w->core.height == 0)
	w->core.height = min_height;

    myXGCV.foreground = w->clock.fgpixel;
    myXGCV.background = w->core.background_pixel;
    if (w->clock.font != NULL)
        myXGCV.font = w->clock.font->fid;
    else
        valuemask &= ~GCFont;	/* use server default font */
    myXGCV.line_width = 0;
    w->clock.myGC = XtGetGC((Widget)w, valuemask, &myXGCV);

    valuemask = GCForeground | GCLineWidth ;
    myXGCV.foreground = w->core.background_pixel;
    w->clock.EraseGC = XtGetGC((Widget)w, valuemask, &myXGCV);

    myXGCV.foreground = w->clock.Hipixel;
    w->clock.HighGC = XtGetGC((Widget)w, valuemask, &myXGCV);

    valuemask = GCForeground;
    myXGCV.foreground = w->clock.Hdpixel;
    w->clock.HandGC = XtGetGC((Widget)w, valuemask, &myXGCV);

    if (w->clock.update <= 0)
	w->clock.update = 60;	/* make invalid update's use a default */
    w->clock.show_second_hand = (w->clock.update <= SECOND_HAND_TIME);
    w->clock.numseg = 0;
    w->clock.interval_id = 0;
}

static void Realize (gw, valueMask, attrs)
     Widget gw;
     XtValueMask *valueMask;
     XSetWindowAttributes *attrs;
{
     ClockWidget	w = (ClockWidget) gw;
#ifdef notdef
     *valueMask |= CWBitGravity;
     attrs->bit_gravity = ForgetGravity;
#endif
     switch (w->clock.backing_store) {
     case Always:
     case NotUseful:
     case WhenMapped:
     	*valueMask |=CWBackingStore;
	attrs->backing_store = w->clock.backing_store;
	break;
     }
     XtCreateWindow( gw, InputOutput, (Visual *)CopyFromParent,
		     *valueMask, attrs);
     Resize(gw);
}

static void Destroy (gw)
     Widget gw;
{
     ClockWidget w = (ClockWidget) gw;
     if (w->clock.interval_id) XtRemoveTimeOut (w->clock.interval_id);
     XtDestroyGC (w->clock.myGC);
     XtDestroyGC (w->clock.HighGC);
     XtDestroyGC (w->clock.HandGC);
     XtDestroyGC (w->clock.EraseGC);
}

static void Resize (gw) 
    Widget gw;
{
    ClockWidget w = (ClockWidget) gw;
    /* don't do this computation if window hasn't been realized yet. */
    if (XtIsRealized(gw) && w->clock.analog) {
	/* need signed value since Dimension is unsigned */
	int radius = ((int) min(w->core.width, w->core.height) - (int) (2 * w->clock.padding)) / 2;
        w->clock.radius = (Dimension) max (radius, 1);

        w->clock.second_hand_length = ((SECOND_HAND_FRACT * w->clock.radius) / 100);
        w->clock.minute_hand_length = ((MINUTE_HAND_FRACT * w->clock.radius) / 100);
        w->clock.hour_hand_length = ((HOUR_HAND_FRACT * w->clock.radius) / 100);
        w->clock.hand_width = ((HAND_WIDTH_FRACT * w->clock.radius) / 100);
        w->clock.second_hand_width = ((SECOND_WIDTH_FRACT * w->clock.radius) / 100);

        w->clock.centerX = w->core.width / 2;
        w->clock.centerY = w->core.height / 2;
    }
}

/* ARGSUSED */
static void Redisplay (gw, event, region)
    Widget gw;
    XEvent *event;		/* unused */
    Region region;		/* unused */
{
    ClockWidget w = (ClockWidget) gw;
    if (w->clock.analog) {
	if (w->clock.numseg != 0)
	    erase_hands (w, (struct tm *) 0);
        DrawClockFace(w);
    } else {
	w->clock.prev_time_string[0] = '\0';
    }
    clock_tic((caddr_t)w, (XtIntervalId)0);
}

/* ARGSUSED */
static void clock_tic(client_data, id)
        caddr_t client_data;
        XtIntervalId *id;
{
        ClockWidget w = (ClockWidget)client_data;    
	struct tm tm; 
	long	time_value;
	char	*time_ptr;
        register Display *dpy = XtDisplay(w);
        register Window win = XtWindow(w);

	if (id || !w->clock.interval_id)
	    w->clock.interval_id =
		XtAppAddTimeOut( XtWidgetToApplicationContext( (Widget) w),
				w->clock.update*1000,
				(XtTimerCallbackProc)clock_tic, (caddr_t)w );
	(void) time(&time_value);
	tm = *localtime(&time_value);
	/*
	 * Beep on the half hour; double-beep on the hour.
	 */
	if (w->clock.chime == TRUE) {
	    if (w->clock.beeped && (tm.tm_min != 30) &&
		(tm.tm_min != 0))
	      w->clock.beeped = FALSE;
	    if (((tm.tm_min == 30) || (tm.tm_min == 0)) 
		&& (!w->clock.beeped)) {
		w->clock.beeped = TRUE;
		XBell(dpy, 50);	
		if (tm.tm_min == 0)
		  XBell(dpy, 50);
	    }
	}
	if( w->clock.analog == FALSE ) {
	    int	clear_from;
	    int i, len, prev_len;

	    time_ptr = asctime(&tm);
	    len = strlen (time_ptr);
	    if (time_ptr[len - 1] == '\n') time_ptr[--len] = '\0';
	    prev_len = strlen (w->clock.prev_time_string);
	    for (i = 0; ((i < len) && (i < prev_len) && 
	    		 (w->clock.prev_time_string[i] == time_ptr[i])); i++);
	    strcpy (w->clock.prev_time_string+i, time_ptr+i);

	    XDrawImageString (dpy, win, w->clock.myGC,
			      (2+w->clock.padding +
			       XTextWidth (w->clock.font, time_ptr, i)),
			      2+w->clock.font->ascent+w->clock.padding,
			      time_ptr + i, len - i);
	    /*
	     * Clear any left over bits
	     */
	    clear_from = XTextWidth (w->clock.font, time_ptr, len)
 	    		+ 2 + w->clock.padding;
	    if (clear_from < w->core.width)
		XFillRectangle (dpy, win, w->clock.EraseGC,
		    clear_from, 0, w->core.width - clear_from, w->core.height);
	} else {
			/*
			 * The second (or minute) hand is sec (or min) 
			 * sixtieths around the clock face. The hour hand is
			 * (hour + min/60) twelfths of the way around the
			 * clock-face.  The derivation is left as an excercise
			 * for the reader.
			 */

			/*
			 * 12 hour clock.
			 */
			if(tm.tm_hour > 12)
				tm.tm_hour -= 12;

			erase_hands (w, &tm);

		    if (w->clock.numseg == 0 ||
			tm.tm_min != w->clock.otm.tm_min ||
			tm.tm_hour != w->clock.otm.tm_hour) {
			    w->clock.segbuffptr = w->clock.segbuff;
			    w->clock.numseg = 0;
			    /*
			     * Calculate the hour hand, fill it in with its
			     * color and then outline it.  Next, do the same
			     * with the minute hand.  This is a cheap hidden
			     * line algorithm.
			     */
			    DrawHand(w,
				w->clock.minute_hand_length, w->clock.hand_width,
				((double) tm.tm_min)/60.0
			    );
			    if(w->clock.Hdpixel != w->core.background_pixel)
				XFillPolygon( dpy,
				    win, w->clock.HandGC,
				    w->clock.segbuff, VERTICES_IN_HANDS,
				    Convex, CoordModeOrigin
				);
			    XDrawLines( dpy,
				win, w->clock.HighGC,
				w->clock.segbuff, VERTICES_IN_HANDS,
				       CoordModeOrigin);
			    w->clock.hour = w->clock.segbuffptr;
			    DrawHand(w, 
				w->clock.hour_hand_length, w->clock.hand_width,
				((((double)tm.tm_hour) + 
				    (((double)tm.tm_min)/60.0)) / 12.0)
			    );
			    if(w->clock.Hdpixel != w->core.background_pixel) {
			      XFillPolygon(dpy,
					   win, w->clock.HandGC,
					   w->clock.hour,
					   VERTICES_IN_HANDS,
					   Convex, CoordModeOrigin
					   );
			    }
			    XDrawLines( dpy,
				       win, w->clock.HighGC,
				       w->clock.hour, VERTICES_IN_HANDS,
				       CoordModeOrigin );

			    w->clock.sec = w->clock.segbuffptr;
		    }
		    if (w->clock.show_second_hand == TRUE) {
			    w->clock.segbuffptr = w->clock.sec;
			    DrawSecond(w,
				w->clock.second_hand_length - 2, 
				w->clock.second_hand_width,
				w->clock.minute_hand_length + 2,
				((double) tm.tm_sec)/60.0
			    );
			    if(w->clock.Hdpixel != w->core.background_pixel)
				XFillPolygon( dpy,
				    win, w->clock.HandGC,
				    w->clock.sec,
				    VERTICES_IN_HANDS -2,
				    Convex, CoordModeOrigin
			    );
			    XDrawLines( dpy,
				       win, w->clock.HighGC,
				       w->clock.sec,
				       VERTICES_IN_HANDS-1,
				       CoordModeOrigin
				        );

			}
			w->clock.otm = tm;
		}
}
	
static void erase_hands (w, tm)
ClockWidget	w;
struct tm	*tm;
{
    /*
     * Erase old hands.
     */
    if(w->clock.numseg > 0) {
	Display	*dpy;
	Window	win;

	dpy = XtDisplay (w);
	win = XtWindow (w);
	if (w->clock.show_second_hand == TRUE) {
	    XDrawLines(dpy, win,
		w->clock.EraseGC,
		w->clock.sec,
		VERTICES_IN_HANDS-1,
		CoordModeOrigin);
	    if(w->clock.Hdpixel != w->core.background_pixel) {
		XFillPolygon(dpy,
			win, w->clock.EraseGC,
			w->clock.sec,
			VERTICES_IN_HANDS-2,
			Convex, CoordModeOrigin
			);
	    }
	}
	if(!tm || tm->tm_min != w->clock.otm.tm_min ||
		  tm->tm_hour != w->clock.otm.tm_hour)
 	{
	    XDrawLines( dpy, win,
			w->clock.EraseGC,
			w->clock.segbuff,
			VERTICES_IN_HANDS,
			CoordModeOrigin);
	    XDrawLines( dpy, win,
			w->clock.EraseGC,
			w->clock.hour,
			VERTICES_IN_HANDS,
			CoordModeOrigin);
	    if(w->clock.Hdpixel != w->core.background_pixel) {
		XFillPolygon( dpy, win,
 			      w->clock.EraseGC,
			      w->clock.segbuff, VERTICES_IN_HANDS,
			      Convex, CoordModeOrigin);
		XFillPolygon( dpy, win,
 			      w->clock.EraseGC,
			      w->clock.hour,
			      VERTICES_IN_HANDS,
			      Convex, CoordModeOrigin);
	    }
	}
    }
}

/*
 * DrawLine - Draws a line.
 *
 * blank_length is the distance from the center which the line begins.
 * length is the maximum length of the hand.
 * Fraction_of_a_circle is a fraction between 0 and 1 (inclusive) indicating
 * how far around the circle (clockwise) from high noon.
***** Note: in this routine, fraction_of_a_circle is actually the minute
*****  tic we are drawing, 0 through 59.  This is due to a Solaris 2.0
*****  compiler bug I was not able to work around any other way. C'est la vie.
 *
 *
 * The blank_length feature is because I wanted to draw tick-marks around the
 * circle (for seconds).  The obvious means of drawing lines from the center
 * to the perimeter, then erasing all but the outside most pixels doesn't
 * work because of round-off error (sigh).
 */
static void DrawLine(w, blank_length, length, fraction_of_a_circle)
ClockWidget w;
Dimension blank_length;
Dimension length;
int fraction_of_a_circle;
{
	double dblank_length = (double)blank_length, dlength = (double)length;
	double angle, cosangle, sinangle;
	double cos();
	double sin();
	int cx = w->clock.centerX, cy = w->clock.centerY, x1, y1, x2, y2;

	/*
	 *  A full circle is 2 PI radians.
	 *  Angles are measured from 12 o'clock, clockwise increasing.
	 *  Since in X, +x is to the right and +y is downward:
	 *
	 *	x = x0 + r * sin(theta)
	 *	y = y0 - r * cos(theta)
	 *
	 */
	angle = TWOPI * (double) fraction_of_a_circle / 60. ;
	cosangle = cos(angle);
	sinangle = sin(angle);

	/* break this out so that stupid compilers can cope */
	x1 = cx + (int)(dblank_length * sinangle);
	y1 = cy - (int)(dblank_length * cosangle);
	x2 = cx + (int)(dlength * sinangle);
	y2 = cy - (int)(dlength * cosangle);
	SetSeg(w, x1, y1, x2, y2);
}

/*
 * DrawHand - Draws a hand.
 *
 * length is the maximum length of the hand.
 * width is the half-width of the hand.
 * Fraction_of_a_circle is a fraction between 0 and 1 (inclusive) indicating
 * how far around the circle (clockwise) from high noon.
 *
 */
static void DrawHand(w, length, width, fraction_of_a_circle)
ClockWidget w;
Dimension length, width;
double fraction_of_a_circle;
{

	register double angle, cosangle, sinangle;
	register double ws, wc;
	Position x, y, x1, y1, x2, y2;
	double cos();
	double sin();

	/*
	 *  A full circle is 2 PI radians.
	 *  Angles are measured from 12 o'clock, clockwise increasing.
	 *  Since in X, +x is to the right and +y is downward:
	 *
	 *	x = x0 + r * sin(theta)
	 *	y = y0 - r * cos(theta)
	 *
	 */
	angle = TWOPI * fraction_of_a_circle;
	cosangle = cos(angle);
	sinangle = sin(angle);
	/*
	 * Order of points when drawing the hand.
	 *
	 *		1,4
	 *		/ \
	 *	       /   \
	 *	      /     \
	 *	    2 ------- 3
	 */
	wc = width * cosangle;
	ws = width * sinangle;
	SetSeg(w,
	       x = w->clock.centerX + round(length * sinangle),
	       y = w->clock.centerY - round(length * cosangle),
	       x1 = w->clock.centerX - round(ws + wc), 
	       y1 = w->clock.centerY + round(wc - ws));  /* 1 ---- 2 */
	/* 2 */
	SetSeg(w, x1, y1, 
	       x2 = w->clock.centerX - round(ws - wc), 
	       y2 = w->clock.centerY + round(wc + ws));  /* 2 ----- 3 */

	SetSeg(w, x2, y2, x, y);	/* 3 ----- 1(4) */
}

/*
 * DrawSecond - Draws the second hand (diamond).
 *
 * length is the maximum length of the hand.
 * width is the half-width of the hand.
 * offset is direct distance from center to tail end.
 * Fraction_of_a_circle is a fraction between 0 and 1 (inclusive) indicating
 * how far around the circle (clockwise) from high noon.
 *
 */
static void DrawSecond(w, length, width, offset, fraction_of_a_circle)
ClockWidget w;
Dimension length, width, offset;
double fraction_of_a_circle;
{

	register double angle, cosangle, sinangle;
	register double ms, mc, ws, wc;
	register int mid;
	Position x, y;
	double cos();
	double sin();

	/*
	 *  A full circle is 2 PI radians.
	 *  Angles are measured from 12 o'clock, clockwise increasing.
	 *  Since in X, +x is to the right and +y is downward:
	 *
	 *	x = x0 + r * sin(theta)
	 *	y = y0 - r * cos(theta)
	 *
	 */
	angle = TWOPI * fraction_of_a_circle;
	cosangle = cos(angle);
	sinangle = sin(angle);
	/*
	 * Order of points when drawing the hand.
	 *
	 *		1,5
	 *		/ \
	 *	       /   \
	 *	      /     \
	 *	    2<       >4
	 *	      \     /
	 *	       \   /
	 *		\ /
	 *	-	 3
	 *	|
	 *	|
	 *   offset
	 *	|
	 *	|
	 *	-	 + center
	 */

	mid = (length + offset) / 2;
	mc = mid * cosangle;
	ms = mid * sinangle;
	wc = width * cosangle;
	ws = width * sinangle;
	/*1 ---- 2 */
	SetSeg(w,
	       x = w->clock.centerX + round(length * sinangle),
	       y = w->clock.centerY - round(length * cosangle),
	       w->clock.centerX + round(ms - wc),
	       w->clock.centerY - round(mc + ws) );
	SetSeg(w, w->clock.centerX + round(offset *sinangle),
	       w->clock.centerY - round(offset * cosangle), /* 2-----3 */
	       w->clock.centerX + round(ms + wc), 
	       w->clock.centerY - round(mc - ws));
	w->clock.segbuffptr->x = x;
	w->clock.segbuffptr++->y = y;
	w->clock.numseg ++;
}

static void SetSeg(w, x1, y1, x2, y2)
ClockWidget w;
int x1, y1, x2, y2;
{
	w->clock.segbuffptr->x = x1;
	w->clock.segbuffptr++->y = y1;
	w->clock.segbuffptr->x = x2;
	w->clock.segbuffptr++->y = y2;
	w->clock.numseg += 2;
}

/*
 *  Draw the clock face (every fifth tick-mark is longer
 *  than the others).
 */
static void DrawClockFace(w)
ClockWidget w;
{
	register int i;
	register int delta = (w->clock.radius - w->clock.second_hand_length) / 3;
	
	w->clock.segbuffptr = w->clock.segbuff;
	w->clock.numseg = 0;
	for (i = 0; i < 60; i++)
		DrawLine(w, ( (i % 5) == 0 ? 
			     w->clock.second_hand_length :
			     (w->clock.radius - delta) ),
			 w->clock.radius, i );
	/* Changed last argument to DrawLine from i/60. to i due 
	 * to compiler bug. Updated DrawLine function to reflect this.
	 */

	/*
	 * Go ahead and draw it.
	 */
	XDrawSegments(XtDisplay(w), XtWindow(w),
		      w->clock.myGC, (XSegment *) &(w->clock.segbuff[0]),
		      w->clock.numseg/2);
	
	w->clock.segbuffptr = w->clock.segbuff;
	w->clock.numseg = 0;
}

static int round(x)
double x;
{
	return(x >= 0.0 ? (int)(x + .5) : (int)(x - .5));
}

/* ARGSUSED */
static Boolean SetValues (gcurrent, grequest, gnew)
    Widget gcurrent, grequest, gnew;
{
      ClockWidget current = (ClockWidget) gcurrent;
      ClockWidget new = (ClockWidget) gnew;
      Boolean redisplay = FALSE;
      XtGCMask valuemask;
      XGCValues	myXGCV;

      /* first check for changes to clock-specific resources.  We'll accept all
         the changes, but may need to do some computations first. */

      if (new->clock.update != current->clock.update) {
	  if (current->clock.interval_id)
	      XtRemoveTimeOut (current->clock.interval_id);
	  if (XtIsRealized((Widget)new))
	      new->clock.interval_id = XtAppAddTimeOut( 
                                         XtWidgetToApplicationContext(gnew),
					 new->clock.update*1000,
				         (XtTimerCallbackProc)clock_tic,
				         (caddr_t)gnew);

	  new->clock.show_second_hand =(new->clock.update <= SECOND_HAND_TIME);
      }

      if (new->clock.padding != current->clock.padding)
	   redisplay = TRUE;

      if (new->clock.analog != current->clock.analog)
	   redisplay = TRUE;

       if (new->clock.font != current->clock.font)
	   redisplay = TRUE;

      if ((new->clock.fgpixel != current->clock.fgpixel)
          || (new->core.background_pixel != current->core.background_pixel)) {
          valuemask = GCForeground | GCBackground | GCFont | GCLineWidth;
	  myXGCV.foreground = new->clock.fgpixel;
	  myXGCV.background = new->core.background_pixel;
          myXGCV.font = new->clock.font->fid;
	  myXGCV.line_width = 0;
	  XtDestroyGC (current->clock.myGC);
	  new->clock.myGC = XtGetGC(gcurrent, valuemask, &myXGCV);
	  redisplay = TRUE;
          }

      if (new->clock.Hipixel != current->clock.Hipixel) {
          valuemask = GCForeground | GCLineWidth;
	  myXGCV.foreground = new->clock.fgpixel;
          myXGCV.font = new->clock.font->fid;
	  myXGCV.line_width = 0;
	  XtDestroyGC (current->clock.HighGC);
	  new->clock.HighGC = XtGetGC((Widget)gcurrent, valuemask, &myXGCV);
	  redisplay = TRUE;
          }

      if (new->clock.Hdpixel != current->clock.Hdpixel) {
          valuemask = GCForeground;
	  myXGCV.foreground = new->clock.fgpixel;
	  XtDestroyGC (current->clock.HandGC);
	  new->clock.HandGC = XtGetGC((Widget)gcurrent, valuemask, &myXGCV);
	  redisplay = TRUE;
          }

      if (new->core.background_pixel != current->core.background_pixel) {
          valuemask = GCForeground | GCLineWidth;
	  myXGCV.foreground = new->core.background_pixel;
	  myXGCV.line_width = 0;
	  XtDestroyGC (current->clock.EraseGC);
	  new->clock.EraseGC = XtGetGC((Widget)gcurrent, valuemask, &myXGCV);
	  redisplay = TRUE;
	  }
     
     return (redisplay);

}
