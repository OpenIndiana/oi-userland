/*
 * Copyright (c) 2010, Oracle and/or its affiliates. All rights reserved.
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

#ifndef _INTERACTIVE_SRV_H
#define _INTERACTIVE_SRV_H

#include <X11/extensions/interactive.h>

#define	UNSET_PRIORITY		0
#define	SET_PRIORITY		1
#define	SET_INTERACTIVE		2

typedef struct _ClientProcessInfo {
    int 		count;
    ConnectionPidPtr	pids;
    Bool		boosted;
} ClientProcessRec, *ClientProcessPtr;

typedef struct {
    ClientProcessPtr    process;	/* Process id information */
    Bool		wmgr;
} IAClientPrivateRec, *IAClientPrivatePtr;


/* Set via xorg.conf option in loadable module */
extern int IADebugLevel;
extern void IAExtensionInit(void);

#endif /* _INTERACTIVE_SRV_H */
