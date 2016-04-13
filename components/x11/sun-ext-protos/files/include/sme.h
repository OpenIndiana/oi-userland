/* Copyright (c) 1995, 2004, Oracle and/or its affiliates. All rights reserved.
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
Copyright 1989 by The Massachusetts Institute of Technology
 
Permission to use, copy, modify, and distribute this
software and its documentation for any purpose and without
fee is hereby granted, provided that the above copyright
notice appear in all copies and that both that copyright
notice and this permission notice appear in supporting
documentation, and that the name of MIT not be used in
advertising or publicity pertaining to distribution of the
software without specific prior written permission.
M.I.T. makes no representation about the suitability of
this software for any purpose. It is provided "as is"
without any express or implied warranty.
 
MIT DISCLAIMS ALL WARRANTIES WITH REGARD TO  THIS  SOFTWARE,
INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FIT-
NESS FOR A PARTICULAR PURPOSE. IN NO EVENT SHALL SUN BE  LI-
ABLE  FOR  ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR
ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE,  DATA  OR
PROFITS,  WHETHER  IN  AN  ACTION OF CONTRACT, NEGLIGENCE OR
OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION  WITH
THE USE OR PERFORMANCE OF THIS SOFTWARE.
 
********************************************************/

#ifndef _SME_H_
#define _SME_H_

#include <X11/Xmd.h>
#include <thread.h>
#include <synch.h>

typedef struct _xSMEReq {
    CARD8 reqType;
    CARD8 subReqType;
    CARD16 length B16;
    CARD32 xsunsmesize B32;
} xSMEReq;

#define sz_xSMEReq  8
#define SMENAME "SUN_SME"
#define SMEFILE "/tmp/.X11-sme"

typedef struct _xSmeConnInitReply {
    BYTE type;              /* X_Reply */
    BYTE status;
    CARD16 sequenceNumber B16;  /* of last request received by server */
    CARD32 length B32;
    CARD32 client_index B32;   	/* client index to be used in opening sme*/
    CARD32 pad1 B32;		/* Pad to standard reply size */
    CARD32 pad2 B32;
    CARD32 pad3 B32;
    CARD32 pad4 B32;
    CARD32 pad5 B32;
} xSmeConnInitReply;

/* "Sme2" in hex */
#define SME_MAGIC2	0x53686d32
/* "Sme3" in hex */
#define SME_MAGIC3	0x53686d33
/* "Sme4" in hex */
#define SME_MAGIC4	0x53686d34

/*
 * Add a few more fields to shared memory data structures for
 * debugging.
 */

#define INIT_SME_CONN	1
#define START_SME_CONN	2

#define SMECONNQSIZE	512		/* Total number of allocation
					 * chunks that can be queued in
					 * the fifo. */
/*
 * Shared memory structure
 */
typedef struct _smeRegion {
	INT32	smeMagic;
	INT32	smeHeapSize;		/* Total number of bytes in heap */
	INT32	smeBufferSize;          /* Allocation chunk within heap */
	volatile INT32	smeClientBufferBlocked;
	mutex_t	smeBufferMutex;
	cond_t	smeBufferCV;
	volatile INT32	smeIn;
	volatile INT32	smeOut;
	volatile INT32	smeHeadptr;	/* Relative ptr to first free byte in
					 * the heap.  Only the client updates 
					 * this. */
	volatile INT32	smeTailptr;	/* Relative ptr to the last free byte
					 * in the heap.  Only the server 
					 * updates this. */
	struct smeQueueEntry {
		volatile INT32	bufp;
		volatile INT32	msgSize;
		} smeQueue[SMECONNQSIZE];
} smeRegion;

#endif /* _SME_H_ */
