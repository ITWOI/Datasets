#ifndef __HEADER_FUNC_H__ 
#define __HEADER_FUNC_H__
#include"header_type.h" 

PyObject *PyList_New(Py_ssize_t size);

static inline void _Py_INCREF(PyObject *op) ;


PyObject *PyDict_New(void);

static inline void _Py_DECREF(PyObject *op) ;


PyObject *_Py_BuildValue_SizeT(const char *, ...);

#endif