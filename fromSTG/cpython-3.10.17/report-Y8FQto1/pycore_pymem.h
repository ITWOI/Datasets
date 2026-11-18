#include "header_func.h"
static inline int _PyMem_IsPtrFreed (const void *ptr){
    uintptr_t value = (uintptr_t)ptr;
    return (value == 0 || value == (uintptr_t)14829735431805717965UL || value == (uintptr_t)15987178197214944733UL || value == (uintptr_t)18302063728033398269UL);
}
