/* Copyright (c) 1990, 2011, Oracle and/or its affiliates. All rights reserved.
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



#ifndef _ALLPLANES_H_
#define _ALLPLANES_H_

#define X_AllPlanesQueryVersion			0
#define X_AllPlanesPolyPoint			1
#define X_AllPlanesPolyLine			2
#define X_AllPlanesPolySegment			3
#define X_AllPlanesPolyRectangle		4
#define X_AllPlanesPolyFillRectangle		5

#define AllPlanesNumberEvents			0

#ifndef _ALLPLANES_SERVER_

extern Bool XAllPlanesQueryExtension(Display *dpy, int *event_basep,
				     int *error_basep);
extern Status XAllPlanesQueryVersion(Display *dpy, int *major_versionp,
				     int *minor_versionp);
extern void XAllPlanesDrawPoints(Display *dpy, Drawable d,
				 XPoint *points, int n_points, int mode);
extern void XAllPlanesDrawLines(Display *dpy, Drawable d,
				XPoint *points, int n_points, int mode);
extern void XAllPlanesDrawSegments(Display *dpy, Drawable d,
				   XSegment *segments, int nsegment);
extern void XAllPlanesDrawRectangles(Display *dpy, Drawable d,
				     XRectangle *rects, int n_rects);
extern void XAllPlanesFillRectangles(Display *dpy, Drawable d,
				     XRectangle *rectangles, int n_rects);

#endif /* _ALLPLANES_SERVER_ */

#endif /* _ALLPLANES_H_ */
