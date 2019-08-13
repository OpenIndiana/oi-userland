/*
 * $XConsortium: AsciiSrc.h,v 1.5 89/10/05 13:17:30 kit Exp $
 *
 * Copyright 1989 Massachusetts Institute of Technology
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
 */


/*
 * AsciiSrc.h - Public Header file for Ascii Text Source.
 *
 * This is the public header file for the Ascii Text Source.
 * It is intended to be used with the Text widget, the simplest way to use
 * this text source is to use the AsciiText Object.
 *
 * Date:    June 29, 1989
 *
 * By:      Chris D. Peterson
 *          MIT X Consortium 
 *          kit@expo.lcs.mit.edu
 */


#ifndef _XawAsciiSrc_h
#define _XawAsciiSrc_h

#include <./Xaw3_1TextSrc.h>

/* Resources:

 Name		     Class		RepType		Default Value
 ----		     -----		-------		-------------


*/
 
/* Class record constants */

extern WidgetClass asciiSrcObjectClass;

typedef struct _AsciiSrcClassRec *AsciiSrcObjectClass;
typedef struct _AsciiSrcRec      *AsciiSrcObject;

/*
 * Just to make people's lives a bit easier.
 */

#define AsciiSourceObjectClass AsciiSrcObjectClass
#define AsciiSourceObject      AsciiSrcObject

/*
 * Resource Definitions.
 */

#define XtCDataCompression "DataCompression"
#define XtCPieceSize "PieceSize"
#define XtCType "Type"
#define XtCUseStringInPlace "UseStringInPlace"

#define XtNdataCompression "dataCompression"
#define XtNpieceSize "pieceSize"
#define XtNtype "type"
#define XtNuseStringInPlace "useStringInPlace"

#define XtRAsciiType "AsciiType"

#define XtEstring "string"
#define XtEfile "file"

typedef enum {XawAsciiFile, XawAsciiString} XawAsciiType;

/************************************************************
 *
 * Public routines 
 *
 ************************************************************/

/*	Function Name: XawAsciiSourceFreeString
 *	Description: Frees the string returned by a get values call
 *                   on the string when the source is of type string.
 *	Arguments: w - the AsciiSrc object.
 *	Returns: none.
 */

void XawAsciiSourceFreeString(/* w */);
/*
Widget w;
*/

/*	Function Name: XawAsciiSave
 *	Description: Saves all the pieces into a file or string as required.
 *	Arguments: w - the asciiSrc Object.
 *	Returns: TRUE if the save was successful.
 */

Boolean XawAsciiSave(/* w */);
/*
Widget w;
*/

/*	Function Name: XawAsciiSaveAsFile
 *	Description: Save the current buffer as a file.
 *	Arguments: w - the asciiSrc object.
 *                 name - name of the file to save this file into.
 *	Returns: True if the save was sucessful.
 */

Boolean XawAsciiSaveAsFile(/* w, name */);
/*
Widget w;
String name;
*/

/*	Function Name: XawAsciiSourceChanged
 *	Description: Returns true if the source has changed since last saved.
 *	Arguments: w - the asciiSource object.
 *	Returns: a Boolean (see description).
 */

Boolean XawAsciiSourceChanged(/* w */);
/*
Widget w;
*/

#ifdef XAW_BC
/*************************************************************
 *
 * These functions are only preserved for compatability.     
 */

#define ASCII_STRING		/* Turn on R3 AsciiDisk and AsciiString */
#define ASCII_DISK		/* Emulation modes. */

#ifdef ASCII_STRING
#define XawStringSourceDestroy XtDestroyWidget
#endif

#ifdef ASCII_DISK
#define XawDiskSourceDestroy XtDestroyWidget
#endif

#ifdef ASCII_STRING
/*	Function Name: AsciiStringSourceCreate
 *	Description: Creates a string source.
 *	Arguments: parent - the widget that will own this source.
 *                 args, num_args - the argument list.
 *	Returns: a pointer to the new text source.
 */

Widget XawStringSourceCreate(/* parent, args, num_args */);
/*
Widget parent;
ArgList args;
Cardinal num_args;
*/
#endif /* ASCII_STRING */

#ifdef ASCII_DISK
/*	Function Name: AsciiDiskSourceCreate
 *	Description: Creates a disk source.
 *	Arguments: parent - the widget that will own this source.
 *                 args, num_args - the argument list.
 *	Returns: a pointer to the new text source.
 */

Widget XawDiskSourceCreate(/* parent, args, num_args */);
/*
Widget parent;
ArgList args;
Cardinal num_args;
*/
#endif /* ASCII_DISK */
#endif /* XAW_BC */
/*
 * End of Compatability stuff.
 *  
 ***************************************************/

#endif /* _XawAsciiSrc_h  - Don't add anything after this line. */

