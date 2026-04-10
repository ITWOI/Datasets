#include "header_func.h"
static inline int _Py_IS_TYPE (const PyObject *ob, const PyTypeObject *type){
    return ob->ob_type == type;
}
static inline void _Py_INCREF (PyObject *op){
    op->ob_refcnt++;
}
static inline void _Py_DECREF (PyObject *op){
    if (--op->ob_refcnt != 0) {
    } else {
        _Py_Dealloc(op);
    }
}
static inline void _Py_XINCREF (PyObject *op){
    if (op != ((void *)0)) {
        _Py_INCREF(((PyObject *)(op)));
    }
}
static inline void _Py_XDECREF (PyObject *op){
    if (op != ((void *)0)) {
        _Py_DECREF(((PyObject *)(op)));
    }
}
static inline int PyType_HasFeature (PyTypeObject *type, unsigned long feature){
    unsigned long flags;
    flags = type->tp_flags;
    return ((flags & feature) != 0);
}
static inline int _PyType_Check (PyObject *op){
    return PyType_HasFeature((((PyObject *)(op))->ob_type), (1UL << 31));
}
