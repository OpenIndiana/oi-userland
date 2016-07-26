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
** draw_inquiry.c - state inquiry routines for drawable veneer.
*/

#ifdef SERVER_DGA
#include <X11/Xlib.h>
#endif /* SERVER_DGA */
#include "dga_incls.h"

extern int dgai_mbsmemb_devinfochg (_Dga_window dgawin);
extern int dgai_pix_devinfochg(_Dga_pixmap dgapix);

Display *
dga_draw_display (Dga_drawable dgadraw)
{
    switch ( ((_Dga_drawable)dgadraw)->drawable_type) {
    case DGA_DRAW_WINDOW:
	return (dgai_mbsmemb_display((_Dga_window)dgadraw));
    case DGA_DRAW_PIXMAP:
	return (dgai_pix_display((_Dga_pixmap)dgadraw));
    }
    return (NULL);
}

Drawable
dga_draw_id (Dga_drawable dgadraw)
{
    switch ( ((_Dga_drawable)dgadraw)->drawable_type) {
    case DGA_DRAW_WINDOW:
	return ((Drawable)((_Dga_window)dgadraw)->w_id);
    case DGA_DRAW_PIXMAP:
	return ((Drawable)((_Dga_pixmap)dgadraw)->p_id);
    }
    return (None);
}

int
dga_draw_type (Dga_drawable dgadraw)
{
    switch ( ((_Dga_drawable)dgadraw)->drawable_type) {
    case DGA_DRAW_WINDOW:
	return ((((_Dga_window)dgadraw)->isOverlay)
		? (DGA_DRAW_OVERLAY)
		: (DGA_DRAW_WINDOW));
    case DGA_DRAW_PIXMAP:
	return (DGA_DRAW_PIXMAP);
    }
    return (-1);
}

char *
dga_draw_devname (Dga_drawable dgadraw)
{
    switch ( ((_Dga_drawable)dgadraw)->drawable_type) {
    case DGA_DRAW_WINDOW:
	return (dgai_mbsmemb_devname((_Dga_window)dgadraw));
    case DGA_DRAW_PIXMAP:
	return (dgai_pix_devname((_Dga_pixmap)dgadraw));
    }
    return (NULL);
}

int
dga_draw_devfd (Dga_drawable dgadraw)
{
    switch ( ((_Dga_drawable)dgadraw)->drawable_type) {
    case DGA_DRAW_WINDOW:
	return (dgai_mbsmemb_devfd((_Dga_window)dgadraw));
    case DGA_DRAW_PIXMAP:
	return (dgai_pix_devfd((_Dga_pixmap)dgadraw));
    }
    return (-1);
}

int
dga_draw_depth (Dga_drawable dgadraw)
{
    switch ( ((_Dga_drawable)dgadraw)->drawable_type) {
    case DGA_DRAW_WINDOW:
	return (dgai_mbsmemb_depth((_Dga_window)dgadraw));
    case DGA_DRAW_PIXMAP:
	return (dgai_pix_depth((_Dga_pixmap)dgadraw));
    }
    return (-1);
}

void
dga_draw_set_client_infop (Dga_drawable dgadraw, void *client_info_ptr)
{
#ifdef MT
    mutex_lock(&dgaGlobalMutex);
#endif
    switch ( ((_Dga_drawable)dgadraw)->drawable_type) {
    case DGA_DRAW_WINDOW:
	dgai_mbsmemb_set_client_infop((_Dga_window)dgadraw, client_info_ptr);
	break;
    case DGA_DRAW_PIXMAP:
	dgai_pix_set_client_infop((_Dga_pixmap)dgadraw, client_info_ptr);
	break;
    }
#ifdef MT
    mutex_unlock(&dgaGlobalMutex);
#endif
}

void *
dga_draw_get_client_infop (Dga_drawable dgadraw)
{
    void *rval = NULL;
#ifdef MT
    mutex_lock(&dgaGlobalMutex);
#endif
    switch ( ((_Dga_drawable)dgadraw)->drawable_type) {
    case DGA_DRAW_WINDOW:
	rval = dgai_mbsmemb_get_client_infop((_Dga_window)dgadraw);
	break;
    case DGA_DRAW_PIXMAP:
	rval = dgai_pix_get_client_infop((_Dga_pixmap)dgadraw);
	break;
    }
#ifdef MT
    mutex_unlock(&dgaGlobalMutex);
#endif
    return (rval);
}

int
dga_draw_devinfochg (Dga_drawable dgadraw)
{
    int rval = -1;

#ifdef MT
    mutex_lock(&dgaGlobalMutex);
#endif
    switch ( ((_Dga_drawable)dgadraw)->drawable_type) {
    case DGA_DRAW_WINDOW:
	rval = dgai_mbsmemb_devinfochg((_Dga_window)dgadraw);
	break;
    case DGA_DRAW_PIXMAP:
	rval = dgai_pix_devinfochg((_Dga_pixmap)dgadraw);
	break;
    }
#ifdef MT
    mutex_unlock(&dgaGlobalMutex);
#endif
    return (rval);
}

void *
dga_draw_devinfo (Dga_drawable dgadraw)
{
    void *rval = NULL;

#ifdef MT
    mutex_lock(&dgaGlobalMutex);
#endif
    switch ( ((_Dga_drawable)dgadraw)->drawable_type) {
    case DGA_DRAW_WINDOW:
	rval = dgai_mbsmemb_devinfo((_Dga_window)dgadraw);
	break;
    case DGA_DRAW_PIXMAP:
	rval = dgai_pix_devinfo((_Dga_pixmap)dgadraw);
	break;
    }
#ifdef MT
    mutex_unlock(&dgaGlobalMutex);
#endif
    return (rval);
}

int
dga_draw_sitechg (Dga_drawable dgadraw, int *reason)
{
    int rval = -1;

#ifdef MT
    mutex_lock(&dgaGlobalMutex);
#endif
    switch ( ((_Dga_drawable)dgadraw)->drawable_type) {
    case DGA_DRAW_WINDOW:
	rval = dgai_mbsmemb_sitechg((_Dga_window)dgadraw, reason);
	break;
    case DGA_DRAW_PIXMAP:
	rval = dgai_pix_sitechg((_Dga_pixmap)dgadraw, reason);
	break;
    }
#ifdef MT
    mutex_unlock(&dgaGlobalMutex);
#endif
    return (rval);
}

void
dga_draw_sitesetnotify (Dga_drawable dgadraw, DgaSiteNotifyFunc site_notify_func,
			   void *client_data)
{
#ifdef MT
    mutex_lock(&dgaGlobalMutex);
#endif
    switch ( ((_Dga_drawable)dgadraw)->drawable_type) {
    case DGA_DRAW_WINDOW:
	dgai_mbsmemb_sitesetnotify((_Dga_window)dgadraw, site_notify_func, client_data);
	break;
    case DGA_DRAW_PIXMAP:
	dgai_pix_sitesetnotify((_Dga_pixmap)dgadraw, site_notify_func, client_data);
	break;
    }
#ifdef MT
    mutex_unlock(&dgaGlobalMutex);
#endif
}

void
dga_draw_sitegetnotify (Dga_drawable dgadraw, DgaSiteNotifyFunc *site_notify_func,
			   void **client_data)
{
#ifdef MT
    mutex_lock(&dgaGlobalMutex);
#endif
    switch ( ((_Dga_drawable)dgadraw)->drawable_type) {
    case DGA_DRAW_WINDOW:
	dgai_mbsmemb_sitegetnotify((_Dga_window)dgadraw, site_notify_func, client_data);
	break;
    case DGA_DRAW_PIXMAP:
	dgai_pix_sitegetnotify((_Dga_pixmap)dgadraw, site_notify_func, client_data);
	break;
    }
#ifdef MT
    mutex_unlock(&dgaGlobalMutex);
#endif
}

int
dga_draw_site (Dga_drawable dgadraw)
{
    int rval = -1;

#ifdef MT
    mutex_lock(&dgaGlobalMutex);
#endif
    switch ( ((_Dga_drawable)dgadraw)->drawable_type) {
    case DGA_DRAW_WINDOW:
	rval = dgai_mbsmemb_site((_Dga_window)dgadraw);
	break;
    case DGA_DRAW_PIXMAP:
	rval = dgai_pix_site((_Dga_pixmap)dgadraw);
	break;
    }
#ifdef MT
    mutex_unlock(&dgaGlobalMutex);
#endif
    return (rval);
}

void *
dga_draw_address (Dga_drawable dgadraw)
{
    void *rval = NULL;

#ifdef MT
    mutex_lock(&dgaGlobalMutex);
#endif
    switch ( ((_Dga_drawable)dgadraw)->drawable_type) {
    case DGA_DRAW_WINDOW:
	rval = dgai_mbsmemb_address((_Dga_window)dgadraw);
	break;
    case DGA_DRAW_PIXMAP:
	rval = dgai_pix_address((_Dga_pixmap)dgadraw);
	break;
    }
#ifdef MT
    mutex_unlock(&dgaGlobalMutex);
#endif
    return (rval);
}

int
dga_draw_linebytes (Dga_drawable dgadraw)
{
    int rval = -1;

#ifdef MT
    mutex_lock(&dgaGlobalMutex);
#endif
    switch ( ((_Dga_drawable)dgadraw)->drawable_type) {
    case DGA_DRAW_WINDOW:
	rval = dgai_mbsmemb_linebytes((_Dga_window)dgadraw);
	break;
    case DGA_DRAW_PIXMAP:
	rval = dgai_pix_linebytes((_Dga_pixmap)dgadraw);
	break;
    }
#ifdef MT
    mutex_unlock(&dgaGlobalMutex);
#endif
    return (rval);
}

int
dga_draw_bitsperpixel (Dga_drawable dgadraw)
{
    int rval = -1;

#ifdef MT
    mutex_lock(&dgaGlobalMutex);
#endif
    switch ( ((_Dga_drawable)dgadraw)->drawable_type) {
    case DGA_DRAW_WINDOW:
	rval = dgai_mbsmemb_bitsperpixel((_Dga_window)dgadraw);
	break;
    case DGA_DRAW_PIXMAP:
	rval = dgai_pix_bitsperpixel((_Dga_pixmap)dgadraw);
	break;
    }
#ifdef MT
    mutex_unlock(&dgaGlobalMutex);
#endif
    return (rval);
}

int
dga_draw_clipchg (Dga_drawable dgadraw)
{
    int rval = -1;

#ifdef MT
    mutex_lock(&dgaGlobalMutex);
#endif
    switch ( ((_Dga_drawable)dgadraw)->drawable_type) {
    case DGA_DRAW_WINDOW:
	rval = dgai_mbsmemb_clipchg((_Dga_window)dgadraw);
	break;
    case DGA_DRAW_PIXMAP:
	rval = dgai_pix_clipchg((_Dga_pixmap)dgadraw);
	break;
    }
#ifdef MT
    mutex_unlock(&dgaGlobalMutex);
#endif
    return (rval);
}

void
dga_draw_bbox(Dga_drawable dgadraw, int *xp, int *yp, int *widthp, int *heightp)
{
#ifdef MT
    mutex_lock(&dgaGlobalMutex);
#endif
    switch ( ((_Dga_drawable)dgadraw)->drawable_type) {
    case DGA_DRAW_WINDOW:
	dgai_mbsmemb_bbox((_Dga_window)dgadraw, xp, yp, widthp, heightp);
	break;
    case DGA_DRAW_PIXMAP:
	dgai_pix_bbox((_Dga_pixmap)dgadraw, xp, yp, widthp, heightp);
	break;
    }
#ifdef MT
    mutex_unlock(&dgaGlobalMutex);
#endif
}

int
dga_draw_visibility (Dga_drawable dgadraw)
{ 
    int rval = -1;

#ifdef MT
    mutex_lock(&dgaGlobalMutex);
#endif
    switch ( ((_Dga_drawable)dgadraw)->drawable_type) {
    case DGA_DRAW_WINDOW:
	rval = dgai_mbsmemb_visibility((_Dga_window)dgadraw);
	break;
    case DGA_DRAW_PIXMAP:
	/* always unobscured */
	rval = DGA_VIS_UNOBSCURED;
	break;
    }
#ifdef MT
    mutex_unlock(&dgaGlobalMutex);
#endif
    return (rval);
}

int
dga_draw_empty (Dga_drawable dgadraw)
{ 
    int rval = -1;

#ifdef MT
    mutex_lock(&dgaGlobalMutex);
#endif
    switch ( ((_Dga_drawable)dgadraw)->drawable_type) {
    case DGA_DRAW_WINDOW:
	rval = dgai_mbsmemb_empty((_Dga_window)dgadraw);
	break;
    case DGA_DRAW_PIXMAP:
	rval = dgai_pix_empty((_Dga_pixmap)dgadraw);
	break;
    }
#ifdef MT
    mutex_unlock(&dgaGlobalMutex);
#endif
    return (rval);
}

short *
dga_draw_clipinfo (Dga_drawable dgadraw)
{
    short *rval = NULL;

#ifdef MT
    mutex_lock(&dgaGlobalMutex);
#endif
    switch ( ((_Dga_drawable)dgadraw)->drawable_type) {
    case DGA_DRAW_WINDOW:
	rval = dgai_mbsmemb_clipinfo((_Dga_window)dgadraw);
	break;
    case DGA_DRAW_PIXMAP:
	rval = dgai_pix_clipinfo((_Dga_pixmap)dgadraw);
	break;
    }
#ifdef MT
    mutex_unlock(&dgaGlobalMutex);
#endif
    return (rval);
}


int
dga_draw_singlerect (Dga_drawable dgadraw)
{
    int rval;

#ifdef MT
    mutex_lock(&dgaGlobalMutex);
#endif
    switch ( ((_Dga_drawable)dgadraw)->drawable_type) {
    case DGA_DRAW_WINDOW:
	rval = dgai_mbsmemb_singlerect((_Dga_window)dgadraw);
	break;
    case DGA_DRAW_PIXMAP:
    default:
	/* always a single rect */
	rval = 1;
	break;
    }
#ifdef MT
    mutex_unlock(&dgaGlobalMutex);
#endif
    return (rval);
}

int
dga_draw_obscured (Dga_drawable dgadraw)
{
    int rval;

#ifdef MT
    mutex_lock(&dgaGlobalMutex);
#endif
    switch ( ((_Dga_drawable)dgadraw)->drawable_type) {
    case DGA_DRAW_WINDOW:
	rval = dgai_mbsmemb_obscured((_Dga_window)dgadraw);
	break;
    case DGA_DRAW_PIXMAP:
    default:
	/* never obscured */
	rval = 0;
	break;
    }
#ifdef MT
    mutex_unlock(&dgaGlobalMutex);
#endif
    return (rval);
}


/* CONSOLIDATION PRIVATE */
u_short
dga_draw_borderwidth (Dga_drawable dgadraw) 
{ 
    u_short rval;

#ifdef MT
    mutex_lock(&dgaGlobalMutex);
#endif
    switch ( ((_Dga_drawable)dgadraw)->drawable_type) {
    case DGA_DRAW_WINDOW:
	rval = dgai_mbsmemb_borderwidth((_Dga_window)dgadraw);
	break;
    case DGA_DRAW_PIXMAP:
    default:
	/* always 0 */
	rval = 0;
	break;
    }
#ifdef MT
    mutex_unlock(&dgaGlobalMutex);
#endif
    return (rval);
} 


void
dga_draw_curshandle (Dga_drawable dgadraw, DgaCursTakeDownFunc take_down_func,
		        void *client_data)
{
#ifdef MT
    mutex_lock(&dgaGlobalMutex);
#endif
    switch ( ((_Dga_drawable)dgadraw)->drawable_type) {
    case DGA_DRAW_WINDOW:
	dgai_mbsmemb_curshandle((_Dga_window)dgadraw, take_down_func, client_data);
	break;
    case DGA_DRAW_PIXMAP:
	/* pixmaps never have cursors */
	break;
    }
#ifdef MT
    mutex_unlock(&dgaGlobalMutex);
#endif
}


int		
dga_draw_rtngrab (Dga_drawable dgadraw)
{
    int rval;

#ifdef MT
    mutex_lock(&dgaGlobalMutex);
#endif
    switch ( ((_Dga_drawable)dgadraw)->drawable_type) {
    case DGA_DRAW_WINDOW:
	rval = dgai_mbsmemb_rtngrab((_Dga_window)dgadraw);
	break;
    case DGA_DRAW_PIXMAP:
    default:
	/* not applicable to pixmaps */
	rval = 0;
	break;
    }
#ifdef MT
    mutex_unlock(&dgaGlobalMutex);
#endif
    return (rval);
}

int		
dga_draw_rtnungrab (Dga_drawable dgadraw)
{
    int rval;

#ifdef MT
    mutex_lock(&dgaGlobalMutex);
#endif
    switch ( ((_Dga_drawable)dgadraw)->drawable_type) {
    case DGA_DRAW_WINDOW:
	rval = dgai_mbsmemb_rtnungrab((_Dga_window)dgadraw);
	break;
    case DGA_DRAW_PIXMAP:
    default:
	/* not applicable to pixmaps */
	rval = 0;
	break;
    }
#ifdef MT
    mutex_unlock(&dgaGlobalMutex);
#endif
    return (rval);
}

int		
dga_draw_rtnchg (Dga_drawable dgadraw)
{
    int rval;

#ifdef MT
    mutex_lock(&dgaGlobalMutex);
#endif
    switch ( ((_Dga_drawable)dgadraw)->drawable_type) {
    case DGA_DRAW_WINDOW:
	rval = dgai_mbsmemb_rtnchg((_Dga_window)dgadraw);
	break;
    case DGA_DRAW_PIXMAP:
    default:
	/* not applicable to pixmaps -- force a query for active */
	rval = 1;
	break;
    }
#ifdef MT
    mutex_unlock(&dgaGlobalMutex);
#endif
    return (rval);
}

int		
dga_draw_rtnactive (Dga_drawable dgadraw)
{
    int rval;

#ifdef MT
    mutex_lock(&dgaGlobalMutex);
#endif
    switch ( ((_Dga_drawable)dgadraw)->drawable_type) {
    case DGA_DRAW_WINDOW:
	rval = dgai_mbsmemb_rtnactive((_Dga_window)dgadraw);
	break;
    case DGA_DRAW_PIXMAP:
    default:
	/* not applicable to pixmaps -- never active */
	rval = 0;
	break;
    }
#ifdef MT
    mutex_unlock(&dgaGlobalMutex);
#endif
    return (rval);
}

int		
dga_draw_rtncached (Dga_drawable dgadraw)
{
    int rval;

#ifdef MT
    mutex_lock(&dgaGlobalMutex);
#endif
    switch ( ((_Dga_drawable)dgadraw)->drawable_type) {
    case DGA_DRAW_WINDOW:
	rval = dgai_mbsmemb_rtncached((_Dga_window)dgadraw);
	break;
    case DGA_DRAW_PIXMAP:
    default:
	/* not applicable to pixmaps -- consider never cached */
	rval = 0;
	break;
    }
#ifdef MT
    mutex_unlock(&dgaGlobalMutex);
#endif
    return (rval);
}

void *		
dga_draw_rtndevinfop (Dga_drawable dgadraw)
{
    void *rval;

#ifdef MT
    mutex_lock(&dgaGlobalMutex);
#endif
    switch ( ((_Dga_drawable)dgadraw)->drawable_type) {
    case DGA_DRAW_WINDOW:
	rval = dgai_mbsmemb_rtndevinfop((_Dga_window)dgadraw);
	break;
    case DGA_DRAW_PIXMAP:
    default:
	/* not applicable to pixmaps -- doesn't have devinfo */
	rval = NULL;
	break;
    }
#ifdef MT
    mutex_unlock(&dgaGlobalMutex);
#endif
    return (rval);
}

/* This routine is for compatibility only. In the old interface both
 * the "p" and the "non-p" version were in but the "p" version was the
 * one that was documented. */
void *		
dga_draw_rtndevinfo (Dga_drawable dgadraw)
{
    return(dga_draw_rtndevinfop (dgadraw));
}

void
dga_draw_rtndevtype (Dga_drawable dgadraw, u_char *type, 
		     char **name)
{
#ifdef MT
    mutex_lock(&dgaGlobalMutex);
#endif
    switch ( ((_Dga_drawable)dgadraw)->drawable_type) {
    case DGA_DRAW_WINDOW:
	dgai_mbsmemb_rtndevtype((_Dga_window)dgadraw, type, name);
	break;
    case DGA_DRAW_PIXMAP:
    default:
	/* not applicable to pixmaps -- no dev type and name */
	*type = (u_char) 0;
	*name = NULL;
	break;
    }
#ifdef MT
    mutex_unlock(&dgaGlobalMutex);
#endif
}

void
dga_draw_rtndimensions (Dga_drawable dgadraw, short *width, 
			short *height, u_int *linebytes)
{
#ifdef MT
    mutex_lock(&dgaGlobalMutex);
#endif
    switch ( ((_Dga_drawable)dgadraw)->drawable_type) {
    case DGA_DRAW_WINDOW:
	dgai_mbsmemb_rtndimensions((_Dga_window)dgadraw, width, height, linebytes);
	break;
    case DGA_DRAW_PIXMAP:
    default:
	/* not applicable to pixmaps -- no dimensions */
	*width = 0;
	*height = 0;
	*linebytes = 0;
	break;
    }
#ifdef MT
    mutex_unlock(&dgaGlobalMutex);
#endif
}

int
dga_draw_rtnbitsperpixel (Dga_drawable dgadraw)
{
    int rval;

#ifdef MT
    mutex_lock(&dgaGlobalMutex);
#endif
    switch ( ((_Dga_drawable)dgadraw)->drawable_type) {
    case DGA_DRAW_WINDOW:
	rval = dgai_mbsmemb_rtnbitsperpixel((_Dga_window)dgadraw);
	break;
    case DGA_DRAW_PIXMAP:
    default:
	/* not applicable to pixmaps */
	rval = 0;
	break;
    }
#ifdef MT
    mutex_unlock(&dgaGlobalMutex);
#endif
    return (rval);
}

void *
dga_draw_rtnpixels (Dga_drawable dgadraw)
{
    void *rval;

#ifdef MT
    mutex_lock(&dgaGlobalMutex);
#endif
    switch ( ((_Dga_drawable)dgadraw)->drawable_type) {
    case DGA_DRAW_WINDOW:
	rval = dgai_mbsmemb_rtnpixels((_Dga_window)dgadraw);
	break;
    case DGA_DRAW_PIXMAP:
    default:
	/* not applicable to pixmaps -- doesn't have retained pixels */
	rval = NULL;
	break;
    }
#ifdef MT
    mutex_unlock(&dgaGlobalMutex);
#endif
    return (rval);
}

Dga_widinfo *
dga_draw_widinfop (Dga_drawable dgadraw)
{
    Dga_widinfo *rval;

#ifdef MT
    mutex_lock(&dgaGlobalMutex);
#endif
    switch ( ((_Dga_drawable)dgadraw)->drawable_type) {
    case DGA_DRAW_WINDOW:
	rval = dga_win_widinfop((Dga_window)dgadraw);
	break;
    case DGA_DRAW_PIXMAP:
    default:
	/* not applicable to pixmaps -- doesn't have retained pixels */
	rval = NULL;
	break;
    }
#ifdef MT
    mutex_unlock(&dgaGlobalMutex);
#endif
    return (rval);
}


/* Note: the following routines are consolidation private.  They are not
   a part of the public interface. */

int
dga_draw_mbchg (Dga_drawable dgadraw, int *reason)
{
    switch ( ((_Dga_drawable)dgadraw)->drawable_type) {
    case DGA_DRAW_WINDOW:
	return (dgai_mbsmemb_mbchg((_Dga_window)dgadraw, reason));
    case DGA_DRAW_PIXMAP:
    default:
	/* pixmaps never are multibuffered */
	return (0);
    }
}
 
void
dga_draw_mbsetnotify (Dga_drawable dgadraw, DgaMbNotifyFunc mb_notify_func,
			   void *client_data)
{
    switch ( ((_Dga_drawable)dgadraw)->drawable_type) {
    case DGA_DRAW_WINDOW:
	dgai_mbsmemb_mbsetnotify((_Dga_window)dgadraw, mb_notify_func, client_data);
	break;
    case DGA_DRAW_PIXMAP:
	/* pixmaps never are multibuffered */
	break;
    }
}

void
dga_draw_mbgetnotify (Dga_drawable dgadraw, DgaMbNotifyFunc *mb_notify_func,
			   void **client_data)
{
    switch ( ((_Dga_drawable)dgadraw)->drawable_type) {
    case DGA_DRAW_WINDOW:
	dgai_mbsmemb_mbgetnotify((_Dga_window)dgadraw, mb_notify_func, client_data);
	break;
    case DGA_DRAW_PIXMAP:
	/* pixmaps never are multibuffered */
	break;
    }
}


int
dga_draw_mbaccessmode (Dga_drawable dgadraw)
{
    switch ( ((_Dga_drawable)dgadraw)->drawable_type) {
    case DGA_DRAW_WINDOW:
	return (dgai_mbsmemb_mbaccessmode((_Dga_window)dgadraw));
    case DGA_DRAW_PIXMAP:
    default:
	return (DGA_MBACCESS_NONE);
    }
}

int
dga_draw_mbsitetypeconst (Dga_drawable dgadraw)
{
    switch ( ((_Dga_drawable)dgadraw)->drawable_type) {
    case DGA_DRAW_WINDOW:
	return (dgai_mbsmemb_mbsitetypeconst((_Dga_window)dgadraw));
    case DGA_DRAW_PIXMAP:
    default:
	/* can't tell for pixmaps - be conservative */
	return (0);
    }
}

void
dga_draw_mbsetrendbufnotify (Dga_drawable dgadraw, DgaRendBufNotifyFunc rb_notify_func,
				void *client_data)
{
    switch ( ((_Dga_drawable)dgadraw)->drawable_type) {
    case DGA_DRAW_WINDOW:
	dgai_mbsmemb_mbsetrendbufnotify((_Dga_window)dgadraw, rb_notify_func, client_data);
	break;
    case DGA_DRAW_PIXMAP:
	/* pixmaps never are multibuffered */
	break;
    }
}

void
dga_draw_mbgetrendbufnotify (Dga_drawable dgadraw, DgaRendBufNotifyFunc *rb_notify_func,
				void **client_data)
{
    switch ( ((_Dga_drawable)dgadraw)->drawable_type) {
    case DGA_DRAW_WINDOW:
	dgai_mbsmemb_mbgetrendbufnotify((_Dga_window)dgadraw, rb_notify_func, client_data);
	break;
    case DGA_DRAW_PIXMAP:
	/* pixmaps never are multibuffered */
	break;
    }
}


int
dga_draw_ovlstatechg (Dga_drawable dgadraw)
{
    switch ( ((_Dga_drawable)dgadraw)->drawable_type) {
    case DGA_DRAW_WINDOW:
	return (dgai_mbsmemb_ovlstatechg((_Dga_window)dgadraw));
    case DGA_DRAW_PIXMAP:
    default:
	/* Pixmaps never have an ovlstate */
	return (0);
    }
}

int
dga_draw_ovlstate (Dga_drawable dgadraw)
{
    switch ( ((_Dga_drawable)dgadraw)->drawable_type) {
    case DGA_DRAW_WINDOW:
	return (dgai_mbsmemb_ovlstate((_Dga_window)dgadraw));
    case DGA_DRAW_PIXMAP:
    default:
	/* Pixmaps never have an ovlstate */
	return (DGA_OVLSTATE_CONFLICT);
    }
}

void
dga_draw_ovlstatesetnotify (Dga_drawable dgadraw, 
			    DgaOvlStateNotifyFunc ovlstate_notify_func,
			    void *client_data)
{
    switch ( ((_Dga_drawable)dgadraw)->drawable_type) {
    case DGA_DRAW_WINDOW:
	dgai_mbsmemb_setovlstatenotify((_Dga_window)dgadraw,
				       ovlstate_notify_func,
				       client_data);
    case DGA_DRAW_PIXMAP:
	/* Pixmaps never have an ovlstate */
	break;
    }
}

void
dga_draw_ovlstategetnotify (Dga_drawable dgadraw, 
			    DgaOvlStateNotifyFunc *ovlstate_notify_func,
			    void **client_data)
{
    switch ( ((_Dga_drawable)dgadraw)->drawable_type) {
    case DGA_DRAW_WINDOW:
	dgai_mbsmemb_getovlstatenotify((_Dga_window)dgadraw,
				       ovlstate_notify_func,
				       client_data);
    case DGA_DRAW_PIXMAP:
	/* Pixmaps never have an ovlstate */
	break;
    }
}
