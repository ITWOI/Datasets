#include "header_func.h"
static inline void * _PyModule_GetState (PyObject *mod){
    ;
    return ((PyModuleObject *)mod)->md_state;
}
