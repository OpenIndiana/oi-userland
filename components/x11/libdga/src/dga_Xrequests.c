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
 * dga_Xrequests.c - the client side code for DGA X11 requests
 */

/*
 *-----------------------------------------------------------------------
 * 
 * This code uses the standard extension mechanism for sending
 * SUN_DGA private extension requests.
 *
 *-----------------------------------------------------------------------
 */

#define	NEED_REPLIES
#define NEED_EVENTS

#ifdef SERVER_DGA
#include <X11/X.h>
#include <X11/Xmd.h>
#include "resource.h"
#include "dixstruct.h"
#include <stdio.h>
#include "pixmapstr.h"
#else

#include <X11/Xlibint.h>
#include <sys/resource.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/un.h>
#include <netdb.h>

#ifdef SVR4
#include <sys/utsname.h>
#endif
#endif /* SERVER_DGA */


#include "dga.h"
#include "dga_Xrequests.h"
#include "dga_incls.h"

#include "XineramaInfo.h"

#ifdef SERVER_DGA
#define NEW             1     /* Flag for SHAPES to use new window grabber */
#define BadCookie 0
#endif

#define X_DGA 0 /* a hack, so GetReq and GetResReq work below */

#ifndef	MIN
#define	MIN(i,j)	((i)<(j)?(i):(j))
#endif

static struct dga_extinfo **dga_extinfo_table = 0; /* No table to start with */
static int dga_extinfo_table_size = 0;

static int terminate_dga_ext();
static int islocalhost();
static int dga_winlist_add();
static int dga_winlist_free();
       void * _dga_is_X_window();
       int dga_pixlist_add();
static int dga_pixlist_free();
       void *_dga_is_X_pixmap();
  
extern void dgai_win_ungrab_common();
extern int _thr_main();

#ifdef SVR4

#ifdef MT
mutex_t	dgaGlobalMutex;
mutex_t	dgaGlobalPixmapMutex;
int	dgaThreaded;	/* 1 == linked with libthread, else 0 */
int	dgaMTOn;	/* 1 == MT per-drawable locking is turned on, else 0 */
#endif
int	_dga_client_version = -1;

void
dga_init_version(ver)
int ver;
{
if (ver > -1)
	_dga_client_version = ver;
#ifdef MT
dgaThreaded = (_thr_main() != -1) ? 1 : 0;
	dgaMTOn = 0;
	mutex_init(&dgaGlobalMutex, USYNC_THREAD, NULL);
	mutex_init(&dgaGlobalPixmapMutex, USYNC_THREAD, NULL);
#endif
}

#endif

#ifndef SERVER_DGA
static struct dga_extinfo *
init_dga_ext(dpy)
Display *dpy;
{
	int			protmajor, protminor;
	XExtCodes		*xecp;
	struct dga_extinfo	*infop;

#ifdef SVR4
	if (_dga_client_version < 0)
		return 0;
#endif
	if (dga_extinfo_table_size < (dpy->fd + 1)) {

		/* We've got to allocate or grow the table */
		struct rlimit		rl;
		int			size;
		struct dga_extinfo	**tblptr;

		size = (getrlimit(RLIMIT_NOFILE, &rl) < 0) ?
		    dga_extinfo_table_size : rl.rlim_cur;
		if (size < (dpy->fd + 1))
			return 0;
		tblptr = (struct dga_extinfo **) ((dga_extinfo_table_size) ?
		    realloc(dga_extinfo_table, sizeof(struct dga_extinfo *) *
			size) :
		    malloc(sizeof(struct dga_extinfo *) * size));
		if (tblptr == NULL)
			return 0;
		dga_extinfo_table = tblptr;
		memset((char *) &dga_extinfo_table[dga_extinfo_table_size],
		    (int)'\0',
		    sizeof(struct dga_extinfo *) *
			(size - dga_extinfo_table_size));
		dga_extinfo_table_size = size;
		}

	if (dga_extinfo_table[dpy->fd] != NULL)
		return dga_extinfo_table[dpy->fd];

	if (!islocalhost(dpy))
		return 0;

	if ((xecp = XInitExtension(dpy, "SUN_DGA")) != NULL) {
		if (XDgaQueryVersion(dpy, &protmajor, &protminor) == 0) {
			protmajor = 3;
/*			protminor = 0; let minor number pass through */
			}
		}
	else
		return 0;

	if ((infop = (struct dga_extinfo *)
	    malloc(sizeof(struct dga_extinfo))) == NULL)
		return 0;

	infop->protocol_major_version = protmajor;
	infop->protocol_minor_version = protminor;
	infop->extension = xecp->extension;
	infop->major_opcode = xecp->major_opcode;
	dga_extinfo_table[dpy->fd] = infop;
	XESetCloseDisplay(dpy, infop->extension, terminate_dga_ext);
	return infop;
}

static int
islocalhost(dpy)
Display *dpy;
{
        char    hostname[256];
	char	*colon;
	unsigned int	namelen;
	size_t	hostlen, phostlen;
#ifdef IPv6
        struct addrinfo *localhostaddr;
        struct addrinfo *otherhostaddr;
        struct addrinfo *i, *j;
        int equiv = 0;
	char host[NI_MAXHOST];
#else
	struct hostent *phost;
	struct hostent *h;
#endif
	union genericaddr {
		struct sockaddr	generic;
		struct sockaddr_in	internet;
#ifdef IPv6
		struct sockaddr_in6	internetv6;
 	        struct sockaddr_storage maximumsize;
#endif
		struct sockaddr_un	nuxi;
  		} addr;
  
	if (dpy->display_name[0] == ':')
		return 1;
#ifdef SVR4
	colon = strrchr(dpy->display_name, ':');
#else
	colon = rindex(dpy->display_name, ':');
#endif
	phostlen = strlen(dpy->display_name) - (colon ? strlen(colon) : 0);
	if((strncmp("unix", dpy->display_name, MIN(phostlen, 4)) == 0) ||
	    (strncmp("localhost", dpy->display_name, MIN(phostlen, 9)) == 0))
		return 1;

	/* We're not a unix domain connection so what are we? */

	namelen = sizeof addr;
	memset((char *) &addr, (int)'\0', sizeof addr);
	if(getpeername(dpy->fd, (struct sockaddr *) &addr,
	    &namelen) < 0)
		return 0;

	hostlen = _XGetHostname(hostname, sizeof(hostname));
      
#ifdef IPv6
        if (getaddrinfo(hostname, NULL, NULL, &localhostaddr) != 0)
            return 0;
	if (getnameinfo(&addr.generic, namelen, host, sizeof(host),
	  NULL, 0, 0) != 0) {
	    freeaddrinfo(localhostaddr);
	    return 0;
	}
        if (getaddrinfo(host, NULL, NULL, &otherhostaddr) != 0) {
            freeaddrinfo(localhostaddr);
            return 0;
        }

        for (i = localhostaddr; i != NULL && equiv == 0; i = i->ai_next) {
            for (j = otherhostaddr; j != NULL && equiv == 0; j = j->ai_next) {
                if (i->ai_family == j->ai_family) {
                    if (i->ai_family == AF_INET) {
                        struct sockaddr_in *sinA 
                          = (struct sockaddr_in *) i->ai_addr;
                        struct sockaddr_in *sinB
                          = (struct sockaddr_in *) j->ai_addr;
                        struct in_addr *A = &sinA->sin_addr;
                        struct in_addr *B = &sinB->sin_addr;

                        if (memcmp(A,B,sizeof(struct in_addr)) == 0) {
                            equiv = 1;
                        }
                    } else if (i->ai_family == AF_INET6) {
                        struct sockaddr_in6 *sinA 
                          = (struct sockaddr_in6 *) i->ai_addr;
                        struct sockaddr_in6 *sinB 
                          = (struct sockaddr_in6 *) j->ai_addr;
                        struct in6_addr *A = &sinA->sin6_addr;
                        struct in6_addr *B = &sinB->sin6_addr;

                        if (memcmp(A,B,sizeof(struct in6_addr)) == 0) {
                            equiv = 1;
                        }
                    }
                }
            }
        }
        
        freeaddrinfo(localhostaddr);
        freeaddrinfo(otherhostaddr);
        return equiv;
#else
        if ((addr.generic.sa_family !=  AF_INET) ||
            ((h  =  gethostbyaddr((char *)&addr.internet.sin_addr,
            sizeof addr.internet.sin_addr,
            addr.internet.sin_family)) == 0))
                return 0;

        /* Find real host name on TCPIP */
        phost = gethostbyname(h->h_name);
        phostlen = strlen(phost->h_name);

	if (strncmp(hostname, phost->h_name, MIN(phostlen, hostlen)))
		return 0;

	return 1;
#endif

}

static struct dga_extinfo *
lookup_dga_ext(dpy)
Display *dpy;
{
	if (dga_extinfo_table_size < (dpy->fd + 1))
		return 0;
	return dga_extinfo_table[dpy->fd];
}

static int
terminate_dga_ext(dpy, codes)
Display		*dpy;
XExtCodes	*codes;
{ 
	free(dga_extinfo_table[dpy->fd]);
	dga_extinfo_table[dpy->fd] = NULL;
	dga_winlist_free(dpy, NULL);
	/* TODO: free pixmaps as well? */
	return(1);
}
#endif /* SERVER_DGA */

Dga_token 
XDgaGrabWindow(dpy, win)
Display		*dpy;
Window		win;
{
#ifdef SERVER_DGA
    int val;
    WindowPtr pWin = (WindowPtr)LookupIDByType(win, RT_WINDOW);
    if (!pWin) 
        return (BadCookie);

    if (((DrawablePtr)pWin)->type == DRAWABLE_PIXMAP) 
        return (BadCookie);
    val = DgaWgGrab(pWin, NEW);

    if (val) {
        if (dga_winlist_add(val, dpy, win) == 0) {
            XDgaUnGrabWindow(dpy, win);
            return 0;
        }
    }
    return val;
#else
	xResourceReq		*req;
	xGenericReply		rep;
	struct dga_extinfo	*extinfop;

	if ((extinfop = init_dga_ext(dpy)) == NULL)
		return 0;
	LockDisplay(dpy);
	GetResReq(DGA, win, req);
	req->reqType = extinfop->major_opcode;
	req->pad = (extinfop->protocol_major_version >= 2) ?
	    X_DgaGrabWindow : X_DgaGrabWindow_Old ;
	if (!_XReply(dpy, (xReply *) &rep, 0, xTrue)) {
		UnlockDisplay(dpy);
		SyncHandle();
		return 0;
		}
	UnlockDisplay(dpy);
	SyncHandle();
	if (rep.data00) {
		if (dga_winlist_add(rep.data00, dpy, win) == 0) {
			XDgaUnGrabWindow(dpy, win);
			return 0;
			}
		}
	return rep.data00;
#endif /* SERVER_DGA */
}

int
XDgaUnGrabWindow(dpy, win)
Display *dpy;
Window win;
{
#ifdef SERVER_DGA
    WindowPtr pWin = (WindowPtr)LookupIDByType(win, RT_WINDOW);
    int val;

    if (!pWin) 
        return (BadCookie);
    if (((DrawablePtr)pWin)->type == DRAWABLE_PIXMAP) 
        return (BadCookie);
    val = DgaWgUngrab(pWin, NEW);

    if (val) {
        if (dga_winlist_free(dpy, win) == 0)
            return 0;
    }
    return val;
#else
	xResourceReq		*req;
	xGenericReply		rep;
	struct dga_extinfo      *extinfop;

	if ((extinfop = lookup_dga_ext(dpy)) == NULL)
		return 0;
	LockDisplay(dpy);
	GetResReq(DGA, win, req);
	req->reqType = extinfop->major_opcode;
	req->pad = (extinfop->protocol_major_version >= 2) ?
	    X_DgaUnGrabWindow : X_DgaUnGrabWindow_Old;
	if (!_XReply(dpy, (xReply *) &rep, 0, xTrue)) {
		UnlockDisplay(dpy);
		SyncHandle();
		return 0;
		}
	UnlockDisplay(dpy);
	SyncHandle();
	if (rep.data00) {
		if (dga_winlist_free(dpy, win) == 0)
			return 0;
		}
	return rep.data00;		/* Status */
#endif /* SERVER_DGA */
}


#ifndef SERVER_DGA
Dga_token 
XDgaGrabColormap(dpy, cmap)
Display		*dpy;
Colormap	cmap;
{
	xResourceReq	*req;
	xGenericReply		rep;
	struct dga_extinfo	*extinfop;

#ifdef MT
	mutex_lock(&dgaGlobalMutex);
#endif
	if ((extinfop = init_dga_ext(dpy)) == NULL) {
#ifdef MT
		mutex_unlock(&dgaGlobalMutex);
#endif
		return 0;
	}
	LockDisplay(dpy);
	GetResReq(DGA, cmap, req);
	req->reqType = extinfop->major_opcode;
	req->pad = (extinfop->protocol_major_version >= 3) ?
	    X_DgaGrabColormap : X_DgaGrabColormap_Old;
	if (!_XReply(dpy, (xReply *) &rep, 0, xTrue)) {
		UnlockDisplay(dpy);
		SyncHandle();
#ifdef MT
		mutex_unlock(&dgaGlobalMutex);
#endif
		return 0;
		}
	UnlockDisplay(dpy);
	SyncHandle();
#ifdef MT
	mutex_unlock(&dgaGlobalMutex);
#endif
	return rep.data00;
}

int
XDgaUnGrabColormap(dpy, cmap)
Display		*dpy;
Colormap	cmap;
{
	xResourceReq *req;
	xGenericReply rep;
	struct dga_extinfo	*extinfop;

#ifdef MT
	mutex_lock(&dgaGlobalMutex);
#endif
	if ((extinfop = lookup_dga_ext(dpy)) == NULL) {
#ifdef MT
		mutex_unlock(&dgaGlobalMutex);
#endif
		return 0;
	}
	LockDisplay(dpy);
	GetResReq(DGA, cmap, req);
	req->reqType = extinfop->major_opcode;
	req->pad = (extinfop->protocol_major_version >= 3) ?
	    X_DgaUnGrabColormap : X_DgaUnGrabColormap_Old;
	if (!_XReply(dpy, (xReply *) &rep, 0, xTrue)) {
		UnlockDisplay(dpy);
		SyncHandle();
#ifdef MT
		mutex_unlock(&dgaGlobalMutex);
#endif
		return 0;
		}
	UnlockDisplay(dpy);
	SyncHandle();
#ifdef MT
	mutex_unlock(&dgaGlobalMutex);
#endif
	return rep.data00;		/* Status */
}
#endif /* SERVER_DGA */

int 
XDgaDrawGrabWids(dpy, drawid, nwids)
Display		*dpy;
Drawable 	drawid;
int			nwids;
{
#ifdef SERVER_DGA
    WindowPtr pWin = (WindowPtr)LookupIDByType(drawid, RT_WINDOW);

    if (!pWin) 
        return (BadCookie);
    if (((DrawablePtr)pWin)->type == DRAWABLE_PIXMAP) 
        return (BadCookie);
    return(DgaWidGrab(pWin, nwids));
#else
	xDGAReq			*req;
	xGenericReply		rep;
	struct dga_extinfo	*extinfop;

#ifdef MT
	mutex_lock(&dgaGlobalMutex);
#endif
	if (((extinfop = lookup_dga_ext(dpy)) == NULL) ||
	    (extinfop->protocol_major_version < 2)) {
#ifdef MT
		mutex_unlock(&dgaGlobalMutex);
#endif
		return 0;
	}
	LockDisplay(dpy);
	GetReq(DGA, req);
	req->reqType = extinfop->major_opcode;
	req->pad = X_DgaGrabWids;
	req->id = drawid;
	req->number_objects = nwids;
	if (!_XReply(dpy, (xReply *) &rep, 0, xTrue)) {
		UnlockDisplay(dpy);
		SyncHandle();
#ifdef MT
		mutex_unlock(&dgaGlobalMutex);
#endif
		return 0;
		}
	UnlockDisplay(dpy);
	SyncHandle();
#ifdef MT
	mutex_unlock(&dgaGlobalMutex);
#endif
	return rep.data00;
#endif /* SERVER_DGA */
}

int 
XDgaGrabWids(dpy, win, nwids)
Display	*dpy;
Window 	win;
int			nwids;
{
    return (XDgaDrawGrabWids(dpy, (Drawable)win, nwids));
}

int 
XDgaDrawGrabFCS(dpy, drawid, nfcs)
Display		*dpy;
Drawable	drawid;
int			nfcs;
{
#ifdef SERVER_DGA
    WindowPtr pWin = (WindowPtr)LookupIDByType(drawid, RT_WINDOW);

    if (!pWin) 
        return (BadCookie);
    if (((DrawablePtr)pWin)->type == DRAWABLE_PIXMAP) 
        return (BadCookie);
    /* When OWGX supports PIXMAPS, can be reomoved */
    return(DgaFcsGrab(pWin, nfcs));
#else
	xDGAReq			*req;
	xGenericReply		rep;
	struct dga_extinfo	*extinfop;

#ifdef MT
	mutex_lock(&dgaGlobalMutex);
#endif
	if (((extinfop = lookup_dga_ext(dpy)) == NULL) ||
	    (extinfop->protocol_major_version < 2)) {
#ifdef MT
		mutex_unlock(&dgaGlobalMutex);
#endif
		return 0;
	}
	LockDisplay(dpy);
	GetReq(DGA, req);
	req->reqType = extinfop->major_opcode;
	req->pad = X_DgaGrabFCS;
	req->id = drawid;
	req->number_objects = nfcs;
	if (!_XReply(dpy, (xReply *) &rep, 0, xTrue)) {
		UnlockDisplay(dpy);
		SyncHandle();
#ifdef MT
		mutex_unlock(&dgaGlobalMutex);
#endif
		return 0;
		}
	UnlockDisplay(dpy);
	SyncHandle();
#ifdef MT
	mutex_unlock(&dgaGlobalMutex);
#endif
	return(rep.data00);
#endif /* SERVER_DGA */
}

int 
XDgaGrabFCS(dpy, win, nfcs)
Display		*dpy;
Window		win;
int			nfcs;
{
    return (XDgaDrawGrabFCS(dpy, (Drawable)win, nfcs));
}

int 
XDgaDrawGrabZbuf(dpy, drawid, nzbuftype)
Display		*dpy;
Drawable	drawid;
int			nzbuftype;
{
#ifdef SERVER_DGA
    WindowPtr pWin = (WindowPtr)LookupIDByType(drawid, RT_WINDOW);

    if (!pWin) 
        return (BadCookie);
    if (((DrawablePtr)pWin)->type == DRAWABLE_PIXMAP) 
        return (BadCookie);
    return(DgaZbufGrab(pWin, nzbuftype));
#else
	xDGAReq *req;
	xGenericReply rep;
	struct dga_extinfo	*extinfop;

#ifdef MT
	mutex_lock(&dgaGlobalMutex);
#endif
	if (((extinfop = lookup_dga_ext(dpy)) == NULL) ||
	    (extinfop->protocol_major_version < 2)) {
#ifdef MT
		mutex_unlock(&dgaGlobalMutex);
#endif
		return 0;
	}
	LockDisplay(dpy);
	GetReq(DGA, req);
	req->reqType = extinfop->major_opcode;
	req->pad = X_DgaGrabZbuf;
	req->id = drawid;
	req->number_objects = nzbuftype;
	if (!_XReply(dpy, (xReply *) &rep, 0, xTrue)) {
		UnlockDisplay(dpy);
		SyncHandle();
#ifdef MT
		mutex_unlock(&dgaGlobalMutex);
#endif
		return 0;
		}
	UnlockDisplay(dpy);
	SyncHandle();
#ifdef MT
	mutex_unlock(&dgaGlobalMutex);
#endif
	return(rep.data00);
#endif /* SERVER_DGA */
}

int 
XDgaGrabZbuf(dpy, win, nzbuftype)
Display		*dpy;
Window		win;
int			nzbuftype;
{
    return (XDgaDrawGrabZbuf(dpy, (Drawable)win, nzbuftype));
}

int 
XDgaDrawGrabStereo(dpy, drawid, st_mode)
Display		*dpy;
Drawable	drawid;
int			st_mode;
{
#ifdef SERVER_DGA
    WindowPtr pWin = (WindowPtr)LookupIDByType(drawid, RT_WINDOW);
 
    if (!pWin) 
        return (BadCookie);
    if (((DrawablePtr)pWin)->type == DRAWABLE_PIXMAP) 
        return (BadCookie);
    return(DgaStereoGrab(pWin, st_mode));
#else
	xDGAReq			*req;
	xGenericReply		rep;
	struct dga_extinfo	*extinfop;

#ifdef MT
	mutex_lock(&dgaGlobalMutex);
#endif
	if (((extinfop = lookup_dga_ext(dpy)) == NULL) ||
	    (extinfop->protocol_major_version < 2)) {
#ifdef MT
		mutex_unlock(&dgaGlobalMutex);
#endif
		return 0;
	}
	LockDisplay(dpy);
	GetReq(DGA, req);
	req->reqType = extinfop->major_opcode;
	req->pad = X_DgaGrabStereo;
	req->id = drawid;
	req->number_objects = st_mode;
	if (!_XReply(dpy, (xReply *) &rep, 0, xTrue)) {
		UnlockDisplay(dpy);
		SyncHandle();
#ifdef MT
		mutex_unlock(&dgaGlobalMutex);
#endif
		return 0;
		}
	UnlockDisplay(dpy);
	SyncHandle();
#ifdef MT
	mutex_unlock(&dgaGlobalMutex);
#endif
	return rep.data00;
#endif /* SERVER_DGA */
}

int 
XDgaGrabStereo(dpy, win, st_mode)
Display		*dpy;
Window		win;
int			st_mode;
{
    return (XDgaDrawGrabStereo(dpy, (Drawable)win, st_mode));
}

int
XDgaGrabABuffers(dpy, win, type, buffer_site)
Display        *dpy;
Window         win;
int                     type;
int                     buffer_site;
{
#ifdef SERVER_DGA
    WindowPtr pWin = (WindowPtr)LookupIDByType(win, RT_WINDOW);
 
    if (!pWin)
        return (BadCookie);
    if (((DrawablePtr)pWin)->type == DRAWABLE_PIXMAP)
        return (BadCookie);
    /* Some surf prep may be needed for mpg */
    return(DgaABuffersGrabInfo((DrawablePtr)pWin, type, buffer_site));
#else
        xDgaGrabABuffersReq    *req;
        xGenericReply           rep;
        struct dga_extinfo      *extinfop;
 
        if ((extinfop = lookup_dga_ext(dpy)) == NULL)
                return 0;
        if (extinfop->protocol_major_version < 2)
                return 0;
        LockDisplay(dpy);
        GetReq(DgaGrabABuffers, req);
        req->reqType = extinfop->major_opcode;
        req->pad = X_DgaGrabABuffers;
        req->id = win;
        req->type = type;
        req->buffer_site = buffer_site;
        if (!_XReply(dpy, (xReply *) &rep, 0, xTrue)) {
                UnlockDisplay(dpy);
                SyncHandle();
                return 0;
                }
        UnlockDisplay(dpy);
        SyncHandle();
        return rep.data00;
#endif /* SERVER_DGA */
}

int
XDgaUnGrabABuffers(dpy, win, type)
Display        *dpy;
Window         win;
int                     type;
{
#ifdef SERVER_DGA
    WindowPtr pWin = (WindowPtr)LookupIDByType(win, RT_WINDOW);
 
    if (!pWin)
        return (BadCookie);
    if (((DrawablePtr)pWin)->type == DRAWABLE_PIXMAP)
        return (BadCookie);
    return(DgaABuffersUngrabInfo((DrawablePtr)pWin, type));
#else
        xDgaGrabABuffersReq    *req;
        xGenericReply           rep;
        struct dga_extinfo      *extinfop;
 
        if ((extinfop = lookup_dga_ext(dpy)) == NULL)
                return 0;
        if (extinfop->protocol_major_version < 2)
                return 0;
        LockDisplay(dpy);
        GetReq(DgaGrabABuffers, req);
        req->reqType = extinfop->major_opcode;
        req->pad = X_DgaUnGrabABuffers;
        req->id = win;
        req->type = type;
        req->buffer_site = 0;
        if (!_XReply(dpy, (xReply *) &rep, 0, xTrue)) {
                UnlockDisplay(dpy);
                SyncHandle();
                return 0;
                }
        UnlockDisplay(dpy);
        SyncHandle();
        return rep.data00;
#endif /* SERVER_DGA */
}

int 
XDgaGrabBuffers(dpy, win, nbuffers)
Display		*dpy;
Window		win;
int			nbuffers;
{
#ifdef SERVER_DGA
    WindowPtr pWin = (WindowPtr)LookupIDByType(win, RT_WINDOW);
 
    if (!pWin) 
        return (BadCookie);
    if (((DrawablePtr)pWin)->type == DRAWABLE_PIXMAP) 
        return (BadCookie);
    /* Some surf prep may be needed for mpg */
    return(DgaBufGrab(pWin, nbuffers));
#else
	xDGAReq	*req;
	xGenericReply		rep;
	struct dga_extinfo	*extinfop;

	if ((extinfop = lookup_dga_ext(dpy)) == NULL)
		return 0;
	if (extinfop->protocol_major_version < 2)
		return 0;
	LockDisplay(dpy);
	GetReq(DGA, req);
	req->reqType = extinfop->major_opcode;
	req->pad = X_DgaGrabBuffers;
	req->id = win;
	req->number_objects = nbuffers;
	if (!_XReply(dpy, (xReply *) &rep, 0, xTrue)) {
		UnlockDisplay(dpy);
		SyncHandle();
		return 0;
		}
	UnlockDisplay(dpy);
	SyncHandle();
	return rep.data00;
#endif /* SERVER_DGA */
}


int
XDgaUnGrabBuffers(dpy, win)
Display		*dpy;
Window		win;
{
#ifdef SERVER_DGA
    WindowPtr pWin = (WindowPtr)LookupIDByType(win, RT_WINDOW);

    if (!pWin) 
        return (BadCookie);                               
    if (((DrawablePtr)pWin)->type == DRAWABLE_PIXMAP) 
        return (BadCookie);
    return(DgaBufUngrab(pWin));
#else
	xResourceReq		*req;
	xGenericReply		rep;
	struct dga_extinfo	*extinfop;

	if ((extinfop = lookup_dga_ext(dpy)) == NULL)
		return 0;
	if (extinfop->protocol_major_version < 2)
		return 0;
	LockDisplay(dpy);
	GetResReq(DGA, win, req);
	req->reqType = extinfop->major_opcode;
	req->pad = X_DgaUnGrabBuffers;
	if (!_XReply(dpy, (xReply *) &rep, 0, xTrue)) {
		UnlockDisplay(dpy);
		SyncHandle();
		return 0;
		}
	UnlockDisplay(dpy);
	SyncHandle();
	return rep.data00;
#endif /* SERVER_DGA */
}


int 
XDgaGrabRetainedWindow(dpy, win)
Display		*dpy;
Window		win;
{
#ifdef SERVER_DGA
    WindowPtr pWin = (WindowPtr)LookupIDByType(win, RT_WINDOW);
 
    if (!pWin) 
        return (BadCookie);
    if (((DrawablePtr)pWin)->type == DRAWABLE_PIXMAP) 
        return (BadCookie);
    return(DgaSharedRetained(pWin, 1, win));
#else
	xResourceReq	*req;
	xGenericReply		rep;
	struct dga_extinfo	*extinfop;

	if ((extinfop = lookup_dga_ext(dpy)) == NULL)
		return 0;
	if (extinfop->protocol_major_version < 3)
		return 0;
	LockDisplay(dpy);
	GetResReq(DGA, win, req);
	req->reqType = extinfop->major_opcode;
	req->pad = X_DgaGrabRetained;
	if (!_XReply(dpy, (xReply *) &rep, 0, xTrue)) {
		UnlockDisplay(dpy);
		SyncHandle();
		return 0;
		}
	UnlockDisplay(dpy);
	SyncHandle();
	return rep.data00;
#endif /* SERVER_DGA */
}


int
XDgaUnGrabRetainedWindow(dpy, win)
Display		*dpy;
Window		win;
{
#ifdef SERVER_DGA
    WindowPtr pWin = (WindowPtr)LookupIDByType(win, RT_WINDOW);
 
    if (!pWin) 
        return (BadCookie);
    if (((DrawablePtr)pWin)->type == DRAWABLE_PIXMAP) 
        return (BadCookie);
    return(DgaSharedRetained(pWin, 0, win));
#else
	xResourceReq		*req;
	xGenericReply		rep;
	struct dga_extinfo	*extinfop;

	if ((extinfop = lookup_dga_ext(dpy)) == NULL)
		return 0;
	if (extinfop->protocol_major_version < 3)
		return 0;
	LockDisplay(dpy);
	GetResReq(DGA, win, req);
	req->reqType = extinfop->major_opcode;
	req->pad = X_DgaUnGrabRetained;
	if (!_XReply(dpy, (xReply *) &rep, 0, xTrue)) {
		UnlockDisplay(dpy);
		SyncHandle();
		return 0;
		}
	UnlockDisplay(dpy);
	SyncHandle();
	return rep.data00; /* Status */
#endif /* SERVER_DGA */
}


int
XDgaGetRetainedPath(dpy, win, path)
Display		*dpy;
Window		win;
char			*path;
{
#ifdef SERVER_DGA
    extern char *DgaSharedRetainedPath;
 
    if (DgaSharedRetainedPath)
        strcpy((char *)path, (char *)DgaSharedRetainedPath);
    return 1;
#else
	xResourceReq		*req;
	xDGARtndPathReply	rep;
	struct dga_extinfo	*extinfop;

	if ((extinfop = lookup_dga_ext(dpy)) == NULL)
		return 0;
	if (extinfop->protocol_major_version < 3)
		return 0;
	LockDisplay(dpy);
	GetResReq(DGA, win, req);
	req->reqType = extinfop->major_opcode;
	req->pad = X_DgaGetRetainedPath;
	if (!_XReply(dpy, (xReply *) &rep,
		   (SIZEOF(xDGARtndPathReply) - SIZEOF(xReply)) >> 2, xFalse)) {
		UnlockDisplay(dpy);
		SyncHandle();
		return 0;
		}
	UnlockDisplay(dpy);
	SyncHandle();
	strcpy(path, (char *) rep.path);
	return 1;
#endif /* SERVER_DGA */
}


int
XDgaQueryVersion(dpy, major_versionp, minor_versionp)
Display	*dpy;
int	*major_versionp,
	*minor_versionp;
{
#ifdef SERVER_DGA
    *major_versionp = SUN_DGA_MAJOR_VERSION;
    *minor_versionp = SUN_DGA_MINOR_VERSION;
    return(1);
#else
	xDgaQueryVersionReply rep;
	xDgaQueryVersionReq *req;
	int opcode, tmp;

	if (XQueryExtension(dpy, "SUN_DGA", &opcode, &tmp, &tmp) == 0)
		return 0;

	LockDisplay(dpy);
	GetReq(DgaQueryVersion, req);
	req->reqType = opcode;
	req->dgaReqType = X_DgaQueryVersion;
	if (!_XReply(dpy, (xReply *) & rep, 0, xTrue)) {
		UnlockDisplay(dpy);
		SyncHandle();
		return 0;
		}
	*major_versionp = rep.majorVersion;
	*minor_versionp = rep.minorVersion;
	UnlockDisplay(dpy);
	SyncHandle();
	return 1;
#endif /* SERVER_DGA */
}


Dga_token 
XDgaGrabPixmap(dpy, d)
Display		*dpy;
Pixmap		d;
{
#ifdef SERVER_DGA
    int val;
    PixmapPtr pPix = (PixmapPtr)LookupIDByType(d, RT_PIXMAP);
    if (!pPix)
        return (BadCookie);

    if (((DrawablePtr)pPix)->type == DRAWABLE_WINDOW)
        return (BadCookie);
    val = DgaInitSharedPixmap(pPix, NEW);

    if (val) {
        if (dga_pixlist_add(val, dpy, d) == 0) {
            XDgaUnGrabPixmap(dpy, d);
            return 0;
        }
    }    
    return val;
#else
	xResourceReq		*req;
	xGenericReply		rep;
	struct dga_extinfo	*extinfop;

	if ((extinfop = init_dga_ext(dpy)) == NULL)
		return 0;
	if (extinfop->protocol_major_version < 3)
		return 0;
	LockDisplay(dpy);
	GetResReq(DGA, d, req);
	req->reqType = extinfop->major_opcode;
	req->pad = X_DgaGrabPixmap;
	if (!_XReply(dpy, (xReply *) &rep, 0, xTrue)) {
		UnlockDisplay(dpy);
		SyncHandle();
		return 0;
		}
	UnlockDisplay(dpy);
	SyncHandle();
	if (rep.data00) {
		if (dga_pixlist_add(rep.data00, dpy, d) == 0) {
			XDgaUnGrabPixmap(dpy, d);
			return 0;
			}
		}
	return rep.data00;
#endif /* SERVER_DGA */
}


int
XDgaUnGrabPixmap(dpy, d)
Display		*dpy;
Pixmap		d;
{
#ifdef SERVER_DGA
    PixmapPtr pPix = (PixmapPtr)LookupIDByType(d, RT_PIXMAP);
    int val;

    if (!pPix) 
        return (BadCookie);
    if (((DrawablePtr)pPix)->type == DRAWABLE_WINDOW) 
        return (BadCookie);
    val = DgaDestroySharedPixmap(pPix);

    if (val) {
        if (dga_pixlist_free(dpy, d) == 0)
            return 0;
    }
    return val;
#else
	xResourceReq		*req;
	xGenericReply		rep;
	struct dga_extinfo	*extinfop;

	if ((extinfop = lookup_dga_ext(dpy)) == NULL)
		return 0;
	if (extinfop->protocol_major_version < 3)
		return 0;
	LockDisplay(dpy);
	GetResReq(DGA, d, req);
	req->reqType = extinfop->major_opcode;
	req->pad = X_DgaUnGrabPixmap;
	if (!_XReply(dpy, (xReply *) &rep, 0, xTrue)) {
		UnlockDisplay(dpy);
		SyncHandle();
		return 0;
		}
	UnlockDisplay(dpy);
	SyncHandle();
	return rep.data00; /* Status */
#endif /* SERVER_DGA */
}


static Dga_token
dgai_grabDrawRequest (Display *dpy, Drawable drawid, int *drawType)
{
#ifdef SERVER_DGA
    DrawablePtr pDraw = (DrawablePtr)LookupIDByClass(drawid, RC_DRAWABLE);

    if (!pDraw)
        return(BadCookie);
    return(DgaDrawGrab(drawid, pDraw, NEW, drawType));
#else
    xResourceReq		*req;
    xGenericReply		rep;
    struct dga_extinfo		*extinfop;
    
    if ((extinfop = init_dga_ext(dpy)) == NULL)
	return 0;
    if (extinfop->protocol_major_version < 3)
      return 0;
    LockDisplay(dpy);
    GetResReq(DGA, drawid, req);
    req->reqType = extinfop->major_opcode;
    req->pad = X_DgaGrabDrawable;
    if (!_XReply(dpy, (xReply *) &rep, 0, xTrue)) {
	UnlockDisplay(dpy);
	SyncHandle();
	return 0;
    }
    UnlockDisplay(dpy);
    SyncHandle();
    
    /* 
     ** data00 is the opaque token identifying the drawable shared file.  
     ** data01 is the type of the drawable: window (0) or pixmap (1),
     ** (Note: an attempt to grab a multibuffer drawable XID will fail)
     */
    if (rep.data00) {
	*drawType = rep.data01;
    }

    return (rep.data00);    
#endif /* SERVER_DGA */
}

static int
dgai_ungrabDrawRequest (Display *dpy, Drawable drawid)
{
#ifdef SERVER_DGA
    DrawablePtr pDraw = (DrawablePtr)LookupIDByClass(drawid, RC_DRAWABLE);

    if (!pDraw)
        return(BadCookie);
    return(DgaDrawUngrab(drawid, pDraw, NEW));
#else
    xResourceReq		*req;
    xGenericReply		rep;
    struct dga_extinfo		*extinfop;

    if ((extinfop = lookup_dga_ext(dpy)) == NULL)
      return 0;
    if (extinfop->protocol_major_version < 3)
      return 0;
    LockDisplay(dpy);
    GetResReq(DGA, drawid, req);
    req->reqType = extinfop->major_opcode;
    req->pad = X_DgaUnGrabDrawable;
    if (!_XReply(dpy, (xReply *) &rep, 0, xTrue)) {
	UnlockDisplay(dpy);
	SyncHandle();
	return 0;
    }
    UnlockDisplay(dpy);
    SyncHandle();
    return rep.data00; /* Status */
#endif /* SERVER_DGA */
}


Dga_drawable
XDgaGrabDrawable(Display *dpy, Drawable drawid)
{
    Dga_token   token;
    int		drawType;

#ifdef MT
    mutex_lock(&dgaGlobalMutex);
#endif
    if (!(token = dgai_grabDrawRequest(dpy, drawid, &drawType))) {
#ifdef MT
	mutex_unlock(&dgaGlobalMutex);
#endif
	return (NULL);
    }

    switch (drawType) {

    case DGA_PROTO_OVERLAY:
    case DGA_PROTO_WINDOW: {
	_Dga_window	dgawin;

	if (!dga_winlist_add(token, dpy, (Window)drawid)) {
	    goto Bad;
	}
        if (!(dgawin = (_Dga_window) dgai_win_grab_common(dpy, -1, token, 1))) {            goto Bad;
        }
	dgawin->w_dpy = dpy;
	dgawin->w_id = (Window) drawid;
	if (dgawin->isOverlay = (drawType == DGA_PROTO_OVERLAY)) {
	    dgawin->s_ovlstate_p = &((WXINFO *)dgawin->w_info)->w_ovlstate;
	    dgawin->s_ovlshapevalid_p =
		&((WXINFO *)dgawin->w_info)->w_ovlshapevalid;
		dgawin->ovlStateNotifyFunc = NULL;
	}
#ifdef MT
	mutex_unlock(&dgaGlobalMutex);
#endif
	return ((Dga_drawable)dgawin);
    }

    case DGA_PROTO_PIXMAP: {
	_Dga_pixmap	dgapix;

	if (!dga_pixlist_add(token, dpy, (Pixmap)drawid)) {
	    goto Bad;
	}
	if (!(dgapix = (_Dga_pixmap) dga_pix_grab(token, (Pixmap)drawid))) {
	    goto Bad;
	}
	dgapix->p_dpy = dpy;
	dgapix->p_id = (Pixmap) drawid;
#ifdef MT
	mutex_unlock(&dgaGlobalMutex);
#endif
	return ((Dga_drawable)dgapix);
    }

    }

Bad:
    (void) dgai_ungrabDrawRequest(dpy, drawid);
#ifdef MT
    mutex_unlock(&dgaGlobalMutex);
#endif
    return (NULL);
}



int
XDgaUnGrabDrawable(Dga_drawable dgadraw)
{
    Drawable  drawid = dga_draw_id(dgadraw);
    Display   *dpy = dga_draw_display(dgadraw);
    int       type = dga_draw_type(dgadraw);
    int       status;

    if (dpy == NULL)
	return BadDrawable;

#ifdef MT
    mutex_lock(&dgaGlobalMutex);
#endif
    switch (type) {
    case DGA_DRAW_WINDOW: 
    case DGA_DRAW_OVERLAY: 
	dgai_win_ungrab_common((Dga_window)dgadraw, -1,1);
	break;
    case DGA_DRAW_PIXMAP:
	dga_pix_ungrab((Dga_pixmap)dgadraw);
	break;
    }

    status = dgai_ungrabDrawRequest(dpy, drawid);
#ifdef MT
    mutex_unlock(&dgaGlobalMutex);
#endif
    return (status);
}



static struct dga_xwinrec *dga_xwinlist = NULL;

static int
dga_winlist_add(token, dpy, win)
Dga_token		token;
Display		*dpy;
Window		win;
{
	struct dga_xwinrec	*recp;
	Display			*listdpy;
	Window			listwin;

	while (recp =
	    (struct dga_xwinrec *) _dga_is_X_window(token,&listdpy,&listwin)) {
		if ((win == listwin) && (dpy == listdpy)) {
			recp->refcnt += 1;
			return 1; /* already in list */
			}
		dga_winlist_free(listdpy, listwin); /* remove bogus entry from list */
		}
	recp = (struct dga_xwinrec *) malloc(sizeof(struct dga_xwinrec));
	if (recp == NULL)
		return 0;
	recp->next = dga_xwinlist;
	dga_xwinlist = recp;
	recp->token = token;
	recp->dpy = dpy;
	recp->win = win;
	recp->refcnt = 1;
	return 1;
}

/*
 * Free dga_xwinrec structure for a particular window and display.
 * If win is NULL free all entries on list for this display.
 */
static int
dga_winlist_free(dpy, win)
Display		*dpy;
Window		win;
{
	struct dga_xwinrec	*recp, **prevp;
	int			match = 0;

	prevp = &dga_xwinlist;
	recp = dga_xwinlist;
	while (recp) {
		if (recp->dpy == dpy) {
			if (win == NULL) {
				*prevp = recp->next;
				free(recp);
				match = 1;
				}
			else if (recp->win == win) {
				if (--recp->refcnt == 0) {
					*prevp = recp->next;
					free(recp);
					}
				return 1;
				}
			else {
				prevp = &recp->next;
				}
			}
		else {
			prevp = &recp->next;
			}
		recp = *prevp;
		}
	return (match);
}


void *
_dga_is_X_window(token, dpyp, winp)
Dga_token		token;
Display		**dpyp;
Window		*winp;
{
	struct dga_xwinrec	*recp = dga_xwinlist;

	while (recp) {
		if (recp->token == token) {
			*dpyp = recp->dpy;
			*winp = recp->win;
			return ((void *) recp);
			}
		recp = recp->next;
		}
	return 0;
}

static struct dga_xpixrec *dga_xpixlist = NULL;

/* REMIND DARYL:  This routine is used to clean up "bogus" entries from
 * list. Shouldn't that be done in Ungrab??? */
int
dga_pixlist_add(token, dpy, pix)
Dga_token       token;
Display    *dpy;
Pixmap     pix;
{
    struct dga_xpixrec  *recp;
    Display         *listdpy;

    if (recp = (struct dga_xpixrec *) _dga_is_X_pixmap(pix, &listdpy)) {
        if (dpy == listdpy) {
            recp->refcnt += 1;
            return 1; /* already in list */
        }
        dga_pixlist_free(dpy, pix); /* remove bogus entry from list */
    }
    recp = (struct dga_xpixrec *) malloc(sizeof(struct dga_xpixrec));
    if (recp == NULL)
        return 0;
    recp->next = dga_xpixlist;
    dga_xpixlist = recp;
    recp->token = token;
    recp->dpy = dpy;
    recp->pix = pix;
    recp->refcnt = 1;
    return 1;
}

static int
dga_pixlist_free(dpy, pix)
Display    *dpy;
Pixmap     pix;
{
    struct dga_xpixrec  *recp, **prevp;
    int         match = 0;
 
    prevp = &dga_xpixlist;
    recp = dga_xpixlist;
    while (recp) {
        if (recp->dpy == dpy) {
            if (pix == NULL) {
                *prevp = recp->next;
                free(recp);
                match = 1;
                }
            else if (recp->pix == pix) {
                if (--recp->refcnt == 0) {
                    *prevp = recp->next;
                    free(recp);
                    }
                return 1;
                }
            else {
                prevp = &recp->next;
                }
            }
        else {
            prevp = &recp->next;
            }
        recp = *prevp;
        }
    return (match);
}
 

void *
_dga_is_X_pixmap(pix, dpyp)
Pixmap 	   pix;
Display    **dpyp;
{
    struct dga_xpixrec  *recp = dga_xpixlist;

    while (recp) {
        if (recp->pix == pix) {
	    *dpyp = recp->dpy;
            return ((void *) recp);
	}
        recp = recp->next;
        }
    return 0;
}

#ifndef SERVER_DGA

/************************************

Addition to DGA for Xinerama extension.

	This code allows the client to mine out
	the window ID's that would normaly be 
	hidden from the user in Xinerama mode.

	Xinerama keeps a list of WIDs that are 
	connected to a virtual WID that the user
	gets to handle. 

**************************************/


BOOL 
XDgaGetXineramaInfo(dpy , VirtualWID, info )
Display *dpy;
XID	VirtualWID;
XineramaInfo *info;
{
register xDgaXineramaInfoReq *req;
xDgaXineramaInfoReply *rep;
struct dga_extinfo      *extinfop;

    if ((extinfop = init_dga_ext(dpy)) == NULL)
        return 0;

    rep = malloc(sizeof(xDgaXineramaInfoReply));

    LockDisplay(dpy);
    GetReq(DgaXineramaInfo, req);
    req->reqType = extinfop->major_opcode;
    req->xdgaReqType = X_DgaXineramaInfo;
    req->visual = VirtualWID;

    if (!_XReply(dpy, (xReply *)rep, (sizeof(xDgaXineramaInfoReply)-32) >> 2, 
	xFalse)) 
    {
        UnlockDisplay(dpy);
        SyncHandle();
	Xfree(rep);
        return NULL;
    }
    info->wid = VirtualWID;
    memcpy(&info->subs[0],&rep->subs[0],(MAXSCREEN-1) * sizeof(SubWID));
    UnlockDisplay(dpy);
    SyncHandle();
    free(rep);
    return 1;
}
#endif
