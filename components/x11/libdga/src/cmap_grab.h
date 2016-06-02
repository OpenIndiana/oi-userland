/* Copyright (c) 1993, 1996, Oracle and/or its affiliates. All rights reserved.
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
 * cmap_grab.h - colormap grabber structures and information
 */

#ifndef _CMAP_GRAB_H
#define _CMAP_GRAB_H



/****
 *
 * Colormap grabber header file.
 *
 *
 *
 * Macros defined here:
 *
 *  sh_cm_lock(infop)
 *  sh_cm_unlock(infop)
 *	lock and unlock colormap info page.  'infop' is the Grabbedcmap
 *	pointer returned by cmapgrab_grab()
 *
 *  sh_cmapgrab_cookie(infop)
 *	returns the colormap info page cookie used to map the info page.
 *	this is the value that should be returned to the requesting
 *	client.
 *
 ****/


#include <sys/types.h>
#ifdef MT
#include <synch.h>
#endif

#include "dga.h"
#include "dga_internal.h"


/* method to use to load colormaps */

typedef enum {
	SUNWINDOWS_IOCTL=0,	/* use /dev/winxx SunWindows device driver */
	HW_DEVICE_IOCTL=1,	/* use graphics hardware device driver */
	HW_DEVICE_DIRECT=2	/* access hardware colormap directly */
} cmap_load_method;


#define	CMMAGIC	0x434d4150	/* "CMAP" */
#define	CMVERS	0

#define	MAX_CM_DEVNAME	40	/* better not have long device names */
#define DGA_CM_DEV_INFO_SZ 132

	/* device types, from sh_scr_dev.h */

#define	SCR_DEV_GENERIC	0	/* generic class implementations */
#define	SCR_DEV_MEM1	1	/* depth 1 memory framebuffer */
#define	SCR_DEV_MEM8	2	/* depth 8 memory framebuffer */
#define	SCR_DEV_MEM32	3	/* depth 32 memory framebuffer */

#define	SCR_DEV_CG2	4	/* Sun CG2 framebuffer (depth 8) */
#define	SCR_DEV_BW2	5	/* Sun BW2 framebuffer (depth 1) */
#define	SCR_DEV_CG4	6	/* Sun CG4 framebuffer (1 or 8) */
#define	SCR_DEV_CG6	7	/* Sun CG6 (Lego) */
#define	SCR_DEV_CG3	8	/* Sun CG3 (Color RoadRunner) */
#define	SCR_DEV_GPFB	9	/* GP1/GP+/GP2 framebuffer (depth 8) */
#define	SCR_DEV_GP	10	/* GP1/GP+/GP2 accelerator */
#define	SCR_DEV_CG5	11	/* Sun CG5 framebuffer (depth 8) */
#define SCR_DEV_CG8	12	/* Sun CG8 framebuffer (depth 8, 24 bit color)*/
#define SCR_DEV_GT      13      /* Sun GT (Hawk) depth 1, 8, and 24 bit */
#define SCR_DEV_CG12    14      /* Sun CG12 (Egret) depth 1, 8, and 24 bit */
#define SCR_DEV_REC     15      /* Recording device type */
#define SCR_DEV_SMC     16      /* Sun SMC/MDI (SPAM) depth 1, 8, 24-bit */

#define SCR_DEV_LAST    16


/* info in shared memory */

typedef	struct _grabbedcmap
{
    /* version 0 info starts here */
	long	cm_magic ;	/* "CMAP" = 0x434d4150 ("PAMC" on 386i) */
	long	cm_version ;	/* 0 */
	int	cm_count ;	/* change count */
	struct _grabbedcmap *cm_ptr ;	/* self-reference */
	u_long	cm_cmap ;	/* X11 colormap ID */

	u_long	cm_cookie ;	/* lock-page cookie */

	/* server-specific info, not meaningful to client */
	int	cm_sinfofd ;
	int	cm_sdevfd ;
	u_long	*cm_slockp ;
	u_long	*cm_sunlockp ;
	int	cm_slockcnt ;
	int	cm_clientcnt ;
	int	cm_filesuffix ;
	caddr_t	cm_shras ;

	char	cm_devname[MAX_CM_DEVNAME] ;
	char	cm_lockdevname[MAX_CM_DEVNAME] ;
	int	cm_default ;	/* is it the default colormap for this screen */
	int	cm_installed ;	/* flag: colormap is installed in HW */
	cmap_load_method cm_load_method ;   /* see typedef above */
	char	cm_sunwindows_def_devname[MAX_CM_DEVNAME] ; /* device name, */
	char	cm_sunwindows_def_cmapname[MAX_CM_DEVNAME] ;/* cmap name, and */
	int	cm_sunwindows_def_cmapsize; /* size of server's SunWindows
					       color map "xnews_default" */
	char	cm_sunwindows_inst_devname[MAX_CM_DEVNAME] ; /* device name, */
	char	cm_sunwindows_inst_cmapname[MAX_CM_DEVNAME];/* cmap name, and */
	int	cm_sunwindows_inst_cmapsize; /* size of server's SunWindows
					       color map "xnews_installed" */
	int	cm_fbtype ;	/* reserved */
	int	cm_reallen ;	/* colormap hardware size */
	int	cm_start ;	/* first valid location */
	int	cm_len ;	/* number of valid locations */
	int	cm_cmapnum ;	/* [0]cmap number - FB's with multiple maps */
	int	cm_ioctlbits ;	/* [0]high-order bits for FBIOPUTCMAP */
	int	cm_devtype ;	/* device hardware type */
	int	cm_reserved[5] ;/* reserved */

	long	cm_shadowofs ;	/* byte offset relative to cm_magic of
				   the start of the shadow colormap */

    /* version 1 info starts here */
	int	cm_scount ;	/* server's last remembered count */
	int	cm_locktype ;	/* using /dev/winlock? see below. */

    /* version 2 info starts here */
	u_int   device_offset;	/* offset to device specific section */

	/* Do NOT add any fields below dev_info */
	u_char  dev_info[DGA_CM_DEV_INFO_SZ];/* device specific information */
} Grabbedcmap ;


	/* followed by three arrays of u_shorts, length cm_len, for
	   red, green and blue and one array of bytes which are
	   the change flags for their respective colors:

		rr
		rr
		rr
		:
		gg
		gg
		gg
		:
		bb
		bb
		bb
		:
		f
		f
		f
		:
	    
	    Clients set a flag to non-zero to indicate that the color
	    has been changed.  The server clears these when the chagnes
	    have been seen. */

#define	CM_LOCKDEV	0	/* use GRABPAGEALLOC from device */
#define	CM_WINLOCK	1	/* use winlock functions */




typedef struct cmap_devlist{
	int fd;
	int refcnt;
	char devname[MAX_CM_DEVNAME];
	struct cmap_devlist *next;
} Cmap_Devlist;


#define CM_PAGESZ       (8*1024)
#define CM_LOCK(x)      (*(x)) = 1
#define CM_UNLOCK(x)    (*(x)) = 0


#define	wx_cm_lock(infop)		\
    do {				\
    if( (infop)->cm_lockcnt++ == 0 )	\
	*(infop)->cm_lockp = 1 ;	\
    } while (0)

#define	wx_cm_unlock(infop)		\
    do {				\
    if( --(infop)->cm_lockcnt == 0 )	\
	*(infop)->cm_unlockp = 0 ;	\
    } while (0)


#define CM_INFOP(clientp) ((Grabbedcmap *) ((clientp)->cm_info))

Dga_cmap	wx_cm_grab() ;

#endif /* _CMAP_GRAB_H */
