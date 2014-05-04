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

#include <sys/param.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <ucred.h>
#include <pwd.h>
#include <strings.h>
#include <sys/wait.h>
#include "auditwrite.h"
#include <bsm/libbsm.h>
#include <bsm/audit_uevents.h>
#include "tsol.h"

#include "inputstr.h"
#include "xkbstr.h"
#include "xkbsrv.h"

#define NEED_REPLIES

#include "dixevents.h"
#include "selection.h"
#include "osdep.h"
#include "tsolpolicy.h"
#include "swaprep.h"
#include "swapreq.h"
#include "servermd.h"
#ifdef PANORAMIX
#include "../Xext/panoramiXsrv.h"
#endif
#ifdef XCSECURITY
#include "../Xext/securitysrv.h"
#endif
#include "xace.h"
#include "xacestr.h"

/*
 * The event # here match those in /usr/include/bsm/audit_uevents.h.
 * Changes in one should go with corresponding changes in another.
 */

#define MAX_AUDIT_EVENTS 100

int audit_eventsid[100][2] = {
	{ X_CreateWindow, AUE_CreateWindow },
	{ X_ChangeWindowAttributes, AUE_ChangeWindowAttributes },
	{ X_GetWindowAttributes, AUE_GetWindowAttributes },
	{ X_DestroyWindow, AUE_DestroyWindow },
	{ X_DestroySubwindows, AUE_DestroySubwindows },
	{ X_ChangeSaveSet, AUE_ChangeSaveSet },
	{ X_ReparentWindow, AUE_ReparentWindow },
	{ X_MapWindow, AUE_MapWindow },
	{ X_MapSubwindows, AUE_MapSubwindows },
	{ X_UnmapWindow, AUE_UnmapWindow },
	{ X_UnmapSubwindows, AUE_UnmapSubwindows },
	{ X_ConfigureWindow, AUE_ConfigureWindow },
	{ X_CirculateWindow, AUE_CirculateWindow },
	{ X_GetGeometry, AUE_GetGeometry },
	{ X_QueryTree, AUE_QueryTree },
	{ X_InternAtom, AUE_InternAtom },
	{ X_GetAtomName, AUE_GetAtomName },
	{ X_ChangeProperty, AUE_ChangeProperty },
	{ X_DeleteProperty, AUE_DeleteProperty },
	{ X_GetProperty, AUE_GetProperty },
	{ X_ListProperties, AUE_ListProperties },
	{ X_SetSelectionOwner, AUE_SetSelectionOwner },
	{ X_GetSelectionOwner, AUE_GetSelectionOwner },
	{ X_ConvertSelection, AUE_ConvertSelection },
	{ X_SendEvent, AUE_SendEvent },
	{ X_GrabPointer, AUE_GrabPointer },
	{ X_UngrabPointer, AUE_UngrabPointer },
	{ X_GrabButton, AUE_GrabButton },
	{ X_UngrabButton, AUE_UngrabButton },
	{ X_ChangeActivePointerGrab, AUE_ChangeActivePointerGrab },
	{ X_GrabKeyboard, AUE_GrabKeyboard },
	{ X_UngrabKeyboard, AUE_UngrabKeyboard },
	{ X_GrabKey, AUE_GrabKey },
	{ X_UngrabKey, AUE_UngrabKey },
	{ X_GrabServer, AUE_GrabServer },
	{ X_UngrabServer, AUE_UngrabServer },
	{ X_QueryPointer, AUE_QueryPointer },
	{ X_GetMotionEvents, AUE_GetMotionEvents },
	{ X_TranslateCoords, AUE_TranslateCoords },
	{ X_WarpPointer, AUE_WarpPointer },
	{ X_SetInputFocus, AUE_SetInputFocus },
	{ X_GetInputFocus, AUE_GetInputFocus },
	{ X_QueryKeymap, AUE_QueryKeymap },
	{ X_SetFontPath, AUE_SetFontPath },
	{ X_FreePixmap, AUE_FreePixmap },
	{ X_ChangeGC, AUE_ChangeGC },
	{ X_CopyGC, AUE_CopyGC },
	{ X_SetDashes, AUE_SetDashes },
	{ X_SetClipRectangles, AUE_SetClipRectangles },
	{ X_FreeGC, AUE_FreeGC },
	{ X_ClearArea, AUE_ClearArea },
	{ X_CopyArea, AUE_CopyArea },
	{ X_CopyPlane, AUE_CopyPlane },
	{ X_PolyPoint, AUE_PolyPoint },
	{ X_PolyLine, AUE_PolyLine },
	{ X_PolySegment, AUE_PolySegment },
	{ X_PolyRectangle, AUE_PolyRectangle },
	{ X_PolyArc, AUE_PolyArc },
	{ X_FillPoly, AUE_FillPolygon },
	{ X_PolyFillRectangle, AUE_PolyFillRectangle },
	{ X_PolyFillArc, AUE_PolyFillArc },
	{ X_PutImage, AUE_PutImage },
	{ X_GetImage, AUE_GetImage },
	{ X_PolyText8, AUE_PolyText8 },
	{ X_PolyText16, AUE_PolyText16 },
	{ X_ImageText8, AUE_ImageText8 },
	{ X_ImageText16, AUE_ImageText16 },
	{ X_CreateColormap, AUE_CreateColormap },
	{ X_FreeColormap, AUE_FreeColormap },
	{ X_CopyColormapAndFree, AUE_CopyColormapAndFree },
	{ X_InstallColormap, AUE_InstallColormap },
	{ X_UninstallColormap, AUE_UninstallColormap },
	{ X_ListInstalledColormaps, AUE_ListInstalledColormaps },
	{ X_AllocColor, AUE_AllocColor },
	{ X_AllocNamedColor, AUE_AllocNamedColor },
	{ X_AllocColorCells, AUE_AllocColorCells },
	{ X_AllocColorPlanes, AUE_AllocColorPlanes },
	{ X_FreeColors, AUE_FreeColors },
	{ X_StoreColors, AUE_StoreColors },
	{ X_StoreNamedColor, AUE_StoreNamedColor },
	{ X_QueryColors, AUE_QueryColors },
	{ X_LookupColor, AUE_LookupColor },
	{ X_CreateCursor, AUE_CreateCursor },
	{ X_CreateGlyphCursor, AUE_CreateGlyphCursor },
	{ X_FreeCursor, AUE_FreeCursor },
	{ X_RecolorCursor, AUE_RecolorCursor },
	{ X_ChangeKeyboardMapping, AUE_ChangeKeyboardMapping },
	{ X_ChangeKeyboardControl, AUE_ChangeKeyboardControl },
	{ X_Bell, AUE_Bell },
	{ X_ChangePointerControl, AUE_ChangePointerControl },
	{ X_SetScreenSaver, AUE_SetScreenSaver },
	{ X_ChangeHosts, AUE_ChangeHosts },
	{ X_SetAccessControl, AUE_SetAccessControl },
	{ X_SetCloseDownMode, AUE_SetCloseDownMode },
	{ X_KillClient, AUE_KillClient },
	{ X_RotateProperties, AUE_RotateProperties },
	{ X_ForceScreenSaver, AUE_ForceScreenSaver },
	{ X_SetPointerMapping, AUE_SetPointerMapping },
	{ X_SetModifierMapping, AUE_SetModifierMapping },
	{ X_NoOperation, AUE_XExtensions }
};


extern priv_set_t *pset_win_config;
extern TsolResPtr TsolDrawablePrivateate(DrawablePtr pDraw, ClientPtr client);
extern int
tsol_check_policy(TsolInfoPtr tsolinfo, TsolResPtr tsolres, xpolicy_t flags, int reqcode);
extern Bool client_has_privilege(TsolInfoPtr tsolinfo, priv_set_t *priv);


#define INITIAL_TSOL_NODELENGTH 1500

/*
 * Get number of atoms defined in the system
 */
static Atom
GetLastAtom(void)
{
	Atom a = (Atom) 1; /* atoms start at 1 */

	while (ValidAtom(a)) {
		a++;
	}

	return (--a);
}

/*
 * Update Tsol info for atoms. This function gets
 * called typically during initialization. But, it could also get
 * called if some atoms are created internally by server.
 */
void
UpdateTsolNode(Atom thisAtom, ClientPtr client)
{
	Atom lastAtom = GetLastAtom();
	Atom ia;
	int newsize;

	/* Allocate & Initialize the node for the first time */
	if (tsol_node == NULL) {
		newsize = (lastAtom > INITIAL_TSOL_NODELENGTH ? 
			lastAtom : INITIAL_TSOL_NODELENGTH);

		tsol_node = (TsolNodePtr )xalloc((newsize + 1) * sizeof(TsolNodeRec));
		if (tsol_node == NULL) {
			ErrorF("Cannot allocate memory for Tsol node\n");
			return;
		}

		tsol_nodelength = newsize;

		/* Atom id 0 is invalid */
		tsol_lastAtom = 0;
		tsol_node[0].flags = 0;
		tsol_node[0].slcount = 0;
		tsol_node[0].sl = NULL;
		tsol_node[0].slsize = 0;
		tsol_node[0].IsSpecial = 0;
	}

	/* If the node is already allocated, see if it needs to be extended */
	if (lastAtom > tsol_lastAtom) {
		tsol_node = (TsolNodePtr )xrealloc(tsol_node, 
			(lastAtom + 1) * sizeof(TsolNodeRec));

		if (tsol_node == NULL) {
			ErrorF("Cannot allocate memory for Tsol node\n");
			return;
		}

		tsol_nodelength = lastAtom + 1;

		/*
		 * Initialize all the newly created atoms
		 */
		for (ia = tsol_lastAtom + 1; ia <= lastAtom; ia++) {
			const char *atomname = NameForAtom(ia);

			tsol_node[ia].slcount = 0;
			tsol_node[ia].sl = NULL;
			tsol_node[ia].slsize= 0;
			tsol_node[ia].flags = MatchTsolConfig(atomname, strlen(atomname));
			tsol_node[ia].IsSpecial = SpecialName(atomname, strlen(atomname));
			if (client == NULL) {
				/* Mark as internal atom for GetAtomName to succeed */
				tsol_node[ia].flags |= TSOLM_ATOM;
			}
				

		}
		tsol_lastAtom = lastAtom;
	}

	/* Store the label info for non-global atoms */
	if (thisAtom != 0 && client != NULL && 
			(tsol_node[thisAtom].flags & TSOLM_ATOM) == 0) {
		TsolInfoPtr tsolinfo = GetClientTsolInfo(client);
		TsolNodePtr tndp =  &(tsol_node[thisAtom]);
		int k;

		/* private atoms must have a matching sl */
		for (k = 0; k < tndp->slcount; k++) {
			if (tsolinfo->sl == tndp->sl[k]) {
				return; /* found */
			}
		}

		/* Allocate storage for sl if needed */
		if (tndp->sl == NULL) {
			tndp->sl = (bslabel_t **)xalloc(NODE_SLSIZE * (sizeof(bslabel_t *)));

			if (tndp->sl == NULL) {
				ErrorF("Not enough memory for atoms\n");
			}

			tndp->slcount = 0;
			tndp->slsize = NODE_SLSIZE;
		}

		/* Expand storage space for sl if needed */
		if (tndp->slsize < tndp->slcount) {
			newsize = tndp->slsize + NODE_SLSIZE;
			tndp->sl = (bslabel_t **)xrealloc(tndp->sl, 
				newsize * (sizeof(bslabel_t *)));
			if (tndp->sl == NULL) {
				ErrorF("Not enough memory for atoms\n");
			}
			tndp->slsize = newsize;
		}


		/* Store client's sl */
		tndp->sl[tndp->slcount] = tsolinfo->sl;
		tndp->slcount++;
	}
}

int
ProcTsolInternAtom(ClientPtr client)
{
    Atom atom;
    char *tchar;
    REQUEST(xInternAtomReq);

    REQUEST_FIXED_SIZE(xInternAtomReq, stuff->nbytes);
    if ((stuff->onlyIfExists != xTrue) && (stuff->onlyIfExists != xFalse))
    {
	client->errorValue = stuff->onlyIfExists;
        return(BadValue);
    }
    tchar = (char *) &stuff[1];
    atom = MakeAtom(tchar, stuff->nbytes, !stuff->onlyIfExists);

    if (atom != BAD_RESOURCE)
    {
        /* Assign tsol attributes to this atom */
        UpdateTsolNode(atom, client);

	xInternAtomReply reply;
	reply.type = X_Reply;
	reply.length = 0;
	reply.sequenceNumber = client->sequence;
	reply.atom = atom;
	WriteReplyToClient(client, sizeof(xInternAtomReply), &reply);
	return(client->noClientException);
    }
    else
	return (BadAlloc);
}

int
ProcTsolGetAtomName(ClientPtr client)
{
    const char *str;
    xGetAtomNameReply reply;
    int len;
    REQUEST(xResourceReq);

    REQUEST_SIZE_MATCH(xResourceReq);

    if ((str = NameForAtom(stuff->id)))
    {
        char *blank_str = " ";
        char *atomname;
	TsolNodePtr tndp;

	tndp = &(tsol_node[stuff->id]);
	/* non-global atoms must have matching SL */
	if ((tndp->flags & TSOLM_ATOM) == 0) {
	    int k;
	    TsolInfoPtr tsolinfo = GetClientTsolInfo(client);

	    for (k = 0; k < tndp->slcount; k++) {
		if (tsolinfo->sl == tndp->sl[k]) 
		    break;
	    }

	    /* SL can't be found, so return a blank string */
	    if (k == tndp->slcount)
		str = blank_str;
	}

	len = strlen(str);
	reply.type = X_Reply;
	reply.length = (len + 3) >> 2;
	reply.sequenceNumber = client->sequence;
	reply.nameLength = len;
	WriteReplyToClient(client, sizeof(xGetAtomNameReply), &reply);
	(void)WriteToClient(client, len, str);
	return(client->noClientException);
    }
    else 
    { 
	client->errorValue = stuff->id;
	return (BadAtom);
    }
}

int
TsolInitWindow(ClientPtr client, WindowPtr pWin)
{
    bslabel_t admin_low;
    TsolInfoPtr tsolinfo = GetClientTsolInfo(client);
    TsolResPtr  tsolres = TsolResourcePrivate(pWin);

    tsolres->uid = tsolinfo->uid;
    tsolres->sl = tsolinfo->sl;
    tsolres->pid = tsolinfo->pid;

    if (client == serverClient)
	tsolres->internal = TRUE;
    else
	tsolres->internal = FALSE;

    bsllow(&admin_low);
    if (blequal(tsolres->sl, &admin_low))
        tsolres->flags = TRUSTED_MASK;
    else
        tsolres->flags = 0;

    return (Success);
}

int
TsolInitPixmap(ClientPtr client, PixmapPtr pMap)
{
    TsolInfoPtr tsolinfo = GetClientTsolInfo(client);
    TsolResPtr  tsolres = TsolResourcePrivate(pMap);

    tsolres->uid = tsolinfo->uid;
    tsolres->sl = tsolinfo->sl;
    tsolres->flags = 0;

    return (Success);
}

/* Generic ProcVector wrapper for functions which just need to set the
   client's TrustLevel to Trusted before executing. */
static inline int
ProcTsolUnwrapWithTrust(ClientPtr client, int majorop)
{
    int result, savedtrust;

    savedtrust = setClientTrustLevel(client, XSecurityClientTrusted);
    result = (*TsolSavedProcVector[majorop])(client);
    setClientTrustLevel(client, savedtrust);

    return result;
}


static void
ResetStripeWindow(ClientPtr client)
{
    WindowPtr pParent;
    WindowPtr pWin = NULL;
    int	      rc;

#if defined(PANORAMIX)
    if (!noPanoramiXExtension)
    {
	PanoramiXRes     *panres = NULL;
	int         j;

	if (tpwin) {
            if ((panres = (PanoramiXRes *)LookupIDByType(tpwin->drawable.id,
			XRT_WINDOW)) == NULL)
		return;
	}

	FOR_NSCREENS_BACKWARD(j)
	{
	    if (panres == NULL)
		return;
	    /* Validate trusted stripe window */
	    rc = dixLookupWindow(&pWin, panres->info[j].id, client, 
		DixReadAccess);
	    if (rc != Success)
	        return;

	    if (tpwin == NullWindow || pWin == NullWindow)
		return;

	    pParent = pWin->parent;
    	    if (!pParent || pParent->firstChild == pWin)
		return;

	    ReflectStackChange(pWin, pParent->firstChild, VTStack);
    	}
    } else
#endif
    {
	/* Validate trusted stripe window */
	if (tpwin) {
            rc = dixLookupWindow(&pWin, tpwin->drawable.id, client, 
		DixReadAccess);
            if (rc != Success)
                return;
	}

	if (tpwin == NullWindow || pWin == NullWindow)
	    return;

	pParent = tpwin->parent;
	/* stripe is already at head, nothing to do */
	if (!pParent || pParent->firstChild == tpwin)
	    return;

	ReflectStackChange(tpwin, pParent->firstChild, VTStack);
    }
}


/* Generic ProcVector wrapper for functions which just need to have
   ResetStripeWindow called after executing. */
static inline int
ProcTsolUnwrapAndResetStripe(ClientPtr client, int majorop)
{
    int result;

    result = (*TsolSavedProcVector[majorop])(client);
    ResetStripeWindow(client);

    return result;
}

int
ProcTsolCreateWindow(ClientPtr client)
{
    return ProcTsolUnwrapAndResetStripe(client, X_CreateWindow);
}

int
ProcTsolChangeWindowAttributes(ClientPtr client)
{
    return ProcTsolUnwrapAndResetStripe(client, X_ChangeWindowAttributes);
}

int
ProcTsolConfigureWindow(ClientPtr client)
{
    return ProcTsolUnwrapAndResetStripe(client, X_ConfigureWindow);
}

int
ProcTsolCirculateWindow(ClientPtr client)
{
    return ProcTsolUnwrapAndResetStripe(client, X_CirculateWindow);
}

int
ProcTsolReparentWindow(ClientPtr client)
{
    return ProcTsolUnwrapAndResetStripe(client, X_ReparentWindow);
}

/*
 * HandleHotKey -
 * HotKey is Meta(Diamond)+ Stop Key
 * Breaks untrusted Ptr and Kbd grabs.
 * Trusted Grabs are NOT broken
 * Warps pointer to the Trusted Stripe if not Trusted grabs in force.
 */
void
HandleHotKey(DeviceIntPtr keybd)
{
    int	            x, y;
    Bool            trusted_grab = FALSE;
    ClientPtr       client;
    DeviceIntPtr    mouse = GetPairedDevice(keybd);
    TsolInfoPtr	    tsolinfo;
    GrabPtr         ptrgrab = mouse->deviceGrab.grab;
    GrabPtr         kbdgrab = keybd->deviceGrab.grab;
    ScreenPtr       pScreen;

    if (kbdgrab)
    {
	client = clients[CLIENT_ID(kbdgrab->resource)];
	tsolinfo = GetClientTsolInfo(client);

        if (tsolinfo)
        {
            if (HasTrustedPath(tsolinfo))
                trusted_grab = TRUE;
            else
	        (*keybd->deviceGrab.DeactivateGrab)(keybd);
	}

	if (ptrgrab)
	{
	    client = clients[CLIENT_ID(ptrgrab->resource)];
	    tsolinfo = GetClientTsolInfo(client);

            if (tsolinfo)
            {
                if (HasTrustedPath(tsolinfo))
                    trusted_grab = TRUE;
                else
	            (*mouse->deviceGrab.DeactivateGrab)(mouse);
	    }
        }
    }

    if (!trusted_grab)
    {
        /*
         * Warp the pointer to the Trusted Stripe
         */
	    pScreen = screenInfo.screens[0];
	    x = pScreen->width/2;
	    y = pScreen->height - StripeHeight/2;
	    (*pScreen->SetCursorPosition)(mouse, pScreen, x, y, TRUE);
    }
}

#ifdef UNUSED
void
PrintSiblings(WindowPtr p1)
{
    WindowPtr p2;

    if (p1 == NULL || p1->parent == NULL) return;

    p2 = p1->parent->firstChild;
    while (p2)
    {
	ErrorF( "(%x, %d, %d, %x)\n", p2, p2->drawable.width,
	    p2->drawable.height, p2->prevSib);
	p2 = p2->nextSib;
    }
}

/*
 * Checks that tpwin & its siblings have same
 * parents. Returns 0 if OK, a # indicating which
 * Sibling has a bad parent
 */
int
CheckTPWin(void)
{
	WindowPtr pWin;
	int count = 1;

	pWin = tpwin->nextSib;
	while (pWin)
	{
		if (pWin->parent->parent)
			return count;
		pWin = pWin->nextSib;
		++count;
	}
	return 0;
}
#endif /* UNUSED */

/* NEW */

int
ProcTsolGetGeometry(ClientPtr client)
{
    xGetGeometryReply rep;
    int status;

    REQUEST(xResourceReq);

    if ( noPanoramiXExtension )
    {
        if ((status = GetGeometry(client, &rep)) != Success)
	    return status;

        /* Reduce root window height = stripe height */
        if (stuff->id == rep.root)
        {
            rep.height -= StripeHeight;
        }

        WriteReplyToClient(client, sizeof(xGetGeometryReply), &rep);
        return(client->noClientException);

    } else
    {
        status = (*TsolSavedProcVector[X_GetGeometry])(client);
        return (status);
    }
}

int
ProcTsolGrabServer(ClientPtr client)
{
    TsolInfoPtr tsolinfo = GetClientTsolInfo(client);

    /* REQUEST(xResourceReq); */
    REQUEST_SIZE_MATCH(xReq);

    if (priv_win_config ||
		client_has_privilege(tsolinfo, pset_win_config)) {
    	return (*TsolSavedProcVector[X_GrabServer])(client);
    } else {
	/* turn off auditing because operation ignored */
        tsolinfo->flags &= ~TSOL_DOXAUDIT;
        tsolinfo->flags &= ~TSOL_AUDITEVENT;

        return(client->noClientException);
    }
}

int
ProcTsolUngrabServer(ClientPtr client)
{
    TsolInfoPtr tsolinfo = GetClientTsolInfo(client);

    /* REQUEST(xResourceReq); */
    REQUEST_SIZE_MATCH(xReq);

    if (priv_win_config ||
		client_has_privilege(tsolinfo, pset_win_config)) {
        return (*TsolSavedProcVector[X_UngrabServer])(client);
    } else {
	/* turn off auditing because operation ignored */
        tsolinfo->flags &= ~TSOL_DOXAUDIT;
        tsolinfo->flags &= ~TSOL_AUDITEVENT;

        return(client->noClientException);
    }
}

int
ProcTsolQueryTree(ClientPtr client)
{
    xQueryTreeReply reply;
    int rc, numChildren = 0;
    WindowPtr pChild, pWin, pHead;
    Window  *childIDs = (Window *)NULL;

#ifdef TSOL
    TsolInfoPtr  tsolinfo = GetClientTsolInfo(client);
    TsolResPtr tsolres;
    xpolicy_t flags;
#endif  /* TSOL */

    REQUEST(xResourceReq);

    REQUEST_SIZE_MATCH(xResourceReq);
    rc = dixLookupWindow(&pWin, stuff->id, client, DixListAccess);
    if (rc != Success)
        return rc;

#ifdef TSOL
    flags = (TSOL_MAC|TSOL_DAC|TSOL_READOP);
    /*
     * Because of its recursive nature, QuerryTree can leave a huge trail
     * of audit records which could make deciphering the audit log for
     * critical records difficult. So we turn off any more auditing of
     * this protocol.
     */
    tsolinfo->flags &= ~TSOL_DOXAUDIT;
    tsolinfo->flags &= ~TSOL_AUDITEVENT;
#endif /* TSOL */

    reply.type = X_Reply;
    reply.root = WindowTable[pWin->drawable.pScreen->myNum]->drawable.id;
    reply.sequenceNumber = client->sequence;
    if (pWin->parent)
	reply.parent = pWin->parent->drawable.id;
    else
        reply.parent = (Window)None;
    pHead = RealChildHead(pWin);
    for (pChild = pWin->lastChild; pChild != pHead; pChild = pChild->prevSib)
#ifdef TSOL
    {
	tsolres = TsolResourcePrivate(pChild);
	if (tsol_check_policy(tsolinfo, tsolres, flags, MAJOROP_CODE) == Success) {
		numChildren++;
    	}
    }
#else /* !TSOL */
	numChildren++;
#endif /* TSOL */
    if (numChildren)
    {
	int curChild = 0;

	childIDs = (Window *) xalloc(numChildren * sizeof(Window));
	if (!childIDs)
	    return BadAlloc;
	for (pChild = pWin->lastChild; pChild != pHead; pChild = pChild->prevSib)
#ifdef TSOL
	{

	    tsolres = TsolResourcePrivate(pChild);
	    if (tsol_check_policy(tsolinfo, tsolres, flags, MAJOROP_CODE) == Success) {
	        childIDs[curChild++] = pChild->drawable.id;
    	    }
    	}
#else /* !TSOL */
	    childIDs[curChild++] = pChild->drawable.id;
#endif /* TSOL */
    }

    reply.nChildren = numChildren;
    reply.length = (numChildren * sizeof(Window)) >> 2;

    WriteReplyToClient(client, sizeof(xQueryTreeReply), &reply);
    if (numChildren)
    {
    	client->pSwapReplyFunc = (ReplySwapPtr) Swap32Write;
	WriteSwappedDataToClient(client, numChildren * sizeof(Window), childIDs);
	xfree(childIDs);
    }

    return(client->noClientException);
}

CALLBACK(
TsolAuditStart)
{
    XaceAuditRec *rec = (XaceAuditRec *) calldata;
    ClientPtr client = rec->client;

    unsigned int protocol;
    int xevent_num = -1;
    int count = 0;
    int status = 0;
    Bool do_x_audit = FALSE;
    Bool audit_event = FALSE;
    TsolInfoPtr tsolinfo = (TsolInfoPtr)NULL;
    tsolinfo = GetClientTsolInfo(client);
    if (system_audit_on &&
	(tsolinfo->amask.am_success || tsolinfo->amask.am_failure)) {

	do_x_audit = TRUE;
        auditwrite(AW_PRESELECT, &(tsolinfo->amask), AW_END);

        /*
         * X audit events start from 9101 in audit_uevents.h. The first two
         * events are non-protocol ones viz. ClientConnect, mapped to 9101
         * and ClientDisconnect, mapped to 9102.
         * The protocol events are mapped from 9103 onwards in the serial
         * order of their respective protocol opcode, for eg, the protocol
         * UngrabPointer which is has a protocol opcode 27 is mapped to
         * 9129 (9102 + 27).
         * All extension protocols are mapped to a single audit event
         * AUE_XExtension as opcodes are assigined dynamically to these
         * protocols. We set the extension protocol opcode to be 128, one
         * more than the last standard opcode.
         */
        protocol = (unsigned int)MAJOROP_CODE;
	if (protocol > X_NoOperation) {
             xevent_num = audit_eventsid[MAX_AUDIT_EVENTS - 1][1];
             audit_event = TRUE;
	} else {
            for (count = 0; count < MAX_AUDIT_EVENTS; count++) {
                 if (protocol == audit_eventsid[count][0]) {
                 	xevent_num = audit_eventsid[count][1];
                        audit_event = TRUE;
                        break;
                  }
	    }
	}

	/*
	 * Exclude Clients with Trusted Path such as tsoldtwm, tsoldtsession etc
	 * from generating the audit records for X protocols
	 */
	if (audit_event && do_x_audit &&  !HasTrustedPath(tsolinfo) &&
	    (au_preselect(xevent_num, &(tsolinfo->amask), AU_PRS_BOTH,
                              AU_PRS_USECACHE) == 1)) {
            tsolinfo->flags |= TSOL_AUDITEVENT;
            status = auditwrite(AW_EVENTNUM, xevent_num, AW_APPEND, AW_END);
	} else {
	    tsolinfo->flags &= ~TSOL_AUDITEVENT;
            tsolinfo->flags &= ~TSOL_DOXAUDIT;
	}
    }
}

CALLBACK(
TsolAuditEnd)
{
    XaceAuditRec *rec = (XaceAuditRec *) calldata;
    ClientPtr client = rec->client;
    int result = rec->requestResult;

    char audit_ret = (char)NULL;
    TsolInfoPtr tsolinfo = GetClientTsolInfo(client);

    if (tsolinfo->flags & TSOL_DOXAUDIT)
    {
                tsolinfo->flags &= ~TSOL_DOXAUDIT;
                if (tsolinfo->flags & TSOL_AUDITEVENT)
                    tsolinfo->flags &= ~TSOL_AUDITEVENT;
                if (result != Success)
                    audit_ret = -1;
                else
                    audit_ret = 0;
                auditwrite(AW_RETURN, audit_ret, (u_int)result,
                           AW_WRITE, AW_END);
    }
    else if (tsolinfo->flags & TSOL_AUDITEVENT)
    {
        tsolinfo->flags &= ~TSOL_AUDITEVENT;
        auditwrite(AW_DISCARDRD, -1, AW_END);
    }
}

int
ProcTsolQueryPointer(ClientPtr client)
{
    xQueryPointerReply rep;
    WindowPtr pWin, ptrWin;
    DeviceIntPtr mouse = PickPointer(client);
    DeviceIntPtr keyboard;
    SpritePtr pSprite;
    int rc;
    TsolResPtr tsolres;
    TsolInfoPtr tsolinfo = GetClientTsolInfo(client);
    xpolicy_t flags;

    REQUEST(xResourceReq);
    REQUEST_SIZE_MATCH(xResourceReq);

    rc = dixLookupWindow(&pWin, stuff->id, client, DixGetAttrAccess);
    if (rc != Success)
	return rc;
    rc = XaceHook(XACE_DEVICE_ACCESS, client, mouse, DixReadAccess);
    if (rc != Success && rc != BadAccess)
        return rc;

    keyboard = GetPairedDevice(mouse);

    pSprite = mouse->spriteInfo->sprite;

    ptrWin = GetSpriteWindow(mouse);
    tsolres = TsolResourcePrivate(ptrWin);
    flags = (TSOL_MAC|TSOL_DAC|TSOL_READOP);

    if (tsol_check_policy(tsolinfo, tsolres, flags, MAJOROP_CODE) == Success) {
    	return (*TsolSavedProcVector[X_QueryPointer])(client);
    }

    if (mouse->valuator->motionHintWindow)
	MaybeStopHint(mouse, client);
    memset(&rep, 0, sizeof(xQueryPointerReply));
    rep.type = X_Reply;
    rep.sequenceNumber = client->sequence;
    rep.mask = mouse->button ? (mouse->button->state) : 0;
    rep.mask |= XkbStateFieldFromRec(&keyboard->key->xkbInfo->state);
    rep.length = 0;
    rep.root = RootOf(pWin);
    rep.rootX = 0;
    rep.rootY = 0;
    rep.child = None;
    rep.sameScreen = xTrue;
    rep.winX = 0;
    rep.winY = 0;

    WriteReplyToClient(client, sizeof(xQueryPointerReply), &rep);

    return(Success);
}


int
ProcTsolQueryExtension(ClientPtr client)
{
    /* Allow extensions in the labeled zones */
    return ProcTsolUnwrapWithTrust(client, X_QueryExtension);
}

int
ProcTsolListExtensions(ClientPtr client)
{
    /* Allow extensions in the labeled zones */
    return ProcTsolUnwrapWithTrust(client, X_ListExtensions);
}

int
ProcTsolMapWindow(ClientPtr client)
{
    return ProcTsolUnwrapWithTrust(client, X_MapWindow);
}

int
ProcTsolMapSubwindows(ClientPtr client)
{
    return ProcTsolUnwrapWithTrust(client, X_MapSubwindows);
}

static int
TsolDoGetImage(
    ClientPtr	client,
    int format,
    Drawable drawable,
    int x, int y, int width, int height,
    Mask planemask,
    xGetImageReply **im_return)
{
    DrawablePtr 	pDraw;
    int			nlines, linesPerBuf, rc;
    register int	linesDone;
    long		widthBytesLine, length;
    Mask		plane = 0;
    char		*pBuf;
    xGetImageReply	xgi;

#ifdef TSOL
    Bool        getimage_ok = TRUE; /* if false get all 0s */
    Bool        overlap = FALSE;
    Bool        not_root_window = FALSE;
    WindowPtr   pHead = NULL, pWin = NULL, pRoot;
    TsolResPtr  tsolres_win;
    BoxRec      winbox, box;
    BoxPtr      pwinbox;
    DrawablePtr pDrawtmp;
    TsolResPtr tsolres;
    TsolInfoPtr tsolinfo = GetClientTsolInfo(client);
    xpolicy_t flags;
#endif /* TSOL */

    if ((format != XYPixmap) && (format != ZPixmap))
    {
	client->errorValue = format;
        return(BadValue);
    }
    rc = dixLookupDrawable(&pDraw, drawable, client, 0, DixReadAccess);
    if (rc != Success)
        return rc;


#ifdef TSOL
    flags = (TSOL_MAC|TSOL_DAC|TSOL_READOP);
    tsolres = TsolDrawablePrivate(pDraw, client);
    if (tsol_check_policy(tsolinfo, tsolres, flags, MAJOROP_CODE) == Success)
    {
	return DoGetImage(client, format, drawable, x, y,
		width, height, planemask, im_return);
    }

    if (pDraw->type == DRAWABLE_WINDOW)
    {
        if (DrawableIsRoot(pDraw))
        {
            pWin = XYToWindow(PickPointer(client), x, y);
            if (!WindowIsRoot(pWin))
            {
                pDrawtmp = &(pWin->parent->drawable);
                if (((WindowPtr) pDrawtmp)->realized)
                {
		    int tmpx, tmpy;

                    tmpx = x - pDrawtmp->x;
                    tmpy = y - pDrawtmp->y;

		    /* requested area must be a subset of the window area */
		    if (tmpx >= 0 && tmpy >= 0 &&
			width <= pDrawtmp->width &&
			height <= pDrawtmp->height)
		    {
                        pDraw = pDrawtmp;
			x = tmpx;
			y = tmpy;
                	not_root_window = TRUE;
		    }
                }
            }
        }
        else
        {
            not_root_window = TRUE;
        }

        if (not_root_window)
        {
            Window   root;
            WindowPtr tmpwin;
	    int	     rc;

            not_root_window = TRUE;
            rc = dixLookupWindow(&tmpwin, pDraw->id, client, DixReadAccess);
            if (rc != Success)
		return rc;

            while (tmpwin)
            {
                if (tmpwin->parent && WindowIsRoot(tmpwin->parent))
                {
                    pWin = tmpwin;
                    break;
                }
                tmpwin = tmpwin->parent;
            }
            pwinbox = WindowExtents(pWin, &winbox);
            box.x1 = pwinbox->x1;
            box.y1 = pwinbox->y1;
            box.x2 = pwinbox->x2;
            box.y2 = box.y1;
            tsolres_win = TsolResourcePrivate(pWin);
            root = WindowTable[pWin->drawable.pScreen->myNum]->drawable.id;
            rc = dixLookupWindow(&pRoot, root, client, DixReadAccess);
            if (rc != Success)
		return rc;
            pHead = pRoot->firstChild;
        }

    	tsolres = TsolDrawablePrivate(pDraw, client);
    	if (tsol_check_policy(tsolinfo, tsolres, flags, MAJOROP_CODE) == Success)
            getimage_ok = TRUE;
	else
            getimage_ok = FALSE;
    }
#endif /* TSOL */

    if(pDraw->type == DRAWABLE_WINDOW)
    {

      if( /* check for being viewable */
	 !((WindowPtr) pDraw)->realized ||
	  /* check for being on screen */
         pDraw->x + x < 0 ||
 	 pDraw->x + x + width > pDraw->pScreen->width ||
         pDraw->y + y < 0 ||
         pDraw->y + y + height > pDraw->pScreen->height ||
          /* check for being inside of border */
         x < - wBorderWidth((WindowPtr)pDraw) ||
         x + width > wBorderWidth((WindowPtr)pDraw) + (int)pDraw->width ||
         y < -wBorderWidth((WindowPtr)pDraw) ||
         y + height > wBorderWidth ((WindowPtr)pDraw) + (int)pDraw->height
        )
	    return(BadMatch);
	xgi.visual = wVisual (((WindowPtr) pDraw));
    }
    else
    {
      if(x < 0 ||
         x+width > (int)pDraw->width ||
         y < 0 ||
         y+height > (int)pDraw->height
        )
	    return(BadMatch);
	xgi.visual = None;
    }

    xgi.type = X_Reply;
    xgi.sequenceNumber = client->sequence;
    xgi.depth = pDraw->depth;
    if(format == ZPixmap)
    {
	widthBytesLine = PixmapBytePad(width, pDraw->depth);
	length = widthBytesLine * height;

    }
    else
    {
	widthBytesLine = BitmapBytePad(width);
	plane = ((Mask)1) << (pDraw->depth - 1);
	/* only planes asked for */
	length = widthBytesLine * height *
		 Ones(planemask & (plane | (plane - 1)));

    }

    xgi.length = length;

    if (im_return) {
	pBuf = (char *)xalloc(sz_xGetImageReply + length);
	if (!pBuf)
	    return (BadAlloc);
	if (widthBytesLine == 0)
	    linesPerBuf = 0;
	else
	    linesPerBuf = height;
	*im_return = (xGetImageReply *)pBuf;
	*(xGetImageReply *)pBuf = xgi;
	pBuf += sz_xGetImageReply;
    } else {
	xgi.length = (xgi.length + 3) >> 2;
	if (widthBytesLine == 0 || height == 0)
	    linesPerBuf = 0;
	else if (widthBytesLine >= IMAGE_BUFSIZE)
	    linesPerBuf = 1;
	else
	{
	    linesPerBuf = IMAGE_BUFSIZE / widthBytesLine;
	    if (linesPerBuf > height)
		linesPerBuf = height;
	}
	length = linesPerBuf * widthBytesLine;
	if (linesPerBuf < height)
	{
	    /* we have to make sure intermediate buffers don't need padding */
	    while ((linesPerBuf > 1) &&
		   (length & ((1L << LOG2_BYTES_PER_SCANLINE_PAD)-1)))
	    {
		linesPerBuf--;
		length -= widthBytesLine;
	    }
	    while (length & ((1L << LOG2_BYTES_PER_SCANLINE_PAD)-1))
	    {
		linesPerBuf++;
		length += widthBytesLine;
	    }
	}
	if(!(pBuf = (char *) xalloc(length)))
	    return (BadAlloc);
	WriteReplyToClient(client, sizeof (xGetImageReply), &xgi);
    }

    if (linesPerBuf == 0)
    {
	/* nothing to do */
    }
    else if (format == ZPixmap)
    {
        linesDone = 0;
        while (height - linesDone > 0)
        {
	    nlines = min(linesPerBuf, height - linesDone);
	    (*pDraw->pScreen->GetImage) (pDraw,
	                                 x,
				         y + linesDone,
				         width,
				         nlines,
				         format,
				         planemask,
				         (pointer) pBuf);
#ifdef TSOL
        if (not_root_window)
        {
            WindowPtr  over_win = (WindowPtr)NULL;

            box.y1 = y + linesDone + pDraw->y;
            box.y2 = box.y1 + nlines;
            over_win = AnyWindowOverlapsJustMe(pWin, pHead, &box);
            if (over_win)
	    {
		tsolres = TsolResourcePrivate(over_win);
    		if (tsol_check_policy(tsolinfo, tsolres, flags, MAJOROP_CODE) != Success) 
                	overlap = TRUE;
            }
        }

        /*
         * fill the buffer with zeros in case of security failure
         */
            if (!getimage_ok || overlap)
        {
            if (overlap)
                overlap = FALSE;
            memset(pBuf, 0, (int)(nlines * widthBytesLine));

        }
#endif /* TSOL */

	    /* Note that this is NOT a call to WriteSwappedDataToClient,
               as we do NOT byte swap */
	    if (!im_return)
	    {
/* Don't split me, gcc pukes when you do */
		(void)WriteToClient(client,
				    (int)(nlines * widthBytesLine),
				    pBuf);
	    }
	    linesDone += nlines;
        }
    }
    else /* XYPixmap */
    {
        for (; plane; plane >>= 1)
	{
	    if (planemask & plane)
	    {
	        linesDone = 0;
	        while (height - linesDone > 0)
	        {
		    nlines = min(linesPerBuf, height - linesDone);
	            (*pDraw->pScreen->GetImage) (pDraw,
	                                         x,
				                 y + linesDone,
				                 width,
				                 nlines,
				                 format,
				                 plane,
				                 (pointer)pBuf);
#ifdef TSOL
                if (not_root_window)
                {
                    WindowPtr  over_win = (WindowPtr)NULL;

                    box.y1 = y + linesDone + pDraw->y;
                    box.y2 = box.y1 + nlines;
                    over_win = AnyWindowOverlapsJustMe(pWin, pHead, &box);
		    if (over_win)
		    {
			tsolres = TsolResourcePrivate(over_win);
			if (tsol_check_policy(tsolinfo, tsolres, flags, MAJOROP_CODE) != Success) 
				overlap = TRUE;
		    }
                }
                /*
                 * fill the buffer with zeros in case of security failure
                 */
                if (!getimage_ok || overlap)
                {
                    if (overlap)
                        overlap = FALSE;
                    memset(pBuf, 0, (int)(nlines * widthBytesLine));

                }
#endif /* TSOL */

		    /* Note: NOT a call to WriteSwappedDataToClient,
		       as we do NOT byte swap */
		    if (im_return) {
			pBuf += nlines * widthBytesLine;
		    } else {
/* Don't split me, gcc pukes when you do */
			(void)WriteToClient(client,
					(int)(nlines * widthBytesLine),
					pBuf);
		    }
		    linesDone += nlines;
		}
            }
	}
    }

    if (!im_return)
	xfree(pBuf);
    return (client->noClientException);
}

int
ProcTsolGetImage(ClientPtr client)
{
    REQUEST(xGetImageReq);

    REQUEST_SIZE_MATCH(xGetImageReq);

    return TsolDoGetImage(client, stuff->format, stuff->drawable,
		      stuff->x, stuff->y,
		      (int)stuff->width, (int)stuff->height,
		      stuff->planeMask, (xGetImageReply **)NULL);
}

int
ProcTsolPolySegment(ClientPtr client)
{
    int status;
    GC *pGC;
    DrawablePtr pDraw;
    TsolResPtr tsolres;
    xpolicy_t flags;
    TsolInfoPtr tsolinfo = GetClientTsolInfo(client);

    REQUEST(xPolySegmentReq);
    REQUEST_AT_LEAST_SIZE(xPolySegmentReq);

    VALIDATE_DRAWABLE_AND_GC(stuff->drawable, pDraw, DixWriteAccess);

    flags = (TSOL_MAC|TSOL_DAC|TSOL_WRITEOP);
    tsolres = TsolDrawablePrivate(pDraw, client);
    if (tsol_check_policy(tsolinfo, tsolres, flags, MAJOROP_CODE) != Success) {
        /* ignore the error message */
        return(client->noClientException);
    }

    status = (*TsolSavedProcVector[X_PolySegment])(client);

    return (status);
}

int
ProcTsolPolyRectangle (ClientPtr client)
{
    int savedtrust;
    int status;
    GC *pGC;
    DrawablePtr pDraw;
    TsolResPtr tsolres;
    xpolicy_t flags;
    TsolInfoPtr tsolinfo = GetClientTsolInfo(client);

    REQUEST(xPolyRectangleReq);
    REQUEST_AT_LEAST_SIZE(xPolyRectangleReq);

    VALIDATE_DRAWABLE_AND_GC(stuff->drawable, pDraw, DixWriteAccess);

    flags = (TSOL_MAC|TSOL_DAC|TSOL_WRITEOP);
    tsolres = TsolDrawablePrivate(pDraw, client);
    if (tsol_check_policy(tsolinfo, tsolres, flags, MAJOROP_CODE) != Success) {
        /* ignore the error message */
        return(client->noClientException);
    }

    status = (*TsolSavedProcVector[X_PolyRectangle])(client);

    return (status);
}

int
ProcTsolCopyArea (ClientPtr client)
{
    int savedtrust;
    int status;
    DrawablePtr pDst;
    DrawablePtr pSrc;
    GC *pGC;
    int rc;
    TsolResPtr tsolres;
    xpolicy_t flags;
    TsolInfoPtr tsolinfo = GetClientTsolInfo(client);

    REQUEST(xCopyAreaReq);

    REQUEST_SIZE_MATCH(xCopyAreaReq);

    VALIDATE_DRAWABLE_AND_GC(stuff->dstDrawable, pDst, DixWriteAccess);

    if (stuff->dstDrawable != stuff->srcDrawable)
    {
        rc = dixLookupDrawable(&pSrc, stuff->srcDrawable, client, 0,
				 DixReadAccess);
	if (rc != Success)
	    return rc;
        if ((pDst->pScreen != pSrc->pScreen) || (pDst->depth != pSrc->depth))
        {
            client->errorValue = stuff->dstDrawable;
            return (BadMatch);
        }
    }
    else
        pSrc = pDst;

    flags = (TSOL_MAC|TSOL_DAC|TSOL_READOP);
    tsolres = TsolDrawablePrivate(pSrc, client);
    if (tsol_check_policy(tsolinfo, tsolres, flags, MAJOROP_CODE) != Success) {
        /* ignore the error message for DnD zap effect */
        return(client->noClientException);
    }

    flags = (TSOL_MAC|TSOL_DAC|TSOL_WRITEOP);
    tsolres = TsolDrawablePrivate(pDst, client);
    if (tsol_check_policy(tsolinfo, tsolres, flags, MAJOROP_CODE) != Success) {
        /* ignore the error message for DnD zap effect */
        return(client->noClientException);
    }

    status = (*TsolSavedProcVector[X_CopyArea])(client);

    return (status);
}

int
ProcTsolCopyPlane(ClientPtr client)
{
    int savedtrust;
    int status;
    DrawablePtr psrcDraw, pdstDraw;
    GC *pGC;
    TsolResPtr tsolres;
    TsolInfoPtr tsolinfo = GetClientTsolInfo(client);
    xpolicy_t flags;
    int rc;

    REQUEST(xCopyPlaneReq);

    REQUEST_SIZE_MATCH(xCopyPlaneReq);

    savedtrust = setClientTrustLevel(client, XSecurityClientTrusted);

    VALIDATE_DRAWABLE_AND_GC(stuff->dstDrawable, pdstDraw,  DixWriteAccess);

    if (stuff->dstDrawable != stuff->srcDrawable)
    {
	rc = dixLookupDrawable(&psrcDraw, stuff->srcDrawable, client, 0,
			       DixReadAccess);
	if (rc != Success)
	    return rc;

	if (pdstDraw->pScreen != psrcDraw->pScreen)
	{
	    client->errorValue = stuff->dstDrawable;
	    return (BadMatch);
	}
    }
    else
        psrcDraw = pdstDraw;

    flags = (TSOL_MAC|TSOL_DAC|TSOL_READOP);
    tsolres = TsolDrawablePrivate(psrcDraw, client);
    if (tsol_check_policy(tsolinfo, tsolres, flags, MAJOROP_CODE) != Success) {
        /* ignore the error message for DnD zap effect */
        return(client->noClientException);
    }

    flags = (TSOL_MAC|TSOL_DAC|TSOL_WRITEOP);
    tsolres = TsolDrawablePrivate(pdstDraw, client);
    if (tsol_check_policy(tsolinfo, tsolres, flags, MAJOROP_CODE) != Success) {
        /* ignore the error message for DnD zap effect */
        return(client->noClientException);
    }

    status = (*TsolSavedProcVector[X_CopyPlane])(client);

    return (status);
}
