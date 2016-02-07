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


#ifndef _DGA_PIXSHARED_H
#define _DGA_PIXSHARED_H

/*
 * dga_pixshared.h - Sun Direct Graphics Access shared page include file.
 */

/* Below is the definition of the pixmap shared page structure plus all
 * the other misc. definitions and structures that are used in both the
 * server and dga client library.
 *
 *  Shared Pixmap Information.  This structure contains the information
 *  necessary to allow the server and client to share access to a DGA
 *  pixmap .  This information is located in the first page of
 *  the shared memory created by the server in response to a call to
 *  XDgaGrabPixmap().  The server communicates the current state
 *  of the shared pixmap to the client through the fields within
 *  this structure.
 */

typedef u_int *PX_LOCKP_T;

#define PXMPMAGIC 0x50584D50 /* "PXMP"=0x50584D50 */
#define PXMPVERS        0       /* Current version number */

typedef struct shpx_entry_0 {
    u_int s_fd;           /* server's file descriptor */
    u_int offset;         /* offset to first pixmap info struct*/
    u_int s_size;         /* current total file size */
} SHPX_ENTRY_0;

typedef struct shpx_entry_1 {
    int   s_num_shpx;     /* current number of shared pixmaps */
    u_int s_dir_seq;      /* server's shpx directory change cnt*/
    u_int s_next_offset;  /* server's next avail offset */
} SHPX_ENTRY_1;

typedef struct shpx_entry {
    u_int xid;            /* xid of shared pixmap */
    u_int offset;         /* offset to info struct */
    u_int size;           /* total size of this pixmap */
} SHPX_ENTRY;

typedef union shpx_directory {
    SHPX_ENTRY_0 shpx_entry_0;
    SHPX_ENTRY_1 shpx_entry_1;
    SHPX_ENTRY shpx_entry;
} SHPX_DIRECTORY;

typedef struct shared_pixmap_info {
    u_int   magic;        /* magic number, "PXMP"=0x50584D50 */
    u_char  version;      /* version, currently 0 */
    u_char  obsolete;     /* pixmap info obsolete flag */
    u_char  device;       /* device type identifier from fbio.h ???*/
    u_char  cached;       /* 1 = pixels cached on hw; 0 = pixels in mem */
    u_int   s_cacheseq;   /* server's cache sequence count */
    u_int   s_modified;   /* server has changed this data struct*/
    u_int   data_offset;  /* offset to pixel data */
    u_int   device_offset;      /* offset to device specific section */
    short   width;        /* pixmap width */
    short   height;       /* pixmap height */
    u_int   linebytes;    /* bytes per scanline */
    u_char  depth;        /* pixmap depth */
    u_char  bitsperpixel;   /* pixmap bitsPerPixel */
    u_char  pad1[2];        /* Unused pad area */
    u_int   s_fd;         /* server's file descriptor */
    u_int   s_size;       /* server's size of pixel array */
    u_int   s_dir_index;  /* server's shpx directory index */
    SHPX_DIRECTORY  *s_shpx_dir;    /* server's pointer to shpx dir */
    u_char  *s_pixels;    /* server shared pixel memory pointer*/
    u_char  scr_name[32]; /* screen name for cached pixmap */
    u_char  fn[256];      /* Shared file name */
    u_int   p_refcnt;     /* for nested locking */
    PX_LOCKP_T   p_lockp;       /* pointer to lockpage */
    PX_LOCKP_T   p_unlockp;     /* pointer to unlockpage */
    uint32_t  p_cookie;        /* "cookie" for lock pages */
    int     locktype;       /* type of locking */
    u_int   s_devinfoseq;   /* indicates change to dev_info */
    /* DO NOT ADD ANYTHING BELOW dev_info  - if you need to any any
     * thing, do so after this line and above dev_info
    */
    char dev_info[32];    /* device specific information */
} SHARED_PIXMAP_INFO;

#endif /* _DGA_PIXSHARED_H */
