/*
 * Copyright (c) 2015, Oracle and/or its affiliates. All rights reserved.
 */

/*
 * missing_interfaces.c:
 *
 * Following two interfaces are to provide runtime dependencies for kerberos
 * related components staying in ON.
 *
 */
#include <krb5/krb5.h>
#include <profile.h>

/* avoid including krb5-int.h, it defines functions and introduces deps */
extern void k5_des_fixup_key_parity(unsigned char *keybits);
extern krb5_error_code k5_os_init_context(krb5_context context,
                                          profile_t profile, krb5_flags flags);
typedef unsigned char mit_des_cblock[8];

void
mit_des_fixup_key_parity(mit_des_cblock key)
{
    k5_des_fixup_key_parity(key);
}

krb5_error_code
krb5_os_init_context(krb5_context ctx, krb5_boolean kdc)
{
    return k5_os_init_context(ctx, NULL, kdc? 0x2 : 0x0);
}
