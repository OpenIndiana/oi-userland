#if (!defined(lint) && !defined(SABER))
static char Xrcsid[] = "$XConsortium: AsciiSink.c,v 1.49 89/12/14 19:15:55 converse Exp $";
#endif /* lint && SABER */

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

#include <stdio.h>

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xatom.h>
#include <X11/IntrinsicP.h>
#include <X11/StringDefs.h>
#include <./Xaw3_1XawInit.h>
#include <./Xaw3_1AsciiSinkP.h>
#include <./Xaw3_1AsciiSrcP.h>	/* For source function defs. */
#include <./Xaw3_1TextP.h>	/* I also reach into the text widget. */

#ifdef GETLASTPOS
#undef GETLASTPOS		/* We will use our own GETLASTPOS. */
#endif

#define GETLASTPOS XawTextSourceScan(source, 0, XawstAll, XawsdRight, 1, TRUE)

static void Initialize(), Destroy();
static Boolean SetValues();

static void DisplayText(), InsertCursor(), FindPosition();
static void FindDistance(), Resolve(), GetCursorBounds();

#define offset(field) XtOffset(AsciiSinkObject, ascii_sink.field)

static XtResource resources[] = {
    {XtNecho, XtCOutput, XtRBoolean, sizeof(Boolean),
	offset(echo), XtRImmediate, (caddr_t) True},
    {XtNdisplayNonprinting, XtCOutput, XtRBoolean, sizeof(Boolean),
	offset(display_nonprinting), XtRImmediate, (caddr_t) True},
};
#undef offset

#define SuperClass		(&textSinkClassRec)
AsciiSinkClassRec asciiSinkClassRec = {
  {
/* core_class fields */	
    /* superclass	  	*/	(WidgetClass) SuperClass,
    /* class_name	  	*/	"AsciiSink",
    /* widget_size	  	*/	sizeof(AsciiSinkRec),
    /* class_initialize   	*/	XawInitializeWidgetSet,
    /* class_part_initialize	*/	NULL,
    /* class_inited       	*/	FALSE,
    /* initialize	  	*/	Initialize,
    /* initialize_hook		*/	NULL,
    /* obj1		  	*/	NULL,
    /* obj2		  	*/	NULL,
    /* obj3		  	*/	0,
    /* resources	  	*/	resources,
    /* num_resources	  	*/	XtNumber(resources),
    /* xrm_class	  	*/	NULLQUARK,
    /* obj4		  	*/	FALSE,
    /* obj5		  	*/	FALSE,
    /* obj6			*/	FALSE,
    /* obj7		  	*/	FALSE,
    /* destroy		  	*/	Destroy,
    /* obj8		  	*/	NULL,
    /* obj9		  	*/	NULL,
    /* set_values	  	*/	SetValues,
    /* set_values_hook		*/	NULL,
    /* obj10			*/	NULL,
    /* get_values_hook		*/	NULL,
    /* obj11		 	*/	NULL,
    /* version			*/	XtVersion,
    /* callback_private   	*/	NULL,
    /* obj12		   	*/	NULL,
    /* obj13			*/	NULL,
    /* obj14			*/	NULL,
    /* extension		*/	NULL
  },
/* text_sink_class fields */
  {
    /* DisplayText              */      DisplayText,
    /* InsertCursor             */      InsertCursor,
    /* ClearToBackground        */      XtInheritClearToBackground,
    /* FindPosition             */      FindPosition,
    /* FindDistance             */      FindDistance,
    /* Resolve                  */      Resolve,
    /* MaxLines                 */      XtInheritMaxLines,
    /* MaxHeight                */      XtInheritMaxHeight,
    /* SetTabs                  */      XtInheritSetTabs,
    /* GetCursorBounds          */      GetCursorBounds
  },
/* ascii_sink_class fields. */
  {
    /* Keep Compiler happy.     */      NULL
  }
};

WidgetClass asciiSinkObjectClass = (WidgetClass)&asciiSinkClassRec;

/* Utilities */

static int 
CharWidth (w, x, c)
Widget w;
int x;
unsigned char c;
{
    register int    i, width, nonPrinting;
    AsciiSinkObject sink = (AsciiSinkObject) w;
    XFontStruct *font = sink->text_sink.font;
    Position *tab;

    if ( c == LF ) return(0);

    if (c == TAB) {
	/* Adjust for Left Margin. */
	x -= ((TextWidget) XtParent(w))->text.margin.left;

	if (x >= XtParent(w)->core.width) return 0;
	for (i = 0, tab = sink->text_sink.tabs ; 
	     i < sink->text_sink.tab_count ; i++, tab++) {
	    if (x < *tab) {
		if (*tab < XtParent(w)->core.width)
		    return *tab - x;
		else
		    return 0;
	    }
	}
	return 0;
    }

    if ( (nonPrinting = (c < (unsigned char) SP)) )
	if (sink->ascii_sink.display_nonprinting)
	    c += '@';
	else {
	    c = SP;
	    nonPrinting = False;
	}

    if (font->per_char &&
	    (c >= font->min_char_or_byte2 && c <= font->max_char_or_byte2))
	width = font->per_char[c - font->min_char_or_byte2].width;
    else
	width = font->min_bounds.width;

    if (nonPrinting)
	width += CharWidth(w, x, (unsigned char) '^');

    return width;
}

/*	Function Name: PaintText
 *	Description: Actually paints the text into the windoe.
 *	Arguments: w - the text widget.
 *                 gc - gc to paint text with.
 *                 x, y - location to paint the text.
 *                 buf, len - buffer and length of text to paint.
 *	Returns: the width of the text painted, or 0.
 *
 * NOTE:  If this string attempts to paint past the end of the window
 *        then this function will return zero.
 */

static Dimension
PaintText(w, gc, x, y, buf, len)
Widget w;
GC gc;
Position x, y;
unsigned char * buf;
int len;
{
    AsciiSinkObject sink = (AsciiSinkObject) w;
    TextWidget ctx = (TextWidget) XtParent(w);

    Position max_x;
    Dimension width = XTextWidth(sink->text_sink.font, (char *) buf, len); 
    max_x = (Position) ctx->core.width;

    if ( ((int) width) <= -x)	           /* Don't draw if we can't see it. */
      return(width);

    XDrawImageString(XtDisplay(ctx), XtWindow(ctx), gc, 
		     (int) x, (int) y, (char *) buf, len);
    if ( (((Position) width + x) > max_x) && (ctx->text.margin.right != 0) ) {
	x = ctx->core.width - ctx->text.margin.right;
	width = ctx->text.margin.right;
	XFillRectangle(XtDisplay((Widget) ctx), XtWindow( (Widget) ctx),
		       sink->ascii_sink.normgc, (int) x,
		       (int) y - sink->text_sink.font->ascent, 
		       (unsigned int) width,
		       (unsigned int) (sink->text_sink.font->ascent +
				       sink->text_sink.font->descent));
	return(0);
    }
    return(width);
}

/* Sink Object Functions */

/*
 * This function does not know about drawing more than one line of text.
 */
 
static void 
DisplayText(w, x, y, pos1, pos2, highlight)
Widget w;
Position x, y;
Boolean highlight;
XawTextPosition pos1, pos2;
{
    AsciiSinkObject sink = (AsciiSinkObject) w;
    Widget source = XawTextGetSource(XtParent(w));
    unsigned char buf[BUFSIZ];

    int j, k;
    XawTextBlock blk;
    GC gc = highlight ? sink->ascii_sink.invgc : sink->ascii_sink.normgc;
    GC invgc = highlight ? sink->ascii_sink.normgc : sink->ascii_sink.invgc;

    if (!sink->ascii_sink.echo) return;

    y += sink->text_sink.font->ascent;
    for ( j = 0 ; pos1 < pos2 ; ) {
	pos1 = XawTextSourceRead(source, pos1, &blk, pos2 - pos1);
	for (k = 0; k < blk.length; k++) {
	    if (j >= BUFSIZ) {	/* buffer full, dump the text. */
	        x += PaintText(w, gc, x, y, buf, j);
		j = 0;
	    }
	    buf[j] = blk.ptr[k];
	    if (buf[j] == LF)	/* line feeds ('\n') are not printed. */
	        continue;

	    else if (buf[j] == '\t') {
	        Position temp = 0;
		Dimension width;

	        if ((j != 0) && ((temp = PaintText(w, gc, x, y, buf, j)) == 0))
		  return;

	        x += temp;
		width = CharWidth(w, x, (unsigned char) '\t');
		XFillRectangle(XtDisplayOfObject(w), XtWindowOfObject(w),
			       invgc, (int) x,
			       (int) y - sink->text_sink.font->ascent,
			       (unsigned int) width,
			       (unsigned int) (sink->text_sink.font->ascent +
					       sink->text_sink.font->descent));
		x += width;
		j = -1;
	    }
	    else if ( buf[j] < (unsigned char) ' ' ) {
	        if (sink->ascii_sink.display_nonprinting) {
		    buf[j + 1] = buf[j] + '@';
		    buf[j] = '^';
		    j++;
		}
		else
		    buf[j] = ' ';
	    }
	    j++;
	}
    }
    if (j > 0)
        (void) PaintText(w, gc, x, y, buf, j);
}

#define insertCursor_width 6
#define insertCursor_height 3
static char insertCursor_bits[] = {0x0c, 0x1e, 0x33};

static Pixmap
CreateInsertCursor(s)
Screen *s;
{
    return (XCreateBitmapFromData (DisplayOfScreen(s), RootWindowOfScreen(s),
		  insertCursor_bits, insertCursor_width, insertCursor_height));
}

/*	Function Name: GetCursorBounds
 *	Description: Returns the size and location of the cursor.
 *	Arguments: w - the text object.
 * RETURNED        rect - an X rectangle to return the cursor bounds in.
 *	Returns: none.
 */

static void
GetCursorBounds(w, rect)
Widget w;
XRectangle * rect;
{
    AsciiSinkObject sink = (AsciiSinkObject) w;

    rect->width = (unsigned short) insertCursor_width;
    rect->height = (unsigned short) insertCursor_height;
    rect->x = sink->ascii_sink.cursor_x - (short) (rect->width / 2);
    rect->y = sink->ascii_sink.cursor_y - (short) rect->height;
}

/*
 * The following procedure manages the "insert" cursor.
 */

static void
InsertCursor (w, x, y, state)
Widget w;
Position x, y;
XawTextInsertState state;
{
    AsciiSinkObject sink = (AsciiSinkObject) w;
    Widget text_widget = XtParent(w);
    XRectangle rect;

    sink->ascii_sink.cursor_x = x;
    sink->ascii_sink.cursor_y = y;

    GetCursorBounds(w, &rect);
    if (state != sink->ascii_sink.laststate && XtIsRealized(text_widget)) 
        XCopyPlane(XtDisplay(text_widget),
		   sink->ascii_sink.insertCursorOn,
		   XtWindow(text_widget), sink->ascii_sink.xorgc,
		   0, 0, (unsigned int) rect.width, (unsigned int) rect.height,
		   (int) rect.x, (int) rect.y, 1);
    sink->ascii_sink.laststate = state;
}

/*
 * Given two positions, find the distance between them.
 */

static void
FindDistance (w, fromPos, fromx, toPos, resWidth, resPos, resHeight)
Widget w;
XawTextPosition fromPos;	/* First position. */
int fromx;			/* Horizontal location of first position. */
XawTextPosition toPos;		/* Second position. */
int *resWidth;			/* Distance between fromPos and resPos. */
XawTextPosition *resPos;	/* Actual second position used. */
int *resHeight;			/* Height required. */
{
    AsciiSinkObject sink = (AsciiSinkObject) w;
    Widget source = XawTextGetSource(XtParent(w));

    register XawTextPosition index, lastPos;
    register unsigned char c;
    XawTextBlock blk;

    /* we may not need this */
    lastPos = GETLASTPOS;
    XawTextSourceRead(source, fromPos, &blk, toPos - fromPos);
    *resWidth = 0;
    for (index = fromPos; index != toPos && index < lastPos; index++) {
	if (index - blk.firstPos >= blk.length)
	    XawTextSourceRead(source, index, &blk, toPos - fromPos);
	c = blk.ptr[index - blk.firstPos];
	*resWidth += CharWidth(w, fromx + *resWidth, c);
	if (c == LF) {
	    index++;
	    break;
	}
    }
    *resPos = index;
    *resHeight = sink->text_sink.font->ascent +sink->text_sink.font->descent;
}


static void
FindPosition(w, fromPos, fromx, width, stopAtWordBreak, 
		  resPos, resWidth, resHeight)
Widget w;
XawTextPosition fromPos; 	/* Starting position. */
int fromx;			/* Horizontal location of starting position.*/
int width;			/* Desired width. */
int stopAtWordBreak;		/* Whether the resulting position should be at
				   a word break. */
XawTextPosition *resPos;	/* Resulting position. */
int *resWidth;			/* Actual width used. */
int *resHeight;			/* Height required. */
{
    AsciiSinkObject sink = (AsciiSinkObject) w;
    Widget source = XawTextGetSource(XtParent(w));

    XawTextPosition lastPos, index, whiteSpacePosition;
    int     lastWidth, whiteSpaceWidth;
    Boolean whiteSpaceSeen;
    unsigned char c;
    XawTextBlock blk;

    lastPos = GETLASTPOS;

    XawTextSourceRead(source, fromPos, &blk, BUFSIZ);
    *resWidth = 0;
    whiteSpaceSeen = FALSE;
    c = 0;
    for (index = fromPos; *resWidth <= width && index < lastPos; index++) {
	lastWidth = *resWidth;
	if (index - blk.firstPos >= blk.length)
	    XawTextSourceRead(source, index, &blk, BUFSIZ);
	c = blk.ptr[index - blk.firstPos];
	*resWidth += CharWidth(w, fromx + *resWidth, c);

	if ((c == SP || c == TAB) && *resWidth <= width) {
	    whiteSpaceSeen = TRUE;
	    whiteSpacePosition = index;
	    whiteSpaceWidth = *resWidth;
	}
	if (c == LF) {
	    index++;
	    break;
	}
    }
    if (*resWidth > width && index > fromPos) {
	*resWidth = lastWidth;
	index--;
	if (stopAtWordBreak && whiteSpaceSeen) {
	    index = whiteSpacePosition + 1;
	    *resWidth = whiteSpaceWidth;
	}
    }
    if (index == lastPos && c != LF) index = lastPos + 1;
    *resPos = index;
    *resHeight = sink->text_sink.font->ascent +sink->text_sink.font->descent;
}

static void
Resolve (w, pos, fromx, width, leftPos, rightPos)
Widget w;
XawTextPosition pos;
int fromx, width;
XawTextPosition *leftPos, *rightPos;
{
    int resWidth, resHeight;
    Widget source = XawTextGetSource(XtParent(w));

    FindPosition(w, pos, fromx, width, FALSE, leftPos, &resWidth, &resHeight);
    if (*leftPos > GETLASTPOS)
      *leftPos = GETLASTPOS;
    *rightPos = *leftPos;
}

static void
GetGC(sink)
AsciiSinkObject sink;
{
    XtGCMask valuemask = (GCFont | 
			  GCGraphicsExposures | GCForeground | GCBackground );
    XGCValues values;

    values.font = sink->text_sink.font->fid;
    values.graphics_exposures = (Bool) FALSE;
    
    values.foreground = sink->text_sink.foreground;
    values.background = sink->text_sink.background;
    sink->ascii_sink.normgc = XtGetGC((Widget)sink, valuemask, &values);
    
    values.foreground = sink->text_sink.background;
    values.background = sink->text_sink.foreground;
    sink->ascii_sink.invgc = XtGetGC((Widget)sink, valuemask, &values);
    
    values.function = GXxor;
    values.background = (unsigned long) 0L;	/* (pix ^ 0) = pix */
    values.foreground = (sink->text_sink.background ^ 
			 sink->text_sink.foreground);
    valuemask = GCFunction | GCForeground | GCBackground;
    
    sink->ascii_sink.xorgc = XtGetGC((Widget)sink, valuemask, &values);
}


/***** Public routines *****/

/*	Function Name: Initialize
 *	Description: Initializes the TextSink Object.
 *	Arguments: request, new - the requested and new values for the object
 *                                instance.
 *	Returns: none.
 *
 */

/* ARGSUSED */
static void
Initialize(request, new)
Widget request, new;
{
    AsciiSinkObject sink = (AsciiSinkObject) new;

    GetGC(sink);
    
    sink->ascii_sink.insertCursorOn= CreateInsertCursor(XtScreenOfObject(new));
    sink->ascii_sink.laststate = XawisOff;
    sink->ascii_sink.cursor_x = sink->ascii_sink.cursor_y = 0;
}

/*	Function Name: Destroy
 *	Description: This function cleans up when the object is 
 *                   destroyed.
 *	Arguments: w - the AsciiSink Object.
 *	Returns: none.
 */

static void
Destroy(w)
Widget w;
{
   AsciiSinkObject sink = (AsciiSinkObject) w;

   XtReleaseGC(w, sink->ascii_sink.normgc);
   XtReleaseGC(w, sink->ascii_sink.invgc);
   XtReleaseGC(w, sink->ascii_sink.xorgc);
   XFreePixmap(XtDisplayOfObject(w), sink->ascii_sink.insertCursorOn);
}

/*	Function Name: SetValues
 *	Description: Sets the values for the AsciiSink
 *	Arguments: current - current state of the object.
 *                 request - what was requested.
 *                 new - what the object will become.
 *	Returns: True if redisplay is needed.
 */

/* ARGSUSED */
static Boolean
SetValues(current, request, new)
Widget current, request, new;
{
    AsciiSinkObject w = (AsciiSinkObject) new;
    AsciiSinkObject old_w = (AsciiSinkObject) current;

    if (w->text_sink.font != old_w->text_sink.font) {
	XtReleaseGC((Widget)w, w->ascii_sink.normgc);
	XtReleaseGC((Widget)w, w->ascii_sink.invgc);
	GetGC(w);
	((TextWidget)XtParent(new))->text.redisplay_needed = True;
    } else {
	if ( (w->ascii_sink.echo != old_w->ascii_sink.echo) ||
	     (w->ascii_sink.display_nonprinting != 
                                     old_w->ascii_sink.display_nonprinting) )
	    ((TextWidget)XtParent(new))->text.redisplay_needed = True;
    }
    
    return False;
}
