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

#include <stdio.h>
#include <string.h>
#include <rad/adr.h>
#include <rad/adr_object.h>
#include <rad/rad_modapi.h>
#include "api_smf.h"
#include "smfutil.h"
#include "rhandle.h"
#include "datatype.h"

/*ARGSUSED*/
conerr_t
interface_Entity_read_fmri(rad_instance_t *inst, adr_attribute_t *attr,
    data_t **data, data_t **error)
{
	smfobj_t *smfo = instance_getdata(inst);
	*data = data_new_string(smfo->fmri, lt_copy);
	return (*data == NULL ? ce_nomem : ce_ok);
}

/*ARGSUSED*/
conerr_t
interface_Entity_read_scope(rad_instance_t *inst, adr_attribute_t *attr,
    data_t **data, data_t **error)
{
	*data = data_new_string("localhost", lt_const);
	return (*data == NULL ? ce_nomem : ce_ok);
}

/*ARGSUSED*/
conerr_t
interface_Entity_read_service(rad_instance_t *inst, adr_attribute_t *attr,
    data_t **data, data_t **error)
{
	smfobj_t *smfo = instance_getdata(inst);
	*data = data_new_string(smfo->sname, lt_copy);
	return (*data == NULL ? ce_nomem : ce_ok);
}


/*
 * Common retry callback for collecting data from property groups
 * directly attached to a service or in the running snapshot of an
 * instance.  Will scan only property groups of the specified type,
 * and will return an array of the specified ADR type.
 *
 * An error of SE_NOTFOUND from a callback routine indicates the
 * property group isn't of interest and should be skipped.
 */

struct pgargs {
	smfobj_t *smfo;
	type_t *type;
	const char *pgtype;
	svcerr_t (*cb)(scf_handle_t *, scf_propertygroup_t *, data_t **);
};

/*ARGSUSED*/
static svcerr_t
rt_collect_pgs(scf_handle_t *h, void *arg, data_t **ret, data_t **error)
{
	struct pgargs *pga = arg;
	smfobj_t *smfo = pga->smfo;
	smfu_entity_t entity = SMFU_ENTITY_INIT;
	svcerr_t se = SE_OK;
	data_t *result = data_new_array(pga->type, 5);
	scf_propertygroup_t *pg = scf_pg_create(h);
	scf_iter_t *iter = scf_iter_create(h);

	if (pg == NULL || iter == NULL) {
		se = SE_FATAL;
		goto done;
	}

	if ((se = smfu_lookup(h, smfo->sname, smfo->iname, &entity)) != SE_OK)
		goto done;

	if ((se = smfu_iter_pg_r(h, &entity, pga->pgtype, iter)) != SE_OK)
		goto done;

	int err;
	while ((err = scf_iter_next_pg(iter, pg)) > 0) {
		data_t *item = NULL;
		se = pga->cb(h, pg, &item);
		if (se == SE_OK)
			(void) array_add(result, item);
		else if (se != SE_NOTFOUND)
			goto done;
	}
	se = (err != 0) ? smfu_maperr(scf_error()) : SE_OK;

done:
	scf_iter_destroy(iter);
	smfu_entity_destroy(&entity);
	scf_pg_destroy(pg);

	*ret = result;
	return (se);
}

/*ARGSUSED*/
conerr_t
interface_Entity_read_dependencies(rad_instance_t *inst, adr_attribute_t *attr,
    data_t **data, data_t **error)
{
	struct pgargs pga = {
		.smfo = instance_getdata(inst),
		.type = &t_array__Dependency,
		.pgtype = SCF_GROUP_DEPENDENCY,
		.cb = create_Dependency
	};
	return (smfu_rtrun(rt_collect_pgs, &pga, data, error));
}

/*ARGSUSED*/
conerr_t
interface_Entity_read_manpages(rad_instance_t *inst, adr_attribute_t *attr,
    data_t **data, data_t **error)
{
	struct pgargs pga = {
		.smfo = instance_getdata(inst),
		.type = &t_array__Manpage,
		.pgtype = SCF_GROUP_TEMPLATE,
		.cb = create_Manpage
	};
	return (smfu_rtrun(rt_collect_pgs, &pga, data, error));
}

/*ARGSUSED*/
conerr_t
interface_Entity_read_doclinks(rad_instance_t *inst, adr_attribute_t *attr,
    data_t **data, data_t **error)
{
	struct pgargs pga = {
		.smfo = instance_getdata(inst),
		.type = &t_array__Doclink,
		.pgtype = SCF_GROUP_TEMPLATE,
		.cb = create_Doclink
	};
	return (smfu_rtrun(rt_collect_pgs, &pga, data, error));
}

/*ARGSUSED*/
static svcerr_t
rt_read_pgs(scf_handle_t *h, void *arg, data_t **ret, data_t **error)
{
	smfobj_t *smfo = arg;
	svcerr_t se = SE_OK;
	smfu_entity_t entity = SMFU_ENTITY_INIT;

	scf_propertygroup_t *pg = scf_pg_create(h);
	scf_iter_t *iter = scf_iter_create(h);
	data_t *result = data_new_array(&t_array__PropertyGroup, 5);

	if (pg == NULL || iter == NULL) {
		se = SE_FATAL;
		goto done;
	}

	if ((se = smfu_lookup(h, smfo->sname, smfo->iname, &entity)) != SE_OK)
		goto done;

	if ((se = smfu_iter_pg(&entity, NULL, iter)) != SE_OK)
		goto done;

	int e;
	while ((e = scf_iter_next_pg(iter, pg)) > 0) {
		data_t *pgdata;
		if ((se = create_PropertyGroup(pg, &pgdata)) != SE_OK)
			goto done;
		(void) array_add(result, pgdata);
	}
	if (e != 0)
		se = smfu_maperr(scf_error());

done:
	scf_iter_destroy(iter);
	scf_pg_destroy(pg);
	smfu_entity_destroy(&entity);

	*ret = result;
	return (se);
}

/*ARGSUSED*/
conerr_t
interface_Entity_read_pgs(rad_instance_t *inst, adr_attribute_t *attr,
    data_t **data, data_t **error)
{
	return (smfu_rtrun(rt_read_pgs, instance_getdata(inst), data, error));
}


/*ARGSUSED*/
static svcerr_t
rt_invoke_delete(scf_handle_t *h, void *arg, data_t **ret, data_t **error)
{
	smfobj_t *smfo = arg;
	svcerr_t se = SE_OK;
	smfu_entity_t entity = SMFU_ENTITY_INIT;

	if ((se = smfu_lookup(h, smfo->sname, smfo->iname, &entity)) != SE_OK)
		goto done;

	int e = (entity.instance != NULL) ?
	    scf_instance_delete(entity.instance) :
	    scf_service_delete(entity.service);

	if (e != 0) {
		switch (scf_error()) {
		case SCF_ERROR_PERMISSION_DENIED:
			se = error_scf(error, &e__ErrorCode_DENIED, NULL,
			    NULL, NULL);
			break;
		case SCF_ERROR_BACKEND_READONLY:
			se = error_scf(error, &e__ErrorCode_READONLY, NULL,
			    NULL, NULL);
			break;
		case SCF_ERROR_EXISTS:
			se = error_scf(error, &e__ErrorCode_EXISTS, NULL,
			    NULL, NULL);
			break;
		default:
			se = smfu_maperr(scf_error());
		}
	}
done:
	smfu_entity_destroy(&entity);
	return (se);
}

/*ARGSUSED*/
conerr_t
interface_Entity_invoke_delete(rad_instance_t *inst, adr_method_t *meth,
    data_t **ret, data_t **args, int count, data_t **error)
{
	return (smfu_rtrun(rt_invoke_delete, instance_getdata(inst), NULL,
	    error));
}


/*ARGSUSED*/
static svcerr_t
rt_invoke_deleteCust(scf_handle_t *h, void *arg, data_t **ret, data_t **error)
{
	smfobj_t *smfo = arg;
	svcerr_t se = SE_OK;
	smfu_entity_t entity = SMFU_ENTITY_INIT;

	if ((se = smfu_lookup(h, smfo->sname, smfo->iname, &entity)) != SE_OK)
		goto done;

	int e = (entity.instance != NULL) ?
	    scf_instance_delcust(entity.instance) :
	    scf_service_delcust(entity.service);

	if (e != 0) {
		switch (scf_error()) {
		case SCF_ERROR_PERMISSION_DENIED:
			se = error_scf(error, &e__ErrorCode_DENIED, NULL,
			    NULL, NULL);
			break;
		case SCF_ERROR_BACKEND_READONLY:
			se = error_scf(error, &e__ErrorCode_READONLY, NULL,
			    NULL, NULL);
			break;
		case SCF_ERROR_DELETED:
			se = error_scf(error, &e__ErrorCode_NOTFOUND, NULL,
			    (entity.instance != NULL) ? smfo->iname :
			    smfo->sname, NULL);
			break;
		default:
			se = smfu_maperr(scf_error());
		}
	}
done:
	smfu_entity_destroy(&entity);
	return (se);
}

/*ARGSUSED*/
conerr_t
interface_Entity_invoke_deleteCust(rad_instance_t *inst, adr_method_t *meth,
    data_t **ret, data_t **args, int count, data_t **error)
{
	return (smfu_rtrun(rt_invoke_deleteCust, instance_getdata(inst), NULL,
	    error));
}

/*ARGSUSED*/
static svcerr_t
rt_invoke_createPG(scf_handle_t *h, void *arg, data_t **ret, data_t **error)
{
	radarg_t *ra = arg;
	smfobj_t *smfo = instance_getdata(ra->inst);
	const char *pgname = data_to_string(ra->args[0]);
	const char *pgtype = data_to_string(ra->args[1]);
	unsigned int pgflags = data_to_uinteger(ra->args[2]);
	svcerr_t se = SE_OK;
	smfu_entity_t entity = SMFU_ENTITY_INIT;

	if ((se = smfu_lookup(h, smfo->sname, smfo->iname, &entity)) != SE_OK)
		goto done;

	int e = (entity.instance != NULL) ?
	    scf_instance_add_pg(entity.instance, pgname, pgtype,
	    pgflags, NULL) :
	    scf_service_add_pg(entity.service, pgname, pgtype,
	    pgflags, NULL);

	if (e != 0) {
		switch (scf_error()) {
		case SCF_ERROR_INVALID_ARGUMENT:
			se = error_scf(error, &e__ErrorCode_BADVALUE,
			    &e__ErrorTarget_PROPERTYGROUP, NULL, NULL);
			break;
		case SCF_ERROR_PERMISSION_DENIED:
			se = error_scf(error, &e__ErrorCode_DENIED, NULL,
			    NULL, NULL);
			break;
		case SCF_ERROR_BACKEND_READONLY:
			se = error_scf(error, &e__ErrorCode_READONLY, NULL,
			    NULL, NULL);
			break;
		case SCF_ERROR_EXISTS:
			se = error_scf(error, &e__ErrorCode_EXISTS,
			    &e__ErrorTarget_PROPERTYGROUP, NULL, NULL);
			break;
		default:
			se = smfu_maperr(scf_error());
		}
	}
done:
	smfu_entity_destroy(&entity);
	return (se);
}

/*ARGSUSED*/
conerr_t
interface_Entity_invoke_createPG(rad_instance_t *inst, adr_method_t *meth,
    data_t **ret, data_t **args, int count, data_t **error)
{
	radarg_t ra = { .inst = inst, .args = args };
	return (smfu_rtrun(rt_invoke_createPG, &ra, NULL, error));
}


/*ARGSUSED*/
static svcerr_t
rt_invoke_deletePG(scf_handle_t *h, void *arg, data_t **ret, data_t **error)
{
	radarg_t *ra = arg;
	smfobj_t *smfo = instance_getdata(ra->inst);
	const char *pgname = data_to_string(ra->args[0]);
	svcerr_t se = SE_OK;
	smfu_entity_t entity = SMFU_ENTITY_INIT;
	scf_propertygroup_t *pg = scf_pg_create(h);

	if (pg == NULL) {
		se = SE_FATAL;
		goto done;
	}

	if ((se = smfu_lookup(h, smfo->sname, smfo->iname, &entity)) != SE_OK)
		goto done;

	if ((se = smfu_get_pg(&entity, pgname, pg, error)) != SE_OK)
		goto done;

	if (scf_pg_delete(pg) != 0) {
		switch (scf_error()) {
		case SCF_ERROR_PERMISSION_DENIED:
			se = error_scf(error, &e__ErrorCode_DENIED, NULL,
			    NULL, NULL);
			break;
		case SCF_ERROR_BACKEND_READONLY:
			se = error_scf(error, &e__ErrorCode_READONLY, NULL,
			    NULL, NULL);
			break;
		default:
			se = smfu_maperr(scf_error());
		}
	}

done:
	scf_pg_destroy(pg);
	smfu_entity_destroy(&entity);
	return (se);
}

/*ARGSUSED*/
conerr_t
interface_Entity_invoke_deletePG(rad_instance_t *inst, adr_method_t *meth,
    data_t **ret, data_t **args, int count, data_t **error)
{
	radarg_t ra = { .inst = inst, .args = args };
	return (smfu_rtrun(rt_invoke_deletePG, &ra, NULL, error));
}


/*ARGSUSED*/
static svcerr_t
rt_invoke_deletePGCust(scf_handle_t *h, void *arg, data_t **ret, data_t **error)
{
	radarg_t *ra = arg;
	smfobj_t *smfo = instance_getdata(ra->inst);
	const char *pgname = data_to_string(ra->args[0]);
	svcerr_t se = SE_OK;
	smfu_entity_t entity = SMFU_ENTITY_INIT;
	scf_propertygroup_t *pg = scf_pg_create(h);

	if (pg == NULL) {
		se = SE_FATAL;
		goto done;
	}

	if ((se = smfu_lookup(h, smfo->sname, smfo->iname, &entity)) != SE_OK)
		goto done;

	if ((se = smfu_get_pg(&entity, pgname, pg, error)) != SE_OK)
		goto done;

	if (scf_pg_delcust(pg) != 0) {
		switch (scf_error()) {
		case SCF_ERROR_PERMISSION_DENIED:
			se = error_scf(error, &e__ErrorCode_DENIED, NULL,
			    NULL, NULL);
			break;
		case SCF_ERROR_BACKEND_READONLY:
			se = error_scf(error, &e__ErrorCode_READONLY, NULL,
			    NULL, NULL);
			break;
		case SCF_ERROR_DELETED:
			se = error_scf(error, &e__ErrorCode_NOTFOUND,
			    &e__ErrorTarget_PROPERTYGROUP, pgname, NULL);
			break;
		default:
			se = smfu_maperr(scf_error());
		}
	}

done:
	scf_pg_destroy(pg);
	smfu_entity_destroy(&entity);
	return (se);
}

/*ARGSUSED*/
conerr_t
interface_Entity_invoke_deletePGCust(rad_instance_t *inst, adr_method_t *meth,
    data_t **ret, data_t **args, int count, data_t **error)
{
	radarg_t ra = { .inst = inst, .args = args };
	return (smfu_rtrun(rt_invoke_deletePGCust, &ra, NULL, error));
}

static svcerr_t
rt_invoke_readProperties(scf_handle_t *h, void *arg, data_t **ret,
    data_t **error)
{
	radarg_t *ra = arg;
	smfobj_t *smfo = instance_getdata(ra->inst);
	const char *pgname = data_to_string(ra->args[0]);
	svcerr_t se = SE_OK;
	smfu_entity_t entity = SMFU_ENTITY_INIT;
	scf_propertygroup_t *pg = scf_pg_create(h);

	if (pg == NULL) {
		se = SE_FATAL;
		goto done;
	}

	if ((se = smfu_lookup(h, smfo->sname, smfo->iname, &entity)) != SE_OK)
		goto done;

	if ((se = smfu_get_pg(&entity, pgname, pg, error)) != SE_OK)
		goto done;

	se = create_Properties(h, pg, ret, error);
done:
	scf_pg_destroy(pg);
	smfu_entity_destroy(&entity);
	return (se);
}

/*ARGSUSED*/
conerr_t
interface_Entity_invoke_readProperties(rad_instance_t *inst, adr_method_t *meth,
    data_t **ret, data_t **args, int count, data_t **error)
{
	radarg_t ra = { .inst = inst, .args = args };
	return (smfu_rtrun(rt_invoke_readProperties, &ra, ret, error));
}

/*ARGSUSED*/
static svcerr_t
tx_write_prop(scf_handle_t *h, scf_transaction_t *tx,
    const char *name, scf_type_t type, data_t *values, data_t **error)
{
	scf_transaction_entry_t *entry = scf_entry_create(h);

	if (entry == NULL)
		return (SE_FATAL);

	int r = scf_transaction_property_change(tx, entry, name, type);
	if (r == -1) {
		if (scf_error() == SCF_ERROR_NOT_FOUND) {
			r = scf_transaction_property_new(tx, entry, name, type);
		} else if (scf_error() == SCF_ERROR_TYPE_MISMATCH) {
			r = scf_transaction_property_change_type(tx, entry,
			    name, type);
		}

		if (r == -1) {
			int e = scf_error();
			scf_entry_destroy(entry);
			if (e == SCF_ERROR_INVALID_ARGUMENT)
				return (error_scf(error, &e__ErrorCode_BADVALUE,
				    &e__ErrorTarget_PROPERTY, name, NULL));
			else if (e == SCF_ERROR_IN_USE)
				return (error_scf(error, &e__ErrorCode_INVALID,
				    &e__ErrorTarget_PROPERTY, name, NULL));
			return (smfu_maperr(e));
		}
	}

	int nvalues = array_size(values);
	for (int i = 0; i < nvalues; i++) {
		const char *vstr = data_to_string(array_get(values, i));
		scf_value_t *v = scf_value_create(h);
		if (v == NULL)
			return (SE_FATAL);
		if (scf_value_set_from_string(v, type, vstr) == -1 ||
		    scf_entry_add_value(entry, v) == -1) {
			int e = scf_error();
			scf_value_destroy(v);
			if (e == SCF_ERROR_INVALID_ARGUMENT)
				return (error_scf(error, &e__ErrorCode_BADVALUE,
				    &e__ErrorTarget_VALUE, name, NULL));
			return (smfu_maperr(e));
		}
	}

	return (SE_OK);
}

/*ARGSUSED*/
static svcerr_t
rt_invoke_writeProperties(scf_handle_t *h, void *arg, data_t **ret,
    data_t **error)
{
	radarg_t *ra = arg;
	smfobj_t *smfo = instance_getdata(ra->inst);
	const char *pgname = data_to_string(ra->args[0]);
	data_t *data = ra->args[1];
	svcerr_t se = SE_OK;
	smfu_entity_t entity = SMFU_ENTITY_INIT;
	scf_propertygroup_t *pg = scf_pg_create(h);
	scf_transaction_t *tx = scf_transaction_create(h);

	if (pg == NULL || tx == NULL) {
		se = SE_FATAL;
		goto done;
	}

	if ((se = smfu_lookup(h, smfo->sname, smfo->iname, &entity)) != SE_OK)
		goto done;

	if ((se = smfu_get_pg(&entity, pgname, pg, error)) != SE_OK)
		goto done;

top:
	if (scf_transaction_start(tx, pg) == -1)
		goto txerror;

	int nprops = array_size(data);
	for (int i = 0; i < nprops; i++) {
		data_t *propdata = array_get(data, i);
		const char *propname =
		    data_to_string(struct_get(propdata, "name"));
		scf_type_t proptype =
		    from_PropertyType(struct_get(propdata, "type"));
		data_t *values = struct_get(propdata, "values");

		se = tx_write_prop(h, tx, propname, proptype, values, error);
		if (se != SE_OK)
			goto done;
	}

	int r;
	if ((r = scf_transaction_commit(tx)) == 1)
		goto done;

	if (r == 0 && scf_pg_update(pg) != -1) {
		scf_transaction_destroy_children(tx);
		scf_transaction_reset(tx);
		goto top;
	}

txerror:
	switch (scf_error()) {
	case SCF_ERROR_PERMISSION_DENIED:
		se = error_scf(error, &e__ErrorCode_DENIED, NULL,
		    NULL, NULL);
		break;
	case SCF_ERROR_BACKEND_READONLY:
		se = error_scf(error, &e__ErrorCode_READONLY, NULL,
		    NULL, NULL);
		break;
	default:
		se = smfu_maperr(scf_error());
	}

done:
	scf_transaction_destroy_children(tx);
	scf_transaction_destroy(tx);
	scf_pg_destroy(pg);

	return (se);
}

/*ARGSUSED*/
conerr_t
interface_Entity_invoke_writeProperties(rad_instance_t *inst,
    adr_method_t *meth, data_t **ret, data_t **args, int count, data_t **error)
{
	radarg_t ra = { .inst = inst, .args = args };
	return (smfu_rtrun(rt_invoke_writeProperties, &ra, NULL, error));
}

static svcerr_t
rt_invoke_readProperty(scf_handle_t *h, void *arg, data_t **ret, data_t **error)
{
	radarg_t *ra = arg;
	smfobj_t *smfo = instance_getdata(ra->inst);
	const char *pgname = data_to_string(ra->args[0]);
	const char *propname = data_to_string(ra->args[1]);
	svcerr_t se = SE_OK;
	smfu_entity_t entity = SMFU_ENTITY_INIT;
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

	if ((se = smfu_get_pg(&entity, pgname, pg, error)) != SE_OK)
		goto done;

	if (scf_pg_get_property(pg, propname, prop) == -1) {
		if ((se = smfu_maperr(scf_error())) == SE_NOTFOUND)
			(void) error_scf(error, &e__ErrorCode_NOTFOUND,
			    &e__ErrorTarget_PROPERTY, NULL, NULL);
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
interface_Entity_invoke_readProperty(rad_instance_t *inst, adr_method_t *meth,
    data_t **ret, data_t **args, int count, data_t **error)
{
	radarg_t ra = { .inst = inst, .args = args };
	return (smfu_rtrun(rt_invoke_readProperty, &ra, ret, error));
}


/*ARGSUSED*/
static svcerr_t
rt_invoke_writeProperty(scf_handle_t *h, void *arg, data_t **ret,
    data_t **error)
{
	radarg_t *ra = arg;
	smfobj_t *smfo = instance_getdata(ra->inst);
	const char *pgname = data_to_string(ra->args[0]);
	const char *propname = data_to_string(ra->args[1]);
	scf_type_t proptype = from_PropertyType(ra->args[2]);
	data_t *data = ra->args[3];
	svcerr_t se = SE_OK;
	smfu_entity_t entity = SMFU_ENTITY_INIT;
	scf_propertygroup_t *pg = scf_pg_create(h);
	scf_transaction_t *tx = scf_transaction_create(h);

	if (pg == NULL || tx == NULL) {
		se = internal_error(error, NULL);
		goto done;
	}

	if ((se = smfu_lookup(h, smfo->sname, smfo->iname, &entity)) != SE_OK)
		goto done;

	if ((se = smfu_get_pg(&entity, pgname, pg, error)) != SE_OK)
		goto done;

top:
	if (scf_transaction_start(tx, pg) == -1)
		goto txerror;

	if ((se = tx_write_prop(h, tx, propname, proptype, data, error))
	    != SE_OK)
		goto done;

	int r;
	if ((r = scf_transaction_commit(tx)) == 1)
		goto done;

	if (r == 0 && scf_pg_update(pg) != -1) {
		scf_transaction_destroy_children(tx);
		scf_transaction_reset(tx);
		goto top;
	}

txerror:
	switch (scf_error()) {
	case SCF_ERROR_PERMISSION_DENIED:
		se = error_scf(error, &e__ErrorCode_DENIED, NULL,
		    NULL, NULL);
		break;
	case SCF_ERROR_BACKEND_READONLY:
		se = error_scf(error, &e__ErrorCode_READONLY, NULL,
		    NULL, NULL);
		break;
	default:
		se = smfu_maperr(scf_error());
	}

done:
	scf_transaction_destroy_children(tx);
	scf_transaction_destroy(tx);
	scf_pg_destroy(pg);

	return (se);
}

/*ARGSUSED*/
conerr_t
interface_Entity_invoke_writeProperty(rad_instance_t *inst, adr_method_t *meth,
    data_t **ret, data_t **args, int count, data_t **error)
{
	radarg_t ra = { .inst = inst, .args = args };
	return (smfu_rtrun(rt_invoke_writeProperty, &ra, NULL, error));
}

static svcerr_t
tx_delete_prop(scf_handle_t *h, scf_transaction_t *tx,
    const char *name, data_t **error)
{
	scf_transaction_entry_t *entry = scf_entry_create(h);

	if (entry == NULL)
		return (SE_FATAL);

	if (scf_transaction_property_delete(tx, entry, name) == -1) {
		int e = scf_error();
		scf_entry_destroy(entry);
		switch (e) {
		case SCF_ERROR_NOT_FOUND:
			return (error_scf(error, &e__ErrorCode_NOTFOUND,
			    &e__ErrorTarget_PROPERTY, name, NULL));
		case SCF_ERROR_INVALID_ARGUMENT:
			return (error_scf(error, &e__ErrorCode_BADVALUE,
			    &e__ErrorTarget_PROPERTY, name, NULL));
		case SCF_ERROR_IN_USE:
			return (error_scf(error, &e__ErrorCode_INVALID,
			    &e__ErrorTarget_PROPERTY, name, NULL));
		}
		return (smfu_maperr(e));
	}
	return (SE_OK);
}

/*ARGSUSED*/
static svcerr_t
rt_invoke_deleteProperty(scf_handle_t *h, void *arg, data_t **ret,
    data_t **error)
{
	radarg_t *ra = arg;
	smfobj_t *smfo = instance_getdata(ra->inst);
	const char *pgname = data_to_string(ra->args[0]);
	const char *propname = data_to_string(ra->args[1]);
	svcerr_t se = SE_OK;
	smfu_entity_t entity = SMFU_ENTITY_INIT;
	scf_propertygroup_t *pg = scf_pg_create(h);
	scf_transaction_t *tx = scf_transaction_create(h);

	if (pg == NULL || tx == NULL) {
		se = internal_error(error, NULL);
		goto done;
	}

	if ((se = smfu_lookup(h, smfo->sname, smfo->iname, &entity)) != SE_OK)
		goto done;

	if ((se = smfu_get_pg(&entity, pgname, pg, error)) != SE_OK)
		goto done;

top:
	if (scf_transaction_start(tx, pg) == -1)
		goto txerror;

	if ((se = tx_delete_prop(h, tx, propname, error)) != SE_OK)
		goto done;

	int r;
	if ((r = scf_transaction_commit(tx)) == 1)
		goto done;

	if (r == 0 && scf_pg_update(pg) != -1) {
		scf_transaction_destroy_children(tx);
		scf_transaction_reset(tx);
		goto top;
	}

txerror:
	switch (scf_error()) {
	case SCF_ERROR_PERMISSION_DENIED:
		se = error_scf(error, &e__ErrorCode_DENIED, NULL,
		    NULL, NULL);
		break;
	case SCF_ERROR_BACKEND_READONLY:
		se = error_scf(error, &e__ErrorCode_READONLY, NULL,
		    NULL, NULL);
		break;
	default:
		se = smfu_maperr(scf_error());
	}

done:
	scf_transaction_destroy_children(tx);
	scf_transaction_destroy(tx);
	scf_pg_destroy(pg);

	return (se);
}

/*ARGSUSED*/
conerr_t
interface_Entity_invoke_deleteProperty(rad_instance_t *inst, adr_method_t *meth,
    data_t **ret, data_t **args, int count, data_t **error)
{
	radarg_t ra = { .inst = inst, .args = args };
	return (smfu_rtrun(rt_invoke_deleteProperty, &ra, NULL, error));
}

static svcerr_t
tx_delete_propcust(scf_handle_t *h, scf_transaction_t *tx,
    const char *name, data_t **error)
{
	svcerr_t se = SE_OK;
	scf_transaction_entry_t *entry = scf_entry_create(h);

	if (entry == NULL)
		return (SE_FATAL);

	if (scf_transaction_property_delcust(tx, entry, name) == -1) {
		int e = scf_error();
		scf_entry_destroy(entry);
		switch (e) {
		case SCF_ERROR_PERMISSION_DENIED:
			se = error_scf(error, &e__ErrorCode_DENIED, NULL,
			    NULL, NULL);
			break;
		case SCF_ERROR_BACKEND_READONLY:
			se = error_scf(error, &e__ErrorCode_READONLY, NULL,
			    NULL, NULL);
			break;
		case SCF_ERROR_DELETED:
			se = error_scf(error, &e__ErrorCode_NOTFOUND,
			    &e__ErrorTarget_PROPERTY, name, NULL);
			break;
		default:
			se = smfu_maperr(e);
		}
	}
	return (se);
}

/*ARGSUSED*/
static svcerr_t
rt_invoke_deletePropertyCust(scf_handle_t *h, void *arg, data_t **ret,
    data_t **error)
{
	radarg_t *ra = arg;
	smfobj_t *smfo = instance_getdata(ra->inst);
	const char *pgname = data_to_string(ra->args[0]);
	const char *propname = data_to_string(ra->args[1]);
	svcerr_t se = SE_OK;
	smfu_entity_t entity = SMFU_ENTITY_INIT;
	scf_propertygroup_t *pg = scf_pg_create(h);
	scf_transaction_t *tx = scf_transaction_create(h);

	if (pg == NULL || tx == NULL) {
		se = internal_error(error, NULL);
		goto done;
	}

	if ((se = smfu_lookup(h, smfo->sname, smfo->iname, &entity)) != SE_OK)
		goto done;

	if ((se = smfu_get_pg(&entity, pgname, pg, error)) != SE_OK)
		goto done;

top:
	if (scf_transaction_start(tx, pg) == -1)
		goto txerror;

	if ((se = tx_delete_propcust(h, tx, propname, error)) != SE_OK)
		goto done;

	int r;
	if ((r = scf_transaction_commit(tx)) == 1)
		goto done;

	if (r == 0 && scf_pg_update(pg) != -1) {
		scf_transaction_destroy_children(tx);
		scf_transaction_reset(tx);
		goto top;
	}

txerror:
	switch (scf_error()) {
	case SCF_ERROR_PERMISSION_DENIED:
		se = error_scf(error, &e__ErrorCode_DENIED, NULL,
		    NULL, NULL);
		break;
	case SCF_ERROR_BACKEND_READONLY:
		se = error_scf(error, &e__ErrorCode_READONLY, NULL,
		    NULL, NULL);
		break;
	default:
		se = smfu_maperr(scf_error());
	}

done:
	scf_transaction_destroy_children(tx);
	scf_transaction_destroy(tx);
	scf_pg_destroy(pg);

	return (se);
}

/*ARGSUSED*/
conerr_t
interface_Entity_invoke_deletePropertyCust(rad_instance_t *inst,
    adr_method_t *meth, data_t **ret, data_t **args, int count, data_t **error)
{
	radarg_t ra = { .inst = inst, .args = args };
	return (smfu_rtrun(rt_invoke_deletePropertyCust, &ra, NULL, error));
}

/*
 * Common retry callback for reading old-style template data from
 * either a service's directly-attached property groups or an
 * instance's running snapshot.
 */

struct tmplarg {
	smfobj_t *smfo;
	const char *pgname;
	const char *locale;
};

/*ARGSUSED*/
static svcerr_t
rt_get_template(scf_handle_t *h, void *arg, data_t **ret, data_t **error)
{
	struct tmplarg *ta = arg;
	svcerr_t se = SE_OK;
	smfu_entity_t entity = SMFU_ENTITY_INIT;
	scf_propertygroup_t *pg = scf_pg_create(h);
	char *str = NULL;

	if (pg == NULL) {
		se = SE_FATAL;
		goto done;
	}

	if ((se = smfu_lookup(h, ta->smfo->sname, ta->smfo->iname,
	    &entity)) != SE_OK)
		goto done;

	if ((se = smfu_get_pg_r(h, &entity, ta->pgname, pg)) == SE_OK &&
	    (se = smfu_get_l10n_str(h, pg, ta->locale, &str)) == SE_OK) {
		if ((*ret = data_new_string(str, lt_free)) == NULL)
			se = SE_FATAL;
	} else if (se == SE_NOTFOUND) {
		se = SE_OK;
	}

done:
	smfu_entity_destroy(&entity);
	scf_pg_destroy(pg);

	return (se);
}

/*ARGSUSED*/
conerr_t
interface_Entity_invoke_getCommonName(rad_instance_t *inst, adr_method_t *meth,
    data_t **ret, data_t **args, int count, data_t **error)
{
	struct tmplarg ta = {
	    .smfo = instance_getdata(inst),
	    .pgname = SCF_PG_TM_COMMON_NAME,
	    .locale = data_to_string(args[0])
	};
	return (smfu_rtrun_opt(rt_get_template, &ta, ret, error));
}

/*ARGSUSED*/
conerr_t
interface_Entity_invoke_getDescription(rad_instance_t *inst, adr_method_t *meth,
    data_t **ret, data_t **args, int count, data_t **error)
{
	struct tmplarg ta = {
	    .smfo = instance_getdata(inst),
	    .pgname = SCF_PG_TM_DESCRIPTION,
	    .locale = data_to_string(args[0])
	};
	return (smfu_rtrun_opt(rt_get_template, &ta, ret, error));
}


/*ARGSUSED*/
static svcerr_t
rt_invoke_getPGTemplates(scf_handle_t *h, void *arg, data_t **ret,
    data_t **error)
{
	radarg_t *ra = arg;
	smfobj_t *smfo = instance_getdata(ra->inst);
	const char *locale = data_to_string(ra->args[0]);
	svcerr_t se = SE_OK;
	data_t *result = data_new_array(&t_array__PGTemplate, 5);

	scf_pg_tmpl_t *pgtmpl = scf_tmpl_pg_create(h);
	if (pgtmpl == NULL) {
		se = SE_FATAL;
		goto done;
	}

	int e;
	while ((e = scf_tmpl_iter_pgs(pgtmpl, smfo->fmri, NULL, NULL,
	    SCF_PG_TMPL_FLAG_CURRENT)) == 1) {
		data_t *t = NULL;
		if ((se = create_PGTemplate(pgtmpl, locale, &t)) != SE_OK)
			goto done;
		(void) array_add(result, t);
	}
	if (e == -1)
		se = smfu_maperr(scf_error());
done:
	*ret = result;
	scf_tmpl_pg_destroy(pgtmpl);

	return (se);
}

/*ARGSUSED*/
conerr_t
interface_Entity_invoke_getPGTemplates(rad_instance_t *inst, adr_method_t *meth,
    data_t **ret, data_t **args, int count, data_t **error)
{
	radarg_t ra = { .inst = inst, .args = args };
	return (smfu_rtrun(rt_invoke_getPGTemplates, &ra, ret, error));
}


/*ARGSUSED*/
static svcerr_t
rt_invoke_getPropTemplates(scf_handle_t *h, void *arg, data_t **ret,
    data_t **error)
{
	radarg_t *ra = arg;
	smfobj_t *smfo = instance_getdata(ra->inst);
	const char *pgname = data_to_string(ra->args[0]);
	const char *pgtype = data_to_string(ra->args[1]);
	const char *locale = data_to_string(ra->args[2]);
	svcerr_t se = SE_OK;
	data_t *result = data_new_array(&t_array__PropTemplate, 5);

	scf_pg_tmpl_t *pgtmpl = scf_tmpl_pg_create(h);
	scf_prop_tmpl_t *proptmpl = scf_tmpl_prop_create(h);

	if (pgtmpl == NULL || proptmpl == NULL) {
		se = SE_FATAL;
		goto done;
	}

	if (scf_tmpl_get_by_pg_name(smfo->fmri, NULL, pgname, pgtype, pgtmpl,
	    0) == -1) {
		se = smfu_maperr(scf_error());
		goto done;
	}

	int e;
	while ((e = scf_tmpl_iter_props(pgtmpl, proptmpl, 0)) == 0) {
		data_t *t = NULL;
		if ((se = create_PropTemplate(proptmpl, locale, &t)) != SE_OK)
			goto done;
		(void) array_add(result, t);
	}
	if (e == -1)
		se = smfu_maperr(scf_error());
done:
	*ret = result;
	scf_tmpl_prop_destroy(proptmpl);
	scf_tmpl_pg_destroy(pgtmpl);

	return (se);
}

/*ARGSUSED*/
conerr_t
interface_Entity_invoke_getPropTemplates(rad_instance_t *inst,
    adr_method_t *meth, data_t **ret, data_t **args, int count, data_t **error)
{
	radarg_t ra = { .inst = inst, .args = args };
	return (smfu_rtrun(rt_invoke_getPropTemplates, &ra, ret, error));
}
