/* Copyright (c) 1993, 1999, Oracle and/or its affiliates. All rights reserved.
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


#ifndef _TRANSOVLSTR_H_
#define _TRANSOVLSTR_H_

#include "transovl.h"

/*
   B U G : 4173223

   These items should be 32 bit type.

   We must redefine the following types in terms 
   of Xmd.h's types, which may include bit fields.  
   All of these are #undef'd at the end of this file,
   restoring the definitions in X.h.  
 */

#define Window CARD32
#define Drawable CARD32
#define Font CARD32
#define Pixmap CARD32
#define Cursor CARD32
#define Colormap CARD32
#define GContext CARD32
#define Atom CARD32
#define VisualID CARD32
#define Time CARD32
#define KeyCode CARD8
#define KeySym CARD32


#define OVLNAME "SUN_OVL"
#define OVL_MAJOR_VERSION	1	/* current version numbers */
#define OVL_MINOR_VERSION	0

typedef struct {
    CARD8	reqType;		/* always OvlReqCode */
    CARD8	ovlReqType;		/* always X_OvlQueryVersion */
    CARD16	length B16;
} xOvlQueryVersionReq;
#define sz_xOvlQueryVersionReq	4

typedef struct {
    BYTE	type;			/* X_Reply */
    CARD8	unused;
    CARD16	sequenceNumber B16;
    CARD32	length B32;
    CARD16	majorVersion B16;
    CARD16	minorVersion B16;
    CARD32	pad0 B32;
    CARD32	pad1 B32;
    CARD32	pad2 B32;
    CARD32	pad3 B32;
    CARD32	pad4 B32;
} xOvlQueryVersionReply;
#define sz_xOvlQueryVersionReply	32

typedef struct {
    CARD8	reqType;		/* always OvlReqCode */
    CARD8	ovlReqType;		/* always X_OvlGetPartners */
    CARD16	length B16;
    CARD32	screen B32;
} xOvlGetPartnersReq;
#define sz_xOvlGetPartnersReq	8

typedef struct {
    BYTE	type;			/* X_Reply */
    BOOL	restricted;
    CARD16	sequenceNumber B16;
    CARD32	length B32;
    CARD16	numPairs B16;
    CARD16	pad0 B16;
    CARD32	pad1 B32;
    CARD32	pad2 B32;
    CARD32	pad3 B32;
    CARD32	pad4 B32;
    CARD32	pad5 B32;
} xOvlGetPartnersReply;
#define sz_xOvlGetPartnersReply	32

typedef struct {
    VisualID	overlayVid;
    VisualID	underlayVid;
} XOvlVidPair;

typedef struct {
    CARD8	reqType;		/* always OvlReqCode */
    CARD8	ovlReqType;		/* always X_OvlGetSharedPixels */
    CARD16	length B16;
    CARD32	screen B32;
} xOvlGetSharedPixelsReq;
#define sz_xOvlGetSharedPixelsReq	8

typedef struct {
    BYTE	type;			/* X_Reply */
    CARD8	unused;
    CARD16	sequenceNumber B16;
    CARD32	length B32;
    CARD16	numPGInfos B16;
    CARD16	pad0 B16;
    CARD32	pad1 B32;
    CARD32	pad2 B32;
    CARD32	pad3 B32;
    CARD32	pad4 B32;
    CARD32	pad5 B32;
} xOvlGetSharedPixelsReply;
#define sz_xOvlGetSharedPixelsReply	32

typedef struct {
    VisualID	vid;
    CARD32	ovplanes;
    CARD32	unplanes;
} XOvlPGInfo;

typedef struct {
    CARD8	reqType;		/* always OvlReqCode */
    CARD8	ovlReqType;		/* always X_OvlGetSharedColors */
    CARD16	length B16;
    CARD32	screen B32;
} xOvlGetSharedColorsReq;
#define sz_xOvlGetSharedColorsReq	8

typedef struct {
    BYTE	type;			/* X_Reply */
    CARD8	unused;
    CARD16	sequenceNumber B16;
    CARD32	length B32;
    CARD16	numClutInfos B16;
    CARD16	pad0 B16;
    CARD32	pad1 B32;
    CARD32	pad2 B32;
    CARD32	pad3 B32;
    CARD32	pad4 B32;
    CARD32	pad5 B32;
} xOvlGetSharedColorsReply;
#define sz_xOvlGetSharedColorsReply	32

typedef struct {
    VisualID	vid;
    CARD32	pool;
    INT32	count;
} XOvlClutInfo;

#define AllMaskBits (CWBackPixmap|CWBackPixel|CWBorderPixmap|\
		     CWBorderPixel|CWBitGravity|CWWinGravity|\
		     CWBackingStore|CWBackingPlanes|CWBackingPixel|\
		     CWOverrideRedirect|CWSaveUnder|CWEventMask|\
		     CWDontPropagate|CWColormap|CWCursor)

typedef struct {
    CARD8	reqType;		/* always OvlReqCode */
    CARD8	ovlReqType;		/* always X_OvlCreateWindow */
    CARD16	length B16;
    Window	wid B32;
    Window	parent B32;
    INT16	x B16;
    INT16	y B16;
    CARD16	width B16;
    CARD16	height B16;
    CARD16	borderWidth B16;
    INT16	depth B16;
    CARD32	class B32;
    VisualID	visual B32;
    CARD32	mask B32;
} xOvlCreateWindowReq;
#define sz_xOvlCreateWindowReq	36

typedef struct {
    CARD8	reqType;		/* always OvlReqCode */
    CARD8	ovlReqType;		/* always X_OvlIsOverlayWindow */
    CARD16	length B16;
    Window	wid B32;
} xOvlIsOverlayWindowReq;
#define sz_xOvlIsOverlayWindowReq	8

typedef struct {
    BYTE	type;			/* X_Reply */
    BOOL	isoverlay;
    CARD16	sequenceNumber B16;
    CARD32	length B32;
    CARD32	pad0 B32;
    CARD32	pad1 B32;
    CARD32	pad2 B32;
    CARD32	pad3 B32;
    CARD32	pad4 B32;
    CARD32	pad5 B32;
} xOvlIsOverlayWindowReply;
#define sz_xOvlIsOverlayWindowReply	32

typedef struct {
    CARD8		reqType;	/* always OvlReqCode */
    CARD8		ovlReqType;	/* always X_OvlSetWindowTransparent */
    CARD16		length B16;
    Window		wid B32;
} xOvlSetWindowTransparentReq;
#define sz_xOvlSetWindowTransparentReq	8

typedef struct {
    CARD8		reqType;	/* always OvlReqCode */
    CARD8		ovlReqType;	/* always X_OvlSetPaintType */
    CARD16		length B16;
    GContext		gc B32;
    XSolarisOvlPaintType paintType B32;
} xOvlSetPaintTypeReq;
#define sz_xOvlSetPaintTypeReq	12

typedef struct {
    CARD8	reqType;		/* always OvlReqCode */
    CARD8	ovlReqType;		/* always X_OvlCopyPaintType */
    CARD16	length B16;
    Drawable	srcDrawable B32;
    Drawable	dstDrawable B32;
    GContext	gc B32;
    INT16	srcX B16;
    INT16	srcY B16;
    INT16	destX B16;
    INT16	destY B16;
    CARD16	width B16;
    CARD16	height B16;
    CARD32      action_mask B32;
    CARD32      bitPlane B32;
} xOvlCopyPaintTypeReq;
#define sz_xOvlCopyPaintTypeReq	36

typedef struct {
    CARD8	reqType;		/* always OvlReqCode */
    CARD8	ovlReqType;		/* always X_OvlCopyAreaAndPaintType */
    CARD16	length B16;
    Drawable	colorSrc B32;
    Drawable	paintTypeSrc B32;
    Drawable	colorDst B32;
    Drawable	paintTypeDst B32;
    GContext	colorGC B32;
    GContext	paintTypeGC B32;
    INT16	colorSrcX B16;
    INT16	colorSrcY B16;
    INT16	paintTypeSrcX B16;
    INT16	paintTypeSrcY B16;
    INT16	colorDstX B16;
    INT16	colorDstY B16;
    INT16	paintTypeDstX B16;
    INT16	paintTypeDstY B16;
    CARD16	width B16;
    CARD16	height B16;
    CARD32      action_mask B32;
    CARD32      bitPlane B32;
} xOvlCopyAreaAndPaintTypeReq;
#define sz_xOvlCopyAreaAndPaintTypeReq	56

#define READSCREEN_BLUEMASK	0x00ff0000
#define READSCREEN_GREENMASK	0x0000ff00
#define READSCREEN_REDMASK	0x000000ff

typedef struct {
    CARD8	reqType;		/* always OvlReqCode */
    CARD8	ovlReqType;		/* always X_OvlReadScreen */
    CARD16	length B16;
    Window	window B32;
    INT16	x B16;
    INT16	y B16;
    CARD16	width B16;
    CARD16	height B16;
    BOOL	includeCursor;
    CARD8	pad[3];
} xOvlReadScreenReq;
#define sz_xOvlReadScreenReq	20

typedef struct {
    BYTE	type;			/* X_Reply */
    CARD8	unused;
    CARD16	sequenceNumber B16;
    CARD32	length B32;
    CARD32	pad0 B32;
    CARD32	pad1 B32;
    CARD32	pad2 B32;
    CARD32	pad3 B32;
    CARD32	pad4 B32;
    CARD32	pad5 B32;
} xOvlReadScreenReply;
#define sz_xOvlReadScreenReply 32


/*
   B U G : 4173223
 */
/* restore these definitions back to the typedefs in X.h */
#undef Window
#undef Drawable
#undef Font
#undef Pixmap
#undef Cursor
#undef Colormap
#undef GContext
#undef Atom
#undef VisualID
#undef Time
#undef KeyCode
#undef KeySym

#endif /* _TRANSOVLSTR_H_ */
