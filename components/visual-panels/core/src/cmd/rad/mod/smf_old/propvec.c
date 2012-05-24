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
 * Copyright (c) 2009, 2012, Oracle and/or its affiliates. All rights reserved.
 */

#include <assert.h>
#include <stdio.h>
#include <strings.h>
#include <string.h>
#include <stdlib.h>
#include <sys/param.h>
#include <errno.h>
#include <libscf.h>
#include "propvec.h"

extern scf_handle_t *handle_create(void);

static scf_type_t
scf_true_base_type(scf_type_t type)
{
	scf_type_t base = type;

	do {
		type = base;
		(void) scf_type_base_type(type, &base);
	} while (base != type);

	return (base);
}

/*
 * Convenience routine which frees all strings and opaque data
 * allocated by scf_read_propvec.
 *
 * Like free(3C), this function preserves the value of errno.
 */
void
rad_clean_propvec(rad_propvec_t *propvec)
{
	int saved_errno = errno;
	rad_propvec_t *prop;

	for (prop = propvec; prop->pv_prop != NULL; prop++) {
		assert(prop->pv_type != SCF_TYPE_INVALID);
		if (prop->pv_type == SCF_TYPE_OPAQUE) {
			rad_opaque_t *o = prop->pv_ptr;

			if (o->so_addr != NULL)
				free(o->so_addr);
		} else if (scf_true_base_type(prop->pv_type) ==
		    SCF_TYPE_ASTRING) {
			if (*(char **)prop->pv_ptr != NULL)
				free(*(char **)prop->pv_ptr);
		}
	}

	errno = saved_errno;
}

/*
 * Reads a vector of properties from the specified fmri/property group.
 * If 'running' is true, reads from the running snapshot instead of the
 * editing snapshot.
 *
 * For string types, a buffer is allocated using malloc(3C) to hold the
 * zero-terminated string, a pointer to which is stored in the
 * caller-provided char **.  It is the caller's responsbility to free
 * this string.  To simplify error handling, unread strings are
 * initialized to NULL.
 *
 * For opaque types, a buffer is allocated using malloc(3C) to hold the
 * opaque data.  A pointer to this buffer and its size are stored in
 * the caller-provided rad_opaque_t.  It is the caller's responsibility
 * to free this buffer.  To simplify error handling, the address fields
 * for unread opaque data are initialized to NULL.
 *
 * All other data is stored directly in caller-provided variables or
 * structures.
 *
 * If this function fails to read a specific property, *badprop is set
 * to point at that property's entry in the properties array.
 *
 * On all failures, all memory allocated by this function is freed.
 */
int
rad_read_propvec(const char *fmri, const char *pgname, boolean_t running,
    rad_propvec_t *properties, rad_propvec_t **badprop)
{
	scf_handle_t *h = handle_create();
	scf_service_t *s = scf_service_create(h);
	scf_instance_t *i = scf_instance_create(h);
	scf_snapshot_t *snap = running ? scf_snapshot_create(h) : NULL;
	scf_propertygroup_t *pg = scf_pg_create(h);
	scf_property_t *p = scf_property_create(h);
	scf_value_t *v = scf_value_create(h);
	boolean_t instance = B_TRUE;
	rad_propvec_t *prop;
	int error = 0;

	for (prop = properties; prop->pv_prop != NULL; prop++) {
		if (prop->pv_type == SCF_TYPE_OPAQUE)
			((rad_opaque_t *)prop->pv_ptr)->so_addr = NULL;
		else if (scf_true_base_type(prop->pv_type) == SCF_TYPE_ASTRING)
			*((char **)prop->pv_ptr) = NULL;
	}

	if (h == NULL || s == NULL || i == NULL || (running && snap == NULL) ||
	    pg == NULL || p == NULL || v == NULL)
		goto scferror;

	if (scf_handle_decode_fmri(h, fmri, NULL, s, i, NULL, NULL, 0) == -1)
		goto scferror;

	if (scf_instance_to_fmri(i, NULL, 0) == -1) {
		if (scf_error() != SCF_ERROR_NOT_SET)
			goto scferror;
		instance = B_FALSE;
	}

	if (running) {
		if (!instance) {
			error = SCF_ERROR_TYPE_MISMATCH;
			goto out;
		}

		if (scf_instance_get_snapshot(i, "running", snap) !=
		    SCF_SUCCESS)
			goto scferror;
	}

	if ((instance ? scf_instance_get_pg_composed(i, snap, pgname, pg) :
	    scf_service_get_pg(s, pgname, pg)) == -1)
		goto scferror;

	for (prop = properties; prop->pv_prop != NULL; prop++) {
		int ret = 0;

		if (scf_pg_get_property(pg, prop->pv_prop, p) == -1 ||
		    scf_property_get_value(p, v) == -1) {
			*badprop = prop;
			goto scferror;
		}
		switch (prop->pv_type) {
		case SCF_TYPE_BOOLEAN: {
			uint8_t b;

			ret = scf_value_get_boolean(v, &b);
			if (ret == -1)
				break;
			if (prop->pv_aux != 0) {
				uint64_t *bits = prop->pv_ptr;
				*bits = b ? (*bits | prop->pv_aux) :
				    (*bits & ~prop->pv_aux);
			} else {
				boolean_t *bool = prop->pv_ptr;
				*bool = b ? B_TRUE : B_FALSE;
			}
			break;
		}
		case SCF_TYPE_COUNT:
			ret = scf_value_get_count(v, prop->pv_ptr);
			break;
		case SCF_TYPE_INTEGER:
			ret = scf_value_get_integer(v, prop->pv_ptr);
			break;
		case SCF_TYPE_TIME: {
			scf_time_t *time = prop->pv_ptr;

			ret = scf_value_get_time(v, &time->t_seconds,
			    &time->t_ns);
			break;
		}
		case SCF_TYPE_OPAQUE: {
			rad_opaque_t *opaque = prop->pv_ptr;
			ssize_t size = scf_value_get_opaque(v, NULL, 0);

			if (size == -1) {
				*badprop = prop;
				goto scferror;
			}
			if ((opaque->so_addr = malloc(size)) == NULL) {
				error = SCF_ERROR_NO_MEMORY;
				rad_clean_propvec(properties);
				goto out;
			}
			opaque->so_size = size;
			ret = scf_value_get_opaque(v, opaque->so_addr, size);
			break;
		}
		default: {
			char *s;
			ssize_t size;

			assert(scf_true_base_type(prop->pv_type) ==
			    SCF_TYPE_ASTRING);

			size = scf_value_get_astring(v, NULL, 0);
			if (size == -1) {
				*badprop = prop;
				goto scferror;
			}
			if ((s = malloc(++size)) == NULL) {
				error = SCF_ERROR_NO_MEMORY;
				rad_clean_propvec(properties);
				goto out;
			}
			ret = scf_value_get_astring(v, s, size);
			*(char **)prop->pv_ptr = s;
		}

		if (ret == -1) {
			*badprop = prop;
			goto scferror;
		}

		}
	}

	goto out;

scferror:
	error = scf_error();
	rad_clean_propvec(properties);
out:
	scf_value_destroy(v);
	scf_property_destroy(p);
	scf_pg_destroy(pg);
	scf_snapshot_destroy(snap);
	scf_instance_destroy(i);
	scf_service_destroy(s);
	scf_handle_destroy(h);

	return (error);
}
