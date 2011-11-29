/*
 * This product includes cryptographic software developed by the OpenSSL
 * Project for use in the OpenSSL Toolkit (http://www.openssl.org/).
 */

/*
 * ====================================================================
 * Copyright (c) 1998-2011 The OpenSSL Project.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * 3. All advertising materials mentioning features or use of this
 *    software must display the following acknowledgment:
 *    "This product includes software developed by the OpenSSL Project
 *    for use in the OpenSSL Toolkit. (http://www.openssl.org/)"
 *
 * 4. The names "OpenSSL Toolkit" and "OpenSSL Project" must not be used to
 *    endorse or promote products derived from this software without
 *    prior written permission. For written permission, please contact
 *    openssl-core@openssl.org.
 *
 * 5. Products derived from this software may not be called "OpenSSL"
 *    nor may "OpenSSL" appear in their names without prior written
 *    permission of the OpenSSL Project.
 *
 * 6. Redistributions of any form whatsoever must retain the following
 *    acknowledgment:
 *    "This product includes software developed by the OpenSSL Project
 *    for use in the OpenSSL Toolkit (http://www.openssl.org/)"
 *
 * THIS SOFTWARE IS PROVIDED BY THE OpenSSL PROJECT ``AS IS'' AND ANY
 * EXPRESSED OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE OpenSSL PROJECT OR
 * ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 * ====================================================================
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
	{ERR_FUNC(T4_F_CIPHER_INIT_DES),	"T4_CIPHER_INIT_DES"},
	{ERR_FUNC(T4_F_CIPHER_DO_DES),		"T4_CIPHER_DO_DES"},
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
