/*
 * Copyright (c) 2009, 2015, Oracle and/or its affiliates. All rights reserved.
 */
/*
 * Solaris Kerberos:
 * Iterate through a keytab (keytab) looking for an entry which matches
 * the components of a principal (princ) but match on any realm. When a
 * suitable entry is found return the entry's realm.
 */

#include "k5-int.h"

krb5_error_code krb5_kt_find_realm(krb5_context context, krb5_keytab keytab,
    krb5_principal princ, krb5_data *realm) {

	krb5_kt_cursor cur;
	krb5_keytab_entry ent;
	krb5_boolean match;
	krb5_data tmp_realm;
	krb5_error_code ret, ret2;

	ret = krb5_kt_start_seq_get(context, keytab, &cur);
	if (ret != 0) {
		return (ret);
	}

	while ((ret = krb5_kt_next_entry(context, keytab, &ent, &cur)) == 0) {
		/* For the comparison the realms should be the same. */
		memcpy(&tmp_realm, &ent.principal->realm, sizeof (krb5_data));
		memcpy(&ent.principal->realm, &princ->realm,
		    sizeof (krb5_data));

		match = krb5_principal_compare(context, ent.principal, princ);

		/* Copy the realm back */
		memcpy(&ent.principal->realm, &tmp_realm, sizeof (krb5_data));

		if (match) {
			/*
			 * A suitable entry was found in the keytab.
			 * Copy its realm
			 */
			ret = krb5int_copy_data_contents(context,
			    &ent.principal->realm, realm);
			if (ret) {
				krb5_kt_free_entry(context, &ent);
				krb5_kt_end_seq_get(context, keytab, &cur);
				return (ret);
			}

			krb5_kt_free_entry(context, &ent);
			break;
		}

		krb5_kt_free_entry(context, &ent);
	}

	ret2 = krb5_kt_end_seq_get(context, keytab, &cur);

	if (ret == KRB5_KT_END) {
		return (KRB5_KT_NOTFOUND);
	}

	return (ret ? ret : ret2);
}
