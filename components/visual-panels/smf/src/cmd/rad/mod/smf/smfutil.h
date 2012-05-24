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

#ifndef	_SMFUTIL_H
#define	_SMFUTIL_H

#include <sys/types.h>
#include <rad/adr.h>
#include <rad/rad_modapi.h>
#include <libscf.h>

#ifdef	__cplusplus
extern "C" {
#endif

/*
 * SMF object names.
 *
 * All names are in the "com.oracle.solaris.rad.smf" domain.
 *
 * Services have a "type" of "Service", and specify a "service" name.
 *
 * Instances have a "type" of "Instance, and specify both "service" and
 * "instance" names.
 *
 * Both services and instances may specify a "scope".  If no scope is
 * specified, localhost is assumed.  The canonical object name for an
 * object with a scope of localhost does not specify a scope.
 *
 * A singleton object of "type" "Master" provides aggregate information
 * and operations.
 */

#define	SMF_DOMAIN		"com.oracle.solaris.rad.smf"
#define	SMF_KEY_TYPE		"type"
#define	SMF_TYPE_INSTANCE	"Instance"
#define	SMF_TYPE_SERVICE	"Service"
#define	SMF_TYPE_MASTER		"Master"
#define	SMF_KEY_SCOPE		"scope"
#define	SMF_KEY_SERVICE		"service"
#define	SMF_KEY_INSTANCE	"instance"

/*
 * Error conditions used to manage flow within the SMF module.
 */
typedef enum svcerr {
			/* Top-level error conditions */
	SE_OK,		/* Success */
	SE_FATAL,	/* Operation failed */
	SE_NOTFOUND,	/* Something not found (fatal if uncaught) */
	SE_STALE,	/* Service/instance not found (stale rad instance) */
	SE_RECONNECT,	/* Reconnect and retry */
	SE_RETRY,	/* Retry w/o reconnecting */

			/* Special internal error conditions */
	SE_BREAK	/* Stop iterating, return SE_OK */
} svcerr_t;

/*
 * Per service/instance rad instance data
 */
typedef struct smfobj {
	char *sname;
	char *iname;
	char *fmri;
} smfobj_t;

/*
 * A simple abstraction around what could be a service or an instance.
 */
typedef struct smfu_entity {
	scf_service_t *service;
	scf_instance_t *instance;
} smfu_entity_t;

#define	SMFU_ENTITY_INIT	{ NULL, NULL }

/*
 * Useful SMF constants obtainable only programmatically.
 */
extern ssize_t max_fmri;
extern ssize_t max_name;
extern ssize_t max_value;
extern ssize_t max_pgtype;

/*
 * Error handling routines
 */
svcerr_t error_scf(data_t **, data_t *, data_t *, const char *, const char *);
svcerr_t internal_error(data_t **error, const char *msg);
svcerr_t smfu_maperr(scf_error_t);

typedef svcerr_t (*svc_callback_t)(scf_handle_t *, scf_service_t *,
    const char *sname, void *arg);
typedef svcerr_t (*inst_callback_t)(scf_handle_t *, scf_instance_t *,
    const char *sname, const char *iname, void *arg);

/*
 * SCF-like factored routines
 */
scf_error_t smfu_read_enabled(scf_instance_t *, scf_propertygroup_t *,
    scf_property_t *, scf_value_t *, const char *, uint8_t *);
scf_error_t smfu_value_get_string(scf_value_t *val, char **strp);
svcerr_t smfu_instance_get_composed_pg(scf_handle_t *handle,
    scf_instance_t *instance, const char *snapname, const char *pgname,
    scf_propertygroup_t *pg, data_t **error);
scf_error_t smfu_instance_iter_composed_pgs(scf_handle_t *handle,
    scf_instance_t *instance, const char *snapname, const char *pgtype,
    scf_iter_t *iter);

svcerr_t smfu_get_l10n_str(scf_handle_t *handle, scf_propertygroup_t *pg,
    const char *locale, char **result);

/*
 * Operate on directly-attached property groups.
 */
svcerr_t smfu_get_pg(smfu_entity_t *entity, const char *name,
    scf_propertygroup_t *pg, data_t **);
svcerr_t smfu_iter_pg(smfu_entity_t *entity, const char *type,
    scf_iter_t *iter);

/*
 * Operate on an instance's running snapshot or a service.
 */
svcerr_t smfu_get_pg_r(scf_handle_t *handle, smfu_entity_t *entity,
    const char *name, scf_propertygroup_t *pg);
svcerr_t smfu_iter_pg_r(scf_handle_t *handle, smfu_entity_t *entity,
    const char *type, scf_iter_t *iter);

/*
 * Service/instance lookup routines.
 */
svcerr_t smfu_iter_svcs(scf_handle_t *, svc_callback_t, inst_callback_t,
    void *);
svcerr_t smfu_lookup(scf_handle_t *, const char *, const char *,
    smfu_entity_t *);
svcerr_t smfu_test(const char *, const char *);

void smfu_entity_destroy(smfu_entity_t *);

adr_name_t *smfu_name_alloc(const char *, const char *);
char *smfu_fmri_alloc(const char *, const char *);
smfobj_t *smfu_obj_alloc(const char *, const char *);
void smfu_obj_free(smfobj_t *);

/* A frequently used lexical scope surrogate */
typedef struct radarg {
	rad_instance_t *inst;
	data_t **args;
} radarg_t;

typedef svcerr_t (*smfu_rtfunc_t)(scf_handle_t *, void *, data_t **, data_t **);
conerr_t smfu_rtrun(smfu_rtfunc_t, void *, data_t **, data_t **);
conerr_t smfu_rtrun_opt(smfu_rtfunc_t, void *, data_t **, data_t **);

void smfu_init();

#ifdef	__cplusplus
}
#endif

#endif	/* _SMFUTIL_H */
