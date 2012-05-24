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

#include <rad/rad_modapi.h>
#include <libscf.h>

#include "smfutil.h"

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

static conerr_t
maperr(scf_error_t e)
{
	switch (e) {
	case SCF_ERROR_NONE:
		return (ce_ok);
	case SCF_ERROR_PERMISSION_DENIED:
		return (ce_priv);
	default:
		return (ce_system);
	}
}

conerr_t
smfu_get_property(char *fmri, char *pgname, char *propname, char *value,
    size_t n)
{
	conerr_t err = ce_ok;
	scf_handle_t *scfhandle = handle_create();
	scf_service_t *service = scf_service_create(scfhandle);
	scf_instance_t *instance = scf_instance_create(scfhandle);
	scf_propertygroup_t *pg = scf_pg_create(scfhandle);
	scf_property_t *prop = scf_property_create(scfhandle);
	scf_iter_t *iter = scf_iter_create(scfhandle);
	scf_value_t *val = scf_value_create(scfhandle);

	if (scfhandle == NULL || service == NULL || instance == NULL ||
	    pg == NULL || prop == NULL || iter == NULL || val == NULL) {
		err = ce_nomem;
		goto out;
	}

	if (scf_handle_decode_fmri(scfhandle, fmri, NULL, service, instance,
	    NULL, NULL, 0) != SCF_SUCCESS) {
		rad_log(RL_ERROR, "couldn't decode '%s': %s\n", fmri,
		    scf_strerror(scf_error()));
		err = maperr(scf_error());
		goto out;
	}

	if (scf_instance_get_pg(instance, pgname, pg) != 0 ||
	    scf_pg_get_property(pg, propname, prop) != 0 ||
	    scf_iter_property_values(iter, prop) != 0) {
		rad_log(RL_ERROR, "couldn't get property: '%s/%s/%s': %s\n",
		    fmri, pgname, propname, scf_strerror(scf_error()));
		err = maperr(scf_error());
		goto out;
	}

	if (scf_iter_next_value(iter, val) > 0 &&
	    scf_value_get_as_string(val, value, n) == -1) {
		rad_log(RL_ERROR,
		    "couldn't get property value: '%s/%s/%s': %s\n", fmri,
		    pgname, propname, scf_strerror(scf_error()));
		err = maperr(scf_error());
		goto out;
	}
out:
	scf_value_destroy(val);
	scf_property_destroy(prop);
	scf_pg_destroy(pg);
	scf_iter_destroy(iter);
	scf_instance_destroy(instance);
	scf_service_destroy(service);
	scf_handle_destroy(scfhandle);

	return (err);
}

conerr_t
smfu_set_property(char *fmri, char *pgname, char *propname, char *value)
{
	conerr_t err = ce_ok;
	scf_handle_t *scfhandle = handle_create();
	scf_service_t *service = scf_service_create(scfhandle);
	scf_instance_t *instance = scf_instance_create(scfhandle);
	scf_propertygroup_t *pg = scf_pg_create(scfhandle);
	scf_property_t *prop = scf_property_create(scfhandle);
	scf_value_t *val = scf_value_create(scfhandle);
	scf_transaction_t *tx = scf_transaction_create(scfhandle);
	scf_transaction_entry_t *ent = scf_entry_create(scfhandle);
	scf_type_t type;

	if (scfhandle == NULL || service == NULL || instance == NULL ||
	    pg == NULL || prop == NULL || tx == NULL || ent == NULL ||
	    val == NULL) {
		err = ce_nomem;
		goto out;
	}

	if (scf_handle_decode_fmri(scfhandle, fmri, NULL, service, instance,
	    NULL, NULL, 0) != SCF_SUCCESS) {
		rad_log(RL_ERROR, "couldn't decode '%s': %s\n", fmri,
		    scf_strerror(scf_error()));
		err = maperr(scf_error());
		goto out;
	}

	if (scf_instance_get_pg(instance, pgname, pg) != 0 ||
	    scf_pg_get_property(pg, propname, prop) != 0 ||
	    scf_property_type(prop, &type) != 0) {
		rad_log(RL_ERROR, "couldn't get property: '%s/%s/%s': %s\n",
		    fmri, pgname, propname, scf_strerror(scf_error()));
		err = maperr(scf_error());
		goto out;
	}

top:
	if (scf_transaction_start(tx, pg) == -1 ||
	    scf_transaction_property_change(tx, ent, propname, type) != 0 ||
	    scf_value_set_from_string(val, type, value) != 0 ||
	    scf_entry_add_value(ent, val) != 0) {
		rad_log(RL_ERROR, "couldn't set property: '%s/%s/%s': %s\n",
		    fmri, pgname, propname, scf_strerror(scf_error()));
		err = maperr(scf_error());
		goto out;
	}

	switch (scf_transaction_commit(tx)) {
	/* success */
	case 1:
		if (smf_refresh_instance(fmri) != 0) {
			err = maperr(scf_error());
			goto out;
		}
		break;
	/* retry */
	case 0:
		if (scf_pg_update(pg) != 0) {
			err = maperr(scf_error());
			goto out;
		}
		scf_transaction_reset(tx);
		goto top;
	default:
		err = maperr(scf_error());
		goto out;
	}
out:
	scf_entry_destroy(ent);
	scf_transaction_destroy(tx);
	scf_value_destroy(val);
	scf_property_destroy(prop);
	scf_pg_destroy(pg);
	scf_instance_destroy(instance);
	scf_service_destroy(service);
	scf_handle_destroy(scfhandle);

	return (err);
}
