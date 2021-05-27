#define MOZ_UNIFIED_BUILD
#include "jit/shared/Lowering-shared.cpp"
#ifdef PL_ARENA_CONST_ALIGN_MASK
#error "jit/shared/Lowering-shared.cpp uses PL_ARENA_CONST_ALIGN_MASK, so it cannot be built in unified mode."
#undef PL_ARENA_CONST_ALIGN_MASK
#endif
#ifdef INITGUID
#error "jit/shared/Lowering-shared.cpp defines INITGUID, so it cannot be built in unified mode."
#undef INITGUID
#endif
#include "jit/x64/Assembler-x64.cpp"
#ifdef PL_ARENA_CONST_ALIGN_MASK
#error "jit/x64/Assembler-x64.cpp uses PL_ARENA_CONST_ALIGN_MASK, so it cannot be built in unified mode."
#undef PL_ARENA_CONST_ALIGN_MASK
#endif
#ifdef INITGUID
#error "jit/x64/Assembler-x64.cpp defines INITGUID, so it cannot be built in unified mode."
#undef INITGUID
#endif
#include "jit/x64/Bailouts-x64.cpp"
#ifdef PL_ARENA_CONST_ALIGN_MASK
#error "jit/x64/Bailouts-x64.cpp uses PL_ARENA_CONST_ALIGN_MASK, so it cannot be built in unified mode."
#undef PL_ARENA_CONST_ALIGN_MASK
#endif
#ifdef INITGUID
#error "jit/x64/Bailouts-x64.cpp defines INITGUID, so it cannot be built in unified mode."
#undef INITGUID
#endif
#include "jit/x64/BaselineCompiler-x64.cpp"
#ifdef PL_ARENA_CONST_ALIGN_MASK
#error "jit/x64/BaselineCompiler-x64.cpp uses PL_ARENA_CONST_ALIGN_MASK, so it cannot be built in unified mode."
#undef PL_ARENA_CONST_ALIGN_MASK
#endif
#ifdef INITGUID
#error "jit/x64/BaselineCompiler-x64.cpp defines INITGUID, so it cannot be built in unified mode."
#undef INITGUID
#endif
#include "jit/x64/BaselineIC-x64.cpp"
#ifdef PL_ARENA_CONST_ALIGN_MASK
#error "jit/x64/BaselineIC-x64.cpp uses PL_ARENA_CONST_ALIGN_MASK, so it cannot be built in unified mode."
#undef PL_ARENA_CONST_ALIGN_MASK
#endif
#ifdef INITGUID
#error "jit/x64/BaselineIC-x64.cpp defines INITGUID, so it cannot be built in unified mode."
#undef INITGUID
#endif
#include "jit/x64/CodeGenerator-x64.cpp"
#ifdef PL_ARENA_CONST_ALIGN_MASK
#error "jit/x64/CodeGenerator-x64.cpp uses PL_ARENA_CONST_ALIGN_MASK, so it cannot be built in unified mode."
#undef PL_ARENA_CONST_ALIGN_MASK
#endif
#ifdef INITGUID
#error "jit/x64/CodeGenerator-x64.cpp defines INITGUID, so it cannot be built in unified mode."
#undef INITGUID
#endif