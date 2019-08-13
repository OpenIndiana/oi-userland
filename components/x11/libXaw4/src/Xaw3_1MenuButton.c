#ifndef lint
static char Xrcsid[] = "$XConsortium: MenuButton.c,v 1.13 89/12/11 14:57:40 kit Exp $";
#endif /* lint */

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
 */


/***********************************************************************
 *
 * MenuButton Widget
 *
 ***********************************************************************/

/*
 * MenuButton.c - Source code for MenuButton widget.
 *
 * This is the source code for the Athena MenuButton widget.
 * It is intended to provide an easy method of activating pulldown menus.
 *
 * Date:    May 2, 1989
 *
 * By:      Chris D. Peterson
 *          MIT X Consortium 
 *          kit@expo.lcs.mit.edu
 */

#include <stdio.h>
#include <X11/IntrinsicP.h>
#include <X11/StringDefs.h>

#include <./Xaw3_1XawInit.h>
#include <./Xaw3_1MenuButtoP.h>

static void Realize();
static void PopupMenu();

#define superclass ((CommandWidgetClass)&commandClassRec)

static char defaultTranslations[] = 
    "<EnterWindow>:     highlight()             \n\
     <LeaveWindow>:     reset()                 \n\
     <BtnDown>:         reset() PopupMenu()     ";

/****************************************************************
 *
 * Full class record constant
 *
 ****************************************************************/

/* Private Data */

#define offset(field) XtOffset(MenuButtonWidget, field)
static XtResource resources[] = {
  {
    XtNmenuName, XtCMenuName, XtRString, sizeof(String), 
    offset(menu_button.menu_name), XtRString, (caddr_t)"menu"},
};
#undef offset

static XtActionsRec actionsList[] =
{
  {"PopupMenu",	PopupMenu}
};

/* %%% Export the actions list as a hack until an Intrinsics interface 
 * allows applications to call action procedures.  Used in xmh: button.c
 * Donna Converse, 7 July, 1989.  To be removed before R4 public release.
 */
XtActionList xaw_mbutton_actions_list = actionsList;
/* End of the hack */

MenuButtonClassRec menuButtonClassRec = {
  {
    (WidgetClass) superclass,		/* superclass		  */	
    "MenuButton",			/* class_name		  */
    sizeof(MenuButtonRec),       	/* size			  */
    XawInitializeWidgetSet,		/* class_initialize	  */
    NULL,				/* class_part_initialize  */
    FALSE,				/* class_inited		  */
    NULL,				/* initialize		  */
    NULL,				/* initialize_hook	  */
    Realize,         			/* realize		  */
    actionsList,			/* actions		  */
    XtNumber(actionsList),		/* num_actions		  */
    resources,				/* resources		  */
    XtNumber(resources),		/* resource_count	  */
    NULLQUARK,				/* xrm_class		  */
    FALSE,				/* compress_motion	  */
    TRUE,				/* compress_exposure	  */
    TRUE,				/* compress_enterleave    */
    FALSE,				/* visible_interest	  */
    NULL,				/* destroy		  */
    XtInheritResize,			/* resize		  */
    XtInheritExpose,			/* expose		  */
    NULL,				/* set_values		  */
    NULL,				/* set_values_hook	  */
    XtInheritSetValuesAlmost,		/* set_values_almost	  */
    NULL,				/* get_values_hook	  */
    NULL,				/* accept_focus		  */
    XtVersion,				/* version		  */
    NULL,				/* callback_private	  */
    defaultTranslations,               	/* tm_table		  */
    XtInheritQueryGeometry,		/* query_geometry	  */
    XtInheritDisplayAccelerator,	/* display_accelerator	  */
    NULL				/* extension		  */
  },  /* CoreClass fields initialization */
  {
    XtInheritChangeSensitive		/* change_sensitive	  */ 
  },  /* SimpleClass fields initialization */
  {
    0,                                     /* field not used    */
  },  /* LabelClass fields initialization */
  {
    0,                                     /* field not used    */
  },  /* CommandClass fields initialization */
  {
    0,                                     /* field not used    */
  },  /* MenuButtonClass fields initialization */
};

  /* for public consumption */
WidgetClass menuButtonWidgetClass = (WidgetClass) &menuButtonClassRec;

/****************************************************************
 *
 * Private Procedures
 *
 ****************************************************************/

/* ARGSUSED */
static void 
Realize(w, mask, attrs)
Widget w;
Mask *mask;
XSetWindowAttributes *attrs;
{
  (*superclass->core_class.realize) (w, mask, attrs);

  /* We have a window now. Register a grab. */

  XGrabButton( XtDisplay(w), AnyButton, AnyModifier, XtWindow(w),
	       TRUE, ButtonPressMask|ButtonReleaseMask,
	       GrabModeAsync, GrabModeAsync, None, None );
} 
  
/* ARGSUSED */
static void
PopupMenu(w, event, params, num_params)
Widget w;
XEvent * event;
String * params;
Cardinal * num_params;
{
  MenuButtonWidget mbw = (MenuButtonWidget) w;
  Widget menu, temp;
  Arg arglist[2];
  Cardinal num_args;
  int menu_x, menu_y, menu_width, menu_height, button_width, button_height;
  Position button_x, button_y;

  temp = w;
  while(temp != NULL) {
    menu = XtNameToWidget(temp, mbw->menu_button.menu_name);
    if (menu == NULL) 
      temp = XtParent(temp);
    else
      break;
  }

  if (menu == NULL) {
    char error_buf[BUFSIZ];
    sprintf(error_buf, "MenuButton: %s %s.",
	    "Could not find menu widget named", mbw->menu_button.menu_name);
    XtAppWarning(XtWidgetToApplicationContext(w), error_buf);
    return;
  }
  if (!XtIsRealized(menu))
    XtRealizeWidget(menu);
  
  menu_width = menu->core.width + 2 * menu->core.border_width;
  button_width = w->core.width + 2 * w->core.border_width;
  button_height = w->core.height + 2 * w->core.border_width;

  menu_height = menu->core.height + 2 * menu->core.border_width;

  XtTranslateCoords(w, 0, 0, &button_x, &button_y);
  menu_x = button_x;
  menu_y = button_y + button_height;

  if (menu_x < 0) 
    menu_x = 0;
  else {
    int scr_width = WidthOfScreen(XtScreen(menu));
    if (menu_x + menu_width > scr_width)
      menu_x = scr_width - menu_width;
  }

  if (menu_y < 0)
    menu_y = 0;
  else {
    int scr_height = HeightOfScreen(XtScreen(menu));
    if (menu_y + menu_height > scr_height)
      menu_y = scr_height - menu_height;
  }

  num_args = 0;
  XtSetArg(arglist[num_args], XtNx, menu_x); num_args++;
  XtSetArg(arglist[num_args], XtNy, menu_y); num_args++;
  XtSetValues(menu, arglist, num_args);

  XtPopupSpringLoaded(menu);
}

