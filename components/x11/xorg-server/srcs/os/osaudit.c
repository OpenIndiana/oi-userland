/*
 * Copyright (c) 2011, 2012, Oracle and/or its affiliates. All rights reserved.
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

#define XSERV_t
#define TRANS_SERVER
#include <X11/Xtrans/Xtrans.h>
#include <X11/Xtrans/Xtransint.h>

#include "misc.h"
#include "osdep.h"
#include "dixstruct.h"

static DevPrivateKeyRec OSAuditPrivKeyRec;
#define OSAuditPrivKey (&OSAuditPrivKeyRec)

#define GetOSAuditClient(pClient)    \
  ((OSAuditClientPrivatePtr) dixLookupPrivate(&(pClient)->devPrivates, OSAuditPrivKey))

#ifdef HAVE_LIBBSM	/* Solaris auditing implementation */
#include <ucred.h>
#include <bsm/adt.h>
#include <bsm/adt_event.h>

#ifdef ADT_xconnect
# define OS_AUDIT_IMPLEMENTED

typedef struct {
    adt_session_data_t	*ah;		/* audit handle */
    ClientState		 prevState;
} OSAuditClientPrivateRec, *OSAuditClientPrivatePtr;

static void
OSAuditClientInit (ClientPtr pClient)
{
    adt_session_data_t	*ah;		/* audit handle */
    ucred_t		*uc = NULL;	/* peer's ucred */
    XtransConnInfo	 ci;		/* peer's connection info */
    int			 peer;		/* peer's file descriptor */
    int			 saveid;

    OSAuditClientPrivatePtr	 priv = GetOSAuditClient(pClient);

    saveid = geteuid();
    if (saveid != 0) {
	/* reset privs back to root */
        if (seteuid(0) < 0) {
	    ErrorF("OSAuditClientInit: seteuid(0): %s\n", strerror(errno));
	    saveid = 0;
	}
    }
    
    if (adt_start_session(&ah, NULL, 0) != 0) {
	ErrorF("OSAuditClientInit: adt_start_session: %s\n", strerror(errno));
	goto end;
    }

    if (pClient->osPrivate == NULL) {
	ErrorF("OSAuditClientInit: NULL osPrivate: %s\n", strerror(errno));
	goto end;
    }
    ci = ((OsCommPtr)pClient->osPrivate)->trans_conn;
    peer = _XSERVTransGetConnectionNumber(ci);
    if (getpeerucred(peer, &uc) == 0) {
	if (adt_set_from_ucred(ah, uc, ADT_NEW) != 0) {
	    ErrorF("OSAuditClientInit: adt_set_from_ucred: %s\n",
		   strerror(errno));
	}
	ucred_free(uc);
    } else {
	if (adt_set_user(ah, ADT_NO_ATTRIB, ADT_NO_ATTRIB, ADT_NO_ATTRIB,
			 ADT_NO_ATTRIB, NULL, ADT_NEW) != 0) {
	    ErrorF("OSAuditClientInit: adt_set_user: %s\n", strerror(errno));
	}
    }

    priv->ah = ah;

  end:
    if (saveid != 0) {
	/* set privs back to user */
        if (seteuid(saveid) < 0) {
	    ErrorF("OSAuditClientInit: seteuid(saveid): %s\n", strerror(errno));
	}
    }

}

static void
OSAudit (ClientPtr pClient, int event_id, int status, int reason)
{
    adt_event_data_t	*event;		/* event handle */
    XtransConnInfo	 ci;		/* peer's connection info */
    int			 peer;		/* peer's file descriptor */
    int			 saveid;

    OSAuditClientPrivatePtr	 priv = GetOSAuditClient(pClient);

    if (priv->ah == NULL) {
	ErrorF("OSAudit: NULL adt_session_data: %s\n", strerror(errno));
	return;
    }

    if ((event = adt_alloc_event(priv->ah, event_id)) == NULL) {
	ErrorF("OSAudit: adt_set_from_ucred: %s\n", strerror(errno));
	return;
    }

    /* fill in event */
    switch (event_id) {
    case ADT_xconnect:
	if (pClient->osPrivate != NULL) {
	    ci = ((OsCommPtr)pClient->osPrivate)->trans_conn;
	    peer = _XSERVTransGetConnectionNumber(ci);
	} else {
	    peer = -1;
	}
	event->adt_xconnect.client = pClient->index;
	event->adt_xconnect.peer = peer;
	break;
    case ADT_xdisconnect:
	event->adt_xdisconnect.client = pClient->index;
	break;
    default:
	ErrorF("OSAudit: unknown event_id: %s\n", strerror(errno));
    }

    saveid = geteuid();
    if (saveid != 0) {
	/* reset privs back to root */
        if (seteuid(0) < 0) {
	    ErrorF("OSAuditClientInit: seteuid(0): %s\n", strerror(errno));
	    saveid = 0;
	}
    }
    
    if (adt_put_event(event, status, reason) != 0) {
	ErrorF("OSAudit: adt_put_event: %s\n", strerror(errno));
    }

    if (saveid != 0) {
	/* set privs back to user */
        if (seteuid(saveid) < 0) {
	    ErrorF("OSAuditClientInit: seteuid(saveid): %s\n", strerror(errno));
	}
    }    
    
    adt_free_event(event);
}

/* Called when new client connects or existing client disconnects */
static void
OSAuditClientStateChange(CallbackListPtr *pcbl, pointer nulldata, pointer calldata)
{
    NewClientInfoRec *pci = (NewClientInfoRec *)calldata;
    ClientPtr pClient = pci->client;
    OSAuditClientPrivatePtr	 priv = GetOSAuditClient(pClient);

    switch (pClient->clientState) {

    case ClientStateInitial:  /* client attempting to connect */
	OSAuditClientInit(pClient);
	break;

    case ClientStateRunning:  /* connection accepted */
	OSAudit (pClient, ADT_xconnect, ADT_SUCCESS, ADT_SUCCESS);
	break;

    case ClientStateGone:     /* connection terminating */
	if (priv->prevState == ClientStateInitial) /* was never accepted */
	    OSAudit (pClient, ADT_xconnect, ADT_FAILURE, EACCES);
	else	/* successful connection that ran for a while */
	    OSAudit (pClient, ADT_xdisconnect, ADT_SUCCESS, ADT_SUCCESS);
	adt_end_session(priv->ah);
	priv->ah = NULL;
	break;

    default:
	return; /* skip over setting prevState to an unknown state */
    }

    priv->prevState = pClient->clientState;
}
#endif /* ADT_xconnect */
#endif /* HAVE_LIBBSM -- Solaris auditing implementation */

/* Generic code to initialize all OS auditing implementations */
void
OSAuditInit(void)
{
#ifdef OS_AUDIT_IMPLEMENTED
    /* Reserve room in the client privates for the audit data */
    if (!dixRegisterPrivateKey(&OSAuditPrivKeyRec, PRIVATE_CLIENT,
			       sizeof(OSAuditClientPrivateRec)))
	FatalError("could not allocate OSAuditPrivKey\n");

    /* Register callback to be called on every client connect & disconnect */
    if (!AddCallback(&ClientStateCallback, OSAuditClientStateChange, NULL))
	FatalError("could not register OSAuditClientStateChange callback\n");
#else
/* nothing implemented for this OS */
    return;
#endif
}
