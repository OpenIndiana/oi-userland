/*
* $XConsortium: Paned.h,v 1.8 89/10/04 19:35:43 kit Exp $
*/


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

/*
 * Paned.h - Paned Composite Widget's public header file.
 *
 * Updated and significantly modifided from the Athena VPaned Widget.
 *
 * Date:    March 1, 1989
 *
 * By:      Chris D. Peterson
 *          MIT X Consortium
 *          kit@expo.lcs.mit.edu
 */

#ifndef _XawPaned_h
#define _XawPaned_h

#include <X11/Constraint.h>

/****************************************************************
 *
 * Vertical Paned Widget (SubClass of CompositeClass)
 *
 ****************************************************************/

/* RESOURCES:

 Name		         Class		   RepType	    Default Value
 ----		         -----		   -------	    -------------
 background	         Background	   Pixel	    XtDefaultBackground
 betweenCursor	         Cursor	           Cursor	    **
 border		         BorderColor       Pixel	    XtDefaultForeground
 borderWidth	         BorderWidth       Dimension	    1
 cursor		         Cursor	           Cursor	    None
 destroyCallback         Callback	   Pointer	    NULL
 height		         Height	           Dimension	    0
 gripIndent	         GripIndent	   Position	    16
 gripCursor	         Cursor	           Cursor	    **
 horizontalGripCursol    Cursor	           Cursor	    sb_h_double_arrow
 horizontalBetweencursor Cursor	           Cursor	    sb_up_arrow
 internalBorderColor     BorderColor	   Pixel	    XtDefaultForeground
 internalBorderWidth     BorderWidth	   Position	    1
 leftCursor	         Cursor	           Cursor	    sb_left_arrow
 lowerCursor	         Cursor	           Cursor	    sb_down_arrow
 mappedWhenManaged       MappedWhenManaged Boolean	    True
 orientation             Orientation       XtOrientation    XtorientVertical
 refigureMode	         Boolean	   Boolean	    On
 rightCursor	         Cursor	           Cursor           sb_right_arrow
 sensitive	         Sensitive	   Boolean	    True
 upperCursor	         Cursor	           Cursor	    sb_up_arrow
 verticalBetweenCursor   Cursor	           Cursor           sb_left_arrow
 verticalGripCursor      Cursor	           Cursor           sb_v_double_arrow
 width		         Width	           Dimension	    0
 x		         Position	   Position	    0
 y		         Position	   Position    	    0

** These resources now are set to the vertical or horizontal cursor
   depending upon orientation, by default.  If a value is specified here
   then that cursor will be used reguardless of orientation.


CONSTRAINT RESOURCES:

 Name		      Class		RepType		Default Value
 ----		      -----		-------		-------------
 allowResize	      Boolean	        Boolean         False
 max		      Max	        Dimension	unlimited
 min		      Min		Dimension	Grip Size
 preferredPaneSize    PerferredPaneSize Dimension	PANED_ASK_CHILD
 resizeToPreferred    Boolean		Boolean	 	False
 showGrip	      ShowGrip		Boolean		True
 skipAdjust	      Boolean	        Boolean         False

*/

#define PANED_ASK_CHILD 0
#define PANED_GRIP_SIZE 0

/* New Fields */
#define XtNallowResize "allowResize"
#define XtNbetweenCursor "betweenCursor"
#define XtNverticalBetweenCursor "verticalBetweenCursor"
#define XtNhorizontalBetweenCursor "horizontalBetweenCursor"
#define XtNgripCursor "gripCursor"
#define XtNgripIndent "gripIndent"
#define XtNhorizontalGripCursor "horizontalGripCursor"
#define XtNinternalBorderColor "internalBorderColor"
#define XtNinternalBorderWidth "internalBorderWidth"
#define XtNleftCursor "leftCursor"
#define XtNlowerCursor "lowerCursor"
#define XtNrefigureMode "refigureMode"
#define XtNposition "position"
#define XtNmin "min"
#define XtNmax "max"
#define XtNpreferredPaneSize "preferredPaneSize"
#define XtNresizeToPreferred "resizeToPreferred"
#define XtNrightCursor "rightCursor"
#define XtNshowGrip "showGrip"
#define XtNskipAdjust "skipAdjust"
#define XtNupperCursor "upperCursor"
#define XtNverticalGripCursor "verticalGripCursor"

#define XtCGripIndent "GripIndent"
#define XtCMin "Min"
#define XtCMax "Max"
#define XtCPreferredPaneSize "PreferredPaneSize"
#define XtCShowGrip "ShowGrip"

/* Class record constant */
extern WidgetClass panedWidgetClass;

#ifdef XAW_BC			/* for compatability only. */
  extern WidgetClass vPanedWidgetClass;
#endif

typedef struct _PanedClassRec	*PanedWidgetClass;
typedef struct _PanedRec	*PanedWidget;

/************************************************************
 *
 *  Public Procedures 
 *
 ************************************************************/


/*	Function Name: XawPanedSetMinMax
 *	Description: Sets the min and max size for a pane.
 *	Arguments: widget - the widget that is a child of the Paned widget.
 *                 min, max - the new min and max size for the pane.
 *	Returns: none.
 */

extern void XawPanedSetMinMax();		/* widget, min, max */
    /* Widget widget; */
    /* int min, max; */

/*	Function Name: XawPanedGetMinMax
 *	Description: Gets the min and max size for a pane.
 *	Arguments: widget - the widget that is a child of the Paned widget.
 ** RETURNED **    min, max - the current min and max size for the pane.
 *	Returns: none.
 */

extern void XawPanedGetMinMax(); /* widget, min, max */
    /* Widget widget; */
    /* int    *min, *max; */

/*	Function Name: XawPanedSetRefigureMode
 *	Description: Allows a flag to be set the will inhibit 
 *                   the paned widgets relayout routine.
 *	Arguments: w - the paned widget.
 *                 mode - if FALSE then inhibit refigure.
 *	Returns: none.
 */

extern void XawPanedSetRefigureMode();	/* w, mode */
    /* Widget w; */
    /* Boolean mode; */

/*	Function Name: XawPanedGetNumSub
 *	Description: Returns the number of panes in the paned widget.
 *	Arguments: w - the paned widget.
 *	Returns: the number of panes in the paned widget.
 */

extern int XawPanedGetNumSub();		/* w */
    /* Widget w; */

/*	Function Name: XawPanedAllowResize
 *	Description: Allows a flag to be set that determines if the paned
 *                   widget will allow geometry requests from this child
 *	Arguments: widget - a child of the paned widget.
 *	Returns: none.
 */

extern void XawPanedAllowResize();  /* widget, allow_resize */
    /* Widget widget; */
    /* Boolean allow_resize; */

#ifdef XAW_BC
/*************************************************************
 * For Compatibility only.                                   */

#define XtPanedSetMinMax        XawPanedSetMinMax
#define XtPanedGetMinMax        XawPanedGetMinMax
#define XtPanedGetNumSub        XawPanedGetNumSub
#define XtPanedAllowResize      XawPanedAllowResize
#define XtPanedSetRefigureMode  XawPanedSetRefigureMode

/*************************************************************/
#endif /* XAW_BC */
  
#endif /* _XawPaned_h */
/* DON'T ADD STUFF AFTER THIS #endif */
