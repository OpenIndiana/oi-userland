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


#ifndef _DGA_INTERNAL_H
#define _DGA_INTERNAL_H

/*
 * dga_internal.h - Sun Direct Graphics Access interface internal include file
 */

/* Note that _Dga_window, _Dga_cmap, _Dga_pixmap are all internal declarations
 * for the externally visible Dga_window, Dga_cmap and Dga_pixmap ( no leading
 * underscore). In the externally visible include file, these are all declared
 * as void * and thus quite opaque.
 *
 * Note: there is a DGA_FAST_DRAW_LOCK() macro that also access the
 * fields in struct dga_window and dga_pixmap but is not currently in dga.h.
 * Consider this macro before modifying fields.
*/

typedef u_int   *Dga_lockp;
 
typedef struct dga_mbufset *DgaMbufSetPtr;


/* used only to get at the drawable type.  After that, we vector off
   to either a window or pixmap routine */
typedef struct dga_drawable {
        int	    drawable_type;	/* pointer to drawable type */
} *_Dga_drawable;

typedef	struct dga_window {
	int	    drawable_type;	/* pointer to drawable type */
	u_int	    c_chngcnt;          /* last recorded window change count */
	u_int	    *s_chngcnt_p;	/* ptr to server's global change cnt */
	int	    w_lockcnt;	        /* lock count for nested locks */
	Dga_lockp   w_lockp;		/* pointer to lock page */
	Dga_lockp   w_unlockp;		/* points to unlock page */
#ifdef MT
	mutex_t	    *mutexp;   		/* points to drawable's mutex */
#else
	int	    (*w_lock_func)();   /* alternate function for locking */
#endif
	int	    (*w_unlock_func)(Dga_drawable); /* alternate func for unlocking */
	int	    (*w_update_func)(Dga_drawable);
	int	    w_modif;		/* cached result of update check */
	u_int       c_wm_chngcnt[17];	/* last recorded global change counts */
	u_int       *w_wm_2nd;          /* Ptr to second entry in wm_chngcnt[]*/
	void	    *w_info;	        /* pointer to shared memory */
	u_int	    c_clipseq;		/* last recorded clip change count */
	u_int	    *s_clipseq_p;	/* ptr to server's clip change count */
	short	    *w_clipptr;		/* client virtual ptr to clip array. */
	u_int	    w_cliplen;		/* client's size of cliplist in bytes*/
	Dga_token   w_token;		/* token used to grab window */
	int	    w_infofd;		/* fd of shared memory file */
	int	    w_devfd;		/* fd of framebuffer */
	int	    w_grab_count;	/* how many times we've grabbed it */
	struct dga_window *w_next;	/* used to link all grabbed windows */
	void	    *w_lib_private;	/* library private data */
	void	    *w_client;		/* for client use */


	/* cursor grabber info */
	void	    *curs_info;		/* pointer to client's cursor info */
	int	    curs_fd;		/* Client side file descriptor */
	u_int	    c_curseq;		/* last recorded cursor change count */
	u_int	    *s_curseq_p;	/* ptr to server's cursor change cnt */

        /* Ancillay Buffer info */
        void   *back;
        void   *depth;
        void   *stencil;
        void   *accum;
        void   *alpha;
        int    buf_resize_flag;
        u_int  c_buffer_swap;

	/* double buffering info */
	u_int	    db_enabled;		/* flag to tell if initialized */
	u_int	    *db_vrtcntrp;	/* Client's ptr to VRT counter */
	u_int	    db_lastvrtcntr;	/* VRT counter value at last flip */
	u_int	    db_swapint;		/* number of intervals between flips */
	int	   (*vrt_func)(Dga_window);/* user supplied vrt retrace func */

	/* retained window grabber info */
	int	    rtn_fd;	/* Client side fd for shared memory */
	u_int	    rtn_size;	/* Client size of pixel block in bytes */
	u_int	    c_rtnseq;	/* Client rtn modification counter */
	u_int	    *s_rtnseq_p;/* Ptr to server's rtn mod counter */
	u_int	    c_rtncachseq;/* Client device cache modification counter */
	u_int	    *s_rtncachseq_p; /* Ptr to server's dev cache modification counter */
	void	    *rtn_info;	/* Ptr to Shared memory structure */
	void	    *rtn_pixels;	/* Client ptr to Client pixel mapping */
	u_int	    rtn_flags;	/* to record state of retained grab */

	/*
	** New fields for drawable grabber.
        */

	Display     	*w_dpy;			/* display the window belongs to */
	Window		w_id;			/* XID of window */
	DgaMbufSetPtr	pMbs;			/* Non-null for multibuf wins */
	u_int		*s_mbufseq_p;		/* pointer to mbuf seq in shinfo */
	u_int		c_mbufseq;		/* last mbufset composition sequence count */
	u_int		*s_mbcomposseq_p;	/* pointer to mbufset compos seq in shinfo */
	u_int		c_mbcomposseq;		/* last mb state sequence count */
	u_int		*s_devinfoseq_p;	/* pointer to devinfo seq in shinfo */
	u_int		c_devinfoseq;		/* last devinfo state sequence count */

	/* notification functions */
	DgaSiteNotifyFunc    siteNotifyFunc;
	void		     *siteNotifyClientData;
	DgaMbNotifyFunc	     mbNotifyFunc;
	void		     *mbNotifyClientData;
	DgaRendBufNotifyFunc rendBufNotifyFunc;
	void		     *rendBufNotifyClientData;

	/*  real lock subject - the win/mbuf currently locked by the client */
	short		rLockSubj;

	/*  effective lock subject - the actual lock subject. This will be used by
	    the DGA state inquiry functions called by the client.   If the 
	    win/mbuf is not aliased, eLockSubj will be the same as rLockSubj */
	short		eLockSubj;

	/*  previous effective lock subject - the lock subject for which a
	    change was last signalled to the client.  It is assumed that the
	    client synchronized its state to this lock subject.  This is always
	    true for well-behaved DGA clients */
	short		eLockSubjPrev;
	
	/* mbChgReason is the reason for an mbufset change.  prevWasMbuffered 
	   is used to help us figure this out.  It is set during the update
	   phase and may be used during the inquiry phase */
	char   		prevWasMbuffered;
        char		mbChgReason;

	/* used during update phase to indicate what state changed */
	u_int		changeMask;

	/* reason for any site change */
        char		siteChgReason;

	/* Has the window been previously locked? */
	char		prevLocked;

	u_char	        alignPad[2];

	/* overlay info
	 *
	 * If the window is an overlay, the isOverlay flag will be set to
	 * true and the s_ovlstate_p pointer will point to the ovlstate
	 * flag on the shared page and the s_ovlshapevalid_p pointer will
	 * point to the w_ovl_shape_valid flag.
	 */
	int		isOverlay;
	int		c_ovlstate;
	int		*s_ovlstate_p;
	int		*s_ovlshapevalid_p;
	DgaOvlStateNotifyFunc ovlStateNotifyFunc;
	void		*ovlStateNotifyClientData;

#ifdef MT
	/* For the threaded case, this stores the real change counts while
	 * c_wm_chngcnt[] is used to force the update function to be called.
	 */
	u_int		shadow_chngcnt[17];
#endif

} *_Dga_window;


typedef struct _dgaLastSeqs {
    u_int	mbufseq;
    u_int 	clipseq;
    u_int 	curseq;
    u_int 	rtnseq;
} DgaLastSeqs, *DgaLastSeqsPtr;

typedef	struct dga_cmap {
	void	    *cm_info;/* pointer to shared memory */
	u_int	    c_chngcnt;		/* last recorded change count */
	u_int	    *s_chngcnt_p;	/* last recorded change count */
	int	    cm_lockcnt;		/* lock count for nested locks */
	u_int	    *cm_lockp;		/* pointer to lock page */
	u_int	    *cm_unlockp;	/* pointer to unlock page */
	int	    cm_use_new_ioctl; 	/* use new hardware ioctl? */
	Dga_token   cm_token;		/* token used to grab cmap */
	int	    cm_infofd;		/* fd of shared memory file */
	int	    cm_devfd;		/* fd of framebuffer */
	int	    cm_lockfd;		/* fd of lock device 
					 * (if not framebuffer) */
	int	    cm_sunwindows_def_fd; /* client fd for server's
				   	SunWindows default cmap window */
	int	    cm_sunwindows_inst_fd; /* client fd for server's
					   SunWindows installed cmap window */
	int	    cm_grab_count;	/* how many times we've grabbed it */
	struct dga_cmap *cm_next;	/* used to link all grabbed cmaps */
	void	    *cm_lib_private;	/* library private data */
	void	    *cm_client;		/* for client use */
} *_Dga_cmap;

/*
* When the pixmap interface is made public, this declaration should be
* moved into the dga.h file and taken out of the dga_internal.h file
* Also the lock routiens currently in pix_grab,c should be made into
* macros and added to dga.h
*/

typedef struct dga_pixmap {
    int     	drawable_type;  /* pointer to drawable type - window/pixmap*/
    u_int       obsolete;       /* last recorded global change count */
    u_int       *s_chngcnt_p;   /* ptr to server's global change cnt */
    int		p_lockcnt;	/* lock count for nested locks */
    Dga_lockp   p_lockp;        /* pointer to lock page */
    Dga_lockp   p_unlockp;      /* points to unlock page */
#ifdef MT
    mutex_t	*mutexp;   		/* points to drawable's mutex */
#else
    int         (*p_lock_func)(); /* alternate function for locking */
#endif
    int         (*p_unlock_func)(Dga_drawable); /* alternate func for unlocking */
    int         (*p_update_func)(Dga_drawable, short); /* function to call for updates */
    int         p_modif;        /* cached result of update check ?? */
    u_int	c_chngcnt[1];   /* Last recorded global change count */
    u_int       *p_chngcnt_2nd;  /* Pts to c_chngcnt[0]*/
    void     	*p_infop;        /* pointer to shared pixmap memory*/
/* TODO: Why are the next two entries in here?  It's not clear to me why
 * the client side cares if the shpx_dir changes. The only time a pixmap
 * is removed from the directory structure is when it is destroyed and
 * then the obsolete flag is set. */
    u_int       c_dirchngcnt;   /* Client's last recorderd dir chng cnt */
    u_int       *s_dirchngcnt_p;/* Ptr to server's dir chng cnt */
    u_int	c_devinfocnt;   /* Client's last recorded devinfo seq cnt */
    u_int	*s_devinfocnt_p; /* Ptr to server's devinfo seq cnt */
    u_int       c_cachecnt;     /* Client's last recorded cache sequence cnt */
    u_int       *s_cachecnt_p;  /* ptr to Server cache sequence count */
    u_char      c_cached;       /* Client's last recorded cache state */
    u_char      *s_cached_p;   /* Ptr to server's cache state */
    u_int       p_dir_index;    /* Client's pixmap's directory index */
    void     	*p_shpx_dir;     /* Client's ptr to the shpx dir */
    void     	*p_shpx_client;     /* Client's ptr to the shpx client struct */
    Dga_token   p_token;        /* token used to grab window */
    u_int       c_size;         /* Client's size of pixel array */
    u_char      *c_pixels;       /* pointer to clients pixels */ 
    u_char      depth;          /* pixmap depth in bits */
    char        pad0;          /* padding to align to int */
    u_short     pad1;          /* padding to align to int */
    u_int       linebytes;       /* pixmap linebyte */    
    struct dga_pixmap *p_next;  /* used to link all grabbed pixmaps */
    int         p_infofd;       /* fd of shared memory file */  
    u_int       pix_flags;      /* to record state of grab ?? */
    Display	*p_dpy;
    Pixmap	p_id;		/* XID of pixmap */
    void	*p_client;	/* for client use */

    /* used during update phase to indicate what state changed */
    u_int		changeMask;

    /* reason for any site change */
    char		siteChgReason;
    u_char	        alignPad[3];

    DgaSiteNotifyFunc    siteNotifyFunc;
    void        	*siteNotifyClientData;
#ifdef MT
    /* For the threaded case, this stores the real change counts while
     * c_chngcnt[] is used to force the update function to be called.
     */
    u_int	shadow_chngcnt[1];
#endif
} *_Dga_pixmap;

typedef void * Dga_pixmap;

#ifdef MT
extern mutex_t		dgaGlobalMutex;
extern mutex_t		dgaGlobalPixmapMutex;
extern int		dgaThreaded;
extern int		dgaMTOn;
#endif

#ifdef MT
extern int		dgai_unlock(Dga_drawable dgadraw);
#endif

/* Pixmap grabber routines - these are not Public yet */
extern	Dga_token	XDgaGrabPixmap(Display*, Pixmap);
extern	int		XDgaUnGrabPixmap(Display*, Pixmap);
extern Dga_pixmap	dga_pix_grab(Dga_token, Pixmap);
extern	void		dga_pix_ungrab(Dga_pixmap);
extern	int		dga_pix_cachechg(Dga_pixmap);
extern	int		dga_pix_cached(Dga_pixmap);
extern	char*		dga_pix_devname(Dga_pixmap);
extern	void		*dga_pix_pixels(Dga_pixmap);
extern	int		dga_pix_linebytes(Dga_pixmap);
extern	u_char		dga_pix_depth(Dga_pixmap);
extern	void		*dga_pix_devinfo(Dga_pixmap);


/* These are always going to be private routines  to be backward
 * compatible
*/
extern	int		XDgaGrabRetainedWindow(Display*, Window);
extern	int		XDgaUnGrabRetainedWindow(Display *, Window);
extern	int		XDgaGetRetainedPath(Display*, Window, char*);
extern	int		XDgaQueryVersion(Display*, int*, int*);
extern	int		XDgaGrabBuffers(Display *, Window, int	);
extern	int		XDgaUnGrabBuffers(Display *, Window);
extern	void		dga_cm_get(Dga_cmap, int, int, u_char *, u_char *,
					u_char *);
extern	void		dga_cm_put(Dga_cmap, int, int, u_char *, u_char*,
					u_char *);
extern	int		dga_db_access(Dga_window);
extern	void		dga_db_release(Dga_window);
extern	int		dga_db_display_complete(Dga_window, int);
extern void		*dga_rtn_devinfo(Dga_window);

/*
** Internal mbuf grab routine
*/

extern Dga_window	dga_mbuf_grab (int devfd, Dga_token winToken);

/*
** Internal mbufset member update routines
*/

extern int		dgai_mbsmemb_update (Dga_drawable dgadraw, short bufIndex);
extern int		dgai_mbsmemb_syncZombie (_Dga_window dgawin);
extern void		dgai_mbsmemb_syncMbufset (_Dga_window dgawin);
extern void		dgai_mbsmemb_syncRendBuf (_Dga_window dgawin);
extern void		dgai_mbsmemb_figureDerivChgs (_Dga_window dgawin);
extern void		dgai_mbsmemb_notify (_Dga_window dgawin);
extern void		dgai_mbsmemb_devinfo_update(_Dga_window dgawin);


/*
** Internal window update routines
*/

extern Dga_window	dgai_win_grab_common (Display *dpy, int devfd, Dga_token token, int drawableGrabber);
extern int 		dgai_win_update (_Dga_window dgawin, short bufIndex);
extern void		dgai_win_clip_update(_Dga_window dgawin);
extern void		dgai_win_curs_update(_Dga_window dgawin);
extern void		dgai_win_rtn_update(_Dga_window dgawin);
extern void		dgai_win_syncChanges (_Dga_window dgawin, DgaLastSeqsPtr pLastSeqs);
extern int		dgai_win_visibility(Dga_window wini);

/*
** Internal multibuffer update routines
*/

extern int		dgai_mbuf_update (_Dga_window dgawin, short bufIndex);
extern void		dgai_vmbuf_syncChanges (_Dga_window dgawin, DgaLastSeqsPtr pLastSeqs, short bufIndex);
extern void		dgai_nmbuf_syncChanges (_Dga_window dgawin);
extern void		dgai_nmbuf_cache_update(_Dga_window dgawin);
extern void		dgai_nmbuf_devinfo_update(_Dga_window dgawin);

/*
** Internal multibuffer set routines
*/

extern DgaMbufSetPtr	dgai_mbufset_create (_Dga_window dgawin);
extern void		dgai_mbufset_incref (DgaMbufSetPtr pMbs);
extern void		dgai_mbufset_decref (DgaMbufSetPtr pMbs);

/*
** Internal mbufset member inquiry routines
*/

extern Display *	dgai_mbsmemb_display (_Dga_window dgawin);
extern char *		dgai_mbsmemb_devname (_Dga_window dgawin);
extern int		dgai_mbsmemb_devfd (_Dga_window dgawin);
extern int		dgai_mbsmemb_depth (_Dga_window dgawin);
extern void		dgai_mbsmemb_set_client_infop (_Dga_window dgawin, void *client_info_ptr);
extern void *		dgai_mbsmemb_get_client_infop (_Dga_window dgawin);
extern void *		dgai_mbsmemb_devinfo (_Dga_window dgawin);
extern int		dgai_mbsmemb_sitechg (_Dga_window dgawin, int *reason);
extern void		dgai_mbsmemb_sitesetnotify (_Dga_window dgawin, 
						    DgaSiteNotifyFunc site_notify_func,
						    void *client_data);
extern void		dgai_mbsmemb_sitegetnotify (_Dga_window dgawin, 
						    DgaSiteNotifyFunc *site_notify_func,
						    void **client_data);
extern int		dgai_mbsmemb_site (_Dga_window dgawin);
extern void *		dgai_mbsmemb_address (_Dga_window dgawin);
extern int		dgai_mbsmemb_linebytes (_Dga_window dgawin);
extern int		dgai_mbsmemb_bitsperpixel (_Dga_window dgawin);
extern int		dgai_mbsmemb_clipchg (_Dga_window dgawin);
extern void		dgai_mbsmemb_bbox(_Dga_window dgawin, int *xp, int *yp, 
					  int *widthp, int *heightp);
extern int		dgai_mbsmemb_visibility (_Dga_window dgawin);
extern int		dgai_mbsmemb_empty (_Dga_window dgawin);
extern short *		dgai_mbsmemb_clipinfo (_Dga_window dgawin);
extern int		dgai_mbsmemb_singlerect (_Dga_window dgawin);
extern int		dgai_mbsmemb_obscured (_Dga_window dgawin);
extern u_short		dgai_mbsmemb_borderwidth (_Dga_window dgawin);
extern void		dgai_mbsmemb_curshandle (_Dga_window dgawin, DgaCursTakeDownFunc take_down_func,
						 void *client_data);
extern int		dgai_mbsmemb_rtngrab (_Dga_window dgawin);
extern int		dgai_mbsmemb_rtnungrab (_Dga_window dgawin);
extern int		dgai_mbsmemb_rtnchg (_Dga_window dgawin);
extern int		dgai_mbsmemb_rtnactive (_Dga_window dgawin);
extern int		dgai_mbsmemb_rtncached (_Dga_window dgawin);
extern void *		dgai_mbsmemb_rtndevinfop (_Dga_window dgawin);
extern void		dgai_mbsmemb_rtndevtype (_Dga_window dgawin, u_char *type, 
						 char **name);
extern void		dgai_mbsmemb_rtndimensions (_Dga_window dgawin, short *width, 
						    short *height, u_int *linebytes);
extern int		dgai_mbsmemb_rtnbitsperpixel(_Dga_window dgawin);
extern void *		dgai_mbsmemb_rtnpixels (_Dga_window dgawin);
extern int		dgai_mbsmemb_mbchg (_Dga_window dgawin, int *reason);
extern void		dgai_mbsmemb_mbsetnotify (_Dga_window dgawin, DgaMbNotifyFunc mb_notify_func,
						  void *client_data);
extern void		dgai_mbsmemb_mbgetnotify (_Dga_window dgawin, DgaMbNotifyFunc *mb_notify_func,
						  void **client_data);
extern int		dgai_mbsmemb_mbaccessmode (_Dga_window dgawin);
extern int		dgai_mbsmemb_mbsitetypeconst (_Dga_window dgawin);
extern void		dgai_mbsmemb_mbsetrendbufnotify (_Dga_window dgawin, 
							 DgaRendBufNotifyFunc rb_notify_func,
							 void *client_data);
extern void		dgai_mbsmemb_mbgetrendbufnotify (_Dga_window dgawin, 
							 DgaRendBufNotifyFunc *rb_notify_func,
							 void **client_data);
extern int		dgai_mbsmemb_ovlstatechg (_Dga_window dgawin);
extern int		dgai_mbsmemb_ovlstate (_Dga_window dgawin);
extern void		dgai_mbsmemb_setovlstatenotify (_Dga_window dgawin, 
							DgaOvlStateNotifyFunc ovlstate_notify_func,
							void *client_data);
extern void		dgai_mbsmemb_getovlstatenotify (_Dga_window dgawin, 
							DgaOvlStateNotifyFunc *ovlstate_notify_func,
							void **client_data);


/*
** Internal pixmap inquiry routines
*/

/* TODO: dhuff: must supply */

extern int		dgai_pix_update(Dga_drawable dgadraw, short bufIndex);
extern Display *	dgai_pix_display (_Dga_pixmap dgapix);
extern char *		dgai_pix_devname (_Dga_pixmap dgapix);
extern int		dgai_pix_devfd (_Dga_pixmap dgapix);
extern int		dgai_pix_depth (_Dga_pixmap dgapix);
extern void		dgai_pix_set_client_infop (_Dga_pixmap dgapix, void *client_info_ptr);
extern void *		dgai_pix_get_client_infop (_Dga_pixmap dgapix);
extern void *		dgai_pix_devinfo (_Dga_pixmap dgapix);
extern int		dgai_pix_sitechg (_Dga_pixmap dgapix, int *reason);
extern void		dgai_pix_sitesetnotify (_Dga_pixmap dgapix, 
						    DgaSiteNotifyFunc site_notify_func,
						    void *client_data);
extern void		dgai_pix_sitegetnotify (_Dga_pixmap dgapix, 
						    DgaSiteNotifyFunc *site_notify_func,
						    void **client_data);
extern int		dgai_pix_site (_Dga_pixmap dgapix);
extern void *		dgai_pix_address (_Dga_pixmap dgapix);
extern int		dgai_pix_linebytes (_Dga_pixmap dgapix);
extern int		dgai_pix_bitsperpixel (_Dga_pixmap dgapix);
extern int		dgai_pix_clipchg (_Dga_pixmap dgapix);
extern void		dgai_pix_bbox(_Dga_pixmap dgapix, int *xp, int *yp, 
					  int *widthp, int *heightp);
extern int		dgai_pix_empty (_Dga_pixmap dgapix);
extern short *		dgai_pix_clipinfo (_Dga_pixmap dgapix);

#endif /* _DGA_INTERNAL_H */

