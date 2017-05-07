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

/************************************************************************/
/*									*/
/* AccessX	   						        */
/* 									*/
/* 	This module provides the client library functions necessary for	*/
/*	an AccessX client to communicate with the AccessX server        */
/*	extension.							*/
/*									*/
/* Revision History:							*/
/*									*/
/*	11-Jun-1993	WDW & MEN					*/
/*			Develop sample implementation.			*/
/*									*/
/************************************************************************/
#include <stdio.h>
#define NEED_EVENTS
#define NEED_REPLIES
#include <X11/Xlibint.h>
#include <X11/Xproto.h>
#include <X11/keysym.h>
#include <X11/extensions/extutil.h>
#include <X11/extensions/Xext.h>
#include <X11/Intrinsic.h>
#include "AccessXproto.h"
#include "AccessXlibint.h"

#ifndef WORD64
#define _XRead32(dpy, data, len) _XRead((dpy), (char *)(data), (len))
#endif

static int	XAccessXCloseDisplay(Display *dpy, XExtCodes *codes);
static Bool	XAccessXWireToEvent(Display *dpy, XEvent *event, xEvent *wire);
static Status	XAccessXEventToWire(Display *dpy, XEvent *event, xEvent *wire);

XExtensionInfo	*accessXExtensionInfo = NULL;
XExtensionHooks	accessXExtensionHooks = 
{
    NULL,			/* create_gc		*/
    NULL,			/* copy_gc		*/
    NULL,			/* flush_gc		*/
    NULL,			/* free_gc		*/
    NULL,			/* create_font		*/
    NULL,			/* free_font		*/
    XAccessXCloseDisplay,	/* close_display	*/
    XAccessXWireToEvent,	/* wire_to_event	*/
    NULL,			/* event_to_wire	*/
    NULL,			/* error		*/
    NULL			/* error_string		*/
};

XEXT_GENERATE_FIND_DISPLAY(XAccessXFindDisplay,
			   accessXExtensionInfo,
			   AccessXExtName,
			   &accessXExtensionHooks,
			   AccessXNumEvents,
			   NULL)

XEXT_GENERATE_CLOSE_DISPLAY(XAccessXCloseDisplay,
			    accessXExtensionInfo)

/************************************************************************/
/*									*/
/* XAccessXWireToEvent - takes a raw event off the wire an converts it	*/
/*			 into an Xlib event structure.			*/
/*									*/
/************************************************************************/
#if NeedFunctionPrototypes
Bool XAccessXWireToEvent(Display *dpy,
			 XEvent  *libevent,
			 xEvent  *netevent)
#else
Bool XAccessXWireToEvent(dpy,libevent,netevent)
    Display *dpy;
    XEvent  *libevent;
    xEvent  *netevent;
#endif
{
    XExtDisplayInfo *info = XAccessXFindDisplay(dpy);
    XAccessXEvent *ev = (XAccessXEvent *) libevent;
    xAccessXEvent *event = (xAccessXEvent *) netevent;
    
    XextCheckExtension(dpy,info,AccessXExtName,False);
    
    ev->type		= event->type & 0x7f;
    ev->serial		= _XSetLastRequestRead(dpy,(xGenericReply *)netevent);
    ev->send_event	= ((event->type & 0x80) != 0);
    ev->display		= dpy;
    ev->detail		= event->detail;
    ev->keyOrButton	= event->keyOrButton;
    ev->modifier	= event->modifier;
    ev->control		= event->control;
    ev->gain		= event->gain;
    
    return True;
    
} /* XAccessXWireToEvent */

/************************************************************************/
/*									*/
/*  XAccessXQueryExtension						*/
/*									*/
/*  DESCRIPTION:							*/
/*									*/
/*      This routine returns TRUE if the AccessX extension is 		*/
/*	available on the given display.					*/
/*									*/
/************************************************************************/
#if NeedFunctionPrototypes
Bool XAccessXQueryExtension(Display 			*dpy,
			    AccessXClientContextRec	*accessXClient)
#else
Bool XAccessXQueryExtension(dpy,accessXClient)
    Display 			*dpy;
    AccessXClientContextRec	*accessXClient;
#endif
{
    XExtDisplayInfo	*info = XAccessXFindDisplay(dpy);
    
    if (XextHasExtension(info))
    {
	accessXClient->majorOpcode = (CARD16) (info->codes->major_opcode);
	accessXClient->eventBase = (CARD16) (info->codes->first_event);
	accessXClient->errorBase = (CARD16) (info->codes->first_error);
	return True;
    }
    else
        return False;
        
} /* XAccessXQueryExtension */

/************************************************************************/
/*									*/
/*  XAccessXQueryVersion						*/
/*									*/
/*  DESCRIPTION:							*/
/*									*/
/*      This routine sends an X_AccessXQueryVersion request to the 	*/
/*      AccessX extension on the server, and then waits for a reply.	*/
/*									*/
/************************************************************************/
#if NeedFunctionPrototypes
int XAccessXQueryVersion(Display 			*dpy,
			 AccessXClientContextRec	*accessXClient,
			 CARD8				*majorVersion,
			 CARD8				*minorVersion)
#else
int XAccessXQueryVersion(dpy,accessXClient,majorVersion,minorVersion)
    Display 			*dpy;
    AccessXClientContextRec	*accessXClient;
    CARD8   			*majorVersion;
    CARD8   			*minorVersion;
#endif
{
    int				status = True;
    xAccessXQueryVersionReq	*req;
    xAccessXQueryVersionReply	rep;
    
    /* Send the request and wait for the reply.
     */
    LockDisplay(dpy);
    ExtGetReq(accessXClient->majorOpcode,AccessXQueryVersion,req);
    status = _XReply(dpy,(xReply *)&rep,0,xTrue);
    
    SyncHandle();
    UnlockDisplay(dpy);
    
    *majorVersion = rep.majorVersion;
    *minorVersion = rep.minorVersion;
    
    return(status);
    
} /* XAccessXQueryVersion */

/************************************************************************/
/*									*/
/*  XAccessXSelectInput							*/
/*									*/
/*  DESCRIPTION:							*/
/*									*/
/*      This routine sends an X_AccessXSelectInput request to the 	*/
/*      AccessX extension on the server.			        */
/*									*/
/************************************************************************/
#if NeedFunctionPrototypes
void XAccessXSelectInput(Display 			*dpy,
			 AccessXClientContextRec	*accessXClient,
			 BYTE	 			enable)
#else
void XAccessXSelectInput(dpy,accessXClient,enable)
    Display 			*dpy;
    AccessXClientContextRec	*accessXClient;
    BYTE    			enable;
#endif
{
    xAccessXSelectInputReq *req;
    
    ExtGetReq(accessXClient->majorOpcode,AccessXSelectInput,req);
    req->enable = enable;
    
    XFlush(dpy);
    SyncHandle();

    return;
        
} /* XAccessXSelectInput */

/************************************************************************/
/*									*/
/*  XAccessXQueryState							*/
/*									*/
/*  DESCRIPTION:							*/
/*									*/
/*      This routine sends an X_AccessXQueryState request to the 	*/
/*      AccessX extension on the server, and then waits for a reply.	*/
/*									*/
/************************************************************************/
#if NeedFunctionPrototypes
int XAccessXQueryState(Display 			*dpy,
		       AccessXClientContextRec	*accessXClient,
		       AccessXStateRec		*accessXState)
#else
int XAccessXQueryState(dpy,accessXClient,accessXState)
    Display			*dpy;
    AccessXClientContextRec	*accessXClient;
    AccessXStateRec		*accessXState;
#endif
{
    int				status = True;
    xAccessXQueryStateReply	rep;
    xAccessXQueryStateReq	*req;
    
    /* Send the request and wait for the reply.
     */
    LockDisplay(dpy);
    ExtGetReq(accessXClient->majorOpcode,AccessXQueryState,req);
    status = _XReply(dpy,(xReply *)&rep,2,xTrue);
    
    accessXState->control = rep.control;
    accessXState->timeOutInterval = rep.timeOutInterval;
    accessXState->mouseKeysTimeToMax = rep.mouseKeysTimeToMax;
    accessXState->mouseKeysGain = rep.mouseKeysGain;
    accessXState->mouseKeysInterval = rep.mouseKeysInterval;
    accessXState->mouseKeysCtrlMask = rep.mouseKeysCtrlMask;
    accessXState->mouseKeysCtrlKeyCode = rep.mouseKeysCtrlKeyCode;
    accessXState->currentMouseButton = rep.currentMouseButton;
    accessXState->latchedModifiers = rep.latchedModifiers;
    accessXState->lockedModifiers = rep.lockedModifiers;
    accessXState->slowKeysDelay = rep.slowKeysDelay;
    accessXState->debounceDelay = rep.debounceDelay;
    accessXState->repeatKeysDelay = rep.repeatKeysDelay;
    accessXState->repeatKeysRate = rep.repeatKeysRate;

    SyncHandle();
    UnlockDisplay(dpy);
    
    return(status);
    
} /* XAccessXQueryState */

/************************************************************************/
/*									*/
/*  XAccessXConfigure							*/
/*									*/
/*  DESCRIPTION:							*/
/*									*/
/*      This routine sends an X_AccessXConfigure request to the 	*/
/*      AccessX extension on the server.				*/
/*									*/
/************************************************************************/
#if NeedFunctionPrototypes
int XAccessXConfigure(Display 			*dpy,
		      AccessXClientContextRec	*accessXClient,
		      CARD16			mask,
		      AccessXStateRec		*accessXState)
#else
int XAccessXConfigure(dpy,accessXClient,mask,accessXState)
    Display 			*dpy;
    AccessXClientContextRec	*accessXClient;
    CARD16			mask;
    AccessXStateRec		*accessXState;
#endif
{
    int	status = True;
    xAccessXConfigureReq	*req;
    
    ExtGetReq(accessXClient->majorOpcode,AccessXConfigure,req);

    req->mask = mask;
    req->control = accessXState->control;
    req->timeOutInterval = accessXState->timeOutInterval;
    req->mouseKeysTimeToMax = accessXState->mouseKeysTimeToMax;
    req->mouseKeysGain = accessXState->mouseKeysGain;
    req->mouseKeysInterval = accessXState->mouseKeysInterval;
    req->mouseKeysCtrlMask = accessXState->mouseKeysCtrlMask;
    req->mouseKeysCtrlKeyCode = accessXState->mouseKeysCtrlKeyCode;
    req->currentMouseButton = accessXState->currentMouseButton;
    req->slowKeysDelay = accessXState->slowKeysDelay;
    req->debounceDelay = accessXState->debounceDelay;
    req->repeatKeysDelay = accessXState->repeatKeysDelay;
    req->repeatKeysRate = accessXState->repeatKeysRate;

    XFlush(dpy);
    SyncHandle();
        
    return(status);
    
} /* XAccessXConfigure */
#if 0
/************************************************************************/
/*									*/
/*  XAccessXGetMouseKeys						*/
/*									*/
/*  DESCRIPTION:							*/
/*									*/
/*      This routine sends an X_AccessXGetMouseKeys request to the 	*/
/*      AccessX extension on the server, and then waits for a reply.	*/
/*									*/
/************************************************************************/
#if NeedFunctionPrototypes
AccessXMouseKeysRec *XAccessXGetMouseKeys(Display 			*dpy,
					  AccessXClientContextRec	*accessXClient,
					  int				*numKeys)
#else
AccessXMouseKeysRec *XAccessXGetMouseKeys(dpy,accessXClient,numKeys)
    Display 			*dpy;
    AccessXClientContextRec	*accessXClient;
    int 			*numKeys;
#endif
{
    int				status = True;
    xAccessXGetMouseKeysReq	*req;
    xAccessXGetMouseKeysReply	rep;
    int				numBytes;
    AccessXMouseKeysRec		*mouseKeys = NULL;
    
    *numKeys = 0;
    
    /* Send the request and wait for the reply.
     */
    return; 	/* NOthing for now */
    LockDisplay(dpy);
    ExtGetReq(accessXClient->majorOpcode,AccessXGetMouseKeys,req);
    
    if (! _XReply(dpy,(xReply *)&rep,0,xFalse))
    {
	UnlockDisplay(dpy);
	SyncHandle();
	return (AccessXMouseKeysRec *) NULL;
    }
    
    *numKeys = rep.numKeys;
    numBytes = rep.numKeys * sizeof(AccessXMouseKeysRec);

    mouseKeys = (AccessXMouseKeysRec *) Xmalloc(numBytes);
    if (!mouseKeys)
	_XEatData(dpy,(unsigned long) numBytes);
    else
	_XRead32(dpy,(char *) mouseKeys, numBytes);
    
    SyncHandle();
    UnlockDisplay(dpy);
    
    return(mouseKeys);
    
} /* XAccessXGetMouseKeys */

/************************************************************************/
/*									*/
/*  XAccessXSetMouseKey							*/
/*									*/
/*  DESCRIPTION:							*/
/*									*/
/*      This routine sends an X_AccessXSetMouseKey request to the 	*/
/*      AccessX extension in the server.			        */
/*									*/
/************************************************************************/
#if NeedFunctionPrototypes
void XAccessXSetMouseKey(Display 			*dpy,
			 AccessXClientContextRec	*accessXClient,
			 CARD8	 			keyCode,
			 CARD8	 			action,
			 INT8	 			info1,
			 INT8	 			info2)
#else
void XAccessXSetMouseKey(dpy,accessXClient,keyCode,action,info1,info2)
    Display 			*dpy;
    AccessXClientContextRec	*accessXClient;
    CARD8   			keyCode;
    CARD8   			action;
    INT8    			info1;
    INT8    			info2;
#endif
{
    xAccessXSetMouseKeyReq *req;
    
    return;	/* Nothing for now */
    ExtGetReq(accessXClient->majorOpcode,AccessXSetMouseKey,req);

    req->keyCode = keyCode; 	/* KeyCode of key to be modified */
    req->action = action;       /* What to do if MouseKeys is on */
    req->info1 = info1;		/* button or deltax		 */
    req->info2 = info2;		/* how_many or deltay		 */
        
    XFlush(dpy);
    SyncHandle();

    return;
        
} /* XAccessXSetMouseKey */
#endif

/************************************************************************/
/*									*/
/*  XAccessXInit							*/
/*									*/
/*  DESCRIPTION:							*/
/*									*/
/*	Initialize the connection with the AccessX server extension.	*/
/*									*/
/************************************************************************/
#if NeedFunctionPrototypes
void XAccessXInit(Display 			*dpy,
		  AccessXClientContextRec	*accessXClient)
#else
void XAccessXInit(dpy,accessXClient)
    Display 			*dpy;
    AccessXClientContextRec	*accessXClient;
#endif
{
    /* Find the AccessX extension
     */
    if (!XAccessXQueryExtension(dpy,accessXClient))
    {
        fprintf(stderr,"Could not query %s extension\n",
		AccessXExtName);
        exit(1L);
    }

} /* XAccessXInit */

/************************************************************************/
/*									*/
/*  XAccessXMainLoop							*/
/*									*/
/************************************************************************/
#if NeedFunctionPrototypes
void XAccessXAppMainLoop(XtAppContext 			appContext,
			 AccessXClientContextRec	*accessXClient)
#else
void XAccessXAppMainLoop(appContext,accessXClient)
    XtAppContext 		appContext;
    AccessXClientContextRec	*accessXClient;
#endif
{
    XEvent event;

    for (;;) 
    {
	/* The AccessX extension will spit out only one event type,
	 * and this the type accessXEventBase.  The intrinsics do not
	 * have a graceful way to allow extensions to add events to
	 * XtAppMainLoop, so it is necessary to write our own which
	 * checks for accessXEventBase.
	 */
	XtAppNextEvent(appContext,&event);
	if ((event.type == accessXClient->eventBase) &&
	    (accessXClient->eventHandler))
	    (*accessXClient->eventHandler)((XAccessXEvent *)&event);
	else
	    XtDispatchEvent(&event);
    }
} /* XAccessXAppMainLoop */
