/* Copyright (c) 1993, 1998, Oracle and/or its affiliates. All rights reserved.
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
 *
 *
 *      @@@@   @@@@@  @   @          @@@@  @@@@    @@@   @@@@
 *      @   @    @    @@  @         @      @   @  @   @  @   @
 *      @@@@     @    @ @ @         @ @@@  @@@@   @@@@@  @@@@
 *      @  @     @    @  @@         @   @  @  @   @   @  @   @
 *      @   @    @    @   @  @@@@@   @@@@  @   @  @   @  @@@@
 *
 *      DGA shared retained window access routines
 *
 *	int
 *	dga_rtn_active(clientp)
 *	    Dga_window clientp;
 *
 *	u_char
 *	dga_rtn_cached(clientp)
 *	    Dga_window clientp;
 *
 *	void *	
 *	dga_rtn_devinfo(clientp)
 *	    Dga_window clientp;
 *
 *	void
 *	dga_rtn_devtype(clientp, type, name)
 *	    Dga_window   clientp;
 *	    u_char      *type;
 *	    char       **name;
 *
 *	void 
 *	dga_rtn_dimensions(clientp, width, height, linebytes) 
 *	    Dga_window  clientp; 
 *	    short      *width; 
 *	    short      *height; 
 *	    u_int      *linebytes;
 *
 *	int
 *	dga_rtn_grab(clientp)
 *	    Dga_window  clientp; 
 *
 *	void *
 *	dga_rtn_pixels(clientp)
 *	    Dga_window clientp;
 *
 *	int
 *	dga_rtn_ungrab(clientp)
 *	    Dga_window  clientp; 
 *
 *	int
 *	_dga_rtn_map(clientp)
 *	    Dga_window  clientp;
 *
 *	int
 *	_dga_rtn_unmap(clientp)
 *	    Dga_window clientp;
 *
 */

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#ifdef SERVER_DGA
#include <X11/X.h>
#include <X11/Xmd.h>
#include "windowstr.h"
#include "dga_externaldefs.h"
#include "dga/dgawinstr.h"
#else
#include <fcntl.h>
#include <sys/mman.h>

#ifdef SVR4
#include <netdb.h>
#include <sys/stat.h>
#else
#include <sys/param.h>
#endif

#include <X11/Xlib.h>
#endif /* SERVER_DGA */

#include "dga_incls.h"
#include "rtn_grab.h"

int dgai_rtn_ungrab_common();
extern int dgai_win_check_multiple_grab(_Dga_window clientp, int drawableGrabber);
extern void *_dga_is_X_window(Dga_token token, Display **dpyp, Window *winp);

/*
 *
 *  dga_rtn_active()
 *
 *  DGA Retained Windows Active.  This function is called to determine
 *  if DGA to the retained portion of the specified dga_window is currently
 *  active.  Since the server can drop support for this functionality at 
 *  any time, the client should always call this function when a change has 
 *  been has been recorded in the retained window information.  This function 
 *  should be called prior to accessing any other retained window information.
 *  The function returns a non-zero result if DGA to the retained portion
 *  of the window is active.  A zero result is returned if support has
 *  been dropped.  
 *
 *  Inputs:     Dga_window - Pointer to the client structure.
 *
 *  Outputs:     0 - DGA Retained window support has been dropped.
 *		-1 - DGA Retained window support continues.
 *
 *  Globals:    None.
 *
 *  Externals:  None.
 *
 */
int
dga_rtn_active(clientpi)
    Dga_window clientpi;
{
    _Dga_window clientp = (struct dga_window *)clientpi;
    
    if ((clientp->rtn_flags & RTN_MAPPED))
	return (RTN_PASSED);
    else
	return (RTN_FAILED);
}

/*
 *
 *  dga_rtn_cached()
 *
 *  DGA Retained HW Cache status.  This function returns a non-zero
 *  value if the retained raster is cached in hardware.  If set to
 *  DGA_RTN_NEW_DEV then the server has re-cached the retained
 *  raster from one device to another.  If set to DGA_RTN_SAME_DEV
 *  the raster remains cached in the same device as previously
 *  recorded.  If the retained raster is not cached in hw then the
 *  function returns DGA_RTN_NOT_CACHED (0).
 *
 *  Inputs:     Dga_window - Pointer to the client structure.
 *
 *  Outputs:    DGA_RTN_NOT_CACHED - not cached in hw
 *		DGA_RTN_SAME_DEV   - cached in the same hw device
 *		DGA_RTN_NEW_DEV    - cached in the new hw device
 *
 *  Globals:    None.
 *
 *  Externals:  RTN_INFOP()	Internal MACRO
 *
 *
 */
int
dga_rtn_cached(clientpi)
    Dga_window clientpi;
{
    _Dga_window clientp = (struct dga_window *)clientpi;
    
    if (RTN_INFOP(clientp)->cached) 
	if (clientp->c_rtncachseq != *(clientp->s_rtncachseq_p)) {
	    clientp->c_rtncachseq = *(clientp->s_rtncachseq_p);
	    return (DGA_RTN_NEW_DEV);
	}
	else
	    return (DGA_RTN_SAME_DEV);
    else
	return (DGA_RTN_NOT_CACHED);
}

/*
 *
 *  dga_rtn_devinfop()	<---external interface just to be consistent 
 *  dga_rtn_devinfo()
 *
 *  DGA Retained Device Info.  This function returns a pointer to
 *  the shared device specific retained raster information when
 *  the retained raster is cached in hw.  The pointer is invalid
 *  if the retained raster isn't cached in hw.
 *
 *  Inputs:     Dga_window - Pointer to the client structure.
 *
 *  Outputs:    void *  - Pointer to the device specific information
 *
 *  Globals:    None.
 *
 *  Externals:  RTN_INFOP()	Internal MACRO
 *
 */
void *
dga_rtn_devinfo(clientpi)
    Dga_window clientpi;
{   
    /* This is the internal interface */
    _Dga_window clientp = (struct dga_window *)clientpi;
    
    return (((char *)clientp->rtn_info) + RTN_INFOP(clientp)->device_offset);
}

void *
dga_rtn_devinfop(clientpi)
    Dga_window clientpi;
{
    _Dga_window clientp = (struct dga_window *)clientpi;
    
    return (((char *)clientp->rtn_info) + RTN_INFOP(clientp)->device_offset);
}

/*
 *
 *  dga_rtn_devtype()
 *
 *  DGA Retained Device Type.  This function is used to obtain
 *  the retained raster hardware cache device type and name.
 *
 *  Inputs:     Dga_window - Pointer to the client structure.
 *		Unsign8 *  - Pointer to location to store device type.
 *		char **    - Pointer to location to store name string pointer.
 *
 *  Outputs:    None.
 *
 *  Globals:    None.
 *
 *  Externals:  RTN_INFOP()	Internal MACRO
 * 
 */
void
dga_rtn_devtype(clientpi, type, name)
    Dga_window  clientpi;
    u_char     *type;
    char      **name;
{
    _Dga_window clientp = (struct dga_window *)clientpi;
    
    *type = RTN_INFOP(clientp)->device;
    *name = (char *) RTN_INFOP(clientp)->scr_name;
}
    
/*
 *
 *  dga_rtn_dimensions()
 *
 *  DGA Retained Raster Dimensions.  This function is used to obtain
 *  the retained raster's dimensions.
 *
 *  Inputs:     Dga_window - Pointer to the client structure.
 *              short    * - Pointer to location to store the width.
 *              short    * - Pointer to location to store the height.
 *		u_int	 * - Pointer to the location to store the linebytes.
 *
 *  Outputs:    None.
 *
 *  Globals:    None.
 *
 *  Externals:  RTN_INFOP()	Internal MACRO
 *
 */
void
dga_rtn_dimensions(clientpi, width, height, linebytes)
    Dga_window  clientpi;
    short      *width;
    short      *height;
    u_int      *linebytes;
{
    _Dga_window clientp = (struct dga_window *)clientpi;
    
    *width = RTN_INFOP(clientp)->width;
    *height = RTN_INFOP(clientp)->height;
    *linebytes = RTN_INFOP(clientp)->linebytes;
}

int
dga_rtn_bitsperpixel(Dga_window clientpi)
{
    _Dga_window clientp = (struct dga_window *)clientpi;
    
    return(RTN_INFOP(clientp)->bitsperpixel);
}

/*
 *
 *  dga_rtn_grab()
 *
 *  DGA Retained Window Grab.  This function creates the shared memory
 *  interface to allow the calling process Direct Graphics Access (DGA)
 *  to the retained raster associated with the specified DGA window.
 *  A request to allow DGA access to the retained raster is sent to the
 *  X/NeWS server.  Should the server honor this request, shared memory 
 *  mappings within the calling process's address space are then created. 
 *  Should any of these steps fail, 0 is returned and the calling process 
 *  is not allowed DGA to the retained raster.  A non-zero result is 
 *  returned upon success.
 *
 *  Inputs:     Dga_window - Pointer to the Dga_window for which DGA
 *			     to the retained raster is desired.
 *
 *  Outputs:     0 - failed
 *		-1 - passed
 *
 *  Globals:    None.
 *
 *  Externals:	XDgaGrabRetainedWindow()
 *		XDgaUnGrabRetainedWindow()
 *		_dga_is_X_window()
 *		_dga_rtn_map()
 *		fprintf()			DEBUG ONLY
 *
 */
int
dga_rtn_grab(clientpi)
    Dga_window	 clientpi;
{
    Display	*dpy;
    Window	 win;
#ifdef SERVER_DGA
    WXINFO  *infop;
    WindowPtr pWin;
#endif /* SERVER_DGA */

    /*
     *  Check for an invalid Dga_window
     */
     _Dga_window clientp = (struct dga_window *)clientpi;
    
    if ((clientp == (_Dga_window) NULL)) {
#ifdef DEBUG
	(void) fprintf(stderr, "dga_rtn_grab: passed null pointer\n");
#endif
	return (RTN_FAILED);
    }

#ifdef SERVER_DGA
        /* Determine the window associated with this clientp */
    infop = (WXINFO *) clientp->w_info;
    pWin = (((WDEV *)(infop->wdev))->pWin);

    /* Check to see if backing store has been turned on for thw window */
    if (pWin->backingStore == NotUseful)
	return (RTN_FAILED);


    if (!DgaSharedRetained(pWin, 1, pWin->drawable.id)) {
        return (RTN_FAILED);
    }
   /* Map the shared memory into the calling process's address space.*/
   if (!_dga_rtn_map(clientp)) {

                /* Ungrab the retained raster */
        (void) DgaSharedRetained(pWin, 0, pWin->drawable.id);
        return (RTN_FAILED);
    }
#else
    /*
     *  If the retained raster has already been grabbed. Don't
     *  do anything.
     */
    if (clientp->rtn_flags & RTN_GRABBED)
	return (RTN_PASSED);

    /*
     *  Find out if this is an X window.  If so get the Display and window
     *  id.  These are used to determine the name of the shared retained
     *  info file.  NOTE:  DGA to retained rasters are currently supported
     *  only for X windows.
     */
     if (!_dga_is_X_window(clientp->w_token, &dpy, &win)) {
#ifdef DEBUG
	(void) fprintf(stderr, "dga_rtn_grab: Unsupported window type\n");
#endif
	return (RTN_FAILED);
    }
    /* Check to see if backing store is turned on for this window; if not
     * report failure
   */
   {
	XWindowAttributes	attr;
   	XGetWindowAttributes(dpy,win,&attr);
	if (attr.backing_store == NotUseful) {
#ifdef DEBUG
		(void) fprintf(stderr,"dga_rtn_grab: Window has no backing store\n");
#endif
		return (RTN_FAILED);
	}
   }
   

    /*
     *  Request the server to allow DGA to the retained raster associated
     *  with this Dga_window.
     */
    if (!XDgaGrabRetainedWindow(dpy, win)) {
#ifdef DEBUG
	(void) fprintf(stderr, "dga_rtn_grab: XDgaGrabRetainedWindow failed\n");
#endif
	return (RTN_FAILED);
    }
   /*
    *  Now map the shared memory into the calling process's address
    *  space.
    */
   if (!_dga_rtn_map(clientp)) {
#ifdef DEBUG
	(void) fprintf(stderr, "dga_rtn_grab: unable to map shared info\n");
#endif
	/*
	 *  Ungrab the retained raster
	 */
	(void) XDgaUnGrabRetainedWindow(dpy, win);
	return (RTN_FAILED);
    }
#endif /* SERVER_DGA */
    clientp->rtn_flags |= RTN_GRABBED;
    return (RTN_PASSED);
}

/*
 *
 *  dga_rtn_pixels()
 *
 *  DGA Retained Pixel Memory .  This function returns a pointer
 *  to the shared retained pixel memory.
 *
 *  Inputs:     Dga_window - Pointer to the client structure.
 *
 *  Outputs:    u_char * - Pointer to retained pixel memory.
 *
 *  Globals:    None.
 *
 *  Externals:  None.
 *
 *
 */
void *
dga_rtn_pixels(clientpi)
    Dga_window clientpi;
{
    _Dga_window clientp = (struct dga_window *)clientpi;
    
    return ((void *)clientp->rtn_pixels);
}

/*
 *
 *  dga_rtn_ungrab()
 *
 *  DGA Retained Window Ungrab.  This function frees the resources 
 *  associated with a DGA retained retained raster.  The shared
 *  memory mappings in the calling process's address space are 
 *  unmapped, the shared info file is closed, and the server is
 *  notified through a protocol extension to free all its resources
 *  associated with the DGA retained raster.  Should any of these 
 *  steps fail, 0 is returned.  A non-zero result is returned upon 
 *  success.
 *
 *  Inputs:     Dga_window - Pointer to the Dga_window for which DGA
 *                           to the retained raster is desired.
 *
 *  Outputs:     0 - failed
 *              -1 - passed
 *
 *  Globals:    None.
 *
 *  Externals:  DisplayString()                 X11 MACRO
 *              XDgaUnGrabRetainedWindow()
 *		_dga_is_X_window()
 *              _dga_rtn_unmap()
 *              fprintf()                       DEBUG ONLY
 *
 */
int
dga_rtn_ungrab(clientpi)
    Dga_window	clientpi;
{
    _Dga_window clientp = (struct dga_window *)clientpi;    

    return (dgai_rtn_ungrab_common(clientp, 0));
}

int
dgai_rtn_ungrab_common(clientp, drawableGrabber)
    _Dga_window  clientp;
    int	drawableGrabber;
{
    int		status = -1;
#ifdef SERVER_DGA
    WindowPtr      pWin;
    WXINFO  *infop;
#else
    Display    *dpy;
    Window	win;
#endif /* SERVER_DGA */

    /*
     *  Check for an invalid Dga_window
     */
    if ((clientp == (Dga_window) NULL)) {
#ifdef DEBUG
        (void) fprintf(stderr, "dga_rtn_ungrab: passed null pointer\n");
#endif
        return (RTN_FAILED);
    }

    /*
     *  If the retained window has not been grabbed then don't
     *  do anything.
     */
    if ((clientp->rtn_flags & RTN_GRABBED) == 0)
	return (RTN_FAILED);

    /*
     *  Unmap the calling process's resources if present.
     */
    status &= _dga_rtn_unmap(clientp);

    /*
     *  Set the dga_window retained window server sequence counter pointer
     *  to reflect that the retained raster has NOT been grabbed.
     */
    clientp->s_rtnseq_p = &(clientp->c_rtnseq);

#ifdef SERVER_DGA
    /* Determine the window associated with this clientp */
    infop = (WXINFO *) clientp->w_info;
    pWin = (((WDEV *)(infop->wdev))->pWin);
       
    status &= DgaSharedRetained(pWin, 0, pWin->drawable.id);
#else
    /*
     *  Find out if this is an X window.  If so get the Display and window
     *  id.  These are used to determine the name of the shared retained
     *  info file.  NOTE:  DGA to retained rasters is currently supported
     *  only for X windows.
     */
     if (!_dga_is_X_window(clientp->w_token, &dpy, &win)) {
#ifdef DEBUG
        (void) fprintf(stderr, "dga_rtn_grab: Unsupported window type\n");
#endif
        return (RTN_FAILED);
    }

    /*
     *  Tell the server to deallocate its retained window
     *  resources.if there are no other clients grabbing this window
     */
    if (!dgai_win_check_multiple_grab(clientp,drawableGrabber))
	status &= XDgaUnGrabRetainedWindow(dpy, win);

#endif /* SERVER_DGA */

    clientp->rtn_flags = 0;

    if (status)
	return (RTN_PASSED);
    else
	return (RTN_FAILED);
}

/*
 *
 *  _dga_rtn_map()
 *
 *  DGA Retained Window Map.  This function maps the retained window
 *  shared memory into the clients address space after determining 
 *  the path to the retained window information file.  The shared 
 *  retained info structure is mapped followed by the actual pixel 
 *  array used when the pixels are not cached in hardware.  The 
 *  address of the shared retained info structure is then place in 
 *  the dga_window structure along with the client dependent information.
 *  Should any operation fail, a NULL pointer is placed in the dga_window 
 *  structure and 0 is returned.
 *  
 *  Inputs:	Dga_window - Pointer to the dga_window structure
 *
 *  Outputs:	 0 - failed
 *		-1 - passed
 *
 *  Globals:	None.
 *	
 *  Externals:	DisplayString()		X11 MACRO
 *		XDgaGetRetainedPath()
 *		_dga_is_X_window()
 *		close()
 *		fprintf()		DEBUG ONLY
 *		fstat()
 *		getpagesize() 		SUNOS ONLY
 *		mmap()
 *		munmap()
 *		open()
 *		sprintf()
 *		sscanf()
 *		strcat()
 *		strcpy()
 *		strlen()
 *		sysconf()		SVR4  ONLY
 *		unlink()
 *		
 */
int
_dga_rtn_map(clientp)
_Dga_window clientp; 
{
    SHARED_RETAINED_INFO	*infop;
#ifdef SERVER_DGA
    WXINFO  			*winfop;
#else
    u_char			*pixels;
    int				 filefd;
    size_t			 size;
    size_t			 pagesize;
    u_int			 port;
    Display			*dpy;
    Window			 win;
    char			*dpystr;
    struct stat			 rstat;
    char			 path[256];
    char			 host[MAXHOSTNAMELEN];
#endif /* SERVER_DGA */

    /*
     *  Check for a non-zero pointer.
     */
    if (clientp == (_Dga_window) NULL) {
#ifdef DEBUG
	(void) fprintf(stderr, "_dga_rtn_map: dga_window pointer (NULL)\n");
#endif
	return (RTN_FAILED);
    }

    /*
     *  If the shared retained information has already been mapped don't 
     *  do anything.
     */
    if ((clientp->rtn_flags & RTN_MAPPED))
	return (RTN_PASSED);

#ifdef SERVER_DGA
    /* Determine the window associated with this clientp */
    winfop = (WXINFO *) clientp->w_info;
    infop = (SHARED_RETAINED_INFO *)winfop->w_srtndlink;
 
    /* Initialise clientp's retained info structure - refer dga.h */
    clientp->rtn_fd = 0; /* I don't think that it is needed any more */
    clientp->rtn_size = infop->s_size;
    clientp->c_rtnseq = 0;
    clientp->s_rtnseq_p = (u_int *)&(infop->s_modified);
    clientp->c_rtncachseq = 0;
    clientp->s_rtncachseq_p = (u_int *)&(infop->s_cacheseq);
    clientp->rtn_info = (caddr_t)infop;
    clientp->rtn_pixels = (caddr_t)(infop->s_pixels);
    clientp->rtn_flags |= RTN_MAPPED;
 
        return (RTN_PASSED);
#else /* SERVER_DGA */
    /*
     *  Find out if this is an X window.  If so get the Display and window
     *  id.  These are used to determine the name of the shared retained
     *  info file.  NOTE:  DGA to retained rasters are currently supported
     *  only for X windows.
     */
     if (!_dga_is_X_window(clientp->w_token, &dpy, &win)) {
#ifdef DEBUG
        (void) fprintf(stderr, "_dga_rtn_map: Unsupported window type\n");
#endif
        return (RTN_FAILED);
    }

    /*
     *  Now locate the shared retained info file within the file system.
     *  This file is located in /tmp by default, but through a server
     *  command line option, can be located anywhere on the system in
     *  question.  Get the path from the server using the protocol
     *  extension.  Then create the filename using the display string
     *  and the port number.
     */
    if (!XDgaGetRetainedPath(dpy, win, path)) {
#ifdef DEBUG
	(void) fprintf(stderr, "_dga_rtn_map: XDgaGetRetainedPath failed\n");
#endif
	return (RTN_FAILED);
    }

    /*
     *  If the path is equal to "", then use the default directory
     *  path.
     */
    if (!(*path)) 
	(void) strcpy(path, "/tmp");
    else if (strlen(path) > RTN_MAXPATH) {
#ifdef DEBUG
	(void) fprintf(stderr, "_dga_rtn_map: path longer than supported\n");
#endif
	return (RTN_FAILED);
    }
    (void) strcat(path, RTN_FILE);

    /*
     *  Now get the port number for this display
     */   
    dpystr = DisplayString(dpy);
    if (dpystr[0] == ':') 
	(void) sscanf(dpystr, ":%u", &port);
    else
	(void) sscanf(dpystr, "%[^:]:%u", host, &port);

   /*
    *  Combine the port number and the window id with the path
    *  string.
    */
    size = strlen(path);
    (void) sprintf(path+size, "%01x.%08x", port, win);

    if ((filefd = open(path,O_RDWR,0666))<0) {
#ifdef DEBUG
	(void) fprintf(stderr, "_dga_rtn_map: unable to open file %s\n", 
		       path);
#endif
	return (RTN_FAILED);
    }

    /*
     *  Now unlink the file to guarantee that it will disappear
     *  should the client or server crash.
     */
    (void) unlink(path);

#ifdef SVR4
    pagesize = sysconf(_SC_PAGESIZE);
#else
    pagesize = getpagesize();
#endif

    /*
     *  Check the state of the file.  If the size of the file
     *  is insufficient to contain the first page of the shared
     *  retained info structure (ie < pagesize) report a failure.
     */
    if (fstat(filefd, &rstat) < 0) {
#ifdef DEBUG
        (void) fprintf(stderr, "_dga_rtn_map: unable get file status\n");
#endif
        (void) close(filefd);
        return (RTN_FAILED);
    }
    if (rstat.st_size < pagesize) {
#ifdef DEBUG
        (void) fprintf(stderr, "_dga_rtn_map: file not correct size, %ld\n",
                rstat.st_size);
#endif
        (void) close(filefd);
        return (RTN_FAILED);
    }

    /*
     *  Map the SHARED_RETAINED_INFO structure
     */
    infop = (SHARED_RETAINED_INFO *) mmap(0,
                            pagesize,
                            PROT_READ|PROT_WRITE,
                            MAP_SHARED,
                            filefd,
                            (off_t)0);

    if (infop == (SHARED_RETAINED_INFO *) -1) {
#ifdef DEBUG
	(void) fprintf(stderr, "_dga_rtn_map: unable to mmap file %s\n", 
		       path);
#endif
	(void) close(filefd);
	return (RTN_FAILED);
    }

    /*
     *  If the file is not actually a shared retained information file
     *  or its the wrong version, unmap the shared memory, close the
     *  file and return the error status.
     */
    if ((infop->magic != RTN_MAGIC) || (infop->version > RTN_VERS)) {
#ifdef DEBUG
	(void) fprintf(stderr, "_dga_rtn_map: contents of file %s incorrect\n", 
		       path);
#endif
        (void) munmap((caddr_t) infop, pagesize);
        (void) close(filefd);
	return (RTN_FAILED);
    }

    /* 
     *  Map the pixel page
     */
    pixels = (u_char *) mmap(0,
                        infop->s_size,
                        PROT_READ|PROT_WRITE,
                        MAP_SHARED,
                        filefd,
			(off_t)infop->first_mmap_offset);
 
    if (pixels == (u_char *) -1) {
#ifdef DEBUG
	(void) fprintf(stderr, "_dga_rtn_map: unable to mmap pixel area\n");
#endif
        (void) munmap((caddr_t) infop, pagesize);
        (void) close(filefd);
	return (RTN_FAILED);
    }

    /*
     *  Set the fields of the client information.
     */
    clientp->rtn_fd = filefd;
    clientp->rtn_size = infop->s_size;
    clientp->c_rtnseq = 0;
    clientp->s_rtnseq_p = &(infop->s_modified);
    clientp->c_rtncachseq = 0;
    clientp->s_rtncachseq_p = &(infop->s_cacheseq);
    clientp->rtn_info = (void *) infop;
    clientp->rtn_pixels = (void *) pixels;
    clientp->rtn_flags |= RTN_MAPPED;

#ifdef DEBUG
    _dga_rtn_dump(infop);
#endif

    return (RTN_PASSED);
#endif /* SERVER_DGA */
}

/*
 *
 *  _dga_rtn_unmap()
 *
 *  DGA Retained Window Unmap.  This function unmaps the retained window
 *  shared memory from the clients address space given the pointer to the 
 *  dga_window structure.  The pixel array associated with the retained info 
 *  structure is unmapped first followed by the shared retained info 
 *  structure.  The pointer to the shared memory info structure within the
 *  dga_window structure is set to NULL and the shared memory file is then 
 *  closed.  Should any operation fail zero is returned.
 *
 *  Inputs:     Dga_window - Pointer to the dga_window structure for which
 *			     the the shared retained info structure is to 
 *			     be removed.
 *
 *  Outputs:     0 - failed
 *		-1 - passed
 *
 *  Globals:    None.
 *
 *  Externals:  close()
 *		fprintf()	DEBUG ONLY
 *              getpagesize()   SUNOS ONLY
 *              munmap()
 *              sysconf()       SVR4  ONLY
 *              unlink()
 *
 */
int
_dga_rtn_unmap(clientp)
    _Dga_window	clientp;
{
    size_t	 pagesize;
    int		 status = 0;

    if ((clientp->rtn_flags & RTN_MAPPED) == 0)
	return (RTN_FAILED);

#ifndef SERVER_DGA
#ifdef SVR4
        pagesize = sysconf(_SC_PAGESIZE);
#else
        pagesize = getpagesize();
#endif

    if (munmap(clientp->rtn_pixels, clientp->rtn_size)) {
#ifdef DEBUG
	(void) fprintf(stderr, "_dga_rtn_unmap: pixel unmap failed\n");
#endif
	status++;
    }
    if (munmap(clientp->rtn_info, pagesize)) {
#ifdef DEBUG
	(void) fprintf(stderr, "_dga_rtn_unmap: info page unmap failed\n");
#endif
	status++;
    }
#endif /*SERVER_DGA */
    clientp->rtn_info = (void *) NULL;
    clientp->c_rtnseq = 0;
    clientp->s_rtnseq_p = (u_int *) &(clientp->s_rtnseq_p);
    clientp->c_rtncachseq = 0;
    clientp->s_rtncachseq_p = &(clientp->c_rtncachseq);
    clientp->rtn_pixels = (void*) NULL;
    (void) close(clientp->rtn_fd);
    clientp->rtn_fd = -1;
    clientp->rtn_flags &= ~(RTN_MAPPED);
    clientp->rtn_flags |= RTN_MAPCHG;
    if (status)
        return (RTN_FAILED);
    else
        return (RTN_PASSED);
}

#ifdef DEBUG
/*
 *
 *  _dga_rtn_dump()
 *
 *  DGA Retained Info Structure Dump.  This function prints out the contents
 *  of the shared retained info structure found at the specified address.
 *
 *  Inputs:     SHARED_RETAINED_INFO * - Pointer to the structure to dump.
 *
 *  Outputs:    None.
 *
 *  Globals:    None.
 *
 *  Externals:  printf()
 *              
 */
void
_dga_rtn_dump(infop)
    SHARED_RETAINED_INFO *infop;
{

    if (infop == (SHARED_RETAINED_INFO *) NULL) 
	(void) printf("NULL info pointer passed to _dga_rtn_dump\n");
    else {
	(void) printf("Retained window info page is %p\n", infop);
	(void) printf("\tmagic =\t\t%u\n", infop->magic);
	(void) printf("\tversion =\t%u\n", infop->version);
	(void) printf("\tobsolete =\t%u\n", infop->obsolete);
	(void) printf("\tdevice =\t%u\n", infop->device);
	(void) printf("\tcached =\t%u\n", infop->cached);
	(void) printf("\ts_cacheseq =\t%u\n", infop->s_cacheseq);
	(void) printf("\ts_modified =\t%u\n", infop->s_modified);
	(void) printf("\ts_wxlink =\t%p\n", infop->s_wxlink);
	(void) printf("\tfirst_mmap_offset =\t%u\n", infop->first_mmap_offset);
	(void) printf("\tdevice_offset =\t%u\n", infop->device_offset);
	(void) printf("\twidth =\t\t%d\n", infop->width);
	(void) printf("\theight =\t%d\n", infop->height);
	(void) printf("\tlineybtes =\t%u\n", infop->linebytes);
	(void) printf("\ts_fd =\t\t%d\n", infop->s_fd);
	(void) printf("\ts_size =\t%u\n", infop->s_size);
	(void) printf("\ts_pixels =\t%p\n", infop->s_pixels);
	(void) printf("\tfn = \t\t%s\n", infop->fn);
	(void) printf("\tscr_name = \t%s\n", infop->scr_name);
	(void) printf("\tc_fd =\t\t%d\n", infop->c_fd);
	(void) printf("\tc_size =\t%u\n", infop->c_size);
	(void) printf("\tc_pixels =\t%p\n", infop->c_pixels);
	(void) printf("\tc_modified =\t%u\n", infop->c_modified);
	(void) printf("\tc_cacheseq =\t%u\n", infop->c_cacheseq);
    }
}
#endif


void *
dga_win_bboxinfop(clientpi)
Dga_window clientpi;
{
    _Dga_window clientp = (struct dga_window *)clientpi;
    WXINFO *infop = (WXINFO *) clientp->w_info;

    if (infop->w_version < 2)
                return 0;
    return (void *) &(infop->w_window_boundary);
}
