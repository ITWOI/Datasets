#ifndef __HEADER_FUNC_H__ 
#define __HEADER_FUNC_H__
#include"header_type.h" 
static inline int _Py_IS_TYPE(const PyObject *ob, const PyTypeObject *type) ;


int PyType_IsSubtype(PyTypeObject *, PyTypeObject *);


void _Py_Dealloc(PyObject *);

static inline void _Py_DECREF(PyObject *op) ;

static inline int PyType_HasFeature(PyTypeObject *type, unsigned long feature) ;

static inline vectorcallfunc PyVectorcall_Function(PyObject *callable) ;


PyObject *_PyObject_MakeTpCall(PyThreadState *tstate, PyObject *callable, PyObject *const *args, Py_ssize_t nargs, PyObject *keywords);

static inline Py_ssize_t PyVectorcall_NARGS(size_t n) ;


PyObject *_Py_CheckFunctionResult(PyThreadState *tstate, PyObject *callable, PyObject *result, const char *where);


PyThreadState *PyThreadState_Get(void);

static inline PyObject *_PyObject_VectorcallTstate(PyThreadState *tstate, PyObject *callable, PyObject *const *args, size_t nargsf, PyObject *kwnames) ;


PyGILState_STATE PyGILState_Ensure(void);


Py_ssize_t PySequence_Size(PyObject *o);

static void PrintError(const char *msg, ...) ;


PyObject *PyTuple_New(Py_ssize_t size);


extern StgDictObject *PyType_stgdict(PyObject *obj);


extern int _ctypes_simple_instance(PyObject *obj);

static inline int _PyObject_TypeCheck(PyObject *ob, PyTypeObject *type) ;


void PyErr_SetString(PyObject *exception, const char *string);


PyObject *PySequence_GetItem(PyObject *o, Py_ssize_t i);

static inline PyObject *_PyObject_CallNoArg(PyObject *func) ;

extern PyTypeObject PyCData_Type;
;

PyObject *_ctypes_get_errobj(int **pspace);


PyObject *PyObject_CallObject(PyObject *callable, PyObject *args);


void _PyErr_WriteUnraisableMsg(const char *err_msg, PyObject *obj);

static inline void _Py_XDECREF(PyObject *op) ;


int PyErr_WarnEx(PyObject *category, const char *message, Py_ssize_t stack_level);

extern ffi_type ffi_type_void;
;

extern struct fielddesc *_ctypes_get_fielddesc(const char *fmt);

extern PyObject _Py_NoneStruct;
;
static void _CallPythonObject(void *mem, ffi_type *restype, SETFUNC setfunc, PyObject *callable, PyObject *converters, int flags, void **pArgs) ;

#endif