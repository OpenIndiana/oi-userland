#if (!defined(lint) && !defined(SABER))
static char Xrcsid[] = "$XConsortium: Text.c,v 1.136 89/12/15 12:10:56 kit Exp $";
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
#include <X11/IntrinsicP.h>
#include <X11/StringDefs.h>
#include <X11/Shell.h>
#include <X11/Xatom.h>

#include <X11/Xmu/Atoms.h>
#include <X11/Xmu/CharSet.h>
#include <X11/Xmu/Converters.h>
#include <X11/Xmu/StdSel.h>
#include <X11/Xmu/Misc.h>

#include <./Xaw3_1XawInit.h>
#include <./Xaw3_1Cardinals.h>
#include <./Xaw3_1Scrollbar.h>
#include <./Xaw3_1TextP.h>

#ifdef SYSV
#ifndef bcopy
#define bcopy(a,b,c) memmove(b,a,c)
#endif
#ifndef bzero
#define bzero(a,b) memset(a,0,b)
#endif
#endif

Atom FMT8BIT = NULL;

#define SinkClearToBG          XawTextSinkClearToBackground

#define SrcScan                XawTextSourceScan
#define SrcRead                XawTextSourceRead
#define SrcReplace             XawTextSourceReplace
#define SrcSearch              XawTextSourceSearch
#define SrcCvtSel              XawTextSourceConvertSelection
#define SrcSetSelection        XawTextSourceSetSelection

#ifndef SYSV
extern void bcopy();
#endif
extern int errno, sys_nerr;
extern char* sys_errlist[];

#define BIGNUM ((Dimension)32023)
#define MULTI_CLICK_TIME 500L

#define IsValidLine(ctx, num) ( ((num) == 0) || \
			        ((ctx)->text.lt.info[(num)].position != 0) )

/*
 * Defined in Text.c
 */

static void VScroll(), VJump(), HScroll(), HJump(), ClearWindow(); 
static void DisplayTextWindow(), ModifySelection();
static void UpdateTextInLine(), UpdateTextInRectangle();
static Boolean LineAndXYForPosition();
static XawTextPosition FindGoodPosition(), _BuildLineTable();

void _XawTextAlterSelection(), _XawTextExecuteUpdate();
void _XawTextBuildLineTable(), _XawTextSetScrollBars();
void _XawTextPrepareToUpdate(TextWidget ctx);

/****************************************************************
 *
 * Full class record constant
 *
 ****************************************************************/

static XawTextSelectType defaultSelectTypes[] = {
  XawselectPosition, XawselectWord, XawselectLine, XawselectParagraph,
  XawselectAll,      XawselectNull,
};

static caddr_t defaultSelectTypesPtr = (caddr_t)defaultSelectTypes;
extern char *_XawDefaultTextTranslations1, *_XawDefaultTextTranslations2,
  *_XawDefaultTextTranslations3;
static Dimension defWidth = 100;
static Dimension defHeight = DEFAULT_TEXT_HEIGHT;

#define offset(field) XtOffset(TextWidget, field)
static XtResource resources[] = {
  {XtNwidth, XtCWidth, XtRDimension, sizeof(Dimension),
     offset(core.width), XtRDimension, (caddr_t)&defWidth},
  {XtNcursor, XtCCursor, XtRCursor, sizeof(Cursor),
     offset(simple.cursor), XtRString, "xterm"},
  {XtNheight, XtCHeight, XtRDimension, sizeof(Dimension),
     offset(core.height), XtRDimension, (caddr_t)&defHeight},

  {XtNdisplayPosition, XtCTextPosition, XtRInt, sizeof(XawTextPosition), 
     offset(text.lt.top), XtRImmediate, (caddr_t)0},
  {XtNinsertPosition, XtCTextPosition, XtRInt, sizeof(XawTextPosition),
     offset(text.insertPos), XtRImmediate,(caddr_t)0},
  {XtNleftMargin, XtCMargin, XtRPosition, sizeof (Position),
     offset(text.r_margin.left), XtRImmediate, (caddr_t)2},
  {XtNrightMargin, XtCMargin, XtRPosition, sizeof (Position),
     offset(text.r_margin.right), XtRImmediate, (caddr_t)4},
  {XtNtopMargin, XtCMargin, XtRPosition, sizeof (Position),
     offset(text.r_margin.top), XtRImmediate, (caddr_t)2},
  {XtNbottomMargin, XtCMargin, XtRPosition, sizeof (Position),
     offset(text.r_margin.bottom), XtRImmediate, (caddr_t)2},
  {XtNselectTypes, XtCSelectTypes, XtRPointer,
     sizeof(XawTextSelectType*), offset(text.sarray),
     XtRPointer, (caddr_t)&defaultSelectTypesPtr},
  {XtNtextSource, XtCTextSource, XtRWidget, sizeof (Widget),
     offset(text.source), XtRImmediate, NULL},
  {XtNtextSink, XtCTextSink, XtRWidget, sizeof (Widget),
     offset(text.sink), XtRImmediate, NULL},
  {XtNdisplayCaret, XtCOutput, XtRBoolean, sizeof(Boolean),
     offset(text.display_caret), XtRImmediate, (caddr_t)True},
  {XtNscrollVertical, XtCScroll, XtRScrollMode, sizeof(XawTextScrollMode),
     offset(text.scroll_vert), XtRImmediate, (caddr_t) XawtextScrollNever},
  {XtNscrollHorizontal, XtCScroll, XtRScrollMode, sizeof(XawTextScrollMode),
     offset(text.scroll_horiz), XtRImmediate, (caddr_t) XawtextScrollNever},
  {XtNwrap, XtCWrap, XtRWrapMode, sizeof(XawTextWrapMode),
     offset(text.wrap), XtRImmediate, (caddr_t) XawtextWrapNever},
  {XtNresize, XtCResize, XtRResizeMode, sizeof(XawTextResizeMode),
     offset(text.resize), XtRImmediate, (caddr_t) XawtextResizeNever},
  {XtNautoFill, XtCAutoFill, XtRBoolean, sizeof(Boolean),
     offset(text.auto_fill), XtRImmediate, (caddr_t) FALSE},

#ifdef XAW_BC
/*
 * This resource is obsolete. 
 */
  {XtNtextOptions, XtCTextOptions, XtRInt, sizeof (int),
     offset(text.options), XtRImmediate, (caddr_t)0},
#endif
};
#undef offset

#define done(address, type) \
        { toVal->size = sizeof(type); toVal->addr = (caddr_t) address; }

/* ARGSUSED */
static void 
CvtStringToEditMode(args, num_args, fromVal, toVal)
XrmValuePtr args;		/* unused */
Cardinal	*num_args;	/* unused */
XrmValuePtr	fromVal;
XrmValuePtr	toVal;
{
  static XawTextEditType editType;
  static  XrmQuark  QRead, QAppend, QEdit;
  XrmQuark    q;
  char        lowerName[BUFSIZ];
  static Boolean inited = FALSE;
    
  if ( !inited ) {
    QRead   = XrmStringToQuark(XtEtextRead);
    QAppend = XrmStringToQuark(XtEtextAppend);
    QEdit   = XrmStringToQuark(XtEtextEdit);
    inited = TRUE;
  }

  XmuCopyISOLatin1Lowered (lowerName, (char *)fromVal->addr);
  q = XrmStringToQuark(lowerName);

  if       (q == QRead)          editType = XawtextRead;
  else if (q == QAppend)         editType = XawtextAppend;
  else if (q == QEdit)           editType = XawtextEdit;
  else {
    done(NULL, 0);
    return;
  }
  done(&editType, XawTextEditType);
  return;
}


/* ARGSUSED */
static void 
CvtStringToScrollMode(args, num_args, fromVal, toVal)
XrmValuePtr args;		/* unused */
Cardinal	*num_args;	/* unused */
XrmValuePtr	fromVal;
XrmValuePtr	toVal;
{
  static XawTextScrollMode scrollMode;
  static  XrmQuark  QScrollNever, QScrollAlways, QScrollWhenNeeded;
  XrmQuark    q;
  char        lowerName[BUFSIZ];
  static Boolean inited = FALSE;
    
  if ( !inited ) {
    QScrollNever      = XrmStringToQuark(XtEtextScrollNever);
    QScrollWhenNeeded = XrmStringToQuark(XtEtextScrollWhenNeeded);
    QScrollAlways     = XrmStringToQuark(XtEtextScrollAlways);
    inited = TRUE;
  }

  XmuCopyISOLatin1Lowered (lowerName, (char *)fromVal->addr);
  q = XrmStringToQuark(lowerName);

  if      (q == QScrollNever)          scrollMode = XawtextScrollNever;
  else if (q == QScrollWhenNeeded)     scrollMode = XawtextScrollWhenNeeded;
  else if (q == QScrollAlways)         scrollMode = XawtextScrollAlways;
  else {
    done(NULL, 0);
    return;
  }
  done(&scrollMode, XawTextScrollMode);
  return;
}

/* ARGSUSED */
static void 
CvtStringToWrapMode(args, num_args, fromVal, toVal)
XrmValuePtr args;		/* unused */
Cardinal	*num_args;	/* unused */
XrmValuePtr	fromVal;
XrmValuePtr	toVal;
{
  static XawTextWrapMode wrapMode;
  static  XrmQuark QWrapNever, QWrapLine, QWrapWord;
  XrmQuark    q;
  char        lowerName[BUFSIZ];
  static Boolean inited = FALSE;
    
  if ( !inited ) {
    QWrapNever = XrmStringToQuark(XtEtextWrapNever);
    QWrapLine  = XrmStringToQuark(XtEtextWrapLine);
    QWrapWord  = XrmStringToQuark(XtEtextWrapWord);
    inited = TRUE;
  }

  XmuCopyISOLatin1Lowered (lowerName, (char *)fromVal->addr);
  q = XrmStringToQuark(lowerName);

  if      (q == QWrapNever)     wrapMode = XawtextWrapNever;
  else if (q == QWrapLine)      wrapMode = XawtextWrapLine;
  else if (q == QWrapWord)      wrapMode = XawtextWrapWord;
  else {
    done(NULL, 0);
    return;
  }
  done(&wrapMode, XawTextWrapMode);
  return;
}

/* ARGSUSED */
static void 
CvtStringToResizeMode(args, num_args, fromVal, toVal)
XrmValuePtr args;		/* unused */
Cardinal	*num_args;	/* unused */
XrmValuePtr	fromVal;
XrmValuePtr	toVal;
{
  static XawTextResizeMode resizeMode;
  static  XrmQuark  QResizeNever, QResizeWidth, QResizeHeight, QResizeBoth;
  XrmQuark    q;
  char        lowerName[BUFSIZ];
  static Boolean inited = FALSE;
    
  if ( !inited ) {
    QResizeNever      = XrmStringToQuark(XtEtextResizeNever);
    QResizeWidth      = XrmStringToQuark(XtEtextResizeWidth);
    QResizeHeight     = XrmStringToQuark(XtEtextResizeHeight);
    QResizeBoth       = XrmStringToQuark(XtEtextResizeBoth);
    inited = TRUE;
  }

  XmuCopyISOLatin1Lowered (lowerName, (char *)fromVal->addr);
  q = XrmStringToQuark(lowerName);

  if      (q == QResizeNever)          resizeMode = XawtextResizeNever;
  else if (q == QResizeWidth)          resizeMode = XawtextResizeWidth;
  else if (q == QResizeHeight)         resizeMode = XawtextResizeHeight;
  else if (q == QResizeBoth)           resizeMode = XawtextResizeBoth;
  else {
    done(NULL, 0);
    return;
  }
  done(&resizeMode, XawTextResizeMode);
  return;
}

#undef done

static void 
ClassInitialize()
{
  int len1 = strlen (_XawDefaultTextTranslations1);
  int len2 = strlen (_XawDefaultTextTranslations2);
  int len3 = strlen (_XawDefaultTextTranslations3);
  char *buf = XtMalloc (len1 + len2 + len3 + 1);
  char *cp = buf;

  XawInitializeWidgetSet();

/* 
 * Set the number of actions.
 */

  textClassRec.core_class.num_actions = textActionsTableCount;
  
  strcpy (cp, _XawDefaultTextTranslations1); cp += len1;
  strcpy (cp, _XawDefaultTextTranslations2); cp += len2;
  strcpy (cp, _XawDefaultTextTranslations3);
  textWidgetClass->core_class.tm_table = buf;

  XtAddConverter(XtRString, XtREditMode,   CvtStringToEditMode,   NULL, 0);
  XtAddConverter(XtRString, XtRScrollMode, CvtStringToScrollMode, NULL, 0);
  XtAddConverter(XtRString, XtRWrapMode,   CvtStringToWrapMode,   NULL, 0);
  XtAddConverter(XtRString, XtRResizeMode, CvtStringToResizeMode, NULL, 0);
}

/*	Function Name: PositionHScrollBar.
 *	Description: Positions the Horizontal scrollbar.
 *	Arguments: ctx - the text widget.
 *	Returns: none
 */

static void
PositionHScrollBar(ctx)
TextWidget ctx;
{
  Widget vbar = ctx->text.vbar, hbar = ctx->text.hbar;
  Position top, left = 0;

  if (ctx->text.hbar == NULL) return;

  if (vbar != NULL)
    left += (Position) (vbar->core.width + vbar->core.border_width);

  XtResizeWidget( hbar, ctx->core.width - left, hbar->core.height,
		 hbar->core.border_width );

  left -= (Position) hbar->core.border_width;
  
  top = ctx->core.height - ( hbar->core.height + hbar->core.border_width);
  XtMoveWidget( hbar, left, top); 
}

/*	Function Name: PositionVScrollBar.
 *	Description: Positions the Vertical scrollbar.
 *	Arguments: ctx - the text widget.
 *	Returns: none.
 */

static void
PositionVScrollBar(ctx)
TextWidget ctx;
{
  Widget vbar = ctx->text.vbar;
  Dimension bw;

  if (vbar == NULL) return;
  bw = vbar->core.border_width;

  XtResizeWidget( vbar, vbar->core.width, ctx->core.height, bw);
  XtMoveWidget( vbar, -(Position)bw, -(Position)bw );
}

static void 
CreateVScrollBar(ctx)
TextWidget ctx;
{
  Widget vbar;

  if (ctx->text.vbar != NULL) return;

  ctx->text.vbar = vbar =
    XtCreateWidget("vScrollbar", scrollbarWidgetClass, (Widget)ctx, NULL, ZERO);
  XtAddCallback( vbar, XtNscrollProc, VScroll, (caddr_t)ctx );
  XtAddCallback( vbar, XtNjumpProc, VJump, (caddr_t)ctx );

  ctx->text.r_margin.left += vbar->core.width + vbar->core.border_width;
  ctx->text.margin.left = ctx->text.r_margin.left;

  PositionVScrollBar(ctx);
  PositionHScrollBar(ctx);	/* May modify location of Horiz. Bar. */

  if (XtIsRealized((Widget)ctx)) {
    XtRealizeWidget(vbar);
    XtMapWidget(vbar);
  }
}

/*	Function Name: DestroyVScrollBar
 *	Description: Removes a vertical ScrollBar.
 *	Arguments: ctx - the parent text widget.
 *	Returns: none.
 */

static void
DestroyVScrollBar(ctx)
TextWidget ctx;
{
  Widget vbar = ctx->text.vbar;

  if (vbar == NULL) return;

  ctx->text.r_margin.left -= vbar->core.width + vbar->core.border_width;
  ctx->text.margin.left = ctx->text.r_margin.left;
  XtDestroyWidget(vbar);
  ctx->text.vbar = NULL;
  PositionHScrollBar(ctx);
}
  
static void 
CreateHScrollBar(ctx)
TextWidget ctx;
{
  Arg args[1];
  Widget hbar;

  if (ctx->text.hbar != NULL) return;

  XtSetArg(args[0], XtNorientation, XtorientHorizontal);
  ctx->text.hbar = hbar =
    XtCreateWidget("hScrollbar", scrollbarWidgetClass, (Widget)ctx, args, ONE);
  XtAddCallback( hbar, XtNscrollProc, HScroll, (caddr_t)ctx );
  XtAddCallback( hbar, XtNjumpProc, HJump, (caddr_t)ctx );

  PositionHScrollBar(ctx);
  if (XtIsRealized((Widget)ctx)) {
    XtRealizeWidget(hbar);
    XtMapWidget(hbar);
  }
}

/*	Function Name: DestroyHScrollBar
 *	Description: Removes a horizontal ScrollBar.
 *	Arguments: ctx - the parent text widget.
 *	Returns: none.
 */

static void
DestroyHScrollBar(ctx)
TextWidget ctx;
{
  Widget hbar = ctx->text.hbar;

  if (hbar == NULL) return;

/*
  ctx->text.r_margin.bottom -= hbar->core.height + hbar->core.border_width;
  ctx->text.margin.bottom = ctx->text.r_margin.bottom;
*/

  XtDestroyWidget(hbar);
  ctx->text.hbar = NULL;
}

/* ARGSUSED */
static void 
Initialize(request, new, args, num_args)
Widget request, new;
ArgList args;			/* unused */
Cardinal *num_args;		/* unused */
{
  TextWidget ctx = (TextWidget) new;
  char error_buf[BUFSIZ];

  if (!FMT8BIT)
    FMT8BIT = XInternAtom(XtDisplay(new), "FMT8BIT", False);

  ctx->text.lt.lines = 0;
  ctx->text.lt.info = NULL;
  bzero((char *) &(ctx->text.origSel), sizeof(XawTextSelection));
  bzero((char *) &(ctx->text.s), sizeof(XawTextSelection)); 
  ctx->text.s.type = XawselectPosition;
  ctx->text.hbar = ctx->text.vbar = (Widget) NULL;
  ctx->text.lasttime = 0; /* ||| correct? */
  ctx->text.time = 0; /* ||| correct? */
  ctx->text.showposition = TRUE;
  ctx->text.lastPos = (ctx->text.source != NULL) ? GETLASTPOS : 0;
  ctx->text.file_insert = NULL;
  ctx->text.search = NULL;
  ctx->text.updateFrom = (XawTextPosition *) XtMalloc(ONE);
  ctx->text.updateTo = (XawTextPosition *) XtMalloc(ONE);
  ctx->text.numranges = ctx->text.maxranges = 0;
  ctx->text.gc = DefaultGCOfScreen(XtScreen(ctx)); 
  ctx->text.hasfocus = FALSE;
  ctx->text.margin = ctx->text.r_margin; /* Strucure copy. */
  ctx->text.update_disabled = FALSE;
  ctx->text.old_insert = -1;
  ctx->text.mult = 1;
  ctx->text.single_char = FALSE;

#ifdef XAW_BC
/*******************************
 * For Compatability.          */

  if (ctx->text.options != 0)
    XawTextChangeOptions((Widget) ctx, ctx->text.options);
/*******************************/
#endif /* XAW_BC */  

  if (ctx->core.height == DEFAULT_TEXT_HEIGHT) {
    ctx->core.height = VMargins(ctx);
    if (ctx->text.sink != NULL)
      ctx->core.height += XawTextSinkMaxHeight(ctx->text.sink, 1);
  }

  if (ctx->text.scroll_vert != XawtextScrollNever) 
    if ( (ctx->text.resize == XawtextResizeHeight) ||
     	 (ctx->text.resize == XawtextResizeBoth) ) {
      sprintf(error_buf, "Text Widget (%s):\n %s %s.", ctx->core.name,
	      "Vertical scrolling not allowed with height resize.\n",
	      "Vertical scrolling has been DEACTIVATED.");
      XtAppWarning(XtWidgetToApplicationContext(new), error_buf);
      ctx->text.scroll_vert = XawtextScrollNever;
    }
    else if (ctx->text.scroll_vert == XawtextScrollAlways)
      CreateVScrollBar(ctx);

  if (ctx->text.scroll_horiz != XawtextScrollNever) 
    if (ctx->text.wrap != XawtextWrapNever) {
      sprintf(error_buf, "Text Widget (%s):\n %s %s.", ctx->core.name,
	      "Horizontal scrolling not allowed with wrapping active.\n",
	      "Horizontal scrolling has been DEACTIVATED.");
      XtAppWarning(XtWidgetToApplicationContext(new), error_buf);
      ctx->text.scroll_horiz = XawtextScrollNever;
    }
    else if ( (ctx->text.resize == XawtextResizeWidth) ||
	      (ctx->text.resize == XawtextResizeBoth) ) {
      sprintf(error_buf, "Text Widget (%s):\n %s %s.", ctx->core.name,
	      "Horizontal scrolling not allowed with width resize.\n",
	      "Horizontal scrolling has been DEACTIVATED.");
      XtAppWarning(XtWidgetToApplicationContext(new), error_buf);
      ctx->text.scroll_horiz = XawtextScrollNever;
    }
    else if (ctx->text.scroll_horiz == XawtextScrollAlways)
      CreateHScrollBar(ctx);
}

static void 
Realize( w, valueMask, attributes )
Widget w;
Mask *valueMask;
XSetWindowAttributes *attributes;
{
  TextWidget ctx = (TextWidget)w;
  
  (*textClassRec.core_class.superclass->core_class.realize)
    (w, valueMask, attributes);
  
  if (ctx->text.hbar != NULL) {	        /* Put up Hbar -- Must be first. */
    XtRealizeWidget(ctx->text.hbar);
    XtMapWidget(ctx->text.hbar);
  }

  if (ctx->text.vbar != NULL) {	        /* Put up Vbar. */
    XtRealizeWidget(ctx->text.vbar);
    XtMapWidget(ctx->text.vbar);
  }

  _XawTextBuildLineTable(ctx, ctx->text.lt.top, TRUE);
  _XawTextSetScrollBars(ctx);
}

/* Utility routines for support of Text */

static void
_CreateCutBuffers(d)
Display *d;
{
  static struct _DisplayRec {
    struct _DisplayRec *next;
    Display *dpy;
  } *dpy_list = NULL;
  struct _DisplayRec *dpy_ptr;

  for (dpy_ptr = dpy_list; dpy_ptr != NULL; dpy_ptr = dpy_ptr->next)
    if (dpy_ptr->dpy == d) return;

  dpy_ptr = XtNew(struct _DisplayRec);
  dpy_ptr->next = dpy_list;
  dpy_ptr->dpy = d;
  dpy_list = dpy_ptr;

#define Create(buffer) \
    XChangeProperty(d, RootWindow(d, 0), buffer, XA_STRING, 8, \
		    PropModeAppend, NULL, 0 );

    Create( XA_CUT_BUFFER0 );
    Create( XA_CUT_BUFFER1 );
    Create( XA_CUT_BUFFER2 );
    Create( XA_CUT_BUFFER3 );
    Create( XA_CUT_BUFFER4 );
    Create( XA_CUT_BUFFER5 );
    Create( XA_CUT_BUFFER6 );
    Create( XA_CUT_BUFFER7 );

#undef Create
}

/*
 * Procedure to manage insert cursor visibility for editable text.  It uses
 * the value of ctx->insertPos and an implicit argument. In the event that
 * position is immediately preceded by an eol graphic, then the insert cursor
 * is displayed at the beginning of the next line.
*/
static void 
InsertCursor (w, state)
Widget w;
XawTextInsertState state;
{
  TextWidget ctx = (TextWidget)w;
  Position x, y;
  int line;
  
  if (ctx->text.lt.lines < 1) return;

  if ( LineAndXYForPosition(ctx, ctx->text.insertPos, &line, &x, &y) ) {
    if (line < ctx->text.lt.lines)
      y += (ctx->text.lt.info[line + 1].y - ctx->text.lt.info[line].y) + 1;
    else
      y += (ctx->text.lt.info[line].y - ctx->text.lt.info[line - 1].y) + 1;

    if (ctx->text.display_caret)
      XawTextSinkInsertCursor(ctx->text.sink, x, y, state);
  }
  ctx->text.ev_x = x;
  ctx->text.ev_y = y;
}

/*
 * Procedure to register a span of text that is no longer valid on the display
 * It is used to avoid a number of small, and potentially overlapping, screen
 * updates. 
*/

void
_XawTextNeedsUpdating(ctx, left, right)
TextWidget ctx;
XawTextPosition left, right;
{
  int i;
  if (left < right) {
    for (i = 0; i < ctx->text.numranges; i++) {
      if (left <= ctx->text.updateTo[i] && right >= ctx->text.updateFrom[i]) {
	ctx->text.updateFrom[i] = Min(left, ctx->text.updateFrom[i]);
	ctx->text.updateTo[i] = Max(right, ctx->text.updateTo[i]);
	return;
      }
    }
    ctx->text.numranges++;
    if (ctx->text.numranges > ctx->text.maxranges) {
      ctx->text.maxranges = ctx->text.numranges;
      i = ctx->text.maxranges * sizeof(XawTextPosition);
      ctx->text.updateFrom = (XawTextPosition *) 
	XtRealloc((char *)ctx->text.updateFrom, (unsigned) i);
      ctx->text.updateTo = (XawTextPosition *) 
	XtRealloc((char *)ctx->text.updateTo, (unsigned) i);
    }
    ctx->text.updateFrom[ctx->text.numranges - 1] = left;
    ctx->text.updateTo[ctx->text.numranges - 1] = right;
  }
}

/*
 * Procedure to read a span of text in Ascii form. This is purely a hack and
 * we probably need to add a function to sources to provide this functionality.
 * [note: this is really a private procedure but is used in multiple modules].
 */

char *
_XawTextGetText(ctx, left, right)
TextWidget ctx;
XawTextPosition left, right;
{
  char *result, *tempResult;
  XawTextBlock text;
  Cardinal length = (Cardinal) (right - left);

  tempResult = result = XtMalloc(length + ONE);	/* leave space for '\0'. */
  while (left < right) {
    left = SrcRead(ctx->text.source, left, &text, right - left);
    (void) strncpy(tempResult, text.ptr, text.length);
    tempResult += text.length;
  }
  result[(int) length] = '\0';	/* NULL terminate this sucker */
  return(result);
}

/* like _XawTextGetText, but enforces ICCCM STRING type encoding */

char *
_XawTextGetSTRING(ctx, left, right)
TextWidget ctx;
XawTextPosition left, right;
{
  register unsigned char *s;
  register unsigned char c;
  register int i, j, n;

  s = (unsigned char *)_XawTextGetText(ctx, left, right);
  /* only HT and NL control chars are allowed, strip out others */
  n = strlen((char *)s);
  i = 0;
  for (j = 0; j < n; j++) {
    c = s[j];
    if (((c >= 0x20) && c <= 0x7f) ||
	(c >= 0xa0) || (c == '\t') || (c == '\n')) {
      s[i] = c;
      i++;
    }
  }
  s[i] = 0;
  return (char *)s;
}

/* 
 * This routine maps an x and y position in a window that is displaying text
 * into the corresponding position in the source.
 *
 * NOTE: it is illegal to call this routine unless there is a valid line table!
 */

/*** figure out what line it is on ***/

static XawTextPosition
PositionForXY (ctx, x, y)
TextWidget ctx;
Position x,y;
{
  int fromx, line, width, height;
  XawTextPosition position;

  if (ctx->text.lt.lines == 0) return 0;
  
  for (line = 0; line < ctx->text.lt.lines - 1; line++) {
    if (y <= ctx->text.lt.info[line + 1].y)
      break;
  }
  position = ctx->text.lt.info[line].position;
  if (position >= ctx->text.lastPos)
    return(ctx->text.lastPos);
  fromx = (int) ctx->text.margin.left; 
  XawTextSinkFindPosition( ctx->text.sink, position, fromx, x - fromx,
			  FALSE, &position, &width, &height);
  if (position >= ctx->text.lt.info[line + 1].position)
    position = SrcScan(ctx->text.source, ctx->text.lt.info[line + 1].position,
		       XawstPositions, XawsdLeft, 1, TRUE);
  if (position > ctx->text.lastPos) position = ctx->text.lastPos;
  return(position);
}

/*
 * This routine maps a source position in to the corresponding line number
 * of the text that is displayed in the window.
 *
 * NOTE: It is illegal to call this routine unless there is a valid line table!
 */

static int 
LineForPosition (ctx, position)
TextWidget ctx;
XawTextPosition position;
{
  int line;
  
  for (line = 0; line < ctx->text.lt.lines; line++)
    if (position < ctx->text.lt.info[line + 1].position)
      break;
  return(line);
}

/*
 * This routine maps a source position into the corresponding line number
 * and the x, y coordinates of the text that is displayed in the window.
 *
 * NOTE: It is illegal to call this routine unless there is a valid line table!
 */

static Boolean
LineAndXYForPosition (ctx, pos, line, x, y)
TextWidget ctx;
XawTextPosition pos;
int *line;
Position *x, *y;
{
  XawTextPosition linePos, endPos;
  Boolean visible;
  int realW, realH;

  *line = 0;
  *x = ctx->text.margin.left;
  *y = ctx->text.margin.top;
  if (visible = IsPositionVisible(ctx, pos)) {
    *line = LineForPosition(ctx, pos);
    *y = ctx->text.lt.info[*line].y;
    *x = ctx->text.margin.left;
    linePos = ctx->text.lt.info[*line].position;
    XawTextSinkFindDistance( ctx->text.sink, linePos,
			    *x, pos, &realW, &endPos, &realH);
    *x += realW;
  }
  return(visible);
}

/*
 * This routine builds a line table. It does this by starting at the
 * specified position and measuring text to determine the staring position
 * of each line to be displayed. It also determines and saves in the
 * linetable all the required metrics for displaying a given line (e.g.
 * x offset, y offset, line length, etc.).
 */

void 
_XawTextBuildLineTable (ctx, position, force_rebuild)
TextWidget ctx;
XawTextPosition position;	/* top. */
Boolean force_rebuild;
{
  Dimension height = 0;
  int lines = 0; 
  Cardinal size;

  if (ctx->core.height > VMargins(ctx)) {
    height = ctx->core.height - VMargins(ctx);
    lines = XawTextSinkMaxLines(ctx->text.sink, height);
  }
  size = sizeof(XawTextLineTableEntry) * (lines + 1);

  if ( (lines != ctx->text.lt.lines) || (ctx->text.lt.info == NULL) ) {
    ctx->text.lt.info = (XawTextLineTableEntry *) XtRealloc((char *) ctx->text.
							    lt.info, size);
    ctx->text.lt.lines = lines;
    force_rebuild = TRUE;
  }

  if ( force_rebuild || (position != ctx->text.lt.top) ) {
    bzero((char *) ctx->text.lt.info, size);
    (void) _BuildLineTable(ctx, ctx->text.lt.top = position, zeroPosition, 0);
  }
}

/*
 * This assumes that the line table does not change size.
 */

static XawTextPosition
_BuildLineTable(ctx, position, min_pos, line)
TextWidget ctx;
XawTextPosition position, min_pos;	
int line;
{
  XawTextLineTableEntry * lt = ctx->text.lt.info + line;
  XawTextPosition endPos;
  Position y;
  int count, width, realW, realH;
  Widget src = ctx->text.source;

  if ( ((ctx->text.resize == XawtextResizeWidth) ||
	(ctx->text.resize == XawtextResizeBoth)    ) ||
       (ctx->text.wrap == XawtextWrapNever) )
    width = BIGNUM;
  else 
    width = Max(0, (ctx->core.width - HMargins(ctx)));

  y = ( (line == 0) ? ctx->text.margin.top : lt->y );

  while ( TRUE ) {
    lt->y = y;
    lt->position = position;
    
    XawTextSinkFindPosition( ctx->text.sink, position, ctx->text.margin.left,
			    width, ctx->text.wrap == XawtextWrapWord,
			    &endPos, &realW, &realH);
    lt->textWidth = realW;
    y += realH;

    if (ctx->text.wrap == XawtextWrapNever) 
      endPos = SrcScan(src, position, XawstEOL, XawsdRight, 1, TRUE);

    if ( endPos == ctx->text.lastPos) { /* We have reached the end. */
      if(SrcScan(src, position, XawstEOL, XawsdRight, 1, FALSE) == endPos)
	break;
    }

    ++lt;
    ++line;
    if ( (line > ctx->text.lt.lines) ||
	 ((lt->position == (position = endPos)) && (position > min_pos)) )
      return(position);
  }

/*
 * If we are at the end of the buffer put two special lines in the table.
 *
 * a) Both have position > text.lastPos and lt->textWidth = 0.
 * b) The first has a real height, and the second has a height that
 *    is the rest of the screen.
 *
 * I counld fill in the rest of the table with valid heights and a large
 * lastPos, but this method keeps the number of fill regions down to a 
 * minimum.
 *
 * One valid endty is needed at the end of the table so that the cursor
 * does not jump off the bottom of the window.
 */

  for ( count = 0; count < 2 ; count++) 
    if (line++ < ctx->text.lt.lines) { /* make sure not to run of the end. */
      (++lt)->y = (count == 0) ? y : ctx->core.height;
      lt->textWidth = 0;
      lt->position = ctx->text.lastPos + 100;
    }

  if (line < ctx->text.lt.lines) /* Clear out rest of table. */
    bzero( (char *) (lt + 1), 
	  (ctx->text.lt.lines - line) * sizeof(XawTextLineTableEntry) );

  ctx->text.lt.info[ctx->text.lt.lines].position = lt->position;

  return(endPos);
}

/*	Function Name: GetWidestLine
 *	Description: Returns the width (in pixels) of the widest line that
 *                   is currently visable.
 *	Arguments: ctx - the text widget.
 *	Returns: the width of the widest line.
 *
 * NOTE: This function requires a valid line table.
 */

static Dimension
GetWidestLine(ctx)
TextWidget ctx;
{
  int i;
  Dimension widest;
  XawTextLineTablePtr lt = &(ctx->text.lt);

  for (i = 0, widest = 1 ; i < lt->lines ; i++)
    if (widest < lt->info[i].textWidth)
      widest = lt->info[i].textWidth;
  
  return(widest);
}

static void
CheckVBarScrolling(ctx)
TextWidget ctx;
{
  float first, last;
  Boolean temp = (ctx->text.vbar == NULL);

  if (ctx->text.scroll_vert == XawtextScrollNever) return;

  if ( (ctx->text.lastPos > 0) && (ctx->text.lt.lines > 0)) {
    first = ctx->text.lt.top;
    first /= (float) ctx->text.lastPos; 
    last = ctx->text.lt.info[ctx->text.lt.lines].position;
    if ( ctx->text.lt.info[ctx->text.lt.lines].position <= ctx->text.lastPos)
      last /= (float) ctx->text.lastPos;
    else 
      last = 1.0;

    if (ctx->text.scroll_vert == XawtextScrollWhenNeeded)
      if ( (last - first) < 1.0 )
	CreateVScrollBar(ctx);
      else /* last - first >= 1.0 */
	DestroyVScrollBar(ctx);
  
    if (ctx->text.vbar != NULL) 
      XawScrollbarSetThumb(ctx->text.vbar, first, last - first);
  
    if ( (ctx->text.vbar == NULL) != temp) {
      _XawTextNeedsUpdating(ctx, zeroPosition, ctx->text.lastPos);
      if (ctx->text.vbar == NULL)
	_XawTextBuildLineTable (ctx, zeroPosition, FALSE);
    }
  }
  else if (ctx->text.vbar != NULL)
    if (ctx->text.scroll_vert == XawtextScrollWhenNeeded)
      DestroyVScrollBar(ctx);
    else if (ctx->text.scroll_vert == XawtextScrollAlways)
      XawScrollbarSetThumb(ctx->text.vbar, 0.0, 1.0);
}

/*
 * This routine is used by Text to notify an associated scrollbar of the
 * correct metrics (position and shown fraction) for the text being currently
 * displayed in the window.
 */

void 
_XawTextSetScrollBars(ctx)
TextWidget ctx;
{
  float first, last, widest;
  Boolean temp = (ctx->text.hbar == NULL);

  CheckVBarScrolling(ctx);

  if (ctx->text.scroll_horiz == XawtextScrollNever) return;

  if (ctx->text.vbar != NULL) 
    widest = (ctx->core.width - ctx->text.vbar->core.width -
	      ctx->text.vbar->core.border_width);
  else
    widest = ctx->core.width;
  widest /= (last = GetWidestLine(ctx));
  if (ctx->text.scroll_horiz == XawtextScrollWhenNeeded) 
    if (widest < 1.0)
      CreateHScrollBar(ctx);
    else
      DestroyHScrollBar(ctx);
  
  if (ctx->text.hbar != NULL) {
    first = ctx->text.r_margin.left - ctx->text.margin.left;
    first /= last;
    XawScrollbarSetThumb(ctx->text.hbar, first, widest); 
  }
  else if (ctx->text.margin.left != ctx->text.r_margin.left) {
    ctx->text.margin.left = ctx->text.r_margin.left;
    _XawTextNeedsUpdating(ctx, zeroPosition, ctx->text.lastPos);      
  }

  if ( (ctx->text.hbar == NULL) != temp ) {
    _XawTextBuildLineTable (ctx, ctx->text.lt.top, TRUE);
    CheckVBarScrolling(ctx);
  }
}

/*
 * The routine will scroll the displayed text by lines.  If the arg  is
 * positive, move up; otherwise, move down. [note: this is really a private
 * procedure but is used in multiple modules].
 */

void
_XawTextVScroll(ctx, n)
TextWidget ctx;
int n;			
{
  XawTextPosition top, target;
  int y;
  XawTextLineTable * lt = &(ctx->text.lt);

  if (abs(n) > ctx->text.lt.lines) 
    n = (n > 0) ? ctx->text.lt.lines : -ctx->text.lt.lines;

  if (n == 0) return;

  if (n > 0) {
    if ( IsValidLine(ctx, n) )
      top = Min(lt->info[n].position, ctx->text.lastPos);
    else
      top = ctx->text.lastPos;

    y = IsValidLine(ctx, n) ? lt->info[n].y : ctx->core.height;
    _XawTextBuildLineTable(ctx, top, FALSE);
    if (top >= ctx->text.lastPos)
      DisplayTextWindow( (Widget) ctx);
    else {
      XCopyArea(XtDisplay(ctx), XtWindow(ctx), XtWindow(ctx), ctx->text.gc,
		0, y, (int)ctx->core.width, (int)ctx->core.height - y,
		0, ctx->text.margin.top);
      SinkClearToBG(ctx->text.sink, 
		    (Position) 0,
		    (Position) (ctx->text.margin.top + ctx->core.height - y),
		   (Dimension) ctx->core.width, (Dimension) ctx->core.height);

      if (n < lt->lines) n++; /* update descenders at bottom */
      _XawTextNeedsUpdating(ctx, lt->info[lt->lines - n].position, 
			    ctx->text.lastPos);
      _XawTextSetScrollBars(ctx);
    }
  } 
  else {
    XawTextPosition updateTo;
    unsigned int height, clear_height;

    n = -n;
    target = lt->top;
    top = SrcScan(ctx->text.source, target, XawstEOL,
		  XawsdLeft, n+1, FALSE);

    _XawTextBuildLineTable(ctx, top, FALSE);
    y = IsValidLine(ctx, n) ? lt->info[n].y : ctx->core.height;
    updateTo = IsValidLine(ctx, n) ? lt->info[n].position : ctx->text.lastPos;
    if (IsValidLine(ctx, lt->lines - n))
      height = lt->info[lt->lines-n].y - ctx->text.margin.top;
    else if (ctx->core.height - HMargins(ctx))
      height = ctx->core.height - HMargins(ctx);
    else
      height = 0;
    if (y > (int) ctx->text.margin.top)
      clear_height = y - ctx->text.margin.top;
    else
      clear_height = 0;

    if ( updateTo == target ) {
      XCopyArea(XtDisplay(ctx), XtWindow(ctx), XtWindow(ctx), ctx->text.gc, 
		0, ctx->text.margin.top, (int) ctx->core.width, height, 0, y);
      SinkClearToBG(ctx->text.sink, (Position) 0, ctx->text.margin.top,
		   (Dimension) ctx->core.width, (Dimension) clear_height);
      
      _XawTextNeedsUpdating(ctx, lt->info[0].position, updateTo);
      _XawTextSetScrollBars(ctx);
    } 
    else if (lt->top != target)
      DisplayTextWindow((Widget)ctx);
  }
}

/*ARGSUSED*/
static void 
HScroll(w, closure, callData)
Widget w;
caddr_t closure;		/* TextWidget */
caddr_t callData;		/* #pixels */
{
  TextWidget ctx = (TextWidget) closure;
  Widget tw = (Widget) ctx;
  Position old_left, pixels = (Position) callData;
  XRectangle rect, t_rect;
  
  _XawTextPrepareToUpdate(ctx);

  old_left = ctx->text.margin.left;
  ctx->text.margin.left -= pixels;
  if (ctx->text.margin.left > ctx->text.r_margin.left) {
    ctx->text.margin.left = ctx->text.r_margin.left;
    pixels = old_left - ctx->text.margin.left;
  }
  
  if (pixels > 0) {
    rect.width = (unsigned short) pixels + ctx->text.margin.right;
    rect.x = (short) ctx->core.width - (short) rect.width;
    rect.y = (short) ctx->text.margin.top;
    rect.height = (unsigned short) ctx->core.height - rect.y;

    XCopyArea(XtDisplay(tw), XtWindow(tw), XtWindow(tw), ctx->text.gc,
	      pixels, (int) rect.y,
	      (unsigned int) rect.x, (unsigned int) ctx->core.height,
	      0, (int) rect.y);
  }
  else if (pixels < 0) {
    rect.x = 0;

    if (ctx->text.vbar != NULL)
      rect.x += (short) (ctx->text.vbar->core.width +
			 ctx->text.vbar->core.border_width);

    rect.width = (Position) - pixels;
    rect.y = ctx->text.margin.top;
    rect.height = ctx->core.height - rect.y;

    XCopyArea(XtDisplay(tw), XtWindow(tw), XtWindow(tw), ctx->text.gc,
	      (int) rect.x, (int) rect.y,
	      (unsigned int) ctx->core.width - rect.width,
	      (unsigned int) rect.height,
	      (int) rect.x + rect.width, (int) rect.y);

/*
 * Redraw the line overflow marks.
 */

    t_rect.x = ctx->core.width - ctx->text.margin.right;
    t_rect.width = ctx->text.margin.right;
    t_rect.y = rect.y;
    t_rect.height = rect.height;
      
    SinkClearToBG(ctx->text.sink, (Position) t_rect.x, (Position) t_rect.y,
		  (Dimension) t_rect.width, (Dimension) t_rect.height);
    
    UpdateTextInRectangle(ctx, &t_rect);
  }

/*  
 * Put in the text that just became visable.
 */

  if ( pixels != 0 ) {
    SinkClearToBG(ctx->text.sink, (Position) rect.x, (Position) rect.y,
		  (Dimension) rect.width, (Dimension) rect.height);
    
    UpdateTextInRectangle(ctx, &rect);
  }
  _XawTextExecuteUpdate(ctx);
  _XawTextSetScrollBars(ctx);
}

/*ARGSUSED*/
static void 
HJump(w, closure, callData)
Widget w;
caddr_t closure, callData; /* closure = TextWidget, callData = percent. */
{
  TextWidget ctx = (TextWidget) closure;
  float * percent = (float *) callData;
  Position move, new_left, old_left = ctx->text.margin.left;

  new_left = ctx->text.r_margin.left;
  new_left -= (Position) (*percent * GetWidestLine(ctx));
  move = old_left - new_left;

  if (abs(move) < ctx->core.width) {
    HScroll(w, (caddr_t) ctx, (caddr_t) move);
    return;
  }
  _XawTextPrepareToUpdate(ctx);
  ctx->text.margin.left = new_left;
  if (XtIsRealized((Widget) ctx)) DisplayTextWindow((Widget) ctx); 
  _XawTextExecuteUpdate(ctx);
}

/*	Function Name: UpdateTextInLine
 *	Description: Updates some text in a given line.
 *	Arguments: ctx - the text widget.
 *                 line - the line number (in the line table) of this line.
 *                 left, right - left and right pixel offsets of the
 *                               area to update.
 *	Returns: none.
 */

static void
UpdateTextInLine(ctx, line, left, right)
TextWidget ctx;
int line;
Position left, right;
{
  XawTextPosition pos1, pos2; 
  int width, height, local_left, local_width;
  XawTextLineTableEntry * lt = ctx->text.lt.info + line;

  if ( ((lt->textWidth + ctx->text.margin.left) < left) ||
       ( ctx->text.margin.left > right ) )
    return;			/* no need to update. */

  local_width = left - ctx->text.margin.left;
  XawTextSinkFindPosition(ctx->text.sink, lt->position,
			  (int) ctx->text.margin.left, 
			  local_width, FALSE, &pos1, &width, &height);

  if (right >= (Position) lt->textWidth - ctx->text.margin.left) 
    if ( (IsValidLine(ctx, line + 1)) &&
	 (ctx->text.lt.info[line + 1].position <= ctx->text.lastPos) )
      pos2 = SrcScan( ctx->text.source, (lt + 1)->position, XawstPositions, 
			   XawsdLeft, 1, TRUE);
    else 
      pos2 = GETLASTPOS;
  else {
    XawTextPosition t_pos;

    local_left = ctx->text.margin.left + width;
    local_width = right  - local_left;
    XawTextSinkFindPosition(ctx->text.sink, pos1, local_left,
			    local_width, FALSE, &pos2, &width, &height);
    
    t_pos = SrcScan( ctx->text.source, pos2,
		     XawstPositions, XawsdRight, 1, TRUE);
    if (t_pos < (lt + 1)->position)
      pos2 = t_pos;
  }

  _XawTextNeedsUpdating(ctx, pos1, pos2);
}

/*
 * The routine will scroll the displayed text by pixels.  If the calldata is
 * positive, move up; otherwise, move down.
 */

/*ARGSUSED*/
static void 
VScroll(w, closure, callData)
Widget w;
caddr_t closure;		/* TextWidget */
caddr_t callData;		/* #pixels */
{
  TextWidget ctx = (TextWidget)closure;
  int height, lines = (int) callData;

  height = ctx->core.height - VMargins(ctx);
  if (height < 1)
    height = 1;
  lines = (int) (lines * (int) ctx->text.lt.lines) / height;
  _XawTextPrepareToUpdate(ctx);
  _XawTextVScroll(ctx, lines);
  _XawTextExecuteUpdate(ctx);
}

/*
 * The routine "thumbs" the displayed text. Thumbing means reposition the
 * displayed view of the source to a new position determined by a fraction
 * of the way from beginning to end. Ideally, this should be determined by
 * the number of displayable lines in the source. This routine does it as a
 * fraction of the first position and last position and then normalizes to
 * the start of the line containing the position.
 *
 * BUG/deficiency: The normalize to line portion of this routine will
 * cause thumbing to always position to the start of the source.
 */

/*ARGSUSED*/
static void 
VJump(w, closure, callData)
Widget w;
caddr_t closure, callData; /* closuer = TextWidget, callData = percent. */
{
  float * percent = (float *) callData;
  TextWidget ctx = (TextWidget)closure;
  XawTextPosition position, old_top, old_bot;
  XawTextLineTable * lt = &(ctx->text.lt);

  _XawTextPrepareToUpdate(ctx);
  old_top = lt->top;
  if ( (lt->lines > 0) && (IsValidLine(ctx, lt->lines - 1)) )
    old_bot = lt->info[lt->lines - 1].position;
  else
    old_bot = ctx->text.lastPos;

  position = (long) (*percent * (float) ctx->text.lastPos);
  position= SrcScan(ctx->text.source, position, XawstEOL, XawsdLeft, 1, FALSE);
  if ( (position >= old_top) && (position <= old_bot) ) {
    int line = 0;
    for (;(line < lt->lines) && (position > lt->info[line].position) ; line++);
    _XawTextVScroll(ctx, line);
  }
  else {
    XawTextPosition new_bot;
    _XawTextBuildLineTable(ctx, position, FALSE);
    new_bot = IsValidLine(ctx, lt->lines-1) ? lt->info[lt->lines-1].position 
                                            : ctx->text.lastPos;

    if ((old_top >= lt->top) && (old_top <= new_bot)) {
      int line = 0;
      for (;(line < lt->lines) && (old_top > lt->info[line].position); line++);
      _XawTextBuildLineTable(ctx, old_top, FALSE);
      _XawTextVScroll(ctx, -line);
    }
    else 
      DisplayTextWindow( (Widget) ctx);
  }
  _XawTextExecuteUpdate(ctx);
}


static Boolean 
ConvertSelection(w, selection, target, type, value, length, format)
Widget w;
Atom *selection, *target, *type;
caddr_t *value;
unsigned long *length;
int *format;
{
  Display* d = XtDisplay(w);
  TextWidget ctx = (TextWidget)w;
  Widget src = ctx->text.source;
  XawTextEditType edit_mode;
  Arg args[1];

  if (*target == XA_TARGETS(d)) {
    Atom* targetP, * std_targets;
    unsigned long std_length;

    if ( SrcCvtSel(src, selection, target, type, value, length, format) ) 
	return True;

    XmuConvertStandardSelection(w, ctx->text.time, selection, 
				target, type, (caddr_t*)&std_targets,
				&std_length, format);
    
    *value = XtMalloc((unsigned) sizeof(Atom)*(std_length + 7));
    targetP = *(Atom**)value;
    *length = std_length + 6;
    *targetP++ = XA_STRING;
    *targetP++ = XA_TEXT(d);
    *targetP++ = XA_COMPOUND_TEXT(d);
    *targetP++ = XA_LENGTH(d);
    *targetP++ = XA_LIST_LENGTH(d);
    *targetP++ = XA_CHARACTER_POSITION(d);

    XtSetArg(args[0], XtNeditType,&edit_mode);
    XtGetValues(src, args, ONE);

    if (edit_mode == XawtextEdit) {
      *targetP++ = XA_DELETE(d);
      (*length)++;
    }
    bcopy((char*)std_targets, (char*)targetP, sizeof(Atom)*std_length);
    XtFree((char*)std_targets);
    *type = XA_ATOM;
    *format = 32;
    return True;
  }
  
  if ( SrcCvtSel(src, selection, target, type, value, length, format) )
    return True;

  if (*target == XA_STRING ||
      *target == XA_TEXT(d) ||
      *target == XA_COMPOUND_TEXT(d)) {
    if (*target == XA_COMPOUND_TEXT(d))
      *type = *target;
    else
      *type = XA_STRING;
    *value = _XawTextGetSTRING(ctx, ctx->text.s.left, ctx->text.s.right);
    *length = strlen(*value);
    *format = 8;
    return True;
  }

  if ( (*target == XA_LIST_LENGTH(d)) || (*target == XA_LENGTH(d)) ) {
    long * temp;
    
    temp = (long *) XtMalloc(sizeof(long));
    if (*target == XA_LIST_LENGTH(d))
      *temp = 1L;
    else			/* *target == XA_LENGTH(d) */
      *temp = (long) (ctx->text.s.right - ctx->text.s.left);
    
    *value = (caddr_t) temp;
    *type = XA_INTEGER;
    *length = 1L;
    *format = 32;
    return True;
  }

  if (*target == XA_CHARACTER_POSITION(d)) {
    long * temp;
    
    temp = (long *) XtMalloc(2 * sizeof(long));
    temp[0] = (long) (ctx->text.s.left + 1);
    temp[1] = ctx->text.s.right;
    *value = (caddr_t) temp;
    *type = XA_SPAN(d);
    *length = 2L;
    *format = 32;
    return True;
  }

  if (*target == XA_DELETE(d)) {
    void _XawTextZapSelection(); /* From TextAction.c */
    
    _XawTextZapSelection( ctx, (XEvent *) NULL, TRUE);
    *value = NULL;
    *type = XA_NULL(d);
    *length = 0;
    *format = 32;
    return True;
  }

  if (XmuConvertStandardSelection(w, ctx->text.time, selection, target, type,
				  value, length, format))
    return True;
  
  /* else */
  return False;
}

/*	Function Name: GetCutBuffferNumber
 *	Description: Returns the number of the cut buffer.
 *	Arguments: atom - the atom to check.
 *	Returns: the number of the cut buffer representing this atom or
 *               NOT_A_CUT_BUFFER.
 */

#define NOT_A_CUT_BUFFER -1

static int
GetCutBufferNumber(atom)
register Atom atom;
{
  if (atom == XA_CUT_BUFFER0) return(0);
  if (atom == XA_CUT_BUFFER1) return(1);
  if (atom == XA_CUT_BUFFER2) return(2);
  if (atom == XA_CUT_BUFFER3) return(3);
  if (atom == XA_CUT_BUFFER4) return(4);
  if (atom == XA_CUT_BUFFER5) return(5);
  if (atom == XA_CUT_BUFFER6) return(6);
  if (atom == XA_CUT_BUFFER7) return(7);
  return(NOT_A_CUT_BUFFER);
}

static void 
LoseSelection(w, selection)
Widget w;
Atom *selection;
{
  TextWidget ctx = (TextWidget) w;
  register Atom* atomP;
  register int i;

  _XawTextPrepareToUpdate(ctx);

  atomP = ctx->text.s.selections;
  for (i = 0 ; i < ctx->text.s.atom_count; i++, atomP++)
    if ( (*selection == *atomP) || 
	(GetCutBufferNumber(*atomP) != NOT_A_CUT_BUFFER) )/* is a cut buffer */
      *atomP = (Atom)0;

  while (ctx->text.s.atom_count &&
	 ctx->text.s.selections[ctx->text.s.atom_count-1] == 0)
    ctx->text.s.atom_count--;

/*
 * Must walk the selection list in opposite order from UnsetSelection.
 */

  atomP = ctx->text.s.selections;
  for (i = 0 ; i < ctx->text.s.atom_count; i++, atomP++)
    if (*atomP == (Atom)0) {
      *atomP = ctx->text.s.selections[--ctx->text.s.atom_count];
      while (ctx->text.s.atom_count &&
	     ctx->text.s.selections[ctx->text.s.atom_count-1] == 0)
	ctx->text.s.atom_count--;
    }
  
  if (ctx->text.s.atom_count == 0)
    ModifySelection(ctx, ctx->text.insertPos, ctx->text.insertPos);
      
  if (ctx->text.old_insert >= 0) /* Update in progress. */
    _XawTextExecuteUpdate(ctx);
}

void 
_SetSelection(ctx, left, right, selections, count)
TextWidget ctx;
XawTextPosition left, right;
Atom *selections;
Cardinal count;
{
  XawTextPosition pos;
  
  if (left < ctx->text.s.left) {
    pos = Min(right, ctx->text.s.left);
    _XawTextNeedsUpdating(ctx, left, pos);
  }
  if (left > ctx->text.s.left) {
    pos = Min(left, ctx->text.s.right);
    _XawTextNeedsUpdating(ctx, ctx->text.s.left, pos);
  }
  if (right < ctx->text.s.right) {
    pos = Max(right, ctx->text.s.left);
    _XawTextNeedsUpdating(ctx, pos, ctx->text.s.right);
  }
  if (right > ctx->text.s.right) {
    pos = Max(left, ctx->text.s.right);
    _XawTextNeedsUpdating(ctx, pos, right);
  }
  
  ctx->text.s.left = left;
  ctx->text.s.right = right;

  SrcSetSelection(ctx->text.source, left, right,
		  (count == 0) ? NULL : selections[0]);

  if (left < right) {
    Widget w = (Widget) ctx;
    int buffer;
    
    while (count) {
      Atom selection = selections[--count];
/*
 * If this is a cut buffer.
 */

      if ((buffer = GetCutBufferNumber(selection)) != NOT_A_CUT_BUFFER) {
	char *ptr;
	ptr = _XawTextGetSTRING(ctx, ctx->text.s.left, ctx->text.s.right);
	if (buffer == 0) {
	  _CreateCutBuffers(XtDisplay(w));
	  XRotateBuffers(XtDisplay(w), 1);
	}
	XStoreBuffer(XtDisplay(w), ptr, Min(strlen(ptr), MAXCUT), buffer);
	XtFree (ptr);
      }
      else			/* This is a real selection. */
	XtOwnSelection(w, selection, ctx->text.time,
		       (XtConvertSelectionProc)ConvertSelection,
		       LoseSelection, NULL);
    }
  }
  else
    XawTextUnsetSelection((Widget)ctx);
}

/*
 * This internal routine deletes the text from pos1 to pos2 in a source and
 * then inserts, at pos1, the text that was passed. As a side effect it
 * "invalidates" that portion of the displayed text (if any).
 *
 * NOTE: It is illegal to call this routine unless there is a valid line table!
 */

int 
_XawTextReplace (ctx, pos1, pos2, text)
TextWidget ctx;
XawTextPosition pos1, pos2;
XawTextBlock *text;
{
  int i, line1, delta, error;
  XawTextPosition updateFrom, updateTo;
  Widget src = ctx->text.source;
  XawTextEditType edit_mode;
  Arg args[1];
  
  ctx->text.update_disabled = True; /* No redisplay during replacement. */

/*
 * The insertPos may not always be set to the right spot in XawtextAppend 
 */

  XtSetArg(args[0], XtNeditType, &edit_mode);
  XtGetValues(src, args, ONE);

  if ((pos1 == ctx->text.insertPos) && (edit_mode == XawtextAppend)) {
    ctx->text.insertPos = ctx->text.lastPos;
    pos2 = SrcScan(src, ctx->text.insertPos, XawstPositions, XawsdRight,
		   (ctx->text.insertPos - pos1), TRUE);
    pos1 = ctx->text.insertPos;
    if ( (pos1 == pos2) && (text->length == 0) ) {
      ctx->text.update_disabled = FALSE; /* rearm redisplay. */
      return( XawEditError );
    }
  }

  updateFrom = SrcScan(src, pos1, XawstWhiteSpace, XawsdLeft, 1, TRUE);
  updateFrom = SrcScan(src, updateFrom, XawstPositions, XawsdLeft, 1, TRUE);
  updateFrom = Max(updateFrom, ctx->text.lt.top);

  line1 = LineForPosition(ctx, updateFrom);
  if ( (error = SrcReplace(src, pos1, pos2, text)) != 0) {
    ctx->text.update_disabled = FALSE; /* rearm redisplay. */
    return(error);
  }

  XawTextUnsetSelection((Widget)ctx);

  ctx->text.lastPos = GETLASTPOS;
  if (ctx->text.lt.top >= ctx->text.lastPos) {
    _XawTextBuildLineTable(ctx, ctx->text.lastPos, FALSE);
    ClearWindow( (Widget) ctx);
    ctx->text.update_disabled = FALSE; /* rearm redisplay. */
    return(0);			/* Things are fine. */
  }

  delta = text->length - (pos2 - pos1);

  if ( abs(delta) <= 1 )
      ctx->text.single_char = TRUE;
  else
      ctx->text.single_char = FALSE;

  if (delta < ctx->text.lastPos) {
    for (pos2 += delta, i = 0; i < ctx->text.numranges; i++) {
      if (ctx->text.updateFrom[i] > pos1)
	ctx->text.updateFrom[i] += delta;
      if (ctx->text.updateTo[i] >= pos1)
	ctx->text.updateTo[i] += delta;
    }
  }
  
  /* 
   * fixup all current line table entries to reflect edit.
   * %%% it is not legal to do arithmetic on positions.
   * using Scan would be more proper.
   */ 
  if (delta != 0) {
    XawTextLineTableEntry *lineP;
    i = LineForPosition(ctx, pos1) + 1;
    for (lineP = ctx->text.lt.info + i; i <= ctx->text.lt.lines; i++, lineP++)
      lineP->position += delta;
  }
  
  /*
   * Now process the line table and fixup in case edits caused
   * changes in line breaks. If we are breaking on word boundaries,
   * this code checks for moving words to and from lines.
   */
  
  if (IsPositionVisible(ctx, updateFrom)) {
    updateTo = _BuildLineTable(ctx, 
			       ctx->text.lt.info[line1].position, pos1, line1);
    _XawTextNeedsUpdating(ctx, updateFrom, updateTo);
  }

  ctx->text.update_disabled = FALSE; /* rearm redisplay. */
  return(0);			/* Things are fine. */
}

/*
 * This routine will display text between two arbitrary source positions.
 * In the event that this span contains highlighted text for the selection, 
 * only that portion will be displayed highlighted.
 *
 * NOTE: it is illegal to call this routine unless there
 *       is a valid line table! 
 */

static void 
DisplayText(w, pos1, pos2)
Widget w;
XawTextPosition pos1, pos2;
{
  TextWidget ctx = (TextWidget)w;
  Position x, y;
  int height, line, i, lastPos = ctx->text.lastPos;
  XawTextPosition startPos, endPos;
  Boolean clear_eol, done_painting;

  pos1 = (pos1 < ctx->text.lt.top) ? ctx->text.lt.top : pos1;
  pos2 = FindGoodPosition(ctx, pos2);
  if ( (pos1 >= pos2) || !LineAndXYForPosition(ctx, pos1, &line, &x, &y) )
    return;			/* line not visible, or pos1 >= pos2. */

  for ( startPos = pos1, i = line; IsValidLine(ctx, i) && 
                                   (i < ctx->text.lt.lines) ; i++) {

    
    if ( (endPos = ctx->text.lt.info[i + 1].position) > pos2 ) {
      clear_eol = ((endPos = pos2) >= lastPos);
      done_painting = (!clear_eol || ctx->text.single_char);
    }
    else {
      clear_eol = TRUE;
      done_painting = FALSE;
    }

    height = ctx->text.lt.info[i + 1].y - ctx->text.lt.info[i].y;

    if ( (endPos > startPos) ) {
      if ( (x == (Position) ctx->text.margin.left) && (x > 0) )
	 SinkClearToBG (ctx->text.sink,
			(Position) 0, y, 
			(Dimension) ctx->text.margin.left, (Dimension)height); 

      if ( (startPos >= ctx->text.s.right) || (endPos <= ctx->text.s.left) ) 
	XawTextSinkDisplayText(ctx->text.sink, x, y, startPos, endPos, FALSE);
      else if ((startPos >= ctx->text.s.left) && (endPos <= ctx->text.s.right))
	XawTextSinkDisplayText(ctx->text.sink, x, y, startPos, endPos, TRUE);
      else {
	DisplayText(w, startPos, ctx->text.s.left);
	DisplayText(w, Max(startPos, ctx->text.s.left),
		    Min(endPos, ctx->text.s.right));
	DisplayText(w, ctx->text.s.right, endPos);
      }
    }
    startPos = endPos;
    if (clear_eol) {
	SinkClearToBG(ctx->text.sink, 
		      (Position) (ctx->text.lt.info[i].textWidth +
				  ctx->text.margin.left),
		      (Position) y, w->core.width, (Dimension) height);

	/*
	 * We only get here if single character is true, and we need
	 * to clear to the end of the screen.  We know that since there
	 * was only on character deleted that this is the same
	 * as clearing an extra line, so we do this, and are done.
	 * 
	 * This a performance hack, and a pretty gross one, but it works.
	 *
	 * Chris Peterson 11/13/89.
	 */

	if (done_painting) {
	    y += height;
	    SinkClearToBG(ctx->text.sink, 
			  (Position) ctx->text.margin.left, (Position) y, 
			  w->core.width, (Dimension) height);

	    break;		/* set single_char to FALSE and return. */
	}
    }

    x = (Position) ctx->text.margin.left;
    y = ctx->text.lt.info[i + 1].y;
    if ( done_painting || (y >= ctx->core.height - ctx->text.margin.bottom) )
      break;
  }
  ctx->text.single_char = FALSE;
}

/*
 * This routine implements multi-click selection in a hardwired manner.
 * It supports multi-click entity cycling (char, word, line, file) and mouse
 * motion adjustment of the selected entitie (i.e. select a word then, with
 * button still down, adjust wich word you really meant by moving the mouse).
 * [NOTE: This routine is to be replaced by a set of procedures that
 * will allows clients to implements a wide class of draw through and
 * multi-click selection user interfaces.]
 */

static void 
DoSelection (ctx, pos, time, motion)
TextWidget ctx;
XawTextPosition pos;
Time time;
Boolean motion;
{
  XawTextPosition newLeft, newRight;
  XawTextSelectType newType, *sarray;
  Widget src = ctx->text.source;

  if (motion)
    newType = ctx->text.s.type;
  else {
    if ( (abs((long) time - (long) ctx->text.lasttime) < MULTI_CLICK_TIME) &&
	 ((pos >= ctx->text.s.left) && (pos <= ctx->text.s.right))) {
      sarray = ctx->text.sarray;
      for (;*sarray != XawselectNull && *sarray != ctx->text.s.type; sarray++);

      if (*sarray == XawselectNull)
	newType = *(ctx->text.sarray);
      else {
	newType = *(sarray + 1);
	if (newType == XawselectNull) 
	  newType = *(ctx->text.sarray);
      }
    } 
    else 			                      /* single-click event */
      newType = *(ctx->text.sarray);

    ctx->text.lasttime = time;
  }
  switch (newType) {
  case XawselectPosition: 
    newLeft = newRight = pos;
    break;
  case XawselectChar: 
    newLeft = pos;
    newRight = SrcScan(src, pos, XawstPositions, XawsdRight, 1, FALSE);
    break;
  case XawselectWord: 
    newRight = SrcScan(src, pos, XawstWhiteSpace, XawsdRight, 1, FALSE);
    newLeft= SrcScan(src, newRight, XawstWhiteSpace, XawsdLeft, 1, FALSE);
    break;
  case XawselectParagraph: 
    newRight = SrcScan(src, pos, XawstParagraph, XawsdRight, 1, FALSE);
    newLeft = SrcScan(src, newRight, XawstParagraph, XawsdLeft, 1, FALSE);
    break;
  case XawselectLine: 
    newLeft = SrcScan(src, pos, XawstEOL, XawsdLeft, 1, FALSE);
    newRight = SrcScan(src, pos, XawstEOL, XawsdRight, 1, FALSE);
    break;
  case XawselectAll: 
    newLeft = SrcScan(src, pos, XawstAll, XawsdLeft, 1, FALSE);
    newRight = SrcScan(src, pos, XawstAll, XawsdRight, 1, FALSE);
    break;
  default:
    XtAppWarning(XtWidgetToApplicationContext((Widget) ctx),
	       "Text Widget: empty selection array.");
    return;
  }

  if ( (newLeft != ctx->text.s.left) || (newRight != ctx->text.s.right)
      || (newType != ctx->text.s.type)) {
    ModifySelection(ctx, newLeft, newRight);
    if (pos - ctx->text.s.left < ctx->text.s.right - pos)
      ctx->text.insertPos = newLeft;
    else 
      ctx->text.insertPos = newRight;
    ctx->text.s.type = newType;
  }
  if (!motion) { /* setup so we can freely mix select extend calls*/
    ctx->text.origSel.type = ctx->text.s.type;
    ctx->text.origSel.left = ctx->text.s.left;
    ctx->text.origSel.right = ctx->text.s.right;

    if (pos >= ctx->text.s.left + ((ctx->text.s.right - ctx->text.s.left) / 2))
      ctx->text.extendDir = XawsdRight;
    else
      ctx->text.extendDir = XawsdLeft;
  }
}

/*
 * This routine implements extension of the currently selected text in
 * the "current" mode (i.e. char word, line, etc.). It worries about
 * extending from either end of the selection and handles the case when you
 * cross through the "center" of the current selection (e.g. switch which
 * end you are extending!).
 * [NOTE: This routine will be replaced by a set of procedures that
 * will allows clients to implements a wide class of draw through and
 * multi-click selection user interfaces.]
*/

static void 
ExtendSelection (ctx, pos, motion)
TextWidget ctx;
XawTextPosition pos;
Boolean motion;
{
  XawTextScanDirection dir;

  if (!motion) {		/* setup for extending selection */
    ctx->text.origSel.type = ctx->text.s.type;
    ctx->text.origSel.left = ctx->text.s.left;
    ctx->text.origSel.right = ctx->text.s.right;
    if (pos >= ctx->text.s.left + ((ctx->text.s.right - ctx->text.s.left) / 2))
      ctx->text.extendDir = XawsdRight;
    else
      ctx->text.extendDir = XawsdLeft;
  }
  else /* check for change in extend direction */
    if ((ctx->text.extendDir == XawsdRight && pos < ctx->text.origSel.left) ||
	(ctx->text.extendDir == XawsdLeft && pos > ctx->text.origSel.right)) {
      ctx->text.extendDir = (ctx->text.extendDir == XawsdRight) ?
	                                            XawsdLeft : XawsdRight;
      ModifySelection(ctx, ctx->text.origSel.left, ctx->text.origSel.right);
    }

  dir = ctx->text.extendDir;
  switch (ctx->text.s.type) {
  case XawselectWord: 
    pos = SrcScan(ctx->text.source, pos, XawstWhiteSpace, dir, 1, FALSE);
    break;
  case XawselectLine:
    pos = SrcScan(ctx->text.source, pos, XawstEOL, dir, 1, dir == XawsdRight);
    break;
  case XawselectParagraph:
    pos = SrcScan(ctx->text.source, pos, XawstParagraph, dir, 1, FALSE);
    break;
  case XawselectAll: 
    pos = ctx->text.insertPos;
  case XawselectPosition:	/* fall through. */
  default:
    break;
  }
  
  if (ctx->text.extendDir == XawsdRight)
    ModifySelection(ctx, ctx->text.s.left, pos);
  else
    ModifySelection(ctx, pos, ctx->text.s.right);

  ctx->text.insertPos = pos;
}

/*
 * Clear the window to background color.
 */

static void
ClearWindow (w)
Widget w;
{
  TextWidget ctx = (TextWidget) w;

  if (XtIsRealized(w))
    SinkClearToBG(ctx->text.sink, 
		  (Position) 0, (Position) 0, 
		  w->core.width, w->core.height);
}

/*	Function Name: _XawTextClearAndCenterDisplay
 *	Description: Redraws the display with the cursor in insert point
 *                   centered vertically.
 *	Arguments: ctx - the text widget.
 *	Returns: none.
 */

void
_XawTextClearAndCenterDisplay(ctx)
TextWidget ctx;
{
  int insert_line = LineForPosition(ctx, ctx->text.insertPos);
  int scroll_by = insert_line - ctx->text.lt.lines/2;

  _XawTextVScroll(ctx, scroll_by);
  DisplayTextWindow( (Widget) ctx);
}
  
/*
 * Internal redisplay entire window.
 * Legal to call only if widget is realized.
 */

static void
DisplayTextWindow (w)
Widget w;
{
  TextWidget ctx = (TextWidget) w;
  ClearWindow(w);
  _XawTextBuildLineTable(ctx, ctx->text.lt.top, FALSE);
  _XawTextNeedsUpdating(ctx, zeroPosition, ctx->text.lastPos);
  _XawTextSetScrollBars(ctx);
}

/*
 * This routine checks to see if the window should be resized (grown or
 * shrunk) when text to be painted overflows to the right or
 * the bottom of the window. It is used by the keyboard input routine.
 */

void
_XawTextCheckResize(ctx)
TextWidget ctx;
{
  Widget w = (Widget) ctx;
  int line = 0, old_height;
  XtWidgetGeometry rbox;

  if ( (ctx->text.resize == XawtextResizeWidth) ||
       (ctx->text.resize == XawtextResizeBoth) ) {
    XawTextLineTableEntry *lt;
    rbox.width = 0;
    for (lt = ctx->text.lt.info; 
	 IsValidLine(ctx, line) && (line < ctx->text.lt.lines) ; line++, lt++) 
      AssignMax(rbox.width, lt->textWidth + ctx->text.margin.left);
    
    rbox.width += ctx->text.margin.right;
    if (rbox.width > ctx->core.width) { /* Only get wider. */
      rbox.request_mode = CWWidth;
      if (XtMakeGeometryRequest(w, &rbox, &rbox) == XtGeometryAlmost)
	(void) XtMakeGeometryRequest(w, &rbox, &rbox);
    }
  }

  if ( !((ctx->text.resize == XawtextResizeHeight) ||
	 (ctx->text.resize == XawtextResizeBoth)) )
      return;

  if (IsPositionVisible(ctx, ctx->text.lastPos))
    line = LineForPosition(ctx, ctx->text.lastPos);
  else
    line = ctx->text.lt.lines;
  
  if ( (line + 1) == ctx->text.lt.lines ) return;
  
  old_height = ctx->core.height;
  rbox.request_mode = CWHeight;
  rbox.height = XawTextSinkMaxHeight(ctx->text.sink, line + 1) + VMargins(ctx);
  
  if (rbox.height < old_height) return; /* It will only get taller. */

  if (XtMakeGeometryRequest(w, &rbox, &rbox) == XtGeometryAlmost)
    if (XtMakeGeometryRequest(w, &rbox, &rbox) != XtGeometryYes)
      return;
  
  _XawTextBuildLineTable(ctx, ctx->text.lt.top, TRUE);
}

/*
 * Converts (params, num_params) to a list of atoms & caches the
 * list in the TextWidget instance.
 */

Atom*
_XawTextSelectionList(ctx, list, nelems)
TextWidget ctx;
String *list;
Cardinal nelems;
{
  Atom * sel = ctx->text.s.selections;

  if (nelems > ctx->text.s.array_size) {
    sel = (Atom *) XtRealloc((caddr_t)sel, sizeof(Atom) * nelems);
    ctx->text.s.array_size = nelems;
  }
  XmuInternStrings(XtDisplay((Widget)ctx), list, nelems, sel);
  ctx->text.s.atom_count = nelems;
  return(ctx->text.s.selections = sel);
}

/*	Function Name: SetSelection
 *	Description: Sets the current selection.
 *	Arguments: ctx - the text widget.
 *                 defaultSel - the default selection.
 *                 l, r - the left and right ends of the selection.
 *                 list, nelems - the selection list (as strings).
 *	Returns: none.
 *
 *  NOTE: if (ctx->text.s.left >= ctx->text.s.right) then the selection
 *        is unset.
 */

void
_XawTextSetSelection(ctx, l, r, list, nelems)
TextWidget ctx;
XawTextPosition l, r;
String *list;
Cardinal nelems;
{
  if (nelems == 0) {
    String defaultSel = "PRIMARY";
    list = &defaultSel;
    nelems = 1;
  }
  _SetSelection(ctx, l, r, _XawTextSelectionList(ctx, list, nelems), nelems);
}


/*	Function Name: ModifySelection
 *	Description: Modifies the current selection.
 *	Arguments: ctx - the text widget.
 *                 left, right - the left and right ends of the selection.
 *	Returns: none.
 *
 *  NOTE: if (ctx->text.s.left >= ctx->text.s.right) then the selection
 *        is unset.
 */

static void
ModifySelection(ctx, left, right)
TextWidget ctx;
XawTextPosition left, right;
{
  if (left == right) 
    ctx->text.insertPos = left;
  _SetSelection( ctx, left, right, (Atom *)NULL, ZERO);
}

/*
 * This routine is used to perform various selection functions. The goal is
 * to be able to specify all the more popular forms of draw-through and
 * multi-click selection user interfaces from the outside.
 */

void 
_XawTextAlterSelection (ctx, mode, action, params, num_params)
TextWidget ctx;
XawTextSelectionMode mode;   /* {XawsmTextSelect, XawsmTextExtend} */
XawTextSelectionAction action; /* {XawactionStart, 
				  XawactionAdjust, XawactionEnd} */
String	*params;
Cardinal	*num_params;
{
  XawTextPosition position;
  Boolean flag;

/*
 * This flag is used by TextPop.c:DoReplace() to determine if the selection
 * is okay to use, or if it has been modified.
 */
    
  if (ctx->text.search != NULL)
    ctx->text.search->selection_changed = TRUE;

  position = PositionForXY (ctx, (int) ctx->text.ev_x, (int) ctx->text.ev_y);

  flag = (action != XawactionStart);
  if (mode == XawsmTextSelect)
    DoSelection (ctx, position, ctx->text.time, flag);
  else			/* mode == XawsmTextExtend */
    ExtendSelection (ctx, position, flag);

  if (action == XawactionEnd) 
    _XawTextSetSelection(ctx, ctx->text.s.left, ctx->text.s.right,
			 params, *num_params);
}

/*	Function Name: RectanglesOverlap
 *	Description: Returns TRUE if two rectangles overlap.
 *	Arguments: rect1, rect2 - the two rectangles to check.
 *	Returns: TRUE iff these rectangles overlap.
 */

static Boolean
RectanglesOverlap(rect1, rect2)
XRectangle *rect1, *rect2;
{
  return ( (rect1->x < rect2->x + (short) rect2->width) &&
	   (rect2->x < rect1->x + (short) rect1->width) &&
	   (rect1->y < rect2->y + (short) rect2->height) &&
	   (rect2->y < rect1->y + (short) rect1->height) );
}

/*	Function Name: UpdateTextInRectangle.
 *	Description: Updates the text in a rectangle.
 *	Arguments: ctx - the text widget.
 *                 rect - the rectangle to update.
 *	Returns: none.
 */

static void
UpdateTextInRectangle(ctx, rect)
TextWidget ctx;
XRectangle * rect;
{
  XawTextLineTableEntry *info = ctx->text.lt.info;
  int line, x = rect->x, y = rect->y;
  int right = rect->width + x, bottom = rect->height + y;

  for (line = 0;( (line < ctx->text.lt.lines) &&
		 IsValidLine(ctx, line) && (info->y < bottom)); line++, info++)
    if ( (info + 1)->y >= y ) 
      UpdateTextInLine(ctx, line, x, right);
}

/*
 * This routine processes all "expose region" XEvents. In general, its job
 * is to the best job at minimal re-paint of the text, displayed in the
 * window, that it can.
 */

/* ARGSUSED */
static void
ProcessExposeRegion(w, event, region)
Widget w;
XEvent *event;
Region region;			/* Unused. */
{
    TextWidget ctx = (TextWidget) w;
    XRectangle expose, cursor;
    
    if (event->type == Expose) {
	expose.x = event->xexpose.x;
	expose.y = event->xexpose.y;
	expose.width = event->xexpose.width;
	expose.height = event->xexpose.height;
    }
    else {  /* Graphics Expose. */
	expose.x = event->xgraphicsexpose.x;
	expose.y = event->xgraphicsexpose.y;
	expose.width = event->xgraphicsexpose.width;
	expose.height = event->xgraphicsexpose.height;
    }      
    
    _XawTextPrepareToUpdate(ctx);
    UpdateTextInRectangle(ctx, &expose);
    XawTextSinkGetCursorBounds(ctx->text.sink, &cursor);
    if (RectanglesOverlap(&cursor, &expose)) {
	SinkClearToBG(ctx->text.sink, (Position) cursor.x, (Position) cursor.y,
		      (Dimension) cursor.width, (Dimension) cursor.height);
	UpdateTextInRectangle(ctx, &cursor);
    }
    _XawTextExecuteUpdate(ctx);
}

/*
 * This routine does all setup required to syncronize batched screen updates
 */

void 
_XawTextPrepareToUpdate(ctx)
TextWidget ctx;
{
  if (ctx->text.old_insert < 0) {
    InsertCursor((Widget)ctx, XawisOff);
    ctx->text.numranges = 0;
    ctx->text.showposition = FALSE;
    ctx->text.old_insert = ctx->text.insertPos;
  }
}

/*
 * This is a private utility routine used by _XawTextExecuteUpdate. It
 * processes all the outstanding update requests and merges update
 * ranges where possible.
 */

static 
void FlushUpdate(ctx)
TextWidget ctx;
{
  int i, w;
  XawTextPosition updateFrom, updateTo;
  if (!XtIsRealized((Widget)ctx)) {
    ctx->text.numranges = 0;
    return;
  }
  while (ctx->text.numranges > 0) {
    updateFrom = ctx->text.updateFrom[0];
    w = 0;
    for (i = 1 ; i < ctx->text.numranges ; i++) {
      if (ctx->text.updateFrom[i] < updateFrom) {
	updateFrom = ctx->text.updateFrom[i];
	w = i;
      }
    }
    updateTo = ctx->text.updateTo[w];
    ctx->text.numranges--;
    ctx->text.updateFrom[w] = ctx->text.updateFrom[ctx->text.numranges];
    ctx->text.updateTo[w] = ctx->text.updateTo[ctx->text.numranges];
    for (i = ctx->text.numranges - 1 ; i >= 0 ; i--) {
      while (ctx->text.updateFrom[i] <= updateTo && i < ctx->text.numranges) {
	updateTo = ctx->text.updateTo[i];
	ctx->text.numranges--;
	ctx->text.updateFrom[i] = ctx->text.updateFrom[ctx->text.numranges];
	ctx->text.updateTo[i] = ctx->text.updateTo[ctx->text.numranges];
      }
    }
    DisplayText((Widget)ctx, updateFrom, updateTo);
  }
}

/*
 * This is a private utility routine used by _XawTextExecuteUpdate. This
 * routine worries about edits causing new data or the insertion point becoming
 * invisible (off the screen, or under the horiz. scrollbar). Currently 
 * it always makes it visible by scrolling. It probably needs 
 * generalization to allow more options.
 */

void _XawTextShowPosition(ctx)
TextWidget ctx;
{
  int x, y, number, lines;
  XawTextPosition max_pos, top, first, second;

  if ( (!XtIsRealized((Widget)ctx)) || (ctx->text.lt.lines <= 0) )
    return;
  
#ifdef notdef
  lines = ctx->text.lt.lines;
  if ( IsValidLine(ctx, lines)) 
    max_pos = ctx->text.lt.info[lines].position;
  else
    max_pos = ctx->text.lastPos + 1;
#else				/* Using this code now... */

/*
 * Find out the bottom the visable window, and make sure that the
 * cursor does not go past the end of this space.  
 *
 * This makes sure that the cursor does not go past the end of the 
 * visable window. 
 */

  x = ctx->text.margin.left;
  y = ctx->core.height - ctx->text.margin.left;
  if (ctx->text.hbar != NULL)
    y -= ctx->text.hbar->core.height - 2 * ctx->text.hbar->core.border_width;
  
  max_pos = PositionForXY (ctx, x, y);
  max_pos = SrcScan(ctx->text.source, max_pos, XawstEOL, XawsdRight, 1, FALSE);
  max_pos++;
  lines = LineForPosition(ctx, max_pos); /* number of visable lines. */
#endif
  
  if ( (ctx->text.insertPos >= ctx->text.lt.top) &&
       ((ctx->text.insertPos < max_pos) || ( max_pos > ctx->text.lastPos)) ) 
    return;

  first = ctx->text.lt.top;
  if (IsValidLine(ctx, 1))
    second = ctx->text.lt.info[1].position;
  else
    second = max_pos;
      
  if (ctx->text.insertPos < first)
    number = 1;
  else
    number = lines;

  top = SrcScan(ctx->text.source, ctx->text.insertPos,
		XawstEOL, XawsdLeft, number, FALSE);

  _XawTextBuildLineTable(ctx, top, FALSE);
  while (ctx->text.insertPos >= ctx->text.lt.info[lines].position) {
    if (ctx->text.lt.info[lines].position > ctx->text.lastPos)
      break; 
    _XawTextBuildLineTable(ctx, ctx->text.lt.info[1].position, FALSE);
  }
  if (ctx->text.lt.top == second) {
    _XawTextBuildLineTable(ctx, first, FALSE);
    _XawTextVScroll(ctx, 1);
  } else if (ctx->text.lt.info[1].position == first) {
    _XawTextBuildLineTable(ctx, first, FALSE);
    _XawTextVScroll(ctx, -1);
  } else {
    ctx->text.numranges = 0;
    if (ctx->text.lt.top != first)
      DisplayTextWindow((Widget)ctx);
  }
}

/*
 * This routine causes all batched screen updates to be performed
 */

void
_XawTextExecuteUpdate(ctx)
TextWidget ctx;
{
  if ( ctx->text.update_disabled || (ctx->text.old_insert < 0) ) 
    return;

  if((ctx->text.old_insert != ctx->text.insertPos) || (ctx->text.showposition))
    _XawTextShowPosition(ctx);
  FlushUpdate(ctx);
  InsertCursor((Widget)ctx, XawisOn);
  ctx->text.old_insert = -1;
}


static void 
TextDestroy(w)
Widget w;
{
  TextWidget ctx = (TextWidget)w;

  if (ctx->text.file_insert != NULL)
    XtDestroyWidget(ctx->text.file_insert);
 
  DestroyHScrollBar(ctx);
  DestroyVScrollBar(ctx);

  XtFree((char *)ctx->text.updateFrom);
  XtFree((char *)ctx->text.updateTo);
}

/*
 * by the time we are managed (and get this far) we had better
 * have both a source and a sink 
 */

static void
Resize(w)
Widget w;
{
  TextWidget ctx = (TextWidget) w;

  PositionVScrollBar(ctx);
  PositionHScrollBar(ctx);

  _XawTextBuildLineTable(ctx, ctx->text.lt.top, TRUE);
  _XawTextSetScrollBars(ctx);
}

/*
 * This routine allow the application program to Set attributes.
 */

/*ARGSUSED*/
static Boolean 
SetValues(current, request, new, args, num_args)
Widget current, request, new;
ArgList args;
Cardinal *num_args;
{
  TextWidget oldtw = (TextWidget) current;
  TextWidget newtw = (TextWidget) new;
  Boolean    redisplay = FALSE;
  Boolean    display_caret = newtw->text.display_caret;


#ifdef XAW_BC
/*******************************
 * For Compatability.          */

  if (newtw->text.options != oldtw->text.options)
    XawTextChangeOptions((Widget) newtw, newtw->text.options);
/*******************************/
#endif /* XAW_BC */  

  newtw->text.display_caret = oldtw->text.display_caret;
  _XawTextPrepareToUpdate(newtw);
  newtw->text.display_caret = display_caret;

  if (oldtw->text.r_margin.left != newtw->text.r_margin.left) {
    newtw->text.margin.left = newtw->text.r_margin.left;
    if (newtw->text.vbar != NULL)
      newtw->text.margin.left += newtw->text.vbar->core.width +
	                         newtw->text.vbar->core.border_width;
    redisplay = TRUE;
  }
  
  if (oldtw->text.scroll_vert != newtw->text.scroll_vert) {
    if (newtw->text.scroll_vert == XawtextScrollNever) 
      DestroyVScrollBar(newtw);
    else if (newtw->text.scroll_vert == XawtextScrollAlways)
      CreateVScrollBar(newtw);
    redisplay = TRUE;
  }

  if (oldtw->text.r_margin.bottom != newtw->text.r_margin.bottom) {
    newtw->text.margin.bottom = newtw->text.r_margin.bottom;
    if (newtw->text.hbar != NULL)
      newtw->text.margin.bottom += newtw->text.hbar->core.height +
	                           newtw->text.hbar->core.border_width;
    redisplay = TRUE;
  }
  
  if (oldtw->text.scroll_horiz != newtw->text.scroll_horiz) {
    if (newtw->text.scroll_horiz == XawtextScrollNever) 
      DestroyHScrollBar(newtw);
    else if (newtw->text.scroll_horiz == XawtextScrollAlways)
      CreateHScrollBar(newtw);
    redisplay = TRUE;
  }

  if ( oldtw->text.source != newtw->text.source )
    XawTextSetSource( (Widget) newtw, newtw->text.source, newtw->text.lt.top);

  newtw->text.redisplay_needed = False;
  XtSetValues( (Widget)newtw->text.source, args, *num_args );
  XtSetValues( (Widget)newtw->text.sink, args, *num_args );

  if ( oldtw->text.wrap != newtw->text.wrap ||
       oldtw->text.lt.top != newtw->text.lt.top ||
       oldtw->text.r_margin.right != newtw->text.r_margin.right ||
       oldtw->text.r_margin.top != newtw->text.r_margin.top ||
       oldtw->text.sink != newtw->text.sink ||
       newtw->text.redisplay_needed )
  {
    _XawTextBuildLineTable(newtw, newtw->text.lt.top, TRUE);
    redisplay = TRUE;
  }

  if (oldtw->text.insertPos != newtw->text.insertPos)
    newtw->text.showposition = TRUE;
  
  _XawTextExecuteUpdate(newtw);
  if (redisplay)
    _XawTextSetScrollBars(newtw);

  return redisplay;
}

/*	Function Name: GetValuesHook
 *	Description: This is a get values hook routine that gets the
 *                   values in the text source and sink.
 *	Arguments: w - the Text Widget.
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
  XtGetValues( ((TextWidget) w)->text.source, args, *num_args );
  XtGetValues( ((TextWidget) w)->text.sink, args, *num_args );
}

/*	Function Name: FindGoodPosition
 *	Description: Returns a valid position given any postition
 *	Arguments: pos - any position.
 *	Returns: a position between (0 and lastPos);
 */

static XawTextPosition
FindGoodPosition(ctx, pos)
TextWidget ctx;
XawTextPosition pos;
{
  if (pos < 0) return(0);
  return ( ((pos > ctx->text.lastPos) ? ctx->text.lastPos : pos) );
}

/*******************************************************************
The following routines provide procedural interfaces to Text window state
setting and getting. They need to be redone so than the args code can use
them. I suggest we create a complete set that takes the context as an
argument and then have the public version lookp the context and call the
internal one. The major value of this set is that they have actual application
clients and therefore the functionality provided is required for any future
version of Text.
********************************************************************/

void 
XawTextDisplay (w)
Widget w;
{
  if (!XtIsRealized(w)) return;
  
  _XawTextPrepareToUpdate( (TextWidget) w);
  DisplayTextWindow(w);
  _XawTextExecuteUpdate( (TextWidget) w);
}

void
XawTextSetSelectionArray(w, sarray)
Widget w;
XawTextSelectType *sarray;
{
  ((TextWidget)w)->text.sarray = sarray;
}

void
XawTextGetSelectionPos(w, left, right)
Widget w;
XawTextPosition *left, *right;
{
  *left = ((TextWidget) w)->text.s.left;
  *right = ((TextWidget) w)->text.s.right;
}


void 
XawTextSetSource(w, source, startPos)
Widget w, source;
XawTextPosition startPos;
{
  TextWidget ctx = (TextWidget) w;

  ctx->text.source = source;
  ctx->text.lt.top = startPos;
  ctx->text.s.left = ctx->text.s.right = 0;
  ctx->text.insertPos = startPos;
  ctx->text.lastPos = GETLASTPOS;
  
  _XawTextBuildLineTable(ctx, ctx->text.lt.top, TRUE);
  XawTextDisplay(w);
}

/*
 * This public routine deletes the text from startPos to endPos in a source and
 * then inserts, at startPos, the text that was passed. As a side effect it
 * "invalidates" that portion of the displayed text (if any), so that things
 * will be repainted properly.
 */

int 
XawTextReplace(w, startPos, endPos, text)
Widget w;
XawTextPosition  startPos, endPos;
XawTextBlock *text;
{
  TextWidget ctx = (TextWidget) w;
  int result;

  _XawTextPrepareToUpdate(ctx);
  endPos = FindGoodPosition(ctx, endPos);
  startPos = FindGoodPosition(ctx, startPos);
  if ((result = _XawTextReplace(ctx, startPos, endPos, text)) == XawEditDone) {
    int delta = text->length - (endPos - startPos);
    if (ctx->text.insertPos >= (endPos + delta)) {
      XawTextScanDirection sd = (delta < 0) ? XawsdLeft : XawsdRight;
      ctx->text.insertPos = SrcScan(ctx->text.source, ctx->text.insertPos,
				    XawstPositions, sd, abs(delta), TRUE);
    }
  }

  _XawTextCheckResize(ctx);
  _XawTextExecuteUpdate(ctx);
  _XawTextSetScrollBars(ctx);
  
  return result;
}

XawTextPosition 
XawTextTopPosition(w)
Widget w;
{
  return( ((TextWidget) w)->text.lt.top );
}

void 
XawTextSetInsertionPoint(w, position)
Widget w;
XawTextPosition position;
{
  TextWidget ctx = (TextWidget) w;

  _XawTextPrepareToUpdate(ctx);
  ctx->text.insertPos = FindGoodPosition(ctx, position);
  ctx->text.showposition = TRUE;
  _XawTextExecuteUpdate(ctx);
}

XawTextPosition
XawTextGetInsertionPoint(w)
Widget w;
{
  return( ((TextWidget) w)->text.insertPos);
}

/*
 * NOTE: Must walk the selection list in opposite order from LoseSelection.
 */

void 
XawTextUnsetSelection(w)
Widget w;
{
  register TextWidget ctx = (TextWidget)w;

  while (ctx->text.s.atom_count != 0) {
    Atom sel = ctx->text.s.selections[ctx->text.s.atom_count - 1];
    if ( sel != (Atom) 0 ) {
/*
 * As selections are lost the atom_count will decrement.
 */
      if (GetCutBufferNumber(sel) == NOT_A_CUT_BUFFER)
	XtDisownSelection(w, sel, ctx->text.time);
      LoseSelection(w, &sel); /* In case this is a cut buffer, or 
				 XtDisownSelection failed to call us. */
    }
  }
}

#ifdef XAW_BC
void 
XawTextChangeOptions(w, options)
Widget w;
int options;
{
  TextWidget ctx = (TextWidget) w;

  ctx->text.options = options;

  if (ctx->text.options & scrollVertical)
    ctx->text.scroll_vert = XawtextScrollAlways;
  else 
    ctx->text.scroll_vert = XawtextScrollNever;

  if (ctx->text.options & scrollHorizontal)
    ctx->text.scroll_horiz = XawtextScrollAlways;
  else 
    ctx->text.scroll_horiz = XawtextScrollNever;

  if (ctx->text.options & resizeWidth) /* Set up resize options. */
    if (ctx->text.options & resizeHeight)
      ctx->text.resize = XawtextResizeBoth;
    else
      ctx->text.resize = XawtextResizeWidth;
  else if (ctx->text.options & resizeHeight)
    ctx->text.resize = XawtextResizeHeight;
  else
    ctx->text.resize = XawtextResizeNever;

  if (ctx->text.options & wordBreak)
    ctx->text.wrap = XawtextWrapWord;
  else
    ctx->text.wrap = XawtextWrapNever;
}

int 
XawTextGetOptions(w)
Widget w;
{
  return(((TextWidget) w)->text.options);
}
#endif /* XAW_BC */

void
XawTextSetSelection (w, left, right)
Widget w;
XawTextPosition left, right;
{
  TextWidget ctx = (TextWidget) w;
  
  _XawTextPrepareToUpdate(ctx);
  _XawTextSetSelection(ctx, FindGoodPosition(ctx, left),
		       FindGoodPosition(ctx, right), (String *)NULL, ZERO);
  _XawTextExecuteUpdate(ctx);
}

void 
XawTextInvalidate(w, from, to)
Widget w;
XawTextPosition from,to;
{
  TextWidget ctx = (TextWidget) w;

  from = FindGoodPosition(ctx, from);
  to = FindGoodPosition(ctx, to);
  ctx->text.lastPos = GETLASTPOS;
  _XawTextPrepareToUpdate(ctx);
  _XawTextNeedsUpdating(ctx, from, to);
  _XawTextBuildLineTable(ctx, ctx->text.lt.top, TRUE);
  _XawTextExecuteUpdate(ctx);
}

/*ARGSUSED*/
void 
XawTextDisableRedisplay(w)
Widget w;
{
  ((TextWidget) w)->text.update_disabled = True;
  _XawTextPrepareToUpdate( (TextWidget) w);
}

void 
XawTextEnableRedisplay(w)
Widget w;
{
  register TextWidget ctx = (TextWidget)w;
  XawTextPosition lastPos;

  if (!ctx->text.update_disabled) return;

  ctx->text.update_disabled = False;
  lastPos = ctx->text.lastPos = GETLASTPOS;
  ctx->text.lt.top = FindGoodPosition(ctx, ctx->text.lt.top);
  ctx->text.insertPos = FindGoodPosition(ctx, ctx->text.insertPos);
  if ( (ctx->text.s.left > lastPos) || (ctx->text.s.right > lastPos) ) 
    ctx->text.s.left = ctx->text.s.right = 0;
  
  _XawTextBuildLineTable(ctx, ctx->text.lt.top, TRUE);
  if (XtIsRealized(w))
    DisplayTextWindow(w);
  _XawTextExecuteUpdate(ctx);
}

Widget
XawTextGetSource(w)
Widget w;
{
  return ((TextWidget)w)->text.source;
}

void 
XawTextDisplayCaret (w, display_caret)
Widget w;
Boolean display_caret;
{
  TextWidget ctx = (TextWidget) w;

  if (ctx->text.display_caret == display_caret) return;

  if (XtIsRealized(w)) {
    _XawTextPrepareToUpdate(ctx);
    ctx->text.display_caret = display_caret;
    _XawTextExecuteUpdate(ctx);
  }
  else
    ctx->text.display_caret = display_caret;
}

/*	Function Name: XawTextSearch(w, dir, text).
 *	Description: searches for the given text block.
 *	Arguments: w - The text widget.
 *                 dir - The direction to search. 
 *                 text - The text block containing info about the string
 *                        to search for.
 *	Returns: The position of the text found, or XawTextSearchError on 
 *               an error.
 */

XawTextPosition
XawTextSearch(w, dir, text) 
Widget w;
XawTextScanDirection dir;
XawTextBlock * text;
{
  TextWidget ctx = (TextWidget) w;

  return(SrcSearch(ctx->text.source, ctx->text.insertPos, dir, text));
}
  
TextClassRec textClassRec = {
  { /* core fields */
    /* superclass       */      (WidgetClass) &simpleClassRec,
    /* class_name       */      "Text",
    /* widget_size      */      sizeof(TextRec),
    /* class_initialize */      ClassInitialize,
    /* class_part_init  */	NULL,
    /* class_inited     */      FALSE,
    /* initialize       */      Initialize,
    /* initialize_hook  */	NULL,
    /* realize          */      Realize,
    /* actions          */      textActionsTable,
    /* num_actions      */      0,                /* Set in ClassInitialize. */
    /* resources        */      resources,
    /* num_ resource    */      XtNumber(resources),
    /* xrm_class        */      NULLQUARK,
    /* compress_motion  */      TRUE,
    /* compress_exposure*/      XtExposeGraphicsExpose,
    /* compress_enterleave*/	TRUE,
    /* visible_interest */      FALSE,
    /* destroy          */      TextDestroy,
    /* resize           */      Resize,
    /* expose           */      ProcessExposeRegion,
    /* set_values       */      SetValues,
    /* set_values_hook  */	NULL,
    /* set_values_almost*/	XtInheritSetValuesAlmost,
    /* get_values_hook  */	GetValuesHook,
    /* accept_focus     */      NULL,
    /* version          */	XtVersion,
    /* callback_private */      NULL,
    /* tm_table         */      NULL,    /* set in ClassInitialize */
    /* query_geometry   */	XtInheritQueryGeometry,
    /* display_accelerator*/	XtInheritDisplayAccelerator,
    /* extension	*/	NULL
  },
  { /* Simple fields */
    /* change_sensitive	*/	XtInheritChangeSensitive
  },
  { /* text fields */
    /* empty            */	0
  }
};

WidgetClass textWidgetClass = (WidgetClass)&textClassRec;
