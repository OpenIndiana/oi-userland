/*
 * Copyright (c) 1999, 2015, Oracle and/or its affiliates. All rights reserved.
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


#define NEED_REPLIES
#include <X11/Xlibint.h>
#include <X11/extensions/fbpm.h>
#include <X11/extensions/fbpmstr.h>
#include <X11/extensions/Xext.h>
#include <X11/extensions/extutil.h>
#include <stdio.h>

static XExtensionInfo _fbpm_info_data;
static XExtensionInfo *fbpm_info = &_fbpm_info_data;
static char *fbpm_extension_name = FBPMExtensionName;

#define FBPMCheckExtension(dpy,i,val) \
  XextCheckExtension (dpy, i, fbpm_extension_name, val)

/*****************************************************************************
 *                                                                           *
 *                         private utility routines                          *
 *                                                                           *
 *****************************************************************************/

static int close_display(Display *dpy, XExtCodes *codes);
static /* const */ XExtensionHooks fbpm_extension_hooks = {
    NULL,                               /* create_gc */
    NULL,                               /* copy_gc */
    NULL,                               /* flush_gc */
    NULL,                               /* free_gc */
    NULL,                               /* create_font */
    NULL,                               /* free_font */
    close_display,                      /* close_display */
    NULL,                               /* wire_to_event */
    NULL,                               /* event_to_wire */
    NULL,                               /* error */
    NULL                                /* error_string */
};

static XEXT_GENERATE_FIND_DISPLAY (find_display, fbpm_info,
				   fbpm_extension_name,
                                   &fbpm_extension_hooks, FBPMNumberEvents,
                                   NULL)

static XEXT_GENERATE_CLOSE_DISPLAY (close_display, fbpm_info)
                                                              
/*****************************************************************************
 *                                                                           *
 *                  public routines                                          *
 *                                                                           *
 *****************************************************************************/

Bool FBPMQueryExtension (
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

Status FBPMGetVersion(
    Display *dpy,
    int	    *major_versionp,
    int	    *minor_versionp)
{
    XExtDisplayInfo *info = find_display (dpy);
    xFBPMGetVersionReply	    rep;
    register xFBPMGetVersionReq  *req;

    FBPMCheckExtension (dpy, info, 0);

    LockDisplay (dpy);
    GetReq (FBPMGetVersion, req);
    req->reqType = info->codes->major_opcode;
    req->fbpmReqType = X_FBPMGetVersion;
    if (!_XReply (dpy, (xReply *) &rep, 0, xTrue)) {
	UnlockDisplay (dpy);
	SyncHandle ();
	return 0;
    }
    *major_versionp = rep.majorVersion;
    *minor_versionp = rep.minorVersion;
    UnlockDisplay (dpy);
    SyncHandle ();
    return 1;
}

Bool FBPMCapable(
    Display *dpy)
{
    XExtDisplayInfo *info = find_display (dpy);
    register xFBPMCapableReq *req;
    xFBPMCapableReply rep;

    FBPMCheckExtension (dpy, info, 0);

    LockDisplay(dpy);
    GetReq(FBPMCapable, req);
    req->reqType = info->codes->major_opcode;
    req->fbpmReqType = X_FBPMCapable;

    if (!_XReply(dpy, (xReply *)&rep, 0, xFalse)) {
	UnlockDisplay(dpy);
	SyncHandle();
	return False;
    }
    UnlockDisplay(dpy);
    SyncHandle();
    return rep.capable;
}


Bool FBPMEnable(
    Display *dpy,
    int state)
{
    XExtDisplayInfo *info = find_display (dpy);
    register xFBPMEnableReq *req;

    FBPMCheckExtension (dpy, info, 0);
    LockDisplay(dpy);
    GetReq(FBPMEnable, req);
    req->reqType = info->codes->major_opcode;
    req->fbpmReqType = X_FBPMEnable;
    req->level = state;

    UnlockDisplay(dpy);
    SyncHandle();
    return True;
}

Status FBPMDisable(
    Display *dpy)
{
    XExtDisplayInfo *info = find_display (dpy);
    register xFBPMDisableReq *req;

    FBPMCheckExtension (dpy, info, 0);
    LockDisplay(dpy);
    GetReq(FBPMDisable, req);
    req->reqType = info->codes->major_opcode;
    req->fbpmReqType = X_FBPMDisable;

    UnlockDisplay(dpy);
    SyncHandle();
    return 1;
}
Status FBPMForceLevel(
    Display *dpy,
    CARD16 level)
{
    XExtDisplayInfo *info = find_display (dpy);
    register xFBPMForceLevelReq *req;

    FBPMCheckExtension (dpy, info, 0);

    if ((level != FBPMModeOn) &&
        (level != FBPMModeStandby) &&
        (level != FBPMModeSuspend) &&
        (level != FBPMModeOff))
        return BadValue;

    LockDisplay(dpy);
    GetReq(FBPMForceLevel, req);
    req->reqType = info->codes->major_opcode;
    req->fbpmReqType = X_FBPMForceLevel;
    req->level = level;

    UnlockDisplay(dpy);
    SyncHandle();
    return 1;
}

Status FBPMInfo(
    Display *dpy,
    CARD16 *state,
    BOOL *onoff)
{
    XExtDisplayInfo *info = find_display (dpy);
    register xFBPMInfoReq *req;
    xFBPMInfoReply rep;

    FBPMCheckExtension (dpy, info, 0);

    LockDisplay(dpy);
    GetReq(FBPMInfo, req);
    req->reqType = info->codes->major_opcode;
    req->fbpmReqType = X_FBPMInfo;

    if (!_XReply(dpy, (xReply *)&rep, 0, xTrue)) {
        UnlockDisplay(dpy);
        SyncHandle();
        return 0;
    }
    UnlockDisplay(dpy);
    SyncHandle();
    *state = rep.power_level;
    *onoff = rep.state;
    return 1;
}

