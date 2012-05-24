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

#include <sys/list.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <unistd.h>
#include <fcntl.h>
#include <assert.h>

#include <libscf.h>
#include <libscf_priv.h>

#include <rad/adr.h>
#include <rad/rad_modapi.h>

#include "api_smf.h"
#include "rhandle.h"
#include "smfutil.h"

/* Shared with other files */
ssize_t max_fmri;
ssize_t max_name;
ssize_t max_value;
ssize_t max_pgtype;

svcerr_t
error_scf(data_t **error, data_t *code, data_t *target, const char *aux,
    const char *msg)
{
	assert(data_type(code) == &t__ErrorCode);
	assert(target == NULL || data_type(target) == &t__ErrorTarget);

	if (error != NULL) {
		data_t *e = data_new_struct(&t__SmfError);
		struct_set(e, "error", code);
		struct_set(e, "target", target == NULL ?
		    &e__ErrorTarget_NONE : target);
		if (aux != NULL)
			struct_set(e, "aux", data_new_string(aux, lt_copy));
		if (msg != NULL)
			struct_set(e, "message", data_new_string(msg, lt_copy));
		*error = data_purify(e);
	}
	return (SE_FATAL);
}

svcerr_t
internal_error(data_t **error, const char *msg)
{
	return (error_scf(error, &e__ErrorCode_INTERNAL, NULL, NULL, msg));
}

/*
 * Generic error-mapping routine.
 *
 * Maps connection errors to SE_RECONNECT, deletions to SE_RETRY,
 * notfound to SE_NOTFOUND, and everything else to SE_FATAL.
 */
svcerr_t
smfu_maperr(scf_error_t e)
{
	switch (e) {
	case SCF_ERROR_DELETED:
		return (SE_RETRY);
	case SCF_ERROR_NO_SERVER:
	case SCF_ERROR_NOT_BOUND:
	case SCF_ERROR_CONNECTION_BROKEN:
		return (SE_RECONNECT);
	case SCF_ERROR_NOT_FOUND:
		return (SE_NOTFOUND);
	default:
		return (SE_FATAL);
	}
}


/*
 * Reads the specified instance's "enabled" property from the named
 * property group.  Returns an error code or 0 on success.
 */
scf_error_t
smfu_read_enabled(scf_instance_t *inst, scf_propertygroup_t *pg,
    scf_property_t *prop, scf_value_t *value, const char *pgname, uint8_t *bool)
{
	if (scf_instance_get_pg(inst, pgname, pg) == -1 ||
	    scf_pg_get_property(pg, SCF_PROPERTY_ENABLED, prop) == -1 ||
	    scf_property_get_value(prop, value) == -1 ||
	    scf_value_get_boolean(value, bool) == -1)
		return (scf_error());
	return (0);
}

/*
 * Gets a value as a string, allocating the necessary buffer and
 * returning it in *strp.  Returns an error code or 0 on success.
 */
scf_error_t
smfu_value_get_string(scf_value_t *val, char **strp)
{
	ssize_t len, l;
	char *s = NULL;

	len = scf_value_get_as_string(val, NULL, 0);
	for (; len != -1; len = l) {
		s = malloc(len + 1);
		if (s == NULL)
			return (SCF_ERROR_NO_MEMORY);

		l = scf_value_get_as_string(val, s, len + 1);
		if (l == len) {
			*strp = s;
			return (0);
		}
		free(s);
	}

	return (scf_error());
}

/*
 * Gets the named pg in the composed view of the named snapshot. If
 * snapname is not specified, the current pgs/properties are returned.
 * The caller must allocate the pg.  Returns an error code or SE_OK
 * on success.
 */
svcerr_t
smfu_instance_get_composed_pg(scf_handle_t *handle, scf_instance_t *instance,
    const char *snapname, const char *pgname, scf_propertygroup_t *pg,
    data_t **error)
{
	svcerr_t se = SE_OK;
	scf_snapshot_t *snap = NULL;

	if (snapname != NULL) {
		if ((snap = scf_snapshot_create(handle)) == NULL)
			return (SE_FATAL);
		if (scf_instance_get_snapshot(instance, snapname,
		    snap) == -1) {
			if ((se = smfu_maperr(scf_error())) == SE_NOTFOUND)
				(void) error_scf(error, &e__ErrorCode_NOTFOUND,
				    &e__ErrorTarget_SNAPSHOT, snapname, NULL);
			scf_snapshot_destroy(snap);
			return (se);
		}
	}
	if (scf_instance_get_pg_composed(instance, snap, pgname,
	    pg) == -1) {
		if ((se = smfu_maperr(scf_error())) == SE_NOTFOUND)
			(void) error_scf(error, &e__ErrorCode_NOTFOUND,
			    &e__ErrorTarget_PROPERTYGROUP, pgname, NULL);
	}
	if (snap != NULL)
		scf_snapshot_destroy(snap);
	return (se);
}

/*
 * Wrappers around the scf_iter_{instance,service} routines that take an
 * optional type.  Behave like normal scf_* routines on error.
 */

static int
iter_instance_pgs(scf_iter_t *iter, scf_instance_t *inst, const char *type)
{
	if (type == NULL)
		return (scf_iter_instance_pgs(iter, inst));
	return (scf_iter_instance_pgs_typed(iter, inst, type));
}

static int
iter_instance_pgs_composed(scf_iter_t *iter, scf_instance_t *inst,
    scf_snapshot_t *snap, const char *type)
{
	if (type == NULL)
		return (scf_iter_instance_pgs_composed(iter, inst, snap));
	return (scf_iter_instance_pgs_typed_composed(iter, inst, snap, type));
}

static int
iter_service_pgs(scf_iter_t *iter, scf_service_t *service, const char *type)
{
	if (type == NULL)
		return (scf_iter_service_pgs(iter, service));
	return (scf_iter_service_pgs_typed(iter, service, type));
}


/*
 * Iterates over pgs in the composed view of the named snapshot. If
 * snapname is not specified, the current pgs/properties are used. A
 * property group type may be specified.  Returns an error code or 0
 * on success.
 */
scf_error_t
smfu_instance_iter_composed_pgs(scf_handle_t *handle, scf_instance_t *instance,
    const char *snapname, const char *pgtype, scf_iter_t *iter)
{
	int err = 0;
	scf_snapshot_t *snap = NULL;
	if (snapname != NULL) {
		if ((snap = scf_snapshot_create(handle)) == NULL ||
		    scf_instance_get_snapshot(instance, snapname, snap) == -1) {
			err = scf_error();
			goto done;
		}
	}
	if (iter_instance_pgs_composed(iter, instance, snap, pgtype) == -1)
		err = scf_error();

done:
	if (snap != NULL)
		scf_snapshot_destroy(snap);
	return (err);
}


/*
 * Operates like scf_pg_get_property, but takes a fallback property
 * that is returned if the first one isn't found.  Behaves like normal
 * scf_* routines on error.
 */
static int
smfu_pg_get_fb_prop(scf_propertygroup_t *pg,
    const char *name, const char *fbname, scf_property_t *prop)
{
	int res = scf_pg_get_property(pg, name, prop);
	if (res != 0 && scf_error() == SCF_ERROR_NOT_FOUND)
		res = scf_pg_get_property(pg, fbname, prop);
	return (res);
}

/*
 * Reads a string value from a traditionally localized template
 * property group (i.e. description, common name).  First tries the
 * specified locale and then falls back to the C locale.
 */
svcerr_t
smfu_get_l10n_str(scf_handle_t *handle, scf_propertygroup_t *pg,
    const char *locale, char **result)
{
	scf_property_t *prop = scf_property_create(handle);
	scf_value_t *value = scf_value_create(handle);
	svcerr_t se = SE_OK;

	if (prop == NULL || value == NULL) {
		se = SE_FATAL;
		goto done;
	}

	if (smfu_pg_get_fb_prop(pg, locale, "C", prop) != 0 ||
	    scf_property_get_value(prop, value) != 0) {
		se = smfu_maperr(scf_error());
		goto done;
	}

	scf_error_t serr = smfu_value_get_string(value, result);
	if (serr != 0)
		se = smfu_maperr(serr);

done:
	scf_property_destroy(prop);
	scf_value_destroy(value);
	return (se);
}

/*
 * Obtains the specified property group of the service/instance
 * identified by "entity".  For a service, returns the directly
 * attached property group, for an instance, returns the property group
 * from the composed view of the running snapshot.
 */
svcerr_t
smfu_get_pg_r(scf_handle_t *handle, smfu_entity_t *entity, const char *name,
    scf_propertygroup_t *pg)
{
	svcerr_t se = SE_OK;

	if (entity->instance != NULL) {
		se = smfu_instance_get_composed_pg(handle, entity->instance,
		    "running", name, pg, NULL);
	} else if (scf_service_get_pg(entity->service, name, pg) != 0) {
		se = smfu_maperr(scf_error());
	}

	return (se);
}

/*
 * Iterates over the property groups, of type "type" if "type" is
 * non-NULL, of the service/instance identified by "entity".  For a
 * service, iterates over directly attached property groups, for an
 * instance, iterates over the property groups in the composed view of
 * the running snapshot.
 */
svcerr_t
smfu_iter_pg_r(scf_handle_t *handle, smfu_entity_t *entity, const char *type,
    scf_iter_t *iter)
{
	svcerr_t se = SE_OK;

	if (entity->instance != NULL) {
		scf_error_t scferr = smfu_instance_iter_composed_pgs(handle,
		    entity->instance, "running", type, iter);
		if (scferr != 0)
			se = smfu_maperr(scferr);
	} else if (iter_service_pgs(iter, entity->service, type) != 0) {
		se = smfu_maperr(scf_error());
	}

	return (se);
}

/*
 * Obtains the specified property group of the service/instance
 * identified by "entity".  For both services and instances, returns
 * the directly attached property group.
 */
svcerr_t
smfu_get_pg(smfu_entity_t *entity, const char *name,
    scf_propertygroup_t *pg, data_t **error)
{
	svcerr_t se = SE_OK;

	if (entity->instance != NULL) {
		if (scf_instance_get_pg(entity->instance, name, pg) != 0)
			se = smfu_maperr(scf_error());
	} else if (scf_service_get_pg(entity->service, name, pg) != 0) {
		se = smfu_maperr(scf_error());
	}

	if (se == SE_NOTFOUND)
		(void) error_scf(error, &e__ErrorCode_NOTFOUND,
		    &e__ErrorTarget_PROPERTYGROUP, NULL, NULL);

	return (se);
}

/*
 * Iterates over the property groups, of type "type" if "type" is
 * non-NULL, of the service/instance identified by "entity".  For both
 * services and instances, iterates over directly attached property
 * groups.
 */
svcerr_t
smfu_iter_pg(smfu_entity_t *entity, const char *type,
    scf_iter_t *iter)
{
	svcerr_t se = SE_OK;

	if (entity->instance != NULL) {
		if (iter_instance_pgs(iter, entity->instance, type) != 0)
			se = smfu_maperr(scf_error());
	} else if (iter_service_pgs(iter, entity->service, type) != 0) {
		se = smfu_maperr(scf_error());
	}

	return (se);
}

/*
 * Iterates over all services and instances on the system.  Calls scb()
 * on each service if scb is non-NULL.  Calls icb() on each instance if
 * icb is non-NULL.
 */
svcerr_t
smfu_iter_svcs(scf_handle_t *h, svc_callback_t scb, inst_callback_t icb,
    void *arg)
{
	svcerr_t se = SE_OK;

	scf_scope_t *scope = scf_scope_create(h);
	scf_iter_t *siter = scf_iter_create(h);
	scf_iter_t *iiter = scf_iter_create(h);
	scf_service_t *service = scf_service_create(h);
	scf_instance_t *instance = scf_instance_create(h);
	char sname[max_name + 1];
	char iname[max_name + 1];

	if (scope == NULL || siter == NULL || iiter == NULL ||
	    service == NULL || instance == NULL) {
		se = SE_FATAL;
		goto out;
	}

	if (scf_handle_get_scope(h, SCF_SCOPE_LOCAL, scope) == -1 ||
	    scf_iter_scope_services(siter, scope) == -1) {
		se = smfu_maperr(scf_error());
		goto out;
	}

	int e;
	while ((e = scf_iter_next_service(siter, service)) > 0) {
		if (scf_service_get_name(service, sname, sizeof (sname))
		    == -1) {
			se = smfu_maperr(scf_error());
			goto out;
		}
		if (scb) {
			if ((se = scb(h, service, sname, arg)) != SE_OK)
				goto out;
		}

		if (icb) {
			if (scf_iter_service_instances(iiter, service) == -1) {
				se = smfu_maperr(scf_error());
				goto out;
			}
			while (scf_iter_next_instance(iiter, instance) > 0) {
				if (scf_instance_get_name(instance, iname,
				    sizeof (iname)) == -1) {
					se = smfu_maperr(scf_error());
					goto out;
				}
				se = icb(h, instance, sname, iname, arg);
				if (se != SE_OK)
					goto out;
			}
		}
	}
	if (e != 0)
		se = smfu_maperr(scf_error());

out:
	scf_instance_destroy(instance);
	scf_service_destroy(service);
	scf_iter_destroy(iiter);
	scf_iter_destroy(siter);
	scf_scope_destroy(scope);
	return (se == SE_BREAK ? SE_OK : se);
}

/*
 * Look up an entity based on service and (optional) instance name.
 */
svcerr_t
smfu_lookup(scf_handle_t *scfhandle, const char *sname, const char *iname,
    smfu_entity_t *entity)
{
	svcerr_t se = SE_FATAL;
	scf_scope_t *scope = scf_scope_create(scfhandle);
	scf_service_t *service = scf_service_create(scfhandle);
	scf_instance_t *instance = scf_instance_create(scfhandle);

	if (scope == NULL || service == NULL || instance == NULL) {
		se = SE_FATAL;
		goto error;
	}

	if (scf_handle_get_scope(scfhandle, SCF_SCOPE_LOCAL, scope) != 0 ||
	    scf_scope_get_service(scope, sname, service) != 0) {
		se = smfu_maperr(scf_error());
		goto error;
	}

	if (iname != NULL) {
		if (scf_service_get_instance(service, iname, instance) != 0) {
			se = smfu_maperr(scf_error());
			goto error;
		}
		entity->instance = instance;
	}

	entity->service = service;
	scf_scope_destroy(scope);
	return (SE_OK);

error:
	scf_instance_destroy(instance);
	scf_service_destroy(service);
	scf_scope_destroy(scope);

	if (se == SE_NOTFOUND)
		return (SE_STALE);
	return (se);
}

/*
 * Free an entity.
 */
void
smfu_entity_destroy(smfu_entity_t *entity)
{
	scf_service_destroy(entity->service);
	scf_instance_destroy(entity->instance);
}


/*
 * Test for the existence of service sname, optionally with instance iname.
 */
svcerr_t
smfu_test(const char *sname, const char *iname)
{
	svcerr_t se;
	do {
		rad_handle_t *rh = rh_fetch();
		if (rh == NULL) {
			se = smfu_maperr(scf_error());
		} else {
			smfu_entity_t entity = SMFU_ENTITY_INIT;
			se = smfu_lookup(rh_hdl(rh), sname, iname, &entity);
			smfu_entity_destroy(&entity);
		}

		if (se == SE_RECONNECT)
			rh_kill(rh);
		rh_rele(rh);
	} while (se == SE_RETRY || se == SE_RECONNECT);

	return (se);
}

/*
 * Construct the ADR name for a service/instance.
 */
adr_name_t *
smfu_name_alloc(const char *sname, const char *iname)
{
	if (iname != NULL)
		return (adr_name_vcreate(SMF_DOMAIN, 3,
		    SMF_KEY_TYPE, SMF_TYPE_INSTANCE,
		    SMF_KEY_SERVICE, sname,
		    SMF_KEY_INSTANCE, iname));
	return (adr_name_vcreate(SMF_DOMAIN, 2,
	    SMF_KEY_TYPE, SMF_TYPE_SERVICE,
	    SMF_KEY_SERVICE, sname));
}

/*
 * Construct the FMRI for a service/instance.
 */
char *
smfu_fmri_alloc(const char *sname, const char *iname)
{
	char *result = NULL;
	if (iname != NULL)
		(void) asprintf(&result, "svc:/%s:%s", sname, iname);
	else
		(void) asprintf(&result, "svc:/%s", sname);
	return (result);
}

void
smfu_obj_free(smfobj_t *obj)
{
	free(obj->sname);
	free(obj->iname);
	free(obj->fmri);
	free(obj);
}

smfobj_t *
smfu_obj_alloc(const char *sname, const char *iname)
{
	smfobj_t *smfo = rad_zalloc(sizeof (smfobj_t));
	if (smfo == NULL)
		return (NULL);

	if ((smfo->sname = strdup(sname)) == NULL ||
	    (iname != NULL && (smfo->iname = strdup(iname)) == NULL) ||
	    (smfo->fmri = smfu_fmri_alloc(sname, iname)) == NULL) {
		smfu_obj_free(smfo);
		return (NULL);
	}

	return (smfo);
}


/*
 * Automatic retry mechanism.
 *
 * Calls cb() repeatedly while it returns SE_RETRY, reconnecting to the
 * repository as necessary.
 *
 * For the convenience of the callback, if a data_t pointer is stored
 * in its result argument on failure it is freed.  Also verifies the
 * result on success.
 */
static conerr_t
smfu_rtrun_int(smfu_rtfunc_t cb, void *arg, data_t **ret, data_t **error,
    boolean_t nullable)
{
	svcerr_t se = SE_OK;
	data_t *result = NULL;

	do {
		rad_handle_t *rh = rh_fetch();
		if (rh == NULL)
			se = smfu_maperr(scf_error());
		else
			se = cb(rh_hdl(rh), arg, &result, error);

		if (se != SE_OK && result != NULL) {
			data_free(result);
			result = NULL;
		}

		if (se == SE_RECONNECT)
			rh_kill(rh);
		rh_rele(rh);
	} while (se == SE_RETRY || se == SE_RECONNECT);

	assert(ret != NULL || result == NULL);
	if (ret != NULL && se == SE_OK) {
		if ((nullable && result == NULL) ||
		    data_verify(result, NULL, B_TRUE)) {
			*ret = result;
		} else {
			data_free(result);
			se = internal_error(error, NULL);
		}
	}

	if (se == SE_OK)
		return (ce_ok);
	if (se == SE_STALE)
		return (ce_notfound);

	if (se == SE_FATAL || se == SE_NOTFOUND) {
		if (error != NULL && *error == NULL)
			(void) internal_error(error, NULL);
		return (ce_object);
	}

	/* Shouldn't be seeing SE_RETRY, SE_RECONNECT, SE_BREAK */
	rad_log(RL_FATAL, "smfu_rtrun: callback returned bad error: %d", se);
	return (ce_system);
}

conerr_t
smfu_rtrun_opt(smfu_rtfunc_t cb, void *arg, data_t **ret, data_t **error)
{
	return (smfu_rtrun_int(cb, arg, ret, error, B_TRUE));
}

conerr_t
smfu_rtrun(smfu_rtfunc_t cb, void *arg, data_t **ret, data_t **error)
{
	return (smfu_rtrun_int(cb, arg, ret, error, B_FALSE));
}


void
smfu_init()
{
	/*
	 * Initialize constants
	 */
	max_fmri = scf_limit(SCF_LIMIT_MAX_FMRI_LENGTH);
	max_pgtype = scf_limit(SCF_LIMIT_MAX_PG_TYPE_LENGTH);
	max_name = scf_limit(SCF_LIMIT_MAX_NAME_LENGTH);
	max_value = scf_limit(SCF_LIMIT_MAX_VALUE_LENGTH);
}
