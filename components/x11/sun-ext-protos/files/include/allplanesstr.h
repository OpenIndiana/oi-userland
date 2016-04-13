/* Copyright (c) 1990, Oracle and/or its affiliates. All rights reserved.
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


#ifndef _ALLPLANESSTR_H_
#define _ALLPLANESSTR_H_

#include "allplanes.h"

#define ALLPLANESNAME "SUN_ALLPLANES"
#define ALLPLANES_MAJOR_VERSION	1	/* current version numbers */
#define ALLPLANES_MINOR_VERSION	0

typedef struct {
    CARD8       reqType;		/* always AllPlanesReqCode */
    CARD8       allplanesReqType;	/* always X_AllPlanesQueryVersion */
    CARD16	length B16;
} xAllPlanesQueryVersionReq;
#define sz_xAllPlanesQueryVersionReq	4

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
} xAllPlanesQueryVersionReply;
#define sz_xAllPlanesQueryVersionReply	32

typedef struct {
    CARD8       reqType;		/* always AllPlanesReqCode */
    CARD8       allplanesReqType;	/* always X_AllPlanesPolySegment */
    CARD16	length B16;
    Drawable	drawable B32;
} xAllPlanesPolySegmentReq;
#define sz_xAllPlanesPolySegmentReq 8

typedef xAllPlanesPolySegmentReq xAllPlanesPolyRectangleReq;
#define sz_xAllPlanesPolyRectangleReq 8

typedef xAllPlanesPolySegmentReq xAllPlanesPolyFillRectangleReq;
#define sz_xAllPlanesPolyFillRectangleReq 8

typedef struct {
    CARD8       reqType;		/* always AllPlanesReqCode */
    CARD8       allplanesReqType;	/* always X_AllPlanesPolyPoint */
    CARD16	length B16;
    Drawable	drawable B32;
    BYTE	coordMode;
    CARD8	pad0;
    CARD16	pad1 B16;
} xAllPlanesPolyPointReq;
#define sz_xAllPlanesPolyPointReq 12

typedef xAllPlanesPolyPointReq xAllPlanesPolyLineReq;
#define sz_xAllPlanesPolyLineReq 12
#endif /* _ALLPLANESSTR_H_ */
