/* Copyright (c) 1996, 1999, Oracle and/or its affiliates. All rights reserved.
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
 * dga_ab.c - the client side code for Ancillary Buffers (ABMG ) 
 */

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/fcntl.h>
#include <X11/X.h>
#include "dga_incls.h"

extern int XDgaGrabABuffers(Display *dpy, Window win, int type, int buffer_site);
extern int XDgaUnGrabABuffers(Display *dpy, Window win, int type);
extern void *_dga_is_X_window(Dga_token token, Display **dpyp, Window *winp);

#ifdef DEBUG
#define assert(expr) \
if(!(expr)) \
{fprintf(stderr, "Assertion fails in file %s, line %d: expr\n",__FILE__,__LINE__); \
abort();}
#else
#define assert(expr)
#endif /* DEBUG */

#define UNMAP_BUFFER(addr, allocsize) \
    if ( addr ) { \
        munmap((char *)addr, allocsize); \
        addr = NULL; \
    }

#define GET_SW_HW_BUFFER(dgawin_buf, fname, bufsize)  \
    bufferp = (dga_buffer)get_specified_buffer((char *)fname, bufsize); \
    (dgawin_buf)->bufferp  = bufferp; \
    (dgawin_buf)->pDraw    = dgadraw; \
    (dgawin_buf)->buf_size = bufsize; \
    ret_buf = dgawin_buf;

#define STORE_BUFFERS(buf_addr, filename, fn_addr0, allocsize) \
    bufferp = (buf_addr)->bufferp; \
    if ( bufferp) { \
        if (resize_flag) \
            UNMAP_BUFFER(bufferp, (buf_addr)->buf_size) \
        if ( filename && fn_addr0)  { \
            if ( bufferp ) { \
                buffers[count++] = (Dga_buffer *)buf_addr; \
                bufferp->pDraw = dgadraw; \
            } \
            else {\
                (buf_addr)->bufferp = bufferp = (void *) \
                    get_specified_buffer((char *)filename, allocsize); \
                 (buf_addr)->pDraw = dgadraw; \
                 if (bufferp) { \
                     buffers[count++] = (Dga_buffer *)buf_addr; \
                     bufferp->pDraw = dgadraw; \
                     (buf_addr)->buf_size = allocsize; \
                 } \
                 else { \
                     (buf_addr)->buf_size = 0; \
                 } \
            }\
        }\
    }

static dga_buffer
get_specified_buffer(char *filename, int allocsize)
{
    int         filefd = -1;
    dga_buffer  return_buf = NULL;

    if ( filename && filename[0] ) {
        if ((filefd = open(filename,O_RDWR,0666)) != -1 ) {
            return_buf = (dga_buffer)mmap(0, allocsize,
                PROT_READ|PROT_WRITE, MAP_SHARED, filefd, (off_t)0);
            close (filefd);  /* May need to keep trap of fds... */

            if ( return_buf == (dga_buffer) -1)
                return ( (dga_buffer)NULL ); /* mmap failed. */

            /* Set the data filed properly */
	    assert(sizeof(dga_buffer_rec) & 0x7 == 0);
            return_buf->data = (char *)(return_buf + 1);
        }
    }
    return return_buf;

}

static void
remap_buffers(Dga_drawable dgadraw)
{
    int         filefd = -1;
    char        *filename;
    int         count = 0;
    dga_buffer  bufferp = NULL;
    static      void     *buffers[DGA_NUM_BUFFER_TYPES];
    _Dga_window dgawin = (_Dga_window)dgadraw;
    WXINFO      *infop = wx_infop(dgawin);
    int         resize_flag = True;
 
    if ( dgawin->buf_resize_flag >= infop->wx_abuf.s_modified )
        return;

    STORE_BUFFERS((dga_internal_buffer)dgawin->back, infop->wx_abuf.back_fn, infop->wx_abuf.back_fn[0], infop->wx_abuf.back_size);

    STORE_BUFFERS((dga_internal_buffer)dgawin->depth, infop->wx_abuf.depth_fn, infop->wx_abuf.depth_fn[0], infop->wx_abuf.depth_size);

    STORE_BUFFERS((dga_internal_buffer)dgawin->stencil, infop->wx_abuf.stencil_fn, infop->wx_abuf.stencil_fn[0], infop->wx_abuf.stencil_size);

    STORE_BUFFERS((dga_internal_buffer)dgawin->accum, infop->wx_abuf.accum_fn, infop->wx_abuf.accum_fn[0], infop->wx_abuf.accum_size);

    STORE_BUFFERS((dga_internal_buffer)dgawin->alpha, infop->wx_abuf.alpha_fn, infop->wx_abuf.alpha_fn[0], infop->wx_abuf.alpha_size);

    dgawin->buf_resize_flag = infop->wx_abuf.s_modified;

    return;
}

/*
 * Name    : dga_draw_grab_buffer
 * Synopsis: This function requests the window system to provide 
 * ancillary buffer service for the grabbed drawable name in the
 * dgadraw argument.  The call requests  the type of the buffer
 * specified to be grabbed to the client.  If buffer_site is 
 * DGA_SITE_SYSTEM, server allocates the buffer in the shared 
 * memory.  If it is DGA_SITE_DEVICE, the server tries to grab
 * hardware buffers.  If the device does not support the given 
 * buffer type in hardware, the request fails.
 * The drawable must have been grabbed previously via XDgaGrabDrawable.
 * 
 * Implementation:  If buffer_stie is DGA_SITE_SYSTEM, this function
 * increments the grab_cnt if the buffer is already grabbed by other clients.
 * If this client has grabbed the specified buffer already, this function
 * returns the grabbed buffer pointer.
 * Otherwise, it sends a request to the server to grab a buffer.
 * If the request is successful, this function returns the buffer 
 * address.
 * A special case where if the grab_cnt is "0", this function still sends
 * a request to the server to grab the buffer  because there is a chance
 * that the visual capabilities of the window might have been changed. 
 */

Dga_buffer 
dga_draw_grab_buffer(Dga_drawable dgadraw, Dga_buffer_type type, int buffer_site)
{
    _Dga_window dgawin = (struct dga_window *)dgadraw;
    Dga_window  clientpi = (Dga_window)dgawin;
    _Dga_window clientp = (struct dga_window *)clientpi;
    WXINFO      *infop;
    Display     *dpy;
    Window      win;
    int         depth  = 0;
    dga_buffer  bufferp = NULL;
    dga_internal_buffer ret_buf = NULL;
    dga_internal_buffer c_bufferp = NULL;

    /* Ancillary Buffers are not supported for drawable_type 
     * DGA_DRAW_PIXMAP
     */
    if ( ((_Dga_drawable)dgadraw)->drawable_type != DGA_DRAW_WINDOW ) 
        return (0);

    if (!DGA_LOCKSUBJ_WINDOW(dgawin, dgawin->eLockSubj)) 
        return (0);

    if ((clientp == (_Dga_window) NULL)) {
#ifdef DEBUG
        (void) fprintf(stderr, "dga_draw_grab_buffer: passed null pointer\n");
#endif
        return (0);
    }

    /*
     *  Find out if this is an X window.  If so get the Display and window
     *  id.
     */
    if (!_dga_is_X_window(clientp->w_token, &dpy, &win)) {
#ifdef DEBUG
        (void) fprintf(stderr, "dga_draw_grab_buffer: Unsupported window type\n");
#endif
        return (0);
    }

    infop = wx_infop(dgawin) ;

    if ( dgawin->buf_resize_flag < infop->wx_abuf.s_modified )
        remap_buffers(dgadraw);
 
    switch ( type ) {
    case DGA_BACK_BUFFER:
        c_bufferp = (dga_internal_buffer)dgawin->back;
        if ( c_bufferp->bufferp )
            return dgawin->back;
        GET_SW_HW_BUFFER(c_bufferp, infop->wx_abuf.back_fn, infop->wx_abuf.back_size);
        break;
    case DGA_DEPTH_BUFFER:
        c_bufferp = (dga_internal_buffer)dgawin->depth;
        if ( c_bufferp->bufferp )
            return dgawin->depth;
        GET_SW_HW_BUFFER(c_bufferp, infop->wx_abuf.depth_fn, infop->wx_abuf.depth_size);
        break;
    case DGA_STENCIL_BUFFER:
        c_bufferp = (dga_internal_buffer)dgawin->stencil;
        if ( c_bufferp->bufferp )
            return dgawin->stencil;
        GET_SW_HW_BUFFER(c_bufferp, infop->wx_abuf.stencil_fn, infop->wx_abuf.stencil_size);
        break;
    case DGA_ACCUM_BUFFER:
        c_bufferp = (dga_internal_buffer)dgawin->accum;
        if ( c_bufferp->bufferp )
            return dgawin->accum;
        GET_SW_HW_BUFFER(c_bufferp, infop->wx_abuf.accum_fn, infop->wx_abuf.accum_size);
        break;
    case DGA_ALPHA_BUFFER:
        c_bufferp = (dga_internal_buffer)dgawin->alpha;
        if ( c_bufferp->bufferp )
            return dgawin->alpha;
        GET_SW_HW_BUFFER(c_bufferp, infop->wx_abuf.alpha_fn, infop->wx_abuf.alpha_size);
        break;
    default:
        return (0);
    }

    /* If grab_cnt is "0", then the reinitialization should go thru'
     * server.  We can not just increment the grab_cnt.
     * There is a chance that the buffers capabilities might have
     * been changed in which case the server gets the bitsPerPixel
     * from SunExtVis info struct and reallocates the buffer.
     * If buffer_site is not DGA_SITE_SYSTEM, then it might be
     * a Hardware Buffers.
     */
    if ( bufferp && (bufferp->buffer_site == DGA_SITE_SYSTEM) &&  
            bufferp->grab_cnt > 0 ) {
        bufferp->grab_cnt++;
        return (Dga_buffer ) ret_buf;
    }

    /*
     *  Request the server to allow DGA to the buffers associated
     *  with this Dga_window.
     */
    if (!XDgaGrabABuffers(dpy, win, type, buffer_site)) {
#ifdef DEBUG
        (void)fprintf(stderr, "dga_draw_grab_buffer: XDgaGrabABuffers failed\n");
#endif
        return (0);
    }

    /* infop will contain the proper pointer to the selected buffer since
     * it is in the dga shared page.
     */
    infop = wx_infop(dgawin) ;
 
    /* get_specified_buffer:  This function checks on the filenames
     * where if it is software buffer this member should have a 
     * valid file name.
     * If it is NULL, then it may be a hardware buffer and just
     * return from this point where the hardware buffer would have
     * been allocated already.
     */
    switch ( type ) {
    case DGA_BACK_BUFFER:
        c_bufferp = (dga_internal_buffer)dgawin->back;
        GET_SW_HW_BUFFER(c_bufferp, infop->wx_abuf.back_fn, infop->wx_abuf.back_size);
        break;
        
    case DGA_DEPTH_BUFFER:
        c_bufferp = (dga_internal_buffer)dgawin->depth;
        GET_SW_HW_BUFFER(c_bufferp, infop->wx_abuf.depth_fn, infop->wx_abuf.depth_size);
        break;

    case DGA_STENCIL_BUFFER:
        c_bufferp = (dga_internal_buffer)dgawin->stencil;
        GET_SW_HW_BUFFER(c_bufferp, infop->wx_abuf.stencil_fn, infop->wx_abuf.stencil_size);
        break;

    case DGA_ACCUM_BUFFER:
        c_bufferp = (dga_internal_buffer)dgawin->accum;
        GET_SW_HW_BUFFER(c_bufferp, infop->wx_abuf.accum_fn, infop->wx_abuf.accum_size);
        break;

    case DGA_ALPHA_BUFFER:
        c_bufferp = (dga_internal_buffer)dgawin->alpha;
        GET_SW_HW_BUFFER(c_bufferp, infop->wx_abuf.alpha_fn, infop->wx_abuf.alpha_size);
        break; 

    }

    if ( bufferp ) {
        bufferp->pDraw = ret_buf->pDraw = dgadraw;
        return (Dga_buffer) ret_buf;
    } else {
        if (buffer_site == DGA_SITE_DEVICE)
            return (Dga_buffer) c_bufferp;
    }

    return NULL;
}

/*
 * Name    : dga_draw_ungrab_buffer
 * Synopsis: This function ungrabs the buffer for the specified drawable
 * which has been grabbed previously. Note that ungrabbing a buffer does
 * not necessarily cause it to be freed.  If any of these steps fail,
 * zero is returned.  True is returned upon success.
 *
 * Implementation: If the buffer is grabbed already, this function
 * decrements the grab_cnt.  If grab_cnt  is negative, it will be 
 * reset to "0".  
 * If this client hasn't grabbed the buffer already, this function returns 0.
 * This function will send a request to the server to ungrab the
 * buffer only if buffer grabbed is in DGA_SITE_DEVICE ( Hardware ).
 */
int
dga_draw_ungrab_buffer(Dga_drawable dgadraw, Dga_buffer_type type)
{
    _Dga_window dgawin = (_Dga_window)dgadraw;
    WXINFO     *infop;
    Display     *dpy;
    Window       win;
    dga_buffer  bufferp = NULL;
    dga_internal_buffer ret_buf = NULL;
    dga_internal_buffer c_bufferp = NULL;

    /* Ancillary Buffers are not supported for drawable_type 
     * DGA_DRAW_PIXMAP
     */
    if ( ((_Dga_drawable)dgadraw)->drawable_type != DGA_DRAW_WINDOW ) 
        return (0);

    if (!DGA_LOCKSUBJ_WINDOW(dgawin, dgawin->eLockSubj)) 
        return (0);

    if ((dgawin == (_Dga_window) NULL)) {
#ifdef DEBUG
        (void) fprintf(stderr, "dga_draw_ungrab_buffer: passed null pointer\n");
#endif
        return (0);
    }

    /*
     *  Find out if this is an X window.  If so get the Display and window
     *  id.
     */
    if (!_dga_is_X_window(dgawin->w_token, &dpy, &win)) {
#ifdef DEBUG
        (void) fprintf(stderr, "dga_draw_ungrab_buffer: Unsupported window type\n");
#endif
        return (0);
    }

    infop = wx_infop(dgawin) ;
 
    switch ( type ) {
    case DGA_BACK_BUFFER:
        c_bufferp = (dga_internal_buffer)dgawin->back;
        if ( c_bufferp->bufferp )
            return 0;   
        GET_SW_HW_BUFFER(c_bufferp, infop->wx_abuf.back_fn, infop->wx_abuf.back_size);
        break;
    case DGA_DEPTH_BUFFER:
        c_bufferp = (dga_internal_buffer)dgawin->depth;
        if ( c_bufferp->bufferp )
            return 0;   
        GET_SW_HW_BUFFER(c_bufferp, infop->wx_abuf.depth_fn, infop->wx_abuf.depth_size);
        break;
    case DGA_STENCIL_BUFFER:
        c_bufferp = (dga_internal_buffer)dgawin->stencil;
        if ( c_bufferp->bufferp )
            return 0;   
        GET_SW_HW_BUFFER(c_bufferp, infop->wx_abuf.stencil_fn, infop->wx_abuf.stencil_size);
        break;
    case DGA_ACCUM_BUFFER:
        c_bufferp = (dga_internal_buffer)dgawin->accum;
        if ( c_bufferp->bufferp )
            return 0;   
        GET_SW_HW_BUFFER(c_bufferp, infop->wx_abuf.accum_fn, infop->wx_abuf.accum_size);
        break;
    case DGA_ALPHA_BUFFER:
        c_bufferp = (dga_internal_buffer)dgawin->alpha;
        if ( c_bufferp->bufferp )
            return 0;   
        GET_SW_HW_BUFFER(c_bufferp, infop->wx_abuf.alpha_fn, infop->wx_abuf.alpha_size);
        break;
    default:
        return (0);
    } /* end of switch ( type ).. */

/* Currently Just decrement the grab_cnt and if there is no grab
 * don't free it.  Next time when it is getting grabbed, we will
 * increment the count
 * If the when the grab_cnt is "0" and the dga_drawable is getting
 * resized then the buffers are thrown away.
 */

    if ( !bufferp )
        return (0);
        
    if ( bufferp->buffer_site == DGA_SITE_SYSTEM ) {
        bufferp->grab_cnt--;

        if ( bufferp->grab_cnt < 0 ) 
            bufferp->grab_cnt = 0;

        switch ( type ) {
        case DGA_BACK_BUFFER:
            ((dga_internal_buffer)dgawin->back)->bufferp = NULL;
            break;
        case DGA_DEPTH_BUFFER:
            ((dga_internal_buffer)dgawin->depth)->bufferp = NULL;
            break;
        case DGA_STENCIL_BUFFER:
            ((dga_internal_buffer)dgawin->stencil)->bufferp = NULL;
            break;
        case DGA_ACCUM_BUFFER:
            ((dga_internal_buffer)dgawin->accum)->bufferp = NULL;
            break;
        case DGA_ALPHA_BUFFER:
            ((dga_internal_buffer)dgawin->alpha)->bufferp = NULL;
            break;
        default:
            return (0);
        } /* end of switch */
    }
    else {
        /* Buffer site is DGA_SITE_DEVICE */
        if (!XDgaUnGrabABuffers(dpy, win, type)) {
#ifdef DEBUG
        (void) fprintf(stderr, "dga_draw_ungrab_buffer: XDgaUnGrabABuffers failed\n");
#endif
        return (0);

        }
    } /* end of ( ret_buf->buffer_site == DGA_SITE_SYSTEM ).. */

    return 1;
}

/*
 * Name    : dga_draw_get_buffers
 * Synopsis: This function returns the number of ancillary buffers
 * associated with the specified dgadraw and an arry of buffer
 * pointers.  Note that only buffers which have been grabbed by
 * the client are returned.  Buffers which might exist (because of 
 * grabs by other clients or the server) are not returned.
 */
int
dga_draw_get_buffers(Dga_drawable dgadraw, Dga_buffer **pBufs )
{
    char        *filename;
    int         count = 0;
    dga_buffer  bufferp = NULL;
    static      void     *buffers[DGA_NUM_BUFFER_TYPES];
    _Dga_window dgawin = (_Dga_window)dgadraw;
    WXINFO      *infop = wx_infop(dgawin);
    int         resize_flag = False;
    
    if ( dgawin->buf_resize_flag < infop->wx_abuf.s_modified )
        resize_flag = True;

    STORE_BUFFERS((dga_internal_buffer)dgawin->back, infop->wx_abuf.back_fn, infop->wx_abuf.back_fn[0], infop->wx_abuf.back_size);

    STORE_BUFFERS((dga_internal_buffer)dgawin->depth, infop->wx_abuf.depth_fn, infop->wx_abuf.depth_fn[0], infop->wx_abuf.depth_size);

    STORE_BUFFERS((dga_internal_buffer)dgawin->stencil, infop->wx_abuf.stencil_fn, infop->wx_abuf.stencil_fn[0], infop->wx_abuf.stencil_size);

    STORE_BUFFERS((dga_internal_buffer)dgawin->accum, infop->wx_abuf.accum_fn, infop->wx_abuf.accum_fn[0], infop->wx_abuf.accum_size);

    STORE_BUFFERS((dga_internal_buffer)dgawin->alpha, infop->wx_abuf.alpha_fn, infop->wx_abuf.alpha_fn[0], infop->wx_abuf.alpha_size);

    if ( resize_flag )
        dgawin->buf_resize_flag = infop->wx_abuf.s_modified;
 
    *pBufs = buffers;

    return count;
}


/*
 * Name    : dga_buffer_type
 * Synopsis: This function returns the type of the buffer specified.
 */
Dga_buffer_type
dga_buffer_type(Dga_buffer bufferp)
{
    _Dga_window dgawin;
    WXINFO      *infop;
    dga_buffer local_buf;
 
    if ( !bufferp || !(local_buf = ((dga_internal_buffer)bufferp)->bufferp))
        return -1;
 
    dgawin =  (_Dga_window)((dga_internal_buffer)bufferp)->pDraw;
    infop  = wx_infop(dgawin);
 
    if ( dgawin->buf_resize_flag < infop->wx_abuf.s_modified ) {
        remap_buffers((Dga_drawable)((dga_internal_buffer)bufferp)->pDraw);
        local_buf = ((dga_internal_buffer)bufferp)->bufferp;
    }
 
    return local_buf->buffer_type;
}


#if 0
/* We had this function for completeness. */
/*
 * Name    : dga_buffer_get_drawable
 * Synopsis: This function returns the Dga_drawable associated with the
 * buffer specified.
 */
Dga_drawable
dga_buffer_get_drawable(Dga_buffer bufferp )
{
    if ( !bufferp )
        return NULL;

    return ((dga_buffer)bufferp)->pDraw;
}
#endif


/*
 * Name    : dga_buffer_site (Lock Only)
 * Synopsis: This function returns the site of the buffer specified.
 * The values are the same as those returned by dga_draw_site().
 * DGA_SITE_SYSTEM, DGA_SITE_DEVICE and DGA_SITE_NULL.
 */
int
dga_buffer_site(Dga_buffer bufferp)
{
    _Dga_window dgawin;
    WXINFO      *infop;
    dga_buffer local_buf;
 
    if ( !bufferp || !(local_buf = ((dga_internal_buffer)bufferp)->bufferp))
        return DGA_SITE_NULL;  
 
    dgawin =  (_Dga_window)((dga_internal_buffer)bufferp)->pDraw;
    infop  = wx_infop(dgawin);
 
    if ( dgawin->buf_resize_flag < infop->wx_abuf.s_modified ) {
        remap_buffers((Dga_drawable)((dga_internal_buffer)bufferp)->pDraw);
        local_buf = ((dga_internal_buffer)bufferp)->bufferp;
    }

    return local_buf->buffer_site;
}


/*
 * Name    : dga_draw_bufferchg
 * Synopsis: This function returns True if any of the buffers 
 * associated with the dgadraw have undergone a state change
 * since the last lock.  When dga_draw_bufferchg returns True,
 * the client should call dga_buffer_sitechg for each of the
 * Drawable's buffers.
 */
int
dga_draw_bufferchg(Dga_drawable dgadraw)
{
    _Dga_window dgawin = (_Dga_window)dgadraw;
    WXINFO      *infop = wx_infop(dgawin);

    if (infop && (infop->wx_abuf.s_modified))
        return True;
 
    return False;
}

/*
 * Name    : dga_buffer_sitechg
 * Synopsis: This function returns True if the buffer has sitechg 
 * flag set.  Note that this function always returns False for 
 * device buffers.  Only memory buffers ever have a site chagne.
 * dga_buffer_sitechg() also returns the reason for site change.
 * Currenly the only possible values for reason are DGA_SITECHG_INITIAL,
 * which is reported the first time a Drawable is locaked after a buffer
 * has been created and DGA_SITECHG_CACHE which indicates that the
 * buffer has been resized since the time that the Dga_drawable was last 
 * locked.
 */
int
dga_buffer_sitechg(Dga_buffer bufferp, int *reason)
{
    _Dga_window dgawin; 
    WXINFO      *infop; 
    dga_buffer local_buf;
 
    if ( !bufferp || !(local_buf = ((dga_internal_buffer)bufferp)->bufferp))
        return False; /* Returning False may mislead the developer */
 
    dgawin =  (_Dga_window)((dga_internal_buffer)bufferp)->pDraw;
    infop  = wx_infop(dgawin);
 
    if ( dgawin->buf_resize_flag < infop->wx_abuf.s_modified ) {
        remap_buffers((Dga_drawable)((dga_internal_buffer)bufferp)->pDraw);
        local_buf = ((dga_internal_buffer)bufferp)->bufferp;
    }
 
    if  (local_buf->buffer_site != DGA_SITE_SYSTEM)
        return False;

    if (local_buf->sitechg) {
        *reason = local_buf->sitechg;
        local_buf->sitechg = DGA_SITECHG_UNKNOWN;
        return True;
    } else
        return False;
}

/*
 * Name    : dga_buffer_address (Lock Only)
 * Synopsis: This function returns the data pointer from the shared
 * buffer page of the buffer specified.  An address will be returned
 * only for buffers which are located in system memory.  
 * If dga_buffer_address is called on a buffer located with 
 * DGA_SITE_DEVICE, NULL will be returned.  The value returned 
 * remains valid across locks until a sitechg is reported as 
 * described above.
 */
void *
dga_buffer_address(Dga_buffer bufferp)
{
    _Dga_window dgawin; 
    WXINFO      *infop; 
    dga_buffer local_buf;
 
    if ( !bufferp || !(local_buf = ((dga_internal_buffer)bufferp)->bufferp))
        return NULL;
 
    dgawin =  (_Dga_window)((dga_internal_buffer)bufferp)->pDraw;
    infop  = wx_infop(dgawin);

    if ( dgawin->buf_resize_flag < infop->wx_abuf.s_modified ) {
        remap_buffers((Dga_drawable)((dga_internal_buffer)bufferp)->pDraw);
        local_buf = ((dga_internal_buffer)bufferp)->bufferp;
    }
 
    if  (local_buf->buffer_site == DGA_SITE_SYSTEM) {
        local_buf->data = (char *)(local_buf + 1);
        return local_buf->data; 
    }
    else
        return NULL;
}

/*
 * Name    : dga_buffer_linebytes
 * Synopsis: This function returns the number of bytes per scanline
 * of the buffer specified.  Only buffers which are located in
 * system memory are addressable.  If dga_buffer_linebytes is called
 * for a buffer located on the device, "0" is returned.
 */
int
dga_buffer_linebytes(Dga_buffer bufferp)
{
    _Dga_window dgawin; 
    WXINFO      *infop; 
    dga_buffer local_buf;

    if ( !bufferp || !(local_buf = ((dga_internal_buffer)bufferp)->bufferp))
        return 0;
 
    dgawin =  (_Dga_window)((dga_internal_buffer)bufferp)->pDraw;
    infop  = wx_infop(dgawin);
 
    if ( dgawin->buf_resize_flag < infop->wx_abuf.s_modified ) {
        remap_buffers((Dga_drawable)((dga_internal_buffer)bufferp)->pDraw);
        local_buf = ((dga_internal_buffer)bufferp)->bufferp;
    }

    if  (local_buf->buffer_site == DGA_SITE_SYSTEM)
        return local_buf->linebytes; 
    else
        return 0;
}

/*
 * Name    : dga_buffer_bitsperpixel
 * Synopsis: This function returns bitsperpixel of the buffer 
 * specified if the buffer is located in system memory.  If the
 * buffer is located on the device, zero is returned.  Note that
 * the value might be different than the number of significant bits.
 * For example, an unpacked 4 bit stencil buffer would return
 * 8 bits per pixel, and a 24 bit Z buffer would return 
 * 32 bits per pixel.
 */
int
dga_buffer_bitsperpixel(Dga_buffer bufferp)
{
    _Dga_window dgawin; 
    WXINFO      *infop; 
    dga_buffer local_buf;

    if ( !bufferp || !(local_buf = ((dga_internal_buffer)bufferp)->bufferp))
        return 0;

    dgawin =  (_Dga_window)((dga_internal_buffer)bufferp)->pDraw;
    infop  = wx_infop(dgawin);

    if ( dgawin->buf_resize_flag < infop->wx_abuf.s_modified ) {
        remap_buffers((Dga_drawable)((dga_internal_buffer)bufferp)->pDraw);
        local_buf = ((dga_internal_buffer)bufferp)->bufferp;
    }

    if  (local_buf->buffer_site == DGA_SITE_SYSTEM)
        return local_buf->bitsPerPixel; 
    else
        return 0;
}

void
dga_draw_buffer_swap(Dga_drawable dgadraw, int (*visfunc)(Dga_window))
{
     _Dga_window dgawin = (_Dga_window)dgadraw;
     WXINFO      *infop = wx_infop(dgawin);

    if (visfunc)
        (*visfunc)(dgawin);

    if ( infop && infop->wx_abuf.back_fn && infop->wx_abuf.back_fn[0] 
                && infop->wx_abuf.back ) {
        infop->wx_abuf.buffer_swap++;
        dgawin->c_buffer_swap = infop->wx_abuf.buffer_swap;
    }
 
    return; 
}

int
dga_draw_swap_check(Dga_drawable dgadraw)
{
    _Dga_window dgawin = (_Dga_window)dgadraw;
    WXINFO      *infop = wx_infop(dgawin);
 
    if ( infop && infop->wx_abuf.back_fn && infop->wx_abuf.back_fn[0]  
           && infop->wx_abuf.back 
           && ( dgawin->c_buffer_swap != infop->wx_abuf.buffer_swap)) {
        dgawin->c_buffer_swap = infop->wx_abuf.buffer_swap;
        return 1;
    }

    return 0; 
}
