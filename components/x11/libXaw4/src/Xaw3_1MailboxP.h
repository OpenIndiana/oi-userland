/*
 * $XConsortium: MailboxP.h,v 1.16 89/05/11 01:05:56 kit Exp $
 *
 * Copyright 1988 Massachusetts Institute of Technology
 *
 * Permission to use, copy, modify, and distribute this software and its
 * documentation for any purpose and without fee is hereby granted, provided
 * that the above copyright notice appear in all copies and that both that
 * copyright notice and this permission notice appear in supporting
 * documentation, and that the name of M.I.T. not be used in advertising or
 * publicity pertaining to distribution of the software without specific,
 * written prior permission.  M.I.T. makes no representations about the
 * suitability of this software for any purpose.  It is provided "as is"
 * without express or implied warranty.
 *
 * Author:  Jim Fulton, MIT X Consortium
 */

#ifndef _XawMailboxP_h
#define _XawMailboxP_h

#include <./Xaw3_1Mailbox.h>

#ifdef SYSV
#define MAILBOX_DIRECTORY "/usr/mail"
#else
#define MAILBOX_DIRECTORY "/usr/spool/mail"
#endif

typedef struct {			/* new fields for mailbox widget */
    /* resources */
    int update;				/* seconds between updates */
    Pixel foreground_pixel;		/* color index of normal state fg */
    String filename;			/* filename to watch */
    String check_command;		/* command to exec for mail check */
    Boolean reverseVideo;		/* do reverse video? */
    Boolean flipit;			/* do flip of full pixmap */
    int volume;				/* bell volume */
    Boolean once_only;			/* ring bell only once on new mail */
    /* local state */
    GC gc;				/* normal GC to use */
    long last_size;			/* size in bytes of mailboxname */
    XtIntervalId interval_id;		/* time between checks */
    Boolean flag_up;			/* is the flag up? */
    struct _mbimage {
	Pixmap bitmap, mask;		/* depth 1, describing shape */
	Pixmap pixmap;			/* full depth pixmap */
	int width, height;		/* geometry of pixmaps */
    } full, empty;
#ifdef SHAPE
    Boolean shapeit;			/* do shape extension */
    struct {
	Pixmap mask;
	int x, y;
    } shape_cache;			/* last set of info */
#endif
} MailboxPart;

typedef struct _MailboxRec {		/* full instance record */
    CorePart core;
    MailboxPart mailbox;
} MailboxRec;


typedef struct {			/* new fields for mailbox class */
    int dummy;				/* stupid C compiler */
} MailboxClassPart;

typedef struct _MailboxClassRec {	/* full class record declaration */
    CoreClassPart core_class;
    MailboxClassPart mailbox_class;
} MailboxClassRec;

extern MailboxClassRec mailboxClassRec;	 /* class pointer */

#endif /* _XawMailboxP_h */
