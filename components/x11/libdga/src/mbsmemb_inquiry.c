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
** mbsmemb_inquiry.c - state inquiry routines for mbufset members.
*/

#ifdef SERVER_DGA
#include <X11/Xlib.h>
#endif  /* SERVER_DGA */
#include "dga_incls.h"
#include "pix_grab.h"
#include "mbufsetstr.h"

extern int dgai_rtn_ungrab_common(_Dga_window dgawin, int drawableGrabber);
extern int dga_rtn_bitsperpixel(Dga_window clientpi);

Display *
dgai_mbsmemb_display (_Dga_window dgawin)
{
    return (dgawin->w_dpy);
}

char *
dgai_mbsmemb_devname (_Dga_window dgawin)
{
    if (dgawin->changeMask & DGA_CHANGE_ZOMBIE)
	return (NULL);

    return(((WXINFO *) (dgawin->w_info))->w_devname);
}

int
dgai_mbsmemb_devfd (_Dga_window dgawin)
{
    return(dgawin->w_devfd);
}

int
dgai_mbsmemb_depth (_Dga_window dgawin)
{
    WXINFO *infop = (WXINFO *) dgawin->w_info;
	
    if (dgawin->changeMask & DGA_CHANGE_ZOMBIE)
	return (NULL);

    if (infop->w_version >= 3) 
	return((int)infop->w_depth);
    else 
	return (0);
}

void
dgai_mbsmemb_set_client_infop (_Dga_window dgawin, void *client_info_ptr)
{
    dgawin->w_client = client_info_ptr;
}

void *
dgai_mbsmemb_get_client_infop (_Dga_window dgawin)
{
    return (dgawin->w_client);
}

void *
dgai_mbsmemb_devinfo (_Dga_window dgawin)
{
    SHARED_PIXMAP_INFO *infop;

    if ((dgawin->eLockSubj == DGA_LOCKSUBJ_INVALID) ||
	dgawin->changeMask & DGA_CHANGE_ZOMBIE) {
	return (NULL);
    }

    if (dgawin->eLockSubj == -1) {
        WXINFO *infop = (WXINFO *) dgawin->w_info;

        return ((void *) &(infop->wx_dbuf.device_info));
    }
    infop = dgawin->pMbs->pNbShinfo[dgawin->eLockSubj];
    return (((char *)infop) + infop->device_offset);
}

int
dgai_mbsmemb_devinfochg (_Dga_window dgawin)
{
    if (dgawin->changeMask & DGA_CHANGE_DEVINFO) {
	dgawin->changeMask &= ~DGA_CHANGE_DEVINFO;
	return (1);
    } else {
	return (0);
    }
}

int
dgai_mbsmemb_sitechg (_Dga_window dgawin, int *reason)
{
    if (dgawin->changeMask & DGA_CHANGE_SITE) {
	dgawin->changeMask &= ~DGA_CHANGE_SITE;
	*reason = dgawin->siteChgReason;
	return (1);
    } else {
	*reason = DGA_SITECHG_UNKNOWN;
	return (0);
    }
}

void
dgai_mbsmemb_sitesetnotify (_Dga_window dgawin, DgaSiteNotifyFunc site_notify_func,
			   void *client_data)
{
    dgawin->siteNotifyFunc = site_notify_func;
    dgawin->siteNotifyClientData = client_data;
}

void
dgai_mbsmemb_sitegetnotify (_Dga_window dgawin, DgaSiteNotifyFunc *site_notify_func,
			   void **client_data)
{
    *site_notify_func = dgawin->siteNotifyFunc;
    *client_data = dgawin->siteNotifyClientData;
}

int
dgai_mbsmemb_site (_Dga_window dgawin)
{
    SHARED_PIXMAP_INFO *infop;

    if ((dgawin->eLockSubj == DGA_LOCKSUBJ_INVALID)||
	 dgawin->changeMask & DGA_CHANGE_ZOMBIE) {
	return (DGA_SITE_NULL);
    }

    /* viewable drawables always are in device site */
    if (DGA_LOCKSUBJ_VIEWABLE(dgawin, dgawin->eLockSubj)) {
	return (DGA_SITE_DEVICE);
    }

    /* the site of a nonviewable multibuffer depends on whether or not
       it is cached */

    infop = dgawin->pMbs->pNbShinfo[dgawin->eLockSubj];
    return (infop->cached ? DGA_SITE_DEVICE : DGA_SITE_SYSTEM);
}

void *
dgai_mbsmemb_address (_Dga_window dgawin)
{
    SHARED_PIXMAP_INFO *infop;
    
    if ((dgawin->eLockSubj == DGA_LOCKSUBJ_INVALID) ||
    	dgawin->changeMask & DGA_CHANGE_ZOMBIE ||
	DGA_LOCKSUBJ_VIEWABLE(dgawin, dgawin->eLockSubj)) {
	return (NULL);
    }

    /* the return value is only valid for nonviewable multibuffers that
       are not cached */
    	infop = dgawin->pMbs->pNbShinfo[dgawin->eLockSubj];
    	return (infop->cached ? NULL : (void *)(infop + 1));
}

int
dgai_mbsmemb_linebytes (_Dga_window dgawin)
{
    SHARED_PIXMAP_INFO *infop;
    
    if ((dgawin->eLockSubj == DGA_LOCKSUBJ_INVALID) ||
	dgawin->changeMask & DGA_CHANGE_ZOMBIE ||
	DGA_LOCKSUBJ_VIEWABLE(dgawin, dgawin->eLockSubj)) {
	return (0);
    }

    /* the return value is only valid for nonviewable multibuffers that
       are not cached */
    infop = dgawin->pMbs->pNbShinfo[dgawin->eLockSubj];
    return (infop->cached ? 0 : infop->linebytes);
}

int
dgai_mbsmemb_bitsperpixel (_Dga_window dgawin)
{
    SHARED_PIXMAP_INFO *infop;
    
    if ((dgawin->eLockSubj == DGA_LOCKSUBJ_INVALID) ||
	dgawin->changeMask & DGA_CHANGE_ZOMBIE ||
	DGA_LOCKSUBJ_VIEWABLE(dgawin, dgawin->eLockSubj)) {
	return (0);
    }

    /* the return value is only valid for nonviewable multibuffers that
       are not cached */
    infop = dgawin->pMbs->pNbShinfo[dgawin->eLockSubj];
    return (infop->cached ? 0 : infop->bitsperpixel);
}

int
dgai_mbsmemb_clipchg (_Dga_window dgawin)
{
    /* always force a clip change on a zombie to get the client
       to notice */
    if (dgawin->changeMask & DGA_CHANGE_ZOMBIE) {
	return (1);
    }

    if (DGA_LOCKSUBJ_VIEWABLE(dgawin, dgawin->eLockSubj)) {
	if (dga_win_clipchg((Dga_window)dgawin) || 
	    (dgawin->changeMask & DGA_CHANGE_CLIP)) {
	    dgawin->changeMask &= ~DGA_CHANGE_CLIP;
	    return (1);
	} else {
	    return (0);
	}
    } else {
	/* nonviewable */
	if (dgawin->changeMask & DGA_CHANGE_CLIP) {
	    dgawin->changeMask &= ~DGA_CHANGE_CLIP;
	    return (1);
        } else {
	    return (0);
	}
    }
}

void
dgai_mbsmemb_bbox(_Dga_window dgawin, int *xp, int *yp, int *widthp, int *heightp)
{
    if ((dgawin->eLockSubj == DGA_LOCKSUBJ_INVALID) ||
	dgawin->changeMask & DGA_CHANGE_ZOMBIE) {
	*xp = 0;
	*yp = 0;
	*widthp = 0;
	*heightp = 0;
	return;
    }

    if (DGA_LOCKSUBJ_VIEWABLE(dgawin, dgawin->eLockSubj)) {
	dga_win_bbox((Dga_window)dgawin, xp, yp, widthp, heightp);
    } else {
	/* nonviewable */
	SHARED_PIXMAP_INFO *infop;

	infop = dgawin->pMbs->pNbShinfo[dgawin->eLockSubj];
	*xp = 0;
	*yp = 0;
	*widthp = infop->width;
	*heightp = infop->height;
    }
}

int
dgai_mbsmemb_visibility (_Dga_window dgawin)
{
    if (dgawin->changeMask & DGA_CHANGE_ZOMBIE) {
	return (DGA_VIS_FULLY_OBSCURED);
    }

    if (DGA_LOCKSUBJ_VIEWABLE(dgawin, dgawin->eLockSubj)) {
	return (dgai_win_visibility((Dga_window)dgawin));
    } else {
        /* Non viewable mbufs are always unobscured */
        return (DGA_VIS_UNOBSCURED);
    }
}

int
dgai_mbsmemb_empty (_Dga_window dgawin)
{ 
    if ((dgawin->eLockSubj == DGA_LOCKSUBJ_INVALID)||
	dgawin->changeMask & DGA_CHANGE_ZOMBIE) {
	return (1);
    }

    if (DGA_LOCKSUBJ_VIEWABLE(dgawin, dgawin->eLockSubj)) {
	return (dga_win_empty((Dga_window)dgawin));
    } else {
	/* nonviewable */
	SHARED_PIXMAP_INFO *infop;

	infop = dgawin->pMbs->pNbShinfo[dgawin->eLockSubj];
	return (infop->width <= 0 || infop->height <= 0);
    }
}

static short nonviewableShape[] = {
    0, /* ymin */
    0, /* ymax: fill in based on height */
    0, /* xmin */
    0, /* xmax: fill in based on width */
    DGA_X_EOL,
    DGA_Y_EOL,
};

#define YMAX_INDEX 1
#define XMAX_INDEX 3

short *
dgai_mbsmemb_clipinfo (_Dga_window dgawin)
{
    if ((dgawin->eLockSubj == DGA_LOCKSUBJ_INVALID) ||
	 dgawin->changeMask & DGA_CHANGE_ZOMBIE) {
	return (NULL);
    }

    if (DGA_LOCKSUBJ_VIEWABLE(dgawin, dgawin->eLockSubj)) {
	return (dga_win_clipinfo((Dga_window)dgawin));
    } else {
	/* nonviewable */
	SHARED_PIXMAP_INFO *infop;

	/* build a dummy shape describing the rectangle */
	infop = dgawin->pMbs->pNbShinfo[dgawin->eLockSubj];
	if (infop->width <= 0 || infop->height <= 0) {
	    return (NULL);
	} else {
	    nonviewableShape[YMAX_INDEX] = infop->height - 1;
	    nonviewableShape[XMAX_INDEX] = infop->width - 1;
	    return (nonviewableShape);
	}
    }
}


int
dgai_mbsmemb_singlerect (_Dga_window dgawin)
{
    if (dgawin->changeMask & DGA_CHANGE_ZOMBIE) {
	/* consider a zombie to be a "single rectangle" of 0 width and height */
	return (1);
    }

    if (DGA_LOCKSUBJ_VIEWABLE(dgawin, dgawin->eLockSubj)) {
	return (dga_win_singlerect((Dga_window)dgawin));
    } else {
	/* nonviewable is always a single rectangle */
	return (1);
    }
}

int
dgai_mbsmemb_obscured (_Dga_window dgawin)
{
    if (dgawin->changeMask & DGA_CHANGE_ZOMBIE) {
	/* consider a zombie to be always fully obscured */
	return (1);
    }

    if (DGA_LOCKSUBJ_VIEWABLE(dgawin, dgawin->eLockSubj)) {
	return (dga_win_obscured((Dga_window)dgawin));
    } else {
	/* nonviewable can never be obscured */
	return (0);
    }
}


u_short
dgai_mbsmemb_borderwidth (_Dga_window dgawin) 
{ 
    if (dgawin->changeMask & DGA_CHANGE_ZOMBIE) {
	/* zombies don't have borders */
	return (0);
    }

    if (DGA_LOCKSUBJ_WINDOW(dgawin, dgawin->eLockSubj)) {
	return (dga_win_borderwidth((Dga_window)dgawin));
    } else {
	/* multibuffers don't have borders */
	return (0);
    }
} 


typedef void (*DgaCursTakeDownFuncOld)();

void
dgai_mbsmemb_curshandle (_Dga_window dgawin, DgaCursTakeDownFunc take_down_func,
		        void *client_data)
{
    Dga_window dgaw;

    /* Nonviewable drawables never have a cursor */
    if (!DGA_LOCKSUBJ_VIEWABLE(dgawin, dgawin->eLockSubj)) {
	return;
    }

    /* viewable multibuffers share the cursor of the main window */
    dgaw = (Dga_window) dgawin;    
    if (dga_win_curschg(dgaw)) {
	if (dga_win_cursactive(dgaw)) {
	    dga_win_cursupdate(dgaw, 
			       (DgaCursTakeDownFuncOld)take_down_func,
			       client_data);
	}
    }
}


int
dgai_mbsmemb_rtngrab (_Dga_window dgawin)
{
    /* rtngrab is not something that must be called from inside a lock
     * and therefore the eLockSubj is meaningless.  Just do a
     * dga_rtn_grab() on the window. */

    return (dga_rtn_grab((Dga_window)dgawin));
}

int
dgai_mbsmemb_rtnungrab (_Dga_window dgawin)
{
    return (dgai_rtn_ungrab_common(dgawin,1));
}

int
dgai_mbsmemb_rtnchg (_Dga_window dgawin)
{
    if (DGA_LOCKSUBJ_WINDOW(dgawin, dgawin->eLockSubj)) {
	return (dga_win_rtnchg((Dga_window)dgawin));
    } else {
	/* rtn is not applicable to multibuffers -- always force an activity check */
	return (1);
    }
}

int
dgai_mbsmemb_rtnactive (_Dga_window dgawin)
{
    if (DGA_LOCKSUBJ_WINDOW(dgawin, dgawin->eLockSubj)) {
	return (dga_rtn_active((Dga_window)dgawin));
    } else {
	/* rtn is not applicable to multibuffers -- never active */
	return (0);
    }
}

int
dgai_mbsmemb_rtncached (_Dga_window dgawin)
{
    if (DGA_LOCKSUBJ_WINDOW(dgawin, dgawin->eLockSubj)) {
	return (dga_rtn_cached((Dga_window)dgawin));
    } else {
	/* rtn is not applicable to multibuffers -- never cached */
	return (0);
    }
}

void *
dgai_mbsmemb_rtndevinfop (_Dga_window dgawin)
{
    if (DGA_LOCKSUBJ_WINDOW(dgawin, dgawin->eLockSubj)) {
	return (dga_rtn_devinfo((Dga_window)dgawin));
    } else {
	/* rtn is not applicable to multibuffers -- no devinfo */
	return (NULL);
    }
}

void
dgai_mbsmemb_rtndevtype (_Dga_window dgawin, u_char *type, char **name)
{
    if (DGA_LOCKSUBJ_WINDOW(dgawin, dgawin->eLockSubj)) {
	dga_rtn_devtype((Dga_window)dgawin, type, name);
    } else {
	/* rtn is not applicable to multibuffers -- values of return args are arbitrary */
	*type = (u_char) 0;
	*name = NULL;
    }
}

void
dgai_mbsmemb_rtndimensions (_Dga_window dgawin, short *width, short *height, 
			    u_int *linebytes)
{
    if (DGA_LOCKSUBJ_WINDOW(dgawin, dgawin->eLockSubj)) {
	dga_rtn_dimensions((Dga_window)dgawin, width, height, linebytes);
    } else {
	/* rtn is not applicable to multibuffers -- values of return args are arbitrary */
	*width =  0;
	*height = 0;
	*linebytes = 0;
    }
}

int
dgai_mbsmemb_rtnbitsperpixel (_Dga_window dgawin)
{
    if (DGA_LOCKSUBJ_WINDOW(dgawin, dgawin->eLockSubj)) {
	return (dga_rtn_bitsperpixel((Dga_window)dgawin));
    } else {
	/* rtn is not applicable to multibuffers -- values of return args are arbitrary */
	return (0);
    }
}

void *
dgai_mbsmemb_rtnpixels (_Dga_window dgawin)
{
    if (DGA_LOCKSUBJ_WINDOW(dgawin, dgawin->eLockSubj)) {
	return (dga_rtn_pixels((Dga_window)dgawin));
    } else {
	/* rtn is not applicable to multibuffers -- return NULL */
	return (NULL);
    }
}


int
dgai_mbsmemb_mbchg (_Dga_window dgawin, int *reason)
{
    if (dgawin->changeMask & DGA_CHANGE_MBUFSET) {
	dgawin->changeMask &= ~DGA_CHANGE_MBUFSET;
	*reason = dgawin->mbChgReason;
	return (1);
    } else {
	*reason = DGA_MBCHG_UNKNOWN;
	return (0);
    }
}
 
void
dgai_mbsmemb_mbsetnotify (_Dga_window dgawin, DgaMbNotifyFunc mb_notify_func,
			   void *client_data)
{
    dgawin->mbNotifyFunc = mb_notify_func;
    dgawin->mbNotifyClientData = client_data;
}

void
dgai_mbsmemb_mbgetnotify (_Dga_window dgawin, DgaMbNotifyFunc *mb_notify_func,
			   void **client_data)
{
    *mb_notify_func = dgawin->mbNotifyFunc;
    *client_data = dgawin->mbNotifyClientData;
}


int
dgai_mbsmemb_mbaccessmode (_Dga_window dgawin)
{
    if (!dgawin->pMbs) {
	return (DGA_MBACCESS_NONE);
    } else {
	WXINFO	*infop;
	
	infop = (WXINFO *) dgawin->w_info;
	
	return (infop->w_mbsInfo.accessMode);
    }
}

int
dgai_mbsmemb_mbsitetypeconst (_Dga_window dgawin)
{
    if (!dgawin->pMbs) {
	return (1);
    } else {
	WXINFO	*infop;
	
	infop = (WXINFO *) dgawin->w_info;

	return (infop->w_mbsInfo.siteTypeConst);
    }
}

void
dgai_mbsmemb_mbsetrendbufnotify (_Dga_window dgawin, DgaRendBufNotifyFunc rb_notify_func,
				void *client_data)
{
    dgawin->rendBufNotifyFunc = rb_notify_func;
    dgawin->rendBufNotifyClientData = client_data;
}

void
dgai_mbsmemb_mbgetrendbufnotify (_Dga_window dgawin, DgaRendBufNotifyFunc *rb_notify_func,
				void **client_data)
{
    *rb_notify_func = dgawin->rendBufNotifyFunc;
    *client_data = dgawin->rendBufNotifyClientData;
}

int
dgai_mbsmemb_ovlstatechg (_Dga_window dgawin)
{
    if (dgawin->changeMask & DGA_CHANGE_OVLSTATE) {
	dgawin->changeMask &= ~DGA_CHANGE_OVLSTATE;
	return (1);
    } else {
	return (0);
    }
}

int
dgai_mbsmemb_ovlstate (_Dga_window dgawin)
{
    /* REMIND: Do we need to check this stuff? */
    if ((dgawin->eLockSubj == DGA_LOCKSUBJ_INVALID) ||
	(dgawin->changeMask & DGA_CHANGE_ZOMBIE)) {
	return (DGA_OVLSTATE_CONFLICT);
    }
    if (!dgawin->isOverlay)
	/* Don't let clients do "overlay" rendering to regular windows! */
	return DGA_OVLSTATE_CONFLICT;
    else
	return dgawin->c_ovlstate;
}

void
dgai_mbsmemb_setovlstatenotify (_Dga_window dgawin, 
				DgaOvlStateNotifyFunc ovlstate_notify_func,
				void *client_data)
{
    dgawin->ovlStateNotifyFunc = ovlstate_notify_func;
    dgawin->ovlStateNotifyClientData = client_data;
}

void
dgai_mbsmemb_getovlstatenotify (_Dga_window dgawin, 
				DgaOvlStateNotifyFunc *ovlstate_notify_func,
				void **client_data)
{
    *ovlstate_notify_func = dgawin->ovlStateNotifyFunc;
    *client_data = dgawin->ovlStateNotifyClientData;
}
