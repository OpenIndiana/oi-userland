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
 * This engine supports SPARC microprocessors that provide DES and other
 * cipher and hash instructions, such as the T4 microprocessor.
 *
 * This file implements the DES and DES3 cipher operations.
 */

#include <openssl/opensslconf.h>

#if !defined(OPENSSL_NO_HW) && !defined(OPENSSL_NO_HW_DES_T4) && \
	!defined(OPENSSL_NO_DES)
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <openssl/engine.h>
#include "eng_t4_des_asm.h"

#include "eng_t4_err.c"

/* Index for the supported DES ciphers */
typedef enum {
	T4_DES_CBC,
	T4_DES3_CBC,
	T4_DES_ECB,
	T4_DES3_ECB,
	T4_DES_MAX
} t4_des_cipher_id;

/* From Solaris file usr/src/common/crypto/des/des_impl.c */
typedef struct {
	uint64_t ksch_encrypt[16];
	uint64_t ksch_decrypt[16];
} t4_keysched_t;

typedef struct {
	uint64_t ksch_encrypt[16 * 3];
	uint64_t ksch_decrypt[16 * 3];
} t4_keysched3_t;

/* T4 cipher context; must be 8-byte aligned (last field must be uint64_t)  */
typedef struct t4_des_cipher_ctx {
	t4_des_cipher_id	index;
	uint64_t		*iv;
	uint64_t		aligned_iv_buffer; /* use if IV unaligned */
	union {
		t4_keysched_t	des;
		t4_keysched3_t	des3;
	} ks;
} t4_des_cipher_ctx_t;

typedef struct t4_cipher {
	t4_des_cipher_id	id;
	int			nid;
	int			iv_len;
	int			min_key_len;
	int			max_key_len;
} t4_des_cipher_t;


#if (defined(sun4v) || defined(__sparcv9) || defined(__sparcv8plus) || \
	defined(__sparcv8)) && !defined(OPENSSL_NO_ASM)
#define	COMPILE_HW_T4
#endif

#ifdef	COMPILE_HW_T4
static t4_des_cipher_id get_des_cipher_index_by_nid(int nid);
#pragma inline(get_des_cipher_index_by_nid)


/*
 * Cipher Table for all supported symmetric ciphers.
 * Must be in same order as t4_des_cipher_id.
 */
static t4_des_cipher_t t4_des_cipher_table[] = {
	/* ID			NID		IV	min-key	max-key */
	{T4_DES_CBC,	NID_des_cbc,		8,	8,	8},
	{T4_DES3_CBC,	NID_des_ede3_cbc,	8,	24,	24},
	{T4_DES_ECB,	NID_des_ecb,		0,	8,	8},
	{T4_DES3_ECB,	NID_des_ede3_ecb,	0,	24,	24},
};


/* Formal declaration for functions in EVP_CIPHER structure */
static int t4_cipher_init_des(EVP_CIPHER_CTX *ctx, const unsigned char *key,
    const unsigned char *iv, int enc);

static int t4_cipher_do_des_cbc(EVP_CIPHER_CTX *ctx, unsigned char *out,
    const unsigned char *in, size_t inl);
static int t4_cipher_do_des3_cbc(EVP_CIPHER_CTX *ctx, unsigned char *out,
    const unsigned char *in, size_t inl);
static int t4_cipher_do_des_ecb(EVP_CIPHER_CTX *ctx, unsigned char *out,
    const unsigned char *in, size_t inl);
static int t4_cipher_do_des3_ecb(EVP_CIPHER_CTX *ctx, unsigned char *out,
    const unsigned char *in, size_t inl);


/*
 * Cipher Algorithms
 *
 * OpenSSL's libcrypto EVP stuff. This is how this engine gets wired to EVP.
 * EVP_CIPHER is defined in evp.h.  To maintain binary compatibility the
 * definition cannot be modified.
 * Stuff specific to the t4 engine is kept in t4_des_cipher_ctx_t, which is
 * pointed to by cipher_data or md_data
 *
 * Fields: nid, block_size, key_len, iv_len, flags,
 *	init(), do_cipher(), cleanup(),
 *	ctx_size,
 *	set_asn1_parameters(), get_asn1_parameters(), ctrl(), app_data
 */

const EVP_CIPHER t4_des_cbc = {
	NID_des_cbc,
	8, 8, 8,
	EVP_CIPH_CBC_MODE,
	t4_cipher_init_des, t4_cipher_do_des_cbc, NULL,
	sizeof (t4_des_cipher_ctx_t),
	EVP_CIPHER_set_asn1_iv, EVP_CIPHER_get_asn1_iv,
	NULL, NULL
};
const EVP_CIPHER t4_des3_cbc = {
	NID_des_ede3_cbc,
	8, 24, 8,
	EVP_CIPH_CBC_MODE,
	t4_cipher_init_des, t4_cipher_do_des3_cbc, NULL,
	sizeof (t4_des_cipher_ctx_t),
	EVP_CIPHER_set_asn1_iv, EVP_CIPHER_get_asn1_iv,
	NULL, NULL
};

/*
 * ECB modes don't use an Initial Vector, so that's why set_asn1_parameters,
 * get_asn1_parameters, and cleanup fields are set to NULL.
 */
const EVP_CIPHER t4_des_ecb = {
	NID_des_ecb,
	8, 8, 8,
	EVP_CIPH_ECB_MODE,
	t4_cipher_init_des, t4_cipher_do_des_ecb, NULL,
	sizeof (t4_des_cipher_ctx_t),
	NULL, NULL, NULL, NULL
};
const EVP_CIPHER t4_des3_ecb = {
	NID_des_ede3_ecb,
	8, 24, 8,
	EVP_CIPH_ECB_MODE,
	t4_cipher_init_des, t4_cipher_do_des3_ecb, NULL,
	sizeof (t4_des_cipher_ctx_t),
	NULL, NULL, NULL, NULL
};


/*
 * DES Cipher functions
 */

/* Called by t4_cipher_init_des() */
static t4_des_cipher_id
get_des_cipher_index_by_nid(int nid)
{
	t4_des_cipher_id i;

	for (i = (t4_des_cipher_id)0; i < T4_DES_MAX; ++i)
		if (t4_des_cipher_table[i].nid == nid)
			return (i);
	return (T4_DES_MAX);
}


/*
 * Initialize encryption and decryption key schedules for DES or DES3.
 * Called by t4_cipher_init_des().
 *
 * Modified from Solaris DES function des_init_keysched().
 */
static int
t4_des_init_keysched(const unsigned char *cipherKey,
    unsigned int keysize, void *ks)
{
	uint64_t *encryption_ks, *decryption_ks;
	uint64_t keysched[16 * 3];	/* 128 or 384 bytes for DES or DES3 */
	uint64_t key_uint64[3];		/* 8 or 24 bytes for DES or DES3 */
	uint64_t *aligned_key;
	uint64_t tmp;
	uint_t	i, j;

	switch (keysize) {
	case 8: /* DES */
		encryption_ks = ((t4_keysched_t *)ks)->ksch_encrypt;
		decryption_ks = ((t4_keysched_t *)ks)->ksch_decrypt;
		break;
	case 24: /* DES3 */
		encryption_ks = ((t4_keysched3_t *)ks)->ksch_encrypt;
		decryption_ks = ((t4_keysched3_t *)ks)->ksch_decrypt;
		break;
	default:
		T4err(T4_F_CIPHER_INIT_DES, T4_R_CIPHER_KEY);
		return (0);
	}

	/* Align key, if needed */
	if (((unsigned long)cipherKey & 0x7) == 0) { /* aligned */
		/* LINTED: pointer alignment */
		aligned_key = (uint64_t *)cipherKey;
	} else { /* unaligned--copy byte-by-byte */
		for (i = 0, j = 0; j < keysize; ++i, j += 8) {
			key_uint64[i] = (((uint64_t)cipherKey[j] << 56) |
			    ((uint64_t)cipherKey[j + 1] << 48) |
			    ((uint64_t)cipherKey[j + 2] << 40) |
			    ((uint64_t)cipherKey[j + 3] << 32) |
			    ((uint64_t)cipherKey[j + 4] << 24) |
			    ((uint64_t)cipherKey[j + 5] << 16) |
			    ((uint64_t)cipherKey[j + 6] << 8) |
			    (uint64_t)cipherKey[j + 7]);
		}
		aligned_key = key_uint64;
	}

	/* Expand key schedule */
	switch (keysize) {
	case 8: /* DES */
		t4_des_expand(keysched, (const uint32_t *)aligned_key);
		break;

	case 24: /* DES3 */
		t4_des_expand(keysched, (const uint32_t *)aligned_key);
		t4_des_expand(keysched + 16,
		    (const uint32_t *)&aligned_key[1]);
		for (i = 0; i < 8; ++i) {
			tmp = keysched[16 + i];
			keysched[16 + i] = keysched[31 - i];
			keysched[31 - i] = tmp;
		}
		t4_des_expand(keysched + 32,
		    (const uint32_t *)&aligned_key[2]);
		break;

	default:
		T4err(T4_F_CIPHER_INIT_DES, T4_R_CIPHER_KEY);
		return (0);
	}

	/* Save encryption key schedule */
	memcpy(encryption_ks, keysched, keysize * 16);

	/* Reverse key schedule */
	for (i = 0; i < keysize; ++i) {
		tmp = keysched[i];
		keysched[i] = keysched[2 * keysize - 1 - i];
		keysched[2 * keysize -1 -i] = tmp;
	}

	/* Save decryption key schedule */
	memcpy(decryption_ks, keysched, keysize * 16);

	return (1);
}


/* ARGSUSED2 */
static int
t4_cipher_init_des(EVP_CIPHER_CTX *ctx, const unsigned char *key,
    const unsigned char *iv, int enc)
{
	t4_des_cipher_ctx_t	*tctx = ctx->cipher_data;
	uint64_t		*encryption_ks, *decryption_ks;
	t4_des_cipher_t		*t4_cipher;
	t4_des_cipher_id	index;
	unsigned int		key_len = ctx->key_len;
	uint64_t		aligned_key_buffer[3]; /* 8 or 24 bytes long */
	uint64_t		*aligned_key;

	if (key == NULL) {
		T4err(T4_F_CIPHER_INIT_DES, T4_R_CIPHER_KEY);
		return (0);
	}

	/* Get the cipher entry index in t4_des_cipher_table from nid */
	index = get_des_cipher_index_by_nid(ctx->cipher->nid);
	if (index >= T4_DES_MAX) {
		T4err(T4_F_CIPHER_INIT_DES, T4_R_CIPHER_NID);
		return (0); /* Error */
	}
	t4_cipher = &t4_des_cipher_table[index];

	/* Check key size and iv size */
	if (ctx->cipher->iv_len < t4_cipher->iv_len) {
		T4err(T4_F_CIPHER_INIT_DES, T4_R_IV_LEN_INCORRECT);
		return (0); /* Error */
	}
	if ((key_len < t4_cipher->min_key_len) ||
	    (key_len > t4_cipher->max_key_len)) {
		T4err(T4_F_CIPHER_INIT_DES, T4_R_KEY_LEN_INCORRECT);
		return (0); /* Error */
	}

	/* Expand key schedule */
	if (t4_des_init_keysched(key, key_len, &tctx->ks) == 0)
		return (0); /* Error */

	/* Save index to cipher */
	tctx->index = index;

	/* Align IV, if needed */
	if (t4_cipher->iv_len <= 0) { /* no IV (such as with ECB mode) */
		tctx->iv = NULL;
	} else if (((unsigned long)ctx->iv & 0x7) == 0) { /* already aligned */
		tctx->iv = (uint64_t *)ctx->iv;
	} else {
		/* IV is not 8 byte aligned */
		(void) memcpy(&tctx->aligned_iv_buffer, ctx->iv,
		    ctx->cipher->iv_len);
		tctx->iv = &tctx->aligned_iv_buffer;
#ifdef	DEBUG_T4
		(void) fprintf(stderr,
		    "t4_cipher_init_des: IV is not 8 byte aligned\n");
		(void) fprintf(stderr,
		    "t4_cipher_init_des: ctx->cipher->iv_len =%d\n",
		    ctx->cipher->iv_len);
		(void) fprintf(stderr, "t4_cipher_init_des: after "
		    "re-alignment, tctx->iv = %p\n", (void *)tctx->iv);
#endif	/* DEBUG_T4 */
	}

	return (1);
}


/*
 * ENCRYPT_UPDATE or DECRYPT_UPDATE
 */
#define	T4_CIPHER_DO_DES(t4_cipher_do_des, t4_des_load_keys,		\
    t4_des_encrypt, t4_des_decrypt, ksched_encrypt, ksched_decrypt, iv)	\
static int								\
t4_cipher_do_des(EVP_CIPHER_CTX *ctx, unsigned char *out,		\
    const unsigned char *in, size_t inl)				\
{									\
	t4_des_cipher_ctx_t	*tctx = ctx->cipher_data;		\
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
	/* Data length must be an even multiple of block size. */	\
	if ((inl & 0x7) != 0) {						\
		OPENSSL_free(bufout_alloc);				\
		OPENSSL_free(bufin_alloc);				\
		T4err(T4_F_CIPHER_DO_DES, T4_R_NOT_BLOCKSIZE_LENGTH);	\
		return (0);						\
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
	if (ctx->encrypt) {						\
		uint64_t	*ksch_encrypt = ksched_encrypt;		\
		t4_des_load_keys(ksch_encrypt);				\
		t4_des_encrypt(ksch_encrypt, (uint64_t *)bufin,		\
		    (uint64_t *)bufout, (size_t)inl, iv);		\
	} else { /* decrypt */						\
		uint64_t	*ksch_decrypt = ksched_decrypt;		\
		t4_des_load_keys(ksch_decrypt);				\
		t4_des_decrypt(ksch_decrypt, (uint64_t *)bufin,		\
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


/* DES CBC mode. */
T4_CIPHER_DO_DES(t4_cipher_do_des_cbc, t4_des_load_keys,
	t4_des_cbc_encrypt, t4_des_cbc_decrypt,
	tctx->ks.des.ksch_encrypt, tctx->ks.des.ksch_decrypt, tctx->iv)
T4_CIPHER_DO_DES(t4_cipher_do_des3_cbc, t4_des3_load_keys,
	t4_des3_cbc_encrypt, t4_des3_cbc_decrypt,
	tctx->ks.des3.ksch_encrypt, tctx->ks.des3.ksch_decrypt, tctx->iv)

/* DES ECB mode. */
T4_CIPHER_DO_DES(t4_cipher_do_des_ecb, t4_des_load_keys,
	t4_des_ecb_crypt, t4_des_ecb_crypt,
	tctx->ks.des.ksch_encrypt, tctx->ks.des.ksch_decrypt, NULL)
T4_CIPHER_DO_DES(t4_cipher_do_des3_ecb, t4_des3_load_keys,
	t4_des3_ecb_crypt, t4_des3_ecb_crypt,
	tctx->ks.des3.ksch_encrypt, tctx->ks.des3.ksch_decrypt, NULL)


#endif	/* COMPILE_HW_T4 */
#endif	/* !OPENSSL_NO_HW && !OPENSSL_NO_HW_DES_T4 && !OPENSSL_NO_DES */
