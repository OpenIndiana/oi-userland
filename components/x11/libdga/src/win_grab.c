/* Copyright (c) 1993, 2015, Oracle and/or its affiliates. All rights reserved.
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
 * win_grab.c - the client side code for DGA window grabber
 */

/****
 *
 *
 *	Shared window synchronization routines - client side
 *
 *
 *
 * Functions:
 *
 *    Dga_window
 *    dga_win_grab(devfd, token)
 *		int		devfd ;
 *		Dga_token	token ;
 *
 *	Grab a window.  'token' is the window-info handle returned by
 *	XDgaGrabWindow.  'devfd' is the file descriptor of the frame buffer
 *	if known, -1 otherwise.  If you specify -1, dga_win_grab will open the
 *	frame buffer.  The frame buffer fd may be inquired from the returned
 *	Dga_window structure via the dga_win_devfd() routine.
 *
 *	Returns a pointer to the a struct dga_window on success, NULL on
 *	failure.
 *
 *
 *
 *    dga_win_ungrab(infop, cflag)
 *		Dga_window	infop ;
 *		int		cflag ;
 *
 *	Ungrab a window.  All resources allocated by dga_win_grab are freed.
 *	If 'cflag' is nonzero, the framebuffer fd described for the device
 *	is also closed.
 *
 *	The application should call XDgaUnGrabWindow(dpy,win) after
 *	calling dga_win_ungrab() so that the server may free the window-info
 *	page at the other end.
 *
 *
 *
 *	short *
 *	dga_win_clipinfo(win)
 *		Dga_window	win ;
 *
 *	Returns pointer to cliplist.  Replaces old wx_sh_clipinfo_c() macro.
 *
 *
 *
 *	char *
 *	dga_win_fbname(win)
 *		Dga_window	win ;
 *
 *	Returns name of fb.  Replaces old wx_devname_c() macro.
 *
 *
 *
 *	int
 *	dga_win_clipchg(win)
 *		Dga_window	win ;
 *
 *	Returns 1 if cliplist changed since last call.  Replaces old
 *	wx_modif_c() and wx_seen_c() macros.
 *
 *
 *
 *	int
 *	dga_win_curschg(win)
 *		Dga_window	win ;
 *
 *	Returns 1 if cursor changed since last call.
 *
 *
 *
 *	int
 *	dga_win_rtnchg(win)
 *		Dga_window	win ;
 *
 *	Returns 1 if retained info changed since last call.
 *
 *
 *
 *	int
 *	dga_win_devfd(win)
 *		Dga_window	win ;
 *
 *	Returns framebuffer fd.
 *
 *
 *
 *	dga_win_bbox(win, xp, yp, widthp, heightp)
 *		Dga_window win;
 *		int *xp, *yp, *widthp, *heightp;
 *
 *	Returns window bounding box
 *
 *
 *
 *	int
 *	dga_win_singlerect(win)
 *		Dga_window win;
 *
 *	Returns nonzero if the window is a single rectangle.
 *
 *
 *
 *	int
 *	dga_win_empty(win)
 *		Dga_window win;
 *
 *	Returns nonzero if the window is empty.
 *
 *
 *
 *	int
 *	dga_win_obscured(win)
 *		Dga_window win;
 *
 *	Returns nonzero if the window is obscured.
 *
 *
 *
 *	int
 *	dga_win_cursactive(win)
 *		Dga_window win;
 *
 *	Returns nonzero if the cursor grabber is active.
 *
 *
 *
 *	void
 *	dga_win_cursupdate(win, func, data)
 *		Dga_window	win;
 *		void		(*func)();
 *		void*		data;
 *
 *	Decide if the cursor needs to be taken down, and if so, call
 *		(*func)(data, win, x, y, mem)
 *			void*		data ;
 *			Dga_window	win ;
 *			int		x,y ;
 *			Dga_curs_mpr	*mem ;
 *
 *
 *
 *	Dga_dbinfo *
 *	dga_win_dbinfop(win)
 *		Dga_window win;
 *
 *	Return dbinfo pointer.
 *
 *
 *
 *	Dga_widinfo *
 *	dga_win_widinfop(win)
 *		Dga_window win;
 *
 *	Return window id info pointer.
 *
 *      dga_win_depth(win)
 *              Dga_window win;
 *
 *      Return windows depth .
 *
 *
 *      dga_win_borderwidth(win) 
 *              Dga_window win; 
 * 
 *      Return windows borderwidth .   
 *
 * 	void 
 * 	dga_win_set_client_infop(win, client_info_ptr)
 *		Dga_window win;
 *		void* client_info_ptr;
 *	Sets a client specific pointer in Dga_window
 *
 *
 *      dga_win_get_client_infop(win) 
 *              Dga_window win;
 * 	Returns the client specific pointer
 *
 ****/
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#ifdef SERVER_DGA
#include <X11/X.h>
#include <X11/Xmd.h>
#include "windowstr.h"
#include "dga_externaldefs.h"
#include "dga/dgawinstr.h"
#else
#include <sys/file.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <errno.h>
#include <X11/Xlib.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#ifdef SVR4
#include <sys/fbio.h>
#include <sys/fcntl.h>
#else
#include <sun/fbio.h>
#include <fcntl.h>
#endif
#endif /* SERVER_DGA */

#include "dga_incls.h"
#include "rtn_grab.h"
 
#define	GRABFILE	"/tmp/wg"
#define	CURGFILE	"/tmp/curg"
#define	NDIGITS		8

#define	MINSHMEMSIZE	(8*1024)
#define	MAXSHMEMSIZE	(0x00040000)
#define WX_PAGESZ       (8*1024)

#if 0
#ifdef DEBUG
extern	int	sys_nerr;
extern	char	*sys_errlist[] ;
#endif
#endif

extern int _dga_winlockat(u_long cookie, int **lockp, int **unlockp);
extern int _dga_winlockdt(int *lockp, int *unlockp);

/* Some structure definition for internal bookkeeping */
typedef struct dga_winlist {
    Dga_token		w_token;	 /* Token associated with win */
    struct dga_window	*dga_clientplist;/*List of client ptrs in win */
    struct dga_window	*dga_clientplist_draw; /* List of client ptrs in win
						* using drawable i/f. */
    struct dga_winlist	*next_winlist;  /* Next link in the dga list */
#ifdef MT
    mutex_t		mutex;
#endif
	
} *Dga_winlist;

static struct dga_winlist *dga_wlist = NULL;

static int 	dga_win_update(Dga_drawable dgawin);
static int	dgai_win_initMbufset (_Dga_window dgawin);
static void	release_lockpages(int devfd, _Dga_window clientp);
static _Dga_window check_other_curg_windows(WXINFO *);
void     dgai_win_ungrab_common(_Dga_window dgawin, int cflag,int drawableGrabber);
int 	dgai_win_check_multiple_grab(_Dga_window dgawin, int drawableGrabber);
void safe_free_clientp(_Dga_window clientp);

/*bug fix for 4248958: use safe_free_client() to replace free() */
void
safe_free_clientp(clientp)
    _Dga_window  clientp;
{
     
    if(clientp){
        if(clientp->back) free(clientp->back);
        if(clientp->depth) free(clientp->depth);
        if(clientp->stencil) free(clientp->stencil);
        if(clientp->accum) free(clientp->accum);
        if(clientp->alpha) free(clientp->alpha);
        free(clientp);
    }
}

/******************************************
 *
 * dgai_win_grab_common:
 *
 *	create shared memory file for window information
 *	map to lock page
 *
 *	arguments:
 *
 *	int	devfd;	INPUT
 *		file descriptor of graphics device
 *
 *	Dga_token	token;	INPUT
 *		magic cookie supplied by the server
 *
 *	returns a user virtual address for a dga_window structure.
 *	returns NULL if anything goes awry.
 *
 *	'devfd' is the file descriptor of the frame buffer, if known,
 *	-1 otherwise.  If you specify -1, wx_grab will open the
 *	frame buffer.  The frame buffer fd may be inquired from the returned
 *	Dga_window ptr to the struct dga_window via the dga_win_devfd() routine.
 *
 *****************************************/


/*
** Shared between both drawable grabber and window compatibility interface.
*/

Dga_window
dgai_win_grab_common (Display *dpy, int devfd, Dga_token token, int drawableGrabber)
{
	WXINFO	*infop;
	_Dga_window clientp = NULL;
	Dga_winlist wlist;
	int	lockfd ;
	Dga_lockp	lockp, unlockp ;
	char	filename[sizeof(GRABFILE)+NDIGITS+1];
	int	filefd;
	int	locktype ;
	int	i;
#ifdef SERVER_DGA
	WindowPtr	pWin;
	Window		win;

	if (!_dga_is_X_window(token, &dpy, &win)) {
	    return  NULL;
        }
	pWin = (WindowPtr)LookupIDByType(win, RT_WINDOW);
#endif /* SERVER_DGA */

	/* First, check if already grabbed by this client. Note that we
	   always treat the new drawable and old window grabbers separately */
	for(wlist = dga_wlist;wlist != NULL;wlist = wlist->next_winlist) {
	    if (wlist->w_token == token) {
		_Dga_window orig_clientp,new_clientp;

		/* If multiple clients are grabbing the same
		 * window, then we duplicate the per client info
		 * structure and return that instead of the original
		 * allocated clientp structure. Also remember to add
		 * this new info structure to the linked list. This 
		 * change obsoletes the w_grab_count field which
		 * will always be equal to 1
		 */

		if ((new_clientp =  
		  (_Dga_window) malloc(sizeof(struct dga_window))) == NULL)
		    return NULL ;

		if (drawableGrabber) {
		    if (wlist->dga_clientplist_draw)
		        orig_clientp = wlist->dga_clientplist_draw;
                    else
			orig_clientp = wlist->dga_clientplist;
		    *new_clientp = *orig_clientp;
		    new_clientp->w_lockcnt =0;
		    new_clientp->w_grab_count =1;
    
		    if (wlist->dga_clientplist_draw) {
		        /* Add it to the list of clientp structure associated
		         * with this window */

		        new_clientp->w_next = orig_clientp;
		    } else {
			
			/* Need to initialize all drawableGrabber
			 * specific data. */

			infop = (WXINFO *)new_clientp->w_info;
			if (infop->info_sz != sizeof(WXINFO)) {
				/* mismatch on 64 bit port or other trouble */
	    		fprintf(stderr, 
"wx_grab: mismatch on shared WXINFO size info page is %d sizeof is %d \n",
				infop->info_sz, sizeof(WXINFO));
				free(new_clientp);
				return(NULL);
			}
			new_clientp->drawable_type = DGA_DRAW_WINDOW;
			new_clientp->w_update_func = 
				      (int(*)())dgai_mbsmemb_update;
                        new_clientp->c_mbufseq = 0;
                        new_clientp->s_mbufseq_p = &infop->w_mbsInfo.mbufseq;
                        new_clientp->c_mbcomposseq = 0;
                        new_clientp->s_mbcomposseq_p = 
                                          &infop->w_mbsInfo.compositionseq;
                        new_clientp->s_devinfoseq_p = &infop->w_devinfoseq;
                        new_clientp->c_devinfoseq = 0;
                        new_clientp->siteNotifyFunc = NULL;
                        new_clientp->siteNotifyClientData = NULL;
                        new_clientp->mbNotifyFunc = NULL;
                        new_clientp->mbNotifyClientData = NULL;
                        new_clientp->rendBufNotifyFunc = NULL;
                        new_clientp->rendBufNotifyClientData = NULL;
                        new_clientp->rLockSubj = DGA_LOCKSUBJ_INVALID;
                        new_clientp->eLockSubj = DGA_LOCKSUBJ_INVALID;
                        new_clientp->eLockSubjPrev = DGA_LOCKSUBJ_INVALID;
                        new_clientp->changeMask = 0;
                        new_clientp->prevWasMbuffered = 0;
                        new_clientp->mbChgReason = DGA_MBCHG_UNKNOWN;
                        new_clientp->siteChgReason = DGA_SITECHG_UNKNOWN;
                        new_clientp->prevLocked = 0;
			if ((dpy != NULL) && drawableGrabber) {
			    if (!dgai_win_initMbufset(new_clientp)) {
				dga_win_ungrab(new_clientp, 0);
			    }
                        }
			new_clientp->w_next = NULL;
		    }
		    wlist->dga_clientplist_draw = new_clientp;

		    /* the same mbufset is shared between all client 
		     * structures for this window */

		    if (orig_clientp->pMbs) {
		        dgai_mbufset_incref(orig_clientp->pMbs);
		    }
#ifdef MT
		    new_clientp->mutexp = &wlist->mutex;
			/* Same window was grabbed 2 or more times via the
             * drawable interface so turn per-drawable MT
             * locking on if we are linked with -lthread also.
             */
            if (dgaThreaded) {
            /* Currently, this variable gets set to 1 and
             * never gets turned off.  This could be optimized
             * if needed.
             */
            dgaMTOn = 1;
            }
#endif
		    return new_clientp;

		} else {
		    if (wlist->dga_clientplist)
		        orig_clientp = wlist->dga_clientplist;
		    else
			orig_clientp = wlist->dga_clientplist_draw;
		    *new_clientp = *orig_clientp;
	            new_clientp->w_update_func = dga_win_update;
		    new_clientp->w_lockcnt =0;
		    new_clientp->w_grab_count =1;

		    if (wlist->dga_clientplist) {
			/* Add it to the list of clientp structure associated
		         * with this window */
		        new_clientp->w_next = orig_clientp;
                    } else {
			new_clientp->w_next = NULL;
		    }
		    wlist->dga_clientplist = new_clientp;
#ifdef MT
		    new_clientp->mutexp = &wlist->mutex;
#endif
		    return new_clientp;

		}
	    }
	}

	if( (clientp = 
	    (_Dga_window) malloc(sizeof(struct dga_window))) == NULL )
	    return NULL ;
	memset(clientp, 0, sizeof(struct dga_window));
	
#ifdef SERVER_DGA
        {                  
            /* Now get a pointer to the shared info page from
             * pWin's private data */
     
            DgaSetupWindow(pWin);
            WDEV    *wdev;
     
            wdev = pDgaWindow->pDgaWdev;
            infop = (WXINFO *)wdev->infop;
            if (infop == NULL) return NULL;
         }
#else
	sprintf(filename, "%s%08x", GRABFILE, token);

        if ((filefd = open(filename,O_RDWR,0666))<0) {
	    safe_free_clientp(clientp) ;
	    return((Dga_window)NULL);
	}

	/* map the wx_winfo area */
        infop = (WXINFO *)mmap(0,
		    MAXSHMEMSIZE,
		    PROT_READ|PROT_WRITE,
		    MAP_SHARED,
		    filefd,
		    (off_t)0);

	if (infop == (WXINFO *)-1) {
	    close(filefd);
	    safe_free_clientp(clientp) ;
	    return((Dga_window)NULL);
	}
	if (infop->info_sz != sizeof(WXINFO)) {
		/* mismatch on 64 bit port or other trouble */
#ifdef DEBUG
   		fprintf(stderr, 
	"wx_grab: mismatch on WXINFO size info page is %d sizeof is %d \n",
			infop->info_sz, sizeof(WXINFO));
#endif
	    munmap((caddr_t)infop, MAXSHMEMSIZE) ;
	    close(filefd) ;
	    safe_free_clientp(clientp) ;
	    return(NULL);
	}

	/* open the frame buffer if not already opened by client */
	if( devfd >= 0 )
	  lockfd = devfd ;
	else {
	  lockfd = open(infop->w_devname, O_RDWR,0666) ;
	  if( lockfd < 0 )  {
#ifdef DEBUG
	    fprintf(stderr, "wx_grab: cannot open %s, %s\n",
		infop->w_devname, strerror(errno)) ;
#endif
	    munmap((caddr_t)infop, MAXSHMEMSIZE) ;
	    close(filefd) ;
	    safe_free_clientp(clientp) ;
	    return NULL ;
	  }
	}
#endif /* SERVER_DGA */

	if (drawableGrabber) {
	    clientp->drawable_type = DGA_DRAW_WINDOW;
	}
	clientp->w_dpy = dpy;
	clientp->w_info = (void*)infop ;
	clientp->w_infofd = 0; /* no longer needed */
	clientp->w_next = NULL;

	clientp->curs_info = NULL; /* must set up here, may be changed below */
	clientp->curs_fd = -1;

#ifdef SERVER_DGA
	clientp->w_devfd = infop->w_sdevfd; ;
        clientp->w_lockp = (Dga_lockp)infop->w_slockp;
        clientp->w_unlockp = (Dga_lockp)infop->w_slockp;
    
        clientp->w_lib_private = (void *) infop; /* PRIVATE DATA  */
#else
	clientp->w_devfd = lockfd ;
	lockp = NULL; /* init to NULL for check below */
	unlockp = NULL;

	/* On cursor-grabbed devices, find out if we already have a
	 * lockp, unlockp, and cursor page mapping for this device.
	 * We don't want to grab the same lockpage, etc. twice.
	 */
	if (infop->w_version >= 2  &&  infop->c_sinfo) {
	    _Dga_window winp;

	    winp = check_other_curg_windows(infop);
	    if (winp) {
		clientp->curs_fd = winp->curs_fd;
		clientp->curs_info = winp->curs_info;
		lockp = winp->w_lockp;
		unlockp = winp->w_unlockp;
	    }
	}

	if (lockp == NULL) { 
	    /* only get new lock pages if necessary */
	    locktype = infop->w_version >= 2 ? infop->w_locktype : WG_LOCKDEV ;
	    switch( locktype ) {
		case WG_LOCKDEV:
		    /* map the lock page */
		    lockp = (Dga_lockp)mmap(0,
			WX_PAGESZ,
			PROT_READ|PROT_WRITE,
			MAP_SHARED,
			lockfd,(off_t)infop->w_cookie);

		    if (lockp == (Dga_lockp)-1) {
#ifdef DEBUG
		    fprintf(stderr, "wx_grab: cannot map lock page, %s\n",
			strerror(errno)) ;
#endif
		    munmap((caddr_t)infop, MAXSHMEMSIZE) ;
		    close(filefd);
		    if( devfd < 0 )
		    close(lockfd) ;
		    safe_free_clientp(clientp) ;
		    return(NULL);
		}

		/* map the unlock page */
		unlockp = (Dga_lockp)mmap(0,
			WX_PAGESZ,
			PROT_READ|PROT_WRITE,
			MAP_SHARED,
			lockfd,(off_t)infop->w_cookie) ;

		if(unlockp == (Dga_lockp)-1) {
#ifdef DEBUG
		fprintf(stderr, "wx_grab: cannot map unlock page\n") ;
#endif
		munmap((caddr_t)lockp, WX_PAGESZ) ;
		munmap((caddr_t)infop, MAXSHMEMSIZE) ;
		close(filefd);
		if( devfd < 0 )
		  close(lockfd) ;
		safe_free_clientp(clientp) ;
		return(NULL);
	    }
	    break ;

	    case WG_WINLOCK:
		if( _dga_winlockat(infop->w_cookie, &lockp, &unlockp) != 0 ) {
		    munmap((caddr_t)infop, MAXSHMEMSIZE);
		    close(filefd);
		    if( devfd < 0 )
			close(lockfd) ;
		    safe_free_clientp(clientp) ;
		    return(NULL);
		}
	    break ;
	  }
	}

	clientp->w_lockp = lockp ;
	clientp->w_unlockp = unlockp ;

	/* cursor grabber stuff */
	if ((infop->w_version >= 2)  &&  (infop->c_sinfo) &&
	  ((clientp->curs_fd == -1) || (clientp->curs_info == NULL))) {
	    char    cfn[sizeof(CURGFILE)+NDIGITS+1];
	    int	    curs_fd;
	    
	    strcpy(cfn,CURGFILE);
	    sprintf(cfn+sizeof(CURGFILE)-1,"%08x", infop->c_filesuffix);
	    
	    /* open the shared cursor page */
	    if ((curs_fd = open(cfn, O_RDWR,0666))<0) {
#ifdef DEBUG
		fprintf(stderr, "wx_grab: cannot open cursor grabber page\n") ;
#endif		
		release_lockpages(devfd, clientp);
		return((Dga_window)NULL);
	    }
	    clientp->curs_fd = curs_fd;

	    /* Map it */
	    clientp->curs_info = (caddr_t) mmap(0,
			MINSHMEMSIZE,	
			PROT_READ|PROT_WRITE,
			MAP_SHARED,
			curs_fd,
			(off_t)0);
			
	    if (clientp->curs_info == (caddr_t) -1) {
#ifdef DEBUG
		fprintf(stderr, "wx_grab: cannot map cursor page, %s\n",
		    strerror(errno)) ;
#endif
		close(curs_fd);
		release_lockpages(devfd, clientp);
		return(NULL);
	    }
	    /* check to see if you have a good magic number */
	    if (((Dga_cursinfo *) (clientp->curs_info))->c_magic !=
		DGA_CURG_MAGIC) {
#ifdef DEBUG
		fprintf(stderr, "wx_grab: wrong cursor page mapped, %s\n",
		    strerror(errno)) ;
#endif		
		munmap(clientp->curs_info, MINSHMEMSIZE) ;
		close(curs_fd);
		release_lockpages(devfd, clientp);
		return(NULL);
	    }
	}
#endif /* SERVER_DGA */

	/* success, fill out rest of structure */
	clientp->w_token = token;
	clientp->w_client = 0 ;
	clientp->c_clipseq = 0 ;
	clientp->s_clipseq_p = &(infop->u.vn.w_clipseq) ;
	if (drawableGrabber) {
	    clientp->w_update_func = (int(*)())dgai_mbsmemb_update;
	} else {
	    /* compatibility */
	    clientp->w_update_func = dga_win_update;
	}
#ifdef MT
	if (dgaThreaded) {
	    clientp->w_unlock_func = dgai_unlock;
	} else {
	    clientp->w_unlock_func = NULL;
	}
#else
	clientp->w_lock_func = NULL;
	clientp->w_unlock_func = NULL;
#endif
	clientp->w_lockcnt = 0;
	if (infop->w_version != 0) {
	  clientp->w_clipptr = (short *)((char *)infop+infop->u.vn.w_clipoff);
          clientp->w_cliplen = 0;
        }
	if (infop->w_version < 2) {
	    clientp->c_chngcnt = 0;
	    clientp->s_chngcnt_p = clientp->s_clipseq_p;
	} else {
	    clientp->c_chngcnt = 0;
	    clientp->s_chngcnt_p = &(infop->w_chng_cnt);
	    for (i = 0; i < DGA_MAX_GRABBABLE_BUFS + 1; i ++) {
	        clientp->c_wm_chngcnt[i] = 0;
#ifdef MT
	        clientp->shadow_chngcnt[i] = 0;
#endif
	    }
	}
        /* Now initialize the next field to pt to the second member of
         * c_wm_chngcnt array - this is specifically for performance
         * tuning of the lock macro
        */
        clientp->w_wm_2nd = clientp->c_wm_chngcnt + 1;

	if ((infop->w_version < 2) || (clientp->curs_info == NULL)) {
	    clientp->s_curseq_p = &clientp->c_curseq;
	    clientp->c_curseq = 0;
	} else {
	    clientp->s_curseq_p =
	        &(((Dga_cursinfo *) (clientp->curs_info))->c_chng_cnt);
	    clientp->c_curseq =
		((Dga_cursinfo *) (clientp->curs_info))->c_chng_cnt - 1;
	    /* so first test of dga_win_curschg will see a change */
	}

        clientp->back = (void *)malloc(sizeof(dga_internal_buffer_rec));
        if ( !clientp->back )
            return NULL;

        clientp->depth = (void *)malloc(sizeof(dga_internal_buffer_rec));
        if ( !clientp->depth )
            return NULL;

        clientp->stencil = (void *)malloc(sizeof(dga_internal_buffer_rec));
        if ( !clientp->stencil )
            return NULL;

        clientp->accum = (void *)malloc(sizeof(dga_internal_buffer_rec));
        if ( !clientp->accum )
            return NULL;

        clientp->alpha = (void *)malloc(sizeof(dga_internal_buffer_rec));
        if ( !clientp->alpha )
            return NULL;

        ((dga_internal_buffer)clientp->back)->bufferp = NULL;
        ((dga_internal_buffer)clientp->depth)->bufferp = NULL;
        ((dga_internal_buffer)clientp->stencil)->bufferp = NULL;
        ((dga_internal_buffer)clientp->accum)->bufferp = NULL;
        ((dga_internal_buffer)clientp->alpha)->bufferp = NULL;

        ((dga_internal_buffer)clientp->back)->pDraw = (Dga_drawable)clientp;
        ((dga_internal_buffer)clientp->depth)->pDraw = (Dga_drawable)clientp;
        ((dga_internal_buffer)clientp->stencil)->pDraw = (Dga_drawable)clientp;
        ((dga_internal_buffer)clientp->accum)->pDraw = (Dga_drawable)clientp;
        ((dga_internal_buffer)clientp->alpha)->pDraw = (Dga_drawable)clientp;

        ((dga_internal_buffer)clientp->back)->buf_size = 0;
        ((dga_internal_buffer)clientp->depth)->buf_size = 0;
        ((dga_internal_buffer)clientp->stencil)->buf_size = 0;
        ((dga_internal_buffer)clientp->accum)->buf_size = 0;
        ((dga_internal_buffer)clientp->alpha)->buf_size =  0;

        clientp->buf_resize_flag = 0;
        clientp->c_buffer_swap = 0;

	clientp->db_enabled = 0;
	clientp->c_rtnseq = 0;
	clientp->s_rtnseq_p = &clientp->c_rtnseq;
	clientp->rtn_info = NULL;
	clientp->rtn_flags = 0;

        /* initialization for drawable grabber code */
	clientp->pMbs = NULL;
	if (drawableGrabber) {
	    clientp->c_mbufseq = 0;
	    clientp->s_mbufseq_p = &infop->w_mbsInfo.mbufseq;
	    clientp->c_mbcomposseq = 0;
	    clientp->s_mbcomposseq_p = &infop->w_mbsInfo.compositionseq;
	    clientp->s_devinfoseq_p = &infop->w_devinfoseq;
	    clientp->c_devinfoseq = 0;
	    clientp->siteNotifyFunc = NULL;
	    clientp->siteNotifyClientData = NULL;
	    clientp->mbNotifyFunc = NULL;
	    clientp->mbNotifyClientData = NULL;
	    clientp->rendBufNotifyFunc = NULL;
	    clientp->rendBufNotifyClientData = NULL;
	    clientp->rLockSubj = DGA_LOCKSUBJ_INVALID;
	    clientp->eLockSubj = DGA_LOCKSUBJ_INVALID;
	    clientp->eLockSubjPrev = DGA_LOCKSUBJ_INVALID;
	    clientp->changeMask = 0;
	    clientp->prevWasMbuffered = 0;
	    clientp->mbChgReason = DGA_MBCHG_UNKNOWN;
	    clientp->siteChgReason = DGA_SITECHG_UNKNOWN;
	    clientp->prevLocked = 0;
	}

	/* add to linked list of grabbed windows - for internal bookkeeping
	 * Note: this should be done last in order for other code, e.g.
	 * check_other_curg_windows() to work correctly
	 */
	if (!dga_wlist) {

	   if ((dga_wlist = 
	    (Dga_winlist) malloc(sizeof(struct dga_winlist))) == NULL )
	    return NULL ;
	   dga_wlist->w_token = token;
	   if (drawableGrabber) {
	       dga_wlist->dga_clientplist_draw = clientp;
	       dga_wlist->dga_clientplist = NULL;
	   } else {
	       dga_wlist->dga_clientplist_draw = NULL;
	       dga_wlist->dga_clientplist = clientp;
	   }
	   dga_wlist->next_winlist = NULL;
	} else {
	   struct dga_winlist *new_wlist;
		
	   if ((new_wlist =
                   (Dga_winlist) malloc(sizeof(struct dga_winlist))) == NULL )
		return NULL;
	   new_wlist->w_token = token;
	   if (drawableGrabber) {
	       new_wlist->dga_clientplist_draw = clientp;
	       new_wlist->dga_clientplist = NULL;
	   } else {
	       new_wlist->dga_clientplist_draw = NULL;
	       new_wlist->dga_clientplist = clientp;
	   }
	   new_wlist->next_winlist = dga_wlist;
	   dga_wlist = new_wlist;
	}
#ifndef SERVER_DGA
	close(filefd) ;
#endif /* SERVER_DGA */

#ifdef MT
	mutex_init(&dga_wlist->mutex, USYNC_THREAD, NULL);
	clientp->mutexp = &dga_wlist->mutex;
#endif

	/* If window is multibuffered, initialize multibuffer set */
	/* If window is being grabbed through the old interface don't
	 * init the mbufset since mbuffers where not supported int
	 * older versions of DGA */
	if ((dpy != NULL) && drawableGrabber) {
	    if (!dgai_win_initMbufset(clientp)) {
		dga_win_ungrab(clientp, 0);
	    }
	}

	return((Dga_window)clientp);
}


Dga_window
dga_win_grab(devfd, token)
	int		devfd;
	Dga_token	token;
{
    /* Call the common grab routine with dpy == NULL to signify that
     * mbuffers are not to be initialized. */

    return (dgai_win_grab_common(NULL, devfd, token, 0));
}


#ifndef SERVER_DGA
static _Dga_window
check_other_curg_windows(infop)
WXINFO *infop;
{
	Dga_winlist winp;
	_Dga_window clientp;
	WXINFO *linfop;

	for(winp = dga_wlist; winp != NULL; winp = winp->next_winlist) {
	    if (clientp = winp->dga_clientplist_draw) {
		linfop = (WXINFO *) clientp->w_info;
		if (strcmp(linfop->w_devname, infop->w_devname) == 0) {
		    return(clientp);
		}
	    }
	    if (clientp = winp->dga_clientplist) {
		linfop = (WXINFO *) clientp->w_info;
		if (strcmp(linfop->w_devname, infop->w_devname) == 0) {
		    return(clientp);
		}
	    }
	}
	return NULL;
}


static void
release_lockpages(devfd, clientp)
	int		devfd ;
	_Dga_window	clientp;
{
	int		lockfd = clientp->w_devfd ;
	WXINFO		*infop = (WXINFO *) clientp->w_info ;
	Dga_lockp	lockp = clientp->w_lockp ;
	Dga_lockp	unlockp = clientp->w_unlockp ;
	int		locktype ;

	if ((clientp->curs_info ||
	     ((infop->w_version >= 2)  &&  (infop->c_sinfo))) &&
	    ((check_other_curg_windows(infop) != NULL) ||
	     (check_other_curg_windows(infop) == NULL && infop->w_devname[0] == 0))) { 
	    /* don't free lock pages
	     * Note: check both clientp->curs_info and infop->c_sinfo because
	     * this routine is called both at grab and ungrab time.  Client
	     * may not have set curs_info non-zero at grab time.  Server may
	     * set c_sinfo NULL at window destroy time.
	     */
	} else {
	    locktype = infop->w_version >= 2 ? infop->w_locktype : WG_LOCKDEV ;
	    switch(locktype ) {
	      case WG_LOCKDEV:
	        munmap((caddr_t)lockp, WX_PAGESZ) ;
	        munmap((caddr_t)unlockp, WX_PAGESZ) ;
	        break ;
	      case WG_WINLOCK:
	        (void) _dga_winlockdt((int *)lockp, (int *)unlockp) ;
	        break ;
	    }
	}
	if( devfd < 0 )
	     close(lockfd) ;
	munmap((caddr_t)infop, MAXSHMEMSIZE) ;
	safe_free_clientp(clientp) ;
}
#endif /* SERVER_DGA */

void
dga_win_ungrab(clientpi, cflag)
    Dga_window  clientpi;
    int cflag ;
{
    _Dga_window clientp = (struct dga_window *)clientpi;
 
    dgai_win_ungrab_common(clientpi,cflag, 0);
}

void
dgai_win_ungrab_common(clientp, cflag,drawableGrabber)
    _Dga_window	clientp;
    int	cflag ;
    int drawableGrabber;
{

    WXINFO	*infop = (WXINFO *) clientp->w_info ;
    int	infofd, devfd , curs_fd, match;
    struct dga_winlist	*prevwinp, *winp;

    /* remove from linked list of grabbed windows
     * Note: this should be done first in order for other code, e.g.
     * check_other_curg_windows() to work correctly
     */
    match = 0;
    winp = dga_wlist;
    prevwinp = NULL;
    while (winp) {
	if (winp->w_token == clientp->w_token) {
	    struct dga_window *clntp, *prevclntp;
	    if (drawableGrabber)			
	    	clntp = winp->dga_clientplist_draw;
	    else
		clntp = winp->dga_clientplist;

	    prevclntp = NULL;
	    while (clntp) {
		if (clntp == clientp) {
		    match = 1;
		    if( prevclntp )
			prevclntp->w_next = clntp->w_next;
		    else {
			if (drawableGrabber)
			    winp->dga_clientplist_draw = clntp->w_next;
			else
			    winp->dga_clientplist = clntp->w_next;
		    }
		    break;
		}
		prevclntp = clntp;
		clntp = clntp->w_next;
	    }
	    if (!match) {
		/* Check for old style clients */
	        clntp = winp->dga_clientplist;
	        prevclntp = NULL;
	        while (clntp) {
		    if (clntp == clientp) {
		        match = 1;
		        if( prevclntp )
			    prevclntp->w_next = clntp->w_next;
		        else {
			    if (drawableGrabber)
				winp->dga_clientplist_draw = clntp->w_next; 
			    else
			        winp->dga_clientplist = clntp->w_next;
			}
		        break;
		    }
		    prevclntp = clntp;
		    clntp = clntp->w_next;
	        }
	    }
	    break ;
	}
	prevwinp = winp;
	winp = winp->next_winlist;
    }

    if (!match)
	return;	/* error */

    /* TODO: do this for every client, or only once? */
    if ((clientp->rtn_flags & RTN_GRABBED) && (!winp->dga_clientplist))
	dga_rtn_ungrab(clientp);
    if (clientp->db_enabled && (!winp->dga_clientplist))
	dga_db_release(clientp);
    devfd = clientp->w_devfd ;

#ifndef SERVER_DGA
    /* Cursor grabber stuff */
    /* TODO: do this for every client, or only once? */
    if ((clientp->curs_info) && (check_other_curg_windows(infop) == NULL) &&
	(!infop->c_sinfo)) { 
	curs_fd = clientp->curs_fd;
	munmap(clientp->curs_info, MINSHMEMSIZE) ;
	close(curs_fd);
    }
#endif /* SERVER_DGA */

    /* deref any associated multibuffer set */
    if (clientp->pMbs) {
	dgai_mbufset_decref(clientp->pMbs);
	clientp->pMbs = NULL;
    }

    /* TODO: shouldn't we free the clientp??? */
    /* Now check to see  if all that needs to be freed has been freed */
    if ((winp->dga_clientplist_draw == NULL) && 
	(winp->dga_clientplist == NULL)){
#ifndef SERVER_DGA
	release_lockpages( cflag ? -1 : 0, clientp ) ;
#endif /* SERVER_DGA */
	/* Then free this node and unlink it from the list */	
	if( prevwinp != NULL )
	    prevwinp->next_winlist = winp->next_winlist ;
	else
	    dga_wlist = winp->next_winlist ;
#ifdef MT
	mutex_destroy(&winp->mutex);
#endif
	free(winp);
    }
}

int
dgai_win_check_multiple_grab(clientp, drawableGrabber)
_Dga_window clientp;
{

    struct dga_winlist *winp;
    int match;

    /* Checking to see if this client is grabbing a multiply grabbed
     * window	
    */
    match = 0;
    winp = dga_wlist;

    while (winp) {
	if (winp->w_token == clientp->w_token) {
	    /* Now we have the correct window */
	    struct dga_window *clntp, *prevclntp;

            if (drawableGrabber)         
                clntp = winp->dga_clientplist_draw;
            else
                clntp = winp->dga_clientplist;

            prevclntp = NULL;
            while (clntp) {
		/* Now we have the correct client */
                if (clntp == clientp) {
		   /* Check to see if there are any more... */
		   if (prevclntp || clntp->w_next) {
			match = 1;
			break;	
		    }	
		}
		prevclntp = clntp;
		clntp = clntp->w_next;
	    }
	    if (match) break;
        }
	winp = winp->next_winlist;
    }
    return match; 
}

short *
dga_win_clipinfo(wini)
Dga_window	wini ;
{
    _Dga_window win = (struct dga_window *)wini;
    WXINFO	*infop = (WXINFO *) win->w_info ;

    if (wx_shape_flags(infop) & DGA_SH_RECT_FLAG)
	  return((short *)&((struct class_SHAPE_vn *)((char *)(infop) +
	      (infop)->u.vn.w_shapeoff))->SHAPE_YMIN);
    return(win->w_clipptr);
}


char *
dga_win_fbname(wini)
Dga_window wini;
{
    _Dga_window win = (struct dga_window *)wini;
    
    return(((WXINFO *) (win->w_info))->w_devname);
}

int
dga_win_clipchg(wini)
Dga_window wini;
{
    _Dga_window win = (struct dga_window *)wini;
    
    if (win->c_clipseq != *(win->s_clipseq_p)) {
	((WXINFO *) win->w_info)->w_flag &= ~WMODIF;
	win->c_clipseq = *(win->s_clipseq_p);
	return 1;
    }
    return 0;
}

int
dga_win_curschg(wini)
Dga_window wini;
{
    _Dga_window win = (struct dga_window *)wini;
    
    if (win->c_curseq != *(win->s_curseq_p)) {
	win->c_curseq = *(win->s_curseq_p);
	return 1;
    }
    return 0;
}

int
dga_win_rtnchg(wini)
Dga_window wini;
{
    _Dga_window win = (struct dga_window *)wini;
    if ((win->rtn_flags & RTN_GRABBED) && !(win->rtn_flags & RTN_MAPPED)) {
	/* rtn grabbed, but not currently mapped */
	if (win->rtn_flags & RTN_MAPCHG) {
	    /* just went unmapped */
	    win->rtn_flags &= ~RTN_MAPCHG;
	    return 1;
	}
	return 0;
    }
    /* otherwise either not rtn grabbed or have a rtn mapping */
    if (win->c_rtnseq != *(win->s_rtnseq_p)) {
	win->c_rtnseq = *(win->s_rtnseq_p);
	return 1;
    }
    return 0;
}

int
dga_win_devfd(wini)
Dga_window wini;
{
    _Dga_window win = (struct dga_window *)wini;
    return(win->w_devfd);
}

void
dga_win_bbox(wini, xp, yp, widthp, heightp)
Dga_window wini;
int *xp, *yp, *widthp, *heightp;
{
    _Dga_window win = (struct dga_window *)wini;
    WXINFO *infop = (WXINFO *) win->w_info;

    if (infop->w_version < 2) {
	*xp = infop->w_org.x >> 16;
	*yp = infop->w_org.y >> 16;
	*widthp = infop->w_dim.x >> 16;
	*heightp = infop->w_dim.y >> 16;
	return;
    }
    *xp = infop->w_window_boundary.xleft;
    *yp = infop->w_window_boundary.ytop;
    *widthp = infop->w_window_boundary.width;
    *heightp = infop->w_window_boundary.height;
}

int
dga_win_singlerect(wini)
Dga_window wini;
{
    _Dga_window win = (struct dga_window *)wini;
    WXINFO *infop = (WXINFO *) win->w_info;

    return(wx_shape_flags(infop) & DGA_SH_RECT_FLAG);
}

int
dga_win_empty(wini)
Dga_window wini; 
{ 
    _Dga_window win = (struct dga_window *)wini;
    WXINFO *infop = (WXINFO *) win->w_info;

    return(wx_shape_flags(infop) & DGA_SH_EMPTY_FLAG);
}

u_char
dga_win_depth(wini)
Dga_window wini;
{
    _Dga_window win = (struct dga_window *)wini;
    WXINFO *infop = (WXINFO *) win->w_info;
	
    if (infop->w_version >= 3) 
	return(infop->w_depth);
    else 
	return 0;
}

u_short
dga_win_borderwidth(wini) 
Dga_window wini; 
{ 
    _Dga_window win = (struct dga_window *)wini;
    WXINFO *infop = (WXINFO *) win->w_info; 
      
    if (infop->w_version >= 3) 
        return(infop->w_borderwidth);
    else  
        return 0; 
} 

int
dga_win_obscured(wini)
Dga_window wini;
{
    _Dga_window win = (struct dga_window *)wini;
    WXINFO *infop = (WXINFO *) win->w_info;
    int xb, yb, wb, hb;
    int ytop, ybot, xleft, xright;
    int tmp;
    short *ptr;

    if (wx_shape_flags(infop) & DGA_SH_RECT_FLAG) {
	dga_win_bbox(win, &xb, &yb, &wb, &hb);
	ptr = dga_win_clipinfo(win);
	ytop = *ptr++; ybot = *ptr++; xleft = *ptr++; xright = *ptr++;
	if (ytop > ybot) {
	    tmp = ytop; ytop = ybot; ybot = tmp;
	}
	if (xleft > xright) {
	    tmp = xleft; xleft = xright; xright = tmp;
	}
	if ((yb == ytop) && (xb == xleft) &&
	    (hb == (ybot - ytop)) && (wb == (xright - xleft))) {
		return 1;
	}
    }
    return 0;
}

int
dgai_win_visibility(Dga_window wini)
{
    if (dga_win_empty(wini))
	return (DGA_VIS_FULLY_OBSCURED);
    /* This routine returns the reverse of what one would think.
     * it returns true if the window is unobscured false otherwise. */
    else if (!dga_win_obscured(wini))
	return (DGA_VIS_PARTIALLY_OBSCURED);
    
    return (DGA_VIS_UNOBSCURED);

    /*  This will work when we get to R6 but for now the visibility
     * entry in the window structure (which is where this comes from)
     * is bogus.  I looked at the R6 code and it looks like they
     * attempted to get this working.
    _Dga_window win = (struct dga_window *)wini;
    WXINFO *infop = (WXINFO *) win->w_info;
    
    return (infop->w_visibility);
    */
}	

#define	ROUNDUP(i)	(((i)+WX_PAGESZ-1)&~(WX_PAGESZ-1))

void
dgai_win_clip_update (_Dga_window clientp)
{
    /* Do anything here that may require unlock/relock, because
    * it takes so long.
    */

    WXINFO	*infop = (WXINFO *) clientp->w_info ;
    unsigned int	cliplen;
    short	*clipptr;
    short	*cmclip;
#ifndef SERVER_DGA
    char	filename[sizeof(GRABFILE)+NDIGITS+1];
    int		filefd;
#endif /*SERVER_DGA */

    cmclip = (short *)((char *)infop+infop->u.vn.w_clipoff);

#ifdef SERVER_DGA
    if (infop->w_flag & WEXTEND) { /* server has an extended mapping */
        if (clientp->w_clipptr == cmclip) {
            clientp->w_cliplen = infop->w_scliplen;
            clientp->w_clipptr = (short *)infop->u.vn.w_sclipptr;
        }
    } else {
        if (clientp->w_clipptr != cmclip) {
            clientp->w_clipptr = cmclip;
        }
    }
#else
    while(1) {
	if (infop->w_flag & WEXTEND) { 
	    /* server has an extended mapping */
	    if (clientp->w_clipptr == cmclip) { 
		/* ...and we don't. */
		cliplen = infop->w_scliplen;
		DGA_UNLOCK(clientp);
		sprintf(filename, "%s%08x", GRABFILE, clientp->w_token);

		if ((filefd = open(filename,O_RDWR,0666))<0) {
		    return;
		}
		if (ftruncate(filefd,MINSHMEMSIZE+cliplen)<0) {
		    close(filefd);
		    return;
		}

		close(filefd);

		clipptr = (short *)((char *)infop + MINSHMEMSIZE);

		DGA_LOCK(clientp);
		if ((int)clipptr != -1) {
		    clientp->w_cliplen = cliplen;
		    clientp->w_clipptr = clipptr;
		}
		continue;  /* at while */
	    }
	    if (clientp->w_cliplen != infop->w_scliplen) {
		/* ...and we do... but the wrong size. */
		cliplen = infop->w_scliplen;
		DGA_UNLOCK(clientp);
		sprintf(filename, "%s%08x", GRABFILE, clientp->w_token);

		if ((filefd = open(filename,O_RDWR,0666))<0) {
		    return;
		}
		if (ftruncate(filefd,MINSHMEMSIZE+cliplen)<0) {
		    close(filefd);
		    return;
		}
		close(filefd);
		clipptr = (short *)((char *)infop + MINSHMEMSIZE);

		DGA_LOCK(clientp);
		if ((int)clipptr == -1)
		    clientp->w_clipptr = cmclip;
		else {
		    clientp->w_cliplen = cliplen;
		    clientp->w_clipptr = clipptr;
		}
		continue;  /* at while */
	    }
	} else { 	
	    /* server doesn't have an extended mapping */
            if (clientp->w_clipptr != cmclip) { 
		/* ...and we do. */
                DGA_UNLOCK(clientp);
		sprintf(filename, "%s%08x", GRABFILE, clientp->w_token);

		if ((filefd = open(filename,O_RDWR,0666))<0) {
		    clientp->w_clipptr = cmclip;
		    return;
		}
		if (ftruncate(filefd,MINSHMEMSIZE)<0) {
		    clientp->w_clipptr = cmclip;
		    close(filefd);
		    return;
		}
		close(filefd);

                DGA_LOCK(clientp);
		clientp->w_clipptr = cmclip;
		continue;  /* at while */
	    }
	    /*
	    else {	 ...nor do we
		break;
	    }
	    */
	}
    break;
    }
#endif /* SERVER_DGA */
}

void
dgai_win_curs_update(_Dga_window win)
{
    /* Do anything here that may require unlock/relock, because
    * it takes so long.
    *
    * We can add code here in the future to remap the cursor page,
    * etc., if we want.
    */
    return;
}


/*
 *
 *  dgai_rtn_update()
 *
 *  Do anything here that may require unlock/relock, because
 *  it takes so long.  Remap retained info, etc.
 *
 *  DGA Retained Window Information Update.  This function checks that the
 *  shared retained information structure hasn't become obsolete.  If the
 *  structure is found to be obsolete, this routine attempts to free and
 *  re-allocate the resources associated with the retained window.  Nothing
 *  is done in the event that the shared retained information is not obsolete.
 *
 *  Inputs:     Dga_window - Pointer to the dga_window structure for which
 *                           the the shared retained info structure is to
 *                           be removed.
 *
 *  Outputs:    None.
 *
 *  Globals:    None.
 *
 *  Externals:  DGA_LOCK()              DGA MACRO
 *              DGA_UNLOCK()            DGA MACRO
 *              RTN_INFOP()             DGA MACRO
 *              _dga_rtn_map()
 *              _dga_rtn_unmap()
 *
 */
void
dgai_win_rtn_update (_Dga_window clientp)
{
    unsigned int         mapped;
 
#ifdef SERVER_DGA
    mapped = clientp->rtn_flags & RTN_MAPPED;
    if (mapped && RTN_INFOP(clientp)->obsolete) {
        /* mapped, but obsolete */
        (void) _dga_rtn_unmap(clientp);
        (void)  _dga_rtn_map(clientp);
    }
 
    if (!mapped && (((WXINFO *) clientp->w_info)->w_srtndlink != NULL)) {
        /* unmapped on client side, but server has valid w_srtndlink */
        (void) _dga_rtn_map(clientp);
    }
#else
    while (1) {
	mapped = clientp->rtn_flags & RTN_MAPPED;
        if (mapped && RTN_INFOP(clientp)->obsolete) {
	    /* mapped, but obsolete */
            DGA_UNLOCK(clientp);
            (void) _dga_rtn_unmap(clientp);
            (void)  _dga_rtn_map(clientp);
            DGA_LOCK(clientp);
            continue;
        } 
	if (!mapped && (((WXINFO *) clientp->w_info)->w_srtndlink != NULL)) {
	    /* unmapped on client side, but server has valid w_srtndlink */
	    DGA_UNLOCK(clientp);
	    (void) _dga_rtn_map(clientp);
	    DGA_LOCK(clientp);
	    continue;
	}
        break;
    }    
#endif /* SERVER_DGA */
}


static int
dga_win_update(wini)
Dga_window wini;
{
    _Dga_window win = (struct dga_window *)wini;
    WXINFO *infop = (WXINFO *) win->w_info;
    unsigned int sav_clipseq, sav_curseq, sav_rtnseq;

    /* establish the new real lock subject */
    win->rLockSubj = -1;
 
    /* save last lock subject.  This may be used later in the update phase */
    win->eLockSubjPrev = win->eLockSubj;

    /* start out assuming we're not aliased.  This may change if we detect
       aliasing later in the update phase */
    win->eLockSubj = win->rLockSubj;

    /* Do anything here that may require unlock/relock, because
    * it takes so long.  Also, update win->c_chngcnt.
    */

    sav_clipseq = win->c_clipseq;
    sav_curseq = win->c_curseq;
    sav_rtnseq = win->c_rtnseq;
    do {
	/* repeat update functions as needed
	 * through possible unlock/relocks
	*/
	if (sav_clipseq != *win->s_clipseq_p) {
	    dgai_win_clip_update(win);
	    sav_clipseq = *win->s_clipseq_p;
	}
	if (sav_curseq != *win->s_curseq_p) {
	    dgai_win_curs_update(win);
	    sav_curseq = *win->s_curseq_p;
	}
	if ((sav_rtnseq != *win->s_rtnseq_p) ||
	    ((win->rtn_flags & RTN_GRABBED) &&
	     !(win->rtn_flags & RTN_MAPPED))) {
		dgai_win_rtn_update(win);
		sav_rtnseq = *win->s_rtnseq_p;
	}
    } while ((sav_clipseq != *win->s_clipseq_p) ||
	 (sav_curseq != *win->s_curseq_p) ||
	 (sav_rtnseq != *win->s_rtnseq_p));

    if (infop->w_version < 2) {	
	/* pre OWV3 */
	win->c_chngcnt = *win->s_chngcnt_p;
	return 1;
    } else {		
	/* post OWV3 beta */
	win->c_chngcnt = *win->s_chngcnt_p;
	return 1;
    }
}

int
dga_win_cursactive(wini)
Dga_window wini;
{
    _Dga_window win = (struct dga_window *)wini;
    if (win->curs_info)
	return 1;
    return 0;
}

void
dga_win_cursupdate(wini, func, data)
Dga_window	wini;
void		(*func)();
void*		data;
{
    _Dga_window win = (struct dga_window *)wini;
    /* assumes the window is already locked */

    Dga_cursinfo	*curgp = (Dga_cursinfo *) (win->curs_info);
    Dga_curs_mpr	*curg_mpr;
    Dga_curs_memimage curg_mem;
    int		x, y, w, h;

    if ((curgp == 0) || (curgp->c_state_flag != DGA_CURSOR_UP))
		return;

    curg_mpr = (Dga_curs_mpr *) ((char *) curgp + curgp->c_offset);

    dga_win_bbox(win, &x, &y, &w, &h);
    if (((curgp->c_org.x + curg_mpr->curg_dim.x) < x) ||
        (curgp->c_org.x > (x + w)) ||
        ((curgp->c_org.y + curg_mpr->curg_dim.y) < y) ||
        (curgp->c_org.y > (y + h)))
    	return;

    if (func) {
	curg_mem.width = curg_mpr->curg_dim.x;
	curg_mem.height = curg_mpr->curg_dim.y;
	curg_mem.depth = curg_mpr->curg_depth;
	curg_mem.linebytes = curg_mpr->curg_linebytes;
#ifdef _LP64
	curg_mem.memptr = (void *)(curg_mpr + 1);
#else  /* _LP64 */
	curg_mem.memptr = ((caddr_t) curg_mpr) + sizeof(Dga_curs_mpr);
#endif /* _LP64 */
	(*func) (data, win, curgp->c_org.x, curgp->c_org.y, &curg_mem);
	curgp->c_state_flag = DGA_CURSOR_DOWN;
	/* have to bump the shared memory counter, so update the saved
	* version as well
	*/
	win->c_curseq = ++(curgp->c_chng_cnt); 
    }
}

Dga_dbinfo *
dga_win_dbinfop(wini)
Dga_window wini;
{
    _Dga_window win = (struct dga_window *)wini;
    return ((Dga_dbinfo *)&(((WXINFO *) win->w_info)->wx_dbuf));
}

Dga_widinfo *
dga_win_widinfop(wini)
Dga_window wini;
{
    _Dga_window win = (struct dga_window *)wini;
    return ((Dga_widinfo *)(&(((WXINFO *) win->w_info)->w_wid_info)));
}

void
dga_win_set_client_infop(wini, client_info_ptr)
Dga_window wini;
void* client_info_ptr;
{
    _Dga_window win = (struct dga_window *)wini;
    win->w_client = client_info_ptr;
}

void *
dga_win_get_client_infop(wini)
Dga_window wini;
{
    _Dga_window win = (struct dga_window *)wini;
    return (void *)(win->w_client);
}


static int
dgai_win_initMbufset (_Dga_window dgawin)
{
    WXINFO	*infop;
    int		status = 0; 

    /* Lock the window to see if it is multibuffered */
#ifndef SERVER_DGA
    DGA_LOCK(dgawin);
#endif /* SERVER_DGA */

    infop = (WXINFO *) dgawin->w_info;
    if (!infop->w_mbsInfo.enabled) {
	/* it's okay if it's not multibuffered; return success */
	dgawin->pMbs = NULL;
	status = 1;
	goto Exit;
    }

    if (!(dgawin->pMbs = dgai_mbufset_create(dgawin))) {
	goto Exit;
    }

    dgawin->c_mbcomposseq = *dgawin->s_mbcomposseq_p;

    /* success */
    status = 1;

Exit:
#ifndef SERVER_DGA
    DGA_UNLOCK(dgawin);
#endif /* SERVER_DGA */
    return (status);
}

#ifdef SERVER_DGA
/*
 *  There is no equivalent for the following function in client side
 *  The main purpose of this function is to isolate SHAPES header files
 *  and XGL files.
 */

void
dga_win_lock(win)
Dga_window win;
{
       _Dga_window 	wini = (_Dga_window)win;

       if (((wini)->w_lockcnt)++ == 0) {
            wg_lock((WXINFO *) (wini->w_lib_private));
            DGA_S_LOCK(wini);
            wini->w_modif = ((((wini)->c_chngcnt) == (*((wini)->s_chngcnt_p)))
                 ? 0 : (*((wini)->w_update_func))(wini));
       } 
 
}
 
/*
 *  There is no equivalent for the following function in client side
 *  The main purpose of this function is to isolate SHAPES header file
 *  and XGL files.
 */
 
void
dga_win_unlock(win)
Dga_window win;
{
       _Dga_window 	wini = (_Dga_window)win;

        if (--((wini)->w_lockcnt) == 0) {
                        wg_unlock((WXINFO *) (wini->w_lib_private));
                        if ((wini)->w_unlock_func)
                                (*((wini)->w_unlock_func))(wini);
        }
 
}
#endif /* SERVER_DGA */


#ifdef	DEBUG
dga_win_dump(clientpi)
	Dga_window	clientpi ;
{
	_Dga_window clientp = (struct dga_window *)clientpi;
WXINFO	*infop = (WXINFO *) clientp->w_info ;

	printf("client page is %p\n", clientp) ;
	printf("  w_info = %p\n", (WXINFO *) clientp->w_info) ;
	printf("  w_next = %p\n", clientp->w_next) ;
	printf("  w_client = %p\n", clientp->w_client) ;
	printf("  c_clipseq = %u\n", clientp->c_clipseq) ;
	printf("  s_clipseq_p = %p\n", clientp->s_clipseq_p) ;
	printf("  w_update_func = %p\n", clientp->w_update_func) ;
	printf("  w_infofd = %d\n", clientp->w_infofd) ;
	printf("  w_devfd = %d\n", clientp->w_devfd) ;
	printf("  w_lockcnt = %d\n", clientp->w_lockcnt) ;
	printf("  w_lockp = %p\n", clientp->w_lockp) ;
	printf("  w_unlockp = %p\n", clientp->w_unlockp) ;
	printf("  w_clipptr = %p\n", clientp->w_clipptr) ;
	printf("  w_cliplen = %u\n", clientp->w_cliplen) ;

	printf("info page is %p\n", infop) ;
	printf("  w_flag = %lu\n", infop->w_flag) ;
	printf("  w_magic = %ld\n", infop->w_magic) ;
	printf("  w_version = %ld\n", infop->w_version) ;
	printf("  w_cunlockp = %p\n", infop->w_cunlockp) ;
	printf("  w_devname = %s\n", infop->w_devname) ;
	printf("  w_cookie = %lu\n", infop->w_cookie) ;
	printf("  w_clipoff = %ld\n", infop->u.vn.w_clipoff) ;
	printf("  w_scliplen = %u\n", infop->w_scliplen) ;
	printf("  w_org = %u,(%f,%f)\n",
		infop->w_org.t, infop->w_org.x/65536., infop->w_org.y/65536.) ;
	printf("  w_dim = %u,(%f,%f)\n",
		infop->w_dim.t, infop->w_dim.x/65536., infop->w_dim.y/65536.) ;
	printf("  &w_shape_hdr = %p\n", &infop->u.v0.w_shape_hdr) ;
	printf("  &w_shape = %p\n", &infop->w_shape) ;
	printf("  w_shape.SHAPE_FLAGS = %u\n", infop->w_shape.SHAPE_FLAGS) ;
	printf("  w_shape.SHAPE_YMIN = %d\n", infop->w_shape.SHAPE_YMIN) ;
	printf("  w_shape.SHAPE_YMAX = %d\n", infop->w_shape.SHAPE_YMAX) ;
	printf("  w_shape.SHAPE_XMIN = %d\n", infop->w_shape.SHAPE_XMIN) ;
	printf("  w_shape.SHAPE_XMAX = %d\n", infop->w_shape.SHAPE_XMAX) ;
	printf("  w_shape.SHAPE_X_EOL = %d\n", infop->w_shape.SHAPE_X_EOL) ;
	printf("  w_shape.SHAPE_Y_EOL = %d\n", infop->w_shape.u.SHAPE_Y_EOL) ;
	printf("  &w_cliparray = %p\n", &infop->w_cliparray) ;
}
#endif /* DEBUG */

#ifdef MT
int
dgai_unlock(Dga_drawable dgadraw)
{
    _Dga_window dgawin;

    if (dgaMTOn) {
	dgawin = (_Dga_window) dgadraw;
	mutex_unlock(dgawin->mutexp);
    }
    return Success;
}
#endif
