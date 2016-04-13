/* Copyright (c) 1990, 2015, Oracle and/or its affiliates. All rights reserved.
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

/*-
 *-----------------------------------------------------------------------
 * XGrabWin.c - X11 Client Side interface to Window Grabber.
 * 
 * This code uses the standard R3 extension mechanism for sending the grab or
 * ungrab window requests. If the extension isn't present, it uses the un-used
 * protocol if the server is from Sun.
 *
 * The global state is only relevant to one display. Multiple displays
 * will have to be implemented via arrays of global data.
 *-----------------------------------------------------------------------
 */
#define	NEED_REPLIES
#define NEED_EVENTS

#include <string.h>
#include <unistd.h>

#include <X11/Xlibint.h>	/* from usr.lib/libX11 */
#include <X11/Xproto.h>		/* from usr.lib/libX11/include */
#include <X11/extensions/dgast.h>

#include <sys/socket.h>
#include <netinet/in.h>  
#include <sys/types.h>
				/* Unused requests	*/
#define X_GrabWindow	125	/* should be in Xproto.h */
#define X_UnGrabWindow	126	/* just before X_NoOperation */

#define BadCookie	0

static int X_WxExtensionCode;

static int WxError (Display *dpy,int mc);

static enum {
  NOT_INITIALIZED,
  USE_EXTENSION,
  USE_EXTRA_PROTOCOL,
  NOT_LOCAL_HOST
  } WxInitialized = NOT_INITIALIZED;

static void
Initialize(Display *dpy)
{
  int tmp;

  if (dpy->display_name[0] != ':') {
    char hostname[64];

    gethostname(hostname,64);
    if (strncmp("unix",dpy->display_name,4) &&
	strncmp("localhost",dpy->display_name,9) &&
	strncmp(hostname,dpy->display_name,strlen(hostname))) {
      WxInitialized = NOT_LOCAL_HOST;
      return;
    }
  }

  if (XQueryExtension(dpy, "SunWindowGrabber",&X_WxExtensionCode,
			      &tmp, &tmp))
    WxInitialized = USE_EXTENSION;
  else if (!strcmp(dpy->vendor,"X11/NeWS - Sun Microsystems Inc."))
    WxInitialized = USE_EXTRA_PROTOCOL;
}

int 
XGrabWindow(
    Display *dpy,
    Window win)
{
  xResourceReq *req;
  xGenericReply rep;

  if (WxInitialized == NOT_INITIALIZED)
    Initialize(dpy);

  switch (WxInitialized) {
  case USE_EXTENSION:
    LockDisplay(dpy);
    GetResReq(WxExtensionCode, win, req);
    req->pad = X_WxGrab;
    (void) _XReply(dpy, (xReply *) &rep, 0, xFalse);
    UnlockDisplay(dpy);
    SyncHandle();
    return rep.data00;
  case USE_EXTRA_PROTOCOL:
    LockDisplay(dpy);
    GetResReq(GrabWindow, win, req);
    (void) _XReply(dpy, (xReply *) &rep, 0, xFalse);
    UnlockDisplay(dpy);
    SyncHandle();
    return (rep.data00);	/* GrabToken */
  case NOT_INITIALIZED:
     WxError(dpy,X_WxGrab);
  case NOT_LOCAL_HOST:
    return BadCookie;
  }
  return BadImplementation;
}

int
XUnGrabWindow(
    Display *dpy,
    Window win)
{
  xResourceReq *req;
  xGenericReply rep;

  if (WxInitialized == NOT_INITIALIZED)
    Initialize(dpy);

  switch (WxInitialized) {
  case USE_EXTENSION:
    LockDisplay(dpy);
    GetResReq(WxExtensionCode, win, req);
    req->pad = X_WxUnGrab;
    (void) _XReply(dpy, (xReply *) &rep, 0, xFalse);
    UnlockDisplay(dpy);
    SyncHandle();
    return rep.data00;		/* Status */
  case USE_EXTRA_PROTOCOL:
    LockDisplay(dpy);
    GetResReq(UnGrabWindow, win, req);
    (void) _XReply(dpy, (xReply *) &rep, 0, xFalse);
    UnlockDisplay(dpy);
    SyncHandle();
    return (rep.data00);	/* Status */
  case NOT_INITIALIZED:
    WxError(dpy,X_WxUnGrab);
  case NOT_LOCAL_HOST:
    return BadCookie;
  }
  return BadImplementation;
}


int 
XGrabColormap(
    Display *dpy,
    Colormap cmap)
{
  xResourceReq *req;
  xGenericReply rep;

  if (WxInitialized == NOT_INITIALIZED)
    Initialize(dpy);

  switch (WxInitialized) {
  case USE_EXTENSION:
    LockDisplay(dpy);
    GetResReq(WxExtensionCode, cmap, req);
    req->pad = X_WxGrabColormap;
    (void) _XReply(dpy, (xReply *) &rep, 0, xFalse);
    UnlockDisplay(dpy);
    SyncHandle();
    return rep.data00;
  case USE_EXTRA_PROTOCOL:
  case NOT_INITIALIZED:
    WxError(dpy,X_WxGrabColormap);
  case NOT_LOCAL_HOST:
    return BadCookie;
  }
  return BadImplementation;
}

int
XUnGrabColormap(
    Display *dpy,
    Colormap cmap)
{
  xResourceReq *req;
  xGenericReply rep;

  if (WxInitialized == NOT_INITIALIZED)
    Initialize(dpy);

  switch (WxInitialized) {
  case USE_EXTENSION:
    LockDisplay(dpy);
    GetResReq(WxExtensionCode, cmap, req);
    req->pad = X_WxUnGrabColormap;
    (void) _XReply(dpy, (xReply *) &rep, 0, xFalse);
    UnlockDisplay(dpy);
    SyncHandle();
    return rep.data00;		/* Status */
  case USE_EXTRA_PROTOCOL:
  case NOT_INITIALIZED:
    WxError(dpy,X_WxGrabColormap);
  case NOT_LOCAL_HOST:
    return BadCookie;
  }
  return BadImplementation;
}


int 
XGrabRetainedWindow(
    Display *dpy,
    Window win)
{
  xResourceReq *req;
  xGenericReply rep;

  if (WxInitialized == NOT_INITIALIZED)
    Initialize(dpy);

  switch (WxInitialized) {
  case USE_EXTENSION:
    LockDisplay(dpy);
    GetResReq(WxExtensionCode, win, req);
    req->pad = X_WxGrabRetained;
    (void) _XReply(dpy, (xReply *) &rep, 0, xFalse);
    UnlockDisplay(dpy);
    SyncHandle();
    return rep.data00;
  case USE_EXTRA_PROTOCOL:
  case NOT_INITIALIZED:
     WxError(dpy,X_WxGrabRetained);
  case NOT_LOCAL_HOST:
    return BadCookie;
  }
  return BadImplementation;
}

int
XUnGrabRetainedWindow(
    Display *dpy,
    Window win)
{
  xResourceReq *req;
  xGenericReply rep;

  if (WxInitialized == NOT_INITIALIZED)
    Initialize(dpy);

  switch (WxInitialized) {
  case USE_EXTENSION:
    LockDisplay(dpy);
    GetResReq(WxExtensionCode, win, req);
    req->pad = X_WxUnGrabRetained;
    (void) _XReply(dpy, (xReply *) &rep, 0, xFalse);
    UnlockDisplay(dpy);
    SyncHandle();
    return rep.data00;		/* Status */
  case USE_EXTRA_PROTOCOL:
  case NOT_INITIALIZED:
    WxError(dpy,X_WxUnGrabRetained);
  case NOT_LOCAL_HOST:
    return BadCookie;
  }
  return BadImplementation;
}


int
XGetRetainedPath(
    Display *dpy,
    Window win,
    char *path)
{
  xResourceReq *req;
  xOWGXRtndPathReply rep;

  if (WxInitialized == NOT_INITIALIZED)
    Initialize(dpy);

  switch (WxInitialized) {
  case USE_EXTENSION:
    LockDisplay(dpy);
    GetResReq(WxExtensionCode, win, req);
    req->pad = X_WxGetRetainedPath;
    (void) _XReply(dpy, (xReply *) &rep,
		   (SIZEOF(xOWGXRtndPathReply) - SIZEOF(xReply)) >> 2, xFalse);
    UnlockDisplay(dpy);
    SyncHandle();
    strcpy(path, rep.path);
    return Success;
  case USE_EXTRA_PROTOCOL:
  case NOT_INITIALIZED:
    WxError(dpy,X_WxGetRetainedPath);
  case NOT_LOCAL_HOST:
    return BadCookie;
  }
  return BadImplementation;
}





static int
WxError (
    Display *dpy,
    int mc)
{
  XErrorEvent event;

  event.display = dpy;
  event.type = X_Error;
  event.error_code = BadImplementation;
  event.request_code = 0xff;	/* Means that we were requesting an extension*/
  event.minor_code = mc;
  event.serial = dpy->request;
  if (_XErrorFunction != NULL) {
    return ((*_XErrorFunction)(dpy, &event));
  }
  exit(1);
  /*NOTREACHED*/
}
