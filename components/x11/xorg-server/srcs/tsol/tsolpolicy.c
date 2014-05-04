/* Copyright (c) 2004, 2009, Oracle and/or its affiliates. All rights reserved.
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


#ifdef HAVE_DIX_CONFIG_H
#include <dix-config.h>
#endif

#include <X11/X.h>
#define		NEED_REPLIES
#define		NEED_EVENTS
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include "auditwrite.h"
#include <bsm/audit_kevents.h>
#include <bsm/audit_uevents.h>
#include <X11/Xproto.h>
#include "dix.h"
#include "misc.h"
#include "scrnintstr.h"
#include "os.h"
#include "regionstr.h"
#include "validate.h"
#include "windowstr.h"
#include "propertyst.h"
#include "input.h"
#include "inputstr.h"
#include "resource.h"
#include "colormapst.h"
#include "cursorstr.h"
#include "dixstruct.h"
#include "selection.h"
#include "gcstruct.h"
#include "servermd.h"
#include <syslog.h>
#include "extnsionst.h"
#include "registry.h"
#include "xace.h"
#include "xacestr.h"
#ifdef PANORAMIX
#include "../Xext/panoramiXsrv.h"
#endif
#include "tsol.h"
#include "tsolinfo.h"
#include "tsolpolicy.h"

priv_set_t *pset_win_mac_write = NULL;
priv_set_t *pset_win_dac_write = NULL;
priv_set_t *pset_win_config = NULL;

static priv_set_t *pset_win_mac_read = NULL;
static priv_set_t *pset_win_dac_read = NULL;
static priv_set_t *pset_win_devices = NULL;
static priv_set_t *pset_win_fontpath = NULL;
static priv_set_t *pset_win_colormap = NULL;
static priv_set_t *pset_win_upgrade_sl = NULL;
static priv_set_t *pset_win_downgrade_sl = NULL;
static priv_set_t *pset_win_selection = NULL;

#define SAMECLIENT(client, xid) ((client)->index == CLIENT_ID(xid))

/* Unless NO_TSOL_DEBUG_MESSAGES is defined, admins will be able to enable
   debugging messages at runtime via Xorg -logverbose */
#ifndef NO_TSOL_DEBUG_MESSAGES
static char *xsltos(bslabel_t *sl);

#endif /* NO_TSOL_DEBUG_MESSAGES */

extern int tsol_mac_enabled;

static void
set_audit_flags(TsolInfoPtr tsolinfo)
{
    if (tsolinfo->flags & TSOL_AUDITEVENT)
        tsolinfo->flags &= ~TSOL_AUDITEVENT;
    if (!(tsolinfo->flags & TSOL_DOXAUDIT))
        tsolinfo->flags |= TSOL_DOXAUDIT;

}

static void
unset_audit_flags(TsolInfoPtr tsolinfo)
{
    if (tsolinfo->flags & TSOL_AUDITEVENT)
        tsolinfo->flags &= ~TSOL_AUDITEVENT;
    if (tsolinfo->flags & TSOL_DOXAUDIT)
        tsolinfo->flags &= ~TSOL_DOXAUDIT;

}
/*
 * returns 
 *   TRUE  - if client/subject has the required privilege
 *   FALSE - otherwise
 */

Bool
client_has_privilege(TsolInfoPtr tsolinfo, priv_set_t *priv)
{

	if (tsolinfo->privs == NULL) {
		return TRUE; /* server itself */
	}

	if (priv_issubset(priv, tsolinfo->privs)) {
		if (tsolinfo->flags & TSOL_AUDITEVENT) {
			auditwrite(AW_USEOFPRIV, AUDIT_SUCCESS, priv, 
				AW_APPEND, AW_END);
		}

		return TRUE;
	} else
		return FALSE;
}

int
tsol_check_policy(TsolInfoPtr tsolinfo, TsolResPtr tsolres, xpolicy_t flags, int reqcode)
{
	int status = BadAccess;

	/* Check for Trusted Path (TP) */
	if (flags & TSOL_TP) {
		if (HasTrustedPath(tsolinfo)) {
			status = Success;
		} else {
			goto bad;
		}
	}

	/* Check for Mandatory Access Control (MAC) */
	if (tsol_mac_enabled & flags & TSOL_MAC) {
		if (flags & TSOL_READOP) {
			if (blequal(tsolinfo->sl, tsolres->sl) ||
			    (blequal(tsolres->sl, &PublicObjSL) &&
			 	reqcode != X_GetImage) ||
			    ((flags & TSOL_DOMINATE)  &&
				bldominates(tsolinfo->sl, tsolres->sl)) ||
			    client_has_privilege(tsolinfo, pset_win_mac_read) ||
			    HasTrustedPath(tsolinfo)) {

				status = Success;
			} else {
				goto bad;
			}
		}
			
		if (flags & TSOL_WRITEOP) {
			if (blequal(tsolinfo->sl, tsolres->sl) ||
			    client_has_privilege(tsolinfo, pset_win_mac_write)) {
				status = Success;
			} else {
				goto bad;
			}
		}
	}

	/* Check for Discretionary Access Control (DAC) */
	if (flags & TSOL_DAC) {
		if (flags & TSOL_READOP) {
			if ((tsolinfo->uid == tsolres->uid) ||
			    tsolres->internal ||
			    ((tsolres->uid == OwnerUID) && 
			    /* ((tsolres->uid == OwnerUID || tsolres->uid == DEF_UID) &&  */
			 	blequal(tsolres->sl, &PublicObjSL)) ||
			    client_has_privilege(tsolinfo, pset_win_dac_read)) {

				status = Success;
			} else {
				goto bad;
			}
		}

		if (flags & TSOL_WRITEOP) {
			if ((tsolinfo->uid == tsolres->uid) ||
			   (tsolinfo->uid == OwnerUID &&
                               reqcode == X_ChangeWindowAttributes) ||
			    client_has_privilege(tsolinfo, pset_win_dac_write)) {

				status = Success;
			} else {
				goto bad;
			}
		}
	}

	return Success;

bad:
	/* Access denied */
	LogMessageVerb(X_ERROR, TSOL_MSG_ERROR,
		TSOL_LOG_PREFIX
		"tsol_check_policy(%s, %s, %d, pid=%d, %s, %d, %s) = %s\n",
		tsolinfo->pname, xsltos(tsolinfo->sl), tsolinfo->uid, 
		tsolres->pid, xsltos(tsolres->sl), tsolres->uid, 
		TsolRequestNameString(reqcode),
		"BadAccess");

	return BadAccess;
}


#ifndef NO_TSOL_DEBUG_MESSAGES
/*
 * Converts SL to string
 */
static char *
xsltos(bslabel_t *sl)
{
	char *slstring = NULL;

	if (bsltos(sl, &slstring, 0,
		VIEW_INTERNAL|SHORT_CLASSIFICATION | LONG_WORDS | ALL_ENTRIES) <= 0)
		return (NULL);
	else
		return slstring;
}
#endif /* !NO_TSOL_DEBUG_MESSAGES */


/*
 * Allocate a single privilege set
 */
static priv_set_t *
alloc_win_priv(const char *priv)
{
	priv_set_t *pset;

	if ((pset = priv_allocset()) == NULL) {
		perror("priv_allocset");
		FatalError("Cannot allocate privilege set");
	}
	priv_emptyset(pset);
	priv_addset(pset, priv);

	return pset;
}

/*
 * Initialize all string window privileges to the binary equivalent.
 * Binary privilege testing is much faster than the string testing
 */
void
init_win_privsets(void)
{

	pset_win_mac_read = alloc_win_priv(PRIV_WIN_MAC_READ);
	pset_win_mac_write = alloc_win_priv(PRIV_WIN_MAC_WRITE);
	pset_win_dac_read = alloc_win_priv(PRIV_WIN_DAC_READ);
	pset_win_dac_write = alloc_win_priv(PRIV_WIN_DAC_WRITE);
	pset_win_config = alloc_win_priv(PRIV_WIN_CONFIG);
	pset_win_devices = alloc_win_priv(PRIV_WIN_DEVICES);
	pset_win_fontpath = alloc_win_priv(PRIV_WIN_FONTPATH);
	pset_win_colormap = alloc_win_priv(PRIV_WIN_COLORMAP);
	pset_win_upgrade_sl = alloc_win_priv(PRIV_WIN_UPGRADE_SL);
	pset_win_downgrade_sl = alloc_win_priv(PRIV_WIN_DOWNGRADE_SL);
	pset_win_selection = alloc_win_priv(PRIV_WIN_SELECTION);
}

void
free_win_privsets(void)
{
	priv_freeset(pset_win_mac_read);
	priv_freeset(pset_win_mac_write);
	priv_freeset(pset_win_dac_read);
	priv_freeset(pset_win_dac_write);
	priv_freeset(pset_win_config);
	priv_freeset(pset_win_devices);
	priv_freeset(pset_win_fontpath);
	priv_freeset(pset_win_colormap);
	priv_freeset(pset_win_upgrade_sl);
	priv_freeset(pset_win_downgrade_sl);
	priv_freeset(pset_win_selection);
}

int
HasWinSelection(TsolInfoPtr tsolinfo)
{
	return (priv_issubset(pset_win_selection, (tsolinfo->privs)));
}

void
TsolCheckDrawableAccess(CallbackListPtr *pcbl, pointer nulldata, pointer calldata)
{
	XaceResourceAccessRec *rec = calldata;
	ClientPtr client = rec->client;
	XID id = rec->id;
	RESTYPE rtype = rec->rtype;
	Mask access_mode = rec->access_mode;
	DeviceIntPtr device = PickPointer(client);
	WindowPtr pWin;
	PixmapPtr pMap;
	Mask modes;
	int obj_code;
	int status;
	int err_code;

	Mask check_mode = access_mode;
	TsolInfoPtr tsolinfo = GetClientTsolInfo(client);
	TsolResPtr  tsolres;
	xpolicy_t flags;
	int msgType;
	int msgVerb;
	int reqtype;

	if (client->requestBuffer) {
		reqtype = MAJOROP;  /* protocol */
	} else {
		reqtype = -1;
	}

	status = BadAccess;

	switch (rtype) {
	case RT_WINDOW:
		obj_code = AW_XWINDOW;
		pWin = (WindowPtr ) (rec->res);
		tsolres = TsolResourcePrivate(pWin);
		err_code = BadWindow;
		break;
	case RT_PIXMAP:
		obj_code = AW_XPIXMAP;
		pMap = (PixmapPtr ) (rec->res);
		tsolres = TsolResourcePrivate(pMap);
		err_code = BadDrawable;
		break;
	}

	switch (reqtype) {
	case X_GetImage:
	case X_CopyArea:
	case X_CopyPlane:
		/* 
		 * Image operations are allowed here for lookup reasons.
		 * The actual policy enforcement is in the protocol handler.
		 */
		if (check_mode & DixReadAccess) {
			status = Success;
			check_mode &= ~DixReadAccess;
		}
		break;
				

	case X_ClearArea:
		if (check_mode & DixWriteAccess) {
			status = Success;
			check_mode &= ~DixWriteAccess;
		}
		break;

	case X_GrabPointer:
	case X_UngrabPointer:
	case X_GrabKeyboard:
	case X_UngrabKeyboard:
	case X_GrabKey:
	case X_UngrabKey:
	case X_GrabButton:
	case X_UngrabButton:
		/*
		 * Allow pointer grab on root window, as long as
		 * pointer is currently in a window owned by
		 * requesting client.
		 */

		if (WindowIsRoot(pWin)) {
			pWin = GetSpriteWindow(device);
			tsolres = TsolResourcePrivate(pWin);
		}
		break;

	case X_ChangeSaveSet:
		modes = (DixManageAccess|DixSetAttrAccess);
		if (check_mode & modes) {
			if (priv_win_config ||
				client_has_privilege(tsolinfo, pset_win_config)) {
				status = Success;
			}
			check_mode &= ~modes;

		}
		break;

	}

	{
		/* Perform the standard MAC/DAC tests here */
		modes = (DixAddAccess|DixRemoveAccess|DixReadAccess|DixGetAttrAccess|
				DixSetAttrAccess|
				DixGetPropAccess|DixListPropAccess|DixSetPropAccess);
		if (rtype == RT_WINDOW && check_mode & modes) {
			if (WindowIsRoot(pWin) || XTSOLTrusted(pWin)) {
				status = Success;
				check_mode &= ~modes;
			}
		}

		/* Newly created drawable. Initialize it. */
		if (check_mode & DixCreateAccess) {
			if (rtype == RT_WINDOW)
				TsolInitWindow(client, pWin);
			if (rtype == RT_PIXMAP)
				TsolInitPixmap(client, pMap);

			status = Success;
			check_mode &= ~(DixCreateAccess);
		}

		modes = (DixReadAccess|DixGetAttrAccess|
				DixShowAccess|DixHideAccess|
				DixListAccess|DixGetPropAccess|DixListPropAccess);
		if (check_mode & modes) {
			flags = (TSOL_MAC|TSOL_DAC|TSOL_READOP);
			if (reqtype == X_GetInputFocus)
				flags |= TSOL_DOMINATE;
			status = tsol_check_policy(tsolinfo, tsolres, flags, reqtype);
			check_mode &= ~modes;
		}

		modes = (DixWriteAccess|DixSetAttrAccess|DixDestroyAccess|
				DixManageAccess|
				DixGrabAccess|DixSetAttrAccess|DixSetPropAccess|
				DixAddAccess|DixRemoveAccess);
		if (check_mode & modes) {
			flags = (TSOL_MAC|TSOL_DAC|TSOL_WRITEOP);
			status = tsol_check_policy(tsolinfo, tsolres, flags, reqtype);
			check_mode &= ~modes;
		}

		/* Event access, actual policy is implemented in the hook */
		modes = (DixSendAccess|DixReceiveAccess);
		if (check_mode & modes) {
			status = Success;
			check_mode &= ~modes;
		}
	}
	
	if (tsolinfo->flags & TSOL_AUDITEVENT) {
		set_audit_flags(tsolinfo);
		auditwrite(obj_code, id, tsolres->uid,
			 AW_SLABEL, tsolres->sl,
			 AW_APPEND, AW_END);
	}

	if (status == Success)
		rec->status = Success;
	else
		rec->status = err_code;

#ifndef NO_TSOL_DEBUG_MESSAGES
    if (check_mode) { /* Any access mode bits not yet handled ? */
	LogMessageVerb(X_NOT_IMPLEMENTED, TSOL_MSG_UNIMPLEMENTED,
		       TSOL_LOG_PREFIX
		       "policy not implemented for TsolCheckWindowAccess, "
		       "rtype=0x%x (%s), mode=0x%x (%s)\n",
		       (int) rtype, TsolResourceTypeString(rtype),
		       check_mode, TsolDixAccessModeNameString(check_mode));
    }

    if (rec->status != Success) {
    	tsolinfo = GetClientTsolInfo(client);
    	LogMessageVerb(X_ERROR, TSOL_MSG_ERROR,
		   TSOL_LOG_PREFIX
		   "TsolCheckDrawableAccess(%s, %s, 0x%x, %s, %s) = %s\n",
		   tsolinfo->pname,
		   TsolResourceTypeString(rtype), id,
		   TsolDixAccessModeNameString(access_mode),
		   TsolRequestNameString(reqtype),
		   TsolErrorNameString(rec->status));
    }

#endif /* !NO_TSOL_DEBUG_MESSAGES */

}

void
TsolCheckXIDAccess(CallbackListPtr *pcbl, pointer nulldata, pointer calldata)
{
	XaceResourceAccessRec *rec = calldata;
	ClientPtr client = rec->client;
	XID id = rec->id;
	RESTYPE rtype = rec->rtype;
	Mask access_mode = rec->access_mode;
	Mask modes;
	int object_code;
	int err_code;
	int status;

	Mask check_mode = access_mode;
	TsolInfoPtr tsolinfo = GetClientTsolInfo(client);
	xpolicy_t flags;
	int msgType;
	int msgVerb;
	int reqtype;

	if (client->requestBuffer) {
		reqtype = MAJOROP;  /* protocol */
	} else {
		reqtype = -1;
	}

	switch (rtype) {
	case RT_FONT:
		err_code = BadFont;
		object_code = AW_XFONT;
		break;
	case RT_GC:
		err_code = BadGC;
		object_code = AW_XGC;
		break;
	case RT_CURSOR:
		err_code = BadCursor;
		object_code = AW_XCURSOR;
		break;
	case RT_COLORMAP:
		err_code = BadColor;
		object_code = AW_XCOLORMAP;
		break;
	default:
		err_code = BadValue;
		break;
	}

	/* Anyone can create an object */
	if (check_mode & DixCreateAccess) {
		rec->status = Success;
		check_mode &= ~DixCreateAccess;
	}

	/* DAC check is based on client isolation */
	modes = (DixReadAccess|DixGetAttrAccess|DixUseAccess); 
	if (check_mode & modes) {
		if (!client_private(client, id) &&
			(!client_has_privilege(tsolinfo, pset_win_dac_read))) {
			rec->status = err_code;
		}
		check_mode &= ~modes;
	}

	modes = (DixWriteAccess|DixSetAttrAccess|DixDestroyAccess);
	if (check_mode & modes) {
		if (!client_private(client, id) &&
			(!client_has_privilege(tsolinfo, pset_win_dac_write))) {
			rec->status = err_code;
		}
		check_mode &= ~modes;
	}
			
	if (tsolinfo->flags & TSOL_AUDITEVENT) {
		set_audit_flags(tsolinfo);
		auditwrite(object_code, (u_long)id, tsolinfo->uid,
			 AW_APPEND, AW_END);
	}

#ifndef NO_TSOL_DEBUG_MESSAGES
    if (check_mode) { /* Any access mode bits not yet handled ? */
	LogMessageVerb(X_NOT_IMPLEMENTED, TSOL_MSG_UNIMPLEMENTED,
		       TSOL_LOG_PREFIX
		       "policy not implemented for TsolCheckXIDAccess, "
		       "rtype=0x%x (%s), mode=0x%x (%s)\n",
		       (int) rtype, TsolResourceTypeString(rtype),
		       check_mode, TsolDixAccessModeNameString(check_mode));
    }

    if (rec->status != Success) {
	    tsolinfo = GetClientTsolInfo(client);
	    LogMessageVerb(X_ERROR, TSOL_MSG_ERROR,
		   TSOL_LOG_PREFIX
		   "TsolCheckXIDAccess(%s, %s, 0x%x, %s, %s) = %s\n",
		   tsolinfo->pname,
		   TsolResourceTypeString(rtype), id,
		   TsolDixAccessModeNameString(access_mode),
		   TsolRequestNameString(reqtype),
		   TsolErrorNameString(rec->status));
    }
#endif /* !NO_TSOL_DEBUG_MESSAGES */
}

void
TsolCheckServerAccess(CallbackListPtr *pcbl, pointer nulldata, pointer calldata)
{
	XaceServerAccessRec *rec = calldata;
	ClientPtr client = rec->client;
	Mask access_mode = rec->access_mode;
	Mask modes;
	int object_code = 0;
	int err_code;

	Mask check_mode = access_mode;
	TsolInfoPtr tsolinfo = GetClientTsolInfo(client);
	xpolicy_t flags;
	int reqtype;

	if (client->requestBuffer) {
		reqtype = MAJOROP;  /* protocol */
	} else {
		reqtype = -1;
	}

	/* rec->status = Success; return; */

	rec->status = BadAccess;

	modes = (DixManageAccess);
	if (check_mode & modes) {
		switch (reqtype) {
		case X_SetFontPath:
			if (priv_win_fontpath ||
				client_has_privilege(tsolinfo, pset_win_fontpath)) {
				rec->status = Success;
			}
			object_code = AW_XFONT;
			break;

		case X_ChangeHosts:
		case X_SetAccessControl:
			if (priv_win_config ||
				client_has_privilege(tsolinfo, pset_win_config)) {
				rec->status = Success;
			}
			object_code = AW_XCLIENT;
			break;
		}

		check_mode &= ~modes;

		if (tsolinfo->flags & TSOL_AUDITEVENT && object_code != 0) {
			set_audit_flags(tsolinfo);
			auditwrite(object_code, (u_long)client->index, tsolinfo->uid,
				 AW_SLABEL, tsolinfo->sl,
				 AW_APPEND, AW_END);
		}
	}

	/* Allow get/read attributes, grab is enforced in protocol handler */
	modes = (DixReadAccess|DixGetAttrAccess|DixGrabAccess); 
	if (check_mode & modes) {
		rec->status = Success;
		check_mode &= ~modes;
	}

#ifndef NO_TSOL_DEBUG_MESSAGES
    if (check_mode) { /* Any access mode bits not yet handled ? */
	LogMessageVerb(X_NOT_IMPLEMENTED, TSOL_MSG_UNIMPLEMENTED,
		       TSOL_LOG_PREFIX
		       "policy not implemented for TsolCheckServerAccess, "
		       "mode=0x%x (%s)\n",
		       check_mode, TsolDixAccessModeNameString(check_mode));
    }

    if (rec->status != Success) {
    	tsolinfo = GetClientTsolInfo(client);
    	LogMessageVerb(X_ERROR, TSOL_MSG_ERROR,
		   TSOL_LOG_PREFIX
		   "TsolCheckServerAccess(%s, %s, %s) = %s\n",
		   tsolinfo->pname,
		   TsolDixAccessModeNameString(access_mode),
		   TsolRequestNameString(reqtype),
		   TsolErrorNameString(rec->status));
    }

#endif /* !NO_TSOL_DEBUG_MESSAGES */
}

void
TsolCheckClientAccess(CallbackListPtr *pcbl, pointer nulldata, pointer calldata)
{
	XaceClientAccessRec *rec = calldata;
	ClientPtr client = rec->client;
	Mask access_mode = rec->access_mode;
	Mask modes;
	int object_code = 0;
	int err_code;

	Mask check_mode = access_mode;
	TsolInfoPtr tsolinfo = GetClientTsolInfo(client);
	xpolicy_t flags;
	int msgType;
	int msgVerb;
	int reqtype;

	if (client->requestBuffer) {
		reqtype = MAJOROP;  /* protocol */
	} else {
		reqtype = -1;
	}

	rec->status = BadAccess;

	modes = (DixManageAccess|DixDestroyAccess);
	if (check_mode & modes) {
		if (priv_win_config ||
				client_has_privilege(tsolinfo, pset_win_config)) {
			rec->status = Success;
		}
		check_mode &= ~modes;

		if (tsolinfo->flags & TSOL_AUDITEVENT) {
			set_audit_flags(tsolinfo);
			auditwrite(AW_XCLIENT, (u_long)client->index, tsolinfo->uid,
				 AW_SLABEL, tsolinfo->sl,
				 AW_APPEND, AW_END);
		}
	}

#ifndef NO_TSOL_DEBUG_MESSAGES
    if (check_mode) { /* Any access mode bits not yet handled ? */
	LogMessageVerb(X_NOT_IMPLEMENTED, TSOL_MSG_UNIMPLEMENTED,
		       TSOL_LOG_PREFIX
		       "policy not implemented for TsolCheckClientAccess, "
		       "mode=0x%x (%s)\n",
		       check_mode, TsolDixAccessModeNameString(check_mode));
    }

    if (rec->status != Success) {
    	tsolinfo = GetClientTsolInfo(client);
    	LogMessageVerb(X_ERROR, TSOL_MSG_ERROR,
		   TSOL_LOG_PREFIX
		   "TsolCheckClientAccess(%s, %s, %s) = %s\n",
		   tsolinfo->pname,
		   TsolDixAccessModeNameString(access_mode),
		   TsolRequestNameString(reqtype),
		   TsolErrorNameString(rec->status));
    }

#endif /* !NO_TSOL_DEBUG_MESSAGES */

}

void
TsolCheckDeviceAccess(CallbackListPtr *pcbl, pointer nulldata, pointer calldata)
{
	XaceDeviceAccessRec *rec = (XaceDeviceAccessRec *) calldata;
	ClientPtr client = rec->client;
	Mask access_mode = rec->access_mode;
	Mask check_mode = access_mode;
	TsolInfoPtr tsolinfo = GetClientTsolInfo(client);
	int reqtype;
	Mask modes;

	if (client->requestBuffer) {
		reqtype = MAJOROP;  /* protocol */
	} else {
		reqtype = -1;
	}

	rec->status = BadWindow;

	/* get/read access is allowed */
	modes = (DixCreateAccess | DixGetAttrAccess | DixGetFocusAccess | DixReadAccess |
		 DixShowAccess | DixHideAccess|DixUseAccess | DixBellAccess);
	if (check_mode & modes) {
		rec->status = Success;
		check_mode &= ~modes;
	}

	/* change/set access requires privilege */
	modes = (DixFreezeAccess | DixGrabAccess | DixManageAccess | DixSetAttrAccess |
		 DixSetFocusAccess | DixForceAccess);
	if (check_mode & modes) {
		if (priv_win_devices || client_has_privilege(tsolinfo, pset_win_devices))
			rec->status = Success;
			if (tsolinfo->flags & TSOL_AUDITEVENT) {
				set_audit_flags(tsolinfo);
				auditwrite(AW_XCLIENT, client->index, 
					AW_APPEND, AW_END);
			}
		check_mode &= ~modes;
	}

#ifndef NO_TSOL_DEBUG_MESSAGES
    if (check_mode) { /* Any access mode bits not yet handled ? */
	LogMessageVerb(X_NOT_IMPLEMENTED, TSOL_MSG_UNIMPLEMENTED,
		       TSOL_LOG_PREFIX
		       "policy not implemented for TsolCheckDeviceAccess, %s, %s\n",
		       TsolDixAccessModeNameString(check_mode),
		       TsolRequestNameString(reqtype));
    }

    if (rec->status != Success) {
    	tsolinfo = GetClientTsolInfo(client);
    	LogMessageVerb(X_ERROR, TSOL_MSG_ERROR,
		   TSOL_LOG_PREFIX
		   "TsolCheckDeviceAccess(%s, %s, %s) = %s\n",
		   tsolinfo->pname,
		   TsolDixAccessModeNameString(access_mode),
		   TsolRequestNameString(reqtype),
		   TsolErrorNameString(rec->status));
    }

#endif /* !NO_TSOL_DEBUG_MESSAGES */
} 

TsolResPtr 
TsolDrawablePrivate(DrawablePtr pDraw, ClientPtr client)
{
	int	rc;
	TsolResPtr tsolres = NULL;
	PixmapPtr pMap = NullPixmap;
	WindowPtr pWin = NullWindow;

	if (pDraw->type == DRAWABLE_WINDOW) {
		rc = dixLookupWindow(&pWin, pDraw->id, client, DixReadAccess);
		if (rc == Success && pWin != NullWindow)
			tsolres = TsolResourcePrivate(pWin);
	}
	else if (pDraw->type == DRAWABLE_PIXMAP)
	{
		rc = dixLookupDrawable((DrawablePtr *)&pMap, pDraw->id, client,
				       M_DRAWABLE_PIXMAP, DixReadAccess);
		if (rc == Success && pMap != NullPixmap)
			tsolres = TsolResourcePrivate(pMap);
	}

	return tsolres;
}
