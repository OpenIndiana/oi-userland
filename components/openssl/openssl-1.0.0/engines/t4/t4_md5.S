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
#include <sys/md5.h>

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
