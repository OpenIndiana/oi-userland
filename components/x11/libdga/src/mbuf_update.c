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
** mbuf_update.c
**
** Routines of the update phase for multibuffers.
*/

#include <assert.h>
#ifdef SERVER_DGA
#include <X11/Xlib.h>
#endif /* SERVER_DGA */
#include "dga_incls.h"
#include "pix_grab.h"
#include "mbufsetstr.h"

static void	dgai_mbuf_getLastSeqs (_Dga_window dgawin, DgaLastSeqsPtr pLastSeqs, short bufIndex);
static int	dgai_mbuf_syncAgain (_Dga_window dgawin, DgaLastSeqsPtr pLastSeqs);
static void	dgai_mbuf_mb_update (_Dga_window dgawin);
static void	dgai_mbuf_syncLockSubj (_Dga_window dgawin);
static void	dgai_mbuf_figureDerivChgs (_Dga_window dgawin);

/*
** Note: On every alias or mbufset change, we will report the following
** types of changes. See comment at start of win_update.c for reason why we
** don't try to optimize change reporting.  
**
**	site
**	clip
**	curs
**      bstore
**	cache (nonviewable mbufs only)
**
** TODO: ISSUE: since an alias change occurs on every multibuffer frame,
** if we don't optimize for multibuffers this could add unwanted per-frame 
** overhead.  Is it significant?  If so, we are forced to optimize alias 
** change reporting.  Composition changes are so infrequent that it still 
** won't be worth optimizing the reporting of them. (Note: this issue 
** doesn't apply to windows.)
*/


/*
** ENTRY ROUTINE FOR MULTIBUFFER UPDATE PHASE 
*/

int
dgai_mbuf_update (_Dga_window dgawin, short bufIndex)
{
    DgaLastSeqs		lastSeqs;
    DgaMbufSetPtr	pMbufSet;

    /*
     * Before we get going check to make sure that composition changes
     * have been noticed.  If we don't and the number of multibuffers
     * has increased bad things will happen.
     */

    if (dgawin->c_mbufseq != *dgawin->s_mbufseq_p)
	dgai_mbsmemb_syncMbufset(dgawin);

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

    pMbufSet = dgawin->pMbs;
    /* Determine sequence counts for state reported to client */
    dgai_mbuf_getLastSeqs(dgawin, &lastSeqs, bufIndex);

    /* start accumulating changes */
    dgawin->changeMask = 0;

    /* repeat synchronization functions as needed through possible unlock/relocks */
    do {

	/* first, see if the window shared info is still valid */
	if (dgai_mbsmemb_syncZombie(dgawin)) {
	    break;
        }

	/* the first thing we must change is the multibuffer state.
	   This may later the effective lock subject, whose type the
	   other synchronization checks depend on */
	if (lastSeqs.mbufseq != *dgawin->s_mbufseq_p) {
	    dgai_mbuf_mb_update(dgawin);
	    lastSeqs.mbufseq = *dgawin->s_mbufseq_p;
	    pMbufSet->mbufseq[bufIndex] = lastSeqs.mbufseq;
	}

	/* synchronize with current changes to attributes of
	   the effective lock subject -- depends on the type
	   of the current lock subject */
	if        (DGA_LOCKSUBJ_WINDOW(dgawin, dgawin->eLockSubj)) {
	    dgai_win_syncChanges(dgawin, &lastSeqs);
	} else if (DGA_LOCKSUBJ_VMBUFFER(dgawin, dgawin->eLockSubj)) {
	    dgai_vmbuf_syncChanges(dgawin, &lastSeqs, bufIndex);
	} else if (DGA_LOCKSUBJ_NMBUFFER(dgawin, dgawin->eLockSubj)) {
	    dgai_nmbuf_syncChanges(dgawin);
	} else {
	    /* should never happen */
	    assert(0);
	}

	/* Note: whether we need to sync again depends on the type too */
    } while (dgai_mbuf_syncAgain(dgawin, &lastSeqs));

    /* Check if the devinfo has changed */
    dgai_mbsmemb_devinfo_update(dgawin);

    /* 
    ** 2. The foregoing synchronization step has determined whether 
    **    any attribute changes have occurred.  We must now determine
    **    if there are any derivative changes to report.
    */
    dgai_mbuf_figureDerivChgs(dgawin);


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

    /* if there are still any changes that were not notified through notification
       functions, DGA_DRAW_MODIF will return nonzero (the client is
       supposed to call this routine immediately following the lock).
       This will cause a well-behaved client to synchronize with 
       the remaining unreported changes */
    return (dgawin->changeMask);
}


static void
dgai_mbuf_getLastSeqs (_Dga_window dgawin, DgaLastSeqsPtr pLastSeqs, short bufIndex)
{
    DgaMbufSetPtr	pMbufSet = dgawin->pMbs;

    if (DGA_LOCKSUBJ_WINDOW(dgawin, dgawin->eLockSubj)) {
        pLastSeqs->mbufseq = dgawin->c_mbufseq;
        pLastSeqs->clipseq = dgawin->c_clipseq;
        pLastSeqs->curseq = dgawin->c_curseq;
        pLastSeqs->rtnseq = dgawin->c_rtnseq;
    } else {
        pLastSeqs->mbufseq = pMbufSet->mbufseq[bufIndex];
        pLastSeqs->clipseq = pMbufSet->clipseq[bufIndex];
        pLastSeqs->curseq = pMbufSet->curseq[bufIndex];
        pLastSeqs->rtnseq = dgawin->c_rtnseq;
    }
}


/*
** Returns nonzero if we are still not synchronized 
*/

static int
dgai_mbuf_syncAgain (_Dga_window dgawin, DgaLastSeqsPtr pLastSeqs)
{
    /* if a multibuffer change happened, we're still not done */
    if (pLastSeqs->mbufseq != *dgawin->s_mbufseq_p) {
	return (1);
    }

    if (DGA_LOCKSUBJ_WINDOW(dgawin, dgawin->eLockSubj)) {
	if ((pLastSeqs->clipseq == *dgawin->s_clipseq_p)  &&
	    (pLastSeqs->curseq  == *dgawin->s_curseq_p)   &&
	    (pLastSeqs->rtnseq  == *dgawin->s_rtnseq_p)) {
	    return (0);
	}
    } else if (DGA_LOCKSUBJ_VMBUFFER(dgawin, dgawin->eLockSubj)) {
	if ((pLastSeqs->clipseq == *dgawin->s_clipseq_p)  &&
	    (pLastSeqs->curseq  == *dgawin->s_curseq_p)) {
	    /* Note: viewable mbuf never has bstore to sync up to */
	    return (0);
	}
    } else if (DGA_LOCKSUBJ_NMBUFFER(dgawin, dgawin->eLockSubj)) {
	/* Note: we don't need to check the cacheseq here, because for
	   a nonviewable drawable the cache is the only thing to sync 
	   so there will never be any reason for it to be out-of-sync 
	   when we get here */
        return (0);
    }

    /* we're now all synchronized */
    return (1);
}


/* 
** Called at window lock time when we have detected an mbufset change.
** At the return of this routine, dgawin->eLockSubj indicates the member
** drawable for which subsequent changes are to be detected.
*/

static void
dgai_mbuf_mb_update (_Dga_window dgawin)
{
    /* react to enable and composition changes */
    dgai_mbsmemb_syncMbufset(dgawin);

    /* if window is multibuffered we may need to synchronize */
    if (dgawin->pMbs) {
	WXINFO	*infop;
	
	infop = (WXINFO *) dgawin->w_info;

	/* Now that we know the current mbufset composition, we know the
	   number of multibuffers. if the real lock subject is beyond
	   this, treat it as a zombie */
	if (dgawin->rLockSubj != -1 &&
	    dgawin->rLockSubj >= infop->wx_dbuf.number_buffers) {
	    dgawin->changeMask |= DGA_CHANGE_ZOMBIE;
	    return;
	}	    

	/* synchronize with any display buffer change */
	dgai_mbuf_syncLockSubj(dgawin);

	/* synchronize render buffer state (if necessary) */
	dgai_mbsmemb_syncRendBuf(dgawin);

    } else {
	/* The window is no longer multibuffered. This multibuffer is a zombie */
	dgawin->changeMask |= DGA_CHANGE_ZOMBIE;
	return;
    }

    /* an mbufset change causes us to report changes to all attrs  */
    { u_int reportChanges;
      if (DGA_LOCKSUBJ_WINDOW(dgawin, dgawin->eLockSubj)) {
	  reportChanges = DGA_WIN_CHANGEABLE_ATTRS;
      } else if (DGA_LOCKSUBJ_VMBUFFER(dgawin, dgawin->eLockSubj)) {
	  reportChanges = DGA_VMBUF_CHANGEABLE_ATTRS;
      } else {
	  reportChanges = DGA_NMBUF_CHANGEABLE_ATTRS;
      }
      dgawin->changeMask |= (DGA_CHANGE_MBUFSET | reportChanges);
    }
}

/*
** Determine effective lock subject for a multibuffered window.
*/

static void
dgai_mbuf_syncLockSubj (_Dga_window dgawin)
{
    WXINFO	*infop;
	
    infop = (WXINFO *) dgawin->w_info;

    /* see if there is buffer aliasing.  Buffer aliasing
       can only happen in copy flip mode */
    /* TODO Daryl  Is this true?  In document it talks about
     * buffer aliasing with DGA_MBFLIP_VIDEO mode. */
    if ((infop->w_mbsInfo.flipMode == DGA_MBFLIP_COPY) &&
	(infop->wx_dbuf.display_buffer == dgawin->rLockSubj)) {
	
	/* when the buffer is aliased, the effective lock subject is
	   always the main window */
	dgawin->eLockSubj = -1;

	if (dgawin->eLockSubj != dgawin->eLockSubjPrev) {

	    /* an alias change causes us to report changes on all attributes */
	    dgawin->changeMask |= (DGA_CHANGE_ALIAS | DGA_WIN_CHANGEABLE_ATTRS);

	}
    }
}


/*
** In addition to the mbufset-common types of derivative changes, 
** we may also need to cause a clip change to be reported.
*/

static void
dgai_mbuf_figureDerivChgs (_Dga_window dgawin)
{
    int 	curViewable;
    int		prevViewable;

    /* common changes */
    dgai_mbsmemb_figureDerivChgs(dgawin);

    /* 
    ** If we've switched from a viewable lock subject to 
    ** a nonviewable one (or vice versa) force a clip change even
    ** if the clip of the current effective lock subject has not changed.
    ** This is because the clips of nonviewable drawables are
    ** always rectangular and those of viewable ones may not be.
    */
    curViewable = DGA_LOCKSUBJ_VALID(dgawin, dgawin->eLockSubj) &&
                  (dgawin->eLockSubj == -1 || 
		   DGA_MBUF_ISVIEWABLE(dgawin->pMbs, dgawin->eLockSubj));
    prevViewable = DGA_LOCKSUBJ_VALID(dgawin, dgawin->eLockSubjPrev) &&
                  (dgawin->eLockSubjPrev == -1 || 
		   DGA_MBUF_ISVIEWABLE(dgawin->pMbs, dgawin->eLockSubjPrev));
    
    if ((curViewable && !prevViewable) || 
	(!curViewable && prevViewable)) {
	dgawin->changeMask |= DGA_CHANGE_CLIP;
    }
}


/*
** Current lock subject is a viewable multibuffer. Synchronize with changes.
*/

void
dgai_vmbuf_syncChanges (_Dga_window dgawin, DgaLastSeqsPtr pLastSeqs, short bufIndex)
{
    /* Note: viewable multibuffers share the clip and cursor state 
       of the main window */

    /* clip state of main window has changed? */
    if (pLastSeqs->clipseq != *dgawin->s_clipseq_p) {
	dgawin->changeMask |= DGA_CHANGE_CLIP;
	dgai_win_clip_update(dgawin);
	pLastSeqs->clipseq = *dgawin->s_clipseq_p;
	dgawin->pMbs->clipseq[bufIndex] = pLastSeqs->clipseq;
    }

    /* cursor state of main window has changed? */
    if (pLastSeqs->curseq != *dgawin->s_curseq_p) {
	dgawin->changeMask |= DGA_CHANGE_CURSOR;
	dgai_win_curs_update(dgawin);
	pLastSeqs->curseq = *dgawin->s_curseq_p;
	dgawin->pMbs->curseq[bufIndex] = pLastSeqs->curseq;
    }

    /* Note: viewable multibuffers do not yet have backing store */
}


/*
** Current lock subject is a non-viewable multibuffer. Synchronize with changes.
*/

void
dgai_nmbuf_syncChanges (_Dga_window dgawin)
{
    SHARED_PIXMAP_INFO	*infop;

    /* don't try to synchronize if multibuffer is a zombie */
    if ((dgawin->changeMask & DGA_CHANGE_ZOMBIE)) {
	return;
    }

    /* first, see if the shared info is still valid */
    infop = dgawin->pMbs->pNbShinfo[dgawin->eLockSubj];
    if (infop->obsolete) {
        dgawin->changeMask |= DGA_CHANGE_ZOMBIE;
	return;
    }

    /* Note: a non-viewable multibuffer never has a cursor
       or backing store.  And it's clip is always constant.  The
       only thing that can change is the cache or devinfo state */

    /* Has the cache changed? */
    dgai_nmbuf_cache_update(dgawin);

    /* Has the dev_info changed? */
    dgai_nmbuf_devinfo_update(dgawin);
}


void 
dgai_nmbuf_cache_update (_Dga_window dgawin) 
{
    DgaMbufSetPtr 		pMbs;
    u_int			*s_cacheseq_p;

    pMbs = dgawin->pMbs;
    s_cacheseq_p = &(pMbs->pNbShinfo[dgawin->eLockSubj]->s_cacheseq);

    if (pMbs->cacheSeqs[dgawin->eLockSubj] != *s_cacheseq_p) {
	dgawin->changeMask |= DGA_CHANGE_CACHE;

	/* synchronize change counts */
	pMbs->cacheSeqs[dgawin->eLockSubj] = *s_cacheseq_p;
    }
}

void 
dgai_nmbuf_devinfo_update (_Dga_window dgawin) 
{
    DgaMbufSetPtr 		pMbs;
    u_int			*s_devinfoseq_p;

    pMbs = dgawin->pMbs;
    s_devinfoseq_p = &(pMbs->pNbShinfo[dgawin->eLockSubj]->s_devinfoseq);

    if (pMbs->devInfoSeqs[dgawin->eLockSubj] != *s_devinfoseq_p) {
	dgawin->changeMask |= DGA_CHANGE_DEVINFO;

	/* synchronize change counts */
	pMbs->devInfoSeqs[dgawin->eLockSubj] = *s_devinfoseq_p;
    }
}



