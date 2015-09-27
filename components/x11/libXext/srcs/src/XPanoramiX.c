/* $TOG: XPanoramiX.c /main/2 1997/11/16 08:45:41 kaleb $ */
/*****************************************************************

Copyright (c) 1991, 1997 Digital Equipment Corporation, Maynard, Massachusetts.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software.

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
DIGITAL EQUIPMENT CORPORATION BE LIABLE FOR ANY CLAIM, DAMAGES, INCLUDING, 
BUT NOT LIMITED TO CONSEQUENTIAL OR INCIDENTAL DAMAGES, OR OTHER LIABILITY, 
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR 
IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

Except as contained in this notice, the name of Digital Equipment Corporation 
shall not be used in advertising or otherwise to promote the sale, use or other
dealings in this Software without prior written authorization from Digital 
Equipment Corporation.

******************************************************************/
/* Copyright (c) 1999, 2015, Oracle and/or its affiliates. All rights reserved.
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

#define NEED_EVENTS
#define NEED_REPLIES
#include <X11/Xlibint.h>
#include <X11/Xutil.h>
#include <X11/Xresource.h>
#include <X11/extensions/Xext.h>
#include <X11/extensions/extutil.h>
#include <X11/extensions/panoramiXext.h>
#include <X11/extensions/panoramiXproto.h>
#include <X11/extensions/xinerama.h>

Bool XGetXineramaInfo(Display *dpy, int screen_number, XID VirtualWID, XineramaInfo *info);

static XExtensionInfo _panoramiX_ext_info_data;
static XExtensionInfo *panoramiX_ext_info = &_panoramiX_ext_info_data;
static /* const */ char *panoramiX_extension_name = PANORAMIX_PROTOCOL_NAME;

#define PanoramiXCheckExtension(dpy,i,val) \
  XextCheckExtension (dpy, i, panoramiX_extension_name, val)
#define PanoramiXSimpleCheckExtension(dpy,i) \
  XextSimpleCheckExtension (dpy, i, panoramiX_extension_name)

static int close_display(Display *dpy, XExtCodes *codes);
static Bool wire_to_event(Display *dpy, XEvent *libevent, xEvent *netevent);
static Status event_to_wire(Display *dpy, XEvent *libevent, xEvent *netevent);
static /* const */ XExtensionHooks panoramiX_extension_hooks = {
    NULL,				/* create_gc */
    NULL,				/* copy_gc */
    NULL,				/* flush_gc */
    NULL,				/* free_gc */
    NULL,				/* create_font */
    NULL,				/* free_font */
    close_display,			/* close_display */
    NULL,				/* wire_to_event */
    NULL,				/* event_to_wire */
    NULL,				/* error */
    NULL,				/* error_string */
};

static XEXT_GENERATE_FIND_DISPLAY (find_display, panoramiX_ext_info,
				   panoramiX_extension_name, 
				   &panoramiX_extension_hooks,
				   0, NULL)

static XEXT_GENERATE_CLOSE_DISPLAY (close_display, panoramiX_ext_info)



#ifdef SUNSOFT
struct XineramaExtVersionInfo
{
    int major_vers, minor_vers;
};

/**** Code taken from xc/include/extensions/Xinerama.h in Xorg for
      compatibility with XFree86 & Xorg protocols ****/

static Bool XineramaIsActive(Display *dpy);

/* 
   Returns the number of heads and a pointer to an array of
   structures describing the position and size of the individual
   heads.  Returns NULL and number = 0 if Xinerama is not active.
  
   Returned array should be freed with XFree().
*/
typedef struct {
   int   screen_number;
   short x_org;
   short y_org;
   short width;
   short height;
} XineramaScreenInfo;

static XineramaScreenInfo * 
XineramaQueryScreens(
   Display *dpy,
   int     *number
);

#endif

/****************************************************************************
 *                                                                          *
 *			    PanoramiX public interfaces                         *
 *                                                                          *
 ****************************************************************************/

Bool XPanoramiXQueryExtension (
    Display *dpy,
    int *event_basep,
    int *error_basep)
{
    XExtDisplayInfo *info = find_display (dpy);

    if (XextHasExtension(info)) {
	*event_basep = info->codes->first_event;
	*error_basep = info->codes->first_error;
	return True;
    } else {
	return False;
    }
}


Status XPanoramiXQueryVersion(
    Display *dpy,
    int	    *major_versionp,
    int     *minor_versionp)
{
    XExtDisplayInfo *info = find_display (dpy);
    xPanoramiXQueryVersionReply	    rep;
    register xPanoramiXQueryVersionReq  *req;

#ifdef SUNSOFT
    struct XineramaExtVersionInfo	*vinfo;

    if (info->data != NULL) {
	vinfo = (struct XineramaExtVersionInfo *) info->data;
	
	*major_versionp = vinfo->major_vers;	
	*minor_versionp = vinfo->minor_vers;
	return 1;	
    }
#endif
    
    PanoramiXCheckExtension (dpy, info, 0);

    LockDisplay (dpy);
    GetReq (PanoramiXQueryVersion, req);
    req->reqType = info->codes->major_opcode;
    req->panoramiXReqType = X_PanoramiXQueryVersion;
    req->clientMajor = PANORAMIX_MAJOR_VERSION;
    req->clientMinor = PANORAMIX_MINOR_VERSION;
    if (!_XReply (dpy, (xReply *) &rep, 0, xTrue)) {
	UnlockDisplay (dpy);
	SyncHandle ();
	return 0;
    }
    *major_versionp = rep.majorVersion;
    *minor_versionp = rep.minorVersion;
#ifdef SUNSOFT /* Cache version info */
    vinfo = Xmalloc(sizeof(struct XineramaExtVersionInfo));

    if (vinfo != NULL) {
	vinfo->major_vers = rep.majorVersion;
	vinfo->minor_vers = rep.minorVersion;
	info->data = (XPointer) vinfo;
    }
#endif    
    UnlockDisplay (dpy);
    SyncHandle ();
    return 1;
}

XPanoramiXInfo *XPanoramiXAllocInfo(void)
{
	return (XPanoramiXInfo *) Xmalloc (sizeof (XPanoramiXInfo));
}

Status XPanoramiXGetState (
    Display		*dpy,
    Drawable		drawable,
    XPanoramiXInfo	*panoramiX_info)
{
    XExtDisplayInfo			*info = find_display (dpy);
    xPanoramiXGetStateReply	rep;
    register xPanoramiXGetStateReq	*req;

    PanoramiXCheckExtension (dpy, info, 0);

    LockDisplay (dpy);
    GetReq (PanoramiXGetState, req);
    req->reqType = info->codes->major_opcode;
    req->panoramiXReqType = X_PanoramiXGetState;
    req->window = drawable;
    if (!_XReply (dpy, (xReply *) &rep, 0, xTrue)) {
	UnlockDisplay (dpy);
	SyncHandle ();
	return 0;
    }
    UnlockDisplay (dpy);
    SyncHandle ();
    panoramiX_info->window = rep.window;
    panoramiX_info->State = rep.state;
    return 1;
}

Status XPanoramiXGetScreenCount (
    Display		*dpy,
    Drawable		drawable,
    XPanoramiXInfo	*panoramiX_info)
{
    XExtDisplayInfo			*info = find_display (dpy);
    xPanoramiXGetScreenCountReply	rep;
    register xPanoramiXGetScreenCountReq	*req;

    PanoramiXCheckExtension (dpy, info, 0);

    LockDisplay (dpy);
    GetReq (PanoramiXGetScreenCount, req);
    req->reqType = info->codes->major_opcode;
    req->panoramiXReqType = X_PanoramiXGetScreenCount;
    req->window = drawable;
    if (!_XReply (dpy, (xReply *) &rep, 0, xTrue)) {
	UnlockDisplay (dpy);
	SyncHandle ();
	return 0;
    }
    UnlockDisplay (dpy);
    SyncHandle ();
    panoramiX_info->window = rep.window;
    panoramiX_info->ScreenCount = rep.ScreenCount;
    return 1;
}

Status XPanoramiXGetScreenSize (
    Display		*dpy,
    Drawable		drawable,
    int			screen_num,
    XPanoramiXInfo	*panoramiX_info)
{
    XExtDisplayInfo			*info = find_display (dpy);
    xPanoramiXGetScreenSizeReply	rep;
    register xPanoramiXGetScreenSizeReq	*req;

    PanoramiXCheckExtension (dpy, info, 0);

    LockDisplay (dpy);
    GetReq (PanoramiXGetScreenSize, req);
    req->reqType = info->codes->major_opcode;
    req->panoramiXReqType = X_PanoramiXGetScreenSize;
    req->window = drawable;
    req->screen = screen_num;			/* need to define */ 
    if (!_XReply (dpy, (xReply *) &rep, 0, xTrue)) {
	UnlockDisplay (dpy);
	SyncHandle ();
	return 0;
    }
    UnlockDisplay (dpy);
    SyncHandle ();
    panoramiX_info->window = rep.window;
    panoramiX_info->screen = rep.screen;
    panoramiX_info->width =  rep.width;
    panoramiX_info->height = rep.height;
    return 1;
}


/* new api for xinerama */

Bool XineramaGetState(Display * display, int screen_number)
{
    XExtDisplayInfo	 *info = find_display (display);

    /* screen_number may seem like hyper-bogus stuff, but:
       it may be possible to have 2 xinerama screen sets on
       one server */

    if(screen_number) 
	return False;  /* no no, must say zero */

    if(!XextHasExtension(info)) 
	return False;
    else
    {
	int maj, min;

	if (XPanoramiXQueryVersion(display, &maj, &min) == 0) {
	    return False;
	}
	if ((maj == 1) && (min >= 0)) {
	    return XineramaIsActive(display);
	} else {
    	    return True; /* can't check in 1.0 protocol */
	}
    }
}

Status XineramaGetInfo(Display * display, int screen_number, XRectangle *
	framebuffer_rects, unsigned char * framebuffer_hints, int *
	num_framebuffers )

{
    int	framebuffercount;	/* number of fb's we know about */
    int	i;			/* fortran */
    Window	win;
    int x = 0, y = 0;
    int maj, min;
    
    if(!XineramaGetState(display, screen_number))
	return 0;

    if (XPanoramiXQueryVersion(display, &maj, &min) == 0) {
	return 0;
    }
    if ((maj == 1) && (min >= 0)) {
	/* Use XFree86/Xorg extended protocol */
	XineramaScreenInfo	*xsi;

	xsi = XineramaQueryScreens(display, &framebuffercount);
	if (xsi == NULL || framebuffercount == 0) {
	    return 0;
	}
	for (i = 0; i < framebuffercount ; i++) {
	    framebuffer_rects[i].x 	= xsi[i].x_org;
	    framebuffer_rects[i].y 	= xsi[i].y_org;
	    framebuffer_rects[i].width 	= xsi[i].width;
	    framebuffer_rects[i].height = xsi[i].height;
	}
	XFree(xsi);
    } else {
	/* Use Sun extended protocol */
	XPanoramiXInfo	panoramiX_info;	
	XineramaInfo *info;		/* list of screen x,y etc */

	/* get the count of screens that we need to know about 
	   NOTE:  screen_number implies a set of fb's for this
	   working surface */

	win = 0;

	XPanoramiXGetScreenCount(display, win, &panoramiX_info);
    
	if(!panoramiX_info.ScreenCount) {
	    return 0;
	}
	framebuffercount = panoramiX_info.ScreenCount;
    
	/* Make sure not to overflow buffers if X server has more screens
	   than we expect */
	if (framebuffercount > MAXSCREEN)
	    framebuffercount = MAXSCREEN;

	info = malloc(sizeof(XineramaInfo));
    
	if(!info)
	    return 0;

	/* now read the servers list of frame buffers */

	if(!XGetXineramaInfo(display,screen_number, 
		(XID)	RootWindow(display,screen_number),info))
	{
		free(info);
		return 0;
	}


	for(i = 0; i < framebuffercount; i++)
	{
		framebuffer_rects[i].x = info->subs[i].dx;
		framebuffer_rects[i].y = info->subs[i].dy;
		framebuffer_rects[i].width = info->subs[i].wdx;
		framebuffer_rects[i].height = info->subs[i].wdy;
	}

	free(info);
    }

    *num_framebuffers = framebuffercount;
    
    /* assume the start up and list are in the same order */

    for(i = 0; i < framebuffercount; i++)
    {
	framebuffer_hints[i] = 0;
	if (i > 0) 	/* fb0 never gets a hint */
	{
	    if (framebuffer_rects[i].x > x) { 		/* right */
		if (framebuffer_rects[i].y == y)
		    framebuffer_hints[i] = XINERAMA_PLACE_RIGHT;
	    }
	    else if (framebuffer_rects[i].x == x) {	/* up/down */
		if (framebuffer_rects[i].y > y)
		    framebuffer_hints[i] = XINERAMA_PLACE_TOP;
		else if (framebuffer_rects[i].y < y)
		    framebuffer_hints[i] = XINERAMA_PLACE_BOTTOM;
	    } else if (framebuffer_rects[i].x < x) {	/* left */
		if (framebuffer_rects[i].y == y)
		    framebuffer_hints[i] = XINERAMA_PLACE_LEFT;
	    }
	}
	x = framebuffer_rects[i].x;
	y = framebuffer_rects[i].y;

    }
    return framebuffercount;
}

Bool
XGetXineramaInfo(Display *dpy ,int  screen_number,XID VirtualWID,XineramaInfo *info )
{
    xXineramaInfoReq 	*req;
    xXineramaInfoReply 	*rep;
    XExtDisplayInfo *Extinfo = find_display (dpy);

    if(!XineramaGetState(dpy, screen_number))
	return False;

    rep = malloc(sizeof(xXineramaInfoReply));

    LockDisplay(dpy);
    GetReq(XineramaInfo, req);
    req->reqType = Extinfo->codes->major_opcode;
    req->xXineramaReqType = X_XineramaInfo;
    req->visual = VirtualWID;

    if (!_XReply(dpy, (xReply *)rep, (sizeof(xXineramaInfoReply)-32) >> 2
,
        xFalse))
    {
        UnlockDisplay(dpy);
        SyncHandle();
        Xfree(rep);
        return NULL;
    }
    info->wid = VirtualWID;
    memcpy(&info->subs[0],&rep->subs[0],(MAXSCREEN-1) * sizeof(SubWID));
    UnlockDisplay(dpy);
    SyncHandle();
    free(rep);
    return 1;
}

Status XineramaGetCenterHint(Display* display, int screen_number,
				int* xret, int* yret)
{
   int x = -1;
   int y = -1;
   int fb = -1;
   int fbs;
   XrmDatabase xrdb;
   XrmValue value;
   char* vtype;
   char buffer[20];
   XRectangle rects[MAXSCREEN];
   unsigned char hints[MAXSCREEN];
   Bool xiGetState, xiGetInfo;
   long n;
    

   if (screen_number)
      return 0;  /* don't yet support multiple Xinerama screens */

   xiGetState = XineramaGetState(display, screen_number);
   xiGetInfo = XineramaGetInfo(display, screen_number, rects, hints, &fbs);

   if (xrdb = XrmGetDatabase(display))
   {
      if (XrmGetResource(xrdb, "xineramaDefaultFramebuffer",
		"XineramaDefaultFramebuffer", &vtype, &value))
      {
	  if (value.size < sizeof(buffer)) {
	      strncpy(buffer, value.addr, value.size);
	      buffer[value.size] = 0;
	      errno = 0;
	      n = strtol(buffer, (char **)NULL, 10);
	      if ( ! ((n == 0) && (errno == EINVAL)) )
		  fb = n;
	  }
      }

      if (!xiGetState || !xiGetInfo)
	 fbs = 1;
      if ((fb < 0) || (fb >= fbs)) /* fb value not valid */
      {
         if (XrmGetResource(xrdb, "xineramaCenterHintX", "XineramaCenterHintX",
		   &vtype, &value))
         {
	     if (value.size < sizeof(buffer)) {
		 strncpy(buffer, value.addr, value.size);
		 buffer[value.size] = 0;
		 errno = 0;
		 n = strtol(buffer, (char **)NULL, 10);
		 if ( ! ((n == 0) && (errno == EINVAL)) )
		     x = n;
	     }
         }
         if (XrmGetResource(xrdb, "xineramaCenterHintY", "XineramaCenterHintY",
		   &vtype, &value))
         {
	     if (value.size < sizeof(buffer)) {
		 strncpy(buffer, value.addr, value.size);
		 buffer[value.size] = 0;
		 errno = 0;
		 n = strtol(buffer, (char **)NULL, 10);
		 if ( ! ((n == 0) && (errno == EINVAL)) )
		     y = n;
	     }
         }
      }
   }

   if (!xiGetState)
   {
      /* Xinerama is not active, so there's only one framebuffer */
      /* (for screen 0). Return appropriate values anyway.       */

      if (fb == 0) /* assume screen == fb == 0. Code only supports one screen.*/
      {
         *xret = (WidthOfScreen(ScreenOfDisplay(display, 0))) / 2;
         *yret = (HeightOfScreen(ScreenOfDisplay(display, 0))) / 2;
      }
      else
      {
         if ((x >= 0) && (x < WidthOfScreen(ScreenOfDisplay(display, 0))))
            *xret = x;
         else
            *xret = (WidthOfScreen(ScreenOfDisplay(display, 0))) / 2;

         if ((y >= 0) && (y < HeightOfScreen(ScreenOfDisplay(display, 0))))
            *yret = y;
         else
            *yret = (HeightOfScreen(ScreenOfDisplay(display, 0))) / 2;
      }
   }
   else
   {
      /* Xinerama is active, so do the right thing. */

      if (!xiGetInfo)
         return 0;

      if ((fb >= 0) && (fb < fbs) && (fb < MAXSCREEN))  /* if fb has a legal value */
      {
         *xret = rects[fb].x + (rects[fb].width / 2);
         *yret = rects[fb].y + (rects[fb].height / 2);
      }
      else
      {
         if ((x >= 0) && (x < WidthOfScreen(ScreenOfDisplay(display, 0))))
            *xret = x;
         else
            *xret = (WidthOfScreen(ScreenOfDisplay(display, 0))) / 2;

         if ((y >= 0) && (y < HeightOfScreen(ScreenOfDisplay(display, 0))))
            *yret = y;
         else
            *yret = (HeightOfScreen(ScreenOfDisplay(display, 0))) / 2;
      }
   }
   return 1;
}

/**** Code taken from xc/lib/Xinerama/Xinerama.c in Xorg for compatibility with
      XFree86 & Xorg Xinerama 1.1 protocol ****/

/*******************************************************************\
  Alternate interface to make up for shortcomings in the original,
  namely, the omission of the screen origin.  The new interface is
  in the "Xinerama" namespace instead of "PanoramiX".
\*******************************************************************/

static
Bool XineramaIsActive(Display *dpy)
{
    xXineramaIsActiveReply	rep;
    xXineramaIsActiveReq  	*req;
    XExtDisplayInfo 		*info = find_display (dpy);

    if(!XextHasExtension(info))
	return False;  /* server doesn't even have the extension */

    LockDisplay (dpy);
    GetReq (XineramaIsActive, req);
    req->reqType = info->codes->major_opcode;
    req->panoramiXReqType = X_XineramaIsActive;
    if (!_XReply (dpy, (xReply *) &rep, 0, xTrue)) {
	UnlockDisplay (dpy);
	SyncHandle ();
	return False;
    }
    UnlockDisplay (dpy);
    SyncHandle ();
    return rep.state;
}

static
XineramaScreenInfo * 
XineramaQueryScreens(
   Display *dpy,
   int     *number
)
{
    XExtDisplayInfo		*info = find_display (dpy);
    xXineramaQueryScreensReply	rep;
    xXineramaQueryScreensReq	*req;
    XineramaScreenInfo		*scrnInfo = NULL;

    PanoramiXCheckExtension (dpy, info, 0);

    LockDisplay (dpy);
    GetReq (XineramaQueryScreens, req);
    req->reqType = info->codes->major_opcode;
    req->panoramiXReqType = X_XineramaQueryScreens;
    if (!_XReply (dpy, (xReply *) &rep, 0, xFalse)) {
	UnlockDisplay (dpy);
	SyncHandle ();
	return NULL;
    }

    /*
     * rep.number is a CARD32 so could be as large as 2^32
     * The X11 protocol limits the total screen size to 64k x 64k,
     * and no screen can be smaller than a pixel.  While technically
     * that means we could theoretically reach 2^32 screens, and that's
     * not even taking overlap into account, Xorg is currently limited
     * to 16 screens, and few known servers have a much higher limit,
     * so 1024 seems more than enough to prevent both integer overflow
     * and insane X server responses causing massive memory allocation.
     */
    if ((rep.number > 0) && (rep.number <= 1024))
	scrnInfo = Xmalloc(sizeof(XineramaScreenInfo) * rep.number);
    if (scrnInfo != NULL) {
	int i;

	for (i = 0; i < rep.number; i++) {
	    xXineramaScreenInfo scratch;

	    _XRead(dpy, (char*)(&scratch), sz_XineramaScreenInfo);

	    scrnInfo[i].screen_number = i;
	    scrnInfo[i].x_org	= scratch.x_org;
	    scrnInfo[i].y_org	= scratch.y_org;
	    scrnInfo[i].width	= scratch.width;
	    scrnInfo[i].height	= scratch.height;
	}

	*number = rep.number;
    } else {
	_XEatDataWords(dpy, rep.length);
	*number = 0;
    }

    UnlockDisplay (dpy);
    SyncHandle ();
    return scrnInfo;
}



