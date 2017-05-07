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
 * dga_winshared.h - Sun Direct Graphics Access shared page include file.
 */

#ifndef _DGA_WINSHARED_H
#define _DGA_WINSHARED_H

#include "dga_externaldefs.h"
#include <sys/int_types.h>



/* Mbufset Shared Info format */
typedef struct dga_mbufset_shinfo {
    unsigned int    mbufseq;        /* incremented on composition or display
                                     * change */
    unsigned int    compositionseq; /* incremented on composition change */
    unsigned char   enabled;        /* nonzero if an mbufset is active */
    unsigned char   flipMode;       /* 0 = video flip; 1 = copy flip */
    unsigned char   accessMode;     /* 0 = single addr; 1 = multi addr */
    unsigned char   siteTypeConst;  /* zero if access mode can change */
    uint32_t		bufViewableFlags; /* bit n is 1 if buf n is viewable */
    unsigned int    nmbufShpxToken; /* token for shared pixmap file nonviewable
                                     * multibuf */
    XID             nmbufIds[DGA_MAX_GRABBABLE_BUFS];   /* XID's of nonviewable
                                                         * mbufs */
#if !defined(_LP64) && !defined(_I32LPX)
	int				pad_bufIds[DGA_MAX_GRABBABLE_BUFS];
#endif
} DgaMbufSetShinfo, *DgaMbufSetShinfoPtr;


/*
 * This portion of the file file describes the shared memory info page 
 * used by the window
 * grabber.  Many of the structures are shapes specific, and their
 * definitions are copied from shapes #include files.  If the shapes
 * structures are changed, then this file would be messed up; but
 * if that happens, a lot of other things would get messed up too, so
 * let's hope that it never happens.
 *
 * This structure is defined in such a way as to allow expansion.  In
 * particular, the field 'w_clipoff' contains the offset, in bytes, of
 * the clip data relative to the start of the window information area.
 * Do not attempt to refer directly to the 'w_shape_hdr' element of
 * this structure, as that can cause old executables to break with new
 * servers.
 *
 * Here is a brief description of the WXINFO structure elements
 * which are relavent to the client:
 *
 *      w_flag          set to WMODIF by the server whenever any field
 *                      in the window info area is changed.  Set back to
 *                      WSEEN by the client once the info has been read.
 *                      The window-info area should be locked while examining
 *                      this flag and copying information from the
 *                      window-info area.
 *      w_magic         Set to 0x47524142 ("GRAB").
 *      w_version       version of window-info area.  This header file
 *                      currently describes version 1.  Programs should
 *                      check the version number and either refuse to run
 *                      with older versions or at least be careful not to
 *                      use fields not defined in older versions.  The
 *                      comments in the WXINFO structure definition will
 *                      show you which these are.
 *      w_devname       Ascii device name.  Let's hope there's never a
 *                      framebuffer with a filename larger than 20 characters.
 *      w_cinfofd       File descriptor of wininfo file.  This file has
 *                      been mmap'ed, so there is no reason for the
 *                      application to need to use this.
 *      w_cdevfd        File descriptor of the framebuffer named in w_devname.
 *      w_crefcnt       Lock count for nested locking.
 *      w_cookie        Internal use only.  NOT related to the window cookie
 *                      that was returned by X_GrabWindow().
 *      w_clockp        pointer to lockpage, used by wx_lock().
 *      w_clipoff       Byte offset from start of info page to start of
 *                      clip list.
 *      w_clipsize      size of cliplist.
 *      w_org, w_dim    window dimensions, i.e. bounding box of whole window
 *                      In 16-bit signed fract format.
 *      w_shape         cliplist info
 *      w_depth         depth of window
 *      w_borderwidth   server's idea of the window's bw. This need not be
 *                      equal to what the client requested since
 *                      something like OLWM could override the client
 *                      request and the clinet now has wrong bw.
 *
 * Interpreting the clip info:
 *
 *  The client is interested in the following structures:
 *    w_shape_hdr       pointed to via the wx_clipinfo macro.
 *    w_shape           contains flags and a bounding-box for the cliplist.
 *    cliparray         follows w_shape.  Contains the clip list.
 *
 *  w_shape.SHAPE_FLAGS contains flags that describe the cliplist.  If
 *  DGA_SH_EMPTY_FLAG is set, then the clip list is empty (window obscured or
 *  something).
 *
 *  If DGA_SH_RECT_FLAG is set, the clip list is a single rectangle
 *  described by w_shape->SHAPE_{XMIN,YMIN,XMAX,YMAX}.
 *
 *  For non-empty cliplists, use the dga_win_clipinfo(win) routine to get
 *  a pointer to the cliplist.
 *
 *  "Normal" cliplists are a sequence of signed shorts which describes
 *  a sequence of rectangles.  The data consists of a sequence of one
 *  or more ymin,ymax pairs, each of which is followed by a sequence of
 *  one or more xmin,xmax pairs.  xmin,xmax sequences are terminated by
 *  a single value of DGA_X_EOL.  ymin,ymax sequences are terminated by a
 *  single value of DGA_Y_EOL.  This is best described with some sample
 *  code:
 *
 *      short x0,y0,x1,y1;
 *
 *      ptr = dga_win_clipinfo(win);
 *      while( (y0=*ptr++) != DGA_Y_EOL )
 *      {
 *        y1 = *ptr++;
 *        while( (x0=*ptr++) != DGA_X_EOL )
 *        {
 *          x1 = *ptr++;
 *          printf("rectangle from (%d,%d) to (%d,%d)\n",x0,y0,x1-1,y1-1);
 *        }
 *      }
 *
 *  Note that the xmax, ymax values are actually one pixel too high.  This
 *  may be a bug or a feature, I don't know.
 *
 */

#define DGA_DB_DEV_INFO_SZ  132

#if !defined (WMODIF)               /* cliplist flag, one of: */
#define WMODIF      1               /* server has set a new cliplist */
#define WEXTEND     2               /* extended cliplist present    */
#define WXMAGIC     0x47524142      /* "GRAB" */
#endif  /* WMODIF */

#define WX_PAGESZ   (8*1024)


typedef struct {
    unsigned int    t;
    int             x, y;
} POINT_B2D;


typedef struct {
    short   x, y;
} Dga_coord_2d;


#if !defined (_SH_CLASS)
#if defined(_LP64) || defined(_I32LPX)
typedef int OBJID;
typedef OBJID   CLASS_OPER;
#else
typedef void    *OBJID;
typedef OBJID   (*CLASS_OPER)();
#endif


typedef struct {
    unsigned char   type;
    unsigned char   id;
} CLASS;


struct  obj_hdr {
    unsigned int    obj_flags :  8;
    unsigned int    obj_size  : 24;
    CLASS           obj_class;
    unsigned short  obj_use;
    CLASS_OPER     *obj_func;
#if !defined(_LP64) && !defined(_I32LPX)
	int32_t        pad_func;
#endif
};
#endif  /* _SH_CLASS */


#if !defined (_SH_SHAPE_INT)
struct  class_SHAPE_vn {
    unsigned char   SHAPE_FLAGS;
    unsigned char   SHAPE_SIZE;     /* new with 1.1 */
    short           SHAPE_YMIN;
    short           SHAPE_YMAX;
    short           SHAPE_XMIN;
    short           SHAPE_XMAX;
    short           SHAPE_X_EOL;
#if 0
#if !defined(_LP64) && !defined(_I32LPX)
	char 			pad_to_y_eol[2];
#endif
#endif
    union {
        short   SHAPE_Y_EOL;
        OBJID   obj;                /* new with 1.1 */
    } u;
#if 0
#if !defined(_LP64) && !defined(_I32LPX)
	int32_t        pad_obj;
#endif
#endif

#define shape_obj           u.obj
#define shape_xeol          SHAPE_X_EOL
#define shape_yeol          u.SHAPE_Y_EOL
#define SHAPE_RECT_SIZE     (6 * sizeof (short))
#define SHAPE_NO_SIZE       0xFF
};
 
struct  class_SHAPE_v0 {
    unsigned char   SHAPE_FLAGS;
    short           SHAPE_YMIN;
    short           SHAPE_YMAX;
    short           SHAPE_XMIN;
    short           SHAPE_XMAX;
    short           SHAPE_X_EOL;
    short           SHAPE_Y_EOL;
};
#endif  /*_SH_SHAPE_INT*/


/* Cursor Grabber defines and structures */

#define DGA_CURSOR_DOWN     0
#define DGA_CURSOR_UP       1
#define DGA_CURG_MAGIC      0x43555247


typedef struct dga_curs_mpr {
    u_int           curg_linebytes;
    Dga_coord_2d    curg_dim;
    u_char          curg_depth;
    /* image data floats under here */
} Dga_curs_mpr;


typedef struct dga_cursinfo
{
    u_int           c_magic;        /* magic no, "CURG"=0x43555247 */
    u_int           c_filesuffix;   /* to derive cursor grabber filename */
    uint32_t		c_pad;          /* No longer used */
    int             c_scurgfd;      /* file descriptor for server */
    int             c_ref_cnt;      /* total number of cur-grabbers*/
    int             c_state_flag;   /* client/server can set this */
    u_int           c_chng_cnt;     /* Change count */
    int             c_index;        /* entry no. in global array */
    Dga_coord_2d    c_org;          /* top left */
    Dga_coord_2d    c_hot_spot;     /* why bother with this? */
    int             c_offset;       /* offset in bytes from top of
                                     * page to save_under info */
    Dga_curs_mpr    *c_sptr;        /* server's ptr to save_unders*/
    u_int           c_cookie;       /* "cookie" for lock pages */
#if defined(_LP64) || defined(_I32LPX)
    void*           c_slockp;       /* all windows on this screen use */
    void*           c_sunlockp;     /* the same lock context */
#else
    void*           c_slockp;       /* all windows on this screen use */
    void*           c_sunlockp;     /* the same lock context */
#endif
    int             c_locktype;
    int             c_smemsize;     /* number of bytes for saved cursor */
 
    /*
     * FLOATING INFO STARTS HERE, CLIENT DO NOT
     * REFER DIRECTLY TO ANYTHING BELOW THIS LINE.
     */
 
    Dga_curs_mpr    c_saved_under;  /* this gets puts back up */

} Dga_cursinfo;


typedef struct wx_dbinfo {
        short   number_buffers;
        short   read_buffer;
        short   write_buffer;
        short   display_buffer;
        u_int   reserved_1;
        u_int   reserved_2;
        u_int   reserved_3;
        u_int   reserved_4;
        u_int   reserved_5;
        u_int   WID;            /* Mpg window id. */
        u_int   UNIQUE;
        u_char  device_info[DGA_DB_DEV_INFO_SZ];
} DBINFO;

/* Ancillary Buffers ... */
#ifndef True
#define True  1
#define False 0
#endif

#ifndef DGA_NUM_BUFFER_TYPES
/* The following buffer types also defined(duplicated) in dga.h file.
 * I can't include dga.h in hw/solaris/dga due to some declarations 
 * inconsistency.  Whenever someone changes/addes/deleted
 * to this enumerated values, please also update dga.h which is located
 * in xc/include/dga/.  Also ddx uses this. 
 */
typedef enum {
   DGA_DEPTH_BUFFER = 0,
   DGA_STENCIL_BUFFER,
   DGA_ACCUM_BUFFER,
   DGA_ALPHA_BUFFER,
   DGA_BACK_BUFFER,
   DGA_AUX_BUFFER0,
   DGA_AUX_BUFFER1,
   DGA_AUX_BUFFER2,
   DGA_AUX_BUFFER3
} Dga_buffer_type;
 
#define DGA_NUM_BUFFER_TYPES (DGA_AUX_BUFFER3+1)
#endif
 
/* dga_buffer:  This structure will contain pDraw pointer and
 * buffer_site as his first two members, since all the buffer
 * API's type case the pointer to dga_buffer and dereference
 * the buffer_site value.
 *   pDraw        ->  Will be assigned at the client side.
 *   buffer_site  ->  Software Buffers - DGA_SITE_SYSTEM
 *                    Hardware Buffers - DGA_SITE_DEVICE 
 *   fn           ->  shared of file name of the specified buffer.
 *   buffer_type  ->  Type of the buffer.
 *   sitechg      ->  Initialized to DGA_SITECHG_INITIAL when the
 *                    buffer is created. When the buffer is getting
 *                    reallocated, this will have DGA_SITECHG_CACHE.
 *   bitsPerPixel ->  depth of the buffer 
 *   bytesPerPixel->  (bitsPerPixel +7) >> 3
 *   width        ->  buffer width (Window's width)
 *   height       ->  buffer height (Window's height)
 *   linebytes    ->  ((bytesPerPixel * width) + 3) & ~3
 *   b_offset     ->  offset to data member from buffer address 
 *   allocsize    ->  Shared file size.
 *   data         ->  Buffer data bits pointer.
 *   pad	  ->  Padding to make sure it is 64-bit aligned, for now.
 */
typedef struct {
#if defined(_LP64) || defined(_I32LPX)
    void 				*pDraw;
#else
    void*               pDraw;
	int					pad_pdraw;
#endif
    Bool                buffer_site;
    int                 buffer_type;
    Bool                sitechg;
    int                 grab_cnt;
    u_char              fn[256];
    int                 width;
    int                 height;
    int                 bitsPerPixel;
    int                 bytesPerPixel;
    int                 linebytes;
    int                 b_offset;
    int                 allocsize;
#if defined(_LP64) || defined(_I32LPX)
    uint32_t               data;
#else
    void*               data;
#endif
    char		pad[4];
} dga_buffer_rec, * dga_buffer;


typedef struct {
#if defined(_LP64) || defined(_I32LPX)
    dga_buffer bufferp;
    void	*pDraw;
#else
    dga_buffer bufferp;
	int			pad_bufferp;
    void *pDraw;
	int			pad_pdraw;
#endif
    int   buf_size;
} dga_internal_buffer_rec, *dga_internal_buffer;


/* ABINFO:  This structure contains buffer pointers and their
 * respective filenames.  
 * s_modified  -> Will be set to "1" when the buffer is resized.
 * remap_flag  -> This is used across server and client dga implementation
 * buffer_swap -> swap counter.
 */
 
typedef struct wx_abinfo {
    int                 s_modified;
    u_int               buffer_swap; 
    int                 width;  /* width & height are used to detect resize */
    int                 height;
    u_char              back_fn[256];
    u_char              depth_fn[256];
    u_char              stencil_fn[256];
    u_char              accum_fn[256];
    u_char              alpha_fn[256];
#if defined(_LP64) || defined(_I32LPX)
    dga_buffer          back;
    dga_buffer          depth;
    dga_buffer          stencil;
    dga_buffer          accum;
    dga_buffer          alpha;
#else
    dga_buffer          back;
	int					pad_1_bufinfo;
    dga_buffer          depth;
	int					pad_2_bufinfo;
    dga_buffer          stencil;
	int					pad_3_bufinfo;
    dga_buffer          accum;
	int					pad_4_bufinfo;
    dga_buffer          alpha;
	int					pad_5_bufinfo;
#endif
    Bool                extPixmap;
#if !defined(_LP64) && !defined(_I32LPX)
	int					pad_pix;
#endif
    XID                 tag;
#if !defined(_LP64) && !defined(_I32LPX)
	int					pad_tag;
#endif
    XID                 vid;
#if !defined(_LP64) && !defined(_I32LPX)
	int					pad_vid;
#endif
    int                 back_size;
    int                 depth_size;
    int                 stencil_size;
    int                 accum_size;
    int                 alpha_size;
} ABINFO;

typedef struct  wx_winfo
{
    /* VERSION 0 INFO STARTS HERE */

    uint32_t      w_flag;         /* cliplist flag */
    int32_t        w_magic;        /* magic number, "GRAB" = 0x47524142 */
    int32_t        w_version;      /* version, currently 4 */
#if defined(_LP64) || defined(_I32LPX)
    uint32_t      w_cunlockp;     /* used to be w_list */
                                /* points to unlock page */
#else
    u_int      *w_cunlockp;     /* used to be w_list */
                                /* points to unlock page */

#endif
    /* server info, meaningless to client */

    int         w_sinfofd;      /* fd of wxinfo file */
    int         w_sdevfd;       /* fd of framebuffer */
#if defined(_LP64) || defined(_I32LPX)
    uint32_t      w_slockp;       /* pointer to lockpage */
#else
    u_int      *w_slockp;       /* pointer to lockpage */
#endif
    int         w_srefcnt;      /* lock count for nested locks */


    /* client info */

    char        w_devname[20];  /* framebuffer device name */
    int         w_cinfofd;      /* fd of wxinfo file */
    int         w_cdevfd;       /* fd of framebuffer */
    int         w_crefcnt;      /* lock count for nested locks */

    uint32_t      w_cookie;       /* "cookie" for lock pages */
    uint32_t      w_filesuffix;   /* "cookie" for info file */
#if defined(_LP64) || defined(_I32LPX)
    uint32_t      w_clockp;       /* pointer to lock page */
#else
    u_int      *w_clockp;       /* pointer to lock page */
#endif


    /* clipping info */

#if defined(_LP64) || defined(_I32LPX)
    uint32_t	w_cclipptr;     /* client virtual pointer to clip array. */
#else
    short      *w_cclipptr;     /* client virtual pointer to clip array. */
#endif
    u_int       w_scliplen;     /* server's size of cliplist in bytes. */


    /* shapes stuff */
    
    POINT_B2D   w_org;          /* origin of window */
    POINT_B2D   w_dim;          /* size of window */


    /* VERSION 1 INFO STARTS HERE */
#if !defined(_LP64) && !defined(_I32LPX)
	char		pad_to_union[4];
#endif

    union {
        struct {
            int32_t    w_clipoff;  /* byte offset from wx_info to w_cliparray. */
            int32_t    w_shapeoff; /* byte offset from wx_info to w_shape. */
            u_int   w_clipseq;  /* clip sequence number */
            int32_t    w_ccliplen; /* client's size of clip list in bytes. */
#if defined(_LP64) || defined(_I32LPX)
            uint32_t    w_sclipptr; /* server's pointer to clip array */
#else
            int    *w_sclipptr; /* server's pointer to clip array */
#endif
        } vn;
        struct {
            struct  obj_hdr         w_shape_hdr;    /* not useful to client */
            struct  class_SHAPE_v0  w_shape;
            short                   w_cliparray;
        } v0;
    } u;

    /* VERSION 2 INFO STARTS HERE */

    /* cursor grabber info */

    u_int       c_filesuffix;   /* to derive shared cursor filename */
#if defined(_LP64) || defined(_I32LPX)
    uint32_t	c_sinfo;      /* pointer to server's cursor info */
    uint32_t	c_pad1;         /* obsolete */
#else
    Dga_cursinfo *c_sinfo;      /* pointer to server's cursor info */
    void       *c_pad1;         /* obsolete */
#endif
    int         c_pad2;         /* obsolete */

    /* wid info */

    struct {
        short   number_wids;    /* number of contiguous wids alloc */
        short   start_wid;      /* starting wid */
        short   wid;            /* current wid */
        short   reserved_1;     /* for the future */
    } w_wid_info;               /* WID info structure */

    /* integer version of window bounds */

    struct {
        int     xleft, ytop;    /* upper-left corner, in pixels */
        int     width, height;  /* dimensions, in pixels */
    } w_window_boundary;


    /* db info */

    struct      wx_dbinfo wx_dbuf;  /* double buffer info structure */

    int         w_auxdevfd;         /* Aux fd for asynch devices */
    char        w_auxdevname[20];   /* Asynch device name */
    short       w_auxdevid;         /* ID number for aux dev type */
    short       w_auxserveronly;    /* To keep SERVER_ONLY's in sync */
#if defined(_LP64) || defined(_I32LPX)
    uint32_t      w_sunlockp;         /* pointer to unlockpage */
#else
    u_int      *w_sunlockp;         /* pointer to unlockpage */
#endif
    int         w_extnd_seq;        /* cliplist extension counter */
    int         w_clientcnt;        /* # of clients using new protocol */
    int         w_oldproto;         /* client used old protocol */
    int         w_locktype;         /* what type of locking */

#if defined(_LP64) || defined(_I32LPX)
    uint32_t	wdev;               /* pointer to server-internal data  */
    uint32_t	w_srtndlink;        /* server's retained struct pointer */
#else
    void       *wdev;               /* pointer to server-internal data  */
    char       *w_srtndlink;        /* server's retained struct pointer */
#endif
    u_int       w_chng_cnt;         /* bumped when anything changes */


    /* VERSION 3 INFO STARTS HERE */

    u_char      w_depth;            /* Window depth */
    u_char      pad[1];             /* Padding for int alignment */
    u_short     w_borderwidth;      /* Actual bw of the window */
    float       w_refresh_period;   /* monitor refresh period- millisec */
#if !defined(_LP64) && !defined(_I32LPX)
	char pad_rfresh[4];
#endif
 
    /*
     * Attributes of multibuffer set
     *
     * Note: the number of buffers in an mbuf set is specified by
     * wx_dbuf.number_buffers.
     */

    DgaMbufSetShinfo    w_mbsInfo;  /*info for multibuf set (if win is mbuf) */
#if !defined(_LP64) && !defined(_I32LPX)
	char pad_mbsinfo[4];
#endif
    u_int       w_devinfoseq;       /*devinfo seq. # in the Dga_dbinfo struct.*/
    int         w_obsolete;         /* 0 when shinfo no longer is valid */
    int         w_visibility;       /* visibility of window. */

    /* VERSION 4 INFO STARTS HERE */

    Bool        w_ovlshapevalid;    /* client will clear this when locking */
                                    /* so the server knows to recalculate */
                                    /* the overlay's opaque shape */
    int         w_ovlstate;         /* conflict mode of an overlay, one of: */
                                    /* MPG_NONE => DGA_OVLSTATE_SAFE     */
                                    /* MPG_SAFE => DGA_OVLSTATE_SAFE     */
                                    /* MPG_SOFT => DGA_OVLSTATE_MULTIWID */
                                    /* MPG_HARD => DGA_OVLSTATE_CONFLICT */

    /* VERSION 5 INFO STARTS HERE */
#if !defined(_LP64) && !defined(_I32LPX)
	char pad_ovlstate[4];
#endif
 
    struct      wx_abinfo wx_abuf;  /* Ancillay Buffers info structure */
#if !defined(_LP64) && !defined(_I32LPX)
	char pad_szinfo[4];
#endif
	int 					info_sz;
 
  /*
   * FLOATING INFO STARTS HERE, DO NOT REFER
   * DIRECTLY TO ANYTHING BELOW THIS LINE.
   */
#if 0
#if !defined(_LP64) && !defined(_I32LPX)
	char pad_abinfo[4];
#endif
#endif

    struct class_SHAPE_vn   w_shape;
    short                   w_cliparray;
 
} WXINFO;

#define WG_LOCKDEV      0       /* use GRABPAGEALLOC from fb */
#define WG_WINLOCK      1       /* use winlock functions */

#endif  /* _DGA_WINSHARED_H */
