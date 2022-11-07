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
    typelib_TypeDescription * pReturnTypeDescr,
    sal_Int64 * pStackLongs,
    sal_Int32 nStackLongs,
    void** pCppRegisters)
{
    // parameter list is mixed list of * and values
    // reference parameters are pointers

    assert(pAdjustedThisPtr && "### no this ptr !");
    static_assert((sizeof(void *) == 8) && (sizeof(sal_Int32) == 4), "### unexpected size of int!");
    static_assert((sizeof(long) == 8),"### unexpected size of long!");
    long edx;
    long eax = (long)pRegisterReturn; // for register returns, if it returns the pointer then it's already been written
    void * stackptr;

	//pStackLongs = return ptr, this, params
    asm volatile (
        // new pseudo stack frame
        // we don't want a real frame, as it will be created during the actual call
        "mov   %%rsp, %2\n\t"


        // number of longs in external stack
        "mov   %3, %%edx\n\t"

        // Make sure the stack will align to 16 bytes after variable pushes.
        "mov %%rdx,%%r11\n\t"
        "and $1,%%r11\n\t"
        "mov %%rsp,%%rsi\n\t"
        "and   $8, %%rsi\n\t"
        "shr   $3, %%rsi\n\t"
        "add %%rdx,%%rsi\n\t" 
        "and   $1, %%rsi\n\t"
        "jz  noAlignNeeded\n\t"
        "sub $8,  %%rsp\n\t"
        "noAlignNeeded:\n\t"

    	// location of external stack bottom
        "mov   %4, %%rsi\n\t"


        // skip copy if no stack arguments
        "test       %%rdx,%%rdx\n\t"
        "jz         Lvcall\n\t"


        // copy values from external stack bottom to stack frame top (reverse order)
        "Lcopy:\n\t"
        "pushq -8(%%rsi,%%rdx,8)\n\t"
        "dec   %%rdx\n\t"
        "jnz   Lcopy\n\t"

        // do the actual call
        "Lvcall:\n\t"

        // for loading registers
        "mov %7, %%r11\n\t"

        // General purpose registers 
        "movq	0x00(%%r11), %%rdi\n\t"
        "movq	0x08(%%r11), %%rsi\n\t"
        "movq	0x10(%%r11), %%rdx\n\t"
        "movq	0x18(%%r11), %%rcx\n\t"
        "movq	0x20(%%r11), %%r8\n\t"
        "movq	0x28(%%r11), %%r9\n\t"

        // FP/SSE registers
        "movsd	0x30(%%r11), %%xmm0\n\t"
        "movsd	0x38(%%r11), %%xmm1\n\t"
        "movsd	0x40(%%r11), %%xmm2\n\t"
        "movsd	0x48(%%r11), %%xmm3\n\t"
        "movsd	0x50(%%r11), %%xmm4\n\t"
        "movsd	0x58(%%r11), %%xmm5\n\t"
        "movsd	0x60(%%r11), %%xmm6\n\t"
        "movsd	0x68(%%r11), %%xmm7\n\t"

        "mov   %5, %%r11\n\t"
        "mov   0(%%r11), %%r11\n\t"
        "mov   %6, %%eax\n\t"
        "shl   $3, %%rax\n\t"
        "add   %%rax, %%r11\n\t"
        "mov   0(%%r11), %%r11\n\t"
        "call  *%%r11\n\t"

        // save return registers
        "cmp %0, %%rax  \n\t"
        "je Lnocopy\n\t"
        "mov   %%rax, %0\n\t"
        "mov   %%rdx, %1\n\t"
        "Lnocopy:\n\t"

    	// delete stack frame
    	"mov %2, %%rsp\n\t"

        : "=m"(eax), "=m"(edx), "=m"(stackptr)
        : "m"(nStackLongs), "m"(pStackLongs), "m"(pAdjustedThisPtr), "m"(nVtableIndex), "m"(pCppRegisters)
	    :   "rax", "rdi", "rsi", "rdx", "rcx", "r8", "r9", "r10", "r11",
            "xmm0", "xmm1", "xmm2", "xmm3", "xmm4", "xmm5", "xmm6", "xmm7",
            "xmm8", "xmm9", "xmm10", "xmm11", "xmm12", "xmm13", "xmm14", "xmm15",
            "memory" );
 
    typelib_TypeClass eReturnType = pReturnTypeDescr->eTypeClass;
    switch( eReturnType )
    {
        case typelib_TypeClass_HYPER:
        case typelib_TypeClass_UNSIGNED_HYPER:
            ((unsigned long*)pRegisterReturn)[1] = edx;
        case typelib_TypeClass_LONG:
        case typelib_TypeClass_UNSIGNED_LONG:
        case typelib_TypeClass_CHAR:
        case typelib_TypeClass_ENUM:
            ((unsigned long*)pRegisterReturn)[0] = eax;
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
            asm ( "fstps %0\n\t" : : "m"(*(char *)pRegisterReturn) );
            break;
        case typelib_TypeClass_DOUBLE:
            asm ( "fstpl %0\n\t" : : "m"(*(char *)pRegisterReturn) );
            break;
        case typelib_TypeClass_STRUCT:
            if (eax == (long)pRegisterReturn)
                break;
            if (((typelib_StructTypeDescription*) pReturnTypeDescr)->aBase.aBase.nSize > 16)
                break;
            if (((typelib_StructTypeDescription*) pReturnTypeDescr)->aBase.aBase.nSize > 8)
                ((unsigned long*)pRegisterReturn)[1] = edx;
            ((unsigned long*)pRegisterReturn)[0] = eax;
            break;
        case typelib_TypeClass_VOID:
            break;
	    default:
	        break;
    }
}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
