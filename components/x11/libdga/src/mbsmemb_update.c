/* Copyright (c) 1993, 1999, Oracle and/or its affiliates. All rights reserved.
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
** mbsmemb_update.c
**
** Routines of the update phase that apply equally to both types of
** multibuffer set members, windows and multibuffers.
*/

#include <stdio.h>
#include <sys/types.h>
#ifdef SERVER_DGA
#include <X11/Xlib.h>
#endif /* SERVER_DGA */
#include "dga_incls.h"
#include "pix_grab.h"
#include "mbufsetstr.h"

static void 		dgai_mbsmemb_notifySiteChg (_Dga_window dgawin);
static void		dgai_mbsmemb_notifyMbChg (_Dga_window dgawin);
static void		dgai_mbsmemb_notifyOvlState (_Dga_window dgawin);

/*
** The update phase entry routine for mbufset members.
** Called if the master change count of the shared info
** differs from the last recorded count in the client structure.
*/

int
dgai_mbsmemb_update (Dga_drawable dgadraw, short bufIndex)
{
    _Dga_window dgawin = (_Dga_window) dgadraw;
    int status;

#ifdef MT
    if (dgaMTOn) {
	mutex_lock(dgawin->mutexp);  /* lock the per-window mutex */
	DGA_LOCK(dgadraw);
	/* check the real change count that we saved away */
	if (dgawin->shadow_chngcnt[bufIndex + 1] == *dgawin->s_chngcnt_p) {
	    DGA_UNLOCK(dgadraw);
	    mutex_unlock(dgawin->mutexp);
	    return (0);
	}
    }
    mutex_lock(&dgaGlobalMutex);
#endif
    /* establish the new real lock subject */
    dgawin->rLockSubj = bufIndex;

    /* save last lock subject.  This may be used later in the update phase */
    dgawin->eLockSubjPrev = dgawin->eLockSubj;
    
    /* start out assuming we're not aliased.  This may change if we detect
       aliasing later in the update phase */
    dgawin->eLockSubj = dgawin->rLockSubj;

    /* the first thing we do is distinguish between locking a window
       and a multibuffer.  The update logic is different */
    if (bufIndex == -1) {
	status = dgai_win_update(dgawin, bufIndex);
    } else {
	status = dgai_mbuf_update(dgawin, bufIndex);
    }
#ifdef MT
    if (dgaMTOn) {
	/* save the real change count */
	dgawin->shadow_chngcnt[bufIndex + 1] =
	    dgawin->c_wm_chngcnt[bufIndex + 1];
	/* For the MT case, make sure that this update function gets called
	 * the next time around, so overwrite the change count to make it
	 * different.
	 */
	dgawin->c_wm_chngcnt[bufIndex + 1] = *dgawin->s_chngcnt_p - 1;
	DGA_UNLOCK(dgadraw);
	mutex_unlock(dgawin->mutexp);  /* unlock the per-window mutex */
    }
    mutex_unlock(&dgaGlobalMutex);
#endif
    return (status);
}


/*
** See if the shared info of the main window is still valid.
** Nonzero is returned if it is no longer valid and has become
** a zombie.
*/

int
dgai_mbsmemb_syncZombie (_Dga_window dgawin)
{
    WXINFO *infop;

    infop = (WXINFO *) dgawin->w_info;

    if (infop->w_obsolete) {
	dgawin->changeMask |= DGA_CHANGE_ZOMBIE;
	return (1);
    } else {
	return (0);
    }
}

/*
** The way we deal with any composition change is to destroy the old
** multibuffer set and establish a new one.
*/

void
dgai_mbsmemb_syncMbufset (_Dga_window dgawin)
{

    DgaMbufSetPtr	pMbs;
    WXINFO 		*infop;

    /* check to see if this is an actual composition change or simply
       a display change */
    if (dgawin->c_mbcomposseq == *dgawin->s_mbcomposseq_p) {
	/* no change -- must be only a display change */
	return;
    }

    /* this is a real composition change.  Destroy the old mbufset (if any)
       and create a new one */

    infop = (WXINFO *) dgawin->w_info;
    pMbs = dgawin->pMbs;

    /* remember whether window was previously multibuffered.  This is 
       used later in the update phase to determine the reason for the
       mbufset change */
    dgawin->prevWasMbuffered = (pMbs != NULL);

    /* destroy the old one */
    if (pMbs) {
	dgai_mbufset_decref(pMbs);
	dgawin->pMbs = NULL;
    }

    dgawin->c_mbcomposseq = *dgawin->s_mbcomposseq_p;

    if (!infop->w_mbsInfo.enabled) {
	return;
    }
    
    /* create a new one */
    pMbs = dgai_mbufset_create(dgawin);
    
    if (!pMbs) {
	/* TODO: really the only way we have of responding to this is treat 
	   it as a zombie.  It's not ideal, but what else can we do? */
	dgawin->changeMask |= DGA_CHANGE_ZOMBIE;
    }

    dgawin->pMbs = pMbs;
}


/*
** If a render buffer notification function has been registered
** and the current effective lock subject differs from the current
** write buffer, call the notification function to change the render 
** buffer state.
*/

void
dgai_mbsmemb_syncRendBuf (_Dga_window dgawin)
{
    WXINFO	*infop;
    short	*pRendBuf;
	
    infop = (WXINFO *) dgawin->w_info;

    /* has client registered the notification function? */
    if (!dgawin->rendBufNotifyFunc) {
	return;
    }

    /* we only need to notify in single-address access mode */
    if (infop->w_mbsInfo.accessMode != DGA_MBACCESS_SINGLEADDR) {
	return;
    }

    /* 
     * Only notify if rend buf is different from what we want it to be 
     * Note: we treat the write buffer index as the render buffer and ignore
     * the read buffer index.
     */
    pRendBuf = &infop->wx_dbuf.write_buffer;
    if (*pRendBuf != dgawin->eLockSubj) {
	(*dgawin->rendBufNotifyFunc)((Dga_drawable)dgawin, dgawin->eLockSubj,
				    dgawin->rendBufNotifyClientData);

	/* update the shared info so both the server and other clients can
	   see and react to the change */
	*pRendBuf = dgawin->eLockSubj;
    }
}

/*
** A derivative change is one which is dependent on changes discovered 
** earlier in the update phase (i.e. the basic changes).  We determine here which ones need
** to be reported.  Derivative changes may be reported along with 
** the basic changes.  The derivative changes in common for mbufset
** members are: site change.
*/

void
dgai_mbsmemb_figureDerivChgs (_Dga_window dgawin)
{
    /* safety */
    dgawin->siteChgReason = DGA_SITECHG_UNKNOWN;

    /* check for zombie */
    if (dgawin->changeMask & DGA_CHANGE_ZOMBIE) {
	/* report both a site change and a clip for zombies.  This is simply
	   more insurance that the client will sync up with the null clip. */
	dgawin->changeMask |= (DGA_CHANGE_SITE | DGA_CHANGE_CLIP);
	dgawin->siteChgReason = DGA_SITECHG_ZOMBIE;
	return;
    }

    /* check for first time */
    if ((dgawin->eLockSubj == -1) && !dgawin->prevLocked) {
	dgawin->changeMask |= DGA_CHANGE_SITE;
	dgawin->siteChgReason = DGA_SITECHG_INITIAL;
	dgawin->prevLocked = 1;
	return;
    } else if ((dgawin->eLockSubj >= 0) &&
               !dgawin->pMbs->prevLocked[(int)dgawin->eLockSubj]) {
	dgawin->changeMask |= DGA_CHANGE_SITE;
	dgawin->siteChgReason = DGA_SITECHG_INITIAL;
	dgawin->pMbs->prevLocked[dgawin->eLockSubj] = 1;
	return;
    }

    /* check for cache change */
    if (dgawin->changeMask & DGA_CHANGE_CACHE) {
	dgawin->changeMask |= DGA_CHANGE_SITE;
	dgawin->siteChgReason = DGA_SITECHG_CACHE;
	return;
    }

    /* check for alias change */
    if (dgawin->changeMask & DGA_CHANGE_ALIAS) {
	dgawin->changeMask |= DGA_CHANGE_SITE;
	dgawin->siteChgReason = DGA_SITECHG_ALIAS;
	return;
    }

    /* check for mbufset composition change */
    if (dgawin->changeMask & DGA_CHANGE_MBUFSET) {
	dgawin->changeMask |= DGA_CHANGE_SITE;
	dgawin->siteChgReason = DGA_SITECHG_MB;
	return;
    }
}


/*
** If we can report any changes through notification, do so now.
*/

void
dgai_mbsmemb_notify (_Dga_window dgawin)
{
    /* report any mbufset change */
    if (dgawin->changeMask & DGA_CHANGE_MBUFSET) {
	dgai_mbsmemb_notifyMbChg(dgawin);
    }

    if (dgawin->changeMask & DGA_CHANGE_SITE) {
	 dgai_mbsmemb_notifySiteChg(dgawin);
    }

    if (dgawin->changeMask & DGA_CHANGE_OVLSTATE) {
	dgai_mbsmemb_notifyOvlState(dgawin);
    }

    /* there are no notify functions for the following:
       clip, cursor, bstore, cache */
}

void
dgai_mbsmemb_devinfo_update(_Dga_window dgawin)
{
    if (!DGA_LOCKSUBJ_VALID(dgawin, dgawin->eLockSubj) || 
	dgawin->changeMask & DGA_CHANGE_ZOMBIE) {
	return;
    }

    if        (DGA_LOCKSUBJ_WINDOW(dgawin, dgawin->eLockSubj)) {
	/* check for window devinfo change */
	if (dgawin->c_devinfoseq != *dgawin->s_devinfoseq_p) {
	    dgawin->changeMask |= DGA_CHANGE_DEVINFO;
	    dgawin->c_devinfoseq = *dgawin->s_devinfoseq_p;
	}
    } else if (!DGA_LOCKSUBJ_VIEWABLE(dgawin, dgawin->eLockSubj)) {
	/* check for nonviewable mbuf devinfo change */
	dgai_nmbuf_devinfo_update(dgawin);
    }

    /* Note: viewable mbufs don't have dev info */
}

static void
dgai_mbsmemb_notifySiteChg (_Dga_window dgawin)
{
    if (dgawin->siteNotifyFunc) {
	(*dgawin->siteNotifyFunc)((Dga_drawable)dgawin, dgawin->eLockSubj,
				  dgawin->siteNotifyClientData,
				  dgawin->siteChgReason);
	dgawin->changeMask &= ~DGA_CHANGE_SITE;
	dgawin->siteChgReason = DGA_SITECHG_UNKNOWN;
    } else {
	/* client must find out through dga_draw_sitechg */
    }
}


static void
dgai_mbsmemb_notifyMbChg (_Dga_window dgawin)
{
    /* figure out reason for change */
    if        (!dgawin->prevWasMbuffered && dgawin->pMbs) {
	dgawin->mbChgReason = DGA_MBCHG_ACTIVATION;
    } else if (dgawin->prevWasMbuffered && !dgawin->pMbs) {
	dgawin->mbChgReason = DGA_MBCHG_DEACTIVATION;
    } else if (dgawin->prevWasMbuffered && dgawin->pMbs) {
	dgawin->mbChgReason = DGA_MBCHG_REPLACEMENT;
    } else {
	/* this might happen if the mbufset was activated and then, in
	   the same update phase, deactivated.  In this case, allow it,
	   but just don't report any changes */
	dgawin->changeMask &= ~DGA_CHANGE_MBUFSET;
	dgawin->mbChgReason = DGA_MBCHG_UNKNOWN;
	return;
    }
    
    if (dgawin->mbNotifyFunc) {
	(*dgawin->mbNotifyFunc)((Dga_drawable)dgawin, 
				dgawin->mbNotifyClientData,
				dgawin->mbChgReason); 
	dgawin->changeMask &= ~DGA_CHANGE_MBUFSET;
	dgawin->mbChgReason = DGA_MBCHG_UNKNOWN;
    } else {
	/* client must find out through dga_draw_mbchg */
    }
}


static void
dgai_mbsmemb_notifyOvlState (_Dga_window dgawin)
{
    if (dgawin->ovlStateNotifyFunc) {
	(*dgawin->ovlStateNotifyFunc)((Dga_drawable)dgawin,
				      dgawin->ovlStateNotifyClientData,
				      dgawin->c_ovlstate);
	dgawin->changeMask &= ~DGA_CHANGE_OVLSTATE;
    } else {
	/* client must find out through dga_draw_sitechg */
    }
}

