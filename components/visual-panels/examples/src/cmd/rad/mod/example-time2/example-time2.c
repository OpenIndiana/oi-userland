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

#include <sys/types.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>
#include <limits.h>

#include <rad/adr.h>
#include <rad/rad_modapi.h>

#include "api_example_time2.h"

/*ARGSUSED*/
conerr_t
interface_Time_read_time(rad_instance_t *inst, adr_attribute_t *attr,
    adr_data_t **data, adr_data_t **error)
{
	*data = adr_data_new_long((long long)time(NULL) * 1000);
	return (CE_OK);
}

/*ARGSUSED*/
conerr_t
interface_Time_write_time(rad_instance_t *inst, adr_attribute_t *attr,
    adr_data_t *data, adr_data_t **error)
{
	long long rawtime = adr_data_to_longint(data) / 1000;
	time_t newtime = (time_t)rawtime;

	if (rawtime > LONG_MAX)
		return (CE_OBJECT);

	if (stime(&newtime) == -1) {
		if (errno == EPERM)
			return (CE_PRIV);
		return (CE_OBJECT);
	}

	return (CE_OK);
}


int
_rad_init(void)
{
	adr_name_t *name = adr_name_vcreate(
	    MOD_DOMAIN, 1, "type", "Time");
	(void) rad_cont_insert_singleton(rad_container, name, &modinfo,
	    &interface_Time_svr);

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
