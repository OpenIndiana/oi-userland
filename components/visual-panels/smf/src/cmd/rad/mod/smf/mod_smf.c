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
#include "datatype.h"

/*
 * The SMF rad module.
 *
 * This module is atypically involved due to the sheer size of the
 * exported API, the complexity of consuming SMF, and the fact
 * the exported API represents a significant abstraction of the
 * underlying functionality.
 *
 * This file (mod_smf.c) contains the rad module linkage, the dynamic
 * namespace callbacks, and the implementation of the master object.
 *
 * smfutil.c and rhandle.c contain a variety of routines that factor
 * common combinations of libscf operations into more manageable
 * chunks.
 *
 * datatype.c contains routines that map a libscf type or object into
 * the appropriate ADR type.
 *
 * common.c contains the implementation of attributes and methods
 * common to instances and services.
 *
 * service.c and instance.c contain the implementation of attributes
 * and methods specific to services and instances, respectively.
 */

/*
 * "Master" object implementation.
 */

struct read_services_data {
	data_t *rsd_result;
	data_t *rsd_insts;
};

/*
 * Master.service instance iteration callback.  Adds the name of the
 * instance to the current service's instance list.
 */
/*ARGSUSED*/
static svcerr_t
read_services_inst_cb(scf_handle_t *scfhandle, scf_instance_t *instance,
    const char *sname, const char *iname, void *arg)
{
	struct read_services_data *rsd = arg;

	assert(rsd->rsd_insts != NULL);
	(void) array_add(rsd->rsd_insts, data_new_string(iname, lt_copy));

	return (SE_OK);
}

/*
 * master.service service iteration callback.  Constructs a service and
 * adds it to the list.  Stores a pointer to the service's instance
 * list in the iteration data for use by the instance iteration
 * callback.
 */
/*ARGSUSED*/
static svcerr_t
read_services_svc_cb(scf_handle_t *scfhandle, scf_service_t *service,
    const char *sname, void *arg)
{
	struct read_services_data *rsd = arg;

	rsd->rsd_insts = data_new_array(&t_array_string, 5);

	data_t *sdata = data_new_struct(&t__Service);
	struct_set(sdata, "fmri",
	    data_new_string(smfu_fmri_alloc(sname, NULL), lt_free));
	struct_set(sdata, "objectName",
	    data_new_name(smfu_name_alloc(sname, NULL)));
	struct_set(sdata, "instances", rsd->rsd_insts);
	(void) array_add(rsd->rsd_result, sdata);

	return (SE_OK);
}

/*ARGSUSED*/
static svcerr_t
rt_read_services(scf_handle_t *h, void *arg, data_t **ret, data_t **error)
{
	data_t *result = data_new_array(&t_array__Service, 200);
	struct read_services_data rsd = { result, NULL };

	svcerr_t se = smfu_iter_svcs(h, read_services_svc_cb,
	    read_services_inst_cb, &rsd);

	*ret = result;
	return (se);
}

/* ARGSUSED */
conerr_t
interface_Master_read_services(rad_instance_t *inst, adr_attribute_t *attr,
    data_t **data, data_t **error)
{
	return (smfu_rtrun(rt_read_services, NULL, data, error));
}

struct read_instances_data {
	data_t *rid_result;

	/*
	 * For efficiency, reuse a single set of objects.
	 */
	scf_propertygroup_t *rid_pg;
	scf_property_t *rid_prop;
	scf_value_t *rid_val;
};

/*
 * master.instances instance iteration callback.  Constructs an
 * Instance and adds it to the list.
 */
/*ARGSUSED*/
static svcerr_t
read_instances_cb(scf_handle_t *scfhandle, scf_instance_t *instance,
    const char *sname, const char *iname, void *arg)
{
	if (!scf_instance_is_complete(instance))
		return (SE_OK);

	struct read_instances_data *rid = arg;
	svcerr_t se;

	data_t *inst = NULL;
	if ((se = create_Instance(instance, sname, iname, &inst,
	    rid->rid_pg, rid->rid_prop, rid->rid_val)) == SE_OK)
		(void) array_add(rid->rid_result, inst);

	return (se == SE_NOTFOUND ? SE_OK : se);
}

/*
 * master.instances read callback.  Iterates over all instances,
 * constructing a list of Instance objects that are returned to the
 * caller.
 */
/*ARGSUSED*/
static svcerr_t
rt_read_instances(scf_handle_t *h, void *arg, data_t **ret, data_t **error)
{
	struct read_instances_data rid;
	svcerr_t se;

	rid.rid_pg = scf_pg_create(h);
	rid.rid_prop = scf_property_create(h);
	rid.rid_val = scf_value_create(h);

	if (rid.rid_pg == NULL || rid.rid_prop == NULL || rid.rid_val == NULL) {
		se = SE_FATAL;
		goto out;
	}

	rid.rid_result = data_new_array(&t_array__Instance, 200);
	se = smfu_iter_svcs(h, NULL, read_instances_cb, &rid);

out:
	scf_value_destroy(rid.rid_val);
	scf_property_destroy(rid.rid_prop);
	scf_pg_destroy(rid.rid_pg);

	*ret = rid.rid_result;
	return (se);
}

/* ARGSUSED */
conerr_t
interface_Master_read_instances(rad_instance_t *inst, adr_attribute_t *attr,
    data_t **data, data_t **error)
{
	return (smfu_rtrun(rt_read_instances, NULL, data, error));
}

struct listdata {
	adr_name_t *ld_pattern;
	data_t *ld_result;
};

/*
 * Module linkage & dynamic namespace callbacks.
 */

/*
 * Dynamic list instance iteration callback.  Compares the instance with
 * the pattern; if it matches adds the instance's name to the list.
 */
/*ARGSUSED*/
static svcerr_t
list_insts(scf_handle_t *scfhandle, scf_instance_t *instance, const char *sname,
    const char *iname, void *arg)
{
	if (!scf_instance_is_complete(instance))
		return (SE_OK);

	struct listdata *ld = arg;
	adr_name_t *name = smfu_name_alloc(sname, iname);
	if (name == NULL)
		return (SE_FATAL);

	if (adr_name_match(name, ld->ld_pattern))
		(void) array_add(ld->ld_result,
		    data_new_string(adr_name_tostr(name), lt_free));
	adr_name_rele(name);

	return (SE_OK);
}

/*
 * Dynamic list service iteration callback.  Compares the service with
 * the pattern; if it matches adds the service's name to the list.
 */
/*ARGSUSED*/
static svcerr_t
list_svcs(scf_handle_t *scfhandle, scf_service_t *service, const char *sname,
    void *arg)
{
	struct listdata *ld = arg;
	adr_name_t *name = smfu_name_alloc(sname, NULL);
	if (name == NULL)
		return (SE_FATAL);

	if (adr_name_match(name, ld->ld_pattern))
		(void) array_add(ld->ld_result,
		    data_new_string(adr_name_tostr(name), lt_free));
	adr_name_rele(name);

	return (SE_OK);
}

struct arg_listf {
	adr_name_t *pattern;
	boolean_t instance;
};

/*
 * Dynamic namespace list callback.  Iterates over all services or
 * instances, accumulating their object names.
 */
/*ARGSUSED*/
static svcerr_t
rt_listf(scf_handle_t *h, void *arg, data_t **ret, data_t **error)
{
	struct arg_listf *rtarg = (struct arg_listf *)arg;
	data_t *result = data_new_array(&t_array_string, 300);
	struct listdata ld = { rtarg->pattern, result };

	svcerr_t se = smfu_iter_svcs(h, rtarg->instance ? NULL : list_svcs,
	    rtarg->instance ? list_insts : NULL, &ld);

	*ret = result;
	return (se);
}

/*
 * Dynamic namespace list handler.
 */
static conerr_t
smf_listf(adr_name_t *pattern, data_t **names, void *arg)
{
	struct arg_listf rtarg = { pattern, (boolean_t)arg };

	conerr_t ce = smfu_rtrun(rt_listf, &rtarg, names, NULL);
	return (ce == ce_object ? ce_system : ce);
}

/*
 * Dynamic namespace lookup handler.
 */
static conerr_t
smf_lookupf(adr_name_t **name, rad_instance_t **inst, void *arg)
{
	const char *sname = adr_name_key(*name, SMF_KEY_SERVICE);
	const char *iname = adr_name_key(*name, SMF_KEY_INSTANCE);
	const char *scope = adr_name_key(*name, SMF_KEY_SCOPE);
	boolean_t instance = (boolean_t)arg;
	int kcount = scope != NULL ? 3 : 2;	/* type, service, [scope] */

	if (instance) {
		/* Instances must specify an instance */
		if (iname == NULL)
			return (ce_notfound);
		kcount += 1;
	} else {
		/* Services may not specify an instance */
		if (iname != NULL)
			return (ce_notfound);
	}

	/* Reject names with bad keys/values */
	if (sname == NULL || kcount != adr_name_nkeys(*name))
		return (ce_notfound);

	/*
	 * Reject non-localhost scopes and remap localhost scopes to a
	 * canonical non-scoped form.
	 */
	if (scope != NULL) {
		if (strcmp(scope, SCF_SCOPE_LOCAL) != 0)
			return (ce_notfound);
		adr_name_t *newname = smfu_name_alloc(sname, iname);
		if (newname == NULL)
			return (ce_nomem);
		adr_name_rele(*name);
		*name = newname;
		assert(*inst == NULL);
		return (ce_ok);
	}

	/* Fail if the service/instance doesn't exist */
	if (smfu_test(sname, iname) != SE_OK)
		return (ce_notfound);

	/* Create and return new rad instance for the service/instance */

	smfobj_t *smfo;
	if ((smfo = smfu_obj_alloc(sname, iname)) == NULL)
		return (ce_nomem);

	*inst = instance_create(adr_name_hold(*name),
	    instance ? &interface_Instance_svr : &interface_Service_svr,
	    smfo, (void(*)(void *))smfu_obj_free);

	return (ce_ok);
}

static rad_modinfo_t modinfo = { "smf", "SMF module" };

int
_rad_init(void *handle)
{
	adr_name_t *spat, *ipat, *mpat;

	if (rad_module_register(handle, RAD_MODVERSION, &modinfo) == -1)
		return (-1);

	if (rad_isproxy)
		return (0);

	smfu_init();

	/*
	 * Create singleton, static master object.
	 */

	mpat = adr_name_vcreate(SMF_DOMAIN, 1, SMF_KEY_TYPE, SMF_TYPE_MASTER);
	rad_instance_t *agg_inst =
	    instance_create(mpat, &interface_Master_svr, NULL, NULL);
	if (agg_inst != NULL)
		(void) cont_insert(rad_container, agg_inst, INST_ID_PICK);

	/*
	 * Register dynamic namespace handlers for services and instances.
	 * We must register twice: once for type=service and once for
	 * type=instance.  We use the same callbacks for both.
	 */
	spat = adr_name_vcreate(SMF_DOMAIN, 1, SMF_KEY_TYPE, SMF_TYPE_SERVICE);
	if (spat != NULL) {
		(void) cont_register_dynamic(rad_container, spat, smf_listf,
		    smf_lookupf, (void *)B_FALSE);
		adr_name_rele(spat);
	}

	ipat = adr_name_vcreate(SMF_DOMAIN, 1, SMF_KEY_TYPE, SMF_TYPE_INSTANCE);
	if (ipat != NULL) {
		(void) cont_register_dynamic(rad_container, ipat, smf_listf,
		    smf_lookupf, (void *)B_TRUE);
		adr_name_rele(ipat);
	}

	return (0);
}
