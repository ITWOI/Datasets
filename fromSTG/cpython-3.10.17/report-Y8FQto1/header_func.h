#ifndef __HEADER_FUNC_H__ 
#define __HEADER_FUNC_H__
#include"header_type.h" 
void _Py_Dealloc(PyObject *);

static inline void _Py_DECREF(PyObject *op) ;

static inline int _Py_MakeRecCheck(PyThreadState *tstate) ;


int _Py_CheckRecursiveCall(PyThreadState *tstate, const char *where);

static inline PyThreadState *_PyRuntimeState_GetThreadState(_PyRuntimeState *runtime) ;

extern _PyRuntimeState _PyRuntime;
;
static inline int _PyType_HasFeature(PyTypeObject *type, unsigned long feature) ;

static inline Py_ssize_t _Py_REFCNT(const PyObject *ob) ;

void _PyObject_AssertFailed(PyObject *obj, const char *expr, const char *msg, const char *file, int line, const char *function);

static inline void _Py_SET_REFCNT(PyObject *ob, Py_ssize_t refcnt) ;

void PyObject_CallFinalizer(PyObject *self) ;

void _Py_NewReference(PyObject *op);


int PyErr_CheckSignals(void);


PyThreadState *PyEval_SaveThread(void);


void PyEval_RestoreThread(PyThreadState *);

PyObject *PyObject_Str(PyObject *);

PyObject *PyObject_Repr(PyObject *);

static inline int PyType_HasFeature(PyTypeObject *type, unsigned long feature) ;


PyObject *PyUnicode_AsEncodedString(PyObject *unicode, const char *encoding, const char *errors);


PyObject *PyErr_Format(PyObject *exception, const char *format, ...);

static inline void _Py_XDECREF(PyObject *op) ;

static inline int _PyMem_IsPtrFreed(const void *ptr) ;

int _PyObject_IsFreed(PyObject *op) ;

extern FILE *stderr;
;

PyGILState_STATE PyGILState_Ensure(void);

int PyObject_Print(PyObject *op, FILE *fp, int flags) ;


PyObject *PyUnicode_FromString(const char *u);


PyObject *PyUnicode_FromFormat(const char *format, ...);

static inline PyThreadState *_PyThreadState_GET(void) ;

static inline int _Py_EnterRecursiveCall(PyThreadState *tstate, const char *where) ;

static inline void _Py_LeaveRecursiveCall(PyThreadState *tstate) ;


PyObject *_PyErr_Format(PyThreadState *tstate, PyObject *exception, const char *format, ...);


int _PyUnicode_Ready(PyObject *unicode);

static inline int _Py_IS_TYPE(const PyObject *ob, const PyTypeObject *type) ;

static inline void _Py_INCREF(PyObject *op) ;

extern PyTypeObject PyUnicode_Type;
;

extern void _PyMem_DumpTraceback(int fd, const void *ptr);

void _PyObject_Dump(PyObject *op) ;

#endif