/*
*
* Copyright (c) 1993, 2015, Oracle and/or its affiliates. All rights reserved.
*
* Permission is hereby granted, free of charge, to any person obtaining a
* copy of this software and associated documentation files (the "Software"),
* to deal in the Software without restriction, including without limitation
* the rights to use, copy, modify, merge, publish, distribute, sublicense,
* and/or sell copies of the Software, and to permit persons to whom the
* Software is furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice (including the next
* paragraph) shall be included in all copies or substantial portions of the
* Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
* THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
* FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
* DEALINGS IN THE SOFTWARE.
*/

/************************************************************************/
/*									*/
/*		Copyright 1987, 1988, 1989, 1990, 1991, 1992, 1993	*/
/*		by Digital Equipment Corp., Maynard, MA			*/
/*									*/
/*	Permission to use, copy, modify, and distribute this software	*/
/*	and its documentation for any purpose and without fee is hereby	*/
/*	granted, provided that the above copyright notice appear in all	*/
/*	copies and that both that copyright notice and this permission 	*/
/*	notice appear in supporting documentation, and that the name of	*/
/*	Digital not be used in advertising or publicity pertaining to	*/
/*	distribution of the software without specific, written prior 	*/
/*	permission.  							*/
/*									*/
/*	DIGITAL DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE,	*/
/*	INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND 	*/
/*	FITNESS, IN NO EVENT SHALL DIGITAL BE LIABLE FOR ANY SPECIAL,	*/
/*	INDIRECT OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER 	*/
/*	RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN 	*/
/*	ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, 	*/
/*	ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE 	*/
/*	OF THIS SOFTWARE.						*/
/*									*/
/************************************************************************/
/*									*/
/* AccessX	   						        */
/* 									*/
/* 	This module is intended to provide access features for people	*/
/*	with physical disabilities.  This is a Motif client that	*/
/*	communicates with the AccessX server extension and allows us to	*/
/*	get visual feedback regarding the state of the AccessX features.*/
/*									*/
/* Revision History:							*/
/*									*/
/*	11-Jun-1993	WDW & MEN					*/
/*			Develop sample implementation.			*/
/*									*/
/*	14-Aug-1993	JMS & WEJ					*/
/*			Redesign GUI					*/
/*									*/
/************************************************************************/

/* Special constants needed for the accessx extension */
#define NEED_EVENTS
#define NEED_REPLIES

/************************************************************************/
/*                                                                      */
/* Include Files                                                        */
/*                                                                      */
/************************************************************************/
 
/* Standard C Include Files */
#include <stdio.h>
#include <sys/param.h>
#include <stdlib.h>
 
/* X Window System Include Files */
#include <X11/Xlib.h>
#include <X11/Xproto.h>
#include <X11/Intrinsic.h>
 
/* accessx Specific Include Files */
#include "AccessXlib.h"
#include "AccessXproto.h"
#include "accessx.btm"

/* XKB files */
#include <X11/XKBlib.h>

/* Help related files */
#include <locale.h>


/* Motif Toolkit Include Files */
#include <Xm/Form.h>
#include <Xm/Text.h>
#include <Xm/DialogS.h>
#include <Xm/MessageB.h>
#include <Xm/ToggleB.h>
#include <Xm/ToggleBG.h>
#include <Xm/Scale.h>
#include <Mrm/MrmAppl.h>

/************************************************************************/
/*									*/
/* Forward Declarations							*/
/*									*/
/************************************************************************/
#if NeedFunctionPrototypes
#define P(s) s
#else
#define P(s) ()
#endif

int XAccessXConfigure P((Display                   *dpy,
    			 AccessXClientContextRec   *accessXClient,
    			 CARD16                    mask,
			 AccessXStateRec           *accessXState));
int XAccessXQueryState P((Display                  *dpy,
                          AccessXClientContextRec  *accessXClient,
                          AccessXStateRec          *accessXState));
void XAccessXSelectInput P((Display                        *dpy,
                            AccessXClientContextRec        *accessXClient,
                            BYTE                           enable));
void XAccessXInit P((Display                       *dpy,
                     AccessXClientContextRec       *accessXClient));
void XAccessXAppMainLoop P((XtAppContext                   appContext,
                            AccessXClientContextRec        *accessXClient));


void AccessXEventHandler P((XAccessXEvent *));

/* Conversion Related Functions */
float ConvertScaleValueToUnits P((int, short));
int   ConvertUnitsToScaleValue P((float, short));

/* State-of-Widget related Functions */
void SetStateFromView P((void));
void SetStateFromViewXKB P((void));
void SetStateFromViewAX P((void));
void SetViewFromState P((void));
void SetViewFromStateXKB P((void));
void SetViewFromStateAX P((void));
void SetSettingsViewFromState P((AccessXStateRec));
void SetStickyStatusViewFromState P((void));
void SetStickyStatusViewFromStateXKB P((void));
void SetStickyStatusViewFromStateAX P((void));
void SetMouseStatusViewFromState P((void));
void SetMouseStatusViewFromStateXKB P((void));
void SetMouseStatusViewFromStateAX P((void));
void UpdateWidgetSensitivity P((void));
void DisplayStatusDialogsIfNeeded P((void));
void SetDefaults P((void));
void SetDefaultsXKB P((void));
void SetDefaultsAX P((void));

/* UIL Callback Functions */
void CreateProc P((Widget, int *, unsigned long));
void ActivateProc P((Widget, int *, XmAnyCallbackStruct *));
void ChangeControlProc P((Widget, int *, XmToggleButtonCallbackStruct *));
 
/* Help Facility Functions */
int  GetSizeOfHelpText P((int));
Bool AllocateHelpTextMemory P((int));
Bool SetHelpText P((int));
Bool InitHelp P((void));
Bool ReadHelpFile P((FILE *));

/* Creation-Destruction Status Windows Functions */
void InitializeInterface P((unsigned int, char **));
void CreateAndMapStickyStatusWindow P((void));
void UnmapStickyStatusWindow P((void));
void CreateAndMapMouseStatusWindow P((void));
void UnmapMouseStatusWindow P((void));
 
/* Load-Save Related Functions */
char *ResolveResourceFileName P((void));
void LoadSettingsFromFile P((void));
void SaveSettingsToFile P((void));
void StoreSettingsWindowToDatabase P((void));
void RestoreSettingsWindowFromDatabase P((void));

/* XKB related functions */
Boolean XkbEventHandler P((XEvent *));
Boolean InitXkb P((Display *));
#undef P

/************************************************************************/
/*									*/
/* X11, Xt, and Other Global Variables					*/
/*									*/
/************************************************************************/
AccessXClientContextRec	accessXClient;

/* X11, Xt and General Widgets Global Variables */
Display         *dpy;
XtAppContext    appContext;
Widget		topLevel;
Widget		mainWindow;
static XrmDatabase  	settingsWindowDatabase = NULL;

/* XKB stuff */
int		xkbEventBase;

/* Widgets Shells and Dialogs */
Widget		mouseTopLevel = NULL;
Widget		stickyTopLevel = NULL;
Widget 		statusStickyKeysDialog; 
Widget 		statusMouseKeysDialog; 
Widget		settingsDialog;
Widget		helpDialog;
Widget		helpErrDialog, helpErrBox;
Widget		saveDoneDialog, saveDoneBox;
Widget		saveErrDialog, saveErrBox;
Widget		loadDoneDialog, loadDoneBox;
Widget		loadErrDialog, loadErrBox;

/* Global Flags and State */
char 		*textString;		/* Help text string */
int		XKBExtension;		/* 1:XKB 0:Accessx */

/************************************************************************/
/*									*/
/* Mrm & Motif Global Variables						*/
/*									*/
/************************************************************************/
MrmHierarchy	mrmHierarchy;	
MrmCode         dummyClass;

char *dbFilenameVec[] = {"accessx.uid"};
int dbFilenameNum = (sizeof dbFilenameVec / sizeof dbFilenameVec [0]);

static MrmRegisterArg regList [] = { 
    {"CreateProc", (caddr_t)CreateProc},
    {"ActivateProc", (caddr_t)ActivateProc},
    {"ChangeControlProc", (caddr_t)ChangeControlProc}
};
int regListNum = (sizeof regList / sizeof regList[0]);

/* Motif String Global Variables */
XmString helpWindowString;
XmString stickyKeysString, mouseKeysString;
XmString shiftString, shiftEmptyString;
XmString controlString, controlEmptyString;
XmString mod1String, mod1EmptyString;
XmString mod2String, mod2EmptyString;
XmString mod3String, mod3EmptyString;
XmString mod4String, mod4EmptyString;
XmString mod5String, mod5EmptyString;
XmString mb1String, mb1EmptyString;
XmString mb2String, mb2EmptyString;
XmString mb3String, mb3EmptyString;
XmString mb4String, mb4EmptyString;
XmString mb5String, mb5EmptyString;

/************************************************************************/
/*									*/
/* 	Help Global variables						*/
/*									*/
/************************************************************************/
static char *generalHelpString = NULL;
static char *stickyHelpString = NULL;
static char *mouseHelpString = NULL;
static char *toggleHelpString = NULL;
static char *repeatHelpString = NULL;
static char *slowHelpString = NULL;
static char *bounceHelpString = NULL;

#define ACCESSXHELP_DIRECTORY "/usr/share/X11/locale/"
/* used for debugging.
#define ACCESSXHELP_DIRECTORY "./locale/"
*/
#define HELPDIR "/accessx/"
#define ACCESSXHELP_FILE      "accessx.hlp"
#define COMMENT '-'

/************************************************************************/
/*									*/
/* Constant Declarations						*/
/*									*/
/************************************************************************/

/* WIDGET INDEXING DECLARATIONS */

/* Toggle Widgets */
#define	ENABLE_ACCESSX_TGL	1	
#define	ONOFF_SOUND_TGL		2	
#define	TIME_OUT_TGL		3	

#define	STICKY_KEYS_TGL		4
#define	MOUSE_KEYS_TGL		5
#define	TOGGLE_KEYS_TGL		6
#define	REPEAT_KEYS_TGL		7
#define	SLOW_KEYS_TGL		8	
#define	BOUNCE_KEYS_TGL		9	

#define	STICKY_MOD_SOUND_TGL	10	
#define	STICKY_TWO_KEYS_TGL	11	

#define	KRG_PRESS_SOUND_TGL	12
#define	KRG_ACCEPT_SOUND_TGL	13	

#define MAIN_TOGGLE_WIDGETS_MIN	1
#define MAIN_TOGGLE_WIDGETS_MAX	9

#define SETTINGS_TOGGLE_WIDGETS_MIN 10
#define SETTINGS_TOGGLE_WIDGETS_MAX 13

#define TOGGLE_WIDGETS_MIN	1
#define TOGGLE_WIDGETS_MAX	13

#define NUM_TOGGLE_WIDGETS	14   /* number plus one */

/* Scale Widgets */
#define TIME_OUT_SCL		14

#define	MOUSE_MAX_SPEED_SCL	15	
#define	MOUSE_TIME_TO_MAX_SCL	16
#define MOUSE_DELAY_SCL		17	

#define	KRG_REPEAT_DELAY_SCL	18
#define	KRG_REPEAT_RATE_SCL	19	
#define	KRG_SLOW_DELAY_SCL	20	
#define	KRG_DEBOUNCE_SCL	21	

#define SCALE_WIDGETS_MIN	14
#define SCALE_WIDGETS_MAX	21

/* Main Menu Push Button Items */
#define LOAD_BTN		22
#define SAVE_BTN		23
#define EXIT_BTN		24
#define STICKY_STATUS_BTN	25
#define	MOUSE_STATUS_BTN       	26
#define SETTINGS_BTN		27

#define GENERAL_HELP_BTN	28
#define STICKY_HELP_BTN		29
#define MOUSE_HELP_BTN		30
#define TOGGLE_HELP_BTN		31
#define REPEAT_HELP_BTN		32
#define SLOW_HELP_BTN		33
#define BOUNCE_HELP_BTN		34

/* Help Related Widgets */
#define HELP_TEXT		35
#define CLOSE_HELP_BTN		36

/* Settings Window Related Widgets */
#define SETTINGS_OK_BTN	 	37
#define SETTINGS_RESET_BTN 	38
#define SETTINGS_DEFAULTS_BTN 	39
#define SETTINGS_CANCEL_BTN	40
#define SETTINGS_HELP_BTN	41

/* Sticky Keys Status Widgets */
#define	SHIFT_LATCHED_LBL	42
#define	SHIFT_LOCKED_LBL	43
#define	CONTROL_LATCHED_LBL	44
#define	CONTROL_LOCKED_LBL	45
#define	MOD1_LATCHED_LBL	46
#define	MOD1_LOCKED_LBL		47
#define	MOD2_LATCHED_LBL	48
#define	MOD2_LOCKED_LBL		49
#define	MOD3_LATCHED_LBL	50
#define	MOD3_LOCKED_LBL		51
#define	MOD4_LATCHED_LBL	52
#define	MOD4_LOCKED_LBL		53
#define	MOD5_LATCHED_LBL	54
#define	MOD5_LOCKED_LBL		55
#define STICKY_CLOSE_BTN	56

/* Mouse Keys Status Widgets */
#define	CURRENT_BUTTON_LBL     	57
#define	MB1_PRESSED_LBL	       	58
#define	MB1_RELEASED_LBL       	59
#define	MB2_PRESSED_LBL	       	60
#define	MB2_RELEASED_LBL       	61
#define	MB3_PRESSED_LBL	       	62
#define	MB3_RELEASED_LBL       	63
#define	MB4_PRESSED_LBL	       	64
#define	MB4_RELEASED_LBL       	65
#define	MB5_PRESSED_LBL	       	66
#define	MB5_RELEASED_LBL       	67
#define	MOUSE_CLOSE_BTN      	68

/* Load-Save Dialog Widgets */
#define SAVE_DONE_CANCEL_BTN	69
#define	SAVE_DONE_OK_BTN	70	
#define	SAVE_DONE_HELP_BTN	71

#define SAVE_ERR_CANCEL_BTN	72
#define SAVE_ERR_OK_BTN		73	
#define SAVE_ERR_HELP_BTN	74

#define LOAD_DONE_CANCEL_BTN	75
#define LOAD_DONE_OK_BTN	76
#define LOAD_DONE_HELP_BTN	77

#define LOAD_ERR_CANCEL_BTN	78
#define LOAD_ERR_OK_BTN		79
#define LOAD_ERR_HELP_BTN	80

#define HELP_ERR_CANCEL_BTN	81
#define HELP_ERR_OK_BTN		82
#define HELP_ERR_HELP_BTN	83

/* This Should Reflect Current Designs */
#define NUM_WIDGETS		83	
#define NUM_RES_WIDGETS		25	/* # of widgets which have resources */

/* Application Class String */
#define ACCESSX_CLASS		"AccessX"
#define ACCESSX_FILE		ACCESSX_CLASS

/************************************************************************/
/*									*/
/* Macro Definitions							*/
/*									*/
/************************************************************************/
#define SECSTOMILLIS(x) (int)((float)x * (float)1000)
#define MILLISTOSECS(x) (float)((float)x / (float)1000)


static Widget widgets[NUM_WIDGETS];
char resStrings[NUM_RES_WIDGETS][256] = {
	"",
	"*EnableAccessXToggle.set",
	"*SoundOnOffToggle.set",
	"*TimeOutToggle.set",
	"*StickyKeysToggle.set",
	"*MouseKeysToggle.set",
	"*ToggleKeysToggle.set",
	"*RepeatKeysToggle.set",
	"*SlowKeysToggle.set",
	"*BounceKeysToggle.set",
	"*StickyModSoundToggle.set",
	"*StickyTwoKeysToggle.set",
	"*SlowKeysOnPressToggle.set",
	"*SlowKeysOnAcceptToggle.set",
	"*TimeOutScale",
	"*MouseMaxSpeedScale",
	"*MouseTimeToMaxScale",
	"*KRGRepeatDelayScale",
	"*KRGRepeatRateScale",
	"*KRGSlowKeysDelayScale",
	"*KRGDebounceScale" };

char classStrings[NUM_RES_WIDGETS][80] = {
	"",
	"AccessX*ToggleButtonGadget.XmCSet",
	"AccessX*ToggleButtonGadget.XmCSet",
	"AccessX*ToggleButtonGadget.XmCSet",
	"AccessX*ToggleButtonGadget.XmCSet",
	"AccessX*ToggleButtonGadget.XmCSet",
	"AccessX*ToggleButtonGadget.XmCSet",
	"AccessX*ToggleButtonGadget.XmCSet",
	"AccessX*ToggleButtonGadget.XmCSet",
	"AccessX*ToggleButtonGadget.XmCSet",
	"AccessX*ToggleButtonGadget.XmCSet",
	"AccessX*ToggleButtonGadget.XmCSet",
	"AccessX*ToggleButtonGadget.XmCSet",
	"AccessX*ToggleButtonGadget.XmCSet",
        "AccessX*XmScale",
        "AccessX*XmScale",
        "AccessX*XmScale",
        "AccessX*XmScale",
        "AccessX*XmScale",
        "AccessX*XmScale",
        "AccessX*XmScale" };

int toggleWidgetsMask[NUM_TOGGLE_WIDGETS] = {
	0,
	ALLOW_ACCESSX_MASK,
	STICKY_ONOFF_SOUND_MASK | MOUSE_ONOFF_SOUND_MASK | KRG_ONOFF_SOUND_MASK,
	TIME_OUT_MASK,
	STICKY_KEYS_MASK,
	MOUSE_KEYS_MASK,
	TOGGLE_KEYS_MASK,
	REPEAT_KEYS_MASK,
	SLOW_KEYS_MASK,
	BOUNCE_KEYS_MASK,
	STICKY_MOD_SOUND_MASK,
	TWO_KEYS_MASK,
	KRG_PRESS_SOUND_MASK,
	KRG_ACCEPT_SOUND_MASK };


/************************************************************************/
/*									*/
/* Application Resources						*/
/*									*/
/************************************************************************/
typedef struct 
{
    Boolean     iconifyMain;		/* Start main window iconified	*/
    Boolean     automaticPopup;		/* For Sticky & Mouse status 	*/
    Boolean	useServer;		/* Use server settings		*/
} OptionsRec;

OptionsRec options;

#define Offset(field) XtOffsetOf(OptionsRec,field)
XtResource resources[] = 
{
    {"iconifyMain", "IconifyMain", XtRBoolean, sizeof(Boolean),
     Offset(iconifyMain), "XtRImmediate", (XtPointer)   False},
    {"automaticPopup", "AutomaticPopup", XtRBoolean, sizeof(Boolean),
     Offset(automaticPopup), "XtRImmediate", (XtPointer)   False},
    {"useServer", "UseServer", XtRBoolean, sizeof(Boolean),
     Offset(useServer), XtRImmediate, (XtPointer)      False}
};
#undef Offset

XrmOptionDescRec optionDesc[] = {
    {"-iconic", "*iconifyMain", XrmoptionNoArg, (XtPointer) "true"},
    {"-auto", "*automaticPopup", XrmoptionNoArg, (XtPointer) "true"},
    {"-noauto", "*automaticPopup", XrmoptionNoArg, (XtPointer) "false"},
    {"-server", "*useServer", XrmoptionNoArg, (XtPointer) "true"},
    {"-client", "*useServer", XrmoptionNoArg, (XtPointer) "false"}
};

/* The fallback resources are used to define the default values for
 * interface items such as the range/detail of the scales.
 */
static String fallbackResources[] = {
    "*EnableAccessXToggle.set: True",
    "*SoundOnOffToggle.set: True",
    "*ShowStatusToggle.set: False",
    "*TimeOutToggle.set: False",
    "*TimeOutScale.minimum: 1",
    "*TimeOutScale.maximum: 10",
    "*TimeOutScale.decimalPoints: 0",
    "*TimeOutScale.value: 2",
    "*StickyKeysToggle.set: False",
    "*MouseKeysToggle.set: False",
    "*ToggleKeysToggle.set: False",
    "*RepeatKeysToggle.set: True",
    "*SlowKeysToggle.set: False",
    "*BounceKeysToggle.set: False",
    "*StickyTwoKeysToggle.set: True",
    "*StickyModSoundToggle.set: True",
    "*MouseMaxSpeedScale.minimum: 1",
    "*MouseMaxSpeedScale.maximum: 500",
    "*MouseMaxSpeedScale.decimalPoints: 0",
    "*MouseMaxSpeedScale.value: 300",
    "*MouseAccelScale.minimum: 1",
    "*MouseAccelScale.maximum: 40",
    "*MouseAccelScale.decimalPoints: 1",
    "*MouseAccelScale.value: 20",
    "*MouseDelayScale.minimum: 1",
    "*MouseDelayScale.maximum: 40",
    "*MouseDelayScale.decimalPoints: 1",
    "*MouseDelayScale.value: 3",
    "*KRGRepeatRateScale.minimum: 1",
    "*KRGRepeatRateScale.maximum: 400",
    "*KRGRepeatRateScale.decimalPoints: 2",
    "*KRGRepeatRateScale.value: 5",
    "*KRGRepeatDelayScale.minimum: 1",
    "*KRGRepeatDelayScale.maximum: 400",
    "*KRGRepeatDelayScale.decimalPoints: 2",
    "*KRGRepeatDelayScale.value: 66",
    "*SlowKeysOnPressToggle.set: True",
    "*SlowKeysOnAcceptToggle.set: True",
    "*KRGSlowKeysDelayScale.minimum: 1",
    "*KRGSlowKeysDelayScale.maximum: 40",
    "*KRGSlowKeysDelayScale.decimalPoints: 1",
    "*KRGSlowKeysDelayScale.value: 3",
    "*KRGDebounceScale.minimum: 0",
    "*KRGDebounceScale.maximum: 40",
    "*KRGDebounceScale.decimalPoints: 1",
    "*KRGDebounceScale.value: 3",
    NULL
};


/************************************************************************/
/*									*/
/*  AccessXEventHandler 						*/
/*									*/
/*  DESCRIPTION:							*/
/*									*/
/*      Handle all events generated by the AccessX server extension.	*/
/*									*/
/************************************************************************/
#if NeedFunctionPrototypes
void AccessXEventHandler(XAccessXEvent *event)
#else
void AccessXEventHandler(event)
    XAccessXEvent *event;
#endif
{
    Arg 	argList[2];

    switch (event->detail) {
	case X_AccessXStickyKeysOn:
	    XmToggleButtonSetState(widgets[STICKY_KEYS_TGL],True,False);
            if (options.automaticPopup) {
               CreateAndMapStickyStatusWindow();
            }

	    /*[[[should put a check in for sounds]]]*/
	    break;
	
	case X_AccessXStickyKeysOff:
	    XmToggleButtonSetState(widgets[STICKY_KEYS_TGL],False,False);

            XtSetArg(argList[0], XmNlabelString, shiftEmptyString);
            XtSetValues(widgets[SHIFT_LATCHED_LBL], argList, 1);
            XtSetValues(widgets[SHIFT_LOCKED_LBL], argList, 1);

            XtSetArg(argList[0], XmNlabelString, controlEmptyString);
            XtSetValues(widgets[CONTROL_LATCHED_LBL], argList, 1);
            XtSetValues(widgets[CONTROL_LOCKED_LBL], argList, 1);

            XtSetArg(argList[0], XmNlabelString, mod1EmptyString);
            XtSetValues(widgets[MOD1_LATCHED_LBL], argList, 1);
            XtSetValues(widgets[MOD1_LOCKED_LBL], argList, 1);

            XtSetArg(argList[0], XmNlabelString, mod2EmptyString);
            XtSetValues(widgets[MOD2_LATCHED_LBL], argList, 1);
            XtSetValues(widgets[MOD2_LOCKED_LBL], argList, 1);

            XtSetArg(argList[0], XmNlabelString, mod3EmptyString);
            XtSetValues(widgets[MOD3_LATCHED_LBL], argList, 1);
            XtSetValues(widgets[MOD3_LOCKED_LBL], argList, 1);

            XtSetArg(argList[0], XmNlabelString, mod4EmptyString);
            XtSetValues(widgets[MOD4_LATCHED_LBL], argList, 1);
            XtSetValues(widgets[MOD4_LOCKED_LBL], argList, 1);

            XtSetArg(argList[0], XmNlabelString, mod5EmptyString);
            XtSetValues(widgets[MOD5_LATCHED_LBL], argList, 1);
            XtSetValues(widgets[MOD5_LOCKED_LBL], argList, 1);

            if (options.automaticPopup) {
		UnmapStickyStatusWindow();
            }

	    /*[[[should put a check in for sounds]]]*/
	    break;

	/*[[[MouseKeys On/Off has not been implemented in the server yet]]]*/
	case X_AccessXMouseKeysOn:
	    XmToggleButtonSetState(widgets[MOUSE_KEYS_TGL], True, False);

            if (options.automaticPopup) {
               CreateAndMapMouseStatusWindow();
            }

	    /*[[[should put a check in for sounds]]]*/
	    break;
	
	case X_AccessXMouseKeysOff:
	    XmToggleButtonSetState(widgets[MOUSE_KEYS_TGL],False,False);

            if (options.automaticPopup) {
		UnmapMouseStatusWindow();
            }
	    /*[[[should put a check in for sounds]]]*/
	    break;
	
	case X_AccessXKRGWarning:
	    /*[[[should put a check in for sounds]]]*/
	    break;

	case X_AccessXKRGOn:
	    if (event->control & REPEAT_KEYS_MASK)
		XmToggleButtonSetState(widgets[REPEAT_KEYS_TGL],True,False);
	    if (event->control & SLOW_KEYS_MASK) {
		XmToggleButtonSetState(widgets[SLOW_KEYS_TGL],True,False);
		XmToggleButtonSetState(widgets[BOUNCE_KEYS_TGL],False,False);
	    }
	    if (event->control & BOUNCE_KEYS_MASK) {
		XmToggleButtonSetState(widgets[SLOW_KEYS_TGL],False,False);
		XmToggleButtonSetState(widgets[BOUNCE_KEYS_TGL],True,False);
	    }

	    /*[[[should put a check in for sounds]]]*/
	    break;
	
	case X_AccessXKRGOff:
	    XmToggleButtonSetState(widgets[REPEAT_KEYS_TGL],False,False);	
	    XmToggleButtonSetState(widgets[SLOW_KEYS_TGL],False,False);	
	    XmToggleButtonSetState(widgets[BOUNCE_KEYS_TGL],False,False);	
	    /*[[[should put a check in for sounds]]]*/
	    break;
	
	case X_AccessXToggleKeysOn:
	    XmToggleButtonSetState(widgets[TOGGLE_KEYS_TGL],True,False);
	    break;
	
	case X_AccessXToggleKeysOff:
	    XmToggleButtonSetState(widgets[TOGGLE_KEYS_TGL],False,False);
	    break;
	
	case X_AccessXToggleKeyDown:
	    /*[[[should put a check in for sounds]]]*/
	    break;
	
	case X_AccessXToggleKeyUp:
	    /*[[[should put a check in for sounds]]]*/
	    break;
	
	case X_AccessXModifierLatch:
	    if (event->modifier & ShiftMask) {
		XtSetArg(argList[0],XmNlabelString,shiftString);
		XtSetValues(widgets[SHIFT_LATCHED_LBL],argList,1);
	    }
	    else if (event->modifier & ControlMask) {
		XtSetArg(argList[0],XmNlabelString,controlString);
		XtSetValues(widgets[CONTROL_LATCHED_LBL],argList,1);
	    }
	    else if (event->modifier & Mod1Mask) {
		XtSetArg(argList[0],XmNlabelString,mod1String);
		XtSetValues(widgets[MOD1_LATCHED_LBL],argList,1);
	    }
	    else if (event->modifier & Mod2Mask) {
		XtSetArg(argList[0],XmNlabelString,mod2String);
		XtSetValues(widgets[MOD2_LATCHED_LBL],argList,1);
	    }
	    else if (event->modifier & Mod3Mask) {
		XtSetArg(argList[0],XmNlabelString,mod3String);
		XtSetValues(widgets[MOD3_LATCHED_LBL],argList,1);
	    }
	    else if (event->modifier & Mod4Mask) {
		XtSetArg(argList[0],XmNlabelString,mod4String);
		XtSetValues(widgets[MOD4_LATCHED_LBL],argList,1);
	    }
	    else if (event->modifier & Mod5Mask) {
		XtSetArg(argList[0],XmNlabelString,mod5String);
		XtSetValues(widgets[MOD5_LATCHED_LBL],argList,1);
	    }

	    break;
	
	case X_AccessXModifierUnlatch:
	    if (event->modifier & ShiftMask) {
		XtSetArg(argList[0], XmNlabelString, shiftEmptyString);
		XtSetValues(widgets[SHIFT_LATCHED_LBL], argList, 1);
	    }
	    else if (event->modifier & ControlMask) {
		XtSetArg(argList[0], XmNlabelString, controlEmptyString);
		XtSetValues(widgets[CONTROL_LATCHED_LBL], argList, 1);
	    }
	    else if (event->modifier & Mod1Mask) {
		XtSetArg(argList[0],XmNlabelString,mod1EmptyString);
		XtSetValues(widgets[MOD1_LATCHED_LBL],argList,1);
	    }
	    else if (event->modifier & Mod2Mask) {
		XtSetArg(argList[0],XmNlabelString,mod2EmptyString);
		XtSetValues(widgets[MOD2_LATCHED_LBL],argList,1);
	    }
	    else if (event->modifier & Mod3Mask) {
		XtSetArg(argList[0],XmNlabelString,mod3EmptyString);
		XtSetValues(widgets[MOD3_LATCHED_LBL],argList,1);
	    }
	    else if (event->modifier & Mod4Mask) {
		XtSetArg(argList[0],XmNlabelString,mod4EmptyString);
		XtSetValues(widgets[MOD4_LATCHED_LBL],argList,1);
	    }
	    else if (event->modifier & Mod5Mask) {
		XtSetArg(argList[0],XmNlabelString,mod5EmptyString);
		XtSetValues(widgets[MOD5_LATCHED_LBL],argList,1);
	    }

	    break;
	
	case X_AccessXModifierLock:
	    if (event->modifier & ShiftMask) {
		XtSetArg(argList[0],XmNlabelString,shiftString);
		XtSetValues(widgets[SHIFT_LOCKED_LBL],argList,1);
	    }
	    else if (event->modifier & ControlMask) {
		XtSetArg(argList[0],XmNlabelString,controlString);
		XtSetValues(widgets[CONTROL_LOCKED_LBL],argList,1);
	    }
	    else if (event->modifier & Mod1Mask) {
		XtSetArg(argList[0],XmNlabelString,mod1String);
		XtSetValues(widgets[MOD1_LOCKED_LBL],argList,1);
	    }
	    else if (event->modifier & Mod2Mask) {
		XtSetArg(argList[0],XmNlabelString,mod2String);
		XtSetValues(widgets[MOD2_LOCKED_LBL],argList,1);
	    }
	    else if (event->modifier & Mod3Mask) {
		XtSetArg(argList[0],XmNlabelString,mod3String);
		XtSetValues(widgets[MOD3_LOCKED_LBL],argList,1);
	    }
	    else if (event->modifier & Mod4Mask) {
		XtSetArg(argList[0],XmNlabelString,mod4String);
		XtSetValues(widgets[MOD4_LOCKED_LBL],argList,1);
	    }
	    else if (event->modifier & Mod5Mask) {
		XtSetArg(argList[0],XmNlabelString,mod5String);
		XtSetValues(widgets[MOD5_LOCKED_LBL],argList,1);
	    }

	    break;
	
	case X_AccessXModifierUnlock:
	    if (event->modifier & ShiftMask) {
		XtSetArg(argList[0],XmNlabelString,shiftEmptyString);
		XtSetValues(widgets[SHIFT_LOCKED_LBL],argList,1);
	    }
	    else if (event->modifier & ControlMask) {
		XtSetArg(argList[0],XmNlabelString,controlEmptyString);
		XtSetValues(widgets[CONTROL_LOCKED_LBL],argList,1);
	    }
	    else if (event->modifier & Mod1Mask) {
		XtSetArg(argList[0],XmNlabelString,mod1EmptyString);
		XtSetValues(widgets[MOD1_LOCKED_LBL],argList,1);
	    }
	    else if (event->modifier & Mod2Mask) {
		XtSetArg(argList[0],XmNlabelString,mod2EmptyString);
		XtSetValues(widgets[MOD2_LOCKED_LBL],argList,1);
	    }
	    else if (event->modifier & Mod3Mask) {
		XtSetArg(argList[0],XmNlabelString,mod3EmptyString);
		XtSetValues(widgets[MOD3_LOCKED_LBL],argList,1);
	    }
	    else if (event->modifier & Mod4Mask) {
		XtSetArg(argList[0],XmNlabelString,mod4EmptyString);
		XtSetValues(widgets[MOD4_LOCKED_LBL],argList,1);
	    }
	    else if (event->modifier & Mod5Mask) {
		XtSetArg(argList[0],XmNlabelString,mod5EmptyString);
		XtSetValues(widgets[MOD5_LOCKED_LBL],argList,1);
	    }

	    break;
	
	case X_AccessXPressSlowKey:
	    /*[[[should put a check in for sounds]]]*/
	    break;

	case X_AccessXAcceptSlowKey:
	    /*[[[should put a check in for sounds]]]*/
	    break;

        case X_AccessXChangeCurrentButton:
            XtSetArg(argList[0],"empty" , "");
            XtSetArg(argList[1],"empty" , "");
            switch (event->keyOrButton) {
            case 1:
               XtSetArg(argList[0], XmNlabelString, mb1String);
               break;
            case 2:
               XtSetArg(argList[0], XmNlabelString, mb2String);
               break;
            case 3:
               XtSetArg(argList[0], XmNlabelString, mb3String);
               break;
            case 4:
               XtSetArg(argList[0], XmNlabelString, mb4String);
               break;
            case 5:
               XtSetArg(argList[0], XmNlabelString, mb5String);
               break;
            }
	    if (widgets[CURRENT_BUTTON_LBL]) {
               XtSetValues(widgets[CURRENT_BUTTON_LBL], argList, 1);
            }
            break;

        case X_AccessXPressButton:
            switch (event->keyOrButton) {
            case 1:
              XtSetArg(argList[0], XmNlabelString, mb1String);
              XtSetValues(widgets[MB1_PRESSED_LBL], argList, 1);
              XtSetArg(argList[0], XmNlabelString, mb1EmptyString);
              XtSetValues(widgets[MB1_RELEASED_LBL], argList, 1);
              break;
            case 2:
              XtSetArg(argList[0], XmNlabelString, mb2String);
              XtSetValues(widgets[MB2_PRESSED_LBL], argList, 1);
              XtSetArg(argList[0], XmNlabelString, mb2EmptyString);
              XtSetValues(widgets[MB2_RELEASED_LBL], argList, 1);
              break;
            case 3:
              XtSetArg(argList[0], XmNlabelString, mb3String);
              XtSetValues(widgets[MB3_PRESSED_LBL], argList, 1);
              XtSetArg(argList[0], XmNlabelString, mb3EmptyString);
              XtSetValues(widgets[MB3_RELEASED_LBL], argList, 1);
              break;
#ifdef SHOW_5_BUTTONS_IN_MOUSEKEYS_STATUS
            case 4:
              XtSetArg(argList[0], XmNlabelString, mb4String);
              XtSetValues(widgets[MB4_PRESSED_LBL], argList, 1);
              XtSetArg(argList[0], XmNlabelString, mb4EmptyString);
              XtSetValues(widgets[MB4_RELEASED_LBL], argList, 1);
              break;
            case 5:
              XtSetArg(argList[0], XmNlabelString, mb5String);
              XtSetValues(widgets[MB5_PRESSED_LBL], argList, 1);
              XtSetArg(argList[0], XmNlabelString, mb5EmptyString);
              XtSetValues(widgets[MB5_RELEASED_LBL], argList, 1);
              break;
#endif
            }
            break;

        case X_AccessXReleaseButton:
            XtSetArg(argList[0], XmNshadowType, XmSHADOW_ETCHED_OUT);
            switch (event->keyOrButton) {
            case 1:
              XtSetArg(argList[0], XmNlabelString, mb1String);
              XtSetValues(widgets[MB1_RELEASED_LBL], argList, 1);
              XtSetArg(argList[0], XmNlabelString, mb1EmptyString);
              XtSetValues(widgets[MB1_PRESSED_LBL], argList, 1);
              break;
            case 2:
              XtSetArg(argList[0], XmNlabelString, mb2String);
              XtSetValues(widgets[MB2_RELEASED_LBL], argList, 1);
              XtSetArg(argList[0], XmNlabelString, mb2EmptyString);
              XtSetValues(widgets[MB2_PRESSED_LBL], argList, 1);
              break;
            case 3:
              XtSetArg(argList[0], XmNlabelString, mb3String);
              XtSetValues(widgets[MB3_RELEASED_LBL], argList, 1);
              XtSetArg(argList[0], XmNlabelString, mb3EmptyString);
              XtSetValues(widgets[MB3_PRESSED_LBL], argList, 1);
              break;
#ifdef SHOW_5_BUTTONS_IN_MOUSEKEYS_STATUS
            case 4:
              XtSetArg(argList[0], XmNlabelString, mb4String);
              XtSetValues(widgets[MB4_RELEASED_LBL], argList, 1);
              XtSetArg(argList[0], XmNlabelString, mb4EmptyString);
              XtSetValues(widgets[MB4_PRESSED_LBL], argList, 1);
              break;
            case 5:
              XtSetArg(argList[0], XmNlabelString, mb5String);
              XtSetValues(widgets[MB5_RELEASED_LBL], argList, 1);
              XtSetArg(argList[0], XmNlabelString, mb5EmptyString);
              XtSetValues(widgets[MB5_PRESSED_LBL], argList, 1);
              break;
#endif
            }
	    break;

	case X_AccessXChangeGain:
	{
	    break;
	}
    }
} /* AccessXEventHandler */

/************************************************************************/
/*                                                                      */
/* ConvertScaleValueToUnits                                             */
/*                                                                      */
/*	Take a scale reading and a decimal point reading and returns    */
/* 	a floating point number which is the value the scale really     */
/*	represents. The purpose of this function is to easily convert   */
/*	between both representations independent of what the value      */
/*	actually represents.                                            */
/*                                                                      */
/************************************************************************/
#if NeedFunctionPrototypes
float ConvertScaleValueToUnits(int value, short decimalPoints)
#else
float ConvertScaleValueToUnits(value, decimalPoints)
     int value;
     short decimalPoints;
#endif
{
  int i, j;

  j = 1;
  for (i = 0; i < decimalPoints; i++) {
    j *= 10;
  }

  return ((float)value / (float)j);
}

/************************************************************************/
/*                                                                      */
/* ConvertUnitsToScaleValue                                             */
/*                                                                      */
/*	Take a floating point value and a decimal points reading and    */
/*	returns an adjusted integer value which may be used as a value  */
/*      for a scale widget. The purpose of this function is to easily   */
/*      convert between both representation independent of what the     */
/*      value actually represents.                                      */
/*                                                                      */
/************************************************************************/
#if NeedFunctionPrototypes
int ConvertUnitsToScaleValue(float value, short decimalPoints)
#else
int ConvertUnitsToScaleValue(value, decimalPoints)
     float value;
     short decimalPoints;
#endif
{
  int i, j;

  j = 1;
  for (i = 0; i < decimalPoints; i++) {
    j *= 10;
  }
  return ((int)(value * (float)j));
}

/************************************************************************/
/*									*/
/* SetStateFromView							*/
/*									*/
/*	Sets the state of the extension according to the state of the	*/
/*	widgets in the interface.					*/
/*									*/
/************************************************************************/
#if NeedFunctionPrototypes
void SetStateFromView(void)
#else
void SetStateFromView()
#endif
{
    if(XKBExtension)
	SetStateFromViewXKB();
    else
	SetStateFromViewAX();
} /* SetStateFromView */


#if NeedFunctionPrototypes
void SetStateFromViewXKB(void)
#else
void SetStateFromViewXKB()
#endif
{
    unsigned  long	which;
    CARD32 		enabled,changeEnabled;
    XkbDescRec 		*desc;
    Arg 		argList[2];
    int 		scaleValue;
    short 		decimalPoints;
    
    which = XkbAccessXKeysMask | XkbAccessXTimeoutMask |
	    XkbControlsEnabledMask |
	    XkbMouseKeysAccelMask |
	    XkbRepeatKeysMask | XkbSlowKeysMask | XkbBounceKeysMask;

    changeEnabled = XkbAccessXKeysMask |
	            XkbAccessXFeedbackMask |
	            XkbStickyKeysMask | XkbMouseKeysMask | 
		    XkbRepeatKeysMask | XkbSlowKeysMask | XkbBounceKeysMask;

    enabled = XkbAccessXFeedbackMask;
    
    desc = XkbGetMap(dpy,0,XkbUseCoreKbd);
    XkbGetControls(dpy,XkbAllControlsMask,desc);

    desc->ctrls->ax_options = XkbAX_LatchToLockMask;
    
    /********************************************************************/
    /*									*/
    /* Global values:  Enable AccessX, Beep on Feature Use, TimeOut	*/
    /*							 		*/
    /********************************************************************/
    if (XmToggleButtonGadgetGetState(widgets[ENABLE_ACCESSX_TGL]))
	enabled |= XkbAccessXKeysMask;

    if (XmToggleButtonGadgetGetState(widgets[ONOFF_SOUND_TGL]))
	desc->ctrls->ax_options |= XkbAX_FeatureFBMask | XkbAX_SlowWarnFBMask;
    
    if (XmToggleButtonGadgetGetState(widgets[TIME_OUT_TGL]))
    {
	XtSetArg(argList[0], XmNsensitive, True);
	XtSetValues(widgets[TIME_OUT_SCL],argList,1);
	enabled |= XkbAccessXTimeoutMask;
    }	    
    else
    {
	XtSetArg(argList[0], XmNsensitive, False);
	XtSetValues(widgets[TIME_OUT_SCL],argList,1);	
    }
    
    XtSetArg(argList[0],XmNvalue,&scaleValue);
    XtSetArg(argList[1],XmNdecimalPoints,&decimalPoints);
    XtGetValues(widgets[TIME_OUT_SCL],argList,2);
    desc->ctrls->ax_timeout = 60 * ConvertScaleValueToUnits(scaleValue,
							    decimalPoints);

    if(desc->ctrls->ax_timeout <= 0) desc->ctrls->ax_timeout = 1;
    /********************************************************************/
    /*									*/
    /* Keyboard Control: StickyKeys, MouseKeys, ToggleKeys		*/
    /*							 		*/
    /********************************************************************/
    if (XmToggleButtonGadgetGetState(widgets[STICKY_KEYS_TGL]))
    {
	enabled |= XkbStickyKeysMask;
    }
    
    if (XmToggleButtonGadgetGetState(widgets[MOUSE_KEYS_TGL]))
    {
	enabled |= XkbMouseKeysMask;
    }
    
    if (XmToggleButtonGadgetGetState(widgets[TOGGLE_KEYS_TGL]))
	desc->ctrls->ax_options |= XkbAX_IndicatorFBMask;
    
    /********************************************************************/
    /*									*/
    /* Keyboard Response: RepeatKeys, SlowKeys, BounceKeys		*/
    /*							 		*/
    /********************************************************************/
    if (XmToggleButtonGadgetGetState(widgets[REPEAT_KEYS_TGL]))
	enabled |= XkbRepeatKeysMask;

    if (XmToggleButtonGadgetGetState(widgets[SLOW_KEYS_TGL]))
	enabled |= XkbSlowKeysMask;

    if (XmToggleButtonGadgetGetState(widgets[BOUNCE_KEYS_TGL]))
	enabled |= XkbBounceKeysMask;

    /********************************************************************/
    /*									*/
    /* StickyKeys Settings:  Auto Off, Modifiers Beep			*/
    /*							 		*/
    /********************************************************************/
    if (XmToggleButtonGadgetGetState(widgets[STICKY_TWO_KEYS_TGL]))
	desc->ctrls->ax_options |= XkbAX_TwoKeysMask;
    
    if (XmToggleButtonGadgetGetState(widgets[STICKY_MOD_SOUND_TGL]))
	desc->ctrls->ax_options |= XkbAX_StickyKeysFBMask;
        
    /********************************************************************/
    /*									*/
    /* MouseKeys Settings:  Speed Delay, Max Speed			*/
    /*							 		*/
    /********************************************************************/
    desc->ctrls->mk_interval = 10;
    desc->ctrls->mk_curve = 50;

    XtSetArg(argList[0],XmNvalue,&scaleValue);
    XtSetArg(argList[1],XmNdecimalPoints,&decimalPoints);
    XtGetValues(widgets[MOUSE_MAX_SPEED_SCL],argList,2);
    desc->ctrls->mk_max_speed = 
	ConvertScaleValueToUnits(scaleValue,decimalPoints);
    if(desc->ctrls->mk_max_speed <=0 ) desc->ctrls->mk_max_speed = 1;
    
    XtSetArg(argList[0],XmNvalue,&scaleValue);
    XtSetArg(argList[1],XmNdecimalPoints,&decimalPoints);
    XtGetValues(widgets[MOUSE_TIME_TO_MAX_SCL],argList,2);
    desc->ctrls->mk_time_to_max = 
	SECSTOMILLIS(ConvertScaleValueToUnits(scaleValue,decimalPoints));
    if(desc->ctrls->mk_time_to_max <= 0) desc->ctrls->mk_time_to_max = 1;
    
    XtSetArg(argList[0],XmNvalue,&scaleValue);
    XtSetArg(argList[1],XmNdecimalPoints,&decimalPoints);
    XtGetValues(widgets[MOUSE_DELAY_SCL],argList,2);
    desc->ctrls->mk_delay = 
	SECSTOMILLIS(ConvertScaleValueToUnits(scaleValue,decimalPoints));
    if(desc->ctrls->mk_delay <= 0) desc->ctrls->mk_delay = 1;
    
    /********************************************************************/
    /*									*/
    /* RepeatKeys Settings:  Delay, Rate				*/
    /*							 		*/
    /********************************************************************/
    XtSetArg(argList[0],XmNvalue,&scaleValue);
    XtSetArg(argList[1],XmNdecimalPoints,&decimalPoints);
    XtGetValues(widgets[KRG_REPEAT_RATE_SCL],argList,2);
    desc->ctrls->repeat_interval = 
	SECSTOMILLIS((float)1.0 / (float)ConvertScaleValueToUnits(scaleValue,decimalPoints));
    if(desc->ctrls->repeat_interval <= 0) desc->ctrls->repeat_interval = 1;

    XtSetArg(argList[0],XmNvalue,&scaleValue);
    XtSetArg(argList[1],XmNdecimalPoints,&decimalPoints);
    XtGetValues(widgets[KRG_REPEAT_DELAY_SCL],argList,2);
    desc->ctrls->repeat_delay = 
	SECSTOMILLIS(ConvertScaleValueToUnits(scaleValue,decimalPoints));
    if(desc->ctrls->repeat_delay <= 0) desc->ctrls->repeat_delay = 1;

    /********************************************************************/
    /*									*/
    /* SlowKeys Settings:  Beep On Press, Beep on Accept, Delay		*/
    /*							 		*/
    /********************************************************************/
    if (XmToggleButtonGadgetGetState(widgets[KRG_PRESS_SOUND_TGL]))
	desc->ctrls->ax_options |= XkbAX_SKPressFBMask;

    if (XmToggleButtonGadgetGetState(widgets[KRG_ACCEPT_SOUND_TGL]))
	desc->ctrls->ax_options |= XkbAX_SKAcceptFBMask;

    XtSetArg(argList[0],XmNvalue,&scaleValue);
    XtSetArg(argList[1],XmNdecimalPoints,&decimalPoints);
    XtGetValues(widgets[KRG_SLOW_DELAY_SCL],argList,2);
    desc->ctrls->slow_keys_delay = 
	SECSTOMILLIS(ConvertScaleValueToUnits(scaleValue,decimalPoints));
    if(desc->ctrls->slow_keys_delay <= 0) desc->ctrls->slow_keys_delay = 1;

    /********************************************************************/
    /*									*/
    /* BounceKeys Settings:  Delay					*/
    /*							 		*/
    /********************************************************************/
    XtSetArg(argList[0],XmNvalue,&scaleValue);
    XtSetArg(argList[1],XmNdecimalPoints,&decimalPoints);
    XtGetValues(widgets[KRG_DEBOUNCE_SCL],argList,2);
    desc->ctrls->debounce_delay = 
	SECSTOMILLIS(ConvertScaleValueToUnits(scaleValue,decimalPoints));
    if(desc->ctrls->debounce_delay <= 0) desc->ctrls->debounce_delay = 1;

    /********************************************************************/
    /*									*/
    /* Set the values.							*/
    /*									*/
    /********************************************************************/
    desc->ctrls->enabled_ctrls &= ~changeEnabled;
    desc->ctrls->enabled_ctrls |= (changeEnabled & enabled);
    XkbSetControls(dpy,which,desc);

    UpdateWidgetSensitivity();
} /* SetStateFromViewXKB */


#if NeedFunctionPrototypes
void SetStateFromViewAX(void)
#else
void SetStateFromViewAX()
#endif
{
    int i;
    AccessXStateRec req;
    CARD16 mask;
    
    Arg argList[2];
    int scaleValue;
    short decimalPoints;

    mask = SET_CONTROL_MASK;	
    req.control = 0;

    for (i = TOGGLE_WIDGETS_MIN; i <= TOGGLE_WIDGETS_MAX; i++) {
        if (XmToggleButtonGadgetGetState(widgets[i])) {
          req.control |= toggleWidgetsMask[i];
        }
    }

    XtSetArg(argList[0],XmNvalue,&scaleValue);
    XtSetArg(argList[1],XmNdecimalPoints,&decimalPoints);
    XtGetValues(widgets[TIME_OUT_SCL],argList,2);

    /* Do a special case for the Time Out toggle */
    req.control |= TIME_OUT_MASK;
    mask |= SET_TIME_OUT_INTERVAL_MASK;

    if (XmToggleButtonGadgetGetState(widgets[TIME_OUT_TGL])) {
	/* The scale reads "minutes" and we want to give the extension 
	 * A timeout value in seconds.
	 */
	req.timeOutInterval = 60 *  
           ConvertScaleValueToUnits(scaleValue,decimalPoints);

	XtSetArg(argList[0], XmNsensitive, True);
	XtSetValues(widgets[TIME_OUT_SCL],argList,1);
    }
    else {
	req.timeOutInterval = 0;

	XtSetArg(argList[0], XmNsensitive, False);
	XtSetValues(widgets[TIME_OUT_SCL],argList,1);
    }

    /* The only thing we want to do a GetValues on are the scale widgets,
     * so we only need to set the argument list up once.
     */
    XtSetArg(argList[0],XmNvalue,&scaleValue);
    XtSetArg(argList[1],XmNdecimalPoints,&decimalPoints);

    /* The scale reads "seconds" and we want to give the extension a
     * value in milliseconds.
     */
    XtGetValues(widgets[KRG_REPEAT_DELAY_SCL],argList,2);
    mask |= SET_REPEAT_DELAY_MASK;
    req.repeatKeysDelay = SECSTOMILLIS(
          ConvertScaleValueToUnits(scaleValue,decimalPoints));
    
    /* The scale reads "keys/second" and we want to give the extension a
     * value in milliseconds/key.
     */
    XtGetValues(widgets[KRG_REPEAT_RATE_SCL],argList,2);
    mask |= SET_REPEAT_RATE_MASK;
    req.repeatKeysRate = SECSTOMILLIS((float)1.0 /
       (float)ConvertScaleValueToUnits(scaleValue, decimalPoints));
    
    /* The scale reads "seconds" and we want to give the extension a
     * value in milliseconds.
     */
    XtGetValues(widgets[KRG_SLOW_DELAY_SCL],argList,2);
    mask |= SET_SLOW_KEYS_DELAY_MASK;
    req.slowKeysDelay = SECSTOMILLIS(
       ConvertScaleValueToUnits(scaleValue, decimalPoints));
    
    /* The scale reads "seconds" and we want to give the extension a
     * value in milliseconds.
     */
    XtGetValues(widgets[KRG_DEBOUNCE_SCL],argList,2);
    mask |= SET_DEBOUNCE_DELAY_MASK;
    req.debounceDelay = SECSTOMILLIS(
       ConvertScaleValueToUnits(scaleValue,decimalPoints));    

    /* The scale reads "seconds" and we want to give the extension a
     * value in seconds.
     */
    XtGetValues(widgets[MOUSE_TIME_TO_MAX_SCL],argList,2);
    mask |= SET_MOUSE_KEYS_TIME_TO_MAX_MASK;
    req.mouseKeysTimeToMax = ConvertScaleValueToUnits(scaleValue,decimalPoints);

    /* The scale reads "pixels/sec" and we want to give the extension a
     * value in milliseconds/pixel.
     */
    XtGetValues(widgets[MOUSE_MAX_SPEED_SCL],argList,2);
    mask |= SET_MOUSE_KEYS_INTERVAL_MASK;
    req.mouseKeysInterval = (int)SECSTOMILLIS(1.0 /  
         (float)ConvertScaleValueToUnits(scaleValue, decimalPoints)); 

    XAccessXConfigure(dpy, &accessXClient, mask, &req);
    UpdateWidgetSensitivity();

} /* SetStateFromViewAX */

/************************************************************************/
/*									*/
/*  SetDefaults								*/
/*									*/
/*       Sets the state of the extension to the below values		*/
/*									*/
/************************************************************************/
#if NeedFunctionPrototypes
void SetDefaults(void)
#else 
void SetDefaults()
#endif
{
    if(XKBExtension)
	SetDefaultsXKB();
    else
	SetDefaultsAX();
} /* SetDefaults */

#if NeedFunctionPrototypes
void SetDefaultsXKB(void)
#else 
void SetDefaultsXKB()
#endif
{
    unsigned long	which;
    XkbDescRec 		*desc;
    
    desc = XkbGetMap(dpy,0,XkbUseCoreKbd);
    XkbGetControls(dpy,XkbAllControlsMask,desc);

    which = XkbAccessXKeysMask | XkbMouseKeysAccelMask | XkbRepeatKeysMask | 
            XkbSlowKeysMask | XkbBounceKeysMask;

    desc->ctrls->ax_options |= XkbAX_TwoKeysMask|XkbAX_StickyKeysFBMask|
	                       XkbAX_SKPressFBMask|XkbAX_SKAcceptFBMask;

    desc->ctrls->mk_interval = 10;
    desc->ctrls->mk_curve = 50;
    desc->ctrls->mk_max_speed = 300;
    desc->ctrls->mk_time_to_max = 2000;
    desc->ctrls->mk_delay = 300;
    desc->ctrls->repeat_interval = 40;
    desc->ctrls->repeat_delay = 660;
    desc->ctrls->slow_keys_delay = 300;
    desc->ctrls->debounce_delay = 300;
    XkbSetControls(dpy,which,desc);
} /* SetDefaultsXKB */

#if NeedFunctionPrototypes
void SetDefaultsAX(void)
#else 
void SetDefaultsAX()
#endif
{
   int i;
   short decimalPoints;
   Arg argList[2];
   

   /* We don't want to do it for TIME_OUT_TGL, but that's OK */
   for (i = MAIN_TOGGLE_WIDGETS_MIN; i <= MAIN_TOGGLE_WIDGETS_MAX; i++) {
        XmToggleButtonSetState(widgets[i], False, False);
	XtSetArg(argList[0], XmNsensitive, False);
	XtSetValues(widgets[TIME_OUT_SCL],argList,1);
   }
   XmToggleButtonSetState(widgets[ENABLE_ACCESSX_TGL], True, False);
   /*XmToggleButtonSetState(widgets[TIME_OUT_TGL], False, False);*/


   for (i = SETTINGS_TOGGLE_WIDGETS_MIN; i<=SETTINGS_TOGGLE_WIDGETS_MAX; i++)
        XmToggleButtonSetState(widgets[i], False, False);

   /* The scale reads pixels per movement. */
   XtSetArg(argList[0],XmNdecimalPoints,&decimalPoints);

   /* The scale reads "seconds" and the extension gives us time in seconds. */
   XtGetValues(widgets[MOUSE_TIME_TO_MAX_SCL],argList,1);
   XmScaleSetValue(widgets[MOUSE_TIME_TO_MAX_SCL], 2);

   /* The scale reads "pixels/sec" but the extension gives us time
      in milliseconds/pixel. */
   XtGetValues(widgets[MOUSE_MAX_SPEED_SCL],argList,1);
   XmScaleSetValue(widgets[MOUSE_MAX_SPEED_SCL], 300); 

   /* The scale reads "seconds" but the extension gives us time
    * in milliseconds. */
   XtGetValues(widgets[KRG_REPEAT_DELAY_SCL],argList,1);
   XmScaleSetValue(widgets[KRG_REPEAT_DELAY_SCL], 6.6);

   /* The scale reads "keys/second" but the extension gives us time
    * in milliseconds/key. */
   XtGetValues(widgets[KRG_REPEAT_RATE_SCL],argList,1);
   XmScaleSetValue(widgets[KRG_REPEAT_RATE_SCL], 90);

   /* The scale reads "seconds" but the extension gives us time
    * in milliseconds. */
   XtGetValues(widgets[KRG_SLOW_DELAY_SCL],argList,1);
   XmScaleSetValue(widgets[KRG_SLOW_DELAY_SCL], 3);

   /* The scale reads "seconds" but the extension gives us time
    * in milliseconds. */
   XtGetValues(widgets[KRG_DEBOUNCE_SCL],argList,1);
   XmScaleSetValue(widgets[KRG_DEBOUNCE_SCL], 3);

   SetStateFromView();
   UpdateWidgetSensitivity();

} /* SetDefaultsAX */

/************************************************************************/
/*									*/
/* SetViewFromState							*/
/*									*/
/*	Sets the user interface state from the state of the extension.	*/
/*									*/
/************************************************************************/
#if NeedFunctionPrototypes
void SetViewFromState(void)
#else 
void SetViewFromState()
#endif
{
    if(XKBExtension)
	SetViewFromStateXKB();
    else
	SetViewFromStateAX();
}

#if NeedFunctionPrototypes
void SetViewFromStateXKB(void)
#else 
void SetViewFromStateXKB()
#endif
{
    XkbDescRec 	*desc;
    int minimum,maximum,scaleVal;
    short decimalPoints;
    Arg argList[3];

    desc = XkbGetMap(dpy,0,XkbUseCoreKbd);
    XkbGetControls(dpy,XkbAllControlsMask,desc);

    /********************************************************************/
    /*									*/
    /* Global values:  Enable AccessX, Beep on Feature Use, TimeOut	*/
    /*							 		*/
    /********************************************************************/
    if (desc->ctrls->enabled_ctrls&XkbAccessXKeysMask)
	XmToggleButtonSetState(widgets[ENABLE_ACCESSX_TGL], True, False);
    else
	XmToggleButtonSetState(widgets[ENABLE_ACCESSX_TGL], False, False);

    if (XkbAX_NeedFeedback(desc->ctrls,XkbAX_FeatureFBMask))
	XmToggleButtonSetState(widgets[ONOFF_SOUND_TGL], True, False);
    else
	XmToggleButtonSetState(widgets[ONOFF_SOUND_TGL], False, False);

    if (desc->ctrls->enabled_ctrls&XkbAccessXTimeoutMask)
    {
	XtSetArg(argList[0], XmNsensitive, True);
	XtSetValues(widgets[TIME_OUT_SCL],argList,1);	
	XmToggleButtonSetState(widgets[TIME_OUT_TGL], True, False);
    }
    else
    {
	XtSetArg(argList[0], XmNsensitive, False);
	XtSetValues(widgets[TIME_OUT_SCL],argList,1);	
	XmToggleButtonSetState(widgets[TIME_OUT_TGL], False, False);
    }
    
    XtSetArg(argList[0], XmNdecimalPoints,&decimalPoints);
    XtSetArg(argList[1], XmNminimum, &minimum);
    XtSetArg(argList[2], XmNmaximum, &maximum);
    XtGetValues(widgets[TIME_OUT_SCL],argList,3);
    scaleVal = ConvertUnitsToScaleValue(desc->ctrls->ax_timeout/60, 
					decimalPoints);

    if (scaleVal > maximum)
    {
	XtSetArg(argList[0], XmNmaximum, scaleVal);
	XtSetValues(widgets[TIME_OUT_SCL],argList,1);
    }
    else if (scaleVal < minimum)
    {
	XtSetArg(argList[0], XmNminimum, scaleVal);
	XtSetValues(widgets[TIME_OUT_SCL],argList,1);
    }
    XmScaleSetValue(widgets[TIME_OUT_SCL],scaleVal);
    
    /********************************************************************/
    /*									*/
    /* Keyboard Control: StickyKeys, MouseKeys, ToggleKeys		*/
    /*							 		*/
    /********************************************************************/
    if (desc->ctrls->enabled_ctrls&XkbStickyKeysMask)
	XmToggleButtonSetState(widgets[STICKY_KEYS_TGL], True, False);
    else
	XmToggleButtonSetState(widgets[STICKY_KEYS_TGL], False, False);
    
    if (desc->ctrls->enabled_ctrls&XkbMouseKeysMask)
	XmToggleButtonSetState(widgets[MOUSE_KEYS_TGL], True, False);
    else
	XmToggleButtonSetState(widgets[MOUSE_KEYS_TGL], False, False);

    if (XkbAX_NeedFeedback(desc->ctrls,XkbAX_IndicatorFBMask))
	XmToggleButtonSetState(widgets[TOGGLE_KEYS_TGL], True, False);
    else
	XmToggleButtonSetState(widgets[TOGGLE_KEYS_TGL], False, False);
    
    /********************************************************************/
    /*									*/
    /* Keyboard Response: RepeatKeys, SlowKeys, BounceKeys		*/
    /*							 		*/
    /********************************************************************/
    if (desc->ctrls->enabled_ctrls&XkbRepeatKeysMask)
	XmToggleButtonSetState(widgets[REPEAT_KEYS_TGL], True, False);
    else
	XmToggleButtonSetState(widgets[REPEAT_KEYS_TGL], False, False);
    
    if (desc->ctrls->enabled_ctrls&XkbSlowKeysMask)
	XmToggleButtonSetState(widgets[SLOW_KEYS_TGL], True, False);
    else
	XmToggleButtonSetState(widgets[SLOW_KEYS_TGL], False, False);
    
    if (desc->ctrls->enabled_ctrls&XkbBounceKeysMask)
	XmToggleButtonSetState(widgets[BOUNCE_KEYS_TGL], True, False);
    else
	XmToggleButtonSetState(widgets[BOUNCE_KEYS_TGL], False, False);

    /********************************************************************/
    /*									*/
    /* StickyKeys Settings:  Auto Off, Modifiers Beep			*/
    /*							 		*/
    /********************************************************************/
    if (XkbAX_NeedOption(desc->ctrls,XkbAX_TwoKeysMask))
	XmToggleButtonSetState(widgets[STICKY_TWO_KEYS_TGL], True, False);
    else
	XmToggleButtonSetState(widgets[STICKY_TWO_KEYS_TGL], False, False);
    
    if (XkbAX_NeedFeedback(desc->ctrls,XkbAX_StickyKeysFBMask))
	XmToggleButtonSetState(widgets[STICKY_MOD_SOUND_TGL], True, False);
    else
	XmToggleButtonSetState(widgets[STICKY_MOD_SOUND_TGL], False, False);
        
    /********************************************************************/
    /*									*/
    /* MouseKeys Settings:  Max Speed, Acceleration, Delay		*/
    /*							 		*/
    /********************************************************************/
    XtSetArg(argList[0], XmNdecimalPoints,&decimalPoints);
    XtSetArg(argList[1], XmNminimum, &minimum);
    XtSetArg(argList[2], XmNmaximum, &maximum);
    XtGetValues(widgets[MOUSE_MAX_SPEED_SCL],argList,3);
    scaleVal = ConvertUnitsToScaleValue(desc->ctrls->mk_max_speed,
					decimalPoints);

    if (scaleVal > maximum)
    {
	XtSetArg(argList[0], XmNmaximum, scaleVal);
	XtSetValues(widgets[MOUSE_MAX_SPEED_SCL],argList,1);
    }
    else if (scaleVal < minimum)
    {
	XtSetArg(argList[0], XmNminimum, scaleVal);
	XtSetValues(widgets[MOUSE_MAX_SPEED_SCL],argList,1);
    }
    XmScaleSetValue(widgets[MOUSE_MAX_SPEED_SCL],scaleVal);

    XtSetArg(argList[0], XmNdecimalPoints,&decimalPoints);
    XtSetArg(argList[1], XmNminimum, &minimum);
    XtSetArg(argList[2], XmNmaximum, &maximum);
    XtGetValues(widgets[MOUSE_TIME_TO_MAX_SCL],argList,3);
    scaleVal = ConvertUnitsToScaleValue(MILLISTOSECS(desc->ctrls->mk_time_to_max),
					decimalPoints);

    if (scaleVal > maximum)
    {
	XtSetArg(argList[0], XmNmaximum, scaleVal);
	XtSetValues(widgets[MOUSE_TIME_TO_MAX_SCL],argList,1);
    }
    else if (scaleVal < minimum)
    {
	XtSetArg(argList[0], XmNminimum, scaleVal);
	XtSetValues(widgets[MOUSE_TIME_TO_MAX_SCL],argList,1);
    }
    XmScaleSetValue(widgets[MOUSE_TIME_TO_MAX_SCL],scaleVal);

    XtSetArg(argList[0], XmNdecimalPoints,&decimalPoints);
    XtSetArg(argList[1], XmNminimum, &minimum);
    XtSetArg(argList[2], XmNmaximum, &maximum);
    XtGetValues(widgets[MOUSE_DELAY_SCL],argList,3);
    scaleVal = ConvertUnitsToScaleValue(MILLISTOSECS(desc->ctrls->mk_delay),
					decimalPoints);

    if (scaleVal > maximum)
    {
	XtSetArg(argList[0], XmNmaximum, scaleVal);
	XtSetValues(widgets[MOUSE_DELAY_SCL],argList,1);
    }
    else if (scaleVal < minimum)
    {
	XtSetArg(argList[0], XmNminimum, scaleVal);
	XtSetValues(widgets[MOUSE_DELAY_SCL],argList,1);
    }
    XmScaleSetValue(widgets[MOUSE_DELAY_SCL],scaleVal);

    /********************************************************************/
    /*									*/
    /* RepeatKeys Settings:  Delay, Rate				*/
    /*							 		*/
    /********************************************************************/
    XtSetArg(argList[0], XmNdecimalPoints,&decimalPoints);
    XtSetArg(argList[1], XmNminimum, &minimum);
    XtSetArg(argList[2], XmNmaximum, &maximum);
    XtGetValues(widgets[KRG_REPEAT_RATE_SCL],argList,3);
    scaleVal = ConvertUnitsToScaleValue(((float)1.0 / (float)MILLISTOSECS(desc->ctrls->repeat_interval)), 
					decimalPoints);

    if (scaleVal > maximum)
    {
	XtSetArg(argList[0], XmNmaximum, scaleVal);
	XtSetValues(widgets[KRG_REPEAT_RATE_SCL],argList,1);
    }
    else if (scaleVal < minimum)
    {
	XtSetArg(argList[0], XmNminimum, scaleVal);
	XtSetValues(widgets[KRG_REPEAT_RATE_SCL],argList,1);
    }
    XmScaleSetValue(widgets[KRG_REPEAT_RATE_SCL],scaleVal);

    XtSetArg(argList[0], XmNdecimalPoints,&decimalPoints);
    XtSetArg(argList[1], XmNminimum, &minimum);
    XtSetArg(argList[2], XmNmaximum, &maximum);
    XtGetValues(widgets[KRG_REPEAT_DELAY_SCL],argList,3);
    scaleVal = ConvertUnitsToScaleValue(MILLISTOSECS(desc->ctrls->repeat_delay), 
					decimalPoints);

    if (scaleVal > maximum)
    {
	XtSetArg(argList[0], XmNmaximum, scaleVal);
	XtSetValues(widgets[KRG_REPEAT_DELAY_SCL],argList,1);
    }
    else if (scaleVal < minimum)
    {
	XtSetArg(argList[0], XmNminimum, scaleVal);
	XtSetValues(widgets[KRG_REPEAT_DELAY_SCL],argList,1);
    }
    XmScaleSetValue(widgets[KRG_REPEAT_DELAY_SCL],scaleVal);

    /********************************************************************/
    /*									*/
    /* SlowKeys Settings:  Beep On Press, Beep on Accept, Delay		*/
    /*							 		*/
    /********************************************************************/
    if (XkbAX_NeedFeedback(desc->ctrls,XkbAX_SKPressFBMask))
	XmToggleButtonSetState(widgets[KRG_PRESS_SOUND_TGL], True, False);
    else
	XmToggleButtonSetState(widgets[KRG_PRESS_SOUND_TGL], False, False);

    if (XkbAX_NeedFeedback(desc->ctrls,XkbAX_SKAcceptFBMask))
	XmToggleButtonSetState(widgets[KRG_ACCEPT_SOUND_TGL], True, False);
    else
	XmToggleButtonSetState(widgets[KRG_ACCEPT_SOUND_TGL], False, False);

    XtSetArg(argList[0], XmNdecimalPoints,&decimalPoints);
    XtSetArg(argList[1], XmNminimum, &minimum);
    XtSetArg(argList[2], XmNmaximum, &maximum);
    XtGetValues(widgets[KRG_SLOW_DELAY_SCL],argList,3);
    scaleVal = ConvertUnitsToScaleValue(MILLISTOSECS(desc->ctrls->slow_keys_delay), 
					decimalPoints);

    if (scaleVal > maximum)
    {
	XtSetArg(argList[0], XmNmaximum, scaleVal);
	XtSetValues(widgets[KRG_SLOW_DELAY_SCL],argList,1);
    }
    else if (scaleVal < minimum)
    {
	XtSetArg(argList[0], XmNminimum, scaleVal);
	XtSetValues(widgets[KRG_SLOW_DELAY_SCL],argList,1);
    }
    XmScaleSetValue(widgets[KRG_SLOW_DELAY_SCL],scaleVal);
    
    /********************************************************************/
    /*									*/
    /* BounceKeys Settings:  Delay					*/
    /*							 		*/
    /********************************************************************/
    XtSetArg(argList[0], XmNdecimalPoints,&decimalPoints);
    XtSetArg(argList[1], XmNminimum, &minimum);
    XtSetArg(argList[2], XmNmaximum, &maximum);
    XtGetValues(widgets[KRG_DEBOUNCE_SCL],argList,3);
    scaleVal = ConvertUnitsToScaleValue(MILLISTOSECS(desc->ctrls->debounce_delay), 
					decimalPoints);

    if (scaleVal > maximum)
    {
	XtSetArg(argList[0], XmNmaximum, scaleVal);
	XtSetValues(widgets[KRG_DEBOUNCE_SCL],argList,1);
    }
    else if (scaleVal < minimum)
    {
	XtSetArg(argList[0], XmNminimum, scaleVal);
	XtSetValues(widgets[KRG_DEBOUNCE_SCL],argList,1);
    }
    XmScaleSetValue(widgets[KRG_DEBOUNCE_SCL],scaleVal);

    UpdateWidgetSensitivity();
}

#if NeedFunctionPrototypes
void SetViewFromStateAX(void)
#else 
void SetViewFromStateAX()
#endif
{
   int i, minimum;
   short decimalPoints;
   Arg argList[2];
   AccessXStateRec state;
   
   XAccessXQueryState(dpy, &accessXClient, &state);

   /* We don't want to do it for TIME_OUT_TGL, but that's OK */
   for (i = MAIN_TOGGLE_WIDGETS_MIN; i <= MAIN_TOGGLE_WIDGETS_MAX; i++) {
      if (state.control & toggleWidgetsMask[i]) {
	XmToggleButtonSetState(widgets[i], True, False);
	XtSetArg(argList[0], XmNsensitive, True);
	XtSetValues(widgets[TIME_OUT_SCL],argList,1);
      }
      else {
        XmToggleButtonSetState(widgets[i], False, False);
	XtSetArg(argList[0], XmNsensitive, False);
	XtSetValues(widgets[TIME_OUT_SCL],argList,1);
      }
   }

   /* The scale reads "minutes" but the extension gives us time
    * in seconds.
    */
   XtSetArg(argList[0],XmNdecimalPoints,&decimalPoints);
   XtGetValues(widgets[TIME_OUT_SCL],argList,1);
   if (state.timeOutInterval) {
      XmScaleSetValue(widgets[TIME_OUT_SCL],
	  ConvertUnitsToScaleValue(state.timeOutInterval / 60, decimalPoints));
      XmToggleButtonSetState(widgets[TIME_OUT_TGL], True, False);
   }
   else {
     XtSetArg(argList[0], XmNminimum, &minimum);
     XtGetValues(widgets[TIME_OUT_SCL], argList, 1);
     XmScaleSetValue(widgets[TIME_OUT_SCL], minimum);
     XmToggleButtonSetState(widgets[TIME_OUT_TGL], False, False);
   } 

   SetSettingsViewFromState(state);
   UpdateWidgetSensitivity();

} /* SetViewFromState */

/************************************************************************/
/*									*/
/* SetSettingsViewFromState						*/
/*									*/
/************************************************************************/
#if NeedFunctionPrototypes
void SetSettingsViewFromState(AccessXStateRec state)
#else
void SetSettingsViewFromState(state)
     AccessXStateRec state;
#endif
{
   int i;
   Arg argList[2];
   short decimalPoints;

   for (i = SETTINGS_TOGGLE_WIDGETS_MIN; i<=SETTINGS_TOGGLE_WIDGETS_MAX; i++) {
      if (state.control & toggleWidgetsMask[i]) {
	XmToggleButtonSetState(widgets[i], True, False);
      }
      else {
        XmToggleButtonSetState(widgets[i], False, False);
      }
   }

   /* The scale reads pixels per movement. */
   XtSetArg(argList[0],XmNdecimalPoints,&decimalPoints);

   /* The scale reads "seconds" and the extension gives us time in seconds. */
   XtGetValues(widgets[MOUSE_TIME_TO_MAX_SCL],argList,1);
   XmScaleSetValue(widgets[MOUSE_TIME_TO_MAX_SCL],
	    ConvertUnitsToScaleValue(state.mouseKeysTimeToMax, decimalPoints));

   /* The scale reads "pixels/sec" but the extension gives us time
      in milliseconds/pixel. */
   XtGetValues(widgets[MOUSE_MAX_SPEED_SCL],argList,1);
   XmScaleSetValue(widgets[MOUSE_MAX_SPEED_SCL],
      ConvertUnitsToScaleValue((float)(1.0 / 
          (float)MILLISTOSECS(state.mouseKeysInterval)), decimalPoints)); 

   /* The scale reads "seconds" but the extension gives us time
    * in milliseconds. */
   XtSetArg(argList[0],XmNdecimalPoints,&decimalPoints);
   XtGetValues(widgets[KRG_REPEAT_DELAY_SCL],argList,1);
   XmScaleSetValue(widgets[KRG_REPEAT_DELAY_SCL],
    ConvertUnitsToScaleValue(MILLISTOSECS(state.repeatKeysDelay),decimalPoints));

   /* The scale reads "keys/second" but the extension gives us time
    * in milliseconds/key. */
   XtGetValues(widgets[KRG_REPEAT_RATE_SCL],argList,1);
   XmScaleSetValue(widgets[KRG_REPEAT_RATE_SCL], ConvertUnitsToScaleValue(
            ((float)1.0 /
	    (float)MILLISTOSECS(state.repeatKeysRate)), decimalPoints));

   /* The scale reads "seconds" but the extension gives us time
    * in milliseconds. */
   XtGetValues(widgets[KRG_SLOW_DELAY_SCL],argList,1);
   XmScaleSetValue(widgets[KRG_SLOW_DELAY_SCL],
     ConvertUnitsToScaleValue(MILLISTOSECS(state.slowKeysDelay),decimalPoints));

   /* The scale reads "seconds" but the extension gives us time
    * in milliseconds. */
   XtGetValues(widgets[KRG_DEBOUNCE_SCL],argList,1);
   XmScaleSetValue(widgets[KRG_DEBOUNCE_SCL],
     ConvertUnitsToScaleValue(MILLISTOSECS(state.debounceDelay),decimalPoints));
}

/************************************************************************/
/*   									*/
/* SetStickyStatusViewFromState						*/
/*									*/
/************************************************************************/
#if NeedFunctionPrototypes
void SetStickyStatusViewFromState(void)
#else
void SetStickyStatusViewFromState()
#endif
{
    if(XKBExtension)
	SetStickyStatusViewFromStateXKB();
    else
	SetStickyStatusViewFromStateAX();
}/* SetStickyStatusViewFromState */

#if NeedFunctionPrototypes
void SetStickyStatusViewFromStateXKB(void)
#else
void SetStickyStatusViewFromStateXKB()
#endif
{
    XkbStateRec state;
    XkbDescRec  *desc;
    Arg argList[2];


    desc = XkbGetMap(dpy,0,XkbUseCoreKbd);
    XkbGetControls(dpy,XkbAllControlsMask,desc);
    XkbGetState(dpy,XkbUseCoreKbd,&state);

    /* Emtpy all mod settings first */
    XtSetArg(argList[0],XmNlabelString,shiftEmptyString);
    XtSetValues(widgets[SHIFT_LATCHED_LBL],argList,1);
    XtSetValues(widgets[SHIFT_LOCKED_LBL],argList,1);

    XtSetArg(argList[0],XmNlabelString,controlEmptyString);
    XtSetValues(widgets[CONTROL_LATCHED_LBL],argList,1);
    XtSetValues(widgets[CONTROL_LOCKED_LBL],argList,1);

    XtSetArg(argList[0],XmNlabelString,mod1EmptyString);
    XtSetValues(widgets[MOD1_LATCHED_LBL],argList,1);
    XtSetValues(widgets[MOD1_LOCKED_LBL],argList,1);

    XtSetArg(argList[0],XmNlabelString,mod2EmptyString);
    XtSetValues(widgets[MOD2_LATCHED_LBL],argList,1);
    XtSetValues(widgets[MOD2_LOCKED_LBL],argList,1);

    XtSetArg(argList[0],XmNlabelString,mod3EmptyString);
    XtSetValues(widgets[MOD3_LATCHED_LBL],argList,1);
    XtSetValues(widgets[MOD3_LOCKED_LBL],argList,1);

    XtSetArg(argList[0],XmNlabelString,mod4EmptyString);
    XtSetValues(widgets[MOD4_LATCHED_LBL],argList,1);
    XtSetValues(widgets[MOD4_LOCKED_LBL],argList,1);

    XtSetArg(argList[0],XmNlabelString,mod5EmptyString);
    XtSetValues(widgets[MOD5_LATCHED_LBL],argList,1);
    XtSetValues(widgets[MOD5_LOCKED_LBL],argList,1);

    /* Now set all the mods */
    if (state.latched_mods & ShiftMask) {
        XtSetArg(argList[0],XmNlabelString,shiftString);
        XtSetValues(widgets[SHIFT_LATCHED_LBL],argList,1);
    } else if (state.locked_mods & ShiftMask) {
        XtSetArg(argList[0],XmNlabelString,shiftString);
        XtSetValues(widgets[SHIFT_LOCKED_LBL],argList,1);
    }

    if (state.latched_mods & ControlMask) {
        XtSetArg(argList[0],XmNlabelString,controlString);
        XtSetValues(widgets[CONTROL_LATCHED_LBL],argList,1);
    }
    else if (state.locked_mods & ControlMask) {
        XtSetArg(argList[0],XmNlabelString,controlString);
        XtSetValues(widgets[CONTROL_LOCKED_LBL],argList,1);
    }

    if (state.latched_mods & Mod1Mask) {
        XtSetArg(argList[0],XmNlabelString,mod1String);
        XtSetValues(widgets[MOD1_LATCHED_LBL],argList,1);
    }
    else if (state.locked_mods & Mod1Mask) {
        XtSetArg(argList[0],XmNlabelString,mod1String);
        XtSetValues(widgets[MOD1_LOCKED_LBL],argList,1);
    }

    if (state.latched_mods & Mod2Mask) {
        XtSetArg(argList[0],XmNlabelString,mod2String);
        XtSetValues(widgets[MOD2_LATCHED_LBL],argList,1);
    }
    else if (state.locked_mods & Mod2Mask) {
        XtSetArg(argList[0],XmNlabelString,mod2String);
        XtSetValues(widgets[MOD2_LOCKED_LBL],argList,1);
    }

    if (state.latched_mods & Mod3Mask) {
        XtSetArg(argList[0],XmNlabelString,mod3String);
        XtSetValues(widgets[MOD3_LATCHED_LBL],argList,1);
    }
    else if (state.locked_mods & Mod3Mask) {
        XtSetArg(argList[0],XmNlabelString,mod3String);
        XtSetValues(widgets[MOD3_LOCKED_LBL],argList,1);
    }

    if (state.latched_mods & Mod4Mask) {
        XtSetArg(argList[0],XmNlabelString,mod4String);
        XtSetValues(widgets[MOD4_LATCHED_LBL],argList,1);
    }
    else if (state.locked_mods & Mod4Mask) {
        XtSetArg(argList[0],XmNlabelString,mod4String);
        XtSetValues(widgets[MOD4_LOCKED_LBL],argList,1);
    }

    if (state.latched_mods & Mod5Mask) {
        XtSetArg(argList[0],XmNlabelString,mod5String);
        XtSetValues(widgets[MOD5_LATCHED_LBL],argList,1);
    }
    else if (state.locked_mods & Mod5Mask) {
        XtSetArg(argList[0],XmNlabelString,mod5String);
        XtSetValues(widgets[MOD5_LOCKED_LBL],argList,1);
    }

}/* SetStickyStatusViewFromStateXKB  */

#if NeedFunctionPrototypes
void SetStickyStatusViewFromStateAX(void)
#else
void SetStickyStatusViewFromStateAX()
#endif
{
    Arg argList[2];
    AccessXStateRec state;

    XAccessXQueryState(dpy, &accessXClient, &state);

    if (state.latchedModifiers & ShiftMask) {
	XtSetArg(argList[0],XmNlabelString,shiftString);
	XtSetValues(widgets[SHIFT_LATCHED_LBL],argList,1);
    }
    else {
	XtSetArg(argList[0],XmNlabelString,shiftEmptyString);
	XtSetValues(widgets[SHIFT_LATCHED_LBL],argList,1);
    }

    if (state.lockedModifiers & ShiftMask) {
	XtSetArg(argList[0],XmNlabelString,shiftString);
	XtSetValues(widgets[SHIFT_LOCKED_LBL],argList,1);
    }
    else {
	XtSetArg(argList[0],XmNlabelString,shiftEmptyString);
	XtSetValues(widgets[SHIFT_LOCKED_LBL],argList,1);
    }

    if (state.latchedModifiers & ControlMask) {
	XtSetArg(argList[0],XmNlabelString,controlString);
	XtSetValues(widgets[CONTROL_LATCHED_LBL],argList,1);
    }
    else {
	XtSetArg(argList[0],XmNlabelString,controlEmptyString);
	XtSetValues(widgets[CONTROL_LATCHED_LBL],argList,1);
    }

    if (state.lockedModifiers & ControlMask) {
	XtSetArg(argList[0],XmNlabelString,controlString);
	XtSetValues(widgets[CONTROL_LOCKED_LBL],argList,1);
    }
    else {
	XtSetArg(argList[0],XmNlabelString,controlEmptyString);
	XtSetValues(widgets[CONTROL_LOCKED_LBL],argList,1);
    }

    if (state.latchedModifiers & Mod1Mask) {
	XtSetArg(argList[0],XmNlabelString,mod1String);
	XtSetValues(widgets[MOD1_LATCHED_LBL],argList,1);
    }
    else {
	XtSetArg(argList[0],XmNlabelString,mod1EmptyString);
	XtSetValues(widgets[MOD1_LATCHED_LBL],argList,1);
    }

    if (state.lockedModifiers & Mod1Mask) {
	XtSetArg(argList[0],XmNlabelString,mod1String);
	XtSetValues(widgets[MOD1_LOCKED_LBL],argList,1);
    }
    else {
	XtSetArg(argList[0],XmNlabelString,mod1EmptyString);
	XtSetValues(widgets[MOD1_LOCKED_LBL],argList,1);
    }

    if (state.latchedModifiers & Mod2Mask) {
	XtSetArg(argList[0],XmNlabelString,mod2String);
	XtSetValues(widgets[MOD2_LATCHED_LBL],argList,1);
    }
    else {
	XtSetArg(argList[0],XmNlabelString,mod2EmptyString);
	XtSetValues(widgets[MOD2_LATCHED_LBL],argList,1);
    }

    if (state.lockedModifiers & Mod2Mask) {
	XtSetArg(argList[0],XmNlabelString,mod2String);
	XtSetValues(widgets[MOD2_LOCKED_LBL],argList,1);
    }
    else {
	XtSetArg(argList[0],XmNlabelString,mod2EmptyString);
	XtSetValues(widgets[MOD2_LOCKED_LBL],argList,1);
    }

    if (state.latchedModifiers & Mod3Mask) {
	XtSetArg(argList[0],XmNlabelString,mod3String);
	XtSetValues(widgets[MOD3_LATCHED_LBL],argList,1);
    }
    else {
	XtSetArg(argList[0],XmNlabelString,mod3EmptyString);
	XtSetValues(widgets[MOD3_LATCHED_LBL],argList,1);
    }

    if (state.lockedModifiers & Mod3Mask) {
	XtSetArg(argList[0],XmNlabelString,mod3String);
	XtSetValues(widgets[MOD3_LOCKED_LBL],argList,1);
    }
    else {
	XtSetArg(argList[0],XmNlabelString,mod3EmptyString);
	XtSetValues(widgets[MOD3_LOCKED_LBL],argList,1);
    }

    if (state.latchedModifiers & Mod4Mask) {
	XtSetArg(argList[0],XmNlabelString,mod4String);
	XtSetValues(widgets[MOD4_LATCHED_LBL],argList,1);
    }
    else {
	XtSetArg(argList[0],XmNlabelString,mod4EmptyString);
	XtSetValues(widgets[MOD4_LATCHED_LBL],argList,1);
    }

    if (state.lockedModifiers & Mod4Mask) {
	XtSetArg(argList[0],XmNlabelString,mod4String);
	XtSetValues(widgets[MOD4_LOCKED_LBL],argList,1);
    }
    else {
	XtSetArg(argList[0],XmNlabelString,mod4EmptyString);
	XtSetValues(widgets[MOD4_LOCKED_LBL],argList,1);
    }

    if (state.latchedModifiers & Mod5Mask) {
	XtSetArg(argList[0],XmNlabelString,mod5String);
	XtSetValues(widgets[MOD5_LATCHED_LBL],argList,1);
    }
    else {
	XtSetArg(argList[0],XmNlabelString,mod5EmptyString);
	XtSetValues(widgets[MOD5_LATCHED_LBL],argList,1);
    }

    if (state.lockedModifiers & Mod5Mask) {
	XtSetArg(argList[0],XmNlabelString,mod5String);
	XtSetValues(widgets[MOD5_LOCKED_LBL],argList,1);
    }
    else {
	XtSetArg(argList[0],XmNlabelString,mod5EmptyString);
	XtSetValues(widgets[MOD5_LOCKED_LBL],argList,1);
    }
} /* SetStickyStatusViewFromStateAX */
	
/************************************************************************/
/*                                                                      */
/* SetMouseStatusViewFromState                                          */
/*                                                                      */
/************************************************************************/
#if NeedFunctionPrototypes
void SetMouseStatusViewFromState(void)
#else
void SetMouseStatusViewFromState()
#endif
{
    if(XKBExtension)
	SetMouseStatusViewFromStateXKB();
    else
	SetMouseStatusViewFromStateAX();
} /* SetMouseStatusViewFromState */

#if NeedFunctionPrototypes
void SetMouseStatusViewFromStateXKB(void)
#else
void SetMouseStatusViewFromStateXKB()
#endif
{
    Window          rootWindow,childWindow;
    int             rootX,rootY,windowX,windowY;
    unsigned long   mask;
    XkbStateRec state;
    XkbDescRec  *desc;
    Arg argList[2];
    XmString	    currentButtonString = NULL;

    desc = XkbGetMap(dpy,0,XkbUseCoreKbd);
    XkbGetControls(dpy,XkbAllControlsMask,desc);
    XkbGetState(dpy,XkbUseCoreKbd,&state);

    switch (desc->ctrls->mk_dflt_btn) {
    case 1:
	currentButtonString = mb1String;
	break;
    case 2:
	currentButtonString = mb2String;
	break;
    case 3:
	currentButtonString = mb3String;
	break;
    case 4:
	currentButtonString = mb4String;
	break;
    case 5:
	currentButtonString = mb5String;
	break;
    }
    if (currentButtonString != NULL) {
	XtSetArg(argList[0], XmNlabelString, currentButtonString);
	XtSetValues(widgets[CURRENT_BUTTON_LBL], argList, 1);
    }

    XQueryPointer(dpy,
                  XDefaultRootWindow(dpy),
                  &rootWindow,
                  &childWindow,
                  &rootX,&rootY,
                  &windowX,&windowY,
                  (unsigned int*)&mask);
 
    if (mask & Button1Mask) {
      XtSetArg(argList[0], XmNlabelString, mb1String);
      XtSetValues(widgets[MB1_PRESSED_LBL], argList, 1);
      XtSetArg(argList[0], XmNlabelString, mb1EmptyString);
      XtSetValues(widgets[MB1_RELEASED_LBL], argList, 1);
    }
    else {
      XtSetArg(argList[0], XmNlabelString, mb1EmptyString);
      XtSetValues(widgets[MB1_PRESSED_LBL], argList, 1);
      XtSetArg(argList[0], XmNlabelString, mb1String);
      XtSetValues(widgets[MB1_RELEASED_LBL], argList, 1);
    }
 
    if (mask & Button2Mask) {
      XtSetArg(argList[0], XmNlabelString, mb2String);
      XtSetValues(widgets[MB2_PRESSED_LBL], argList, 1);
      XtSetArg(argList[0], XmNlabelString, mb2EmptyString);
      XtSetValues(widgets[MB2_RELEASED_LBL], argList, 1);
    }
    else {
      XtSetArg(argList[0], XmNlabelString, mb2EmptyString);
      XtSetValues(widgets[MB2_PRESSED_LBL], argList, 1);
      XtSetArg(argList[0], XmNlabelString, mb2String);
      XtSetValues(widgets[MB2_RELEASED_LBL], argList, 1);
    }
 
    if (mask & Button3Mask) {
      XtSetArg(argList[0], XmNlabelString, mb3String);
      XtSetValues(widgets[MB3_PRESSED_LBL], argList, 1);
      XtSetArg(argList[0], XmNlabelString, mb3EmptyString);
      XtSetValues(widgets[MB3_RELEASED_LBL], argList, 1);
    }
    else {
      XtSetArg(argList[0], XmNlabelString, mb3EmptyString);
      XtSetValues(widgets[MB3_PRESSED_LBL], argList, 1);
      XtSetArg(argList[0], XmNlabelString, mb3String);
      XtSetValues(widgets[MB3_RELEASED_LBL], argList, 1);
    }


} /* SetMouseStatusViewFromStateXKB */

#if NeedFunctionPrototypes
void SetMouseStatusViewFromStateAX(void)
#else
void SetMouseStatusViewFromStateAX()
#endif
{
   Arg argList[2];
   AccessXStateRec state;
   Window	   rootWindow,childWindow;
   int		   rootX,rootY,windowX,windowY;
   unsigned long   mask;

   XAccessXQueryState(dpy, &accessXClient, &state);

   switch (state.currentMouseButton) {
   case 1:
     XtSetArg(argList[0], XmNlabelString, mb1String);
     break;
   case 2:
     XtSetArg(argList[0], XmNlabelString, mb2String);
     break;
   case 3:
     XtSetArg(argList[0], XmNlabelString, mb3String);
     break;
   case 4:
     XtSetArg(argList[0], XmNlabelString, mb4String);
     break;
   case 5:
     XtSetArg(argList[0], XmNlabelString, mb5String);
     break;
   }
   XtSetValues(widgets[CURRENT_BUTTON_LBL], argList, 1);

   XQueryPointer(dpy,
		 XDefaultRootWindow(dpy),
		 &rootWindow,
		 &childWindow,
		 &rootX,&rootY,
		 &windowX,&windowY,
		 (unsigned int*)&mask);

   if (mask & Button1Mask) {
     XtSetArg(argList[0], XmNlabelString, mb1String);
     XtSetValues(widgets[MB1_PRESSED_LBL], argList, 1);
     XtSetArg(argList[0], XmNlabelString, mb1EmptyString); 
     XtSetValues(widgets[MB1_RELEASED_LBL], argList, 1);
   }
   else {
     XtSetArg(argList[0], XmNlabelString, mb1EmptyString);
     XtSetValues(widgets[MB1_PRESSED_LBL], argList, 1);
     XtSetArg(argList[0], XmNlabelString, mb1String); 
     XtSetValues(widgets[MB1_RELEASED_LBL], argList, 1);
   }

   if (mask & Button2Mask) {
     XtSetArg(argList[0], XmNlabelString, mb2String);
     XtSetValues(widgets[MB2_PRESSED_LBL], argList, 1);
     XtSetArg(argList[0], XmNlabelString, mb2EmptyString); 
     XtSetValues(widgets[MB2_RELEASED_LBL], argList, 1);
   }
   else {
     XtSetArg(argList[0], XmNlabelString, mb2EmptyString);
     XtSetValues(widgets[MB2_PRESSED_LBL], argList, 1);
     XtSetArg(argList[0], XmNlabelString, mb2String); 
     XtSetValues(widgets[MB2_RELEASED_LBL], argList, 1);
   }
 
   if (mask & Button3Mask) {
     XtSetArg(argList[0], XmNlabelString, mb3String);
     XtSetValues(widgets[MB3_PRESSED_LBL], argList, 1);
     XtSetArg(argList[0], XmNlabelString, mb3EmptyString); 
     XtSetValues(widgets[MB3_RELEASED_LBL], argList, 1);
   }
   else {
     XtSetArg(argList[0], XmNlabelString, mb3EmptyString);
     XtSetValues(widgets[MB3_PRESSED_LBL], argList, 1);
     XtSetArg(argList[0], XmNlabelString, mb3String); 
     XtSetValues(widgets[MB3_RELEASED_LBL], argList, 1);
   }

#ifdef SHOW_5_BUTTONS_IN_MOUSEKEYS_STATUS
   if (mask & Button4Mask) {
     XtSetArg(argList[0], XmNlabelString, mb4String);
     XtSetValues(widgets[MB4_PRESSED_LBL], argList, 1);
     XtSetArg(argList[0], XmNlabelString, mb4EmptyString); 
     XtSetValues(widgets[MB4_RELEASED_LBL], argList, 1);
   }
   else {
     XtSetArg(argList[0], XmNlabelString, mb4EmptyString);
     XtSetValues(widgets[MB4_PRESSED_LBL], argList, 1);
     XtSetArg(argList[0], XmNlabelString, mb4String); 
     XtSetValues(widgets[MB4_RELEASED_LBL], argList, 1);
   }

   if (mask & Button5Mask) {
     XtSetArg(argList[0], XmNlabelString, mb5String);
     XtSetValues(widgets[MB5_PRESSED_LBL], argList, 1);
     XtSetArg(argList[0], XmNlabelString, mb5EmptyString); 
     XtSetValues(widgets[MB5_RELEASED_LBL], argList, 1);
   }
   else {
     XtSetArg(argList[0], XmNlabelString, mb5EmptyString);
     XtSetValues(widgets[MB5_PRESSED_LBL], argList, 1);
     XtSetArg(argList[0], XmNlabelString, mb5String); 
     XtSetValues(widgets[MB5_RELEASED_LBL], argList, 1);
   }
#endif
} /* SetMouseStatusViewFromStateAX */

/************************************************************************/
/*                                                                      */
/* UpdateWidgetSensitivity                                              */
/*                                                                      */
/************************************************************************/
#if NeedFunctionPrototypes
void UpdateWidgetSensitivity(void)
#else
void UpdateWidgetSensitivity()
#endif
{
   int i;
   Arg argList[2];

   /* If the enable toggle is turned of then grey out everything */
   if (XmToggleButtonGadgetGetState(widgets[ENABLE_ACCESSX_TGL])) {
     XtSetArg(argList[0], XmNsensitive, True);
   }
   else {
     XtSetArg(argList[0], XmNsensitive, False);
   }

   for (i = TOGGLE_WIDGETS_MIN; i <= TOGGLE_WIDGETS_MAX; i++) {
      if (i != ENABLE_ACCESSX_TGL) {
         XtSetValues(widgets[i], argList, 1);
      }
   }

   for (i = SCALE_WIDGETS_MIN; i <= SCALE_WIDGETS_MAX; i++) {
      XtSetValues(widgets[i], argList, 1);
   }

   /* Toggle Sensitivity of TimeOut Scale based upon ENABLE_ACCESS
    * as well as the TimeOut Toggle.
    */
   if (XmToggleButtonGadgetGetState(widgets[TIME_OUT_TGL]) &&
       XmToggleButtonGadgetGetState(widgets[ENABLE_ACCESSX_TGL])) {
       XtSetArg(argList[0], XmNsensitive, True);
       XtSetValues(widgets[TIME_OUT_SCL],argList,1);
   }
   else {
       XtSetArg(argList[0], XmNsensitive, False);
       XtSetValues(widgets[TIME_OUT_SCL],argList,1);
   }

   /* Always grey out the mouse delay scale with the old AccessX extension */
   if(!XKBExtension) {
	   XtSetArg(argList[0], XmNsensitive, False);
	   XtSetValues(widgets[MOUSE_DELAY_SCL],argList,1);
   }

}

/************************************************************************/
/*									*/
/* CreateProc								*/
/*									*/
/*	Procedure called when a widget is fetched from Mrm.		*/
/*									*/
/************************************************************************/
#if NeedFunctionPrototypes
void CreateProc(Widget 		widget, 
		int		*id, 
		unsigned long	reason)
#else
void CreateProc(widget,id,reason)
    Widget 		widget;
    int			*id;
    unsigned long	reason;
#endif
{
    widgets[*id] = widget;

} /* CreateProc */

/************************************************************************/
/*									*/
/* ActivateProc								*/
/*									*/
/*	Procedure called when a widget is activated.  [[[Right now it	*/
/*	merely handles the pushbuttons in the interface.  Things like	*/
/*	saving the current state when bringing up a dialog box and 	*/
/*	restoring the prvious state when the user hits "Cancel" need	*/
/*	to be added.  In addition, the whole help mechanism needs to be	*/
/*	defined.]]]							*/
/*									*/
/************************************************************************/
#if NeedFunctionPrototypes
void ActivateProc(Widget 		widget, 
		  int			*id, 
		  XmAnyCallbackStruct	*callbackData)
#else
void ActivateProc(widget,id,callbackData)
    Widget 		widget;
    int			*id;
    XmAnyCallbackStruct	*callbackData;
#endif
{
    switch (*id) {
    case EXIT_BTN:
       XAccessXSelectInput(dpy,&accessXClient,False);
       exit(0);

    case LOAD_BTN:
       LoadSettingsFromFile();
       break;

    case SAVE_BTN:
       SaveSettingsToFile();
       break;

    case SETTINGS_BTN:
       StoreSettingsWindowToDatabase();
       XtManageChild(settingsDialog);
       break;

    case SETTINGS_RESET_BTN:
       RestoreSettingsWindowFromDatabase();
       SetStateFromView();
       break;

    case SETTINGS_DEFAULTS_BTN:
	SetDefaults();
	break;

    case SETTINGS_OK_BTN:
       XtUnmanageChild(settingsDialog);
       SaveSettingsToFile();
       break;

    case SETTINGS_CANCEL_BTN:
       RestoreSettingsWindowFromDatabase();
       SetStateFromView();
       XtUnmanageChild(settingsDialog);
       break;
   
    case MOUSE_STATUS_BTN:
          CreateAndMapMouseStatusWindow();
          break;

    case STICKY_STATUS_BTN:
          CreateAndMapStickyStatusWindow();
          break;

    case MOUSE_CLOSE_BTN:
          UnmapMouseStatusWindow();
          break;

    case STICKY_CLOSE_BTN:
          UnmapStickyStatusWindow();
          break;

    case SAVE_DONE_OK_BTN:
    case SAVE_DONE_CANCEL_BTN:
          XtUnmanageChild(saveDoneDialog);
          break;

    case SAVE_ERR_OK_BTN:
    case SAVE_ERR_CANCEL_BTN:
          XtUnmanageChild(saveErrDialog);
          break;

    case LOAD_DONE_OK_BTN:
    case LOAD_DONE_CANCEL_BTN:
          XtUnmanageChild(loadDoneDialog);
          break;

    case LOAD_ERR_OK_BTN:
    case LOAD_ERR_CANCEL_BTN:
          XtUnmanageChild(loadErrDialog);
          break;

    case CLOSE_HELP_BTN:
          XtUnmanageChild(helpDialog);
          XtFree(textString);
          break;
	
    case GENERAL_HELP_BTN:
    case STICKY_HELP_BTN:
    case MOUSE_HELP_BTN:
    case TOGGLE_HELP_BTN:
    case REPEAT_HELP_BTN:
    case SLOW_HELP_BTN:
    case BOUNCE_HELP_BTN:
    case SETTINGS_HELP_BTN:
          XtManageChild(helpDialog);
          if (!SetHelpText(*id)) {
             break;
          }
          XmTextSetString(widgets[HELP_TEXT], textString);
          break;
    } 
} /* ActivateProc */

/************************************************************************/
/*									*/
/* GetSizeOfHelpText							*/
/*									*/
/************************************************************************/
#if NeedFunctionPrototypes
int GetSizeOfHelpText(int type)
#else
int GetSizeOfHelpText(type)
     int type;
#endif
{
   int size;

   size = 0;

   switch (type) {
   case GENERAL_HELP_BTN:
      size += strlen(generalHelpString);
      break;

   case STICKY_HELP_BTN:
      size += strlen(stickyHelpString);
      break;

   case MOUSE_HELP_BTN:
      size += strlen(mouseHelpString);
      break;

   case TOGGLE_HELP_BTN:
      size += strlen(toggleHelpString);
      break;

   case REPEAT_HELP_BTN:
      size += strlen(repeatHelpString);
      break;

   case SLOW_HELP_BTN:
      size += strlen(slowHelpString);
      break;

   case BOUNCE_HELP_BTN:
      size += strlen(bounceHelpString);
      break;
   }

   return(size);
} /* GetSizeOfHelpText */
 
/************************************************************************/
/*									*/
/* AllocateHelpTextMemory						*/
/*									*/
/************************************************************************/
#if NeedFunctionPrototypes
Bool AllocateHelpTextMemory(int size)
#else
Bool AllocateHelpTextMemory(size)
     int size;
#endif
{
   if ((textString = XtMalloc(size)) == NULL) {
      return(False);
   }

   return(True);
} /* AllocateHelpTextMemory */

/************************************************************************/
/*									*/
/* InitHelp								*/
/*									*/
/************************************************************************/
#if NeedFunctionPrototypes
Bool InitHelp(void)
#else
Bool InitHelp()
#endif 
{

	char *locale = setlocale(LC_MESSAGES, NULL);
	char *helpfile;
	FILE *helpfilefp;
	Bool i;

	helpfile = XtMalloc(strlen(ACCESSXHELP_DIRECTORY) + strlen(locale) + 
			strlen(HELPDIR) +
			strlen(ACCESSXHELP_FILE) + 10);
	if (!helpfile) {
		return(False);
	}

	sprintf(helpfile,"%s%s%s%s", ACCESSXHELP_DIRECTORY, locale, 
		HELPDIR,
		ACCESSXHELP_FILE);

	helpfilefp = fopen(helpfile, "r");
	if (!helpfilefp) {
		/* 4340632: accessx application should show C locale help
		   if localized help not available */
		sprintf(helpfile,"%s%s%s%s", ACCESSXHELP_DIRECTORY, "C",
		    HELPDIR,ACCESSXHELP_FILE);
		helpfilefp = fopen(helpfile, "r");
		if (!helpfilefp) {
			XtFree(helpfile);
			return(False);
		}
	}
	i = ReadHelpFile(helpfilefp);
	fclose(helpfilefp);
	XtFree(helpfile);
	return(i);
	
}
/************************************************************************/
/*									*/
/* ReadHelpFile								*/
/*									*/
/************************************************************************/


#define MEMORYCHUNKS 	4096

#if NeedFunctionPrototypes
Bool ReadHelpFile(FILE *fp)
#else
Bool ReadHelpFile(fp)
	FILE * fp;
#endif
{

	char line[256];
	char *ptr;
	int size = sizeof(line);
	int reallocsize = 1;
	int currentmemsize = 0;
	
/*	char *getaline(); */
	
	ptr = fgets(line, size, fp);
	if (!ptr)
		return(False);
	
	while (*ptr == COMMENT) {
		ptr = fgets(line, size, fp);
		if (!ptr)
			return(False);
	}
	
	generalHelpString = (char *)malloc(MEMORYCHUNKS);
	if (!generalHelpString) {
		return(False);
	}

	generalHelpString[0] = '\0';
	currentmemsize = MEMORYCHUNKS - 1;

	/* it is general help */
	while (*ptr != COMMENT) {
		reallocsize += strlen(line);
		if (reallocsize >= currentmemsize) {
		    currentmemsize += MEMORYCHUNKS;
		    generalHelpString = XtRealloc (generalHelpString, 
			currentmemsize);
		    if (!generalHelpString) {
			return(False);
		    }
		}

		strcat (generalHelpString, line);
		ptr = fgets(line, size, fp);
		if (!ptr) {
			return(False);
		}
			
	}

	/* remove the comment line */
	ptr = fgets(line, size, fp);
	if (!ptr) {
		return(False);
	}

	stickyHelpString = (char *)malloc(MEMORYCHUNKS);
	if (!stickyHelpString) {
		return(False);
	}

	stickyHelpString[0] = '\0';
	currentmemsize = MEMORYCHUNKS - 1;

	/* it is Sticky Key help */
	reallocsize = 1;
	while (*ptr != COMMENT) {
		reallocsize += strlen(line);
		if (reallocsize >= currentmemsize) {
		    currentmemsize += MEMORYCHUNKS;
		    stickyHelpString = XtRealloc (stickyHelpString,
			currentmemsize);
		    if (!stickyHelpString) {
			return(False);
		    }
		}


		strcat (stickyHelpString, line);
		ptr = fgets(line, size, fp);
		if (!ptr) {
			return(False);
		}
			
	}
	
	/* remove the comment line */
	ptr = fgets(line, size, fp);
	if (!ptr) {
		return(False);
	}

	mouseHelpString = (char *)malloc(MEMORYCHUNKS);
	if (!mouseHelpString) {
		return(False);
	}

	mouseHelpString[0] = '\0';
	currentmemsize = MEMORYCHUNKS - 1;

	/* it is Mouse Key help */
	reallocsize = 1;
	while (*ptr != COMMENT) {
		reallocsize += strlen(line);
		if (reallocsize >= currentmemsize) {
		    currentmemsize += MEMORYCHUNKS;
		    mouseHelpString = XtRealloc (mouseHelpString,
			    currentmemsize);
		    if (!mouseHelpString) {
			return(False);
		    }
		}


		strcat (mouseHelpString, line);
		ptr = fgets(line, size, fp);
		if (!ptr) {
			return(False);
		}
			
	}
	
	/* remove the comment line */
	ptr = fgets(line, size, fp);
	if (!ptr) {
		return(False);
	}

	toggleHelpString = (char *)malloc(MEMORYCHUNKS);
	if (!toggleHelpString) {
		return(False);
	}

	toggleHelpString[0] = '\0';
	currentmemsize = MEMORYCHUNKS - 1;

	/* it is Toggle Key help */
	reallocsize = 1;
	while (*ptr != COMMENT) {
		reallocsize += strlen(line);
		if (reallocsize >= currentmemsize) {
		    currentmemsize += MEMORYCHUNKS;
		    toggleHelpString = XtRealloc (toggleHelpString,
			    currentmemsize);
		    if (!toggleHelpString) {
			return(False);
		    }
		}


		strcat (toggleHelpString, line);
		ptr = fgets(line, size, fp);
		if (!ptr) {
			return(False);
		}
			
	}
	
	/* remove the comment line */
	ptr = fgets(line, size, fp);
	if (!ptr) {
		return(False);
	}

	repeatHelpString = (char *)malloc(MEMORYCHUNKS);
	if (!repeatHelpString) {
		return(False);
	}

	repeatHelpString[0] = '\0';
	currentmemsize = MEMORYCHUNKS;

	/* it is Repeat Key help */
	reallocsize = 1;
	while (*ptr != COMMENT) {
		reallocsize += strlen(line);
		if (reallocsize >= currentmemsize) {
		    currentmemsize += MEMORYCHUNKS;
		    repeatHelpString = XtRealloc (repeatHelpString,
			    currentmemsize);
		    if (!repeatHelpString) {
			    return(False);
		    }
		}


		strcat (repeatHelpString, line);
		ptr = fgets(line, size, fp);
		if (!ptr) {
			return(False);
		}
			
	}
	
	/* remove the comment line */
	ptr = fgets(line, size, fp);
	if (!ptr) {
		return(False);
	}

	slowHelpString = (char *)malloc(MEMORYCHUNKS);
	if (!slowHelpString) {
		return(False);
	}

	slowHelpString[0] = '\0';
	currentmemsize = MEMORYCHUNKS;

	/* it is Slow Key help */
	reallocsize = 1;
	while (*ptr != COMMENT) {
		reallocsize += strlen(line);
		if (reallocsize >= currentmemsize) {
		    currentmemsize += MEMORYCHUNKS;
		    slowHelpString = XtRealloc (slowHelpString,
			    currentmemsize);
		    if (!slowHelpString) {
			    return(False);
		    }
		}


		strcat (slowHelpString, line);
		ptr = fgets(line, size, fp);
		if (!ptr) {
			return(False);
		}
			
	}
	
	/* remove the comment line */
	ptr = fgets(line, size, fp);
	if (!ptr) {
		return(False);
	}

	bounceHelpString = (char *)malloc(MEMORYCHUNKS);
	if (!bounceHelpString) {
		return(False);
	}

	bounceHelpString[0] = '\0';
	currentmemsize = MEMORYCHUNKS;

	/* it is Bounce Key help */
	reallocsize = 1;
	while (*ptr != COMMENT) {
		reallocsize += strlen(line);
		if (reallocsize >= currentmemsize) {
		    currentmemsize += MEMORYCHUNKS;
		    bounceHelpString = XtRealloc (bounceHelpString,
			currentmemsize);
		    if (!bounceHelpString) {
			    return(False);
		    }
		}


		strcat (bounceHelpString, line);
		ptr = fgets(line, size, fp);
		if (!ptr) {
			return(True);
		}
			
	}
	return(True);
}	

/************************************************************************/
/*									*/
/* SetHelpText								*/
/*									*/
/************************************************************************/
#if NeedFunctionPrototypes
Bool SetHelpText(int id)
#else
Bool SetHelpText(id)
     int id;
#endif
{
   int result;
   static int inited = 0;	/* initialization flag */

   if (!inited) {
	 if (InitHelp() == False) {
		fprintf(stderr, "The help file \n"
			"[" ACCESSXHELP_DIRECTORY "<locale>" HELPDIR ACCESSXHELP_FILE "] is not installed.\n"
			"Please contact your system administrator\n");
		return(False);
	 }
	 inited = 1;
   }

   if (id == SETTINGS_HELP_BTN) {
      result = AllocateHelpTextMemory(GetSizeOfHelpText(STICKY_HELP_BTN) +
		GetSizeOfHelpText(MOUSE_HELP_BTN) +
		GetSizeOfHelpText(TOGGLE_HELP_BTN) +
		GetSizeOfHelpText(REPEAT_HELP_BTN) +
		GetSizeOfHelpText(SLOW_HELP_BTN) +
		GetSizeOfHelpText(BOUNCE_HELP_BTN) + 1);
   }
   else {
      result = AllocateHelpTextMemory(GetSizeOfHelpText(id) + 1);
   }
   if (!result) {
      return(False);
   }

   strcpy(textString, "");

   switch (id) {
   case GENERAL_HELP_BTN:
      strcat(textString, generalHelpString);
      break;

   case STICKY_HELP_BTN:
      strcat(textString, stickyHelpString);
      break;

   case MOUSE_HELP_BTN:
      strcat(textString, mouseHelpString);
      break;
   
    case TOGGLE_HELP_BTN:
      strcat(textString, toggleHelpString);
      break;

   case REPEAT_HELP_BTN:
      strcat(textString, repeatHelpString);
      break;

   case SLOW_HELP_BTN:
      strcat(textString, slowHelpString);
      break;

   case BOUNCE_HELP_BTN:
      strcat(textString, bounceHelpString);
      break;

   case SETTINGS_HELP_BTN:
      strcat(textString, stickyHelpString);
      strcat(textString, mouseHelpString);
      strcat(textString, toggleHelpString);
      strcat(textString, repeatHelpString);
      strcat(textString, slowHelpString);
      strcat(textString, bounceHelpString);
      break; 
   }
 
   return(True);
}

/************************************************************************/
/*                                                                      */
/* SpaceAndSizeButtons		                                        */
/*                                                                      */
/************************************************************************/
#if NeedFunctionPrototypes
void SpaceAndSizeButtons(Widget		*widgets,
			 int		numWidgets)
#else
void SpaceAndSizeButtons(widgets, numWidgets)
    Widget	*widgets;
    int		numWidgets;
#endif
{
    Arg argList[5];
    int i;
    int widest = 0;
    
    /* Find the widest button.
     */
    for (i = 0; i < numWidgets; i++) 
    {
        if (XtWidth(widgets[i]) > widest)
            widest = XtWidth(widgets[i]);
    }

    /*  Equally space the buttons.
     */
    XtSetArg(argList[0], XmNwidth, widest);
    XtSetArg(argList[1], XmNleftOffset, 0);
    XtSetArg(argList[2], XmNleftAttachment, XmATTACH_POSITION);
    XtSetArg(argList[3], XmNleftPosition, 0);
    for (i = 0; i < numWidgets; i++) 
    {
	argList[1].value = widest * (i - numWidgets) / (numWidgets + 1);
        argList[3].value = 100 * (i + 1) / (numWidgets + 1);
	XtSetValues (widgets[i], argList, 4);
    }

} /* SpaceAndSizeButtons */

/************************************************************************/
/*                                                                      */
/* CreateAndMapStickyStatusWindow                                       */
/*                                                                      */
/************************************************************************/
#if NeedFunctionPrototypes
void CreateAndMapStickyStatusWindow(void)
#else
void CreateAndMapStickyStatusWindow()
#endif
{
       XtManageChild(statusStickyKeysDialog);
       XtRealizeWidget(stickyTopLevel);

       XtVaSetValues ( stickyTopLevel,
			XmNtransientFor, NULL,
			XmNwindowGroup, XtUnspecifiedWindowGroup,
			NULL );

   XtMapWidget(stickyTopLevel);
   SetStickyStatusViewFromState();
   
} /* CreateAndMapStickyStatusWindow */

/************************************************************************/
/*                                                                      */
/* UnmapStickyStatusWindow                                              */
/*                                                                      */
/************************************************************************/
#if NeedFunctionPrototypes
void UnmapStickyStatusWindow(void)
#else
void UnmapStickyStatusWindow()
#endif
{
   if (stickyTopLevel != NULL)
       XtUnmapWidget(stickyTopLevel);  


} /* UnmapStickyStatusWindow */

/************************************************************************/
/*                                                                      */
/* CreateAndMapMouseStatusWindow                                        */
/*                                                                      */
/************************************************************************/
#if NeedFunctionPrototypes
void CreateAndMapMouseStatusWindow(void)
#else
void CreateAndMapMouseStatusWindow()
#endif
{
       XtManageChild(statusMouseKeysDialog);
       XtRealizeWidget(mouseTopLevel);

       XtVaSetValues ( mouseTopLevel,
			XmNtransientFor, NULL,
			XmNwindowGroup, XtUnspecifiedWindowGroup,
			NULL );

   XtMapWidget(mouseTopLevel);
   SetMouseStatusViewFromState();

} /* CreateAndMapMouseStatusWindow */

/************************************************************************/
/*                                                                      */
/* UnmapMouseStatusWindow                                               */
/*                                                                      */
/************************************************************************/
#if NeedFunctionPrototypes
void UnmapMouseStatusWindow(void)
#else
void UnmapMouseStatusWindow()
#endif
{
   if (mouseTopLevel != NULL)
       XtUnmapWidget(mouseTopLevel);

} /* UnmapMouseStatusWindow */

/************************************************************************/
/*									*/
/* ChangeControlProc							*/
/*									*/
/*	Procedure called when one of the widgets indicating the AccessX	*/
/*	state is activated.						*/
/*									*/
/************************************************************************/
#if NeedFunctionPrototypes
void ChangeControlProc(Widget 				widget, 
		       int				*id, 
		       XmToggleButtonCallbackStruct	*callbackData)
#else
void ChangeControlProc(widget,id,callbackData)
    Widget 				widget;
    int					*id;
    XmToggleButtonCallbackStruct	*callbackData;
#endif
{
    /* Before we do anything, make sure we emulate the radio behavior
       of the SlowKeys and BounceKeys buttons. */
    if ((*id == SLOW_KEYS_TGL) && (callbackData->set)) {
	XmToggleButtonGadgetSetState(widgets[BOUNCE_KEYS_TGL],False,False);
    }
    else if ((*id == BOUNCE_KEYS_TGL) && (callbackData->set)) {
	XmToggleButtonGadgetSetState(widgets[SLOW_KEYS_TGL],False,False);
    }

    /* Set the repeat state and keysym mappings of the mouse keys if
       this is the MouseKeys toggle buttons. */
    if (*id == MOUSE_KEYS_TGL) {
	if (callbackData->set) {
            if (options.automaticPopup) {
               CreateAndMapMouseStatusWindow();
            }
	}	
	else {
            if (options.automaticPopup) {
		UnmapMouseStatusWindow();
            }
	}
    }

    SetStateFromView();

    /* Save To A File IF Needed  */
    SaveSettingsToFile();

} /* ChangeControlProc */

/************************************************************************/
/*                                                                      */
/* ResolveResourceFileName                                              */
/*                                                                      */
/************************************************************************/
#if NeedFunctionPrototypes
char *ResolveResourceFileName(void)
#else
char *ResolveResourceFileName()
#endif
{
   static char *homeDirectory, fullPath[MAXPATHLEN];

   if ((homeDirectory = getenv("HOME")) == NULL) {
      return(NULL);
   }
   sprintf(fullPath, "%s/%s", homeDirectory, ACCESSX_FILE);

   return(fullPath);

} /* ResolveResourceFileName */

/************************************************************************/
/*                                                                      */
/* LoadSettingsFromFile                                                 */
/*                                                                      */
/************************************************************************/
#if NeedFunctionPrototypes
void LoadSettingsFromFile(void)
#else
void LoadSettingsFromFile()
#endif
{
   int i, value;
   short decimalPoints;
   XrmDatabase accessXDatabase;
   char *res, classValueString[256], classDecimalPointsString[256];
   XrmValue resourceValue;
   Arg argList[2];

   accessXDatabase = XrmGetFileDatabase(ResolveResourceFileName());
   if (accessXDatabase == NULL) {
      XtManageChild(loadErrDialog);
      return;
   }

   for (i = TOGGLE_WIDGETS_MIN; i <= TOGGLE_WIDGETS_MAX; i++) {
      XrmGetResource(accessXDatabase, resStrings[i], classStrings[i],
                     &res, &resourceValue);
      if (strcmp(resourceValue.addr, "True") == 0) {
         XmToggleButtonGadgetSetState(widgets[i], True, False);
      }
      else {
         XmToggleButtonGadgetSetState(widgets[i], False, False);
      }
   }

   for (i = SCALE_WIDGETS_MIN; i <= SCALE_WIDGETS_MAX; i++)  {
      sprintf(classValueString, "%s.value", resStrings[i]);
      sprintf(classDecimalPointsString, "%s.decimalPoints", resStrings[i]);

      XrmGetResource(accessXDatabase, classValueString, classStrings[i],
                     &res, &resourceValue); 
      if (resourceValue.addr == NULL)
	  continue;
      value = atoi(resourceValue.addr);
      XrmGetResource(accessXDatabase, classDecimalPointsString, classStrings[i],
                     &res, &resourceValue);
      if (resourceValue.addr == NULL)
	  continue;
      decimalPoints = atoi(resourceValue.addr);

      XtSetArg(argList[0], XmNvalue, value);
      XtSetArg(argList[1], XmNdecimalPoints, decimalPoints);
      XtSetValues(widgets[i], argList, 2);
   }
      
   SetStateFromView();
   /* XtManageChild(loadDoneDialog); */

} /* LoadSettingsFromFile */

/************************************************************************/
/*                                                                      */
/* SaveSettingsToFile                                                   */
/*                                                                      */
/************************************************************************/
#if NeedFunctionPrototypes
void SaveSettingsToFile(void)
#else
void SaveSettingsToFile()
#endif
{
    int i, scaleValue;
    short decimalPoints;
    Arg argList[2];
    char scaleValueString[32], decimalPointsString[32];
    char scaleValueRes[256], decimalPointsRes[256];
    char *fname;
    XrmDatabase accessXDatabase = NULL, fileDatabase;

    for (i = TOGGLE_WIDGETS_MIN; i <= TOGGLE_WIDGETS_MAX; i++) {
       if (XmToggleButtonGadgetGetState(widgets[i])) {
         XrmPutStringResource(&accessXDatabase, resStrings[i], "True");
       }
       else {
         XrmPutStringResource(&accessXDatabase, resStrings[i], "False");
       }
    }

    for (i = SCALE_WIDGETS_MIN; i <= SCALE_WIDGETS_MAX; i++) {
      XtSetArg(argList[0], XmNvalue, &scaleValue);
      XtSetArg(argList[1], XmNdecimalPoints, &decimalPoints);
      XtGetValues(widgets[i], argList, 2);

      sprintf(scaleValueString, "%d", scaleValue);
      sprintf(decimalPointsString, "%d", decimalPoints);

      sprintf(scaleValueRes, "%s.%s", resStrings[i], "value");
      sprintf(decimalPointsRes, "%s.%s", resStrings[i], "decimalPoints");

      XrmPutStringResource(&accessXDatabase, scaleValueRes, scaleValueString);
      XrmPutStringResource(&accessXDatabase, decimalPointsRes, 
                           decimalPointsString);
    }

   if ((fname = ResolveResourceFileName()) == NULL) {
      XtManageChild(saveErrDialog);
      return;
   }
   fileDatabase = XrmGetFileDatabase(fname);

   XrmCombineDatabase(accessXDatabase, &fileDatabase, True);
   XrmPutFileDatabase(fileDatabase, fname);

} /* SaveSettingsToFile */

/************************************************************************/
/*									*/
/* StoreSettingsWindowToDatabase					*/
/*									*/
/************************************************************************/
#if NeedFunctionPrototypes
void StoreSettingsWindowToDatabase(void)
#else
void StoreSettingsWindowToDatabase()
#endif
{
    int i, scaleValue;
    short decimalPoints;
    Arg argList[2];
    char scaleValueString[32], decimalPointsString[32];
    char scaleValueRes[256], decimalPointsRes[256];
   
    settingsWindowDatabase = NULL;

    for (i = SETTINGS_TOGGLE_WIDGETS_MIN; i<=SETTINGS_TOGGLE_WIDGETS_MAX; i++) {
       if (XmToggleButtonGadgetGetState(widgets[i])) {
         XrmPutStringResource(&settingsWindowDatabase, resStrings[i], "True");
       }
       else {
         XrmPutStringResource(&settingsWindowDatabase, resStrings[i], "False");
       }
    }

    for (i = SCALE_WIDGETS_MIN; i <= SCALE_WIDGETS_MAX; i++) {
      if (i == TIME_OUT_SCL) { /* special case the time out scale here */
         continue;
      }
      XtSetArg(argList[0], XmNvalue, &scaleValue);
      XtSetArg(argList[1], XmNdecimalPoints, &decimalPoints);
      XtGetValues(widgets[i], argList, 2);

      sprintf(scaleValueString, "%d", scaleValue);
      sprintf(decimalPointsString, "%d", decimalPoints);

      sprintf(scaleValueRes, "%s.%s", resStrings[i], "value");
      sprintf(decimalPointsRes, "%s.%s", resStrings[i], "decimalPoints");

      XrmPutStringResource(&settingsWindowDatabase, scaleValueRes,
			 scaleValueString);
      XrmPutStringResource(&settingsWindowDatabase, decimalPointsRes, 
                           decimalPointsString);
    }

} /* StoreSettingsWindowToDatabase */

/************************************************************************/
/*									*/
/* RestoreSettingsWindowFromDatabase					*/
/*									*/
/************************************************************************/
#if NeedFunctionPrototypes
void RestoreSettingsWindowFromDatabase(void)
#else
void RestoreSettingsWindowFromDatabase()
#endif
{
   int i, value;
   short decimalPoints;
   char *res, classValueString[256], classDecimalPointsString[256];
   XrmValue resourceValue;
   Arg argList[2];

   for (i = SETTINGS_TOGGLE_WIDGETS_MIN; i<=SETTINGS_TOGGLE_WIDGETS_MAX; i++) {
      XrmGetResource(settingsWindowDatabase, resStrings[i], classStrings[i],
                     &res, &resourceValue);
      if (strcmp(resourceValue.addr, "True") == 0) {
         XmToggleButtonGadgetSetState(widgets[i], True, False);
      }
      else {
         XmToggleButtonGadgetSetState(widgets[i], False, False);
      }
   }

   for (i = SCALE_WIDGETS_MIN; i <= SCALE_WIDGETS_MAX; i++)  {
      if (i == TIME_OUT_SCL) {  /* special case the time out scale */
         continue;
      }
      sprintf(classValueString, "%s.value", resStrings[i]);
      sprintf(classDecimalPointsString, "%s.decimalPoints", resStrings[i]);

      XrmGetResource(settingsWindowDatabase, classValueString, classStrings[i],
                     &res, &resourceValue); 
      value = atoi(resourceValue.addr);
      XrmGetResource(settingsWindowDatabase, classDecimalPointsString,
                     classStrings[i], &res, &resourceValue);
      decimalPoints = atoi(resourceValue.addr);

      XtSetArg(argList[0], XmNvalue, value);
      XtSetArg(argList[1], XmNdecimalPoints, decimalPoints);
      XtSetValues(widgets[i], argList, 2);
   }

} /* RestoreSettingsWindowFromDatabase */

/************************************************************************/
/*									*/
/* DisplayStatusDialogsIfNeeded						*/
/*									*/
/************************************************************************/
#if NeedFunctionPrototypes
void DisplayStatusDialogsIfNeeded(void)
#else
void DisplayStatusDialogsIfNeeded()
#endif
{
  if (!options.automaticPopup)
      return;
  
  if (XmToggleButtonGetState(widgets[STICKY_KEYS_TGL])) {
     CreateAndMapStickyStatusWindow();
  }

  if (XmToggleButtonGetState(widgets[MOUSE_KEYS_TGL])) {
     CreateAndMapMouseStatusWindow();
  }

} /* DisplayStatusDialogsIfNeeded */

/************************************************************************/
/*									*/
/* InitializeInterface							*/
/*									*/
/************************************************************************/
#if NeedFunctionPrototypes
void InitializeInterface(unsigned int	argc, 
			 char		*argv[])
#else
void InitializeInterface(argc,argv)
    unsigned int	argc;
    char		*argv[];
#endif
{
    Arg 	argList[3];
    int 	n;
    Widget 	mainWindow,foo;
    Pixmap      bitmap;
    
    
    /* Initialize the toolkit and Mrm */
    MrmInitialize();
    topLevel = XtAppInitialize(&appContext, ACCESSX_CLASS, optionDesc,
		XtNumber(optionDesc), (int *)&argc, argv, fallbackResources,
		NULL, 0);
    
    XtGetApplicationResources(topLevel, (XtPointer)&options, resources,
		XtNumber(resources), NULL, 0);

    dpy = XtDisplay(topLevel);
    
    /* Find which extension to use */
    XKBExtension = InitXkb(dpy) ? 1 : 0;

    /* Initialize widget array to all NULLS */
    for (n = 0; n < NUM_WIDGETS; n++) {
	widgets[n] = NULL;
    }

    bitmap = XCreatePixmapFromBitmapData(XtDisplay(topLevel),
                RootWindowOfScreen(XtScreen(topLevel)), (char *)accessXIcon_bits,
                accessXIcon_width, accessXIcon_height, 1, 0, 1);

    XtSetArg(argList[0], XmNallowShellResize, True);
    XtSetArg(argList[1], XmNiconPixmap, bitmap);
    if (options.iconifyMain) {
       XtSetArg(argList[2], XmNinitialState, IconicState);
    }
    else {
       XtSetArg(argList[2], XmNinitialState, NormalState);
    }
    XtSetValues(topLevel,argList,3);

    /* Open up the UID database and fetch/manage the main window */
    if (MrmOpenHierarchy(dbFilenameNum, dbFilenameVec, NULL, &mrmHierarchy)
	!=MrmSUCCESS) {
	printf("Could not open hierarchy.\n");
	exit(1);
    }
    
    MrmRegisterNames(regList, regListNum);
    MrmFetchWidget(mrmHierarchy, "AccessXMainWindow", topLevel,
		&mainWindow, &dummyClass);
    SpaceAndSizeButtons(&widgets[SETTINGS_BTN],1);
    XtManageChild(mainWindow);

    MrmFetchWidget(mrmHierarchy, "HelpDialog", topLevel, &helpDialog,
		   &dummyClass);
    SpaceAndSizeButtons(&widgets[CLOSE_HELP_BTN],1);

    MrmFetchWidget(mrmHierarchy, "HelpErrorDialog", topLevel, &helpErrDialog,
                   &dummyClass);
    MrmFetchWidget(mrmHierarchy, "HelpErrorBox", topLevel, &helpErrBox,
                   &dummyClass);
   
    MrmFetchWidget(mrmHierarchy, "SettingsDialog", topLevel, &settingsDialog,
                   &dummyClass);
    SpaceAndSizeButtons(&widgets[SETTINGS_OK_BTN],5);

    n = 0;
    XtSetArg (argList[n], XmNtransientFor, NULL); n++;
    XtSetArg (argList[n], XmNwindowGroup, XtUnspecifiedWindowGroup); n++;
    stickyTopLevel = XmCreateDialogShell(topLevel,
                 "stickyTopLevel", argList, n);

    MrmFetchWidget(mrmHierarchy, "StickyKeysStatusDialog", 
     			stickyTopLevel, &statusStickyKeysDialog, &dummyClass);

    n = 0;
    XtSetArg (argList[n], XmNtransientFor, NULL); n++;
    XtSetArg (argList[n], XmNwindowGroup, XtUnspecifiedWindowGroup); n++;
    mouseTopLevel = XmCreateDialogShell(topLevel,
                 "mouseTopLevel", argList, n);

    MrmFetchWidget(mrmHierarchy, "MouseKeysStatusDialog", mouseTopLevel,
		      &statusMouseKeysDialog, &dummyClass);

    
    MrmFetchWidget(mrmHierarchy, "SaveDoneDialog", topLevel, &saveDoneDialog,
                   &dummyClass);
    MrmFetchWidget(mrmHierarchy, "SaveDoneBox", saveDoneDialog,
                   &saveDoneBox, &dummyClass);
 
    MrmFetchWidget(mrmHierarchy, "SaveErrorDialog", topLevel, &saveErrDialog,
                   &dummyClass);
    MrmFetchWidget(mrmHierarchy, "SaveErrorBox", saveErrDialog, &saveErrBox,
                   &dummyClass);

    MrmFetchWidget(mrmHierarchy, "LoadDoneDialog", topLevel, &loadDoneDialog,
                   &dummyClass);
    MrmFetchWidget(mrmHierarchy, "LoadDoneBox", loadDoneDialog, &loadDoneBox,
                   &dummyClass);

    MrmFetchWidget(mrmHierarchy, "LoadErrorDialog", topLevel, &loadErrDialog,
                   &dummyClass);
    MrmFetchWidget(mrmHierarchy, "LoadErrorBox", loadErrDialog, &loadErrBox,
                   &dummyClass);

    /* Realize the topLevel widget and Initialize the AccessX extension.
     */
    XtRealizeWidget(topLevel);

    foo = XmMessageBoxGetChild(helpErrBox, XmDIALOG_CANCEL_BUTTON);
    XtUnmanageChild(XmMessageBoxGetChild(helpErrBox, XmDIALOG_CANCEL_BUTTON));
    XtUnmanageChild(XmMessageBoxGetChild(helpErrBox, XmDIALOG_HELP_BUTTON));
    XtUnmanageChild(XmMessageBoxGetChild(saveDoneBox, XmDIALOG_CANCEL_BUTTON));
    XtUnmanageChild(XmMessageBoxGetChild(saveDoneBox, XmDIALOG_HELP_BUTTON));
    XtUnmanageChild(XmMessageBoxGetChild(saveErrBox, XmDIALOG_CANCEL_BUTTON));
    XtUnmanageChild(XmMessageBoxGetChild(saveErrBox, XmDIALOG_HELP_BUTTON));
    XtUnmanageChild(XmMessageBoxGetChild(loadDoneBox, XmDIALOG_CANCEL_BUTTON));
    XtUnmanageChild(XmMessageBoxGetChild(loadDoneBox, XmDIALOG_HELP_BUTTON));
    XtUnmanageChild(XmMessageBoxGetChild(loadErrBox, XmDIALOG_CANCEL_BUTTON));
    XtUnmanageChild(XmMessageBoxGetChild(loadErrBox, XmDIALOG_HELP_BUTTON));

    MrmFetchLiteral(mrmHierarchy, "StickyString", dpy,
                    (XtPointer *)&stickyKeysString, &dummyClass);
    MrmFetchLiteral(mrmHierarchy, "MouseString", dpy,
                    (XtPointer *)&mouseKeysString, &dummyClass);

    MrmFetchLiteral(mrmHierarchy, "ShiftString", dpy,
		    (XtPointer *)&shiftString, &dummyClass);
    MrmFetchLiteral(mrmHierarchy, "ShiftEmptyString", dpy,
                    (XtPointer *)&shiftEmptyString, &dummyClass);

    MrmFetchLiteral(mrmHierarchy, "ControlString", dpy,
                    (XtPointer *)&controlString, &dummyClass);
    MrmFetchLiteral(mrmHierarchy, "ControlEmptyString", dpy,
                    (XtPointer *)&controlEmptyString, &dummyClass);

    MrmFetchLiteral(mrmHierarchy, "Mod1String", dpy,
                    (XtPointer *)&mod1String, &dummyClass);
    MrmFetchLiteral(mrmHierarchy, "Mod1EmptyString", dpy,
                    (XtPointer *)&mod1EmptyString, &dummyClass);

    MrmFetchLiteral(mrmHierarchy, "Mod2String", dpy,
                    (XtPointer *)&mod2String, &dummyClass);
    MrmFetchLiteral(mrmHierarchy, "Mod2EmptyString", dpy,
                    (XtPointer *)&mod2EmptyString, &dummyClass);

    MrmFetchLiteral(mrmHierarchy, "Mod3String", dpy,
                    (XtPointer *)&mod3String, &dummyClass);
    MrmFetchLiteral(mrmHierarchy, "Mod3EmptyString", dpy,
                    (XtPointer *)&mod3EmptyString, &dummyClass);

    MrmFetchLiteral(mrmHierarchy, "Mod4String", dpy,
                    (XtPointer *)&mod4String, &dummyClass);
    MrmFetchLiteral(mrmHierarchy, "Mod4EmptyString", dpy,
                    (XtPointer *)&mod4EmptyString, &dummyClass);

    MrmFetchLiteral(mrmHierarchy, "Mod5String", dpy,
                    (XtPointer *)&mod5String, &dummyClass);
    MrmFetchLiteral(mrmHierarchy, "Mod5EmptyString", dpy,
                    (XtPointer *)&mod5EmptyString, &dummyClass);

    MrmFetchLiteral(mrmHierarchy, "MB1String", dpy,
                    (XtPointer *)&mb1String, &dummyClass);
    MrmFetchLiteral(mrmHierarchy, "MB1EmptyString", dpy,
                    (XtPointer *)&mb1EmptyString, &dummyClass);

    MrmFetchLiteral(mrmHierarchy, "MB2String", dpy,
                    (XtPointer *)&mb2String, &dummyClass);
    MrmFetchLiteral(mrmHierarchy, "MB2EmptyString", dpy,
                    (XtPointer *)&mb2EmptyString, &dummyClass);

    MrmFetchLiteral(mrmHierarchy, "MB3String", dpy,
                    (XtPointer *)&mb3String, &dummyClass);
    MrmFetchLiteral(mrmHierarchy, "MB3EmptyString", dpy,
                    (XtPointer *)&mb3EmptyString, &dummyClass);

    MrmFetchLiteral(mrmHierarchy, "MB4String", dpy,
                    (XtPointer *)&mb4String, &dummyClass);
    MrmFetchLiteral(mrmHierarchy, "MB4EmptyString", dpy,
                    (XtPointer *)&mb4EmptyString, &dummyClass);

    MrmFetchLiteral(mrmHierarchy, "MB5String", dpy,
                    (XtPointer *)&mb5String, &dummyClass);
    MrmFetchLiteral(mrmHierarchy, "MB5EmptyString", dpy,
                    (XtPointer *)&mb5EmptyString, &dummyClass);

    MrmFetchLiteral(mrmHierarchy, "HelpWindowString", dpy,
                    (XtPointer *)&helpWindowString, &dummyClass);

    /* Initialize the accessx extention */
    if(!XKBExtension)
    {
	accessXClient.eventHandler = AccessXEventHandler;
	XAccessXInit(dpy, &accessXClient);
	XAccessXSelectInput(dpy,&accessXClient,True);
    }
	
    if (options.useServer) {
	SetViewFromState();
    }
    else {
	SetStateFromView();
    }
	
    DisplayStatusDialogsIfNeeded();

} /* InitializeInterface */

/************************************************************************/
/*									*/
/*  XkbEventHandler	 						*/
/*									*/
/*  DESCRIPTION:							*/
/*									*/
/*      Handles events generated by the Xkb server extension.		*/
/*									*/
/************************************************************************/
Boolean XkbEventHandler(XEvent *event)
{
    XkbEvent *xkbEv = (XkbEvent *) event;

    switch(xkbEv->any.xkb_type)
    {
	case XkbStateNotify:
	    SetStickyStatusViewFromState();
	    SetMouseStatusViewFromState();
	    break;
	
	case XkbControlsNotify:
	    SetViewFromState();
	    SetMouseStatusViewFromState();
	    break;
	
	default: break;
    }

    return True;
    
} /* XkbEventHandler */

/************************************************************************/
/*									*/
/* InitXkb								*/
/*									*/
/************************************************************************/
Boolean InitXkb(Display *theDisplay)
{
    int	opcode,errorBase,major,minor;

    if (!XkbQueryExtension(theDisplay,
			   &opcode,
			   &xkbEventBase,
			   &errorBase,
			   &major,
			   &minor))
	return False;

    if (!XkbUseExtension(theDisplay,&major,&minor))
	return False;

    XkbSelectEvents(theDisplay,
                    XkbUseCoreKbd,
                    XkbAllEventsMask,
                    XkbAllEventsMask);

    XtSetEventDispatcher(theDisplay,
                         xkbEventBase+XkbEventCode,
                         XkbEventHandler);


    return True;
    
} /* InitXkb */
/************************************************************************/
/*									*/
/* main									*/
/*									*/
/************************************************************************/
#if NeedFunctionPrototypes
int main( int	argc, 
	  char		*argv[])
#else
int main(argc, argv)
    int	argc;
    char		*argv[];
#endif
{
    char *uidpathstr = "UIDPATH=/usr/share/X11/locale/%L/accessx/accessx.uid:/usr/share/X11/locale/C/accessx/accessx.uid";
    char *xfilesearchpathstr = "XFILESEARCHPATH=/usr/dt/app-defaults/%L/%N:/usr/dt/app-defaults/C/%N:/usr/share/X11/app-defaults/%L/%N:/usr/share/X11/app-defaults/C/%N";
    char *tmpstr;

    if ((tmpstr = getenv("UIDPATH")) == NULL) {
        (void)putenv(uidpathstr);
    }

    if ((tmpstr = getenv("XFILESEARCHPATH")) == NULL) {
        (void)putenv(xfilesearchpathstr);
    }

    /* set locale */
    XtSetLanguageProc((XtAppContext)NULL, (XtLanguageProc)NULL, (XtPointer)NULL);
    
    /* Initialize the Interface */
    InitializeInterface(argc, argv);

    /* Automatically load the users settings */
    LoadSettingsFromFile();

    /* First try initalizing XKB, if that fails then try the old AccessX extension. */
    if(XKBExtension)
	XtAppMainLoop(appContext);
    else
	XAccessXAppMainLoop(appContext, &accessXClient);

    return(0L);
}
