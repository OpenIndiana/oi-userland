/* Copyright (c) 1993, 1997, Oracle and/or its affiliates. All rights reserved.
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
** mbufset.c - Routines to manipulate multibuffer set objects.
*/

#include <malloc.h>
#ifdef SERVER_DGA
#include <X11/Xlib.h>
#endif /* SERVER_DGA */
#include "dga_incls.h"
#include "pix_grab.h"
#include "mbufsetstr.h"

static void dgai_mbufset_destroy (DgaMbufSetPtr pMbs);

extern int dga_pixlist_add(Dga_token token, Display *dpy, Pixmap pix);

/*
** Create a client-side multibuffer set object based on information
** in the shinfo of a window.  The window must be locked prior to calling.
*/

DgaMbufSetPtr
dgai_mbufset_create (_Dga_window dgawin)
{
    DgaMbufSetPtr 	pMbs;
    WXINFO		*infop;
    DgaMbufSetShinfoPtr	pMbsInfo;
    short		numBufs, i;
    unsigned long	bufViewableFlags, bufMask;
    Dga_token		token;
    _Dga_pixmap		dgapix;
    XID			*pShinfoId;

    infop = (WXINFO *) dgawin->w_info;
    pMbsInfo = &infop->w_mbsInfo;    
    token = (Dga_token) pMbsInfo->nmbufShpxToken;
    pShinfoId = &(pMbsInfo->nmbufIds[0]);

    /* allocate mbufset client structure */
    if (!(pMbs = (DgaMbufSetPtr) malloc(sizeof(DgaMbufSet)))) {
	return (NULL);
    }

    numBufs = infop->wx_dbuf.number_buffers;
    pMbs->numBufs = numBufs;

    for (i = 0; i < numBufs;  i++) {
	pMbs->pNbPixmaps[i] = NULL;
    }

    bufViewableFlags = pMbsInfo->bufViewableFlags;
    bufMask = 1L;
    for (i = 0; i < numBufs;  i++, pShinfoId++) {
	if (!(bufViewableFlags & bufMask)) {
	    if (!dga_pixlist_add(token, dgawin->w_dpy, (Pixmap)*pShinfoId) ||
	        !(dgapix = dga_pix_grab(token, (Pixmap)*pShinfoId))) {
		goto Bad;
	    }
	    pMbs->pNbPixmaps[i] = dgapix;
	    pMbs->pNbShinfo[i] = (SHARED_PIXMAP_INFO *)dgapix->p_infop;
	} else {
	    pMbs->pNbShinfo[i] = NULL;
	}
	pMbs->mbufseq[i] = 0;
	pMbs->clipseq[i] = 0;
	pMbs->curseq[i] = 0;
	pMbs->cacheSeqs[i] = 0;
	pMbs->devInfoSeqs[i] = 0;
	pMbs->prevLocked[i] = 0;
	bufMask = bufMask << 1;
    }

    /* success */
    pMbs->refcnt = 1;
    return (pMbs);

Bad:
    dgai_mbufset_destroy(pMbs);
    return (NULL);
}


void
dgai_mbufset_incref (DgaMbufSetPtr pMbs)
{
    pMbs->refcnt++;
}


static void
dgai_mbufset_destroy (DgaMbufSetPtr pMbs)
{
    short i;

    for (i = 0; i < pMbs->numBufs;  i++) {
	if (pMbs->pNbPixmaps[i]) {
	    dga_pix_ungrab(pMbs->pNbPixmaps[i]);
	}
    }
    free(pMbs);
}

void
dgai_mbufset_decref (DgaMbufSetPtr pMbs)
{
    if ((int)(--(pMbs->refcnt)) <= 0) {
	dgai_mbufset_destroy(pMbs);
    }
}


