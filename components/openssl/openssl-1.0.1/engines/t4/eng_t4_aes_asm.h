/*
 * This product includes cryptographic software developed by the OpenSSL
 * Project for use in the OpenSSL Toolkit (http://www.openssl.org/).
 */

/*
 * ====================================================================
 * Copyright (c) 1999-2007 The OpenSSL Project.  All rights reserved.
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

#ifndef	ENG_T4_AES_ASM_H
#define	ENG_T4_AES_ASM_H

/*
 * SPARC AES assembly language functions.
 *
 * Based on Solaris file aes_impl.h.
 */

#ifdef	__cplusplus
extern "C" {
#endif

#include <sys/types.h>

#if (defined(sun4v) || defined(__sparcv9) || defined(__sparcv8plus) || \
	defined(__sparcv8)) && ! defined(OPENSSL_NO_ASM)

extern void t4_aes_expand128(uint64_t *rk, const uint32_t *key);
extern void t4_aes_expand192(uint64_t *rk, const uint32_t *key);
extern void t4_aes_expand256(uint64_t *rk, const uint32_t *key);
extern void t4_aes_encrypt128(const uint64_t *rk, const uint32_t *pt,
    uint32_t *ct);
extern void t4_aes_encrypt192(const uint64_t *rk, const uint32_t *pt,
    uint32_t *ct);
extern void t4_aes_encrypt256(const uint64_t *rk, const uint32_t *pt,
    uint32_t *ct);
extern void t4_aes_decrypt128(const uint64_t *rk, const uint32_t *ct,
    uint32_t *pt);
extern void t4_aes_decrypt192(const uint64_t *rk, const uint32_t *ct,
    uint32_t *pt);
extern void t4_aes_decrypt256(const uint64_t *rk, const uint32_t *ct,
    uint32_t *pt);
extern void t4_aes128_load_keys_for_encrypt(uint64_t *ks);
extern void t4_aes192_load_keys_for_encrypt(uint64_t *ks);
extern void t4_aes256_load_keys_for_encrypt(uint64_t *ks);
extern void t4_aes128_ecb_encrypt(uint64_t *ks, uint64_t *asm_in,
    uint64_t *asm_out, size_t amount_to_encrypt, uint64_t *dummy);
extern void t4_aes192_ecb_encrypt(uint64_t *ks, uint64_t *asm_in,
    uint64_t *asm_out, size_t amount_to_encrypt, uint64_t *dummy);
extern void t4_aes256_ecb_encrypt(uint64_t *ks, uint64_t *asm_in,
    uint64_t *asm_out, size_t amount_to_encrypt, uint64_t *dummy);
extern void t4_aes128_cbc_encrypt(uint64_t *ks, uint64_t *asm_in,
    uint64_t *asm_out, size_t amount_to_encrypt, uint64_t *iv);
extern void t4_aes192_cbc_encrypt(uint64_t *ks, uint64_t *asm_in,
    uint64_t *asm_out, size_t amount_to_encrypt, uint64_t *iv);
extern void t4_aes256_cbc_encrypt(uint64_t *ks, uint64_t *asm_in,
    uint64_t *asm_out, size_t amount_to_encrypt, uint64_t *iv);
extern void t4_aes128_ctr_crypt(uint64_t *ks, uint64_t *asm_in,
    uint64_t *asm_out, size_t amount_to_encrypt, uint64_t *iv);
extern void t4_aes192_ctr_crypt(uint64_t *ks, uint64_t *asm_in,
    uint64_t *asm_out, size_t amount_to_encrypt, uint64_t *iv);
extern void t4_aes256_ctr_crypt(uint64_t *ks, uint64_t *asm_in,
    uint64_t *asm_out, size_t amount_to_encrypt, uint64_t *iv);
extern void t4_aes128_cfb128_encrypt(uint64_t *ks, uint64_t *asm_in,
    uint64_t *asm_out, size_t amount_to_encrypt, uint64_t *iv);
extern void t4_aes192_cfb128_encrypt(uint64_t *ks, uint64_t *asm_in,
    uint64_t *asm_out, size_t amount_to_encrypt, uint64_t *iv);
extern void t4_aes256_cfb128_encrypt(uint64_t *ks, uint64_t *asm_in,
    uint64_t *asm_out, size_t amount_to_encrypt, uint64_t *iv);
extern void t4_aes128_load_keys_for_decrypt(uint64_t *ks);
extern void t4_aes192_load_keys_for_decrypt(uint64_t *ks);
extern void t4_aes256_load_keys_for_decrypt(uint64_t *ks);
extern void t4_aes128_ecb_decrypt(uint64_t *ks, uint64_t *asm_in,
    uint64_t *asm_out, size_t amount_to_decrypt, uint64_t *dummy);
extern void t4_aes192_ecb_decrypt(uint64_t *ks, uint64_t *asm_in,
    uint64_t *asm_out, size_t amount_to_decrypt, uint64_t *dummy);
extern void t4_aes256_ecb_decrypt(uint64_t *ks, uint64_t *asm_in,
    uint64_t *asm_out, size_t amount_to_decrypt, uint64_t *dummy);
extern void t4_aes128_cbc_decrypt(uint64_t *ks, uint64_t *asm_in,
    uint64_t *asm_out, size_t amount_to_decrypt, uint64_t *iv);
extern void t4_aes192_cbc_decrypt(uint64_t *ks, uint64_t *asm_in,
    uint64_t *asm_out, size_t amount_to_decrypt, uint64_t *iv);
extern void t4_aes256_cbc_decrypt(uint64_t *ks, uint64_t *asm_in,
    uint64_t *asm_out, size_t amount_to_decrypt, uint64_t *iv);
extern void t4_aes128_cfb128_decrypt(uint64_t *ks, uint64_t *asm_in,
    uint64_t *asm_out, size_t amount_to_decrypt, uint64_t *iv);
extern void t4_aes192_cfb128_decrypt(uint64_t *ks, uint64_t *asm_in,
    uint64_t *asm_out, size_t amount_to_decrypt, uint64_t *iv);
extern void t4_aes256_cfb128_decrypt(uint64_t *ks, uint64_t *asm_in,
    uint64_t *asm_out, size_t amount_to_decrypt, uint64_t *iv);

#endif	/* (sun4v||__sparv9||__sparcv8plus||__sparvc8) && !OPENSSL_NO_ASM */

#ifdef	__cplusplus
}
#endif
#endif	/* ENG_T4_AES_ASM_H */
