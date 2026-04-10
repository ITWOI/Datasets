#include "header_func.h"
static inline Py_ssize_t _Py_REFCNT (const PyObject *ob){
    return ob->ob_refcnt;
}
static inline int _Py_IS_TYPE (const PyObject *ob, const PyTypeObject *type){
    return ob->ob_type == type;
}
static inline void _Py_INCREF (PyObject *op){
    op->ob_refcnt++;
}
static inline void _Py_DECREF (PyObject *op){
    if (--op->ob_refcnt != 0) {
    } else {
        ;
    }
}
