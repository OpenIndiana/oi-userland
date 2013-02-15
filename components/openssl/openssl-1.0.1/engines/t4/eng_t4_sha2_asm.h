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

#ifndef	ENG_T4_SHA2_ASM_H
#define	ENG_T4_SHA2_ASM_H

/*
 * SPARC T4 SHA2 (SHA256/SHA512) assembly language functions and context.
 * The context must match that used by the Solaris SPARC T4 assembly
 * (except for OpenSSL-specific fields num and md_len that aren't in Solaris).
 *
 * Based on OpenSSL file openssl/sha.h and Solaris file sys/sha2.h.
 */

#include <stddef.h>
#include <sys/types.h>
#include <openssl/sha.h>

#ifdef	__cplusplus
extern "C" {
#endif

#ifndef OPENSSL_NO_SHA256
/*
 * The contents of this structure are a private interface between the
 * Init/Update/Multiblock/Final functions.
 * Callers must never attempt to read or write any of the fields
 * in this structure directly.
 */
typedef struct t4_SHA256state_st {
	uint32_t algotype;		/* Solaris-only field; unused here */
	uint32_t algotype_pad;		/* Pad to align next field 0 mod 8 */
	uint32_t h[8];			/* State (ABCDEFGH) */
	uint32_t h_pad[8];		/* Pad fields to match T4_SHA512_CTX */
	uint32_t Nl, Nh;		/* Number of bits, module 2^64 */
	uint32_t Nl_pad, Nh_pad;	/* Pad fields to match T4_SHA512_CTX */
	uint32_t data[SHA_LBLOCK];	/* Input */
	unsigned int num, md_len;	/* Fields unused by Solaris assembly */
} T4_SHA256_CTX;
#endif	/* !OPENSSL_NO_SHA256 */


#ifndef OPENSSL_NO_SHA512
/*
 * The contents of this structure are a private interface between the
 * Init/Update/Multiblock/Final functions.
 * Callers must never attempt to read or write any of the fields
 * in this structure directly.
 */
typedef struct t4_SHA512state_st {
	uint32_t algotype;		/* Solaris-only field; unused here */
	uint64_t h[8];			/* State (ABCDEFGH) */
	uint64_t Nl, Nh;		/* Number of bits, module 2^128 */
	union {
		uint64_t	d[SHA_LBLOCK];
		unsigned char	p[SHA512_CBLOCK];
	} u;				/* Input */
	unsigned int num, md_len;	/* Fields unused by Solaris assembly */
} T4_SHA512_CTX;
#endif	/* !OPENSSL_NO_SHA512 */

/*
 * SPARC T4 assembly language functions
 */
#ifndef	OPENSSL_NO_SHA256
extern void t4_sha256_multiblock(T4_SHA256_CTX *c, const void *input,
	size_t num);
#endif
#ifndef	OPENSSL_NO_SHA512
extern void t4_sha512_multiblock(T4_SHA512_CTX *c, const void *input,
	size_t num);
#endif

#ifdef	__cplusplus
}
#endif
#endif	/* ENG_T4_SHA2_ASM_H */
