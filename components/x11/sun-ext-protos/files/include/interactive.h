/*
 * Copyright (c) 1993, 1994, Oracle and/or its affiliates. All rights reserved.
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

/************************************************************
	Protocol defs for XIA extension
********************************************************/

/* THIS IS NOT AN X CONSORTIUM STANDARD */

#ifndef _INTERACTIVE_H
#define _INTERACTIVE_H


#include <X11/Xproto.h>

#include "interactiveCommon.h"

#define X_IAQueryVersion                0
#define X_IASetProcessInfo              1
#define X_IAGetProcessInfo              2

#define IANumberEvents                  0
#define IANumberErrors                  0

typedef int ConnectionPidRec;
typedef int * ConnectionPidPtr;

#define IANAME "SolarisIA"

#define IA_MAJOR_VERSION	1	/* current version numbers */
#define IA_MINOR_VERSION	1

typedef struct _IAQueryVersion {
    CARD8	reqType;		/* always IAReqCode */
    CARD8	IAReqType;		/* always X_IAQueryVersion */
    CARD16	length B16;
} xIAQueryVersionReq;
#define sz_xIAQueryVersionReq	4

typedef struct {
    BYTE	type;			/* X_Reply */
    CARD8	pad;			/* padding */
    CARD16	sequenceNumber B16;
    CARD32	length B32;
    CARD16	majorVersion B16;	/* major version of IA protocol */
    CARD16	minorVersion B16;	/* minor version of IA protocol */
    CARD32	pad1 B32;
    CARD32	pad2 B32;
    CARD32	pad3 B32;
    CARD32	pad4 B32;
    CARD32	pad5 B32;
} xIAQueryVersionReply;
#define sz_xIAQueryVersionReply	32

typedef struct _IASetProcessInfo {
    CARD8	reqType;		/* Always IAReqCode */
    CARD8	connectionAttrType;	/* What attribute */
    CARD16	length B16;		/* Request length */
    CARD32	flags B32;		/* Request flags */
    CARD32	uid B32;		/* requestor's uid */
} xIASetProcessInfoReq;
#define sz_xIASetProcessInfoReq	12	

typedef struct _IAGetProcessInfo {
    CARD8	reqType;		/* Always IAReqCode */
    CARD8	connectionAttrType;	/* What attribute */
    CARD16	length;			/* Request length */
    CARD32	flags B32;		/* Request flags */
} xIAGetProcessInfoReq;
#define sz_xIAGetProcessInfoReq	8

typedef struct {
    BYTE	type;			/* X_Reply */
    CARD8	pad;			/* padding */
    CARD16	sequenceNumber B16;
    CARD32	length B32;
    CARD32	count B32;
    CARD32	pad1 B32;
    CARD32	pad2 B32;
    CARD32	pad3 B32;
    CARD32	pad4 B32;
    CARD32	pad5 B32;
} xIAGetProcessInfoReply;

#define sz_xIAGetProcessInfo 32

#endif 
