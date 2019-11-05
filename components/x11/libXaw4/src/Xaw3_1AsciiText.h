/*
 * $XConsortium: AsciiText.h,v 1.15 89/07/06 16:00:35 kit Exp $ 
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

/***********************************************************************
 *
 * AsciiText Widget
 *
 ***********************************************************************/

/*
 * AsciiText.c - Public header file for AsciiText Widget.
 *
 * This Widget is intended to be used as a simple front end to the 
 * text widget with an ascii source and ascii sink attached to it.
 *
 * Date:    June 29, 1989
 *
 * By:      Chris D. Peterson
 *          MIT X Consortium 
 *          kit@expo.lcs.mit.edu
 */

#ifndef _AsciiText_h
#define _AsciiText_h

/****************************************************************
 *
 * AsciiText widgets
 *
 ****************************************************************/

#include <./Xaw3_1Text.h>		/* AsciiText is a subclass of Text */
#include <./Xaw3_1AsciiSrc.h>

/* Resources:

 Name		     Class		RepType		Default Value
 ----		     -----		-------		-------------
 background	     Background		Pixel		XtDefaultBackground
 border		     BorderColor	Pixel		XtDefaultForeground
 borderWidth	     BorderWidth	Dimension	1
 destroyCallback     Callback		Pointer		NULL
 displayPosition     TextPosition	int		0
 editType	     EditType		XawTextEditType	XawtextRead
 font		     Font		XFontStruct*	Fixed
 foreground	     Foreground		Pixel		Black
 height		     Height		Dimension	font height
 insertPosition	     TextPosition	int		0
 leftMargin	     Margin		Dimension	2
 mappedWhenManaged   MappedWhenManaged	Boolean		True
 selectTypes	     SelectTypes	Pointer		(internal)
 selection	     Selection		Pointer		empty selection
 sensitive	     Sensitive		Boolean		True
 string		     String		String		NULL
 textOptions	     TextOptions	int		0
 width		     Width		Dimension	100
 x		     Position		Position	0
 y		     Position		Position	0

*/

/*
 * Everything else we need is in StringDefs.h or Text.h
 */

typedef struct _AsciiTextClassRec	*AsciiTextWidgetClass;
typedef struct _AsciiRec	        *AsciiWidget;

extern WidgetClass asciiTextWidgetClass;

/************************************************************
 *
 * Disk and String Emulation Info.
 * 
 ************************************************************/

#ifdef ASCII_STRING
extern WidgetClass asciiStringWidgetClass;
#endif

#ifdef ASCII_DISK
extern WidgetClass asciiDiskWidgetClass;
#endif

#endif /* _AsciiText_h */
