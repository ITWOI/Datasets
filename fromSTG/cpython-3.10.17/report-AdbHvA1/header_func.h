#ifndef __HEADER_FUNC_H__ 
#define __HEADER_FUNC_H__
#include"header_type.h" 

void _Py_Dealloc(PyObject *);

static inline void _Py_DECREF(PyObject *op) ;

static inline void _Py_INCREF(PyObject *op) ;

static inline void _Py_SET_SIZE(PyVarObject *ob, Py_ssize_t size) ;


void *PyMem_Realloc(void *ptr, size_t new_size);


PyObject *PyErr_NoMemory(void);


void *PyMem_Malloc(size_t size);

static int list_resize(PyListObject *self, Py_ssize_t newsize) ;

static inline void _Py_XDECREF(PyObject *op) ;


void PyMem_Free(void *ptr);

static inline int _Py_IS_TYPE(const PyObject *ob, const PyTypeObject *type) ;


PyObject *PySequence_Fast(PyObject *o, const char *m);

static inline int PyType_HasFeature(PyTypeObject *type, unsigned long feature) ;

static inline PyObject *_Py_NewRef(PyObject *obj) ;

static int list_preallocate_exact(PyListObject *self, Py_ssize_t size) ;

static void list_dealloc(PyListObject *op) ;

static PyObject *list_repr(PyListObject *v) ;


Py_hash_t PyObject_HashNotImplemented(PyObject *);


PyObject *PyObject_GenericGetAttr(PyObject *, PyObject *);

static int list_traverse(PyListObject *o, visitproc visit, void *arg) ;

static int _list_clear(PyListObject *a) ;

static PyObject *list_richcompare(PyObject *v, PyObject *w, int op) ;

static PyObject *list_iter(PyObject *seq);

static int list___init__(PyObject *self, PyObject *args, PyObject *kwargs) ;


PyObject *PyType_GenericAlloc(PyTypeObject *, Py_ssize_t);


PyObject *PyType_GenericNew(PyTypeObject *, PyObject *, PyObject *);


void PyObject_GC_Del(void *);

static PyObject *list_vectorcall(PyObject *type, PyObject *const *args, size_t nargsf, PyObject *kwnames) ;

extern PyTypeObject PyType_Type;
static Py_ssize_t list_length(PyListObject *a) ;

static PyObject *list_concat(PyListObject *a, PyObject *bb) ;

static PyObject *list_repeat(PyListObject *a, Py_ssize_t n) ;

static PyObject *list_item(PyListObject *a, Py_ssize_t i) ;

static int list_ass_item(PyListObject *a, Py_ssize_t i, PyObject *v) ;

static int list_contains(PyListObject *a, PyObject *el) ;

static PyObject *list_inplace_concat(PyListObject *self, PyObject *other) ;

static PyObject *list_inplace_repeat(PyListObject *self, Py_ssize_t n) ;

static PySequenceMethods list_as_sequence = {(lenfunc)list_length, (binaryfunc)list_concat, (ssizeargfunc)list_repeat, (ssizeargfunc)list_item, 0, (ssizeobjargproc)list_ass_item, 0, (objobjproc)list_contains, (binaryfunc)list_inplace_concat, (ssizeargfunc)list_inplace_repeat};
static PyObject *list_subscript(PyListObject *self, PyObject *item) ;

static int list_ass_subscript(PyListObject *self, PyObject *item, PyObject *value) ;

static PyMappingMethods list_as_mapping = {(lenfunc)list_length, (binaryfunc)list_subscript, (objobjargproc)list_ass_subscript};
static const char list___init____doc__[] = "list(iterable=(), /)\n--\n\nBuilt-in mutable sequence.\n\nIf no argument is given, the constructor creates a new empty list.\nThe argument must be an iterable if specified.";
static PyObject *list___reversed__(PyListObject *self, PyObject *_unused_ignored) ;

static const char list___reversed____doc__[] = "__reversed__($self, /)\n--\n\nReturn a reverse iterator over the list.";
static PyObject *list___sizeof__(PyListObject *self, PyObject *_unused_ignored) ;

static const char list___sizeof____doc__[] = "__sizeof__($self, /)\n--\n\nReturn the size of the list in memory, in bytes.";
static PyObject *list_clear(PyListObject *self, PyObject *_unused_ignored) ;

static const char list_clear__doc__[] = "clear($self, /)\n--\n\nRemove all items from list.";
static PyObject *list_copy(PyListObject *self, PyObject *_unused_ignored) ;

static const char list_copy__doc__[] = "copy($self, /)\n--\n\nReturn a shallow copy of the list.";
static PyObject *list_append(PyListObject *self, PyObject *object) ;

static const char list_append__doc__[] = "append($self, object, /)\n--\n\nAppend object to the end of the list.";
static PyObject *list_insert(PyListObject *self, PyObject *const *args, Py_ssize_t nargs) ;

static const char list_insert__doc__[] = "insert($self, index, object, /)\n--\n\nInsert object before index.";
static PyObject *list_extend(PyListObject *self, PyObject *iterable) ;

static const char list_extend__doc__[] = "extend($self, iterable, /)\n--\n\nExtend list by appending elements from the iterable.";
static PyObject *list_pop(PyListObject *self, PyObject *const *args, Py_ssize_t nargs) ;

static const char list_pop__doc__[] = "pop($self, index=-1, /)\n--\n\nRemove and return item at index (default last).\n\nRaises IndexError if list is empty or index is out of range.";
static PyObject *list_remove(PyListObject *self, PyObject *value) ;

static const char list_remove__doc__[] = "remove($self, value, /)\n--\n\nRemove first occurrence of value.\n\nRaises ValueError if the value is not present.";
static PyObject *list_index(PyListObject *self, PyObject *const *args, Py_ssize_t nargs) ;

static const char list_index__doc__[] = "index($self, value, start=0, stop=sys.maxsize, /)\n--\n\nReturn first index of value.\n\nRaises ValueError if the value is not present.";
static PyObject *list_count(PyListObject *self, PyObject *value) ;

static const char list_count__doc__[] = "count($self, value, /)\n--\n\nReturn number of occurrences of value.";
static PyObject *list_reverse(PyListObject *self, PyObject *_unused_ignored) ;

static const char list_reverse__doc__[] = "reverse($self, /)\n--\n\nReverse *IN PLACE*.";
static PyObject *list_sort(PyListObject *self, PyObject *const *args, Py_ssize_t nargs, PyObject *kwnames) ;

static const char list_sort__doc__[] = "sort($self, /, *, key=None, reverse=False)\n--\n\nSort the list in ascending order and return None.\n\nThe sort is in-place (i.e. the list itself is modified) and stable (i.e. the\norder of two equal elements is maintained).\n\nIf a key function is given, apply it once to each list item and sort them,\nascending or descending, according to their function values.\n\nThe reverse flag can be set to sort in descending order.";

PyObject *Py_GenericAlias(PyObject *, PyObject *);

static PyMethodDef list_methods[] = {{"__getitem__", (PyCFunction)list_subscript, 8 | 64, "x.__getitem__(y) <==> x[y]"}, {"__reversed__", (PyCFunction)list___reversed__, 4, list___reversed____doc__}, {"__sizeof__", (PyCFunction)list___sizeof__, 4, list___sizeof____doc__}, {"clear", (PyCFunction)list_clear, 4, list_clear__doc__}, {"copy", (PyCFunction)list_copy, 4, list_copy__doc__}, {"append", (PyCFunction)list_append, 8, list_append__doc__}, {"insert", (PyCFunction)(void (*)(void))list_insert, 128, list_insert__doc__}, {"extend", (PyCFunction)list_extend, 8, list_extend__doc__}, {"pop", (PyCFunction)(void (*)(void))list_pop, 128, list_pop__doc__}, {"remove", (PyCFunction)list_remove, 8, list_remove__doc__}, {"index", (PyCFunction)(void (*)(void))list_index, 128, list_index__doc__}, {"count", (PyCFunction)list_count, 8, list_count__doc__}, {"reverse", (PyCFunction)list_reverse, 4, list_reverse__doc__}, {"sort", (PyCFunction)(void (*)(void))list_sort, 128 | 2, list_sort__doc__}, {"__class_getitem__", (PyCFunction)Py_GenericAlias, 8 | 16, "See PEP 585"}, {((void *)0), ((void *)0)}};
PyTypeObject PyList_Type = {{{1, &PyType_Type}, 0}, "list", sizeof(PyListObject), 0, (destructor)list_dealloc, 0, 0, 0, 0, (reprfunc)list_repr, 0, &list_as_sequence, &list_as_mapping, PyObject_HashNotImplemented, 0, 0, PyObject_GenericGetAttr, 0, 0, (0 | 0) | (1UL << 14) | (1UL << 10) | (1UL << 25) | (1UL << 22) | (1 << 5), list___init____doc__, (traverseproc)list_traverse, (inquiry)_list_clear, list_richcompare, 0, list_iter, 0, list_methods, 0, 0, 0, 0, 0, 0, 0, (initproc)list___init__, PyType_GenericAlloc, PyType_GenericNew, PyObject_GC_Del, .tp_vectorcall = list_vectorcall};
;
extern PyTypeObject PyTuple_Type;
;
extern PyObject _Py_NoneStruct;
;

PyObject *PyObject_GetIter(PyObject *);


Py_ssize_t PyObject_LengthHint(PyObject *o, Py_ssize_t);


PyObject *PyErr_Occurred(void);


int PyErr_ExceptionMatches(PyObject *);


void PyErr_Clear(void);

extern PyObject *PyExc_StopIteration;
;
static int app1(PyListObject *self, PyObject *v) ;


int _PyArg_NoKwnames(const char *funcname, PyObject *kwnames);

static inline Py_ssize_t PyVectorcall_NARGS(size_t n) ;


int _PyArg_CheckPositional(const char *, Py_ssize_t, Py_ssize_t, Py_ssize_t);

static int list___init___impl(PyListObject *self, PyObject *iterable) ;

#endif