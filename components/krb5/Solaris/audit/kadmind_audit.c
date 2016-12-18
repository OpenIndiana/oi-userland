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

#include <socket-utils.h>
#include <rpc/rpc.h>
#include <syslog.h>
#include <bsm/adt.h>
#include <bsm/adt_event.h>

void
audit_kadmind(char *op, char *target, char *client, char *service, char *status,
    SVCXPRT *xprt, int failure)
{
	adt_session_data_t	*ah;
	adt_event_data_t	*event;
	adt_termid_t		*termid;
	int			adtstat = failure ? ADT_FAILURE : ADT_SUCCESS;
	void			*p = (void *)xprt->xp_rtaddr.buf;
	struct sockaddr_in	*p4;
	struct sockaddr_in6	*p6;

	if (adt_start_session(&ah, NULL, ADT_USE_PROC_DATA) != 0) {
		syslog(LOG_AUTH | LOG_ALERT, "adt_start_session(): %m");
		return;
	}

	if ((event = adt_alloc_event(ah, ADT_kadmind)) == NULL) {
		syslog(LOG_AUTH | LOG_ALERT, "adt_alloc_event(): %m");
		(void) adt_end_session(ah);
		return;
	}

	if (((struct sockaddr *)p)->sa_family == AF_INET) {
		p4 = (struct sockaddr_in *)p;
		event->adt_kadmind.cl_port = ntohs(p4->sin_port);
		event->adt_kadmind.cl_addr_type = ADT_IPv4;
		event->adt_kadmind.cl_addr_address[0] =
		    (uint32_t)p4->sin_addr.s_addr;
	} else if (((struct sockaddr *)p)->sa_family == AF_INET6) {
		p6 = (struct sockaddr_in6 *)p;
		event->adt_kadmind.cl_port = ntohs(p6->sin6_port);
		event->adt_kadmind.cl_addr_type = ADT_IPv6;
		(void) memcpy(event->adt_kadmind.cl_addr_address,
		    &p6->sin6_addr, 4 * sizeof (uint_t));
	}

	event->adt_kadmind.op = op;
	event->adt_kadmind.target = target;
	event->adt_kadmind.client = client;
	event->adt_kadmind.service = service;
	event->adt_kadmind.status = status;

	if (adt_put_event(event, adtstat, adtstat) != 0)
		syslog(LOG_AUTH | LOG_ALERT, "adt_put_event(): %m");

	adt_free_event(event);
	(void) adt_end_session(ah);
}
