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
#include <openssl/sha.h>
#include "../engine/eng_t4_sha2_asm.h"

/*ARGSUSED*/
void
t4_sha256_multiblock(T4_SHA256_CTX *c, const void *input,
	size_t num)
{ return; }

/*ARGSUSED*/
void
t4_sha512_multiblock(T4_SHA512_CTX *c, const void *input,
	size_t num)
{ return; }

#else	/* lint || __lint */

#include<sys/asm_linkage.h>

	ENTRY(t4_sha256_multiblock)

	add	%o0, 0x8, %o0		!skip over first field in ctx

!load result from previous digest (stored in ctx)
	ld	[%o0], %f0
	ld	[%o0 + 0x4], %f1
	ld	[%o0 + 0x8], %f2
	ld	[%o0 + 0xc], %f3
	ld	[%o0 + 0x10], %f4
	ld	[%o0 + 0x14], %f5
	ld	[%o0 + 0x18], %f6
	ld	[%o0 + 0x1c], %f7

	and	%o1, 7, %o3
	brnz	%o3, sha256_unaligned_input
	nop

sha256_loop:

!load 64 bytes of data
	ldd	[%o1], %f8		!load 8 bytes of data
	ldd	[%o1 + 0x8], %f10	!load 8 bytes of data
	ldd	[%o1 + 0x10], %f12	!load 8 bytes of data
	ldd	[%o1 + 0x18], %f14	!load 8 bytes of data
	ldd	[%o1 + 0x20], %f16	!load 8 bytes of data
	ldd	[%o1 + 0x28], %f18	!load 8 bytes of data
	ldd	[%o1 + 0x30], %f20	!load 8 bytes of data
	ldd	[%o1 + 0x38], %f22	!load 8 bytes of data

!perform crypto instruction here
	!sha256
	.byte	0x81, 0xb0, 0x28, 0x40

	dec	%o2
	brnz	%o2, sha256_loop
	add	%o1, 0x40, %o1

!copy digest back into ctx
	st	%f0, [%o0]
	st	%f1, [%o0 + 0x4]
	st	%f2, [%o0 + 0x8]
	st	%f3, [%o0 + 0xc]
	st	%f4, [%o0 + 0x10]
	st	%f5, [%o0 + 0x14]
	st	%f6, [%o0 + 0x18]
	retl
	st	%f7, [%o0 + 0x1c]

sha256_unaligned_input:
	alignaddr %o1, %g0, %g0		! generate %gsr
	andn	%o1, 7, %o1

sha256_unaligned_input_loop:
	ldd	[%o1], %f8		!load 8 bytes of data
	ldd	[%o1 + 0x8], %f10	!load 8 bytes of data
	ldd	[%o1 + 0x10], %f12	!load 8 bytes of data
	ldd	[%o1 + 0x18], %f14	!load 8 bytes of data
	ldd	[%o1 + 0x20], %f16	!load 8 bytes of data
	ldd	[%o1 + 0x28], %f18	!load 8 bytes of data
	ldd	[%o1 + 0x30], %f20	!load 8 bytes of data
	ldd	[%o1 + 0x38], %f22	!load 8 bytes of data
	ldd	[%o1 + 0x40], %f24	!load 8 bytes of data
	faligndata %f8, %f10, %f8
	faligndata %f10, %f12, %f10
	faligndata %f12, %f14, %f12
	faligndata %f14, %f16, %f14
	faligndata %f16, %f18, %f16
	faligndata %f18, %f20, %f18
	faligndata %f20, %f22, %f20
	faligndata %f22, %f24, %f22

!perform crypto instruction here
	!sha256
	.byte	0x81, 0xb0, 0x28, 0x40

	dec	%o2
	brnz	%o2, sha256_unaligned_input_loop
	add	%o1, 0x40, %o1

!copy digest back into ctx
	st	%f0, [%o0]
	st	%f1, [%o0 + 0x4]
	st	%f2, [%o0 + 0x8]
	st	%f3, [%o0 + 0xc]
	st	%f4, [%o0 + 0x10]
	st	%f5, [%o0 + 0x14]
	st	%f6, [%o0 + 0x18]
	retl
	st	%f7, [%o0 + 0x1c]

	SET_SIZE(t4_sha256_multiblock)


	ENTRY(t4_sha512_multiblock)

	add	%o0, 0x8, %o0		!skip over first field in ctx

!load result from previous digest (stored in ctx)
	ld	[%o0], %f0
	ld	[%o0 + 0x4], %f1
	ld	[%o0 + 0x8], %f2
	ld	[%o0 + 0xc], %f3
	ld	[%o0 + 0x10], %f4
	ld	[%o0 + 0x14], %f5
	ld	[%o0 + 0x18], %f6
	ld	[%o0 + 0x1c], %f7
	ld	[%o0 + 0x20], %f8
	ld	[%o0 + 0x24], %f9
	ld	[%o0 + 0x28], %f10
	ld	[%o0 + 0x2c], %f11
	ld	[%o0 + 0x30], %f12
	ld	[%o0 + 0x34], %f13
	ld	[%o0 + 0x38], %f14
	ld	[%o0 + 0x3c], %f15

	and	%o1, 7, %o3
	brnz	%o3, sha512_unaligned_input
	nop

sha512_loop:

!load 128 bytes of data
	ldd	[%o1], %f16		!load 8 bytes of data
	ldd	[%o1 + 0x8], %f18	!load 8 bytes of data
	ldd	[%o1 + 0x10], %f20	!load 8 bytes of data
	ldd	[%o1 + 0x18], %f22	!load 8 bytes of data
	ldd	[%o1 + 0x20], %f24	!load 8 bytes of data
	ldd	[%o1 + 0x28], %f26	!load 8 bytes of data
	ldd	[%o1 + 0x30], %f28	!load 8 bytes of data
	ldd	[%o1 + 0x38], %f30	!load 8 bytes of data
	ldd	[%o1 + 0x40], %f32	!load 8 bytes of data
	ldd	[%o1 + 0x48], %f34	!load 8 bytes of data
	ldd	[%o1 + 0x50], %f36	!load 8 bytes of data
	ldd	[%o1 + 0x58], %f38	!load 8 bytes of data
	ldd	[%o1 + 0x60], %f40	!load 8 bytes of data
	ldd	[%o1 + 0x68], %f42	!load 8 bytes of data
	ldd	[%o1 + 0x70], %f44	!load 8 bytes of data
	ldd	[%o1 + 0x78], %f46	!load 8 bytes of data

!perform crypto instruction here
	!sha512
	.byte	0x81, 0xb0, 0x28, 0x60

	dec	%o2
	brnz	%o2, sha512_loop
	add	%o1, 0x80, %o1

!copy digest back into ctx
	st	%f0, [%o0]
	st	%f1, [%o0 + 0x4]
	st	%f2, [%o0 + 0x8]
	st	%f3, [%o0 + 0xc]
	st	%f4, [%o0 + 0x10]
	st	%f5, [%o0 + 0x14]
	st	%f6, [%o0 + 0x18]
	st	%f7, [%o0+ 0x1c]
	st	%f8, [%o0+ 0x20]
	st	%f9, [%o0+ 0x24]
	st	%f10, [%o0+ 0x28]
	st	%f11, [%o0+ 0x2c]
	st	%f12, [%o0+ 0x30]
	st	%f13, [%o0+ 0x34]
	st	%f14, [%o0+ 0x38]
	retl
	st	%f15, [%o0+ 0x3c]

sha512_unaligned_input:
	alignaddr %o1, %g0, %g0		! generate %gsr
	andn	%o1, 7, %o1

sha512_unaligned_input_loop:
	ldd	[%o1], %f16		!load 8 bytes of data
	ldd	[%o1 + 0x8], %f18	!load 8 bytes of data
	ldd	[%o1 + 0x10], %f20	!load 8 bytes of data
	ldd	[%o1 + 0x18], %f22	!load 8 bytes of data
	ldd	[%o1 + 0x20], %f24	!load 8 bytes of data
	ldd	[%o1 + 0x28], %f26	!load 8 bytes of data
	ldd	[%o1 + 0x30], %f28	!load 8 bytes of data
	ldd	[%o1 + 0x38], %f30	!load 8 bytes of data
	ldd	[%o1 + 0x40], %f32	!load 8 bytes of data
	ldd	[%o1 + 0x48], %f34	!load 8 bytes of data
	ldd	[%o1 + 0x50], %f36	!load 8 bytes of data
	ldd	[%o1 + 0x58], %f38	!load 8 bytes of data
	ldd	[%o1 + 0x60], %f40	!load 8 bytes of data
	ldd	[%o1 + 0x68], %f42	!load 8 bytes of data
	ldd	[%o1 + 0x70], %f44	!load 8 bytes of data
	ldd	[%o1 + 0x78], %f46	!load 8 bytes of data
	ldd	[%o1 + 0x80], %f48	!load 8 bytes of data
	faligndata %f16, %f18, %f16
	faligndata %f18, %f20, %f18
	faligndata %f20, %f22, %f20
	faligndata %f22, %f24, %f22
	faligndata %f24, %f26, %f24
	faligndata %f26, %f28, %f26
	faligndata %f28, %f30, %f28
	faligndata %f30, %f32, %f30
	faligndata %f32, %f34, %f32
	faligndata %f34, %f36, %f34
	faligndata %f36, %f38, %f36
	faligndata %f38, %f40, %f38
	faligndata %f40, %f42, %f40
	faligndata %f42, %f44, %f42
	faligndata %f44, %f46, %f44
	faligndata %f46, %f48, %f46

!perform crypto instruction here
	!sha512
	.byte	0x81, 0xb0, 0x28, 0x60

	dec	%o2
	brnz	%o2, sha512_unaligned_input_loop
	add	%o1, 0x80, %o1

!copy digest back into ctx
	st	%f0, [%o0]
	st	%f1, [%o0 + 0x4]
	st	%f2, [%o0 + 0x8]
	st	%f3, [%o0 + 0xc]
	st	%f4, [%o0 + 0x10]
	st	%f5, [%o0 + 0x14]
	st	%f6, [%o0 + 0x18]
	st	%f7, [%o0+ 0x1c]
	st	%f8, [%o0+ 0x20]
	st	%f9, [%o0+ 0x24]
	st	%f10, [%o0+ 0x28]
	st	%f11, [%o0+ 0x2c]
	st	%f12, [%o0+ 0x30]
	st	%f13, [%o0+ 0x34]
	st	%f14, [%o0+ 0x38]
	retl
	st	%f15, [%o0+ 0x3c]

	SET_SIZE(t4_sha512_multiblock)

#endif  /* lint || __lint */
