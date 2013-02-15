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

#ifndef	ENG_T4_ERR_H
#define	ENG_T4_ERR_H

#ifdef	__cplusplus
extern "C" {
#endif

static void ERR_unload_t4_strings(void);
#pragma inline(ERR_unload_t4_strings)
static void ERR_t4_error(int function, int reason, char *file, int line);

#define	T4err(f, r)	ERR_t4_error((f), (r), __FILE__, __LINE__)

/* Function codes */
#define	T4_F_INIT 				100
#define	T4_F_DESTROY 				101
#define	T4_F_FINISH				102
#define	T4_F_CIPHER_INIT_AES			103
#define	T4_F_ADD_NID				104
#define	T4_F_GET_ALL_CIPHERS			105
#define	T4_F_CIPHER_DO_AES			106
#define	T4_F_CIPHER_CLEANUP			107
#define	T4_F_CIPHER_INIT_DES			108
#define	T4_F_CIPHER_DO_DES			109

/* Reason codes */
#define	T4_R_CIPHER_KEY				100
#define	T4_R_CIPHER_NID				101
#define	T4_R_IV_LEN_INCORRECT			102
#define	T4_R_KEY_LEN_INCORRECT			103
#define	T4_R_ASN1_OBJECT_CREATE			104
#define	T4_R_NOT_BLOCKSIZE_LENGTH		105

#ifdef	__cplusplus
}
#endif

#endif	/* ENG_T4_ERR_H */
