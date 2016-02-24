/*
 * Copyright (c) 2014, 2015, Oracle and/or its affiliates. All rights reserved.
 */

#include "mglueP.h"

OM_uint32
__gss_mech_to_oid(const char *mechStr, gss_OID* oid) {
	return (gssint_mech_to_oid(mechStr, oid));
}

const char *
__gss_oid_to_mech(const gss_OID oid) {
	return (gssint_oid_to_mech(oid));
}

OM_uint32
__gss_get_mechanisms(char *mechArray[], int arrayLen) {
	return (gssint_get_mechanisms(mechArray, arrayLen));
}

char *
__gss_get_kmodName(const gss_OID oid) {
	return (gssint_get_kmodName(oid));
}

gss_mechanism
__gss_get_mechanism(const gss_OID oid) {
	return (gssint_get_mechanism(oid));
}

char *
__gss_get_modOptions(const gss_OID oid) {
	return (gssint_get_modOptions(oid));
}

OM_uint32
__gss_get_mech_type(gss_OID OID, gss_buffer_t token) {
	return (gssint_get_mech_type(OID, token));
}

unsigned int
der_length_size(unsigned int len) {
	return (gssint_der_length_size(len));
}

int
get_der_length(unsigned char **buf, unsigned int buf_len, unsigned int *bytes) {
	return (gssint_get_der_length(buf, buf_len, bytes));
}

int
put_der_length(unsigned int length, unsigned char **buf, unsigned int max_len) {
	return (gssint_put_der_length(length, buf, max_len));
}

OM_uint32
__gss_get_mech_info(char *mech, char **qops) {
	return (gssint_get_mech_info(mech, qops));
}

OM_uint32
__gss_num_to_qop(char *mech, OM_uint32 num, char **qop) {
	return (gssint_num_to_qop(mech, num, qop));
}

OM_uint32
__gss_qop_to_num(char *qop, char *mech, OM_uint32 *num) {
	return (gssint_qop_to_num(qop, mech, num));
}

/*
 * Wrapper __gss_userok -> gss_authorize_localname
 */
OM_uint32
__gss_userok(OM_uint32 *minor, const gss_name_t name, const char *user,
	    int *user_ok) {
	OM_uint32 ret, dummy_minor;
	gss_buffer_desc user_buf;
	gss_name_t user_name;

	*user_ok = 0;

	user_buf.value = (void *)user;
	user_buf.length = strlen(user);

	ret = gss_import_name(minor, &user_buf, GSS_C_NT_USER_NAME, &user_name);
	if (GSS_ERROR(ret))
		return (ret);

	ret = gss_authorize_localname(minor, name, user_name);
	if (ret == GSS_S_COMPLETE)
		*user_ok = 1;

	(void) gss_release_name(&dummy_minor, &user_name);

	return (ret);
}
