/*
 * CDDL HEADER START
 *
 * The contents of this file are subject to the terms of the
 * Common Development and Distribution License (the "License").
 * You may not use this file except in compliance with the License.
 *
 * You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
 * or http://www.opensolaris.org/os/licensing.
 * See the License for the specific language governing permissions
 * and limitations under the License.
 *
 * When distributing Covered Code, include this CDDL HEADER in each
 * file and include the License file at usr/src/OPENSOLARIS.LICENSE.
 * If applicable, add the following below this CDDL HEADER, with the
 * fields enclosed by brackets "[]" replaced with your own identifying
 * information: Portions Copyright [yyyy] [name of copyright owner]
 *
 * CDDL HEADER END
 */

/*
 * Copyright (c) 2016, Oracle and/or its affiliates. All rights reserved.
 */

/*
 * This is a Solaris plugin for auditing the KDC.
 */

#include <k5-int.h>
#include <krb5/audit_plugin.h>
#include <kdc_j_encode.h>
#include "j_dict.h"
#include <syslog.h>
#include <bsm/adt.h>
#include <bsm/adt_event.h>
#include <k5-json.h>

extern krb5_error_code data_to_value(krb5_data *, k5_json_object, const char *);
extern krb5_error_code req_to_value(krb5_kdc_req *, const krb5_boolean,
	k5_json_object);
extern krb5_error_code rep_to_value(krb5_kdc_rep *, const krb5_boolean,
	k5_json_object);

krb5_error_code
audit_solaris_initvt(krb5_context context, int maj_ver, int min_ver,
	krb5_plugin_vtable vtable);

struct krb5_audit_moddata_st {
	adt_session_data_t	*ah;
};

/* Create handle to the audit system. Returns 0 on success. */
static krb5_error_code
open_au(krb5_audit_moddata *auctx_out)
{
	adt_session_data_t	*ah;
	krb5_error_code		ret;
	krb5_audit_moddata	auctx;

	auctx = k5calloc(1, sizeof (*auctx), &ret);
	if (ret)
		return (ENOMEM);

	if (adt_start_session(&ah, NULL, ADT_USE_PROC_DATA) != 0) {
		syslog(LOG_AUTH | LOG_ALERT, "adt_start_session(): %m");
		free(auctx);
		return (KRB5_PLUGIN_NO_HANDLE);
	}

	auctx->ah = ah;
	*auctx_out = auctx;

	return (0);
}

/* Close connection to the audit system. Returns 0 on success. */
static krb5_error_code
close_au(krb5_audit_moddata auctx)
{
	adt_session_data_t	*ah = auctx->ah;

	(void) adt_end_session(ah);

	return (0);
}

/* Log KDC-start event. Returns 0 on success. */
static krb5_error_code
kdc_start(krb5_audit_moddata auctx, krb5_boolean ev_success)
{
	adt_session_data_t	*ah = auctx->ah;
	adt_event_data_t	*event;
	int			status = ev_success ? ADT_SUCCESS : ADT_FAILURE;

	if (ah == NULL)
		return (KRB5_PLUGIN_NO_HANDLE); /* audit handle unavailable */

	if ((event = adt_alloc_event(ah, ADT_krb5kdc_start)) == NULL) {
		syslog(LOG_AUTH | LOG_ALERT, "adt_alloc_event(): %m");
		(void) adt_end_session(ah);
		return (KRB5_PLUGIN_NO_HANDLE);
	}

	if (adt_put_event(event, status, status) != 0) {
		syslog(LOG_AUTH | LOG_ALERT, "adt_put_event(): %m");
		adt_free_event(event);
		(void) adt_end_session(ah);
		return (KRB5_PLUGIN_NO_HANDLE);
	}

	adt_free_event(event);

	return (0);
}

/* Log KDC-stop event. Returns 0 on success. */
static krb5_error_code
kdc_stop(krb5_audit_moddata auctx, krb5_boolean ev_success)
{
	adt_session_data_t	*ah = auctx->ah;
	adt_event_data_t	*event;
	int			status = ev_success ? ADT_SUCCESS : ADT_FAILURE;

	if (ah == NULL)
		return (KRB5_PLUGIN_NO_HANDLE); /* audit handle unavailable */

	if ((event = adt_alloc_event(ah, ADT_krb5kdc_stop)) == NULL) {
		syslog(LOG_AUTH | LOG_ALERT, "adt_alloc_event(): %m");
		(void) adt_end_session(ah);
		return (KRB5_PLUGIN_NO_HANDLE);
	}

	if (adt_put_event(event, status, status) != 0) {
		syslog(LOG_AUTH | LOG_ALERT, "adt_put_event(): %m");
		adt_free_event(event);
		(void) adt_end_session(ah);
		return (KRB5_PLUGIN_NO_HANDLE);
	}

	adt_free_event(event);

	return (0);
}

/* Log AS_REQ event. Returns 0 on success */
static krb5_error_code
as_req(krb5_audit_moddata auctx, krb5_boolean ev_success,
	krb5_audit_state *state)
{
	adt_session_data_t	*ah = auctx->ah;
	adt_event_data_t	*event;
	int			status = ev_success ? ADT_SUCCESS : ADT_FAILURE;
	krb5_error_code		ret = 0;
	char			*cprinc = NULL, *sprinc = NULL;
	krb5_context		context;

	if (ah == NULL)
		return (KRB5_PLUGIN_NO_HANDLE);
	/* Return success if NULL state */
	if (state == NULL)
		return (0);

	if (ret = krb5_init_context(&context)) {
		syslog(LOG_AUTH | LOG_ALERT, "krb5_init_context(): %m");
		goto error;
	}

	if ((event = adt_alloc_event(ah, ADT_as_req)) == NULL) {
		syslog(LOG_AUTH | LOG_ALERT, "adt_alloc_event(): %m");
		ret = ENOMEM;
		goto error;
	}

	event->adt_as_req.cl_port = state->cl_port;

	if (state->cl_addr && state->cl_addr->addrtype == ADDRTYPE_INET)
		event->adt_as_req.cl_addr_type = ADT_IPv4;
	else if (state->cl_addr && state->cl_addr->addrtype == ADDRTYPE_INET6)
		event->adt_as_req.cl_addr_type = ADT_IPv6;
	else {
		syslog(LOG_AUTH | LOG_ALERT, "invalid address type(): %m");
		ret = EIO;
		goto error;
	}
	(void) memcpy(event->adt_as_req.cl_addr_address,
	    state->cl_addr->contents, state->cl_addr->length);

	if (state->request && state->request->client != NULL) {
		if (ret = krb5_unparse_name(context, state->request->client,
		    &cprinc)) {
			syslog(LOG_AUTH | LOG_ALERT, "krb5_unparse_name(): %m");
			goto error;
		}
		event->adt_as_req.client = strdup(cprinc);
	} else
		event->adt_as_req.client = strdup("<none>");
	if (event->adt_as_req.client == NULL) {
		ret = ENOMEM;
		goto error;
	}

	if (state->request && state->request->server != NULL) {
		if (ret = krb5_unparse_name(context, state->request->server,
		    &sprinc)) {
			syslog(LOG_AUTH | LOG_ALERT, "krb5_unparse_name(): %m");
			goto error;
		}
		event->adt_as_req.service = strdup(sprinc);
	} else
		event->adt_as_req.service = strdup("<none>");
	if (event->adt_as_req.service == NULL) {
		ret = ENOMEM;
		goto error;
	}

	if (state->status != NULL)
		event->adt_as_req.status = strdup(state->status);
	else
		event->adt_as_req.status = strdup("SUCCESS");
	if (event->adt_as_req.status == NULL) {
		ret = ENOMEM;
		goto error;
	}

	if (adt_put_event(event, status, status) != 0) {
		syslog(LOG_AUTH | LOG_ALERT, "adt_put_event(): %m");
		ret = ENOMEM;
	}

error:
	if (event != NULL)
		adt_free_event(event);
	if (cprinc != NULL)
		free(cprinc);
	if (sprinc != NULL)
		free(sprinc);
	if (ret != 0)
		(void) adt_end_session(ah);

	return (ret);
}

/* Log TGS_REQ event. Returns 0 on success */
static krb5_error_code
tgs_req(krb5_audit_moddata auctx, krb5_boolean ev_success,
	krb5_audit_state *state)
{
	adt_session_data_t	*ah = auctx->ah;
	adt_event_data_t	*event;
	int			status = ev_success ? ADT_SUCCESS : ADT_FAILURE;
	krb5_error_code		ret = 0;
	char			*cprinc = NULL, *sprinc = NULL;
	krb5_context		context;

	if (ah == NULL)
		return (KRB5_PLUGIN_NO_HANDLE);
	/* Return success if NULL state */
	if (state == NULL)
		return (0);

	if (ret = krb5_init_context(&context)) {
		syslog(LOG_AUTH | LOG_ALERT, "krb5_init_context(): %m");
		goto error;
	}

	if ((event = adt_alloc_event(ah, ADT_tgs_req)) == NULL) {
		syslog(LOG_AUTH | LOG_ALERT, "adt_alloc_event(): %m");
		ret = ENOMEM;
		goto error;
	}

	event->adt_tgs_req.cl_port = state->cl_port;

	if (state->cl_addr && state->cl_addr->addrtype == ADDRTYPE_INET)
		event->adt_tgs_req.cl_addr_type = ADT_IPv4;
	else if (state->cl_addr && state->cl_addr->addrtype == ADDRTYPE_INET6)
		event->adt_tgs_req.cl_addr_type = ADT_IPv6;
	else {
		syslog(LOG_AUTH | LOG_ALERT, "invalid address type(): %m");
		ret = EIO;
		goto error;
	}
	(void) memcpy(event->adt_tgs_req.cl_addr_address,
	    state->cl_addr->contents, state->cl_addr->length);

	if (state->reply && state->reply->client != NULL) {
		if (ret = krb5_unparse_name(context, state->reply->client,
		    &cprinc)) {
			syslog(LOG_AUTH | LOG_ALERT, "krb5_unparse_name(): %m");
			goto error;
		}
		event->adt_tgs_req.client = strdup(cprinc);
	} else
		event->adt_tgs_req.client = strdup("<none>");
	if (event->adt_tgs_req.client == NULL) {
		ret = ENOMEM;
		goto error;
	}

	if (state->request && state->request->server != NULL) {
		if (ret = krb5_unparse_name(context, state->request->server,
		    &sprinc)) {
			syslog(LOG_AUTH | LOG_ALERT, "krb5_unparse_name(): %m");
			goto error;
		}
		event->adt_tgs_req.service = strdup(sprinc);
	} else
		event->adt_tgs_req.service = strdup("<none>");
	if (event->adt_tgs_req.service == NULL) {
		ret = ENOMEM;
		goto error;
	}

	if (state->status != NULL)
		event->adt_tgs_req.status = strdup(state->status);
	else
		event->adt_tgs_req.status = strdup("SUCCESS");
	if (event->adt_tgs_req.status == NULL) {
		ret = ENOMEM;
		goto error;
	}

	if (adt_put_event(event, status, status) != 0) {
		syslog(LOG_AUTH | LOG_ALERT, "adt_put_event(): %m");
		ret = ENOMEM;
	}

error:
	if (event != NULL)
		adt_free_event(event);
	if (cprinc != NULL)
		free(cprinc);
	if (sprinc != NULL)
		free(sprinc);
	if (ret != 0)
		(void) adt_end_session(ah);

	return (ret);
}

/* Log TGS_S4U2SELF event. Returns 0 on success */
static krb5_error_code
tgs_s4u2self(krb5_audit_moddata auctx, krb5_boolean ev_success,
	krb5_audit_state *state)
{
	adt_session_data_t	*ah = auctx->ah;
	adt_event_data_t	*event;
	int			status = ev_success ? ADT_SUCCESS : ADT_FAILURE;
	krb5_error_code		ret = 0;
	char			*cprinc = NULL, *sprinc = NULL;
	krb5_context		context;

	if (ah == NULL)
		return (KRB5_PLUGIN_NO_HANDLE);
	/* Return success if NULL state */
	if (state == NULL)
		return (0);

	if (ret = krb5_init_context(&context)) {
		syslog(LOG_AUTH | LOG_ALERT, "krb5_init_context(): %m");
		goto error;
	}

	if ((event = adt_alloc_event(ah, ADT_tgs_s4u2self)) == NULL) {
		syslog(LOG_AUTH | LOG_ALERT, "adt_alloc_event(): %m");
		ret = ENOMEM;
		goto error;
	}

	event->adt_tgs_s4u2self.cl_port = state->cl_port;

	if (state->cl_addr && state->cl_addr->addrtype == ADDRTYPE_INET)
		event->adt_tgs_s4u2self.cl_addr_type = ADT_IPv4;
	else if (state->cl_addr && state->cl_addr->addrtype == ADDRTYPE_INET6)
		event->adt_tgs_s4u2self.cl_addr_type = ADT_IPv6;
	else {
		syslog(LOG_AUTH | LOG_ALERT, "invalid address type(): %m");
		ret = EIO;
		goto error;
	}
	(void) memcpy(event->adt_tgs_s4u2self.cl_addr_address,
	    state->cl_addr->contents, state->cl_addr->length);

	if (state->reply && state->reply->client != NULL) {
		if (ret = krb5_unparse_name(context, state->reply->client,
		    &cprinc)) {
			syslog(LOG_AUTH | LOG_ALERT, "krb5_unparse_name(): %m");
			goto error;
		}
		event->adt_tgs_s4u2self.client = strdup(cprinc);
	} else
		event->adt_tgs_s4u2self.client = strdup("<none>");
	if (event->adt_tgs_s4u2self.client == NULL) {
		ret = ENOMEM;
		goto error;
	}

	if (state->request && state->request->server != NULL) {
		if (ret = krb5_unparse_name(context, state->request->server,
		    &sprinc)) {
			syslog(LOG_AUTH | LOG_ALERT, "krb5_unparse_name(): %m");
			goto error;
		}
		event->adt_tgs_s4u2self.service = strdup(sprinc);
	} else
		event->adt_tgs_s4u2self.service = strdup("<none>");
	if (event->adt_tgs_s4u2self.service == NULL) {
		ret = ENOMEM;
		goto error;
	}

	if (state->status != NULL)
		event->adt_tgs_s4u2self.status = strdup(state->status);
	else
		event->adt_tgs_s4u2self.status = strdup("SUCCESS");
	if (event->adt_tgs_s4u2self.status == NULL) {
		ret = ENOMEM;
		goto error;
	}

	if (adt_put_event(event, status, status) != 0) {
		syslog(LOG_AUTH | LOG_ALERT, "adt_put_event(): %m");
		ret = ENOMEM;
	}

error:
	if (event != NULL)
		adt_free_event(event);
	if (cprinc != NULL)
		free(cprinc);
	if (sprinc != NULL)
		free(sprinc);
	if (ret != 0)
		(void) adt_end_session(ah);

	return (ret);
}

/* Log TGS_S4U2PROXY event. Returns 0 on success */
static krb5_error_code
tgs_s4u2proxy(krb5_audit_moddata auctx, krb5_boolean ev_success,
	krb5_audit_state *state)
{
	adt_session_data_t	*ah = auctx->ah;
	adt_event_data_t	*event;
	int			status = ev_success ? ADT_SUCCESS : ADT_FAILURE;
	krb5_error_code		ret = 0;
	char			*cprinc = NULL, *sprinc = NULL;
	krb5_context		context;

	if (ah == NULL)
		return (KRB5_PLUGIN_NO_HANDLE);
	/* Return success if NULL state */
	if (state == NULL)
		return (0);

	if (ret = krb5_init_context(&context)) {
		syslog(LOG_AUTH | LOG_ALERT, "krb5_init_context(): %m");
		goto error;
	}

	if ((event = adt_alloc_event(ah, ADT_tgs_s4u2proxy)) == NULL) {
		syslog(LOG_AUTH | LOG_ALERT, "adt_alloc_event(): %m");
		ret = ENOMEM;
		goto error;
	}

	event->adt_tgs_s4u2proxy.cl_port = state->cl_port;

	if (state->cl_addr && state->cl_addr->addrtype == ADDRTYPE_INET)
		event->adt_tgs_s4u2proxy.cl_addr_type = ADT_IPv4;
	else if (state->cl_addr && state->cl_addr->addrtype == ADDRTYPE_INET6)
		event->adt_tgs_s4u2proxy.cl_addr_type = ADT_IPv6;
	else {
		syslog(LOG_AUTH | LOG_ALERT, "invalid address type(): %m");
		ret = EIO;
		goto error;
	}
	(void) memcpy(event->adt_tgs_s4u2proxy.cl_addr_address,
	    state->cl_addr->contents, state->cl_addr->length);

	if (state->reply && state->reply->client != NULL) {
		if (ret = krb5_unparse_name(context, state->reply->client,
		    &cprinc)) {
			syslog(LOG_AUTH | LOG_ALERT, "krb5_unparse_name(): %m");
			goto error;
		}
		event->adt_tgs_s4u2proxy.client = strdup(cprinc);
	} else
		event->adt_tgs_s4u2proxy.client = strdup("<none>");
	if (event->adt_tgs_s4u2proxy.client == NULL) {
		ret = ENOMEM;
		goto error;
	}

	if (state->request && state->request->server != NULL) {
		if (ret = krb5_unparse_name(context, state->request->server,
		    &sprinc)) {
			syslog(LOG_AUTH | LOG_ALERT, "krb5_unparse_name(): %m");
			goto error;
		}
		event->adt_tgs_s4u2proxy.service = strdup(sprinc);
	} else
		event->adt_tgs_s4u2proxy.service = strdup("<none>");
	if (event->adt_tgs_s4u2proxy.service == NULL) {
		ret = ENOMEM;
		goto error;
	}

	if (state->status != NULL)
		event->adt_tgs_s4u2proxy.status = strdup(state->status);
	else
		event->adt_tgs_s4u2proxy.status = strdup("SUCCESS");
	if (event->adt_tgs_s4u2proxy.status == NULL) {
		ret = ENOMEM;
		goto error;
	}

	if (adt_put_event(event, status, status) != 0) {
		syslog(LOG_AUTH | LOG_ALERT, "adt_put_event(): %m");
		ret = ENOMEM;
	}

error:
	if (event != NULL)
		adt_free_event(event);
	if (cprinc != NULL)
		free(cprinc);
	if (sprinc != NULL)
		free(sprinc);
	if (ret != 0)
		(void) adt_end_session(ah);

	return (ret);
}

/* Log TGS_U2U event. Returns 0 on success */
static krb5_error_code
tgs_u2u(krb5_audit_moddata auctx, krb5_boolean ev_success,
	krb5_audit_state *state)
{
	adt_session_data_t	*ah = auctx->ah;
	adt_event_data_t	*event;
	int			status = ev_success ? ADT_SUCCESS : ADT_FAILURE;
	krb5_error_code		ret = 0;
	char			*cprinc = NULL, *sprinc = NULL;
	krb5_context		context;

	if (ah == NULL)
		return (KRB5_PLUGIN_NO_HANDLE);
	/* Return success if NULL state */
	if (state == NULL)
		return (0);

	if (ret = krb5_init_context(&context)) {
		syslog(LOG_AUTH | LOG_ALERT, "krb5_init_context(): %m");
		goto error;
	}

	if ((event = adt_alloc_event(ah, ADT_tgs_u2u)) == NULL) {
		syslog(LOG_AUTH | LOG_ALERT, "adt_alloc_event(): %m");
		ret = ENOMEM;
		goto error;
	}

	event->adt_tgs_u2u.cl_port = state->cl_port;

	if (state->cl_addr && state->cl_addr->addrtype == ADDRTYPE_INET)
		event->adt_tgs_u2u.cl_addr_type = ADT_IPv4;
	else if (state->cl_addr && state->cl_addr->addrtype == ADDRTYPE_INET6)
		event->adt_tgs_u2u.cl_addr_type = ADT_IPv6;
	else {
		syslog(LOG_AUTH | LOG_ALERT, "invalid address type(): %m");
		ret = EIO;
		goto error;
	}
	(void) memcpy(event->adt_tgs_u2u.cl_addr_address,
	    state->cl_addr->contents, state->cl_addr->length);

	if (state->reply && state->reply->client != NULL) {
		if (ret = krb5_unparse_name(context, state->reply->client,
		    &cprinc)) {
			syslog(LOG_AUTH | LOG_ALERT, "krb5_unparse_name(): %m");
			goto error;
		}
		event->adt_tgs_u2u.client = strdup(cprinc);
	} else
		event->adt_tgs_u2u.client = strdup("<none>");
	if (event->adt_tgs_u2u.client == NULL) {
		ret = ENOMEM;
		goto error;
	}

	if (state->request && state->request->server != NULL) {
		if (ret = krb5_unparse_name(context, state->request->server,
		    &sprinc)) {
			syslog(LOG_AUTH | LOG_ALERT, "krb5_unparse_name(): %m");
			goto error;
		}
		event->adt_tgs_u2u.service = strdup(sprinc);
	} else
		event->adt_tgs_u2u.service = strdup("<none>");
	if (event->adt_tgs_u2u.service == NULL) {
		ret = ENOMEM;
		goto error;
	}

	if (state->status != NULL)
		event->adt_tgs_u2u.status = strdup(state->status);
	else
		event->adt_tgs_u2u.status = strdup("SUCCESS");
	if (event->adt_tgs_u2u.status == NULL) {
		ret = ENOMEM;
		goto error;
	}

	if (adt_put_event(event, status, status) != 0) {
		syslog(LOG_AUTH | LOG_ALERT, "adt_put_event(): %m");
		ret = ENOMEM;
	}

error:
	if (event != NULL)
		adt_free_event(event);
	if (cprinc != NULL)
		free(cprinc);
	if (sprinc != NULL)
		free(sprinc);
	if (ret != 0)
		(void) adt_end_session(ah);

	return (ret);
}

krb5_error_code
audit_solaris_initvt(krb5_context context, int maj_ver,
	int min_ver, krb5_plugin_vtable vtable)
{
	krb5_audit_vtable vt;

	if (maj_ver != 1)
		return (KRB5_PLUGIN_VER_NOTSUPP);
	vt = (krb5_audit_vtable)vtable;
	vt->name = "solaris";
	vt->open = open_au;
	vt->close = close_au;
	vt->kdc_start = kdc_start;
	vt->kdc_stop = kdc_stop;
	vt->as_req = as_req;
	vt->tgs_req = tgs_req;
	vt->tgs_s4u2self = tgs_s4u2self;
	vt->tgs_s4u2proxy = tgs_s4u2proxy;
	vt->tgs_u2u = tgs_u2u;

	return (0);
}
