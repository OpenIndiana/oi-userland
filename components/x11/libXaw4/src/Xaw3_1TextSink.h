/*
 * $XConsortium: TextSink.h,v 1.5 89/11/01 17:28:26 kit Exp $
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

#ifndef _XawTextSink_h
#define _XawTextSink_h

/***********************************************************************
 *
 * TextSink Object
 *
 ***********************************************************************/

#include <X11/Object.h>

/* Resources:

 Name		     Class		RepType		Default Value
 ----		     -----		-------		-------------
 font                Font            XFontStruct *      XtDefaultFont
 foreground          Foreground      Pixel              XtDefaultForeground
 background          Background      Pixel              XtDefaultBackground

*/
 
/* Class record constants */

extern WidgetClass textSinkObjectClass;

typedef struct _TextSinkClassRec *TextSinkObjectClass;
typedef struct _TextSinkRec      *TextSinkObject;

typedef enum {XawisOn, XawisOff} XawTextInsertState;

/************************************************************
 *
 * Public Functions.
 *
 ************************************************************/

/*	Function Name: XawTextSinkDisplayText
 *	Description: Stub function that in subclasses will display text. 
 *	Arguments: w - the TextSink Object.
 *                 x, y - location to start drawing text.
 *                 pos1, pos2 - location of starting and ending points
 *                              in the text buffer.
 *                 highlight - hightlight this text?
 *	Returns: none.
 *
 * This function doesn't actually display anything, it is only a place
 * holder.
 */

void XawTextSinkDisplayText(/* w, x, y, pos1, pos2, highlight */);
/*
Widget w;
Position x, y;
Boolean highlight;
XawTextPosition pos1, pos2;
*/

/*	Function Name: XawTextSinkInsertCursor
 *	Description: Places the InsertCursor.
 *	Arguments: w - the TextSink Object.
 *                 x, y - location for the cursor.
 *                 staye - whether to turn the cursor on, or off.
 *	Returns: none.
 *
 * This function doesn't actually display anything, it is only a place
 * holder.
 */

void XawTextSinkInsertCursor( /* w, x, y, state */ );
/*
Widget w;
Position x, y;
XawTextInsertState state;
*/

/*	Function Name: XawTextSinkClearToBackground
 *	Description: Clears a region of the sink to the background color.
 *	Arguments: w - the TextSink Object.
 *                 x, y  - location of area to clear.
 *                 width, height - size of area to clear
 *	Returns: void.
 *
 * This function doesn't actually display anything, it is only a place
 * holder.
 */

void XawTextSinkClearToBackground (/* w, x, y, width, height */);
/*
Widget w;
Position x, y;
Dimension width, height;
*/

/*	Function Name: XawTextSinkFindPosition
 *	Description: Finds a position in the text.
 *	Arguments: w - the TextSink Object.
 *                 fromPos - reference position.
 *                 fromX   - reference location.
 *                 width,  - width of section to paint text.
 *                 stopAtWordBreak - returned position is a word break?
 *                 resPos - Position to return.      *** RETURNED ***
 *                 resWidth - Width actually used.   *** RETURNED ***
 *                 resHeight - Height actually used. *** RETURNED ***
 *	Returns: none (see above).
 */

void XawTextSinkFindPosition(/* w, fromPos, fromx, width, stopAtWordBreak, 
			     resPos, resWidth, resHeight */ );
/*
Widget w;
XawTextPosition fromPos; 
int fromx, width;			
Boolean stopAtWordBreak;		
XawTextPosition *resPos;	
int *resWidth, *resHeight;		
*/

/*	Function Name: XawTextSinkFindDistance
 *	Description: Find the Pixel Distance between two text Positions.
 *	Arguments: w - the TextSink Object.
 *                 fromPos - starting Position.
 *                 fromX   - x location of starting Position.
 *                 toPos   - end Position.
 *                 resWidth - Distance between fromPos and toPos.
 *                 resPos   - Acutal toPos used.
 *                 resHeight - Height required by this text.
 *	Returns: none.
 */

void XawTextSinkFindDistance (/* w, fromPos, fromx, 
				 toPos, resWidth, resPos, resHeight */);
/*
Widget w;
XawTextPosition fromPos, toPos, *resPos;
int fromx, *resWidth, *resHeight;
*/

/*	Function Name: XawTextSinkResolve
 *	Description: Resloves a location to a position.
 *	Arguments: w - the TextSink Object.
 *                 pos - a reference Position.
 *                 fromx - a reference Location.
 *                 width - width to move.
 *                 resPos - the resulting position.
 *	Returns: none
 */

void XawTextSinkResolve(/* w, pos, fromx, width, resPos */);
/*
Widget w;
XawTextPosition pos;
int fromx, width;
XawTextPosition *resPos;
*/

/*	Function Name: XawTextSinkMaxLines
 *	Description: Finds the Maximum number of lines that will fit in
 *                   a given height.
 *	Arguments: w - the TextSink Object.
 *                 height - height to fit lines into.
 *	Returns: the number of lines that will fit.
 */

int XawTextSinkMaxLines(/* w, height */);
/*
Widget w;
Dimension height;
*/

/*	Function Name: XawTextSinkMaxHeight
 *	Description: Finds the Minium height that will contain a given number 
 *                   lines.
 *	Arguments: w - the TextSink Object.
 *                 lines - the number of lines.
 *	Returns: the height.
 */

int XawTextSinkMaxHeight(/* w, lines */);
/*
Widget w;
int lines;
*/

/*	Function Name: XawTextSinkSetTabs
 *	Description: Sets the Tab stops.
 *	Arguments: w - the TextSink Object.
 *                 tab_count - the number of tabs in the list.
 *                 tabs - the text positions of the tabs.
 *	Returns: none
 */

void XawTextSinkSetTabs(/* w, tab_count, tabs */);
/*
Widget w;
int tab_count, *tabs;
*/
						  
/*	Function Name: XawTextSinkGetCursorBounds
 *	Description: Finds the bounding box for the insert curor (caret).
 *	Arguments: w - the TextSinkObject.
 *                 rect - an X rectance containing the cursor bounds.
 *	Returns: none (fills in rect).
 */

void XawTextSinkGetCursorBounds(/* w, rect */);
/*
Widget w;
XRectangle * rect;
*/

#endif /* _XawTextSrc_h -- DON'T ADD STUFF AFTER THIS #endif */
