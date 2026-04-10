#include "header_func.h"
static inline PyThreadState * _PyRuntimeState_GetThreadState (_PyRuntimeState *runtime){
    return (PyThreadState *)__c11_atomic_load(&(((&runtime->gilstate.tstate_current))->_value), _Py_memory_order_relaxed);
}
static inline PyThreadState * _PyThreadState_GET (){
    return _PyRuntimeState_GetThreadState(&_PyRuntime);
}
static inline PyInterpreterState * _PyInterpreterState_GET (){
    PyThreadState *tstate = _PyThreadState_GET();
    return tstate->interp;
}
