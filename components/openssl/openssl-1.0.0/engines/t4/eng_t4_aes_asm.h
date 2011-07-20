/*
 * CDDL HEADER START
 *
 * The contents of this file are subject to the terms of the
 * Common Development and Distribution License (the "License").
 * You may not use this file except in compliance with the License.
 *
 * You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
 * or http://www.opensolaris.org/os/licensing.
 * See the License for the specific language governing permissions
 * and limitations under the License.
 *
 * When distributing Covered Code, include this CDDL HEADER in each
 * file and include the License file at usr/src/OPENSOLARIS.LICENSE.
 * If applicable, add the following below this CDDL HEADER, with the
 * fields enclosed by brackets "[]" replaced with your own identifying
 * information: Portions Copyright [yyyy] [name of copyright owner]
 *
 * CDDL HEADER END
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
