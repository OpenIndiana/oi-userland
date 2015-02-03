/* Copyright (c) 1994, 1999, Oracle and/or its affiliates. All rights reserved.
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
 *-----------------------------------------------------------------------
 * SUN_DGA private extension minor op codes
 *-----------------------------------------------------------------------
 */

#ifndef _SUN_DGA_H
#define _SUN_DGA_H

#define SUN_DGA_MAJOR_VERSION	3	/* current version numbers */
#define SUN_DGA_MINOR_VERSION	2

/* protocol requests in Protocol Version 1 - OpenWindows 2.0 FCS */
#define  X_WxGrab 		1
#define  X_WxUnGrab 		2
#define  X_WxGrabColormap 	3
#define  X_WxUnGrabColormap 	4

/* additional protocol requests in Protocol Version 2 - OpenWindows 3.0 Beta */
#define  X_WxGrabWids 		5	
#define  X_WxGrabBuffers 	6	
#define  X_WxUnGrabBuffers  	7	
#define  X_WxGrabFCS		8
#define  X_WxGrabZbuf		9
#define  X_WxGrabStereo	       10	
#define  X_WxGrab_New 	       11
#define  X_WxUnGrab_New	       12

/* additional protocol requests in Protocol Version 3 - OpenWindows 3.0 FCS */
#define  X_WxGrabColormapNew   13
#define  X_WxUnGrabColormapNew 14
#define  X_WxGrabRetained      15
#define  X_WxUnGrabRetained    16
#define  X_WxGetRetainedPath   17
#define  X_DgaQueryVersion     18

/* additional protocol requests in Protocol Version 3 - OpenWindows 3.0 FCS */

#define  X_WxGrabPixmap        19
#define  X_WxUnGrabPixmap      20

/* additional protocol requests in Protocol Version 3.2 */

#define  X_WxGrabDrawable      21
#define  X_WxUnGrabDrawable    22

/* additional protocol requests in Protocol Version 3.6 */

#define  X_WxGrabABuffers      23
#define  X_WxUnGrabABuffers    24

#ifdef PANORAMIX
#define X_DgaXineramaInfo 25
#endif

/*
** Types of grabbable drawables
*/

#define DGA_PROTO_WINDOW  0
#define DGA_PROTO_PIXMAP  1
#define DGA_PROTO_OVERLAY 2

#define DGA_TOKEN_NULL    0

/* Ancillary Buffers request structure */

 typedef struct {
    CARD8 reqType;
    BYTE pad;
    CARD16 length B16;
    CARD32 id B32;  /* a Window, Drawable, Font, GContext, Pixmap, etc. */
    CARD32 type;
    CARD32 buffer_site;
    } xDgaGrabABuffersReq;
#define sz_xDgaGrabABuffersReq    (sizeof(xDgaGrabABuffersReq))

/*
** OWGX request structure
*/

 typedef struct {
    CARD8 reqType;
    BYTE pad;
    CARD16 length B16;
    CARD32 id B32;  /* a Window, Drawable, Font, GContext, Pixmap, etc. */
    CARD32 number_objects B32;
    } xOWGXReq;
#define sz_xOWGXReq    12


/*
** OWGX shared retained path reply structure
*/

 typedef struct {
    BYTE type;			/* X_Reply */
    CARD8 pad;
    CARD16 sequenceNumber B16;
    CARD32 length B32;
    CARD8  path[200];
    } xOWGXRtndPathReply;
#define sz_xOWGXRtndPathReply 208


/*
 * DgaQueryVersion request and reply structures
 */

typedef struct {
    CARD8       reqType;		/* always SUN_DGA major opcode */
    CARD8       dgaReqType;		/* always X_DgaQueryVersion */
    CARD16	length B16;
} xDgaQueryVersionReq;
#define sz_xDgaQueryVersionReq	4

typedef struct {
    BYTE        type;			/* X_Reply */
    CARD8       unused;
    CARD16	sequenceNumber B16;
    CARD32	length B32;
    CARD16	majorVersion B16;
    CARD16	minorVersion B16;
    CARD32	pad0 B32;
    CARD32	pad1 B32;
    CARD32	pad2 B32;
    CARD32	pad3 B32;
    CARD32	pad4 B32;
} xDgaQueryVersionReply;
#define sz_xDgaQueryVersionReply	32



#endif /* _SUN_DGA_H */

