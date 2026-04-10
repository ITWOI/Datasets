#include "header_func.h"
static inline Py_ssize_t _Py_REFCNT (const PyObject *ob){
    return ob->ob_refcnt;
}
static inline int _Py_IS_TYPE (const PyObject *ob, const PyTypeObject *type){
    return ob->ob_type == type;
}
static inline void _Py_SET_TYPE (PyObject *ob, PyTypeObject *type){
    ob->ob_type = type;
}
static inline void _Py_SET_SIZE (PyVarObject *ob, Py_ssize_t size){
    ob->ob_size = size;
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
static inline void _Py_XDECREF (PyObject *op){
    if (op != ((void *)0)) {
        _Py_DECREF(((PyObject *)(op)));
    }
}
static inline PyObject * _Py_NewRef (PyObject *obj){
    _Py_INCREF(((PyObject *)(obj)));
    return obj;
}
static inline int PyType_HasFeature (PyTypeObject *type, unsigned long feature){
    unsigned long flags;
    flags = type->tp_flags;
    return ((flags & feature) != 0);
}
