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
 * dga_db.c - the client side code for DGA double buffering
 */


#include <stdio.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <X11/Xlib.h>

#include <sys/fbio.h>

#ifndef FBIOVRTOFFSET
#ifdef SVR4
#define FBIOVRTOFFSET	(FIOC | 38)
#else
#define FBIOVRTOFFSET   _IOR(F, 38, int)
#endif
#endif

#include <netdb.h>
#include <sys/stat.h>
#include <unistd.h>

#include "dga_incls.h"

#define	DGA_WIN_LOCK_NOMODIF(win)			\
{							\
    if ((((_Dga_window)(win))->w_lockcnt)++ == 0) {	\
	DGA_LOCK(win);					\
	}						\
}

#define DGA_WIN_UNLOCK_NOMODIF(win)		\
{						\
    if (--(((_Dga_window)(win))->w_lockcnt) == 0) \
	DGA_UNLOCK(win);			\
}
    
extern void *_dga_is_X_window(Dga_token token, Display **dpyp, Window *winp);

#ifdef _LP64
static int _dga_db_vrtfunc_internal(Dga_window);
#else  /* _LP64 */
#if defined(__STDC__)
static int _dga_db_vrtfunc_internal(Dga_window);
#else
static int _dga_db_vrtfunc_internal();
#endif
#endif /* _LP64 */

static u_int *dga_vrt_access();
static void dga_vrt_release();

int 
dga_db_access(wg_clientpi)
     Dga_window wg_clientpi ;
{
    _Dga_window wg_clientp = (struct dga_window *)wg_clientpi;
     WXINFO	*infop = wx_infop(wg_clientp) ;
     u_int	*cpage;
     u_int	*dga_vrt_access();

    if (wg_clientp->db_enabled)
	return 0;
    if (infop->wx_dbuf.number_buffers < 2)
	return 1;

    cpage = dga_vrt_access(wg_clientp->w_devfd);

    if (cpage)
    {
	wg_clientp->db_enabled = 1;
	wg_clientp->db_vrtcntrp = cpage;
	wg_clientp->db_lastvrtcntr = *cpage;
	wg_clientp->db_swapint = 1;
	wg_clientp->vrt_func = _dga_db_vrtfunc_internal ;
	if ((infop->wx_dbuf.display_buffer < 0) ||
	 (infop->wx_dbuf.display_buffer > (infop->wx_dbuf.number_buffers - 1)))
		infop->wx_dbuf.display_buffer = 0;
	if ((infop->wx_dbuf.read_buffer < 0) ||
	   (infop->wx_dbuf.read_buffer > (infop->wx_dbuf.number_buffers - 1)))
		infop->wx_dbuf.read_buffer = 1;
	if ((infop->wx_dbuf.write_buffer < 0) ||
	    (infop->wx_dbuf.write_buffer > (infop->wx_dbuf.number_buffers - 1)))
		infop->wx_dbuf.write_buffer = 1;
	return(0);
    }
    else
	return(1);
}

void
dga_db_release(wg_clientpi)
     Dga_window wg_clientpi ;
{
     void	dga_vrt_release();
    _Dga_window wg_clientp = (struct dga_window *)wg_clientpi;
    
     if (wg_clientp->db_vrtcntrp)
         dga_vrt_release(wg_clientp->db_vrtcntrp);
     wg_clientp->db_enabled = 0;
 
}


void
dga_db_write(wg_clientpi,buffer,writefunc,data)
     Dga_window wg_clientpi ;
     int buffer;
#ifdef _LP64
     int (*writefunc)(void*, Dga_window, int);
#else  /* _LP64 */
#if defined (__STDC__)
     int (*writefunc)(void*, Dga_window, int);
#else
    int (*writefunc)();
#endif
#endif /* _LP64 */
     void* data;
{
    _Dga_window wg_clientp = (struct dga_window *)wg_clientpi;
    
     DGA_WIN_LOCK_NOMODIF(wg_clientp);
     if (writefunc)
	(*writefunc) (data,wg_clientpi,buffer);
     wx_infop(wg_clientp)->wx_dbuf.write_buffer = buffer; 
     DGA_WIN_UNLOCK_NOMODIF(wg_clientp);
}

void
dga_db_read(wg_clientpi,buffer,readfunc,data)
     Dga_window wg_clientpi ;
     int buffer;
#ifdef _LP64
     int (*readfunc)(void*, Dga_window, int);
#else  /* _LP64 */
#if defined (__STDC__)
     int (*readfunc)(void*, Dga_window, int);
#else
    int (*readfunc)();
#endif
#endif /* _LP64 */
     void* data;
{
    _Dga_window wg_clientp = (struct dga_window *)wg_clientpi;
    
     DGA_WIN_LOCK_NOMODIF(wg_clientp);
     wx_infop(wg_clientp)->wx_dbuf.read_buffer = buffer; 
     if (readfunc)
	(*readfunc) (data,wg_clientpi,buffer);
     DGA_WIN_UNLOCK_NOMODIF(wg_clientp);
}


void
dga_db_display(wg_clientpi,buffer,visfunc,data)
     Dga_window wg_clientpi ;
     int buffer;
#ifdef _LP64
     int (*visfunc)(void*, Dga_window, int);
#else  /* _LP64 */
#if defined (__STDC__)
     int (*visfunc)(void*, Dga_window, int);
#else
    int (*visfunc)();
#endif
#endif /* _LP64 */
     void* data;
{
    _Dga_window wg_clientp = (struct dga_window *)wg_clientpi;
    
    if (!dga_db_interval_check(wg_clientpi))
       dga_db_interval_wait(wg_clientpi);
    if (visfunc) 
	(*visfunc)(data, wg_clientpi, buffer);
    if (wg_clientp->db_vrtcntrp)
        wg_clientp->db_lastvrtcntr = *wg_clientp->db_vrtcntrp;
    wx_infop(wg_clientp)->wx_dbuf.display_buffer = buffer;
}

void
dga_db_interval(wg_clientpi,interval)
     Dga_window wg_clientpi ;
     int interval;		/* number of milliseconds */
{
     int ref_rate;
     float rr;
     _Dga_window wg_clientp = (struct dga_window *)wg_clientpi;

     ref_rate  = wx_infop(wg_clientp)->w_refresh_period;
    if (ref_rate == 0) ref_rate = 66000;

    if (interval < 0)
	interval = 0;
    if (interval > ref_rate)
	interval = ref_rate;
    rr = ((float)ref_rate)* 0.001;
    wg_clientp->db_swapint = rr * ((float)interval* 0.001);

    if (wg_clientp->db_swapint == 0)
        wg_clientp->db_swapint = 1;
}


void
dga_db_interval_wait(wg_clientpi)
     Dga_window wg_clientpi ;
{
    _Dga_window wg_clientp = (struct dga_window *)wg_clientpi;
    u_int *counter = wg_clientp->db_vrtcntrp;

    /* Do a block if necessary and if vrt_func has been supplied */

    if (!wg_clientp->vrt_func || !wg_clientp->db_vrtcntrp) return;

    while (((u_int) (*counter - wg_clientp->db_lastvrtcntr))
          < wg_clientp->db_swapint)
    {
	if ((*(wg_clientp->vrt_func))(wg_clientpi) < 0) return ;;
    }
    return;
}

int
dga_db_interval_check(wg_clientpi)
     Dga_window wg_clientpi ;
{
    _Dga_window wg_clientp = (struct dga_window *)wg_clientpi;
     u_int *counter = wg_clientp->db_vrtcntrp;

     if ((wg_clientp->db_vrtcntrp) && 
	 ((u_int) (*counter - wg_clientp->db_lastvrtcntr))
          < wg_clientp->db_swapint)
        return(0);
     else
   	return(1);
}

int
dga_db_write_inquire(wg_clientpi)
     Dga_window wg_clientpi ;
{
    _Dga_window wg_clientp = (struct dga_window *)wg_clientpi;
     return(wx_infop(wg_clientp)->wx_dbuf.write_buffer);
}

int
dga_db_read_inquire(wg_clientpi)
     Dga_window wg_clientpi ;
{
    _Dga_window wg_clientp = (struct dga_window *)wg_clientpi;
    
     return(wx_infop(wg_clientp)->wx_dbuf.read_buffer);
}

int
dga_db_display_inquire(wg_clientpi)
     Dga_window wg_clientpi ;
{
    _Dga_window wg_clientp = (struct dga_window *)wg_clientpi;
     return(wx_infop(wg_clientp)->wx_dbuf.display_buffer);
}

/* INTERNAL INTERFACE */
int
dga_db_display_complete(wg_clientpi, flag)
    Dga_window wg_clientpi ;
    int flag;
{
    _Dga_window wg_clientp = (struct dga_window *)wg_clientpi;
    if (wg_clientp->db_vrtcntrp && 
	(wg_clientp->db_lastvrtcntr != *(wg_clientp->db_vrtcntrp)))
	return 1;
    if (flag == 0)
	return 0;
    if (ioctl(wg_clientp->w_devfd,FBIOVERTICAL,0) < 0)
	return 0;
    return 1;
}

/* INTERNAL INTERFACE */
static u_int
*dga_vrt_access(devfd)
   int devfd;
{
        u_int *cpage;
        u_int dev_offset;
	u_int pagesize;

        dev_offset = 0;
        if (ioctl(devfd, FBIOVRTOFFSET, &dev_offset) < 0)
           return (NULL);

#ifdef SVR4
	pagesize = sysconf(_SC_PAGESIZE);
#else
	pagesize = getpagesize();
#endif

	/*
	 * the driver provides the dev_offset into the mmaped page
	 * where the vertical retrace counter word is.
	 * We will mmap a shared memory page that is on a
	 * page boundary then modify the pointer to the
	 * vertical retrace counter to reflect the exact
	 * location where the counter word exists
	 */

	cpage = (u_int *) mmap((char *)0,
				pagesize,
				PROT_READ | PROT_WRITE,
				MAP_SHARED | _MAP_NEW,
				devfd,
				(off_t) (dev_offset & ~(pagesize - 1)));

	/* if the mmap failed then return NULL otherwide return
	 * the computed address of the vertical retract counter
	 * by adding the beginning of the mmaped page to the
	 * dev_offset into the page returned by the device driver
	 */

	if (cpage == (u_int *) -1)
		return NULL;

        return ((u_int *) ((int) cpage | (dev_offset & (pagesize - 1))));
}

static void
dga_vrt_release(counter)
u_int *counter;
{
	char *counter_page;
	int pagesize;

#ifdef SVR4
	pagesize = sysconf(_SC_PAGESIZE);
#else
	pagesize = getpagesize();
#endif

	/* Unmap the page for this client.
	 * remove the offset computation and munmap the
	 * vertical retrace counter page.  we remove the
	 * offset by simply setting the lower bits of 
	 * the address to 0
	 */

	counter_page = (char *) (((int) counter) & (~(pagesize - 1)));
        munmap(counter_page, pagesize) ;
	return;
}

/* New routines that will be exposed to the public */

int 
dga_db_display_done(wg_clientpi,flag, display_done_func)
Dga_window wg_clientpi;
int flag;
#ifdef _LP64
int (*display_done_func)(Dga_window);
{
    int (*vrt_func)(Dga_window);
#else  /* _LP64 */
#if defined (__STDC__)
int (*display_done_func)(Dga_window);
#else
int (*display_done_func)();
#endif
{
#if defined (__STDC__)
    int (*vrt_func)(Dga_window);
#else
    int (*vrt_func)();
#endif
#endif /* _LP64 */
    _Dga_window wg_clientp = (struct dga_window *)wg_clientpi;
    int ret_val;
    
    /* Return 1 = done, 0 = not done, -1 = error */
    ret_val = (*display_done_func)(wg_clientpi);

    /* If the user does not want to block or if the
     * display_done_func() returned a non-zero, we return
     * else we try till success after each vrt_retrace()
    */
    if ((!flag) || (ret_val != 0))
	return (ret_val);
    
    vrt_func = wg_clientp->vrt_func;
    if (!vrt_func) return 1;

    while((ret_val = (*display_done_func)(wg_clientpi)) == 0)
	if (vrt_func(wg_clientpi) < 0) return -1;
    return (ret_val);
}

/* Returns 0 on fail and non-zero on success */
int
dga_db_grab(clientpi, nbuffers, vrtfunc, vrtcounterp)
Dga_window clientpi;
int nbuffers;
#ifdef _LP64
int (*vrtfunc)(Dga_window);
#else  /* _LP64 */
#if defined (__STDC__)
int (*vrtfunc)(Dga_window);
#else
int (*vrtfunc)();
#endif
#endif /* _LP64 */
u_int *vrtcounterp;
{
    Display	*dpy;
    Window	 win;

    /*
     *  Check for an invalid Dga_window
     */
     _Dga_window clientp = (struct dga_window *)clientpi;
     WXINFO	*infop;
    
    if ((clientp == (_Dga_window) NULL)) {
#ifdef DEBUG
	(void) fprintf(stderr, "dga_db_grab: passed null pointer\n");
#endif
	return (0);
    }

    /*
     *  If the buffers has already been grabbed. Don't
     *  do anything.
     */
    if (clientp->db_enabled)
	return (1);

    /*
     *  Find out if this is an X window.  If so get the Display and window
     *  id.  
     */
     if (!_dga_is_X_window(clientp->w_token, &dpy, &win)) {
#ifdef DEBUG
	(void) fprintf(stderr, "dga_db_grab: Unsupported window type\n");
#endif
	return (0);
    }

    /*
     *  Request the server to allow DGA to the buffers associated
     *  with this Dga_window.
     */
    if (!XDgaGrabBuffers(dpy, win, nbuffers)) {
#ifdef DEBUG
	(void) fprintf(stderr, "dga_db_grab: XDgaGrabBuffers failed\n");
#endif
	return (0);
    }

    /* Now if they supplied vrtfunc, update the clientp
     */

    infop =wx_infop(clientp) ;
    clientp->vrt_func = vrtfunc;

    /* Now update the clientp pointer with other info */
    if (vrtcounterp) {
	clientp->db_enabled = 1;
	clientp->db_vrtcntrp = (u_int *)vrtcounterp;
	clientp->db_lastvrtcntr = *vrtcounterp;
	clientp->db_swapint = 1;
	if ((infop->wx_dbuf.display_buffer < 0) ||
	 (infop->wx_dbuf.display_buffer > (infop->wx_dbuf.number_buffers - 1)))
		infop->wx_dbuf.display_buffer = 0;
	if ((infop->wx_dbuf.read_buffer < 0) ||
	   (infop->wx_dbuf.read_buffer > (infop->wx_dbuf.number_buffers - 1)))
		infop->wx_dbuf.read_buffer = 1;
	if ((infop->wx_dbuf.write_buffer < 0) ||
	   (infop->wx_dbuf.write_buffer > (infop->wx_dbuf.number_buffers - 1)))
		infop->wx_dbuf.write_buffer = 1;
	return(1);
    } else {

	/* Even though they have not supplied vrtp we allow the db_grab
	 * to succeed but we null out vrtfunc and set vrtcntrp to point
	 * to itself!
	*/
	clientp->db_enabled = 1;
	clientp->vrt_func = NULL;
	clientp->db_vrtcntrp = NULL;
	return(1);
    }
    
}

/* Returns 0 on failure and non-zero on success */
int
dga_db_ungrab(clientpi)
Dga_window clientpi;
{
    _Dga_window clientp = (struct dga_window *)clientpi;    
    Display    *dpy;
    Window	win;
    int		status = -1;

    /*
     *  Check for an invalid Dga_window
     */
    if ((clientp == (Dga_window) NULL)) {
#ifdef DEBUG
        (void) fprintf(stderr, "dga_db_ungrab: passed null pointer\n");
#endif
        return (0);
    }
    
    /* If it wasm't grabbed in the first place. don't do anything */
    if (!clientp->db_enabled)
	return 1;


    /*
     *  Find out if this is an X window.  If so get the Display and window
     *  id.  
     */
     if (!_dga_is_X_window(clientp->w_token, &dpy, &win)) {
#ifdef DEBUG
        (void) fprintf(stderr, "dga_db_ungrab: Unsupported window type\n");
#endif
        return (0);
    }
    /* Mark the window as single buffered */
    clientp->db_enabled = 0;

    /* Tell server t ungrab */
    return (XDgaUnGrabBuffers(dpy, win));

    
}
/* This is just for internal use */
static int
_dga_db_vrtfunc_internal(wg_clientp)
Dga_window wg_clientp;
{
   ( ioctl(((_Dga_window)wg_clientp)->w_devfd,FBIOVERTICAL,0));
   return(1);
}
