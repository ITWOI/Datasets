#ifndef __HEADER_FUNC_H__ 
#define __HEADER_FUNC_H__
#include"header_type.h" 

int PySys_Audit(const char *event, const char *argFormat, ...);


void PyErr_SetString(PyObject *exception, const char *string);


PyThreadState *PyEval_SaveThread(void);


void PyEval_RestoreThread(PyThreadState *);

extern PyObject _Py_NoneStruct;
;
static inline PyObject *_Py_NewRef(PyObject *obj) ;

#endif