#ifndef lint
static char Xrcsid[] = "$XConsortium: Command.c,v 1.70 89/12/12 20:17:23 swick Exp $";
#endif /* lint */

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
 * Command.c - Command button widget
 *
 */

#include <stdio.h>

#include <X11/IntrinsicP.h>
#include <X11/StringDefs.h>

#include <X11/Xmu/Misc.h>

#include <./Xaw3_1XawInit.h>
#include <./Xaw3_1CommandP.h>

#ifdef SHAPE
#include <X11/Xmu/Converters.h>
#endif

#define DEFAULT_HIGHLIGHT_THICKNESS 2

#ifdef SHAPE
#    define DEFAULT_SHAPE_HIGHLIGHT 32767
#endif

/****************************************************************
 *
 * Full class record constant
 *
 ****************************************************************/

/* Private Data */

static char defaultTranslations[] =
    "<EnterWindow>:	highlight()		\n\
     <LeaveWindow>:	reset()			\n\
     <Btn1Down>:	set()			\n\
     <Btn1Up>:		notify() unset()	";

#define offset(field) XtOffset(CommandWidget, field)
static XtResource resources[] = { 

   {XtNcallback, XtCCallback, XtRCallback, sizeof(XtPointer), 
      offset(command.callbacks), XtRCallback, (XtPointer)NULL},
   {XtNhighlightThickness, XtCThickness, XtRDimension, sizeof(Dimension),
#ifndef SHAPE
      offset(command.highlight_thickness), XtRImmediate,
      (XtPointer)DEFAULT_HIGHLIGHT_THICKNESS },
#else
      offset(command.highlight_thickness), XtRImmediate,
      (XtPointer) DEFAULT_SHAPE_HIGHLIGHT},

   {XtNshapeStyle, XtCShapeStyle, XtRShapeStyle, sizeof(int),
      offset(command.shape_style), XtRImmediate, (XtPointer)XawShapeRectangle},
   {XtNcornerRoundPercent, XtCCornerRoundPercent, 
	XtRDimension, sizeof(Dimension),
	offset(command.corner_round), XtRImmediate, (XtPointer) 25},
#endif /*SHAPE*/
};
#undef offset

static Boolean SetValues();
static void Initialize(), Redisplay(), Set(), Reset(), Notify(), Unset();
static void Highlight(), Unhighlight(), Destroy(), PaintCommandWidget();
static void ClassInitialize();

#ifdef SHAPE
static Boolean ShapeButton();
static void Realize(), Resize();
#endif /* SHAPE */

static XtActionsRec actionsList[] =
{
  {"set",		Set},
  {"notify",		Notify},
  {"highlight",		Highlight},
  {"reset",		Reset},
  {"unset",		Unset},
  {"unhighlight",	Unhighlight},
};

/*
 * This is a temporary exported actions list for the command
 * widget I have added this code because there is a bug in the MIT
 * Xtk Intrinsics implementation that does not allow the action table
 * to be retreived from the widget class, Ralph Swick has promised me that
 * this will eventually be fixed, but until then this is how the toggle
 * widget will get the command widget's actions list.
 *
 * Chris D. Peterson - 12/28/88.
 */

XtActionList xaw_command_actions_list = actionsList;

#define SuperClass ((LabelWidgetClass)&labelClassRec)

CommandClassRec commandClassRec = {
  {
    (WidgetClass) SuperClass,		/* superclass		  */	
    "Command",				/* class_name		  */
    sizeof(CommandRec),			/* size			  */
    ClassInitialize,			/* class_initialize	  */
    NULL,				/* class_part_initialize  */
    FALSE,				/* class_inited		  */
    Initialize,				/* initialize		  */
    NULL,				/* initialize_hook	  */
#ifdef SHAPE
    Realize,				/* realize		  */
#else
    XtInheritRealize,			/* realize		  */
#endif /*SHAPE*/
    actionsList,			/* actions		  */
    XtNumber(actionsList),		/* num_actions		  */
    resources,				/* resources		  */
    XtNumber(resources),		/* resource_count	  */
    NULLQUARK,				/* xrm_class		  */
    FALSE,				/* compress_motion	  */
    TRUE,				/* compress_exposure	  */
    TRUE,				/* compress_enterleave    */
    FALSE,				/* visible_interest	  */
    Destroy,				/* destroy		  */
#ifdef SHAPE
    Resize,				/* resize		  */
#else
    XtInheritResize,			/* resize		  */
#endif /* SHAPE */
    Redisplay,				/* expose		  */
    SetValues,				/* set_values		  */
    NULL,				/* set_values_hook	  */
    XtInheritSetValuesAlmost,		/* set_values_almost	  */
    NULL,				/* get_values_hook	  */
    NULL,				/* accept_focus		  */
    XtVersion,				/* version		  */
    NULL,				/* callback_private	  */
    defaultTranslations,		/* tm_table		  */
    XtInheritQueryGeometry,		/* query_geometry	  */
    XtInheritDisplayAccelerator,	/* display_accelerator	  */
    NULL				/* extension		  */
  },  /* CoreClass fields initialization */
  {
    XtInheritChangeSensitive		/* change_sensitive	*/
  },  /* SimpleClass fields initialization */
  {
    0,                                     /* field not used    */
  },  /* LabelClass fields initialization */
  {
    0,                                     /* field not used    */
  },  /* CommandClass fields initialization */
};

  /* for public consumption */
WidgetClass commandWidgetClass = (WidgetClass) &commandClassRec;

/****************************************************************
 *
 * Private Procedures
 *
 ****************************************************************/

static GC 
Get_GC(cbw, fg, bg)
CommandWidget cbw;
Pixel fg, bg;
{
  XGCValues	values;
  
  values.foreground   = fg;
  values.background	= bg;
  values.font		= cbw->label.font->fid;
  values.cap_style = CapProjecting;
  
  if (cbw->command.highlight_thickness > 1 )
    values.line_width   = cbw->command.highlight_thickness;
  else 
    values.line_width   = 0;
  
  return XtGetGC((Widget)cbw,
		 (GCForeground|GCBackground|GCFont|GCLineWidth|GCCapStyle),
		 &values);
}


/* ARGSUSED */
static void 
Initialize(request, new, args, num_args)
Widget request, new;
ArgList args;			/* unused */
Cardinal *num_args;		/* unused */
{
  CommandWidget cbw = (CommandWidget) new;
#ifdef SHAPE
  int shape_event_base, shape_error_base;

  if (cbw->command.shape_style != XawShapeRectangle
      && !XShapeQueryExtension(XtDisplay(new), &shape_event_base, 
			       &shape_error_base))
      cbw->command.shape_style = XawShapeRectangle;
  if (cbw->command.highlight_thickness == DEFAULT_SHAPE_HIGHLIGHT) {
      if (cbw->command.shape_style != XawShapeRectangle)
	  cbw->command.highlight_thickness = 0;
      else
	  cbw->command.highlight_thickness = DEFAULT_HIGHLIGHT_THICKNESS;
  }
#endif /*SHAPE*/

  cbw->command.normal_GC = Get_GC(cbw, cbw->label.foreground, 
				  cbw->core.background_pixel);
  cbw->command.inverse_GC = Get_GC(cbw, cbw->core.background_pixel, 
				   cbw->label.foreground);
  XtReleaseGC(new, cbw->label.normal_GC);
  cbw->label.normal_GC = cbw->command.normal_GC;

  cbw->command.set = FALSE;
  cbw->command.highlighted = HighlightNone;
}

static Region 
HighlightRegion(cbw)
CommandWidget cbw;
{
  static Region outerRegion = NULL, innerRegion, emptyRegion;
  XRectangle rect;

  if (cbw->command.highlight_thickness == 0 ||
      cbw->command.highlight_thickness > Min(cbw->core.width,
					     cbw->core.height)/2)
    return(NULL);

  if (outerRegion == NULL) {
    /* save time by allocating scratch regions only once. */
    outerRegion = XCreateRegion();
    innerRegion = XCreateRegion();
    emptyRegion = XCreateRegion();
  }

  rect.x = rect.y = 0;
  rect.width = cbw->core.width;
  rect.height = cbw->core.height;
  XUnionRectWithRegion( &rect, emptyRegion, outerRegion );
  rect.x = rect.y = cbw->command.highlight_thickness;
  rect.width -= cbw->command.highlight_thickness * 2;
  rect.height -= cbw->command.highlight_thickness * 2;
  XUnionRectWithRegion( &rect, emptyRegion, innerRegion );
  XSubtractRegion( outerRegion, innerRegion, outerRegion );
  return outerRegion;
}

/***************************
*
*  Action Procedures
*
***************************/

/* ARGSUSED */
static void 
Set(w,event,params,num_params)
Widget w;
XEvent *event;
String *params;		/* unused */
Cardinal *num_params;	/* unused */
{
  CommandWidget cbw = (CommandWidget)w;

  if (cbw->command.set)
    return;

  cbw->command.set= TRUE;
  if (XtIsRealized(w))
    PaintCommandWidget(w, (Region) NULL, TRUE);
}

/* ARGSUSED */
static void
Unset(w,event,params,num_params)
Widget w;
XEvent *event;
String *params;		/* unused */
Cardinal *num_params;
{
  CommandWidget cbw = (CommandWidget)w;

  if (!cbw->command.set)
    return;

  cbw->command.set = FALSE;
  if (XtIsRealized(w)) {
    XClearWindow(XtDisplay(w), XtWindow(w));
    PaintCommandWidget(w, (Region) NULL, TRUE);
  }
}

/* ARGSUSED */
static void 
Reset(w,event,params,num_params)
Widget w;
XEvent *event;
String *params;		/* unused */
Cardinal *num_params;   /* unused */
{
  CommandWidget cbw = (CommandWidget)w;

  if (cbw->command.set) {
    cbw->command.highlighted = HighlightNone;
    Unset(w, event, params, num_params);
  }
  else
    Unhighlight(w, event, params, num_params);
}

/* ARGSUSED */
static void 
Highlight(w,event,params,num_params)
Widget w;
XEvent *event;
String *params;		
Cardinal *num_params;	
{
  CommandWidget cbw = (CommandWidget)w;

  if ( *num_params == (Cardinal) 0) 
    cbw->command.highlighted = HighlightWhenUnset;
  else {
    if ( *num_params != (Cardinal) 1) 
      XtWarning("Too many parameters passed to highlight action table.");
    switch (params[0][0]) {
    case 'A':
    case 'a':
      cbw->command.highlighted = HighlightAlways;
      break;
    default:
      cbw->command.highlighted = HighlightWhenUnset;
      break;
    }
  }

  if (XtIsRealized(w))
    PaintCommandWidget(w, HighlightRegion(cbw), TRUE);
}

/* ARGSUSED */
static void 
Unhighlight(w,event,params,num_params)
Widget w;
XEvent *event;
String *params;		/* unused */
Cardinal *num_params;	/* unused */
{
  CommandWidget cbw = (CommandWidget)w;

  cbw->command.highlighted = HighlightNone;
  if (XtIsRealized(w))
    PaintCommandWidget(w, HighlightRegion(cbw), TRUE);
}

/* ARGSUSED */
static void 
Notify(w,event,params,num_params)
Widget w;
XEvent *event;
String *params;		/* unused */
Cardinal *num_params;	/* unused */
{
  CommandWidget cbw = (CommandWidget)w; 

  /* check to be sure state is still Set so that user can cancel
     the action (e.g. by moving outside the window, in the default
     bindings.
  */
  if (cbw->command.set)
    XtCallCallbackList(w, cbw->command.callbacks, NULL);
}

/*
 * Repaint the widget window
 */

/************************
*
*  REDISPLAY (DRAW)
*
************************/

/* ARGSUSED */
static void 
Redisplay(w, event, region)
Widget w;
XEvent *event;
Region region;
{
  PaintCommandWidget(w, region, FALSE);
}

/*	Function Name: PaintCommandWidget
 *	Description: Paints the command widget.
 *	Arguments: w - the command widget.
 *                 region - region to paint (passed to the superclass).
 *                 change - did it change either set or highlight state?
 *	Returns: none
 */

static void 
PaintCommandWidget(w, region, change)
Widget w;
Region region;
Boolean change;
{
  CommandWidget cbw = (CommandWidget) w;
  Boolean very_thick;
  GC norm_gc, rev_gc;
   
  very_thick = cbw->command.highlight_thickness > Min(cbw->core.width,
						      cbw->core.height)/2;

  if (cbw->command.set) {
    cbw->label.normal_GC = cbw->command.inverse_GC;
    XFillRectangle(XtDisplay(w), XtWindow(w), cbw->command.normal_GC,
		   0, 0, cbw->core.width, cbw->core.height);
    region = NULL;		/* Force label to repaint text. */
  }
  else
      cbw->label.normal_GC = cbw->command.normal_GC;

  if (cbw->command.highlight_thickness <= 0)
  {
    (*SuperClass->core_class.expose) (w, (XEvent *) NULL, region);
    return;
  }

/*
 * If we are set then use the same colors as if we are not highlighted. 
 */

  if (cbw->command.set == (cbw->command.highlighted == HighlightNone)) {
    norm_gc = cbw->command.inverse_GC;
    rev_gc = cbw->command.normal_GC;
  }
  else {
    norm_gc = cbw->command.normal_GC;
    rev_gc = cbw->command.inverse_GC;
  }

  if ( !( (!change && (cbw->command.highlighted == HighlightNone)) ||
	  ((cbw->command.highlighted == HighlightWhenUnset) &&
	   (cbw->command.set))) ) {
    if (very_thick) {
      cbw->label.normal_GC = norm_gc; /* Give the label the right GC. */
      XFillRectangle(XtDisplay(w),XtWindow(w), rev_gc,
		     0, 0, cbw->core.width, cbw->core.height);
    }
    else {
      /* wide lines are centered on the path, so indent it */
      int offset = cbw->command.highlight_thickness/2;
      XDrawRectangle(XtDisplay(w),XtWindow(w), rev_gc, offset, offset, 
		     cbw->core.width - cbw->command.highlight_thickness,
		     cbw->core.height - cbw->command.highlight_thickness);
    }
  }
  (*SuperClass->core_class.expose) (w, (XEvent *) NULL, region);
}

static void 
Destroy(w)
Widget w;
{
  CommandWidget cbw = (CommandWidget) w;

  /* so Label can release it */
  if (cbw->label.normal_GC == cbw->command.normal_GC)
    XtReleaseGC( w, cbw->command.inverse_GC );
  else
    XtReleaseGC( w, cbw->command.normal_GC );
}

/*
 * Set specified arguments into widget
 */

/* ARGSUSED */
static Boolean 
SetValues (current, request, new)
Widget current, request, new;
{
  CommandWidget oldcbw = (CommandWidget) current;
  CommandWidget cbw = (CommandWidget) new;
  Boolean redisplay = False;

  if ( oldcbw->core.sensitive != cbw->core.sensitive && !cbw->core.sensitive) {
    /* about to become insensitive */
    cbw->command.set = FALSE;
    cbw->command.highlighted = HighlightNone;
    redisplay = TRUE;
  }
  
  if ( (oldcbw->label.foreground != cbw->label.foreground)           ||
       (oldcbw->core.background_pixel != cbw->core.background_pixel) ||
       (oldcbw->command.highlight_thickness != 
                                   cbw->command.highlight_thickness) ||
       (oldcbw->label.font != cbw->label.font) ) 
  {
    if (oldcbw->label.normal_GC == oldcbw->command.normal_GC)
	/* Label has release one of these */
      XtReleaseGC(new, cbw->command.inverse_GC);
    else
      XtReleaseGC(new, cbw->command.normal_GC);

    cbw->command.normal_GC = Get_GC(cbw, cbw->label.foreground, 
				    cbw->core.background_pixel);
    cbw->command.inverse_GC = Get_GC(cbw, cbw->core.background_pixel, 
				     cbw->label.foreground);
    XtReleaseGC(new, cbw->label.normal_GC);
    cbw->label.normal_GC = (cbw->command.set
			    ? cbw->command.inverse_GC
			    : cbw->command.normal_GC);
    
    redisplay = True;
  }

#ifdef SHAPE
  if ( XtIsRealized(new)
       && oldcbw->command.shape_style != cbw->command.shape_style
       && !ShapeButton(cbw))
  {
      cbw->command.shape_style = oldcbw->command.shape_style;
  }
#endif /*SHAPE*/

  return (redisplay);
}

static void ClassInitialize()
{
    XawInitializeWidgetSet();
#ifdef SHAPE
    XtSetTypeConverter( XtRString, XtRShapeStyle, XmuCvtStringToShapeStyle,
		        NULL, 0, XtCacheNone, NULL );
#endif
}



#ifdef SHAPE

static Boolean
ShapeButton(cbw)
CommandWidget cbw;
{
    Dimension corner_size;

    if ( (cbw->command.shape_style == XawShapeRoundedRectangle) ) {
	corner_size = (cbw->core.width < cbw->core.height) ? cbw->core.width 
	                                                   : cbw->core.height;
	corner_size = (corner_size * cbw->command.corner_round) / 100;
    }

    if (cbw->command.shape_style != XawShapeRectangle) {
	if (!XmuReshapeWidget((Widget) cbw, cbw->command.shape_style,
			      corner_size, corner_size)) {
	    cbw->command.shape_style = XawShapeRectangle;
	    return(False);
	}
    }
    return(TRUE);
}

static void Realize(w, valueMask, attributes)
    Widget w;
    Mask *valueMask;
    XSetWindowAttributes *attributes;
{
    (*commandWidgetClass->core_class.superclass->core_class.realize)
	(w, valueMask, attributes);

    ShapeButton( (CommandWidget) w);
}

static void Resize(w)
    Widget w;
{
    if (XtIsRealized(w)) 
	ShapeButton( (CommandWidget) w);

    (*commandWidgetClass->core_class.superclass->core_class.resize)(w);
}
#endif /*SHAPE*/
