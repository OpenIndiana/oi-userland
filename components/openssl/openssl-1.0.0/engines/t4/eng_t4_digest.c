/*
 * Copyright (c) 2011, Oracle and/or its affiliates. All rights reserved.
 */

/*
 * The basic framework for this code came from the reference
 * implementation for MD5 provided in RFC 1321.
 *
 * Copyright (C) 1991-2, RSA Data Security, Inc. Created 1991. All
 * rights reserved.
 *
 * License to copy and use this software is granted provided that it
 * is identified as the "RSA Data Security, Inc. MD5 Message-Digest
 * Algorithm" in all material mentioning or referencing this software
 * or this function.
 *
 * License is also granted to make and use derivative works provided
 * that such works are identified as "derived from the RSA Data
 * Security, Inc. MD5 Message-Digest Algorithm" in all material
 * mentioning or referencing the derived work.
 *
 * RSA Data Security, Inc. makes no representations concerning either
 * the merchantability of this software or the suitability of this
 * software for any particular purpose. It is provided "as is"
 * without express or implied warranty of any kind.
 *
 * These notices must be retained in any copies of any part of this
 * documentation and/or software.
 */


/*
 * This engine supports SPARC microprocessors that provide AES and other
 * cipher and hash instructions, such as the T4 microprocessor.
 *
 * This file implements the MD5, SHA1, and SHA2 message digest operations.
 */

#include <openssl/opensslconf.h>

#if !defined(OPENSSL_NO_HW) && !defined(OPENSSL_NO_HW_MD_T4)
#include <sys/types.h>
#include <sys/auxv.h>		/* getisax() */
#include <sys/sysmacros.h>	/* IS_P2ALIGNED() */
#include <sys/byteorder.h>	/* htonl() and friends */
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#ifndef OPENSSL_NO_SHA
/*
 * Solaris sys/sha2.h and OpenSSL openssl/sha.h both define
 * SHA256_CTX, SHA512_CTX, SHA256, SHA384, and SHA512.
 */
#define	SHA256_CTX	OPENSSL_SHA256_CTX
#define	SHA512_CTX	OPENSSL_SHA512_CTX
#define	SHA256		OPENSSL_SHA256
#define	SHA512		OPENSSL_SHA512
#include <openssl/sha.h>
#undef	SHA256_CTX
#undef	SHA512_CTX
#undef	SHA256
#undef	SHA512
#endif	/* !OPENSSL_NO_SHA */

#include <openssl/bio.h>
#include <openssl/aes.h>
#include <openssl/engine.h>

/* Solaris digest definitions (must follow openssl/sha.h) */
#include <sys/md5.h>
#ifndef OPENSSL_NO_SHA
#include <sys/sha1.h>
#define	_SHA2_IMPL	/* Required for SHA*_MECH_INFO_TYPE enum */
#include <sys/sha2.h>
#endif	/* !OPENSSL_NO_SHA */

#if (defined(sun4v) || defined(__sparcv9) || defined(__sparcv8plus) || \
	defined(__sparcv8)) && !defined(OPENSSL_NO_ASM)
#define	COMPILE_HW_T4
#endif

#ifdef	COMPILE_HW_T4

/* Copied from OpenSSL md5.h */
#ifndef MD5_CBLOCK
#define	MD5_CBLOCK		64
#endif

/* Padding needed is 64 bytes for MD5 and SHA1, 128 for SHA2 */
static const uint8_t PADDING[128] = { 0x80, 0 /* all zeros */ };

static const int t4_digest_nids[] = {
	NID_md5,
#ifndef OPENSSL_NO_SHA
	NID_sha1,
	NID_sha256,
	NID_sha512,
#endif	/* !OPENSSL_NO_SHA */
};
static const int t4_digest_count =
	(sizeof (t4_digest_nids) / sizeof (t4_digest_nids[0]));

/* Assembly language functions */
extern void t4_md5_multiblock(MD5_CTX *ctx, const uint8_t *input,
    unsigned int input_length_in_blocks);
extern void t4_sha1_multiblock(SHA1_CTX *ctx, const uint8_t *input,
    size_t nr_blocks);
extern void t4_sha256_multiblock(SHA2_CTX *ctx, const uint8_t *input,
    size_t nr_blocks);
extern void t4_sha512_multiblock(SHA2_CTX *ctx, const uint8_t *input,
    size_t nr_blocks);

/* Internal functions */
static void t4_md5_encode(uint8_t *restrict output,
    const uint32_t *restrict input, size_t input_len);
#pragma inline(t4_md5_encode)
static void t4_sha1_256_encode(uint8_t *restrict output,
    const uint32_t *restrict input, size_t len);
#pragma inline(t4_sha1_256_encode)
static void t4_sha512_encode64(uint8_t *restrict output,
    const uint64_t *restrict input, size_t len);
#pragma inline(t4_sha512_encode64)

/* Formal declaration for functions in EVP_MD structure */
static int t4_digest_init_md5(EVP_MD_CTX *ctx);
static int t4_digest_update_md5(EVP_MD_CTX *ctx, const void *data,
    size_t count);
static int t4_digest_final_md5(EVP_MD_CTX *ctx, unsigned char *md);
static int t4_digest_copy_md5(EVP_MD_CTX *to, const EVP_MD_CTX *from);
#ifndef OPENSSL_NO_SHA
static int t4_digest_init_sha1(EVP_MD_CTX *ctx);
static int t4_digest_update_sha1(EVP_MD_CTX *ctx, const void *data,
    size_t count);
static int t4_digest_final_sha1(EVP_MD_CTX *ctx, unsigned char *md);
static int t4_digest_copy_sha1(EVP_MD_CTX *to, const EVP_MD_CTX *from);
static int t4_digest_copy_sha2(EVP_MD_CTX *to, const EVP_MD_CTX *from);
static int t4_digest_init_sha256(EVP_MD_CTX *ctx);
static int t4_digest_update_sha256(EVP_MD_CTX *ctx, const void *data,
    size_t count);
static int t4_digest_final_sha256(EVP_MD_CTX *ctx, unsigned char *md);
static int t4_digest_init_sha512(EVP_MD_CTX *ctx);
static int t4_digest_update_sha512(EVP_MD_CTX *ctx, const void *data,
    size_t count);
static int t4_digest_final_sha512(EVP_MD_CTX *ctx, unsigned char *md);
#endif	/* !OPENSSL_NO_SHA */


/*
 * Message Digests (MD5 and SHA*)
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
static const EVP_MD t4_md5 = {
	NID_md5, NID_md5WithRSAEncryption, MD5_DIGEST_LENGTH, 0,
	t4_digest_init_md5, t4_digest_update_md5, t4_digest_final_md5,
	t4_digest_copy_md5, NULL,
	EVP_PKEY_RSA_method, MD5_CBLOCK,
	sizeof (MD5_CTX), NULL
	};

#ifndef OPENSSL_NO_SHA
static const EVP_MD t4_sha1 = {
	NID_sha1, NID_sha1WithRSAEncryption, SHA_DIGEST_LENGTH,
	EVP_MD_FLAG_PKEY_METHOD_SIGNATURE|EVP_MD_FLAG_DIGALGID_ABSENT,
	t4_digest_init_sha1, t4_digest_update_sha1, t4_digest_final_sha1,
	t4_digest_copy_sha1, NULL,
	EVP_PKEY_RSA_method, SHA_CBLOCK,
	sizeof (SHA1_CTX), NULL
	};

static const EVP_MD t4_sha256 = {
	NID_sha256, NID_sha256WithRSAEncryption, SHA256_DIGEST_LENGTH,
	EVP_MD_FLAG_PKEY_METHOD_SIGNATURE|EVP_MD_FLAG_DIGALGID_ABSENT,
	t4_digest_init_sha256, t4_digest_update_sha256, t4_digest_final_sha256,
	t4_digest_copy_sha2, NULL,
	EVP_PKEY_RSA_method, SHA256_CBLOCK,
	sizeof (SHA2_CTX), NULL
	};

static const EVP_MD t4_sha512 = {
	NID_sha512, NID_sha512WithRSAEncryption, SHA512_DIGEST_LENGTH,
	EVP_MD_FLAG_PKEY_METHOD_SIGNATURE|EVP_MD_FLAG_DIGALGID_ABSENT,
	t4_digest_init_sha512, t4_digest_update_sha512, t4_digest_final_sha512,
	t4_digest_copy_sha2, NULL,
	EVP_PKEY_RSA_method, SHA512_CBLOCK,
	sizeof (SHA2_CTX), NULL
	};
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
	case NID_md5:
		*digest = &t4_md5;
		break;
#ifndef OPENSSL_NO_SHA
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
	case NID_sha256:
		*digest = &t4_sha256;
		break;
	case NID_sha512:
		*digest = &t4_sha512;
		break;
#endif	/* !OPENSSL_NO_SHA */
	default:
		/* digest not supported */
		*digest = NULL;
		return (0);
	}

	return (1);
}


/*
 * MD5 functions
 */
static int
t4_digest_init_md5(EVP_MD_CTX *ctx)
{
	MD5_CTX	*md5_ctx = (MD5_CTX *)ctx->md_data;

	md5_ctx->state[0] = 0x01234567U;
	md5_ctx->state[1] = 0x89abcdefU;
	md5_ctx->state[2] = 0xfedcba98U;
	md5_ctx->state[3] = 0x76543210U;
	md5_ctx->count[0] = md5_ctx->count[1] = 0;

	return (1);
}


/*
 * Continue a MD5 digest operation, using the message block to update the
 * context.  MD5 crunches in 64-byte blocks.
 */
static int
t4_digest_update_md5(EVP_MD_CTX *ctx, const void *data, size_t count)
{
	MD5_CTX	*md5_ctx = (MD5_CTX *)ctx->md_data;

	uint32_t		i = 0, buf_index, remaining_len;
	const uint32_t		buf_limit = 64;
	uint32_t		block_count;
	const unsigned char	*input = (const unsigned char *)data;

	if (count == 0)
		return (1);

	/* Compute (number of bytes computed so far) mod 64 */
	buf_index = (md5_ctx->count[0] >> 3) & 0x3F;

	/* Update number of bits hashed into this MD5 computation so far */
	if ((md5_ctx->count[0] += (count << 3)) < (count << 3))
		md5_ctx->count[1]++;
	md5_ctx->count[1] += (count >> 29);

	remaining_len = buf_limit - buf_index;

	if (count >= remaining_len) {
		if (buf_index != 0) {
			(void) memcpy(&md5_ctx->buf_un.buf8[buf_index], input,
			    remaining_len);
			t4_md5_multiblock(md5_ctx, md5_ctx->buf_un.buf8, 1);
			i = remaining_len;
		}

		block_count = (count - i) >> 6;
		if (block_count > 0) {
			t4_md5_multiblock(md5_ctx, &input[i], block_count);
			i += block_count << 6;
		}

		if (count == i) {
			return (1);
		}

		buf_index = 0;
	}

	/* Buffer remaining input */
	(void) memcpy(&md5_ctx->buf_un.buf8[buf_index], &input[i], count - i);

	return (1);
}


/* Convert numbers from big endian to little endian. */
static void
t4_md5_encode(uint8_t *restrict output, const uint32_t *restrict input,
    size_t input_len)
{
	size_t		i, j;

	for (i = 0, j = 0; j < input_len; i++, j += sizeof (uint32_t)) {
		output[j] = input[i] & 0xff;
		output[j + 1] = (input[i] >> 8)  & 0xff;
		output[j + 2] = (input[i] >> 16) & 0xff;
		output[j + 3] = (input[i] >> 24) & 0xff;
	}
}


/* End MD5 digest operation, finalizing message digest and zeroing context. */
static int
t4_digest_final_md5(EVP_MD_CTX *ctx, unsigned char *md)
{
	MD5_CTX		*md5_ctx = (MD5_CTX *)ctx->md_data;
	uint8_t		bitcount_le[sizeof (md5_ctx->count)];
	uint32_t	index = (md5_ctx->count[0] >> 3) & 0x3f;

	/* store bit count, little endian */
	t4_md5_encode(bitcount_le, md5_ctx->count, sizeof (bitcount_le));

	/* pad out to 56 mod 64 */
	(void) t4_digest_update_md5(ctx, PADDING,
	    ((index < 56) ? 56 : 120) - index);

	/* append length (before padding) */
	(void) t4_digest_update_md5(ctx, bitcount_le, sizeof (bitcount_le));

	(void) memcpy(md, md5_ctx->state, 16);

	/* zeroize sensitive information */
	(void) memset(md5_ctx, 0, sizeof (*md5_ctx));

	return (1);
}


static int
t4_digest_copy_md5(EVP_MD_CTX *to, const EVP_MD_CTX *from)
{
	if ((to->md_data == NULL) || (from->md_data == NULL)) {
		return (1);
	}
	(void) memcpy(to->md_data, from->md_data, sizeof (MD5_CTX));
	return (1);
}


#ifndef OPENSSL_NO_SHA
/*
 * SHA1 functions
 */
static int
t4_digest_init_sha1(EVP_MD_CTX *ctx)
{
	SHA1_CTX	*sha1_ctx = (SHA1_CTX *)ctx->md_data;

	sha1_ctx->state[0] = 0x67452301U;
	sha1_ctx->state[1] = 0xefcdab89U;
	sha1_ctx->state[2] = 0x98badcfeU;
	sha1_ctx->state[3] = 0x10325476U;
	sha1_ctx->state[4] = 0xc3d2e1f0U;
	sha1_ctx->count[0] = sha1_ctx->count[1] = 0;

	return (1);
}


/*
 * Continue a SHA1 digest operation, using the message block to update the
 * context.
 */
static int
t4_digest_update_sha1(EVP_MD_CTX *ctx, const void *data, size_t count)
{
	SHA1_CTX	*sha1_ctx = (SHA1_CTX *)ctx->md_data;
	size_t	  i;
	uint32_t	buf_index, remaining_len;
	const uint32_t	buf_limit = 64;
	const uint8_t   *input = data;
	size_t	  block_count;

	if (count == 0)
		return (1);

	/* compute number of bytes mod 64 */
	buf_index = (sha1_ctx->count[1] >> 3) & 0x3F;

	/* update number of bits */
	if ((sha1_ctx->count[1] += (count << 3)) < (count << 3))
		sha1_ctx->count[0]++;

	sha1_ctx->count[0] += (count >> 29);

	remaining_len = buf_limit - buf_index;

	i = 0;
	if (count >= remaining_len) {
		if (buf_index) {
			(void) memcpy(&sha1_ctx->buf_un.buf8[buf_index], input,
			    remaining_len);

			t4_sha1_multiblock(sha1_ctx, sha1_ctx->buf_un.buf8, 1);
			i = remaining_len;
		}

		block_count = (count - i) >> 6;
		if (block_count > 0) {
			t4_sha1_multiblock(sha1_ctx, &input[i], block_count);
			i += block_count << 6;
		}

		if (count == i)
			return (1);

		buf_index = 0;
	}

	/* buffer remaining input */
	(void) memcpy(&sha1_ctx->buf_un.buf8[buf_index], &input[i], count - i);

	return (1);
}


/* Convert numbers from little endian to big endian for SHA1/SHA384/SHA256. */
static void
t4_sha1_256_encode(uint8_t *restrict output,
    const uint32_t *restrict input, size_t len)
{
	size_t		i, j;

	if (IS_P2ALIGNED(output, sizeof (uint32_t))) {
		for (i = 0, j = 0; j < len; i++, j += sizeof (uint32_t)) {
			/* LINTED E_BAD_PTR_CAST_ALIGN */
			*((uint32_t *)(output + j)) = htonl(input[i]);
		}
	} else { /* Big and little endian independent, but slower */
		for (i = 0, j = 0; j < len; i++, j += 4) {
			output[j]	= (input[i] >> 24) & 0xff;
			output[j + 1]	= (input[i] >> 16) & 0xff;
			output[j + 2]	= (input[i] >>  8) & 0xff;
			output[j + 3]	= input[i] & 0xff;
		}
	}
}


/* End SHA1 digest operation, finalizing message digest and zeroing context. */
static int
t4_digest_final_sha1(EVP_MD_CTX *ctx, unsigned char *md)
{
	SHA1_CTX		*sha1_ctx = (SHA1_CTX *)ctx->md_data;
	uint8_t			bitcount_be[sizeof (sha1_ctx->count)];
	uint32_t		index = (sha1_ctx->count[1] >> 3) & 0x3f;

	/* store bit count, big endian */
	t4_sha1_256_encode(bitcount_be, sha1_ctx->count, sizeof (bitcount_be));

	/* pad out to 56 mod 64 */
	(void) t4_digest_update_sha1(ctx, PADDING,
	    ((index < 56) ? 56 : 120) - index);

	/* append length (before padding) */
	(void) t4_digest_update_sha1(ctx, bitcount_be, sizeof (bitcount_be));

	/* store state in digest */
	t4_sha1_256_encode(md, sha1_ctx->state, sizeof (sha1_ctx->state));

	/* zeroize sensitive information */
	(void) memset(sha1_ctx, 0, sizeof (*sha1_ctx));

	return (1);
}


static int
t4_digest_copy_sha1(EVP_MD_CTX *to, const EVP_MD_CTX *from)
{
	if ((to->md_data == NULL) || (from->md_data == NULL)) {
		return (1);
	}
	(void) memcpy(to->md_data, from->md_data, sizeof (SHA1_CTX));
	return (1);
}
#endif	/* !OPENSSL_NO_SHA */


#ifndef OPENSSL_NO_SHA
/* SHA2 (SHA256/SHA512) functions */
static int
t4_digest_copy_sha2(EVP_MD_CTX *to, const EVP_MD_CTX *from)
{
	if ((to->md_data == NULL) || (from->md_data == NULL)) {
		return (1);
	}
	(void) memcpy(to->md_data, from->md_data, sizeof (SHA2_CTX));
	return (1);
}


/* Convert numbers from little endian to big endian for SHA384/SHA512. */
static void t4_sha512_encode64(uint8_t *restrict output,
    const uint64_t *restrict input, size_t len)
{
	size_t		i, j;

	if (IS_P2ALIGNED(output, sizeof (uint64_t))) {
		for (i = 0, j = 0; j < len; i++, j += sizeof (uint64_t)) {
			/* LINTED E_BAD_PTR_CAST_ALIGN */
			*((uint64_t *)(output + j)) = htonll(input[i]);
		}
	} else { /* Big and little endian independent, but slower */
		for (i = 0, j = 0; j < len; i++, j += 8) {
			output[j]	= (input[i] >> 56) & 0xff;
			output[j + 1]	= (input[i] >> 48) & 0xff;
			output[j + 2]	= (input[i] >> 40) & 0xff;
			output[j + 3]	= (input[i] >> 32) & 0xff;
			output[j + 4]	= (input[i] >> 24) & 0xff;
			output[j + 5]	= (input[i] >> 16) & 0xff;
			output[j + 6]	= (input[i] >>  8) & 0xff;
			output[j + 7]	= input[i] & 0xff;
		}
	}
}


/*
 * SHA256 functions
 */
static int
t4_digest_init_sha256(EVP_MD_CTX *ctx)
{
	SHA2_CTX	*sha2_ctx = (SHA2_CTX *)ctx->md_data;

	sha2_ctx->algotype = SHA256_MECH_INFO_TYPE;
	sha2_ctx->state.s32[0] = 0x6a09e667U;
	sha2_ctx->state.s32[1] = 0xbb67ae85U;
	sha2_ctx->state.s32[2] = 0x3c6ef372U;
	sha2_ctx->state.s32[3] = 0xa54ff53aU;
	sha2_ctx->state.s32[4] = 0x510e527fU;
	sha2_ctx->state.s32[5] = 0x9b05688cU;
	sha2_ctx->state.s32[6] = 0x1f83d9abU;
	sha2_ctx->state.s32[7] = 0x5be0cd19U;
	sha2_ctx->count.c64[0] = sha2_ctx->count.c64[1] = 0;

	return (1);
}


/*
 * Continue a SHA256 digest operation, using the message block to update the
 * context.
 */
static int
t4_digest_update_sha256(EVP_MD_CTX *ctx, const void *data, size_t count)
{
	SHA2_CTX	*sha2_ctx = (SHA2_CTX *)ctx->md_data;
	size_t		i;
	uint32_t	buf_index, remaining_len;
	const uint32_t	buf_limit = 64;
	const uint8_t	*input = data;
	size_t		block_count;

	if (count == 0)
		return (1);

	/* compute number of bytes mod 64 */
	buf_index = (sha2_ctx->count.c32[1] >> 3) & 0x3F;

	/* update number of bits */
	if ((sha2_ctx->count.c32[1] += (count << 3)) < (count << 3))
		sha2_ctx->count.c32[0]++;

	sha2_ctx->count.c32[0] += (count >> 29);

	remaining_len = buf_limit - buf_index;

	i = 0;
	if (count >= remaining_len) {
		if (buf_index) {
			(void) memcpy(&sha2_ctx->buf_un.buf8[buf_index], input,
			    remaining_len);
			t4_sha256_multiblock(sha2_ctx, sha2_ctx->buf_un.buf8,
			    1);
			i = remaining_len;
		}

		block_count = (count - i) >> 6;
		if (block_count > 0) {
			t4_sha256_multiblock(sha2_ctx, &input[i], block_count);
			i += block_count << 6;
		}

		if (count == i)
			return (1);

		buf_index = 0;
	}

	/* buffer remaining input */
	(void) memcpy(&sha2_ctx->buf_un.buf8[buf_index], &input[i], count - i);
	return (1);
}


/* End SHA256 digest operation, finalizing message digest and zeroing context */
static int
t4_digest_final_sha256(EVP_MD_CTX *ctx, unsigned char *md)
{
	SHA2_CTX	*sha2_ctx = (SHA2_CTX *)ctx->md_data;
	uint8_t		bitcount_be[sizeof (sha2_ctx->count.c32)];
	uint32_t	index  = (sha2_ctx->count.c32[1] >> 3) & 0x3f;

	t4_sha1_256_encode(bitcount_be, sha2_ctx->count.c32,
	    sizeof (bitcount_be));
	(void) t4_digest_update_sha256(ctx, PADDING,
	    ((index < 56) ? 56 : 120) - index);
	(void) t4_digest_update_sha256(ctx, bitcount_be, sizeof (bitcount_be));
	t4_sha1_256_encode(md, sha2_ctx->state.s32,
	    sizeof (sha2_ctx->state.s32));

	/* zeroize sensitive information */
	(void) memset(sha2_ctx, 0, sizeof (*sha2_ctx));

	return (1);
}


/*
 * SHA512 functions
 */
static int
t4_digest_init_sha512(EVP_MD_CTX *ctx)
{
	SHA2_CTX	*sha2_ctx = (SHA2_CTX *)ctx->md_data;

	sha2_ctx->algotype = SHA512_MECH_INFO_TYPE;
	sha2_ctx->state.s64[0] = 0x6a09e667f3bcc908ULL;
	sha2_ctx->state.s64[1] = 0xbb67ae8584caa73bULL;
	sha2_ctx->state.s64[2] = 0x3c6ef372fe94f82bULL;
	sha2_ctx->state.s64[3] = 0xa54ff53a5f1d36f1ULL;
	sha2_ctx->state.s64[4] = 0x510e527fade682d1ULL;
	sha2_ctx->state.s64[5] = 0x9b05688c2b3e6c1fULL;
	sha2_ctx->state.s64[6] = 0x1f83d9abfb41bd6bULL;
	sha2_ctx->state.s64[7] = 0x5be0cd19137e2179ULL;
	sha2_ctx->count.c64[0] = sha2_ctx->count.c64[1] = 0;

	return (1);
}


/*
 * Continue a SHA512 digest operation, using the message block to update the
 * context.
 */
static int
t4_digest_update_sha512(EVP_MD_CTX *ctx, const void *data, size_t count)
{
	SHA2_CTX	*sha2_ctx = (SHA2_CTX *)ctx->md_data;
	size_t		i;
	uint32_t	buf_index, remaining_len;
	const uint32_t	buf_limit = 128;
	const uint8_t	*input = data;
	size_t		block_count;

	if (count == 0)
		return (1);

	/* compute number of bytes mod 128 */
	buf_index = (sha2_ctx->count.c64[1] >> 3) & 0x7F;

	/* update numb-g -xer of bits */
	if ((sha2_ctx->count.c64[1] += (count << 3)) < (count << 3))
		sha2_ctx->count.c64[0]++;

	sha2_ctx->count.c64[0] += (count >> 29);

	remaining_len = buf_limit - buf_index;

	i = 0;
	if (count >= remaining_len) {
		if (buf_index) {
			(void) memcpy(&sha2_ctx->buf_un.buf8[buf_index], input,
			    remaining_len);
			t4_sha512_multiblock(sha2_ctx, sha2_ctx->buf_un.buf8,
			    1);
			i = remaining_len;
		}

		block_count = (count - i) >> 7;
		if (block_count > 0) {
			t4_sha512_multiblock(sha2_ctx, &input[i], block_count);
			i += block_count << 7;
		}

		if (count == i)
			return (1);

		buf_index = 0;
	}

	/* buffer remaining input */
	(void) memcpy(&sha2_ctx->buf_un.buf8[buf_index], &input[i], count - i);
	return (1);
}


/* End SHA512 digest operation, finalizing message digest and zeroing context */
static int
t4_digest_final_sha512(EVP_MD_CTX *ctx, unsigned char *md)
{
	SHA2_CTX	*sha2_ctx = (SHA2_CTX *)ctx->md_data;
	uint8_t		bitcount_be64[sizeof (sha2_ctx->count.c64)];
	uint32_t	index  = (sha2_ctx->count.c64[1] >> 3) & 0x7f;

	t4_sha512_encode64(bitcount_be64, sha2_ctx->count.c64,
	    sizeof (bitcount_be64));
	(void) t4_digest_update_sha512(ctx, PADDING,
	    ((index < 112) ? 112 : 240) - index);
	(void) t4_digest_update_sha512(ctx, bitcount_be64,
	    sizeof (bitcount_be64));
	t4_sha512_encode64(md, sha2_ctx->state.s64,
	    sizeof (sha2_ctx->state.s64));

	/* zeroize sensitive information */
	(void) memset(sha2_ctx, 0, sizeof (*sha2_ctx));

	return (1);
}

#endif	/* !OPENSSL_NO_SHA */
#endif	/* COMPILE_HW_T4 */
#endif	/* !OPENSSL_NO_HW && !OPENSSL_NO_HW_MD_T4 */
