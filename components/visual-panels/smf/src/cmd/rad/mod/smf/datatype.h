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

#ifndef	_DATATYPE_H
#define	_DATATYPE_H

#include <sys/types.h>
#include <rad/adr.h>
#include <rad/rad_modapi.h>
#include <libscf.h>

#include "smfutil.h"

#ifdef	__cplusplus
extern "C" {
#endif

data_t *create_SMFState(const char *);
scf_type_t from_PropertyType(data_t *);

svcerr_t create_Dependency(scf_handle_t *, scf_propertygroup_t *, data_t **);
svcerr_t create_Manpage(scf_handle_t *, scf_propertygroup_t *, data_t **);
svcerr_t create_Doclink(scf_handle_t *, scf_propertygroup_t *, data_t **);

svcerr_t create_PropertyGroup(scf_propertygroup_t *, data_t **);

svcerr_t create_Property(scf_property_t *, scf_iter_t *, scf_value_t *,
    data_t **, data_t **);
svcerr_t create_Properties(scf_handle_t *, scf_propertygroup_t *, data_t **,
    data_t **);

svcerr_t create_ExtendedState(scf_handle_t *, scf_instance_t *, data_t **);

svcerr_t create_PGTemplate(scf_pg_tmpl_t *, const char *, data_t **);
svcerr_t create_PropTemplate(scf_prop_tmpl_t *, const char *, data_t **);

svcerr_t create_Instance(scf_instance_t *, const char *, const char *,
    data_t **, scf_propertygroup_t *, scf_property_t *, scf_value_t *);

#ifdef	__cplusplus
}
#endif

#endif	/* _DATATYPE_H */
