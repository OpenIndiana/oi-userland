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


/*
 * AllPlanes.c - the client side interface to the SUN_ALLPLANES extension.
 */

#define NEED_EVENTS
#define NEED_REPLIES
#include <stdio.h>
#include <X11/Xlibint.h>
#include <X11/extensions/Xext.h>
#include <X11/extensions/extutil.h>
#include <X11/extensions/allplanesstr.h>

static int  close_display(Display *dpy, XExtCodes *codes);

static XExtensionInfo *ext_info;
static char *ext_name = ALLPLANESNAME;
static XExtensionHooks ext_hooks = {
    NULL,			/* create_gc */
    NULL,			/* copy_gc */
    NULL,			/* flush_gc */
    NULL,			/* free_gc */
    NULL,			/* create_font */
    NULL,			/* free_font */
    close_display,		/* close_display */
    NULL,			/* wire_to_event */
    NULL,			/* event_to_wire */
    NULL,			/* error */
    NULL,			/* error_string */
};

static
XEXT_GENERATE_CLOSE_DISPLAY(close_display,
			    ext_info)

static
XEXT_GENERATE_FIND_DISPLAY(find_display,
			   ext_info, ext_name, &ext_hooks,
			   AllPlanesNumberEvents, NULL)

#define AllPlanesCheckExtension(dpy,i,val) \
  XextCheckExtension (dpy, i, ext_name, val)
#define AllPlanesSimpleCheckExtension(dpy,i) \
  XextSimpleCheckExtension (dpy, i, ext_name)

/**********************************************************************/

Bool
XAllPlanesQueryExtension(
    Display    *dpy,
    int        *event_basep,
    int        *error_basep)
{
    XExtDisplayInfo *info = find_display(dpy);

    if (XextHasExtension(info)) {
	*event_basep = info->codes->first_event;
	*error_basep = info->codes->first_error;
	return True;
    } else {
	return False;
    }
}


Status
XAllPlanesQueryVersion(
    Display    *dpy,
    int        *major_versionp,
    int        *minor_versionp)
{
    XExtDisplayInfo *info = find_display(dpy);
    xAllPlanesQueryVersionReply rep;
    xAllPlanesQueryVersionReq *req;

    AllPlanesCheckExtension(dpy, info, 0);

    LockDisplay(dpy);
    GetReq(AllPlanesQueryVersion, req);
    req->reqType = info->codes->major_opcode;
    req->allplanesReqType = X_AllPlanesQueryVersion;
    if (!_XReply(dpy, (xReply *) & rep, 0, xTrue)) {
	UnlockDisplay(dpy);
	SyncHandle();
	return 0;
    }
    *major_versionp = rep.majorVersion;
    *minor_versionp = rep.minorVersion;
    UnlockDisplay(dpy);
    SyncHandle();
    return 1;
}


void
XAllPlanesDrawPoints(
    Display    *dpy,
    Drawable    d,
    XPoint     *points,
    int         n_points,
    int         mode)		/* CoordMode */
{
    XExtDisplayInfo *info = find_display(dpy);
    xAllPlanesPolyPointReq *req;
    long nbytes;
    int         n;
    int         xoff,
                yoff;
    XPoint      pt;

    AllPlanesSimpleCheckExtension(dpy, info);

    xoff = yoff = 0;
    LockDisplay(dpy);
    while (n_points) {
	GetReq(AllPlanesPolyPoint, req);
	req->reqType = info->codes->major_opcode;
	req->allplanesReqType = X_AllPlanesPolyPoint;
	req->drawable = d;
	req->coordMode = mode;
	n = n_points;
	if (n > (dpy->max_request_size - req->length))
	    n = dpy->max_request_size - req->length;
	req->length += n;
	nbytes = ((long) n) << 2;
	if (xoff || yoff) {
	    pt.x = xoff + points->x;
	    pt.y = yoff + points->y;
	    Data16(dpy, (short *) &pt, 4);
	    if (nbytes > 4) {
		Data16(dpy, (short *) (points + 1), nbytes - 4);
	    }
	} else {
	    Data16(dpy, (short *) points, nbytes);
	}
	n_points -= n;
	if (n_points && (mode == CoordModePrevious)) {
	    XPoint *pptr = points;
	    points += n;
	    while (pptr != points) {
		xoff += pptr->x;
		yoff += pptr->y;
		pptr++;
	    }
	} else
	    points += n;
    }
    UnlockDisplay(dpy);
    SyncHandle();
}


void
XAllPlanesDrawLines(
    Display    *dpy,
    Drawable    d,
    XPoint     *points,
    int         npoints,
    int         mode)
{
    XExtDisplayInfo *info = find_display(dpy);
    xAllPlanesPolyLineReq *req;
    long        len;

    AllPlanesSimpleCheckExtension(dpy, info);

    LockDisplay(dpy);
    GetReq(AllPlanesPolyLine, req);
    req->reqType = info->codes->major_opcode;
    req->allplanesReqType = X_AllPlanesPolyLine;
    req->drawable = d;
    req->coordMode = mode;
    if ((req->length + npoints) > 65535)
	npoints = 65535 - req->length;	/* force BadLength, if possible */
    req->length += npoints;
    /* each point is 2 16-bit integers */
    len = npoints << 2;
    Data16(dpy, (short *) points, len);
    UnlockDisplay(dpy);
    SyncHandle();
}


void
XAllPlanesDrawSegments(
    Display    *dpy,
    Drawable    d,
    XSegment   *segments,
    int         nsegments)
{
    XExtDisplayInfo *info = find_display(dpy);
    xAllPlanesPolySegmentReq *req;
    long        len;
    int         n;

    AllPlanesSimpleCheckExtension(dpy, info);

    LockDisplay(dpy);
    while (nsegments) {
	GetReq(AllPlanesPolySegment, req);
	req->reqType = info->codes->major_opcode;
	req->allplanesReqType = X_AllPlanesPolySegment;
	req->drawable = d;
	n = nsegments;
	len = ((long) n) << 1;
	if (len > (dpy->max_request_size - req->length)) {
	    n = (dpy->max_request_size - req->length) >> 1;
	    len = ((long) n) << 1;
	}
	req->length += len;
	len <<= 2;
	Data16(dpy, (short *) segments, len);
	nsegments -= n;
	segments += n;
    }
    UnlockDisplay(dpy);
    SyncHandle();
}


void
XAllPlanesDrawRectangles(
    Display    *dpy,
    Drawable    d,
    XRectangle *rects,
    int         n_rects)
{
    XExtDisplayInfo *info = find_display(dpy);
    xAllPlanesPolyRectangleReq *req;
    long        len;
    int         n;

    AllPlanesSimpleCheckExtension(dpy, info);

    LockDisplay(dpy);
    while (n_rects) {
	GetReq(AllPlanesPolyRectangle, req);
	req->reqType = info->codes->major_opcode;
	req->allplanesReqType = X_AllPlanesPolyRectangle;
	req->drawable = d;
	n = n_rects;
	len = ((long) n) << 1;
	if (len > (dpy->max_request_size - req->length)) {
	    n = (dpy->max_request_size - req->length) >> 1;
	    len = ((long) n) << 1;
	}
	req->length += len;
	len <<= 2;
	Data16(dpy, (short *) rects, len);
	n_rects -= n;
	rects += n;
    }
    UnlockDisplay(dpy);
    SyncHandle();
}


void
XAllPlanesFillRectangles(
    Display    *dpy,
    Drawable    d,
    XRectangle *rectangles,
    int         n_rects)
{
    XExtDisplayInfo *info = find_display(dpy);
    xAllPlanesPolyFillRectangleReq *req;
    long        len;
    int         n;

    AllPlanesSimpleCheckExtension(dpy, info);

    LockDisplay(dpy);
    while (n_rects) {
	GetReq(AllPlanesPolyFillRectangle, req);
	req->reqType = info->codes->major_opcode;
	req->allplanesReqType = X_AllPlanesPolyFillRectangle;
	req->drawable = d;
	n = n_rects;
	len = ((long) n) << 1;
	if (len > (dpy->max_request_size - req->length)) {
	    n = (dpy->max_request_size - req->length) >> 1;
	    len = ((long) n) << 1;
	}
	req->length += len;
	len <<= 2;
	Data16(dpy, (short *) rectangles, len);
	n_rects -= n;
	rectangles += n;
    }
    UnlockDisplay(dpy);
    SyncHandle();
}
