/* Copyright (c) 1993, 1994, Oracle and/or its affiliates. All rights reserved.
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


#ifndef	_DGA_MBUFSETSTR_H
#define	_DGA_MBUFSETSTR_H

/*
** Client structure for multibuffer set.
*/

/*
** A "multibuffer set" (mbufset) stores client-side info about the multibuffers
** attached to a multibuffered window.
*/

typedef struct dga_mbufset {
    unsigned int	refcnt;
    short		numBufs;
    _Dga_pixmap		pNbPixmaps[DGA_MAX_GRABBABLE_BUFS];	

    /* shared info for nonviewable mbufs.  Indices that
       correspond to viewable mbufs are always NULL */
    SHARED_PIXMAP_INFO	*pNbShinfo[DGA_MAX_GRABBABLE_BUFS];	

    u_int		mbufseq[DGA_MAX_GRABBABLE_BUFS];
    u_int		clipseq[DGA_MAX_GRABBABLE_BUFS];
    u_int		curseq[DGA_MAX_GRABBABLE_BUFS];

    /* last recorded cache count for nonviewable mbufs.  Indices that
       correspond to viewable mbufs are always 0 */
    u_int		cacheSeqs[DGA_MAX_GRABBABLE_BUFS];	

    /* last recorded cache count for nonviewable mbufs.  Indices that
       correspond to viewable mbufs are always 0 (viewable mbufs 
       don't have devce info) */
    u_int		devInfoSeqs[DGA_MAX_GRABBABLE_BUFS];	

    /* Has the buffer been locked previously? */
    char		prevLocked[DGA_MAX_GRABBABLE_BUFS];

} DgaMbufSet;


#endif /* _DGA_MBUFSETSTR_H */

