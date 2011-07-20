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

/*LINTLIBRARY*/

#if defined(lint) || defined(__lint)


#include <sys/types.h>

/*ARGSUSED*/
void t4_aes_expand128(uint64_t *rk, const uint32_t *key)
{ return; }

/*ARGSUSED*/
void t4_aes_expand192(uint64_t *rk, const uint32_t *key)
{ return; }

/*ARGSUSED*/
void t4_aes_expand256(uint64_t *rk, const uint32_t *key)
{ return; }

void t4_aes128_load_keys_for_encrypt(uint64_t *ks)
{ return; }

/*ARGSUSED*/
void t4_aes192_load_keys_for_encrypt(uint64_t *ks)
{ return; }

/*ARGSUSED*/
void t4_aes256_load_keys_for_encrypt(uint64_t *ks)
{ return; }

/*ARGSUSED*/
void t4_aes128_ecb_encrypt(uint64_t *ks, uint64_t *asm_in,
    uint64_t * asm_out, size_t amount_to_encrypt, uint64_t *iv)
{ return; }

/*ARGSUSED*/
void t4_aes192_ecb_encrypt(uint64_t *ks, uint64_t *asm_in,
    uint64_t * asm_out, size_t amount_to_encrypt, uint64_t *iv)
{ return; }

/*ARGSUSED*/
void t4_aes256_ecb_encrypt(uint64_t *ks, uint64_t *asm_in,
    uint64_t * asm_out, size_t amount_to_encrypt, uint64_t *iv)
{ return; }

/*ARGSUSED*/
void t4_aes128_cbc_encrypt(uint64_t *ks, uint64_t *asm_in,
    uint64_t * asm_out, size_t amount_to_encrypt, uint64_t *iv)
{ return; }

/*ARGSUSED*/
void t4_aes192_cbc_encrypt(uint64_t *ks, uint64_t *asm_in,
    uint64_t * asm_out, size_t amount_to_encrypt, uint64_t *iv)
{ return; }

/*ARGSUSED*/
void t4_aes256_cbc_encrypt(uint64_t *ks, uint64_t *asm_in,
    uint64_t * asm_out, size_t amount_to_encrypt, uint64_t *iv)
{ return; }

/*ARGSUSED*/
void t4_aes128_ctr_crypt(uint64_t *ks, uint64_t *asm_in,
    uint64_t * asm_out, size_t amount_to_encrypt, uint64_t *iv)
{ return; }

/*ARGSUSED*/
void t4_aes192_ctr_crypt(uint64_t *ks, uint64_t *asm_in,
    uint64_t * asm_out, size_t amount_to_encrypt, uint64_t *iv)
{ return; }

/*ARGSUSED*/
void t4_aes256_ctr_crypt(uint64_t *ks, uint64_t *asm_in,
    uint64_t * asm_out, size_t amount_to_encrypt, uint64_t *iv)
{ return; }

/*ARGSUSED*/
void t4_aes128_cfb128_encrypt(uint64_t *ks, uint64_t *asm_in,
    uint64_t * asm_out, size_t amount_to_encrypt, uint64_t *iv)
{ return; }

/*ARGSUSED*/
void t4_aes192_cfb128_encrypt(uint64_t *ks, uint64_t *asm_in,
    uint64_t * asm_out, size_t amount_to_encrypt, uint64_t *iv)
{ return; }

/*ARGSUSED*/
void t4_aes256_cfb128_encrypt(uint64_t *ks, uint64_t *asm_in,
    uint64_t * asm_out, size_t amount_to_encrypt, uint64_t *iv)
{ return; }

void t4_aes128_load_keys_for_decrypt(uint64_t *ks)
{ return; }

/*ARGSUSED*/
void t4_aes192_load_keys_for_decrypt(uint64_t *ks)
{ return; }

/*ARGSUSED*/
void t4_aes256_load_keys_for_decrypt(uint64_t *ks)
{ return; }

/*ARGSUSED*/
void t4_aes128_ecb_decrypt(uint64_t *ks, uint64_t *asm_in,
    uint64_t * asm_out, size_t amount_to_encrypt, uint64_t *iv)
{ return; }

/*ARGSUSED*/
void t4_aes192_ecb_decrypt(uint64_t *ks, uint64_t *asm_in,
    uint64_t * asm_out, size_t amount_to_encrypt, uint64_t *iv)
{ return; }

/*ARGSUSED*/
void t4_aes256_ecb_decrypt(uint64_t *ks, uint64_t *asm_in,
    uint64_t * asm_out, size_t amount_to_encrypt, uint64_t *iv)
{ return; }

/*ARGSUSED*/
void t4_aes128_cbc_decrypt(uint64_t *ks, uint64_t *asm_in,
    uint64_t * asm_out, size_t amount_to_encrypt, uint64_t *iv)
{ return; }

/*ARGSUSED*/
void t4_aes192_cbc_decrypt(uint64_t *ks, uint64_t *asm_in,
    uint64_t * asm_out, size_t amount_to_encrypt, uint64_t *iv)
{ return; }

/*ARGSUSED*/
void t4_aes256_cbc_decrypt(uint64_t *ks, uint64_t *asm_in,
    uint64_t * asm_out, size_t amount_to_encrypt, uint64_t *iv)
{ return; }

/*ARGSUSED*/
void t4_aes128_cfb128_decrypt(uint64_t *ks, uint64_t *asm_in,
    uint64_t * asm_out, size_t amount_to_encrypt, uint64_t *iv)
{ return; }

/*ARGSUSED*/
void t4_aes192_cfb128_decrypt(uint64_t *ks, uint64_t *asm_in,
    uint64_t * asm_out, size_t amount_to_encrypt, uint64_t *iv)
{ return; }

/*ARGSUSED*/
void t4_aes256_cfb128_decrypt(uint64_t *ks, uint64_t *asm_in,
    uint64_t * asm_out, size_t amount_to_encrypt, uint64_t *iv)
{ return; }

#else	/* lint || __lint */

#include<sys/asm_linkage.h>


	ENTRY(t4_aes_expand128)

!load key
	ld	[%o1], %f0
	ld	[%o1 + 0x4], %f1
	ld	[%o1 + 0x8], %f2
	ld	[%o1 + 0xc], %f3

!expand the key
	.byte	0x88, 0xc8, 0x01, 0x02
	.byte	0x8d, 0xb0, 0xa6, 0x24
	.byte	0x90, 0xc9, 0x03, 0x06
	.byte	0x95, 0xb1, 0xa6, 0x28
	.byte	0x98, 0xca, 0x05, 0x0a
	.byte	0x9d, 0xb2, 0xa6, 0x2c
	.byte	0xa0, 0xcb, 0x07, 0x0e
	.byte	0xa5, 0xb3, 0xa6, 0x30
	.byte	0xa8, 0xcc, 0x09, 0x12
	.byte	0xad, 0xb4, 0xa6, 0x34
	.byte	0xb0, 0xcd, 0x0b, 0x16
	.byte	0xb5, 0xb5, 0xa6, 0x38
	.byte	0xb8, 0xce, 0x0d, 0x1a
	.byte	0xbd, 0xb6, 0xa6, 0x3c
	.byte	0x82, 0xcf, 0x0f, 0x1e
	.byte	0x87, 0xb7, 0xa6, 0x21
	.byte	0x8a, 0xc8, 0x51, 0x03
	.byte	0x8f, 0xb0, 0xe6, 0x25
	.byte	0x92, 0xc9, 0x53, 0x07
	.byte	0x97, 0xb1, 0xe6, 0x29

!copy expanded key back into array
	std	%f4, [%o0]
	std	%f6, [%o0 + 0x8]
	std	%f8, [%o0 + 0x10]
	std	%f10, [%o0 + 0x18]
	std	%f12, [%o0 + 0x20]
	std	%f14, [%o0 + 0x28]
	std	%f16, [%o0 + 0x30]
	std	%f18, [%o0 + 0x38]
	std	%f20, [%o0 + 0x40]
	std	%f22, [%o0 + 0x48]
	std	%f24, [%o0 + 0x50]
	std	%f26, [%o0 + 0x58]
	std	%f28, [%o0 + 0x60]
	std	%f30, [%o0 + 0x68]
	std	%f32, [%o0 + 0x70]
	std	%f34, [%o0 + 0x78]
	std	%f36, [%o0 + 0x80]
	std	%f38, [%o0 + 0x88]
	std	%f40, [%o0 + 0x90]
	retl
	std	%f42, [%o0 + 0x98]

	SET_SIZE(t4_aes_expand128)


	ENTRY(t4_aes_expand192)

!load key
	ld	[%o1], %f0
	ld	[%o1 + 0x4], %f1
	ld	[%o1 + 0x8], %f2
	ld	[%o1 + 0xc], %f3
	ld	[%o1 + 0x10], %f4
	ld	[%o1 + 0x14], %f5

!expand the key
	.byte	0x8c, 0xc8, 0x01, 0x04
	.byte	0x91, 0xb0, 0xa6, 0x26
	.byte	0x95, 0xb1, 0x26, 0x28
	.byte	0x98, 0xc9, 0x83, 0x0a
	.byte	0x9d, 0xb2, 0x26, 0x2c
	.byte	0xa1, 0xb2, 0xa6, 0x2e
	.byte	0xa4, 0xcb, 0x05, 0x10
	.byte	0xa9, 0xb3, 0xa6, 0x32
	.byte	0xad, 0xb4, 0x26, 0x34
	.byte	0xb0, 0xcc, 0x87, 0x16
	.byte	0xb5, 0xb5, 0x26, 0x38
	.byte	0xb9, 0xb5, 0xa6, 0x3a
	.byte	0xbc, 0xce, 0x09, 0x1c
	.byte	0x83, 0xb6, 0xa6, 0x3e
	.byte	0x87, 0xb7, 0x26, 0x21
	.byte	0x8a, 0xcf, 0x8b, 0x03
	.byte	0x8f, 0xb0, 0x66, 0x25
	.byte	0x93, 0xb0, 0xe6, 0x27
	.byte	0x96, 0xc9, 0x4d, 0x09
	.byte	0x9b, 0xb1, 0xe6, 0x2b
	.byte	0x9f, 0xb2, 0x66, 0x2d
	.byte	0xa2, 0xca, 0xcf, 0x0f
	.byte	0xa7, 0xb3, 0x66, 0x31

!copy expanded key back into array
	std	%f6, [%o0]
	std	%f8, [%o0 + 0x8]
	std	%f10, [%o0 + 0x10]
	std	%f12, [%o0 + 0x18]
	std	%f14, [%o0 + 0x20]
	std	%f16, [%o0 + 0x28]
	std	%f18, [%o0 + 0x30]
	std	%f20, [%o0 + 0x38]
	std	%f22, [%o0 + 0x40]
	std	%f24, [%o0 + 0x48]
	std	%f26, [%o0 + 0x50]
	std	%f28, [%o0 + 0x58]
	std	%f30, [%o0 + 0x60]
	std	%f32, [%o0 + 0x68]
	std	%f34, [%o0 + 0x70]
	std	%f36, [%o0 + 0x78]
	std	%f38, [%o0 + 0x80]
	std	%f40, [%o0 + 0x88]
	std	%f42, [%o0 + 0x90]
	std	%f44, [%o0 + 0x98]
	std	%f46, [%o0 + 0xa0]
	std	%f48, [%o0 + 0xa8]
	retl
	std	%f50, [%o0 + 0xb0]

	SET_SIZE(t4_aes_expand192)


	ENTRY(t4_aes_expand256)

!load key
	ld	[%o1], %f0
	ld	[%o1 + 0x4], %f1
	ld	[%o1 + 0x8], %f2
	ld	[%o1 + 0xc], %f3
	ld	[%o1 + 0x10], %f4
	ld	[%o1 + 0x14], %f5
	ld	[%o1 + 0x18], %f6
	ld	[%o1 + 0x1c], %f7

!expand the key
	.byte	0x90, 0xc8, 0x01, 0x06
	.byte	0x95, 0xb0, 0xa6, 0x28
	.byte	0x99, 0xb1, 0x26, 0x0a
	.byte	0x9d, 0xb1, 0xa6, 0x2c
	.byte	0xa0, 0xca, 0x03, 0x0e
	.byte	0xa5, 0xb2, 0xa6, 0x30
	.byte	0xa9, 0xb3, 0x26, 0x12
	.byte	0xad, 0xb3, 0xa6, 0x34
	.byte	0xb0, 0xcc, 0x05, 0x16
	.byte	0xb5, 0xb4, 0xa6, 0x38
	.byte	0xb9, 0xb5, 0x26, 0x1a
	.byte	0xbd, 0xb5, 0xa6, 0x3c
	.byte	0x82, 0xce, 0x07, 0x1e
	.byte	0x87, 0xb6, 0xa6, 0x21
	.byte	0x8b, 0xb7, 0x26, 0x03
	.byte	0x8f, 0xb7, 0xa6, 0x25
	.byte	0x92, 0xc8, 0x49, 0x07
	.byte	0x97, 0xb0, 0xe6, 0x29
	.byte	0x9b, 0xb1, 0x66, 0x0b
	.byte	0x9f, 0xb1, 0xe6, 0x2d
	.byte	0xa2, 0xca, 0x4b, 0x0f
	.byte	0xa7, 0xb2, 0xe6, 0x31
	.byte	0xab, 0xb3, 0x66, 0x13
	.byte	0xaf, 0xb3, 0xe6, 0x35
	.byte	0xb2, 0xcc, 0x4d, 0x17
	.byte	0xb7, 0xb4, 0xe6, 0x39

!copy expanded key back into array
	std	%f8, [%o0]
	std	%f10, [%o0 + 0x8]
	std	%f12, [%o0 + 0x10]
	std	%f14, [%o0 + 0x18]
	std	%f16, [%o0 + 0x20]
	std	%f18, [%o0 + 0x28]
	std	%f20, [%o0 + 0x30]
	std	%f22, [%o0 + 0x38]
	std	%f24, [%o0 + 0x40]
	std	%f26, [%o0 + 0x48]
	std	%f28, [%o0 + 0x50]
	std	%f30, [%o0 + 0x58]
	std	%f32, [%o0 + 0x60]
	std	%f34, [%o0 + 0x68]
	std	%f36, [%o0 + 0x70]
	std	%f38, [%o0 + 0x78]
	std	%f40, [%o0 + 0x80]
	std	%f42, [%o0 + 0x88]
	std	%f44, [%o0 + 0x90]
	std	%f46, [%o0 + 0x98]
	std	%f48, [%o0 + 0xa0]
	std	%f50, [%o0 + 0xa8]
	std	%f52, [%o0 + 0xb0]
	std	%f54, [%o0 + 0xb8]
	std	%f56, [%o0 + 0xc0]
	retl
	std	%f58, [%o0 + 0xc8]

	SET_SIZE(t4_aes_expand256)


#define	FIRST_TWO_EROUNDS \
	.byte	0xb2, 0xc8, 0x3e, 0x1d ; \
	.byte	0xb6, 0xc8, 0xbe, 0x3d ; \
	.byte	0xba, 0xc9, 0x36, 0x19 ; \
	.byte	0xbe, 0xc9, 0xb6, 0x39

#define	MID_TWO_EROUNDS \
	.byte	0xb2, 0xca, 0x3e, 0x1d ; \
	.byte	0xb6, 0xca, 0xbe, 0x3d ; \
	.byte	0xba, 0xcb, 0x36, 0x19 ; \
	.byte	0xbe, 0xcb, 0xb6, 0x39

#define	MID_TWO_EROUNDS_2 \
	.byte	0x8c, 0xca, 0x04, 0x00 ; \
	.byte	0x88, 0xca, 0x84, 0x20 ; \
	.byte	0xb2, 0xca, 0x3e, 0x1d ; \
	.byte	0xb6, 0xca, 0xbe, 0x3d ; \
	.byte	0x80, 0xcb, 0x08, 0x06 ; \
	.byte	0x84, 0xcb, 0x88, 0x26 ; \
	.byte	0xba, 0xcb, 0x36, 0x19 ; \
	.byte	0xbe, 0xcb, 0xb6, 0x39

#define	TEN_EROUNDS \
	.byte	0xb2, 0xcc, 0x3e, 0x1d ; \
	.byte	0xb6, 0xcc, 0xbe, 0x3d ; \
	.byte	0xba, 0xcd, 0x36, 0x19 ; \
	.byte	0xbe, 0xcd, 0xb6, 0x39 ; \
	.byte	0xb2, 0xce, 0x3e, 0x1d ; \
	.byte	0xb6, 0xce, 0xbe, 0x3d ; \
	.byte	0xba, 0xcf, 0x36, 0x19 ; \
	.byte	0xbe, 0xcf, 0xb6, 0x39 ; \
	.byte	0xb2, 0xc8, 0x7e, 0x1d ; \
	.byte	0xb6, 0xc8, 0xfe, 0x3d ; \
	.byte	0xba, 0xc9, 0x76, 0x19 ; \
	.byte	0xbe, 0xc9, 0xf6, 0x39 ; \
	.byte	0xb2, 0xca, 0x7e, 0x1d ; \
	.byte	0xb6, 0xca, 0xfe, 0x3d ; \
	.byte	0xba, 0xcb, 0x76, 0x19 ; \
	.byte	0xbe, 0xcb, 0xf6, 0x39 ; \
	.byte	0xb2, 0xcc, 0x7e, 0x1d ; \
	.byte	0xb6, 0xcc, 0xfe, 0x3d ; \
	.byte	0xba, 0xcd, 0x76, 0x99 ; \
	.byte	0xbe, 0xcd, 0xf6, 0xb9

#define	TEN_EROUNDS_2 \
	.byte	0x8c, 0xcc, 0x04, 0x00 ; \
	.byte	0x88, 0xcc, 0x84, 0x20 ; \
	.byte	0xb2, 0xcc, 0x3e, 0x1d ; \
	.byte	0xb6, 0xcc, 0xbe, 0x3d ; \
	.byte	0x80, 0xcd, 0x08, 0x06 ; \
	.byte	0x84, 0xcd, 0x88, 0x26 ; \
	.byte	0xba, 0xcd, 0x36, 0x19 ; \
	.byte	0xbe, 0xcd, 0xb6, 0x39 ; \
	.byte	0x8c, 0xce, 0x04, 0x00 ; \
	.byte	0x88, 0xce, 0x84, 0x20 ; \
	.byte	0xb2, 0xce, 0x3e, 0x1d ; \
	.byte	0xb6, 0xce, 0xbe, 0x3d ; \
	.byte	0x80, 0xcf, 0x08, 0x06 ; \
	.byte	0x84, 0xcf, 0x88, 0x26 ; \
	.byte	0xba, 0xcf, 0x36, 0x19 ; \
	.byte	0xbe, 0xcf, 0xb6, 0x39 ; \
	.byte	0x8c, 0xc8, 0x44, 0x00 ; \
	.byte	0x88, 0xc8, 0xc4, 0x20 ; \
	.byte	0xb2, 0xc8, 0x7e, 0x1d ; \
	.byte	0xb6, 0xc8, 0xfe, 0x3d ; \
	.byte	0x80, 0xc9, 0x48, 0x06 ; \
	.byte	0x84, 0xc9, 0xc8, 0x26 ; \
	.byte	0xba, 0xc9, 0x76, 0x19 ; \
	.byte	0xbe, 0xc9, 0xf6, 0x39 ; \
	.byte	0x8c, 0xca, 0x44, 0x00 ; \
	.byte	0x88, 0xca, 0xc4, 0x20 ; \
	.byte	0xb2, 0xca, 0x7e, 0x1d ; \
	.byte	0xb6, 0xca, 0xfe, 0x3d ; \
	.byte	0x80, 0xcb, 0x48, 0x06 ; \
	.byte	0x84, 0xcb, 0xc8, 0x26 ; \
	.byte	0xba, 0xcb, 0x76, 0x19 ; \
	.byte	0xbe, 0xcb, 0xf6, 0x39 ; \
	.byte	0x8c, 0xcc, 0x44, 0x00 ; \
	.byte	0x88, 0xcc, 0xc4, 0x20 ; \
	.byte	0xb2, 0xcc, 0x7e, 0x1d ; \
	.byte	0xb6, 0xcc, 0xfe, 0x3d ; \
	.byte	0x80, 0xcd, 0x48, 0x86 ; \
	.byte	0x84, 0xcd, 0xc8, 0xa6 ; \
	.byte	0xba, 0xcd, 0x76, 0x99 ; \
	.byte	0xbe, 0xcd, 0xf6, 0xb9

#define	TWELVE_EROUNDS \
	MID_TWO_EROUNDS	; \
	TEN_EROUNDS

#define	TWELVE_EROUNDS_2 \
	MID_TWO_EROUNDS_2	; \
	TEN_EROUNDS_2

#define	FOURTEEN_EROUNDS \
	FIRST_TWO_EROUNDS ; \
	TWELVE_EROUNDS

#define	FOURTEEN_EROUNDS_2 \
	.byte	0xb0, 0xc8, 0x2c, 0x14 ; \
	.byte	0xac, 0xc8, 0xac, 0x34 ; \
	ldd	[%o0 + 0x60], %f20 ; \
	.byte	0xb2, 0xc8, 0x3e, 0x1d ; \
	.byte	0xb6, 0xc8, 0xbe, 0x3d ; \
	.byte	0x80, 0xc9, 0x2c, 0x18 ; \
	.byte	0x84, 0xc9, 0xac, 0x38 ;\
	ldd	[%o0 + 0x68], %f22 ; \
	.byte	0xba, 0xc9, 0x36, 0x19 ; \
	ldd	[%o0 + 0x70], %f24 ; \
	.byte	0xbe, 0xc9, 0xb6, 0x39 ; \
	.byte	0x8c, 0xca, 0x04, 0x00 ; \
	.byte	0x88, 0xca, 0x84, 0x20 ; \
	.byte	0xb2, 0xca, 0x3e, 0x1d ; \
	.byte	0xb6, 0xca, 0xbe, 0x3d ; \
	.byte	0x80, 0xcb, 0x08, 0x06 ; \
	.byte	0x84, 0xcb, 0x88, 0x26 ; \
	.byte	0xba, 0xcb, 0x36, 0x19 ; \
	.byte	0xbe, 0xcb, 0xb6, 0x39 ; \
	.byte	0x8c, 0xcc, 0x04, 0x00 ; \
	.byte	0x88, 0xcc, 0x84, 0x20 ; \
	.byte	0xb2, 0xcc, 0x3e, 0x1d ; \
	.byte	0xb6, 0xcc, 0xbe, 0x3d ; \
	.byte	0x80, 0xcd, 0x08, 0x06 ; \
	.byte	0x84, 0xcd, 0x88, 0x26 ; \
	.byte	0xba, 0xcd, 0x36, 0x19 ; \
	.byte	0xbe, 0xcd, 0xb6, 0x39 ; \
	.byte	0x8c, 0xce, 0x04, 0x00 ; \
	.byte	0x88, 0xce, 0x84, 0x20 ; \
	.byte	0xb2, 0xce, 0x3e, 0x1d ; \
	.byte	0xb6, 0xce, 0xbe, 0x3d ; \
	.byte	0x80, 0xcf, 0x08, 0x06 ; \
	.byte	0x84, 0xcf, 0x88, 0x26 ; \
	.byte	0xba, 0xcf, 0x36, 0x19 ; \
	.byte	0xbe, 0xcf, 0xb6, 0x39 ; \
	.byte	0x8c, 0xc8, 0x44, 0x00 ; \
	.byte	0x88, 0xc8, 0xc4, 0x20 ; \
	.byte	0xb2, 0xc8, 0x7e, 0x1d ; \
	.byte	0xb6, 0xc8, 0xfe, 0x3d ; \
	.byte	0x80, 0xc9, 0x48, 0x06 ; \
	.byte	0x84, 0xc9, 0xc8, 0x26 ; \
	.byte	0xba, 0xc9, 0x76, 0x19 ; \
	.byte	0xbe, 0xc9, 0xf6, 0x39 ; \
	.byte	0x8c, 0xca, 0x44, 0x00 ; \
	.byte	0x88, 0xca, 0xc4, 0x20 ; \
	.byte	0xb2, 0xca, 0x7e, 0x1d ; \
	.byte	0xb6, 0xca, 0xfe, 0x3d ; \
	.byte	0x80, 0xcb, 0x48, 0x06 ; \
	.byte	0x84, 0xcb, 0xc8, 0x26 ; \
	.byte	0xba, 0xcb, 0x76, 0x19 ; \
	.byte	0xbe, 0xcb, 0xf6, 0x39 ; \
	.byte	0x8c, 0xcc, 0x44, 0x00 ; \
	.byte	0x88, 0xcc, 0xc4, 0x20 ; \
	ldd	[%o0 + 0x10], %f0 ; \
	.byte	0xb2, 0xcc, 0x7e, 0x1d ; \
	ldd	[%o0 + 0x18], %f2 ; \
	.byte	0xb6, 0xcc, 0xfe, 0x3d ; \
	.byte	0xa8, 0xcd, 0x48, 0x86 ; \
	.byte	0xac, 0xcd, 0xc8, 0xa6 ; \
	ldd	[%o0 + 0x20], %f4 ; \
	.byte	0xba, 0xcd, 0x76, 0x99 ; \
	ldd	[%o0 + 0x28], %f6 ; \
	.byte	0xbe, 0xcd, 0xf6, 0xb9

#define	FIRST_TWO_DROUNDS \
	.byte	0xb2, 0xc8, 0x3e, 0x5d ; \
	.byte	0xb6, 0xc8, 0xbe, 0x7d ; \
	.byte	0xba, 0xc9, 0x36, 0x59 ; \
	.byte	0xbe, 0xc9, 0xb6, 0x79

#define	MID_TWO_DROUNDS \
	.byte	0xb2, 0xca, 0x3e, 0x5d ; \
	.byte	0xb6, 0xca, 0xbe, 0x7d ; \
	.byte	0xba, 0xcb, 0x36, 0x59 ; \
	.byte	0xbe, 0xcb, 0xb6, 0x79

#define	MID_TWO_DROUNDS_2 \
	.byte	0x8c, 0xca, 0x04, 0x40 ; \
	.byte	0x88, 0xca, 0x84, 0x60 ; \
	.byte	0xb2, 0xca, 0x3e, 0x5d ; \
	.byte	0xb6, 0xca, 0xbe, 0x7d ; \
	.byte	0x80, 0xcb, 0x08, 0x46 ; \
	.byte	0x84, 0xcb, 0x88, 0x66 ; \
	.byte	0xba, 0xcb, 0x36, 0x59 ; \
	.byte	0xbe, 0xcb, 0xb6, 0x79

#define	TEN_DROUNDS \
	.byte	0xb2, 0xcc, 0x3e, 0x5d ; \
	.byte	0xb6, 0xcc, 0xbe, 0x7d ; \
	.byte	0xba, 0xcd, 0x36, 0x59 ; \
	.byte	0xbe, 0xcd, 0xb6, 0x79 ; \
	.byte	0xb2, 0xce, 0x3e, 0x5d ; \
	.byte	0xb6, 0xce, 0xbe, 0x7d ; \
	.byte	0xba, 0xcf, 0x36, 0x59 ; \
	.byte	0xbe, 0xcf, 0xb6, 0x79 ; \
	.byte	0xb2, 0xc8, 0x7e, 0x5d ; \
	.byte	0xb6, 0xc8, 0xfe, 0x7d ; \
	.byte	0xba, 0xc9, 0x76, 0x59 ; \
	.byte	0xbe, 0xc9, 0xf6, 0x79 ; \
	.byte	0xb2, 0xca, 0x7e, 0x5d ; \
	.byte	0xb6, 0xca, 0xfe, 0x7d ; \
	.byte	0xba, 0xcb, 0x76, 0x59 ; \
	.byte	0xbe, 0xcb, 0xf6, 0x79 ; \
	.byte	0xb2, 0xcc, 0x7e, 0x5d ; \
	.byte	0xb6, 0xcc, 0xfe, 0x7d ; \
	.byte	0xba, 0xcd, 0x76, 0xd9 ; \
	.byte	0xbe, 0xcd, 0xf6, 0xf9

#define	TEN_DROUNDS_2 \
	.byte	0x8c, 0xcc, 0x04, 0x40 ; \
	.byte	0x88, 0xcc, 0x84, 0x60 ; \
	.byte	0xb2, 0xcc, 0x3e, 0x5d ; \
	.byte	0xb6, 0xcc, 0xbe, 0x7d ; \
	.byte	0x80, 0xcd, 0x08, 0x46 ; \
	.byte	0x84, 0xcd, 0x88, 0x66 ; \
	.byte	0xba, 0xcd, 0x36, 0x59 ; \
	.byte	0xbe, 0xcd, 0xb6, 0x79 ; \
	.byte	0x8c, 0xce, 0x04, 0x40 ; \
	.byte	0x88, 0xce, 0x84, 0x60 ; \
	.byte	0xb2, 0xce, 0x3e, 0x5d ; \
	.byte	0xb6, 0xce, 0xbe, 0x7d ; \
	.byte	0x80, 0xcf, 0x08, 0x46 ; \
	.byte	0x84, 0xcf, 0x88, 0x66 ; \
	.byte	0xba, 0xcf, 0x36, 0x59 ; \
	.byte	0xbe, 0xcf, 0xb6, 0x79 ; \
	.byte	0x8c, 0xc8, 0x44, 0x40 ; \
	.byte	0x88, 0xc8, 0xc4, 0x60 ; \
	.byte	0xb2, 0xc8, 0x7e, 0x5d ; \
	.byte	0xb6, 0xc8, 0xfe, 0x7d ; \
	.byte	0x80, 0xc9, 0x48, 0x46 ; \
	.byte	0x84, 0xc9, 0xc8, 0x66 ; \
	.byte	0xba, 0xc9, 0x76, 0x59 ; \
	.byte	0xbe, 0xc9, 0xf6, 0x79 ; \
	.byte	0x8c, 0xca, 0x44, 0x40 ; \
	.byte	0x88, 0xca, 0xc4, 0x60 ; \
	.byte	0xb2, 0xca, 0x7e, 0x5d ; \
	.byte	0xb6, 0xca, 0xfe, 0x7d ; \
	.byte	0x80, 0xcb, 0x48, 0x46 ; \
	.byte	0x84, 0xcb, 0xc8, 0x66 ; \
	.byte	0xba, 0xcb, 0x76, 0x59 ; \
	.byte	0xbe, 0xcb, 0xf6, 0x79 ; \
	.byte	0x8c, 0xcc, 0x44, 0x40 ; \
	.byte	0x88, 0xcc, 0xc4, 0x60 ; \
	.byte	0xb2, 0xcc, 0x7e, 0x5d ; \
	.byte	0xb6, 0xcc, 0xfe, 0x7d ; \
	.byte	0x80, 0xcd, 0x48, 0xc6 ; \
	.byte	0x84, 0xcd, 0xc8, 0xe6 ; \
	.byte	0xba, 0xcd, 0x76, 0xd9 ; \
	.byte	0xbe, 0xcd, 0xf6, 0xf9

#define	TWELVE_DROUNDS \
	MID_TWO_DROUNDS	; \
	TEN_DROUNDS

#define	TWELVE_DROUNDS_2 \
	MID_TWO_DROUNDS_2	; \
	TEN_DROUNDS_2

#define	FOURTEEN_DROUNDS \
	FIRST_TWO_DROUNDS ; \
	TWELVE_DROUNDS

#define	FOURTEEN_DROUNDS_2 \
	.byte	0xb0, 0xc8, 0x2c, 0x54 ; \
	.byte	0xac, 0xc8, 0xac, 0x74 ; \
	ldd	[%o0 + 0x80], %f20 ; \
	.byte	0xb2, 0xc8, 0x3e, 0x5d ; \
	.byte	0xb6, 0xc8, 0xbe, 0x7d ; \
	.byte	0x80, 0xc9, 0x2c, 0x58 ; \
	.byte	0x84, 0xc9, 0xac, 0x78 ; \
	ldd	[%o0 + 0x88], %f22 ; \
	.byte	0xba, 0xc9, 0x36, 0x59 ; \
	ldd	[%o0 + 0x70], %f24 ; \
	.byte	0xbe, 0xc9, 0xb6, 0x79 ; \
	.byte	0x8c, 0xca, 0x04, 0x40 ; \
	.byte	0x88, 0xca, 0x84, 0x60 ; \
	.byte	0xb2, 0xca, 0x3e, 0x5d ; \
	.byte	0xb6, 0xca, 0xbe, 0x7d ; \
	.byte	0x80, 0xcb, 0x08, 0x46 ; \
	.byte	0x84, 0xcb, 0x88, 0x66 ; \
	.byte	0xba, 0xcb, 0x36, 0x59 ; \
	.byte	0xbe, 0xcb, 0xb6, 0x79 ; \
	.byte	0x8c, 0xcc, 0x04, 0x40 ; \
	.byte	0x88, 0xcc, 0x84, 0x60 ; \
	.byte	0xb2, 0xcc, 0x3e, 0x5d ; \
	.byte	0xb6, 0xcc, 0xbe, 0x7d ; \
	.byte	0x80, 0xcd, 0x08, 0x46 ; \
	.byte	0x84, 0xcd, 0x88, 0x66 ; \
	.byte	0xba, 0xcd, 0x36, 0x59 ; \
	.byte	0xbe, 0xcd, 0xb6, 0x79 ; \
	.byte	0x8c, 0xce, 0x04, 0x40 ; \
	.byte	0x88, 0xce, 0x84, 0x60 ; \
	.byte	0xb2, 0xce, 0x3e, 0x5d ; \
	.byte	0xb6, 0xce, 0xbe, 0x7d ; \
	.byte	0x80, 0xcf, 0x08, 0x46 ; \
	.byte	0x84, 0xcf, 0x88, 0x66 ; \
	.byte	0xba, 0xcf, 0x36, 0x59 ; \
	.byte	0xbe, 0xcf, 0xb6, 0x79 ; \
	.byte	0x8c, 0xc8, 0x44, 0x40 ; \
	.byte	0x88, 0xc8, 0xc4, 0x60 ; \
	.byte	0xb2, 0xc8, 0x7e, 0x5d ; \
	.byte	0xb6, 0xc8, 0xfe, 0x7d ; \
	.byte	0x80, 0xc9, 0x48, 0x46 ; \
	.byte	0x84, 0xc9, 0xc8, 0x66 ; \
	.byte	0xba, 0xc9, 0x76, 0x59 ; \
	.byte	0xbe, 0xc9, 0xf6, 0x79 ; \
	.byte	0x8c, 0xca, 0x44, 0x40 ; \
	.byte	0x88, 0xca, 0xc4, 0x60 ; \
	.byte	0xb2, 0xca, 0x7e, 0x5d ; \
	.byte	0xb6, 0xca, 0xfe, 0x7d ; \
	.byte	0x80, 0xcb, 0x48, 0x46 ; \
	.byte	0x84, 0xcb, 0xc8, 0x66 ; \
	.byte	0xba, 0xcb, 0x76, 0x59 ; \
	.byte	0xbe, 0xcb, 0xf6, 0x79 ; \
	.byte	0x8c, 0xcc, 0x44, 0x40 ; \
	.byte	0x88, 0xcc, 0xc4, 0x60 ; \
	ldd	[%o0 + 0xd0], %f0 ; \
	.byte	0xb2, 0xcc, 0x7e, 0x5d ; \
	ldd	[%o0 + 0xd8], %f2 ; \
	.byte	0xb6, 0xcc, 0xfe, 0x7d ; \
	.byte	0xa8, 0xcd, 0x48, 0xc6 ; \
	.byte	0xac, 0xcd, 0xc8, 0xe6 ; \
	ldd	[%o0 + 0xc0], %f4 ; \
	.byte	0xba, 0xcd, 0x76, 0xd9 ; \
	ldd	[%o0 + 0xc8], %f6 ; \
	.byte	0xbe, 0xcd, 0xf6, 0xf9


	ENTRY(t4_aes128_load_keys_for_encrypt)

	ldd	[%o0 + 0x10], %f16
	ldd	[%o0 + 0x18], %f18
	ldd	[%o0 + 0x20], %f20
	ldd	[%o0 + 0x28], %f22
	ldd	[%o0 + 0x30], %f24
	ldd	[%o0 + 0x38], %f26
	ldd	[%o0 + 0x40], %f28
	ldd	[%o0 + 0x48], %f30
	ldd	[%o0 + 0x50], %f32
	ldd	[%o0 + 0x58], %f34
	ldd	[%o0 + 0x60], %f36
	ldd	[%o0 + 0x68], %f38
	ldd	[%o0 + 0x70], %f40
	ldd	[%o0 + 0x78], %f42
	ldd	[%o0 + 0x80], %f44
	ldd	[%o0 + 0x88], %f46
	ldd	[%o0 + 0x90], %f48
	ldd	[%o0 + 0x98], %f50
	ldd	[%o0 + 0xa0], %f52
	retl
	ldd	[%o0 + 0xa8], %f54

	SET_SIZE(t4_aes128_load_keys_for_encrypt)


	ENTRY(t4_aes192_load_keys_for_encrypt)

	ldd	[%o0 + 0x10], %f8
	ldd	[%o0 + 0x18], %f10
	ldd	[%o0 + 0x20], %f12
	ldd	[%o0 + 0x28], %f14
	ldd	[%o0 + 0x30], %f16
	ldd	[%o0 + 0x38], %f18
	ldd	[%o0 + 0x40], %f20
	ldd	[%o0 + 0x48], %f22
	ldd	[%o0 + 0x50], %f24
	ldd	[%o0 + 0x58], %f26
	ldd	[%o0 + 0x60], %f28
	ldd	[%o0 + 0x68], %f30
	ldd	[%o0 + 0x70], %f32
	ldd	[%o0 + 0x78], %f34
	ldd	[%o0 + 0x80], %f36
	ldd	[%o0 + 0x88], %f38
	ldd	[%o0 + 0x90], %f40
	ldd	[%o0 + 0x98], %f42
	ldd	[%o0 + 0xa0], %f44
	ldd	[%o0 + 0xa8], %f46
	ldd	[%o0 + 0xb0], %f48
	ldd	[%o0 + 0xb8], %f50
	ldd	[%o0 + 0xc0], %f52
	retl
	ldd	[%o0 + 0xc8], %f54

	SET_SIZE(t4_aes192_load_keys_for_encrypt)


	ENTRY(t4_aes256_load_keys_for_encrypt)

	ldd	[%o0 + 0x10], %f0
	ldd	[%o0 + 0x18], %f2
	ldd	[%o0 + 0x20], %f4
	ldd	[%o0 + 0x28], %f6
	ldd	[%o0 + 0x30], %f8
	ldd	[%o0 + 0x38], %f10
	ldd	[%o0 + 0x40], %f12
	ldd	[%o0 + 0x48], %f14
	ldd	[%o0 + 0x50], %f16
	ldd	[%o0 + 0x58], %f18
	ldd	[%o0 + 0x60], %f20
	ldd	[%o0 + 0x68], %f22
	ldd	[%o0 + 0x70], %f24
	ldd	[%o0 + 0x78], %f26
	ldd	[%o0 + 0x80], %f28
	ldd	[%o0 + 0x88], %f30
	ldd	[%o0 + 0x90], %f32
	ldd	[%o0 + 0x98], %f34
	ldd	[%o0 + 0xa0], %f36
	ldd	[%o0 + 0xa8], %f38
	ldd	[%o0 + 0xb0], %f40
	ldd	[%o0 + 0xb8], %f42
	ldd	[%o0 + 0xc0], %f44
	ldd	[%o0 + 0xc8], %f46
	ldd	[%o0 + 0xd0], %f48
	ldd	[%o0 + 0xd8], %f50
	ldd	[%o0 + 0xe0], %f52
	retl
	ldd	[%o0 + 0xe8], %f54

	SET_SIZE(t4_aes256_load_keys_for_encrypt)


#define	TEST_PARALLEL_ECB_ENCRYPT
#ifdef	TEST_PARALLEL_ECB_ENCRYPT
	ENTRY(t4_aes128_ecb_encrypt)

	ldx	[%o0], %g1	! ks[0]
	ldx	[%o0 + 8], %g2	! ks[1]
	and	%o3, 16, %o4
	brz	%o4, ecbenc128_loop
	nop

	ldx	[%o1], %g3	!input
	ldx	[%o1 + 8], %g4	!input
	xor	%g1, %g3, %g3	!input ^ ks[0-1]
	xor	%g2, %g4, %g4	!input ^ ks[0-1]
	movxtod	%g3, %f60
	movxtod	%g4, %f62

	TEN_EROUNDS

	std	%f60, [%o2]
	std	%f62, [%o2 + 8]

	add	%o1, 16, %o1
	subcc	%o3, 16, %o3
	be	ecbenc128_loop_end
	add	%o2, 16, %o2

ecbenc128_loop:
	ldx	[%o1], %g3	!input
	ldx	[%o1 + 8], %g4	!input
	xor	%g1, %g3, %g3	!input ^ ks[0-1]
	xor	%g2, %g4, %g4	!input ^ ks[0-1]
	movxtod	%g3, %f0
	movxtod	%g4, %f2
	ldx	[%o1 + 16], %g3	!input
	ldx	[%o1 + 24], %g4	!input
	xor	%g1, %g3, %g3	!input ^ ks[0-1]
	xor	%g2, %g4, %g4	!input ^ ks[0-1]
	movxtod	%g3, %f60
	movxtod	%g4, %f62

	TEN_EROUNDS_2

	std	%f0, [%o2]
	std	%f2, [%o2 + 8]

	std	%f60, [%o2 + 16]
	std	%f62, [%o2 + 24]

	add	%o1, 32, %o1
	subcc	%o3, 32, %o3
	bne	ecbenc128_loop
	add	%o2, 32, %o2
ecbenc128_loop_end:
	retl
	nop

	SET_SIZE(t4_aes128_ecb_encrypt)


	ENTRY(t4_aes192_ecb_encrypt)

	ldx	[%o0], %g1	! ks[0]
	ldx	[%o0 + 8], %g2	! ks[1]
	and	%o3, 16, %o4
	brz	%o4, ecbenc192_loop
	nop

	ldx	[%o1], %g3	!input
	ldx	[%o1 + 8], %g4	!input
	xor	%g1, %g3, %g3	!input ^ ks[0-1]
	xor	%g2, %g4, %g4	!input ^ ks[0-1]
	movxtod	%g3, %f60
	movxtod	%g4, %f62

	TWELVE_EROUNDS

	std	%f60, [%o2]
	std	%f62, [%o2 + 8]

	add	%o1, 16, %o1
	subcc	%o3, 16, %o3
	be	ecbenc192_loop_end
	add	%o2, 16, %o2

ecbenc192_loop:
	ldx	[%o1], %g3	!input
	ldx	[%o1 + 8], %g4	!input
	xor	%g1, %g3, %g3	!input ^ ks[0-1]
	xor	%g2, %g4, %g4	!input ^ ks[0-1]
	movxtod	%g3, %f0
	movxtod	%g4, %f2
	ldx	[%o1 + 16], %g3	!input
	ldx	[%o1 + 24], %g4	!input
	xor	%g1, %g3, %g3	!input ^ ks[0-1]
	xor	%g2, %g4, %g4	!input ^ ks[0-1]
	movxtod	%g3, %f60
	movxtod	%g4, %f62

	TWELVE_EROUNDS_2

	std	%f0, [%o2]
	std	%f2, [%o2 + 8]

	std	%f60, [%o2 + 16]
	std	%f62, [%o2 + 24]

	add	%o1, 32, %o1
	subcc	%o3, 32, %o3
	bne	ecbenc192_loop
	add	%o2, 32, %o2
ecbenc192_loop_end:
	retl
	nop

	SET_SIZE(t4_aes192_ecb_encrypt)


	ENTRY(t4_aes256_ecb_encrypt)

	ldx	[%o0], %g1	! ks[0]
	ldx	[%o0 + 8], %g2	! ks[1]
	and	%o3, 16, %o4
	brz	%o4, ecbenc256_loop
	nop

	ldx	[%o1], %g3	!input
	ldx	[%o1 + 8], %g4	!input
	xor	%g1, %g3, %g3	!input ^ ks[0-1]
	xor	%g2, %g4, %g4	!input ^ ks[0-1]
	movxtod	%g3, %f60
	movxtod	%g4, %f62

	FOURTEEN_EROUNDS

	std	%f60, [%o2]
	std	%f62, [%o2 + 8]

	add	%o1, 16, %o1
	subcc	%o3, 16, %o3
	be	ecbenc256_loop_end
	add	%o2, 16, %o2

ecbenc256_loop:
	ldx	[%o1], %g3	!input
	ldx	[%o1 + 8], %g4	!input
	xor	%g1, %g3, %g3	!input ^ ks[0-1]
	xor	%g2, %g4, %g4	!input ^ ks[0-1]
	movxtod	%g3, %f20
	movxtod	%g4, %f22
	ldx	[%o1 + 16], %g3	!input
	ldx	[%o1 + 24], %g4	!input
	xor	%g1, %g3, %g3	!input ^ ks[0-1]
	xor	%g2, %g4, %g4	!input ^ ks[0-1]
	movxtod	%g3, %f60
	movxtod	%g4, %f62

	FOURTEEN_EROUNDS_2

	std	%f20, [%o2]
	std	%f22, [%o2 + 8]

	std	%f60, [%o2 + 16]
	std	%f62, [%o2 + 24]

	add	%o1, 32, %o1
	subcc	%o3, 32, %o3
	bne	ecbenc256_loop
	add	%o2, 32, %o2

	ldd	[%o0 + 0x60], %f20
	ldd	[%o0 + 0x68], %f22 

ecbenc256_loop_end:
	retl
	nop

	SET_SIZE(t4_aes256_ecb_encrypt)

#else

	ENTRY(t4_aes128_ecb_encrypt)

	ldx	[%o0], %g1	! ks[0]
	ldx	[%o0 + 8], %g2	! ks[1]

ecbenc128_loop:
	ldx	[%o1], %g3	!input
	ldx	[%o1 + 8], %g4	!input
	xor	%g1, %g3, %g3	!input ^ ks[0-1]
	xor	%g2, %g4, %g4	!input ^ ks[0-1]
	movxtod	%g3, %f60
	movxtod	%g4, %f62

	TEN_EROUNDS

	std	%f60, [%o2]
	std	%f62, [%o2 + 8]

	add	%o1, 16, %o1
	subcc	%o3, 16, %o3
	bne	ecbenc128_loop
	add	%o2, 16, %o2

	retl
	nop

	SET_SIZE(t4_aes128_ecb_encrypt)


	ENTRY(t4_aes192_ecb_encrypt)

	ldx	[%o0], %g1	! ks[0]
	ldx	[%o0 + 8], %g2	! ks[1]

ecbenc192_loop:
	ldx	[%o1], %g3	!input
	ldx	[%o1 + 8], %g4	!input
	xor	%g1, %g3, %g3	!input ^ ks[0-1]
	xor	%g2, %g4, %g4	!input ^ ks[0-1]
	movxtod	%g3, %f60
	movxtod	%g4, %f62

	TWELVE_EROUNDS

	std	%f60, [%o2]
	std	%f62, [%o2 + 8]

	add	%o1, 16, %o1
	subcc	%o3, 16, %o3
	bne	ecbenc192_loop
	add	%o2, 16, %o2

	retl
	nop

	SET_SIZE(t4_aes192_ecb_encrypt)


	ENTRY(t4_aes256_ecb_encrypt)

	ldx	[%o0], %g1	! ks[0]
	ldx	[%o0 + 8], %g2	! ks[1]

ecbenc256_loop:
	ldx	[%o1], %g3	!input
	ldx	[%o1 + 8], %g4	!input
	xor	%g1, %g3, %g3	!input ^ ks[0-1]
	xor	%g2, %g4, %g4	!input ^ ks[0-1]
	movxtod	%g3, %f60
	movxtod	%g4, %f62

	FOURTEEN_EROUNDS

	std	%f60, [%o2]
	std	%f62, [%o2 + 8]

	add	%o1, 16, %o1
	subcc	%o3, 16, %o3
	bne	ecbenc256_loop
	add	%o2, 16, %o2

	retl
	nop

	SET_SIZE(t4_aes256_ecb_encrypt)
#endif


	ENTRY(t4_aes128_cbc_encrypt)

	ldd	[%o4], %f60	! IV
	ldd	[%o4 +8], %f62	! IV
	ldx	[%o0], %g1	! ks[0]
	ldx	[%o0 + 8], %g2	! ks[1]

cbcenc128_loop:
	ldx	[%o1], %g3	!input
	ldx	[%o1 + 8], %g4	!input
	xor	%g1, %g3, %g3	!input ^ ks[0-1]
	xor	%g2, %g4, %g4	!input ^ ks[0-1]
	movxtod	%g3, %f56
	movxtod	%g4, %f58
	fxor	%f60, %f56, %f60
	fxor	%f62, %f58, %f62

	TEN_EROUNDS

	std	%f60, [%o2]
	std	%f62, [%o2 + 8]

	add	%o1, 16, %o1
	subcc	%o3, 16, %o3
	bne	cbcenc128_loop
	add	%o2, 16, %o2

	std	%f60, [%o4]
	retl
	std	%f62, [%o4 + 8]

	SET_SIZE(t4_aes128_cbc_encrypt)


	ENTRY(t4_aes192_cbc_encrypt)

	ldd	[%o4], %f60	! IV
	ldd	[%o4 + 8], %f62	! IV
	ldx	[%o0], %g1	! ks[0]
	ldx	[%o0 + 8], %g2	! ks[1]

cbcenc192_loop:
	ldx	[%o1], %g3	!input
	ldx	[%o1 + 8], %g4	!input
	xor	%g1, %g3, %g3	!input ^ ks[0-1]
	xor	%g2, %g4, %g4	!input ^ ks[0-1]
	movxtod	%g3, %f56
	movxtod	%g4, %f58
	fxor	%f60, %f56, %f60
	fxor	%f62, %f58, %f62

	TWELVE_EROUNDS

	std	%f60, [%o2]
	std	%f62, [%o2 + 8]

	add	%o1, 16, %o1
	subcc	%o3, 16, %o3
	bne	cbcenc192_loop
	add	%o2, 16, %o2

	std	%f60, [%o4]
	retl
	std	%f62, [%o4 + 8]

	SET_SIZE(t4_aes192_cbc_encrypt)


	ENTRY(t4_aes256_cbc_encrypt)

	ldd	[%o4], %f60	! IV
	ldd	[%o4 + 8], %f62	! IV
	ldx	[%o0], %g1	! ks[0]
	ldx	[%o0 + 8], %g2	! ks[1]

cbcenc256_loop:
	ldx	[%o1], %g3	!input
	ldx	[%o1 + 8], %g4	!input
	xor	%g1, %g3, %g3	!input ^ ks[0-1]
	xor	%g2, %g4, %g4	!input ^ ks[0-1]
	movxtod	%g3, %f56
	movxtod	%g4, %f58
	fxor	%f60, %f56, %f60
	fxor	%f62, %f58, %f62

	FOURTEEN_EROUNDS

	std	%f60, [%o2]
	std	%f62, [%o2 + 8]

	add	%o1, 16, %o1
	subcc	%o3, 16, %o3
	bne	cbcenc256_loop
	add	%o2, 16, %o2

	std	%f60, [%o4]
	retl
	std	%f62, [%o4 + 8]

	SET_SIZE(t4_aes256_cbc_encrypt)


#define	 TEST_PARALLEL_CTR_CRYPT
#ifdef	TEST_PARALLEL_CTR_CRYPT
	ENTRY(t4_aes128_ctr_crypt)

	ldx	[%o4], %g3	! IV
	ldx	[%o4 +8], %g4	! IV
	ldx	[%o0], %g1	! ks[0]
	ldx	[%o0 + 8], %g2	! ks[1]
	and	%o3, 16, %g5
	brz, %g5, ctr128_loop

	xor	%g1, %g3, %g5
	movxtod	%g5, %f60
	xor	%g2, %g4, %g5
	movxtod	%g5, %f62
	inc	%g4

	TEN_EROUNDS

	ldd	[%o1], %f56	!input
	ldd	[%o1 + 8], %f58	!input
	fxor	%f60, %f56, %f60
	fxor	%f62, %f58, %f62
	std	%f60, [%o2]
	std	%f62, [%o2 + 8]

	add	%o1, 16, %o1
	subcc	%o3, 16, %o3
	be	ctr128_loop_end
	add	%o2, 16, %o2

ctr128_loop:
	xor	%g1, %g3, %g5
	movxtod	%g5, %f0
	xor	%g2, %g4, %g5
	movxtod	%g5, %f2
	inc	%g4

	xor	%g1, %g3, %g5
	movxtod	%g5, %f60
	xor	%g2, %g4, %g5
	movxtod	%g5, %f62
	inc	%g4

	TEN_EROUNDS_2

	ldd	[%o1], %f6		!input
	ldd	[%o1 + 8], %f4		!input
	ldd	[%o1 + 16], %f56	!input
	ldd	[%o1 + 24], %f58	!input
	fxor	%f0, %f6, %f0
	fxor	%f2, %f4, %f2
	fxor	%f60, %f56, %f60
	fxor	%f62, %f58, %f62
	std	%f0, [%o2]
	std	%f2, [%o2 + 8]
	std	%f60, [%o2 + 16]
	std	%f62, [%o2 + 24]

	add	%o1, 32, %o1
	subcc	%o3, 32, %o3
	bne	ctr128_loop
	add	%o2, 32, %o2

ctr128_loop_end:
	stx	%g3, [%o4]
	retl
	stx	%g4, [%o4 + 8]

	SET_SIZE(t4_aes128_ctr_crypt)


	ENTRY(t4_aes192_ctr_crypt)

	ldx	[%o4], %g3	! IV
	ldx	[%o4 +8], %g4	! IV
	ldx	[%o0], %g1	! ks[0]
	ldx	[%o0 + 8], %g2	! ks[1]
	and	%o3, 16, %g5
	brz, %g5, ctr192_loop

	xor	%g1, %g3, %g5
	movxtod	%g5, %f60
	xor	%g2, %g4, %g5
	movxtod	%g5, %f62
	inc	%g4

	TWELVE_EROUNDS

	ldd	[%o1], %f56	!input
	ldd	[%o1 + 8], %f58	!input
	fxor	%f60, %f56, %f60
	fxor	%f62, %f58, %f62
	std	%f60, [%o2]
	std	%f62, [%o2 + 8]

	add	%o1, 16, %o1
	subcc	%o3, 16, %o3
	be	ctr192_loop_end
	add	%o2, 16, %o2

ctr192_loop:
	xor	%g1, %g3, %g5
	movxtod	%g5, %f0
	xor	%g2, %g4, %g5
	movxtod	%g5, %f2
	inc	%g4

	xor	%g1, %g3, %g5
	movxtod	%g5, %f60
	xor	%g2, %g4, %g5
	movxtod	%g5, %f62
	inc	%g4

	TWELVE_EROUNDS_2

	ldd	[%o1], %f6		!input
	ldd	[%o1 + 8], %f4		!input
	ldd	[%o1 + 16], %f56	!input
	ldd	[%o1 + 24], %f58	!input
	fxor	%f0, %f6, %f0
	fxor	%f2, %f4, %f2
	fxor	%f60, %f56, %f60
	fxor	%f62, %f58, %f62
	std	%f0, [%o2]
	std	%f2, [%o2 + 8]
	std	%f60, [%o2 + 16]
	std	%f62, [%o2 + 24]

	add	%o1, 32, %o1
	subcc	%o3, 32, %o3
	bne	ctr192_loop
	add	%o2, 32, %o2

ctr192_loop_end:
	stx	%g3, [%o4]
	retl
	stx	%g4, [%o4 + 8]

	SET_SIZE(t4_aes192_ctr_crypt)


	ENTRY(t4_aes256_ctr_crypt)

	ldx	[%o4], %g3	! IV
	ldx	[%o4 +8], %g4	! IV
	ldx	[%o0], %g1	! ks[0]
	ldx	[%o0 + 8], %g2	! ks[1]
	and	%o3, 16, %g5
	brz,	%g5, ctr256_loop

	xor	%g1, %g3, %g5
	movxtod	%g5, %f60
	xor	%g2, %g4, %g5
	movxtod	%g5, %f62
	inc	%g4

	FOURTEEN_EROUNDS

	ldd	[%o1], %f56	!input
	ldd	[%o1 + 8], %f58	!input
	fxor	%f60, %f56, %f60
	fxor	%f62, %f58, %f62
	std	%f60, [%o2]
	std	%f62, [%o2 + 8]

	add	%o1, 16, %o1
	subcc	%o3, 16, %o3
	be	ctr256_loop_end
	add	%o2, 16, %o2

ctr256_loop:
	xor	%g1, %g3, %g5
	movxtod	%g5, %f20
	xor	%g2, %g4, %g5
	movxtod	%g5, %f22
	inc	%g4

	xor	%g1, %g3, %g5
	movxtod	%g5, %f60
	xor	%g2, %g4, %g5
	movxtod	%g5, %f62
	inc	%g4

	FOURTEEN_EROUNDS_2

	ldd	[%o1], %f56		!input
	ldd	[%o1 + 8], %f58		!input
	fxor	%f20, %f56, %f20
	fxor	%f22, %f58, %f22
	ldd	[%o1 + 16], %f56	!input
	ldd	[%o1 + 24], %f58	!input
	fxor	%f60, %f56, %f60
	fxor	%f62, %f58, %f62
	std	%f20, [%o2]
	std	%f22, [%o2 + 8]
	std	%f60, [%o2 + 16]
	std	%f62, [%o2 + 24]

	add	%o1, 32, %o1
	subcc	%o3, 32, %o3
	bne	ctr256_loop
	add	%o2, 32, %o2

	ldd	[%o0 + 0x60], %f20
	ldd	[%o0 + 0x68], %f22

ctr256_loop_end:
	stx	%g3, [%o4]
	retl
	stx	%g4, [%o4 + 8]

	SET_SIZE(t4_aes256_ctr_crypt)

#else

	ENTRY(t4_aes128_ctr_crypt)

	ldx	[%o4], %g3	! IV
	ldx	[%o4 +8], %g4	! IV
	ldx	[%o0], %g1	! ks[0]
	ldx	[%o0 + 8], %g2	! ks[1]

ctr128_loop:
	xor	%g1, %g3, %g5
	movxtod	%g5, %f60
	xor	%g2, %g4, %g5
	movxtod	%g5, %f62
	inc	%g4

	TEN_EROUNDS

	ldd	[%o1], %f56	!input
	ldd	[%o1 + 8], %f58	!input
	fxor	%f60, %f56, %f60
	fxor	%f62, %f58, %f62
	std	%f60, [%o2]
	std	%f62, [%o2 + 8]

	add	%o1, 16, %o1
	subcc	%o3, 16, %o3
	bne	ctr128_loop
	add	%o2, 16, %o2

	stx	%g3, [%o4]
	retl
	stx	%g4, [%o4 + 8]

	SET_SIZE(t4_aes128_ctr_crypt)

	ENTRY(t4_aes192_ctr_crypt)

	ldx	[%o4], %g3	! IV
	ldx	[%o4 +8], %g4	! IV
	ldx	[%o0], %g1	! ks[0]
	ldx	[%o0 + 8], %g2	! ks[1]

ctr192_loop:
	xor	%g1, %g3, %g5
	movxtod	%g5, %f60
	xor	%g2, %g4, %g5
	movxtod	%g5, %f62
	inc	%g4

	TWELVE_EROUNDS

	ldd	[%o1], %f56	!input
	ldd	[%o1 + 8], %f58	!input
	fxor	%f60, %f56, %f60
	fxor	%f62, %f58, %f62
	std	%f60, [%o2]
	std	%f62, [%o2 + 8]

	add	%o1, 16, %o1
	subcc	%o3, 16, %o3
	bne	ctr192_loop
	add	%o2, 16, %o2

	stx	%g3, [%o4]
	retl
	stx	%g4, [%o4 + 8]

	SET_SIZE(t4_aes192_ctr_crypt)


	ENTRY(t4_aes256_ctr_crypt)

	ldx	[%o4], %g3	! IV
	ldx	[%o4 +8], %g4	! IV
	ldx	[%o0], %g1	! ks[0]
	ldx	[%o0 + 8], %g2	! ks[1]

ctr256_loop:
	xor	%g1, %g3, %g5
	movxtod	%g5, %f60
	xor	%g2, %g4, %g5
	movxtod	%g5, %f62
	inc	%g4

	FOURTEEN_EROUNDS

	ldd	[%o1], %f56	!input
	ldd	[%o1 + 8], %f58	!input
	fxor	%f60, %f56, %f60
	fxor	%f62, %f58, %f62
	std	%f60, [%o2]
	std	%f62, [%o2 + 8]

	add	%o1, 16, %o1
	subcc	%o3, 16, %o3
	bne	ctr256_loop
	add	%o2, 16, %o2

	stx	%g3, [%o4]
	retl
	stx	%g4, [%o4 + 8]

	SET_SIZE(t4_aes256_ctr_crypt)

#endif

	ENTRY(t4_aes128_cfb128_encrypt)

	ldd	[%o4], %f60	! IV
	ldd	[%o4 +8], %f62	! IV
	ldx	[%o0], %g1	! ks[0]
	ldx	[%o0 + 8], %g2	! ks[1]

cfb128_128_loop:
	movxtod	%g1, %f56
	movxtod	%g2, %f58
	fxor	%f60, %f56, %f60
	fxor	%f62, %f58, %f62

	TEN_EROUNDS

	ldd	[%o1], %f56	!input
	ldd	[%o1 + 8], %f58	!input
	fxor	%f60, %f56, %f60
	fxor	%f62, %f58, %f62

	std	%f60, [%o2]
	std	%f62, [%o2 + 8]

	add	%o1, 16, %o1
	subcc	%o3, 16, %o3
	bne	cfb128_128_loop
	add	%o2, 16, %o2

	std	%f60, [%o4]
	retl
	std	%f62, [%o4 + 8]

	SET_SIZE(t4_aes128_cfb128_encrypt)


	ENTRY(t4_aes192_cfb128_encrypt)

	ldd	[%o4], %f60	! IV
	ldd	[%o4 +8], %f62	! IV
	ldx	[%o0], %g1	! ks[0]
	ldx	[%o0 + 8], %g2	! ks[1]

cfb128_192_loop:
	movxtod	%g1, %f56
	movxtod	%g2, %f58
	fxor	%f60, %f56, %f60
	fxor	%f62, %f58, %f62

	TWELVE_EROUNDS

	ldd	[%o1], %f56	!input
	ldd	[%o1 + 8], %f58	!input
	fxor	%f60, %f56, %f60
	fxor	%f62, %f58, %f62

	std	%f60, [%o2]
	std	%f62, [%o2 + 8]

	add	%o1, 16, %o1
	subcc	%o3, 16, %o3
	bne	cfb128_192_loop
	add	%o2, 16, %o2

	std	%f60, [%o4]
	retl
	std	%f62, [%o4 + 8]

	SET_SIZE(t4_aes192_cfb128_encrypt)


	ENTRY(t4_aes256_cfb128_encrypt)

	ldd	[%o4], %f60	! IV
	ldd	[%o4 +8], %f62	! IV
	ldx	[%o0], %g1	! ks[0]
	ldx	[%o0 + 8], %g2	! ks[1]

cfb128_256_loop:
	movxtod	%g1, %f56
	movxtod	%g2, %f58
	fxor	%f60, %f56, %f60
	fxor	%f62, %f58, %f62

	FOURTEEN_EROUNDS

	ldd	[%o1], %f56	!input
	ldd	[%o1 + 8], %f58	!input
	fxor	%f60, %f56, %f60
	fxor	%f62, %f58, %f62

	std	%f60, [%o2]
	std	%f62, [%o2 + 8]

	add	%o1, 16, %o1
	subcc	%o3, 16, %o3
	bne	cfb128_256_loop
	add	%o2, 16, %o2

	std	%f60, [%o4]
	retl
	std	%f62, [%o4 + 8]

	SET_SIZE(t4_aes256_cfb128_encrypt)


	ENTRY(t4_aes128_load_keys_for_decrypt)

	ldd	[%o0], %f52
	ldd	[%o0 + 0x8], %f54
	ldd	[%o0 + 0x10], %f48
	ldd	[%o0 + 0x18], %f50
	ldd	[%o0 + 0x20], %f44
	ldd	[%o0 + 0x28], %f46
	ldd	[%o0 + 0x30], %f40
	ldd	[%o0 + 0x38], %f42
	ldd	[%o0 + 0x40], %f36
	ldd	[%o0 + 0x48], %f38
	ldd	[%o0 + 0x50], %f32
	ldd	[%o0 + 0x58], %f34
	ldd	[%o0 + 0x60], %f28
	ldd	[%o0 + 0x68], %f30
	ldd	[%o0 + 0x70], %f24
	ldd	[%o0 + 0x78], %f26
	ldd	[%o0 + 0x80], %f20
	ldd	[%o0 + 0x88], %f22
	ldd	[%o0 + 0x90], %f16
	retl
	ldd	[%o0 + 0x98], %f18

	SET_SIZE(t4_aes128_load_keys_for_decrypt)


	ENTRY(t4_aes192_load_keys_for_decrypt)

	ldd	[%o0], %f52
	ldd	[%o0 + 0x8], %f54
	ldd	[%o0 + 0x10], %f48
	ldd	[%o0 + 0x18], %f50
	ldd	[%o0 + 0x20], %f44
	ldd	[%o0 + 0x28], %f46
	ldd	[%o0 + 0x30], %f40
	ldd	[%o0 + 0x38], %f42
	ldd	[%o0 + 0x40], %f36
	ldd	[%o0 + 0x48], %f38
	ldd	[%o0 + 0x50], %f32
	ldd	[%o0 + 0x58], %f34
	ldd	[%o0 + 0x60], %f28
	ldd	[%o0 + 0x68], %f30
	ldd	[%o0 + 0x70], %f24
	ldd	[%o0 + 0x78], %f26
	ldd	[%o0 + 0x80], %f20
	ldd	[%o0 + 0x88], %f22
	ldd	[%o0 + 0x90], %f16
	ldd	[%o0 + 0x98], %f18
	ldd	[%o0 + 0xa0], %f12
	ldd	[%o0 + 0xa8], %f14
	ldd	[%o0 + 0xb0], %f8
	retl
	ldd	[%o0 + 0xb8], %f10

	SET_SIZE(t4_aes192_load_keys_for_decrypt)


	ENTRY(t4_aes256_load_keys_for_decrypt)


	ldd	[%o0], %f52
	ldd	[%o0 + 0x8], %f54
	ldd	[%o0 + 0x10], %f48
	ldd	[%o0 + 0x18], %f50
	ldd	[%o0 + 0x20], %f44
	ldd	[%o0 + 0x28], %f46
	ldd	[%o0 + 0x30], %f40
	ldd	[%o0 + 0x38], %f42
	ldd	[%o0 + 0x40], %f36
	ldd	[%o0 + 0x48], %f38
	ldd	[%o0 + 0x50], %f32
	ldd	[%o0 + 0x58], %f34
	ldd	[%o0 + 0x60], %f28
	ldd	[%o0 + 0x68], %f30
	ldd	[%o0 + 0x70], %f24
	ldd	[%o0 + 0x78], %f26
	ldd	[%o0 + 0x80], %f20
	ldd	[%o0 + 0x88], %f22
	ldd	[%o0 + 0x90], %f16
	ldd	[%o0 + 0x98], %f18
	ldd	[%o0 + 0xa0], %f12
	ldd	[%o0 + 0xa8], %f14
	ldd	[%o0 + 0xb0], %f8
	ldd	[%o0 + 0xb8], %f10
	ldd	[%o0 + 0xc0], %f4
	ldd	[%o0 + 0xc8], %f6
	ldd	[%o0 + 0xd0], %f0
	retl
	ldd	[%o0 + 0xd8], %f2

	SET_SIZE(t4_aes256_load_keys_for_decrypt)


#define	 TEST_PARALLEL_ECB_DECRYPT
#ifdef	TEST_PARALLEL_ECB_DECRYPT
	ENTRY(t4_aes128_ecb_decrypt)

	ldx	[%o0 + 0xa0], %g1	!ks[last-1]
	ldx	[%o0 + 0xa8], %g2	!ks[last]
	and	%o3, 16, %o4
	brz	%o4, ecbdec128_loop
	nop

	ldx	[%o1], %o4
	ldx	[%o1 + 8], %o5
	xor	%g1, %o4, %g3	!initial ARK
	movxtod	%g3, %f60
	xor	%g2, %o5, %g3	!initial ARK
	movxtod	%g3, %f62

	TEN_DROUNDS

	std	%f60, [%o2]
	std	%f62, [%o2 + 0x8]

	add	%o1, 16, %o1
	subcc	%o3, 16, %o3
	be	ecbdec128_loop_end
	add	%o2, 16, %o2

ecbdec128_loop:
	ldx	[%o1], %o4
	ldx	[%o1 + 8], %o5
	xor	%g1, %o4, %g3	!initial ARK
	movxtod	%g3, %f0
	xor	%g2, %o5, %g3	!initial ARK
	movxtod	%g3, %f2
	ldx	[%o1 + 16], %o4
	ldx	[%o1 + 24], %o5
	xor	%g1, %o4, %g3	!initial ARK
	movxtod	%g3, %f60
	xor	%g2, %o5, %g3	!initial ARK
	movxtod	%g3, %f62

	TEN_DROUNDS_2

	std	%f0, [%o2]
	std	%f2, [%o2 + 8]
	std	%f60, [%o2 + 16]
	std	%f62, [%o2 + 24]

	add	%o1, 32, %o1
	subcc	%o3, 32, %o3
	bne	ecbdec128_loop
	add	%o2, 32, %o2
ecbdec128_loop_end:

	retl
	nop

	SET_SIZE(t4_aes128_ecb_decrypt)

	ENTRY(t4_aes192_ecb_decrypt)

	ldx	[%o0 + 0xc0], %g1	!ks[last-1]
	ldx	[%o0 + 0xc8], %g2	!ks[last]
	and	%o3, 16, %o4
	brz	%o4, ecbdec192_loop
	nop

	ldx	[%o1], %o4
	ldx	[%o1 + 8], %o5
	xor	%g1, %o4, %g3	!initial ARK
	movxtod	%g3, %f60
	xor	%g2, %o5, %g3	!initial ARK
	movxtod	%g3, %f62

	TWELVE_DROUNDS

	std	%f60, [%o2]
	std	%f62, [%o2 + 0x8]

	add	%o1, 16, %o1
	subcc	%o3, 16, %o3
	be	ecbdec192_loop_end
	add	%o2, 16, %o2

ecbdec192_loop:
	ldx	[%o1], %o4
	ldx	[%o1 + 8], %o5
	xor	%g1, %o4, %g3	!initial ARK
	movxtod	%g3, %f0
	xor	%g2, %o5, %g3	!initial ARK
	movxtod	%g3, %f2
	ldx	[%o1 + 16], %o4
	ldx	[%o1 + 24], %o5
	xor	%g1, %o4, %g3	!initial ARK
	movxtod	%g3, %f60
	xor	%g2, %o5, %g3	!initial ARK
	movxtod	%g3, %f62

	TWELVE_DROUNDS_2

	std	%f0, [%o2]
	std	%f2, [%o2 + 8]
	std	%f60, [%o2 + 16]
	std	%f62, [%o2 + 24]

	add	%o1, 32, %o1
	subcc	%o3, 32, %o3
	bne	ecbdec192_loop
	add	%o2, 32, %o2
ecbdec192_loop_end:

	retl
	nop

	SET_SIZE(t4_aes192_ecb_decrypt)


	ENTRY(t4_aes256_ecb_decrypt)

	ldx	[%o0 + 0xe0], %g1	!ks[last-1]
	ldx	[%o0 + 0xe8], %g2	!ks[last]
	and	%o3, 16, %o4
	brz	%o4, ecbdec256_loop
	nop

	ldx	[%o1], %o4
	ldx	[%o1 + 8], %o5
	xor	%g1, %o4, %g3	!initial ARK
	movxtod	%g3, %f60
	xor	%g2, %o5, %g3	!initial ARK
	movxtod	%g3, %f62

	FOURTEEN_DROUNDS

	std	%f60, [%o2]
	std	%f62, [%o2 + 0x8]

	add	%o1, 16, %o1
	subcc	%o3, 16, %o3
	be	ecbdec256_loop_end
	add	%o2, 16, %o2

ecbdec256_loop:
	ldx	[%o1], %o4
	ldx	[%o1 + 8], %o5
	xor	%g1, %o4, %g3	!initial ARK
	movxtod	%g3, %f20
	xor	%g2, %o5, %g3	!initial ARK
	movxtod	%g3, %f22
	ldx	[%o1 + 16], %o4
	ldx	[%o1 + 24], %o5
	xor	%g1, %o4, %g3	!initial ARK
	movxtod	%g3, %f60
	xor	%g2, %o5, %g3	!initial ARK
	movxtod	%g3, %f62

	FOURTEEN_DROUNDS_2

	std	%f20, [%o2]
	std	%f22, [%o2 + 8]
	std	%f60, [%o2 + 16]
	std	%f62, [%o2 + 24]

	add	%o1, 32, %o1
	subcc	%o3, 32, %o3
	bne	ecbdec256_loop
	add	%o2, 32, %o2

	ldd	[%o0 + 0x80], %f20
	ldd	[%o0 + 0x88], %f22 

ecbdec256_loop_end:

	retl
	nop

	SET_SIZE(t4_aes256_ecb_decrypt)

#else

	ENTRY(t4_aes128_ecb_decrypt)

	ldx	[%o0 + 0xa0], %g1	!ks[last-1]
	ldx	[%o0 + 0xa8], %g2	!ks[last]

ecbdec128_loop:
	ldx	[%o1], %o4
	ldx	[%o1 + 8], %o5
	xor	%g1, %o4, %g3	!initial ARK
	movxtod	%g3, %f60
	xor	%g2, %o5, %g3	!initial ARK
	movxtod	%g3, %f62

	TEN_DROUNDS

	std	%f60, [%o2]
	std	%f62, [%o2 + 0x8]

	add	%o1, 16, %o1
	subcc	%o3, 16, %o3
	bne	ecbdec128_loop
	add	%o2, 16, %o2

	retl
	nop

	SET_SIZE(t4_aes128_ecb_decrypt)


	ENTRY(t4_aes192_ecb_decrypt)

	ldx	[%o0 + 0xc0], %g1	!ks[last-1]
	ldx	[%o0 + 0xc8], %g2	!ks[last]

ecbdec192_loop:
	ldx	[%o1], %o4
	ldx	[%o1 + 8], %o5
	xor	%g1, %o4, %g3	!initial ARK
	movxtod	%g3, %f60
	xor	%g2, %o5, %g3	!initial ARK
	movxtod	%g3, %f62

	TWELVE_DROUNDS

	std	%f60, [%o2]
	std	%f62, [%o2 + 0x8]

	add	%o1, 16, %o1
	subcc	%o3, 16, %o3
	bne	ecbdec192_loop
	add	%o2, 16, %o2

	retl
	nop

	SET_SIZE(t4_aes192_ecb_decrypt)


	ENTRY(t4_aes256_ecb_decrypt)

	ldx	[%o0 + 0xe0], %g1	!ks[last-1]
	ldx	[%o0 + 0xe8], %g2	!ks[last]

ecbdec256_loop:
	ldx	[%o1], %o4
	ldx	[%o1 + 8], %o5
	xor	%g1, %o4, %g3	!initial ARK
	movxtod	%g3, %f60
	xor	%g2, %o5, %g3	!initial ARK
	movxtod	%g3, %f62

	FOURTEEN_DROUNDS

	std	%f60, [%o2]
	std	%f62, [%o2 + 0x8]

	add	%o1, 16, %o1
	subcc	%o3, 16, %o3
	bne	ecbdec256_loop
	add	%o2, 16, %o2

	retl
	nop

	SET_SIZE(t4_aes256_ecb_decrypt)

#endif

#define	TEST_PARALLEL_CBC_DECRYPT
#ifdef	EST_PARALLEL_CBC_DECRYPT
		ENTRY(t4_aes128_cbc_decrypt)

	save	%sp, -SA(MINFRAME), %sp
	ldx	[%i4], %o0		!IV
	ldx	[%i4 + 8], %o1		!IV
	ldx	[%i0 + 0xa0], %o2	!ks[last-1]
	ldx	[%i0 + 0xa8], %o3	!ks[last]
	and	%i3, 16, %o4
	brz	%o4, cbcdec128_loop
	nop

	ldx	[%i1], %o4
	ldx	[%i1 + 8], %o5
	xor	%o2, %o4, %i5	!initial ARK
	movxtod	%i5, %f60
	xor	%o3, %o5, %i5	!initial ARK
	movxtod	%i5, %f62

	TEN_DROUNDS

	movxtod	%o0, %f56
	movxtod	%o1, %f58
	mov	%o4, %o0	!save last block as next IV
	mov	%o5, %o1
	fxor	%f56, %f60, %f60	!add in previous IV
	fxor	%f58, %f62, %f62

	std	%f60, [%i2]
	std	%f62, [%i2 + 0x8]

	add	%i1, 16, %i1
	subcc	%i3, 16, %i3
	be	cbcdec128_loop_end
	add	%i2, 16, %i2


cbcdec128_loop:
	ldx	[%i1], %g4
	ldx	[%i1 + 8], %g5
	xor	%o2, %g4, %i5	!initial ARK
	movxtod	%i5, %f0
	xor	%o3, %g5, %i5	!initial ARK
	movxtod	%i5, %f2

	ldx	[%i1 + 16], %o4
	ldx	[%i1 + 24], %o5
	xor	%o2, %o4, %i5	!initial ARK
	movxtod	%i5, %f60
	xor	%o3, %o5, %i5	!initial ARK
	movxtod	%i5, %f62

	TEN_DROUNDS_2

	movxtod	%o0, %f6
	movxtod	%o1, %f4
	fxor	%f6, %f0, %f0	!add in previous IV
	fxor	%f4, %f2, %f2

	std	%f0, [%i2]
	std	%f2, [%i2 + 8]

	movxtod	%g4, %f56
	movxtod	%g5, %f58
	mov	%o4, %o0	!save last block as next IV
	mov	%o5, %o1
	fxor	%f56, %f60, %f60	!add in previous IV
	fxor	%f58, %f62, %f62

	std	%f60, [%i2 + 16]
	std	%f62, [%i2 + 24]

	add	%i1, 32, %i1
	subcc	%i3, 32, %i3
	bne	cbcdec128_loop
	add	%i2, 32, %i2

cbcdec128_loop_end:
	stx	%o0, [%i4]
	stx	%o1, [%i4 + 8]
	ret
	restore

	SET_SIZE(t4_aes128_cbc_decrypt)


	ENTRY(t4_aes192_cbc_decrypt)

	save	%sp, -SA(MINFRAME), %sp
	ldx	[%i4], %o0		!IV
	ldx	[%i4 + 8], %o1		!IV
	ldx	[%i0 + 0xc0], %o2	!ks[last-1]
	ldx	[%i0 + 0xc8], %o3	!ks[last]
	and	%i3, 16, %o4
	brz	%o4, cbcdec192_loop
	nop

	ldx	[%i1], %o4
	ldx	[%i1 + 8], %o5
	xor	%o2, %o4, %i5	!initial ARK
	movxtod	%i5, %f60
	xor	%o3, %o5, %i5	!initial ARK
	movxtod	%i5, %f62

	TWELVE_DROUNDS

	movxtod	%o0, %f56
	movxtod	%o1, %f58
	mov	%o4, %o0	!save last block as next IV
	mov	%o5, %o1
	fxor	%f56, %f60, %f60	!add in previous IV
	fxor	%f58, %f62, %f62

	std	%f60, [%i2]
	std	%f62, [%i2 + 0x8]

	add	%i1, 16, %i1
	subcc	%i3, 16, %i3
	be	cbcdec192_loop_end
	add	%i2, 16, %i2


cbcdec192_loop:
	ldx	[%i1], %g4
	ldx	[%i1 + 8], %g5
	xor	%o2, %g4, %i5	!initial ARK
	movxtod	%i5, %f0
	xor	%o3, %g5, %i5	!initial ARK
	movxtod	%i5, %f2

	ldx	[%i1 + 16], %o4
	ldx	[%i1 + 24], %o5
	xor	%o2, %o4, %i5	!initial ARK
	movxtod	%i5, %f60
	xor	%o3, %o5, %i5	!initial ARK
	movxtod	%i5, %f62

	TWELVE_DROUNDS_2

	movxtod	%o0, %f6
	movxtod	%o1, %f4
	fxor	%f6, %f0, %f0	!add in previous IV
	fxor	%f4, %f2, %f2

	std	%f0, [%i2]
	std	%f2, [%i2 + 8]

	movxtod	%g4, %f56
	movxtod	%g5, %f58
	mov	%o4, %o0	!save last block as next IV
	mov	%o5, %o1
	fxor	%f56, %f60, %f60	!add in previous IV
	fxor	%f58, %f62, %f62

	std	%f60, [%i2 + 16]
	std	%f62, [%i2 + 24]

	add	%i1, 32, %i1
	subcc	%i3, 32, %i3
	bne	cbcdec192_loop
	add	%i2, 32, %i2

cbcdec192_loop_end:
	stx	%o0, [%i4]
	stx	%o1, [%i4 + 8]
	ret
	restore

	SET_SIZE(t4_aes192_cbc_decrypt)


	ENTRY(t4_aes256_cbc_decrypt)

	save	%sp, -SA(MINFRAME), %sp
	mov	%i0, %o0
	ldx	[%i4], %i0		!IV
	ldx	[%i4 + 8], %o1		!IV
	ldx	[%o0 + 0xe0], %o2	!ks[last-1]
	ldx	[%o0 + 0xe8], %o3	!ks[last]
	and	%i3, 16, %o4
	brz	%o4, cbcdec256_loop
	nop

	ldx	[%i1], %o4
	ldx	[%i1 + 8], %o5
	xor	%o2, %o4, %i5	!initial ARK
	movxtod	%i5, %f60
	xor	%o3, %o5, %i5	!initial ARK
	movxtod	%i5, %f62

	FOURTEEN_DROUNDS

	movxtod	%i0, %f56
	movxtod	%o1, %f58
	mov	%o4, %i0	!save last block as next IV
	mov	%o5, %o1
	fxor	%f56, %f60, %f60	!add in previous IV
	fxor	%f58, %f62, %f62

	std	%f60, [%i2]
	std	%f62, [%i2 + 0x8]

	add	%i1, 16, %i1
	subcc	%i3, 16, %i3
	be	cbcdec256_loop_end
	add	%i2, 16, %i2


cbcdec256_loop:
	ldx	[%i1], %g4
	ldx	[%i1 + 8], %g5
	xor	%o2, %g4, %i5	!initial ARK
	movxtod	%i5, %f20
	xor	%o3, %g5, %i5	!initial ARK
	movxtod	%i5, %f22

	ldx	[%i1 + 16], %o4
	ldx	[%i1 + 24], %o5
	xor	%o2, %o4, %i5	!initial ARK
	movxtod	%i5, %f60
	xor	%o3, %o5, %i5	!initial ARK
	movxtod	%i5, %f62

	FOURTEEN_DROUNDS_2

	movxtod	%i0, %f56
	movxtod	%o1, %f58
	fxor	%f56, %f20, %f20	!add in previous IV
	fxor	%f58, %f22, %f22

	std	%f20, [%i2]
	std	%f22, [%i2 + 8]

	movxtod	%g4, %f56
	movxtod	%g5, %f58
	mov	%o4, %i0	!save last block as next IV
	mov	%o5, %o1
	fxor	%f56, %f60, %f60	!add in previous IV
	fxor	%f58, %f62, %f62

	std	%f60, [%i2 + 16]
	std	%f62, [%i2 + 24]

	add	%i1, 32, %i1
	subcc	%i3, 32, %i3
	bne	cbcdec256_loop
	add	%i2, 32, %i2

	ldd	[%o0 + 0x80], %f20
	ldd	[%o0 + 0x88], %f22 

cbcdec256_loop_end:
	stx	%i0, [%i4]
	stx	%o1, [%i4 + 8]
	ret
	restore

	SET_SIZE(t4_aes256_cbc_decrypt)

#else

	ENTRY(t4_aes128_cbc_decrypt)

	save	%sp, -SA(MINFRAME), %sp
	ldx	[%i4], %o0		!IV
	ldx	[%i4 + 8], %o1		!IV
	ldx	[%i0 + 0xa0], %o2	!ks[last-1]
	ldx	[%i0 + 0xa8], %o3	!ks[last]

cbcdec128_loop:
	ldx	[%i1], %o4
	ldx	[%i1 + 8], %o5
	xor	%o2, %o4, %i5	!initial ARK
	movxtod	%i5, %f60
	xor	%o3, %o5, %i5	!initial ARK
	movxtod	%i5, %f62

	TEN_DROUNDS

	movxtod	%o0, %f56
	movxtod	%o1, %f58
	mov	%o4, %o0	!save last block as next IV
	mov	%o5, %o1
	fxor	%f56, %f60, %f60	!add in previous IV
	fxor	%f58, %f62, %f62

	std	%f60, [%i2]
	std	%f62, [%i2 + 0x8]

	add	%i1, 16, %i1
	subcc	%i3, 16, %i3
	bne	cbcdec128_loop
	add	%i2, 16, %i2

	stx	%o0, [%i4]
	stx	%o1, [%i4 + 8]
	ret
	restore

	SET_SIZE(t4_aes128_cbc_decrypt)


	ENTRY(t4_aes192_cbc_decrypt)

	save	%sp, -SA(MINFRAME), %sp
	ldx	[%i4], %o0		!IV
	ldx	[%i4 + 8], %o1		!IV
	ldx	[%i0 + 0xc0], %o2	!ks[last-1]
	ldx	[%i0 + 0xc8], %o3	!ks[last]

cbcdec192_loop:
	ldx	[%i1], %o4
	ldx	[%i1 + 8], %o5
	xor	%o2, %o4, %i5	!initial ARK
	movxtod	%i5, %f60
	xor	%o3, %o5, %i5	!initial ARK
	movxtod	%i5, %f62

	TWELVE_DROUNDS

	movxtod	%o0, %f56
	movxtod	%o1, %f58
	mov	%o4, %o0	!save last block as next IV
	mov	%o5, %o1
	fxor	%f56, %f60, %f60	!add in previous IV
	fxor	%f58, %f62, %f62

	std	%f60, [%i2]
	std	%f62, [%i2 + 0x8]

	add	%i1, 16, %i1
	subcc	%i3, 16, %i3
	bne	cbcdec192_loop
	add	%i2, 16, %i2

	stx	%o0, [%i4]
	stx	%o1, [%i4 + 8]
	ret
	restore

	SET_SIZE(t4_aes192_cbc_decrypt)


	ENTRY(t4_aes256_cbc_decrypt)

	save	%sp, -SA(MINFRAME), %sp
	ldx	[%i4], %o0		!IV
	ldx	[%i4 + 8], %o1		!IV
	ldx	[%i0 + 0xe0], %o2	!ks[last-1]
	ldx	[%i0 + 0xe8], %o3	!ks[last]

cbcdec256_loop:
	ldx	[%i1], %o4
	ldx	[%i1 + 8], %o5
	xor	%o2, %o4, %i5	!initial ARK
	movxtod	%i5, %f60
	xor	%o3, %o5, %i5	!initial ARK
	movxtod	%i5, %f62

	FOURTEEN_DROUNDS

	movxtod	%o0, %f56
	movxtod	%o1, %f58
	mov	%o4, %o0	!save last block as next IV
	mov	%o5, %o1
	fxor	%f56, %f60, %f60	!add in previous IV
	fxor	%f58, %f62, %f62

	std	%f60, [%i2]
	std	%f62, [%i2 + 0x8]

	add	%i1, 16, %i1
	subcc	%i3, 16, %i3
	bne	cbcdec256_loop
	add	%i2, 16, %i2

	stx	%o0, [%i4]
	stx	%o1, [%i4 + 8]
	ret
	restore

	SET_SIZE(t4_aes256_cbc_decrypt)

#endif

#define	TEST_PARALLEL_CFB128_DECRYPT
#ifdef	TEST_PARALLEL_CFB128_DECRYPT

	ENTRY(t4_aes128_cfb128_decrypt)

	ldd	[%o4], %f56	!IV
	ldd	[%o4 + 8], %f58	!IV
	ldx	[%o0], %g1	! ks[0]
	ldx	[%o0 + 8], %g2	! ks[1]
	and	%o3, 16, %o5
	brz	%o5, cfb128dec_128_loop

	movxtod	%g1, %f60
	movxtod	%g2, %f62
	fxor	%f60, %f56, %f60
	fxor	%f62, %f58, %f62

	/* CFB mode uses encryption for the decrypt operation */
	TEN_EROUNDS

	ldd	[%o1], %f56	!input
	ldd	[%o1 + 8], %f58	!input
	fxor	%f60, %f56, %f60
	fxor	%f62, %f58, %f62

	std	%f60, [%o2]
	std	%f62, [%o2 + 8]

	add	%o1, 16, %o1
	subcc	%o3, 16, %o3
	be	cfb128dec_128_loop_end
	add	%o2, 16, %o2

cfb128dec_128_loop:
	ldd	[%o1], %f6	!input
	ldd	[%o1 + 8], %f4	!input
	movxtod	%g1, %f60
	movxtod	%g2, %f62
	fxor	%f60, %f6, %f0
	fxor	%f62, %f4, %f2
	fxor	%f60, %f56, %f60
	fxor	%f62, %f58, %f62

	/* CFB mode uses encryption for the decrypt operation */
	TEN_EROUNDS_2

	ldd	[%o1], %f6	!input
	ldd	[%o1 + 8], %f4	!input
	ldd	[%o1 + 16], %f56	!input
	ldd	[%o1 + 24], %f58	!input

	fxor	%f60, %f6, %f6
	fxor	%f62, %f4, %f4
	fxor	%f0, %f56, %f60
	fxor	%f2, %f58, %f62

	std	%f6, [%o2]
	std	%f4, [%o2 + 8]
	std	%f60, [%o2 + 16]
	std	%f62, [%o2 + 24]

	add	%o1, 32, %o1
	subcc	%o3, 32, %o3
	bne	cfb128dec_128_loop
	add	%o2, 32, %o2

cfb128dec_128_loop_end:
	std	%f56, [%o4]
	retl
	std	%f58, [%o4 + 8]

	SET_SIZE(t4_aes128_cfb128_decrypt)


	ENTRY(t4_aes192_cfb128_decrypt)

	ldd	[%o4], %f56	!IV
	ldd	[%o4 + 8], %f58	!IV
	ldx	[%o0], %g1	! ks[0]
	ldx	[%o0 + 8], %g2	! ks[1]
	and	%o3, 16, %o5
	brz	%o5, cfb128dec_192_loop

	movxtod	%g1, %f60
	movxtod	%g2, %f62
	fxor	%f60, %f56, %f60
	fxor	%f62, %f58, %f62

	/* CFB mode uses encryption for the decrypt operation */
	TWELVE_EROUNDS

	ldd	[%o1], %f56	!input
	ldd	[%o1 + 8], %f58	!input
	fxor	%f60, %f56, %f60
	fxor	%f62, %f58, %f62

	std	%f60, [%o2]
	std	%f62, [%o2 + 8]

	add	%o1, 16, %o1
	subcc	%o3, 16, %o3
	be	cfb128dec_192_loop_end
	add	%o2, 16, %o2

cfb128dec_192_loop:
	ldd	[%o1], %f6	!input
	ldd	[%o1 + 8], %f4	!input
	movxtod	%g1, %f60
	movxtod	%g2, %f62
	fxor	%f60, %f6, %f0
	fxor	%f62, %f4, %f2
	fxor	%f60, %f56, %f60
	fxor	%f62, %f58, %f62

	/* CFB mode uses encryption for the decrypt operation */
	TWELVE_EROUNDS_2

	ldd	[%o1], %f6	!input
	ldd	[%o1 + 8], %f4	!input
	ldd	[%o1 + 16], %f56	!input
	ldd	[%o1 + 24], %f58	!input

	fxor	%f60, %f6, %f6
	fxor	%f62, %f4, %f4
	fxor	%f0, %f56, %f60
	fxor	%f2, %f58, %f62

	std	%f6, [%o2]
	std	%f4, [%o2 + 8]
	std	%f60, [%o2 + 16]
	std	%f62, [%o2 + 24]

	add	%o1, 32, %o1
	subcc	%o3, 32, %o3
	bne	cfb128dec_192_loop
	add	%o2, 32, %o2

cfb128dec_192_loop_end:
	std	%f56, [%o4]
	retl
	std	%f58, [%o4 + 8]

	SET_SIZE(t4_aes192_cfb128_decrypt)


	ENTRY(t4_aes256_cfb128_decrypt)

	ldd	[%o4], %f56	!IV
	ldd	[%o4 + 8], %f58	!IV
	ldx	[%o0], %g1	! ks[0]
	ldx	[%o0 + 8], %g2	! ks[1]
	and	%o3, 16, %o5
	brz	%o5, cfb128dec_256_loop

	movxtod	%g1, %f60
	movxtod	%g2, %f62
	fxor	%f60, %f56, %f60
	fxor	%f62, %f58, %f62

	/* CFB mode uses encryption for the decrypt operation */
	FOURTEEN_EROUNDS

	ldd	[%o1], %f56	!input
	ldd	[%o1 + 8], %f58	!input
	fxor	%f60, %f56, %f60
	fxor	%f62, %f58, %f62

	std	%f60, [%o2]
	std	%f62, [%o2 + 8]

	add	%o1, 16, %o1
	subcc	%o3, 16, %o3
	be	cfb128dec_256_loop_end
	add	%o2, 16, %o2

cfb128dec_256_loop:
	ldd	[%o1], %f20	!input
	ldd	[%o1 + 8], %f22	!input
	movxtod	%g1, %f60
	movxtod	%g2, %f62
	fxor	%f60, %f20, %f20
	fxor	%f62, %f22, %f22
	fxor	%f60, %f56, %f60
	fxor	%f62, %f58, %f62

	/* CFB mode uses encryption for the decrypt operation */
	FOURTEEN_EROUNDS_2

	ldd	[%o1 + 16], %f56	!input
	ldd	[%o1 + 24], %f58	!input
	fxor	%f20, %f56, %f20
	fxor	%f22, %f58, %f22
	std	%f20, [%o2 + 16]
	std	%f22, [%o2 + 24]

	ldd	[%o1], %f20	!input
	ldd	[%o1 + 8], %f22	!input

	fxor	%f60, %f20, %f20
	fxor	%f62, %f22, %f22

	std	%f20, [%o2]
	std	%f22, [%o2 + 8]

	add	%o1, 32, %o1
	subcc	%o3, 32, %o3
	bne	cfb128dec_256_loop
	add	%o2, 32, %o2

	ldd	[%o0 + 0x60], %f20
	ldd	[%o0 + 0x68], %f22 

cfb128dec_256_loop_end:
	std	%f56, [%o4]
	retl
	std	%f58, [%o4 + 8]

	SET_SIZE(t4_aes256_cfb128_decrypt)

#else
	ENTRY(t4_aes128_cfb128_decrypt)

	ldd	[%o4], %f56	!IV
	ldd	[%o4 + 8], %f58	!IV
	ldx	[%o0], %g1	! ks[0]
	ldx	[%o0 + 8], %g2	! ks[1]

cfb128dec_128_loop:
	movxtod	%g1, %f60
	movxtod	%g2, %f62
	fxor	%f60, %f56, %f60
	fxor	%f62, %f58, %f62

	/* CFB mode uses encryption for the decrypt operation */
	TEN_EROUNDS

	ldd	[%o1], %f56	!input
	ldd	[%o1 + 8], %f58	!input
	fxor	%f60, %f56, %f60
	fxor	%f62, %f58, %f62

	std	%f60, [%o2]
	std	%f62, [%o2 + 8]

	add	%o1, 16, %o1
	subcc	%o3, 16, %o3
	bne	cfb128dec_128_loop
	add	%o2, 16, %o2

	std	%f56, [%o4]
	retl
	std	%f58, [%o4 + 8]

	SET_SIZE(t4_aes128_cfb128_decrypt)


	ENTRY(t4_aes192_cfb128_decrypt)

	ldd	[%o4], %f56	!IV
	ldd	[%o4 + 8], %f58	!IV
	ldx	[%o0], %g1	! ks[0]
	ldx	[%o0 + 8], %g2	! ks[1]

cfb128dec_192_loop:
	movxtod	%g1, %f60
	movxtod	%g2, %f62
	fxor	%f60, %f56, %f60
	fxor	%f62, %f58, %f62

	/* CFB mode uses encryption for the decrypt operation */
	TWELVE_EROUNDS

	ldd	[%o1], %f56	!input
	ldd	[%o1 + 8], %f58	!input
	fxor	%f60, %f56, %f60
	fxor	%f62, %f58, %f62

	std	%f60, [%o2]
	std	%f62, [%o2 + 8]

	add	%o1, 16, %o1
	subcc	%o3, 16, %o3
	bne	cfb128dec_192_loop
	add	%o2, 16, %o2

	std	%f56, [%o4]
	retl
	std	%f58, [%o4 + 8]

	SET_SIZE(t4_aes192_cfb128_decrypt)


	ENTRY(t4_aes256_cfb128_decrypt)

	ldd	[%o4], %f56	!IV
	ldd	[%o4 + 8], %f58	!IV
	ldx	[%o0], %g1	! ks[0]
	ldx	[%o0 + 8], %g2	! ks[1]

cfb128dec_256_loop:
	movxtod	%g1, %f60
	movxtod	%g2, %f62
	fxor	%f60, %f56, %f60
	fxor	%f62, %f58, %f62

	/* CFB mode uses encryption for the decrypt operation */
	FOURTEEN_EROUNDS

	ldd	[%o1], %f56	!input
	ldd	[%o1 + 8], %f58	!input
	fxor	%f60, %f56, %f60
	fxor	%f62, %f58, %f62

	std	%f60, [%o2]
	std	%f62, [%o2 + 8]

	add	%o1, 16, %o1
	subcc	%o3, 16, %o3
	bne	cfb128dec_256_loop
	add	%o2, 16, %o2

	std	%f56, [%o4]
	retl
	std	%f58, [%o4 + 8]

	SET_SIZE(t4_aes256_cfb128_decrypt)

#endif

#endif	/* lint || __lint */
