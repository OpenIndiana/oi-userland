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
#include <openssl/md5.h>

/*ARGSUSED*/
void
t4_md5_multiblock(MD5_CTX *ctx, const uint8_t *input,
    unsigned int input_length_in_blocks)
{ return; }

#else	/* lint || __lint */

#include<sys/asm_linkage.h>

	ENTRY(t4_md5_multiblock)

!load result from previous digest (stored in ctx)
	ld	[%o0], %f0
	ld	[%o0 + 0x4], %f1
	ld	[%o0 + 0x8], %f2
	ld	[%o0 + 0xc], %f3

	and	%o1, 7, %o3
	brnz	%o3, md5_unaligned_input
	nop

md5_loop:

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
	!md5
	.byte	0x81, 0xb0, 0x28, 0x00

	dec	%o2
	brnz	%o2, md5_loop
	add	%o1, 0x40, %o1

!copy digest back into ctx
	st	%f0, [%o0]
	st	%f1, [%o0 + 0x4]
	st	%f2, [%o0 + 0x8]
	retl
	st	%f3, [%o0 + 0xc]

md5_unaligned_input:
	alignaddr %o1, %g0, %g0		! generate %gsr
	andn	%o1, 7, %o1

md5_unaligned_input_loop:
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
	!md5
	.byte	0x81, 0xb0, 0x28, 0x00

	dec	%o2
	brnz	%o2, md5_unaligned_input_loop
	add	%o1, 0x40, %o1

!copy digest back into ctx
	st	%f0, [%o0]
	st	%f1, [%o0 + 0x4]
	st	%f2, [%o0 + 0x8]
	retl
	st	%f3, [%o0 + 0xc]

	SET_SIZE(t4_md5_multiblock)

#endif  /* lint || __lint */
