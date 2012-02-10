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

/*
 * This engine supports SPARC microprocessors that provide AES and other
 * cipher and hash instructions, such as the T4 microprocessor.
 */

#include <openssl/opensslconf.h>

#if !defined(OPENSSL_NO_HW) && !defined(OPENSSL_NO_HW_AES_T4) && \
	!defined(OPENSSL_NO_AES)
#include <sys/types.h>
#include <sys/auxv.h>	/* getisax() */
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>
#include <openssl/aes.h>
#include <openssl/engine.h>
#include "eng_t4_aes_asm.h"

#define	T4_LIB_NAME "SPARC T4 engine"
#include "eng_t4_err.c"

/* Copied from Solaris aes_impl.h */
#ifndef	MAX_AES_NR
#define	MAX_AES_NR		14 /* Maximum number of rounds */
#endif
#ifndef	MAX_AES_NB
#define	MAX_AES_NB		4  /* Number of columns comprising a state */
#endif

/* Index for the supported ciphers */
typedef enum {
	T4_AES_128_CBC,
	T4_AES_192_CBC,
	T4_AES_256_CBC,
#ifndef	SOLARIS_NO_AES_CFB128
	T4_AES_128_CFB128,
	T4_AES_192_CFB128,
	T4_AES_256_CFB128,
#endif	/* !SOLARIS_NO_AES_CFB128 */
#ifndef	SOLARIS_NO_AES_CTR
	T4_AES_128_CTR,
	T4_AES_192_CTR,
	T4_AES_256_CTR,
#endif
	T4_AES_128_ECB,
	T4_AES_192_ECB,
	T4_AES_256_ECB,
	T4_CIPHER_MAX
} t4_cipher_id;

/* T4 cipher context; must be 8-byte aligned (last field must be uint64_t)  */
typedef struct t4_cipher_ctx {
	t4_cipher_id	index;
	uint64_t	*iv;
	uint64_t	aligned_iv_buffer[2]; /* use if original IV unaligned */
	/* Encryption and decryption key schedule are the same: */
	uint64_t	t4_ks[((MAX_AES_NR) + 1) * (MAX_AES_NB)];
} t4_cipher_ctx_t;

typedef struct t4_cipher {
	t4_cipher_id	id;
	int		nid;
	int		iv_len;
	int		min_key_len;
	int		max_key_len;
	unsigned long	flags;
} t4_cipher_t;

/* Constants used when creating the ENGINE */
static const char *ENGINE_T4_ID = "t4";
static const char *ENGINE_T4_NAME = "SPARC T4 engine support";
static const char *ENGINE_NO_T4_NAME = "SPARC T4 engine support (no T4)";


#if (defined(sun4v) || defined(__sparcv9) || defined(__sparcv8plus) || \
	defined(__sparcv8)) && !defined(OPENSSL_NO_ASM)
#define	COMPILE_HW_T4
static int t4_bind_helper(ENGINE *e, const char *id);
#pragma inline(t4_bind_helper)
#endif

/*
 * This makes the engine "built-in" with OpenSSL.
 * On non-T4 CPUs this just returns.
 * Called by ENGINE_load_builtin_engines().
 */
void
ENGINE_load_t4(void)
{
#ifdef	COMPILE_HW_T4
	ENGINE *toadd = ENGINE_new();
	if (toadd != NULL) {
		if (t4_bind_helper(toadd, ENGINE_T4_ID) != 0) {
			(void) ENGINE_add(toadd);
			(void) ENGINE_free(toadd);
			ERR_clear_error();
		} else {
			(void) ENGINE_free(toadd);
		}
	}
#endif
}


#ifdef	COMPILE_HW_T4
static int t4_bind(ENGINE *e);
#ifndef	DYNAMIC_ENGINE
#pragma inline(t4_bind)
#endif
static t4_cipher_id get_cipher_index_by_nid(int nid);
#pragma inline(get_cipher_index_by_nid)
static void t4_instructions_present(_Bool *aes_present, _Bool *des_present,
    _Bool *digest_present, _Bool *montmul_present);
#pragma inline(t4_instructions_present)

/* Digest registration function. Called by ENGINE_set_ciphers() */
int t4_get_all_digests(ENGINE *e, const EVP_MD **digest,
    const int **nids, int nid);

/* RSA_METHOD structure used by ENGINE_set_RSA() */
extern RSA_METHOD *t4_RSA(void);

/* DH_METHOD structure used by ENGINE_set_DH() */
extern DH_METHOD *t4_DH(void);

/* DSA_METHOD structure used by ENGINE_set_DSA() */
extern DSA_METHOD *t4_DSA(void);

#ifndef	SOLARIS_NO_AES_CTR
/*
 * NIDs for AES counter mode that will be defined during the engine
 * initialization (because OpenSSL doesn't support CTR mode).
 */
static int NID_t4_aes_128_ctr = NID_undef;
static int NID_t4_aes_192_ctr = NID_undef;
static int NID_t4_aes_256_ctr = NID_undef;

static int t4_add_NID(char *sn, char *ln);
static int t4_add_aes_ctr_NIDs(void);
#pragma inline(t4_add_aes_ctr_NIDs)
static void t4_free_aes_ctr_NIDs(void);
#define	T4_FREE_AES_CTR_NIDS	t4_free_aes_ctr_NIDs()
#else
#define	T4_FREE_AES_CTR_NIDS
#endif	/* !SOLARIS_NO_AES_CTR */

/* Static variables */
/* This can't be const as NID*ctr is inserted when the engine is initialized */
static int t4_cipher_nids[] = {
	NID_aes_128_cbc, NID_aes_192_cbc, NID_aes_256_cbc,
#ifndef	SOLARIS_NO_AES_CFB128
	NID_aes_128_cfb128, NID_aes_192_cfb128, NID_aes_256_cfb128,
#endif
#ifndef	SOLARIS_NO_AES_CTR
	/* NID_t4_aes_128_ctr, NID_t4_aes_192, NID_t4_aes_256 */
	NID_undef, NID_undef, NID_undef,
#endif
	NID_aes_128_ecb, NID_aes_192_ecb, NID_aes_256_ecb,
#ifndef	OPENSSL_NO_DES
	/* Must be at end of list (see t4_des_cipher_count in t4_bind() */
	NID_des_cbc, NID_des_ede3_cbc, NID_des_ecb, NID_des_ede3_ecb,
#endif
};
static const int t4_des_cipher_count = 4;
static int t4_cipher_count =
	(sizeof (t4_cipher_nids) / sizeof (t4_cipher_nids[0]));

/*
 * Cipher Table for all supported symmetric ciphers.
 * Must be in same order as t4_cipher_id.
 */
static t4_cipher_t t4_cipher_table[] = {
	/* ID			NID			IV min- max-key flags */
	{T4_AES_128_CBC,	NID_aes_128_cbc,	16, 16, 16, 0},
	{T4_AES_192_CBC,	NID_aes_192_cbc,	16, 24, 24, 0},
	{T4_AES_256_CBC,	NID_aes_256_cbc,	16, 32, 32, 0},
#ifndef	SOLARIS_NO_AES_CFB128
	{T4_AES_128_CFB128,	NID_aes_128_cfb128,	16, 16, 16,
							EVP_CIPH_NO_PADDING},
	{T4_AES_192_CFB128,	NID_aes_192_cfb128,	16, 24, 24,
							EVP_CIPH_NO_PADDING},
	{T4_AES_256_CFB128,	NID_aes_256_cfb128,	16, 32, 32,
							EVP_CIPH_NO_PADDING},
#endif
#ifndef	SOLARIS_NO_AES_CTR
	/* We don't know the correct NIDs until the engine is initialized */
	{T4_AES_128_CTR,	NID_undef,		16, 16, 16,
							EVP_CIPH_NO_PADDING},
	{T4_AES_192_CTR,	NID_undef,		16, 24, 24,
							EVP_CIPH_NO_PADDING},
	{T4_AES_256_CTR,	NID_undef,		16, 32, 32,
							EVP_CIPH_NO_PADDING},
#endif
	{T4_AES_128_ECB,	NID_aes_128_ecb,	0, 16, 16, 0},
	{T4_AES_192_ECB,	NID_aes_192_ecb,	0, 24, 24, 0},
	{T4_AES_256_ECB,	NID_aes_256_ecb,	0, 32, 32, 0},
};


/* Formal declaration for functions in EVP_CIPHER structure */
static int t4_cipher_init_aes(EVP_CIPHER_CTX *ctx, const unsigned char *key,
    const unsigned char *iv, int enc);

static int t4_cipher_do_aes_128_cbc(EVP_CIPHER_CTX *ctx, unsigned char *out,
    const unsigned char *in, size_t inl);
static int t4_cipher_do_aes_192_cbc(EVP_CIPHER_CTX *ctx, unsigned char *out,
    const unsigned char *in, size_t inl);
static int t4_cipher_do_aes_256_cbc(EVP_CIPHER_CTX *ctx, unsigned char *out,
    const unsigned char *in, size_t inl);
#ifndef	SOLARIS_NO_AES_CFB128
static int t4_cipher_do_aes_128_cfb128(EVP_CIPHER_CTX *ctx, unsigned char *out,
    const unsigned char *in, size_t inl);
static int t4_cipher_do_aes_192_cfb128(EVP_CIPHER_CTX *ctx, unsigned char *out,
    const unsigned char *in, size_t inl);
static int t4_cipher_do_aes_256_cfb128(EVP_CIPHER_CTX *ctx, unsigned char *out,
    const unsigned char *in, size_t inl);
#endif
#ifndef	SOLARIS_NO_AES_CTR
static int t4_cipher_do_aes_128_ctr(EVP_CIPHER_CTX *ctx, unsigned char *out,
    const unsigned char *in, size_t inl);
static int t4_cipher_do_aes_192_ctr(EVP_CIPHER_CTX *ctx, unsigned char *out,
    const unsigned char *in, size_t inl);
static int t4_cipher_do_aes_256_ctr(EVP_CIPHER_CTX *ctx, unsigned char *out,
    const unsigned char *in, size_t inl);
#endif	/* !SOLARIS_NO_AES_CTR */
static int t4_cipher_do_aes_128_ecb(EVP_CIPHER_CTX *ctx, unsigned char *out,
    const unsigned char *in, size_t inl);
static int t4_cipher_do_aes_192_ecb(EVP_CIPHER_CTX *ctx, unsigned char *out,
    const unsigned char *in, size_t inl);
static int t4_cipher_do_aes_256_ecb(EVP_CIPHER_CTX *ctx, unsigned char *out,
    const unsigned char *in, size_t inl);


/*
 * Cipher Algorithms
 *
 * OpenSSL's libcrypto EVP stuff. This is how this engine gets wired to EVP.
 * EVP_CIPHER is defined in evp.h.  To maintain binary compatibility the
 * definition cannot be modified.
 * Stuff specific to the t4 engine is kept in t4_cipher_ctx_t, which is
 * pointed to by cipher_data or md_data
 *
 * Fields: nid, block_size, key_len, iv_len, flags,
 *	init(), do_cipher(), cleanup(),
 *	ctx_size,
 *	set_asn1_parameters(), get_asn1_parameters(), ctrl(), app_data
 */

static const EVP_CIPHER t4_aes_128_cbc = {
	NID_aes_128_cbc,
	16, 16, 16,
	EVP_CIPH_CBC_MODE,
	t4_cipher_init_aes, t4_cipher_do_aes_128_cbc, NULL,
	sizeof (t4_cipher_ctx_t),
	EVP_CIPHER_set_asn1_iv, EVP_CIPHER_get_asn1_iv,
	NULL, NULL
};
static const EVP_CIPHER t4_aes_192_cbc = {
	NID_aes_192_cbc,
	16, 24, 16,
	EVP_CIPH_CBC_MODE,
	t4_cipher_init_aes, t4_cipher_do_aes_192_cbc, NULL,
	sizeof (t4_cipher_ctx_t),
	EVP_CIPHER_set_asn1_iv, EVP_CIPHER_get_asn1_iv,
	NULL, NULL
};
static const EVP_CIPHER t4_aes_256_cbc = {
	NID_aes_256_cbc,
	16, 32, 16,
	EVP_CIPH_CBC_MODE,
	t4_cipher_init_aes, t4_cipher_do_aes_256_cbc, NULL,
	sizeof (t4_cipher_ctx_t),
	EVP_CIPHER_set_asn1_iv, EVP_CIPHER_get_asn1_iv,
	NULL, NULL
};

#ifndef	SOLARIS_NO_AES_CFB128
static const EVP_CIPHER t4_aes_128_cfb128 = {
	NID_aes_128_cfb128,
	16, 16, 16,
	EVP_CIPH_CFB_MODE,
	t4_cipher_init_aes, t4_cipher_do_aes_128_cfb128, NULL,
	sizeof (t4_cipher_ctx_t),
	EVP_CIPHER_set_asn1_iv, EVP_CIPHER_get_asn1_iv,
	NULL, NULL
};
static const EVP_CIPHER t4_aes_192_cfb128 = {
	NID_aes_192_cfb128,
	16, 24, 16,
	EVP_CIPH_CFB_MODE,
	t4_cipher_init_aes, t4_cipher_do_aes_192_cfb128, NULL,
	sizeof (t4_cipher_ctx_t),
	EVP_CIPHER_set_asn1_iv, EVP_CIPHER_get_asn1_iv,
	NULL, NULL
};
static const EVP_CIPHER t4_aes_256_cfb128 = {
	NID_aes_256_cfb128,
	16, 32, 16,
	EVP_CIPH_CFB_MODE,
	t4_cipher_init_aes, t4_cipher_do_aes_256_cfb128, NULL,
	sizeof (t4_cipher_ctx_t),
	EVP_CIPHER_set_asn1_iv, EVP_CIPHER_get_asn1_iv,
	NULL, NULL
};
#endif	/* !SOLARIS_NO_AES_CFB128 */

#ifndef	SOLARIS_NO_AES_CTR
/*
 * Counter mode is not defined in OpenSSL.
 * NID_undef's will be changed to AES counter mode NIDs as soon as they are
 * created in t4_add_aes_ctr_NIDs() when the engine is initialized.
 * Note that the need to change these structures during initialization is the
 * reason why we don't define them with the const keyword.
 */
static EVP_CIPHER t4_aes_128_ctr = {
	NID_undef,
	16, 16, 16,
	EVP_CIPH_CBC_MODE,
	t4_cipher_init_aes, t4_cipher_do_aes_128_ctr, NULL,
	sizeof (t4_cipher_ctx_t),
	EVP_CIPHER_set_asn1_iv, EVP_CIPHER_get_asn1_iv,
	NULL, NULL
};
static EVP_CIPHER t4_aes_192_ctr = {
	NID_undef,
	16, 24, 16,
	EVP_CIPH_CBC_MODE,
	t4_cipher_init_aes, t4_cipher_do_aes_192_ctr, NULL,
	sizeof (t4_cipher_ctx_t),
	EVP_CIPHER_set_asn1_iv, EVP_CIPHER_get_asn1_iv,
	NULL, NULL
};
static EVP_CIPHER t4_aes_256_ctr = {
	NID_undef,
	16, 32, 16,
	EVP_CIPH_CBC_MODE,
	t4_cipher_init_aes, t4_cipher_do_aes_256_ctr, NULL,
	sizeof (t4_cipher_ctx_t),
	EVP_CIPHER_set_asn1_iv, EVP_CIPHER_get_asn1_iv,
	NULL, NULL
};
#endif	/* !SOLARIS_NO_AES_CTR */

/*
 * ECB modes don't use an Initial Vector, so that's why set_asn1_parameters,
 * get_asn1_parameters, and cleanup fields are set to NULL.
 */
static const EVP_CIPHER t4_aes_128_ecb = {
	NID_aes_128_ecb,
	16, 16, 0,
	EVP_CIPH_ECB_MODE,
	t4_cipher_init_aes, t4_cipher_do_aes_128_ecb, NULL,
	sizeof (t4_cipher_ctx_t),
	NULL, NULL, NULL, NULL
};
static const EVP_CIPHER t4_aes_192_ecb = {
	NID_aes_192_ecb,
	16, 24, 0,
	EVP_CIPH_ECB_MODE,
	t4_cipher_init_aes, t4_cipher_do_aes_192_ecb, NULL,
	sizeof (t4_cipher_ctx_t),
	NULL, NULL, NULL, NULL
};
static const EVP_CIPHER t4_aes_256_ecb = {
	NID_aes_256_ecb,
	16, 32, 0,
	EVP_CIPH_ECB_MODE,
	t4_cipher_init_aes, t4_cipher_do_aes_256_ecb, NULL,
	sizeof (t4_cipher_ctx_t),
	NULL, NULL, NULL, NULL
};

#ifndef	OPENSSL_NO_DES
extern const EVP_CIPHER t4_des_cbc;
extern const EVP_CIPHER t4_des3_cbc;
extern const EVP_CIPHER t4_des_ecb;
extern const EVP_CIPHER t4_des3_ecb;
#endif	/* OPENSSL_NO_DES */


/*
 * Message Digest variables
 */
static const int t4_digest_nids[] = {
#ifndef	OPENSSL_NO_MD5
	NID_md5,
#endif
#ifndef	OPENSSL_NO_SHA
#ifndef	OPENSSL_NO_SHA1
	NID_sha1,
#endif
#ifndef	OPENSSL_NO_SHA256
	NID_sha224,
	NID_sha256,
#endif
#ifndef	OPENSSL_NO_SHA512
	NID_sha384,
	NID_sha512,
#endif
#endif	/* !OPENSSL_NO_SHA */
};
static const int t4_digest_count =
	(sizeof (t4_digest_nids) / sizeof (t4_digest_nids[0]));

#ifndef	OPENSSL_NO_MD5
extern const EVP_MD t4_md5;
#endif
#ifndef	OPENSSL_NO_SHA
#ifndef	OPENSSL_NO_SHA1
extern const EVP_MD t4_sha1;
#endif
#ifndef	OPENSSL_NO_SHA256
extern const EVP_MD t4_sha224;
extern const EVP_MD t4_sha256;
#endif
#ifndef	OPENSSL_NO_SHA512
extern const EVP_MD t4_sha384;
extern const EVP_MD t4_sha512;
#endif
#endif	/* !OPENSSL_NO_SHA */

/*
 * Message Digest functions
 */

/*
 * Registered by the ENGINE with ENGINE_set_digests().
 * Finds out how to deal with a particular digest NID in the ENGINE.
 */
/* ARGSUSED */
int
t4_get_all_digests(ENGINE *e, const EVP_MD **digest,
    const int **nids, int nid)
{
	if (digest == NULL) { /* return a list of all supported digests */
		*nids = (t4_digest_count > 0) ? t4_digest_nids : NULL;
		return (t4_digest_count);
	}

	switch (nid) {
#ifndef	OPENSSL_NO_MD5
	case NID_md5:
		*digest = &t4_md5;
		break;
#endif
#ifndef	OPENSSL_NO_SHA
#ifndef	OPENSSL_NO_SHA1
	/*
	 * A special case. For "openssl dgst -dss1 ...",
	 * OpenSSL calls EVP_get_digestbyname() on "dss1" which ends up
	 * calling t4_get_all_digests() for NID_dsa. Internally, if an
	 * engine is not used, OpenSSL uses SHA1_Init() as expected for
	 * DSA. So, we must return t4_sha1 for NID_dsa as well. Note
	 * that this must have changed between 0.9.8 and 1.0.0 since we
	 * did not have the problem with the 0.9.8 version.
	 */
	case NID_dsa:
	case NID_sha1:
		*digest = &t4_sha1;
		break;
#endif
#ifndef	OPENSSL_NO_SHA256
	case NID_sha224:
		*digest = &t4_sha224;
		break;
	case NID_sha256:
		*digest = &t4_sha256;
		break;
#endif
#ifndef	OPENSSL_NO_SHA512
	case NID_sha384:
		*digest = &t4_sha384;
		break;
	case NID_sha512:
		*digest = &t4_sha512;
		break;
#endif
#endif	/* !OPENSSL_NO_SHA */
	default:
		/* digest not supported */
		*digest = NULL;
		return (0);
	}

	return (1);
}


/*
 * Utility Functions
 */

/*
 * Set aes_present, des_present, digest_present and montmul_present
 * to B_FALSE or B_TRUE depending on
 * whether the current SPARC processor supports AES, DES,
 * MD5/SHA1/SHA256/SHA512 and MONTMUL, respectively.
 */
static void
t4_instructions_present(_Bool *aes_present, _Bool *des_present,
    _Bool *digest_present, _Bool *montmul_present)
{
#ifdef	OPENSSL_NO_DES
#undef	AV_SPARC_DES
#define	AV_SPARC_DES	0
#endif
#ifdef	OPENSSL_NO_MD5
#undef	AV_SPARC_MD5
#define	AV_SPARC_MD5	0
#endif
#ifndef	OPENSSL_NO_SHA
#ifdef	OPENSSL_NO_SHA1
#undef	AV_SPARC_SHA1
#define	AV_SPARC_SHA1	0
#endif
#ifdef	OPENSSL_NO_SHA256
#undef	AV_SPARC_SHA256
#define	AV_SPARC_SHA256	0
#endif
#ifdef	OPENSSL_NO_SHA512
#undef	AV_SPARC_SHA512
#define	AV_SPARC_SHA512	0
#endif
#else
#undef	AV_SPARC_SHA1
#undef	AV_SPARC_SHA256
#undef	AV_SPARC_SHA512
#define	AV_SPARC_SHA1	0
#define	AV_SPARC_SHA256	0
#define	AV_SPARC_SHA512	0
#endif	/* !OPENSSL_NO_SHA */

#define	DIGEST_MASK	(AV_SPARC_MD5 | AV_SPARC_SHA1 | AV_SPARC_SHA256 | \
	AV_SPARC_SHA512)
	uint_t		ui;

	(void) getisax(&ui, 1);
	*aes_present = ((ui & AV_SPARC_AES) != 0);
	*des_present = ((ui & AV_SPARC_DES) != 0);
	*digest_present = ((ui & DIGEST_MASK) == DIGEST_MASK);
	*montmul_present = ((ui & AV_SPARC_MONT) != 0);
}


#ifndef	SOLARIS_NO_AES_CTR
/* Create a new NID when we have no OID for that mechanism */
static int
t4_add_NID(char *sn, char *ln)
{
	ASN1_OBJECT	*o;
	int		nid;

	if ((o = ASN1_OBJECT_create(OBJ_new_nid(1), (unsigned char *)"",
	    1, sn, ln)) == NULL) {
		T4err(T4_F_ADD_NID, T4_R_ASN1_OBJECT_CREATE);
		return (0);
	}

	/* Will return NID_undef on error */
	nid = OBJ_add_object(o);
	ASN1_OBJECT_free(o);

	return (nid);
}


/*
 * Create new NIDs for AES counter mode.
 * OpenSSL doesn't support them now so we have to help ourselves here.
 */
static int
t4_add_aes_ctr_NIDs(void)
{
	/* Are we already set? */
	if (NID_t4_aes_256_ctr != NID_undef)
		return (1);

	/*
	 * There are no official names for AES counter modes yet so we just
	 * follow the format of those that exist.
	 */

	/* Initialize NID_t4_aes_*_ctr and t4_cipher_table[] variables */
	if ((NID_t4_aes_128_ctr = t4_add_NID("AES-128-CTR", "aes-128-ctr")) ==
	    NID_undef)
		return (0);
	t4_cipher_table[T4_AES_128_CTR].nid =
	    t4_aes_128_ctr.nid = NID_t4_aes_128_ctr;

	if ((NID_t4_aes_192_ctr = t4_add_NID("AES-192-CTR", "aes-192-ctr")) ==
	    NID_undef)
		return (0);
	t4_cipher_table[T4_AES_192_CTR].nid =
	    t4_aes_192_ctr.nid = NID_t4_aes_192_ctr;

	if ((NID_t4_aes_256_ctr = t4_add_NID("AES-256-CTR", "aes-256-ctr")) ==
	    NID_undef)
		return (0);
	t4_cipher_table[T4_AES_256_CTR].nid =
	    t4_aes_256_ctr.nid = NID_t4_aes_256_ctr;

	/* Initialize t4_cipher_nids[] */
	for (int i = 0; i < t4_cipher_count; ++i) {
		if (t4_cipher_nids[i] == NID_undef) { /* found */
			t4_cipher_nids[i] = NID_t4_aes_128_ctr;
			t4_cipher_nids[++i] = NID_t4_aes_192_ctr;
			t4_cipher_nids[++i] = NID_t4_aes_256_ctr;
			break;
		}
	}

	return (1);
}


static void
t4_free_aes_ctr_NIDs(void)
{
	ASN1_OBJECT *o = NULL;

	/* Clear entries in t4_cipher_nids[] */
	for (int i = 0; i < t4_cipher_count; ++i) {
		if (t4_cipher_nids[i] == NID_t4_aes_128_ctr) {
			t4_cipher_nids[i] = NID_undef;
		} else if (t4_cipher_nids[i] == NID_t4_aes_192_ctr) {
			t4_cipher_nids[i] = NID_undef;
		} else if (t4_cipher_nids[i] == NID_t4_aes_256_ctr) {
			t4_cipher_nids[i] = NID_undef;
		}
	}

	/* Clear NID_t4_aes_*_ctr and t4_cipher_table[] variables */
	if (NID_t4_aes_128_ctr != NID_undef) {
		o = OBJ_nid2obj(NID_t4_aes_128_ctr);
		if (o != NULL)
			ASN1_OBJECT_free(o);
		NID_t4_aes_128_ctr = NID_undef;
		t4_cipher_table[T4_AES_128_CTR].nid =
		    t4_aes_128_ctr.nid = NID_undef;
	}

	if (NID_t4_aes_192_ctr != NID_undef) {
		o = OBJ_nid2obj(NID_t4_aes_192_ctr);
		if (o != NULL)
			ASN1_OBJECT_free(o);
		NID_t4_aes_192_ctr = NID_undef;
		t4_cipher_table[T4_AES_192_CTR].nid =
		    t4_aes_192_ctr.nid = NID_undef;
	}

	if (NID_t4_aes_256_ctr != NID_undef) {
		o = OBJ_nid2obj(NID_t4_aes_256_ctr);
		if (o != NULL)
		ASN1_OBJECT_free(o);
		NID_t4_aes_256_ctr = NID_undef;
		t4_cipher_table[T4_AES_256_CTR].nid =
		    t4_aes_256_ctr.nid = NID_undef;
	}
}
#endif	/* !SOLARIS_NO_AES_CTR */


/*
 * Cipher functions
 */


/*
 * Registered by the ENGINE with ENGINE_set_ciphers().
 * Finds out how to deal with a particular cipher NID in the ENGINE.
 */
/* ARGSUSED */
static int
t4_get_all_ciphers(ENGINE *e, const EVP_CIPHER **cipher,
    const int **nids, int nid)
{
	if (cipher == NULL) { /* return a list of all supported ciphers */
		*nids = (t4_cipher_count > 0) ? t4_cipher_nids : NULL;
		return (t4_cipher_count);
	}

	switch (nid) {
	case NID_aes_128_cbc:
		*cipher = &t4_aes_128_cbc;
		break;
	case NID_aes_192_cbc:
		*cipher = &t4_aes_192_cbc;
		break;
	case NID_aes_256_cbc:
		*cipher = &t4_aes_256_cbc;
		break;
	case NID_aes_128_ecb:
		*cipher = &t4_aes_128_ecb;
		break;
	case NID_aes_192_ecb:
		*cipher = &t4_aes_192_ecb;
		break;
	case NID_aes_256_ecb:
		*cipher = &t4_aes_256_ecb;
		break;
#ifndef	SOLARIS_NO_AES_CFB128
	case NID_aes_128_cfb128:
		*cipher = &t4_aes_128_cfb128;
		break;
	case NID_aes_192_cfb128:
		*cipher = &t4_aes_192_cfb128;
		break;
	case NID_aes_256_cfb128:
		*cipher = &t4_aes_256_cfb128;
		break;
#endif	/* !SOLARIS_NO_AES_CFB128 */
#ifndef	OPENSSL_NO_DES
	case NID_des_cbc:
		*cipher = &t4_des_cbc;
		break;
	case NID_des_ede3_cbc:
		*cipher = &t4_des3_cbc;
		break;
	case NID_des_ecb:
		*cipher = &t4_des_ecb;
		break;
	case NID_des_ede3_ecb:
		*cipher = &t4_des3_ecb;
		break;
#endif	/* !OPENSSL_NO_DES */

	default:
#ifndef	SOLARIS_NO_AES_CTR
		/* These NIDs cannot be const, so must be tested with "if" */
		if (nid == NID_t4_aes_128_ctr) {
			*cipher = &t4_aes_128_ctr;
			break;
		} else if (nid == NID_t4_aes_192_ctr) {
			*cipher = &t4_aes_192_ctr;
			break;
		} else if (nid == NID_t4_aes_256_ctr) {
			*cipher = &t4_aes_256_ctr;
			break;
		} else
#endif	/* !SOLARIS_NO_AES_CTR */
		{
			/* cipher not supported */
			*cipher = NULL;
			return (0);
		}
	}

	return (1);
}


/* Called by t4_cipher_init_aes() */
static t4_cipher_id
get_cipher_index_by_nid(int nid)
{
	t4_cipher_id i;

	for (i = (t4_cipher_id)0; i < T4_CIPHER_MAX; ++i)
		if (t4_cipher_table[i].nid == nid)
			return (i);
	return (T4_CIPHER_MAX);
}


/* ARGSUSED2 */
static int
t4_cipher_init_aes(EVP_CIPHER_CTX *ctx, const unsigned char *key,
    const unsigned char *iv, int enc)
{
	t4_cipher_ctx_t	*tctx = ctx->cipher_data;
	uint64_t	*t4_ks = tctx->t4_ks;
	t4_cipher_t	*t4_cipher;
	t4_cipher_id	index;
	int		key_len = ctx->key_len;
	uint64_t	aligned_key_buffer[4]; /* 16, 24, or 32 bytes long */
	uint64_t	*aligned_key;

	if (key == NULL) {
		T4err(T4_F_CIPHER_INIT_AES, T4_R_CIPHER_KEY);
		return (0);
	}

	/* Get the cipher entry index in t4_cipher_table from nid */
	index = get_cipher_index_by_nid(ctx->cipher->nid);
	if (index >= T4_CIPHER_MAX) {
		T4err(T4_F_CIPHER_INIT_AES, T4_R_CIPHER_NID);
		return (0); /* Error */
	}
	t4_cipher = &t4_cipher_table[index];

	/* Check key size and iv size */
	if (ctx->cipher->iv_len < t4_cipher->iv_len) {
		T4err(T4_F_CIPHER_INIT_AES, T4_R_IV_LEN_INCORRECT);
		return (0); /* Error */
	}
	if ((key_len < t4_cipher->min_key_len) ||
	    (key_len > t4_cipher->max_key_len)) {
		T4err(T4_F_CIPHER_INIT_AES, T4_R_KEY_LEN_INCORRECT);
		return (0); /* Error */
	}

	/* Set cipher flags, if any */
	ctx->flags |= t4_cipher->flags;

	/* Align the key */
	if (((unsigned long)key & 0x7) == 0) /* already aligned */
		aligned_key = (uint64_t *)key;
	else { /* key is not 8-byte aligned */
#ifdef	DEBUG_T4
		(void) fprintf(stderr, "T4: key is not 8 byte aligned\n");
#endif
		(void) memcpy(aligned_key_buffer, key, key_len);
		aligned_key = aligned_key_buffer;
	}


	/*
	 * Expand the key schedule.
	 * Copy original key to start of t4_ks key schedule. Note that the
	 * encryption and decryption key schedule are the same for T4.
	 */
	switch (key_len) {
		case 16:
			t4_aes_expand128(&t4_ks[2],
			    (const uint32_t *)aligned_key);
			t4_ks[0] = aligned_key[0];
			t4_ks[1] = aligned_key[1];
			break;
		case 24:
			t4_aes_expand192(&t4_ks[3],
			    (const uint32_t *)aligned_key);
			t4_ks[0] = aligned_key[0];
			t4_ks[1] = aligned_key[1];
			t4_ks[2] = aligned_key[2];
			break;
		case 32:
			t4_aes_expand256(&t4_ks[4],
			    (const uint32_t *)aligned_key);
			t4_ks[0] = aligned_key[0];
			t4_ks[1] = aligned_key[1];
			t4_ks[2] = aligned_key[2];
			t4_ks[3] = aligned_key[3];
			break;
		default:
			T4err(T4_F_CIPHER_INIT_AES, T4_R_CIPHER_KEY);
			return (0);
	}

	/* Save index to cipher */
	tctx->index = index;

	/* Align IV, if needed */
	if (t4_cipher->iv_len <= 0) { /* no IV (such as with ECB mode) */
		tctx->iv = NULL;
	} else if (((unsigned long)ctx->iv & 0x7) == 0) { /* already aligned */
		tctx->iv = (uint64_t *)ctx->iv;
	} else {
		/* IV is not 8 byte aligned */
		(void) memcpy(tctx->aligned_iv_buffer, ctx->iv,
		    ctx->cipher->iv_len);
		tctx->iv = tctx->aligned_iv_buffer;
#ifdef	DEBUG_T4
		(void) fprintf(stderr,
		    "t4_cipher_init_aes: IV is not 8 byte aligned\n");
		(void) fprintf(stderr,
		    "t4_cipher_init_aes: ctx->cipher->iv_len =%d\n",
		    ctx->cipher->iv_len);
		(void) fprintf(stderr, "t4_cipher_init_aes: after "
		    "re-alignment, tctx->iv = %p\n", (void *)tctx->iv);
#endif	/* DEBUG_T4 */
	}

	return (1);
}


/*
 * ENCRYPT_UPDATE or DECRYPT_UPDATE
 */
#define	T4_CIPHER_DO_AES(t4_cipher_do_aes, t4_aes_load_keys_for_encrypt, \
    t4_aes_encrypt, t4_aes_load_keys_for_decrypt, t4_aes_decrypt, iv)	\
static int								\
t4_cipher_do_aes(EVP_CIPHER_CTX *ctx, unsigned char *out,		\
    const unsigned char *in, size_t inl)				\
{									\
	t4_cipher_ctx_t	*tctx = ctx->cipher_data;			\
	uint64_t	*t4_ks = tctx->t4_ks;				\
	unsigned long	outl = inl;					\
	unsigned char	*bufin_alloc = NULL, *bufout_alloc = NULL;	\
	unsigned char	*bufin, *bufout;				\
									\
	/* "in" and "out" must be 8 byte aligned */			\
	if (((unsigned long)in & 0x7) == 0) { /* already aligned */	\
		bufin = (unsigned char *)in;				\
	} else { /* "in" is not 8 byte aligned */			\
		if (((unsigned long)out & 0x7) == 0) { /* aligned */	\
			/* use output buffer for input */		\
			bufin = out;					\
		} else {						\
			bufin = bufin_alloc = OPENSSL_malloc(inl);	\
			if (bufin_alloc == NULL)			\
				return (0); /* error */			\
		}							\
		(void) memcpy(bufin, in, inl);				\
	}								\
									\
	if (((unsigned long)out & 0x7) == 0) { /* already aligned */	\
		bufout = out;						\
	} else { /* "out" is not 8 byte aligned */			\
		if (bufin_alloc != NULL) {				\
			/* use allocated input buffer for output */	\
			bufout = bufin_alloc;				\
		} else {						\
			bufout = bufout_alloc = OPENSSL_malloc(outl);	\
			if (bufout_alloc == NULL) {			\
				OPENSSL_free(bufin_alloc);		\
				return (0); /* error */			\
			}						\
		}							\
	}								\
									\
	/* Data length must be an even multiple of block size. */	\
	if ((inl & 0xf) != 0) {						\
		OPENSSL_free(bufout_alloc);				\
		OPENSSL_free(bufin_alloc);				\
		T4err(T4_F_CIPHER_DO_AES, T4_R_NOT_BLOCKSIZE_LENGTH);	\
		return (0);						\
	}								\
									\
	if (ctx->encrypt) {						\
		t4_aes_load_keys_for_encrypt(t4_ks);			\
		t4_aes_encrypt(t4_ks, (uint64_t *)bufin,		\
		    (uint64_t *)bufout, (size_t)inl, iv);		\
	} else { /* decrypt */						\
		t4_aes_load_keys_for_decrypt(t4_ks);			\
		t4_aes_decrypt(t4_ks, (uint64_t *)bufin,		\
		    (uint64_t *)bufout, (size_t)inl, iv);		\
	}								\
									\
	/* Cleanup */							\
	if (bufin_alloc != NULL) {					\
		if (bufout == bufin_alloc)				\
			(void) memcpy(out, bufout, outl);		\
		OPENSSL_free(bufin_alloc);				\
	}								\
	if (bufout_alloc != NULL) {					\
		(void) memcpy(out, bufout_alloc, outl);			\
		OPENSSL_free(bufout_alloc);				\
	}								\
									\
	return (1);							\
}


/* AES CBC mode. */
T4_CIPHER_DO_AES(t4_cipher_do_aes_128_cbc,
	t4_aes128_load_keys_for_encrypt, t4_aes128_cbc_encrypt,
	t4_aes128_load_keys_for_decrypt, t4_aes128_cbc_decrypt, tctx->iv)
T4_CIPHER_DO_AES(t4_cipher_do_aes_192_cbc,
	t4_aes192_load_keys_for_encrypt, t4_aes192_cbc_encrypt,
	t4_aes192_load_keys_for_decrypt, t4_aes192_cbc_decrypt, tctx->iv)
T4_CIPHER_DO_AES(t4_cipher_do_aes_256_cbc,
	t4_aes256_load_keys_for_encrypt, t4_aes256_cbc_encrypt,
	t4_aes256_load_keys_for_decrypt, t4_aes256_cbc_decrypt, tctx->iv)

/*
 * AES CFB128 mode.
 * CFB128 decrypt uses load_keys_for_encrypt() as the mode uses
 * the raw AES encrypt operation for the decryption, too.
 */
#ifndef	SOLARIS_NO_AES_CFB128
T4_CIPHER_DO_AES(t4_cipher_do_aes_128_cfb128,
	t4_aes128_load_keys_for_encrypt, t4_aes128_cfb128_encrypt,
	t4_aes128_load_keys_for_encrypt, t4_aes128_cfb128_decrypt, tctx->iv)
T4_CIPHER_DO_AES(t4_cipher_do_aes_192_cfb128,
	t4_aes192_load_keys_for_encrypt, t4_aes192_cfb128_encrypt,
	t4_aes192_load_keys_for_encrypt, t4_aes192_cfb128_decrypt, tctx->iv)
T4_CIPHER_DO_AES(t4_cipher_do_aes_256_cfb128,
	t4_aes256_load_keys_for_encrypt, t4_aes256_cfb128_encrypt,
	t4_aes256_load_keys_for_encrypt, t4_aes256_cfb128_decrypt, tctx->iv)
#endif	/* !SOLARIS_NO_AES_CFB128 */

/* AES CTR mode. */
#ifndef	SOLARIS_NO_AES_CTR
T4_CIPHER_DO_AES(t4_cipher_do_aes_128_ctr,
	t4_aes128_load_keys_for_encrypt, t4_aes128_ctr_crypt,
	t4_aes128_load_keys_for_decrypt, t4_aes128_ctr_crypt, tctx->iv)
T4_CIPHER_DO_AES(t4_cipher_do_aes_192_ctr,
	t4_aes192_load_keys_for_encrypt, t4_aes192_ctr_crypt,
	t4_aes192_load_keys_for_decrypt, t4_aes192_ctr_crypt, tctx->iv)
T4_CIPHER_DO_AES(t4_cipher_do_aes_256_ctr,
	t4_aes256_load_keys_for_encrypt, t4_aes256_ctr_crypt,
	t4_aes256_load_keys_for_decrypt, t4_aes256_ctr_crypt, tctx->iv)
#endif	/* !SOLARIS_NO_AES_CTR */

/* AES ECB mode. */
T4_CIPHER_DO_AES(t4_cipher_do_aes_128_ecb,
	t4_aes128_load_keys_for_encrypt, t4_aes128_ecb_encrypt,
	t4_aes128_load_keys_for_decrypt, t4_aes128_ecb_decrypt, NULL)
T4_CIPHER_DO_AES(t4_cipher_do_aes_192_ecb,
	t4_aes192_load_keys_for_encrypt, t4_aes192_ecb_encrypt,
	t4_aes192_load_keys_for_decrypt, t4_aes192_ecb_decrypt, NULL)
T4_CIPHER_DO_AES(t4_cipher_do_aes_256_ecb,
	t4_aes256_load_keys_for_encrypt, t4_aes256_ecb_encrypt,
	t4_aes256_load_keys_for_decrypt, t4_aes256_ecb_decrypt, NULL)


/*
 * Is the t4 engine available?
 * Passed to ENGINE_set_init_function().
 */
/* ARGSUSED */
static int
t4_init(ENGINE *e)
{
	return (1);
}


/* Passed to ENGINE_set_destroy_function(). */
/* ARGSUSED */
static int
t4_destroy(ENGINE *e)
{
	T4_FREE_AES_CTR_NIDS;
	ERR_unload_t4_strings();
	return (1);
}


/*
 * Called by t4_bind_helper().
 * Note: too early to use T4err() functions on errors.
 */
/* ARGSUSED */
static int
t4_bind(ENGINE *e)
{
	_Bool aes_engage, digest_engage, des_engage, montmul_engage;

	t4_instructions_present(&aes_engage, &des_engage, &digest_engage,
	    &montmul_engage);
#ifdef	DEBUG_T4
	(void) fprintf(stderr,
	    "t4_bind: engage aes=%d, des=%d, digest=%d\n",
	    aes_engage, des_engage, digest_engage);
#endif
#ifndef	OPENSSL_NO_DES
	if (!des_engage) { /* Remove DES ciphers from list */
		t4_cipher_count -= t4_des_cipher_count;
	}
#endif

#ifndef	SOLARIS_NO_AES_CTR
	/*
	 * We must do this before we start working with slots since we need all
	 * NIDs there.
	 */
	if (aes_engage) {
		if (t4_add_aes_ctr_NIDs() == 0) {
			T4_FREE_AES_CTR_NIDS;
			return (0);
		}
	}
#endif	/* !SOLARIS_NO_AES_CTR */

#ifdef	DEBUG_T4
	(void) fprintf(stderr, "t4_cipher_count = %d; t4_cipher_nids[] =\n",
	    t4_cipher_count);
	for (int i = 0; i < t4_cipher_count; ++i) {
		(void) fprintf(stderr, " %d", t4_cipher_nids[i]);
	}
	(void) fprintf(stderr, "\n");
#endif	/* DEBUG_T4 */

	/* Register T4 engine ID, name, and functions */
	if (!ENGINE_set_id(e, ENGINE_T4_ID) ||
	    !ENGINE_set_name(e,
	    aes_engage ? ENGINE_T4_NAME: ENGINE_NO_T4_NAME) ||
	    !ENGINE_set_init_function(e, t4_init) ||
	    (aes_engage && !ENGINE_set_ciphers(e, t4_get_all_ciphers)) ||
	    (digest_engage && !ENGINE_set_digests(e, t4_get_all_digests)) ||
#ifndef OPENSSL_NO_RSA
	    (montmul_engage && !ENGINE_set_RSA(e, t4_RSA())) ||
#endif	/* OPENSSL_NO_RSA */
#ifndef OPENSSL_NO_DH
	    (montmul_engage && !ENGINE_set_DH(e, t4_DH())) ||
#endif	/* OPENSSL_NO_DH */
#ifndef OPENSSL_NO_DSA
	    (montmul_engage && !ENGINE_set_DSA(e, t4_DSA())) ||
#endif	/* OPENSSL_NO_DSA */
	    !ENGINE_set_destroy_function(e, t4_destroy)) {
		T4_FREE_AES_CTR_NIDS;
		return (0);
	}

	return (1);
}


/*
 * Called by ENGINE_load_t4().
 * Note: too early to use T4err() functions on errors.
 */
static int
t4_bind_helper(ENGINE *e, const char *id)
{
	if (id != NULL && (strcmp(id, ENGINE_T4_ID) != 0)) {
		(void) fprintf(stderr, "T4: bad t4 engine ID\n");
		return (0);
	}
	if (!t4_bind(e)) {
		(void) fprintf(stderr,
		    "T4: failed to bind t4 engine\n");
		return (0);
	}

	return (1);
}


#ifdef	DYNAMIC_ENGINE
IMPLEMENT_DYNAMIC_CHECK_FN()
IMPLEMENT_DYNAMIC_BIND_FN(t4_bind_helper)
#endif	/* DYNAMIC_ENGINE */
#endif	/* COMPILE_HW_T4 */
#endif	/* !OPENSSL_NO_HW && !OPENSSL_NO_HW_AES_T4 && !OPENSSL_NO_AES */
