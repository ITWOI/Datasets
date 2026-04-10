#ifndef __HEADER_FUNC_H__ 
#define __HEADER_FUNC_H__
#include"header_type.h" 

void _Py_Dealloc(PyObject *);

static inline void _Py_INCREF(PyObject *op) ;

static inline void _Py_DECREF(PyObject *op) ;

static inline int PyType_HasFeature(PyTypeObject *type, unsigned long feature) ;

static inline vectorcallfunc PyVectorcall_Function(PyObject *callable) ;


PyObject *_PyObject_MakeTpCall(PyThreadState *tstate, PyObject *callable, PyObject *const *args, Py_ssize_t nargs, PyObject *keywords);

static inline Py_ssize_t PyVectorcall_NARGS(size_t n) ;


PyObject *_Py_CheckFunctionResult(PyThreadState *tstate, PyObject *callable, PyObject *result, const char *where);


PyThreadState *PyThreadState_Get(void);

static inline PyObject *_PyObject_VectorcallTstate(PyThreadState *tstate, PyObject *callable, PyObject *const *args, size_t nargsf, PyObject *kwnames) ;

static inline PyThreadState *_PyRuntimeState_GetThreadState(_PyRuntimeState *runtime) ;

extern _PyRuntimeState _PyRuntime;
;
static inline int _Py_IS_TYPE(const PyObject *ob, const PyTypeObject *type) ;

extern PyTypeObject PyTraceBack_Type;
;
static inline void _Py_XDECREF(PyObject *op) ;

extern PyObject _Py_NoneStruct;
;
static inline PyObject *_PyObject_CallNoArg(PyObject *func) ;


PyObject *PyObject_Call(PyObject *callable, PyObject *args, PyObject *kwargs);

static inline PyObject *PyObject_CallOneArg(PyObject *func, PyObject *arg) ;

PyObject *PyErr_Format(PyObject *exception, const char *format, ...);

extern PyObject *PyExc_TypeError;
;
static inline int _PyType_Check(PyObject *op) ;

PyObject *_PyErr_Format(PyThreadState *tstate, PyObject *exception, const char *format, ...);

extern PyObject *PyExc_SystemError;
;
static inline void _Py_XINCREF(PyObject *op) ;

_PyErr_StackItem *_PyErr_GetTopmostException(PyThreadState *tstate) ;

void _PyErr_Clear(PyThreadState *tstate);

static PyObject *_PyErr_CreateException(PyObject *exception_type, PyObject *value) ;


PyObject *PyException_GetContext(PyObject *);


void PyException_SetContext(PyObject *, PyObject *);


PyObject *PyException_GetTraceback(PyObject *);

void _PyErr_Restore(PyThreadState *tstate, PyObject *type, PyObject *value, PyObject *traceback) ;


PyObject *PyUnicode_FromString(const char *u);

void _PyErr_SetObject(PyThreadState *tstate, PyObject *exception, PyObject *value) ;


Py_ssize_t PyTuple_Size(PyObject *);

int PyErr_GivenExceptionMatches(PyObject *err, PyObject *exc) ;


int PyType_IsSubtype(PyTypeObject *, PyTypeObject *);


int PyObject_IsSubclass(PyObject *object, PyObject *typeorclass);

void _PyErr_SetString(PyThreadState *tstate, PyObject *exception, const char *string) ;

extern PyObject *PyExc_RecursionError;
;
void _PyErr_Fetch(PyThreadState *tstate, PyObject **type, PyObject **value, PyObject **traceback);


void _Py_FatalErrorFunc(const char *func, const char *message);

extern PyObject *PyExc_MemoryError;
;
void _PyErr_NormalizeException(PyThreadState *tstate, PyObject **exc, PyObject **val, PyObject **tb) ;


int PyException_SetTraceback(PyObject *, PyObject *);

static PyObject *_PyErr_FormatV(PyThreadState *tstate, PyObject *exception, const char *format, va_list vargs);


void PyException_SetCause(PyObject *, PyObject *);

static inline PyThreadState *_PyThreadState_GET(void) ;

static PyObject *_PyErr_FormatVFromCause(PyThreadState *tstate, PyObject *exception, const char *format, va_list vargs) ;


PyObject *PyUnicode_FromFormatV(const char *format, va_list vargs);

#endif