/*
 * This product includes cryptographic software developed by the OpenSSL
 * Project for use in the OpenSSL Toolkit (http://www.openssl.org/).
 */

/*
 * ====================================================================
 * Copyright (c) 1999-2011 The OpenSSL Project.  All rights reserved.
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
 *    for use in the OpenSSL Toolkit. (http://www.OpenSSL.org/)"
 *
 * 4. The names "OpenSSL Toolkit" and "OpenSSL Project" must not be used to
 *    endorse or promote products derived from this software without
 *    prior written permission. For written permission, please contact
 *    licensing@OpenSSL.org.
 *
 * 5. Products derived from this software may not be called "OpenSSL"
 *    nor may "OpenSSL" appear in their names without prior written
 *    permission of the OpenSSL Project.
 *
 * 6. Redistributions of any form whatsoever must retain the following
 *    acknowledgment:
 *    "This product includes software developed by the OpenSSL Project
 *    for use in the OpenSSL Toolkit (http://www.OpenSSL.org/)"
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
 * This file implements the RSA, DSA, and DH operations.
 */

#include <openssl/opensslconf.h>

#define	BIGNUM SOLARIS_BIGNUM
#include "eng_t4_bignum.h"
#undef BIGNUM


#if !defined(OPENSSL_NO_HW) && !defined(OPENSSL_NO_HW_MONTMUL_T4)
#include <sys/types.h>
#include <sys/auxv.h>		/* getisax() */
#include <sys/sysmacros.h>	/* IS_P2ALIGNED() */
#include <sys/byteorder.h>	/* htonl() and friends */
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

#ifndef OPENSSL_NO_RSA
#include <openssl/rsa.h>
#endif	/* !OPENSSL_NO_RSA */

#ifndef OPENSSL_NO_DSA
#include <openssl/dsa.h>
#endif	/* !OPENSSL_NO_DSA */

#ifndef OPENSSL_NO_DH
#include <openssl/dh.h>
#endif	/* !OPENSSL_NO_DH */

#include <openssl/bio.h>
#include <openssl/aes.h>
#include <openssl/engine.h>

#if (defined(sun4v) || defined(__sparcv9) || defined(__sparcv8plus) || \
	defined(__sparcv8)) && !defined(OPENSSL_NO_ASM)
#define	COMPILE_HW_T4
#endif

#ifdef	COMPILE_HW_T4

#if !(defined(OPENSSL_NO_RSA) && defined(OPENSSL_NO_DSA) && \
	defined(OPENSSL_NO_DH))


/*
 * Convert OpenSSL's BIGNUM to Solaris's BIGNUM....
 * It assumes that the Solaris BIGNUM has enough space
 */
static void
bn2solbn(const BIGNUM *src, SOLARIS_BIGNUM *dst)
{
	int	i, j;

	if (BN_BITS2 < BIG_CHUNK_SIZE) {
		for (i = 0, j = 0; i < src->top; i++) {
			if ((i & 1) == 0) {
				dst->value[j] = src->d[i];
			} else {
				dst->value[j] += ((uint64_t)(src->d[i])) << 32;
				j++;
			}
		}
		dst->len = (src->top + 1) / 2;
		dst->sign = (src->neg == 1) ? -1 : 1;
	} else if (BN_BITS2 == BIG_CHUNK_SIZE) {
		(void) memcpy(dst->value, src->d, src->top);
		dst->len = src->top;
		dst->sign = (src->neg == 1) ? -1 : 1;
	} else { /* BN_BITS2 > BIG_CHUNK_SIZE */
		for (i = 0, j = 0; i < src->top; i++) {
			dst->value[j++] = src->d[i] & 0xffffffffULL;
			dst->value[j++] = ((uint64_t)(src->d[i])) >> 32;
		}
		dst->len = src->top * 2;
		if (dst->value[dst->len - 1] == 0) {
			dst->len--;
		}
		dst->sign = (src->neg == 1) ? -1 : 1;
	}
}

/*
 * It assumes that OpenSSL's BIGNUM has enough space.
 */
static void
solbn2bn(const SOLARIS_BIGNUM *src, BIGNUM *dst)
{
	int	i, j;

	if (BN_BITS2 < BIG_CHUNK_SIZE) {
		for (i = 0, j = 0; i < src->len; i++) {
			dst->d[j++] = src->value[i] & 0xffffffffULL;
			dst->d[j++] = ((uint64_t)(src->value[i])) >> 32;
		}
		dst->top = src->len * 2;
		if (dst->d[dst->top - 1] == 0) {
			dst->top--;
		}
		dst->neg = (src->sign == -1) ? 1 : 0;
	} else if (BN_BITS2 == BIG_CHUNK_SIZE) {
		(void) memcpy(src->value, dst->d, src->len);
		dst->top = src->len;
		dst->neg = (src->sign == -1) ? 1 : 0;
	} else { /* BN_BITS2 > BIG_CHUNK_SIZE */
		for (i = 0, j = 0; i < src->len; i++) {
			if ((i & 1) == 0) {
				dst->d[j] = src->value[i];
			} else {
				dst->d[j] += ((uint64_t)(src->value[i])) << 32;
				j++;
			}
		}
		dst->top = (src->len + 1) / 2;
		dst->neg =  (src->sign == -1) ? 1 : 0;
	}
}



static int
t4_bn_mod_exp(BIGNUM *r, const BIGNUM *a, const BIGNUM *p, const BIGNUM *m,
    BN_CTX *ctx, BN_MONT_CTX *m_ctx)
{
	int		rv = 0;
	SOLARIS_BIGNUM	sol_r = {0};
	SOLARIS_BIGNUM	sol_a = {0};
	SOLARIS_BIGNUM	sol_p = {0};
	SOLARIS_BIGNUM	sol_m = {0};

	if (big_init(&sol_r, (m->top + 3) * BN_BITS2 / BIG_CHUNK_SIZE) !=
	    BIG_OK) {
		goto cleanup;
	}
	if (big_init(&sol_a, (a->top + 1) * BN_BITS2 / BIG_CHUNK_SIZE) !=
	    BIG_OK) {
		goto cleanup;
	}
	if (big_init(&sol_p, (p->top + 1) * BN_BITS2 / BIG_CHUNK_SIZE) !=
	    BIG_OK) {
		goto cleanup;
	}
	if (big_init(&sol_m, (m->top + 1) * BN_BITS2 / BIG_CHUNK_SIZE) !=
	    BIG_OK) {
		goto cleanup;
	}

	bn2solbn(a, &sol_a);
	bn2solbn(p, &sol_p);
	bn2solbn(m, &sol_m);

	/* calls libsoftcrypto's big_modexp() routine */
	if (big_modexp(&sol_r, &sol_a, &sol_p, &sol_m, NULL) != BIG_OK) {
		goto cleanup;
	}

	if (bn_wexpand(r, m->top + 2) == NULL) {
		goto cleanup;
	}
	solbn2bn(&sol_r, r);

	rv = 1;

cleanup:

	big_finish(&sol_m);
	big_finish(&sol_p);
	big_finish(&sol_a);
	big_finish(&sol_r);

	return (rv);
}

#endif	/* !(OPENSSL_NO_RSA && OPENSSL_NO_DSA) */

#ifndef OPENSSL_NO_RSA

/* Our internal RSA_METHOD that we provide pointers to */
static RSA_METHOD t4_rsa =
{
	"Oracle T4 RSA method",
	NULL,			/* rsa_pub_encrypt */
	NULL,			/* rsa_pub_decrypt */
	NULL,			/* rsa_priv_encrypt */
	NULL,			/* rsa_priv_decrypt */
	NULL,			/* rsa_mod_exp */
	t4_bn_mod_exp,		/* bn_mod_exp */
	NULL,			/* init */
	NULL,			/* finish */
	RSA_FLAG_CACHE_PUBLIC | RSA_FLAG_CACHE_PRIVATE | RSA_FLAG_NO_BLINDING,
				/* flags  */
	NULL,			/* app_data */
	NULL,			/* rsa_sign */
	NULL,			/* rsa_verify */
	/* Internal rsa_keygen will be used if this is NULL. */
	NULL			/* rsa_keygen */
};

RSA_METHOD *
t4_RSA(void)
{
	const RSA_METHOD *meth1;

	meth1 = RSA_PKCS1_SSLeay();
	t4_rsa.rsa_pub_enc = meth1->rsa_pub_enc;
	t4_rsa.rsa_pub_dec = meth1->rsa_pub_dec;
	t4_rsa.rsa_priv_enc = meth1->rsa_priv_enc;
	t4_rsa.rsa_priv_dec = meth1->rsa_priv_dec;
	t4_rsa.rsa_mod_exp = meth1->rsa_mod_exp;
	t4_rsa.finish = meth1->finish;

	return (&t4_rsa);
}

#endif /* !OPENSSL_NO_RSA */


#ifndef OPENSSL_NO_DSA

static int
t4_dsa_bn_mod_exp(DSA *dsa, BIGNUM *r, BIGNUM *a, const BIGNUM *p,
    const BIGNUM *m, BN_CTX *ctx, BN_MONT_CTX *m_ctx)
{
	return (t4_bn_mod_exp(r, a, p, m, ctx, m_ctx));
}


static int
t4_dsa_mod_exp(DSA *dsa, BIGNUM *rr, BIGNUM *a1, BIGNUM *p1,
    BIGNUM *a2, BIGNUM *p2, BIGNUM *m, BN_CTX *ctx, BN_MONT_CTX *in_mont)
{
	int		rv = 0;
	SOLARIS_BIGNUM	sol_rr = {0};
	SOLARIS_BIGNUM	sol_a1 = {0};
	SOLARIS_BIGNUM	sol_p1 = {0};
	SOLARIS_BIGNUM	sol_a2 = {0};
	SOLARIS_BIGNUM	sol_p2 = {0};
	SOLARIS_BIGNUM	sol_m = {0};
	SOLARIS_BIGNUM	sol_tmp = {0};

	if (big_init(&sol_rr, (m->top + 3) * BN_BITS2 / BIG_CHUNK_SIZE) !=
	    BIG_OK) {
		goto cleanup;
	}
	if (big_init(&sol_a1, (a1->top + 1) * BN_BITS2 / BIG_CHUNK_SIZE) !=
	    BIG_OK) {
		goto cleanup;
	}
	if (big_init(&sol_p1, (p1->top + 1) * BN_BITS2 / BIG_CHUNK_SIZE) !=
	    BIG_OK) {
		goto cleanup;
	}
	if (big_init(&sol_a2, (a2->top + 1) * BN_BITS2 / BIG_CHUNK_SIZE) !=
	    BIG_OK) {
		goto cleanup;
	}
	if (big_init(&sol_p2, (p2->top + 1) * BN_BITS2 / BIG_CHUNK_SIZE) !=
	    BIG_OK) {
		goto cleanup;
	}
	if (big_init(&sol_m, (m->top + 1) * BN_BITS2 / BIG_CHUNK_SIZE) !=
	    BIG_OK) {
		goto cleanup;
	}
	if (big_init(&sol_tmp, 2 * sol_m.len + 1) != BIG_OK) {
		goto cleanup;
	}

	if (big_init(&sol_tmp, 2 * sol_m.len + 1) != BIG_OK) {
		goto cleanup;
	}

	bn2solbn(a1, &sol_a1);
	bn2solbn(p1, &sol_p1);
	bn2solbn(a2, &sol_a2);
	bn2solbn(p2, &sol_p2);
	bn2solbn(m, &sol_m);


	/* calls libsoftcrypto's big_modexp() routine */
	if (big_modexp(&sol_rr, &sol_a1, &sol_p1, &sol_m, NULL) !=
	    BIG_OK) {
		goto cleanup;
	}

	if (big_modexp(&sol_tmp, &sol_a2, &sol_p2, &sol_m, NULL) !=
	    BIG_OK) {
		goto cleanup;
	}

	if (big_mul(&sol_tmp, &sol_rr, &sol_tmp) != BIG_OK) {
		goto cleanup;
	}

	if (big_div_pos(NULL, &sol_rr, &sol_tmp, &sol_m) != BIG_OK) {
		goto cleanup;
	}

	if (bn_wexpand(rr, m->top + 2) == NULL) {
		goto cleanup;
	}
	solbn2bn(&sol_rr, rr);

	rv = 1;

cleanup:

	big_finish(&sol_tmp);
	big_finish(&sol_m);
	big_finish(&sol_p2);
	big_finish(&sol_a2);
	big_finish(&sol_p1);
	big_finish(&sol_a1);
	big_finish(&sol_rr);

	return (rv);
}

/* Our internal DSA_METHOD that we provide pointers to */
static DSA_METHOD t4_dsa =
{
	"Oracle T4 DSA method",	/* name */
	NULL,			/* dsa_do_sign */
	NULL,			/* dsa_sign_setup */
	NULL,			/* dsa_do_verify */
	t4_dsa_mod_exp,		/* dsa_mod_exp, */
	t4_dsa_bn_mod_exp,	/* bn_mod_exp, */
	NULL,			/* init */
	NULL,			/* finish */
	NULL,			/* flags */
	NULL,			/* app_data */
	NULL,			/* dsa_paramgen */
	NULL			/* dsa_keygen */
};

DSA_METHOD *
t4_DSA(void)
{
	const DSA_METHOD *meth1;

	meth1 = DSA_OpenSSL();
	t4_dsa.dsa_do_sign = meth1->dsa_do_sign;
	t4_dsa.dsa_sign_setup = meth1->dsa_sign_setup;
	t4_dsa.dsa_do_verify = meth1->dsa_do_verify;
	t4_dsa.finish = meth1->finish;

	return (&t4_dsa);
}

#endif /* !OPENSSL_NO_DSA */


#ifndef OPENSSL_NO_DH

static int
t4_dh_bn_mod_exp(const DH *dh, BIGNUM *r, const BIGNUM *a, const BIGNUM *p,
    const BIGNUM *m, BN_CTX *ctx, BN_MONT_CTX *m_ctx)
{
	return (t4_bn_mod_exp(r, a, p, m, ctx, m_ctx));
}



/* Our internal DH_METHOD that we provide pointers to */
static DH_METHOD t4_dh =
{
	"Oracle T4 DH method",	/* name */
	NULL,			/* generate_key */
	NULL,			/* compute_key */
	t4_dh_bn_mod_exp,	/* bn_mod_exp, */
	NULL,			/* init */
	NULL,			/* finish */
	NULL,			/* flags */
	NULL			/* app_data */
};

DH_METHOD *
t4_DH(void)
{
	const DH_METHOD *meth1;

	meth1 = DH_OpenSSL();
	t4_dh.generate_key = meth1->generate_key;
	t4_dh.compute_key = meth1->compute_key;
	t4_dh.finish = meth1->finish;

	return (&t4_dh);
}

#endif /* !OPENSSL_NO_DH */

#endif	/* COMPILE_HW_T4 */

#endif	/* !OPENSSL_NO_HW && !OPENSSL_NO_HW_MONTMUL_T4 */
