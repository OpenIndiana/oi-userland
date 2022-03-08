/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
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

#include <com/sun/star/uno/genfunc.hxx>
#include "com/sun/star/uno/RuntimeException.hpp"
#include <uno/data.h>

#include "bridge.hxx"
#include "types.hxx"
#include "unointerfaceproxy.hxx"
#include "vtables.hxx"

#include "share.hxx"

#include "callvirtualmethod.hxx"

#include <stdio.h>
void CPPU_CURRENT_NAMESPACE::callVirtualMethod(
    void * pAdjustedThisPtr,
    sal_Int32 nVtableIndex,
    void * pRegisterReturn,
    typelib_TypeClass eReturnType,
    sal_Int64 * pStackLongs,
    sal_Int32 nStackLongs )
{
    // parameter list is mixed list of * and values
    // reference parameters are pointers

    assert(pStackLongs && pAdjustedThisPtr);
    static_assert((sizeof(void *) == 8) && (sizeof(sal_Int32) == 4), "### unexpected size of int!");
    assert(nStackLongs && pStackLongs && "### no stack in callVirtualMethod !");
    // never called
    if (! pAdjustedThisPtr) CPPU_CURRENT_NAMESPACE::dummy_can_throw_anything("xxx"); // address something
    static_assert((sizeof(long) == 8),"### unexpected size of long!");
    long edx, eax; // for register returns
    void * stackptr;
	//pStackLongs = return ptr, this, params
    asm volatile (
	// new pseudo stack frame
	// we don't want a real frame, as it will be created during the actual call
	"mov   %%rsp, %2\n\t"


	// number of longs in external stack
        "mov   %3, %%edx\n\t"

	// skip copy if stack is empty (not sure if this happens)
	"test %%rdx, %%rdx\n\t"
	"jz    Lvcall\n\t"

	// location of external stack bottom
        "mov   %4, %%rsi\n"

        // copy values from external stack bottom to stack frame top (reverse order)
        "Lcopy:\n\t"
        "pushq -8(%%rsi,%%rdx,8)\n\t"
        "dec   %%rdx\n\t"
        "jnz   Lcopy\n\t"

        // do the actual call
	"Lvcall:\n\t"
	// align stack
	"and $0xFFFFFFFFFFFFFFF0, %%rsp\n\t"

	// Load Registers
	"mov %4, %%rbx\n\t"

	// General purpose registers 
	"movq	0x00(%%rbx), %%rdi\n\t"
	"movq	0x08(%%rbx), %%rsi\n\t"
	"movq	0x10(%%rbx), %%rdx\n\t"
	"movq	0x18(%%rbx), %%rcx\n\t"
	"movq	0x20(%%rbx), %%r8\n\t"
	"movq	0x28(%%rbx), %%r9\n\t"

	// FP/SSE registers
	"movsd	0x30(%%rbx), %%xmm0\n\t"
	"movsd	0x38(%%rbx), %%xmm1\n\t"
	"movsd	0x40(%%rbx), %%xmm2\n\t"
	"movsd	0x48(%%rbx), %%xmm3\n\t"
	"movsd	0x50(%%rbx), %%xmm4\n\t"
	"movsd	0x58(%%rbx), %%xmm5\n\t"
	"movsd	0x60(%%rbx), %%xmm6\n\t"
	"movsd	0x68(%%rbx), %%xmm7\n\t"

        "mov   %5, %%rbx\n\t"
        "mov   0(%%rbx), %%rbx\n\t"
        "mov   %6, %%eax\n\t"
        "shl   $3, %%rax\n\t"
        "add   %%rax, %%rbx\n\t"
        "mov   0(%%rbx), %%rbx\n\t"
        "call  *%%rbx\n\t"

        // save return registers
        "mov   %%rax, %0\n\t"
        "mov   %%rdx, %1\n\t"

	// delete stack frame
	"mov %2, %%rsp\n\t"

        : "=m"(eax), "=m"(edx), "=m"(stackptr)
        : "m"(nStackLongs), "m"(pStackLongs), "m"(pAdjustedThisPtr), "m"(nVtableIndex)
	: "rax", "rdi", "rsi", "rdx", "rcx", "r8", "r9", "r10", "r11", "r12",
          "xmm0", "xmm1", "xmm2", "xmm3", "xmm4", "xmm5", "xmm6", "xmm7",
          "xmm8", "xmm9", "xmm10", "xmm11", "xmm12", "xmm13", "xmm14", "xmm15",
          "memory" );

    switch( eReturnType )
    {
        case typelib_TypeClass_HYPER:
        case typelib_TypeClass_UNSIGNED_HYPER:
            ((long*)pRegisterReturn)[1] = edx;
        case typelib_TypeClass_LONG:
        case typelib_TypeClass_UNSIGNED_LONG:
        case typelib_TypeClass_CHAR:
        case typelib_TypeClass_ENUM:
            ((long*)pRegisterReturn)[0] = eax;
            break;
        case typelib_TypeClass_SHORT:
        case typelib_TypeClass_UNSIGNED_SHORT:
            *(unsigned short*)pRegisterReturn = eax;
            break;
        case typelib_TypeClass_BOOLEAN:
        case typelib_TypeClass_BYTE:
            *(unsigned char*)pRegisterReturn = eax;
            break;
        case typelib_TypeClass_FLOAT:
            asm ( "fstps %0" : : "m"(*(char *)pRegisterReturn) );
            break;
        case typelib_TypeClass_DOUBLE:
            asm ( "fstpl %0\n\t" : : "m"(*(char *)pRegisterReturn) );
            break;
	// for clarity's sake, and to quell gcc's whining
	default:
	    break;
    }
}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
