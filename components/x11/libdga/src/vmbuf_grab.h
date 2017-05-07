/* Copyright (c) 1993, Oracle and/or its affiliates. All rights reserved.
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
 * vmbuf_grab.h - Viewable multibuffer shared file definition
 */

#ifndef _VMBUF_GRAB_H
#define _VMBUF_GRAB_H

/* 
** Currently, the code for the viewable multibuffer shared info is commented
** out because there is nothing to put in it.  If something needs to be
** added, define this symbol and complete the code (warning: the code 
** for this is not yet fully complete).
*/
#undef VBSHINFO

#ifdef VBSHINFO

#define	VBMAGIC	0x47524143	/* "GRABBED VIEWABLE MULTIBUFFERS" */
#define VBVERS          4	/* multibuffer grabber version */

typedef	struct _vbinfo
{
    /* Shared data */
    long	magic;		/* magic number: VBMAGIC */
    long	version;	/* version: VBVERS */
    Dga_token	winToken;	/* opaque cookie for shinfo of main window */

    u_int	masterChngCnt;	/* bumped when anything changes in any buffer */
    u_int	chngCnts[DGA_MAX_GRABBABLE_BUFS];	
    				/* change counts for individual buffers */

    /* Server only data */
    u_long	s_filesuffix;	/* "cookie" for info file */
    u_char	*s_wxlink;	/* server's ptr to shinfo of main window */

    /* FUTURE: may include backing store information */

} VBINFO;

#endif /*VBSHINFO*/

#endif /* _VMBUF_GRAB_H */
