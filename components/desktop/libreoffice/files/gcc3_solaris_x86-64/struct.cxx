#include "share.hxx"

// Structs with size <= 16 will return on registers... but if they have alignment
// 1 they are passed as references to their buffer memory.

// This is bad because the bridge expected a simple return (return-by-value on register)
// to be passed in the same way it's returned, I.E. by value. However, alignment == 1 means
// the argument is passed by reference, and then *returned by value*.

// Only if the value can't fit into rdx:rax does it return by reference.

// Thus, if the argument is simple then the struct will be dereferenced twice;
// once by UNO copyAndConvert, and once by the function prologue. This causes an access error.

// This works as expected for all structs except those that contain *only bytes*.

// Thus, we must find the specific instances of structs with size <= 16 and alignment 1,
// and make sure they are not dereferenced twice.

// Also, template structs are always passed by reference.

bool isStructReturnedByReference(typelib_StructTypeDescription const * tDesc) { 
    const typelib_TypeDescription* sDesc = &(tDesc->aBase.aBase);
    if(sDesc->pTypeName->buffer[sDesc->pTypeName->length-1] == '>') return true;
    return (sDesc->nSize > 16 || sDesc->nAlignment == 1);
}

// All large structs return on stack (complex return).
bool isSimpleStruct(typelib_TypeDescription const * tDesc) { 
    if(tDesc->eTypeClass != typelib_TypeClass_STRUCT)
        return false;
    typelib_TypeDescription* sDesc = &(((typelib_StructTypeDescription*) tDesc)->aBase.aBase);
    if(!sDesc->bComplete) typelib_typedescription_complete(&sDesc); 

    // template structs aren't normally simple returns, but they can be if the generated
    // structure is returned by reference.
    return ( sDesc->nSize <= 16 ) && !(sDesc->pTypeName->buffer[sDesc->pTypeName->length-1] == '>' && sDesc->nAlignment == 8);
}

bool isSimple(typelib_TypeDescriptionReference const * type) {
    return bridges::cpp_uno::shared::isSimpleType(type->eTypeClass) || isSimpleStruct(type->pType);
}

bool isSimple(typelib_TypeDescription const * type) {
    return bridges::cpp_uno::shared::isSimpleType(type->eTypeClass) || isSimpleStruct(type);
}
