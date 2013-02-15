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
 * This file implements the SHA-512 message digest operations.
 */

#include <openssl/opensslconf.h>

#if !defined(OPENSSL_NO_HW) && !defined(OPENSSL_NO_HW_MD_T4)
#if !defined(OPENSSL_NO_SHA) && !defined(OPENSSL_NO_SHA512)
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <openssl/engine.h>
/*
 * Solaris sys/sha2.h and OpenSSL openssl/sha.h both define
 * SHA512_CTX, SHA512_CTX, SHA512, SHA384, and SHA512.
 * For SHA2, OpenSSL SHA512_CTX has extra num and md_len fields at
 * the end and Solaris SHA2_CTX has an extra algotype field at the beginning.
 */
#include "eng_t4_sha2_asm.h"

#if (defined(sun4v) || defined(__sparcv9) || defined(__sparcv8plus) || \
	defined(__sparcv8)) && !defined(OPENSSL_NO_ASM)
#define	COMPILE_HW_T4
#endif

#ifdef	COMPILE_HW_T4

/* Formal declaration for functions in EVP_MD structure */
static int t4_digest_init_sha384(EVP_MD_CTX *ctx);
static int t4_digest_init_sha512(EVP_MD_CTX *ctx);
static int t4_digest_update_sha512(EVP_MD_CTX *ctx, const void *data,
    size_t len);
static int t4_digest_final_sha512(EVP_MD_CTX *ctx, unsigned char *md);
static int t4_digest_copy_sha512(EVP_MD_CTX *to, const EVP_MD_CTX *from);


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

const EVP_MD t4_sha512 = {
	NID_sha512, NID_sha512WithRSAEncryption, SHA512_DIGEST_LENGTH,
	EVP_MD_FLAG_PKEY_METHOD_SIGNATURE | EVP_MD_FLAG_DIGALGID_ABSENT,
	t4_digest_init_sha512, t4_digest_update_sha512, t4_digest_final_sha512,
	t4_digest_copy_sha512, NULL,
	EVP_PKEY_RSA_method, SHA512_CBLOCK,
	sizeof (T4_SHA512_CTX), NULL
	};
/* SHA-384 uses the same context, cblock size, & update function as SHA-512: */
const EVP_MD t4_sha384 = {
	NID_sha384, NID_sha384WithRSAEncryption, SHA384_DIGEST_LENGTH,
	EVP_MD_FLAG_PKEY_METHOD_SIGNATURE | EVP_MD_FLAG_DIGALGID_ABSENT,
	t4_digest_init_sha384, t4_digest_update_sha512, t4_digest_final_sha512,
	t4_digest_copy_sha512, NULL,
	EVP_PKEY_RSA_method, SHA512_CBLOCK,
	sizeof (T4_SHA512_CTX), NULL
	};


/*
 * SHA512 functions (part of FIPS 180-2 Secure Hash Standard)
 */

static int
t4_digest_init_sha512(EVP_MD_CTX *ctx)
{
	T4_SHA512_CTX	*c = (T4_SHA512_CTX *)ctx->md_data;

	c->Nl = c->Nh = c->num = 0;
	c->h[0] = 0x6a09e667f3bcc908ULL;
	c->h[1] = 0xbb67ae8584caa73bULL;
	c->h[2] = 0x3c6ef372fe94f82bULL;
	c->h[3] = 0xa54ff53a5f1d36f1ULL;
	c->h[4] = 0x510e527fade682d1ULL;
	c->h[5] = 0x9b05688c2b3e6c1fULL;
	c->h[6] = 0x1f83d9abfb41bd6bULL;
	c->h[7] = 0x5be0cd19137e2179ULL;
	c->md_len = SHA512_DIGEST_LENGTH;

	return (1);
}


static int
t4_digest_init_sha384(EVP_MD_CTX *ctx)
{
	T4_SHA512_CTX	*c = (T4_SHA512_CTX *)ctx->md_data;

	c->Nl = c->Nh = c->num = 0;
	c->h[0] = 0xcbbb9d5dc1059ed8ULL;
	c->h[1] = 0x629a292a367cd507ULL;
	c->h[2] = 0x9159015a3070dd17ULL;
	c->h[3] = 0x152fecd8f70e5939ULL;
	c->h[4] = 0x67332667ffc00b31ULL;
	c->h[5] = 0x8eb44a8768581511ULL;
	c->h[6] = 0xdb0c2e0d64f98fa7ULL;
	c->h[7] = 0x47b5481dbefa4fa4ULL;
	c->md_len = SHA384_DIGEST_LENGTH;

	return (1);
}


/*
 * Continue SHA512 or SHA384 digest operation, using the message block to
 * update context.
 * Modified from SHA512_Update() in OpenSSL crypto/sha/sha512.c.
 */
static int
t4_digest_update_sha512(EVP_MD_CTX *ctx, const void *_data, size_t len)
{
	T4_SHA512_CTX	*c = (T4_SHA512_CTX *)ctx->md_data;
	SHA_LONG64	l;
	unsigned char	*p = c->u.p;
	const unsigned char *data = (const unsigned char *)_data;

	if (len == 0)
		return (1);

	l = (c->Nl + (((SHA_LONG64)len) << 3)) & 0xffffffffffffffffULL;
	if (l < c->Nl)
		c->Nh++;
	if (sizeof (len) >= 8) {
		c->Nh += (((SHA_LONG64)len) >> 61);
	}
	c->Nl = l;

	if (c->num != 0) {
		size_t n = sizeof (c->u) - c->num;

		if (len < n) {
			memcpy(p + c->num, data, len);
			c->num += (unsigned int)len;
			return (1);
		} else	{
			memcpy(p + c->num, data, n);
			c->num = 0;
			len -= n;
			data += n;
			t4_sha512_multiblock(c, p, 1);
		}
	}

	if (len >= sizeof (c->u)) {
		if ((size_t)data % sizeof (c->u.d[0]) != 0) {
			/* Align unaligned data one block-at-a-time */
			while (len >= sizeof (c->u)) {
				memcpy(p, data, sizeof (c->u));
				t4_sha512_multiblock(c, p, 1);
				len  -= sizeof (c->u);
				data += sizeof (c->u);
			}
		} else {
			t4_sha512_multiblock(c, data, len / sizeof (c->u));
			data += len;
			len  %= sizeof (c->u);
			data -= len;
		}
	}

	if (len != 0) {
		memcpy(p, data, len);
		c->num = (int)len;
	}

	return (1);
}


/*
 * End SHA-512 or SHA-384 digest operation, finalizing message digest and
 * zeroing context.
 * Modified from SHA512_Final() in OpenSSL crypto/sha/sha512.c.
 */
static int
t4_digest_final_sha512(EVP_MD_CTX *ctx, unsigned char *md)
{
	T4_SHA512_CTX	*c = (T4_SHA512_CTX *)ctx->md_data;
	unsigned char	*p = (unsigned char *)c->u.p;
	size_t		n = c->num;

	p[n] = 0x80;	/* There always is a room for one */
	n++;
	if (n > (sizeof (c->u) - 16)) {
		memset(p + n, 0, sizeof (c->u) - n);
		n = 0;
		t4_sha512_multiblock(c, p, 1);
	}

	memset(p+n, 0, sizeof (c->u) - 16 - n);
	c->u.d[SHA_LBLOCK - 2] = c->Nh;
	c->u.d[SHA_LBLOCK - 1] = c->Nl;

	t4_sha512_multiblock(c, p, 1);

	if (md == 0)
		return (0);

	switch (c->md_len) {
		/* Let compiler decide if it's appropriate to unroll... */
		case SHA384_DIGEST_LENGTH:
			for (n = 0; n < SHA384_DIGEST_LENGTH / 8; n++) {
				SHA_LONG64 t = c->h[n];

				*(md++)	= (unsigned char)(t >> 56);
				*(md++)	= (unsigned char)(t >> 48);
				*(md++)	= (unsigned char)(t >> 40);
				*(md++)	= (unsigned char)(t >> 32);
				*(md++)	= (unsigned char)(t >> 24);
				*(md++)	= (unsigned char)(t >> 16);
				*(md++)	= (unsigned char)(t >> 8);
				*(md++)	= (unsigned char)(t);
			}
			break;
		case SHA512_DIGEST_LENGTH:
			for (n = 0; n < SHA512_DIGEST_LENGTH / 8; n++) {
				SHA_LONG64 t = c->h[n];

				*(md++)	= (unsigned char)(t >> 56);
				*(md++)	= (unsigned char)(t >> 48);
				*(md++)	= (unsigned char)(t >> 40);
				*(md++)	= (unsigned char)(t >> 32);
				*(md++)	= (unsigned char)(t >> 24);
				*(md++)	= (unsigned char)(t >> 16);
				*(md++)	= (unsigned char)(t >> 8);
				*(md++)	= (unsigned char)(t);
			}
			break;
		/* ... as well as make sure md_len is not abused. */
		default:
			return (0);
	}

	return (1);
}


/* Required for Engine API */
static int
t4_digest_copy_sha512(EVP_MD_CTX *to, const EVP_MD_CTX *from)
{
	if ((to->md_data != NULL) && (from->md_data != NULL)) {
		(void) memcpy(to->md_data, from->md_data,
		    sizeof (T4_SHA512_CTX));
	}
	return (1);
}

#endif	/* COMPILE_HW_T4 */
#endif	/* !OPENSSL_NO_SHA && !OPENSSL_NO_SHA512 */
#endif	/* !OPENSSL_NO_HW && !OPENSSL_NO_HW_MD_T4 */
