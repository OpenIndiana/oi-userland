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
 * Copyright (c) 2013, Oracle and/or its affiliates. All rights reserved.
 */

/*
 * Ruby binding for libbsm used by Puppet to record audit events
 */

#include <ruby.h>
#include <pwd.h>
#include <nss_dbdefs.h>
#include <bsm/adt.h>
#include <bsm/adt_event.h>

VALUE cPuppetAudit;

VALUE
audit_new(VALUE class)
{
	adt_session_data_t	*ah;
	VALUE			data;

	if (adt_start_session(&ah, NULL, 0) != 0) {
		perror("puppet adt_start_session");
		exit(1);
	}
	data = Data_Wrap_Struct(class, 0, 0, ah);
	rb_obj_call_init(data, 0, 0);
	return (data);
}

static VALUE
audit_init(VALUE self)
{
	adt_session_data_t	*ah;
	adt_termid_t		*tid;
	struct passwd		pwd, *result;
	char			*buffer;
	size_t			size = NSS_BUFLEN_PASSWD;

	Data_Get_Struct(self, adt_session_data_t, ah);

	if (adt_load_hostname(NULL, &tid) != 0) {
		perror("puppet adt_load_hostname");
		(void) adt_end_session(ah);
		exit(1);
	}

	if ((buffer = malloc(size)) == NULL)
		exit(1);

	/* set "puppet" as user name and preselection */
	if (getpwnam_r("puppet", &pwd, buffer, size, &result) != 0) {
		perror("puppet getpwnam_r(puppet)");
		(void) adt_end_session(ah);
		free(buffer);
		exit(1);
	}

	if (result == NULL) {
		perror("puppet getpwnam_r(puppet)");
		(void) adt_end_session(ah);
		free(buffer);
		exit(1);
	}

	if (adt_set_user(ah, result->pw_uid, result->pw_gid, result->pw_uid,
	    result->pw_gid, tid, ADT_NEW) != 0) {
		perror("puppet adt_set_user");
		free(tid);
		(void) adt_end_session(ah);
		free(buffer);
		exit(1);
	}
	free(tid);

	/* set audit context on this process */
	if (adt_set_proc(ah) != 0) {
		perror("puppet adt_set_proc");
		(void) adt_end_session(ah);
		free(buffer);
		exit(1);
	}
	free(buffer);
	return (self);
}

static VALUE
audit_start(VALUE self)
{
	adt_event_data_t	*event;
	adt_session_data_t	*ah;

	Data_Get_Struct(self, adt_session_data_t, ah);

	if ((event = adt_alloc_event(ah, ADT_puppet_session_start)) == NULL) {
		perror("adt_alloc_event(ADT_puppet_session_start)");
		(void) adt_end_session(ah);
		ah = NULL;
	} else {
		if (adt_put_event(event, ADT_SUCCESS, ADT_SUCCESS) != 0) {
			perror("adt_put_event(ADT_puppet_session_start)");
		}
		adt_free_event(event);
	}
	return (self);
}

static VALUE
audit_stop(VALUE self)
{
	adt_event_data_t	*event;
	adt_session_data_t	*ah;

	Data_Get_Struct(self, adt_session_data_t, ah);

	if ((event = adt_alloc_event(ah, ADT_puppet_session_end)) == NULL) {
		perror("adt_alloc_event(ADT_puppet_session_end)");
	} else {
		if (adt_put_event(event, ADT_SUCCESS, ADT_SUCCESS) != 0) {
			perror("adt_put_event(ADT_puppet_session_end)");
		}
		adt_free_event(event);
	}
	return (self);
}

static VALUE
audit_teardown(VALUE self)
{
	adt_session_data_t	*ah;

	Data_Get_Struct(self, adt_session_data_t, ah);

	(void) adt_end_session(ah);
	return (self);
}

void
Init_PuppetAudit()
{
	cPuppetAudit = rb_define_class("PuppetAudit", rb_cObject);
	rb_define_singleton_method(cPuppetAudit, "new", audit_new, 0);
	rb_define_method(cPuppetAudit, "initialize", audit_init, 0);
	rb_define_method(cPuppetAudit, "audit_start", audit_start, 0);
	rb_define_method(cPuppetAudit, "audit_stop", audit_stop, 0);
	rb_define_method(cPuppetAudit, "audit_teardown", audit_teardown, 0);
}
