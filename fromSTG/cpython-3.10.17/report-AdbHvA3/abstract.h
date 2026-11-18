#include "header_func.h"
static inline Py_ssize_t PyVectorcall_NARGS (size_t n){
    return n & ~((size_t)1 << (8 * sizeof(size_t) - 1));
}
static inline vectorcallfunc PyVectorcall_Function (PyObject *callable){
    PyTypeObject *tp;
    Py_ssize_t offset;
    vectorcallfunc ptr;
    tp = (((PyObject *)(callable))->ob_type);
    if (!PyType_HasFeature(tp, (1UL << 11))) {
        return ((void *)0);
    }
    ;
    offset = tp->tp_vectorcall_offset;
    memcpy(&ptr, (char *)callable + offset, sizeof (ptr));
    return ptr;
}
static inline PyObject * _PyObject_VectorcallTstate (PyThreadState *tstate, PyObject *callable, PyObject *const *args, size_t nargsf, PyObject *kwnames){
    vectorcallfunc func;
    PyObject *res;
    func = PyVectorcall_Function(callable);
    if (func == ((void *)0)) {
        Py_ssize_t nargs = PyVectorcall_NARGS(nargsf);
        return _PyObject_MakeTpCall(tstate, callable, args, nargs, kwnames);
    }
    res = func(callable, args, nargsf, kwnames);
    return _Py_CheckFunctionResult(tstate, callable, res, ((void *)0));
}
static inline PyObject * PyObject_CallOneArg (PyObject *func, PyObject *arg){
    PyObject *_args[2];
    PyObject **args;
    PyThreadState *tstate;
    size_t nargsf;
    args = _args + 1;
    args[0] = arg;
    tstate = PyThreadState_Get();
    nargsf = 1 | ((size_t)1 << (8 * sizeof(size_t) - 1));
    return _PyObject_VectorcallTstate(tstate, func, args, nargsf, ((void *)0));
}
