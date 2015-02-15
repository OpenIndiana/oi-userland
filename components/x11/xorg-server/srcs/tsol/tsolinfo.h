/*
 * Copyright (c) 2004, 2011, Oracle and/or its affiliates. All rights reserved.
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



#ifndef	_TSOL_INFO_H
#define	_TSOL_INFO_H

#include <sys/types.h>

#include <tsol/label.h>
#include <sys/tsol/tndb.h>
#include <bsm/audit.h>
#include <sys/mkdev.h>
#include <ucred.h>
#include "misc.h"
#include "dixstruct.h"
#include "selection.h"
#include "globals.h"
#include <X11/keysym.h>

/*********************************
 *
 * DEBUG INFO
 *
 *********************************/

/* Message verbosity levels passed to os/log.c functions 
 * Level 0 messages are printed by all servers to stderr.
 * Xorg defaults to logging messages in 0-3 to /var/log/Xorg.<display>.log
 * Ranges of messages to print to stderr can be changed with Xorg -verbose N
 *   and Xephyr -verbosity N
 * Ranges of messages to print to log can be changed with Xorg -logverbose N
 * Other servers don't support runtime configuration of log messages yet.
 */
 
#define TSOL_MSG_ERROR		0		/* Always printed */
#define TSOL_MSG_WARNING	4
#define TSOL_MSG_POLICY_DENIED	5
#define TSOL_MSG_UNIMPLEMENTED	6
#define TSOL_MSG_ACCESS_TRACE	7

#define TSOL_LOG_PREFIX		TSOLNAME ": "
extern const char *TsolDixAccessModeNameString(Mask access_mode);
extern const char *TsolErrorNameString(int req);
extern const char *TsolPolicyReturnString(int pr);
extern const char *TsolRequestNameString(int req);
extern const char *TsolResourceTypeString(RESTYPE resource);

#define MAXNAME            64             /* 63 chars of process name stored */

/*********************************
 *
 * CONSTANTS
 *
 *********************************/


/*
 * X audit events start from 9101 in audit_uevents.h. The first 2 events
 * are non-protocol ones viz. ClientConnect, mapped to 9101 and
 * ClientDisconnect, mapped to 9102.
 * The protocol events are mapped from 9103 onwards in the serial order
 * of their respective protocol opcode, for eg, the protocol UngrabPointer
 * which is has a protocol opcode 27 is mapped to 9129 (9102 + 27).
 * All extension protocols are mapped to a single audit event AUE_XExtension
 * as opcodes are assigined dynamically to these protocols. We set the
 * extension protocol opcode to be 128, one more than the last standard opcode.
 */
#define XAUDIT_Q_SIZE     1024          /* audit queue size for x server */
#define XAUDIT_OFFSET     9102
#define XAUDIT_EXTENSION  128

#define MAX_CLIENT        16
#define MAX_SLS           16            /* used in atom */
#define MAX_POLYPROPS     128           /* used in property */
#define DEF_UID           (uid_t)0      /* uid used for default objects */
#define INVALID_UID       (uid_t)0xFFFF /* invalid uid */
/*
 * Various flags for TsolInfoRec, TsolResRec
 */
#define TSOL_IIL           0x0000001    /* iil changed for window */
#define TSOL_DOXAUDIT      0x0000002    /* write X audit rec if set */
#define TSOL_AUDITEVENT    0x0000004    /* this event mask selected for audit */
#define CONFIG_AUDITED     0x0000008    /* this priv has been asserted for */
#define DAC_READ_AUDITED   0x0000010    /* the same object before */
#define DAC_WRITE_AUDITED  0x0000020
#define MAC_READ_AUDITED   0x0000040
#define MAC_WRITE_AUDITED  0x0000080
#define TRUSTED_MASK	   0x0000100	/* Window has Trusted Path */

/*
 * Polyinstantiated property/selections
 */
#define POLY_SIZE          16           /* increase the list 16 at a time */
#define CONFIG_PRIV_FILE   "config.privs"
#define CONFIG_EXTENSION_FILE "config.extensions"

#define PROCVECTORSIZE (256)

enum tsolconfig_types {
	TSOL_ATOM = 0,
	TSOL_PROPERTY,
	TSOL_SELECTION,
	TSOL_EXTENSION,
	TSOL_PRIVILEGE
};

#define MAJOROP_CODE (client->requestBuffer != 0 ? MAJOROP : (-1))

typedef enum tsolconfig_types tsolconfig_t;

/*
 * Masks corresponding  various types
 */
#define TSOLM_ATOM	1
#define TSOLM_PROPERTY	(1 << 1)
#define TSOLM_SELECTION	(1 << 2)

#define SL_SIZE blabel_size()

/*********************************
 *
 * MACROS
 *
 *********************************/


#define WindowIsRoot(pWin) (pWin && (pWin->parent == NullWindow))
#define DrawableIsRoot(pDraw)\
	(pDraw && (pDraw->id == pDraw->pScreen->root->drawable.id))

/*
 * True if client is part of TrustedPath
 */
#define HasTrustedPath(tsolinfo)\
	(tsolinfo->trusted_path ||\
	(tsolinfo->forced_trust == 1))

#define XTSOLTrusted(pWin) \
    ((TsolWindowPrivate(pWin))->flags & TRUSTED_MASK)


/*********************************
 *
 * DATA STRUCTURES
 *
 *********************************/
enum client_types {
	CLIENT_LOCAL,
	CLIENT_REMOTE
};

typedef enum client_types client_type_t;

/*
 * Extended attributes for each client.
 * Most of the information comes from getpeerucred()
 */
typedef struct _TsolInfo {
    uid_t               uid;            /* real user id */
    uid_t               euid;           /* effective user id */
    gid_t               gid;            /* real group id */
    gid_t               egid;           /* effective group id */
    pid_t               pid;            /* process id */
    zoneid_t		zid;		/* zone id */
    priv_set_t          *privs;         /* privileges */
    bslabel_t		*sl;            /* sensitivity label */
    ulong_t             iaddr;          /* internet addr */
    Bool		trusted_path;	/* has trusted path */
    Bool		priv_debug;	/* do privilege debugging */
    ulong_t             flags;          /* various flags */
    int                 forced_trust;   /* client masked as trusted */
    au_id_t		auid;		/* audit id */
    au_mask_t		amask;		/* audit mask */
    au_asid_t		asid;         	/* audit session id */
    client_type_t    	client_type;    /* Local or Remote client */
    int			asaverd;
    struct sockaddr_storage saddr;	/* socket information */
    char		pname[MAXNAME];	/* process name for debug messages */
} TsolInfoRec, *TsolInfoPtr;

/*
 * per resource info
 */
typedef struct _TsolRes {
    bslabel_t  *sl;                     /* sensitivity label */
    uid_t       uid;                    /* user id */
    ulong_t     flags;                  /* various flags */
    pid_t       pid;                    /* who created it */
    Bool	internal;		/* Created internally by the server */
    Bool	poly;			/* Polyinstantiated or not. Applicable
					   to selection or properties */
} TsolResRec, *TsolResPtr;

/*
 * per keyboard info:
 * Hot Key structure caches keycode/mask for primary & alternate Hot Keys
 */
typedef struct _HotKeyRec {
	int      initialized;
	KeyCode  key;		/* Primary key */
	unsigned shift;		/* Primary modifier/shift */
	KeyCode	 altkey;	/* Alternate key */
	unsigned altshift;	/* Alternate modifier/shift */
} HotKeyRec, *HotKeyPtr;


/*
 * information stored in devPrivates
 */
extern _X_HIDDEN DevPrivateKeyRec tsolClientPrivateKeyRec;
#define tsolClientPrivateKey (&tsolClientPrivateKeyRec)

extern _X_HIDDEN DevPrivateKeyRec tsolPixmapPrivateKeyRec;
#define tsolPixmapPrivateKey (&tsolPixmapPrivateKeyRec)

extern _X_HIDDEN DevPrivateKeyRec tsolWindowPrivateKeyRec;
#define tsolWindowPrivateKey (&tsolWindowPrivateKeyRec)

extern _X_HIDDEN DevPrivateKeyRec tsolPropertyPrivateKeyRec;
#define tsolPropertyPrivateKey (&tsolPropertyPrivateKeyRec)

extern _X_HIDDEN DevPrivateKeyRec tsolSelectionPrivateKeyRec;
#define tsolSelectionPrivateKey (&tsolSelectionPrivateKeyRec)

/* Currently only used in keyboard devices */
extern _X_HIDDEN DevPrivateKeyRec tsolDevicePrivateKeyRec;
#define tsolDevicePrivateKey (&tsolDevicePrivateKeyRec)

static inline TsolInfoPtr
TsolClientPrivate (ClientPtr pClient)
{
	return (TsolInfoPtr) dixLookupPrivate(&(pClient->devPrivates),
					      tsolClientPrivateKey);
}

static inline TsolResPtr
TsolPixmapPrivate (PixmapPtr pPix)
{
	return (TsolResPtr) dixLookupPrivate(&(pPix->devPrivates),
					     tsolPixmapPrivateKey);
}

static inline TsolResPtr
TsolWindowPrivate (WindowPtr pWin)
{
	return (TsolResPtr) dixLookupPrivate(&(pWin->devPrivates),
					     tsolWindowPrivateKey);
}

static inline TsolResPtr
TsolPropertyPrivate (PropertyPtr pProp)
{
	return (TsolResPtr) dixLookupPrivate(&(pProp->devPrivates),
					     tsolPropertyPrivateKey);
}

static inline TsolResPtr
TsolSelectionPrivate (Selection *pSel)
{
	return (TsolResPtr) dixLookupPrivate(&(pSel->devPrivates),
					     tsolSelectionPrivateKey);
}

static inline HotKeyPtr
TsolKeyboardPrivate (DeviceIntPtr pDev)
{
	return (HotKeyPtr) dixLookupPrivate(&(pDev->devPrivates),
					    tsolDevicePrivateKey);
}


#define NODE_SLSIZE	16	/* increase sl array by this amount */
typedef struct _TsolNodeRec {
	unsigned int flags;
	int slcount; 		/* no. of SLs referenced */
	int slsize;		/* size of the sl array */
	int IsSpecial;
	bslabel_t **sl;

} TsolNodeRec, *TsolNodePtr;

/*
 * if polyinst true, the name list is polyinstantiated
 * if false, the everything except the list is polyinstantiated
 * NOTE: Default for seln: polyinstantiate the list
 *       Default for prop: polyinstantiate everything except the list
 */
typedef struct _TsolPolyAtom {
    int     polyinst;
    int     size;                       /* max size of the list */
    int     count;                      /* how many are actually valid */
    char  **name;
} TsolPolyAtomRec, *TsolPolyAtomPtr;

/*
 * PolyInstInfo represents if a get request will match the
 * client's sl,uid for this or it will use the polyinstinfo
 * information to retrieve values for prop/selection
 */
typedef struct _TsolPolyInstInfo {
    int        enabled;                 /* if true use following sl, uid */
    uid_t      uid;
    bslabel_t  *sl;
} TsolPolyInstInfoRec, *TsolPolyInstInfoPtr;


/*********************************
 *
 * EXTERNS
 *
 *********************************/


extern  int PolyProperty(Atom atom, WindowPtr pWin);
extern  int PolySelection(Atom atom);
extern  TsolPolyInstInfoRec tsolpolyinstinfo;
extern  uid_t OwnerUID;                 /* Workstation owner uid */
extern Bool system_audit_on;

/*********************************
 *
 * FUNCTION PROTOTYPES
 *
 *********************************/


void  TsolReadPolyAtoms(char *filename, TsolPolyAtomPtr polyatomptr);
extern WindowPtr TopClientWin(WindowPtr pWin);
extern WindowPtr RootWin(WindowPtr pWin);
extern Window RootOf(WindowPtr pWin);
extern Window RootOfClient(WindowPtr pWin);
extern int TsolDisabledExtension(const char *extname);
extern int MatchTsolConfig(const char *name, int len);
extern int HasWinSelection(TsolInfoPtr tsolinfo);
extern int same_client (ClientPtr client, XID xid);
extern int client_private (ClientPtr client, XID xid);
extern bslabel_t *lookupSL_low(void);
extern bslabel_t *lookupSL(bslabel_t *slptr);
extern BoxPtr WindowExtents(WindowPtr pWin, BoxPtr pBox);
extern Bool ShapeOverlap(WindowPtr pWin, BoxPtr pWinBox,
	WindowPtr pSib, BoxPtr pSibBox);
extern TsolResPtr TsolDrawablePrivate(DrawablePtr pDraw, ClientPtr client);

#endif	/* _TSOL_INFO_H */
