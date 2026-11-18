#ifndef __HEADER_FUNC_H__ 
#define __HEADER_FUNC_H__
#include"header_type.h" 

void _Py_Dealloc(PyObject *);


int PyDict_Next(PyObject *mp, Py_ssize_t *pos, PyObject **key, PyObject **value);

static inline int PyType_HasFeature(PyTypeObject *type, unsigned long feature) ;


void PyErr_SetString(PyObject *exception, const char *string);


PyObject *PyErr_Format(PyObject *exception, const char *format, ...);


int PySequence_Contains(PyObject *seq, PyObject *ob);

static const char *skipitem(const char **, va_list *, int);


PyObject *PyTuple_New(Py_ssize_t size);

static inline void _Py_DECREF(PyObject *op) ;


void PyUnicode_InternInPlace(PyObject **);


PyObject *PyUnicode_FromString(const char *u);

static struct _PyArg_Parser *static_arg_parsers = ((void *)0);
;

int _PyUnicode_EQ(PyObject *, PyObject *);


void _PyErr_BadInternalCall(const char *filename, int lineno);

static int parser_init(struct _PyArg_Parser *parser) ;


PyObject *PyDict_GetItemWithError(PyObject *mp, PyObject *key);


PyObject *PyErr_Occurred(void);

static PyObject *find_keyword(PyObject *kwnames, PyObject *const *kwstack, PyObject *key) ;

static void error_unexpected_keyword_arg(PyObject *kwargs, PyObject *kwnames, PyObject *kwtuple, const char *fname) ;

#endif