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
 * cmap_grab.c - the client side code for DGA colormap grabber
 */


/*
 *
 *	Shared colormap synchronization routines.
 *
 *	Client side
 *
 *
 * Functions:
 *
 *    Dga_cmap
 *    dga_cm_grab(devfd, filesuffix)
 *		int		devfd ;
 *		unsigned long	filesuffix ;
 *
 *	Grab a colormap.  'filesuffix' is the handle returned by
 *	XDgaGrabColormap.  'devfd' is the file descriptor of the frame buffer
 *	if any, -1 otherwise.  If you specify -1, dga_cm_grab will open
 *	the frame buffer.  The frame buffer fd may be inquired from
 *	the returned dga_cmap structure.
 *
 *	Returns a pointer to a dga_cmap structure on success,
 *	NULL on failure.
 *
 *
 *    void
 *    dga_cm_ungrab(cginfo,cflag)
 *		Dga_cmap	cginfo ;
 *		int		cflag ;
 *
 *	Release a colormap.  All resources allocated by dga_cm_grab are
 *	freed.  The application should call XDgaUnGrabColormap after calling
 *	dga_cm_ungrab() so that the server may free the colormap info page
 *	at the other end.
 *
 *	if cflag is nonzero, the framebuffr fd described in the info page
 *	is also closed.  The info page is invalid after this call and
 *	references to it will probably result in a SIGSEGV.
 *
 *
 *
 *
 *    void
 *    dga_cm_get(cginfo,index,count, red,green,blue)
 *		Dga_cmap	cginfo ;
 *		int		index, count ;
 *		u_char		*red, *green, *blue ;
 *
 *	Read colormap values and return them to the application.
 *
 *
 *    void
 *    dga_cm_put(cginfo,index,count, red,green,blue)
 *		Dga_cmap	cginfo ;
 *		int		index, count ;
 *		u_char		*red, *green, *blue ;
 *
 *	Write colormap to hardware if colormap is installed, otherwise
 *	save them in shared memory.
 *
 *
 *
 *    void
 *    dga_cm_write(cginfo,index,count, red,green,blue, putfunc)
 *      Dga_cmap    cginfo ;
 *      int     index, count ;
 *      u_char      *red, *green, *blue ;
 * 		int		(*putfunc)();
 *
 *  Write colormap to hardware by calling the user supplied putfunc 
 *  if colormap is installed, otherwise save them in shared memory.
 * 
 **    void
 *    dga_cm_read(cginfo,index,count, red,green,blue)
 *      Dga_cmap    cginfo ;
 *      int     index, count ;
 *      u_char      *red, *green, *blue ;
 * 		int		(*putfunc)();
 *
 *	Read colormap values and return them to the application
 *
 *	int
 *	dga_cm_get_devfd(cginfo)
 *	Dga_cmap cginfo;
 *
 *	Return the fd of the device associated with cginfo
 *
 *	void
 *	dga_cm_get_devinfo(cginfo)
 *	Dga_cmap cginfo;
 *
 *	Returns pointer to the device specific info associated with
 *	cginfo. Used to communicate info bet server and client
 *
 *	void
 *	dga_cm_set_client_infop(cginfo, client_info_ptr)
 *	Dga_cmap cginfo;
 *	void*  client_info_ptr;
 *
 *	Sets pointer to client specificr-data associated with cginfo.
 *
 *	void *
 *	dga_cm_get_client_infop(cginfo)
 *	Dga_cmap cginfo;
 *
 *	Returns the client specific data pointer associated with cginfo

 ****/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#include <errno.h>
#include <X11/Xlib.h>

#ifdef SVR4
#include <sys/fbio.h>
#ifdef SUNWINDOWS	/* see note later */
#include <sys/cms.h>
#include <sys/rect.h>
#include <sys/win_screen.h>
#include <sys/win_input.h>
#include <sys/win_ioctl.h>
#endif /* SUNWINDOWS */
#include <unistd.h>
#else
#include <sun/fbio.h>
#include <sunwindow/cms.h>
#include <sunwindow/rect.h>
#include <sunwindow/win_screen.h>
#include <sunwindow/win_input.h>
#include <sunwindow/win_ioctl.h>
#endif

#ifndef FB_CLUTPOST
struct  fb_clut {
        unsigned int    flags;          /* flags                        */
        int             index;          /* CLUT id                      */
        int             offset;         /* offset within the CLUT       */
        int             count;          /* nbr of entries to be posted  */
        unsigned char   *red;           /* pointer to red table         */
        unsigned char   *green;         /* pointer to green table       */
        unsigned char   *blue;          /* pointer to blue table        */
};

#ifdef SVR4
#define FB_CLUTPOST	(('t' << 8) | 4)
#else
#define FB_CLUTPOST     _IOW(t,   4, struct fb_clut)
#endif
#endif


#include "cmap_grab.h"


/* externs */
#if 0
extern	char	*_SysErrorMsg[] ;
#endif

extern int _dga_winlockat(u_long cookie, int **lockp, int **unlockp);
extern int _dga_winlockdt(int *lockp, int *unlockp);

#define	GRABFILE	"/tmp/cm"
#define	NDIGITS		8

#define	MINSHMEMSIZE	(8*1024)
#define	CG_PAGESZ	(8*1024)

static	Dga_cmap	errret() ;
static	int		sunwindows_open();
static	void		sunwindows_close();

static	Dga_cmap	grabbed_list = NULL ;

static	int		cleanup_lockpages();

/*ARGSUSED*/
Dga_cmap
dga_cm_grab(fd, filesuffix)
int		fd ;
Dga_token	filesuffix ;
{
    Grabbedcmap	*infop, tmp ;
    _Dga_cmap	cmap_grab ;
    char		fn[sizeof(GRABFILE)+NDIGITS+1];
    char		*lock, *unlock ;
    int		lockfd,			/* lock device */
		devfd,			/* framebuffer */
		infofd,			/* shared memory file */
		sunwindows_def_fd,	/* /dev/winXX fd */
		sunwindows_inst_fd ;	/* /dev/winXX fd */
    int		locktype = 0 ;		/* use /dev/winlock */
    int		cflag = 0 ;		/* close devfd */
    u_long	cookie;
    int		cmaplen ;
    int		filelen ;
    int		ok;
    struct fbtype   fbd_type;

#ifdef MT
    mutex_lock(&dgaGlobalMutex);
#endif
    /* first and foremost, is this a nested grab? */
    for(cmap_grab = grabbed_list; cmap_grab != NULL;
		     cmap_grab = cmap_grab->cm_next) {
    	if (cmap_grab->cm_token == filesuffix) {
    		++cmap_grab->cm_grab_count;
#ifdef MT
		mutex_unlock(&dgaGlobalMutex);
#endif
    		return cmap_grab;
    	}
    }

    if((cmap_grab = (_Dga_cmap)calloc(1,sizeof(struct dga_cmap))) == NULL ) {
#ifdef MT
	    mutex_unlock(&dgaGlobalMutex);
#endif
	    return errret("malloc failed", fn) ;
    }

    cmap_grab->cm_infofd =
    cmap_grab->cm_devfd =
    cmap_grab->cm_lockfd =
    cmap_grab->cm_sunwindows_def_fd =
    cmap_grab->cm_sunwindows_inst_fd = -1 ;
    cmap_grab->cm_grab_count = 1 ;
    cmap_grab->cm_next = grabbed_list ;
    grabbed_list = cmap_grab ;

    /* open the file.  Read in enough data to find out long it is. */

    sprintf(fn, "%s%08x", GRABFILE, filesuffix) ;

    if ((infofd = open(fn,O_RDWR,0666))<0) {
	cleanup_lockpages(cmap_grab,0,0,0) ;
#ifdef MT
	mutex_unlock(&dgaGlobalMutex);
#endif
	return errret("can't open info page, ", fn) ;
    }

    if( read(infofd, &tmp, sizeof(tmp)) != sizeof(tmp) ) {
	(void) close(infofd) ;
	cleanup_lockpages(cmap_grab,0,0,0) ;
#ifdef MT
	mutex_unlock(&dgaGlobalMutex);
#endif
	return errret("info page too short", fn) ;
    }

    if( tmp.cm_magic != CMMAGIC ) {
	(void) close(infofd) ;
	cleanup_lockpages(cmap_grab,0,0,0) ;
#ifdef MT
	mutex_unlock(&dgaGlobalMutex);
#endif
	return errret("invalid magic number", fn) ;
    }

    cookie = tmp.cm_cookie;
    cmaplen = tmp.cm_reallen ;

    filelen = tmp.cm_shadowofs + 3*cmaplen*sizeof(short) + 4*cmaplen;

    /* map the colormap info area */

    infop = (Grabbedcmap *)mmap(0,
			filelen,
			PROT_READ|PROT_WRITE,
			MAP_SHARED,
			infofd,
			(off_t)0);

    /* we're all done with infofd now.  If the info file becomes
     * subject to growth later, we'll want to keep it open.
     */
    (void) close(infofd) ;
    cmap_grab->cm_infofd = -1 ;

    if (infop == (Grabbedcmap *)-1) {
	cleanup_lockpages(cmap_grab,0,filelen,0) ;
#ifdef MT
	mutex_unlock(&dgaGlobalMutex);
#endif
        return errret("can't map info page", fn) ;
    }
    cmap_grab->cm_info = (void *) infop ;


    /* Open framebuffer if not provided by caller */

    if( fd == -1 ) {
	devfd = open(infop->cm_devname, O_RDWR,0666) ;
	if( devfd < 0 ) {
#ifdef	DEBUG
	    fprintf(stderr, "wx_cm_grab: cannot open %s, %s\n",
		infop->cm_devname, strerror(errno)) ;
#endif	/* DEBUG */
	    cleanup_lockpages(cmap_grab,0,filelen,0) ;
#ifdef MT
	    mutex_unlock(&dgaGlobalMutex);
#endif
	    return NULL ;
	}
	cflag = 1 ;
    } else
	  devfd = fd ;

    cmap_grab->cm_devfd = devfd ;

    locktype = infop->cm_version >= 1 ? infop->cm_locktype : CM_LOCKDEV ;

    switch( locktype ) {
	case CM_LOCKDEV:
	    /* if lockdevice explicitly specified by server, we need to
	     * open it here, even if the calling routine has opened the
	     * framebuffer for us.  Otherwise, we use the framebuffer device.
	     */

	    if( infop->cm_lockdevname[0] != '\0' ) {
		lockfd = open(infop->cm_lockdevname, O_RDWR,0666) ;
		if( lockfd < 0 ) {
#ifdef	DEBUG
		    fprintf(stderr, "wx_cm_grab: cannot open %s, %s\n",
		    infop->cm_lockdevname, strerror(errno)) ;
#endif	/* DEBUG */
		    cleanup_lockpages(cmap_grab,cflag,filelen,locktype) ;
#ifdef MT
		    mutex_unlock(&dgaGlobalMutex);
#endif
		    return NULL ;
		}
	    } else
		lockfd = devfd ;

	    cmap_grab->cm_lockfd = lockfd ;

	    /* map the lock page */
	    lock = (char *)mmap(0, 
		    CM_PAGESZ, 
		    PROT_READ|PROT_WRITE, 
		    MAP_SHARED,
		    lockfd, (off_t)cookie);

	    if (lock == (char *)-1) {
		cleanup_lockpages(cmap_grab,cflag,filelen,0) ;
#ifdef MT
		mutex_unlock(&dgaGlobalMutex);
#endif
		return errret("can't map lock page",tmp.cm_devname) ;
	    }
	    cmap_grab->cm_lockp = (u_int *) lock ;

	    /* map the unlock page */
	    unlock = (char *) mmap(0,
		      CM_PAGESZ, 
		      PROT_READ|PROT_WRITE, 
		      MAP_SHARED,
		      lockfd,(off_t)cookie) ;

	    if( unlock == (char *)-1 ) {
		cleanup_lockpages(cmap_grab,cflag,filelen,0) ;
#ifdef MT
		mutex_unlock(&dgaGlobalMutex);
#endif
		return errret("can't map unlock page", tmp.cm_devname) ;
	    }
	    cmap_grab->cm_unlockp = (u_int *) unlock ;
        break ;
	case CM_WINLOCK:
	    if( _dga_winlockat(cookie, &lock, &unlock) != 0 ) {
	      cleanup_lockpages(cmap_grab,cflag,filelen,locktype) ;
#ifdef MT
	      mutex_unlock(&dgaGlobalMutex);
#endif
	      return errret("can't get lock pages", fn) ;
	    }
	    cmap_grab->cm_lockp = (u_int *) lock ;
	    cmap_grab->cm_unlockp = (u_int *) unlock ;
        break ;
    }

    /* fill in the misc stuff */

    sunwindows_def_fd = sunwindows_inst_fd = -1;
    ok = 1;
    if (infop->cm_default && (infop->cm_sunwindows_def_devname[0] != '\0')) {
	if ((sunwindows_def_fd = sunwindows_open(
			infop->cm_sunwindows_def_devname)) < 0)
	    ok = 0;
    }
    cmap_grab->cm_sunwindows_def_fd = sunwindows_def_fd ;
    if (ok && (infop->cm_sunwindows_inst_devname[0] != '\0')) {
        if ((sunwindows_inst_fd = sunwindows_open(
    		infop->cm_sunwindows_inst_devname)) < 0)
        ok = 0;
    }
    cmap_grab->cm_sunwindows_inst_fd = sunwindows_inst_fd ;

    if(!ok) {
        cleanup_lockpages(cmap_grab,cflag,filelen,locktype) ;
#ifdef MT
	mutex_unlock(&dgaGlobalMutex);
#endif
        return errret("/dev/winxx open failed", fn) ;
    }

    cmap_grab->cm_token = filesuffix;
    cmap_grab->cm_client = NULL ;
    cmap_grab->c_chngcnt = -1 ;	/* flag all changes as not seen */
    cmap_grab->s_chngcnt_p = (u_int *) &(infop->cm_count);
    cmap_grab->cm_lockcnt = 0 ;
    cmap_grab->cm_use_new_ioctl = 1 ;	/* try to use new ioctl */

#ifdef MT
    mutex_unlock(&dgaGlobalMutex);
#endif
    return((Dga_cmap)cmap_grab);
}


static int
cleanup_lockpages(cginfo,cflag,filelen,locktype)
    _Dga_cmap	cginfo ;
    int		cflag, filelen, locktype ;
{
    int	error = 0 ;
    _Dga_cmap	p1, p2 ;

    if (cginfo->cm_sunwindows_def_fd >= 0)
        sunwindows_close(cginfo->cm_sunwindows_def_fd);
    if (cginfo->cm_sunwindows_inst_fd >= 0)
        sunwindows_close(cginfo->cm_sunwindows_inst_fd);
    switch( locktype ) {
	case CM_LOCKDEV:
	    if( cginfo->cm_unlockp != NULL )
	      error |= munmap((char *)cginfo->cm_unlockp,CM_PAGESZ) < 0 ;
	    if( cginfo->cm_lockp != NULL )
	      error |= munmap((char *)cginfo->cm_lockp,CM_PAGESZ) < 0 ;
	    if( cginfo->cm_lockfd != -1 &&
		cginfo->cm_lockfd != cginfo->cm_devfd )
	      error |= close(cginfo->cm_lockfd) ;
	break ;
	case CM_WINLOCK:
	   error |= _dga_winlockdt(cginfo->cm_lockp, cginfo->cm_unlockp) < 0 ;
	break ;
    }
    if( cginfo->cm_info != NULL )
	error |= munmap(cginfo->cm_info, filelen) < 0 ;
    if( cginfo->cm_infofd != -1 )
	    error |= close(cginfo->cm_infofd) < 0 ;
    if( cflag )
	  error |= close(cginfo->cm_devfd) < 0 ;

    for( p1 = grabbed_list, p2 = NULL ; p1 != NULL  &&  p1 != cginfo;
			p2 = p1, p1=p1->cm_next) ;
    if( p1 == NULL )		/* not found?? */
	error = 1 ;
    else {
	if( p2 == NULL )
	    grabbed_list = p1->cm_next ;
	  else
	    p2->cm_next = p1->cm_next ;
    }
    free(cginfo);
    return error ? -1 : 0 ;
}

void
dga_cm_ungrab(cginfoi, cflag)
Dga_cmap	cginfoi ;
int		cflag ;
{
    _Dga_cmap cginfo = (struct dga_cmap *)cginfoi;
    Grabbedcmap  *infop = (Grabbedcmap *) cginfo->cm_info ;
    int	cmaplen, filelen ;
    int	locktype ;

#ifdef MT
    mutex_lock(&dgaGlobalMutex);
#endif
    if( --cginfo->cm_grab_count > 0 ) {
#ifdef MT
	  mutex_unlock(&dgaGlobalMutex);
#endif
	  return;
    }

    cmaplen = infop->cm_reallen ;
    filelen = infop->cm_shadowofs + 3*cmaplen*sizeof(short) + 4*cmaplen ;

    cleanup_lockpages(cginfo,cflag,filelen,
	      infop->cm_version >= 1 ? infop->cm_locktype : CM_LOCKDEV ) ;
#ifdef MT
    mutex_unlock(&dgaGlobalMutex);
#endif
}

static Dga_cmap
errret(msg,file)
char	*msg, *file ;
{
#ifdef	DEBUG
	fprintf(stderr, "colormap-grab: %s: %s, %s\n",
		msg, file, strerror(errno)) ;
#endif	/* DEBUG */
	return NULL ;
}



/*
 * Read colormap from shared memory.
 * Shared memory should always be in sync
 * with server's idea of this X11 colormap's
 * contents.
 */

void
dga_cm_get(cginfoi,index,count, red,green,blue)
Dga_cmap	cginfoi ;
int		index, count ;
u_char		*red, *green, *blue ;
{
    _Dga_cmap cginfo = (struct dga_cmap *)cginfoi;
    Grabbedcmap	*infop = (Grabbedcmap *) cginfo->cm_info ;

#ifdef MT
    mutex_lock(&dgaGlobalMutex);
#endif
    wx_cm_lock(cginfo) ;

    /* REMIND: Currently, we don't need to test for any changes in the
     * shared memory page; but if we did, right here is where we'd do
     * it.  We compare infop->cm_count against cginfo->c_chngcnt and
     * react if there was a difference.  After handling the change,
     * we'd copy infop->cm_count to cginfo->c_chngcnt.
     */

    if( index+count > infop->cm_reallen )
      count = infop->cm_reallen - index ;

    if( count > 0 ) {

	/* copy from shared memory */
	short *shadow ;
	short *ip ;
	u_char *op ;
	int n ;

	shadow = (short *) ( (u_char *)infop + infop->cm_shadowofs ) ;
	shadow += index ;
	for(n=count, op=red, ip=shadow ; --n >= 0 ; *op++ = *ip++>>8 ) ;
	shadow += infop->cm_reallen ;
	for(n=count, op=green, ip=shadow ; --n >= 0 ; *op++ = *ip++>>8 ) ;
	shadow += infop->cm_reallen ;
	for(n=count, op=blue, ip=shadow ; --n >= 0 ; *op++ = *ip++>>8 ) ;
    }
    wx_cm_unlock(cginfo) ;
#ifdef MT
    mutex_unlock(&dgaGlobalMutex);
#endif
}
/* This is the new interface that will be publicly exposed */
void
dga_cm_read(cginfo,index,count, red,green,blue)
Dga_cmap cginfo;
int             index, count ;
u_char          *red, *green, *blue ;
{
    dga_cm_get(cginfo,index,count, red,green,blue);
}


/* write colormap to shared memory, and to DACS if appropriate. */

void
dga_cm_put(cginfoi,index,count, red,green,blue)
Dga_cmap cginfoi ;
int index, count ;
u_char *red, *green, *blue ;
{
    _Dga_cmap cginfo = (struct dga_cmap *)cginfoi;
    Grabbedcmap	*infop = (Grabbedcmap *) cginfo->cm_info ;
    short		*shadow ;
    u_char		*ip ;		/* in pointer */
    short		*op ;		/* out pointer */
    u_char		*fp ;		/* flag pointer */
    int		n ;

#ifdef MT
    mutex_lock(&dgaGlobalMutex);
#endif
    wx_cm_lock(cginfo) ;

    if( index+count > infop->cm_reallen )
	count = infop->cm_reallen - index ;   
    if( count > 0 ) {
	if( index < infop->cm_start )
	    infop->cm_start = index ;
	if( index + count > infop->cm_start + infop->cm_len )
	    infop->cm_len = index + count -infop->cm_start ;

	/* copy to shared memory shadow of grabbed color map */
	/* "stutter" the 8-bit values into 16 bits */

	shadow = (short *) ( (u_char *)infop + infop->cm_shadowofs ) ;
	shadow += index ;
	for(n=count, ip=red, op=shadow ; --n >= 0 ; *op++, *ip++)
		*op = *ip | (*ip << 8);
	shadow += infop->cm_reallen ;
	for(n=count, ip=green, op=shadow ; --n >= 0 ; *op++, *ip++)
		*op = *ip | (*ip << 8);
	shadow += infop->cm_reallen ;
	for(n=count, ip=blue, op=shadow ; --n >= 0 ; *op++, *ip++)
		*op = *ip | (*ip << 8);
	fp = (u_char *)infop + infop->cm_shadowofs +
		3 * infop->cm_reallen * sizeof(short) + index ;
	for(n=count ; --n >= 0 ; *fp++ = 1 ) ;

	if( infop->cm_installed ) {
#ifdef COMMENT
	    /* We no longer need the hw shadow cmap but have to keep
	     * the structures the same size and so we will just stop
	     * updating it
	     */
	    u_char *hwshadow;
	
	    /* copy to shared memory shadow of hardware color map */
	    hwshadow = (u_char *)infop + infop->cm_shadowofs +
		3 * infop->cm_reallen * sizeof(short) +
		infop->cm_reallen + index;
	    for (n=count, ip=red, fp=hwshadow; --n >= 0; *fp++ = *ip++);
	    hwshadow += infop->cm_reallen;
	    for (n=count, ip=green, fp=hwshadow; --n >= 0; *fp++ = *ip++);
	    hwshadow += infop->cm_reallen;
	    for (n=count, ip=blue, fp=hwshadow; --n >= 0; *fp++ = *ip++);
	    hwshadow -= index + 2 * infop->cm_reallen;
#endif
	    switch(infop->cm_load_method) {

#ifdef SUNWINDOWS 
		/* Note from V4 on, SUnwindows include files, support no
		 * longer exist. I am commenting out the code instead of
		 * removing it only for completeness. After Mars, time to
		 * move away from sunwindows....
		*/
		case SUNWINDOWS_IOCTL:
		{
		    struct cmschange cmschange;

		    if( cginfo->cm_sunwindows_def_fd >= 0 ) {
			strcpy(cmschange.cc_cms.cms_name,
			    infop->cm_sunwindows_def_cmapname);
			cmschange.cc_cms.cms_addr = 0;
			cmschange.cc_cms.cms_size =
			    infop->cm_sunwindows_def_cmapsize;
			cmschange.cc_map.cm_red = hwshadow;
			cmschange.cc_map.cm_green = 
			    hwshadow + infop->cm_reallen;
			cmschange.cc_map.cm_blue = 
			hwshadow + 2 * infop->cm_reallen;

		    /* HACK ALERT */
		    /* Adjust SUNWINDOWS cms segment 1st colr != last color */
		    if ((cmschange.cc_map.cm_red[0] ==
		      cmschange.cc_map.cm_red[cmschange.cc_cms.cms_size-1]) &&
		      (cmschange.cc_map.cm_green[0] ==
		      cmschange.cc_map.cm_green[cmschange.cc_cms.cms_size-1]) &&
		      (cmschange.cc_map.cm_blue[0] ==
		      cmschange.cc_map.cm_blue[cmschange.cc_cms.cms_size-1]))
			{
			if (cmschange.cc_map.cm_blue[0] > 0)
			    cmschange.cc_map.cm_blue[0]--;
			else
			    cmschange.cc_map.cm_blue[0] = 1;
			}

		    ioctl(cginfo->cm_sunwindows_def_fd, WINSETCMS, &cmschange);
		    }

		if( cginfo->cm_sunwindows_inst_fd >= 0 )
		    {
		    strcpy(cmschange.cc_cms.cms_name,
			infop->cm_sunwindows_inst_cmapname);
		    cmschange.cc_cms.cms_addr = 0;
		    cmschange.cc_cms.cms_size =
			infop->cm_sunwindows_inst_cmapsize;
		    cmschange.cc_map.cm_red = hwshadow;
		    cmschange.cc_map.cm_green = hwshadow + infop->cm_reallen;
		    cmschange.cc_map.cm_blue = 
			hwshadow + 2 * infop->cm_reallen;

		    /* HACK ALERT */
		    /* Adjust SUNWINDOWS cms segment 1st colr != last color */
		    if ((cmschange.cc_map.cm_red[0] ==
		      cmschange.cc_map.cm_red[cmschange.cc_cms.cms_size-1]) &&
		      (cmschange.cc_map.cm_green[0] ==
		      cmschange.cc_map.cm_green[cmschange.cc_cms.cms_size-1]) &&
		      (cmschange.cc_map.cm_blue[0] ==
		      cmschange.cc_map.cm_blue[cmschange.cc_cms.cms_size-1])) {
			if (cmschange.cc_map.cm_blue[0] > 0)
			    cmschange.cc_map.cm_blue[0]--;
			else
			    cmschange.cc_map.cm_blue[0] = 1;
		    }

		    ioctl(cginfo->cm_sunwindows_inst_fd,WINSETCMS,&cmschange);
		}
	    }
	    break;
#endif /* SUNWINDOWS */
	    case HW_DEVICE_DIRECT:	/* could have device-specific
					   routines here; just fall
					   through to device ioctl
					   for now */

	    case HW_DEVICE_IOCTL:
	    default:
#ifdef	FBIOPUTCMAPI
		if( cginfo->cm_use_new_ioctl) {
		    /* try new ioctl */
		    struct fbcmap_i cmap;

		    cmap.flags = 0 ;
		    cmap.id = infop->cm_cmapnum ;
		    cmap.index = infop->cm_ioctlbits | index;
		    cmap.count = count;
		    cmap.red   = red;
		    cmap.green = green;
		    cmap.blue  = blue;
		    if( ioctl(cginfo->cm_devfd, FBIOPUTCMAPI, &cmap) == 0 )
		    break;
		}
#endif	/* FBIOPUTCMAPI */

		if( cginfo->cm_use_new_ioctl ) {	
		    /* try FB_CLUTPOST ioctl */
		    struct fb_clut cmap;

		    cmap.flags = 0 ;
		    cmap.index = infop->cm_cmapnum;
		    cmap.offset = index;
		    cmap.count = count;
		    cmap.red   = red;
		    cmap.green = green;
		    cmap.blue  = blue;
		    if( ioctl(cginfo->cm_devfd, FB_CLUTPOST, &cmap) == 0 )
			break;
		
		    cginfo->cm_use_new_ioctl = 0;
               }

	       if (cginfo->cm_use_new_ioctl == 0) {
		    struct fbcmap cmap;

		    cmap.index = infop->cm_ioctlbits | index;
		    cmap.count = count;
		    cmap.red   = red;
		    cmap.green = green;
		    cmap.blue  = blue;
		    ioctl(cginfo->cm_devfd, FBIOPUTCMAP, &cmap);
		}
		break;
	    }
	}

	/* We've changed the shared memory page, flag this fact to
	* the server and to any other clients
	*/
	cginfo->c_chngcnt = ++infop->cm_count ;
    }
    wx_cm_unlock(cginfo) ;
#ifdef MT
    mutex_unlock(&dgaGlobalMutex);
#endif
}

/* This is the interfce that will be publicly exposed */
void
dga_cm_write(cginfoi,index,count, red,green,blue, putfunc)
Dga_cmap   cginfoi ;
int     index, count ;
u_char  *red, *green, *blue ;
void		(*putfunc)();
{
    _Dga_cmap cginfo = (struct dga_cmap *)cginfoi;
    Grabbedcmap    *infop = (Grabbedcmap *) cginfo->cm_info ;
    short       *shadow ;
    u_char     *ip ;       /* in pointer */
    short      *op ;       /* out pointer */
    u_char     *fp ;       /* flag pointer */
    int        n ;
 
#ifdef MT
    mutex_lock(&dgaGlobalMutex);
#endif
    wx_cm_lock(cginfo) ;
 
    if( index+count > infop->cm_reallen )
      count = infop->cm_reallen - index ;
 
    if( count > 0 ) {
	if( index < infop->cm_start )
	    infop->cm_start = index ;
 
	if( index + count > infop->cm_start + infop->cm_len )
	    infop->cm_len = index + count -infop->cm_start ;
 
	/* copy to shared memory shadow of grabbed color map */
	/* "stutter" the 8-bit values into 16 bits */
 
	shadow = (short *) ( (u_char *)infop + infop->cm_shadowofs ) ;
	shadow += index ;
	for(n=count, ip=red, op=shadow ; --n >= 0 ; *op++, *ip++)
	    *op = *ip | (*ip << 8);
	shadow += infop->cm_reallen ;
	for(n=count, ip=green, op=shadow ; --n >= 0 ; *op++, *ip++)
	    *op = *ip | (*ip << 8);
	shadow += infop->cm_reallen ;
	for(n=count, ip=blue, op=shadow ; --n >= 0 ; *op++, *ip++)
	    *op = *ip | (*ip << 8);
	fp = (u_char *)infop + infop->cm_shadowofs +
	    3 * infop->cm_reallen * sizeof(short) + index ;
	for(n=count ; --n >= 0 ; *fp++ = 1 ) ;
        
	if( infop->cm_installed ) {
#ifdef COMMENT
	    /* We dont need to update thie any more */
	    u_char *hwshadow;
 
	    /* copy to shared memory shadow of hardware color map */
	    hwshadow = (u_char *)infop + infop->cm_shadowofs +
		3 * infop->cm_reallen * sizeof(short) +
	    infop->cm_reallen + index;
	    for (n=count, ip=red, fp=hwshadow; --n >= 0; *fp++ = *ip++);
	    hwshadow += infop->cm_reallen;
	    for (n=count, ip=green, fp=hwshadow; --n >= 0; *fp++ = *ip++);
	    hwshadow += infop->cm_reallen;
	    for (n=count, ip=blue, fp=hwshadow; --n >= 0; *fp++ = *ip++);
	    hwshadow -= index + 2 * infop->cm_reallen;
 
	    for (n=count, ip=blue, fp=hwshadow; --n >= 0; *fp++ = *ip++);
	    hwshadow -= index + 2 * infop->cm_reallen;
#endif
	    /* Now call the user supplied function for actually
	    * posting the cmap
	    */
	    (*putfunc)( cginfo, index, count, red, green, blue);
      }
         
      /* We've changed the shared memory page, flag this fact to
       * the server and to any other clients
       */
 
      cginfo->c_chngcnt = ++infop->cm_count ;
    }
    wx_cm_unlock(cginfo) ;
#ifdef MT
    mutex_unlock(&dgaGlobalMutex);
#endif
}    

/* Interfaces that will be exposed to the public */
int
dga_cm_devdfd(cginfoi)
Dga_cmap   cginfoi ;
{

    return (((struct dga_cmap *)cginfoi)->cm_devfd);
}

/* This device info is shared between the server and client */
void *
dga_cm_devinfo(cginfoi)
Dga_cmap   cginfoi ;
{
    _Dga_cmap cginfo = (struct dga_cmap *)cginfoi;
    return ((void *)(((char *)cginfo->cm_info) 
			+ CM_INFOP(cginfo)->device_offset));

}

/* Each client may store private info in the client info ptr */
void
dga_cm_set_client_infop(cginfoi, client_info_ptr)
Dga_cmap cginfoi;
void* client_info_ptr;
{
    _Dga_cmap cginfo = (struct dga_cmap *)cginfoi;
    
    cginfo->cm_client = client_info_ptr;
}

void *
dga_cm_get_client_infop(cginfoi) 
Dga_cmap cginfoi; 
{
    _Dga_cmap cginfo = (struct dga_cmap *)cginfoi;
        
    return ((void *)cginfo->cm_client); 
} 

static Cmap_Devlist *devlist = NULL;

static	int
sunwindows_open(devname)
char *devname;
{
	Cmap_Devlist *dlist = devlist;
	int fd;

	while (dlist)
		{
		if (strcmp(devname, dlist->devname) == 0)
			{
			dlist->refcnt++;
			return(dlist->fd);
			}
		dlist = dlist->next;
		}
	if ((fd = open(devname, O_RDWR, 0666)) < 0)
		{
#ifdef	DEBUG
		fprintf(stderr, "colormap-grab: open failed %s, %s\n",
		    devname, strerror(errno)) ;
#endif	/* DEBUG */
		return(-1);
		}
	if((dlist = (Cmap_Devlist *)malloc(sizeof(Cmap_Devlist))) == NULL )
		{
		close(fd);
#ifdef	DEBUG
		fprintf(stderr, "colormap-grab: malloc failed %s, %s\n",
		    devname, strerror(errno)) ;
#endif	/* DEBUG */
		return(-1);
		}
	dlist->next = devlist;
	devlist = dlist;
	dlist->refcnt = 1;
	dlist->fd = fd;
	strcpy(dlist->devname, devname);
	return(fd);
}


static	void
sunwindows_close(fd)
int fd;
{
	Cmap_Devlist *dlist = devlist;
	Cmap_Devlist **dlptr = &devlist;

	while (dlist)
		{
		if (fd == dlist->fd)
			{
			if (--dlist->refcnt == 0)
				{
				close(fd);
				*dlptr = dlist->next;
				free(dlist);
				}
			return;
			}
		dlptr = &dlist->next;
		dlist = dlist->next;
		}
}






/* /dev/winlock management code.  This is a temporary hack so we can
 * develop the new /dev/winlock interface.  Hopefully, this will become
 * part of the C library someday.
 *
 */


#include <sys/ioccom.h>

	/* structure for allocating lock contexts.  The identification
	 * should be provided as the offset for mmap(2).  The offset is
	 * the byte-offset relative to the start of the page returned
	 * by mmap(2).
	 */

struct	winlockalloc {
	u_long	sy_key ;	/* user-provided key, if any */
	u_long	sy_ident ;	/* system-provided identification */
	} ;

struct	winlocktimeout {
	u_long	sy_ident ;
	u_int	sy_timeout ;
	int	sy_flags ;
	} ;


#ifndef WINLOCKALLOC
#ifdef	SVR4
#define WIOC    ('L'<<8)
#define WINLOCKALLOC            (WIOC|0)
#define WINLOCKFREE             (WIOC|1)
#define WINLOCKSETTIMEOUT       (WIOC|2)
#define WINLOCKGETTIMEOUT       (WIOC|3)
#define WINLOCKDUMP             (WIOC|4)
#else	/* SVR4 */
#define	WINLOCKALLOC	_IOWR(L, 0, struct winlockalloc)
#define	WINLOCKFREE	_IOW(L, 1, u_long)
#define	WINLOCKSETTIMEOUT	_IOW(L, 2, struct winlocktimeout)
#define	WINLOCKGETTIMEOUT	_IOWR(L, 3, struct winlocktimeout)
#define	WINLOCKDUMP	_IO(L, 4)
#endif	/* SVR4 */
#endif	/* WINLOCKALLOC */


/* flag bits */
#define SY_NOTIMEOUT	0x1	/* This client never times out */


static	char	*lockdev_name = "/dev/winlock" ;
static	char	*alt_lockdev_name = "/dev/cgsix0" ;

static	int	lock_fd = -1 ;
static	u_long	pagemask ;
static	u_long	pageoffset ;
static	u_long	pagesize ;



	/* return non-zero if fail */

static int
init()
{
	if( lock_fd == -1 ) {
	  if( (lock_fd = open(lockdev_name, O_RDWR, 0)) == -1  &&
	      (lock_fd = open(alt_lockdev_name, O_RDWR, 0)) == -1 )
	    return 1 ;
#ifdef SVR4
	pagesize = sysconf(_SC_PAGESIZE);
#else
	  pagesize = getpagesize() ;
#endif
	  pageoffset = pagesize - 1 ;
	  pagemask = ~pageoffset ;
	}

	return 0 ;
}


int
_dga_winlockat(cookie, lockp, unlockp)
	u_long	cookie ;
	int	**lockp, **unlockp ;
{
	u_long	ofs ;
	caddr_t	ptr ;

	if( lock_fd == -1  &&  init() )
	{
	  errno = EINVAL ;
	  return -1 ;
	}

	ofs = cookie & pageoffset ;
	cookie &= pagemask ;

	ptr = mmap(0, pagesize, PROT_READ|PROT_WRITE,
		MAP_SHARED, lock_fd, (off_t)cookie) ;
	if( (int)ptr == -1 )
	{
	  errno = ENOSPC ;
	  return -1 ;
	}
	*lockp = (int *) (ptr+ofs) ;

	ptr = mmap(0, pagesize, PROT_READ|PROT_WRITE,
		MAP_SHARED, lock_fd, (off_t)cookie) ;
	if( (int)ptr == -1 )
	{
	  (void) munmap((caddr_t)*lockp, pagesize) ;
	  errno = ENOSPC ;
	  return -1 ;
	}
	*unlockp = (int *) (ptr+ofs) ;

	return 0 ;
}



int
_dga_winlockdt(lockp, unlockp)
	int	*lockp, *unlockp ;
{
	caddr_t	ptr ;

	if( lock_fd == -1  &&  init() )
	{
	  errno = EINVAL ;
	  return -1 ;
	}

	ptr = (caddr_t) ((long)lockp & pagemask) ;
	if( munmap(ptr, pagesize) )
	    perror("_dga_winlockdt: munmap:");

        ptr = (caddr_t) ((long)unlockp & pagemask) ;
        if( munmap(ptr, pagesize) )
            perror("_dga_winlockdt: munmap:");

	return 0 ;
}
