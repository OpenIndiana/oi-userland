/*
 * Copyright (c) 2016, Oracle and/or its affiliates. All rights reserved.
 */

/*
 * Solaris Kerberos
 * This is a private header file, therefore the interfaces that this file
 * declares are subject to change without prior notice.
 */

#ifndef	_PROF_SOLARIS_H
#define	_PROF_SOLARIS_H

#include <profile.h>
#include <sys/types.h>

#define	K5_PROFILE_VAL_SUCCESS					0
#define	K5_PROFILE_VAL_DEF_REALM_CASE			1
#define	K5_PROFILE_VAL_REALM_CASE				2
#define	K5_PROFILE_VAL_NO_DEF_IN_REALM			3
#define	K5_PROFILE_VAL_NO_DEF_REALM				4
#define	K5_PROFILE_VAL_NULL_REALM				5
#define	K5_PROFILE_VAL_NO_DOM_REALM_MAP			6
#define	K5_PROFILE_VAL_KDC_NO_REALM				7
#define	K5_PROFILE_VAL_ADMIN_NO_REALM			8
#define	K5_PROFILE_VAL_DOM_REALM_CASE			9
#define	K5_PROFILE_VAL_NO_REALM					10

typedef struct _profile_options {
		char *name;
		int  *value;
		int  found;
} profile_options_boolean;

typedef struct _profile_times {
		char *name;
		char **value;
		int  found;
} profile_option_strings;

errcode_t
profile_get_options_boolean(profile_t, char **, profile_options_boolean *);

errcode_t
profile_get_options_string(profile_t, char **, profile_option_strings *);

long k5_profile_init(char *filename, profile_t *profile);
long k5_profile_release(profile_t profile);
void k5_profile_abandon(profile_t profile);
long k5_profile_add_domain_mapping(profile_t profile, char *domain,
    char *realm);
long k5_profile_remove_domain_mapping(profile_t profile, char *realm);
long k5_profile_get_realm_entry(profile_t profile, char *realm, char *name,
    char ***ret_value);
long k5_profile_add_realm_entry(profile_t profile, char *realm, char *name,
    char **values);
long k5_profile_get_libdefaults_entry(profile_t profile, char *name,
    char **ret_value);
long k5_profile_add_libdefaults_entry(profile_t profile, char *name,
    char *value);
long k5_profile_get_default_realm(profile_t profile, char **realm);
long k5_profile_get_realms(profile_t profile, char ***realms);
long k5_profile_add_realm(profile_t profile, char *realm, char *master,
    char **kdcs, boolean_t set_change, boolean_t default_realm);
long k5_profile_remove_xrealm_mapping(profile_t profile, char *realm);
long k5_profile_remove_realm(profile_t profile, char *realm);
long k5_profile_add_xrealm_mapping(profile_t profile, char *source,
    char *target, char *inter);
long k5_profile_validate(profile_t profile, char *realm, int *val_err,
    char **val, boolean_t master_required, boolean_t kdc_required);
long k5_profile_validate_get_error_msg(profile_t profile, int err, char *val,
    char **err_msg);
long k5_profile_set_libdefaults(profile_t profile, char *realm);

#endif /* _PROF_SOLARIS_H */
