#include "header_func.h"
static PyObject * _elementtree_Element___getstate___impl (ElementObject *self){
    Py_ssize_t i;
    PyObject *children, *attrib;
    children = PyList_New(self->extra ? self->extra->length : 0);
    if (!children)
        return ((void *)0);
    for (i = 0; i < (((PyVarObject *)((((void)(0)) , (PyListObject *)(children))))->ob_size); i++) {
        PyObject *child = self->extra->children[i];
        _Py_INCREF(((PyObject *)(child)));
        ((void)((((void)(0)) , (PyListObject *)(children))->ob_item[i] = (child)));
    }
    if (self->extra && self->extra->attrib) {
        attrib = self->extra->attrib;
        _Py_INCREF(((PyObject *)(attrib)));
    } else {
        ;
    }
    return _Py_BuildValue_SizeT("{sOsNsNsOsO}", "tag", self->tag, "_children", children, "attrib", attrib, "text", ((PyObject *)((uintptr_t)(self->text) & ~(uintptr_t)1)), "tail", ((PyObject *)((uintptr_t)(self->tail) & ~(uintptr_t)1)));
}
