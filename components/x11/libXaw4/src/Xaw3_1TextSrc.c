#if ( !defined(lint) && !defined(SABER) )
static char Xrcsid[] = "$XConsortium: TextSrc.c,v 1.4 89/10/31 17:12:19 kit Exp $";
#endif 

/*
 * Copyright 1989 Massachusetts Institute of Technology
 *
 * Permission to use, copy, modify, distribute, and sell this software and its
 * documentation for any purpose is hereby granted without fee, provided that
 * the above copyright notice appear in all copies and that both that
 * copyright notice and this permission notice appear in supporting
 * documentation, and that the name of M.I.T. not be used in advertising or
 * publicity pertaining to distribution of the software without specific,
 * written prior permission.  M.I.T. makes no representations about the
 * suitability of this software for any purpose.  It is provided "as is"
 * without express or implied warranty.
 *
 * M.I.T. DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING ALL
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO EVENT SHALL M.I.T.
 * BE LIABLE FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION
 * OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
 * CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 * Author:  Chris Peterson, MIT X Consortium.
 *
 * Much code taken from X11R3 String and Disk Sources.
 */

/*
 * TextSrc.c - TextSrc object. (For use with the text widget).
 *
 */

#include <stdio.h>
#include <ctype.h>
#include <X11/IntrinsicP.h>
#include <X11/StringDefs.h>
#include <./Xaw3_1XawInit.h>
#include <./Xaw3_1TextSrcP.h>

/****************************************************************
 *
 * Full class record constant
 *
 ****************************************************************/

/* Private Data */

#define offset(field) XtOffset(TextSrcObject, textSrc.field)
static XtResource resources[] = {
    {XtNeditType, XtCEditType, XtREditMode, sizeof(XawTextEditType), 
        offset(edit_mode), XtRString, "read"},
};

static void ClassPartInitialize(), SetSelection();
static Boolean ConvertSelection();
static XawTextPosition Search(), Scan(), Read();
static int Replace();

#define SuperClass		(&objectClassRec)
TextSrcClassRec textSrcClassRec = {
  {
/* core_class fields */	
    /* superclass	  	*/	(WidgetClass) SuperClass,
    /* class_name	  	*/	"TextSrc",
    /* widget_size	  	*/	sizeof(TextSrcRec),
    /* class_initialize   	*/	XawInitializeWidgetSet,
    /* class_part_initialize	*/	ClassPartInitialize,
    /* class_inited       	*/	FALSE,
    /* initialize	  	*/	NULL,
    /* initialize_hook		*/	NULL,
    /* realize		  	*/	NULL,
    /* actions		  	*/	NULL,
    /* num_actions	  	*/	0,
    /* resources	  	*/	resources,
    /* num_resources	  	*/	XtNumber(resources),
    /* xrm_class	  	*/	NULLQUARK,
    /* compress_motion	  	*/	FALSE,
    /* compress_exposure  	*/	FALSE,
    /* compress_enterleave	*/	FALSE,
    /* visible_interest	  	*/	FALSE,
    /* destroy		  	*/	NULL,
    /* resize		  	*/	NULL,
    /* expose		  	*/	NULL,
    /* set_values	  	*/	NULL,
    /* set_values_hook		*/	NULL,
    /* set_values_almost	*/	NULL,
    /* get_values_hook		*/	NULL,
    /* accept_focus	 	*/	NULL,
    /* version			*/	XtVersion,
    /* callback_private   	*/	NULL,
    /* tm_table		   	*/	NULL,
    /* query_geometry		*/	NULL,
    /* display_accelerator	*/	NULL,
    /* extension		*/	NULL
  },
/* textSrc_class fields */
  {
    /* Read                     */      Read,
    /* Replace                  */      Replace,
    /* Scan                     */      Scan,
    /* Search                   */      Search,
    /* SetSelection             */      SetSelection,
    /* ConvertSelection         */      ConvertSelection
  }
};

WidgetClass textSrcObjectClass = (WidgetClass)&textSrcClassRec;

static void
ClassPartInitialize(wc)
WidgetClass wc;
{
  register TextSrcObjectClass t_src, superC;

  t_src = (TextSrcObjectClass) wc;
  superC = (TextSrcObjectClass) t_src->object_class.superclass;

/* 
 * We don't need to check for null super since we'll get to TextSrc
 * eventually.
 */

    if (t_src->textSrc_class.Read == XtInheritRead) 
      t_src->textSrc_class.Read = superC->textSrc_class.Read;

    if (t_src->textSrc_class.Replace == XtInheritReplace) 
      t_src->textSrc_class.Replace = superC->textSrc_class.Replace;

    if (t_src->textSrc_class.Scan == XtInheritScan) 
      t_src->textSrc_class.Scan = superC->textSrc_class.Scan;

    if (t_src->textSrc_class.Search == XtInheritSearch) 
      t_src->textSrc_class.Search = superC->textSrc_class.Search;

    if (t_src->textSrc_class.SetSelection == XtInheritSetSelection) 
      t_src->textSrc_class.SetSelection = superC->textSrc_class.SetSelection;

    if (t_src->textSrc_class.ConvertSelection == XtInheritConvertSelection) 
      t_src->textSrc_class.ConvertSelection =
	                               superC->textSrc_class.ConvertSelection;
}

/************************************************************
 *
 * Class specific methods.
 *
 ************************************************************/

/*	Function Name: Read
 *	Description: This function reads the source.
 *	Arguments: w - the TextSrc Object.
 *                 pos - position of the text to retreive.
 * RETURNED        text - text block that will contain returned text.
 *                 length - maximum number of characters to read.
 *	Returns: The number of characters read into the buffer.
 */

/* ARGSUSED */
static XawTextPosition
Read(w, pos, text, length)
Widget w;
XawTextPosition pos;
XawTextBlock *text;	
int length;		
{
  XtAppError(XtWidgetToApplicationContext(w), 
	     "TextSrc Object: No read function is defined.");
}

/*	Function Name: Replace.
 *	Description: Replaces a block of text with new text.
 *	Arguments: src - the Text Source Object.
 *                 startPos, endPos - ends of text that will be removed.
 *                 text - new text to be inserted into buffer at startPos.
 *	Returns: XawEditError.
 */

/*ARGSUSED*/
static int 
Replace (w, startPos, endPos, text)
Widget w;
XawTextPosition startPos, endPos;
XawTextBlock *text;
{
  return(XawEditError);
}

/*	Function Name: Scan
 *	Description: Scans the text source for the number and type
 *                   of item specified.
 *	Arguments: w - the TextSrc Object.
 *                 position - the position to start scanning.
 *                 type - type of thing to scan for.
 *                 dir - direction to scan.
 *                 count - which occurance if this thing to search for.
 *                 include - whether or not to include the character found in
 *                           the position that is returned. 
 *	Returns: EXITS WITH AN ERROR MESSAGE.
 *
 */

/* ARGSUSED */
static 
XawTextPosition 
Scan (w, position, type, dir, count, include)
Widget                w;
XawTextPosition       position;
XawTextScanType       type;
XawTextScanDirection  dir;
int     	      count;
Boolean	              include;
{
  XtAppError(XtWidgetToApplicationContext(w), 
	     "TextSrc Object: No SCAN function is defined.");
}

/*	Function Name: Search
 *	Description: Searchs the text source for the text block passed
 *	Arguments: w - the TextSource Object.
 *                 position - the position to start scanning.
 *                 dir - direction to scan.
 *                 text - the text block to search for.
 *	Returns: XawTextSearchError.
 */

/* ARGSUSED */
static XawTextPosition 
Search(w, position, dir, text)
Widget                w;
XawTextPosition       position;
XawTextScanDirection  dir;
XawTextBlock *        text;
{
  return(XawTextSearchError);
}

/*	Function Name: ConvertSelection
 *	Description: Dummy selection converter.
 *	Arguments: w - the TextSrc object.
 *                 selection - the current selection atom.
 *                 target    - the current target atom.
 *                 type      - the type to conver the selection to.
 * RETURNED        value, length - the return value that has been converted.
 * RETURNED        format    - the format of the returned value.
 *	Returns: TRUE if the selection has been converted.
 *
 */

/* ARGSUSED */
static Boolean
ConvertSelection(w, selection, target, type, value, length, format)
Widget w;
Atom * selection, * target, * type;
caddr_t * value;
unsigned long * length;
int * format;
{
  return(FALSE);
}

/*	Function Name: SetSelection
 *	Description: allows special setting of the selection.
 *	Arguments: w - the TextSrc object.
 *                 left, right - bounds of the selection.
 *                 selection - the selection atom.
 *	Returns: none
 */

/* ARGSUSED */
static void
SetSelection(w, left, right, selection)
Widget w;
XawTextPosition left, right;
Atom selection;
{
  /* This space intentionally left blank. */
}

/************************************************************
 *
 * Public Functions.
 *
 ************************************************************/

/*	Function Name: XawTextSourceRead
 *	Description: This function reads the source.
 *	Arguments: w - the TextSrc Object.
 *                 pos - position of the text to retreive.
 * RETURNED        text - text block that will contain returned text.
 *                 length - maximum number of characters to read.
 *	Returns: The number of characters read into the buffer.
 */

XawTextPosition
XawTextSourceRead(w, pos, text, length)
Widget w;
XawTextPosition pos;
XawTextBlock *text;	
int length;		
{
  TextSrcObjectClass class = (TextSrcObjectClass) w->core.widget_class;

  return((*class->textSrc_class.Read)(w, pos, text, length));
}

/*	Function Name: XawTextSourceReplace.
 *	Description: Replaces a block of text with new text.
 *	Arguments: src - the Text Source Object.
 *                 startPos, endPos - ends of text that will be removed.
 *                 text - new text to be inserted into buffer at startPos.
 *	Returns: XawEditError or XawEditDone.
 */

/*ARGSUSED*/
int 
XawTextSourceReplace (w, startPos, endPos, text)
Widget w;
XawTextPosition startPos, endPos;
XawTextBlock *text;
{
  TextSrcObjectClass class = (TextSrcObjectClass) w->core.widget_class;

  return((*class->textSrc_class.Replace)(w, startPos, endPos, text));
}

/*	Function Name: XawTextSourceScan
 *	Description: Scans the text source for the number and type
 *                   of item specified.
 *	Arguments: w - the TextSrc Object.
 *                 position - the position to start scanning.
 *                 type - type of thing to scan for.
 *                 dir - direction to scan.
 *                 count - which occurance if this thing to search for.
 *                 include - whether or not to include the character found in
 *                           the position that is returned. 
 *	Returns: The position of the text.
 *
 */

XawTextPosition
XawTextSourceScan(w, position, type, dir, count, include)
Widget                w;
XawTextPosition       position;
XawTextScanType       type;
XawTextScanDirection  dir;
int     	      count;
Boolean	              include;
{
  TextSrcObjectClass class = (TextSrcObjectClass) w->core.widget_class;

  return((*class->textSrc_class.Scan)(w, position, type, dir, count, include));
}

/*	Function Name: XawTextSourceSearch
 *	Description: Searchs the text source for the text block passed
 *	Arguments: w - the TextSource Object.
 *                 position - the position to start scanning.
 *                 dir - direction to scan.
 *                 text - the text block to search for.
 *	Returns: The position of the text we are searching for or
 *               XawTextSearchError.
 */

XawTextPosition 
XawTextSourceSearch(w, position, dir, text)
Widget                w;
XawTextPosition       position;
XawTextScanDirection  dir;
XawTextBlock *        text;
{
  TextSrcObjectClass class = (TextSrcObjectClass) w->core.widget_class;

  return((*class->textSrc_class.Search)(w, position, dir, text));
}

/*	Function Name: XawTextSourceConvertSelection
 *	Description: Dummy selection converter.
 *	Arguments: w - the TextSrc object.
 *                 selection - the current selection atom.
 *                 target    - the current target atom.
 *                 type      - the type to conver the selection to.
 * RETURNED        value, length - the return value that has been converted.
 * RETURNED        format    - the format of the returned value.
 *	Returns: TRUE if the selection has been converted.
 *
 */

Boolean
XawTextSourceConvertSelection(w, selection, 
			      target, type, value, length, format)
Widget w;
Atom * selection, * target, * type;
caddr_t * value;
unsigned long * length;
int * format;
{
  TextSrcObjectClass class = (TextSrcObjectClass) w->core.widget_class;

  return((*class->textSrc_class.ConvertSelection)(w, selection, target, type,
						  value, length, format));
}

/*	Function Name: XawTextSourceSetSelection
 *	Description: allows special setting of the selection.
 *	Arguments: w - the TextSrc object.
 *                 left, right - bounds of the selection.
 *                 selection - the selection atom.
 *	Returns: none
 */

void
XawTextSourceSetSelection(w, left, right, selection)
Widget w;
XawTextPosition left, right;
Atom selection;
{
  TextSrcObjectClass class = (TextSrcObjectClass) w->core.widget_class;

  (*class->textSrc_class.SetSelection)(w, left, right, selection);
}
