#ifndef __HEADER_FUNC_H__ 
#define __HEADER_FUNC_H__
#include"header_type.h" 
static inline int _Py_IS_TYPE(const PyObject *ob, const PyTypeObject *type) ;


int PyType_IsSubtype(PyTypeObject *, PyTypeObject *);


void _Py_Dealloc(PyObject *);


int PyOS_snprintf(char *str, size_t size, const char *format, ...);


PyObject *PyErr_Occurred(void);


void PyErr_SetString(PyObject *exception, const char *string);


PyObject *_PyNumber_Index(PyObject *o);


Py_ssize_t PyLong_AsSsize_t(PyObject *);

static inline void _Py_DECREF(PyObject *op) ;

static inline int PyType_HasFeature(PyTypeObject *type, unsigned long feature) ;


unsigned long PyLong_AsUnsignedLongMask(PyObject *);

static const char *converterr(const char *expected, PyObject *arg, char *msgbuf, size_t bufsize) ;


unsigned long long PyLong_AsUnsignedLongLongMask(PyObject *);


Py_complex PyComplex_AsCComplex(PyObject *op);


Py_ssize_t PyBytes_Size(PyObject *);

static inline int _PyObject_TypeCheck(PyObject *ob, PyTypeObject *type) ;


Py_ssize_t PyByteArray_Size(PyObject *);


int _PyUnicode_Ready(PyObject *unicode);

static int getbuffer(PyObject *, Py_buffer *, const char **);

static int addcleanup(void *ptr, freelist_t *freelist, destr_t destructor) ;

static int cleanup_buffer(PyObject *self, void *ptr) ;

static Py_ssize_t convertbuffer(PyObject *, const void **p, const char **);


int PyBuffer_FillInfo(Py_buffer *view, PyObject *o, void *buf, Py_ssize_t len, int readonly, int flags);


const char *PyUnicode_AsUTF8AndSize(PyObject *unicode, Py_ssize_t *size);


int PyErr_WarnFormat(PyObject *category, Py_ssize_t stack_level, const char *format, ...);


Py_UNICODE *PyUnicode_AsUnicodeAndSize(PyObject *unicode, Py_ssize_t *size);


const char *PyUnicode_GetDefaultEncoding(void);

static inline void _Py_INCREF(PyObject *op) ;


PyObject *PyUnicode_AsEncodedString(PyObject *unicode, const char *encoding, const char *errors);


void *PyMem_Malloc(size_t size);


PyObject *PyErr_NoMemory(void);

static int cleanup_ptr(PyObject *self, void *ptr) ;


PyObject *PyErr_Format(PyObject *exception, const char *format, ...);


int PyObject_GetBuffer(PyObject *obj, Py_buffer *view, int flags);


void PyErr_Clear(void);


int PyBuffer_IsContiguous(const Py_buffer *view, char fort);


void PyBuffer_Release(Py_buffer *view);

extern PyObject *PyExc_OverflowError;
;

long PyLong_AsLong(PyObject *);


long long PyLong_AsLongLong(PyObject *);


double PyFloat_AsDouble(PyObject *);

extern PyTypeObject PyByteArray_Type;
;
extern char _PyByteArray_empty_string[];
;

int PyObject_IsTrue(PyObject *);

extern PyObject *PyExc_SystemError;
;
extern PyObject *PyExc_ValueError;
;
extern PyObject _Py_NoneStruct;
;
extern PyObject *PyExc_DeprecationWarning;
;
#endif