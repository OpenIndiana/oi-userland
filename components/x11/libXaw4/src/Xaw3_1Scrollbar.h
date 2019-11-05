/*
* $XConsortium: Scrollbar.h,v 1.1 89/12/15 11:40:43 kit Exp $
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

#ifndef _Scrollbar_h
#define _Scrollbar_h

/****************************************************************
 *
 * Scrollbar Widget
 *
 ****************************************************************/

#include <X11/Xmu/Converters.h>

/* Parameters:

 Name		     Class		RepType		Default Value
 ----		     -----		-------		-------------
 background	     Background		Pixel		White
 border		     BorderColor	Pixel		Black
 borderWidth	     BorderWidth	Dimension	1
 destroyCallback     Callback		Function		NULL
 foreground	     Color		Pixel		Black
 height		     Height		Dimension	length or thickness
 jumpProc	     Callback		Function	NULL
 length		     Length		Dimension	1
 mappedWhenManaged   MappedWhenManaged	Boolean		True
 orientation	     Orientation	XtOrientation	XtorientVertical
 reverseVideo	     ReverseVideo	Boolean		False
 scrollDCursor	     Cursor		Cursor		XC_sb_down_arrow
 scrollHCursor	     Cursor		Cursor		XC_sb_h_double_arrow
 scrollLCursor	     Cursor		Cursor		XC_sb_left_arrow
 scrollProc	     Callback		Function	NULL
 scrollRCursor	     Cursor		Cursor		XC_sb_right_arrow
 scrollUCursor	     Cursor		Cursor		XC_sb_up_arrow
 scrollVCursor	     Cursor		Cursor		XC_sb_v_double_arrow
 sensitive	     Sensitive		Boolean		True
 shown		     Shown		float		0.0
 thickness	     Thickness		Dimension	14
 thumb		     Thumb		Pixmap		Grey
 topOfThumb	     TopOfThumb		float		0.0
 width		     Width		Dimension	thickness or length
 x		     Position		Position	0
 y		     Position		Position	0

*/

/* 
 * Most things we need are in StringDefs.h 
 */

#define XtCMinimumThumb "MinimumThumb"
#define XtCShown "Shown"
#define XtCTopOfThumb "TopOfThumb"

#define XtNminimumThumb "minimumThumb"
#define XtNtopOfThumb "topOfThumb"

typedef struct _ScrollbarRec	  *ScrollbarWidget;
typedef struct _ScrollbarClassRec *ScrollbarWidgetClass;

extern WidgetClass scrollbarWidgetClass;

extern void XawScrollbarSetThumb(); /* scrollBar, top, shown */
    /* Widget scrollBar; */
    /* float top, shown; */

#ifdef XAW_BC
/*************************************************************
 * For Compatibility only.                                   */

#define XtScrollBarSetThumb      XawScrollbarSetThumb

/*************************************************************/
#endif /* XAW_BC */

#endif /* _Scrollbar_h */
