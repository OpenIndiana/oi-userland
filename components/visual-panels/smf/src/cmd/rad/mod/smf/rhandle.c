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
 * Copyright (c) 2011, 2012, Oracle and/or its affiliates. All rights reserved.
 */

#include <stdlib.h>
#include <assert.h>
#include <pthread.h>

#include <libscf.h>
#include <rad/rad_modapi.h>

#include "rhandle.h"

static pthread_mutex_t handle_lock = PTHREAD_MUTEX_INITIALIZER;
static rad_handle_t *rhandle;

/*
 * Rebinding a repository handle after the connection is broken
 * requires that we correctly drain all its users, which is difficult.
 * Instead we wrap and reference count the handle, and force callers
 * to re-fetch the latest handle on connection failures.
 */

static scf_handle_t *
handle_create(void)
{
	scf_handle_t *h = scf_handle_create(SCF_VERSION);
	if (h == NULL)
		return (NULL);

	if (scf_handle_bind(h) == -1) {
		scf_handle_destroy(h);
		return (NULL);
	}
	return (h);
}

rad_handle_t *
rh_fetch(void)
{
	rad_handle_t *rh;

	rad_mutex_enter(&handle_lock);
	if (rhandle != NULL) {
		rh = rhandle;
		rh->rh_refs++;
	} else {
		rh = malloc(sizeof (rad_handle_t));
		if (rh == NULL)
			goto out;
		if ((rh->rh_hdl = handle_create()) == NULL) {
			free(rh);
			rh = NULL;
			goto out;
		}
		rh->rh_refs = 1;
		rhandle = rh;
	}
out:
	rad_mutex_exit(&handle_lock);

	return (rh);
}

void
rh_rele(rad_handle_t *rh)
{
	if (rh == NULL)
		return;

	rad_mutex_enter(&handle_lock);
	if (--rh->rh_refs == 0 && rhandle != rh) {
		scf_handle_destroy(rh->rh_hdl);
		free(rh);
	}
	rad_mutex_exit(&handle_lock);
}

void
rh_kill(rad_handle_t *rh)
{
	if (rh == NULL)
		return;

	rad_mutex_enter(&handle_lock);
	if (rhandle == rh)
		rhandle = NULL;
	rad_mutex_exit(&handle_lock);
}
