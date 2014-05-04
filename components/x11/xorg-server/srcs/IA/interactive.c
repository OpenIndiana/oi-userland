/*
 * Copyright (c) 1993, 2010, Oracle and/or its affiliates. All rights reserved.
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


/************************************************************
	Basic boilerplate extension.

	This file also contains the code to make the priocntl on behalf
	of the clients.

	Note that ChangePriority also sets the last client with focus
	to the normal priority.

	If there are knobs to be added to the system, for say the nice
	values for the IA class, they would be added here.
********************************************************/

/* THIS IS NOT AN X CONSORTIUM STANDARD */

#ifdef HAVE_DIX_CONFIG_H
#include <dix-config.h>
#endif

#include <errno.h>
#include <sys/types.h>
#include <stdio.h>

#include <sys/priocntl.h>
#include <sys/iapriocntl.h>
#include <unistd.h>


#define NEED_REPLIES
#define NEED_EVENTS
#include <X11/X.h>
#include <X11/Xproto.h>
#include "os.h"
#include "dixstruct.h"
#include "windowstr.h"
#include "inputstr.h"
#include "extnsionst.h"
#define _XIA_SERVER_
#include <X11/extensions/interactive.h>
#include <X11/Xfuncproto.h>
#include "dix.h"

#include "interactive_srv.h"

static int ProcIADispatch(ClientPtr client), SProcIADispatch(ClientPtr client);
static int ProcIASetProcessInfo(ClientPtr client), SProcIASetProcessInfo(ClientPtr client);
static int ProcIAGetProcessInfo(ClientPtr client), SProcIAGetProcessInfo(ClientPtr client);
static int ProcIAQueryVersion(ClientPtr client), SProcIAQueryVersion(ClientPtr client);
static void IACloseDown(ExtensionEntry *ext);
static void IAClientStateChange(CallbackListPtr *pcbl, pointer nulldata, pointer calldata);

static int InitializeClass(void );
static void SetIAPrivate(int*);
static void ChangeInteractive(ClientPtr);
static int SetPriority(const ClientProcessPtr, int);
static void ChangePriority(register ClientPtr client);

static int SetClientPrivate(ClientPtr client, ConnectionPidPtr stuff, int length);
static void FreeProcessList(IAClientPrivatePtr priv);
/* static int LocalConnection(OsCommPtr); */
static int PidSetEqual(ClientProcessPtr, ClientProcessPtr);

static int IAWrapProcVectors(void);
static int IAUnwrapProcVectors(void);

static CARD32 IAInitTimerCall(OsTimerPtr timer,CARD32 now,pointer arg);

static iaclass_t 	IAClass;
static id_t		TScid;
static ClientProcessPtr	LastPids = NULL;
static int 		ia_nice = IA_BOOST;
static Bool 		InteractiveOS = TRUE;
static unsigned long 	IAExtensionGeneration = 0;
static OsTimerPtr 	IAInitTimer = NULL;
static int (* IASavedProcVector[256]) (ClientPtr client);

static int IAPrivKeyIndex;
static DevPrivateKey IAPrivKey = &IAPrivKeyIndex;

#define GetIAClient(pClient)	\
    ((IAClientPrivatePtr) dixLookupPrivate(&(pClient)->devPrivates, IAPrivKey))

static inline ClientProcessPtr
GetConnectionPids(ClientPtr pClient)
{
    IAClientPrivatePtr priv = GetIAClient(pClient);

    if (priv == NULL) {
	return NULL;
    } else {
	return priv->process;
    }
}

/* Set via xorg.conf option in loadable module */
int IADebugLevel = 0;

#define IA_DEBUG(level, func)	\
	if (IADebugLevel >= level) { func; } else (void)(0)

#define IA_DEBUG_BASIC		1
#define IA_DEBUG_PRIOCNTL	3

void
IAExtensionInit(void)
{
    ConnectionPidRec	myPid = P_MYID;
    ClientProcessRec	myProc = { 1, &myPid, FALSE };

    IA_DEBUG(IA_DEBUG_BASIC,
	     LogMessage(X_INFO, "SolarisIA: Initializing (generation %ld)\n",
			IAExtensionGeneration));

    if (IAExtensionGeneration == serverGeneration)
	return;

    InteractiveOS = FALSE;

    if (InitializeClass() != Success)
	return;

    if (SetPriority(&myProc, SET_INTERACTIVE) != Success)
	return;

    if (SetPriority(&myProc, SET_PRIORITY) != Success)
	return;

    if (!AddCallback(&ClientStateCallback, IAClientStateChange, NULL))
        return;

    if (IAWrapProcVectors() != 0)
	return;

    if (!AddExtension(IANAME, IANumberEvents, IANumberErrors,
		      ProcIADispatch, SProcIADispatch,
		      IACloseDown, StandardMinorOpcode))
	return;

    /* InitExtensions is called before InitClientPrivates(serverClient)
       so we set this timer to callback as soon as we hit WaitForSomething
       to initialize the serverClient */
    IAInitTimer = TimerSet(IAInitTimer, 0, 1, IAInitTimerCall, NULL);

    InteractiveOS = TRUE;
    IAExtensionGeneration = serverGeneration;

    IA_DEBUG(IA_DEBUG_BASIC,
	     LogMessage(X_INFO,
			"SolarisIA: Finished initializing (generation %ld)\n",
			IAExtensionGeneration));
}

/* Allocate client private structure for this client */
static int
IAInitClientPrivate(ClientPtr pClient)
{
    IAClientPrivatePtr priv;

    priv = GetIAClient(pClient);
    if (priv != NULL) {
	return Success;
    }

    priv = xalloc(sizeof(IAClientPrivateRec));
    if (priv == NULL) {
	return BadAlloc;
    }

    priv->process = NULL;
    priv->wmgr = FALSE;

    dixSetPrivate(&(pClient)->devPrivates, IAPrivKey, priv);

    return Success;
}

/* Called when we first hit WaitForSomething to initialize serverClient */
static CARD32
IAInitTimerCall(OsTimerPtr timer,CARD32 now,pointer arg)
{
    ConnectionPidRec serverPid;

    if (InteractiveOS != TRUE)
	return 0;

    IAInitClientPrivate(serverClient);

    serverPid = getpid();
    SetClientPrivate(serverClient, &serverPid, 1);

    ChangePriority(serverClient);
    return 0;
}

/* Called when new client connects or existing client disconnects */
static void
IAClientStateChange(CallbackListPtr *pcbl, pointer nulldata, pointer calldata)
{
    NewClientInfoRec *pci = (NewClientInfoRec *)calldata;
    ClientPtr pClient = pci->client;
    ClientProcessPtr CurrentPids;
    IAClientPrivatePtr priv;
    LocalClientCredRec *lcc;

    switch (pClient->clientState) {
      case ClientStateGone:
      case ClientStateRetained:
	priv = GetIAClient(pClient);
	if (priv == NULL) {
	    return;
	}
	CurrentPids = priv->process;

	if (priv->wmgr) {
	    IA_DEBUG(IA_DEBUG_BASIC,
		     LogMessage(X_INFO,
				"SolarisIA: WindowManager closed (pid %d)\n",
				(CurrentPids && CurrentPids->pids) ?
				 CurrentPids->pids[0] : -1));
	}

	if (CurrentPids && CurrentPids->boosted) {
	    SetPriority(CurrentPids, UNSET_PRIORITY);
	}

	if (CurrentPids && LastPids && PidSetEqual(CurrentPids, LastPids)) {
	    LastPids = NULL;
	}

	FreeProcessList(priv);
	xfree(priv);
	dixSetPrivate(&(pClient)->devPrivates, IAPrivKey, NULL);
	break;

    case ClientStateInitial:
	IAInitClientPrivate(pClient);
	if (GetLocalClientCreds(pClient, &lcc) != -1) {
	    if (lcc->fieldsSet & LCC_PID_SET) {
		ConnectionPidRec clientPid = lcc->pid;
		SetClientPrivate(pClient, &clientPid, 1);
		ChangeInteractive(pClient);
	    }
	    FreeLocalClientCreds(lcc);
	}
	break;

    default:
	break;
    }
}


static int
ProcIADispatch (ClientPtr client)
{
    REQUEST(xReq);
    switch (stuff->data)
    {
    case X_IAQueryVersion:
	return ProcIAQueryVersion(client);
    case X_IASetProcessInfo:
	return ProcIASetProcessInfo(client);
    case X_IAGetProcessInfo:
	return ProcIAGetProcessInfo(client);
    default:
	return BadRequest;
    }
}

static int
ProcIAQueryVersion(ClientPtr client)
{
    REQUEST(xIAQueryVersionReq);
    xIAQueryVersionReply rep;

    REQUEST_SIZE_MATCH(xIAQueryVersionReq);
    rep.type = X_Reply;
    rep.length = 0;
    rep.sequenceNumber = client->sequence;
    rep.majorVersion = IA_MAJOR_VERSION;
    rep.minorVersion = IA_MINOR_VERSION;
    WriteToClient(client, sizeof(xIAQueryVersionReply), (char *)&rep);
    return (client->noClientException);
}

static int
ProcIASetProcessInfo(ClientPtr client)
{

    REQUEST(xIASetProcessInfoReq);
    register int length;
    static uid_t ServerUid = (uid_t)-1;

    REQUEST_AT_LEAST_SIZE(xIASetProcessInfoReq);

    if (ServerUid == (uid_t)-1)
	ServerUid=getuid();

    if ((stuff->flags & INTERACTIVE_INFO) &&
	(stuff->uid==ServerUid || ServerUid==0 || stuff->uid==0) &&
	LocalClient(client)) {
	length = stuff->length - (sizeof(xIASetProcessInfoReq)>>2);
	SetClientPrivate(client, (ConnectionPidPtr)&stuff[1], length);
	ChangeInteractive(client);
    }

    if ((stuff->flags & INTERACTIVE_SETTING) &&
	(stuff->uid==ServerUid || ServerUid==0) &&
	LocalClient(client)) {
	SetIAPrivate((int*)&stuff[1]);
    }

    return (client->noClientException);
}

static int
ProcIAGetProcessInfo(ClientPtr client)
{
    IAClientPrivatePtr	priv;
    ClientProcessPtr CurrentPids;
    REQUEST(xIAGetProcessInfoReq);
    xIAGetProcessInfoReply rep;
    register int length = 0;
    caddr_t write_back = NULL;

    REQUEST_SIZE_MATCH(xIAGetProcessInfoReq);
    rep.type = X_Reply;
    rep.length = 0;
    rep.sequenceNumber = client->sequence;
    if (stuff->flags & INTERACTIVE_INFO) {
	priv = GetIAClient(client);
	if ( (priv == NULL) || (priv->process == NULL) ) {
	    rep.count = 0;
	} else {
    	    CurrentPids = priv->process;
	    rep.count = CurrentPids->count;
	    length = rep.count << 2;
	    write_back=(caddr_t)CurrentPids->pids;
	}
    }
    if (stuff->flags & INTERACTIVE_SETTING) {
	rep.count=1;
	length=rep.count << 2;
	write_back=(caddr_t)&ia_nice;
    }

    WriteToClient(client, sizeof(xIAGetProcessInfoReply), (char *)&rep);
    WriteToClient(client, length, write_back);
    return (client->noClientException);
}

static void
IACloseDown(ExtensionEntry *ext)
{
    InteractiveOS = FALSE;

    IAUnwrapProcVectors();

    DeleteCallback(&ClientStateCallback, IAClientStateChange, NULL);
}

/*
   The SProc* functions are here for completeness. They should never get
   called. But since they do the server has to eat the request and
   return thanks for sharing.
*/

/*ARGSUSED*/
static int
SProcIADispatch (ClientPtr client)
{
    REQUEST(xReq);
    switch (stuff->data)
    {
    case X_IAQueryVersion:
	return SProcIAQueryVersion(client);
    case X_IASetProcessInfo:
	return SProcIASetProcessInfo(client);
    case X_IAGetProcessInfo:
	return SProcIAGetProcessInfo(client);
    default:
	return BadRequest;
    }
}

/*ARGSUSED*/
static int
SProcIAQueryVersion(ClientPtr client)
{
    REQUEST_SIZE_MATCH(xIAQueryVersionReq);
    return (client->noClientException);
}

/*ARGSUSED*/
static int
SProcIASetProcessInfo(ClientPtr client)
{
    REQUEST(xIASetProcessInfoReq);
    REQUEST_AT_LEAST_SIZE(xIASetProcessInfoReq);

    return (client->noClientException);
}

/*ARGSUSED*/
static int
SProcIAGetProcessInfo(ClientPtr client)
{
    REQUEST(xIAGetProcessInfoReq);
    REQUEST_SIZE_MATCH(xIAGetProcessInfoReq);

    return (client->noClientException);
}

static void
ChangeInteractive(ClientPtr client)
{
    ClientProcessPtr CurrentPids = GetConnectionPids(client);

    if (InteractiveOS==FALSE)
        return;

    if (!CurrentPids || !CurrentPids->pids)
	return;

    SetPriority(CurrentPids, SET_INTERACTIVE);
}

/*
 * Loop through pids associated with client. Magically make last focus
 * group go non-interactive -IA_BOOST.
 */
static void
ChangePriority(register ClientPtr client)
{
    IAClientPrivatePtr priv = GetIAClient(client);
    ClientProcessPtr CurrentPids = (priv == NULL ? NULL : priv->process);

    if (CurrentPids && LastPids && PidSetEqual(CurrentPids, LastPids)) {
	/* Shortcut. Focus changed between two windows with same pid */
	return;
    }

    /* Remove priority boost for last focus group */
    if (LastPids) {
	SetPriority(LastPids, UNSET_PRIORITY);
	LastPids = NULL;
    }

    /* If no pid info for current client, then we're done here.
     * This can happen if we have a remote client with focus or if the client
     * is statically linked or if it is using a down rev version of libX11.
     */
    if ( (CurrentPids == NULL) || (CurrentPids->count == 0) ||
	 (CurrentPids->pids == NULL) ) {
	return;
    }

    /* Set the priority boost if it isn't already active */
    if (!CurrentPids->boosted) {
	SetPriority(CurrentPids, SET_PRIORITY);
    }

    /* Make sure server or wmgr isn't unset by testing for them, so
     * that LastPids is never set to point to the server or wmgr pid.
     */
    if ((client->index != serverClient->index) && (priv->wmgr != TRUE)) {
	LastPids = CurrentPids;
    }
}

static int
InitializeClass(void)
{
    pcinfo_t  pcinfo;

    /* Get TS class information */
    strcpy (pcinfo.pc_clname, "TS");
    priocntl(0, 0, PC_GETCID, (caddr_t)&pcinfo);
    TScid = pcinfo.pc_cid;

    /* Get IA class information */
    strcpy (pcinfo.pc_clname, "IA");
    if ((priocntl(0, 0, PC_GETCID, (caddr_t)&pcinfo)) == -1)
        return ~Success;

    IAClass.pc_cid = pcinfo.pc_cid;
    ((iaparms_t*)IAClass.pc_clparms)->ia_uprilim = IA_NOCHANGE;
    ((iaparms_t*)IAClass.pc_clparms)->ia_upri = IA_NOCHANGE;

    return Success;
}

static int
SetPriority(const ClientProcessPtr cpp, int cmd)
{
    pcparms_t 	pcinfo;
    long	ret = Success;
    gid_t	usr_egid = getegid();
    int		i;

    if ( (cpp == NULL) || (cpp->pids == NULL) || (cpp->count == 0) ) {
	return Success;
    }

    if ( setegid(0) < 0 ) {
	Error("Error in setting egid to 0");
    }

    for (i = 0; i < cpp->count ; i++) {
	id_t	pid = cpp->pids[i];

	pcinfo.pc_cid=PC_CLNULL;
	if ((priocntl(P_PID, pid, PC_GETPARMS, (caddr_t)&pcinfo)) < 0) {
	    if ( setegid(usr_egid) < 0 ) {
		Error("Error in resetting egid");
	    }
	    return ~Success; /* Scary time; punt */
	}

	/* If process is in TS or IA class we can safely set parameters */
	if ((pcinfo.pc_cid == IAClass.pc_cid) || (pcinfo.pc_cid == TScid)) {

	    switch (cmd) {
	      case UNSET_PRIORITY:
   		((iaparms_t*)IAClass.pc_clparms)->ia_mode=IA_INTERACTIVE_OFF;
		break;
	      case SET_PRIORITY:
   		((iaparms_t*)IAClass.pc_clparms)->ia_mode=IA_SET_INTERACTIVE;
		break;
	      case SET_INTERACTIVE:
		/* If this returns true, the process is already in the 	*/
		/* IA class, so we don't need to update it.		*/
		if ( pcinfo.pc_cid == IAClass.pc_cid)
		    continue;

   		((iaparms_t*)IAClass.pc_clparms)->ia_mode=IA_INTERACTIVE_OFF;
		break;
	    }

	    if (priocntl(P_PID, pid, PC_SETPARMS, (caddr_t)&IAClass) == -1)
	    {
		ret = ~Success;
	    }

	    IA_DEBUG(IA_DEBUG_PRIOCNTL,
	    {
		const char *cmdmsg;

		switch (cmd) {
		  case UNSET_PRIORITY:	cmdmsg = "UNSET_PRIORITY";	break;
		  case SET_PRIORITY:	cmdmsg = "SET_PRIORITY"; 	break;
		  case SET_INTERACTIVE:	cmdmsg = "SET_INTERACTIVE"; 	break;
		  default:		cmdmsg = "UNKNOWN_CMD!!!"; 	break;
		}
		LogMessage(X_INFO, "SolarisIA: SetPriority(%ld, %s): %s\n",
			   pid, cmdmsg,
			   (ret == Success) ? "succeeeded" : "failed");
	    });
	}
    }

    if (setegid(usr_egid) < 0)
	Error("Error in resetting egid");

    if (ret == Success) {
	if (cmd == SET_PRIORITY) {
	    cpp->boosted = TRUE;
	} else if (cmd == UNSET_PRIORITY) {
	    cpp->boosted = FALSE;
	}
    }

    return ret;
}

static void
SetIAPrivate(int * value)
{
    ia_nice = *value;
}

/*****************************************************************************
 * Various utility functions - in Xsun these lived in Xserver/os/process.c
 */

/* In Xsun we used the osPrivate in OsCommPtr, so this was SetOsPrivate. */
static int
SetClientPrivate(ClientPtr client, ConnectionPidPtr stuff, int length)
{
    ClientProcessPtr	cpp;
    IAClientPrivatePtr priv;

    priv = GetIAClient(client);
    if (priv == NULL) {
	IAInitClientPrivate(client);
    } else {
	FreeProcessList(priv);
    }

    cpp = (ClientProcessPtr)xalloc(sizeof(ClientProcessRec));

    if (cpp == NULL)
	return BadAlloc;

    cpp->pids = (ConnectionPidPtr)xalloc(sizeof(ConnectionPidRec)*length);

    if (cpp->pids == NULL) {
	xfree(cpp);
	return BadAlloc;
    }

    cpp->count = length;
    memcpy(cpp->pids, stuff, sizeof(ConnectionPidRec)*length);
    cpp->boosted = FALSE;

    priv->process = cpp;
    return Success;
}

static void
FreeProcessList(IAClientPrivatePtr priv)
{
    ClientProcessPtr	cpp = priv->process;

    if (cpp == NULL)
	return;
    priv->process = NULL;

    if ( LastPids == cpp )
	LastPids = NULL;

    if (cpp->pids != NULL)
	xfree(cpp->pids);

    xfree(cpp);
}

/*
  Check to see that all in current (a) are in last (b).
  And that a and b have the same number of members in the set.
*/
static int
PidSetEqual(ClientProcessPtr a, ClientProcessPtr b)
{
    int aN, bN;
    int count = a->count;
    int retval = 1;

    if (a->count != b->count) {
	return 0; /* definately NOT the same set */
    }

    for (aN = 0; aN < count; aN++) {
	retval = 0;
	for (bN = 0; bN < count ; bN++) {
	    if (a->pids[aN] == b->pids[bN]) {
		retval = 1;
		break;
	    }
	}
	if (retval == 0)
	    return retval;
    }

    return retval;
}


/*****************************************************************************
 * Wrappers for normal procs - in Xsun we modified the original procs directly
 * in dix, but here we wrap them for a small performance loss but a large
 * increase in maintainability and ease of porting to new releases.
 */

static int
IAProcSetInputFocus(ClientPtr client)
{
    int res;
    Window focusID;
    WindowPtr focusWin;
    REQUEST(xSetInputFocusReq);

    res = (*IASavedProcVector[X_SetInputFocus])(client);
    if ((res != Success) || (InteractiveOS != TRUE))
	return res;

    focusID = stuff->focus;

    switch (focusID) {
      case None:
	focusWin = NullWindow;
	break;
      case PointerRoot:
	focusWin = PointerRootWin;
	break;
      default:
	res = dixLookupWindow(&focusWin, focusID, client, DixReadAccess);
	if (res != Success)
	    return res;
    }

    if ((focusWin != NullWindow) && (focusWin != PointerRootWin)) {
	register ClientPtr requestee = wClient(focusWin);
	ChangePriority(requestee);
    }

    return res;
}

static int
IAProcSendEvent(ClientPtr client)
{
    int res;
    REQUEST(xSendEventReq);

    res = (*IASavedProcVector[X_SendEvent])(client);
    if ((res != Success) || (InteractiveOS != TRUE))
	return res;

    if ((InteractiveOS==TRUE) &&
        (GetIAClient(client)->wmgr == TRUE) &&
        (stuff->event.u.u.type == ClientMessage) &&
        (stuff->event.u.u.detail == 32) ) {

        register ClientPtr requestee;
	WindowPtr pWin = NULL;
	DeviceIntPtr pPtr = PickPointer(client);

	if (stuff->destination == PointerWindow)
	    pWin = GetSpriteWindow(pPtr);
	else if (stuff->destination == InputFocus)
	{
	    WindowPtr inputFocus = inputInfo.keyboard->focus->win;

	    if (inputFocus == NoneWin)
		return Success;

	 /* If the input focus is PointerRootWin, send the event to where
	    the pointer is if possible, then perhaps propogate up to root. */
	    if (inputFocus == PointerRootWin)
		inputFocus = GetCurrentRootWindow(pPtr);

	    if (IsParent(inputFocus, GetSpriteWindow(pPtr)))
		pWin = GetSpriteWindow(pPtr);
	    else
		pWin = inputFocus;
	}
	else
	{
	    res = dixLookupWindow(&pWin, stuff->destination, client,
				  DixReadAccess);
	    if (res != Success)
		return res;
	}


	if (!pWin)
	    return BadWindow;

        requestee = wClient(pWin);
	ChangePriority(requestee);
    }
    return res;
}

static Bool
IAProcChangeWindowAttributes(ClientPtr client)
{
    REQUEST(xChangeWindowAttributesReq);

    if ((InteractiveOS==TRUE) && (stuff->valueMask & CWEventMask) &&
	(GetIAClient(client)->wmgr == FALSE) ) {

	register XID *pVlist = (XID *) &stuff[1];
	register Mask tmask = stuff->valueMask;
	register Mask index2 = 0;

	while (tmask) {
	    index2 = (Mask) lowbit (tmask);
	    tmask &= ~index2;
	    if (index2 == CWEventMask) {
		break;
	    }
	    pVlist++;
	}

	if ((index2 == CWEventMask) && (*pVlist & SubstructureRedirectMask)) {
	    IA_DEBUG(IA_DEBUG_BASIC,
		     ClientProcessPtr CurrentPids=GetConnectionPids(client);

		     LogMessage(X_INFO,
				"SolarisIA: WindowManager detected (pid %d)\n",
				(CurrentPids && CurrentPids->pids) ?
				 CurrentPids->pids[0] : -1));

	    GetIAClient(client)->wmgr = TRUE;
	    ChangePriority(client);
	    LastPids = NULL;
	}
    }

    return (*IASavedProcVector[X_ChangeWindowAttributes])(client);
}


static int
IAWrapProcVectors(void)
{
    IASavedProcVector[X_SetInputFocus] = ProcVector[X_SetInputFocus];
    ProcVector[X_SetInputFocus] = IAProcSetInputFocus;

    IASavedProcVector[X_SendEvent] = ProcVector[X_SendEvent];
    ProcVector[X_SendEvent] = IAProcSendEvent;

    IASavedProcVector[X_ChangeWindowAttributes]
      = ProcVector[X_ChangeWindowAttributes];
    ProcVector[X_ChangeWindowAttributes] = IAProcChangeWindowAttributes;

    return 0;
}

static int
IAUnwrapProcVectors(void)
{
    ProcVector[X_SetInputFocus] = IASavedProcVector[X_SetInputFocus];
    ProcVector[X_SendEvent] = IASavedProcVector[X_SendEvent];
    ProcVector[X_ChangeWindowAttributes] = IASavedProcVector[X_ChangeWindowAttributes];

    return 0;
}


