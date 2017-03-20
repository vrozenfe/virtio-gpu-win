#pragma once
#include "helper.h"
//
// Memory handling
//

// Defaulting the value of PoolType means that any call to new Foo()
// will raise a compiler error for being ambiguous. This is to help keep
// any calls to allocate memory from accidentally NOT going through
// these functions.
_When_((PoolType & NonPagedPoolMustSucceed) != 0,
    __drv_reportError("Must succeed pool allocations are forbidden. "
            "Allocation failures cause a system crash"))
void* __cdecl operator new(size_t Size, POOL_TYPE PoolType = PagedPool);
_When_((PoolType & NonPagedPoolMustSucceed) != 0,
    __drv_reportError("Must succeed pool allocations are forbidden. "
            "Allocation failures cause a system crash"))
void* __cdecl operator new[](size_t Size, POOL_TYPE PoolType = PagedPool);
void  __cdecl operator delete(void* pObject);
void  __cdecl operator delete[](void* pObject);
void  __cdecl operator delete(void *pObject, size_t Size);
