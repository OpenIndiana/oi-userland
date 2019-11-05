/*
* $XConsortium: Text.h,v 1.32 89/10/19 15:01:11 kit Exp $
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

#ifndef _XawText_h
#define _XawText_h

#include <./Xaw3_1TextSink.h>
#include <./Xaw3_1TextSrc.h>

/****************************************************************
 *
 * Text widget
 *
 ****************************************************************/

/* Parameters:

 Name		     Class		RepType		Default Value
 ----		     -----		-------		-------------
 background	     Background		Pixel		XtDefaultBackground
 border		     BorderColor	Pixel		XtDefaultForeground
 borderWidth	     BorderWidth	Dimension	1
 destroyCallback     Callback		Pointer		NULL
 dialogHOffset	     Margin		int		10
 dialogVOffset	     Margin		int		10
 displayCaret	     Output		Boolean		True
 displayPosition     TextPosition	int		0
 editType	     EditType		XtTextEditType	XttextRead
 height		     Height		Dimension	font height
 insertPosition	     TextPosition	int		0
 leftMargin	     Margin		Dimension	2
 mappedWhenManaged   MappedWhenManaged	Boolean		True
 selectTypes	     SelectTypes	Pointer		(internal)
 selection	     Selection		Pointer		empty selection
 sensitive	     Sensitive		Boolean		True
 textSink	     TextSink		Pointer		(none)
 textSource	     TextSource		Pointer		(none)
 width		     Width		Dimension	100
 x		     Position		int		0
 y		     Position		int		0

*/

#define XtEtextScrollNever "never"
#define XtEtextScrollWhenNeeded "whenneeded"
#define XtEtextScrollAlways "always"

#define XtEtextWrapNever "never"
#define XtEtextWrapLine "line"
#define XtEtextWrapWord "word"

#define XtEtextResizeNever "never"
#define XtEtextResizeWidth "width"
#define XtEtextResizeHeight "height"
#define XtEtextResizeBoth "both"

#define XtNautoFill "autoFill"
#define XtNbottomMargin "bottomMargin"
#define XtNdialogHOffset "dialogHOffset"
#define XtNdialogVOffset "dialogVOffset"
#define XtNdisplayCaret "displayCaret"
#define XtNdisplayPosition "displayPosition"
#define XtNinsertPosition "insertPosition"
#define XtNleftMargin "leftMargin"
#define XtNresize "resize"
#define XtNrightMargin "rightMargin"
#define XtNscrollVertical "scrollVertical"
#define XtNscrollHorizontal "scrollHorizontal"
#define XtNselectTypes "selectTypes"
#define XtNselection "selection"
#define XtNtopMargin "topMargin"
#define XtNwrap "wrap"

#define XtCAutoFill "AutoFill"
#define XtCResize "Resize"
#define XtCScroll "Scroll"
#define XtCSelectTypes "SelectTypes"
#define XtCWrap "Wrap"

/* Return Error code for XawTextSearch */

#define XawTextSearchError      (-12345L)

/* Return codes from XawTextReplace */

#define XawEditDone		0
#define XawEditError		1
#define XawPositionError	2

extern Atom FMT8BIT;

/* Class record constants */

extern WidgetClass textWidgetClass;

typedef struct _TextClassRec *TextWidgetClass;
typedef struct _TextRec      *TextWidget;

/* other stuff */

typedef enum { XawtextScrollNever,
	       XawtextScrollWhenNeeded, XawtextScrollAlways} XawTextScrollMode;

typedef enum { XawtextWrapNever, 
	       XawtextWrapLine, XawtextWrapWord} XawTextWrapMode;

typedef enum { XawtextResizeNever, XawtextResizeWidth,
	       XawtextResizeHeight, XawtextResizeBoth} XawTextResizeMode;

typedef enum {XawsdLeft, XawsdRight} XawTextScanDirection;
typedef enum {XawtextRead, XawtextAppend, XawtextEdit} XawTextEditType;
typedef enum {XawselectNull, XawselectPosition, XawselectChar, XawselectWord,
    XawselectLine, XawselectParagraph, XawselectAll} XawTextSelectType;

typedef struct {
    int  firstPos;
    int  length;
    char *ptr;
    Atom format;
    } XawTextBlock, *XawTextBlockPtr; 
#ifdef XAW_BC
/************************************************************
 *
 * This Stuff is only for compatibility, and will go away in 
 * future releases.                                         */

/* preserved for Back Compatability only. */

#define XawTextSource Widget
#define XtTextSource  Widget

#define wordBreak		0x01
#define scrollVertical		0x02
#define scrollHorizontal	0x04
#define scrollOnOverflow	0x08
#define resizeWidth		0x10
#define resizeHeight		0x20
#define editable		0x40

typedef long XtTextPosition;

#define XtTextBlock                XawTextBlock
#define XtTextBlockPtr             XawTextBlockPtr

#define EditDone	           XawEditDone
#define EditError	           XawEditError
#define PositionError	           XawPositionError

#define XtEditDone	           XawEditDone
#define XtEditError	           XawEditError
#define XtPositionError	           XawPositionError

#define XttextRead                 XawtextRead
#define XttextAppend               XawtextAppend
#define XttextEdit                 XawtextEdit
#define XtTextEditType             XawTextEditType
#define XtselectNull               XawselectNull

#define XtselectPosition           XawselectPosition
#define XtselectChar               XawselectChar
#define XtselectWord               XawselectWord
#define XtselectLine               XawselectLine
#define XtselectParagraph          XawselectParagraph
#define XtselectAll                XawselectAll
#define XtTextSelectType           XawTextSelectType

#define XtTextDisableRedisplay     XawTextDisableRedisplay
#define XtTextEnableRedisplay      XawTextEnableRedisplay
#define XtTextGetSource            XawTextGetSource

#define XtTextDisplay              XawTextDisplay
#define XtTextDisplayCaret         XawTextDisplayCaret
#define XtTextSetSelectionArray    XawTextSetSelectionArray
#define XtTextSetLastPos           XawTextSetLastPos
#define XtTextGetSelectionPos      XawTextGetSelectionPos
#define XtTextSetSource            XawTextSetSource
#define XtTextReplace              XawTextReplace
#define XtTextTopPosition          XawTextTopPosition
#define XtTextSetInsertionPoint    XawTextSetInsertionPoint
#define XtTextGetInsertionPoint    XawTextGetInsertionPoint
#define XtTextUnsetSelection       XawTextUnsetSelection
#define XtTextChangeOptions        XawTextChangeOptions
#define XtTextGetOptions           XawTextGetOptions
#define XtTextSetSelection         XawTextSetSelection
#define XtTextInvalidate           XawTextInvalidate

#define XtDiskSourceCreate         XawDiskSourceCreate
#define XtDiskSourceDestroy        XawDiskSourceDestroy
#define XtStringSourceCreate       XawStringSourceCreate
#define XtStringSourceDestroy      XawStringSourceDestroy

extern void XawTextChangeOptions(); /* w, options */
    /* Widget        w;		*/
    /* int    options; */

extern int XawTextGetOptions(); /* w */
    /* Widget        w;		*/

extern void XawTextSetLastPos(); /* w, lastPos */
    /* Widget        w;		*/
    /* XawTextPosition lastPos;  */

/*************************************************************/
#endif /* XAW_BC */

extern void XawTextDisplay(); /* w */
    /* Widget w; */

extern void XawTextEnableRedisplay(); /* w */
    /* Widget w; */

extern void XawTextDisableRedisplay(); /* w */
    /* Widget w; */

extern void XawTextSetSelectionArray(); /* w, sarray */
    /* Widget        w;		*/
    /* SelectionType *sarray;   */

extern void XawTextGetSelectionPos(); /* dpy, w, left, right */
    /* Widget        w;		*/
    /* XawTextPosition *left, *right;    */

extern void XawTextSetSource(); /* dpy, w, source, startPos */
    /* Widget         w;	    */
    /* XawTextSource   source;       */
    /* XawTextPosition startPos;     */

extern int XawTextReplace(); /* w, startPos, endPos, text */
    /* Widget        w;		*/
    /* XawTextPosition   startPos, endPos; */
    /* XawTextBlock      *text; */

extern XawTextPosition XawTextTopPosition(); /* w */
    /* Widget        w;		*/

extern void XawTextSetInsertionPoint(); /*  w, position */
    /* Widget        w;		*/
    /* XawTextPosition position; */

extern XawTextPosition XawTextGetInsertionPoint(); /* w */
    /* Widget        w;		*/

extern void XawTextUnsetSelection(); /* w */
    /* Widget        w;		*/

extern void XawTextSetSelection(); /* w, left, right */
    /* Widget        w;		*/
    /* XawTextPosition left, right; */

extern void XawTextInvalidate(); /* w, from, to */
    /* Widget        w;		*/
    /* XawTextPosition from, to; */

extern Widget XawTextGetSource() ; /* w */
    /* Widget        w;		*/

extern XawTextPosition XawTextSearch() ; /* w, dir, text */
    /* Widget        w;		 */
    /* XawTextScanDirection dir; */
    /* XawTextBlock      *text;  */

/*
 * For R3 compatability only. 
 */

#include <./Xaw3_1AsciiSrc.h>
#include <./Xaw3_1AsciiSink.h>

#endif /* _XawText_h */
/* DON'T ADD STUFF AFTER THIS #endif */
