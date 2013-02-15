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
 * This file implements the SHA-256 message digest operations.
 */

#include <openssl/opensslconf.h>

#if !defined(OPENSSL_NO_HW) && !defined(OPENSSL_NO_HW_MD_T4)
#if !defined(OPENSSL_NO_SHA) && !defined(OPENSSL_NO_SHA256)
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <openssl/engine.h>
/*
 * Solaris sys/sha2.h and OpenSSL openssl/sha.h both define
 * SHA256_CTX, SHA512_CTX, SHA256, SHA384, and SHA512.
 * For SHA2, OpenSSL SHA256_CTX has extra num and md_len fields at
 * the end and Solaris SHA2_CTX has an extra algotype field at the beginning.
 */
#include "eng_t4_sha2_asm.h"

#if (defined(sun4v) || defined(__sparcv9) || defined(__sparcv8plus) || \
	defined(__sparcv8)) && !defined(OPENSSL_NO_ASM)
#define	COMPILE_HW_T4
#endif

#ifdef	COMPILE_HW_T4

/* Formal declaration for functions in EVP_MD structure */
static int t4_digest_init_sha256(EVP_MD_CTX *ctx);
static int t4_digest_init_sha224(EVP_MD_CTX *ctx);
static int t4_digest_update_sha256(EVP_MD_CTX *ctx, const void *data,
    size_t len);
static int t4_digest_final_sha256(EVP_MD_CTX *ctx, unsigned char *md);
static int t4_digest_copy_sha256(EVP_MD_CTX *to, const EVP_MD_CTX *from);


/*
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
const EVP_MD t4_sha256 = {
	NID_sha256, NID_sha256WithRSAEncryption, SHA256_DIGEST_LENGTH,
	EVP_MD_FLAG_PKEY_METHOD_SIGNATURE | EVP_MD_FLAG_DIGALGID_ABSENT,
	t4_digest_init_sha256, t4_digest_update_sha256, t4_digest_final_sha256,
	t4_digest_copy_sha256, NULL,
	EVP_PKEY_RSA_method, SHA256_CBLOCK,
	sizeof (T4_SHA256_CTX), NULL
	};
/* SHA-224 uses the same context, cblock size, & update function as SHA-256: */
const EVP_MD t4_sha224 = {
	NID_sha224, NID_sha224WithRSAEncryption, SHA224_DIGEST_LENGTH,
	EVP_MD_FLAG_PKEY_METHOD_SIGNATURE | EVP_MD_FLAG_DIGALGID_ABSENT,
	t4_digest_init_sha224, t4_digest_update_sha256, t4_digest_final_sha256,
	t4_digest_copy_sha256, NULL,
	EVP_PKEY_RSA_method, SHA256_CBLOCK,
	sizeof (T4_SHA256_CTX), NULL
	};

/* These functions are defined in md32_common.h: */
static int t4_sha256_update(T4_SHA256_CTX *c, const void *data_, size_t len);
static void t4_sha256_transform(T4_SHA256_CTX *c, const unsigned char *data);
static int t4_sha256_final(unsigned char *md, T4_SHA256_CTX *c);
#pragma inline(t4_sha256_update, t4_sha256_transform, t4_sha256_final)

#define	DATA_ORDER_IS_BIG_ENDIAN
/* HASH_LONG/SHA_LONG is unsigned int (32 bits): */
#define	HASH_LONG			SHA_LONG
#define	HASH_CTX			T4_SHA256_CTX
#define	HASH_CBLOCK			SHA_CBLOCK
#define	HASH_UPDATE			t4_sha256_update
#define	HASH_TRANSFORM			t4_sha256_transform
#define	HASH_FINAL			t4_sha256_final
#define	HASH_BLOCK_DATA_ORDER		t4_sha256_multiblock
#define	HASH_MAKE_STRING(c, s) 						\
	do {								\
		unsigned int ll, nn;					\
		switch ((c)->md_len) {					\
		case SHA256_DIGEST_LENGTH:				\
			for (nn = 0; nn < SHA256_DIGEST_LENGTH / 4; nn++) { \
				ll = (c)->h[nn]; HOST_l2c(ll, (s)); }	\
			break;						\
		case SHA224_DIGEST_LENGTH:				\
			for (nn = 0; nn < SHA224_DIGEST_LENGTH / 4; nn++) { \
				ll = (c)->h[nn]; HOST_l2c(ll, (s)); }	\
			break;						\
		default:						\
			if ((c)->md_len > SHA256_DIGEST_LENGTH)		\
			    return (0);					\
			for (nn = 0; nn < (c)->md_len / 4; nn++) {	\
				ll = (c)->h[nn]; HOST_l2c(ll, (s)); }	\
			break;						\
		}							\
	} while (0)

/* This defines HASH_UPDATE, HASH_TRANSFORM, HASH_FINAL functions: */
#include "md32_common.h"


/*
 * SHA256 functions (part of FIPS 180-2 Secure Hash Standard)
 */

static int
t4_digest_init_sha256(EVP_MD_CTX *ctx)
{
	T4_SHA256_CTX	*c = (T4_SHA256_CTX *)ctx->md_data;

	/* Optimization: don't call memset(c, 0,...) or initialize c->data[] */
	c->Nl = c->Nh = c->num = 0;
	c->h[0] = 0x6a09e667U;
	c->h[1] = 0xbb67ae85U;
	c->h[2] = 0x3c6ef372U;
	c->h[3] = 0xa54ff53aU;
	c->h[4] = 0x510e527fU;
	c->h[5] = 0x9b05688cU;
	c->h[6] = 0x1f83d9abU;
	c->h[7] = 0x5be0cd19U;
	c->md_len = SHA256_DIGEST_LENGTH;
	return (1);
}


static int
t4_digest_init_sha224(EVP_MD_CTX *ctx)
{
	T4_SHA256_CTX	*c = (T4_SHA256_CTX *)ctx->md_data;

	/* Optimization: don't call memset(c, 0,...) or initialize c->data[] */
	c->Nl = c->Nh = c->num = 0;
	c->h[0] = 0xc1059ed8UL;
	c->h[1] = 0x367cd507UL;
	c->h[2] = 0x3070dd17UL;
	c->h[3] = 0xf70e5939UL;
	c->h[4] = 0xffc00b31UL;
	c->h[5] = 0x68581511UL;
	c->h[6] = 0x64f98fa7UL;
	c->h[7] = 0xbefa4fa4UL;
	c->md_len = SHA224_DIGEST_LENGTH;
	return (1);
}

/* Continue SHA256 digest operation, using message block to update context. */
static int
t4_digest_update_sha256(EVP_MD_CTX *ctx, const void *data, size_t len)
{
	T4_SHA256_CTX	*sha256_ctx = (T4_SHA256_CTX *)ctx->md_data;

	return (t4_sha256_update((T4_SHA256_CTX *)ctx->md_data, data, len));
}

/* End SHA256 digest operation, finalizing message digest and zeroing context */
static int
t4_digest_final_sha256(EVP_MD_CTX *ctx, unsigned char *md)
{
	T4_SHA256_CTX	*sha256_ctx = (T4_SHA256_CTX *)ctx->md_data;

	return (t4_sha256_final(md, (T4_SHA256_CTX *)ctx->md_data));
}

/* Required for Engine API */
static int
t4_digest_copy_sha256(EVP_MD_CTX *to, const EVP_MD_CTX *from)
{
	if ((to->md_data != NULL) && (from->md_data != NULL)) {
		(void) memcpy(to->md_data, from->md_data,
		    sizeof (T4_SHA256_CTX));
	}
	return (1);
}

#endif	/* COMPILE_HW_T4 */
#endif	/* !OPENSSL_NO_SHA && !OPENSSL_NO_SHA256 */
#endif	/* !OPENSSL_NO_HW && !OPENSSL_NO_HW_MD_T4 */
