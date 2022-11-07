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


#include <strings.h>

#include <sal/log.hxx>

#include "share.hxx"

#include "cppinterfaceproxy.hxx"
#include "vtablefactory.hxx"
#include "call.hxx"

using namespace ::com::sun::star::uno;


static typelib_TypeClass cpp2uno_call(
    bridges::cpp_uno::shared::CppInterfaceProxy * pThis,
    const typelib_TypeDescription * pMemberTypeDescr,
    typelib_TypeDescriptionReference * pReturnTypeRef, // 0 indicates void return
    sal_Int32 nParams, typelib_MethodParameter * pParams,
    void ** pCallStack,
    void ** pRegs,
    sal_Int64 * pRegisterReturn /* space for register return */ )
{
    // pRegs: [ret ptr?],this ptr, params 1-4 or 1-5
    // pCallStack: params 6+
    char * pCppStack = (char *)(pCallStack);
    bool simpleReturn = true;

    void * pUnoReturn = 0;
    void * pCppReturn = 0; // complex return ptr: if != 0 && != pUnoReturn, reconversion need

    // return
    typelib_TypeDescription * pReturnTypeDescr = 0;
    if (pReturnTypeRef)
        TYPELIB_DANGER_GET( &pReturnTypeDescr, pReturnTypeRef );
    if (pReturnTypeDescr) {
        simpleReturn = isSimple( pReturnTypeDescr );
        if (simpleReturn) {
            pUnoReturn = pRegisterReturn; // direct way for simple types
        } else { // complex return via ptr (pCppReturn)
            pCppReturn = (void*)pRegs[0];
            pUnoReturn = (bridges::cpp_uno::shared::relatesToInterfaceType(
                              pReturnTypeDescr )
                          ? alloca( pReturnTypeDescr->nSize )
                          : pCppReturn); // direct way
        }
    }

    // stack space
    static_assert(sizeof(void *) == sizeof(sal_Int64), "### unexpected size!");
    // parameters
    void ** pUnoArgs = (void **)alloca( 4 * sizeof(void *) * nParams );
    void ** pCppArgs = pUnoArgs + nParams;
    // indices of values this have to be converted (interface conversion cpp<=>uno)
    sal_Int32 * pTempIndices = (sal_Int32 *)(pUnoArgs + (2 * nParams));
    // type descriptions for reconversions
    typelib_TypeDescription ** ppTempParamTypeDescr = (typelib_TypeDescription **)(pUnoArgs + (3 * nParams));

    sal_Int32 nTempIndices  = 0;
    sal_uInt8  nFPRsUsed    = 0;
    sal_uInt8  nGPRsUsed;
    if(!simpleReturn)
        nGPRsUsed     = 2; //ignore ret ptr and this ptr
    else
        nGPRsUsed     = 1; //ignore this ptr

    for ( sal_Int32 nPos = 0; nPos < nParams; ++nPos )
    {
        const typelib_MethodParameter & rParam = pParams[nPos];
        typelib_TypeDescription * pParamTypeDescr = 0;
        TYPELIB_DANGER_GET( &pParamTypeDescr, rParam.pTypeRef );

        if (!rParam.bOut
            && isSimple( pParamTypeDescr ) )
            // value
        {
            if(pParamTypeDescr->eTypeClass == typelib_TypeClass_DOUBLE ||
                pParamTypeDescr->eTypeClass == typelib_TypeClass_FLOAT) {
                    if(nFPRsUsed >= 8) {
                        pCppArgs[nPos] = pCppStack;
                        pUnoArgs[nPos] = pCppStack;
                        pCppStack += sizeof(sal_Int64); // standard parameter length
                    } else {
                        pCppArgs[nPos] = &pRegs[6+nFPRsUsed];
                        pUnoArgs[nPos] = &pRegs[6+nFPRsUsed];
                        nFPRsUsed++;
                    }
/*
            } else if(pParamTypeDescr->eTypeClass == typelib_TypeClass_STRUCT &&
               isStructReturnedByReference( (const typelib_StructTypeDescription*)pParamTypeDescr ) ) {
                   if(nGPRsUsed >= 6) {
                        pCppArgs[nPos] = *(void**)pCppStack;
                        pUnoArgs[nPos] = *(void**)pCppStack;
                        pCppStack += sizeof(sal_Int64); // standard parameter length
                   } else {
                        pCppArgs[nPos] = pRegs[nGPRsUsed];
                        pUnoArgs[nPos] = pRegs[nGPRsUsed];
                        nGPRsUsed++;
                   }
*/                    
            } else {
                    if(nGPRsUsed >= 6) {
                        pCppArgs[nPos] = pCppStack;
                        pUnoArgs[nPos] = pCppStack;
                        pCppStack += sizeof(sal_Int64); // standard parameter length
                   } else {
                        pCppArgs[nPos] = &pRegs[nGPRsUsed];
                        pUnoArgs[nPos] = &pRegs[nGPRsUsed];
                        nGPRsUsed++;
                   }
            }
            // no longer needed
            TYPELIB_DANGER_RELEASE( pParamTypeDescr );
        }
        else // ptr to complex value | ref
        {
                
            if(nGPRsUsed >= 6){
                pCppArgs[nPos] = *(void **)pCppStack;
                pCppStack += sizeof(sal_Int64); // standard parameter length
            } else {
                pCppArgs[nPos] = pRegs[nGPRsUsed++];
            }

            if (! rParam.bIn) { // is pure out

                // uno out is unconstructed mem!
                pUnoArgs[nPos] = alloca( pParamTypeDescr->nSize );
                pTempIndices[nTempIndices] = nPos;
                // will be released at reconversion
                ppTempParamTypeDescr[nTempIndices++] = pParamTypeDescr;

            } else { // is in/inout

                if (bridges::cpp_uno::shared::relatesToInterfaceType(
                             pParamTypeDescr ))
                {
                    uno_copyAndConvertData( pUnoArgs[nPos] = alloca( pParamTypeDescr->nSize ),
                                            pCppArgs[nPos], pParamTypeDescr,
                                            pThis->getBridge()->getCpp2Uno() );
                    pTempIndices[nTempIndices] = nPos; // has to be reconverted
                    // will be released at reconversion
                    ppTempParamTypeDescr[nTempIndices++] = pParamTypeDescr;
                }
                else // direct way
                {
                    pUnoArgs[nPos] = pCppArgs[nPos];
                    // no longer needed
                    TYPELIB_DANGER_RELEASE( pParamTypeDescr );
                }
            }
        }
    }

    // ExceptionHolder
    uno_Any aUnoExc; // Any will be constructed by callee
    uno_Any * pUnoExc = &aUnoExc;

    // invoke uno dispatch call
    (*pThis->getUnoI()->pDispatcher)(
        pThis->getUnoI(), pMemberTypeDescr, pUnoReturn, pUnoArgs, &pUnoExc );

    // in case an exception occurred...
    if (pUnoExc)
    {
        // destruct temporary in/inout params
        for ( ; nTempIndices--; )
        {
            sal_Int32 nIndex = pTempIndices[nTempIndices];

            if (pParams[nIndex].bIn) // is in/inout => was constructed
                uno_destructData( pUnoArgs[nIndex], ppTempParamTypeDescr[nTempIndices], 0 );
            TYPELIB_DANGER_RELEASE( ppTempParamTypeDescr[nTempIndices] );
        }
        if (pReturnTypeDescr)
            TYPELIB_DANGER_RELEASE( pReturnTypeDescr );

        CPPU_CURRENT_NAMESPACE::raiseException(
            &aUnoExc, pThis->getBridge()->getUno2Cpp() );
            // has to destruct the any
        // is here for dummy
        return typelib_TypeClass_VOID;
    }
    else // else no exception occurred...
    {
        // temporary params
        for ( ; nTempIndices--; )
        {
            sal_Int32 nIndex = pTempIndices[nTempIndices];
            typelib_TypeDescription * pParamTypeDescr = ppTempParamTypeDescr[nTempIndices];

            if (pParams[nIndex].bOut) // inout/out
            {
                // convert and assign
                uno_destructData( pCppArgs[nIndex], pParamTypeDescr, cpp_release );
                uno_copyAndConvertData( pCppArgs[nIndex], pUnoArgs[nIndex], pParamTypeDescr,
                                        pThis->getBridge()->getUno2Cpp() );
            }
            // destroy temp uno param
            uno_destructData( pUnoArgs[nIndex], pParamTypeDescr, 0 );

            TYPELIB_DANGER_RELEASE( pParamTypeDescr );
        }
        // return
        if (pCppReturn) // has complex return
        {
            if (pUnoReturn != pCppReturn) // needs reconversion
            {
                uno_copyAndConvertData( pCppReturn, pUnoReturn, pReturnTypeDescr,
                                        pThis->getBridge()->getUno2Cpp() );
                // destroy temp uno return
                uno_destructData( pUnoReturn, pReturnTypeDescr, 0 );
            }
            // complex return ptr is set to eax
            *(void **)pRegisterReturn = pCppReturn;
        }
        if (pReturnTypeDescr)
        {
            typelib_TypeClass eRet = (typelib_TypeClass)pReturnTypeDescr->eTypeClass;
            TYPELIB_DANGER_RELEASE( pReturnTypeDescr );
            return eRet;
        }
        else
            return typelib_TypeClass_VOID;
    }
}


typelib_TypeClass cpp_mediate(
    sal_Int32 nFunctionIndex,
    sal_Int32 nVtableOffset,
    void ** pCallStack,
    void ** pRegs,
    sal_Int64 * pRegisterReturn /* space for register return */ )
{
    static_assert(sizeof(sal_Int64)==sizeof(void *), "### unexpected!");

    //pRegs = [simple ret], this, params
    void * pThis;
    // This isn't always the case. Sometimes bit 0x80000000 is set and
    // there is no return pointer, in the case of small structs. Most
    // of the time this works, though...
    if( nFunctionIndex & 0x80000000 )
    {
        nFunctionIndex &= 0x7fffffff;
        pThis = pRegs[1];
    }
    else
    {
        pThis = pRegs[0];
    }
    pThis = static_cast< char * >(pThis) - nVtableOffset;
    bridges::cpp_uno::shared::CppInterfaceProxy * pCppI
        = bridges::cpp_uno::shared::CppInterfaceProxy::castInterfaceToProxy(
            pThis);

    typelib_InterfaceTypeDescription * pTypeDescr = pCppI->getTypeDescr();

    if (nFunctionIndex >= pTypeDescr->nMapFunctionIndexToMemberIndex)
    {
        SAL_WARN(
            "bridges",
            "illegal " << OUString::unacquired(&pTypeDescr->aBase.pTypeName)
                << " vtable index " << nFunctionIndex << "/"
                << pTypeDescr->nMapFunctionIndexToMemberIndex);
        throw RuntimeException(
            ("illegal " + OUString::unacquired(&pTypeDescr->aBase.pTypeName)
             + " vtable index " + OUString::number(nFunctionIndex) + "/"
             + OUString::number(pTypeDescr->nMapFunctionIndexToMemberIndex)),
            (XInterface *)pThis);
    }

    // determine called method
    sal_Int32 nMemberPos = pTypeDescr->pMapFunctionIndexToMemberIndex[nFunctionIndex];
    assert(nMemberPos < pTypeDescr->nAllMembers);

    TypeDescription aMemberDescr( pTypeDescr->ppAllMembers[nMemberPos] );

    typelib_TypeClass eRet;
    switch (aMemberDescr.get()->eTypeClass)
    {
    case typelib_TypeClass_INTERFACE_ATTRIBUTE:
    {
        if (pTypeDescr->pMapMemberIndexToFunctionIndex[nMemberPos] == nFunctionIndex)
        {
            // is GET method
            eRet = cpp2uno_call(
                pCppI, aMemberDescr.get(),
                ((typelib_InterfaceAttributeTypeDescription *)aMemberDescr.get())->pAttributeTypeRef,
                0, 0, // no params
                pCallStack, pRegs, pRegisterReturn );
        }
        else
        {
            // is SET method
            typelib_MethodParameter aParam;
            aParam.pTypeRef =
                ((typelib_InterfaceAttributeTypeDescription *)aMemberDescr.get())->pAttributeTypeRef;
            aParam.pName = 
                ((typelib_InterfaceAttributeTypeDescription *)aMemberDescr.get())->aBase.pMemberName;
            aParam.bIn      = sal_True;
            aParam.bOut     = sal_False;

            eRet = cpp2uno_call(
                pCppI, aMemberDescr.get(),
                0, // indicates void return
                1, &aParam,
                pCallStack, pRegs, pRegisterReturn );
        }
        break;
    }
    case typelib_TypeClass_INTERFACE_METHOD:
    {
        // is METHOD
        switch (nFunctionIndex)
        {
        case 1: // acquire()
            pCppI->acquireProxy(); // non virtual call!
            eRet = typelib_TypeClass_VOID;
            break;
        case 2: // release()
            pCppI->releaseProxy(); // non virtual call!
            eRet = typelib_TypeClass_VOID;
            break;
        case 0: // queryInterface() opt
        {
            typelib_TypeDescription * pTD = 0;
            TYPELIB_DANGER_GET( &pTD, reinterpret_cast< Type * >( pRegs[2] )->getTypeLibType() );
            if (pTD)
            {
                XInterface * pInterface = 0;
                (*pCppI->getBridge()->getCppEnv()->getRegisteredInterface)(
                    pCppI->getBridge()->getCppEnv(),
                    (void **)&pInterface, pCppI->getOid().pData,
                    (typelib_InterfaceTypeDescription *)pTD );

                if (pInterface)
                {
                    ::uno_any_construct(
                        reinterpret_cast< uno_Any * >( pRegs[0] ),
                        &pInterface, pTD, cpp_acquire );
                    pInterface->release();
                    TYPELIB_DANGER_RELEASE( pTD );
                    *(void **)pRegisterReturn = pRegs[0];
                    eRet = typelib_TypeClass_ANY;
                    break;
                }
                TYPELIB_DANGER_RELEASE( pTD );
            }
        } // else perform queryInterface()
        default:
            eRet = cpp2uno_call(
                pCppI, aMemberDescr.get(),
                ((typelib_InterfaceMethodTypeDescription *)aMemberDescr.get())->pReturnTypeRef,
                ((typelib_InterfaceMethodTypeDescription *)aMemberDescr.get())->nParams,
                ((typelib_InterfaceMethodTypeDescription *)aMemberDescr.get())->pParams,
                pCallStack, pRegs, pRegisterReturn );
        }
        break;
    }
    default:
    {
        throw RuntimeException( "no member description found!", (XInterface *)pThis );
    }
    }

    return eRet;
}


const int codeSnippetSize = 24;

// Generate a trampoline that redirects method calls to
// asm_vtable_call_wrapper().
//
// asm_vtable_call_wrapper() saves all the registers that are used for
// parameter passing on x86_64, and calls cpp_mediate(), which
// executes the call, and sets the return values. 
// asm_vtable_call_wrapper() then immediately returns those values which
// were set by cpp_mediate().
//
// Note: The code snippet we build here must not create a stack frame,
// otherwise the UNO exceptions stop working thanks to non-existing
// unwinding info.
static unsigned char * codeSnippet( unsigned char * code,
        sal_Int32 nFunctionIndex, sal_Int32 nVtableOffset,
        bool simpleReturnType )
{
    if ( !simpleReturnType )
        nFunctionIndex |= 0x80000000;

    // movq $<nOffsetAndIndex>, %r10
    *reinterpret_cast<sal_uInt16 *>( code ) = 0xba49;
    *reinterpret_cast<sal_uInt32 *>( code + 2 ) = nFunctionIndex;
    *reinterpret_cast<sal_uInt32 *>( code + 6 ) = nVtableOffset;

    // movq $<asm_vtable_call_wrapper>, %r11
    *reinterpret_cast<sal_uInt16 *>( code + 10 ) = 0xbb49;
    *reinterpret_cast<sal_uInt64 *>( code + 12 )
        = reinterpret_cast<sal_uInt64>(asm_vtable_call_wrapper);

    // jmpq *%r11
    *reinterpret_cast<sal_uInt32 *>( code + 20 ) = 0x00e3ff49;

    return code + codeSnippetSize;
}


struct bridges::cpp_uno::shared::VtableFactory::Slot { void * fn; };

bridges::cpp_uno::shared::VtableFactory::Slot *
bridges::cpp_uno::shared::VtableFactory::mapBlockToVtable(void * block)
{
    return static_cast< Slot * >(block) + 2;
}

std::size_t bridges::cpp_uno::shared::VtableFactory::getBlockSize(
    sal_Int32 slotCount)
{
    return (slotCount + 2) * sizeof (Slot) + slotCount * codeSnippetSize;
}

bridges::cpp_uno::shared::VtableFactory::Slot *
bridges::cpp_uno::shared::VtableFactory::initializeBlock(
    void * block, sal_Int32 slotCount, sal_Int32,
    typelib_InterfaceTypeDescription *)
{
    Slot * slots = mapBlockToVtable(block);
    slots[-2].fn = 0;
    slots[-1].fn = 0;
    return slots + slotCount;
}

unsigned char * bridges::cpp_uno::shared::VtableFactory::addLocalFunctions(
    Slot ** slots, unsigned char * code,
    typelib_InterfaceTypeDescription const * type, sal_Int32 functionOffset,
    sal_Int32 functionCount, sal_Int32 vtableOffset)
{
    (*slots) -= functionCount;
    Slot * s = *slots;
    for (sal_Int32 i = 0; i < type->nMembers; ++i) {
        typelib_TypeDescription * member = 0;
        TYPELIB_DANGER_GET(&member, type->ppMembers[i]);
        assert(member != 0);
        switch (member->eTypeClass) {
            case typelib_TypeClass_INTERFACE_ATTRIBUTE:
                // Getter:
                (s++)->fn = code;
                code = codeSnippet(
                    code, functionOffset++, vtableOffset,
                    isSimple(
                        reinterpret_cast<
                        typelib_InterfaceAttributeTypeDescription * >(
                            member)->pAttributeTypeRef));
                // Setter:
                if (!reinterpret_cast<
                    typelib_InterfaceAttributeTypeDescription * >(
                        member)->bReadOnly)
                {
                    (s++)->fn = code;
                    code = codeSnippet(code, functionOffset++, vtableOffset, true);
                }
            break;

            case typelib_TypeClass_INTERFACE_METHOD:
            {
                (s++)->fn = code;
                typelib_InterfaceMethodTypeDescription *pIMTD = reinterpret_cast<typelib_InterfaceMethodTypeDescription * >(member);
                typelib_TypeDescriptionReference* returnTypeRef = pIMTD->pReturnTypeRef ;
                code = codeSnippet( code, functionOffset++, vtableOffset, isSimple(returnTypeRef)
                        );
            }
            break;

            default:
                assert(false);
            break;
        }
        TYPELIB_DANGER_RELEASE(member);
    }
    return code;
}


void bridges::cpp_uno::shared::VtableFactory::flushCode(
    unsigned char const *, unsigned char const *)
{}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
