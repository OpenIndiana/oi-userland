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


#include <stdio.h>
#include "auditwrite.h"
#include <bsm/libbsm.h>
#include <bsm/audit_uevents.h>
#include <sys/param.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <ucred.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/tsol/tndb.h>
#include <strings.h>
#include <string.h>
#include <pwd.h>
#include <unistd.h>
#include <sys/stat.h>
#include <rpc/rpc.h>
#include <zone.h>


#define NEED_REPLIES

#ifdef HAVE_DIX_CONFIG_H
#include <dix-config.h>
#endif

#include "misc.h"
#include "osdep.h"
#include <X11/Xauth.h>
#include "tsol.h"
#include "inputstr.h"
#include "extnsionst.h"
#include "dixstruct.h"
#include "xace.h"
#include "xacestr.h"
#ifdef PANORAMIX
#include "../Xext/panoramiXsrv.h"
#endif
#ifdef XCSECURITY
#include <X11/extensions/secur.h>
#include "../Xext/securitysrv.h"
#endif
#include "tsolpolicy.h"

#define  BadCmapCookie      0
#define  Tsolextension      0x0080    /* Tsol extensions begin at 128 */
#define  MAX_SCREENS        3         /* screens allowed */
#define EXTNSIZE 128

#define SECURE_RPC_AUTH	"SUN-DES-1"
#define SECURE_RPC_LEN	9

static int ProcTsolDispatch(ClientPtr);
static int ProcSetPolyInstInfo(ClientPtr);
static int ProcSetPropLabel(ClientPtr);
static int ProcSetPropUID(ClientPtr);
static int ProcSetResLabel(ClientPtr);
static int ProcSetResUID(ClientPtr);
static int ProcGetClientAttributes(ClientPtr);
static int ProcGetClientLabel(ClientPtr);
static int ProcGetPropAttributes(ClientPtr);
static int ProcGetResAttributes(ClientPtr);
static int ProcMakeTPWindow(ClientPtr);
static int ProcMakeTrustedWindow(ClientPtr);
static int ProcMakeUntrustedWindow(ClientPtr);

static int SProcTsolDispatch(ClientPtr);
static int SProcSetPolyInstInfo(ClientPtr);
static int SProcSetPropLabel(ClientPtr);
static int SProcSetPropUID(ClientPtr);
static int SProcSetResLabel(ClientPtr);
static int SProcSetResUID(ClientPtr);
static int SProcGetClientAttributes(ClientPtr);
static int SProcGetClientLabel(ClientPtr);
static int SProcGetPropAttributes(ClientPtr);
static int SProcGetResAttributes(ClientPtr);
static int SProcMakeTPWindow(ClientPtr);
static int SProcMakeTrustedWindow(ClientPtr);
static int SProcMakeUntrustedWindow(ClientPtr);

static void TsolReset(ExtensionEntry *extension);
static void BreakAllGrabs(ClientPtr client);

static unsigned char TsolReqCode = 0;
static int tsolEventBase = -1;
static int ScreenStripeHeight[MAX_SCREENS] = {0, 0};

int tsolMultiLevel = TRUE;
int tsol_mac_enabled;

static int OwnerUIDint;
static Selection *tsol_sel_agnt = NULL; /* entry in CurrentSelection to get seln */
static Atom tsol_atom_sel_agnt = 0; /* selection agent atom created during init */

int (*TsolSavedProcVector[PROCVECTORSIZE])(ClientPtr client);
int (*TsolSavedSwappedProcVector[PROCVECTORSIZE])(ClientPtr client);

static SecurityHook tsolSecHook;

static XID TsolCheckAuthorization (unsigned int name_length,
	char *name, unsigned int data_length,
	char *data, ClientPtr client, char **reason);

static void TsolSetClientInfo(ClientPtr client);

/* XACE hook callbacks */
static CALLBACK(TsolCheckExtensionAccess);
static CALLBACK(TsolCheckPropertyAccess);
static CALLBACK(TsolCheckResourceIDAccess);
static CALLBACK(TsolCheckSendAccess);
static CALLBACK(TsolCheckReceiveAccess);
static CALLBACK(TsolCheckSelectionAccess);
static CALLBACK(TsolProcessKeyboard);
CALLBACK(TsolCheckDeviceAccess);
CALLBACK(TsolCheckServerAccess);
CALLBACK(TsolCheckClientAccess);

/* other callbacks */
static CALLBACK(TsolClientStateCallback);
static CALLBACK(TsolSelectionCallback);

extern int tsol_check_policy(TsolInfoPtr tsolinfo, TsolResPtr tsolres, 
	xpolicy_t flags, int reqcode);
extern void TsolCheckDrawableAccess(CallbackListPtr *pcbl, pointer nulldata, 
	pointer calldata);
extern void TsolCheckXIDAccess(CallbackListPtr *pcbl, pointer nulldata, 
	pointer calldata);
extern Bool client_has_privilege(TsolInfoPtr tsolinfo, priv_set_t *priv);

extern priv_set_t *pset_win_mac_write;
extern priv_set_t *pset_win_dac_write;
extern priv_set_t *pset_win_config;

extern RESTYPE RREventType;

/*
 * Initialize the extension. Main entry point for this loadable
 * module.
 */

_X_EXPORT void
TsolExtensionInit(void)
{
	ExtensionEntry *extEntry;
	int i;

	/* sleep(20); */

	/* MAC/Label support is available only if labeld svc is enabled */ 
	if (is_system_labeled()) {
		tsol_mac_enabled = TRUE;
	} else {
		/* DAC support can be added in future */
		tsol_mac_enabled = FALSE;
		return;
	}

	tsolMultiLevel = TRUE;
	(void) setpflags(PRIV_AWARE, 1);

	init_xtsol();
	init_win_privsets();

	extEntry = AddExtension(TSOLNAME, TSOL_NUM_EVENTS, TSOL_NUM_ERRORS,
		ProcTsolDispatch, SProcTsolDispatch, TsolReset,
		StandardMinorOpcode);

	if (extEntry == NULL) {
		ErrorF("TsolExtensionInit: AddExtension failed for X Trusted Extensions\n");
		return;
	}

        TsolReqCode = (unsigned char) extEntry->base;
        tsolEventBase = extEntry->eventBase;

	if (!AddCallback(&ClientStateCallback, TsolClientStateCallback, NULL))
		return;

	if (!AddCallback(&SelectionCallback, TsolSelectionCallback, NULL))
		return;

	/* Allocate storage in devPrivates */
	if (!dixRequestPrivate(tsolPrivateKey, sizeof (TsolPrivateRec))) {
		ErrorF("TsolExtensionInit: Cannot allocate devPrivate.\n");
		return;
	}

	/* Initialize the client info for server itself */
    	if (serverClient) {
        	TsolInfoPtr tsolinfo = GetClientTsolInfo(serverClient);
		if (tsolinfo->sl == NULL) {
			tsolinfo->sl = (bslabel_t *)lookupSL_low();
			tsolinfo->uid = 0;
			tsolinfo->pid = getpid();
			snprintf(tsolinfo->pname, MAXNAME, "client id %d (pid %d)",
  				serverClient->index, tsolinfo->pid);
		}
	}

	LoadTsolConfig();

	MakeTSOLAtoms();
	UpdateTsolNode(0, NULL);

	tsol_atom_sel_agnt = MakeAtom("_TSOL_SEL_AGNT", 14, 1);

	/* Initialize security hooks */
	tsolSecHook.CheckAuthorization = TsolCheckAuthorization;
	pSecHook = &tsolSecHook;

	XaceRegisterCallback(XACE_EXT_DISPATCH, TsolCheckExtensionAccess, NULL);
	XaceRegisterCallback(XACE_RESOURCE_ACCESS, TsolCheckResourceIDAccess, NULL);
	XaceRegisterCallback(XACE_PROPERTY_ACCESS, TsolCheckPropertyAccess, NULL);
	XaceRegisterCallback(XACE_SEND_ACCESS, TsolCheckSendAccess, NULL);
	XaceRegisterCallback(XACE_RECEIVE_ACCESS, TsolCheckReceiveAccess, NULL);
	XaceRegisterCallback(XACE_EXT_ACCESS, TsolCheckExtensionAccess, NULL);
	XaceRegisterCallback(XACE_DEVICE_ACCESS, TsolCheckDeviceAccess, NULL);
	XaceRegisterCallback(XACE_SCREEN_ACCESS, TsolCheckDeviceAccess, NULL);
	XaceRegisterCallback(XACE_SCREENSAVER_ACCESS, TsolCheckDeviceAccess, NULL);
	XaceRegisterCallback(XACE_SELECTION_ACCESS, TsolCheckSelectionAccess, NULL);
	XaceRegisterCallback(XACE_SERVER_ACCESS, TsolCheckServerAccess, NULL);
	XaceRegisterCallback(XACE_CLIENT_ACCESS, TsolCheckClientAccess, NULL);
	XaceRegisterCallback(XACE_KEY_AVAIL, TsolProcessKeyboard, NULL);
	XaceRegisterCallback(XACE_AUDIT_BEGIN, TsolAuditStart, NULL);
	XaceRegisterCallback(XACE_AUDIT_END, TsolAuditEnd, NULL);

	/* Save original Proc vectors */
	for (i = 0; i < PROCVECTORSIZE; i++) {
		TsolSavedProcVector[i] = ProcVector[i];
		TsolSavedSwappedProcVector[i] = SwappedProcVector[i];
	}

	ProcVector[X_InternAtom] = ProcTsolInternAtom;
	ProcVector[X_GetAtomName] = ProcTsolGetAtomName;

	ProcVector[X_CreateWindow] = ProcTsolCreateWindow;
	ProcVector[X_ChangeWindowAttributes] = ProcTsolChangeWindowAttributes;
	ProcVector[X_ConfigureWindow] = ProcTsolConfigureWindow;
	ProcVector[X_CirculateWindow] = ProcTsolCirculateWindow;
	ProcVector[X_ReparentWindow] = ProcTsolReparentWindow;
	ProcVector[X_GrabServer] = ProcTsolGrabServer;
	ProcVector[X_UngrabServer] = ProcTsolUngrabServer;
	ProcVector[X_GetImage] = ProcTsolGetImage;
	ProcVector[X_QueryTree] = ProcTsolQueryTree;
	ProcVector[X_QueryPointer] = ProcTsolQueryPointer;
	ProcVector[X_GetGeometry] = ProcTsolGetGeometry;
	ProcVector[X_CopyArea] = ProcTsolCopyArea;
	ProcVector[X_CopyPlane] = ProcTsolCopyPlane;
	ProcVector[X_PolySegment] = ProcTsolPolySegment;
	ProcVector[X_PolyRectangle] = ProcTsolPolyRectangle;

}

static CALLBACK(
    TsolCheckResourceIDAccess)
{
	XaceResourceAccessRec *rec = calldata;
	RESTYPE rtype = rec->rtype;

	switch (rtype) {
	case RT_WINDOW:
	case RT_PIXMAP:	
		/* Drawables policy */
		TsolCheckDrawableAccess(pcbl, nulldata, calldata);
		break;

	case RT_GC:
	case RT_CURSOR:
	case RT_FONT:
		TsolCheckXIDAccess(pcbl, nulldata, calldata);
		break;
	default:
		/* 
		 * Handle other resource types.
		 * In RANDR extension, usual window policy is 
		 * enforced before checking for RREventType.
		 */
		if (rtype == RREventType) {
			rec->status = Success;
		}
		break;
	}
}

static
CALLBACK(TsolSelectionCallback)
{
	SelectionInfoRec *pselinfo = (SelectionInfoRec *)calldata;
	Selection *pSel = pselinfo->selection;
	TsolResPtr tsolseln = TsolResourcePrivate(pSel);

	switch (pselinfo->kind) {
	case SelectionClientClose:
	    if (tsol_sel_agnt && pSel->selection ==  tsol_sel_agnt->selection) {
		tsol_sel_agnt = NULL; /* selection manager died. */
	    }
	/* fall through to reset the SL */

	case SelectionWindowDestroy:
	    tsolseln->sl = NULL; 
	    break;

	default:
	    /* All others handled in SelectionAccess handler */
	    break;
	}
}

static
CALLBACK(TsolClientStateCallback)
{
 	NewClientInfoRec *pci = (NewClientInfoRec *)calldata;
	ClientPtr client = pci->client;
	TsolInfoPtr tsolinfo = TsolClientPrivate(client);

	switch (client->clientState) {

	case ClientStateInitial:
		/* Got a new connection */
		TsolSetClientInfo(client);
		break;

	case ClientStateRunning:
		break;

	case ClientStateRetained:	/* client disconnected */
		break;
	case ClientStateGone:
		if (tpwin && wClient(tpwin) == client)
		    tpwin = NULL; /* reset tpwin */

		if (tsolinfo != NULL && tsolinfo->privs != NULL) {
			priv_freeset(tsolinfo->privs);
		}
		/* Audit disconnect */
		if (system_audit_on && (au_preselect(AUE_ClientDisconnect, &(tsolinfo->amask),
                              AU_PRS_BOTH, AU_PRS_USECACHE) == 1)) {
			auditwrite(AW_PRESELECT, &(tsolinfo->amask),AW_END);
			auditwrite(AW_EVENTNUM, AUE_ClientDisconnect,
                               AW_XCLIENT, client->index,
			       AW_SLABEL, tsolinfo->sl,
                               AW_RETURN, 0, 0, AW_WRITE, AW_END);

			tsolinfo->flags &= ~TSOL_DOXAUDIT;
			tsolinfo->flags &= ~TSOL_AUDITEVENT;
			auditwrite(AW_FLUSH, AW_END);
			auditwrite(AW_DISCARDRD, tsolinfo->asaverd, AW_END);
			auditwrite(AW_NOPRESELECT, AW_END);
		}
		break;

	default:
                break;
	}

}


static void
TsolReset(ExtensionEntry *extension)
{
    free_win_privsets();
    XaceDeleteCallback(XACE_EXT_DISPATCH, TsolCheckExtensionAccess, NULL);
    XaceDeleteCallback(XACE_RESOURCE_ACCESS, TsolCheckResourceIDAccess, NULL);
    XaceDeleteCallback(XACE_PROPERTY_ACCESS, TsolCheckPropertyAccess, NULL);
    XaceDeleteCallback(XACE_SEND_ACCESS, TsolCheckSendAccess, NULL);
    XaceDeleteCallback(XACE_RECEIVE_ACCESS, TsolCheckReceiveAccess, NULL);
    XaceDeleteCallback(XACE_EXT_ACCESS, TsolCheckExtensionAccess, NULL);
    XaceDeleteCallback(XACE_DEVICE_ACCESS, TsolCheckDeviceAccess, NULL);
    XaceDeleteCallback(XACE_SCREEN_ACCESS, TsolCheckDeviceAccess, NULL);
    XaceDeleteCallback(XACE_SCREENSAVER_ACCESS, TsolCheckDeviceAccess, NULL);
    XaceDeleteCallback(XACE_SELECTION_ACCESS, TsolCheckSelectionAccess, NULL);
    XaceDeleteCallback(XACE_SERVER_ACCESS, TsolCheckServerAccess, NULL);
    XaceDeleteCallback(XACE_CLIENT_ACCESS, TsolCheckClientAccess, NULL);
    XaceDeleteCallback(XACE_KEY_AVAIL, TsolProcessKeyboard, NULL);
    XaceDeleteCallback(XACE_AUDIT_BEGIN, TsolAuditStart, NULL);
    XaceDeleteCallback(XACE_AUDIT_END, TsolAuditEnd, NULL);
}

/*
 * Dispatch routine
 *
 */
static int
ProcTsolDispatch(register ClientPtr client)
{
    int retval;

    REQUEST(xReq);

    switch (stuff->data)
    {
        case X_SetPolyInstInfo:
            retval =  ProcSetPolyInstInfo(client);
            break;
        case X_SetPropLabel:
            retval =  ProcSetPropLabel(client);
            break;
        case X_SetPropUID:
            retval =  ProcSetPropUID(client);
            break;
        case X_SetResLabel:
            retval =  ProcSetResLabel(client);
            break;
        case X_SetResUID:
            retval =  ProcSetResUID(client);
            break;
        case X_GetClientAttributes:
            retval =  ProcGetClientAttributes(client);
            break;
        case X_GetClientLabel:
            retval = ProcGetClientLabel(client);
            break;
        case X_GetPropAttributes:
            retval =  ProcGetPropAttributes(client);
            break;
        case X_GetResAttributes:
            retval =  ProcGetResAttributes(client);
            break;
        case X_MakeTPWindow:
            retval =  ProcMakeTPWindow(client);
            break;
        case X_MakeTrustedWindow:
            retval =  ProcMakeTrustedWindow(client);
            break;
        case X_MakeUntrustedWindow:
            retval =  ProcMakeUntrustedWindow(client);
            break;
        default:
            SendErrorToClient(client, TsolReqCode, stuff->data, 0, BadRequest);
            retval = BadRequest;
    }
    return (retval);
}


static int
SProcTsolDispatch(register ClientPtr client)
{
    int n;
    int retval;

    REQUEST(xReq);

    swaps(&stuff->length, n);
    switch (stuff->data)
    {
        case X_SetPolyInstInfo:
            retval =  SProcSetPolyInstInfo(client);
            break;
        case X_SetPropLabel:
            retval =  SProcSetPropLabel(client);
            break;
        case X_SetPropUID:
            retval =  SProcSetPropUID(client);
            break;
        case X_SetResLabel:
            retval =  SProcSetResLabel(client);
            break;
        case X_SetResUID:
            retval =  SProcSetResUID(client);
            break;
        case X_GetClientAttributes:
            retval =  SProcGetClientAttributes(client);
            break;
        case X_GetClientLabel:
            retval = SProcGetClientLabel(client);
            break;
        case X_GetPropAttributes:
            retval =  SProcGetPropAttributes(client);
            break;
        case X_GetResAttributes:
            retval =  SProcGetResAttributes(client);
            break;
        case X_MakeTPWindow:
            retval =  SProcMakeTPWindow(client);
            break;
        case X_MakeTrustedWindow:
            retval =  SProcMakeTrustedWindow(client);
            break;
        case X_MakeUntrustedWindow:
            retval =  SProcMakeUntrustedWindow(client);
            break;
        default:
            SendErrorToClient(client, TsolReqCode, stuff->data, 0, BadRequest);
            retval = BadRequest;
    }
    return (retval);
}


/*
 * Individual routines
 */

static int
SProcSetPolyInstInfo(ClientPtr client)
{
    int n;

    REQUEST(xSetPolyInstInfoReq);
    swapl(&stuff->uid, n);
    swapl(&stuff->enabled, n);
    swaps(&stuff->sllength, n);

    return (ProcSetPolyInstInfo(client));
}

static int
SProcSetPropLabel(ClientPtr client)
{
    int n;

    REQUEST(xSetPropLabelReq);
    swapl(&stuff->id, n);
    swapl(&stuff->atom, n);
    swaps(&stuff->labelType, n);
    swaps(&stuff->sllength, n);
    swaps(&stuff->illength, n);

    return (ProcSetPropLabel(client));
}

static int
SProcSetPropUID(ClientPtr client)
{
    int n;

    REQUEST(xSetPropUIDReq);
    swapl(&stuff->id, n);
    swapl(&stuff->atom, n);
    swapl(&stuff->uid, n);

    return (ProcSetPropUID(client));
}

static int
SProcSetResLabel(ClientPtr client)
{
    int n;

    REQUEST(xSetResLabelReq);
    swapl(&stuff->id, n);
    swaps(&stuff->resourceType, n);
    swaps(&stuff->labelType, n);
    swaps(&stuff->sllength, n);
    swaps(&stuff->illength, n);

    return (ProcSetResLabel(client));
}

static int
SProcSetResUID(ClientPtr client)
{
    int n;

    REQUEST(xSetResUIDReq);
    swapl(&stuff->id, n);
    swaps(&stuff->resourceType, n);
    swapl(&stuff->uid, n);

    return (ProcSetResUID(client));
}

static int
SProcGetClientAttributes(ClientPtr client)
{
    int n;

    REQUEST(xGetClientAttributesReq);
    swapl(&stuff->id, n);

    return (ProcGetClientAttributes(client));
}

static int
SProcGetClientLabel(ClientPtr client)
{
    int n;

    REQUEST(xGetClientLabelReq);
    swapl(&stuff->id, n);
    swaps(&stuff->mask, n);

    return (ProcGetClientLabel(client));
}

static int
SProcGetPropAttributes(ClientPtr client)
{
    int n;

    REQUEST(xGetPropAttributesReq);
    swapl(&stuff->id, n);
    swapl(&stuff->atom, n);
    swaps(&stuff->mask, n);

    return (ProcGetPropAttributes(client));
}

static int
SProcGetResAttributes(ClientPtr client)
{
    int n;

    REQUEST(xGetResAttributesReq);
    swapl(&stuff->id, n);
    swaps(&stuff->resourceType, n);
    swaps(&stuff->mask, n);

    return (ProcGetResAttributes(client));
}

static int
SProcMakeTPWindow(ClientPtr client)
{
    int n;

    REQUEST(xMakeTPWindowReq);
    swapl(&stuff->id, n);

    return (ProcMakeTPWindow(client));
}

static int
SProcMakeTrustedWindow(ClientPtr client)
{
    int n;

    REQUEST(xMakeTrustedWindowReq);
    swapl(&stuff->id, n);

    return (ProcMakeTrustedWindow(client));
}

static int
SProcMakeUntrustedWindow(ClientPtr client)
{
    int n;

    REQUEST(xMakeUntrustedWindowReq);
    swapl(&stuff->id, n);

    return (ProcMakeUntrustedWindow(client));
}

/*
 * Set PolyInstantiation Info.
 * Normally a get(prop) will
 * get the prop. that has match sl, uid of the client. Setting
 * enabled to true will get only the prop. corresponding to
 * sl, uid specified instead of that of client. This is used
 * by dtwm/dtfile in special motif lib.
 */
static int
ProcSetPolyInstInfo(ClientPtr client)
{
    TsolInfoPtr tsolinfo = GetClientTsolInfo(client);
    bslabel_t *sl;
    int        err_code;
    extern priv_set_t *pset_win_mac_write;

    REQUEST(xSetPolyInstInfoReq);
    REQUEST_AT_LEAST_SIZE(xSetPolyInstInfoReq);

     /* Requires win_mac_write privilege */
    if (!client_has_privilege(tsolinfo, pset_win_mac_write)) {
        return (BadAccess);
    }

    sl = (bslabel_t *)(stuff + 1);

    tsolpolyinstinfo.enabled = stuff->enabled;
    tsolpolyinstinfo.uid = (uid_t) stuff->uid;
    tsolpolyinstinfo.sl = lookupSL(sl);

    return (client->noClientException);
}

static int
ProcSetPropLabel(ClientPtr client)
{
    TsolInfoPtr tsolinfo = GetClientTsolInfo(client);
    bslabel_t   *sl;
    WindowPtr    pWin;
    TsolResPtr  tsolprop;
    PropertyPtr  pProp;
    int          err_code;
    int rc;

    REQUEST(xSetPropLabelReq);

    REQUEST_AT_LEAST_SIZE(xSetPropLabelReq);


    rc = dixLookupWindow(&pWin, stuff->id, client, DixWriteAccess);
    if (rc != Success)
        return rc;

    if (!pWin)
    {
        client->errorValue = stuff->id;
        return (BadWindow);
    }
    if (!ValidAtom(stuff->atom))
    {
        client->errorValue = stuff->atom;
        return (BadAtom);
    }

    /* first see if property already exists */
    pProp = wUserProps (pWin);
    while (pProp)
    {
        if (pProp->propertyName == stuff->atom)
            break;
        pProp = pProp->next;
    }

    if (!pProp)
    {
        /* property does not exist */
        client->errorValue = stuff->atom;
        return (BadAtom);
    }

     /* Requires win_mac_write privilege */
    if (!client_has_privilege(tsolinfo, pset_win_mac_write)) {
        return (BadAccess);
    }

    /* Initialize property created internally by server */
    tsolprop = TsolResourcePrivate(pProp);

    sl = (bslabel_t *)(stuff + 1);

    if (!blequal(tsolprop->sl, sl)) {
        tsolprop->sl = lookupSL(sl);
    }

    return (client->noClientException);
}

static int
ProcSetPropUID(ClientPtr client)
{
    TsolInfoPtr tsolinfo = GetClientTsolInfo(client);
    WindowPtr   pWin;
    TsolResPtr tsolprop;
    PropertyPtr pProp;
    int         err_code;
    int 	rc;

    REQUEST(xSetPropUIDReq);

    REQUEST_SIZE_MATCH(xSetPropUIDReq);

    rc = dixLookupWindow(&pWin, stuff->id, client, DixReadAccess);
    if (rc != Success)
        return rc;

    if (!pWin)
    {
        client->errorValue = stuff->id;
        return (BadWindow);
    }

    if (!ValidAtom(stuff->atom))
    {
        client->errorValue = stuff->atom;
        return (BadAtom);
    }

    /* first see if property already exists */
    pProp = wUserProps (pWin);
    while (pProp)
    {
        if (pProp->propertyName == stuff->atom)
            break;
        pProp = pProp->next;
    }

    if (!pProp)
    {
        /* property does not exist */
        client->errorValue = stuff->atom;
        return (BadAtom);
    }

     /* Requires win_mac_write privilege */
    if (!client_has_privilege(tsolinfo, pset_win_mac_write)) {
        return (BadAccess);
    }

    /* Initialize property created internally by server */
    tsolprop = TsolResourcePrivate(pProp);

    tsolprop->uid = stuff->uid;

    return (client->noClientException);
}

static int
ProcSetResLabel(ClientPtr client)
{
    TsolInfoPtr tsolinfo = GetClientTsolInfo(client);
    bslabel_t  *sl;
    PixmapPtr   pMap;
    WindowPtr   pWin;
    xEvent      message;
    TsolResPtr  tsolres;
    int         err_code;
    int		rc;

    REQUEST(xSetResLabelReq);

    REQUEST_AT_LEAST_SIZE(xSetResLabelReq);

     /* Requires win_mac_write privilege */
    if (!client_has_privilege(tsolinfo, pset_win_mac_write)) {
        return (BadAccess);
    }

    sl = (bslabel_t *)(stuff + 1);
    switch (stuff->resourceType) {
        case SESSIONHI: /* set server session HI */
            memcpy(&SessionHI, sl, SL_SIZE);
            return (client->noClientException);

        case SESSIONLO: /* set server session LO */
            memcpy(&SessionLO, sl, SL_SIZE);
            return (client->noClientException);

        case IsWindow:
	    rc = dixLookupWindow(&pWin, stuff->id, client, DixWriteAccess);
    	    if (rc != Success)
		return rc;

            if (pWin)
            {
                tsolres = TsolResourcePrivate(pWin);
            }
            else
            {
                client->errorValue = stuff->id;
                return (BadWindow);
            }
            break;

        case IsPixmap:
	    rc = dixLookupDrawable((DrawablePtr *)&pMap, stuff->id, client,
				   M_DRAWABLE_PIXMAP, DixWriteAccess);
    	    if (rc != Success)
		return rc;
            if (pMap)
            {
                tsolres = TsolResourcePrivate(pMap);
            }
            else
            {
                client->errorValue = stuff->id;
                return (BadPixmap);
            }
            break;
	default:
	    client->errorValue = stuff->resourceType;
	    return (BadValue);
    }

    if (!blequal(tsolres->sl, sl)) {
	tsolres->sl = lookupSL(sl);
    }

    /* generate the notify event for windows */

    if (stuff->resourceType == IsWindow)
    {
	rc = dixLookupWindow(&pWin, stuff->id, client, DixReadAccess);
    	if (rc != Success)
	    return rc;

        message.u.u.type = ClientMessage; /* 33 */
        message.u.u.detail = 32;
        message.u.clientMessage.window = RootOf(pWin);
        message.u.clientMessage.u.l.type =
            MakeAtom("_TSOL_CMWLABEL_CHANGE", 21, 1);
        message.u.clientMessage.u.l.longs0 = RootOfClient(pWin);
        message.u.clientMessage.u.l.longs1 = stuff->id;
        DeliverEventsToWindow(PickPointer(client), pWin, &message, 1,
                              SubstructureRedirectMask, NullGrab);

    }
    return (client->noClientException);
}

static int
ProcSetResUID(ClientPtr client)
{
    TsolInfoPtr tsolinfo = GetClientTsolInfo(client);
    int       ScreenNumber;
    PixmapPtr pMap;
    WindowPtr pWin;
    TsolResPtr tsolres;
    int        err_code;
    int        rc;
    extern priv_set_t *pset_win_dac_write;

    REQUEST(xSetResUIDReq);

    REQUEST_SIZE_MATCH(xSetResUIDReq);

    switch (stuff->resourceType)
    {
        case STRIPEHEIGHT:
            if (!HasTrustedPath(tsolinfo))
                return (BadAccess);
            StripeHeight = stuff->uid;
            ScreenNumber = stuff->id;

            /* set Screen Stripe Size  */
            DoScreenStripeHeight(ScreenNumber);
            ScreenStripeHeight [ScreenNumber] = StripeHeight;
            return (client->noClientException);

        case RES_OUID:
            if (!HasTrustedPath(tsolinfo))
                return (BadAccess);

            OwnerUID = stuff->uid;
            OwnerUIDint = OwnerUID;
            AddUID(&OwnerUIDint);
            return (client->noClientException);

        case IsWindow:
	    rc = dixLookupWindow(&pWin, stuff->id, client, DixWriteAccess);
    	    if (rc != Success)
		return rc;

            if (pWin)
            {
                tsolres = TsolResourcePrivate(pWin);
            }
            else
            {
                client->errorValue = stuff->id;
                return (BadWindow);
            }
            break;
        case IsPixmap:
	    rc = dixLookupDrawable((DrawablePtr *)&pMap, stuff->id, client,
				   M_DRAWABLE_PIXMAP, DixWriteAccess);
	    if (rc != Success)
		return rc;

            if (pMap)
            {
                tsolres = TsolResourcePrivate(pMap);
            }
            else
            {
                client->errorValue = stuff->id;
                return (BadPixmap);
            }
            break;
        default:
            return (BadValue);
    }

     /* Requires win_dac_write privilege */
    if (!client_has_privilege(tsolinfo, pset_win_dac_write)) {
        return (BadAccess);
    }

    tsolres->uid = stuff->uid;

    return (client->noClientException);
}

static int
ProcGetClientAttributes(ClientPtr client)
{
    int         n;
    int         err_code;
    int         rc;
    ClientPtr   res_client; /* resource owner client */
    TsolInfoPtr tsolinfo, res_tsolinfo;
    WindowPtr	pWin;

    xGetClientAttributesReply rep;

    REQUEST(xGetClientAttributesReq);
    REQUEST_SIZE_MATCH(xGetClientAttributesReq);

    /* Valid window check */
    rc = dixLookupWindow(&pWin, stuff->id, client, DixReadAccess);
    if (rc != Success)
	return rc;

    if (!(res_client = clients[CLIENT_ID(stuff->id)]))
    {
        client->errorValue = stuff->id;
        return (BadWindow);
    }

    tsolinfo = GetClientTsolInfo(client);
    res_tsolinfo = GetClientTsolInfo(res_client);

    /* Transfer the client info to reply rec */
    rep.type = X_Reply;
    rep.sequenceNumber = client->sequence;
    rep.trustflag = (res_tsolinfo->forced_trust == 1
	|| res_tsolinfo->trusted_path) ? (BYTE)1 : (BYTE)0;
    rep.uid = (CARD32) res_tsolinfo->uid;
    rep.pid = (CARD32) res_tsolinfo->pid;
    rep.gid = (CARD32) res_tsolinfo->gid;
    rep.auditid = (CARD32) res_tsolinfo->auid;
    rep.sessionid = (CARD32) res_tsolinfo->asid;
    rep.iaddr = (CARD32) res_tsolinfo->iaddr;
    rep.length = (CARD32) 0;

    if (client->swapped)
    {
        swaps(&rep.sequenceNumber, n);
        swapl(&rep.length, n);
        swapl(&rep.uid, n);
        swapl(&rep.pid, n);
        swapl(&rep.gid, n);
        swapl(&rep.auditid, n);
        swapl(&rep.sessionid, n);
        swapl(&rep.iaddr, n);
    }

    WriteToClient(client, sizeof(xGetClientAttributesReply), (char *)&rep);

    return (client->noClientException);
}

static int
ProcGetClientLabel(ClientPtr client)
{
    int         n;
    int         reply_length = 0;
    int         rc;
    int         err_code;
    Bool        write_to_client = 0;
    bslabel_t   *sl;
    ClientPtr   res_client; /* resource owner client */
    TsolInfoPtr tsolinfo, res_tsolinfo;
    WindowPtr	pWin;

    xGenericReply rep;

    REQUEST(xGetClientLabelReq);
    REQUEST_SIZE_MATCH(xGetClientLabelReq);

    /* Valid window check */
    rc = dixLookupWindow(&pWin, stuff->id, client, DixReadAccess);
    if (rc != Success)
	return rc;

    if (!(res_client = clients[CLIENT_ID(stuff->id)]))
    {
        client->errorValue = stuff->id;
        return (BadWindow);
    }

    tsolinfo = GetClientTsolInfo(client);
    res_tsolinfo = GetClientTsolInfo(res_client);

    /* Transfer the client info to reply rec */
    rep.type = X_Reply;
    rep.sequenceNumber = client->sequence;

    /* allocate temp storage for labels */
    sl = (bslabel_t *)(xalloc(SL_SIZE));
    rep.data00 = rep.data01 = 0;
    if (sl == NULL)
        return (BadAlloc);

    /* fill the fields as per request mask */
    if (stuff->mask & RES_SL)
    {
        memcpy(sl, res_tsolinfo->sl, SL_SIZE);
        rep.data00 = SL_SIZE;
    }

    rep.length = (CARD32)(rep.data00)/4;

    if (rep.length > 0)
    {
        reply_length = rep.length*4;
        write_to_client = 1;
    }
    if (client->swapped)
    {
        swaps(&rep.sequenceNumber, n);
        swapl(&rep.length, n);
        swapl(&rep.data00, n);
        swapl(&rep.data01, n);
    }

    WriteToClient(client, sizeof(xGenericReply), (char *)&rep);

    if (write_to_client == 1)
    {
        WriteToClient(client, reply_length, (char *)sl);
    }
    xfree(sl);

    return (client->noClientException);
}

static int
ProcGetPropAttributes(ClientPtr client)
{
    int          n;
    int          reply_length = 0;
    int          rc;
    Bool         write_to_client = 0;
    PropertyPtr  pProp;
    bslabel_t   *sl;
    WindowPtr    pWin;
    TsolResPtr  tsolprop;
    TsolResPtr	tsolres;
    TsolInfoPtr  tsolinfo = GetClientTsolInfo(client);

    xGetPropAttributesReply rep;

    REQUEST(xGetPropAttributesReq);

    REQUEST_SIZE_MATCH(xGetPropAttributesReq);

    rc = dixLookupWindow(&pWin, stuff->id, client, DixReadAccess);
    if (rc != Success)
	return rc;

    if (!ValidAtom(stuff->atom))
    {
        client->errorValue = stuff->atom;
        return (BadAtom);
    }

    /* first see if property already exists */
    pProp = wUserProps (pWin);
    while (pProp)
    {
        tsolprop = TsolResourcePrivate(pProp);

        if (pProp->propertyName == stuff->atom) {

            if (tsolpolyinstinfo.enabled) {
                if (tsolprop->uid == tsolpolyinstinfo.uid &&
                        tsolprop->sl == tsolpolyinstinfo.sl)
                    break; /* match found */
            } else {
                if (tsolprop->uid == tsolinfo->uid &&
                        tsolprop->sl == tsolinfo->sl) {
                    break; /* match found */
                }
            }
        }
        pProp = pProp->next;
    }

    if (!pProp)
    {
        /* property does not exist, use window's attributes */
	tsolres = TsolResourcePrivate(pWin);
	tsolprop = NULL;
    }

    if (stuff->mask & RES_UID)
    {
        rep.uid = tsolprop ? tsolprop->uid : tsolres->uid;
    }

    /* allocate temp storage for labels */
    sl = (bslabel_t *)(xalloc(SL_SIZE));
    rep.sllength = rep.illength = 0;
    if (sl == NULL)
        return (BadAlloc);

    /* fill the fields as per request mask */
    if (stuff->mask & RES_SL)
    {
        memcpy(sl, tsolprop ? tsolprop->sl : tsolres->sl, SL_SIZE);
        rep.sllength = SL_SIZE;
    }

    rep.type = X_Reply;
    rep.sequenceNumber = client->sequence;
    rep.length = (CARD32) (rep.sllength)/4;

    if (rep.length > 0)
    {
        reply_length = rep.length*4;
        write_to_client = 1;
    }
    if (client->swapped)
    {
        swaps(&rep.sequenceNumber, n);
        swapl(&rep.length, n);
        swapl(&rep.uid, n);
        swaps(&rep.sllength, n);
        swaps(&rep.illength, n);
    }

    WriteToClient(client, sizeof(xGetPropAttributesReply), (char *)&rep);

    if (write_to_client == 1)
    {
        WriteToClient(client, reply_length, (char *)sl);
    }
    xfree(sl);

    return (client->noClientException);
}

static int
ProcGetResAttributes(ClientPtr client)
{
    int         n;
    int         reply_length = 0;
    int         rc;
    Bool        write_to_client = 0;
    bslabel_t  *sl;
    PixmapPtr   pMap;
    WindowPtr   pWin;
    TsolResPtr  tsolres = NULL;

    xGetResAttributesReply rep;

    REQUEST(xGetResAttributesReq);

    REQUEST_SIZE_MATCH(xGetResAttributesReq);

    if (stuff->mask & RES_STRIPE)
    {
        rep.uid = ScreenStripeHeight[stuff->id];
    }
    if (stuff->mask & RES_OUID)
    {
        rep.owneruid = OwnerUID;
    }
    if (stuff->resourceType == IsWindow &&
        (stuff->mask & (RES_UID | RES_SL )))
    {
	rc = dixLookupWindow(&pWin, stuff->id, client, DixReadAccess);
	if (rc != Success)
	    return rc;

	tsolres = TsolResourcePrivate(pWin);
    }

    if (stuff->resourceType == IsPixmap &&
        (stuff->mask & (RES_UID | RES_SL )))
    {
	rc = dixLookupDrawable((DrawablePtr *)&pMap, stuff->id, client,
			       M_DRAWABLE_PIXMAP, DixWriteAccess);
	if (rc != Success)
	    return rc;

	tsolres = TsolResourcePrivate(pMap);
    }

    if (stuff->mask & RES_UID)
    {
        rep.uid = tsolres->uid;
    }

    /* allocate temp storage for labels */
    sl = (bslabel_t *)(xalloc(SL_SIZE));
    rep.sllength = rep.illength = rep.iillength = 0;
    if (sl == NULL)
        return (BadAlloc);

    /* fill the fields as per request mask */
    if (stuff->mask & RES_SL)
    {
        memcpy(sl, tsolres->sl, SL_SIZE);
        rep.sllength = SL_SIZE;
    }

    rep.type = X_Reply;
    rep.sequenceNumber = client->sequence;
    rep.length = (CARD32) (rep.sllength)/4;

    if (rep.length > 0)
    {
        reply_length = rep.length*4;
        write_to_client = 1;
    }
    if (client->swapped)
    {
        swaps(&rep.sequenceNumber, n);
        swapl(&rep.length, n);
        swapl(&rep.uid, n);
        swapl(&rep.owneruid, n);
        swaps(&rep.sllength, n);
        swaps(&rep.illength, n);
        swaps(&rep.iillength, n);
    }

    WriteToClient(client, sizeof(xGetResAttributesReply), (char *)&rep);

    if (write_to_client == 1)
    {
            WriteToClient(client, reply_length, (char *)sl);
    }
    xfree(sl);

    return (client->noClientException);
}

int
ProcMakeTPWindow(ClientPtr client)
{
    WindowPtr pWin = NULL, pParent;
    int       rc;
    int       err_code;
    TsolInfoPtr  tsolinfo;

    REQUEST(xMakeTPWindowReq);
    REQUEST_SIZE_MATCH(xMakeTPWindowReq);

    /*
     * Session type single-level? This is set by the
     * label builder
     */
    tsolinfo = GetClientTsolInfo(client);
    if (tsolinfo && HasTrustedPath(tsolinfo) &&
		blequal(&SessionLO, &SessionHI) && stuff->id == 0) {
	tsolMultiLevel = FALSE;
	return (client->noClientException);
    }

#if defined(PANORAMIX)
    if (!noPanoramiXExtension)
    {
        PanoramiXRes     *panres = NULL;
        int         j;

	if ((panres = (PanoramiXRes *)LookupIDByType(stuff->id, XRT_WINDOW))
		== NULL)
	    return BadWindow;

	FOR_NSCREENS_BACKWARD(j)
	{
		rc = dixLookupWindow(&pWin, panres->info[j].id, 
			client, DixWriteAccess);
		if (rc != Success)
		    return rc;

		/* window should not be root but child of root */
		if (!pWin || (!pWin->parent))
		{
		    client->errorValue = stuff->id;
		    return (BadWindow);
		}

		pParent = pWin->parent;
		if (pParent->firstChild != pWin)
		{
		    tpwin = (WindowPtr)NULL;
		    ReflectStackChange(pWin, pParent->firstChild, VTStack);
		}
	}
    } else
#endif
    {
	rc = dixLookupWindow(&pWin, stuff->id, client, DixWriteAccess);
	if (rc != Success)
	    return rc;


	/* window should not be root but child of root */
	if (!pWin || (!pWin->parent))
	{
            client->errorValue = stuff->id;
            return (BadWindow);
	}

	pParent = pWin->parent;
	if (pParent->firstChild != pWin)
	{
	    tpwin = (WindowPtr)NULL;
	    ReflectStackChange(pWin, pParent->firstChild, VTStack);
	}
    }

    tpwin = pWin;

    /*
     * Force kbd & ptr ungrab. This will cause
     * screen to lock even when kbd/ptr grabbed by
     * a client
     */
    BreakAllGrabs(client);
    return (client->noClientException);
}

/*
 * Turn on window's Trusted bit
 */
static int
ProcMakeTrustedWindow(ClientPtr client)
{
    WindowPtr    pWin;
    int          rc;
    int          err_code;
    TsolInfoPtr  tsolinfo;

    REQUEST(xMakeTrustedWindowReq);
    REQUEST_SIZE_MATCH(xMakeTrustedWindowReq);

    rc = dixLookupWindow(&pWin, stuff->id, client, DixWriteAccess);
    if (rc != Success)
	return rc;

    /* window should not be root but child of root */
    if (!pWin || (!pWin->parent))
    {
        client->errorValue = stuff->id;
        return (BadWindow);
    }
    tsolinfo = GetClientTsolInfo(client);

    if (!HasTrustedPath(tsolinfo))
	return (BadAccess);

    /* Turn on Trusted bit of the window */
    tsolinfo->forced_trust = 1;
    return (client->noClientException);
}

/*
 * Turn off window's Trusted bit
 */
static int
ProcMakeUntrustedWindow(ClientPtr client)
{
    WindowPtr    pWin;
    int          rc;
    int          err_code;
    TsolInfoPtr  tsolinfo;

    REQUEST(xMakeUntrustedWindowReq);
    REQUEST_SIZE_MATCH(xMakeUntrustedWindowReq);

    rc = dixLookupWindow(&pWin, stuff->id, client, DixWriteAccess);
    if (rc != Success)
	return rc;

    /* window should not be root but child of root */
    if (!pWin || (!pWin->parent))
    {
        client->errorValue = stuff->id;
        return (BadWindow);
    }

    tsolinfo = GetClientTsolInfo(client);
    if (!HasTrustedPath(tsolinfo))
	return (BadAccess);

    tsolinfo->forced_trust = 0;
    tsolinfo->trusted_path = FALSE;

    return (client->noClientException);
}

/*
 * Break keyboard & ptr grabs of clients other than
 * the requesting client.
 * Called from ProcMakeTPWindow.
 */
static void
BreakAllGrabs(ClientPtr client)
{
    ClientPtr	    grabclient;
    DeviceIntPtr    keybd = PickKeyboard(client);
    GrabPtr         kbdgrab = keybd->deviceGrab.grab;
    DeviceIntPtr    mouse = PickPointer(client);
    GrabPtr         ptrgrab = mouse->deviceGrab.grab;

	if (kbdgrab) {
	    	grabclient = clients[CLIENT_ID(kbdgrab->resource)];
		if (client->index != grabclient->index)
			(*keybd->deviceGrab.DeactivateGrab)(keybd);
	}

	if (ptrgrab) {
	    	grabclient = clients[CLIENT_ID(ptrgrab->resource)];
		if (client->index != grabclient->index)
			(*mouse->deviceGrab.DeactivateGrab)(mouse);
        }
}

/*
 * Trusted Network interface module. Uses tsix API
 */
extern au_id_t ucred_getauid(const ucred_t *uc);
extern au_asid_t ucred_getasid(const ucred_t *uc);
extern const au_mask_t *ucred_getamask(const ucred_t *uc);
extern tsol_host_type_t tsol_getrhtype(char *);

static void
TsolSetClientInfo(ClientPtr client)
{
	bslabel_t *sl;
	bslabel_t admin_low;
	priv_set_t *privs;
	const au_mask_t *amask;
	socklen_t namelen;
	struct auditinfo auinfo;
	struct auditinfo *pauinfo;
	OsCommPtr oc = (OsCommPtr)client->osPrivate;
	int fd = oc->fd;
	ucred_t *uc = NULL;

	TsolInfoPtr tsolinfo = TsolClientPrivate(client);

	/* Get client attributes from the socket */
	if (getpeerucred(fd, &uc) == -1) {
		const char *errmsg = strerror(errno);

		tsolinfo->uid = (uid_t)(-1);
		tsolinfo->sl = NULL;
		snprintf(tsolinfo->pname, MAXNAME,
			 "client id %d (pid unknown)", client->index);
		LogMessageVerb(X_ERROR, TSOL_MSG_ERROR,
			       TSOL_LOG_PREFIX "Cannot get client attributes"
			       " for %s, getpeerucred failed: %s\n",
			       tsolinfo->pname, errmsg);
		return;
	}

	/* Extract individual fields from the cred structure */
	tsolinfo->zid = ucred_getzoneid(uc);
	tsolinfo->uid = ucred_getruid(uc);
	tsolinfo->euid = ucred_geteuid(uc);
	tsolinfo->gid = ucred_getrgid(uc);
	tsolinfo->egid = ucred_getegid(uc);
	tsolinfo->pid = ucred_getpid(uc);
	sl = ucred_getlabel(uc);
	tsolinfo->sl = (bslabel_t *)lookupSL(sl);

	/* store a string for debug/error messages - would be nice to
	   get the real process name out of /proc in the future
	 */
	snprintf(tsolinfo->pname, MAXNAME, "client id %d (pid %d)",
		 client->index, tsolinfo->pid);

	/* Set privileges */
	if ((tsolinfo->privs = priv_allocset()) != NULL) {
		if (tsolMultiLevel) {
			privs = (priv_set_t *)ucred_getprivset(uc, PRIV_EFFECTIVE);
			if (privs == NULL) {
				priv_emptyset(tsolinfo->privs);
			} else {
				priv_copyset(privs, tsolinfo->privs);
			}
		} else {
			priv_fillset(tsolinfo->privs);
		}
	}

	tsolinfo->priv_debug = FALSE;


	/*
	 * For remote hosts, the uid is determined during access control
	 * using Secure RPC
	 */
	if (tsolinfo->zid == (zoneid_t)-1) {
		tsolinfo->client_type = CLIENT_REMOTE;
	} else {
		tsolinfo->client_type = CLIENT_LOCAL;
	}


	/* Set Trusted Path for local clients */
	if (tsolinfo->zid == GLOBAL_ZONEID) {
		tsolinfo->trusted_path = TRUE;
	}else {
		tsolinfo->trusted_path = FALSE;
	}

	if (tsolinfo->trusted_path || !tsolMultiLevel)
		setClientTrustLevel(client, XSecurityClientTrusted);
	else
		setClientTrustLevel(client, XSecurityClientUntrusted);

        tsolinfo->forced_trust = 0;
        tsolinfo->iaddr = 0;

	bsllow(&admin_low);

	/* Set reasonable defaults for remote clients */
	namelen = sizeof (tsolinfo->saddr);
	if (getpeername(fd, (struct sockaddr *)&tsolinfo->saddr, &namelen) == 0
	  && (tsolinfo->client_type == CLIENT_REMOTE)) {
		int errcode;
		char hostbuf[NI_MAXHOST];
		tsol_host_type_t host_type;

		/* Use NI_NUMERICHOST to avoid DNS lookup */
		errcode = getnameinfo((struct sockaddr *)&(tsolinfo->saddr), namelen,
			hostbuf, sizeof(hostbuf), NULL, 0, NI_NUMERICHOST);

		if (errcode) {
			perror(gai_strerror(errcode));
		} else {
			host_type = tsol_getrhtype(hostbuf);
			if ((host_type == SUN_CIPSO) &&
				blequal(tsolinfo->sl, &admin_low)) {
				tsolinfo->trusted_path = TRUE;
				setClientTrustLevel(client,
						    XSecurityClientTrusted);
				priv_fillset(tsolinfo->privs);
			}
		}
	}

	/* setup audit context */
	if (getaudit(&auinfo) == 0) {
	    pauinfo = &auinfo;
	} else {
	    pauinfo = NULL;
	}

	/* Audit id */
	tsolinfo->auid = ucred_getauid(uc);
	if (tsolinfo->auid == AU_NOAUDITID) {
	    tsolinfo->auid = UID_NOBODY;
	}

	/* session id */
	tsolinfo->asid = ucred_getasid(uc);

	/* Audit mask */
	if ((amask = ucred_getamask(uc)) != NULL) {
	    tsolinfo->amask = *amask;
	} else {
	    if (pauinfo != NULL) {
	        tsolinfo->amask = pauinfo->ai_mask;
	    } else {
	        tsolinfo->amask.am_failure = 0; /* clear the masks */
	        tsolinfo->amask.am_success = 0;
	    }
	}

	tsolinfo->asaverd = 0;

	ucred_free(uc);
}

static enum auth_stat tsol_why;
extern bool_t xdr_opaque_auth(XDR *, struct opaque_auth *);

static char *
tsol_authdes_decode(char *inmsg, int len)
{
    struct rpc_msg  msg;
    char            cred_area[MAX_AUTH_BYTES];
    char            verf_area[MAX_AUTH_BYTES];
    char            *temp_inmsg;
    struct svc_req  r;
    bool_t          res0, res1;
    XDR             xdr;
    SVCXPRT         xprt;

    temp_inmsg = (char *) xalloc(len);
    memmove(temp_inmsg, inmsg, len);

    memset((char *)&msg, 0, sizeof(msg));
    memset((char *)&r, 0, sizeof(r));
    memset(cred_area, 0, sizeof(cred_area));
    memset(verf_area, 0, sizeof(verf_area));

    msg.rm_call.cb_cred.oa_base = cred_area;
    msg.rm_call.cb_verf.oa_base = verf_area;
    tsol_why = AUTH_FAILED;
    xdrmem_create(&xdr, temp_inmsg, len, XDR_DECODE);

    if ((r.rq_clntcred = (caddr_t) xalloc(MAX_AUTH_BYTES)) == NULL)
        goto bad1;
    r.rq_xprt = &xprt;

    /* decode into msg */
    res0 = xdr_opaque_auth(&xdr, &(msg.rm_call.cb_cred));
    res1 = xdr_opaque_auth(&xdr, &(msg.rm_call.cb_verf));
    if ( ! (res0 && res1) )
         goto bad2;

    /* do the authentication */

    r.rq_cred = msg.rm_call.cb_cred;        /* read by opaque stuff */
    if (r.rq_cred.oa_flavor != AUTH_DES) {
        tsol_why = AUTH_TOOWEAK;
        goto bad2;
    }
#ifdef SVR4
    if ((tsol_why = __authenticate(&r, &msg)) != AUTH_OK) {
#else
    if ((tsol_why = _authenticate(&r, &msg)) != AUTH_OK) {
#endif
            goto bad2;
    }
    return (((struct authdes_cred *) r.rq_clntcred)->adc_fullname.name);

bad2:
    Xfree(r.rq_clntcred);
bad1:
    return ((char *)0); /* ((struct authdes_cred *) NULL); */
}

static Bool
TsolCheckNetName (unsigned char *addr, short len, pointer closure)
{
    return (len == (short) strlen ((char *) closure) &&
            strncmp ((char *) addr, (char *) closure, len) == 0);
}

extern	int getdomainname(char *, int);

static XID
TsolCheckAuthorization(unsigned int name_length, char *name,
		       unsigned int data_length, char *data,
		       ClientPtr client, char **reason)
{
	char	domainname[128];
	char	netname[128];
	char	audit_ret;
	u_int	audit_val;
	uid_t	client_uid;
	gid_t	client_gid;
	int	client_gidlen;
	char	*fullname;
	gid_t	client_gidlist;
	XID	auth_token = (XID)(-1);
	TsolInfoPtr tsolinfo = GetClientTsolInfo(client);

	if (tsolinfo->uid == (uid_t) -1) {
		/* Retrieve uid from SecureRPC */
		if (strncmp(name, SECURE_RPC_AUTH, (size_t)name_length) == 0) {
			fullname = tsol_authdes_decode(data, data_length);
			if (fullname == NULL) {
				ErrorF("Unable to authenticate Secure RPC client");
			} else {
				if (netname2user(fullname,
					&client_uid, &client_gid,
					&client_gidlen, &client_gidlist)) {
					tsolinfo->uid = client_uid;
				} else {
					ErrorF("netname2user failed");
				}
			}
		}
	}

	if (tsolinfo->uid == (uid_t)-1) {
		tsolinfo->uid = UID_NOBODY; /* uid not available */
	}

	/*
	 * For multilevel desktop, limit connections to the trusted path
	 * i.e. global zone until a user logs in and the trusted stripe
	 * is in place. Unlabeled connections are rejected.
	 */
	if ((OwnerUID == (uid_t )(-1)) || (tsolMultiLevel && tpwin == NULL)) {
		if (HasTrustedPath(tsolinfo)) {
			auth_token = CheckAuthorization(name_length, name, data_length,
				data, client, reason);
		}
	} else {
		/*
		 * Workstation Owner set, client must be within label
		 * range or have trusted path
		 */
		if (tsolinfo->uid == OwnerUID) {
			if ((tsolinfo->sl != NULL &&
			     (bldominates(tsolinfo->sl, &SessionLO) &&
			      bldominates(&SessionHI, tsolinfo->sl))) ||
			    (HasTrustedPath(tsolinfo))) {
			    auth_token = (XID)(tsolinfo->uid);
			}
		} else {
			/* Allow root from global zone */
			if (tsolinfo->uid == 0 && HasTrustedPath(tsolinfo)) {
				auth_token = (XID)(tsolinfo->uid);
			} else {
				/*
				 * Access check based on uid. Check if
				 * roles or other uids have  been added by
				 * xhost +role@
				 */
				getdomainname(domainname, sizeof(domainname));
				if (!user2netname(netname, tsolinfo->uid, domainname)) {
					return ((XID)-1);
				}
				if (ForEachHostInFamily (FamilyNetname, TsolCheckNetName,
						(pointer) netname)) {
					return ((XID)(tsolinfo->uid));
				} else {
					return (CheckAuthorization(name_length, name, data_length,
						data, client, reason));
				}
			}
		}
	}

	/* Audit the connection */
	if (auth_token == (XID)(-1)) {
		audit_ret = (char )-1; /* failure */
		audit_val = 1;
	} else {
		audit_ret = 0; /* success */
		audit_val = 0;
	}

	if (system_audit_on &&
		(au_preselect(AUE_ClientConnect, &(tsolinfo->amask),
                      AU_PRS_BOTH, AU_PRS_USECACHE) == 1)) {
		int status;
		u_short connect_port = 0;
		struct in_addr *connect_addr = NULL;
		struct sockaddr_in *sin;
		struct sockaddr_in6 *sin6;

		switch (tsolinfo->saddr.ss_family) {
                        case AF_INET:
                                sin = (struct sockaddr_in *)&(tsolinfo->saddr);
                                connect_addr = &(sin->sin_addr);
                                connect_port = sin->sin_port;
                                break;
                        case AF_INET6:
                                sin6 = (struct sockaddr_in6 *)&(tsolinfo->saddr);
                                connect_addr = (struct in_addr *)&(sin6->sin6_addr);
                                connect_port = sin6->sin6_port;
                                break;
		}

		if (connect_addr == NULL || connect_port == 0) {
        		status = auditwrite(AW_EVENTNUM, AUE_ClientConnect,
				AW_XCLIENT, client->index,
				AW_SLABEL, tsolinfo->sl,
				AW_RETURN, audit_ret, audit_val,
				AW_WRITE, AW_END);
		} else {
        		status = auditwrite(AW_EVENTNUM, AUE_ClientConnect,
				AW_XCLIENT, client->index,
				AW_SLABEL, tsolinfo->sl,
				AW_INADDR, connect_addr,
				AW_IPORT, connect_port,
				AW_RETURN, audit_ret, audit_val,
				AW_WRITE, AW_END);
		}

		if (!status)
			(void) auditwrite(AW_FLUSH, AW_END);
		tsolinfo->flags &= ~TSOL_DOXAUDIT;
		tsolinfo->flags &= ~TSOL_AUDITEVENT;
	}

	return (auth_token);
}

static CALLBACK(
TsolProcessKeyboard)
{
    XaceKeyAvailRec *rec = (XaceKeyAvailRec *) calldata;
    xEvent *xE = rec->event;
    DeviceIntPtr keybd = rec->keybd;
/*  int count = rec->count; */
    HotKeyPtr hotkey = TsolKeyboardPrivate(keybd);

    if (xE->u.u.type == KeyPress)
    {
	if (!hotkey->initialized)
	    InitHotKey(keybd);

        if (((xE->u.u.detail == hotkey->key) &&
		(xE->u.keyButtonPointer.state != 0 &&
		 xE->u.keyButtonPointer.state == hotkey->shift)) ||
            ((xE->u.u.detail == hotkey->altkey) &&
		(xE->u.keyButtonPointer.state != 0 &&
		 xE->u.keyButtonPointer.state == hotkey->altshift)))
	{
	    HandleHotKey(keybd);
	}
    }
}

static CALLBACK(
TsolCheckSendAccess)
{
	XaceSendAccessRec *rec = (XaceSendAccessRec *) calldata;
	ClientPtr client = rec->client;
	WindowPtr pWin = rec->pWin;
	TsolResPtr tsolres;
	xpolicy_t flags;
	TsolInfoPtr tsolinfo;

	rec->status = BadAccess;
	if (client == NULL) {
		rec->status = Success;
		return;
	}

	if (WindowIsRoot(pWin) || XTSOLTrusted(pWin)) {
		rec->status = Success;
		return;
	}

	tsolinfo = GetClientTsolInfo(client);
	tsolres = TsolResourcePrivate(pWin);
	flags = (TSOL_MAC|TSOL_DAC|TSOL_DOMINATE|TSOL_READOP);
	rec->status = tsol_check_policy(tsolinfo, tsolres, flags, MAJOROP_CODE);

#ifndef NO_TSOL_DEBUG_MESSAGES
    if (rec->status != Success) {
    	tsolinfo = GetClientTsolInfo(client);
    	LogMessageVerb(X_ERROR, TSOL_MSG_ERROR,
		   TSOL_LOG_PREFIX
		   "TsolCheckSendAccess(%s, %s) = %s\n",
		   tsolinfo->pname,
		   TsolRequestNameString(MAJOROP_CODE),
		   TsolErrorNameString(rec->status));
    }

#endif /* !NO_TSOL_DEBUG_MESSAGES */
}

static CALLBACK(
TsolCheckReceiveAccess)
{
    XaceReceiveAccessRec *rec = (XaceReceiveAccessRec *) calldata;

	rec->status = Success;
}



static CALLBACK(
TsolCheckSelectionAccess)
{
    XaceSelectionAccessRec *rec = (XaceSelectionAccessRec *) calldata;
    ClientPtr client = rec->client;
    Selection *pSel = *rec->ppSel;
    Atom selAtom = pSel->selection;
    Mask access_mode = rec->access_mode;
    int reqtype;
    TsolResPtr tsolseln;
    TsolInfoPtr tsolinfo; /* tsol client info */
    tsolinfo = GetClientTsolInfo(client);
    int polySelection = PolySelection(selAtom);

    reqtype = MAJOROP_CODE;

    switch (reqtype) {
      case X_SetSelectionOwner:
	/*
	 * Special processing for selection agent. This is how
	 * we know who to redirect privileged ConvertSelection requests.
	 * This is also used to fake the onwership of GetSelectionOwner requests.
	 */
	if (selAtom == tsol_atom_sel_agnt) {
	    if (HasWinSelection(tsolinfo)) {
	        if (tsolinfo->flags & TSOL_AUDITEVENT)
		   auditwrite(AW_USEOFPRIV, 1, PRIV_WIN_SELECTION,
			      AW_APPEND, AW_END);
	        tsol_sel_agnt = pSel; /* owner of this seln */
	    } else {
	        if (tsolinfo->flags & TSOL_AUDITEVENT)
		    auditwrite(AW_USEOFPRIV, 0, PRIV_WIN_SELECTION,
			      AW_APPEND, AW_END);
		client->errorValue = selAtom;
		rec->status = BadAtom;
		return;
	   }
	}

        /*
         * The callback function is only called if at least one matching selection exists.
         * If it has no tsol attributes then we know it is the only match so we don't need to
         * check for polyinstantiation. Just initialize it and return.
         */

	tsolseln = TsolResourcePrivate(pSel);

	if (tsolseln->sl == NULL) {
            tsolseln->sl = tsolinfo->sl;
            tsolseln->uid = tsolinfo->uid;
	    break;
	}

	if (polySelection) {

	    /* for poly-selections, search from the beginning to see if sl,uid match */
	    for (pSel = CurrentSelections; pSel; pSel = pSel->next) {

		if (pSel->selection == selAtom) {
		    tsolseln = TsolResourcePrivate(pSel);
		    if (tsolseln->uid == tsolinfo->uid &&
			 tsolseln->sl == tsolinfo->sl)
		        break;
		}
	    }               

	    if (pSel) {
		/* found a match */
	        *rec->ppSel = pSel; 
	    } else {
		/*
		* Doesn't match yet; we'll get called again
		* After it gets created.
		*/
		rec->status = BadMatch;
	    }
	} else {
	    /* Assign the sl & uid */
	    tsolseln->sl = tsolinfo->sl;
            tsolseln->uid = tsolinfo->uid;
	}
	break;

      case X_GetSelectionOwner:
      case X_ConvertSelection:
	    if (polySelection) {

		/* for poly-selections, search from the beginning to see if sl,uid match */
		for (pSel = CurrentSelections; pSel; pSel = pSel->next) {

		    if (pSel->selection == selAtom) {
		        tsolseln = TsolResourcePrivate(pSel);
		        if (tsolseln->uid == tsolinfo->uid &&
			     tsolseln->sl == tsolinfo->sl)
		            break;
		    }
		}               

	        if (pSel) {
	            *rec->ppSel = pSel; /* found match */
	        } else {
		    /*
		    * Doesn't match yet; we'll get called again
		    * After it gets created.
		    */
		    rec->status = BadMatch;
		    return;
	        }
	    }

	    /*
	     * Selection Agent processing. Override the owner
	     */
	    tsolseln = TsolResourcePrivate(pSel);
	    if (!HasWinSelection(tsolinfo) &&
			(tsolseln->uid != tsolinfo->uid ||
			tsolseln->sl != tsolinfo->sl) && 
			pSel->window != None && tsol_sel_agnt != NULL) {
                pSel = tsol_sel_agnt;
           } else {
		if (HasWinSelection(tsolinfo) && 
			(tsolinfo->flags & TSOL_AUDITEVENT)) {
		    auditwrite(AW_USEOFPRIV, 1, PRIV_WIN_SELECTION, AW_APPEND, AW_END);
		}
	    }
	    *rec->ppSel = pSel;
	    break;

       default:
#ifndef NO_TSOL_DEBUG_MESSAGES
              tsolinfo = GetClientTsolInfo(client);
              LogMessageVerb(X_NOT_IMPLEMENTED, TSOL_MSG_UNIMPLEMENTED,
                     TSOL_LOG_PREFIX
                     "policy not implemented for CheckSelectionAccess(%s, %s, %s, %s) = %s\n",
                      tsolinfo->pname,
                     TsolDixAccessModeNameString(access_mode),
                     TsolRequestNameString(reqtype),
                     NameForAtom(selAtom),
                     TsolErrorNameString(rec->status));
#endif /* !NO_TSOL_DEBUG_MESSAGES */
             break;
    }
}

static CALLBACK(
TsolCheckPropertyAccess)
{
    XacePropertyAccessRec *rec = (XacePropertyAccessRec *) calldata;
    ClientPtr client = rec->client;
    WindowPtr pWin = rec->pWin;
    PropertyPtr pProp = *rec->ppProp;
    Atom propertyName = pProp->propertyName;
    Mask access_mode = rec->access_mode;
    TsolInfoPtr tsolinfo = GetClientTsolInfo(client);
    int reqtype;
    TsolResPtr tsolprop;
    TsolResPtr tsolres;
    int tsol_method;
    Status retcode;
    xpolicy_t flags = 0;

    reqtype = MAJOROP_CODE;
    tsolres = TsolResourcePrivate(pWin);
    if (pProp != NULL) {
	int polyprop = PolyProperty(propertyName, pWin);

	tsolprop = TsolResourcePrivate(pProp);

	if (!polyprop) {

	    tsolres = TsolResourcePrivate(pWin);
	    if (tsolprop->sl == NULL) {
		/* Initialize with label/uid etc */
		if (WindowIsRoot(pWin)) {
		    tsolprop->sl = tsolinfo->sl;        /* use client's sl/uid */
		    tsolprop->uid = tsolinfo->uid;
		    tsolprop->pid = tsolinfo->pid;
		} else {
		    tsolprop->sl = tsolres->sl;         /* use window's sl/uid */
		    tsolprop->uid = tsolres->uid;
		    tsolprop->pid = tsolres->pid;
                }
	    }

	    if (access_mode & (DixReadAccess | DixGetAttrAccess))
	        flags = (TSOL_MAC|TSOL_DAC|TSOL_DOMINATE|TSOL_READOP);

	    if (access_mode & (DixWriteAccess | DixSetAttrAccess))
	        flags = (TSOL_MAC|TSOL_DAC|TSOL_WRITEOP);

	    retcode = tsol_check_policy(tsolinfo, tsolprop, flags, MAJOROP_CODE);
	    if (retcode != Success && (access_mode & DixGetAttrAccess)) {
		/* If current property is not accessible, move on to 
		 *  next one for ListProperty
		 */
		retcode = Success;
		*rec->ppProp = pProp->next; /* ignore failurefor List Prop */
	    }
	    rec->status = retcode;
	} else {
	    /* Handle polyinstantiated property */
	    if (tsolprop->sl == NULL) { /* New PolyProp */
		if (!(access_mode & DixCreateAccess)) {
		    rec->status = BadImplementation;
		    return;
	        }
		/* Initialize with label/uid */
		tsolprop->sl = tsolinfo->sl;
		tsolprop->uid = tsolinfo->uid;
		rec->status = Success;
	    } else {
		/* search for a matching (sl, uid) pair */
		while (pProp) {
	    	    tsolprop = TsolResourcePrivate(pProp);
		    if (pProp->propertyName == propertyName &&
			    tsolprop->sl == tsolinfo->sl &&
			    tsolprop->uid == tsolinfo->uid)
			break; /* match found */
		    pProp = pProp->next;
		} 

		if (pProp) {
		    *rec->ppProp = pProp; /* found */
		    rec->status = Success;
		} else {
		    rec->status = BadMatch;
	        }
	    }
	}
#ifndef NO_TSOL_DEBUG_MESSAGES
    LogMessageVerb(X_INFO, TSOL_MSG_ACCESS_TRACE,
		   TSOL_LOG_PREFIX
		   "TsolCheckPropertyAccess(%s, 0x%x, %s, %s) = %s\n",
		   tsolinfo->pname, pWin->drawable.id,
		   NameForAtom(propertyName),
		   TsolDixAccessModeNameString(access_mode),
		   TsolPolicyReturnString(rec->status));
#endif /* !NO_TSOL_DEBUG_MESSAGES */
    }
}

static CALLBACK(
TsolCheckExtensionAccess)
{
    XaceExtAccessRec *rec = (XaceExtAccessRec *) calldata;

    if (TsolDisabledExtension(rec->ext->name)) {
	rec->status = BadAccess;
    } else {
	rec->status = Success;
    }
}

#ifdef UNUSED
/*
 * Return TRUE if host is cipso
 */
int
host_is_cipso(int fd)
{
	struct sockaddr sname;
	socklen_t namelen;
	char *rhost;
	tsol_host_type_t host_type;
	struct sockaddr_in *so = (struct sockaddr_in *)&sname;
	extern tsol_host_type_t tsol_getrhtype(char *);

	namelen = sizeof (sname);
	if (getpeername(fd, &sname, &namelen) == -1) {
		perror("getsockname: failed\n");
		return FALSE;
	}

	rhost = inet_ntoa(so->sin_addr);
	host_type = tsol_getrhtype(rhost);
	if (host_type == SUN_CIPSO) {
		return TRUE;
	}

	return FALSE;
}
#endif
