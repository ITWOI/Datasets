#ifndef __HEADER_FUNC_H__ 
#define __HEADER_FUNC_H__
#include"header_type.h" 
static inline int _Py_IS_TYPE(const PyObject *ob, const PyTypeObject *type) ;


int PyType_IsSubtype(PyTypeObject *, PyTypeObject *);


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


PyObject *_PyUnicode_FromId(_Py_Identifier *);


PyObject *PyObject_VectorcallMethod(PyObject *name, PyObject *const *args, size_t nargsf, PyObject *kwnames);

static inline PyObject *_PyObject_VectorcallMethodId(_Py_Identifier *name, PyObject *const *args, size_t nargsf, PyObject *kwnames) ;

static inline void _Py_XINCREF(PyObject *op) ;

extern PyObject _Py_NoneStruct;
;
static inline PyObject **_PyObject_GET_WEAKREFS_LISTPTR(PyObject *op) ;


void PyObject_GC_UnTrack(void *);

static void clear_weakref(PyWeakReference *self) ;


int PyArg_ParseTupleAndKeywords(PyObject *, PyObject *, const char *, char **, ...);

static inline Py_ssize_t _Py_REFCNT(const PyObject *ob) ;


void PyErr_SetString(PyObject *exception, const char *string);

extern PyObject *PyExc_TypeError;
;

Py_hash_t PyObject_Hash(PyObject *);


PyObject *PyUnicode_FromFormat(const char *format, ...);


int _PyObject_LookupAttrId(PyObject *, struct _Py_Identifier *, PyObject **);

static inline void _Py_XDECREF(PyObject *op) ;

static inline int _PyObject_TypeCheck(PyObject *ob, PyTypeObject *type) ;

static inline PyObject *_Py_NewRef(PyObject *obj) ;

static void weakref_dealloc(PyObject *self) ;

static PyObject *weakref_repr(PyWeakReference *self) ;

static Py_hash_t weakref_hash(PyWeakReference *self) ;

static PyObject *weakref_call(PyWeakReference *self, PyObject *args, PyObject *kw) ;

static int gc_traverse(PyWeakReference *self, visitproc visit, void *arg) ;

static int gc_clear(PyWeakReference *self) ;

static PyObject *weakref_richcompare(PyWeakReference *self, PyWeakReference *other, int op) ;

static int weakref___init__(PyObject *self, PyObject *args, PyObject *kwargs) ;


PyObject *PyType_GenericAlloc(PyTypeObject *, Py_ssize_t);

static PyObject *weakref___new__(PyTypeObject *type, PyObject *args, PyObject *kwargs) ;


void PyObject_GC_Del(void *);

extern PyTypeObject PyType_Type;

PyObject *Py_GenericAlias(PyObject *, PyObject *);

static PyMethodDef weakref_methods[] = {{"__class_getitem__", (PyCFunction)Py_GenericAlias, 8 | 16, "See PEP 585"}, {((void *)0)}};
static PyMemberDef weakref_members[] = {{"__callback__", 6, __builtin_offsetof(PyWeakReference, wr_callback), 1}, {((void *)0)}};
PyTypeObject _PyWeakref_RefType = {{{1, &PyType_Type}, 0}, "weakref.ReferenceType", sizeof(PyWeakReference), 0, weakref_dealloc, 0, 0, 0, 0, (reprfunc)weakref_repr, 0, 0, 0, (hashfunc)weakref_hash, (ternaryfunc)weakref_call, 0, 0, 0, 0, (0 | 0) | (1UL << 14) | (1UL << 10), 0, (traverseproc)gc_traverse, (inquiry)gc_clear, (richcmpfunc)weakref_richcompare, 0, 0, 0, weakref_methods, weakref_members, 0, 0, 0, 0, 0, 0, weakref___init__, PyType_GenericAlloc, weakref___new__, PyObject_GC_Del};
;
static void proxy_dealloc(PyWeakReference *self) ;

static PyObject *proxy_repr(PyWeakReference *proxy) ;

static PyObject *proxy_str(PyObject *proxy) ;

static PyObject *proxy_getattr(PyObject *x, PyObject *y) ;

static int proxy_setattr(PyWeakReference *proxy, PyObject *name, PyObject *value) ;

static PyObject *proxy_richcompare(PyObject *proxy, PyObject *v, int op) ;

static PyObject *proxy_iter(PyWeakReference *proxy) ;

static PyObject *proxy_iternext(PyWeakReference *proxy) ;

static PyObject *proxy_add(PyObject *x, PyObject *y) ;

static PyObject *proxy_sub(PyObject *x, PyObject *y) ;

static PyObject *proxy_mul(PyObject *x, PyObject *y) ;

static PyObject *proxy_mod(PyObject *x, PyObject *y) ;

static PyObject *proxy_divmod(PyObject *x, PyObject *y) ;

static PyObject *proxy_pow(PyObject *proxy, PyObject *v, PyObject *w) ;

static PyObject *proxy_neg(PyObject *proxy) ;

static PyObject *proxy_pos(PyObject *proxy) ;

static PyObject *proxy_abs(PyObject *proxy) ;

static int proxy_bool(PyWeakReference *proxy) ;

static PyObject *proxy_invert(PyObject *proxy) ;

static PyObject *proxy_lshift(PyObject *x, PyObject *y) ;

static PyObject *proxy_rshift(PyObject *x, PyObject *y) ;

static PyObject *proxy_and(PyObject *x, PyObject *y) ;

static PyObject *proxy_xor(PyObject *x, PyObject *y) ;

static PyObject *proxy_or(PyObject *x, PyObject *y) ;

static PyObject *proxy_int(PyObject *proxy) ;

static PyObject *proxy_float(PyObject *proxy) ;

static PyObject *proxy_iadd(PyObject *x, PyObject *y) ;

static PyObject *proxy_isub(PyObject *x, PyObject *y) ;

static PyObject *proxy_imul(PyObject *x, PyObject *y) ;

static PyObject *proxy_imod(PyObject *x, PyObject *y) ;

static PyObject *proxy_ipow(PyObject *proxy, PyObject *v, PyObject *w) ;

static PyObject *proxy_ilshift(PyObject *x, PyObject *y) ;

static PyObject *proxy_irshift(PyObject *x, PyObject *y) ;

static PyObject *proxy_iand(PyObject *x, PyObject *y) ;

static PyObject *proxy_ixor(PyObject *x, PyObject *y) ;

static PyObject *proxy_ior(PyObject *x, PyObject *y) ;

static PyObject *proxy_floor_div(PyObject *x, PyObject *y) ;

static PyObject *proxy_true_div(PyObject *x, PyObject *y) ;

static PyObject *proxy_ifloor_div(PyObject *x, PyObject *y) ;

static PyObject *proxy_itrue_div(PyObject *x, PyObject *y) ;

static PyObject *proxy_index(PyObject *proxy) ;

static PyObject *proxy_matmul(PyObject *x, PyObject *y) ;

static PyObject *proxy_imatmul(PyObject *x, PyObject *y) ;

static PyNumberMethods proxy_as_number = {proxy_add, proxy_sub, proxy_mul, proxy_mod, proxy_divmod, proxy_pow, proxy_neg, proxy_pos, proxy_abs, (inquiry)proxy_bool, proxy_invert, proxy_lshift, proxy_rshift, proxy_and, proxy_xor, proxy_or, proxy_int, 0, proxy_float, proxy_iadd, proxy_isub, proxy_imul, proxy_imod, proxy_ipow, proxy_ilshift, proxy_irshift, proxy_iand, proxy_ixor, proxy_ior, proxy_floor_div, proxy_true_div, proxy_ifloor_div, proxy_itrue_div, proxy_index, proxy_matmul, proxy_imatmul};
static Py_ssize_t proxy_length(PyWeakReference *proxy) ;

static int proxy_contains(PyWeakReference *proxy, PyObject *value) ;

static PySequenceMethods proxy_as_sequence = {(lenfunc)proxy_length, 0, 0, 0, 0, 0, 0, (objobjproc)proxy_contains};
static PyObject *proxy_getitem(PyObject *x, PyObject *y) ;

static int proxy_setitem(PyWeakReference *proxy, PyObject *key, PyObject *value) ;

static PyMappingMethods proxy_as_mapping = {(lenfunc)proxy_length, proxy_getitem, (objobjargproc)proxy_setitem};
static PyObject *proxy_bytes(PyObject *proxy, PyObject *_unused_ignored) ;

static PyObject *proxy_reversed(PyObject *proxy, PyObject *_unused_ignored) ;

static PyMethodDef proxy_methods[] = {{"__bytes__", proxy_bytes, 4}, {"__reversed__", proxy_reversed, 4}, {((void *)0), ((void *)0)}};
PyTypeObject _PyWeakref_ProxyType = {{{1, &PyType_Type}, 0}, "weakref.ProxyType", sizeof(PyWeakReference), 0, (destructor)proxy_dealloc, 0, 0, 0, 0, (reprfunc)proxy_repr, &proxy_as_number, &proxy_as_sequence, &proxy_as_mapping, 0, 0, proxy_str, proxy_getattr, (setattrofunc)proxy_setattr, 0, (0 | 0) | (1UL << 14), 0, (traverseproc)gc_traverse, (inquiry)gc_clear, proxy_richcompare, 0, (getiterfunc)proxy_iter, (iternextfunc)proxy_iternext, proxy_methods};
;
static PyObject *proxy_call(PyObject *proxy, PyObject *v, PyObject *w) ;

PyTypeObject _PyWeakref_CallableProxyType = {{{1, &PyType_Type}, 0}, "weakref.CallableProxyType", sizeof(PyWeakReference), 0, (destructor)proxy_dealloc, 0, 0, 0, 0, (unaryfunc)proxy_repr, &proxy_as_number, &proxy_as_sequence, &proxy_as_mapping, 0, proxy_call, proxy_str, proxy_getattr, (setattrofunc)proxy_setattr, 0, (0 | 0) | (1UL << 14), 0, (traverseproc)gc_traverse, (inquiry)gc_clear, proxy_richcompare, 0, (getiterfunc)proxy_iter, (iternextfunc)proxy_iternext};
;
extern PyObject _Py_NotImplementedStruct;
;
extern struct _longobject _Py_TrueStruct;
;
extern struct _longobject _Py_FalseStruct;
;

PyObject *PyObject_RichCompare(PyObject *, PyObject *, int);


int PyArg_UnpackTuple(PyObject *, const char *, Py_ssize_t, Py_ssize_t, ...);

static int parse_weakref_init_args(const char *funcname, PyObject *args, PyObject *kwargs, PyObject **obp, PyObject **callbackp) ;


PyObject *PyErr_Format(PyObject *exception, const char *format, ...);

static void get_basic_refs(PyWeakReference *head, PyWeakReference **refp, PyWeakReference **proxyp) ;

static void init_weakref(PyWeakReference *self, PyObject *ob, PyObject *callback) ;

static void insert_head(PyWeakReference *newref, PyWeakReference **list) ;

static void insert_after(PyWeakReference *newref, PyWeakReference *prev) ;


int _PyArg_NoKeywords(const char *funcname, PyObject *kwargs);

extern PyObject *PyExc_ReferenceError;
;
static int proxy_checkref(PyWeakReference *proxy) ;


int PyObject_SetAttr(PyObject *, PyObject *, PyObject *);


int PyObject_IsTrue(PyObject *);


int PySequence_Contains(PyObject *seq, PyObject *ob);


Py_ssize_t PyObject_Size(PyObject *o);


int PyObject_DelItem(PyObject *o, PyObject *key);


int PyObject_SetItem(PyObject *o, PyObject *key, PyObject *v);


PyObject *PyObject_GetIter(PyObject *);


int PyIter_Check(PyObject *);


PyObject *PyIter_Next(PyObject *);

static inline PyObject *PyObject_CallOneArg(PyObject *func, PyObject *arg) ;


void PyErr_WriteUnraisable(PyObject *);


void _PyErr_BadInternalCall(const char *filename, int lineno);


void PyErr_Fetch(PyObject **, PyObject **, PyObject **);

static void handle_callback(PyWeakReference *ref, PyObject *callback) ;


PyObject *PyTuple_New(Py_ssize_t size);


void _PyErr_ChainExceptions(PyObject *, PyObject *, PyObject *);


void PyErr_Restore(PyObject *, PyObject *, PyObject *);

Py_ssize_t _PyWeakref_GetWeakrefCount(PyWeakReference *head) ;

#endif