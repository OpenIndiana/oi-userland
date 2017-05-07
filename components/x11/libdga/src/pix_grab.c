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


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>
#include <netdb.h>
#ifdef SERVER_DGA
#include <X11/Xlib.h>
#else
#include <unistd.h>
#include <sys/fcntl.h>
#include <sys/mman.h>
#endif /* SERVER_DGA */

#include "dga_incls.h"
#include "pix_grab.h"



#define NDIGITS     8
#define MINSHMEMSIZE    (8*1024)
#define MAXSHMEMSIZE    (0x00040000)
#define MAXSHPXMEMSIZE    (0x01000000)
#define SHPX_MAX_CLIENTS    64
#define SHPX_MAX_PIXMAPS    341



/* Some structure definition for internal bookkeeping
 * NOTE: there is only one locking window created per device for
 * the use of all pixmaps on that device 
*/
typedef struct dga_pixlist {
    Dga_token       	p_token;     	  /* Token associated with pix */
    int             	num_clientp;
    struct dga_pixmap   *dga_clientplist; /*List of client ptrs in pix */
    struct dga_pixlist  *next_plist;  	  /* Next link in the dga list */
} *Dga_pixlist;

static struct dga_pixlist *dga_plist = NULL;
#ifdef SERVER_DGA
extern  SHPX_CLIENT_ENTRY    shpx_client_directory[];
extern  int                 Dga_shpx_client_count;
#else
static  SHPX_CLIENT_ENTRY   shpx_client_directory[SHPX_MAX_CLIENTS];
static  int                 Dga_shpx_client_count = 0;
#endif /* SERVER_DGA */
static u_long pagesize;

extern int _dga_winlockat(u_long cookie, int **lockp, int **unlockp);
extern int _dga_winlockdt(int *lockp, int *unlockp);
extern void *_dga_is_X_pixmap(Pixmap pix, Display **dpyp);

/******************************************
 *
 * dga_pix_grab:
 *
 *  create shared memory file for pixmap information
 *  map to lock page
 *
 *  arguments:
 *
 *  Dga_token   token;  INPUT
 *      magic cookie supplied by the server
 *
 *  returns a user virtual address for a dga_window structure.
 *  returns NULL if anything goes awry.
 *
 *****************************************/

Dga_pixmap
dga_pix_grab(token, pix)
    Dga_token   token;
    Pixmap  pix;
{
    SHARED_PIXMAP_INFO *infop;
    _Dga_pixmap clientp ;
    Display  *dpy;
    int c_fd, i, entry_found;
    u_int	port;
    size_t size;
    SHPX_DIRECTORY  *shpx_dir;
    char    c_fn[256];
    char   *dpystr;
    static char    path[256];
    char    host[MAXHOSTNAMELEN];
    Dga_lockp	lockp, unlockp;

    /* Remember to account for multiple clients grabbing the same pixmap
     * later
     */ 

    /* First determine if this is a X pixmap - if so, get 
     * the dpy and pixid
    */
    if (!_dga_is_X_pixmap(pix, &dpy)) {
#ifdef DEBUG
        (void) fprintf(stderr, "dga_pix_grab: Unsupported pixmap type\n");
#endif
        return (PIX_FAILED);
    }

    if (!dga_plist) {
	/* This is the first time through this code so get the
	 * retained path */
	if (!XDgaGetRetainedPath(dpy, pix, path)) {
#ifdef DEBUG
	    (void) fprintf(stderr, 
		"dga_pix_grab: XDgaGetRetainedPath failed\n");
#endif
	    return (PIX_FAILED);
	}	
    }
#ifndef SERVER_DGA
    /*  Now get the port number for this display */
    dpystr = DisplayString(dpy);
    if (dpystr[0] == ':')
        (void) sscanf(dpystr, ":%u", &port);
    else
        (void) sscanf(dpystr, "%[^:]:%u", host, &port);

    if (Dga_shpx_client_count == 0) {
    	/* Now start by initializing all the per client structs - 
    	 * all 64 of them  - if thie is the first time you 
    	 * are grabbing  a pixmap
    	*/
        for (i = 0; i < SHPX_MAX_CLIENTS; i++) {
        	shpx_client_directory[i].cid = 0;
        	shpx_client_directory[i].shpx_directory = NULL;
        	shpx_client_directory[i].fd = 0;
        	shpx_client_directory[i].size = 0;
        	shpx_client_directory[i].npix = 0;
        }
    } else 
#endif /* SERVER_DGA */
    {
    	/* If it is not the first time, see if this client has grabbed
	 * a pixmap before and therefore done all the set up.
	 * Search through the client structures for matching token
	 */
        i = 0;
        while ((i < SHPX_MAX_CLIENTS) &&
        	(shpx_client_directory[i].cid != token)) {
            i++;
	}
        if ((i == SHPX_MAX_CLIENTS) &&
        	(Dga_shpx_client_count == SHPX_MAX_CLIENTS)) {
            return(0);
        }
    }
    
    if ((Dga_shpx_client_count > 0) && (i < SHPX_MAX_CLIENTS)) {
	/* We found a match and the pixmap already has been grabbed before */
        shpx_dir = shpx_client_directory[i].shpx_directory;
	shpx_client_directory[i].npix++;
    } 
#ifndef SERVER_DGA
    else {
	/* This client has Never grabbed before set up the direct 
	 * structure etc.
         * Open the shared file using server command line 
	 * -sharedretainedpath variable for file path if it is 
	 * set, else use /tmp.  This is because these files can 
	 * be very big and there usually isn't much space in /tmp.
         */
        c_fn[0] = 0;


        if ((path) && (strlen(path) > 0))
	    strcpy(c_fn, path);
         else 
	    strcpy(c_fn, "/tmp");

        strcat(c_fn, PIX_FILE);
        size = strlen(c_fn);
        sprintf(c_fn+size,"%01x.%08x", port, token);
 
#ifdef SYSV
        pagesize = sysconf(_SC_PAGESIZE);
#else
        pagesize = getpagesize();
#endif
        i = 0;
        while ((i < SHPX_MAX_CLIENTS) && (shpx_client_directory[i].cid != 0))
        	i++;
        if (i >= SHPX_MAX_CLIENTS)
        	return(0);
        if ((c_fd = open(c_fn,O_RDWR ,0666)) < 0) 
        	return(0);
        /* map the shpx directory for this client and map at 4 megabytes */
        shpx_dir =   (SHPX_DIRECTORY *)mmap(0,
                MAXSHPXMEMSIZE,
                PROT_READ|PROT_WRITE,
                MAP_SHARED,
                c_fd,
                (off_t)0);
 
        if (shpx_dir == (SHPX_DIRECTORY *)-1) {
	    close(c_fd);
	    return(0);
        }
        Dga_shpx_client_count++;
        shpx_client_directory[i].cid = token; /* BMAC - correct?? */
        shpx_client_directory[i].shpx_directory = shpx_dir;
        shpx_client_directory[i].fd = c_fd; /* no longer need to save it */
	shpx_client_directory[i].size = shpx_dir[0].shpx_entry_0.s_size;
	shpx_client_directory[i].npix = 1;
    }
#endif /* SERVER_DGA */

    /* The first 2 entries on the file have special meaning. */
    i = 2;
    entry_found = 0;
    while ((i < SHPX_MAX_PIXMAPS) && (!entry_found)) {
	if (shpx_dir[i].shpx_entry.xid == pix) 
	    entry_found = 1;
        else 
	    i++;
    }
 
    if (!entry_found) {
#ifndef SERVER_DGA
        close(c_fd);
#endif /* SERVER_DGA */
        return(0);
    }
    infop = (SHARED_PIXMAP_INFO *)
            (((u_char *)shpx_dir) + shpx_dir[i].shpx_entry.offset);
 
    if ((infop->magic != PXMPMAGIC) || (infop->version > PXMPVERS)) {
#ifndef SERVER_DGA
        close(c_fd);
#endif /* SERVER_DGA */
        return(0);
    }
    if (infop->obsolete) {
#ifndef SERVER_DGA
        close(c_fd);
#endif /* SERVER_DGA */
        return(0);
    }
    /* BMAC - Find out about the rache code - what should I do there? */

    /* Now fill out the Dga_pixmap structure */
    if( (clientp = (_Dga_pixmap) malloc(sizeof(struct dga_pixmap))) == NULL )
        return NULL ;

    clientp->drawable_type = DGA_DRAW_PIXMAP;
    clientp->p_lockcnt = 0;
    clientp->obsolete = 0;
    clientp->p_modif = NULL;
    clientp->p_infop = (void *)infop ;
    clientp->c_chngcnt[0] = 0; 
#ifdef MT
    clientp->shadow_chngcnt[0] = 0;
#endif
    /* This is the new location added for locking performance
     * For windows it pts to the second member in the c_wm_chngcnt
     * array but here I think that it just pts to the previous field
     * since for pixmaps the array ctr is -1 always
    */
    clientp->p_chngcnt_2nd = clientp->c_chngcnt +1;

    clientp->s_chngcnt_p = &(infop->s_modified);	
    clientp->c_dirchngcnt = shpx_dir[1].shpx_entry_1.s_dir_seq;
    clientp->s_dirchngcnt_p = &(shpx_dir[1].shpx_entry_1.s_dir_seq);
    clientp->c_devinfocnt = 0;
    clientp->s_devinfocnt_p = &(infop->s_devinfoseq);
    clientp->c_cachecnt = 0;
    clientp->s_cachecnt_p = &(infop->s_cacheseq);	
    clientp->c_cached = 0;
    clientp->s_cached_p = &(infop->cached);	
    clientp->p_dir_index = i;
    clientp->p_shpx_dir = (void *)shpx_dir; /*CHECK ME */
#ifdef MT
    if (dgaThreaded) {
	clientp->p_unlock_func = dgai_unlock;
    } else {
	clientp->p_unlock_func = NULL;
    }
#else
    clientp->p_lock_func = NULL;
    clientp->p_unlock_func = NULL;
#endif
    clientp->p_update_func = dgai_pix_update;
    clientp->p_shpx_client = NULL;
    clientp->p_token = token;
    clientp->c_size = infop->s_size;
    clientp->c_pixels = (u_char *)(infop + 1);
    clientp->depth = infop->depth;
    clientp->linebytes = infop->linebytes;
    clientp->p_next = NULL;
    clientp->p_infofd = NULL;
    clientp->pix_flags = PIX_NOTICE_CLIPCHG;	
    clientp->p_dpy = 0;
    clientp->p_id = NULL;
    clientp->p_client = NULL;
    clientp->changeMask = NULL;
    clientp->siteChgReason = NULL;
    clientp->siteNotifyFunc = NULL;
    clientp->siteNotifyClientData = NULL;

#ifdef SERVER_DGA
    clientp->p_lockp = infop->p_lockp;
    clientp->p_unlockp = infop->p_unlockp;
#else
    lockp = NULL;	/* init to NULL for check below */
    unlockp = NULL;

    /* Check to see if there are already a lockp and unlockp 
     * for this device--if not create 'em
    */
    if (dga_plist) {
	lockp = dga_plist->dga_clientplist->p_lockp;
	unlockp = dga_plist->dga_clientplist->p_unlockp;
    }

    if (!lockp) {
	/* only get new lock pages if necessary */
        if( _dga_winlockat(infop->p_cookie, &lockp, &unlockp) != 0 ) {
            munmap((caddr_t)infop, MAXSHPXMEMSIZE);
/* REMIND Daryl: What else do we need to clean up? */
            free(clientp) ;
            return(NULL);
        }
    }

    clientp->p_lockp = lockp;
    clientp->p_unlockp = unlockp;
#endif /* SERVER_DGA */

    /* add to linked list of grabbed pixmaps - for internal bookkeeping
    */
    if (!dga_plist) {
       if ((dga_plist =
	    (Dga_pixlist) malloc(sizeof(struct dga_pixlist))) == NULL )
            return NULL ;
       	dga_plist->p_token = token;
       	dga_plist->num_clientp = 1;
       	dga_plist->dga_clientplist = clientp;
       	dga_plist->next_plist = NULL;
    } else {
       struct dga_pixlist *new_plist;

       if ((new_plist =               
                   (Dga_pixlist) malloc(sizeof(struct dga_pixlist))) == NULL )
        return NULL;
       new_plist->p_token = token;
       new_plist->num_clientp = 1;
       new_plist->dga_clientplist = clientp;
       new_plist->next_plist = dga_plist;
       dga_plist = new_plist;
    }
#ifdef MT
    if (dgaThreaded) {
	clientp->mutexp = &dgaGlobalPixmapMutex;
    } else {
	clientp->mutexp = NULL;
    }
#endif
    return ((Dga_pixmap) clientp);
}

void
dga_pix_ungrab(clientpi)
Dga_pixmap clientpi;
{
    _Dga_pixmap clientp = (struct dga_pixmap *)clientpi;
    Dga_pixlist	prev_pixlist = NULL;
    Dga_pixlist pixlist = dga_plist;
    u_int	i;
    
    /* Find pixmap in dga_plist */
    while (pixlist) {
	if (pixlist->dga_clientplist == clientp) {
#ifndef SERVER_DGA
            i = 0;
            while ((i < SHPX_MAX_CLIENTS) &&
        	    (shpx_client_directory[i].cid != pixlist->p_token)) {
                i++;
	    }
            if (i >= SHPX_MAX_CLIENTS) {
                return;
            }
	    shpx_client_directory[i].npix--;
	    if (!shpx_client_directory[i].npix) {
		munmap((caddr_t)shpx_client_directory[i].shpx_directory, 
		       MAXSHPXMEMSIZE);
		close(shpx_client_directory[i].fd);
		shpx_client_directory[i].cid = 0;
		shpx_client_directory[i].shpx_directory = NULL;
		shpx_client_directory[i].fd = 0;
		shpx_client_directory[i].size = 0;
	    }	
#endif /* SERVER_DGA */

	    if (prev_pixlist)
	        prev_pixlist->next_plist = pixlist->next_plist;
            else
		dga_plist = pixlist->next_plist;
#ifndef SERVER_DGA
            if (!dga_plist)  {
                _dga_winlockdt(clientp->p_lockp, clientp->p_unlockp);
            }
#endif /* SERVER_DGA */
	    free(pixlist);
	    free(clientp);
		if(--Dga_shpx_client_count < 0) 
			Dga_shpx_client_count = 0;
	    return;
        } else {
	    prev_pixlist = pixlist;
	    pixlist = pixlist->next_plist;
        }
    }
}

#ifdef COMMENT
/* TODO: Daryl what is this routine supposed to be used for??? */
int 
dga_pix_sync(clientpi)
Dga_pixmap clientpi;
{
    _Dga_pixmap clientp = (struct dga_pixmap *)clientpi;
	/* this checks to see if the shared pixmap info
	 * area has changed and if so reinits the data
	*/
	/* This routine seems to requoire that the handle have
	1. if the pixmap is cached or not
	2. what type the pixmap is = like retained one??
	3. something called sh_rache_scr0, sh_rache_scr1;
	4. something called sh_Scr_Virt[];      virtual screen table */
}
#endif

int 
dga_pix_cachechg(clientpi)
Dga_pixmap clientpi;
{
    _Dga_pixmap clientp = (struct dga_pixmap *)clientpi;
    
    if (clientp->c_cachecnt != *(clientp->s_cachecnt_p)) {
	/* Something changed */
	clientp->c_cachecnt = *(clientp->s_cachecnt_p);
	return 1;
    } else
	/* Nothing has changed */
	return 0;
}

int 
dga_pix_cached(clientpi)
Dga_pixmap clientpi;
{
    _Dga_pixmap clientp = (struct dga_pixmap *)clientpi;

    if (clientp->c_cached != *(clientp->s_cached_p)) {
	/* Something changed */
	clientp->c_cached = *(clientp->s_cached_p);
	return 1;
    } else
	/* Nothing has changed */
	return 0;
}

char *
dga_pix_devname(clientpi)
Dga_pixmap clientpi;
{
    _Dga_pixmap clientp = (struct dga_pixmap *)clientpi;
    /* CHECK THIS ! */
    return ((char *) PIX_INFOP(clientp)->scr_name);
}

void * 
dga_pix_pixels(clientpi)
Dga_pixmap clientpi;
{
    _Dga_pixmap clientp = (struct dga_pixmap *)clientpi;
    
    return ((void*)clientp->c_pixels);
}

int 
dga_pix_linebytes(clientpi)
Dga_pixmap clientpi;
{
    _Dga_pixmap clientp = (struct dga_pixmap *)clientpi;
    
    return (clientp->linebytes);
}


u_char 
dga_pix_depth(clientpi)
Dga_pixmap clientpi;
{
   _Dga_pixmap clientp = (struct dga_pixmap *)clientpi; 
    return (clientp->depth);
}

void * 
dga_pix_devinfo(clientpi)
Dga_pixmap clientpi;
{
    _Dga_pixmap clientp = (struct dga_pixmap *)clientpi;
    return (((char *)clientp->p_infop) + PIX_INFOP(clientp)->device_offset);
}

