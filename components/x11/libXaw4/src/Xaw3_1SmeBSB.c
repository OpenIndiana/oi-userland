#if ( !defined(lint) && !defined(SABER) )
static char Xrcsid[] = "$XConsortium: SmeBSB.c,v 1.12 90/02/15 13:57:53 kit Exp $";
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
 */

/*
 * SmeBSB.c - Source code file for BSB Menu Entry object.
 *
 * Date:    September 26, 1989
 *
 * By:      Chris D. Peterson
 *          MIT X Consortium 
 *          kit@expo.lcs.mit.edu
 */

#include <stdio.h>
#include <X11/IntrinsicP.h>
#include <X11/StringDefs.h>

#include <X11/Xmu/Drawing.h>

#include <./Xaw3_1XawInit.h>
#include <./Xaw3_1SimpleMenu.h>
#include <./Xaw3_1SmeBSBP.h>
#include <./Xaw3_1Cardinals.h>

#define ONE_HUNDRED 100

#define offset(field) XtOffset(SmeBSBObject, sme_bsb.field)

static XtResource resources[] = {
  {XtNlabel,  XtCLabel, XtRString, sizeof(String),
     offset(label), XtRString, NULL},
  {XtNvertSpace,  XtCVertSpace, XtRInt, sizeof(int),
     offset(vert_space), XtRImmediate, (caddr_t) 25},
  {XtNleftBitmap, XtCLeftBitmap, XtRBitmap, sizeof(Pixmap),
     offset(left_bitmap), XtRImmediate, (caddr_t)None},
  {XtNjustify, XtCJustify, XtRJustify, sizeof(XtJustify),
     offset(justify), XtRImmediate, (caddr_t) XtJustifyLeft},
  {XtNrightBitmap, XtCRightBitmap, XtRBitmap, sizeof(Pixmap),
     offset(right_bitmap), XtRImmediate, (caddr_t)None},
  {XtNleftMargin,  XtCHorizontalMargins, XtRDimension, sizeof(Dimension),
     offset(left_margin), XtRImmediate, (caddr_t) 4},
  {XtNrightMargin,  XtCHorizontalMargins, XtRDimension, sizeof(Dimension),
     offset(right_margin), XtRImmediate, (caddr_t) 4},
  {XtNforeground, XtCForeground, XtRPixel, sizeof(Pixel),
     offset(foreground), XtRString, "XtDefaultForeground"},
  {XtNfont,  XtCFont, XtRFontStruct, sizeof(XFontStruct *),
     offset(font), XtRString, "XtDefaultFont"},
};   
#undef offset

/*
 * Semi Public function definitions. 
 */

static void Redisplay(), Destroy(), Initialize(), FlipColors();
static void ClassInitialize();
static Boolean SetValues();
static XtGeometryResult QueryGeometry();

/* 
 * Private Function Definitions.
 */

static void GetDefaultSize(), DrawBitmaps(), GetBitmapInfo();
static void CreateGCs(), DestroyGCs();
    
#define superclass (&smeClassRec)
SmeBSBClassRec smeBSBClassRec = {
  {
    /* superclass         */    (WidgetClass) superclass,
    /* class_name         */    "SmeBSB",
    /* size               */    sizeof(SmeBSBRec),
    /* class_initializer  */	ClassInitialize,
    /* class_part_initialize*/	NULL,
    /* Class init'ed      */	FALSE,
    /* initialize         */    Initialize,
    /* initialize_hook    */	NULL,
    /* realize            */    NULL,
    /* actions            */    NULL,
    /* num_actions        */    ZERO,
    /* resources          */    resources,
    /* resource_count     */	XtNumber(resources),
    /* xrm_class          */    NULLQUARK,
    /* compress_motion    */    FALSE, 
    /* compress_exposure  */    FALSE,
    /* compress_enterleave*/ 	FALSE,
    /* visible_interest   */    FALSE,
    /* destroy            */    Destroy,
    /* resize             */    NULL,
    /* expose             */    Redisplay,
    /* set_values         */    SetValues,
    /* set_values_hook    */	NULL,
    /* set_values_almost  */	XtInheritSetValuesAlmost,  
    /* get_values_hook    */	NULL,			
    /* accept_focus       */    NULL,
    /* intrinsics version */	XtVersion,
    /* callback offsets   */    NULL,
    /* tm_table		  */    NULL,
    /* query_geometry	  */    QueryGeometry,
    /* display_accelerator*/    NULL,
    /* extension	  */    NULL
  },{
    /* Menu Entry Fields */
      
    /* highlight */             FlipColors,
    /* unhighlight */           FlipColors,
    /* notify */		XtInheritNotify,		
    /* extension	  */    NULL
  }, {
    /* BSB Menu entry Fields */  

    /* extension	  */    NULL
  }
};

WidgetClass smeBSBObjectClass = (WidgetClass) &smeBSBClassRec;

/************************************************************
 *
 * Semi-Public Functions.
 *
 ************************************************************/

/*	Function Name: ClassInitialize
 *	Description: Initializes the SmeBSBObject. 
 *	Arguments: none.
 *	Returns: none.
 */

static void 
ClassInitialize()
{
    XawInitializeWidgetSet();
    XtAddConverter( XtRString, XtRJustify, XmuCvtStringToJustify, NULL, 0 );
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
    SmeBSBObject entry = (SmeBSBObject) new;

    if (entry->sme_bsb.label == NULL) 
	entry->sme_bsb.label = XtName(new);
    else
	entry->sme_bsb.label = XtNewString( entry->sme_bsb.label );

    GetDefaultSize(new, &(entry->rectangle.width), &(entry->rectangle.height));
    CreateGCs(new);

    entry->sme_bsb.left_bitmap_width = entry->sme_bsb.left_bitmap_height = 0;
    entry->sme_bsb.right_bitmap_width = entry->sme_bsb.right_bitmap_height = 0;

    GetBitmapInfo(new, TRUE);	/* Left Bitmap Info */
    GetBitmapInfo(new, FALSE);	/* Right Bitmap Info */
}

/*      Function Name: Destroy
 *      Description: Called at destroy time, cleans up.
 *      Arguments: w - the simple menu widget.
 *      Returns: none.
 */

static void
Destroy(w)
Widget w;
{
    SmeBSBObject entry = (SmeBSBObject) w;

    DestroyGCs(w);
    if (entry->sme_bsb.label != XtName(w))
	XtFree(entry->sme_bsb.label);
}

/*      Function Name: Redisplay
 *      Description: Redisplays the contents of the widget.
 *      Arguments: w - the simple menu widget.
 *                 event - the X event that caused this redisplay.
 *                 region - the region the needs to be repainted. 
 *      Returns: none.
 */

/* ARGSUSED */
static void
Redisplay(w, event, region)
Widget w;
XEvent * event;
Region region;
{
    GC gc;
    SmeBSBObject entry = (SmeBSBObject) w;
    int	font_ascent, font_descent, y_loc;

    entry->sme_bsb.set_values_area_cleared = FALSE;    
    font_ascent = entry->sme_bsb.font->max_bounds.ascent;
    font_descent = entry->sme_bsb.font->max_bounds.descent;

    y_loc = entry->rectangle.y;
    
    if (XtIsSensitive(w) && XtIsSensitive( XtParent(w) ) ) {
	if ( w == XawSimpleMenuGetActiveEntry(XtParent(w)) ) {
	    XFillRectangle(XtDisplayOfObject(w), XtWindowOfObject(w), 
			   entry->sme_bsb.norm_gc, 0, y_loc,
			   (unsigned int) entry->rectangle.width,
			   (unsigned int) entry->rectangle.height);
	    gc = entry->sme_bsb.rev_gc;
	}
	else
	    gc = entry->sme_bsb.norm_gc;
    }
    else
	gc = entry->sme_bsb.norm_gray_gc;
    
    if (entry->sme_bsb.label != NULL) {
	int x_loc = entry->sme_bsb.left_margin;
	int len = strlen(entry->sme_bsb.label);
	char * label = entry->sme_bsb.label;

	switch(entry->sme_bsb.justify) {
	    int width, t_width;

	case XtJustifyCenter:
	    t_width = XTextWidth(entry->sme_bsb.font, label, len);
	    width = entry->rectangle.width - (entry->sme_bsb.left_margin +
					      entry->sme_bsb.right_margin);
	    x_loc += (width - t_width)/2;
	    break;
	case XtJustifyRight:
	    t_width = XTextWidth(entry->sme_bsb.font, label, len);
	    x_loc = entry->rectangle.width - (entry->sme_bsb.right_margin +
					      t_width);
	    break;
	case XtJustifyLeft:
	default:
	    break;
	}

	y_loc += (entry->rectangle.height - 
		  (font_ascent + font_descent)) / 2 + font_ascent;
	
	XDrawString(XtDisplayOfObject(w), XtWindowOfObject(w), gc,
		    x_loc, y_loc, label, len);
    }

    DrawBitmaps(w, gc);
}


/*      Function Name: SetValues
 *      Description: Relayout the menu when one of the resources is changed.
 *      Arguments: current - current state of the widget.
 *                 request - what was requested.
 *                 new - what the widget will become.
 *      Returns: none
 */

/* ARGSUSED */
static Boolean
SetValues(current, request, new)
Widget current, request, new;
{
    SmeBSBObject entry = (SmeBSBObject) new;
    SmeBSBObject old_entry = (SmeBSBObject) current;
    Boolean ret_val = FALSE;

    if (old_entry->sme_bsb.label != entry->sme_bsb.label) {
        if (old_entry->sme_bsb.label != XtName( new ) )
	    XtFree( (char *) old_entry->sme_bsb.label );

	if (entry->sme_bsb.label != XtName(new) ) 
	    entry->sme_bsb.label = XtNewString( entry->sme_bsb.label );

	ret_val = True;
    }

    if (entry->rectangle.sensitive != old_entry->rectangle.sensitive )
	ret_val = TRUE;

    if (entry->sme_bsb.left_bitmap != old_entry->sme_bsb.left_bitmap) {
	GetBitmapInfo(new, TRUE);
	ret_val = TRUE;
    }

    if (entry->sme_bsb.right_bitmap != old_entry->sme_bsb.right_bitmap) {
	GetBitmapInfo(new, FALSE);
	ret_val = TRUE;
    }

    if ( (old_entry->sme_bsb.font != entry->sme_bsb.font) ||
	 (old_entry->sme_bsb.foreground != entry->sme_bsb.foreground) ) {
	DestroyGCs(current);
	CreateGCs(new);
	ret_val = TRUE;
    }

    if (ret_val) {
	GetDefaultSize(new, 
		       &(entry->rectangle.width), &(entry->rectangle.height));
	entry->sme_bsb.set_values_area_cleared = TRUE;
    }
    return(ret_val);
}

/*	Function Name: QueryGeometry.
 *	Description: Returns the preferred geometry for this widget.
 *	Arguments: w - the menu entry object.
 *                 itended, return_val - the intended and return geometry info.
 *	Returns: A Geometry Result.
 *
 * See the Intrinsics manual for details on what this function is for.
 * 
 * I just return the height and width of the label plus the margins.
 */

static XtGeometryResult
QueryGeometry(w, intended, return_val) 
Widget w;
XtWidgetGeometry *intended, *return_val;
{
    SmeBSBObject entry = (SmeBSBObject) w;
    Dimension width, height;
    XtGeometryResult ret_val = XtGeometryYes;
    XtGeometryMask mode = intended->request_mode;

    GetDefaultSize(w, &width, &height );    

    if ( ((mode & CWWidth) && (intended->width != width)) ||
	 !(mode & CWWidth) ) {
	return_val->request_mode |= CWWidth;
	return_val->width = width;
	ret_val = XtGeometryAlmost;
    }

    if ( ((mode & CWHeight) && (intended->height != height)) ||
	 !(mode & CWHeight) ) {
	return_val->request_mode |= CWHeight;
	return_val->height = height;
	ret_val = XtGeometryAlmost;
    }

    if (ret_val == XtGeometryAlmost) {
	mode = return_val->request_mode;
	
	if ( ((mode & CWWidth) && (width == entry->rectangle.width)) &&
	     ((mode & CWHeight) && (height == entry->rectangle.height)) )
	    return(XtGeometryNo);
    }

    return(ret_val);
}
    
/*      Function Name: FlipColors
 *      Description: Invert the colors of the current entry.
 *      Arguments: w - the bsb menu entry widget.
 *      Returns: none.
 */

static void 
FlipColors(w)
Widget w;
{
    SmeBSBObject entry = (SmeBSBObject) w;

    if (entry->sme_bsb.set_values_area_cleared) return;

    XFillRectangle(XtDisplayOfObject(w), XtWindowOfObject(w),
		   entry->sme_bsb.invert_gc, 0, (int) entry->rectangle.y,
		   (unsigned int) entry->rectangle.width, 
		   (unsigned int) entry->rectangle.height);
}

/************************************************************
 *
 * Private Functions.
 *
 ************************************************************/

/*	Function Name: GetDefaultSize
 *	Description: Calculates the Default (preferred) size of
 *                   this menu entry.
 *	Arguments: w - the menu entry widget.
 *                 width, height - default sizes (RETURNED).
 *	Returns: none.
 */

static void
GetDefaultSize(w, width, height) 
Widget w;
Dimension * width, * height;
{
    SmeBSBObject entry = (SmeBSBObject) w;

    if (entry->sme_bsb.label == NULL) 
	*width = 0;
    else
	*width = XTextWidth(entry->sme_bsb.font, entry->sme_bsb.label,
			    strlen(entry->sme_bsb.label));

    *width += entry->sme_bsb.left_margin + entry->sme_bsb.right_margin;
    
    *height = (entry->sme_bsb.font->max_bounds.ascent +
	       entry->sme_bsb.font->max_bounds.descent);

    *height = (*height * ( ONE_HUNDRED + 
			  entry->sme_bsb.vert_space )) / ONE_HUNDRED;
}

/*      Function Name: DrawBitmaps
 *      Description: Draws left and right bitmaps.
 *      Arguments: w - the simple menu widget.
 *                 gc - graphics context to use for drawing.
 *      Returns: none
 */

static void
DrawBitmaps(w, gc)
Widget w;
GC gc;
{
    int x_loc, y_loc;
    SmeBSBObject entry = (SmeBSBObject) w;
    
    if ( (entry->sme_bsb.left_bitmap == None) && 
	 (entry->sme_bsb.right_bitmap == None) ) return;

/*
 * Draw Left Bitmap.
 */

  if (entry->sme_bsb.left_bitmap != None) {
    x_loc = (entry->sme_bsb.left_margin - 
	     entry->sme_bsb.left_bitmap_width) / 2;

    y_loc = entry->rectangle.y + (entry->rectangle.height -
				  entry->sme_bsb.left_bitmap_height) / 2;

    XCopyPlane(XtDisplayOfObject(w), entry->sme_bsb.left_bitmap,
	       XtWindowOfObject(w), gc, 0, 0, 
	       entry->sme_bsb.left_bitmap_width,
	       entry->sme_bsb.left_bitmap_height, x_loc, y_loc, 1);
  }

/*
 * Draw Right Bitmap.
 */


  if (entry->sme_bsb.right_bitmap != None) {
    x_loc = entry->rectangle.width - (entry->sme_bsb.right_margin +
				      entry->sme_bsb.right_bitmap_width) / 2;

    y_loc = entry->rectangle.y + (entry->rectangle.height -
				  entry->sme_bsb.right_bitmap_height) / 2;

    XCopyPlane(XtDisplayOfObject(w), entry->sme_bsb.right_bitmap,
	       XtWindowOfObject(w), gc, 0, 0, 
	       entry->sme_bsb.right_bitmap_width,
	       entry->sme_bsb.right_bitmap_height, x_loc, y_loc, 1);
  }
}

/*      Function Name: GetBitmapInfo
 *      Description: Gets the bitmap information from either of the bitmaps.
 *      Arguments: w - the bsb menu entry widget.
 *                 is_left - TRUE if we are testing left bitmap,
 *                           FALSE if we are testing the right bitmap.
 *      Returns: none
 */

static void
GetBitmapInfo(w, is_left)
Widget w;
Boolean is_left;
{
    SmeBSBObject entry = (SmeBSBObject) w;    
    unsigned int depth, bw;
    Window root;
    int x, y;
    unsigned int width, height;
    char buf[BUFSIZ];
    
    if (is_left) {
	if (entry->sme_bsb.left_bitmap != None) {
	    if (!XGetGeometry(XtDisplayOfObject(w), 
			      entry->sme_bsb.left_bitmap, &root, 
			      &x, &y, &width, &height, &bw, &depth)) {
		sprintf(buf, "SmeBSB Object: %s %s \"%s\".", "Could not",
			"get Left Bitmap geometry information for menu entry ",
			XtName(w));
		XtAppError(XtWidgetToApplicationContext(w), buf);
	    }
	    if (depth != 1) {
		sprintf(buf, "SmeBSB Object: %s \"%s\"%s.", 
			"Left Bitmap of entry ", 
			XtName(w), " is not one bit deep.");
		XtAppError(XtWidgetToApplicationContext(w), buf);
	    }
	    entry->sme_bsb.left_bitmap_width = (Dimension) width; 
	    entry->sme_bsb.left_bitmap_height = (Dimension) height;
	}
    }
    else if (entry->sme_bsb.right_bitmap != None) {
	if (!XGetGeometry(XtDisplayOfObject(w),
			  entry->sme_bsb.right_bitmap, &root,
			  &x, &y, &width, &height, &bw, &depth)) {
	    sprintf(buf, "SmeBSB Object: %s %s \"%s\".", "Could not",
		    "get Right Bitmap geometry information for menu entry ",
		    XtName(w));
	    XtAppError(XtWidgetToApplicationContext(w), buf);
	}
	if (depth != 1) {
	    sprintf(buf, "SmeBSB Object: %s \"%s\"%s.", 
		    "Right Bitmap of entry ", XtName(w),
		    " is not one bit deep.");
	    XtAppError(XtWidgetToApplicationContext(w), buf);
	}
	entry->sme_bsb.right_bitmap_width = (Dimension) width; 
	entry->sme_bsb.right_bitmap_height = (Dimension) height;
    }
}      

/*      Function Name: CreateGCs
 *      Description: Creates all gc's for the simple menu widget.
 *      Arguments: w - the simple menu widget.
 *      Returns: none.
 */

static void
CreateGCs(w)
Widget w;
{
    SmeBSBObject entry = (SmeBSBObject) w;    
    XGCValues values;
    XtGCMask mask;
    
    values.foreground = XtParent(w)->core.background_pixel;
    values.background = entry->sme_bsb.foreground;
    values.font = entry->sme_bsb.font->fid;
    values.graphics_exposures = FALSE;
    mask        = GCForeground | GCBackground | GCFont | GCGraphicsExposures;
    entry->sme_bsb.rev_gc = XtGetGC(w, mask, &values);
    
    values.foreground = entry->sme_bsb.foreground;
    values.background = XtParent(w)->core.background_pixel;
    entry->sme_bsb.norm_gc = XtGetGC(w, mask, &values);
    
    values.fill_style = FillTiled;
    values.tile   = XmuCreateStippledPixmap(XtScreenOfObject(w), 
					    entry->sme_bsb.foreground,
					    XtParent(w)->core.background_pixel,
					    XtParent(w)->core.depth);
    values.graphics_exposures = FALSE;
    mask |= GCTile | GCFillStyle;
    entry->sme_bsb.norm_gray_gc = XtGetGC(w, mask, &values);
    
    values.foreground ^= values.background;
    values.background = 0;
    values.function = GXxor;
    mask = GCForeground | GCBackground | GCGraphicsExposures | GCFunction;
    entry->sme_bsb.invert_gc = XtGetGC(w, mask, &values);
}

/*      Function Name: DestroyGCs
 *      Description: Removes all gc's for the simple menu widget.
 *      Arguments: w - the simple menu widget.
 *      Returns: none.
 */

static void
DestroyGCs(w)
Widget w;
{
    SmeBSBObject entry = (SmeBSBObject) w;    

    XtReleaseGC(w, entry->sme_bsb.norm_gc);
    XtReleaseGC(w, entry->sme_bsb.norm_gray_gc);
    XtReleaseGC(w, entry->sme_bsb.rev_gc);
    XtReleaseGC(w, entry->sme_bsb.invert_gc);
}

#ifdef apollo

/*
 * The apollo compiler that we have optomizes out my code for
 * FlipColors() since it is static. and no one executes it in this
 * file.  I am setting the function pointer into the class structure so
 * that it can be called by my parent who will tell me to when to
 * highlight and unhighlight.
 */

void _XawSmeBSBApolloHack ()
{
    FlipColors();
}
#endif /* apollo */
