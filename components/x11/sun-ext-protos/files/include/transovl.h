/* Copyright (c) 1993, 1994, Oracle and/or its affiliates. All rights reserved.
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


#ifndef _TRANSOVL_H_
#define _TRANSOVL_H_

#if defined(__cplusplus)
extern "C" {
#endif

#ifndef _TRANSOVL_SERVER_

#include <X11/Xlib.h>
#include <X11/Xutil.h>

#endif /* _TRANSOVL_SERVER_ */

#define X_OvlQueryVersion			0
#define X_OvlGetPartners			1
#define X_OvlGetSharedPixels			2
#define X_OvlGetSharedColors			3
#define X_OvlCreateWindow			4
#define X_OvlIsOverlayWindow			5
#define X_OvlSetWindowTransparent		6
#define X_OvlSetPaintType			7
#define X_OvlCopyPaintType			8
#define X_OvlCopyAreaAndPaintType		9
#define X_OvlReadScreen				10

#define OvlNumberEvents				0

typedef enum {
    XSolarisOvlPaintTransparent,
    XSolarisOvlPaintOpaque
} XSolarisOvlPaintType;

typedef enum {
    XSolarisOvlSuccess,
    XSolarisOvlQualifiedSuccess,
    XSolarisOvlCriteriaFailure,
    XSolarisOvlFailure
} XSolarisOvlSelectStatus;

typedef enum {
    XSolarisOvlSelectBestOverlay,
    XSolarisOvlSelectBestUnderlay
} XSolarisOvlSelectType;

typedef struct {
    unsigned long	hardCriteriaMask;
    unsigned long	softCriteriaMask;
    int			c_class;
    unsigned int	depth;
    unsigned int	minColors;
    unsigned int	minRed;
    unsigned int	minGreen;
    unsigned int	minBlue;
    unsigned int	minBitsPerRGB;
    unsigned int	minBuffers;
} XSolarisOvlVisualCriteria;

typedef struct {
    XSolarisOvlVisualCriteria	overlayCriteria;
    XSolarisOvlVisualCriteria	underlayCriteria;
} XSolarisOvlPairCriteria;

#define XSolarisOvlVisualClass		(1L<<0)
#define XSolarisOvlDepth		(1L<<1)
#define XSolarisOvlMinColors		(1L<<2)
#define XSolarisOvlMinRed		(1L<<3)
#define XSolarisOvlMinGreen		(1L<<4)
#define XSolarisOvlMinBlue		(1L<<5)
#define XSolarisOvlMinBitsPerRGB	(1L<<6)
#define XSolarisOvlMinBuffers		(1L<<7)
#define XSolarisOvlUnsharedPixels	(1L<<8)
#define XSolarisOvlUnsharedColors	(1L<<9)
#define XSolarisOvlPreferredPartner	(1L<<10)

#define XSolarisOvlCopyOpaque		(1L<<0)
#define XSolarisOvlCopyTransparent	(1L<<1)
#define XSolarisOvlCopyAll		(XSolarisOvlCopyOpaque|XSolarisOvlCopyTransparent)

#ifndef _TRANSOVL_SERVER_

#if defined(__STDC__) || defined(__cplusplus)
extern Bool XSolarisOvlQueryExtension(Display *, int *, int *);

extern Status XSolarisOvlQueryVersion(Display *, int *, int *);

extern Window XSolarisOvlCreateWindow(Display *, Window, int, int, 
		unsigned int, unsigned int, unsigned int, int, 
		unsigned int, Visual *, unsigned long, XSetWindowAttributes *);

extern Bool XSolarisOvlIsOverlayWindow(Display *, Window);

extern void XSolarisOvlSetWindowTransparent(Display *, Window);

extern Status XSolarisOvlSetPaintType(Display *, GC, XSolarisOvlPaintType);

extern XSolarisOvlPaintType XSolarisOvlGetPaintType(Display *, GC);

extern Status XSolarisOvlCopyPaintType(Display *, Drawable, Drawable, GC, 
		int, int, unsigned int, unsigned int, int, int, 
		unsigned long, unsigned long);

extern Status XSolarisOvlCopyAreaAndPaintType(Display *, 
		Drawable, Drawable, Drawable, Drawable,
		GC, GC, int, int, int, int, 
		unsigned int, unsigned int, int, int, int, int, 
		unsigned long, unsigned long);

extern XImage *XReadScreen(Display *, Window, int, int, unsigned int, unsigned int, Bool);

extern XSolarisOvlSelectStatus XSolarisOvlSelectPartner(Display *, int, VisualID, 
		XSolarisOvlSelectType, int, XSolarisOvlVisualCriteria *, XVisualInfo *, 
		unsigned long *);

extern XSolarisOvlSelectStatus XSolarisOvlSelectPair(Display *, int, int, 
		XSolarisOvlPairCriteria *, XVisualInfo *, XVisualInfo *, 
		unsigned long *, unsigned long *);
#else
extern Bool XSolarisOvlQueryExtension();
extern Status XSolarisOvlQueryVersion();
extern Window XSolarisOvlCreateWindow();
extern Bool XSolarisOvlIsOverlayWindow();
extern void XSolarisOvlSetWindowTransparent();
extern Status XSolarisOvlSetPaintType();
extern XSolarisOvlPaintType XSolarisOvlGetPaintType();
extern Status XSolarisOvlCopyPaintType();
extern Status XSolarisOvlCopyAreaAndPaintType();
extern XImage *XReadScreen();
extern XSolarisOvlSelectStatus XSolarisOvlSelectPartner();
extern XSolarisOvlSelectStatus XSolarisOvlSelectPair();
#endif

#endif /* _TRANSOVL_SERVER_ */

#if defined(__cplusplus)
}
#endif

#endif /* _TRANSOVL_H_ */
