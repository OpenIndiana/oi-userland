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
 * Copyright (c) 2010, 2012, Oracle and/or its affiliates. All rights reserved.
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

static const char *aggregator_pattern =
	"com.oracle.solaris.vp.panel.common.api.smf_old:type=Aggregator";

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
error_scf(data_t **error, int code)
{
	if (error != NULL) {
		data_t *e = data_new_struct(&t__SmfError);
		struct_set(e, "error", data_new_enum(&t__SmfErrorCode, code));
		struct_set(e, "message",
		    data_new_string(scf_strerror(code), lt_const));
		*error = data_purify(e);
	}
	return (ce_object);
}

static conerr_t
simple_scf(data_t **error, int result)
{
	if (result == 0)
		return (ce_ok);
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

static int getpgs(servinst_t *si, data_t **data, boolean_t namesonly,
    boolean_t(*fp)(const char **, const char *), const char **set,
    data_t **error)
{
	conerr_t err = ce_ok;
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

	data_t *result = namesonly ? data_new_array(&t_array_string, 5) :
	    data_new_array(&t_array__PropertyGroup, 5);
	while (scf_iter_next_pg(iter, pg) > 0) {
		char nbuf[1000];
		char tbuf[1000];
		(void) scf_pg_get_name(pg, nbuf, 1000);
		(void) scf_pg_get_type(pg, tbuf, 1000);

		if (fp(set, tbuf)) {
			if (namesonly) {
				(void) array_add(result,
				    data_new_string(nbuf, lt_copy));
			} else {
				data_t *pgdata =
				    data_new_struct(&t__PropertyGroup);
				struct_set(pgdata, "name",
				    data_new_string(nbuf, lt_copy));
				struct_set(pgdata, "type",
				    data_new_string(tbuf, lt_copy));
				(void) array_add(result, pgdata);
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
    data_t **data, data_t **error)
{
	servinst_t *si = instance_getdata(inst);
	*data = data_new_string(si->fmri, lt_copy);
	return (ce_ok);
}

/* ARGSUSED */
conerr_t
interface_ServiceInfo_read_methodNames(rad_instance_t *inst,
    adr_attribute_t *attr, data_t **data, data_t **error)
{
	const char *pgtypes[] = { SCF_GROUP_METHOD, NULL };
	return (getpgs(instance_getdata(inst), data, B_TRUE, strinset, pgtypes,
	    error));
}

/* ARGSUSED */
conerr_t
interface_ServiceInfo_read_dependencyNames(rad_instance_t *inst,
    adr_attribute_t *attr, data_t **data, data_t **error)
{
	const char *pgtypes[] = { SCF_GROUP_DEPENDENCY, NULL };
	return (getpgs(instance_getdata(inst), data, B_TRUE, strinset, pgtypes,
	    error));
}

/* ARGSUSED */
conerr_t
interface_ServiceInfo_read_propertyGroups(rad_instance_t *inst,
    adr_attribute_t *attr, data_t **data, data_t **error)
{
	return (getpgs(instance_getdata(inst), data, B_FALSE, strnotinset,
	    framework_pgtypes, error));
}

/* ARGSUSED */
conerr_t
interface_ServiceInfo_read_manpages(rad_instance_t *inst, adr_attribute_t *attr,
    data_t **data, data_t **error)
{
	servinst_t *si = instance_getdata(inst);
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

	data_t *pgs;
	conerr_t err = getpgs(si, &pgs, B_TRUE, strinset, pgtypes, error);
	if (err != ce_ok)
		return (err);
	data_t *result = data_new_array(&t_array__Manpage, 5);
	for (int i = 0; i < array_size(pgs); i++) {
		const char *str = data_to_string(array_get(pgs, i));
		if (strncmp(str, SCF_PG_TM_MAN_PREFIX,
		    strlen(SCF_PG_TM_MAN_PREFIX)) != 0) {
			continue;
		}

		if (rad_read_propvec(si->fmri, str, B_FALSE, evec,
		    &badprop) != 0)
			continue;

		data_t *mp = data_new_struct(&t__Manpage);
		struct_set(mp, "title", data_new_string(title, lt_copy));
		struct_set(mp, "section", data_new_string(section, lt_copy));
		struct_set(mp, "path", data_new_string(path, lt_copy));
		(void) array_add(result, mp);
		rad_clean_propvec(evec);
	}
	data_free(pgs);
	*data = result;

	return (ce_ok);
}

/* ARGSUSED */
conerr_t
interface_ServiceInfo_read_doclinks(rad_instance_t *inst, adr_attribute_t *attr,
    data_t **data, data_t **error)
{
	servinst_t *si = instance_getdata(inst);
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

	data_t *pgs;
	conerr_t err = getpgs(si, &pgs, B_TRUE, strinset, pgtypes, error);
	if (err != ce_ok)
		return (err);
	data_t *result = data_new_array(&t_array_string, 5);
	for (int i = 0; i < array_size(pgs); i++) {
		const char *str = data_to_string(array_get(pgs, i));
		if (strncmp(str, SCF_PG_TM_DOC_PREFIX,
		    strlen(SCF_PG_TM_DOC_PREFIX)) != 0) {
			continue;
		}

		if (rad_read_propvec(si->fmri, str, B_FALSE, evec,
		    &badprop) == 0) {
			(void) array_add(result, data_new_string(uri, lt_copy));
			rad_clean_propvec(evec);
		}
	}
	data_free(pgs);
	*data = result;

	return (ce_ok);
}

/* ARGSUSED */
conerr_t
interface_ServiceInfo_read_persistentlyEnabled(rad_instance_t *inst,
    adr_attribute_t *attr, data_t **data, data_t **error)
{
	servinst_t *si = instance_getdata(inst);
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

	*data = data_new_boolean(enabled);
	return (ce_ok);
}

/* ARGSUSED */
conerr_t
interface_ServiceInfo_read_temporarilyEnabled(rad_instance_t *inst,
    adr_attribute_t *attr, data_t **data, data_t **error)
{
	servinst_t *si = instance_getdata(inst);
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

	*data = data_new_boolean(enabled);
	return (ce_ok);
}

/* ARGSUSED */
conerr_t
interface_ServiceInfo_read_enabled(rad_instance_t *inst, adr_attribute_t *attr,
    data_t **data, data_t **error)
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
    data_t **data, data_t **error)
{
	servinst_t *si = instance_getdata(inst);
	*data = data_new_boolean(si->instance);
	return (ce_ok);
}

/* ARGSUSED */
conerr_t
interface_ServiceInfo_read_restarter(rad_instance_t *inst,
    adr_attribute_t *attr, data_t **data, data_t **error)
{
	servinst_t *si = instance_getdata(inst);
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
		*data = data_new_string(fmri, lt_copy);
		rad_clean_propvec(evec);
	} else {
		*data = data_new_fstring("svc:/%s:%s",
		    "system/svc/restarter", "default");
	}

	return (*data != NULL ? ce_ok : ce_system);
}

static data_t *
state2enum(const char *state)
{
	if (strcmp(state, SCF_STATE_STRING_UNINIT) == 0) {
		return (&e__SmfState_UNINIT);
	} else if (strcmp(state, SCF_STATE_STRING_MAINT) == 0) {
		return (&e__SmfState_MAINT);
	} else if (strcmp(state, SCF_STATE_STRING_LEGACY) == 0) {
		return (&e__SmfState_LEGACY);
	} else {
		return (data_new_enum_byname(&t__SmfState, state));
	}
}

/* ARGSUSED */
conerr_t
interface_ServiceInfo_read_state(rad_instance_t *inst, adr_attribute_t *attr,
    data_t **data, data_t **error)
{
	servinst_t *si = instance_getdata(inst);
	if (!si->instance)
		return (error_scf(error, SCF_ERROR_INVALID_ARGUMENT));

	char *state = smf_get_state(si->fmri);
	if (state == NULL)
		return (error_scf(error, scf_error()));

	*data = state2enum(state);
	free(state);
	return (*data != NULL ? ce_ok : ce_system);
}

/* ARGSUSED */
conerr_t
interface_ServiceInfo_read_nextState(rad_instance_t *inst,
    adr_attribute_t *attr, data_t **data, data_t **error)
{
	servinst_t *si = instance_getdata(inst);
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
	return (*data != NULL ? ce_ok : ce_system);
}

/* ARGSUSED */
conerr_t
interface_ServiceInfo_read_auxiliaryState(rad_instance_t *inst,
    adr_attribute_t *attr, data_t **data, data_t **error)
{
	servinst_t *si = instance_getdata(inst);
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
			return (ce_ok);
		}
		return (error_scf(error, scferr));
	}

	*data = data_new_string(aux, lt_copy);
	rad_clean_propvec(evec);

	return (*data != NULL ? ce_ok : ce_system);
}

/* ARGSUSED */
conerr_t
interface_ServiceInfo_read_stime(rad_instance_t *inst, adr_attribute_t *attr,
    data_t **data, data_t **error)
{
	servinst_t *si = instance_getdata(inst);
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

	*data = data_new_time(time.t_seconds, time.t_ns);

	return (*data != NULL ? ce_ok : ce_system);
}

/* ARGSUSED */
conerr_t
interface_ServiceInfo_read_contractID(rad_instance_t *inst,
    adr_attribute_t *attr, data_t **data, data_t **error)
{
	servinst_t *si = instance_getdata(inst);
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

	*data = data_new_long(count);

	return (*data != NULL ? ce_ok : ce_system);
}

/* ARGSUSED */
conerr_t
interface_ServiceInfo_read_reason(rad_instance_t *inst, adr_attribute_t *attr,
    data_t **data, data_t **error)
{
	servinst_t *si = instance_getdata(inst);
	if (!si->instance)
		return (error_scf(error, SCF_ERROR_INVALID_ARGUMENT));
	*data = NULL;
	return (ce_ok);
}

/* ARGSUSED */
conerr_t
interface_ServiceInfo_write_persistentlyEnabled(rad_instance_t *inst,
    adr_attribute_t *attr, data_t *data, data_t **error)
{
	servinst_t *si = instance_getdata(inst);
	boolean_t enable = data_to_boolean(data);
	if (!si->instance)
		return (error_scf(error, SCF_ERROR_INVALID_ARGUMENT));

	return (simple_scf(error, enable ? smf_enable_instance(si->fmri, 0) :
	    smf_disable_instance(si->fmri, 0)));
}

static conerr_t
get_pg(scf_handle_t *scfhandle, scf_propertygroup_t *pg, servinst_t *si,
    const char *snapname, const char *pgname, data_t **error)
{
	conerr_t err = ce_ok;
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
    adr_method_t *meth, data_t **ret, data_t **args, int count, data_t **error)
{
	conerr_t err = ce_ok;
	const char *pgname = data_to_string(args[0]);
	servinst_t *si = instance_getdata(inst);
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
	    != ce_ok)
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

	data_t *result = data_new_struct(&t__Dependency);
	data_t *array = data_new_array(&t_array_string, 5);
	struct_set(result, "name", data_ref(args[0]));
	struct_set(result, "grouping", data_new_string(grouping, lt_copy));
	struct_set(result, "restartOn", data_new_string(restarton, lt_copy));
	struct_set(result, "target", array);
	while (scf_iter_next_value(iter, val) > 0) {
		if (scf_value_get_as_string(val, type, sizeof (type)) == -1) {
			err = error_scf(error, scf_error());
			data_free(result);
			goto out;
		}
		(void) array_add(array, data_new_string(type, lt_copy));
	}
	if (!data_verify(result, NULL, B_TRUE)) {
		data_free(result);
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
    adr_method_t *meth, data_t **ret, data_t **args, int count, data_t **error)
{
	conerr_t err = ce_ok;
	const char *pgname = data_to_string(args[0]);
	servinst_t *si = instance_getdata(inst);

	scf_handle_t *scfhandle = handle_create();
	scf_iter_t *iter = scf_iter_create(scfhandle);
	scf_propertygroup_t *pg = scf_pg_create(scfhandle);
	scf_property_t *prop = scf_property_create(scfhandle);

	if (scfhandle == NULL || iter == NULL || pg == NULL || prop == NULL) {
		err = error_scf(error, SCF_ERROR_NO_MEMORY);
		goto out;
	}

	if ((err = get_pg(scfhandle, pg, si, "running", pgname, error))
	    != ce_ok)
		goto out;

	data_t *result = data_new_array(&t_array_string, 5);
	(void) scf_iter_pg_properties(iter, pg);
	while (scf_iter_next_property(iter, prop) > 0) {
		char pbuf[1000];
		(void) scf_property_get_name(prop, pbuf, 1000);
		(void) array_add(result, data_new_string(pbuf, lt_copy));
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
    adr_method_t *meth, data_t **ret, data_t **args, int count, data_t **error)
{
	const char *pgname = data_to_string(args[0]);
	const char *propname = data_to_string(args[1]);
	conerr_t err = ce_ok;
	servinst_t *si = instance_getdata(inst);

	scf_handle_t *scfhandle = handle_create();
	scf_propertygroup_t *pg = scf_pg_create(scfhandle);
	scf_property_t *prop = scf_property_create(scfhandle);
	scf_type_t type;

	if (scfhandle == NULL || pg == NULL || prop == NULL) {
		err = error_scf(error, SCF_ERROR_NO_MEMORY);
		goto out;
	}
	if ((err = get_pg(scfhandle, pg, si, "running", pgname, error))
	    != ce_ok)
		goto out;

	if (scf_pg_get_property(pg, propname, prop) != 0 ||
	    scf_property_type(prop, &type) != 0) {
		err = error_scf(error, scf_error());
		goto out;
	}

	data_t *result = data_new_enum(&t__PropertyType, type);
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
    adr_method_t *meth, data_t **ret, data_t **args, int count, data_t **error)
{
	conerr_t err = ce_ok;
	const char *pgname = data_to_string(args[0]);
	const char *propname = data_to_string(args[1]);

	servinst_t *si = instance_getdata(inst);

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

	data_t *result = data_new_array(&t_array_string, 5);
	while (scf_iter_next_value(iter, val) > 0) {
		char pbuf[1000];
		(void) scf_value_get_as_string(val, pbuf, 1000);
		(void) array_add(result, data_new_string(pbuf, lt_copy));
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
    adr_method_t *meth, data_t **ret, data_t **args, int count, data_t **error)
{
	conerr_t err = ce_ok;
	const char *snapname = data_to_string(args[0]);
	const char *pgname = data_to_string(args[1]);
	const char *propname = data_to_string(args[2]);

	servinst_t *si = instance_getdata(inst);
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
	    != ce_ok)
		goto out;
	if (scf_pg_get_property(pg, propname, prop) != 0) {
		err = error_scf(error, scf_error());
		goto out;
	}

	data_t *result = data_new_array(&t_array_string, 5);
	(void) scf_iter_property_values(iter, prop);
	while (scf_iter_next_value(iter, val) > 0) {
		char pbuf[1000];
		(void) scf_value_get_as_string(val, pbuf, 1000);
		(void) array_add(result, data_new_string(pbuf, lt_copy));
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
    adr_method_t *meth, data_t **ret, data_t **args, int count, data_t **error)
{
	conerr_t err = ce_ok;
	const char *pgname = data_to_string(args[0]);
	const char *propname = data_to_string(args[1]);
	data_t *values = args[2];

	servinst_t *si = instance_getdata(inst);

	scf_handle_t *scfhandle = handle_create();
	scf_service_t *service = scf_service_create(scfhandle);
	scf_instance_t *instance = scf_instance_create(scfhandle);
	scf_propertygroup_t *pg = scf_pg_create(scfhandle);
	scf_property_t *prop = scf_property_create(scfhandle);
	scf_transaction_t *tx = scf_transaction_create(scfhandle);
	scf_transaction_entry_t *ent = scf_entry_create(scfhandle);
	scf_value_t **val =
	    rad_zalloc(array_size(values) * sizeof (scf_value_t *));
	scf_type_t type;

	if (scfhandle == NULL || service == NULL || instance == NULL ||
	    pg == NULL || prop == NULL || tx == NULL || ent == NULL ||
	    val == NULL) {
		err = error_scf(error, SCF_ERROR_NO_MEMORY);
		goto out;
	}

	for (int i = 0; i < array_size(values); i++) {
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

	for (int i = 0; i < array_size(values); i++) {
		if (scf_value_set_from_string(val[i], type,
		    data_to_string(array_get(values, i))) != 0 ||
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
		for (int i = 0; i < array_size(values); i++) {
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
    adr_method_t *meth, data_t **ret, data_t **args, int count, data_t **error)
{
	conerr_t err = ce_ok;
	const char *pgname = data_to_string(args[0]);
	const char *pgtype = data_to_string(args[1]);

	servinst_t *si = instance_getdata(inst);

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
    adr_method_t *meth, data_t **ret, data_t **args, int count, data_t **error)
{
	conerr_t err = ce_ok;
	const char *pgname = data_to_string(args[0]);

	servinst_t *si = instance_getdata(inst);

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
    adr_method_t *meth, data_t **ret, data_t **args, int count, data_t **error)
{
	conerr_t err = ce_ok;
	const char *pgname = data_to_string(args[0]);
	const char *propname = data_to_string(args[1]);
	scf_type_t type = enum_tovalue(args[2]);
	int sret;

	servinst_t *si = instance_getdata(inst);

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
    adr_method_t *meth, data_t **ret, data_t **args, int count, data_t **error)
{
	conerr_t err = ce_ok;
	const char *pgname = data_to_string(args[0]);
	const char *propname = data_to_string(args[1]);
	int sret;

	servinst_t *si = instance_getdata(inst);

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
    adr_method_t *meth, data_t **ret, data_t **args, int count, data_t **error)
{
	conerr_t err = ce_ok;
	const char *pgname = data_to_string(args[0]);
	const char *propname = data_to_string(args[1]);
	const char *locale = data_to_string(args[2]);

	servinst_t *si = instance_getdata(inst);
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

	data_t *result = data_new_struct(&t__Template);

	char *name;
	if (scf_tmpl_prop_common_name(proptmpl, locale, &name) >= 0)
		struct_set(result, "name", data_new_string(name, lt_free));

	if (scf_tmpl_prop_description(proptmpl, locale, &name) >= 0)
		struct_set(result, "description",
		    data_new_string(name, lt_free));

	if (scf_tmpl_prop_units(proptmpl, locale, &name) >= 0)
		struct_set(result, "units", data_new_string(name, lt_free));

	uint8_t vis;
	if (scf_tmpl_prop_visibility(proptmpl, &vis) == -1) {
		data_free(result);
		goto out;
	}
	data_t *visvalue = NULL;
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
	struct_set(result, "visibility", visvalue);

	scf_values_t values;
	if (scf_tmpl_prop_internal_seps(proptmpl, &values) == 0) {
		data_t *array =
		    data_new_array(&t_array_string, values.value_count);
		for (int i = 0; i < values.value_count; i++)
			(void) array_add(array, data_new_string(
			    values.values_as_strings[i], lt_copy));
		struct_set(result, "separators", array);
		scf_values_destroy(&values);
	}

	if (scf_tmpl_value_name_choices(proptmpl, &values) == 0) {
		data_t *array =
		    data_new_array(&t_array_string, values.value_count);
		for (int i = 0; i < values.value_count; i++)
			(void) array_add(array, data_new_string(
			    values.values_as_strings[i], lt_copy));
		struct_set(result, "allowed", array);
		scf_values_destroy(&values);
	}

	if ((*ret = data_purify_deep(result)) == NULL)
		err = error_scf(error, SCF_ERROR_NO_MEMORY);
out:
	scf_tmpl_prop_destroy(proptmpl);
	scf_tmpl_pg_destroy(pgtmpl);
	scf_handle_destroy(scfhandle);

	return (err);
}

static int
get_localedprop(servinst_t *si, const char *locale, const char *name,
    data_t **ret, data_t **error)
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
			return (ce_ok);
		}
		return (error_scf(error, scferr));
	}

	*ret = data_new_string(str, lt_copy);
	rad_clean_propvec(evec);
	return (ce_ok);
}

/* ARGSUSED */
conerr_t
interface_ServiceInfo_invoke_getCommonName(rad_instance_t *inst,
    adr_method_t *meth, data_t **ret, data_t **args, int count, data_t **error)
{
	const char *locale = data_to_string(args[0]);
	servinst_t *si = instance_getdata(inst);

	if (get_localedprop(si, locale, SCF_PG_TM_COMMON_NAME, ret, NULL)
	    == ce_ok)
		return (ce_ok);
	return (get_localedprop(si, "C", SCF_PG_TM_COMMON_NAME, ret, error));
}

/* ARGSUSED */
conerr_t
interface_ServiceInfo_invoke_getDescription(rad_instance_t *inst,
    adr_method_t *meth, data_t **ret, data_t **args, int count, data_t **error)
{
	const char *locale = data_to_string(args[0]);
	servinst_t *si = instance_getdata(inst);

	if (get_localedprop(si, locale, SCF_PG_TM_DESCRIPTION, ret, NULL)
	    == ce_ok)
		return (ce_ok);
	return (get_localedprop(si, "C", SCF_PG_TM_DESCRIPTION, ret, error));
}

/* ARGSUSED */
conerr_t
interface_ServiceInfo_invoke_getLogInfo(rad_instance_t *inst,
    adr_method_t *meth, data_t **ret, data_t **args, int count, data_t **error)
{
	servinst_t *si = instance_getdata(inst);
	if (!si->instance)
		return (ce_object);

	char *logname = NULL;
	rad_propvec_t evec[] = {
		{ SCF_PROPERTY_LOGFILE, NULL, SCF_TYPE_USTRING, &logname, 0 },
		{ NULL }
	};

	rad_propvec_t *badprop;
	int errval = rad_read_propvec(si->fmri, SCF_PG_RESTARTER, B_FALSE,
	    evec, &badprop);
	if (errval != 0)
		return (ce_object);

	struct stat st;
	if (stat(logname, &st) != 0) {
		free(logname);
		return (ce_object);
	}

	int max_size = data_to_integer(args[0]);

	int bsize = max_size >= 0 && max_size < st.st_size ?
	    max_size : st.st_size;
	char *buffer = malloc(bsize);
	if (buffer == NULL) {
		free(logname);
		return (ce_nomem);
	}

	int fd;
	if ((fd = open(logname, O_RDONLY)) == -1) {
		free(buffer);
		free(logname);
		return (ce_priv);
	}

	if (pread(fd, buffer, bsize, st.st_size - bsize) != bsize) {
		(void) close(fd);
		free(buffer);
		free(logname);
		return (ce_system);
	}

	(void) close(fd);

	data_t *result = data_new_struct(&t__LogInfo);
	struct_set(result, "name", data_new_string(logname, lt_free));
	struct_set(result, "size", data_new_integer(st.st_size));
	struct_set(result, "MTime", data_new_time_ts(&st.st_mtim));
	struct_set(result, "contents", data_new_opaque(buffer, bsize, lt_free));

	if ((*ret = data_purify(result)) == NULL)
		return (ce_object);

	return (ce_ok);
}

/* ARGSUSED */
conerr_t
interface_ServiceInfo_invoke_delete(rad_instance_t *inst, adr_method_t *meth,
    data_t **ret, data_t **args, int count, data_t **error)
{
	conerr_t err = ce_ok;
	servinst_t *si = instance_getdata(inst);

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
    data_t **ret, data_t **args, int count, data_t **error)
{
	servinst_t *si = instance_getdata(inst);
	if (!si->instance)
		return (error_scf(error, SCF_ERROR_INVALID_ARGUMENT));

	return (simple_scf(error, smf_restore_instance(si->fmri)));
}

/* ARGSUSED */
conerr_t
interface_ServiceInfo_invoke_degrade(rad_instance_t *inst, adr_method_t *meth,
    data_t **ret, data_t **args, int count, data_t **error)
{
	servinst_t *si = instance_getdata(inst);
	if (!si->instance)
		return (error_scf(error, SCF_ERROR_INVALID_ARGUMENT));

	return (simple_scf(error, smf_degrade_instance(si->fmri,
	    data_to_boolean(args[0]) ? SMF_IMMEDIATE : 0)));
}

/* ARGSUSED */
conerr_t
interface_ServiceInfo_invoke_maintain(rad_instance_t *inst, adr_method_t *meth,
    data_t **ret, data_t **args, int count, data_t **error)
{
	servinst_t *si = instance_getdata(inst);
	if (!si->instance)
		return (error_scf(error, SCF_ERROR_INVALID_ARGUMENT));

	return (simple_scf(error, smf_maintain_instance(si->fmri,
	    data_to_boolean(args[0]) ? SMF_IMMEDIATE : 0)));
}

/* ARGSUSED */
conerr_t
interface_ServiceInfo_invoke_restart(rad_instance_t *inst, adr_method_t *meth,
    data_t **ret, data_t **args, int count, data_t **error)
{
	servinst_t *si = instance_getdata(inst);
	if (!si->instance)
		return (error_scf(error, SCF_ERROR_INVALID_ARGUMENT));

	return (simple_scf(error, smf_restart_instance(si->fmri)));
}

/* ARGSUSED */
conerr_t
interface_ServiceInfo_invoke_refresh(rad_instance_t *inst, adr_method_t *meth,
    data_t **ret, data_t **args, int count, data_t **error)
{
	servinst_t *si = instance_getdata(inst);
	if (!si->instance)
		return (error_scf(error, SCF_ERROR_INVALID_ARGUMENT));

	return (simple_scf(error, smf_refresh_instance(si->fmri)));
}

/* ARGSUSED */
conerr_t
interface_Aggregator_read_services(rad_instance_t *inst, adr_attribute_t *attr,
    data_t **data, data_t **error)
{
	rad_mutex_enter(&service_lock);
	data_t *result = data_new_array(&t_array__Service, service_count);

	for (servinst_t *si = list_head(&service_list); si != NULL;
	    si = list_next(&service_list, si)) {
		data_t *insts = data_new_array(&t_array_string, si->ninstances);
		for (servinst_t *i = list_head(&si->instances); i != NULL;
		    i = list_next(&si->instances, i))
			(void) array_add(insts, data_new_string(i->iname,
			    lt_copy));

		data_t *service = data_new_struct(&t__Service);
		struct_set(service, "fmri", data_new_string(si->fmri, lt_copy));
		struct_set(service, "objectName", instance_getname(si->inst));
		struct_set(service, "instances", insts);
		(void) array_add(result, service);
	}

	if (data_verify(result, NULL, B_TRUE))
		*data = result;
	else
		data_free(result);

	rad_mutex_exit(&service_lock);
	return (*data != NULL ? ce_ok : ce_object);
}

/* ARGSUSED */
conerr_t
interface_Aggregator_read_instances(rad_instance_t *inst, adr_attribute_t *attr,
    data_t **data, data_t **error)
{
	conerr_t err = ce_ok;

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
	data_t *result = data_new_array(&t_array__Instance, instance_count);

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

		data_t *inst = data_new_struct(&t__Instance);
		struct_set(inst, "fmri", data_new_string(si->fmri, lt_copy));
		struct_set(inst, "objectName", instance_getname(si->inst));
		struct_set(inst, "STime", data_new_time(seconds, ns));
		struct_set(inst, "state", state2enum(statestr));
		if (!data_verify(inst, NULL, B_TRUE))
			data_free(inst);
		else
			(void) array_add(result, inst);
	}

	if ((*data = data_purify(result)) == NULL)
		err = ce_object;
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

	rad_thread_ack(arg, rm_ok);
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

		data_t *stime = NULL, *state = NULL, *nstate = NULL;
		data_t *astate = NULL, *reason = NULL;

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

		data_t *event = data_new_struct(&t__StateChange);
		struct_set(event, "source", instance_getname(si->inst));
		struct_set(event, "state", state);
		struct_set(event, "nextState", nstate);
		struct_set(event, "stateTime", stime);
		struct_set(event, "auxState", astate);
		struct_set(event, "reason", reason);
		struct_set(event, "anomaly", data_new_boolean(B_FALSE));
		if (data_verify(event, NULL, B_FALSE)) {
			rad_log(RL_DEBUG, "sending SMF event");
			if (agg_inst != NULL)
				instance_notify(agg_inst, "statechange",
				    0, data_ref(event));
			instance_notify(si->inst, "statechange", 0, event);
		} else {
			rad_log(RL_DEBUG, "failed to send SMF event");
			data_free(event);
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

	return (rm_system);
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
		objname = adr_name_vcreate(
		    "com.oracle.solaris.vp.panel.common.api.smf_old", 3,
		    "type", "service", "service", sname, "instance", iname);
	} else {
		list_create(&si->instances, sizeof (servinst_t),
		    offsetof(servinst_t, snode));
		(void) asprintf(&si->fmri, "svc:/%s", sname);
		objname = adr_name_vcreate(
		    "com.oracle.solaris.vp.panel.common.api.smf_old", 2,
		    "type", "service", "service", sname);
	}
	si->inst = instance_create(objname, &interface_ServiceInfo_svr,
	    si, NULL);
	(void) cont_insert(rad_container, si->inst, INST_ID_PICK);

	if (inst) {
		list_insert_tail(&instance_list, si);
		instance_count++;
	} else {
		list_insert_tail(&service_list, si);
		service_count++;
	}


	return (si);
}

static rad_modinfo_t modinfo = { "smf_old", "Legacy SMF module" };

int
_rad_init(void *handle)
{
	if (rad_module_register(handle, RAD_MODVERSION, &modinfo) == -1)
		return (-1);

	if (rad_isproxy)
		return (0);

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

	agg_inst = instance_create(adr_name_fromstr(aggregator_pattern),
	    &interface_Aggregator_svr, NULL, NULL);
	if (agg_inst != NULL)
		(void) cont_insert(rad_container, agg_inst, INST_ID_PICK);

	if (rad_thread_create(notify_thread, NULL) != rm_ok)
		rad_log(RL_ERROR, "failed to start SMF listener");
	return (0);
}
