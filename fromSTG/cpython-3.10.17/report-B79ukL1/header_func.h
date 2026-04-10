#ifndef __HEADER_FUNC_H__ 
#define __HEADER_FUNC_H__
#include"header_type.h" 
static inline Py_ssize_t stringlib_find_char(const char *s, Py_ssize_t n, char ch) ;

static inline Py_ssize_t stringlib_rfind_char(const char *s, Py_ssize_t n, char ch) ;

static inline Py_ssize_t fastsearch(const char *s, Py_ssize_t n, const char *p, Py_ssize_t m, Py_ssize_t maxcount, int mode) ;

static inline Py_ssize_t stringlib_find(const char *str, Py_ssize_t str_len, const char *sub, Py_ssize_t sub_len, Py_ssize_t offset) ;

static inline Py_ssize_t stringlib_rfind(const char *str, Py_ssize_t str_len, const char *sub, Py_ssize_t sub_len, Py_ssize_t offset) ;

extern PyObject _Py_NoneStruct;
;

int _PyArg_ParseTuple_SizeT(PyObject *, const char *, ...);


int _PyEval_SliceIndex(PyObject *, Py_ssize_t *);

static inline int stringlib_parse_args_finds(const char *function_name, PyObject *args, PyObject **subobj, Py_ssize_t *start, Py_ssize_t *end) ;


int PyObject_CheckBuffer(PyObject *obj);

static inline int _PyIndex_Check(PyObject *obj) ;


PyObject *PyErr_Format(PyObject *exception, const char *format, ...);


Py_ssize_t PyNumber_AsSsize_t(PyObject *o, PyObject *exc);


PyObject *PyErr_Occurred(void);


void PyErr_SetString(PyObject *exception, const char *string);

static inline int parse_args_finds_byte(const char *function_name, PyObject *args, PyObject **subobj, char *byte, Py_ssize_t *start, Py_ssize_t *end) ;


int PyObject_GetBuffer(PyObject *obj, Py_buffer *view, int flags);

static inline Py_ssize_t stringlib_find_slice(const char *str, Py_ssize_t str_len, const char *sub, Py_ssize_t sub_len, Py_ssize_t start, Py_ssize_t end) ;

static inline Py_ssize_t stringlib_rfind_slice(const char *str, Py_ssize_t str_len, const char *sub, Py_ssize_t sub_len, Py_ssize_t start, Py_ssize_t end) ;

static inline Py_ssize_t find_internal(const char *str, Py_ssize_t len, const char *function_name, PyObject *args, int dir) ;


PyObject *PyLong_FromSsize_t(Py_ssize_t);

#endif