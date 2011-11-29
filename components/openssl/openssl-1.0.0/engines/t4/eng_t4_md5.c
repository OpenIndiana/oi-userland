/*
 * This product includes cryptographic software developed by the OpenSSL
 * Project for use in the OpenSSL Toolkit (http://www.openssl.org/). This
 * product includes cryptographic software written by Eric Young
 * (eay@cryptsoft.com).
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

/*
 * This engine supports SPARC microprocessors that provide AES and other
 * cipher and hash instructions, such as the T4 microprocessor.
 *
 * This file implements the MD5 message digest operations.
 */

#include <openssl/opensslconf.h>

#if !defined(OPENSSL_NO_HW) && !defined(OPENSSL_NO_HW_MD_T4)
#ifndef	OPENSSL_NO_MD5

#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <openssl/aes.h>
#include <openssl/engine.h>
/*
 * Solaris sys/md5.h and OpenSSL openssl/md5.h both define MD5_CTX.
 * The OpenSSL MD5_CTX has an extra "num" field at the end.
 */
#include <openssl/md5.h>

#if (defined(sun4v) || defined(__sparcv9) || defined(__sparcv8plus) || \
	defined(__sparcv8)) && !defined(OPENSSL_NO_ASM)
#define	COMPILE_HW_T4
#endif

#ifdef	COMPILE_HW_T4

/* Assembly language function; replaces C function md5_block_data_order(): */
extern void t4_md5_multiblock(MD5_CTX *ctx, const uint8_t *input,
    unsigned int input_length_in_blocks);

/* Formal declaration for functions in EVP_MD structure */
int t4_digest_init_md5(EVP_MD_CTX *ctx);
int t4_digest_update_md5(EVP_MD_CTX *ctx, const void *data, size_t count);
int t4_digest_final_md5(EVP_MD_CTX *ctx, unsigned char *md);
int t4_digest_copy_md5(EVP_MD_CTX *to, const EVP_MD_CTX *from);


/*
 * MD5 Message Digests
 *
 * OpenSSL's libcrypto EVP stuff. This is how this engine gets wired to EVP.
 * EVP_MD is defined in evp.h.  To maintain binary compatibility the
 * definition cannot be modified.
 * Stuff specific to the t4 engine is kept in t4_cipher_ctx_t, which is
 * pointed to by the last field, app_data.
 *
 * Fields: type, pkey_type, md_size, flags,
 *	init(), update(), final(),
 *	copy(), cleanup(), sign(), verify(),
 *	required_pkey_type, block_size, ctx_size, md5_ctrl()
 */
const EVP_MD t4_md5 = {
	NID_md5, NID_md5WithRSAEncryption, MD5_DIGEST_LENGTH,
	0,
	t4_digest_init_md5, t4_digest_update_md5, t4_digest_final_md5,
	t4_digest_copy_md5, NULL,
	EVP_PKEY_RSA_method, MD5_CBLOCK,
	sizeof (MD5_CTX), NULL
	};

/* These functions are implemented in md32_common.h: */
static int t4_md5_update(MD5_CTX *c, const void *data_, size_t len);
static void t4_md5_transform(MD5_CTX *c, const unsigned char *data);
static int t4_md5_final(unsigned char *md, MD5_CTX *c);
#pragma inline(t4_md5_update, t4_md5_transform, t4_md5_final)

#define	DATA_ORDER_IS_LITTLE_ENDIAN
/* HASH_LONG/MD5_LONG is a 32-bit unsigned: */
#define	HASH_LONG		MD5_LONG
#define	HASH_CTX		MD5_CTX
#define	HASH_CBLOCK		MD5_CBLOCK
#define	HASH_UPDATE		t4_md5_update
#define	HASH_TRANSFORM		t4_md5_transform
#define	HASH_FINAL		t4_md5_final
#define	HASH_BLOCK_DATA_ORDER	t4_md5_multiblock
/* HOST_l2c_t4: Hash is already byte-swapped as Little Endian for SPARC T4: */
#define	HOST_l2c_t4(l, c)	(*((unsigned int *)(c)) = (l), (c) += 4, l)
#define	HASH_MAKE_STRING(c, s)	do {	\
		unsigned int ll;		\
		ll = (c)->A; HOST_l2c_t4(ll, (s));	\
		ll = (c)->B; HOST_l2c_t4(ll, (s));	\
		ll = (c)->C; HOST_l2c_t4(ll, (s));	\
		ll = (c)->D; HOST_l2c_t4(ll, (s));	\
	} while (0)

/* This defines HASH_UPDATE, HASH_TRANSFORM, HASH_FINAL functions: */
#include "md32_common.h"


/*
 * MD5 functions (RFC 1321 The MD5 Message-Digest Algorithm)
 */

int
t4_digest_init_md5(EVP_MD_CTX *ctx)
{
	MD5_CTX	*c = (MD5_CTX *)ctx->md_data;

	/* Optimization: don't call memset(c, 0,...) or initialize c->data[] */
	c->Nl = c->Nh = c->num = 0;

	/* Big Endian for T4 */
	c->A = 0x01234567U;
	c->B = 0x89abcdefU;
	c->C = 0xfedcba98U;
	c->D = 0x76543210U;

	return (1);
}

/*
 * Continue MD5 digest operation, using the message block to update context.
 * MD5 crunches in 64-byte blocks.
 */
int
t4_digest_update_md5(EVP_MD_CTX *ctx, const void *data, size_t len)
{
	return (t4_md5_update((MD5_CTX *)ctx->md_data, data, len));
}

/* End MD5 digest operation, finalizing message digest and zeroing context. */
int
t4_digest_final_md5(EVP_MD_CTX *ctx, unsigned char *md)
{
	return (t4_md5_final(md, (MD5_CTX *)ctx->md_data));
}

/* Required for Engine API */
int
t4_digest_copy_md5(EVP_MD_CTX *to, const EVP_MD_CTX *from)
{
	if ((to->md_data != NULL) && (from->md_data != NULL)) {
		(void) memcpy(to->md_data, from->md_data, sizeof (MD5_CTX));
	}
	return (1);
}

#endif	/* COMPILE_HW_T4 */
#endif	/* !OPENSSL_NO_MD5 */
#endif	/* !OPENSSL_NO_HW && !OPENSSL_NO_HW_MD_T4 */
