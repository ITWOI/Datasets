#include "header_func.h"
static inline PyObject ** _PyObject_GET_WEAKREFS_LISTPTR (PyObject *op){
    Py_ssize_t offset = (((PyObject *)(op))->ob_type)->tp_weaklistoffset;
    return (PyObject **)((char *)op + offset);
}
