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

/*LINTLIBRARY*/

#if defined(lint) || defined(__lint)

#include <sys/types.h>
#include "../engine/eng_t4_des_asm.h"

/*ARGSUSED*/
void t4_des_expand(uint64_t *rk, const uint32_t *key)
{ return; }

/*ARGSUSED*/
void t4_des_encrypt(const uint64_t *rk, const uint64_t *pt, uint64_t *ct)
{ return; }


/*ARGSUSED*/
void t4_des_load_keys(uint64_t *ks)
{ return; }

/*ARGSUSED*/
void t4_des_ecb_crypt(uint64_t *ks, uint64_t *asm_in,
    uint64_t *asm_out, size_t amount_to_crypt, uint64_t *iv)
{ return; }

/*ARGSUSED*/
void t4_des_cbc_encrypt(uint64_t *ks, uint64_t *asm_in,
    uint64_t *asm_out, size_t amount_to_crypt, uint64_t *iv)
{ return; }

/*ARGSUSED*/
void t4_des_cbc_decrypt(uint64_t *ks, uint64_t *asm_in,
    uint64_t *asm_out, size_t amount_to_crypt, uint64_t *iv)
{ return; }

/*ARGSUSED*/
void t4_des3_load_keys(uint64_t *ks)
{ return; }

/*ARGSUSED*/
void t4_des3_ecb_crypt(uint64_t *ks, uint64_t *asm_in,
    uint64_t *asm_out, size_t amount_to_crypt, uint64_t *iv)
{ return; }

/*ARGSUSED*/
void t4_des3_cbc_encrypt(uint64_t *ks, uint64_t *asm_in,
    uint64_t *asm_out, size_t amount_to_crypt, uint64_t *iv)
{ return; }

/*ARGSUSED*/
void t4_des3_cbc_decrypt(uint64_t *ks, uint64_t *asm_in,
    uint64_t *asm_out, size_t amount_to_crypt, uint64_t *iv)
{ return; }

#else	/* lint || __lint */

#include <sys/asm_linkage.h>


	ENTRY(t4_des_expand)

!load key
	ld	[%o1], %f0
	ld	[%o1 + 0x4], %f1

!expand the key
	!des_kexpand %f0, 0, %f0
	!des_kexpand %f0, 1, %f2
	!des_kexpand %f2, 3, %f6
	!des_kexpand %f2, 2, %f4
	!des_kexpand %f6, 3, %f10
	!des_kexpand %f6, 2, %f8
	!des_kexpand %f10, 3, %f14
	!des_kexpand %f10, 2, %f12
	!des_kexpand %f14, 1, %f16
	!des_kexpand %f16, 3, %f20
	!des_kexpand %f16, 2, %f18
	!des_kexpand %f20, 3, %f24
	!des_kexpand %f20, 2, %f22
	!des_kexpand %f24, 3, %f28
	!des_kexpand %f24, 2, %f26
	!des_kexpand %f28, 1, %f30
	.byte	0x81, 0xb0, 0x26, 0xc0
	.byte	0x85, 0xb0, 0x26, 0xc1
	.byte	0x8d, 0xb0, 0xa6, 0xc3
	.byte	0x89, 0xb0, 0xa6, 0xc2
	.byte	0x95, 0xb1, 0xa6, 0xc3
	.byte	0x91, 0xb1, 0xa6, 0xc2
	.byte	0x9d, 0xb2, 0xa6, 0xc3
	.byte	0x99, 0xb2, 0xa6, 0xc2
	.byte	0xa1, 0xb3, 0xa6, 0xc1
	.byte	0xa9, 0xb4, 0x26, 0xc3
	.byte	0xa5, 0xb4, 0x26, 0xc2
	.byte	0xb1, 0xb5, 0x26, 0xc3
	.byte	0xad, 0xb5, 0x26, 0xc2
	.byte	0xb9, 0xb6, 0x26, 0xc3
	.byte	0xb5, 0xb6, 0x26, 0xc2
	.byte	0xbd, 0xb7, 0x26, 0xc1

!copy expanded key back into array
	std	%f0, [%o0]
	std	%f2, [%o0 + 0x8]
	std	%f4, [%o0 + 0x10]
	std	%f6, [%o0 + 0x18]
	std	%f8, [%o0 + 0x20]
	std	%f10, [%o0 + 0x28]
	std	%f12, [%o0 + 0x30]
	std	%f14, [%o0 + 0x38]
	std	%f16, [%o0 + 0x40]
	std	%f18, [%o0 + 0x48]
	std	%f20, [%o0 + 0x50]
	std	%f22, [%o0 + 0x58]
	std	%f24, [%o0 + 0x60]
	std	%f26, [%o0 + 0x68]
	std	%f28, [%o0 + 0x70]
	retl
	std	%f30, [%o0 + 0x78]

	SET_SIZE(t4_des_expand)


	ENTRY(t4_des_encrypt)

!load expanded key
	ldd	[%o0], %f0
	ldd	[%o0 + 0x8], %f2
	ldd	[%o0 + 0x10], %f4
	ldd	[%o0 + 0x18], %f6
	ldd	[%o0 + 0x20], %f8
	ldd	[%o0 + 0x28], %f10
	ldd	[%o0 + 0x30], %f12
	ldd	[%o0 + 0x38], %f14
	ldd	[%o0 + 0x40], %f16
	ldd	[%o0 + 0x48], %f18
	ldd	[%o0 + 0x50], %f20
	ldd	[%o0 + 0x58], %f22
	ldd	[%o0 + 0x60], %f24
	ldd	[%o0 + 0x68], %f26
	ldd	[%o0 + 0x70], %f28
	ldd	[%o0 + 0x78], %f30

!load input
	ldd	[%o1], %f32

!perform the cipher transformation
	!des_ip	%f32, %f32
	!des_round %f0,  %f2,  %f32, %f32
	!des_round %f4,  %f6,  %f32, %f32
	!des_round %f8,  %f10, %f32, %f32
	!des_round %f12, %f14, %f32, %f32
	!des_round %f16, %f18, %f32, %f32
	!des_round %f20, %f22, %f32, %f32
	!des_round %f24, %f26, %f32, %f32
	!des_round %f28, %f30, %f32, %f32
	!des_iip	%f32, %f32
	.byte	0x83, 0xb0, 0x66, 0x80
	.byte	0x82, 0xc8, 0x03, 0x22
	.byte	0x82, 0xc9, 0x03, 0x26
	.byte	0x82, 0xca, 0x03, 0x2a
	.byte	0x82, 0xcb, 0x03, 0x2e
	.byte	0x82, 0xcc, 0x03, 0x32
	.byte	0x82, 0xcd, 0x03, 0x36
	.byte	0x82, 0xce, 0x03, 0x3a
	.byte	0x82, 0xcf, 0x03, 0x3e
	.byte	0x83, 0xb0, 0x66, 0xa0

!copy output back to array
	retl
	std	%f32, [%o2]

	SET_SIZE(t4_des_encrypt)

	ENTRY(t4_des_load_keys)

!load expanded key
	ldd	[%o0], %f0
	ldd	[%o0 + 0x8], %f2
	ldd	[%o0 + 0x10], %f4
	ldd	[%o0 + 0x18], %f6
	ldd	[%o0 + 0x20], %f8
	ldd	[%o0 + 0x28], %f10
	ldd	[%o0 + 0x30], %f12
	ldd	[%o0 + 0x38], %f14
	ldd	[%o0 + 0x40], %f16
	ldd	[%o0 + 0x48], %f18
	ldd	[%o0 + 0x50], %f20
	ldd	[%o0 + 0x58], %f22
	ldd	[%o0 + 0x60], %f24
	ldd	[%o0 + 0x68], %f26
	ldd	[%o0 + 0x70], %f28
	retl
	ldd	[%o0 + 0x78], %f30

	SET_SIZE(t4_des_load_keys)

	ENTRY(t4_des3_load_keys)

!load first 30 pieces of the expanded key
	ldd	[%o0], %f0
	ldd	[%o0 + 0x8], %f2
	ldd	[%o0 + 0x10], %f4
	ldd	[%o0 + 0x18], %f6
	ldd	[%o0 + 0x20], %f8
	ldd	[%o0 + 0x28], %f10
	ldd	[%o0 + 0x30], %f12
	ldd	[%o0 + 0x38], %f14
	ldd	[%o0 + 0x40], %f16
	ldd	[%o0 + 0x48], %f18
	ldd	[%o0 + 0x50], %f20
	ldd	[%o0 + 0x58], %f22
	ldd	[%o0 + 0x60], %f24
	ldd	[%o0 + 0x68], %f26
	ldd	[%o0 + 0x70], %f28
	ldd	[%o0 + 0x78], %f30
	ldd	[%o0 + 0x80], %f32
	ldd	[%o0 + 0x88], %f34
	ldd	[%o0 + 0x90], %f36
	ldd	[%o0 + 0x98], %f38
	ldd	[%o0 + 0xa0], %f40
	ldd	[%o0 + 0xa8], %f42
	ldd	[%o0 + 0xb0], %f44
	ldd	[%o0 + 0xb8], %f46
	ldd	[%o0 + 0xc0], %f48
	ldd	[%o0 + 0xc8], %f50
	ldd	[%o0 + 0xd0], %f52
	ldd	[%o0 + 0xd8], %f54
	ldd	[%o0 + 0xe0], %f56
	retl
	ldd	[%o0 + 0xe8], %f58

	SET_SIZE(t4_des3_load_keys)

	ENTRY(t4_des_ecb_crypt)

des_ecb_loop:
!load input
	ldd	[%o1], %f62

!perform the cipher transformation
	!des_ip	%f62, %f62
	!des_round %f0,  %f2,  %f62, %f62
	!des_round %f4,  %f6,  %f62, %f62
	!des_round %f8,  %f10, %f62, %f62
	!des_round %f12, %f14, %f62, %f62
	!des_round %f16, %f18, %f62, %f62
	!des_round %f20, %f22, %f62, %f62
	!des_round %f24, %f26, %f62, %f62
	!des_round %f28, %f30, %f62, %f62
	!des_iip	%f62, %f62
	.byte	0xbf, 0xb7, 0xe6, 0x80
	.byte	0xbe, 0xc8, 0x3f, 0x22
	.byte	0xbe, 0xc9, 0x3f, 0x26
	.byte	0xbe, 0xca, 0x3f, 0x2a
	.byte	0xbe, 0xcb, 0x3f, 0x2e
	.byte	0xbe, 0xcc, 0x3f, 0x32
	.byte	0xbe, 0xcd, 0x3f, 0x36
	.byte	0xbe, 0xce, 0x3f, 0x3a
	.byte	0xbe, 0xcf, 0x3f, 0x3e
	.byte	0xbf, 0xb7, 0xe6, 0xa0

!copy output back to array
	std	%f62, [%o2]
	sub	%o3, 8, %o3
	add	%o1, 8, %o1
	brnz	%o3, des_ecb_loop
	add	%o2, 8, %o2

	retl
	nop

	SET_SIZE(t4_des_ecb_crypt)


	ENTRY(t4_des_cbc_encrypt)

	ldd	[%o4], %f60
des_cbc_encrypt_loop:
!load input
	ldd	[%o1], %f58
	fxor	%f58, %f60, %f62

!perform the cipher transformation
	!des_ip	%f62, %f62
	!des_round %f0,  %f2,  %f62, %f62
	!des_round %f4,  %f6,  %f62, %f62
	!des_round %f8,  %f10, %f62, %f62
	!des_round %f12, %f14, %f62, %f62
	!des_round %f16, %f18, %f62, %f62
	!des_round %f20, %f22, %f62, %f62
	!des_round %f24, %f26, %f62, %f62
	!des_round %f28, %f30, %f62, %f62
	!des_iip	%f62, %f60
	.byte	0xbf, 0xb7, 0xe6, 0x80
	.byte	0xbe, 0xc8, 0x3f, 0x22
	.byte	0xbe, 0xc9, 0x3f, 0x26
	.byte	0xbe, 0xca, 0x3f, 0x2a
	.byte	0xbe, 0xcb, 0x3f, 0x2e
	.byte	0xbe, 0xcc, 0x3f, 0x32
	.byte	0xbe, 0xcd, 0x3f, 0x36
	.byte	0xbe, 0xce, 0x3f, 0x3a
	.byte	0xbe, 0xcf, 0x3f, 0x3e
	.byte	0xbb, 0xb7, 0xe6, 0xa0

!copy output back to array
	std	%f60, [%o2]
	sub	%o3, 8, %o3
	add	%o1, 8, %o1
	brnz	%o3, des_cbc_encrypt_loop
	add	%o2, 8, %o2

	retl
	std	%f60, [%o4]

	SET_SIZE(t4_des_cbc_encrypt)



	ENTRY(t4_des_cbc_decrypt)

	ldd	[%o4], %f60
des_cbc_decrypt_loop:
!load input
	ldd	[%o1], %f62
	ldx	[%o1], %o5

!perform the cipher transformation
	!des_ip	%f62, %f62
	!des_round %f0,  %f2,  %f62, %f62
	!des_round %f4,  %f6,  %f62, %f62
	!des_round %f8,  %f10, %f62, %f62
	!des_round %f12, %f14, %f62, %f62
	!des_round %f16, %f18, %f62, %f62
	!des_round %f20, %f22, %f62, %f62
	!des_round %f24, %f26, %f62, %f62
	!des_round %f28, %f30, %f62, %f62
	!des_iip	%f62, %f62
	.byte	0xbf, 0xb7, 0xe6, 0x80
	.byte	0xbe, 0xc8, 0x3f, 0x22
	.byte	0xbe, 0xc9, 0x3f, 0x26
	.byte	0xbe, 0xca, 0x3f, 0x2a
	.byte	0xbe, 0xcb, 0x3f, 0x2e
	.byte	0xbe, 0xcc, 0x3f, 0x32
	.byte	0xbe, 0xcd, 0x3f, 0x36
	.byte	0xbe, 0xce, 0x3f, 0x3a
	.byte	0xbe, 0xcf, 0x3f, 0x3e
	.byte	0xbf, 0xb7, 0xe6, 0xa0
	fxor	%f60, %f62, %f62
	movxtod	%o5, %f60

!copy output back to array
	std	%f62, [%o2]
	sub	%o3, 8, %o3
	add	%o1, 8, %o1
	brnz	%o3, des_cbc_decrypt_loop
	add	%o2, 8, %o2

	retl
	std	%f60, [%o4]

	SET_SIZE(t4_des_cbc_decrypt)



	ENTRY(t4_des3_ecb_crypt)

des3_ecb_loop:
!load input
	ldd	[%o1], %f62

!perform the cipher transformation
	!des_ip	%f62, %f62
	!des_round %f0,  %f2,  %f62, %f62
	!des_round %f4,  %f6,  %f62, %f62
	!des_round %f8,  %f10, %f62, %f62
	!des_round %f12, %f14, %f62, %f62
	!des_round %f16, %f18, %f62, %f62
	.byte	0xbf, 0xb7, 0xe6, 0x80
	.byte	0xbe, 0xc8, 0x3f, 0x22
	.byte	0xbe, 0xc9, 0x3f, 0x26
	.byte	0xbe, 0xca, 0x3f, 0x2a
	.byte	0xbe, 0xcb, 0x3f, 0x2e
	.byte	0xbe, 0xcc, 0x3f, 0x32

	ldd	[%o0 + 0xf0], %f16
	ldd	[%o0 + 0xf8], %f18
	!des_round %f20, %f22, %f62, %f62
	.byte	0xbe, 0xcd, 0x3f, 0x36
	ldd	[%o0 + 0x100], %f20
	ldd	[%o0 + 0x108], %f22
	!des_round %f24, %f26, %f62, %f62
	.byte	0xbe, 0xce, 0x3f, 0x3a
	ldd	[%o0 + 0x110], %f24
	ldd	[%o0 + 0x118], %f26
	!des_round %f28, %f30, %f62, %f62
	.byte	0xbe, 0xcf, 0x3f, 0x3e
	ldd	[%o0 + 0x120], %f28
	ldd	[%o0 + 0x128], %f30

	!des_iip	%f62, %f62
	!des_ip	%f62, %f62
	.byte	0xbf, 0xb7, 0xe6, 0xa0
	.byte	0xbf, 0xb7, 0xe6, 0x80

	!des_round %f32, %f34, %f62, %f62
	.byte	0xbe, 0xc8, 0x7f, 0x23
	ldd	[%o0 + 0x130], %f0
	ldd	[%o0 + 0x138], %f2
	!des_round %f36, %f38,  %f62, %f62
	.byte	0xbe, 0xc9, 0x7f, 0x27
	ldd	[%o0 + 0x140], %f4
	ldd	[%o0 + 0x148], %f6
	!des_round %f40, %f42, %f62, %f62
	.byte	0xbe, 0xca, 0x7f, 0x2b
	ldd	[%o0 + 0x150], %f8
	ldd	[%o0 + 0x158], %f10
	!des_round %f44, %f46, %f62, %f62
	.byte	0xbe, 0xcb, 0x7f, 0x2f
	ldd	[%o0 + 0x160], %f12
	ldd	[%o0 + 0x168], %f14
	!des_round %f48, %f50, %f62, %f62
	!des_round %f52, %f54, %f62, %f62
	!des_round %f56, %f58, %f62, %f62
	!des_round %f16, %f18, %f62, %f62
	.byte	0xbe, 0xcc, 0x7f, 0x33
	.byte	0xbe, 0xcd, 0x7f, 0x37
	.byte	0xbe, 0xce, 0x7f, 0x3b
	.byte	0xbe, 0xcc, 0x3f, 0x32
	ldd	[%o0 + 0x170], %f16
	ldd	[%o0 + 0x178], %f18

	!des_iip	%f62, %f62
	!des_ip	%f62, %f62
	.byte	0xbf, 0xb7, 0xe6, 0xa0
	.byte	0xbf, 0xb7, 0xe6, 0x80

	!des_round %f20, %f22, %f62, %f62
	.byte	0xbe, 0xcd, 0x3f, 0x36
	ldd	[%o0 + 0x50], %f20
	ldd	[%o0 + 0x58], %f22
	!des_round %f24, %f26, %f62, %f62
	.byte	0xbe, 0xce, 0x3f, 0x3a
	ldd	[%o0 + 0x60], %f24
	ldd	[%o0 + 0x68], %f26
	!des_round %f28, %f30, %f62, %f62
	.byte	0xbe, 0xcf, 0x3f, 0x3e
	ldd	[%o0 + 0x70], %f28
	ldd	[%o0 + 0x78], %f30
	!des_round %f0,  %f2,  %f62, %f62
	.byte	0xbe, 0xc8, 0x3f, 0x22
	ldd	[%o0], %f0
	ldd	[%o0 + 0x8], %f2
	!des_round %f4,  %f6,  %f62, %f62
	.byte	0xbe, 0xc9, 0x3f, 0x26

	ldd	[%o0 + 0x10], %f4
	ldd	[%o0 + 0x18], %f6
	!des_round %f8,  %f10, %f62, %f62
	.byte	0xbe, 0xca, 0x3f, 0x2a
	ldd	[%o0 + 0x20], %f8
	ldd	[%o0 + 0x28], %f10
	!des_round %f12, %f14, %f62, %f62
	.byte	0xbe, 0xcb, 0x3f, 0x2e
	ldd	[%o0 + 0x30], %f12
	ldd	[%o0 + 0x38], %f14
	!des_round %f16, %f18, %f62, %f62
	.byte	0xbe, 0xcc, 0x3f, 0x32
	ldd	[%o0 + 0x40], %f16
	ldd	[%o0 + 0x48], %f18

	!des_iip	%f62, %f62
	.byte	0xbf, 0xb7, 0xe6, 0xa0

!copy output back to array
	std	%f62, [%o2]
	sub	%o3, 8, %o3
	add	%o1, 8, %o1
	brnz	%o3, des3_ecb_loop
	add	%o2, 8, %o2

	retl
	nop

	SET_SIZE(t4_des3_ecb_crypt)


	ENTRY(t4_des3_cbc_encrypt)

	ldd	[%o4], %f62
des3_cbc_encrypt_loop:
!load input
	ldd	[%o1], %f60
	fxor	%f60, %f62, %f62

!perform the cipher transformation
	!des_ip	%f62, %f62
	.byte	0xbf, 0xb7, 0xe6, 0x80
	!des_round %f0,  %f2,  %f62, %f62
	!des_round %f4,  %f6,  %f62, %f62
	!des_round %f8,  %f10, %f62, %f62
	!des_round %f12, %f14, %f62, %f62
	!des_round %f16, %f18, %f62, %f62
	.byte	0xbe, 0xc8, 0x3f, 0x22
	.byte	0xbe, 0xc9, 0x3f, 0x26
	.byte	0xbe, 0xca, 0x3f, 0x2a
	.byte	0xbe, 0xcb, 0x3f, 0x2e
	.byte	0xbe, 0xcc, 0x3f, 0x32
	ldd	[%o0 + 0xf0], %f16
	ldd	[%o0 + 0xf8], %f18
	!des_round %f20, %f22, %f62, %f62
	.byte	0xbe, 0xcd, 0x3f, 0x36
	ldd	[%o0 + 0x100], %f20
	ldd	[%o0 + 0x108], %f22
	!des_round %f24, %f26, %f62, %f62
	.byte	0xbe, 0xce, 0x3f, 0x3a
	ldd	[%o0 + 0x110], %f24
	ldd	[%o0 + 0x118], %f26
	!des_round %f28, %f30, %f62, %f62
	.byte	0xbe, 0xcf, 0x3f, 0x3e
	ldd	[%o0 + 0x120], %f28
	ldd	[%o0 + 0x128], %f30

	!des_iip	%f62, %f62
	!des_ip	%f62, %f62
	.byte	0xbf, 0xb7, 0xe6, 0xa0
	.byte	0xbf, 0xb7, 0xe6, 0x80

	!des_round %f32, %f34, %f62, %f62
	.byte	0xbe, 0xc8, 0x7f, 0x23
	ldd	[%o0 + 0x130], %f0
	ldd	[%o0 + 0x138], %f2
	!des_round %f36, %f38,  %f62, %f62
	.byte	0xbe, 0xc9, 0x7f, 0x27
	ldd	[%o0 + 0x140], %f4
	ldd	[%o0 + 0x148], %f6
	!des_round %f40, %f42, %f62, %f62
	.byte	0xbe, 0xca, 0x7f, 0x2b
	ldd	[%o0 + 0x150], %f8
	ldd	[%o0 + 0x158], %f10
	!des_round %f44, %f46, %f62, %f62
	.byte	0xbe, 0xcb, 0x7f, 0x2f
	ldd	[%o0 + 0x160], %f12
	ldd	[%o0 + 0x168], %f14
	!des_round %f48, %f50, %f62, %f62
	!des_round %f52, %f54, %f62, %f62
	!des_round %f56, %f58, %f62, %f62
	!des_round %f16, %f18, %f62, %f62
	.byte	0xbe, 0xcc, 0x7f, 0x33
	.byte	0xbe, 0xcd, 0x7f, 0x37
	.byte	0xbe, 0xce, 0x7f, 0x3b
	.byte	0xbe, 0xcc, 0x3f, 0x32
	ldd	[%o0 + 0x170], %f16
	ldd	[%o0 + 0x178], %f18

	!des_iip	%f62, %f62
	!des_ip	%f62, %f62
	.byte	0xbf, 0xb7, 0xe6, 0xa0
	.byte	0xbf, 0xb7, 0xe6, 0x80

	!des_round %f20, %f22, %f62, %f62
	.byte	0xbe, 0xcd, 0x3f, 0x36
	ldd	[%o0 + 0x50], %f20
	ldd	[%o0 + 0x58], %f22
	!des_round %f24, %f26, %f62, %f62
	.byte	0xbe, 0xce, 0x3f, 0x3a
	ldd	[%o0 + 0x60], %f24
	ldd	[%o0 + 0x68], %f26
	!des_round %f28, %f30, %f62, %f62
	.byte	0xbe, 0xcf, 0x3f, 0x3e
	ldd	[%o0 + 0x70], %f28
	ldd	[%o0 + 0x78], %f30
	!des_round %f0,  %f2,  %f62, %f62
	.byte	0xbe, 0xc8, 0x3f, 0x22
	ldd	[%o0], %f0
	ldd	[%o0 + 0x8], %f2
	!des_round %f4,  %f6,  %f62, %f62
	.byte	0xbe, 0xc9, 0x3f, 0x26
	ldd	[%o0 + 0x10], %f4
	ldd	[%o0 + 0x18], %f6
	!des_round %f8,  %f10, %f62, %f62
	.byte	0xbe, 0xca, 0x3f, 0x2a
	ldd	[%o0 + 0x20], %f8
	ldd	[%o0 + 0x28], %f10
	!des_round %f12, %f14, %f62, %f62
	.byte	0xbe, 0xcb, 0x3f, 0x2e
	ldd	[%o0 + 0x30], %f12
	ldd	[%o0 + 0x38], %f14
	!des_round %f16, %f18, %f62, %f62
	.byte	0xbe, 0xcc, 0x3f, 0x32
	ldd	[%o0 + 0x40], %f16
	ldd	[%o0 + 0x48], %f18

	!des_iip	%f62, %f62
	.byte	0xbf, 0xb7, 0xe6, 0xa0

!copy output back to array
	std	%f62, [%o2]
	sub	%o3, 8, %o3
	add	%o1, 8, %o1
	brnz	%o3, des3_cbc_encrypt_loop
	add	%o2, 8, %o2

	retl
	std	%f62, [%o4]

	SET_SIZE(t4_des3_cbc_encrypt)


	ENTRY(t4_des3_cbc_decrypt)

	ldd	[%o4], %f60
des3_cbc_decrypt_loop:
!load input
	ldx	[%o1], %o5
	movxtod	%o5, %f62

!perform the cipher transformation
	!des_ip	%f62, %f62
	.byte	0xbf, 0xb7, 0xe6, 0x80
	!des_round %f0,  %f2,  %f62, %f62
	!des_round %f4,  %f6,  %f62, %f62
	!des_round %f8,  %f10, %f62, %f62
	!des_round %f12, %f14, %f62, %f62
	!des_round %f16, %f18, %f62, %f62
	.byte	0xbe, 0xc8, 0x3f, 0x22
	.byte	0xbe, 0xc9, 0x3f, 0x26
	.byte	0xbe, 0xca, 0x3f, 0x2a
	.byte	0xbe, 0xcb, 0x3f, 0x2e
	.byte	0xbe, 0xcc, 0x3f, 0x32
	ldd	[%o0 + 0xf0], %f16
	ldd	[%o0 + 0xf8], %f18
	!des_round %f20, %f22, %f62, %f62
	.byte	0xbe, 0xcd, 0x3f, 0x36
	ldd	[%o0 + 0x100], %f20
	ldd	[%o0 + 0x108], %f22
	!des_round %f24, %f26, %f62, %f62
	.byte	0xbe, 0xce, 0x3f, 0x3a
	ldd	[%o0 + 0x110], %f24
	ldd	[%o0 + 0x118], %f26
	!des_round %f28, %f30, %f62, %f62
	.byte	0xbe, 0xcf, 0x3f, 0x3e
	ldd	[%o0 + 0x120], %f28
	ldd	[%o0 + 0x128], %f30

	!des_iip	%f62, %f62
	!des_ip	%f62, %f62
	.byte	0xbf, 0xb7, 0xe6, 0xa0
	.byte	0xbf, 0xb7, 0xe6, 0x80

	!des_round %f32, %f34, %f62, %f62
	.byte	0xbe, 0xc8, 0x7f, 0x23
	ldd	[%o0 + 0x130], %f0
	ldd	[%o0 + 0x138], %f2
	!des_round %f36, %f38,  %f62, %f62
	.byte	0xbe, 0xc9, 0x7f, 0x27
	ldd	[%o0 + 0x140], %f4
	ldd	[%o0 + 0x148], %f6
	!des_round %f40, %f42, %f62, %f62
	.byte	0xbe, 0xca, 0x7f, 0x2b
	ldd	[%o0 + 0x150], %f8
	ldd	[%o0 + 0x158], %f10
	!des_round %f44, %f46, %f62, %f62
	.byte	0xbe, 0xcb, 0x7f, 0x2f
	ldd	[%o0 + 0x160], %f12
	ldd	[%o0 + 0x168], %f14
	!des_round %f48, %f50, %f62, %f62
	!des_round %f52, %f54, %f62, %f62
	!des_round %f56, %f58, %f62, %f62
	!des_round %f16, %f18, %f62, %f62
	.byte	0xbe, 0xcc, 0x7f, 0x33
	.byte	0xbe, 0xcd, 0x7f, 0x37
	.byte	0xbe, 0xce, 0x7f, 0x3b
	.byte	0xbe, 0xcc, 0x3f, 0x32
	ldd	[%o0 + 0x170], %f16
	ldd	[%o0 + 0x178], %f18

	!des_iip	%f62, %f62
	!des_ip	%f62, %f62
	.byte	0xbf, 0xb7, 0xe6, 0xa0
	.byte	0xbf, 0xb7, 0xe6, 0x80

	!des_round %f20, %f22, %f62, %f62
	.byte	0xbe, 0xcd, 0x3f, 0x36
	ldd	[%o0 + 0x50], %f20
	ldd	[%o0 + 0x58], %f22
	!des_round %f24, %f26, %f62, %f62
	.byte	0xbe, 0xce, 0x3f, 0x3a
	ldd	[%o0 + 0x60], %f24
	ldd	[%o0 + 0x68], %f26
	!des_round %f28, %f30, %f62, %f62
	.byte	0xbe, 0xcf, 0x3f, 0x3e
	ldd	[%o0 + 0x70], %f28
	ldd	[%o0 + 0x78], %f30
	!des_round %f0,  %f2,  %f62, %f62
	.byte	0xbe, 0xc8, 0x3f, 0x22
	ldd	[%o0], %f0
	ldd	[%o0 + 0x8], %f2
	!des_round %f4,  %f6,  %f62, %f62
	.byte	0xbe, 0xc9, 0x3f, 0x26
	ldd	[%o0 + 0x10], %f4
	ldd	[%o0 + 0x18], %f6
	!des_round %f8,  %f10, %f62, %f62
	.byte	0xbe, 0xca, 0x3f, 0x2a
	ldd	[%o0 + 0x20], %f8
	ldd	[%o0 + 0x28], %f10
	!des_round %f12, %f14, %f62, %f62
	.byte	0xbe, 0xcb, 0x3f, 0x2e
	ldd	[%o0 + 0x30], %f12
	ldd	[%o0 + 0x38], %f14
	!des_round %f16, %f18, %f62, %f62
	.byte	0xbe, 0xcc, 0x3f, 0x32
	ldd	[%o0 + 0x40], %f16
	ldd	[%o0 + 0x48], %f18

	!des_iip	%f62, %f62
	.byte	0xbf, 0xb7, 0xe6, 0xa0
	fxor	%f60, %f62, %f62
	movxtod	%o5, %f60

!copy output back to array
	std	%f62, [%o2]
	sub	%o3, 8, %o3
	add	%o1, 8, %o1
	brnz	%o3, des3_cbc_decrypt_loop
	add	%o2, 8, %o2

	retl
	stx	%o5, [%o4]

	SET_SIZE(t4_des3_cbc_decrypt)


#endif  /* lint || __lint */
