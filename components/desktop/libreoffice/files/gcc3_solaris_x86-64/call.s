/*
 * This file is part of the LibreOffice project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This file incorporates work covered by the following license notice:
 *
 *   Licensed to the Apache Software Foundation (ASF) under one or more
 *   contributor license agreements. See the NOTICE file distributed
 *   with this work for additional information regarding copyright
 *   ownership. The ASF licenses this file to you under the Apache
 *   License, Version 2.0 (the "License"); you may not use this file
 *   except in compliance with the License. You may obtain a copy of
 *   the License at http://www.apache.org/licenses/LICENSE-2.0 .
 */

	.extern cpp_vtable_call 		# probably unnecessary
	.text
	.align 2
.globl asm_vtable_call_wrapper
	.type	asm_vtable_call_wrapper, @function
asm_vtable_call_wrapper:
.LFB3:
	pushq	%rbp
.LCFI0:
	movq	%rsp, %rbp
.LCFI1:
	subq	$0x80, %rsp
.LCFI2:
	movq	%r10, -0x08(%rbp)		# Save (nVtableOffset << 32) + nFunctionIndex

	# General purpose registers 
	movq	%rdi, -0x80(%rbp)		# rdi = arg1 = this
	movq	%rsi, -0x78(%rbp)		# rsi = arg2
	movq	%rdx, -0x70(%rbp)		# ...
	movq	%rcx, -0x68(%rbp)
	movq	%r8 , -0x60(%rbp)
	movq	%r9 , -0x58(%rbp)
	
	# FP/SSE registers
	movsd	%xmm0, -0x50(%rbp)		
	movsd	%xmm1, -0x48(%rbp)
	movsd	%xmm2, -0x40(%rbp)
	movsd	%xmm3, -0x38(%rbp)
	movsd	%xmm4, -0x30(%rbp)
	movsd	%xmm5, -0x28(%rbp)
	movsd	%xmm6, -0x20(%rbp)
	movsd	%xmm7, -0x18(%rbp)

	# pCallStack = [ret ptr], this, params
	leaq	-0x88(%rbp), %rdx		# 3rd param: void ** pCallStack
	movl	-0x04(%rbp), %esi		# 2nd param: sal_int32 nVtableOffset
	movl	-0x08(%rbp), %edi		# 1st param: sal_int32 nFunctionIndex
	
	call	cpp_vtable_call

	leave
	ret
.LFE3:
	.size	asm_vtable_call_wrapper, .-asm_vtable_call_wrapper
	# see http://refspecs.linuxfoundation.org/LSB_3.0.0/LSB-Core-generic/LSB-Core-generic/ehframechpt.html
	# for details of the .eh_frame, the "Common Information Entry" and "Frame Description Entry" formats
	# and http://mentorembedded.github.io/cxx-abi/exceptions.pdf for more info
	.section	.eh_frame,"a",@progbits
.Lframe1:
	.long	.LECIE1-.LSCIE1
.LSCIE1:
	.long	0x0
	.byte	0x1
	.string	"zR"
	.uleb128 0x1
	.sleb128 -8
	.byte	0x10
	.uleb128 0x1
	.byte	0x1b
	.byte	0xc
	.uleb128 0x7
	.uleb128 0x8
	.byte	0x90
	.uleb128 0x1
	.align 8
.LECIE1:
.LSFDE1:
	.long	.LEFDE1-.LASFDE1
.LASFDE1:
	.long	.LASFDE1-.Lframe1
	.long	.LFB3-.
	.long	.LFE3-.LFB3
	.uleb128 0x0
	.byte	0x4
	.long	.LCFI0-.LFB3
	.byte	0xe
	.uleb128 0x10
	.byte	0x86
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI1-.LCFI0
	.byte	0xd
	.uleb128 0x6
	.align 8
.LEFDE1:
	.section	.note.GNU-stack,"",@progbits
