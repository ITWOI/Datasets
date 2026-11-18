#include "header_func.h"
static inline int _Py_IS_TYPE (const PyObject *ob, const PyTypeObject *type){
    return ob->ob_type == type;
}
static inline void _Py_SET_SIZE (PyVarObject *ob, Py_ssize_t size){
    ob->ob_size = size;
}
static inline int _PyObject_TypeCheck (PyObject *ob, PyTypeObject *type){
    return _Py_IS_TYPE(((const PyObject *)(ob)), type) || PyType_IsSubtype((((PyObject *)(ob))->ob_type), type);
}
static inline void _Py_DECREF (PyObject *op){
    if (--op->ob_refcnt != 0) {
    } else {
        ;
    }
}
