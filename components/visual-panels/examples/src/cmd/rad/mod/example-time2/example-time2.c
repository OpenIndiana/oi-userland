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

#include "api_example-time2.h"

/*ARGSUSED*/
conerr_t
interface_Time_read_time(rad_instance_t *inst, adr_attribute_t *attr,
    data_t **data, data_t **error)
{
	*data = data_new_long((long long)time(NULL) * 1000);
	return (ce_ok);
}

/*ARGSUSED*/
conerr_t
interface_Time_write_time(rad_instance_t *inst, adr_attribute_t *attr,
    data_t *data, data_t **error)
{
	long long rawtime = data_to_longint(data) / 1000;
	time_t newtime = (time_t)rawtime;

	if (rawtime > LONG_MAX)
		return (ce_object);

	if (stime(&newtime) == -1) {
		if (errno == EPERM)
			return (ce_priv);
		return (ce_object);
	}

	return (ce_ok);
}

static rad_modinfo_t modinfo = { "example-time2", "Example Time2" };

int
_rad_init(void *handle)
{
	if (rad_module_register(handle, RAD_MODVERSION, &modinfo) == -1)
		return (-1);

	if (rad_isproxy)
		return (0);

	adr_name_t *name = adr_name_fromstr(
	    "com.oracle.solaris.vp.panels.example.time2:type=Time");
	(void) cont_insert_singleton(rad_container, name,
	    &interface_Time_svr);

	return (0);
}
