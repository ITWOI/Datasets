#ifndef __HEADER_FUNC_H__ 
#define __HEADER_FUNC_H__
#include"header_type.h" 

void _Py_Dealloc(PyObject *);

static void w_flush(WFILE *p) ;


int _PyBytes_Resize(PyObject **, Py_ssize_t);

static int w_reserve(WFILE *p, Py_ssize_t needed) ;

static void w_long(long x, WFILE *p) ;

static void w_string(const void *s, Py_ssize_t n, WFILE *p) ;

static void w_short(int x, WFILE *p) ;


int _PyFloat_Pack8(double x, unsigned char *p, int le);


char *PyOS_double_to_string(double val, char format_code, int precision, int flags, int *type);

static void w_short_pstring(const void *s, Py_ssize_t n, WFILE *p) ;

static inline Py_ssize_t _Py_REFCNT(const PyObject *ob) ;

static inline _Py_hashtable_entry_t *_Py_hashtable_get_entry(_Py_hashtable_t *ht, const void *key) ;


void PyErr_SetString(PyObject *exception, const char *string);

static inline void _Py_INCREF(PyObject *op) ;


int _Py_hashtable_set(_Py_hashtable_t *ht, const void *key, void *value);

static inline void _Py_DECREF(PyObject *op) ;

static int w_ref(PyObject *v, char *flag, WFILE *p) ;

static void w_complex_object(PyObject *v, char flag, WFILE *p);

extern PyObject _Py_NoneStruct;
;
extern PyObject *PyExc_StopIteration;
;
extern PyObject _Py_EllipsisObject;
;
extern struct _longobject _Py_FalseStruct;
;
extern struct _longobject _Py_TrueStruct;
;
static inline int _Py_IS_TYPE(const PyObject *ob, const PyTypeObject *type) ;

static void w_PyLong(const PyLongObject *ob, char flag, WFILE *p) ;

static void w_float_bin(double v, WFILE *p) ;

static void w_float_str(double v, WFILE *p) ;


double PyComplex_RealAsDouble(PyObject *op);


double PyComplex_ImagAsDouble(PyObject *op);

static void w_pstring(const void *s, Py_ssize_t n, WFILE *p) ;


PyObject *PyUnicode_AsEncodedString(PyObject *unicode, const char *encoding, const char *errors);

static void w_object(PyObject *v, WFILE *p) ;


int PyDict_Next(PyObject *mp, Py_ssize_t *pos, PyObject **key, PyObject **value);


int _PySet_NextEntry(PyObject *set, Py_ssize_t *pos, PyObject **key, Py_hash_t *hash);


int PyObject_CheckBuffer(PyObject *obj);


int PyObject_GetBuffer(PyObject *obj, Py_buffer *view, int flags);


void PyBuffer_Release(Py_buffer *view);

extern PyTypeObject PyLong_Type;
;

long PyLong_AsLongAndOverflow(PyObject *, int *);

extern PyTypeObject PyFloat_Type;
;
extern PyTypeObject PyComplex_Type;
;
extern PyTypeObject PyBytes_Type;
;
extern PyTypeObject PyUnicode_Type;
;
extern PyTypeObject PyTuple_Type;
;
extern PyTypeObject PyList_Type;
;
extern PyTypeObject PyDict_Type;
;
extern PyTypeObject PySet_Type;
;
extern PyTypeObject PyFrozenSet_Type;
;
extern PyTypeObject PyCode_Type;
;
#endif