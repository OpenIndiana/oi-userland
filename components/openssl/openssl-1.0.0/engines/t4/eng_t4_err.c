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
 * Copyright (c) 2011, Oracle and/or its affiliates. All rights reserved.
 */

#include <openssl/err.h>
#include "eng_t4_err.h"

/* BEGIN ERROR CODES */

#ifndef	OPENSSL_NO_ERR

#define	ERR_FUNC(func)		ERR_PACK(0, func, 0)
#define	ERR_REASON(reason)	ERR_PACK(0, 0, reason)

static ERR_STRING_DATA t4_str_functs[] = {
	{ERR_FUNC(T4_F_INIT),			"T4_INIT"},
	{ERR_FUNC(T4_F_DESTROY),		"T4_DESTROY"},
	{ERR_FUNC(T4_F_FINISH),			"T4_FINISH"},
	{ERR_FUNC(T4_F_CIPHER_INIT_AES),	"T4_CIPHER_INIT_AES"},
	{ERR_FUNC(T4_F_ADD_NID),		"T4_ADD_NID"},
	{ERR_FUNC(T4_F_GET_ALL_CIPHERS),	"T4_GET_ALL_CIPHERS"},
	{ERR_FUNC(T4_F_CIPHER_DO_AES),		"T4_CIPHER_DO_AES"},
	{ERR_FUNC(T4_F_CIPHER_CLEANUP),		"T4_CIPHER_CLEANUP"},
	{0, NULL}
};

static ERR_STRING_DATA t4_str_reasons[] = {
	{ERR_REASON(T4_R_CIPHER_KEY),		"invalid cipher key"},
	{ERR_REASON(T4_R_CIPHER_NID),		"invalid cipher NID"},
	{ERR_REASON(T4_R_IV_LEN_INCORRECT),	"IV length incorrect"},
	{ERR_REASON(T4_R_KEY_LEN_INCORRECT),	"key length incorrect"},
	{ERR_REASON(T4_R_ASN1_OBJECT_CREATE),	"ASN1_OBJECT_create failed"},
	{ERR_REASON(T4_R_NOT_BLOCKSIZE_LENGTH),	"blocksize length not even"},
	{0, NULL}
};
#endif	/* OPENSSL_NO_ERR */


#ifdef T4_LIB_NAME
static ERR_STRING_DATA T4_lib_name[] = {
	{0, T4_LIB_NAME},
	{0, NULL}
};
#endif

static int t4_error_code = 0;
static int t4_error_init = 1;


static void
ERR_load_t4_strings(void)
{
	if (t4_error_code == 0)
		t4_error_code = ERR_get_next_error_library();

	if (t4_error_init != 0) {
		t4_error_init = 0;

#ifndef OPENSSL_NO_ERR
		ERR_load_strings(t4_error_code, t4_str_functs);
		ERR_load_strings(t4_error_code, t4_str_reasons);
#endif

#ifdef T4_LIB_NAME
		T4_lib_name->error =
		    ERR_PACK(t4_error_code, 0, 0);
		ERR_load_strings(0, T4_lib_name);
#endif
	}
}


static void
ERR_unload_t4_strings(void)
{
	if (t4_error_init == 0) {
#ifndef OPENSSL_NO_ERR
		ERR_unload_strings(t4_error_code, t4_str_functs);
		ERR_unload_strings(t4_error_code, t4_str_reasons);
#endif

#ifdef T4_LIB_NAME
		ERR_unload_strings(0, T4_lib_name);
#endif
		t4_error_init = 1;
	}
}


static void
ERR_t4_error(int function, int reason, char *file, int line)
{
	if (t4_error_init != 0) {
		ERR_load_t4_strings();
	}

	if (t4_error_code == 0)
		t4_error_code = ERR_get_next_error_library();
	ERR_PUT_error(t4_error_code, function, reason, file, line);
}
