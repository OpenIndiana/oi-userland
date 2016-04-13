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
 *
 * Copyright (c) 2010, Oracle and/or its affiliates. All rights reserved.
 */

#pragma ident	"@(#)e_devcrypto_err.c	1.1	10/10/19 SMI"

#include "e_devcrypto_err.h"

/* BEGIN ERROR CODES */

#ifndef OPENSSL_NO_ERR

#define	ERR_FUNC(func) ERR_PACK(0, func, 0)
#define	ERR_REASON(reason) ERR_PACK(0, 0, reason)

static ERR_STRING_DATA devcrypto_str_functs[]=
{
{ ERR_FUNC(DEVC_F_INIT),		"DEVCRYPTO_INIT"},
{ ERR_FUNC(DEVC_F_DESTROY),		"DEVCRYPTO_DESTROY"},
{ ERR_FUNC(DEVC_F_FINISH),		"DEVCRYPTO_FINISH"},
{ ERR_FUNC(DEVC_F_CIPHER_INIT),		"DEVCRYPTO_CIPHER_INIT"},
{ ERR_FUNC(DEVC_F_CIPHER_DO_CIPHER),	"DEVCRYPTO_CIPHER_DO_CIPHER"},
{ ERR_FUNC(DEVC_F_CIPHER_CLEANUP),	"DEVCRYPTO_CIPHER_CLEANUP"},
{ 0, NULL}
};

static ERR_STRING_DATA devcrypto_str_reasons[]=
{
{ ERR_REASON(DEVC_R_CIPHER_KEY), "invalid cipher key"},
{ ERR_REASON(DEVC_R_CIPHER_NID), "invalid cipher nid"},
{ ERR_REASON(DEVC_R_KEY_OR_IV_LEN_PROBLEM), "IV or key length incorrect"},
{ ERR_REASON(DEVC_R_MECH_STRING), "convert cipher type to string failed"},
{ ERR_REASON(DEVC_R_FIND_SLOT_BY_MECH),
	"no hardware providers support this cipher"},
{ ERR_REASON(DEVC_R_OPEN_SESSION), "CRYPTO_OPEN_SESSION failed"},
{ ERR_REASON(DEVC_R_GET_MECHANISM_NUMBER),
	"CRYPTO_GET_MECHANISM_NUMBER failed"},
{ ERR_REASON(DEVC_R_ENCRYPT_INIT),  	"CRYPTO_ENCRYPT_INIT failed"},
{ ERR_REASON(DEVC_R_ENCRYPT_UPDATE),  	"CRYPTO_ENCRYPT_UPDATE failed"},
{ ERR_REASON(DEVC_R_ENCRYPT_FINAL),  	"CRYPTO_ENCRYPT_FINAL failed"},
{ ERR_REASON(DEVC_R_DECRYPT_INIT),  	"CRYPTO_DECRYPT_INIT failed"},
{ ERR_REASON(DEVC_R_DECRYPT_UPDATE),  	"CRYPTO_DECRYPT_UPDATE failed"},
{ ERR_REASON(DEVC_R_DECRYPT_FINAL),  	"CRYPTO_DECRYPT_FINAL failed"},
{ ERR_REASON(DEVC_R_CLOSE_SESSION),  	"CRYPTO_CLOSE_SESSION failed"},
{ 0, NULL}
};
#endif	/* OPENSSL_NO_ERR */


#ifdef DEVCRYPTO_LIB_NAME
static ERR_STRING_DATA DEVCRYPTO_lib_name[]=
{
{0, DEVCRYPTO_LIB_NAME},
{0, NULL}
};
#endif

static int devcrypto_error_code = 0;
static int devcrypto_error_init = 1;

static void
ERR_load_devcrypto_strings(void)
{
	if (devcrypto_error_code == 0)
		devcrypto_error_code = ERR_get_next_error_library();

	if (devcrypto_error_init) {
		devcrypto_error_init = 0;

#ifndef OPENSSL_NO_ERR
		ERR_load_strings(devcrypto_error_code, devcrypto_str_functs);
		ERR_load_strings(devcrypto_error_code, devcrypto_str_reasons);
#endif

#ifdef DEVCRYPTO_LIB_NAME
		DEVCRYPTO_lib_name->error =
		    ERR_PACK(devcrypto_error_code, 0, 0);
		ERR_load_strings(0, DEVCRYPTO_lib_name);
#endif
	}
}

static void
ERR_unload_devcrypto_strings(void)
{
	if (devcrypto_error_init == 0) {
#ifndef OPENSSL_NO_ERR
		ERR_unload_strings(devcrypto_error_code, devcrypto_str_functs);
		ERR_unload_strings(devcrypto_error_code, devcrypto_str_reasons);
#endif

#ifdef DEVCRYPTO_LIB_NAME
		ERR_unload_strings(0, DEVCRYPTO_lib_name);
#endif
		devcrypto_error_init = 1;
	}
}

static void
ERR_devcrypto_error(int function, int reason, char *file, int line)
{
	if (devcrypto_error_code == 0)
		devcrypto_error_code = ERR_get_next_error_library();
	ERR_PUT_error(devcrypto_error_code, function, reason, file, line);
}
