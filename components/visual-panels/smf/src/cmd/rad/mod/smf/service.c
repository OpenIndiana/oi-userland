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

#include <stdio.h>
#include <rad/adr.h>
#include <rad/adr_object.h>
#include <rad/rad_modapi.h>

#include "api_smf.h"
#include "smfutil.h"
#include "rhandle.h"

/*
 * service.instances read callback.  Looks up the service, iterates
 * over its instances, stores their names in an array, and returns the
 * array to the caller.
 */
/*ARGSUSED*/
static svcerr_t
rt_read_instances(scf_handle_t *h, void *arg, data_t **ret, data_t **error)
{
	smfobj_t *smfo = arg;
	char iname[max_name + 1];
	svcerr_t se;
	smfu_entity_t entity = SMFU_ENTITY_INIT;
	data_t *array = data_new_array(&t_array_string, 5);

	scf_instance_t *instance = scf_instance_create(h);
	scf_iter_t *iter = scf_iter_create(h);

	if (instance == NULL || iter == NULL) {
		se = SE_FATAL;
		goto done;
	}

	if ((se = smfu_lookup(h, smfo->sname, NULL, &entity)) != SE_OK)
		goto done;

	if (scf_iter_service_instances(iter, entity.service) != 0) {
		se = smfu_maperr(scf_error());
		goto done;
	}

	int err;
	while ((err = scf_iter_next_instance(iter, instance)) > 0) {
		if (scf_instance_get_name(instance, iname,
		    sizeof (iname)) == -1) {
			se = smfu_maperr(scf_error());
			goto done;
		}
		(void) array_add(array, data_new_string(iname, lt_copy));
	}

	if (err != 0)
		se = smfu_maperr(scf_error());

done:
	smfu_entity_destroy(&entity);
	scf_instance_destroy(instance);
	scf_iter_destroy(iter);

	*ret = array;
	return (se);
}

/*ARGSUSED*/
conerr_t
interface_Service_read_instances(rad_instance_t *inst, adr_attribute_t *attr,
    data_t **data, data_t **error)
{
	return (smfu_rtrun(rt_read_instances, instance_getdata(inst), data,
	    error));
}
