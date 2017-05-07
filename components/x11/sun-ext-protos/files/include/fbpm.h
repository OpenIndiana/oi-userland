/*
 * Copyright (c) 1999, 2003, Oracle and/or its affiliates. All rights reserved.
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


#define FBPMModeOn	0
#define FBPMModeStandby	1
#define FBPMModeSuspend	2
#define FBPMModeOff	3

#define DDXStatError 0
#define DDXStatFbOk  1
#define DDXStatMonOk 2
#define DDXStatOk	(DDXStatFbOk | DDXStatMonOk)

#ifndef DPMS_SERVER

Bool FBPMQueryExtension(
#if NeedFunctionPrototypes
Display *, 
int *, 
int *
#endif
);
Status FBPMGetVersion(
#if NeedFunctionPrototypes
Display *, 
int *, 
int *
#endif
);
Bool FBPMCapable(
#if NeedFunctionPrototypes
Display *
#endif
);
Bool FBPMEnable(
#if NeedFunctionPrototypes
Display *, 
int
#endif
);
Status FBPMDisable(
#if NeedFunctionPrototypes
Display *
#endif
);
Status FBPMForceLevel(
#if NeedFunctionPrototypes
Display *, 
CARD16
#endif
);
Status FBPMInfo(
#if NeedFunctionPrototypes
Display *, 
CARD16 *, 
BOOL *
#endif
);

#endif
