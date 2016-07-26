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


/*
**
** win_update.c
**
** Routines of the update phase for windows.
*/

#include <assert.h>
#ifdef SERVER_DGA
#include <X11/Xlib.h>
#endif /* SERVER_DGA */
#include "dga_incls.h"
#include "pix_grab.h"
#include "mbufsetstr.h"
#include "rtn_grab.h"

static void	dgai_win_getLastSeqs (_Dga_window dgawin, DgaLastSeqsPtr pLastSeqs);
static int	dgai_win_syncAgain (_Dga_window dgawin, DgaLastSeqsPtr pLastSeqs);
static void 	dgai_win_mb_update (_Dga_window dgawin);
static void	dgai_mbwin_syncLockSubj (_Dga_window dgawin);


/*
** Note: for the sake of simplicity, we always report the following
** types of changes whenever an alias or mbufset composition change
** occurs.  We could try to optimize the change reporting and only
** report an attribute change if we know that the attribute has definitely
** changed since the last lock.  But this requires a lot of comparison
** between the current and previous lock subjects and the decision
** tree gets quite large.  This method of "over reporting" may result 
** in some redundant change reports.  If we want to do this type of optimization
** in the future, we still can.  But for now we keep it simple.
**
** These are the window changes that are automatically reported whenever
** an alias or mbufset composition change occurs.
**
**	site
**	clip
**	curs
**      bstore
*/


/*
** ENTRY ROUTINE FOR WINDOW UPDATE PHASE 
*/

int
dgai_win_update (_Dga_window dgawin, short bufIndex)
{
    DgaLastSeqs	lastSeqs;

    /*
    ** 1. The first thing we do in the update phase is to synchronize
    **    the client structure.  When all pertinent client change
    **    counters match the server, we are synchronized.  The 
    **    reason we must do this in a loop is that some of the
    **    synchronizations require us to temporarily unlock and 
    **    relock.  While the drawable is unlocked, it can undergo
    **    more changes, so we may need to start the synchronization
    **    process over.
    */

    /* Determine sequence counts for state reported to client */
    dgai_win_getLastSeqs(dgawin, &lastSeqs);

    /* start accumulating changes */
    dgawin->changeMask = 0;

    /* repeat synchronization functions as needed through possible unlock/relocks */
    do {

	/* first, see if the window shared info is still valid */
	if (dgai_mbsmemb_syncZombie(dgawin)) {
	    break;
        }

	/* next, we must check the multibuffer state.
	   This may alter the effective lock subject, whose type the
	   other synchronization checks depend on */
	if (lastSeqs.mbufseq != *dgawin->s_mbufseq_p) {
	    dgai_win_mb_update(dgawin);
	    lastSeqs.mbufseq = *dgawin->s_mbufseq_p;
	    dgawin->c_mbufseq = lastSeqs.mbufseq;
	}

	/* synchronize with current changes to attributes of
	   the effective lock subject -- depends on the type
	   of the current lock subject */
	if        (DGA_LOCKSUBJ_WINDOW(dgawin, dgawin->eLockSubj)) {
	    dgai_win_syncChanges(dgawin, &lastSeqs);
	} else if (DGA_LOCKSUBJ_VMBUFFER(dgawin, dgawin->eLockSubj)) {
	    dgai_vmbuf_syncChanges(dgawin, &lastSeqs, bufIndex);
	} else {
	    /* should never happen */
	    assert(0);
	}

	/* Note: whether we need to sync again depends on the type too */
    } while (dgai_win_syncAgain(dgawin, &lastSeqs));

    /* Check if the devinfo has changed */
    dgai_mbsmemb_devinfo_update(dgawin);

    /* 
    ** 2. The foregoing synchronization step has determined whether 
    **    any attribute changes have occurred.  We must now determine
    **    if there are any derivative changes to report.
    **
    **    Currently, the only derivative changes for a window or viewable 
    ** 	  multibuffer are those in common with all mbufset members.
    */
    dgai_mbsmemb_figureDerivChgs(dgawin);

    /* 
    ** 3. Next, we must report changes through notification functions,
    **    if possible.
    */

    /* report any changes that we can through notification */
    dgai_mbsmemb_notify(dgawin);


    /* 
    ** 4. Lastly, indicate that we are fully synchronized and get out.
    */

    /* the dgawin client structure is now fully synchronized with the
       shared info */
    dgawin->c_wm_chngcnt[bufIndex + 1] = *dgawin->s_chngcnt_p;

    /*
    ** 5. If this is an overlay window, then we need to tell the
    **    server that we may have modified the opaque shape.
    */
    if (dgawin->isOverlay && dgawin->c_ovlstate != DGA_OVLSTATE_CONFLICT)
	*dgawin->s_ovlshapevalid_p = 0;

    /* if there are still any changes that were not notified through notification
       functions, DGA_DRAW_MODIF will return nonzero (the client is
       supposed to call this routine immediately following the lock).
       This will cause a well-behaved client to synchronize with 
       the remaining unreported changes */
    return (dgawin->changeMask);
}


static void
dgai_win_getLastSeqs (_Dga_window dgawin, DgaLastSeqsPtr pLastSeqs)
{
    pLastSeqs->mbufseq = dgawin->c_mbufseq;
    pLastSeqs->clipseq = dgawin->c_clipseq;
    pLastSeqs->curseq = dgawin->c_curseq;
    pLastSeqs->rtnseq = dgawin->c_rtnseq;
}


/*
** Returns nonzero if we are still not synchronized 
*/

static int
dgai_win_syncAgain (_Dga_window dgawin, DgaLastSeqsPtr pLastSeqs)
{
    /* if a multibuffer change happened, we're still not done */
    if (pLastSeqs->mbufseq != *dgawin->s_mbufseq_p) {
	return (1);
    }

    /* Note: there's no need to check cacheseq because the effective lock subject
       of a window can only be a window or viewable multibuffer.
       Neither of these are cached */	

    if (DGA_LOCKSUBJ_WINDOW(dgawin, dgawin->eLockSubj)) {
	if ((pLastSeqs->clipseq == *dgawin->s_clipseq_p)  &&
	    (pLastSeqs->curseq  == *dgawin->s_curseq_p)   &&
	    (pLastSeqs->rtnseq  == *dgawin->s_rtnseq_p)   &&
	    (!dgawin->isOverlay
	     || dgawin->c_ovlstate == *dgawin->s_ovlstate_p)) {
	    return (0);
	}
    } else if (DGA_LOCKSUBJ_VMBUFFER(dgawin, dgawin->eLockSubj)) {
	if ((pLastSeqs->clipseq == *dgawin->s_clipseq_p)  &&
	    (pLastSeqs->curseq  == *dgawin->s_curseq_p)) {
	    /* Note: viewable mbuf never has bstore to sync up to */
	    return (0);
	}
    } else {
	/* should never happen */
	assert(0);
    }

    /* we're not synchronized; need to go around the loop again */
    return (1);
}


/* 
** Called at window lock time when we have detected an mbufset change.
** At the return of this routine, dgawin->eLockSubj indicates the member
** drawable for which subsequent changes are to be detected.
*/

static void
dgai_win_mb_update (_Dga_window dgawin)
{
    /* react to enable and composition changes */
    dgai_mbsmemb_syncMbufset(dgawin);

    /* if window is multibuffered we may need synchronization */
    if (dgawin->pMbs) {

	/* synchronize with any display buffer change */
	dgai_mbwin_syncLockSubj(dgawin);

	/* synchronize render buffer state (if necessary) */
	dgai_mbsmemb_syncRendBuf(dgawin);
    }

    /* an mbufset change causes us to report changes to all attrs  */
    { u_int reportChanges;
      if (DGA_LOCKSUBJ_WINDOW(dgawin, dgawin->eLockSubj)) {
	  reportChanges = DGA_WIN_CHANGEABLE_ATTRS;
      } else if (DGA_LOCKSUBJ_VMBUFFER(dgawin, dgawin->eLockSubj)) {
	  reportChanges = DGA_VMBUF_CHANGEABLE_ATTRS;
      } else {
	  /* should never happen */
	  assert(0);
      }
      dgawin->changeMask |= (DGA_CHANGE_MBUFSET | reportChanges);
    }
}

/*
** Determine effective lock subject for a multibuffered window.
*/

static void
dgai_mbwin_syncLockSubj (_Dga_window dgawin)
{
    WXINFO		*infop;
	
    infop = (WXINFO *) dgawin->w_info;

    /* see if there is window aliasing.  Window aliasing
       can only happen in video flip mode */
    if (infop->w_mbsInfo.flipMode == DGA_MBFLIP_VIDEO) {
	
	/* when the window is aliased, the effective lock subject is the 
	   currently displayed buffer */
	dgawin->eLockSubj = infop->wx_dbuf.display_buffer;

	if (dgawin->eLockSubj != dgawin->eLockSubjPrev) {

	    /* an alias change causes us to report changes on all attributes */
	    dgawin->changeMask |= (DGA_CHANGE_ALIAS | DGA_WIN_CHANGEABLE_ATTRS);

	}
    }
}


/*
** Current lock subject is a window. Synchronize with changes.
*/

void
dgai_win_syncChanges (_Dga_window dgawin, DgaLastSeqsPtr pLastSeqs)
{
    /* clip state has changed? */
    if (pLastSeqs->clipseq != *dgawin->s_clipseq_p) {
	dgawin->changeMask |= DGA_CHANGE_CLIP;
	dgai_win_clip_update(dgawin);
	pLastSeqs->clipseq = *dgawin->s_clipseq_p;
    }

    /* cursor state has changed? */
    if (pLastSeqs->curseq != *dgawin->s_curseq_p) {
	dgawin->changeMask |= DGA_CHANGE_CURSOR;
	dgai_win_curs_update(dgawin);
	pLastSeqs->curseq = *dgawin->s_curseq_p;
    }

    /* backing store state has changed? */
    if ((pLastSeqs->rtnseq != *dgawin->s_rtnseq_p) ||
	((dgawin->rtn_flags & RTN_GRABBED) &&
	 !(dgawin->rtn_flags & RTN_MAPPED))) {
	dgawin->changeMask |= DGA_CHANGE_BSTORE;
	dgai_win_rtn_update(dgawin);
	pLastSeqs->rtnseq = *dgawin->s_rtnseq_p;
    }

    if (dgawin->isOverlay && dgawin->c_ovlstate != *dgawin->s_ovlstate_p) {
	dgawin->changeMask |= DGA_CHANGE_OVLSTATE;
	dgawin->c_ovlstate = *dgawin->s_ovlstate_p;
    }
}




