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

#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <rad/adr.h>
#include <rad/adr_object.h>
#include <rad/rad_modapi.h>
#include <stdio.h>
#include <errno.h>
#include <libscf.h>
#include <libscf_priv.h>
#include "api_smf.h"
#include "rhandle.h"
#include "smfutil.h"
#include "datatype.h"

/*ARGSUSED*/
conerr_t
interface_Instance_read_instance(rad_instance_t *inst, adr_attribute_t *attr,
    data_t **data, data_t **error)
{
	smfobj_t *smfo = instance_getdata(inst);
	*data = data_new_string(smfo->iname, lt_copy);
	return (*data == NULL ? ce_nomem : ce_ok);
}


/*ARGSUSED*/
static svcerr_t
rt_read_restarter(scf_handle_t *h, void *arg, data_t **ret, data_t **error)
{
	smfobj_t *smfo = arg;
	smfu_entity_t entity = SMFU_ENTITY_INIT;
	svcerr_t se = SE_OK;
	char fmri[max_fmri + 1];

	scf_propertygroup_t *pg = scf_pg_create(h);
	scf_property_t *prop = scf_property_create(h);
	scf_value_t *value = scf_value_create(h);

	if (pg == NULL || prop == NULL || value == NULL) {
		se = SE_FATAL;
		goto done;
	}

	if ((se = smfu_lookup(h, smfo->sname, smfo->iname, &entity)) != SE_OK)
		goto done;
	se = smfu_get_pg_r(h, &entity, SCF_PG_GENERAL, pg);
	if (se != SE_OK)
		goto done;

	if (scf_pg_get_property(pg, SCF_PROPERTY_RESTARTER, prop) == -1) {
		if (scf_error() == SCF_ERROR_NOT_FOUND)
			*ret = data_new_string(SCF_SERVICE_STARTD, lt_const);
		else
			se = smfu_maperr(scf_error());
		goto done;
	}

	if (scf_property_get_value(prop, value) == -1 ||
	    scf_value_get_as_string(value, fmri, sizeof (fmri)) == -1) {
		se = smfu_maperr(scf_error());
		goto done;
	}

	*ret = data_new_string(fmri, lt_copy);

done:
	scf_value_destroy(value);
	scf_property_destroy(prop);
	scf_pg_destroy(pg);
	smfu_entity_destroy(&entity);

	return (se);
}

/*ARGSUSED*/
conerr_t
interface_Instance_read_restarter(rad_instance_t *inst, adr_attribute_t *attr,
    data_t **data, data_t **error)
{
	return (smfu_rtrun(rt_read_restarter, instance_getdata(inst), data,
	    error));
}


/*ARGSUSED*/
static svcerr_t
rt_read_enabled(scf_handle_t *h, void *arg, data_t **ret, data_t **error)
{
	smfobj_t *smfo = arg;
	smfu_entity_t entity = SMFU_ENTITY_INIT;
	svcerr_t se = SE_OK;

	scf_propertygroup_t *pg = scf_pg_create(h);
	scf_property_t *prop = scf_property_create(h);
	scf_value_t *value = scf_value_create(h);

	if (pg == NULL || prop == NULL || value == NULL) {
		se = SE_FATAL;
		goto done;
	}

	if ((se = smfu_lookup(h, smfo->sname, smfo->iname, &entity)) != SE_OK)
		goto done;

	uint8_t bool;
	scf_error_t serr = smfu_read_enabled(entity.instance, pg, prop,
	    value, SCF_PG_GENERAL_OVR, &bool);
	if (serr == SCF_ERROR_NOT_FOUND)
		serr = smfu_read_enabled(entity.instance, pg, prop,
		    value, SCF_PG_GENERAL, &bool);

	if (serr == 0)
		*ret = data_new_boolean(bool > 0);
	else
		se = smfu_maperr(serr);

done:
	scf_value_destroy(value);
	scf_property_destroy(prop);
	scf_pg_destroy(pg);
	smfu_entity_destroy(&entity);

	return (se);
}

/*ARGSUSED*/
conerr_t
interface_Instance_read_enabled(rad_instance_t *inst, adr_attribute_t *attr,
    data_t **data, data_t **error)
{
	return (smfu_rtrun(rt_read_enabled, instance_getdata(inst), data,
	    error));
}


/*ARGSUSED*/
static svcerr_t
rt_read_state(scf_handle_t *h, void *arg, data_t **ret, data_t **error)
{
	smfobj_t *smfo = arg;
	smfu_entity_t entity = SMFU_ENTITY_INIT;
	svcerr_t se = SE_OK;
	char statestr[MAX_SCF_STATE_STRING_SZ];

	scf_propertygroup_t *pg = scf_pg_create(h);
	scf_property_t *prop = scf_property_create(h);
	scf_value_t *value = scf_value_create(h);

	if (pg == NULL || prop == NULL || value == NULL) {
		se = SE_FATAL;
		goto done;
	}

	if ((se = smfu_lookup(h, smfo->sname, smfo->iname, &entity)) != SE_OK)
		goto done;

	if (scf_instance_get_pg(entity.instance, SCF_PG_RESTARTER, pg) == -1 ||
	    scf_pg_get_property(pg, SCF_PROPERTY_STATE, prop) == -1 ||
	    scf_property_get_value(prop, value) == -1 ||
	    scf_value_get_as_string(value, statestr, sizeof (statestr)) == -1) {
		se = smfu_maperr(scf_error());
		goto done;
	}

	*ret = create_SMFState(statestr);
done:
	scf_value_destroy(value);
	scf_property_destroy(prop);
	scf_pg_destroy(pg);
	smfu_entity_destroy(&entity);
	return (se);
}

/*ARGSUSED*/
conerr_t
interface_Instance_read_state(rad_instance_t *inst, adr_attribute_t *attr,
    data_t **data, data_t **error)
{
	return (smfu_rtrun(rt_read_state, instance_getdata(inst), data, error));
}


/*ARGSUSED*/
static svcerr_t
rt_read_ex_state(scf_handle_t *h, void *arg, data_t **ret, data_t **error)
{
	smfobj_t *smfo = arg;
	smfu_entity_t entity = SMFU_ENTITY_INIT;
	svcerr_t se = SE_OK;

	if ((se = smfu_lookup(h, smfo->sname, smfo->iname, &entity)) != SE_OK)
		return (SE_FATAL);

	se = create_ExtendedState(h, entity.instance, ret);
	smfu_entity_destroy(&entity);
	return (se);
}

/*ARGSUSED*/
conerr_t
interface_Instance_read_ex_state(rad_instance_t *inst, adr_attribute_t *attr,
    data_t **data, data_t **error)
{
	return (smfu_rtrun(rt_read_ex_state, instance_getdata(inst), data,
	    error));
}


/*ARGSUSED*/
static svcerr_t
rt_read_snapshots(scf_handle_t *h, void *arg, data_t **ret, data_t **error)
{
	smfobj_t *smfo = arg;
	smfu_entity_t entity = SMFU_ENTITY_INIT;
	svcerr_t se = SE_OK;
	char sname[max_name + 1];

	scf_snapshot_t *snap = scf_snapshot_create(h);
	scf_iter_t *iter = scf_iter_create(h);
	data_t *rdata = data_new_array(&t_array_string, 6);

	if (snap == NULL || iter == NULL) {
		se = SE_FATAL;
		goto done;
	}

	if ((se = smfu_lookup(h, smfo->sname, smfo->iname, &entity)) != SE_OK)
		goto done;

	if (scf_iter_instance_snapshots(iter, entity.instance) == -1) {
		se = smfu_maperr(scf_error());
		goto done;
	}

	int e;
	while ((e = scf_iter_next_snapshot(iter, snap)) > 0) {
		if (scf_snapshot_get_name(snap, sname, sizeof (sname)) == -1) {
			se = smfu_maperr(scf_error());
			goto done;
		}
		(void) array_add(rdata, data_new_string(sname, lt_copy));
	}
	if (e != 0)
		se = smfu_maperr(scf_error());

done:
	smfu_entity_destroy(&entity);
	scf_iter_destroy(iter);
	scf_snapshot_destroy(snap);
	*ret = rdata;

	return (se);
}

/*ARGSUSED*/
conerr_t
interface_Instance_read_snapshots(rad_instance_t *inst, adr_attribute_t *attr,
    data_t **data, data_t **error)
{
	return (smfu_rtrun(rt_read_snapshots, instance_getdata(inst), data,
	    error));
}


static svcerr_t
rt_invoke_readSnapshotPGs(scf_handle_t *h, void *arg, data_t **ret,
    data_t **error)
{
	radarg_t *ra = arg;
	smfobj_t *smfo = instance_getdata(ra->inst);
	const char *snapname =
	    ra->args[0] == NULL ? NULL : data_to_string(ra->args[0]);
	smfu_entity_t entity = SMFU_ENTITY_INIT;
	svcerr_t se = SE_OK;
	scf_error_t serr;

	scf_propertygroup_t *pg = scf_pg_create(h);
	scf_iter_t *iter = scf_iter_create(h);
	data_t *result = data_new_array(&t_array__PropertyGroup, 5);

	if (pg == NULL || iter == NULL) {
		se = SE_FATAL;
		goto done;
	}

	if ((se = smfu_lookup(h, smfo->sname, smfo->iname, &entity)) != SE_OK)
		goto done;

	if ((serr = smfu_instance_iter_composed_pgs(h, entity.instance,
	    snapname, NULL, iter)) != 0) {
		if (serr == SCF_ERROR_NOT_FOUND)
			se = error_scf(error, &e__ErrorCode_NOTFOUND,
			    &e__ErrorTarget_SNAPSHOT, NULL, NULL);
		else
			se = smfu_maperr(serr);
		goto done;
	}

	int e;
	while ((e = scf_iter_next_pg(iter, pg)) > 0) {
		data_t *dep;
		if ((se = create_PropertyGroup(pg, &dep)) != SE_OK)
			goto done;
		(void) array_add(result, dep);
	}
	if (e != 0)
		se = smfu_maperr(scf_error());

done:
	*ret = result;
	scf_iter_destroy(iter);
	scf_pg_destroy(pg);
	smfu_entity_destroy(&entity);
	return (se);
}

/*ARGSUSED*/
conerr_t
interface_Instance_invoke_readSnapshotPGs(rad_instance_t *inst,
    adr_method_t *meth, data_t **ret, data_t **args, int count, data_t **error)
{
	radarg_t ra = { .inst = inst, .args = args };
	return (smfu_rtrun(rt_invoke_readSnapshotPGs, &ra, ret, error));
}


static svcerr_t
rt_invoke_readSnapshotProperties(scf_handle_t *h, void *arg, data_t **ret,
    data_t **error)
{
	radarg_t *ra = arg;
	smfobj_t *smfo = instance_getdata(ra->inst);
	const char *snapname =
	    ra->args[0] == NULL ? NULL : data_to_string(ra->args[0]);
	const char *pgname = data_to_string(ra->args[1]);
	smfu_entity_t entity = SMFU_ENTITY_INIT;
	svcerr_t se = SE_OK;

	scf_propertygroup_t *pg = scf_pg_create(h);

	if (pg == NULL) {
		se = SE_FATAL;
		goto done;
	}

	if ((se = smfu_lookup(h, smfo->sname, smfo->iname, &entity)) != SE_OK)
		goto done;

	if ((se = smfu_instance_get_composed_pg(h, entity.instance, snapname,
	    pgname, pg, error)) != SE_OK)
		goto done;

	se = create_Properties(h, pg, ret, error);
done:
	scf_pg_destroy(pg);
	smfu_entity_destroy(&entity);
	return (se);
}

/*ARGSUSED*/
conerr_t
interface_Instance_invoke_readSnapshotProperties(rad_instance_t *inst,
    adr_method_t *meth, data_t **ret, data_t **args, int count, data_t **error)
{
	radarg_t ra = { .inst = inst, .args = args };
	return (smfu_rtrun(rt_invoke_readSnapshotProperties, &ra, ret, error));
}


static svcerr_t
rt_invoke_readSnapshotProperty(scf_handle_t *h, void *arg, data_t **ret,
    data_t **error)
{
	radarg_t *ra = arg;
	smfobj_t *smfo = instance_getdata(ra->inst);
	const char *snapname =
	    ra->args[0] == NULL ? NULL : data_to_string(ra->args[0]);
	const char *pgname = data_to_string(ra->args[1]);
	const char *propname = data_to_string(ra->args[2]);
	smfu_entity_t entity = SMFU_ENTITY_INIT;
	svcerr_t se = SE_OK;

	scf_propertygroup_t *pg = scf_pg_create(h);
	scf_property_t *prop = scf_property_create(h);
	scf_iter_t *iter = scf_iter_create(h);
	scf_value_t *value = scf_value_create(h);

	if (pg == NULL || prop == NULL || iter == NULL || value == NULL) {
		se = SE_FATAL;
		goto done;
	}

	if ((se = smfu_lookup(h, smfo->sname, smfo->iname, &entity)) != SE_OK)
		goto done;

	if ((se = smfu_instance_get_composed_pg(h, entity.instance, snapname,
	    pgname, pg, error)) != SE_OK)
		goto done;

	if (scf_pg_get_property(pg, propname, prop) == -1) {
		if (scf_error() == SCF_ERROR_NOT_FOUND)
			se = error_scf(error, &e__ErrorCode_NOTFOUND,
			    &e__ErrorTarget_PROPERTY, propname, NULL);
		else
			se = smfu_maperr(scf_error());
		goto done;
	}

	se = create_Property(prop, iter, value, ret, error);

done:
	scf_value_destroy(value);
	scf_iter_destroy(iter);
	scf_property_destroy(prop);
	scf_pg_destroy(pg);
	smfu_entity_destroy(&entity);
	return (se);
}

/*ARGSUSED*/
conerr_t
interface_Instance_invoke_readSnapshotProperty(rad_instance_t *inst,
    adr_method_t *meth, data_t **ret, data_t **args, int count, data_t **error)
{
	radarg_t ra = { .inst = inst, .args = args };
	return (smfu_rtrun(rt_invoke_readSnapshotProperty, &ra, ret, error));
}


/*
 * Custom retry implementation for smf_*_instance() routines.
 */
static boolean_t
smf_action(conerr_t *result, data_t **error, int rval)
{
	if (rval == 0) {
		*result = ce_ok;
		return (B_FALSE);
	}

	svcerr_t se = SE_OK;
	switch (scf_error()) {
	case SCF_ERROR_BACKEND_READONLY:
		se = error_scf(error, &e__ErrorCode_READONLY, NULL, NULL, NULL);
		break;
	case SCF_ERROR_PERMISSION_DENIED:
		se = error_scf(error, &e__ErrorCode_DENIED, NULL, NULL, NULL);
		break;
	case SCF_ERROR_CONSTRAINT_VIOLATED:
		se = error_scf(error, &e__ErrorCode_INVALID, NULL, NULL, NULL);
		break;
	default:
		se = smfu_maperr(scf_error());
	}

	if (se == SE_NOTFOUND) {
		*result = ce_notfound;
		return (B_FALSE);
	}

	if (se == SE_FATAL) {
		(void) internal_error(error, NULL);
		*result = ce_object;
		return (B_FALSE);
	}

	return (B_TRUE);
}

/*ARGSUSED*/
conerr_t
interface_Instance_invoke_clear(rad_instance_t *inst, adr_method_t *meth,
    data_t **ret, data_t **args, int count, data_t **error)
{
	smfobj_t *smfo = instance_getdata(inst);
	/* boolean_t sync = data_to_boolean(args[0]); */

	conerr_t res;
	while (smf_action(&res, error, smf_restore_instance(smfo->fmri)))
		;
	return (res);
}

/*ARGSUSED*/
conerr_t
interface_Instance_invoke_restart(rad_instance_t *inst, adr_method_t *meth,
    data_t **ret, data_t **args, int count, data_t **error)
{
	smfobj_t *smfo = instance_getdata(inst);
	/* boolean_t sync = data_to_boolean(args[0]); */

	conerr_t res;
	while (smf_action(&res, error, smf_restart_instance(smfo->fmri)))
		;
	return (res);
}

/*ARGSUSED*/
conerr_t
interface_Instance_invoke_refresh(rad_instance_t *inst, adr_method_t *meth,
    data_t **ret, data_t **args, int count, data_t **error)
{
	smfobj_t *smfo = instance_getdata(inst);
	/* boolean_t sync = data_to_boolean(args[0]); */

	conerr_t res;
	while (smf_action(&res, error, smf_refresh_instance(smfo->fmri)))
		;
	return (res);
}

/*ARGSUSED*/
conerr_t
interface_Instance_invoke_maintain(rad_instance_t *inst, adr_method_t *meth,
    data_t **ret, data_t **args, int count, data_t **error)
{
	smfobj_t *smfo = instance_getdata(inst);
	boolean_t imm = data_to_boolean(args[0]);
	boolean_t temp = data_to_boolean(args[1]);
	/* boolean_t sync = data_to_boolean(args[2]); */

	int flags = 0;
	if (imm)
		flags |= SMF_IMMEDIATE;
	if (temp)
		flags |= SMF_TEMPORARY;

	conerr_t res;
	while (smf_action(&res, error,
	    smf_maintain_instance(smfo->fmri, flags)))
		;
	return (res);
}

/*ARGSUSED*/
conerr_t
interface_Instance_invoke_enable(rad_instance_t *inst, adr_method_t *meth,
    data_t **ret, data_t **args, int count, data_t **error)
{
	smfobj_t *smfo = instance_getdata(inst);
	boolean_t temp = data_to_boolean(args[0]);
	/* boolean_t sync = data_to_boolean(args[1]); */

	int flags = 0;
	if (temp)
		flags |= SMF_TEMPORARY;

	conerr_t res;
	while (smf_action(&res, error, smf_enable_instance(smfo->fmri, flags)))
		;
	return (res);
}

/*ARGSUSED*/
conerr_t
interface_Instance_invoke_disable(rad_instance_t *inst, adr_method_t *meth,
    data_t **ret, data_t **args, int count, data_t **error)
{
	smfobj_t *smfo = instance_getdata(inst);
	boolean_t temp = data_to_boolean(args[0]);
	/* boolean_t sync = data_to_boolean(args[1]); */

	int flags = 0;
	if (temp)
		flags |= SMF_TEMPORARY;

	conerr_t res;
	while (smf_action(&res, error, smf_disable_instance(smfo->fmri, flags)))
		;
	return (res);
}


static svcerr_t
rt_get_logfile(scf_handle_t *h, void *arg, data_t **ret, data_t **error)
{
	smfobj_t *smfo = arg;
	smfu_entity_t entity = SMFU_ENTITY_INIT;
	svcerr_t se = SE_OK;

	scf_propertygroup_t *pg = scf_pg_create(h);
	scf_property_t *prop = scf_property_create(h);
	scf_value_t *value = scf_value_create(h);
	char *logfile;

	if (pg == NULL || prop == NULL || value == NULL) {
		se = SE_FATAL;
		goto done;
	}

	if ((se = smfu_lookup(h, smfo->sname, smfo->iname, &entity)) != SE_OK)
		goto done;

	if (scf_instance_get_pg(entity.instance, SCF_PG_RESTARTER, pg) == -1 ||
	    scf_pg_get_property(pg, SCF_PROPERTY_LOGFILE, prop) == -1 ||
	    scf_property_get_value(prop, value) == -1) {
		if (scf_error() == SCF_ERROR_NOT_FOUND) {
			se = error_scf(error, &e__ErrorCode_NOTFOUND, NULL,
			    NULL, NULL);
		} else {
			se = smfu_maperr(scf_error());
		}
		goto done;
	}

	scf_error_t serr = smfu_value_get_string(value, &logfile);
	if (serr != 0) {
		se = smfu_maperr(serr);
		goto done;
	}

	*ret = data_new_string(logfile, lt_free);
done:
	scf_pg_destroy(pg);
	scf_property_destroy(prop);
	scf_value_destroy(value);
	smfu_entity_destroy(&entity);
	return (se);
}

/*ARGSUSED*/
conerr_t
interface_Instance_invoke_getLogInfo(rad_instance_t *inst, adr_method_t *meth,
    data_t **ret, data_t **args, int count, data_t **error)
{
	data_t *logfile = NULL;
	conerr_t ce = smfu_rtrun(rt_get_logfile, instance_getdata(inst),
	    &logfile, error);
	if (ce != ce_ok)
		return (ce);

	struct stat st;
	if (stat(data_to_string(logfile), &st) != 0) {
		data_free(logfile);
		(void) error_scf(error, &e__ErrorCode_NOTFOUND, NULL, NULL,
		    NULL);
		return (ce_object);
	}

	int max_size = data_to_integer(args[0]);
	int bsize = max_size >= 0 && max_size < st.st_size ?
	    max_size : st.st_size;

	char *buffer = malloc(bsize);
	if (buffer == NULL) {
		(void) internal_error(error, NULL);
		data_free(logfile);
		return (ce_object);
	}

	int fd;
	if ((fd = open(data_to_string(logfile), O_RDONLY)) == -1) {
		(void) error_scf(error, (errno == EACCES) ?
		    &e__ErrorCode_DENIED : &e__ErrorCode_INTERNAL,
		    NULL, NULL, NULL);
		data_free(logfile);
		free(buffer);
		return (ce_object);
	}

	if (pread(fd, buffer, bsize, st.st_size - bsize) != bsize) {
		(void) internal_error(error, NULL);
		data_free(logfile);
		free(buffer);
		(void) close(fd);
		return (ce_object);
	}

	(void) close(fd);

	data_t *result = data_new_struct(&t__LogInfo);
	struct_set(result, "name", logfile);
	struct_set(result, "size", data_new_integer(st.st_size));
	struct_set(result, "MTime", data_new_time_ts(&st.st_mtim));
	struct_set(result, "contents", data_new_opaque(buffer, bsize, lt_free));

	if ((*ret = data_purify(result)) == NULL) {
		(void) internal_error(error, NULL);
		return (ce_object);
	}

	return (ce_ok);
}
