#include "header_func.h"
static inline Py_ssize_t PyVectorcall_NARGS (size_t n){
    return n & ~((size_t)1 << (8 * sizeof(size_t) - 1));
}
