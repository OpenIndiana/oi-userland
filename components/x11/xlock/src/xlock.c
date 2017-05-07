/*
 * Copyright (c) 1988, 2015, Oracle and/or its affiliates. All rights reserved.
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
/*
 * xlock.c - X11 client to lock a display and show a screen saver.
 *
 * Copyright (c) 1988-91 by Patrick J. Naughton.
 *
 * Permission to use, copy, modify, and distribute this software and its
 * documentation for any purpose and without fee is hereby granted,
 * provided that the above copyright notice appear in all copies and that
 * both that copyright notice and this permission notice appear in
 * supporting documentation.
 *
 * This file is provided AS IS with no warranties of any kind.  The author
 * shall have no liability with respect to the infringement of copyrights,
 * trade secrets or any patents by this file or any part thereof.  In no
 * event will the author be liable for any lost revenue or profits or
 * other special, indirect and consequential damages.
 *
 * Comments and additions should be sent to the author:
 *
 *		       naughton@eng.sun.com
 *
 *		       Patrick J. Naughton
 *		       MS 10-20
 *		       Sun Laboritories, Inc.
 *		       2550 Garcia Ave
 *		       Mountain View, CA  94043
 *
 * Revision History:
 * 
 * 24-Jun-91: make foreground and background color get used on mono.
 * 24-May-91: added -usefirst.
 * 16-May-91: added pyro and random modes.
 *	      ripped big comment block out of all other files.
 * 08-Jan-91: fix some problems with password entry.
 *	      removed renicing code.
 * 29-Oct-90: added cast to XFree() arg.
 *	      added volume arg to call to XBell().
 * 28-Oct-90: center prompt screen.
 *	      make sure Xlib input buffer does not use up all of swap.
 *	      make displayed text come from resource file for better I18N.
 *	      add backward compatible signal handlers for pre 4.1 machines.
 * 31-Aug-90: added blank mode.
 *	      added swarm mode.
 *	      moved usleep() and seconds() out to usleep.c.
 *	      added SVR4 defines to xlock.h
 * 29-Jul-90: added support for multiple screens to be locked by one xlock.
 *	      moved global defines to xlock.h
 *	      removed use of allowsig().
 * 07-Jul-90: reworked commandline args and resources to use Xrm.
 *	      moved resource processing out to resource.c
 * 02-Jul-90: reworked colors to not use dynamic colormap.
 * 23-May-90: added autoraise when obscured.
 * 15-Apr-90: added hostent alias searching for host authentication.
 * 18-Feb-90: added SunOS3.5 fix.
 *	      changed -mono -> -color, and -saver -> -lock.
 *	      allow non-locking screensavers to display on remote machine.
 *	      added -echokeys to disable echoing of '?'s on input.
 *	      cleaned up all of the parameters and defaults.
 * 20-Dec-89: added -xhost to allow access control list to be left alone.
 *	      added -screensaver (don't disable screen saver) for the paranoid.
 *	      Moved seconds() here from all of the display mode source files.
 *	      Fixed bug with calling XUngrabHosts() in finish().
 * 19-Dec-89: Fixed bug in GrabPointer.
 *	      Changed fontname to XLFD style.
 * 23-Sep-89: Added fix to allow local hostname:0 as a display.
 *	      Put empty case for Enter/Leave events.
 *	      Moved colormap installation later in startup.
 * 20-Sep-89: Linted and made -saver mode grab the keyboard and mouse.
 *	      Replaced SunView code for life mode with Jim Graham's version,
 *		so I could contrib it without legal problems.
 *	      Sent to expo for X11R4 contrib.
 * 19-Sep-89: Added '?'s on input.
 * 27-Mar-89: Added -qix mode.
 *	      Fixed GContext->GC.
 * 20-Mar-89: Added backup font (fixed) if XQueryLoadFont() fails.
 *	      Changed default font to lucida-sans-24.
 * 08-Mar-89: Added -nice, -mode and -display, built vector for life and hop.
 * 24-Feb-89: Replaced hopalong display with life display from SunView1.
 * 22-Feb-89: Added fix for color servers with n < 8 planes.
 * 16-Feb-89: Updated calling conventions for XCreateHsbColormap();
 *	      Added -count for number of iterations per color.
 *	      Fixed defaulting mechanism.
 *	      Ripped out VMS hacks.
 *	      Sent to expo for X11R3 contrib.
 * 15-Feb-89: Changed default font to pellucida-sans-18.
 * 20-Jan-89: Added -verbose and fixed usage message.
 * 19-Jan-89: Fixed monochrome gc bug.
 * 16-Dec-88: Added SunView style password prompting.
 * 19-Sep-88: Changed -color to -mono. (default is color on color displays).
 *	      Added -saver option. (just do display... don't lock.)
 * 31-Aug-88: Added -time option.
 *	      Removed code for fractals to separate file for modularity.
 *	      Added signal handler to restore host access.
 *	      Installs dynamic colormap with a Hue Ramp.
 *	      If grabs fail then exit.
 *	      Added VMS Hacks. (password 'iwiwuu').
 *	      Sent to expo for X11R2 contrib.
 * 08-Jun-88: Fixed root password pointer problem and changed PASSLENGTH to 20.
 * 20-May-88: Added -root to allow root to unlock.
 * 12-Apr-88: Added root password override.
 *	      Added screen saver override.
 *	      Removed XGrabServer/XUngrabServer.
 *	      Added access control handling instead.
 * 01-Apr-88: Added XGrabServer/XUngrabServer for more security.
 * 30-Mar-88: Removed startup password requirement.
 *	      Removed cursor to avoid phosphor burn.
 * 27-Mar-88: Rotate fractal by 45 degrees clockwise.
 * 24-Mar-88: Added color support. [-color]
 *	      wrote the man page.
 * 23-Mar-88: Added HOPALONG routines from Scientific American Sept. 86 p. 14.
 *	      added password requirement for invokation
 *	      removed option for command line password
 *	      added requirement for display to be "unix:0".
 * 22-Mar-88: Recieved Walter Milliken's comp.windows.x posting.
 *
 */

#include <stdio.h>
#include <signal.h>
#include <siginfo.h>
#include <string.h>
#include <stdarg.h>
#include <crypt.h>
#include <shadow.h>
#include <pwd.h>
#ifdef __sun
# include <note.h>
#else
# define NOTE(s)  /* ignored */
#endif

#include "xlock.h"
#include <X11/cursorfont.h>
#include <X11/Xatom.h>

#ifdef USE_PAM
# include <security/pam_appl.h>
# ifndef XLOCK_PAM_SERVICE
#  define XLOCK_PAM_SERVICE "xlock"
# endif
# define PAM_ERROR_PRINT(pamfunc)	\
 if (verbose) { \
   fprintf(stderr, "%s: %s failure: %s\n", ProgramName, pamfunc, \
     pam_strerror(pamh, pam_error)); \
 }
# ifdef sun
#  include <deflt.h>
# endif
#endif

char       *ProgramName;	/* argv[0] */
perscreen   Scr[MAXSCREENS];
Display    *dsp = NULL;		/* server display connection */
int         screen;		/* current screen */
void        (*callback) (Window win) = NULL;
void        (*init) (Window win) = NULL;

static int  screens;		/* number of screens */
static Window win[MAXSCREENS];	/* window used to cover screen */
static Window icon[MAXSCREENS];	/* window used during password typein */
static Window root[MAXSCREENS];	/* convenience pointer to the root window */
static GC   textgc[MAXSCREENS];	/* graphics context used for text rendering */
static XColor fgcol[MAXSCREENS];/* used for text rendering */
static XColor bgcol[MAXSCREENS];/* background of text screen */
XColor ssblack[MAXSCREENS];/* black color for screen saver screen */
XColor sswhite[MAXSCREENS];/* white color for screen saver screen */
static int  iconx[MAXSCREENS];	/* location of left edge of icon */
static int  icony[MAXSCREENS];	/* location of top edge of icon */
static Cursor mycursor;		/* blank cursor */
static Cursor passwdcursor;	/* cursor used in getPassword */
static Pixmap lockc;
static Pixmap lockm;		/* pixmaps for cursor and mask */
static char no_bits[] = {0};	/* dummy array for the blank cursor */
static int  passx;		/* position of the ?'s */
static int  passy;
static XFontStruct *font;
static int  sstimeout;		/* screen saver parameters */
static int  ssinterval;
static int  ssblanking;
static int  ssexposures;

static char buffer[PAM_MAX_RESP_SIZE];
static Bool reallyechokeys = False; /* Echo real keys instead of ?'s */
static Bool stoptryingfornow = False;

#define FALLBACK_FONTNAME	"fixed"
#define ICONW			64
#define ICONH			64

#ifdef DEBUG
#define WIDTH WidthOfScreen(scr) - 100
#define HEIGHT HeightOfScreen(scr) - 100
#define CWMASK CWBackPixel | CWEventMask | CWColormap
#else
#define WIDTH WidthOfScreen(scr)
#define HEIGHT HeightOfScreen(scr)
#define CWMASK CWOverrideRedirect | CWBackPixel | CWEventMask | CWColormap
#endif

#define AllPointerEventMask \
	(ButtonPressMask | ButtonReleaseMask | \
	EnterWindowMask | LeaveWindowMask | \
	PointerMotionMask | PointerMotionHintMask | \
	Button1MotionMask | Button2MotionMask | \
	Button3MotionMask | Button4MotionMask | \
	Button5MotionMask | ButtonMotionMask | \
	KeymapStateMask)

void
error(const char *format, ...)
{
    va_list args;

    fprintf(stderr, "%s: ", ProgramName);
    va_start(args, format);
    vfprintf(stderr, format, args);
    va_end(args);
    exit(1);
}

/*
 * Server access control support.
 */

static XHostAddress *XHosts;	/* the list of "friendly" client machines */
static int  HostAccessCount;	/* the number of machines in XHosts */
static Bool HostAccessState;	/* whether or not we even look at the list */

static void
XGrabHosts(Display    *dsp)
{
    XHosts = XListHosts(dsp, &HostAccessCount, &HostAccessState);
    if (XHosts)
	XRemoveHosts(dsp, XHosts, HostAccessCount);
    XEnableAccessControl(dsp);
}

static void
XUngrabHosts(Display    *dsp)
{
    if (XHosts) {
	XAddHosts(dsp, XHosts, HostAccessCount);
	XFree(XHosts);
    }
    if (HostAccessState == False)
	XDisableAccessControl(dsp);
}


/*
 * Simple wrapper to get an asynchronous grab on the keyboard and mouse.
 * If either grab fails, we sleep for one second and try again since some
 * window manager might have had the mouse grabbed to drive the menu choice
 * that picked "Lock Screen..".  If either one fails the second time we print
 * an error message and exit.
 */
static void
GrabKeyboardAndMouse(void)
{
    Status      status;

    status = XGrabKeyboard(dsp, win[0], True,
			   GrabModeAsync, GrabModeAsync, CurrentTime);
    if (status != GrabSuccess) {
	sleep(1);
	status = XGrabKeyboard(dsp, win[0], True,
			       GrabModeAsync, GrabModeAsync, CurrentTime);

	if (status != GrabSuccess)
	    error("couldn't grab keyboard! (%d)\n", status);
    }
    status = XGrabPointer(dsp, win[0], True, AllPointerEventMask,
			  GrabModeAsync, GrabModeAsync, None, mycursor,
			  CurrentTime);
    if (status != GrabSuccess) {
	sleep(1);
	status = XGrabPointer(dsp, win[0], True, AllPointerEventMask,
			      GrabModeAsync, GrabModeAsync, None, mycursor,
			      CurrentTime);

	if (status != GrabSuccess)
	    error("couldn't grab pointer! (%d)\n", status);
    }
}


/*
 * Assuming that we already have an asynch grab on the pointer,
 * just grab it again with a new cursor shape and ignore the return code.
 */
static void
XChangeGrabbedCursor(Cursor cursor)
{
#ifndef DEBUG
    (void) XGrabPointer(dsp, win[0], True, AllPointerEventMask,
		    GrabModeAsync, GrabModeAsync, None, cursor, CurrentTime);
#endif
}


/*
 * Restore all grabs, reset screensaver, restore colormap, close connection.
 */
static void
finish(void)
{
    XSync(dsp, False);
    if (!nolock && !allowaccess)
	XUngrabHosts(dsp);
    XUngrabPointer(dsp, CurrentTime);
    XUngrabKeyboard(dsp, CurrentTime);
    if (!enablesaver)
	XSetScreenSaver(dsp, sstimeout, ssinterval, ssblanking, ssexposures);
    XFlush(dsp);
    XCloseDisplay(dsp);
}


static volatile int sigcaught = 0;

static void
sigcatch(int sig, siginfo_t *info, void *context)
{
    NOTE(ARGUNUSED(context))
    /* note that we were caught, but don't try to re-enter Xlib from here */
    sigcaught = sig;
    psiginfo(info, ProgramName);
}

static void _X_NORETURN
sigfinish(void)
{
    finish();
    error("caught terminate signal %d.\nAccess control list restored.\n",
	  sigcaught);
}


static int
ReadXString(
    char       *s,
    unsigned int slen
    )
{
    XEvent      event;
    char        keystr[20];
    char        c;
    int         i;
    int         bp;
    int         len;
    int         thisscreen = screen;
    char	pwbuf[PAM_MAX_RESP_SIZE];

    for (screen = 0; screen < screens; screen++)
	if (thisscreen == screen)
	    init(icon[screen]);
	else
	    init(win[screen]);
    bp = 0;
    *s = 0;
    /*CONSTCOND*/
    while (True) {
	long lasteventtime = seconds();
	while (!XPending(dsp)) {
	    if (sigcaught)
		sigfinish();
	    for (screen = 0; screen < screens; screen++)
		if (thisscreen == screen)
		    callback(icon[screen]);
		else
		    callback(win[screen]);
	    XFlush(dsp);
	    usleep((useconds_t) delay);
	    if (seconds() - lasteventtime > (long) timeout) {
		screen = thisscreen;
		stoptryingfornow = True;
		return 1;
	    }
	}
	screen = thisscreen;
	XNextEvent(dsp, &event);
	if (sigcaught)
	    sigfinish();
	switch (event.type) {
	case KeyPress:
	    len = XLookupString((XKeyEvent *) & event, keystr, 20, NULL, NULL);
	    for (i = 0; i < len; i++) {
		c = keystr[i];
		switch (c) {
		case 8:	/* ^H */
		case 127:	/* DEL */
		    if (bp > 0)
			bp--;
		    break;
		case 10:	/* ^J */
		case 13:	/* ^M */
		    s[bp] = '\0';
	            /*
	             * eat all events if there are more than enough pending... this
	             * keeps the Xlib event buffer from growing larger than all
	             * available memory and crashing xlock.
	             */
	            if (XPending(dsp) > 100) {	/* 100 is arbitrarily big enough */
		        register Status status;
		        do {
		            status = XCheckMaskEvent(dsp,
				              KeyPressMask | KeyReleaseMask, &event);
		        } while (status);
		        XBell(dsp, 100);
	            }
		    return 0;
		case 21:	/* ^U */
		    bp = 0;
		    break;
		default:
		    s[bp] = c;
		    if (bp < slen - 1)
			bp++;
		    else
			XSync(dsp, True);	/* flush input buffer */
		}
	    }
	    XSetForeground(dsp, Scr[screen].gc, bgcol[screen].pixel);
	    if (echokeys || reallyechokeys) {
		if (reallyechokeys) {
		    memcpy(pwbuf, s, slen);
		} else {
		    memset(pwbuf, '?', slen);
		} 

		XFillRectangle(dsp, win[screen], Scr[screen].gc,
			       passx, passy - font->ascent,
			       XTextWidth(font, pwbuf, (int) slen),
			       font->ascent + font->descent);
		XDrawString(dsp, win[screen], textgc[screen],
			    passx, passy, pwbuf, bp);
	    }
	    /*
	     * eat all events if there are more than enough pending... this
	     * keeps the Xlib event buffer from growing larger than all
	     * available memory and crashing xlock.
	     */
	    if (XPending(dsp) > 100) {	/* 100 is arbitrarily big enough */
		register Status status;
		do {
		    status = XCheckMaskEvent(dsp,
				      KeyPressMask | KeyReleaseMask, &event);
		} while (status);
		XBell(dsp, 100);
	    }
	    break;

	case ButtonPress:
	    if (((XButtonEvent *) & event)->window == icon[screen]) {
		stoptryingfornow = True;
		return 1;
	    }
	    break;

	case VisibilityNotify:
	    if (event.xvisibility.state != VisibilityUnobscured) {
#ifndef DEBUG
		XRaiseWindow(dsp, win[screen]);
#endif
		s[0] = '\0';
		return 1;
	    }
	    break;

	case KeymapNotify:
	case KeyRelease:
	case ButtonRelease:
	case MotionNotify:
	case LeaveNotify:
	case EnterNotify:
	    break;

	default:
	    fprintf(stderr, "%s: unexpected event: %d\n",
		    ProgramName, event.type);
	    break;
	}
    }
    /* NOTREACHED */
}


static int
CheckPassword(void)
{
    struct spwd *rspw, *uspw;
    struct passwd *upw;
    const char  *user;

    rspw = getspnam("root");

    upw = (struct passwd *)getpwuid(getuid());
    if (upw == NULL) { 	/* should not pass NULL to getspnam  */
	user = "";
    }
    else {
	user = upw->pw_name;
    }
    uspw = getspnam(user);
    if (!uspw) {
	if (allowroot) {
		if (!rspw)
			return(1);
		else
			return(0);
	}
	return(1);
    }

    return(0);
}


static void passwordPrompt(const char *prompt)
{
    int         y, left;
    Screen     *scr = ScreenOfDisplay(dsp, screen);

    left = iconx[screen] + ICONW + font->max_bounds.width;
    y = icony[screen] + font->ascent + font->ascent + font->descent + 2;

    XSetForeground(dsp, Scr[screen].gc, bgcol[screen].pixel);

    XFillRectangle(dsp, win[screen], Scr[screen].gc,
		       left, y - font->ascent, WIDTH - left, 
      		       font->ascent + font->descent + 2);

    XDrawString(dsp, win[screen], textgc[screen],
		left, y, prompt, (int) strlen(prompt));
    XDrawString(dsp, win[screen], textgc[screen],
		left + 1, y, prompt, (int) strlen(prompt));

    passx = left + 1 + XTextWidth(font, prompt, (int) strlen(prompt))
	+ XTextWidth(font, " ", 1);
    passy = y;
}

static void displayTextInfo(const char *infoMsg)
{
    int         y;
    Screen     *scr = ScreenOfDisplay(dsp, screen);

    y = icony[screen] + ICONH + font->ascent + 2;

    XSetForeground(dsp, Scr[screen].gc, bgcol[screen].pixel);

    XFillRectangle(dsp, win[screen], Scr[screen].gc,
		       iconx[screen], y - font->ascent,
		       WIDTH - iconx[screen], 
      		       font->ascent + font->descent + 2);

    XDrawString(dsp, win[screen], textgc[screen],
		iconx[screen], y, infoMsg, (int) strlen(infoMsg));
}

#ifdef USE_PAM
static int pamconv(int num_msg, struct pam_message **msg,
              struct pam_response **response, void *appdata_ptr)
{
    NOTE(ARGUNUSED(appdata_ptr))
    int i;
    int status = PAM_SUCCESS;
    
    struct pam_message      *m;
    struct pam_response     *r;

    *response = calloc(num_msg, sizeof (struct pam_response));
    if (*response == NULL)
	return (PAM_BUF_ERR);

    m = *msg;
    r = *response;

    for (i = 0; i < num_msg; i++ , m++ , r++) {
#ifdef DEBUG
	if (verbose) {
	    fprintf(stderr, "pam_msg: %d: '%s'\n", m->msg_style, m->msg);
	}
#endif
	switch (m->msg_style) {
	  case PAM_ERROR_MSG:
	  case PAM_TEXT_INFO:
	    displayTextInfo(m->msg);
	    break;

          case PAM_PROMPT_ECHO_ON:
	    reallyechokeys = True; 
	    /* FALLTHRU */
          case PAM_PROMPT_ECHO_OFF:
	    passwordPrompt(m->msg);
	    if (ReadXString(buffer, PAM_MAX_RESP_SIZE)) {
		/* timeout or other error */
		status = PAM_CONV_ERR;
		i = num_msg;
	    } else {
		r->resp = strdup(buffer);
		if (r->resp == NULL) {
		    status = PAM_BUF_ERR;
		    i = num_msg;
		}
#ifdef DEBUG
		if (verbose) {
		    fprintf(stderr, "pam_resp: '%s'\n", r->resp);
		}
#endif
	    }
	    reallyechokeys = False;
	    break;

	  default:
	    if (verbose) {
		fprintf(stderr, "%s: Unknown PAM msg_style: %d\n",
		  ProgramName, m->msg_style);
	    }
	}
    }
    if (status != PAM_SUCCESS) {
	/* free responses */
	r = *response;
	for (i = 0; i < num_msg; i++, r++) {
	    if (r->resp)
		free(r->resp);
	}
	free(*response);
	*response = NULL;
    }
    return status;
}
#endif

#ifdef	sun
#include <syslog.h>
#include <bsm/adt.h>
#include <bsm/adt_event.h>


/*
 * audit_lock - audit entry to screenlock
 *
 *	Entry	Process running with appropriate privilege to generate
 *			audit records and real uid of the user.
 *
 *	Exit	ADT_screenlock audit record written.
 */
static void
audit_lock(void)
{
	adt_session_data_t	*ah;	/* audit session handle */
	adt_event_data_t	*event;	/* audit event handle */
 
	/* Audit start of screen lock -- equivalent to logout ;-) */
	
	if (adt_start_session(&ah, NULL, ADT_USE_PROC_DATA) != 0) {

		syslog(LOG_AUTH | LOG_ALERT, "adt_start_session: %m");
		return;
	}
	if ((event = adt_alloc_event(ah, ADT_screenlock)) == NULL) {
	
		syslog(LOG_AUTH | LOG_ALERT,
		    "adt_alloc_event(ADT_screenlock): %m");
	} else {
		if (adt_put_event(event, ADT_SUCCESS, ADT_SUCCESS) != 0) {

			syslog(LOG_AUTH | LOG_ALERT,
			    "adt_put_event(ADT_screenlock): %m");
		}
		adt_free_event(event);
	}
	(void) adt_end_session(ah);
}


/*
 * audit_unlock - audit screen unlock
 *
 *	Entry	Process running with appropriate privilege to generate
 *			audit records and real uid of the user.
 *		pam_status = PAM error code; reason for failure.
 *
 *	Exit	ADT_screenunlock audit record written.
 */
static void
audit_unlock(int pam_status)
{
	adt_session_data_t	*ah;	/* audit session handle */
	adt_event_data_t	*event;	/* audit event handle */

	if (adt_start_session(&ah, NULL, ADT_USE_PROC_DATA) != 0) {

		syslog(LOG_AUTH | LOG_ALERT,
		    "adt_start_session(ADT_screenunlock): %m");
		return;
	}
	if ((event = adt_alloc_event(ah, ADT_screenunlock)) == NULL) {
	
		syslog(LOG_AUTH | LOG_ALERT,
		    "adt_alloc_event(ADT_screenunlock): %m");
	} else {
		if (adt_put_event(event,
		    pam_status == PAM_SUCCESS ? ADT_SUCCESS : ADT_FAILURE,
		    pam_status == PAM_SUCCESS ? ADT_SUCCESS : ADT_FAIL_PAM +
		    pam_status) != 0) {

			syslog(LOG_AUTH | LOG_ALERT,
			    "adt_put_event(ADT_screenunlock(%s): %m",
			    pam_strerror(NULL, pam_status));
		}
		adt_free_event(event);
	}
	(void) adt_end_session(ah);
}


/*
 * audit_passwd - audit password change
 *	Entry	Process running with appropriate privilege to generate
 *			audit records and real uid of the user.
 *		pam_status = PAM error code; reason for failure.
 *
 *	Exit	ADT_passwd audit record written.
 */
static void
audit_passwd(int pam_status)
{
	adt_session_data_t	*ah;	/* audit session handle */
	adt_event_data_t	*event;	/* audit event handle */

	if (adt_start_session(&ah, NULL, ADT_USE_PROC_DATA) != 0) {

		syslog(LOG_AUTH | LOG_ALERT,
		    "adt_start_session(ADT_passwd): %m");
		return;
	}
	if ((event = adt_alloc_event(ah, ADT_passwd)) == NULL) {
	
		syslog(LOG_AUTH | LOG_ALERT,
		    "adt_alloc_event(ADT_passwd): %m");
	} else {
		if (adt_put_event(event,
		    pam_status == PAM_SUCCESS ? ADT_SUCCESS : ADT_FAILURE,
		    pam_status == PAM_SUCCESS ? ADT_SUCCESS : ADT_FAIL_PAM +
		    pam_status) != 0) {

			syslog(LOG_AUTH | LOG_ALERT,
			    "adt_put_event(ADT_passwd(%s): %m",
			    pam_strerror(NULL, pam_status));
		}
		adt_free_event(event);
	}
	(void) adt_end_session(ah);
}
#endif	/* sun */

static int
getPassword(void)
{
    char       *userpass = NULL;
    char       *rootpass = NULL;
    XWindowAttributes xgwa;
    int         y, left, done;
    struct spwd *rspw, *uspw;
    char       *suserpass = NULL;
    char       *srootpass = NULL;
    const char *user;
    struct passwd *rpw, *upw;
#ifdef USE_PAM
    pam_handle_t *pamh = NULL;
    struct pam_conv pc;
    Bool	use_pam = True;
    int		pam_error;
    int		pam_flags = 0;
#endif
    const char *authErrMsg = text_invalid;  

    rpw = getpwuid(0);
    if (rpw) {
       user = rpw->pw_name;
       rootpass = strdup(rpw->pw_passwd);

       rspw = getspnam(user);
       if (rspw && rspw->sp_pwdp)
	   srootpass = strdup(rspw->sp_pwdp);
    }

    upw = getpwuid(getuid());
    if (upw) {
       user = upw->pw_name;
       userpass = strdup(upw->pw_passwd);

       uspw = getspnam(user);
       if (uspw && uspw->sp_pwdp)
	   suserpass = strdup(uspw->sp_pwdp);
    }
    else 
       user = "";

#ifdef USE_PAM
    pc.conv = pamconv;
    
    pam_error = pam_start(XLOCK_PAM_SERVICE, user, &pc, &pamh);
    if (pam_error != PAM_SUCCESS) {
	use_pam = False;
	PAM_ERROR_PRINT("pam_start");
    } else {
#ifdef sun
	/* Check /etc/default/login to see if we should add
	   PAM_DISALLOW_NULL_AUTHTOK to pam_flags */
	if (defopen("/etc/default/login") == 0) {
	    const char *ptr;

	    int flags = defcntl(DC_GETFLAGS, 0);
	    TURNOFF(flags, DC_CASE);
	    (void) defcntl(DC_SETFLAGS, flags);

	    if ((ptr = defread("PASSREQ=")) != NULL &&
	      strcasecmp("YES", ptr) == 0) {
		pam_flags |= PAM_DISALLOW_NULL_AUTHTOK;
	    }

	    (void) defopen(NULL); /* close current file */
	}

#endif

	/* Disable user password non-PAM authentication */
	if (userpass) {
	    memset(userpass, 0, strlen(userpass));
	    free(userpass);
	    userpass = NULL;
	}
	if (suserpass) {
	    memset(suserpass, 0, strlen(suserpass));
	    free(suserpass);
	    suserpass = NULL;
	}
    }
#endif /* USE_PAM */

    XGetWindowAttributes(dsp, win[screen], &xgwa);

    XChangeGrabbedCursor(passwdcursor);

    XSetForeground(dsp, Scr[screen].gc, bgcol[screen].pixel);
    XFillRectangle(dsp, win[screen], Scr[screen].gc,
		   0, 0, xgwa.width, xgwa.height);

    XMapWindow(dsp, icon[screen]);
    XRaiseWindow(dsp, icon[screen]);

    left = iconx[screen] + ICONW + font->max_bounds.width;
    y = icony[screen] + font->ascent;

    XDrawString(dsp, win[screen], textgc[screen],
		left, y, text_name, (int) strlen(text_name));
    XDrawString(dsp, win[screen], textgc[screen],
		left + 1, y, text_name, (int) strlen(text_name));
    XDrawString(dsp, win[screen], textgc[screen],
		left + XTextWidth(font, text_name, (int) strlen(text_name)), y,
		user, (int) strlen(user));

    y = icony[screen] - (font->descent + 2);

    XDrawString(dsp, win[screen], textgc[screen],
		iconx[screen], y, text_info, (int) strlen(text_info));

    passwordPrompt(text_pass);

    XFlush(dsp);

    y = icony[screen] + ICONH + font->ascent + 2
      + font->ascent + font->descent + 2;

    done = False;
    stoptryingfornow = False;
    while (!done) {
	if (sigcaught)
	    sigfinish();
#ifdef USE_PAM
	if (use_pam) {

	    pam_error = pam_authenticate(pamh, pam_flags);
	    if (pam_error == PAM_SUCCESS) {
		const char *pam_error_from = "pam_acct_mgmt";

		pam_error = pam_acct_mgmt(pamh, pam_flags);

		if (pam_error == PAM_NEW_AUTHTOK_REQD) {
		    do {
			pam_error = pam_chauthtok(pamh,
						  PAM_CHANGE_EXPIRED_AUTHTOK);
		    } while (pam_error == PAM_AUTHTOK_ERR || 
		      pam_error == PAM_TRY_AGAIN);
		    pam_error_from = "pam_chauthtok";
#ifdef	sun
		    audit_passwd(pam_error);
#endif	/* sun */
		}

		if (pam_error == PAM_SUCCESS) {
		    pam_error = pam_setcred(pamh,PAM_REFRESH_CRED);  
		    if (pam_error != PAM_SUCCESS) {
			PAM_ERROR_PRINT("pam_setcred(PAM_REFRESH_CRED)");
		    } else {
			done = True;
		    }
		} else {
#ifdef	sun
    		    audit_unlock(pam_error);
#endif	/* sun */
		    PAM_ERROR_PRINT(pam_error_from);
		}
	    } else if (stoptryingfornow) {
		break;
	    } else {
#ifdef	sun
    		audit_unlock(pam_error);
#endif	/* sun */
		PAM_ERROR_PRINT("pam_authenticate");
	    }

	    if (pam_error != PAM_SUCCESS) {
		authErrMsg = pam_strerror(pamh, pam_error);
	    }
	} else if (ReadXString(buffer, PAM_MAX_RESP_SIZE))
	    break;
#endif

	/*
	 *  This section gets a little messy.  In SYSV, the number of
	 *  cases to handle increases because of the existence of the
	 *  shadow file.  There are also a number of cases that need
	 *  to be dealt with where either root or user passwords are
	 *  nil.  Hopefully the code below is easy enough to follow.
	 */

	if (userpass) {
	    if (*userpass == NULL) {
		done = (*buffer == NULL);
	    } else {
		done = (!strcmp(crypt(buffer, userpass), userpass));
	    }
	}
	if (!done && suserpass) {
	    if (*suserpass == NULL) {
		done = (*buffer == NULL);
	    } else {
		done = (!strcmp(crypt(buffer, suserpass), suserpass));
	    }
	}
	if (!done && allowroot) {
	    if (srootpass) {
		if (*srootpass == NULL) {
		    done = (*buffer == NULL);
		} else {
		    done = (!strcmp(crypt(buffer, srootpass), srootpass));
		}
	    }
	    if (!done && rootpass) {
		if (*rootpass == NULL) {
		    done = (*buffer == NULL);
		} else {
		    done = (!strcmp(crypt(buffer, rootpass), rootpass));
		}
	    }
        }

	/* clear plaintext password so you can't grunge around /dev/kmem */
	memset(buffer, 0, sizeof(buffer));

	displayTextInfo(text_valid);

	if (done) {
	    /* clear encrypted passwords just in case */
	    if (rootpass) {
		memset(rootpass, 0, strlen(rootpass));
		free(rootpass);  
	    }
	    if (userpass) {
		memset(userpass, 0, strlen(userpass));
		free(userpass);
	    }
	    if (srootpass) {
		memset(srootpass, 0, strlen(srootpass));
		free(srootpass);  
	    }
	    if (suserpass) {
		memset(suserpass, 0, strlen(suserpass));
		free(suserpass);
	    }
#ifdef USE_PAM
#ifdef	sun
	    audit_unlock(pam_error);
#endif	/* sun */
	    pam_end(pamh, pam_error);
#endif
	    return 0;
	} else {
	    XSync(dsp, True);	/* flush input buffer */
	    sleep(1);
	    
	    displayTextInfo(authErrMsg);

	    if (echokeys || reallyechokeys)	/* erase old echo */
		XFillRectangle(dsp, win[screen], Scr[screen].gc,
			       passx, passy - font->ascent,
			       xgwa.width - passx,
			       font->ascent + font->descent);
	}
    }
    /* clear encrypted passwords just in case */
    if (rootpass) {
	memset(rootpass, 0, strlen(rootpass));
	free(rootpass);  
    }
    if (userpass) {
	memset(userpass, 0, strlen(userpass));
	free(userpass);
    }
    if (srootpass) {
	memset(srootpass, 0, strlen(srootpass));
	free(srootpass);  
    }
    if (suserpass) {
	memset(suserpass, 0, strlen(suserpass));
	free(suserpass);
    }

#ifdef USE_PAM
    pam_end(pamh, pam_error);
#endif
    XChangeGrabbedCursor(mycursor);
    XUnmapWindow(dsp, icon[screen]);
    return 1;
}

static void
justDisplay(void)
{
    XEvent      event;

    for (screen = 0; screen < screens; screen++)
	init(win[screen]);
    do {
	while (!XPending(dsp)) {
	    if (sigcaught)
		sigfinish();
	    for (screen = 0; screen < screens; screen++)
		callback(win[screen]);
	    XFlush(dsp);
	    usleep((useconds_t) delay);
	}
	XNextEvent(dsp, &event);
	if (sigcaught)
	    sigfinish();
#ifndef DEBUG
	if (event.type == VisibilityNotify)
	    XRaiseWindow(dsp, event.xany.window);
#endif
    } while (event.type != ButtonPress && event.type != KeyPress);
    for (screen = 0; screen < screens; screen++)
	if (event.xbutton.root == RootWindow(dsp, screen))
	    break;
    if (usefirst)
	XPutBackEvent(dsp, &event);
}


static void
lockDisplay(void)
{
    if (!allowaccess) {
	sigset_t    oldsigmask;
	sigset_t    newsigmask;
	struct sigaction sigact;

	sigemptyset(&newsigmask);
	sigaddset(&newsigmask, SIGHUP);
	sigaddset(&newsigmask, SIGINT);
	sigaddset(&newsigmask, SIGQUIT);
	sigaddset(&newsigmask, SIGTERM);
	sigprocmask(SIG_BLOCK, &newsigmask, &oldsigmask);

	sigact.sa_sigaction = sigcatch;
	sigact.sa_mask = newsigmask;
	sigact.sa_flags = SA_SIGINFO;

	sigaction(SIGHUP, &sigact, NULL);
	sigaction(SIGINT, &sigact, NULL);
	sigaction(SIGQUIT, &sigact, NULL);
	sigaction(SIGTERM, &sigact, NULL);

	XGrabHosts(dsp);

	sigprocmask(SIG_SETMASK, &oldsigmask, &oldsigmask);
    }
#ifdef	sun
    audit_lock();
#endif	/* sun */
    do {
	justDisplay();
    } while (getPassword());
}


int
main(
    int         argc,
    char       *argv[]
    )
{
    XSetWindowAttributes xswa;
    XGCValues   xgcv;

    ProgramName = strrchr(argv[0], '/');
    if (ProgramName)
	ProgramName++;
    else
	ProgramName = argv[0];

    srandom((uint_t) time((long *) 0));	/* random mode needs the seed set. */

    GetResources(argc, argv);

    CheckResources();

    font = XLoadQueryFont(dsp, fontname);
    if (font == NULL) {
	fprintf(stderr, "%s: can't find font: %s, using %s...\n",
		ProgramName, fontname, FALLBACK_FONTNAME);
	font = XLoadQueryFont(dsp, FALLBACK_FONTNAME);
	if (font == NULL)
	    error("can't even find %s!!!\n", FALLBACK_FONTNAME);
    }

    if (CheckPassword()) {
	error("can't get the user password. Exiting ...\n"
	"\tYou need to run xlock in setuid root mode on your local machine.\n"
	"\tContact your system administrator.\n");
    }
	
    screens = ScreenCount(dsp);
    if (screens > MAXSCREENS)
	error("can only support %d screens.\n", MAXSCREENS);
    for (screen = 0; screen < screens; screen++) {
	XColor      tmp;
	Screen     *scr = ScreenOfDisplay(dsp, screen);
	Visual 	    *vis = XDefaultVisual(dsp, screen);
	Colormap    cmap;
	root[screen] = RootWindowOfScreen(scr);

	cmap = XCreateColormap(dsp, root[screen], vis, AllocNone);

	XAllocNamedColor(dsp, cmap, "White", &sswhite[screen], &tmp);
	XAllocNamedColor(dsp, cmap, "Black", &ssblack[screen], &tmp);

	if (mono || CellsOfScreen(scr) == 2) {
 	    if (!XAllocNamedColor(dsp, cmap, background,
 				  &bgcol[screen], &tmp)) {
 		XAllocNamedColor(dsp, cmap, "White", &bgcol[screen], &tmp);
 	    }
 	    if (!XAllocNamedColor(dsp, cmap, foreground,
 				  &fgcol[screen], &tmp)) {
 		XAllocNamedColor(dsp, cmap, "Black", &fgcol[screen], &tmp);
 	    }
	    Scr[screen].pixels[0] = fgcol[screen].pixel;
	    Scr[screen].pixels[1] = bgcol[screen].pixel;
	    Scr[screen].npixels = 2;
	} else {
	    int         colorcount = NUMCOLORS;
	    u_char      red[NUMCOLORS];
	    u_char      green[NUMCOLORS];
	    u_char      blue[NUMCOLORS];
	    int         i;

	    if (!XAllocNamedColor(dsp, cmap, background,
				  &bgcol[screen], &tmp)) {
		fprintf(stderr, "couldn't allocate: %s\n", background);
		XAllocNamedColor(dsp, cmap, "White", &bgcol[screen], &tmp);
	    }
	    if (!XAllocNamedColor(dsp, cmap, foreground,
				  &fgcol[screen], &tmp)) {
		fprintf(stderr, "couldn't allocate: %s\n", foreground);
		XAllocNamedColor(dsp, cmap, "Black", &fgcol[screen], &tmp);
	    }
	    hsbramp(0.0, saturation, 1.0, 1.0, saturation, 1.0, colorcount,
		    red, green, blue);
	    Scr[screen].npixels = 0;
	    for (i = 0; i < colorcount; i++) {
		XColor      xcolor = {
		    .red = (unsigned short) (red[i] << 8),
		    .green = (unsigned short) (green[i] << 8),
		    .blue = (unsigned short) (blue[i] << 8),
		    .flags = DoRed | DoGreen | DoBlue
		};

		if (!XAllocColor(dsp, cmap, &xcolor))
		    break;

		Scr[screen].pixels[i] = xcolor.pixel;
		Scr[screen].npixels++;
	    }
	    if (verbose)
		fprintf(stderr, "%d pixels allocated\n", Scr[screen].npixels);
	}

	xswa.override_redirect = True;
	xswa.background_pixel = ssblack[screen].pixel;
	xswa.event_mask = KeyPressMask | ButtonPressMask | VisibilityChangeMask;
	xswa.colormap = cmap;		/* In DEBUG mode, we do not see this */

	win[screen] = XCreateWindow(dsp, root[screen], 0, 0, WIDTH, HEIGHT, 0,
				 CopyFromParent, InputOutput, CopyFromParent,
				    CWMASK, &xswa);

#ifdef DEBUG
	{
	    XWMHints    xwmh;

	    xwmh.flags = InputHint;
	    xwmh.input = True;
	    XChangeProperty(dsp, win[screen],
			    XA_WM_HINTS, XA_WM_HINTS, 32, PropModeReplace,
			(unsigned char *) &xwmh, sizeof(xwmh) / sizeof(int));
	}
#endif
	
  	iconx[screen] = (DisplayWidth(dsp, screen) -
  		 XTextWidth(font, text_info, (int) strlen(text_info))) / 2;
	
  	icony[screen] = DisplayHeight(dsp, screen) / 6;
	
 	xswa.border_pixel = fgcol[screen].pixel;
 	xswa.background_pixel = bgcol[screen].pixel;
 	xswa.event_mask = ButtonPressMask;
	xswa.colormap = cmap;		/* In DEBUG mode, we do not see this */

#define CIMASK CWBorderPixel | CWBackPixel | CWEventMask | CWColormap
  	icon[screen] = XCreateWindow(dsp, win[screen],
  				     iconx[screen], icony[screen],
 				     ICONW, ICONH, 1, CopyFromParent,
  				     InputOutput, CopyFromParent,
 				     CIMASK, &xswa);
  
	XMapWindow(dsp, win[screen]);
	XRaiseWindow(dsp, win[screen]);
	XInstallColormap(dsp, cmap);

	xgcv.foreground = sswhite[screen].pixel;
	xgcv.background = ssblack[screen].pixel;
	Scr[screen].gc = XCreateGC(dsp, win[screen],
				   GCForeground | GCBackground, &xgcv);

	xgcv.foreground = fgcol[screen].pixel;
	xgcv.background = bgcol[screen].pixel;
	xgcv.font = font->fid;
	textgc[screen] = XCreateGC(dsp, win[screen],
				GCFont | GCForeground | GCBackground, &xgcv);
    }
    lockc = XCreateBitmapFromData(dsp, root[0], no_bits, 1, 1);
    lockm = XCreateBitmapFromData(dsp, root[0], no_bits, 1, 1);
    mycursor = XCreatePixmapCursor(dsp, lockc, lockm,
				   &fgcol[screen], &bgcol[screen], 0, 0);
    passwdcursor = XCreateFontCursor(dsp, XC_left_ptr);
    XFreePixmap(dsp, lockc);
    XFreePixmap(dsp, lockm);


    if (!enablesaver) {
	XGetScreenSaver(dsp, &sstimeout, &ssinterval,
			&ssblanking, &ssexposures);
	XSetScreenSaver(dsp, 0, 0, 0, 0);	/* disable screen saver */
    }
#ifndef DEBUG
    GrabKeyboardAndMouse();
#endif

    nice(nicelevel);

    if (nolock)
	justDisplay();
    else
	lockDisplay();

    finish();

    return 0;
}
