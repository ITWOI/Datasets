#ifndef __HEADER_FUNC_H__ 
#define __HEADER_FUNC_H__
#include"header_type.h" 
static inline int _Py_IS_TYPE(const PyObject *ob, const PyTypeObject *type) ;


int PyType_IsSubtype(PyTypeObject *, PyTypeObject *);


void _Py_Dealloc(PyObject *);

static inline void *_PyModule_GetState(PyObject *mod) ;


void PyErr_SetString(PyObject *exception, const char *string);

static inline void _Py_SET_SIZE(PyVarObject *ob, Py_ssize_t size) ;


void PyMem_Free(void *ptr);


void *PyMem_Realloc(void *ptr, size_t new_size);


PyObject *PyErr_NoMemory(void);


void _PyErr_BadInternalCall(const char *filename, int lineno);


void *PyMem_Malloc(size_t size);

static inline void _Py_DECREF(PyObject *op) ;

static int array_traverse(PyObject *module, visitproc visit, void *arg) ;

static int array_clear(PyObject *module) ;

static void array_free(void *module) ;

static const char module_doc[] = "This module defines an object type which can efficiently represent\nan array of basic values: characters, integers, floating point\nnumbers.  Arrays are sequence types and behave very much like lists,\nexcept that the type of objects stored in them is constrained.\n";
static PyObject *array__array_reconstructor(PyObject *module, PyObject *const *args, Py_ssize_t nargs) ;

static const char array__array_reconstructor__doc__[] = "_array_reconstructor($module, arraytype, typecode, mformat_code, items,\n                     /)\n--\n\nInternal. Used for pickling support.";
static PyMethodDef a_methods[] = {{"_array_reconstructor", (PyCFunction)(void (*)(void))array__array_reconstructor, 128, array__array_reconstructor__doc__}, {((void *)0), ((void *)0), 0, ((void *)0)}};
static int array_modexec(PyObject *m) ;

static PyModuleDef_Slot arrayslots[] = {{2, array_modexec}, {0, ((void *)0)}};
static struct PyModuleDef arraymodule = {.m_base = {{1, ((void *)0)}, ((void *)0), 0, ((void *)0)}, .m_name = "array", .m_size = sizeof(array_state), .m_doc = module_doc, .m_methods = a_methods, .m_slots = arrayslots, .m_traverse = array_traverse, .m_clear = array_clear, .m_free = array_free};
;
static array_state *get_array_state(PyObject *module) ;


PyObject *_PyType_GetModuleByDef(PyTypeObject *, struct PyModuleDef *);

static PyObject *newarrayobject(PyTypeObject *type, Py_ssize_t size, const struct arraydescr *descr) ;


int PyIndex_Check(PyObject *);


PyObject *PyErr_Occurred(void);


int PySlice_Unpack(PyObject *slice, Py_ssize_t *start, Py_ssize_t *stop, Py_ssize_t *step);


Py_ssize_t PySlice_AdjustIndices(Py_ssize_t length, Py_ssize_t *start, Py_ssize_t *stop, Py_ssize_t step);

extern PyObject *PyExc_IndexError;
;

Py_ssize_t PyNumber_AsSsize_t(PyObject *o, PyObject *exc);

extern PyTypeObject PySlice_Type;
;
static inline int _PyObject_TypeCheck(PyObject *ob, PyTypeObject *type) ;

static PyObject *array_slice(arrayobject *a, Py_ssize_t ilow, Py_ssize_t ihigh) ;

static int array_ass_subscr(arrayobject *self, PyObject *item, PyObject *value) ;


int PyErr_BadArgument(void);


PyObject *PyErr_Format(PyObject *exception, const char *format, ...);

static int array_resize(arrayobject *self, Py_ssize_t newsize) ;

#endif