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


/*
 * dga_Xrequests.h - DGA X11 protocol extension definitions
 */
 
#ifndef _DGA_XREQUESTS_H
#define _DGA_XREQUESTS_H

/*
 *
 *-----------------------------------------------------------------------
 * DGA minor op codes
 *-----------------------------------------------------------------------
 *
 */
#define SUN_DGA_MAJOR_VERSION   3       /* current version numbers */
#define SUN_DGA_MINOR_VERSION   2

/* protocol requests in Protocol Version 1 - OpenWindows 2.0 FCS */
#define  X_DgaGrabWindow_Old	1
#define  X_DgaUnGrabWindow_Old	2
#define  X_DgaGrabColormap_Old 	3
#define  X_DgaUnGrabColormap_Old 4


/* additional protocol requests in Protocol Version 2 - OpenWindows 3.0 Beta */
#define  X_DgaGrabWids 		5
#define  X_DgaGrabBuffers 	6
#define  X_DgaUnGrabBuffers  	7
#define  X_DgaGrabFCS		8
#define  X_DgaGrabZbuf		9
#define  X_DgaGrabStereo       10
#define  X_DgaGrabWindow       11
#define  X_DgaUnGrabWindow     12


/* additional protocol requests in Protocol Version 3 - OpenWindows 3.0 FCS */
#define  X_DgaGrabColormap     13
#define  X_DgaUnGrabColormap   14
#define  X_DgaGrabRetained     15
#define  X_DgaUnGrabRetained   16
#define  X_DgaGetRetainedPath  17
#define  X_DgaQueryVersion     18

/* additional protocol requests in Protocol Version 3 - OpenWindows 3.0.1 FCS*/
#define  X_DgaGrabPixmap       19
#define  X_DgaUnGrabPixmap     20

/* additional protocol requests in Protocol Version 3 - OpenWindows 3.4 FCS*/
#define  X_DgaGrabDrawable     21
#define  X_DgaUnGrabDrawable   22

/* additional protocol requests in Protocol Version 4 - OpenWindows 3.6 FCS*/
#define X_DgaGrabABuffers      23
#define X_DgaUnGrabABuffers    24

#define X_DgaXineramaInfo	25

/*
** Types of grabbable drawables
*/

#define DGA_PROTO_WINDOW  0
#define DGA_PROTO_PIXMAP  1
#define DGA_PROTO_OVERLAY 2

/*
 * DGA request structure
 */

#define sz_xDGAReq 12

typedef struct {
    CARD8 reqType;
    BYTE pad;
    CARD16 length B16;
    CARD32 id B32;  /* a Window, Drawable, Font, GContext, Pixmap, etc. */
    CARD32 number_objects B32;
    } xDGAReq;

/* DGA Ancillary Buffer request structure */
typedef struct {
    CARD8 reqType;
    BYTE pad;
    CARD16 length B16;
    CARD32 id B32;  /* a Window, Drawable, Font, GContext, Pixmap, etc. */
    CARD32 type B32;
    CARD32 buffer_site B32;
    } xDgaGrabABuffersReq;

#define sz_xDgaGrabABuffersReq (sizeof(xDgaGrabABuffersReq))
 
/*
 * DGA shared retained path request structure
 */

#define xDGARtndPathLength	200
#define sz_xDGARtndPathReply	(sizeof(xDGARtndPathReply))

typedef struct {
    BYTE type;                        /* X_Reply */
    CARD8 pad;
    CARD16 sequenceNumber B16;
    CARD32 length B32;        
    INT8  path[xDGARtndPathLength];         
    } xDGARtndPathReply;     



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


struct dga_extinfo {
	int protocol_major_version;	/* major version num of DGA protocol */
	int protocol_minor_version;	/* minor version num of DGA protocol */
	int extension;			/* extension number */
	int major_opcode;		/* major op-code assigned by server */
	};


struct dga_xwinrec {
	struct dga_xwinrec	*next;
	Dga_token		token;
	Display			*dpy;
	Window			win;
	int			refcnt;
	};

struct dga_xpixrec {
    struct dga_xpixrec  *next;
    Dga_token       token;
    Display         *dpy;
    Pixmap          pix;
    int         refcnt;
    };
 


#endif /* _DGA_XREQUESTS_H */
