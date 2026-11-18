#ifndef __HEADER_FUNC_H__ 
#define __HEADER_FUNC_H__
#include"header_type.h" 

void _Py_Dealloc(PyObject *);

static inline void _Py_DECREF(PyObject *op) ;

static inline int PyType_HasFeature(PyTypeObject *type, unsigned long feature) ;

static inline vectorcallfunc PyVectorcall_Function(PyObject *callable) ;


PyObject *_PyObject_MakeTpCall(PyThreadState *tstate, PyObject *callable, PyObject *const *args, Py_ssize_t nargs, PyObject *keywords);

static inline Py_ssize_t PyVectorcall_NARGS(size_t n) ;


PyObject *_Py_CheckFunctionResult(PyThreadState *tstate, PyObject *callable, PyObject *result, const char *where);


PyThreadState *PyThreadState_Get(void);

static inline PyObject *_PyObject_VectorcallTstate(PyThreadState *tstate, PyObject *callable, PyObject *const *args, size_t nargsf, PyObject *kwnames) ;


void PyMem_Free(void *ptr);

static void merge_freemem(MergeState *ms) ;


PyObject *PyErr_NoMemory(void);


void *PyMem_Malloc(size_t size);

static int merge_getmem(MergeState *ms, Py_ssize_t need) ;

static inline void sortslice_memcpy(sortslice *s1, Py_ssize_t i, sortslice *s2, Py_ssize_t j, Py_ssize_t n) ;

static inline void sortslice_copy_incr(sortslice *dst, sortslice *src) ;

static Py_ssize_t gallop_right(MergeState *ms, PyObject *key, PyObject **a, Py_ssize_t n, Py_ssize_t hint) ;

static inline void sortslice_advance(sortslice *slice, Py_ssize_t n) ;

static Py_ssize_t gallop_left(MergeState *ms, PyObject *key, PyObject **a, Py_ssize_t n, Py_ssize_t hint) ;

static inline void sortslice_memmove(sortslice *s1, Py_ssize_t i, sortslice *s2, Py_ssize_t j, Py_ssize_t n) ;

static inline void sortslice_copy(sortslice *s1, Py_ssize_t i, sortslice *s2, Py_ssize_t j) ;

static inline void sortslice_copy_decr(sortslice *dst, sortslice *src) ;

static Py_ssize_t merge_lo(MergeState *ms, sortslice ssa, Py_ssize_t na, sortslice ssb, Py_ssize_t nb) ;

static Py_ssize_t merge_hi(MergeState *ms, sortslice ssa, Py_ssize_t na, sortslice ssb, Py_ssize_t nb) ;

static Py_ssize_t merge_at(MergeState *ms, Py_ssize_t i) ;

static void reverse_slice(PyObject **lo, PyObject **hi) ;


int PyObject_RichCompareBool(PyObject *, PyObject *, int);

extern PyObject _Py_NotImplementedStruct;
;
static inline int _Py_IS_TYPE(const PyObject *ob, const PyTypeObject *type) ;


int PyObject_IsTrue(PyObject *);

extern PyTypeObject PyBool_Type;
;
extern struct _longobject _Py_TrueStruct;
;
extern PyObject _Py_NoneStruct;
;
static inline void _Py_SET_SIZE(PyVarObject *ob, Py_ssize_t size) ;

static inline PyObject *PyObject_CallOneArg(PyObject *func, PyObject *arg) ;

static int unsafe_latin_compare(PyObject *v, PyObject *w, MergeState *ms) ;

static int unsafe_long_compare(PyObject *v, PyObject *w, MergeState *ms) ;

static int unsafe_float_compare(PyObject *v, PyObject *w, MergeState *ms) ;

static int unsafe_object_compare(PyObject *v, PyObject *w, MergeState *ms) ;

static int safe_object_compare(PyObject *v, PyObject *w, MergeState *ms) ;

static int unsafe_tuple_compare(PyObject *v, PyObject *w, MergeState *ms) ;

extern PyTypeObject PyTuple_Type;
;
extern PyTypeObject PyLong_Type;
;
extern PyTypeObject PyUnicode_Type;
;
extern PyTypeObject PyFloat_Type;
;
static void merge_init(MergeState *ms, Py_ssize_t list_size, int has_keyfunc) ;

static Py_ssize_t merge_compute_minrun(Py_ssize_t n) ;

static Py_ssize_t count_run(MergeState *ms, PyObject **lo, PyObject **hi, int *descending) ;

static void reverse_sortslice(sortslice *s, Py_ssize_t n) ;

static int binarysort(MergeState *ms, sortslice lo, PyObject **hi, PyObject **start) ;

static int merge_collapse(MergeState *ms) ;

static int merge_force_collapse(MergeState *ms) ;


void PyErr_SetString(PyObject *exception, const char *string);

static inline void _Py_XDECREF(PyObject *op) ;

#endif