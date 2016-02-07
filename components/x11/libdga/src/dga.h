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
 * dga.h - Sun Direct Graphics Access interface
 */

#ifndef _DGA_H
#define _DGA_H

#include <sys/types.h>
#ifndef	SERVER_DGA
#include "X11/Xlib.h"
#endif /* SERVER_DGA */
#include "dga_externaldefs.h"

#if defined (_POSIX_C_SOURCE)
#define u_int uint_t
#endif

#ifdef SERVER_DGA
#define Display void
#define Bool    int
#endif  /* SERVER_DGA */

#define	DGA_X_EOL		(-32767)
#define	DGA_Y_EOL		(-32768)

#define DGA_DB_DEV_INFO_SZ 	132

#define DGA_RTN_NOT_CACHED      0
#define DGA_RTN_SAME_DEV        1
#define DGA_RTN_NEW_DEV         2

#define DGA_CLIENT_VERSION	1

typedef u_int Dga_token;

typedef struct dga_curs_memimage {
	u_int		width;
	u_int		height;
	u_int		depth;
	u_int		linebytes;
	void		*memptr;
} Dga_curs_memimage;

typedef struct dga_dbinfo {
	short		number_buffers;
	short		read_buffer;
	short		write_buffer;
	short		display_buffer;
	u_int		reserved_1;	/* for future use */
	u_int		reserved_2;	/* for future use */
	u_int		reserved_3;	/* for the future  */
	u_int		reserved_4;	/* for the future */
	u_int		reserved_5;	/* for the future */
	u_int		wid;		/* db window id. */
	u_int		unique;
	u_char		device_info[DGA_DB_DEV_INFO_SZ];
} Dga_dbinfo;

#ifndef DGA_NUM_BUFFER_TYPES
/* The following buffer types also defined(duplicated) in 
 * dga_winshared.h file.  * I can't include dga.h in hw/solaris/dga  
 * due to some declarations inconsistency.
 * Whenever someone changes/addes/deleted to this enumerated values, 
 * please also update dga_winshared.h which is located
 * in xc/include/dga/
 */

/* Known types of ancillary buffers */
typedef enum {
   DGA_DEPTH_BUFFER =0,
   DGA_STENCIL_BUFFER,
   DGA_ACCUM_BUFFER,
   DGA_ALPHA_BUFFER,
   DGA_BACK_BUFFER,
   DGA_AUX_BUFFER0,
   DGA_AUX_BUFFER1,
   DGA_AUX_BUFFER2,
   DGA_AUX_BUFFER3
} Dga_buffer_type;
 
#define DGA_NUM_BUFFER_TYPES (DGA_AUX_BUFFER3+1)
#endif

typedef void *Dga_buffer;

typedef struct dga_widinfo {
	short		number_wids;	/* number of contiguous wids alloc */
	short		start_wid;	/* starting wid */
	short		wid;		/* current wid */
	short		reserved_1;	/* for the future */
} Dga_widinfo;

typedef void* Dga_window;
typedef void* Dga_cmap;

/* May be either a window, the main window of a multibuffer set, or a pixmap */
typedef void* Dga_drawable;

typedef struct dga_opaque {
    int     loc_1;
    u_int   loc_2;
    u_int   *loc_3;
    int	    loc_4;
    u_int   *loc_5;
    u_int   *loc_6;
    int	    (*loc_7)(Dga_window);
    int	    (*loc_8)(Dga_window);
    int	    (*loc_9)(Dga_window);
    int	    loc_10;
} *Dga_opaque;

typedef struct dga_opaque_draw {
    int     loc_1;
    u_int   loc_2;
    u_int   *loc_3;
    int	    loc_4;
    u_int   *loc_5;
    u_int   *loc_6;
    int	    (*loc_7)(Dga_drawable);
    int	    (*loc_8)(Dga_drawable);
    int	    (*loc_9)(Dga_drawable);
    int	    loc_10;
    u_int   loc_11[DGA_MAX_GRABBABLE_BUFS + 1];
    u_int   *loc_12;
} *Dga_opaque_draw;

/* Types for drawable notification functions */
typedef void (*DgaSiteNotifyFunc)(Dga_drawable, short, void *, int);
typedef void (*DgaMbNotifyFunc)(Dga_drawable, void *, int);
typedef void (*DgaRendBufNotifyFunc)(Dga_drawable, short, void *);
typedef void (*DgaCursTakeDownFunc)(void *, Dga_drawable, int, int, Dga_curs_memimage *);
typedef void (*DgaOvlStateNotifyFunc)(Dga_drawable, void *, int);

#define DGA_LOCK(x)	(*(((Dga_opaque)(x))->loc_5)) = 1
#define DGA_UNLOCK(x)	(*(((Dga_opaque)(x))->loc_6)) = 0

#define	DGA_WIN_LOCK(win)						\
    do {								\
    if ((((Dga_opaque)(win))->loc_4)++ == 0) {				\
	DGA_LOCK(win);							\
	((Dga_opaque)win)->loc_10 = (((((Dga_opaque)(win))->loc_2) ==	\
	    (*(((Dga_opaque)(win))->loc_3))) ?				\
	    0 : (*(((Dga_opaque)(win))->loc_9))(win));			\
	}								\
    } while (0)

#define DGA_WIN_UNLOCK(win)			\
    do {					\
    if (--(((Dga_opaque)(win))->loc_4) == 0) { 	\
	DGA_UNLOCK(win);			\
	if (((Dga_opaque)(win))->loc_8)		\
		(*(((Dga_opaque)(win))->loc_8))(win);		\
	}					\
    } while (0)

#define	DGA_WIN_MODIF(win)	(((Dga_opaque)win)->loc_10)


/* this is so we can we can enter the opaque interface */
#define DGA_CASTDRAW(dgadraw) ((Dga_opaque_draw)(dgadraw))

typedef int (*DgaDrawUpdateFunc)(Dga_drawable, short);
#define DGA_CASTFUNC(func)    ((DgaDrawUpdateFunc)(func))


#define	DGA_DRAW_LOCK(dgadraw, bufIndex)			              \
{						                              \
    if ((DGA_CASTDRAW(dgadraw)->loc_4)++ == 0) {			      \
    DGA_LOCK(dgadraw);					        	      \
    DGA_CASTDRAW(dgadraw)->loc_10 =                                           \
	      (								      \
	        ((DGA_CASTDRAW(dgadraw)->loc_11[bufIndex + 1]) ==             \
					   (*(DGA_CASTDRAW(dgadraw)->loc_3))) \
		    ? 0							      \
	            : (*DGA_CASTFUNC(DGA_CASTDRAW(dgadraw)->loc_9))           \
			 		          ((dgadraw), (bufIndex))     \
	      );							      \
    }							              \
}

#define DGA_DRAW_UNLOCK(dgadraw)					      \
{									      \
    if (--(DGA_CASTDRAW(dgadraw)->loc_4) == 0) { 			      \
        DGA_UNLOCK(dgadraw);						      \
        if (DGA_CASTDRAW(dgadraw)->loc_8)				      \
	    (*(DGA_CASTDRAW(dgadraw)->loc_8))(dgadraw);			      \
    }									      \
}

#define DGA_DRAW_LOCK_SRC_AND_DST(dgasrc, bufIndexSrc, dgadst, bufIndexDst)  \
{									     \
    /* Always lock pixmap first. */					     \
    if ((DGA_CASTDRAW(dgasrc)->loc_1 == DGA_DRAW_WINDOW) &&	             \
        (DGA_CASTDRAW(dgadst)->loc_1 == DGA_DRAW_PIXMAP)) {	             \
        DGA_DRAW_LOCK(dgadst, bufIndexDst);				     \
        DGA_DRAW_LOCK(dgasrc, bufIndexSrc);				     \
    } else if ((DGA_CASTDRAW(dgasrc)->loc_1 == DGA_DRAW_PIXMAP) &&           \
               (DGA_CASTDRAW(dgadst)->loc_1 == DGA_DRAW_WINDOW)) {           \
        DGA_DRAW_LOCK(dgasrc, bufIndexSrc);				     \
        DGA_DRAW_LOCK(dgadst, bufIndexDst);				     \
    } else if ((DGA_CASTDRAW(dgasrc)->loc_1 == DGA_DRAW_PIXMAP) &&           \
               (DGA_CASTDRAW(dgadst)->loc_1 == DGA_DRAW_PIXMAP)) {           \
        /* We lock the src pixmap and since all pixmaps share the same       \
         * lock page, the dst pixmap is locked as well. */		     \
 									     \
        DGA_DRAW_LOCK(dgasrc, bufIndexSrc);				     \
                							     \
        /* Now update dest pixmap's modif */				     \
 									     \
        DGA_CASTDRAW(dgadst)->loc_10 =					     \
              (((DGA_CASTDRAW(dgadst)->loc_11[0]) ==   	                     \
				 (*(DGA_CASTDRAW(dgadst)->loc_3)))           \
                 ? 0 : (*DGA_CASTFUNC(DGA_CASTDRAW(dgadst)->loc_9))          \
					       ((dgadst), (bufIndexDst)));   \
    }									     \
}
 
#define DGA_DRAW_UNLOCK_SRC_AND_DST(dgasrc, dgadst)			     \
{									     \
    /* Always unlock window first */					     \
    if ((DGA_CASTDRAW(dgasrc)->loc_1 == DGA_DRAW_WINDOW) &&	             \
        (DGA_CASTDRAW(dgadst)->loc_1 == DGA_DRAW_PIXMAP)) {	             \
        DGA_DRAW_UNLOCK(dgasrc);					     \
        DGA_DRAW_UNLOCK(dgadst);					     \
    } else if ((DGA_CASTDRAW(dgasrc)->loc_1 == DGA_DRAW_PIXMAP) &&           \
               (DGA_CASTDRAW(dgadst)->loc_1 == DGA_DRAW_WINDOW)) {           \
        DGA_DRAW_UNLOCK(dgadst);					     \
        DGA_DRAW_UNLOCK(dgasrc);					     \
    } else if ((DGA_CASTDRAW(dgasrc)->loc_1 == DGA_DRAW_PIXMAP) &&           \
               (DGA_CASTDRAW(dgadst)->loc_1 == DGA_DRAW_PIXMAP)) {           \
        /* Unlock the src pixmap */					     \
        DGA_DRAW_UNLOCK(dgasrc);					     \
    }									     \
}	

#define	DGA_DRAW_MODIF(dgadraw)	(((Dga_opaque_draw)(dgadraw))->loc_10)

#define DGA_INIT()	dga_init_version(DGA_CLIENT_VERSION)


#ifdef	__cplusplus
extern "C" {
#endif

 /* General DGA functions */
extern	void		dga_init_version(int);
/*
 *  X protocol extension functions
 */
extern	Dga_token	XDgaGrabWindow(Display*, Window);
extern	int		XDgaUnGrabWindow(Display*, Window);
extern	Dga_token	XDgaGrabColormap(Display*, Colormap);
extern	int		XDgaUnGrabColormap(Display*, Colormap);
extern	int		XDgaGrabWids(Display*, Window, int);
extern	int		XDgaGrabFCS(Display*, Window, int);
extern	int		XDgaGrabZbuf(Display*, Window, int);
extern	int		XDgaGrabStereo(Display*, Window, int);
/*
 *  Window Compatibility Interface - Window grabber functions
 */

extern	Dga_window	dga_win_grab(int, Dga_token);
extern	void		dga_win_ungrab(Dga_window, int);
extern	char		*dga_win_fbname(Dga_window);
extern	int		dga_win_devfd(Dga_window);
extern	int		dga_win_clipchg(Dga_window);
extern	int		dga_win_curschg(Dga_window);
extern	int		dga_win_rtnchg(Dga_window);
extern	short		*dga_win_clipinfo(Dga_window);
extern	void		dga_win_bbox(Dga_window, int *, int *, int *, int *);
extern	int		dga_win_singlerect(Dga_window);
extern	int		dga_win_empty(Dga_window);
extern	int		dga_win_obscured(Dga_window);
extern	int		dga_win_cursactive(Dga_window);
extern	void		dga_win_cursupdate(Dga_window, void(*)(void *,
			    Dga_window, int, int, Dga_curs_memimage*), void *);
extern	Dga_dbinfo	*dga_win_dbinfop(Dga_window);
extern	Dga_widinfo	*dga_win_widinfop(Dga_window);
extern  void		*dga_win_bboxinfop(Dga_window);
extern u_char		dga_win_depth(Dga_window);
extern u_short		dga_win_borderwidth(Dga_window);
extern void		dga_win_set_client_infop(Dga_window, void *);
extern void		*dga_win_get_client_infop(Dga_window);

/*
 *  Colormap grabber functions
 */

extern	Dga_cmap	dga_cm_grab(int, Dga_token);
extern	void		dga_cm_ungrab(Dga_cmap, int);
extern	void		dga_cm_read(Dga_cmap, int, int, u_char *, u_char *,
					u_char *);
extern	void		dga_cm_write(Dga_cmap, int, int, u_char *, u_char*,
					u_char *, void (*)(Dga_window, int,
					int, u_char *, u_char *, u_char *));
extern int		dga_cm_devfd(Dga_cmap);
extern void		dga_cm_set_client_infop(Dga_cmap, void *);
extern void		*dga_cm_get_client_infop(Dga_cmap);
extern void		*dga_cm_devinfop(Dga_cmap);

/*
 *  Window Compatibility Interface - double buffering functions
 */

extern	int		dga_db_grab(Dga_window, int, int (*)(Dga_window),
			     u_int * );
extern	int		dga_db_ungrab(Dga_window);
extern	void		dga_db_write(Dga_window, int,
			    int(*)(void*, Dga_window, int), void *);
extern	void		dga_db_read(Dga_window,int,
			    int(*)(void*, Dga_window, int), void *);
extern	void		dga_db_display(Dga_window, int,
			    int(*)(void*, Dga_window, int), void *);
extern	void		dga_db_interval(Dga_window, int);
extern	void		dga_db_interval_wait(Dga_window);
extern	int		dga_db_interval_check(Dga_window);
extern	int		dga_db_write_inquire(Dga_window);
extern	int		dga_db_read_inquire(Dga_window);
extern	int		dga_db_display_inquire(Dga_window);
extern	int		dga_db_display_done(Dga_window, int, 
			    int (*)(Dga_window));
/*
 *  Window Compatibility Interface - Retained window grabber functions
 */

extern	int		dga_rtn_grab(Dga_window);
extern	int		dga_rtn_ungrab(Dga_window);
extern	int		dga_rtn_active(Dga_window);
extern	int		dga_rtn_cached(Dga_window);
extern	void		*dga_rtn_devinfo(Dga_window);
extern	void		dga_rtn_devtype(Dga_window, u_char *, char **);
extern	void		dga_rtn_dimensions(Dga_window, short *, short *,
			    u_int*);
extern	void		*dga_rtn_pixels(Dga_window);

/*
 *  Drawable grabber functions
 */

extern Dga_drawable	XDgaGrabDrawable(Display *dpy, Drawable drawid);
extern int 		XDgaUnGrabDrawable(Dga_drawable dgadraw);
extern Display *	dga_draw_display (Dga_drawable dgadraw);
extern Drawable 	dga_draw_id(Dga_drawable);
extern int		dga_draw_type (Dga_drawable dgadraw);
extern char *		dga_draw_devname (Dga_drawable dgadraw);
extern int		dga_draw_devfd (Dga_drawable dgadraw);
extern int		dga_draw_depth (Dga_drawable dgadraw);
extern void		dga_draw_set_client_infop (Dga_drawable dgadraw, void *client_info_ptr);
extern void *		dga_draw_get_client_infop (Dga_drawable dgadraw);
extern void *		dga_draw_devinfo (Dga_drawable dgadraw);
extern int		dga_draw_sitechg (Dga_drawable dgadraw, int *reason);
extern void		dga_draw_sitesetnotify (Dga_drawable dgadraw, 
						    DgaSiteNotifyFunc site_notify_func,
						    void *client_data);
extern void		dga_draw_sitegetnotify (Dga_drawable dgadraw, 
						    DgaSiteNotifyFunc *site_notify_func,
						    void **client_data);
extern int		dga_draw_site (Dga_drawable dgadraw);
extern void *		dga_draw_address (Dga_drawable dgadraw);
extern int		dga_draw_linebytes (Dga_drawable dgadraw);
extern int		dga_draw_clipchg (Dga_drawable dgadraw);
extern void		dga_draw_bbox(Dga_drawable dgadraw, int *xp, int *yp, 
					  int *widthp, int *heightp);
extern int		dga_draw_visibility (Dga_drawable dgadraw);
extern int		dga_draw_empty (Dga_drawable dgadraw);
extern short *		dga_draw_clipinfo (Dga_drawable dgadraw);
extern int		dga_draw_singlerect (Dga_drawable dgadraw);
extern int		dga_draw_obscured (Dga_drawable dgadraw);
extern u_short		dga_draw_borderwidth (Dga_drawable dgadraw);
extern void		dga_draw_curshandle (Dga_drawable dgadraw, 
					     DgaCursTakeDownFunc take_down_func,
					     void *client_data);
extern int		dga_draw_rtngrab (Dga_drawable dgadraw);
extern int		dga_draw_rtnungrab (Dga_drawable dgadraw);
extern int		dga_draw_rtnchg (Dga_drawable dgadraw);
extern int		dga_draw_rtnactive (Dga_drawable dgadraw);
extern int		dga_draw_rtncached (Dga_drawable dgadraw);
extern void *		dga_draw_rtndevinfop (Dga_drawable dgadraw);
extern void		dga_draw_rtndevtype (Dga_drawable dgadraw, u_char *type, 
					     char **name);
extern void		dga_draw_rtndimensions (Dga_drawable dgadraw, short *width, 
						short *height, u_int *linebytes);
extern void *		dga_draw_rtnpixels (Dga_drawable dgadraw);
extern int		dga_draw_mbchg (Dga_drawable dgadraw, int *reason);
extern void		dga_draw_mbsetnotify (Dga_drawable dgadraw, DgaMbNotifyFunc mb_notify_func,
						  void *client_data);
extern void		dga_draw_mbgetnotify (Dga_drawable dgadraw, DgaMbNotifyFunc *mb_notify_func,
						  void **client_data);
extern int		dga_draw_mbaccessmode (Dga_drawable dgadraw);
extern int		dga_draw_mbsitetypeconst (Dga_drawable dgadraw);
extern void		dga_draw_mbsetrendbufnotify (Dga_drawable dgadraw, 
							 DgaRendBufNotifyFunc rb_notify_func,
							 void *client_data);
extern void		dga_draw_mbgetrendbufnotify (Dga_drawable dgadraw, 
							 DgaRendBufNotifyFunc *rb_notify_func,
							 void **client_data);
extern int		dga_draw_ovlstatechg (Dga_drawable dgadraw);
extern int		dga_draw_ovlstate (Dga_drawable dgadraw);
extern void		dga_draw_ovlstatesetnotify (Dga_drawable dgadraw, 
						    DgaOvlStateNotifyFunc ovlstate_notify_func,
						    void *client_data);
extern void		dga_draw_ovlstategetnotify (Dga_drawable dgadraw, 
						    DgaOvlStateNotifyFunc *ovlstate_notify_func,
						    void **client_data);


/*
 *  Drawable grabber functions - Buffer Control Compatibility
 */

extern int		dga_draw_db_grab (Dga_drawable dgadraw, int nbuffers, 
			  int (*vrtfunc)(Dga_drawable), u_int *vrtcounterp);
extern int		dga_draw_db_ungrab (Dga_drawable dgadraw);
extern void		dga_draw_db_write (Dga_drawable dgadraw, int buffer,
			   int (*writefunc)(void*, Dga_drawable, int), 
			   void *data);
extern void		dga_draw_db_read (Dga_drawable dgadraw, int buffer,
			  int (*readfunc)(void*, Dga_drawable, int), 
			  void *data);
extern void		dga_draw_db_display (Dga_drawable dgadraw, int buffer,
			  int (*visfunc)(void*, Dga_drawable, int), 
			  void *data);
extern void		dga_draw_db_interval (Dga_drawable dgadraw, int interval);
extern void		dga_draw_db_interval_wait (Dga_drawable dgadraw);
extern int		dga_draw_db_interval_check (Dga_drawable dgadraw);
extern int		dga_draw_db_write_inquire (Dga_drawable dgadraw);
extern int		dga_draw_db_read_inquire (Dga_drawable dgadraw);
extern int		dga_draw_db_display_inquire (Dga_drawable dgadraw);
extern int		dga_draw_db_display_done (Dga_drawable dgadraw, int flag, 
			  int (*display_done_func)(Dga_drawable));
extern Dga_dbinfo 	*dga_draw_db_dbinfop (Dga_drawable dgadraw);
extern int		dga_draw_devinfochg(Dga_drawable dgadraw);

/*
 *  Misc. grabber functions
 */

extern	int		XDgaDrawGrabWids(Display*, Drawable, int);
extern	Dga_widinfo	*dga_draw_widinfop(Dga_drawable);
extern	int		XDgaDrawGrabFCS(Display*, Drawable, int);
extern	int		XDgaDrawGrabZbuf(Display*, Drawable, int);
extern	int		XDgaDrawGrabStereo(Display*, Drawable, int);

/*
 *  Window Compatibility Interface - Ancillary buffers functions
 *  New feature for 2.6
 */

extern Dga_buffer      dga_draw_grab_buffer(Dga_drawable, 
                                            Dga_buffer_type, int);
extern int             dga_draw_ungrab_buffer(Dga_drawable, Dga_buffer_type);
extern int             dga_draw_get_buffers(Dga_drawable, Dga_buffer **);
extern Dga_buffer_type dga_buffer_type(Dga_buffer);
extern int             dga_buffer_site(Dga_buffer);
extern int             dga_draw_bufferchg(Dga_drawable);
extern int             dga_buffer_sitechg(Dga_buffer, int *);
extern void*           dga_buffer_address(Dga_buffer);
extern int             dga_buffer_linebytes(Dga_buffer);
extern int             dga_buffer_bitsperpixel(Dga_buffer);

#ifdef	__cplusplus
}
#endif

#endif /* _DGA_H */
