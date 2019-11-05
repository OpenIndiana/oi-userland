#if ( !defined(lint) && !defined(SABER) )
static char Xrcsid[] = "$XConsortium: AsciiSrc.c,v 1.28 90/01/10 14:25:21 kit Exp $";
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
 * AsciiSrc.c - AsciiSrc object. (For use with the text widget).
 *
 */

#include <stdio.h>
#include <ctype.h>
#include <X11/IntrinsicP.h>
#include <X11/StringDefs.h>

#include <./Xaw3_1XawInit.h>
#include <./Xaw3_1AsciiSrcP.h>
#include <X11/Xmu/Misc.h>
#include <X11/Xmu/CharSet.h>

#ifdef ASCII_STRING
#include <./Xaw3_1AsciiText.h> /* for Widget Classes. */
#endif
#ifdef ASCII_DISK)
#include <./Xaw3_1AsciiText.h> /* for Widget Classes. */
#endif
/****************************************************************
 *
 * Full class record constant
 *
 ****************************************************************/

/* Private Data */

static int magic_value = MAGIC_VALUE;

#define offset(field) XtOffset(AsciiSrcObject, ascii_src.field)

static XtResource resources[] = {
    {XtNstring, XtCString, XtRString, sizeof (char *),
       offset(string), XtRString, NULL},
    {XtNtype, XtCType, XtRAsciiType, sizeof (XawAsciiType),
       offset(type), XtRImmediate, (XtPointer)XawAsciiString},
    {XtNdataCompression, XtCDataCompression, XtRBoolean, sizeof (Boolean),
       offset(data_compression), XtRImmediate, (XtPointer) TRUE},
    {XtNpieceSize, XtCPieceSize, XtRInt, sizeof (XawTextPosition),
       offset(piece_size), XtRImmediate, (XtPointer) BUFSIZ},
    {XtNcallback, XtCCallback, XtRCallback, sizeof(XtPointer), 
       offset(callback), XtRCallback, (XtPointer)NULL},
    {XtNuseStringInPlace, XtCUseStringInPlace, XtRBoolean, sizeof (Boolean),
       offset(use_string_in_place), XtRImmediate, (XtPointer) FALSE},
    {XtNlength, XtCLength, XtRInt, sizeof (int),
       offset(ascii_length), XtRInt, (XtPointer) &magic_value},

#ifdef ASCII_DISK
    {XtNfile, XtCFile, XtRString, sizeof (String),
       offset(filename), XtRString, NULL},
#endif /* ASCII_DISK */
};

static XawTextPosition Scan(), Search(), ReadText();
static int ReplaceText();
static Piece * FindPiece(), * AllocNewPiece();
static FILE * InitStringOrFile();
static void FreeAllPieces(), RemovePiece(), BreakPiece(), LoadPieces();
static void RemoveOldStringOrFile(),  CvtStringToAsciiType();
static void ClassInitialize(), Initialize(), Destroy(), GetValuesHook();
static String MyStrncpy(), StorePiecesInString();
static Boolean SetValues(), WriteToFile();
extern char *tmpnam();
#ifndef SYSV
void bcopy();
#endif
extern int errno, sys_nerr;
extern char* sys_errlist[];

#define superclass		(&textSrcClassRec)
AsciiSrcClassRec asciiSrcClassRec = {
  {
/* core_class fields */	
    /* superclass	  	*/	(WidgetClass) superclass,
    /* class_name	  	*/	"AsciiSrc",
    /* widget_size	  	*/	sizeof(AsciiSrcRec),
    /* class_initialize   	*/	ClassInitialize,
    /* class_part_initialize	*/	NULL,
    /* class_inited       	*/	FALSE,
    /* initialize	  	*/	Initialize,
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
    /* destroy		  	*/	Destroy,
    /* resize		  	*/	NULL,
    /* expose		  	*/	NULL,
    /* set_values	  	*/	SetValues,
    /* set_values_hook		*/	NULL,
    /* set_values_almost	*/	NULL,
    /* get_values_hook		*/	GetValuesHook,
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
    /* Read                     */      ReadText,
    /* Replace                  */      ReplaceText,
    /* Scan                     */      Scan,
    /* Search                   */      Search,
    /* SetSelection             */      XtInheritSetSelection,
    /* ConvertSelection         */      XtInheritConvertSelection
  },
/* asciiSrc_class fields */
  {
    /* Keep the compiler happy */       NULL
  }
};

WidgetClass asciiSrcObjectClass = (WidgetClass)&asciiSrcClassRec;

/************************************************************
 *
 * Semi-Public Interfaces.
 *
 ************************************************************/

/*      Function Name: ClassInitialize
 *      Description: Class Initialize routine, called only once.
 *      Arguments: none.
 *      Returns: none.
 */

static void
ClassInitialize()
{
  XawInitializeWidgetSet();
  XtAddConverter( XtRString, XtRAsciiType, CvtStringToAsciiType,
		 NULL, (Cardinal) 0);
}

/*      Function Name: Initialize
 *      Description: Initializes the simple menu widget
 *      Arguments: request - the widget requested by the argument list.
 *                 new     - the new widget with both resource and non
 *                           resource values.
 *      Returns: none.
 */

/* ARGSUSED */
static void
Initialize(request, new)
Widget request, new;
{
  AsciiSrcObject src = (AsciiSrcObject) new;
  FILE * file;

/*
 * Set correct flags (override resources) depending upon widget class.
 */

#ifdef ASCII_DISK
  if (XtIsSubclass(XtParent(new), asciiDiskWidgetClass)) {
    src->ascii_src.type = XawAsciiFile;
    src->ascii_src.string = src->ascii_src.filename;
  }
#endif

#ifdef ASCII_STRING
  if (XtIsSubclass(XtParent(new), asciiStringWidgetClass)) {
    src->ascii_src.use_string_in_place = TRUE;
    src->ascii_src.type = XawAsciiString;
  }
#endif

  src->ascii_src.changes = FALSE;
  src->ascii_src.allocated_string = FALSE;

  file = InitStringOrFile(src);
  LoadPieces(src, file, NULL);

  if (file != NULL) fclose(file);

  if ( src->ascii_src.type == XawAsciiString )
      src->ascii_src.string = NULL;
}

/*	Function Name: ReadText
 *	Description: This function reads the source.
 *	Arguments: w - the AsciiSource widget.
 *                 pos - position of the text to retreive.
 * RETURNED        text - text block that will contain returned text.
 *                 length - maximum number of characters to read.
 *	Returns: The number of characters read into the buffer.
 */

static XawTextPosition
ReadText(w, pos, text, length)
Widget w;
XawTextPosition pos;
XawTextBlock *text;	
int length;		
{
  AsciiSrcObject src = (AsciiSrcObject) w;
  XawTextPosition count, start;
  Piece * piece = FindPiece(src, pos, &start);
    
  text->firstPos = pos;
  text->ptr = piece->text + (pos - start);
  count = piece->used - (pos - start);
  text->length = (length > count) ? count : length;
  return(pos + text->length);
}

/*	Function Name: ReplaceText.
 *	Description: Replaces a block of text with new text.
 *	Arguments: w - the AsciiSource widget.
 *                 startPos, endPos - ends of text that will be removed.
 *                 text - new text to be inserted into buffer at startPos.
 *	Returns: XawEditError or XawEditDone.
 */

/*ARGSUSED*/
static int 
ReplaceText (w, startPos, endPos, text)
Widget w;
XawTextPosition startPos, endPos;
XawTextBlock *text;
{
  AsciiSrcObject src = (AsciiSrcObject) w;
  Piece *start_piece, *end_piece, *temp_piece;
  XawTextPosition start_first, end_first;
  int length, firstPos;

/*
 * Editing a read only source is not allowed.
 */

  if (src->text_src.edit_mode == XawtextRead) 
    return(XawEditError);

  start_piece = FindPiece(src, startPos, &start_first);
  end_piece = FindPiece(src, endPos, &end_first);

  src->ascii_src.changes = TRUE; /* We have changed the buffer. */

  XtCallCallbacks(w, XtNcallback, NULL);

/* 
 * Remove Old Stuff. 
 */

  if (start_piece != end_piece) {
    temp_piece = start_piece->next;

/*
 * If empty and not the only piece then remove it. 
 */

    if ( ((start_piece->used = startPos - start_first) == 0) &&
	 !((start_piece->next == NULL) && (start_piece->prev == NULL)) )
      RemovePiece(src, start_piece);

    while (temp_piece != end_piece) {
      temp_piece = temp_piece->next;
      RemovePiece(src, temp_piece->prev);
    }
    end_piece->used -= endPos - end_first;
    if (end_piece->used != 0)
      MyStrncpy(end_piece->text, (end_piece->text + endPos - end_first),
		(int) end_piece->used);
  }
  else {			/* We are fully in one piece. */
    if ( (start_piece->used -= endPos - startPos) == 0) {
      if ( !((start_piece->next == NULL) && (start_piece->prev == NULL)) )
	RemovePiece(src, start_piece);
    }
    else {
      MyStrncpy(start_piece->text + (startPos - start_first),
		start_piece->text + (endPos - start_first),
		(int) (start_piece->used - (startPos - start_first)) );
      if ( src->ascii_src.use_string_in_place && 
	   ((src->ascii_src.length - (endPos - startPos)) < 
	    (src->ascii_src.piece_size - 1)) ) 
	start_piece->text[src->ascii_src.length - (endPos - startPos)] = '\0';
    }
  }

  src->ascii_src.length += -(endPos - startPos) + text->length;

  if ( text->length != 0) {

    /* 
     * Put in the New Stuff.
     */
    
    start_piece = FindPiece(src, startPos, &start_first);
    
    length = text->length;
    firstPos = text->firstPos;
    
    while (length > 0) {
      char * ptr;
      int fill;
      
      if (src->ascii_src.use_string_in_place) {
	if (start_piece->used == (src->ascii_src.piece_size - 1)) {
	  /*
	   * If we are in ascii string emulation mode. Then the
	   *  string is not allowed to grow.
	   */
	  start_piece->used = src->ascii_src.length = 
	                                         src->ascii_src.piece_size - 1;
	  start_piece->text[src->ascii_src.length] = '\0';
	  return(XawEditError);
	}
      }


      if (start_piece->used == src->ascii_src.piece_size) {
	BreakPiece(src, start_piece);
	start_piece = FindPiece(src, startPos, &start_first);
      }

      fill = Min((int)(src->ascii_src.piece_size - start_piece->used), length);
      
      ptr = start_piece->text + (startPos - start_first);
      MyStrncpy(ptr + fill, ptr, 
		(int) start_piece->used - (startPos - start_first));
      strncpy(ptr, text->ptr + firstPos, fill);
      
      startPos += fill;
      firstPos += fill;
      start_piece->used += fill;
      length -= fill;
    }
  }

  if (src->ascii_src.use_string_in_place)
    start_piece->text[start_piece->used] = '\0';

  return(XawEditDone);
}

/*	Function Name: Scan
 *	Description: Scans the text source for the number and type
 *                   of item specified.
 *	Arguments: w - the AsciiSource widget.
 *                 position - the position to start scanning.
 *                 type - type of thing to scan for.
 *                 dir - direction to scan.
 *                 count - which occurance if this thing to search for.
 *                 include - whether or not to include the character found in
 *                           the position that is returned. 
 *	Returns: the position of the item found.
 *
 * Note: While there are only 'n' characters in the file there are n+1 
 *       possible cursor positions (one before the first character and
 *       one after the last character.
 */

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
  AsciiSrcObject src = (AsciiSrcObject) w;
  register int inc;
  Piece * piece;
  XawTextPosition first, first_eol_position;
  register char * ptr;

  if (type == XawstAll) {	/* Optomize this common case. */
    if (dir == XawsdRight)
      return(src->ascii_src.length);
    return(0);			/* else. */
  }

  if (position > src->ascii_src.length)
    position = src->ascii_src.length;

  if ( dir == XawsdRight ) {
    if (position == src->ascii_src.length)
/*
 * Scanning right from src->ascii_src.length???
 */
      return(src->ascii_src.length);
    inc = 1;
  }
  else {
    if (position == 0)
      return(0);		/* Scanning left from 0??? */
    inc = -1;
    position--;
  }

  piece = FindPiece(src, position, &first);

/*
 * If the buffer is empty then return 0. 
 */

  if ( piece->used == 0 ) return(0); 

  ptr = (position - first) + piece->text;

  switch (type) {
  case XawstEOL: 
  case XawstParagraph: 
  case XawstWhiteSpace: 
    for ( ; count > 0 ; count-- ) {
      Boolean non_space = FALSE, first_eol = TRUE;
      while (TRUE) {
	register unsigned char c = *ptr;

	ptr += inc;
	position += inc;
	
	if (type == XawstWhiteSpace) {
	  if (isspace(c)) {
	    if (non_space) 
	      break;
	  }
	  else
	    non_space = TRUE;
	}
	else if (type == XawstEOL) {
	  if (c == '\n') break;
	}
	else { /* XawstParagraph */
	  if (first_eol) {
	    if (c == '\n') {
	      first_eol_position = position;
	      first_eol = FALSE;
	    }
	  }
	  else
	    if ( c == '\n') 
	      break;
	    else if ( !isspace(c) )
	      first_eol = TRUE;
	}
	      

	if ( ptr < piece->text ) {
	  piece = piece->prev;
	  if (piece == NULL)	/* Begining of text. */
	    return(0);
	  ptr = piece->text + piece->used - 1;
	}
	else if ( ptr >= (piece->text + piece->used) ) {
	  piece = piece->next;
	  if (piece == NULL)	/* End of text. */
	    return(src->ascii_src.length);
	  ptr = piece->text;
	}
      }
    }
    if (!include) {
      if ( type == XawstParagraph)
	position = first_eol_position;
      position -= inc;
    }
    break;
  case XawstPositions: 
    position += count * inc;
    break;
/*  case XawstAll:		---- handled in special code above */
  }

  if ( dir == XawsdLeft )
    position++;

  if (position >= src->ascii_src.length)
    return(src->ascii_src.length);
  if (position < 0)
    return(0);

  return(position);
}

/*	Function Name: Search
 *	Description: Searchs the text source for the text block passed
 *	Arguments: w - the AsciiSource Widget.
 *                 position - the position to start scanning.
 *                 dir - direction to scan.
 *                 text - the text block to search for.
 *	Returns: the position of the item found.
 */

static XawTextPosition 
Search(w, position, dir, text)
Widget                w;
XawTextPosition       position;
XawTextScanDirection  dir;
XawTextBlock *        text;
{
  AsciiSrcObject src = (AsciiSrcObject) w;
  register int inc, count = 0;
  register char * ptr;
  Piece * piece;
  char * buf;
  XawTextPosition first;

  if ( dir == XawsdRight )
    inc = 1;
  else {
    inc = -1;
    if (position == 0)
      return(XawTextSearchError);	/* scanning left from 0??? */
    position--;
  }

  buf = XtMalloc(sizeof(unsigned char) * text->length);
  strncpy(buf, (text->ptr + text->firstPos), text->length);
  piece = FindPiece(src, position, &first);
  ptr = (position - first) + piece->text;

  while (TRUE) {
    if (*ptr == ((dir == XawsdRight) ? *(buf + count) 
		                     : *(buf + text->length - count - 1)) ) {
      if (count == (text->length - 1))
	break;
      else
	count++;
    }
    else {
      if (count != 0) {
	position -=inc * count;
	ptr -= inc * count;
      }
      count = 0;
    }

    ptr += inc;
    position += inc;
    
    while ( ptr < piece->text ) {
      piece = piece->prev;
      if (piece == NULL) {	/* Begining of text. */
	XtFree(buf);
	return(XawTextSearchError);
      }
      ptr = piece->text + piece->used - 1;
    }
   
    while ( ptr >= (piece->text + piece->used) ) {
      piece = piece->next;
      if (piece == NULL) {	/* End of text. */
	XtFree(buf);
	return(XawTextSearchError);
      }
      ptr = piece->text;
    }
  }

  XtFree(buf);
  if (dir == XawsdLeft)
    return(position);
  return(position - (text->length - 1));
}

/*	Function Name: SetValues
 *	Description: Sets the values for the AsciiSource.
 *	Arguments: current - current state of the widget.
 *                 request - what was requested.
 *                 new - what the widget will become.
 *	Returns: True if redisplay is needed.
 */

/* ARGSUSED */
static Boolean
SetValues(current, request, new)
Widget current, request, new;
{
  AsciiSrcObject src =      (AsciiSrcObject) new;
  AsciiSrcObject old_src = (AsciiSrcObject) current;
  Boolean total_reset = FALSE;
  FILE * file;

  if ( old_src->ascii_src.use_string_in_place != 
       src->ascii_src.use_string_in_place ) {
      XtAppWarning( XtWidgetToApplicationContext(new),
	   "AsciiSrc: The XtNuseStrinInPlace resources may not be changed.");
       src->ascii_src.use_string_in_place = 
	   old_src->ascii_src.use_string_in_place;
  }

  if ( (old_src->ascii_src.string != src->ascii_src.string) ||
       (old_src->ascii_src.type != src->ascii_src.type) ) {
    if (old_src->ascii_src.string == src->ascii_src.string) {
      /* Fool it into not freeing the string */
      src->ascii_src.allocated_string = FALSE; 
      RemoveOldStringOrFile(old_src);        /* remove old info. */
      src->ascii_src.allocated_string = TRUE;
    }
    else {
      RemoveOldStringOrFile(old_src);        /* remove old info. */
      src->ascii_src.allocated_string = FALSE;
    }

    file = InitStringOrFile(src);    /* Init new info. */
    LoadPieces(src, file, NULL);    /* load new info into internal buffers. */
    if (file != NULL) fclose(file);
    XawTextSetSource( XtParent(new), new, 0);   /* Tell text widget
						   what happened. */
    if ( src->ascii_src.type == XawAsciiString )
	src->ascii_src.string = NULL;

    total_reset = TRUE;
  }

  if ( old_src->ascii_src.ascii_length != src->ascii_src.ascii_length ) 
      src->ascii_src.piece_size = src->ascii_src.ascii_length;

  if ( !total_reset && 
      (old_src->ascii_src.piece_size != src->ascii_src.piece_size) ) {
      String string = StorePiecesInString(old_src);
      FreeAllPieces(old_src);
      LoadPieces(src, NULL, string);
      XtFree(string);
  }

  return(FALSE);
}

/*	Function Name: GetValuesHook
 *	Description: This is a get values hook routine that sets the
 *                   values specific to the ascii source.
 *	Arguments: w - the AsciiSource Widget.
 *                 args - the argument list.
 *                 num_args - the number of args.
 *	Returns: none.
 */

static void
GetValuesHook(w, args, num_args)
Widget w;
ArgList args;
Cardinal * num_args;
{
  AsciiSrcObject src = (AsciiSrcObject) w;
  register int i;

  if (src->ascii_src.use_string_in_place) 
      return;

  if (src->ascii_src.type == XawAsciiString) {
    for (i = 0; i < *num_args ; i++ ) 
      if (streq(args[i].name, XtNstring)) {
	if (XawAsciiSave(w))	/* If save sucessful. */
	  *((char **) args[i].value) = src->ascii_src.string;
	break;
      }
  }
}    

/*	Function Name: Destroy
 *	Description: Destroys an ascii source (frees all data)
 *	Arguments: src - the Ascii source Widget to free.
 *	Returns: none.
 */

static void 
Destroy (w)
Widget w;
{
  RemoveOldStringOrFile((AsciiSrcObject) w);
}

/************************************************************
 *
 * Public routines 
 *
 ************************************************************/

/*	Function Name: XawAsciiSourceFreeString
 *	Description: Frees the string returned by a get values call
 *                   on the string when the source is of type string.
 *	Arguments: w - the AsciiSrc widget.
 *	Returns: none.
 */

void
XawAsciiSourceFreeString(w)
Widget w;
{
  AsciiSrcObject src = (AsciiSrcObject) w;

  if (src->ascii_src.allocated_string) {
    src->ascii_src.allocated_string = FALSE;
    XtFree(src->ascii_src.string);
  }
}

/*	Function Name: XawAsciiSave
 *	Description: Saves all the pieces into a file or string as required.
 *	Arguments: w - the asciiSrc Widget.
 *	Returns: TRUE if the save was successful.
 */

Boolean
XawAsciiSave(w)
Widget w;
{
  AsciiSrcObject src = (AsciiSrcObject) w;

/*
 * If using the string in place then there is no need to play games
 * to get the internal info into a readable string.
 */

  if (src->ascii_src.use_string_in_place) 
    return(TRUE);

  if (src->ascii_src.type == XawAsciiFile) {
    char * string;

    if (!src->ascii_src.changes) 		/* No changes to save. */
      return(TRUE);

    string = StorePiecesInString(src);

    if (WriteToFile(src, string, src->ascii_src.string) == FALSE) {
      XtFree(string);
      return(FALSE);
    }
    XtFree(string);
  }
  else {			/* This is a string widget. */
    if (src->ascii_src.allocated_string == TRUE) 
      XtFree(src->ascii_src.string);
    else
      src->ascii_src.allocated_string = TRUE;
    
    src->ascii_src.string = StorePiecesInString(src);
  }
  src->ascii_src.changes = FALSE;
  return(TRUE);
}

/*	Function Name: XawAsciiSaveAsFile
 *	Description: Save the current buffer as a file.
 *	Arguments: w - the AsciiSrc widget.
 *                 name - name of the file to save this file into.
 *	Returns: True if the save was sucessful.
 */

Boolean
XawAsciiSaveAsFile(w, name)
Widget w;
String name;
{
  AsciiSrcObject src = (AsciiSrcObject) w;
  String string;
  Boolean ret;

  string = StorePiecesInString(src); 

  ret = WriteToFile(src, string, name);
  XtFree(string);
  return(ret);
}

/*	Function Name: XawAsciiSourceChanged
 *	Description: Returns true if the source has changed since last saved.
 *	Arguments: w - the ascii source widget.
 *	Returns: a Boolean (see description).
 */

Boolean 
XawAsciiSourceChanged(w)
Widget w;
{
  return( ((AsciiSrcObject) w)->ascii_src.changes );
}
  
/************************************************************
 *
 * Private Functions.
 *
 ************************************************************/

static void
RemoveOldStringOrFile(src) 
AsciiSrcObject src;
{
  FreeAllPieces(src);

  if (src->ascii_src.allocated_string) 
    XtFree(src->ascii_src.string);
}

/*	Function Name: WriteToFile
 *	Description: Write the string specified to the begining of the file
 *                   specified.
 *	Arguments: w - the widget.          (for error messages only)
 *                 string - string to write.
 *                 name - the name of the file
 *                 file - file to write it to.
 *	Returns: returns TRUE if sucessful, FALSE otherwise.
 */

static Boolean
WriteToFile(src, string, name)
AsciiSrcObject src;
String string, name;
{
  unsigned char buf[BUFSIZ];
  int fd;
  
  if ( ((fd = creat(name, 0666)) == -1 ) ||
       (write(fd, string, sizeof(unsigned char) * strlen(string)) == -1) ) {
    sprintf((char *)buf, "Error, while attempting to write to the file %s.", name);
    XtAppWarning(XtWidgetToApplicationContext((Widget) src), (const char *)buf);
    return(FALSE);
  }

  if ( close(fd) == -1 ) {
    sprintf((char *)buf, "Error, while attempting to close the file %s.", name);
    XtAppWarning(XtWidgetToApplicationContext((Widget) src), (const char *)buf); 
    return(FALSE);
  }
  return(TRUE);
}

/*	Function Name: StorePiecesInString
 *	Description: store the pieces in memory into a standard ascii string.
 *	Arguments: data - the ascii pointer data.
 *	Returns: none.
 */

static String
StorePiecesInString(src)
AsciiSrcObject src;
{
  String string;
  XawTextPosition first;
  Piece * piece;

  string = XtMalloc(sizeof(unsigned char) * src->ascii_src.length + 1);
  
  for (first = 0, piece = src->ascii_src.first_piece ; piece != NULL; 
       first += piece->used, piece = piece->next) 
    strncpy(string + first, piece->text, piece->used);

  string[src->ascii_src.length] = '\0';	/* NULL terminate this sucker. */

/*
 * This will refill all pieces to capacity. 
 */

  if (src->ascii_src.data_compression) {	
    FreeAllPieces(src);
    LoadPieces(src, NULL, string);
  }

  return(string);
}

/*	Function Name: InitStringOrFile.
 *	Description: Initializes the string or file.
 *	Arguments: src - the AsciiSource.
 *	Returns: none - May exit though.
 */

static FILE *
InitStringOrFile(src)
AsciiSrcObject src;
{
    char * open_mode;
    FILE * file;

    if (src->ascii_src.type == XawAsciiString) {
	if (src->ascii_src.string == NULL)
	    src->ascii_src.length = 0;
	else 
	    src->ascii_src.length = strlen(src->ascii_src.string);
	
	if (src->ascii_src.use_string_in_place) {
	    if (src->ascii_src.ascii_length == MAGIC_VALUE) 
		src->ascii_src.piece_size = src->ascii_src.length;
	    else
		src->ascii_src.piece_size = src->ascii_src.ascii_length + 1;
	}
		
	return(NULL);
    }

/*
 * type is XawAsciiFile.
 */
    
    src->ascii_src.is_tempfile = FALSE;
    
    switch (src->text_src.edit_mode) {
    case XawtextRead:
	if (src->ascii_src.string == NULL)
	    XtErrorMsg("NoFile", "asciiSourceCreate", "XawError",
		     "Creating a read only disk widget and no file specified.",
		       NULL, 0);
	open_mode = "r";
	break;
    case XawtextAppend:
    case XawtextEdit:
	if (src->ascii_src.string == NULL) {
	    src->ascii_src.string = tmpnam (XtMalloc((unsigned)TMPSIZ));
	    src->ascii_src.is_tempfile = TRUE;
	} 
	else {
	    if (!src->ascii_src.allocated_string) {
		src->ascii_src.allocated_string = TRUE;
		src->ascii_src.string = XtNewString(src->ascii_src.string);
	    }
	    open_mode = "r+";
	}
	
	break;
    default:
	XtErrorMsg("badMode", "asciiSourceCreate", "XawError",
		"Bad editMode for ascii source; must be Read, Append or Edit.",
		   NULL, NULL);
    }
    
    if (!src->ascii_src.is_tempfile) {
	if ((file = fopen(src->ascii_src.string, open_mode)) == 0) {
	    String params[2];
	    Cardinal num_params = 2;
	    
	    params[0] = src->ascii_src.string;
	    if (errno <= sys_nerr)
		params[1] = sys_errlist[errno];
	    else {
		char msg[11];
		sprintf(msg, "errno=%.4d", errno);
		params[1] = msg;
	    }
	    XtErrorMsg("openError", "asciiSourceCreate", "XawError",
		       "Cannot open source file %s; %s", params, &num_params);
	}
	(void) fseek(file, 0L, 2);
	src->ascii_src.length = ftell (file); 
    } 
    else {
	src->ascii_src.length = 0;
	return(NULL);
    }
    
    return(file);
}

static void
LoadPieces(src, file, string)
AsciiSrcObject src;
FILE * file;
char * string;
{
  char *local_str, *ptr;
  register Piece * piece = NULL;
  XawTextPosition left;

  if (string == NULL) {
    if (src->ascii_src.type == XawAsciiFile) {
      local_str = XtMalloc((src->ascii_src.length + 1) *sizeof(unsigned char));
      if (src->ascii_src.length != 0) {
	fseek(file, 0L, 0);
	if ( fread(local_str, sizeof(unsigned char),
		   src->ascii_src.length, file) != src->ascii_src.length ) 
	  XtErrorMsg("readError", "asciiSourceCreate", "XawError",
		     "fread returned error.", NULL, NULL);
      }
      local_str[src->ascii_src.length] = '\0';
    }
    else
      local_str = src->ascii_src.string;
  }
  else
    local_str = string;

/*
 * If we are using teh string in place then set the other fields as follows:
 *
 * piece_size = length;
 * piece->used = src->ascii_src.length;
 */
  
  if (src->ascii_src.use_string_in_place) {
    piece = AllocNewPiece(src, piece);
    piece->used = Min(src->ascii_src.length, src->ascii_src.piece_size);
    piece->text = src->ascii_src.string;
    return;
  }

  ptr = local_str;
  left = src->ascii_src.length;

  do {
    piece = AllocNewPiece(src, piece);

    piece->text = XtMalloc(src->ascii_src.piece_size * sizeof(unsigned char));
    piece->used = Min(left, src->ascii_src.piece_size);
    if (piece->used != 0)
      strncpy(piece->text, ptr, piece->used);

    left -= piece->used;
    ptr += piece->used;
  } while (left > 0);

  if ( (src->ascii_src.type == XawAsciiFile) && (string == NULL) )
    XtFree(local_str);
}

/*	Function Name: AllocNewPiece
 *	Description: Allocates a new piece of memory.
 *	Arguments: src - The AsciiSrc Widget.
 *                 prev - the piece just before this one, or NULL.
 *	Returns: the allocated piece.
 */

static Piece *
AllocNewPiece(src, prev)
AsciiSrcObject src;
Piece * prev;
{
  Piece * piece = XtNew(Piece);

  if (prev == NULL) {
    src->ascii_src.first_piece = piece;
    piece->next = NULL;
  }
  else {
    if (prev->next != NULL)
      (prev->next)->prev = piece;
    piece->next = prev->next;
    prev->next = piece;
  }
  
  piece->prev = prev;

  return(piece);
}

/*	Function Name: FreeAllPieces
 *	Description: Frees all the pieces
 *	Arguments: src - The AsciiSrc Widget.
 *	Returns: none.
 */

static void 
FreeAllPieces(src)
AsciiSrcObject src;
{
  Piece * next, * first = src->ascii_src.first_piece;

  if (first->prev != NULL)
    printf("Programmer Botch in FreeAllPieces, there may be a memory leak.\n");

  for ( ; first != NULL ; first = next ) {
    next = first->next;
    RemovePiece(src, first);
  }
}
  
/*	Function Name: RemovePiece
 *	Description: Removes a piece from the list.
 *	Arguments: 
 *                 piece - the piece to remove.
 *	Returns: none.
 */

static void
RemovePiece(src, piece)
AsciiSrcObject src;
Piece * piece;
{
  if (piece->prev == NULL)
    src->ascii_src.first_piece = piece->next;
  else
    (piece->prev)->next = piece->next;

  if (piece->next != NULL)
    (piece->next)->prev = piece->prev;

  if (src->ascii_src.allocated_string)
    XtFree(piece->text);

  XtFree((char *)piece);
}

/*	Function Name: FindPiece
 *	Description: Finds the piece containing the position indicated.
 *	Arguments: src - The AsciiSrc Widget.
 *                 position - the position that we are searching for.
 * RETURNED        first - the position of the first character in this piece.
 *	Returns: piece - the piece that contains this position.
 */

static Piece *
FindPiece(src, position, first)
AsciiSrcObject src;
XawTextPosition position, *first;
{
  Piece * old_piece, * piece = src->ascii_src.first_piece;
  XawTextPosition temp;

  for ( temp = 0 ; piece != NULL ; temp += piece->used, piece = piece->next ) {
    *first = temp;
    old_piece = piece;

    if ((temp + piece->used) > position) 
      return(piece);
  }
  return(old_piece);	  /* if we run off the end the return the last piece */
}
    
/*	Function Name: MyStrncpy
 *	Description: Just like string copy, but slower and will always
 *                   work on overlapping strings.
 *	Arguments: (same as strncpy) - s1, s2 - strings to copy (2->1).
 *                  n - the number of chars to copy.
 *	Returns: s1.
 */

static String
MyStrncpy(s1, s2, n)
char * s1, * s2;
int n;
{
  char * temp = XtMalloc(sizeof(unsigned char) * n);

  strncpy(temp, s2, n);		/* Saber has a bug that causes it to generate*/
  strncpy(s1, temp, n);		/* a bogus warning message here (CDP 6/32/89)*/
  XtFree(temp);
  return(s1);
}
  
/*	Function Name: BreakPiece
 *	Description: Breaks a full piece into two new pieces.
 *	Arguments: src - The AsciiSrc Widget.
 *                 piece - the piece to break.
 *	Returns: none.
 */

#define HALF_PIECE (src->ascii_src.piece_size/2)

static void
BreakPiece(src, piece)
AsciiSrcObject src;
Piece * piece;
{
  Piece * new = AllocNewPiece(src, piece);
  
  new->text = XtMalloc(src->ascii_src.piece_size * sizeof(unsigned char));
  strncpy(new->text, piece->text + HALF_PIECE,
	  src->ascii_src.piece_size - HALF_PIECE);
  piece->used = HALF_PIECE;
  new->used = src->ascii_src.piece_size - HALF_PIECE; 
}

/* ARGSUSED */
static void
CvtStringToAsciiType(args, num_args, fromVal, toVal)
XrmValuePtr *args;		/* unused */
Cardinal	*num_args;	/* unused */
XrmValuePtr	fromVal;
XrmValuePtr	toVal;
{
  static XawAsciiType type;
  static XrmQuark  XtQEstring;
  static XrmQuark  XtQEfile;
  static int	  haveQuarks = FALSE;
  XrmQuark q;
  char lowerName[BUFSIZ];

  if (!haveQuarks) {
    XtQEstring = XrmStringToQuark(XtEstring);
    XtQEfile   = XrmStringToQuark(XtEfile);
    haveQuarks = TRUE;
  }

  XmuCopyISOLatin1Lowered(lowerName, (char *) fromVal->addr);
  q = XrmStringToQuark(lowerName);

  if (q == XtQEstring) type = XawAsciiString;
  if (q == XtQEfile)  type = XawAsciiFile;

  (*toVal).size = sizeof(XawAsciiType);
  (*toVal).addr = (caddr_t) &type;
  return;
}

#if (defined(ASCII_STRING) || defined(ASCII_DISK))
#  include <./Xaw3_1Cardinals.h>
#endif

#ifdef ASCII_STRING
/************************************************************
 *
 * Compatability functions.
 *
 ************************************************************/
 
/*	Function Name: AsciiStringSourceCreate
 *	Description: Creates a string source.
 *	Arguments: parent - the widget that will own this source.
 *                 args, num_args - the argument list.
 *	Returns: a pointer to the new text source.
 */

Widget
XawStringSourceCreate(parent, args, num_args)
Widget parent;
ArgList args;
Cardinal num_args;
{
  XawTextSource src;
  ArgList ascii_args;
  Arg temp[2];

  XtSetArg(temp[0], XtNtype, XawAsciiString);
  XtSetArg(temp[1], XtNuseStringInPlace, TRUE);
  ascii_args = XtMergeArgLists(temp, TWO, args, num_args);

  src = XtCreateWidget("genericAsciiString", asciiSrcObjectClass, parent,
		       ascii_args, num_args + TWO);
  XtFree((char *)ascii_args);
  return(src);
}

/*
 * This is hacked up to try to emulate old functionality, it
 * may not work, as I have not old code to test it on.
 *
 * Chris D. Peterson  8/31/89.
 */

void 
XawTextSetLastPos (w, lastPos)
Widget w;
XawTextPosition lastPos;
{
  AsciiSrcObject src = (AsciiSrcObject) XawTextGetSource(w);

  src->ascii_src.piece_size = lastPos;
}
#endif /* ASCII_STRING */

#ifdef ASCII_DISK
/*	Function Name: AsciiDiskSourceCreate
 *	Description: Creates a disk source.
 *	Arguments: parent - the widget that will own this source.
 *                 args, num_args - the argument list.
 *	Returns: a pointer to the new text source.
 */

Widget
XawDiskSourceCreate(parent, args, num_args)
Widget parent;
ArgList args;
Cardinal num_args;
{
  XawTextSource src;
  ArgList ascii_args;
  Arg temp[1];
  register int i;

  XtSetArg(temp[0], XtNtype, XawAsciiFile);

  for (i = 0; i < num_args; i++) 
    if (streq(args[i].name, XtNfile) || streq(args[i].name, XtCFile)) 
      args[i].name = XtNstring;

  ascii_args = XtMergeArgLists(temp, ONE, args, num_args);
  src = XtCreateWidget("genericAsciiDisk", asciiSrcObjectClass, parent,
		       ascii_args, num_args + ONE);
  XtFree((char *)ascii_args);
  return(src);
}
#endif /* ASCII_DISK */
