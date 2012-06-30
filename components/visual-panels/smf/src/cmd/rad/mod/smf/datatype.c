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
#include <limits.h>

#include <libscf.h>
#include <libscf_priv.h>

#include <rad/adr.h>
#include <rad/rad_modapi.h>

#include "api_smf.h"
#include "rhandle.h"
#include "smfutil.h"
#include "datatype.h"

/*
 * Routines for creating ADR data objects from SCF types or objects.
 * Consumed by the API entry points.
 */

adr_data_t *
create_SMFState(const char *state)
{
	if (strcmp(state, SCF_STATE_STRING_UNINIT) == 0) {
		return (&e__SMFState_UNINIT);
	} else if (strcmp(state, SCF_STATE_STRING_MAINT) == 0) {
		return (&e__SMFState_MAINT);
	} else if (strcmp(state, SCF_STATE_STRING_LEGACY) == 0) {
		return (&e__SMFState_LEGACY);
	} else {
		return (adr_data_new_enum_byname(&t__SMFState, state));
	}
}

static adr_data_t *
create_DepGrouping(const char *grouping)
{
	if (strcmp(grouping, SCF_DEP_REQUIRE_ALL) == 0)
		return (&e__DepGrouping_REQUIRE_ALL);
	else if (strcmp(grouping, SCF_DEP_REQUIRE_ANY) == 0)
		return (&e__DepGrouping_REQUIRE_ANY);
	else if (strcmp(grouping, SCF_DEP_EXCLUDE_ALL) == 0)
		return (&e__DepGrouping_EXCLUDE_ALL);
	else if (strcmp(grouping, SCF_DEP_OPTIONAL_ALL) == 0)
		return (&e__DepGrouping_OPTIONAL_ALL);
	return (NULL);
}

static adr_data_t *
create_DepRestart(const char *restarton)
{
	if (strcmp(restarton, SCF_DEP_RESET_ON_ERROR) == 0)
		return (&e__DepRestart_ERROR);
	if (strcmp(restarton, SCF_DEP_RESET_ON_RESTART) == 0)
		return (&e__DepRestart_RESTART);
	if (strcmp(restarton, SCF_DEP_RESET_ON_REFRESH) == 0)
		return (&e__DepRestart_REFRESH);
	if (strcmp(restarton, SCF_DEP_RESET_ON_NONE) == 0)
		return (&e__DepRestart_NONE);
	return (NULL);
}

static adr_data_t *
create_PropertyType(scf_type_t type)
{
	adr_data_t *result = adr_data_new_enum(&t__PropertyType, type);
	assert(result != NULL);
	return (result);
}

scf_type_t
from_PropertyType(adr_data_t *type)
{
	return (adr_enum_tovalue(type));
}

static adr_data_t *
create_PropertyVisibility(uint8_t visibility)
{
	switch (visibility) {
	case SCF_TMPL_VISIBILITY_HIDDEN:
		return (&e__PropertyVisibility_HIDDEN);
	case SCF_TMPL_VISIBILITY_READONLY:
		return (&e__PropertyVisibility_READONLY);
	case SCF_TMPL_VISIBILITY_READWRITE:
		return (&e__PropertyVisibility_READWRITE);
	}
	return (NULL);
}

/*
 * Creates a Dependency object.
 *
 * A return value of SE_NOTFOUND implies that the property group wasn't
 * a dependency and should be skipped.
 */
svcerr_t
create_Dependency(scf_handle_t *scfhandle, scf_propertygroup_t *pg,
    adr_data_t **ret)
{
	svcerr_t se = SE_OK;
	char type[max_pgtype + 1];
	char grouping[max_value + 1];
	char restarton[max_value + 1];
	char pgname[max_name + 1];

	scf_iter_t *iter = scf_iter_create(scfhandle);
	scf_property_t *prop = scf_property_create(scfhandle);
	scf_value_t *val = scf_value_create(scfhandle);

	if (iter == NULL || prop == NULL || val == NULL) {
		se = SE_FATAL;
		goto out;
	}

	if (scf_pg_get_name(pg, pgname, sizeof (pgname)) == -1 ||
	    scf_pg_get_property(pg, SCF_PROPERTY_GROUPING, prop) != 0 ||
	    scf_property_get_value(prop, val) != 0 ||
	    scf_value_get_as_string(val, grouping, sizeof (grouping)) == -1 ||
	    scf_pg_get_property(pg, SCF_PROPERTY_RESTART_ON, prop) != 0 ||
	    scf_property_get_value(prop, val) != 0 ||
	    scf_value_get_as_string(val, restarton, sizeof (restarton)) == -1 ||
	    scf_pg_get_property(pg, SCF_PROPERTY_ENTITIES, prop) != 0 ||
	    scf_iter_property_values(iter, prop) != 0) {
		se = smfu_maperr(scf_error());
		goto out;
	}

	adr_data_t *group = create_DepGrouping(grouping);
	adr_data_t *restart = create_DepRestart(restarton);
	if (group == NULL || restart == NULL) {
		se = SE_NOTFOUND;
		goto out;
	}

	adr_data_t *result = adr_data_new_struct(&t__Dependency);
	adr_struct_set(result, "name", adr_data_new_string(pgname, LT_COPY));
	adr_struct_set(result, "grouping", group);
	adr_struct_set(result, "restartOn", restart);
	adr_data_t *array = adr_data_new_array(&adr_t_array_string, 5);
	adr_struct_set(result, "target", array);

	while (scf_iter_next_value(iter, val) > 0) {
		if (scf_value_get_as_string(val, type, sizeof (type)) == -1) {
			se = smfu_maperr(scf_error());
			adr_data_free(result);
			goto out;
		}
		(void) adr_array_add(array, adr_data_new_string(type, LT_COPY));
	}
	if (!adr_data_verify(result, NULL, B_TRUE)) {
		se = SE_FATAL;
		adr_data_free(result);
		goto out;
	}

	*ret = result;
out:
	scf_value_destroy(val);
	scf_property_destroy(prop);
	scf_iter_destroy(iter);
	return (se);
}

/*
 * Creates a Manpage object.
 *
 * A return value of SE_NOTFOUND implies that the property group wasn't
 * a man page and should be skipped.
 */
svcerr_t
create_Manpage(scf_handle_t *scfhandle, scf_propertygroup_t *pg,
    adr_data_t **ret)
{
	char manpath[max_value + 1];
	char section[max_value + 1];
	char title[max_name + 1];
	char pgname[max_name + 1];
	svcerr_t se = SE_OK;

	if (scf_pg_get_name(pg, pgname, sizeof (pgname)) == -1)
		return (smfu_maperr(scf_error()));

	if (strncmp(SCF_PG_TM_MAN_PREFIX, pgname,
	    strlen(SCF_PG_TM_MAN_PREFIX)) != 0)
		return (SE_NOTFOUND);


	scf_property_t *prop = scf_property_create(scfhandle);
	scf_value_t *val = scf_value_create(scfhandle);

	if (prop == NULL || val == NULL) {
		se = SE_FATAL;
		goto out;
	}

	if (scf_pg_get_property(pg, SCF_PROPERTY_TM_MANPATH, prop) != 0 ||
	    scf_property_get_value(prop, val) != 0 ||
	    scf_value_get_as_string(val, manpath, sizeof (manpath)) == -1 ||
	    scf_pg_get_property(pg, SCF_PROPERTY_TM_TITLE, prop) != 0 ||
	    scf_property_get_value(prop, val) != 0 ||
	    scf_value_get_as_string(val, title, sizeof (title)) == -1 ||
	    scf_pg_get_property(pg, SCF_PROPERTY_TM_SECTION, prop) != 0 ||
	    scf_property_get_value(prop, val) != 0 ||
	    scf_value_get_as_string(val, section, sizeof (section)) == -1) {
		se = smfu_maperr(scf_error());
		goto out;
	}

	adr_data_t *result = adr_data_new_struct(&t__Manpage);
	adr_struct_set(result, "title", adr_data_new_string(title, LT_COPY));
	adr_struct_set(result, "section",
	    adr_data_new_string(section, LT_COPY));
	if (strcmp(manpath, ":default") != 0) {
		adr_data_t *mp = adr_data_new_string(manpath, LT_COPY);
		if (mp == NULL) {
			se = SE_FATAL;
			adr_data_free(result);
			goto out;
		}
		adr_struct_set(result, "path",
		    adr_data_new_string(manpath, LT_COPY));
	}

	if (!adr_data_verify(result, NULL, B_TRUE)) {
		se = SE_FATAL;
		adr_data_free(result);
		goto out;
	}

	*ret = result;
out:
	scf_value_destroy(val);
	scf_property_destroy(prop);
	return (se);
}

/*
 * Creates a Doclink object.
 *
 * A return value of SE_NOTFOUND implies that the property group wasn't
 * a doclink and should be skipped.
 */
svcerr_t
create_Doclink(scf_handle_t *scfhandle, scf_propertygroup_t *pg,
    adr_data_t **ret)
{
	char name[max_value + 1];
	char uri[max_value + 1];
	char pgname[max_name + 1];
	svcerr_t se = SE_OK;

	if (scf_pg_get_name(pg, pgname, sizeof (pgname)) == -1)
		return (smfu_maperr(scf_error()));

	if (strncmp(SCF_PG_TM_DOC_PREFIX, pgname,
	    strlen(SCF_PG_TM_DOC_PREFIX)) != 0)
		return (SE_NOTFOUND);

	scf_property_t *prop = scf_property_create(scfhandle);
	scf_value_t *val = scf_value_create(scfhandle);

	if (prop == NULL || val == NULL) {
		se = SE_FATAL;
		goto out;
	}

	if (scf_pg_get_property(pg, SCF_PROPERTY_TM_NAME, prop) != 0 ||
	    scf_property_get_value(prop, val) != 0 ||
	    scf_value_get_as_string(val, name, sizeof (name)) == -1 ||
	    scf_pg_get_property(pg, SCF_PROPERTY_TM_URI, prop) != 0 ||
	    scf_property_get_value(prop, val) != 0 ||
	    scf_value_get_as_string(val, uri, sizeof (uri)) == -1) {
		se = smfu_maperr(scf_error());
		goto out;
	}

	adr_data_t *result = adr_data_new_struct(&t__Doclink);
	adr_struct_set(result, "name", adr_data_new_string(name, LT_COPY));
	adr_struct_set(result, "uri", adr_data_new_string(uri, LT_COPY));

	if (!adr_data_verify(result, NULL, B_TRUE)) {
		se = SE_FATAL;
		adr_data_free(result);
		goto out;
	}

	*ret = result;
out:
	scf_value_destroy(val);
	scf_property_destroy(prop);
	return (se);
}

svcerr_t
create_PropertyGroup(scf_propertygroup_t *pg, adr_data_t **ret)
{
	char name[max_value + 1];
	char type[max_pgtype + 1];
	uint32_t flags;
	svcerr_t se = SE_OK;

	if (scf_pg_get_name(pg, name, sizeof (name)) == -1 ||
	    scf_pg_get_type(pg, type, sizeof (type)) == -1 ||
	    scf_pg_get_flags(pg, &flags) == -1) {
		se = smfu_maperr(scf_error());
		goto out;
	}

	adr_data_t *result = adr_data_new_struct(&t__PropertyGroup);
	adr_struct_set(result, "name", adr_data_new_string(name, LT_COPY));
	adr_struct_set(result, "type", adr_data_new_string(type, LT_COPY));
	adr_struct_set(result, "flags", adr_data_new_uinteger(flags));

	if (!adr_data_verify(result, NULL, B_TRUE)) {
		se = SE_FATAL;
		adr_data_free(result);
		goto out;
	}

	*ret = result;
out:
	return (se);
}

svcerr_t
create_Property(scf_property_t *prop, scf_iter_t *iter, scf_value_t *value,
    adr_data_t **ret, adr_data_t **error)
{
	char name[max_name + 1];
	scf_type_t type;

	if (scf_property_get_name(prop, name, sizeof (name)) == -1 ||
	    scf_property_type(prop, &type) == -1 ||
	    scf_iter_property_values(iter, prop))
		return (smfu_maperr(scf_error()));

	adr_data_t *values = adr_data_new_array(&adr_t_array_string, 5);
	int err;
	while ((err = scf_iter_next_value(iter, value)) > 0) {
		char *valstr;
		if (smfu_value_get_string(value, &valstr) != 0) {
			adr_data_free(values);
			return (SE_FATAL);
		}
		(void) adr_array_add(values,
		    adr_data_new_string(valstr, LT_FREE));
	}
	if (err != 0) {
		if (scf_error() == SCF_ERROR_PERMISSION_DENIED)
			return (error_scf(error, &e__ErrorCode_DENIED, NULL,
			    NULL, NULL));
		else
			return (smfu_maperr(scf_error()));
	}

	adr_data_t *result = adr_data_new_struct(&t__Property);
	adr_struct_set(result, "name", adr_data_new_string(name, LT_COPY));
	adr_struct_set(result, "type", create_PropertyType(type));
	adr_struct_set(result, "values", values);
	*ret = result;

	return (SE_OK);
}

svcerr_t
create_Properties(scf_handle_t *scfhandle, scf_propertygroup_t *pg,
    adr_data_t **ret, adr_data_t **error)
{
	svcerr_t se = SE_OK;
	scf_iter_t *piter = scf_iter_create(scfhandle);
	scf_iter_t *viter = scf_iter_create(scfhandle);
	scf_value_t *value = scf_value_create(scfhandle);
	scf_property_t *prop = scf_property_create(scfhandle);
	adr_data_t *result = adr_data_new_array(&t_array__Property, 5);

	if (piter == NULL || viter == NULL || value == NULL || prop == NULL) {
		se = SE_FATAL;
		goto out;
	}

	if (scf_iter_pg_properties(piter, pg) == -1) {
		se = smfu_maperr(scf_error());
		goto out;
	}

	int err;
	while ((err = scf_iter_next_property(piter, prop)) > 0) {
		adr_data_t *propdata = NULL;
		if ((se = create_Property(prop, viter, value, &propdata,
		    error)) != SE_OK)
			goto out;
		(void) adr_array_add(result, propdata);
	}
	if (err != 0)
		se = smfu_maperr(scf_error());

out:
	if (se != SE_OK)
		adr_data_free(result);
	else
		*ret = result;

	scf_iter_destroy(piter);
	scf_iter_destroy(viter);
	scf_value_destroy(value);
	scf_property_destroy(prop);

	return (se);
}

svcerr_t
create_ExtendedState(scf_handle_t *scfhandle, scf_instance_t *instance,
    adr_data_t **ret)
{
	scf_propertygroup_t *pg = scf_pg_create(scfhandle);
	scf_property_t *prop = scf_property_create(scfhandle);
	scf_value_t *value = scf_value_create(scfhandle);
	adr_data_t *result = adr_data_new_struct(&t__ExtendedState);
	svcerr_t se = SE_FATAL;
	int serr;
	adr_data_t *dstr;
	char *str;
	int64_t sec;
	int32_t nsec;
	uint64_t ctid;
	uint8_t bool;

	if (pg == NULL || prop == NULL || value == NULL)
		goto error;

	if (scf_instance_get_pg(instance, SCF_PG_RESTARTER, pg) == -1)
		goto scferror;

	if (scf_pg_get_property(pg, SCF_PROPERTY_STATE, prop) == -1 ||
	    scf_property_get_value(prop, value) == -1)
		goto scferror;
	if (smfu_value_get_string(value, &str) != 0)
		goto error;
	adr_struct_set(result, "state", create_SMFState(str));
	free(str);

	if (scf_pg_get_property(pg, SCF_PROPERTY_NEXT_STATE, prop) == -1 ||
	    scf_property_get_value(prop, value) == -1)
		goto scferror;
	if (smfu_value_get_string(value, &str) != 0)
		goto error;
	adr_struct_set(result, "nextState", create_SMFState(str));
	free(str);

	if (scf_pg_get_property(pg, SCF_PROPERTY_AUX_STATE, prop) == -1 ||
	    scf_property_get_value(prop, value) == -1)
		goto scferror;
	if (smfu_value_get_string(value, &str) != 0)
		goto error;
	if ((dstr = adr_data_new_string(str, LT_FREE)) == NULL)
		goto error;
	adr_struct_set(result, "auxstate", dstr);

	if (scf_pg_get_property(pg, SCF_PROPERTY_STATE_TIMESTAMP, prop) == -1 ||
	    scf_property_get_value(prop, value) == -1 ||
	    scf_value_get_time(value, &sec, &nsec) == -1)
		goto scferror;
	adr_struct_set(result, "stime", adr_data_new_time(sec, nsec));

	if (scf_pg_get_property(pg, SCF_PROPERTY_CONTRACT, prop) == -1 ||
	    scf_property_get_value(prop, value) == -1) {
		if (scf_error() == SCF_ERROR_NOT_FOUND)
			adr_struct_set(result, "contractid",
			    adr_data_new_integer(-1));
		else
			goto scferror;
	} else if (scf_value_get_count(value, &ctid) == -1) {
		goto scferror;
	} else {
		adr_struct_set(result, "contractid",
		    adr_data_new_integer(ctid <= INT_MAX ? ctid : -1));
	}

	if ((serr = smfu_read_enabled(instance, pg, prop, value, SCF_PG_GENERAL,
	    &bool)) != 0) {
		se = smfu_maperr(serr);
		goto error;
	}
	adr_data_t *persist = adr_data_new_boolean(bool > 0);
	adr_struct_set(result, "enabled", persist);

	if ((serr = smfu_read_enabled(instance, pg, prop, value,
	    SCF_PG_GENERAL_OVR, &bool)) == 0) {
		adr_struct_set(result, "enabled_temp",
		    adr_data_new_boolean(bool > 0));
	} else if (serr == SCF_ERROR_NOT_FOUND) {
		adr_struct_set(result, "enabled_temp", adr_data_ref(persist));
	} else {
		se = smfu_maperr(serr);
		goto error;
	}

	*ret = result;

	return (SE_OK);

scferror:
	se = smfu_maperr(scf_error());
error:
	adr_data_free(result);
	return (se);
}

svcerr_t
create_PGTemplate(scf_pg_tmpl_t *pgtmpl, const char *locale, adr_data_t **ret)
{
	adr_data_t *pt = adr_data_new_struct(&t__PGTemplate);
	adr_data_t *dstr;
	char *str;
	svcerr_t se = SE_FATAL;

	if (scf_tmpl_pg_name(pgtmpl, &str) == -1)
		goto scferror;
	adr_struct_set(pt, "pgname", adr_data_new_string(str, LT_FREE));

	if (scf_tmpl_pg_type(pgtmpl, &str) == -1)
		goto scferror;
	adr_struct_set(pt, "pgtype", adr_data_new_string(str, LT_FREE));

	if (scf_tmpl_pg_common_name(pgtmpl, locale, &str) == -1) {
		if (scf_error() != SCF_ERROR_NOT_FOUND)
			goto scferror;
	} else {
		if ((dstr = adr_data_new_string(str, LT_FREE)) == NULL)
			goto error;
		adr_struct_set(pt, "name", dstr);
	}

	if (scf_tmpl_pg_description(pgtmpl, locale, &str) == -1) {
		if (scf_error() != SCF_ERROR_NOT_FOUND)
			goto scferror;
	} else {
		if ((dstr = adr_data_new_string(str, LT_FREE)) == NULL)
			goto error;
		adr_struct_set(pt, "description", dstr);
	}

	uint8_t req;
	if (scf_tmpl_pg_required(pgtmpl, &req) == -1) {
		if (scf_error() != SCF_ERROR_NOT_FOUND)
			goto scferror;
		req = 0;
	}
	adr_struct_set(pt, "required", adr_data_new_boolean(req > 0));

	*ret = pt;
	return (SE_OK);

scferror:
	se = smfu_maperr(scf_error());
error:
	adr_data_free(pt);
	return (se);
}

svcerr_t
create_PropTemplate(scf_prop_tmpl_t *proptmpl, const char *locale,
    adr_data_t **ret)
{
	adr_data_t *pt = adr_data_new_struct(&t__PropTemplate);
	adr_data_t *dstr;
	char *str;
	svcerr_t se = SE_FATAL;

	if (scf_tmpl_prop_name(proptmpl, &str) == -1)
		goto error;
	adr_struct_set(pt, "propname", adr_data_new_string(str, LT_FREE));

	scf_type_t type;
	if (scf_tmpl_prop_type(proptmpl, &type) == -1) {
		if (scf_error() != SCF_ERROR_NOT_FOUND)
			goto scferror;
		type = SCF_TYPE_INVALID;
	}
	adr_struct_set(pt, "proptype", create_PropertyType(type));

	if (scf_tmpl_prop_common_name(proptmpl, locale, &str) == -1) {
		if (scf_error() != SCF_ERROR_NOT_FOUND)
			goto scferror;
	} else {
		if ((dstr = adr_data_new_string(str, LT_FREE)) == NULL)
			goto error;
		adr_struct_set(pt, "name", dstr);
	}

	if (scf_tmpl_prop_description(proptmpl, locale, &str) == -1) {
		if (scf_error() != SCF_ERROR_NOT_FOUND)
			goto scferror;
	} else {
		if ((dstr = adr_data_new_string(str, LT_FREE)) == NULL)
			goto error;
		adr_struct_set(pt, "description", dstr);
	}

	if (scf_tmpl_prop_units(proptmpl, locale, &str) == -1) {
		if (scf_error() != SCF_ERROR_NOT_FOUND)
			goto scferror;
	} else {
		if ((dstr = adr_data_new_string(str, LT_FREE)) == NULL)
			goto error;
		adr_struct_set(pt, "units", dstr);
	}

	uint8_t req;
	if (scf_tmpl_prop_required(proptmpl, &req) == -1) {
		if (scf_error() != SCF_ERROR_NOT_FOUND)
			goto scferror;
		req = 0;
	}
	adr_struct_set(pt, "required", adr_data_new_boolean(req > 0));

	uint64_t min, max;
	if (scf_tmpl_prop_cardinality(proptmpl, &min, &max) == -1) {
		if (scf_error() != SCF_ERROR_NOT_FOUND)
			goto scferror;
		min = max = 0;
	}
	adr_struct_set(pt, "cardinality_min", adr_data_new_ulong(min));
	adr_struct_set(pt, "cardinality_max", adr_data_new_ulong(max));

	uint8_t vis;
	if (scf_tmpl_prop_visibility(proptmpl, &vis) == -1) {
		if (scf_error() != SCF_ERROR_NOT_FOUND)
			goto scferror;
		vis = SCF_TMPL_VISIBILITY_READWRITE;
	}
	adr_struct_set(pt, "visibility", create_PropertyVisibility(vis));

	scf_values_t values;
	if (scf_tmpl_prop_internal_seps(proptmpl, &values) == 0) {
		adr_data_t *array =
		    adr_data_new_array(&adr_t_array_string, values.value_count);
		for (int i = 0; i < values.value_count; i++)
			(void) adr_array_add(array, adr_data_new_string(
			    values.values_as_strings[i], LT_COPY));
		if (!adr_data_verify(array, NULL, B_TRUE)) {
			adr_data_free(array);
			goto error;
		}
		adr_struct_set(pt, "separators", array);
		scf_values_destroy(&values);
	} else {
		if (scf_error() != SCF_ERROR_NOT_FOUND)
			goto scferror;
	}

	*ret = pt;
	return (SE_OK);

scferror:
	se = smfu_maperr(scf_error());
error:
	adr_data_free(pt);
	return (se);
}


svcerr_t
create_Instance(scf_instance_t *instance, const char *sname, const char *iname,
    adr_data_t **data, scf_propertygroup_t *pg, scf_property_t *prop,
    scf_value_t *val)
{
	char statestr[MAX_SCF_STATE_STRING_SZ];
	ssize_t len;
	int64_t seconds;
	int32_t nsec;

	if (scf_instance_get_pg(instance, SCF_PG_RESTARTER, pg) != 0)
		return (smfu_maperr(scf_error()));

	if (scf_pg_get_property(pg, SCF_PROPERTY_STATE, prop) != 0 ||
	    scf_property_get_value(prop, val) != 0 ||
	    (len = scf_value_get_as_string(val, statestr,
	    MAX_SCF_STATE_STRING_SZ)) == -1) {
		return (smfu_maperr(scf_error()));
	} else if (len > MAX_SCF_STATE_STRING_SZ - 1) {
		return (SE_FATAL);
	}

	if (scf_pg_get_property(pg, SCF_PROPERTY_STATE_TIMESTAMP, prop) != 0 ||
	    scf_property_get_value(prop, val) != 0 ||
	    scf_value_get_time(val, &seconds, &nsec) != 0)
		return (smfu_maperr(scf_error()));

	adr_data_t *inst = adr_data_new_struct(&t__Instance);
	adr_struct_set(inst, "fmri",
	    adr_data_new_string(smfu_fmri_alloc(sname, iname), LT_FREE));
	adr_struct_set(inst, "objectName",
	    adr_data_new_name(smfu_name_alloc(sname, iname)));
	adr_struct_set(inst, "stime", adr_data_new_time(seconds, nsec));
	adr_struct_set(inst, "state", create_SMFState(statestr));

	if (!adr_data_verify(inst, NULL, B_TRUE)) {
		adr_data_free(inst);
		return (SE_FATAL);
	}

	*data = inst;
	return (SE_OK);
}
