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
 * Copyright (c) 2010, 2013, Oracle and/or its affiliates. All rights reserved.
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
#include <libscf.h>
#include <libscf_priv.h>
#include <rad/adr.h>
#include <rad/rad_modapi.h>

#include "api_smf_old.h"
#include "propvec.h"

static pthread_mutex_t service_lock = PTHREAD_MUTEX_INITIALIZER;
static list_t service_list;
static list_t instance_list;
static rad_instance_t *agg_inst;
static int service_count = 0;
static int instance_count = 0;

typedef struct servinst {
	char *sname;		/* Service name */
	char *iname;		/* Instance name */
	char *fmri;		/* FMRI */
	rad_instance_t *inst;	/* rad object instance */
	boolean_t instance;

	int ninstances;
	list_t instances;	/* A service's instances */
	list_node_t node;	/* Membership in the global list */
	list_node_t snode;	/* An instance's membership in its service */
} servinst_t;

static const char *framework_pgtypes[] = {
	SCF_GROUP_FRAMEWORK,
	SCF_GROUP_DEPENDENCY,
	SCF_GROUP_METHOD,
	SCF_GROUP_TEMPLATE,
	SCF_GROUP_TEMPLATE_PG_PATTERN,
	SCF_GROUP_TEMPLATE_PROP_PATTERN,
	NULL
};

static conerr_t
error_scf(adr_data_t **error, int code)
{
	if (error != NULL) {
		adr_data_t *e = adr_data_new_struct(&t__SmfError);
		adr_struct_set(e, "error",
		    adr_data_new_enum(&t__SmfErrorCode, code));
		adr_struct_set(e, "message",
		    adr_data_new_string(scf_strerror(code), LT_CONST));
		*error = adr_data_purify(e);
	}
	return (CE_OBJECT);
}

static conerr_t
simple_scf(adr_data_t **error, int result)
{
	if (result == 0)
		return (CE_OK);
	return (error_scf(error, scf_error()));
}

static boolean_t
strinset(const char **set, const char *str)
{
	for (; *set != NULL; set++)
		if (strcmp(*set, str) == 0)
			return (B_TRUE);
	return (B_FALSE);
}

static boolean_t
strnotinset(const char **set, const char *str)
{
	return (!strinset(set, str));
}

scf_handle_t *
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

static int getpgs(servinst_t *si, adr_data_t **data, boolean_t namesonly,
    boolean_t(*fp)(const char **, const char *), const char **set,
    adr_data_t **error)
{
	conerr_t err = CE_OK;
	scf_handle_t *scfhandle = handle_create();
	scf_service_t *service = scf_service_create(scfhandle);
	scf_instance_t *instance = scf_instance_create(scfhandle);
	scf_snapshot_t *snap = scf_snapshot_create(scfhandle);
	scf_iter_t *iter = scf_iter_create(scfhandle);
	scf_propertygroup_t *pg = scf_pg_create(scfhandle);

	if (scf_handle_decode_fmri(scfhandle, si->fmri, NULL, service,
	    instance, NULL, NULL, 0) != SCF_SUCCESS) {
		rad_log(RL_WARN, "Couldn't decode '%s': %s\n", si->fmri,
		    scf_strerror(scf_error()));
		err = error_scf(error, scf_error());
		goto out;
	}

	if (si->instance) {
		if (scf_instance_get_snapshot(instance, "running", snap) != 0 ||
		    scf_iter_instance_pgs_composed(iter, instance, snap)
		    != SCF_SUCCESS) {
			err = error_scf(error, scf_error());
			goto out;
		}
	} else {
		if (scf_iter_service_pgs(iter, service) != SCF_SUCCESS) {
			rad_log(RL_WARN, "failed to initialize iterator: %s\n",
			    scf_strerror(scf_error()));
			err = error_scf(error, scf_error());
			goto out;
		}
	}

	adr_data_t *result = namesonly ?
	    adr_data_new_array(&adr_t_array_string, 5) :
	    adr_data_new_array(&t_array__PropertyGroup, 5);
	while (scf_iter_next_pg(iter, pg) > 0) {
		char nbuf[1000];
		char tbuf[1000];
		(void) scf_pg_get_name(pg, nbuf, 1000);
		(void) scf_pg_get_type(pg, tbuf, 1000);

		if (fp(set, tbuf)) {
			if (namesonly) {
				(void) adr_array_add(result,
				    adr_data_new_string(nbuf, LT_COPY));
			} else {
				adr_data_t *pgdata =
				    adr_data_new_struct(&t__PropertyGroup);
				adr_struct_set(pgdata, "name",
				    adr_data_new_string(nbuf, LT_COPY));
				adr_struct_set(pgdata, "type",
				    adr_data_new_string(tbuf, LT_COPY));
				(void) adr_array_add(result, pgdata);
			}
		}
	}

	*data = result;

out:
	scf_pg_destroy(pg);
	scf_snapshot_destroy(snap);
	scf_iter_destroy(iter);
	scf_instance_destroy(instance);
	scf_service_destroy(service);
	scf_handle_destroy(scfhandle);

	return (err);
}

/* ARGSUSED */
conerr_t
interface_ServiceInfo_read_fmri(rad_instance_t *inst, adr_attribute_t *attr,
    adr_data_t **data, adr_data_t **error)
{
	servinst_t *si = rad_instance_getdata(inst);
	*data = adr_data_new_string(si->fmri, LT_COPY);
	return (CE_OK);
}

/* ARGSUSED */
conerr_t
interface_ServiceInfo_read_methodNames(rad_instance_t *inst,
    adr_attribute_t *attr, adr_data_t **data, adr_data_t **error)
{
	const char *pgtypes[] = { SCF_GROUP_METHOD, NULL };
	return (getpgs(rad_instance_getdata(inst), data, B_TRUE,
	    strinset, pgtypes, error));
}

/* ARGSUSED */
conerr_t
interface_ServiceInfo_read_dependencyNames(rad_instance_t *inst,
    adr_attribute_t *attr, adr_data_t **data, adr_data_t **error)
{
	const char *pgtypes[] = { SCF_GROUP_DEPENDENCY, NULL };
	return (getpgs(rad_instance_getdata(inst), data, B_TRUE,
	    strinset, pgtypes, error));
}

/* ARGSUSED */
conerr_t
interface_ServiceInfo_read_propertyGroups(rad_instance_t *inst,
    adr_attribute_t *attr, adr_data_t **data, adr_data_t **error)
{
	return (getpgs(rad_instance_getdata(inst), data, B_FALSE,
	    strnotinset, framework_pgtypes, error));
}

/* ARGSUSED */
conerr_t
interface_ServiceInfo_read_manpages(rad_instance_t *inst, adr_attribute_t *attr,
    adr_data_t **data, adr_data_t **error)
{
	servinst_t *si = rad_instance_getdata(inst);
	char *title, *section, *path;
	rad_propvec_t *badprop;
	rad_propvec_t evec[] = {
		{ SCF_PROPERTY_TM_MANPATH, NULL, SCF_TYPE_USTRING, &path, 0 },
		{ SCF_PROPERTY_TM_TITLE, NULL, SCF_TYPE_USTRING, &title, 0 },
		{ SCF_PROPERTY_TM_SECTION, NULL, SCF_TYPE_USTRING, &section,
		0 },
		{ NULL }
	};

	const char *pgtypes[] = {
		SCF_GROUP_TEMPLATE,
		NULL
	};

	adr_data_t *pgs;
	conerr_t err = getpgs(si, &pgs, B_TRUE, strinset, pgtypes, error);
	if (err != CE_OK)
		return (err);
	adr_data_t *result = adr_data_new_array(&t_array__Manpage, 5);
	for (int i = 0; i < adr_array_size(pgs); i++) {
		const char *str = adr_data_to_string(adr_array_get(pgs, i));
		if (strncmp(str, SCF_PG_TM_MAN_PREFIX,
		    strlen(SCF_PG_TM_MAN_PREFIX)) != 0) {
			continue;
		}

		if (rad_read_propvec(si->fmri, str, B_FALSE, evec,
		    &badprop) != 0)
			continue;

		adr_data_t *mp = adr_data_new_struct(&t__Manpage);
		adr_struct_set(mp, "title",
		    adr_data_new_string(title, LT_COPY));
		adr_struct_set(mp, "section",
		    adr_data_new_string(section, LT_COPY));
		adr_struct_set(mp, "path", adr_data_new_string(path, LT_COPY));
		(void) adr_array_add(result, mp);
		rad_clean_propvec(evec);
	}
	adr_data_free(pgs);
	*data = result;

	return (CE_OK);
}

/* ARGSUSED */
conerr_t
interface_ServiceInfo_read_doclinks(rad_instance_t *inst, adr_attribute_t *attr,
    adr_data_t **data, adr_data_t **error)
{
	servinst_t *si = rad_instance_getdata(inst);
	char *uri;
	rad_propvec_t *badprop;
	rad_propvec_t evec[] = {
		{ SCF_PROPERTY_TM_URI, NULL, SCF_TYPE_USTRING, &uri, 0 },
		{ NULL }
	};

	const char *pgtypes[] = {
		SCF_GROUP_TEMPLATE,
		NULL
	};

	adr_data_t *pgs;
	conerr_t err = getpgs(si, &pgs, B_TRUE, strinset, pgtypes, error);
	if (err != CE_OK)
		return (err);
	adr_data_t *result = adr_data_new_array(&adr_t_array_string, 5);
	for (int i = 0; i < adr_array_size(pgs); i++) {
		const char *str = adr_data_to_string(adr_array_get(pgs, i));
		if (strncmp(str, SCF_PG_TM_DOC_PREFIX,
		    strlen(SCF_PG_TM_DOC_PREFIX)) != 0) {
			continue;
		}

		if (rad_read_propvec(si->fmri, str, B_FALSE, evec,
		    &badprop) == 0) {
			(void) adr_array_add(result,
			    adr_data_new_string(uri, LT_COPY));
			rad_clean_propvec(evec);
		}
	}
	adr_data_free(pgs);
	*data = result;

	return (CE_OK);
}

/* ARGSUSED */
conerr_t
interface_ServiceInfo_read_persistentlyEnabled(rad_instance_t *inst,
    adr_attribute_t *attr, adr_data_t **data, adr_data_t **error)
{
	servinst_t *si = rad_instance_getdata(inst);
	if (!si->instance)
		return (error_scf(error, SCF_ERROR_INVALID_ARGUMENT));

	boolean_t enabled;
	rad_propvec_t evec[] = {
		{ SCF_PROPERTY_ENABLED, NULL, SCF_TYPE_BOOLEAN, &enabled, 0 },
		{ NULL }
	};

	rad_propvec_t *badprop;
	int scferr = rad_read_propvec(si->fmri, SCF_PG_GENERAL, B_FALSE,
	    evec, &badprop);
	if (scferr != 0)
		return (error_scf(error, scferr));
	rad_clean_propvec(evec);

	*data = adr_data_new_boolean(enabled);
	return (CE_OK);
}

/* ARGSUSED */
conerr_t
interface_ServiceInfo_read_temporarilyEnabled(rad_instance_t *inst,
    adr_attribute_t *attr, adr_data_t **data, adr_data_t **error)
{
	servinst_t *si = rad_instance_getdata(inst);
	if (!si->instance)
		return (error_scf(error, SCF_ERROR_INVALID_ARGUMENT));

	boolean_t enabled;
	rad_propvec_t evec[] = {
		{ SCF_PROPERTY_ENABLED, NULL, SCF_TYPE_BOOLEAN, &enabled, 0 },
		{ NULL }
	};

	rad_propvec_t *badprop;
	if (rad_read_propvec(si->fmri, SCF_PG_GENERAL_OVR, B_FALSE, evec,
	    &badprop) != 0)
		return (interface_ServiceInfo_read_persistentlyEnabled(
		    inst, attr, data, error));
	rad_clean_propvec(evec);

	*data = adr_data_new_boolean(enabled);
	return (CE_OK);
}

/* ARGSUSED */
conerr_t
interface_ServiceInfo_read_enabled(rad_instance_t *inst, adr_attribute_t *attr,
    adr_data_t **data, adr_data_t **error)
{
	/*
	 * XXX: The java version always had the same implementation for both.
	 */
	return (interface_ServiceInfo_read_persistentlyEnabled(inst, attr, data,
	    error));
}

/* ARGSUSED */
conerr_t
interface_ServiceInfo_read_instance(rad_instance_t *inst, adr_attribute_t *attr,
    adr_data_t **data, adr_data_t **error)
{
	servinst_t *si = rad_instance_getdata(inst);
	*data = adr_data_new_boolean(si->instance);
	return (CE_OK);
}

/* ARGSUSED */
conerr_t
interface_ServiceInfo_read_restarter(rad_instance_t *inst,
    adr_attribute_t *attr, adr_data_t **data, adr_data_t **error)
{
	servinst_t *si = rad_instance_getdata(inst);
	if (!si->instance)
		return (error_scf(error, SCF_ERROR_INVALID_ARGUMENT));

	char *fmri = NULL;
	rad_propvec_t evec[] = {
		{ SCF_PROPERTY_RESTARTER, NULL, SCF_TYPE_USTRING, &fmri, 0 },
		{ NULL }
	};

	rad_propvec_t *badprop;
	if (rad_read_propvec(si->fmri, SCF_PG_GENERAL, B_FALSE, evec,
	    &badprop) == 0) {
		*data = adr_data_new_string(fmri, LT_COPY);
		rad_clean_propvec(evec);
	} else {
		*data = adr_data_new_fstring("svc:/%s:%s",
		    "system/svc/restarter", "default");
	}

	return (*data != NULL ? CE_OK : CE_SYSTEM);
}

static adr_data_t *
state2enum(const char *state)
{
	if (strcmp(state, SCF_STATE_STRING_UNINIT) == 0) {
		return (&e__SmfState_UNINIT);
	} else if (strcmp(state, SCF_STATE_STRING_MAINT) == 0) {
		return (&e__SmfState_MAINT);
	} else if (strcmp(state, SCF_STATE_STRING_LEGACY) == 0) {
		return (&e__SmfState_LEGACY);
	} else {
		return (adr_data_new_enum_byname(&t__SmfState, state));
	}
}

/* ARGSUSED */
conerr_t
interface_ServiceInfo_read_state(rad_instance_t *inst, adr_attribute_t *attr,
    adr_data_t **data, adr_data_t **error)
{
	servinst_t *si = rad_instance_getdata(inst);
	if (!si->instance)
		return (error_scf(error, SCF_ERROR_INVALID_ARGUMENT));

	char *state = smf_get_state(si->fmri);
	if (state == NULL)
		return (error_scf(error, scf_error()));

	*data = state2enum(state);
	free(state);
	return (*data != NULL ? CE_OK : CE_SYSTEM);
}

/* ARGSUSED */
conerr_t
interface_ServiceInfo_read_nextState(rad_instance_t *inst,
    adr_attribute_t *attr, adr_data_t **data, adr_data_t **error)
{
	servinst_t *si = rad_instance_getdata(inst);
	if (!si->instance)
		return (error_scf(error, SCF_ERROR_INVALID_ARGUMENT));

	char *state = NULL;
	rad_propvec_t evec[] = {
		{ SCF_PROPERTY_NEXT_STATE, NULL, SCF_TYPE_ASTRING, &state, 0 },
		{ NULL }
	};

	rad_propvec_t *badprop;
	int scferr = rad_read_propvec(si->fmri, SCF_PG_RESTARTER, B_FALSE, evec,
	    &badprop);
	if (scferr != 0)
		return (error_scf(error, scferr));

	*data = state2enum(state);
	rad_clean_propvec(evec);
	return (*data != NULL ? CE_OK : CE_SYSTEM);
}

/* ARGSUSED */
conerr_t
interface_ServiceInfo_read_auxiliaryState(rad_instance_t *inst,
    adr_attribute_t *attr, adr_data_t **data, adr_data_t **error)
{
	servinst_t *si = rad_instance_getdata(inst);
	if (!si->instance)
		return (error_scf(error, SCF_ERROR_INVALID_ARGUMENT));

	char *aux;
	rad_propvec_t evec[] = {
		{ SCF_PROPERTY_AUX_STATE, NULL, SCF_TYPE_ASTRING, &aux, 0 },
		{ NULL }
	};

	rad_propvec_t *badprop;
	int scferr = rad_read_propvec(si->fmri, SCF_PG_RESTARTER, B_FALSE, evec,
	    &badprop);
	if (scferr != 0) {
		if (scferr == SCF_ERROR_NOT_FOUND) {
			*data = NULL;
			return (CE_OK);
		}
		return (error_scf(error, scferr));
	}

	*data = adr_data_new_string(aux, LT_COPY);
	rad_clean_propvec(evec);

	return (*data != NULL ? CE_OK : CE_SYSTEM);
}

/* ARGSUSED */
conerr_t
interface_ServiceInfo_read_stime(rad_instance_t *inst, adr_attribute_t *attr,
    adr_data_t **data, adr_data_t **error)
{
	servinst_t *si = rad_instance_getdata(inst);
	if (!si->instance)
		return (error_scf(error, SCF_ERROR_INVALID_ARGUMENT));

	scf_time_t time;
	rad_propvec_t evec[] = {
		{ SCF_PROPERTY_STATE_TIMESTAMP, NULL, SCF_TYPE_TIME, &time, 0 },
		{ NULL }
	};

	rad_propvec_t *badprop;
	int scferr = rad_read_propvec(si->fmri, SCF_PG_RESTARTER, B_FALSE, evec,
	    &badprop);
	if (scferr != 0)
		return (error_scf(error, scferr));

	rad_clean_propvec(evec);

	*data = adr_data_new_time(time.t_seconds, time.t_ns);

	return (*data != NULL ? CE_OK : CE_SYSTEM);
}

/* ARGSUSED */
conerr_t
interface_ServiceInfo_read_contractID(rad_instance_t *inst,
    adr_attribute_t *attr, adr_data_t **data, adr_data_t **error)
{
	servinst_t *si = rad_instance_getdata(inst);
	if (!si->instance)
		return (error_scf(error, SCF_ERROR_INVALID_ARGUMENT));

	uint64_t count;
	rad_propvec_t evec[] = {
		{ SCF_PROPERTY_CONTRACT, NULL, SCF_TYPE_COUNT, &count, 0 },
		{ NULL }
	};

	rad_propvec_t *badprop;
	int scferr = rad_read_propvec(si->fmri, SCF_PG_RESTARTER, B_FALSE, evec,
	    &badprop);
	if (scferr != 0)
		return (error_scf(error, scferr));
	rad_clean_propvec(evec);

	*data = adr_data_new_long(count);

	return (*data != NULL ? CE_OK : CE_SYSTEM);
}

/* ARGSUSED */
conerr_t
interface_ServiceInfo_read_reason(rad_instance_t *inst, adr_attribute_t *attr,
    adr_data_t **data, adr_data_t **error)
{
	servinst_t *si = rad_instance_getdata(inst);
	if (!si->instance)
		return (error_scf(error, SCF_ERROR_INVALID_ARGUMENT));
	*data = NULL;
	return (CE_OK);
}

/* ARGSUSED */
conerr_t
interface_ServiceInfo_write_persistentlyEnabled(rad_instance_t *inst,
    adr_attribute_t *attr, adr_data_t *data, adr_data_t **error)
{
	servinst_t *si = rad_instance_getdata(inst);
	boolean_t enable = adr_data_to_boolean(data);
	if (!si->instance)
		return (error_scf(error, SCF_ERROR_INVALID_ARGUMENT));

	return (simple_scf(error, enable ? smf_enable_instance(si->fmri, 0) :
	    smf_disable_instance(si->fmri, 0)));
}

static conerr_t
get_pg(scf_handle_t *scfhandle, scf_propertygroup_t *pg, servinst_t *si,
    const char *snapname, const char *pgname, adr_data_t **error)
{
	conerr_t err = CE_OK;
	scf_service_t *service = scf_service_create(scfhandle);
	scf_instance_t *instance = scf_instance_create(scfhandle);
	scf_snapshot_t *snap = scf_snapshot_create(scfhandle);

	if (service == NULL || instance == NULL || snap == NULL) {
		err = error_scf(error, SCF_ERROR_NO_MEMORY);
		goto out;
	}

	if (scf_handle_decode_fmri(scfhandle, si->fmri, NULL, service,
	    instance, NULL, NULL, 0) != SCF_SUCCESS) {
		rad_log(RL_WARN, "Couldn't decode '%s': %s\n",
		    si->fmri, scf_strerror(scf_error()));
		err = error_scf(error, scf_error());
		goto out;
	}

	if (si->instance) {
		scf_snapshot_t *usesnap = NULL;
		if (snapname != NULL) {
			usesnap = snap;
			if (scf_instance_get_snapshot(instance, snapname, snap)
			    != 0) {
				err = error_scf(error, scf_error());
				goto out;
			}
		}
		if (scf_instance_get_pg_composed(instance, usesnap, pgname, pg)
		    != 0) {
			err = error_scf(error, scf_error());
			goto out;
		}
	} else {
		if (scf_service_get_pg(service, pgname, pg) != SCF_SUCCESS) {
			err = error_scf(error, scf_error());
			goto out;
		}
	}
out:
	scf_snapshot_destroy(snap);
	scf_instance_destroy(instance);
	scf_service_destroy(service);
	return (err);
}

/* ARGSUSED */
conerr_t
interface_ServiceInfo_invoke_getDependency(rad_instance_t *inst,
    adr_method_t *meth, adr_data_t **ret, adr_data_t **args, int count,
    adr_data_t **error)
{
	conerr_t err = CE_OK;
	const char *pgname = adr_data_to_string(args[0]);
	servinst_t *si = rad_instance_getdata(inst);
	char type[1000];
	char grouping[1000];
	char restarton[1000];

	scf_handle_t *scfhandle = handle_create();
	scf_iter_t *iter = scf_iter_create(scfhandle);
	scf_propertygroup_t *pg = scf_pg_create(scfhandle);
	scf_property_t *prop = scf_property_create(scfhandle);
	scf_value_t *val = scf_value_create(scfhandle);

	if (scfhandle == NULL || iter == NULL || pg == NULL || prop == NULL ||
	    val == NULL) {
		err = error_scf(error, SCF_ERROR_NO_MEMORY);
		goto out;
	}
	if ((err = get_pg(scfhandle, pg, si, "running", pgname, error))
	    != CE_OK)
		goto out;

	if (scf_pg_get_type(pg, type, sizeof (type)) == 0) {
		err = error_scf(error, scf_error());
		goto out;
	}
	if (strcmp(type, SCF_GROUP_DEPENDENCY) != 0) {
		err = error_scf(error, SCF_ERROR_INVALID_ARGUMENT);
		goto out;
	}

	if (scf_pg_get_property(pg, SCF_PROPERTY_GROUPING, prop) != 0 ||
	    scf_property_get_value(prop, val) != 0 ||
	    scf_value_get_as_string(val, grouping, sizeof (grouping)) == -1 ||
	    scf_pg_get_property(pg, SCF_PROPERTY_RESTART_ON, prop) != 0 ||
	    scf_property_get_value(prop, val) != 0 ||
	    scf_value_get_as_string(val, restarton, sizeof (restarton)) == -1 ||
	    scf_pg_get_property(pg, SCF_PROPERTY_ENTITIES, prop) != 0 ||
	    scf_iter_property_values(iter, prop) != 0) {
		err = error_scf(error, scf_error());
		goto out;
	}

	adr_data_t *result = adr_data_new_struct(&t__Dependency);
	adr_data_t *array = adr_data_new_array(&adr_t_array_string, 5);
	adr_struct_set(result, "name", adr_data_ref(args[0]));
	adr_struct_set(result, "grouping",
	    adr_data_new_string(grouping, LT_COPY));
	adr_struct_set(result, "restartOn",
	    adr_data_new_string(restarton, LT_COPY));
	adr_struct_set(result, "target", array);
	while (scf_iter_next_value(iter, val) > 0) {
		if (scf_value_get_as_string(val, type, sizeof (type)) == -1) {
			err = error_scf(error, scf_error());
			adr_data_free(result);
			goto out;
		}
		(void) adr_array_add(array, adr_data_new_string(type, LT_COPY));
	}
	if (!adr_data_verify(result, NULL, B_TRUE)) {
		adr_data_free(result);
		err = error_scf(error, SCF_ERROR_NO_MEMORY);
		goto out;
	}

	*ret = result;
out:
	scf_value_destroy(val);
	scf_property_destroy(prop);
	scf_pg_destroy(pg);
	scf_iter_destroy(iter);
	scf_handle_destroy(scfhandle);
	return (err);
}

/* ARGSUSED */
conerr_t
interface_ServiceInfo_invoke_getPropertyNames(rad_instance_t *inst,
    adr_method_t *meth, adr_data_t **ret, adr_data_t **args, int count,
    adr_data_t **error)
{
	conerr_t err = CE_OK;
	const char *pgname = adr_data_to_string(args[0]);
	servinst_t *si = rad_instance_getdata(inst);

	scf_handle_t *scfhandle = handle_create();
	scf_iter_t *iter = scf_iter_create(scfhandle);
	scf_propertygroup_t *pg = scf_pg_create(scfhandle);
	scf_property_t *prop = scf_property_create(scfhandle);

	if (scfhandle == NULL || iter == NULL || pg == NULL || prop == NULL) {
		err = error_scf(error, SCF_ERROR_NO_MEMORY);
		goto out;
	}

	if ((err = get_pg(scfhandle, pg, si, "running", pgname, error))
	    != CE_OK)
		goto out;

	adr_data_t *result = adr_data_new_array(&adr_t_array_string, 5);
	(void) scf_iter_pg_properties(iter, pg);
	while (scf_iter_next_property(iter, prop) > 0) {
		char pbuf[1000];
		(void) scf_property_get_name(prop, pbuf, 1000);
		(void) adr_array_add(result,
		    adr_data_new_string(pbuf, LT_COPY));
	}
	*ret = result;

out:
	scf_property_destroy(prop);
	scf_pg_destroy(pg);
	scf_iter_destroy(iter);
	scf_handle_destroy(scfhandle);

	return (err);
}

/* ARGSUSED */
conerr_t
interface_ServiceInfo_invoke_getPropertyType(rad_instance_t *inst,
    adr_method_t *meth, adr_data_t **ret, adr_data_t **args, int count,
    adr_data_t **error)
{
	const char *pgname = adr_data_to_string(args[0]);
	const char *propname = adr_data_to_string(args[1]);
	conerr_t err = CE_OK;
	servinst_t *si = rad_instance_getdata(inst);

	scf_handle_t *scfhandle = handle_create();
	scf_propertygroup_t *pg = scf_pg_create(scfhandle);
	scf_property_t *prop = scf_property_create(scfhandle);
	scf_type_t type;

	if (scfhandle == NULL || pg == NULL || prop == NULL) {
		err = error_scf(error, SCF_ERROR_NO_MEMORY);
		goto out;
	}
	if ((err = get_pg(scfhandle, pg, si, "running", pgname, error))
	    != CE_OK)
		goto out;

	if (scf_pg_get_property(pg, propname, prop) != 0 ||
	    scf_property_type(prop, &type) != 0) {
		err = error_scf(error, scf_error());
		goto out;
	}

	adr_data_t *result = adr_data_new_enum(&t__PropertyType, type);
	if (result != NULL)
		*ret = result;
	else
		err = error_scf(error, SCF_ERROR_NO_MEMORY);

out:
	scf_property_destroy(prop);
	scf_pg_destroy(pg);
	scf_handle_destroy(scfhandle);
	return (err);
}

/* ARGSUSED */
conerr_t
interface_ServiceInfo_invoke_getPropertyValues(rad_instance_t *inst,
    adr_method_t *meth, adr_data_t **ret, adr_data_t **args, int count,
    adr_data_t **error)
{
	conerr_t err = CE_OK;
	const char *pgname = adr_data_to_string(args[0]);
	const char *propname = adr_data_to_string(args[1]);

	servinst_t *si = rad_instance_getdata(inst);

	scf_handle_t *scfhandle = handle_create();
	scf_service_t *service = scf_service_create(scfhandle);
	scf_instance_t *instance = scf_instance_create(scfhandle);
	scf_snapshot_t *snap = scf_snapshot_create(scfhandle);
	scf_iter_t *iter = scf_iter_create(scfhandle);
	scf_propertygroup_t *pg = scf_pg_create(scfhandle);
	scf_property_t *prop = scf_property_create(scfhandle);
	scf_value_t *val = scf_value_create(scfhandle);

	if (scfhandle == NULL || service == NULL || instance == NULL ||
	    snap == NULL || iter == NULL || pg == NULL || prop == NULL ||
	    prop == NULL || val == NULL) {
		err = error_scf(error, SCF_ERROR_NO_MEMORY);
		goto out;
	}

	if (scf_handle_decode_fmri(scfhandle, si->fmri, NULL, service,
	    instance, NULL, NULL, 0) != SCF_SUCCESS) {
		rad_log(RL_WARN, "Couldn't decode '%s': %s\n",
		    si->fmri, scf_strerror(scf_error()));
		err = error_scf(error, scf_error());
		goto out;
	}
	if ((si->instance ? scf_instance_get_pg(instance, pgname, pg) :
	    scf_service_get_pg(service, pgname, pg)) != 0 ||
	    scf_pg_get_property(pg, propname, prop) != 0 ||
	    scf_iter_property_values(iter, prop) != 0) {
		err = error_scf(error, scf_error());
		goto out;
	}

	adr_data_t *result = adr_data_new_array(&adr_t_array_string, 5);
	while (scf_iter_next_value(iter, val) > 0) {
		char pbuf[1000];
		(void) scf_value_get_as_string(val, pbuf, 1000);
		(void) adr_array_add(result,
		    adr_data_new_string(pbuf, LT_COPY));
	}
	*ret = result;
out:
	scf_value_destroy(val);
	scf_property_destroy(prop);
	scf_pg_destroy(pg);
	scf_iter_destroy(iter);
	scf_snapshot_destroy(snap);
	scf_instance_destroy(instance);
	scf_service_destroy(service);
	scf_handle_destroy(scfhandle);

	return (err);
}

/* ARGSUSED */
conerr_t
interface_ServiceInfo_invoke_getSnapshotPropertyValues(rad_instance_t *inst,
    adr_method_t *meth, adr_data_t **ret, adr_data_t **args, int count,
    adr_data_t **error)
{
	conerr_t err = CE_OK;
	const char *snapname = adr_data_to_string(args[0]);
	const char *pgname = adr_data_to_string(args[1]);
	const char *propname = adr_data_to_string(args[2]);

	servinst_t *si = rad_instance_getdata(inst);
	if (!si->instance)
		return (error_scf(error, SCF_ERROR_INVALID_ARGUMENT));

	rad_log(RL_DEBUG, "Reading from snapshot: %s\n", snapname);

	scf_handle_t *scfhandle = handle_create();
	scf_iter_t *iter = scf_iter_create(scfhandle);
	scf_propertygroup_t *pg = scf_pg_create(scfhandle);
	scf_property_t *prop = scf_property_create(scfhandle);
	scf_value_t *val = scf_value_create(scfhandle);

	if (scfhandle == NULL || iter == NULL || pg == NULL || prop == NULL ||
	    val == NULL) {
		err = error_scf(error, SCF_ERROR_NO_MEMORY);
		goto out;
	}

	if ((err = get_pg(scfhandle, pg, si, "running", pgname, error))
	    != CE_OK)
		goto out;
	if (scf_pg_get_property(pg, propname, prop) != 0) {
		err = error_scf(error, scf_error());
		goto out;
	}

	adr_data_t *result = adr_data_new_array(&adr_t_array_string, 5);
	(void) scf_iter_property_values(iter, prop);
	while (scf_iter_next_value(iter, val) > 0) {
		char pbuf[1000];
		(void) scf_value_get_as_string(val, pbuf, 1000);
		(void) adr_array_add(result,
		    adr_data_new_string(pbuf, LT_COPY));
	}
	*ret = result;
out:
	scf_value_destroy(val);
	scf_property_destroy(prop);
	scf_pg_destroy(pg);
	scf_iter_destroy(iter);
	scf_handle_destroy(scfhandle);

	return (err);
}

/* ARGSUSED */
conerr_t
interface_ServiceInfo_invoke_setPropertyValues(rad_instance_t *inst,
    adr_method_t *meth, adr_data_t **ret, adr_data_t **args, int count,
    adr_data_t **error)
{
	conerr_t err = CE_OK;
	const char *pgname = adr_data_to_string(args[0]);
	const char *propname = adr_data_to_string(args[1]);
	adr_data_t *values = args[2];

	servinst_t *si = rad_instance_getdata(inst);

	scf_handle_t *scfhandle = handle_create();
	scf_service_t *service = scf_service_create(scfhandle);
	scf_instance_t *instance = scf_instance_create(scfhandle);
	scf_propertygroup_t *pg = scf_pg_create(scfhandle);
	scf_property_t *prop = scf_property_create(scfhandle);
	scf_transaction_t *tx = scf_transaction_create(scfhandle);
	scf_transaction_entry_t *ent = scf_entry_create(scfhandle);
	scf_value_t **val =
	    rad_zalloc(adr_array_size(values) * sizeof (scf_value_t *));
	scf_type_t type;

	if (scfhandle == NULL || service == NULL || instance == NULL ||
	    pg == NULL || prop == NULL || tx == NULL || ent == NULL ||
	    val == NULL) {
		err = error_scf(error, SCF_ERROR_NO_MEMORY);
		goto out;
	}

	for (int i = 0; i < adr_array_size(values); i++) {
		if ((val[i] = scf_value_create(scfhandle)) == NULL) {
			err = error_scf(error, SCF_ERROR_NO_MEMORY);
			goto out;
		}
	}

	if (scf_handle_decode_fmri(scfhandle, si->fmri, NULL, service,
	    instance, NULL, NULL, 0) != SCF_SUCCESS) {
		rad_log(RL_WARN, "Couldn't decode '%s': %s\n",
		    si->fmri, scf_strerror(scf_error()));
		err = error_scf(error, scf_error());
		goto out;
	}

	if (si->instance) {
		/* XXX: silly logic from original java */
		if (scf_instance_get_pg(instance, pgname, pg) != 0 &&
		    scf_service_get_pg(service, pgname, pg) != 0) {
			err = error_scf(error, scf_error());
			goto out;
		}
	} else {
		if (scf_service_get_pg(service, pgname, pg) != 0) {
			err = error_scf(error, scf_error());
			goto out;
		}
	}

	if (scf_pg_get_property(pg, propname, prop) != 0 ||
	    scf_property_type(prop, &type) != 0) {
		err = error_scf(error, scf_error());
		goto out;
	}

top:
	if (scf_transaction_start(tx, pg) == -1) {
		err = error_scf(error, scf_error());
		goto out;
	}
	if (scf_transaction_property_change(tx, ent, propname, type) != 0) {
		err = error_scf(error, scf_error());
		goto out;
	}

	for (int i = 0; i < adr_array_size(values); i++) {
		if (scf_value_set_from_string(val[i], type,
		    adr_data_to_string(adr_array_get(values, i))) != 0 ||
		    scf_entry_add_value(ent, val[i]) != 0) {
			err = error_scf(error, scf_error());
			goto out;
		}
	}

	int txret = scf_transaction_commit(tx);
	if (txret == 1)
		goto out;
	if (txret == 0 && scf_pg_update(pg) != -1) {
		scf_transaction_reset(tx);
		goto top;
	}
	err = error_scf(error, scf_error());

out:
	if (val != NULL) {
		for (int i = 0; i < adr_array_size(values); i++) {
			if (val[i] == NULL)
				break;
			scf_value_destroy(val[i]);
		}
		free(val);
	}

	scf_entry_destroy(ent);
	scf_transaction_destroy(tx);
	scf_property_destroy(prop);
	scf_pg_destroy(pg);
	scf_instance_destroy(instance);
	scf_service_destroy(service);
	scf_handle_destroy(scfhandle);

	return (err);
}

/* ARGSUSED */
conerr_t
interface_ServiceInfo_invoke_createPropertyGroup(rad_instance_t *inst,
    adr_method_t *meth, adr_data_t **ret, adr_data_t **args, int count,
    adr_data_t **error)
{
	conerr_t err = CE_OK;
	const char *pgname = adr_data_to_string(args[0]);
	const char *pgtype = adr_data_to_string(args[1]);

	servinst_t *si = rad_instance_getdata(inst);

	scf_handle_t *scfhandle = handle_create();
	scf_service_t *service = scf_service_create(scfhandle);
	scf_instance_t *instance = scf_instance_create(scfhandle);
	scf_propertygroup_t *pg = scf_pg_create(scfhandle);

	if (scfhandle == NULL || service == NULL || instance == NULL ||
	    pg == NULL) {
		err = error_scf(error, SCF_ERROR_NO_MEMORY);
		goto out;
	}

	if (scf_handle_decode_fmri(scfhandle, si->fmri, NULL, service,
	    instance, NULL, NULL, 0) != SCF_SUCCESS) {
		rad_log(RL_WARN, "Couldn't decode '%s': %s\n",
		    si->fmri, scf_strerror(scf_error()));
		err = error_scf(error, scf_error());
		goto out;
	}

	if (si->instance) {
		if (scf_instance_add_pg(instance, pgname, pgtype, 0, pg) != 0) {
			err = error_scf(error, scf_error());
			goto out;
		}
	} else {
		if (scf_service_add_pg(service, pgname, pgtype, 0, pg) != 0) {
			err = error_scf(error, scf_error());
			goto out;
		}
	}

out:
	scf_pg_destroy(pg);
	scf_instance_destroy(instance);
	scf_service_destroy(service);
	scf_handle_destroy(scfhandle);

	return (err);
}

/* ARGSUSED */
conerr_t
interface_ServiceInfo_invoke_deletePropertyGroup(rad_instance_t *inst,
    adr_method_t *meth, adr_data_t **ret, adr_data_t **args, int count,
    adr_data_t **error)
{
	conerr_t err = CE_OK;
	const char *pgname = adr_data_to_string(args[0]);

	servinst_t *si = rad_instance_getdata(inst);

	scf_handle_t *scfhandle = handle_create();
	scf_service_t *service = scf_service_create(scfhandle);
	scf_instance_t *instance = scf_instance_create(scfhandle);
	scf_propertygroup_t *pg = scf_pg_create(scfhandle);

	if (scfhandle == NULL || service == NULL || instance == NULL ||
	    pg == NULL) {
		err = error_scf(error, SCF_ERROR_NO_MEMORY);
		goto out;
	}

	if (scf_handle_decode_fmri(scfhandle, si->fmri, NULL, service,
	    instance, NULL, NULL, 0) != SCF_SUCCESS) {
		rad_log(RL_WARN, "Couldn't decode '%s': %s\n",
		    si->fmri, scf_strerror(scf_error()));
		err = error_scf(error, scf_error());
		goto out;
	}

	if (si->instance) {
		/* XXX: silly logic from original java */
		if (scf_instance_get_pg(instance, pgname, pg) != 0 &&
		    scf_service_get_pg(service, pgname, pg) != 0) {
			err = error_scf(error, scf_error());
			goto out;
		}
	} else {
		if (scf_service_get_pg(service, pgname, pg) != 0) {
			err = error_scf(error, scf_error());
			goto out;
		}
	}

	if (scf_pg_delete(pg) != 0) {
		err = error_scf(error, scf_error());
		goto out;
	}
out:
	scf_pg_destroy(pg);
	scf_instance_destroy(instance);
	scf_service_destroy(service);
	scf_handle_destroy(scfhandle);

	return (err);
}

/* ARGSUSED */
conerr_t
interface_ServiceInfo_invoke_createProperty(rad_instance_t *inst,
    adr_method_t *meth, adr_data_t **ret, adr_data_t **args, int count,
    adr_data_t **error)
{
	conerr_t err = CE_OK;
	const char *pgname = adr_data_to_string(args[0]);
	const char *propname = adr_data_to_string(args[1]);
	scf_type_t type = adr_enum_tovalue(args[2]);
	int sret;

	servinst_t *si = rad_instance_getdata(inst);

	scf_handle_t *scfhandle = handle_create();
	scf_service_t *service = scf_service_create(scfhandle);
	scf_instance_t *instance = scf_instance_create(scfhandle);
	scf_propertygroup_t *pg = scf_pg_create(scfhandle);
	scf_transaction_t *tx = scf_transaction_create(scfhandle);
	scf_transaction_entry_t *ent = scf_entry_create(scfhandle);

	if (scfhandle == NULL || service == NULL || instance == NULL ||
	    pg == NULL || tx == NULL || ent == NULL) {
		err = error_scf(error, SCF_ERROR_NO_MEMORY);
		goto out;
	}

	if (scf_handle_decode_fmri(scfhandle, si->fmri, NULL, service,
	    instance, NULL, NULL, 0) != SCF_SUCCESS) {
		rad_log(RL_WARN, "Couldn't decode '%s': %s\n",
		    si->fmri, scf_strerror(scf_error()));
		err = error_scf(error, scf_error());
		goto out;
	}

	if (si->instance) {
		/* XXX: silly logic from original java */
		if (scf_instance_get_pg(instance, pgname, pg) != 0 &&
		    scf_service_get_pg(service, pgname, pg) != 0) {
			err = error_scf(error, scf_error());
			goto out;
		}
	} else {
		if (scf_service_get_pg(service, pgname, pg) != 0) {
			err = error_scf(error, scf_error());
			goto out;
		}
	}

top:
	if (scf_transaction_start(tx, pg) == -1) {
		err = error_scf(error, scf_error());
		goto out;
	}
	sret = scf_transaction_property_change(tx, ent, propname, type);
	if (sret == -1 && scf_error() == SCF_ERROR_NOT_FOUND)
		sret = scf_transaction_property_new(tx, ent, propname, type);
	if (sret == -1) {
		err = error_scf(error, scf_error());
		goto out;
	}

	sret = scf_transaction_commit(tx);
	if (sret == 1)
		goto out;
	if (sret == 0 && scf_pg_update(pg) != -1) {
		scf_transaction_reset(tx);
		goto top;
	}
	err = error_scf(error, scf_error());

out:
	scf_entry_destroy(ent);
	scf_transaction_destroy(tx);
	scf_pg_destroy(pg);
	scf_instance_destroy(instance);
	scf_service_destroy(service);
	scf_handle_destroy(scfhandle);

	return (err);
}

/* ARGSUSED */
conerr_t
interface_ServiceInfo_invoke_deleteProperty(rad_instance_t *inst,
    adr_method_t *meth, adr_data_t **ret, adr_data_t **args, int count,
    adr_data_t **error)
{
	conerr_t err = CE_OK;
	const char *pgname = adr_data_to_string(args[0]);
	const char *propname = adr_data_to_string(args[1]);
	int sret;

	servinst_t *si = rad_instance_getdata(inst);

	scf_handle_t *scfhandle = handle_create();
	scf_service_t *service = scf_service_create(scfhandle);
	scf_instance_t *instance = scf_instance_create(scfhandle);
	scf_propertygroup_t *pg = scf_pg_create(scfhandle);
	scf_transaction_t *tx = scf_transaction_create(scfhandle);
	scf_transaction_entry_t *ent = scf_entry_create(scfhandle);

	if (scfhandle == NULL || service == NULL || instance == NULL ||
	    pg == NULL || tx == NULL || ent == NULL) {
		err = error_scf(error, SCF_ERROR_NO_MEMORY);
		goto out;
	}

	if (scf_handle_decode_fmri(scfhandle, si->fmri, NULL, service,
	    instance, NULL, NULL, 0) != SCF_SUCCESS) {
		rad_log(RL_WARN, "Couldn't decode '%s': %s\n",
		    si->fmri, scf_strerror(scf_error()));
		err = error_scf(error, scf_error());
		goto out;
	}

	if (si->instance) {
		/* XXX: really, really silly logic from original java */
		if (scf_instance_get_pg(instance, pgname, pg) != 0 &&
		    scf_service_get_pg(service, pgname, pg) != 0) {
			err = error_scf(error, scf_error());
			goto out;
		}
	} else {
		if (scf_service_get_pg(service, pgname, pg) != 0) {
			err = error_scf(error, scf_error());
			goto out;
		}
	}

top:
	if (scf_transaction_start(tx, pg) == -1) {
		err = error_scf(error, scf_error());
		goto out;
	}
	if (scf_transaction_property_delete(tx, ent, propname) != 0) {
		err = error_scf(error, scf_error());
		goto out;
	}

	sret = scf_transaction_commit(tx);
	if (sret == 1)
		goto out;
	if (sret == 0 && scf_pg_update(pg) != -1) {
		scf_transaction_reset(tx);
		goto top;
	}
	err = error_scf(error, scf_error());

out:
	scf_entry_destroy(ent);
	scf_transaction_destroy(tx);
	scf_pg_destroy(pg);
	scf_instance_destroy(instance);
	scf_service_destroy(service);
	scf_handle_destroy(scfhandle);

	return (err);
}

/* ARGSUSED */
conerr_t
interface_ServiceInfo_invoke_getPropertyTemplate(rad_instance_t *inst,
    adr_method_t *meth, adr_data_t **ret, adr_data_t **args, int count,
    adr_data_t **error)
{
	conerr_t err = CE_OK;
	const char *pgname = adr_data_to_string(args[0]);
	const char *propname = adr_data_to_string(args[1]);
	const char *locale = adr_data_to_string(args[2]);

	servinst_t *si = rad_instance_getdata(inst);
	scf_handle_t *scfhandle = handle_create();
	scf_pg_tmpl_t *pgtmpl = scf_tmpl_pg_create(scfhandle);
	scf_prop_tmpl_t *proptmpl = scf_tmpl_prop_create(scfhandle);

	if (scfhandle == NULL || pgtmpl == NULL || proptmpl == NULL) {
		err = error_scf(error, SCF_ERROR_NO_MEMORY);
		goto out;
	}

	if (scf_tmpl_get_by_pg_name(si->fmri, NULL, pgname, NULL, pgtmpl,
	    0) == -1 ||
	    scf_tmpl_get_by_prop(pgtmpl, propname, proptmpl, 0) == -1) {
		err = error_scf(error, scf_error());
		goto out;
	}

	adr_data_t *result = adr_data_new_struct(&t__Template);

	char *name;
	if (scf_tmpl_prop_common_name(proptmpl, locale, &name) >= 0)
		adr_struct_set(result, "name",
		    adr_data_new_string(name, LT_FREE));

	if (scf_tmpl_prop_description(proptmpl, locale, &name) >= 0)
		adr_struct_set(result, "description",
		    adr_data_new_string(name, LT_FREE));

	if (scf_tmpl_prop_units(proptmpl, locale, &name) >= 0)
		adr_struct_set(result, "units",
		    adr_data_new_string(name, LT_FREE));

	uint8_t vis;
	if (scf_tmpl_prop_visibility(proptmpl, &vis) == -1) {
		adr_data_free(result);
		goto out;
	}
	adr_data_t *visvalue = NULL;
	switch (vis) {
	case SCF_TMPL_VISIBILITY_HIDDEN:
		visvalue = &e__PropertyVisibility_HIDDEN;
		break;
	case SCF_TMPL_VISIBILITY_READONLY:
		visvalue = &e__PropertyVisibility_READONLY;
		break;
	case SCF_TMPL_VISIBILITY_READWRITE:
		visvalue = &e__PropertyVisibility_READWRITE;
		break;
	}
	adr_struct_set(result, "visibility", visvalue);

	scf_values_t values;
	if (scf_tmpl_prop_internal_seps(proptmpl, &values) == 0) {
		adr_data_t *array =
		    adr_data_new_array(&adr_t_array_string, values.value_count);
		for (int i = 0; i < values.value_count; i++)
			(void) adr_array_add(array, adr_data_new_string(
			    values.values_as_strings[i], LT_COPY));
		adr_struct_set(result, "separators", array);
		scf_values_destroy(&values);
	}

	if (scf_tmpl_value_name_choices(proptmpl, &values) == 0) {
		adr_data_t *array =
		    adr_data_new_array(&adr_t_array_string, values.value_count);
		for (int i = 0; i < values.value_count; i++)
			(void) adr_array_add(array, adr_data_new_string(
			    values.values_as_strings[i], LT_COPY));
		adr_struct_set(result, "allowed", array);
		scf_values_destroy(&values);
	}

	if ((*ret = adr_data_purify_deep(result)) == NULL)
		err = error_scf(error, SCF_ERROR_NO_MEMORY);
out:
	scf_tmpl_prop_destroy(proptmpl);
	scf_tmpl_pg_destroy(pgtmpl);
	scf_handle_destroy(scfhandle);

	return (err);
}

static int
get_localedprop(servinst_t *si, const char *locale, const char *name,
    adr_data_t **ret, adr_data_t **error)
{
	char *str;
	rad_propvec_t *badprop;
	rad_propvec_t evec[] = {
		{ locale, NULL, SCF_TYPE_ASTRING, &str, 0 },
		{ NULL }
	};

	int scferr = rad_read_propvec(si->fmri, name, si->instance, evec,
	    &badprop);
	if (scferr != 0) {
		if (error != NULL && scferr == SCF_ERROR_NOT_FOUND) {
			*ret = NULL;
			return (CE_OK);
		}
		return (error_scf(error, scferr));
	}

	*ret = adr_data_new_string(str, LT_COPY);
	rad_clean_propvec(evec);
	return (CE_OK);
}

/* ARGSUSED */
conerr_t
interface_ServiceInfo_invoke_getCommonName(rad_instance_t *inst,
    adr_method_t *meth, adr_data_t **ret, adr_data_t **args, int count,
    adr_data_t **error)
{
	const char *locale = adr_data_to_string(args[0]);
	servinst_t *si = rad_instance_getdata(inst);

	if (get_localedprop(si, locale, SCF_PG_TM_COMMON_NAME, ret, NULL)
	    == CE_OK)
		return (CE_OK);
	return (get_localedprop(si, "C", SCF_PG_TM_COMMON_NAME, ret, error));
}

/* ARGSUSED */
conerr_t
interface_ServiceInfo_invoke_getDescription(rad_instance_t *inst,
    adr_method_t *meth, adr_data_t **ret, adr_data_t **args, int count,
    adr_data_t **error)
{
	const char *locale = adr_data_to_string(args[0]);
	servinst_t *si = rad_instance_getdata(inst);

	if (get_localedprop(si, locale, SCF_PG_TM_DESCRIPTION, ret, NULL)
	    == CE_OK)
		return (CE_OK);
	return (get_localedprop(si, "C", SCF_PG_TM_DESCRIPTION, ret, error));
}

/* ARGSUSED */
conerr_t
interface_ServiceInfo_invoke_getLogInfo(rad_instance_t *inst,
    adr_method_t *meth, adr_data_t **ret, adr_data_t **args, int count,
    adr_data_t **error)
{
	servinst_t *si = rad_instance_getdata(inst);
	if (!si->instance)
		return (CE_OBJECT);

	char *logname = NULL;
	rad_propvec_t evec[] = {
		{ SCF_PROPERTY_LOGFILE, NULL, SCF_TYPE_USTRING, &logname, 0 },
		{ NULL }
	};

	rad_propvec_t *badprop;
	int errval = rad_read_propvec(si->fmri, SCF_PG_RESTARTER, B_FALSE,
	    evec, &badprop);
	if (errval != 0)
		return (CE_OBJECT);

	struct stat st;
	if (stat(logname, &st) != 0) {
		free(logname);
		return (CE_OBJECT);
	}

	int max_size = adr_data_to_integer(args[0]);

	int bsize = max_size >= 0 && max_size < st.st_size ?
	    max_size : st.st_size;
	char *buffer = malloc(bsize);
	if (buffer == NULL) {
		free(logname);
		return (CE_NOMEM);
	}

	int fd;
	if ((fd = open(logname, O_RDONLY)) == -1) {
		free(buffer);
		free(logname);
		return (CE_PRIV);
	}

	if (pread(fd, buffer, bsize, st.st_size - bsize) != bsize) {
		(void) close(fd);
		free(buffer);
		free(logname);
		return (CE_SYSTEM);
	}

	(void) close(fd);

	adr_data_t *result = adr_data_new_struct(&t__LogInfo);
	adr_struct_set(result, "name", adr_data_new_string(logname, LT_FREE));
	adr_struct_set(result, "size", adr_data_new_integer(st.st_size));
	adr_struct_set(result, "MTime", adr_data_new_time_ts(&st.st_mtim));
	adr_struct_set(result, "contents",
	    adr_data_new_opaque(buffer, bsize, LT_FREE));

	if ((*ret = adr_data_purify(result)) == NULL)
		return (CE_OBJECT);

	return (CE_OK);
}

/* ARGSUSED */
conerr_t
interface_ServiceInfo_invoke_delete(rad_instance_t *inst, adr_method_t *meth,
    adr_data_t **ret, adr_data_t **args, int count, adr_data_t **error)
{
	conerr_t err = CE_OK;
	servinst_t *si = rad_instance_getdata(inst);

	scf_handle_t *scfhandle = handle_create();
	scf_service_t *service = scf_service_create(scfhandle);
	scf_instance_t *instance = scf_instance_create(scfhandle);

	if (scfhandle == NULL || service == NULL || instance == NULL) {
		err = error_scf(error, SCF_ERROR_NO_MEMORY);
		goto out;
	}

	if (scf_handle_decode_fmri(scfhandle, si->fmri, NULL, service,
	    instance, NULL, NULL, si->instance ?
	    SCF_DECODE_FMRI_REQUIRE_INSTANCE :
	    SCF_DECODE_FMRI_REQUIRE_NO_INSTANCE) != SCF_SUCCESS) {
		rad_log(RL_WARN, "Couldn't decode '%s': %s\n",
		    si->fmri, scf_strerror(scf_error()));
		err = error_scf(error, scf_error());
		goto out;
	}

	err = simple_scf(error, si->instance ?
	    scf_instance_delete(instance) : scf_service_delete(service));
out:
	scf_service_destroy(service);
	scf_instance_destroy(instance);
	scf_handle_destroy(scfhandle);
	return (err);
}

/* ARGSUSED */
conerr_t
interface_ServiceInfo_invoke_clear(rad_instance_t *inst, adr_method_t *meth,
    adr_data_t **ret, adr_data_t **args, int count, adr_data_t **error)
{
	servinst_t *si = rad_instance_getdata(inst);
	if (!si->instance)
		return (error_scf(error, SCF_ERROR_INVALID_ARGUMENT));

	return (simple_scf(error, smf_restore_instance(si->fmri)));
}

/* ARGSUSED */
conerr_t
interface_ServiceInfo_invoke_degrade(rad_instance_t *inst, adr_method_t *meth,
    adr_data_t **ret, adr_data_t **args, int count, adr_data_t **error)
{
	servinst_t *si = rad_instance_getdata(inst);
	if (!si->instance)
		return (error_scf(error, SCF_ERROR_INVALID_ARGUMENT));

	return (simple_scf(error, smf_degrade_instance(si->fmri,
	    adr_data_to_boolean(args[0]) ? SMF_IMMEDIATE : 0)));
}

/* ARGSUSED */
conerr_t
interface_ServiceInfo_invoke_maintain(rad_instance_t *inst, adr_method_t *meth,
    adr_data_t **ret, adr_data_t **args, int count, adr_data_t **error)
{
	servinst_t *si = rad_instance_getdata(inst);
	if (!si->instance)
		return (error_scf(error, SCF_ERROR_INVALID_ARGUMENT));

	return (simple_scf(error, smf_maintain_instance(si->fmri,
	    adr_data_to_boolean(args[0]) ? SMF_IMMEDIATE : 0)));
}

/* ARGSUSED */
conerr_t
interface_ServiceInfo_invoke_restart(rad_instance_t *inst, adr_method_t *meth,
    adr_data_t **ret, adr_data_t **args, int count, adr_data_t **error)
{
	servinst_t *si = rad_instance_getdata(inst);
	if (!si->instance)
		return (error_scf(error, SCF_ERROR_INVALID_ARGUMENT));

	return (simple_scf(error, smf_restart_instance(si->fmri)));
}

/* ARGSUSED */
conerr_t
interface_ServiceInfo_invoke_refresh(rad_instance_t *inst, adr_method_t *meth,
    adr_data_t **ret, adr_data_t **args, int count, adr_data_t **error)
{
	servinst_t *si = rad_instance_getdata(inst);
	if (!si->instance)
		return (error_scf(error, SCF_ERROR_INVALID_ARGUMENT));

	return (simple_scf(error, smf_refresh_instance(si->fmri)));
}

/* ARGSUSED */
conerr_t
interface_Aggregator_read_services(rad_instance_t *inst, adr_attribute_t *attr,
    adr_data_t **data, adr_data_t **error)
{
	rad_mutex_enter(&service_lock);
	adr_data_t *result =
	    adr_data_new_array(&t_array__Service, service_count);

	for (servinst_t *si = list_head(&service_list); si != NULL;
	    si = list_next(&service_list, si)) {
		adr_data_t *insts = adr_data_new_array(&adr_t_array_string,
		    si->ninstances);
		for (servinst_t *i = list_head(&si->instances); i != NULL;
		    i = list_next(&si->instances, i))
			(void) adr_array_add(insts,
			    adr_data_new_string(i->iname,
			    LT_COPY));

		adr_data_t *service = adr_data_new_struct(&t__Service);
		adr_struct_set(service, "fmri",
		    adr_data_new_string(si->fmri, LT_COPY));
		adr_struct_set(service, "objectName",
		    rad_instance_getname(si->inst));
		adr_struct_set(service, "instances", insts);
		(void) adr_array_add(result, service);
	}

	if (adr_data_verify(result, NULL, B_TRUE))
		*data = result;
	else
		adr_data_free(result);

	rad_mutex_exit(&service_lock);
	return (*data != NULL ? CE_OK : CE_OBJECT);
}

/* ARGSUSED */
conerr_t
interface_Aggregator_read_instances(rad_instance_t *inst, adr_attribute_t *attr,
    adr_data_t **data, adr_data_t **error)
{
	conerr_t err = CE_OK;

	scf_handle_t *scfhandle = handle_create();
	scf_service_t *service = scf_service_create(scfhandle);
	scf_instance_t *instance = scf_instance_create(scfhandle);
	scf_propertygroup_t *pg = scf_pg_create(scfhandle);
	scf_property_t *prop = scf_property_create(scfhandle);
	scf_value_t *val = scf_value_create(scfhandle);

	if (scfhandle == NULL || service == NULL || instance == NULL ||
	    pg == NULL || prop == NULL || prop == NULL ||
	    val == NULL) {
		err = error_scf(error, SCF_ERROR_NO_MEMORY);
		goto out;
	}

	rad_mutex_enter(&service_lock);
	adr_data_t *result = adr_data_new_array(&t_array__Instance,
	    instance_count);

	/*
	 * It would be easy to iterate over all instances -- not just the
	 * ones we know about -- but until we dynamically add and remove
	 * their MBeans we'll stick to our list to avoid confusion.
	 */
	for (servinst_t *si = list_head(&instance_list); si != NULL;
	    si = list_next(&instance_list, si)) {

		char statestr[MAX_SCF_STATE_STRING_SZ];
		ssize_t len;
		int64_t seconds;
		int32_t ns;

		if (scf_handle_decode_fmri(scfhandle, si->fmri, NULL, service,
		    instance, NULL, NULL, 0) != SCF_SUCCESS)
			continue;
		if (scf_instance_get_pg(instance, SCF_PG_RESTARTER, pg) != 0)
			continue;

		if (scf_pg_get_property(pg, SCF_PROPERTY_STATE, prop) != 0 ||
		    scf_property_get_value(prop, val) != 0 ||
		    (len = scf_value_get_as_string(val, statestr,
		    MAX_SCF_STATE_STRING_SZ)) == -1 ||
		    len > MAX_SCF_STATE_STRING_SZ - 1)
			continue;

		if (scf_pg_get_property(pg, SCF_PROPERTY_STATE_TIMESTAMP,
		    prop) != 0 || scf_property_get_value(prop, val) != 0 ||
		    scf_value_get_time(val, &seconds, &ns) != 0)
			continue;

		adr_data_t *inst = adr_data_new_struct(&t__Instance);
		adr_struct_set(inst, "fmri",
		    adr_data_new_string(si->fmri, LT_COPY));
		adr_struct_set(inst, "objectName",
		    rad_instance_getname(si->inst));
		adr_struct_set(inst, "STime", adr_data_new_time(seconds, ns));
		adr_struct_set(inst, "state", state2enum(statestr));
		if (!adr_data_verify(inst, NULL, B_TRUE))
			adr_data_free(inst);
		else
			(void) adr_array_add(result, inst);
	}

	if ((*data = adr_data_purify(result)) == NULL)
		err = CE_OBJECT;
	rad_mutex_exit(&service_lock);
out:
	scf_value_destroy(val);
	scf_property_destroy(prop);
	scf_pg_destroy(pg);
	scf_instance_destroy(instance);
	scf_service_destroy(service);
	scf_handle_destroy(scfhandle);

	return (err);
}

static rad_moderr_t
notify_thread(rad_thread_t *arg)
{
	scf_handle_t *scfhandle = handle_create();
	scf_service_t *service = scf_service_create(scfhandle);
	scf_instance_t *instance = scf_instance_create(scfhandle);
	scf_propertygroup_t *pg = scf_pg_create(scfhandle);
	char fmri[5];
	char sname[1000], iname[1000];
	servinst_t *si;
	int ret;

	if (scfhandle == NULL || service == NULL || instance == NULL ||
	    pg == NULL ||
	    _scf_notify_add_pgtype(scfhandle, SCF_GROUP_FRAMEWORK) != 0)
		goto out;

	rad_thread_ack(arg, RM_OK);
	while ((ret = _scf_notify_wait(pg, fmri, 5)) >= 0) {
		rad_log(RL_DEBUG, "received SMF event");

		if (ret > 0)
			continue;	/* We should care */

		if (scf_pg_get_parent_instance(pg, instance) != 0 ||
		    scf_instance_get_parent(instance, service) != 0 ||
		    scf_instance_get_name(instance, iname, 1000) == -1 ||
		    scf_service_get_name(service, sname, 1000) == -1)
			continue;

		rad_mutex_enter(&service_lock);

		for (si = list_head(&instance_list); si != NULL;
		    si = list_next(&instance_list, si))
			if (strcmp(si->iname, iname) == 0 &&
			    strcmp(si->sname, sname) == 0)
				break;

		if (si == NULL) {
			rad_mutex_exit(&service_lock);
			continue;
		}

		rad_log(RL_DEBUG, "identified SMF event: %s/%s", sname, iname);

		adr_data_t *stime = NULL, *state = NULL, *nstate = NULL;
		adr_data_t *astate = NULL, *reason = NULL;

		/* Inefficient, but expedient */
		(void) interface_ServiceInfo_read_stime(si->inst, NULL, &stime,
		    NULL);
		(void) interface_ServiceInfo_read_state(si->inst, NULL, &state,
		    NULL);
		(void) interface_ServiceInfo_read_nextState(si->inst, NULL,
		    &nstate, NULL);
		(void) interface_ServiceInfo_read_auxiliaryState(si->inst, NULL,
		    &astate, NULL);
		(void) interface_ServiceInfo_read_reason(si->inst, NULL,
		    &reason, NULL);

		adr_data_t *event = adr_data_new_struct(&t__StateChange);
		adr_struct_set(event, "source",
		    rad_instance_getname(si->inst));
		adr_struct_set(event, "state", state);
		adr_struct_set(event, "nextState", nstate);
		adr_struct_set(event, "stateTime", stime);
		adr_struct_set(event, "auxState", astate);
		adr_struct_set(event, "reason", reason);
		adr_struct_set(event, "anomaly", adr_data_new_boolean(B_FALSE));
		if (adr_data_verify(event, NULL, B_FALSE)) {
			rad_log(RL_DEBUG, "sending SMF event");
			if (agg_inst != NULL)
				rad_instance_notify(agg_inst, "statechange",
				    0, adr_data_ref(event));
			rad_instance_notify(si->inst, "statechange", 0, event);
		} else {
			rad_log(RL_DEBUG, "failed to send SMF event");
			adr_data_free(event);
		}

		rad_mutex_exit(&service_lock);
	}
	rad_log(RL_ERROR, "_scf_notify_wait failed: %s",
	    scf_strerror(scf_error()));

	/* XXX: reestablish on configd death */
out:
	scf_pg_destroy(pg);
	scf_instance_destroy(instance);
	scf_service_destroy(service);
	scf_handle_destroy(scfhandle);

	rad_log(RL_ERROR, "exiting SMF event loop");

	return (RM_SYSTEM);
}

static servinst_t *
make_service(char *sname, char *iname)
{
	adr_name_t *objname;
	boolean_t inst = iname != NULL;
	servinst_t *si = rad_zalloc(sizeof (servinst_t));
	si->sname = strdup(sname);
	si->iname = inst ? strdup(iname) : NULL;
	/* LINTED */
	if (si->instance = inst) {
		(void) asprintf(&si->fmri, "svc:/%s:%s", sname, iname);
		objname = adr_name_vcreate(MOD_DOMAIN, 3,
		    "type", "ServiceInfo", "service", sname, "instance", iname);
	} else {
		list_create(&si->instances, sizeof (servinst_t),
		    offsetof(servinst_t, snode));
		(void) asprintf(&si->fmri, "svc:/%s", sname);
		objname = adr_name_vcreate(MOD_DOMAIN, 2,
		    "type", "ServiceInfo", "service", sname);
	}

	si->inst = rad_instance_create(objname, &modinfo,
	    &interface_ServiceInfo_svr, si, NULL);
	(void) rad_cont_insert(rad_container, si->inst, INST_ID_PICK);

	if (inst) {
		list_insert_tail(&instance_list, si);
		instance_count++;
	} else {
		list_insert_tail(&service_list, si);
		service_count++;
	}


	return (si);
}

int
_rad_init(void)
{
	adr_name_t *aname;
	conerr_t cerr;

	list_create(&service_list, sizeof (servinst_t),
	    offsetof(servinst_t, node));
	list_create(&instance_list, sizeof (servinst_t),
	    offsetof(servinst_t, node));

	scf_handle_t *scfhandle = handle_create();
	scf_scope_t *scope = scf_scope_create(scfhandle);
	scf_iter_t *siter = scf_iter_create(scfhandle);
	scf_iter_t *iiter = scf_iter_create(scfhandle);
	scf_service_t *service = scf_service_create(scfhandle);
	scf_instance_t *instance = scf_instance_create(scfhandle);

	(void) scf_handle_get_scope(scfhandle, SCF_SCOPE_LOCAL, scope);
	(void) scf_iter_scope_services(siter, scope);
	while (scf_iter_next_service(siter, service) > 0) {
		char svcname[1000];
		(void) scf_service_get_name(service, svcname, 1000);
		servinst_t *svc = make_service(svcname, NULL);
		(void) scf_iter_service_instances(iiter, service);
		while (scf_iter_next_instance(iiter, instance) > 0) {
			char instname[1000];
			(void) scf_instance_get_name(instance, instname, 1000);
			list_insert_tail(&svc->instances,
			    make_service(svcname, instname));
			svc->ninstances++;
		}
	}

	scf_instance_destroy(instance);
	scf_service_destroy(service);
	scf_iter_destroy(iiter);
	scf_iter_destroy(siter);
	scf_scope_destroy(scope);
	scf_handle_destroy(scfhandle);

	aname = adr_name_vcreate(MOD_DOMAIN, 1, "type", "Aggregator");
	cerr =  rad_cont_insert_singleton(rad_container, aname,
	    &modinfo, &interface_Aggregator_svr);
	adr_name_rele(aname);
	if (cerr != CE_OK) {
		rad_log(RL_ERROR, "(mod_smf) failed to insert Aggregator");
		return (-1);
	}

	if (rad_thread_create(notify_thread, NULL) != RM_OK)
		rad_log(RL_ERROR, "failed to start SMF listener");
	return (0);
}

/*
 * _rad_fini is called by the RAD daemon when the module is unloaded. Any
 * module finalisation is completed here.
 */
/*ARGSUSED*/
void
_rad_fini(void *unused)
{
}
