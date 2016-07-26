/* Copyright (c) 1999, Oracle and/or its affiliates. All rights reserved.
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


#define XinID	int
#define MAXSCREEN 16
#define DELTA	int
#define POINT	int
typedef struct subwid
{
	XinID	wid;	/* sub window id */
	DELTA	dx,dy;	/* delta in screen co-ord from virtual zero */
	POINT	x,y;	/* location of window in screen co-ord */
	DELTA 	wdx,wdy;/* size of window in screen co-ord */
}SubWID, *pSubWID;

typedef struct xineramainfo
{
	XinID 	wid;	/* Window ID of requested virtual window */
	SubWID	subs[MAXSCREEN];	/* there will be 16 slots */
}XineramaInfo, *pXineramaInfo;

typedef struct _XDgaXineramaInfoReply
{
	BYTE	type;
	CARD8	unused;
	CARD16	sequenceNumber B16;
	CARD32	length B32;
	XinID 	wid;	/* Window ID of requested virtual window */
	SubWID	subs[MAXSCREEN];	/* there will be 16 slots */
}xDgaXineramaInfoReply;

typedef struct _XDgaXineramaInfoReq
{
	CARD8	reqType;
	CARD8	xdgaReqType;
	CARD16	length B16;
	CARD32	visual B32;
}xDgaXineramaInfoReq;
#define sz_xDgaXineramaInfoReq 8

