#include "header_func.h"
#include "pycore_moduleobject.h"
#include "object.h"
static array_state * get_array_state (PyObject *module){
    return (array_state *)_PyModule_GetState(module);
}
static PyObject * newarrayobject (PyTypeObject *type, Py_ssize_t size, const struct arraydescr *descr){
    arrayobject *op;
    size_t nbytes;
    if (size < 0) {
        ;
        return ((void *)0);
    }
    if (size > ((Py_ssize_t)(((size_t)-1) >> 1)) / descr->itemsize) {
        return PyErr_NoMemory();
    }
    nbytes = size * descr->itemsize;
    op = (arrayobject *)type->tp_alloc(type, 0);
    if (op == ((void *)0)) {
        return ((void *)0);
    }
    op->ob_descr = descr;
    op->allocated = size;
    op->weakreflist = ((void *)0);
    _Py_SET_SIZE(((PyVarObject *)(op)), size);
    if (size <= 0) {
        op->ob_item = ((void *)0);
    } else {
        op->ob_item = (((size_t)(nbytes) > ((Py_ssize_t)(((size_t)-1) >> 1)) / sizeof(char)) ? ((void *)0) : ((char *)PyMem_Malloc((nbytes) * sizeof(char))));
        if (op->ob_item == ((void *)0)) {
            _Py_DECREF(((PyObject *)(op)));
            return PyErr_NoMemory();
        }
    }
    op->ob_exports = 0;
    return (PyObject *)op;
}
static PyObject * array_concat (arrayobject *a, PyObject *bb){
    array_state *state = (get_array_state(_PyType_GetModuleByDef((((PyObject *)(a))->ob_type), &arraymodule)));
    Py_ssize_t size;
    arrayobject *np;
    if (!_PyObject_TypeCheck(((PyObject *)(bb)), state->ArrayType)) {
        ;
        return ((void *)0);
    }
    if (a->ob_descr != ((arrayobject *)bb)->ob_descr) {
        ;
        return ((void *)0);
    }
    if ((((PyVarObject *)(a))->ob_size) > ((Py_ssize_t)(((size_t)-1) >> 1)) - (((PyVarObject *)(((arrayobject *)bb)))->ob_size)) {
        return PyErr_NoMemory();
    }
    size = (((PyVarObject *)(a))->ob_size) + (((PyVarObject *)(((arrayobject *)bb)))->ob_size);
    np = (arrayobject *)newarrayobject(state->ArrayType, size, a->ob_descr);
    if (np == ((void *)0)) {
        return ((void *)0);
    }
    if ((((PyVarObject *)(((arrayobject *)bb)))->ob_size) > 0) {
        memcpy(np->ob_item + (((PyVarObject *)(a))->ob_size) * a->ob_descr->itemsize, ((arrayobject *)bb)->ob_item, (((PyVarObject *)(((arrayobject *)bb)))->ob_size) * ((arrayobject *)bb)->ob_descr->itemsize);
    }
    return (PyObject *)np;
}
