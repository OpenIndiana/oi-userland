/*
 * Copyright (c) 2010, 2016, Oracle and/or its affiliates. All rights reserved.
 */

/*
 * Solaris Kerberos
 * This is a private header file, therefore the interfaces that this file
 * declares are subject to change without prior notice.
 */

#ifndef	_KT_SOLARIS_H
#define	_KT_SOLARIS_H

#ifdef	__cplusplus
extern "C" {
#endif

#define	K5_KT_FLAG_AES_SUPPORT	1

krb5_error_code k5_kt_add_ad_entries(krb5_context, char **, char *, krb5_kvno,
    uint_t, char *, char *);

krb5_error_code k5_kt_remove_by_realm(krb5_context, char *);

krb5_error_code k5_kt_remove_by_svcprinc(krb5_context, char *);

krb5_error_code k5_kt_ad_validate(krb5_context, char *, uint_t, boolean_t *);

#ifdef	__cplusplus
}
#endif

#endif /* _KT_SOLARIS_H */
