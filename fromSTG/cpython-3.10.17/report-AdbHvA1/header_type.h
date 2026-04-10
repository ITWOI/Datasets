#ifndef __HEADER_TYPE_H__ 
#define __HEADER_TYPE_H__
#include"../common.h" 
struct _object;//insertRecordDeclare 

/*TD*/typedef struct _object PyObject;

struct _typeobject;//insertRecordDeclare 

/*TD*/typedef struct _typeobject PyTypeObject;

/*TD*/typedef ssize_t Py_ssize_t;


struct _object {
    Py_ssize_t ob_refcnt;
    PyTypeObject *ob_type;
};


/*Ano*/typedef struct {
    PyObject ob_base;
    Py_ssize_t ob_size;
} PyVarObject;

/*TD*/typedef void (*destructor)(PyObject *);

/*TD*/typedef PyObject *(*getattrfunc)(PyObject *, char *);

/*TD*/typedef int (*setattrfunc)(PyObject *, char *, PyObject *);

/*TD*/typedef PyObject *(*unaryfunc)(PyObject *);


typedef enum {
    PYGEN_RETURN = 0,
    PYGEN_ERROR = -1,
    PYGEN_NEXT = 1
} PySendResult;

/*TD*/typedef PySendResult (*sendfunc)(PyObject *, PyObject *, PyObject **);


/*Ano*/typedef struct {
    unaryfunc am_await;
    unaryfunc am_aiter;
    unaryfunc am_anext;
    sendfunc am_send;
} PyAsyncMethods;

/*TD*/typedef PyObject *(*reprfunc)(PyObject *);

/*TD*/typedef PyObject *(*binaryfunc)(PyObject *, PyObject *);

/*TD*/typedef PyObject *(*ternaryfunc)(PyObject *, PyObject *, PyObject *);

/*TD*/typedef int (*inquiry)(PyObject *);


/*Ano*/typedef struct {
    binaryfunc nb_add;
    binaryfunc nb_subtract;
    binaryfunc nb_multiply;
    binaryfunc nb_remainder;
    binaryfunc nb_divmod;
    ternaryfunc nb_power;
    unaryfunc nb_negative;
    unaryfunc nb_positive;
    unaryfunc nb_absolute;
    inquiry nb_bool;
    unaryfunc nb_invert;
    binaryfunc nb_lshift;
    binaryfunc nb_rshift;
    binaryfunc nb_and;
    binaryfunc nb_xor;
    binaryfunc nb_or;
    unaryfunc nb_int;
    void *nb_reserved;
    unaryfunc nb_float;
    binaryfunc nb_inplace_add;
    binaryfunc nb_inplace_subtract;
    binaryfunc nb_inplace_multiply;
    binaryfunc nb_inplace_remainder;
    ternaryfunc nb_inplace_power;
    binaryfunc nb_inplace_lshift;
    binaryfunc nb_inplace_rshift;
    binaryfunc nb_inplace_and;
    binaryfunc nb_inplace_xor;
    binaryfunc nb_inplace_or;
    binaryfunc nb_floor_divide;
    binaryfunc nb_true_divide;
    binaryfunc nb_inplace_floor_divide;
    binaryfunc nb_inplace_true_divide;
    unaryfunc nb_index;
    binaryfunc nb_matrix_multiply;
    binaryfunc nb_inplace_matrix_multiply;
} PyNumberMethods;

/*TD*/typedef Py_ssize_t (*lenfunc)(PyObject *);

/*TD*/typedef PyObject *(*ssizeargfunc)(PyObject *, Py_ssize_t);

/*TD*/typedef int (*ssizeobjargproc)(PyObject *, Py_ssize_t, PyObject *);

/*TD*/typedef int (*objobjproc)(PyObject *, PyObject *);


/*Ano*/typedef struct {
    lenfunc sq_length;
    binaryfunc sq_concat;
    ssizeargfunc sq_repeat;
    ssizeargfunc sq_item;
    void *was_sq_slice;
    ssizeobjargproc sq_ass_item;
    void *was_sq_ass_slice;
    objobjproc sq_contains;
    binaryfunc sq_inplace_concat;
    ssizeargfunc sq_inplace_repeat;
} PySequenceMethods;

/*TD*/typedef int (*objobjargproc)(PyObject *, PyObject *, PyObject *);


/*Ano*/typedef struct {
    lenfunc mp_length;
    binaryfunc mp_subscript;
    objobjargproc mp_ass_subscript;
} PyMappingMethods;

/*TD*/typedef Py_ssize_t Py_hash_t;

/*TD*/typedef Py_hash_t (*hashfunc)(PyObject *);

/*TD*/typedef PyObject *(*getattrofunc)(PyObject *, PyObject *);

/*TD*/typedef int (*setattrofunc)(PyObject *, PyObject *, PyObject *);

struct bufferinfo;//insertRecordDeclare 

/*TD*/typedef struct bufferinfo Py_buffer;

/*TD*/typedef int (*getbufferproc)(PyObject *, Py_buffer *, int);

/*TD*/typedef void (*releasebufferproc)(PyObject *, Py_buffer *);


/*Ano*/typedef struct {
    getbufferproc bf_getbuffer;
    releasebufferproc bf_releasebuffer;
} PyBufferProcs;

/*TD*/typedef int (*visitproc)(PyObject *, void *);

/*TD*/typedef int (*traverseproc)(PyObject *, visitproc, void *);

/*TD*/typedef PyObject *(*richcmpfunc)(PyObject *, PyObject *, int);

/*TD*/typedef PyObject *(*getiterfunc)(PyObject *);

/*TD*/typedef PyObject *(*iternextfunc)(PyObject *);

struct PyMethodDef;//insertRecordDeclare 

struct PyMemberDef;//insertRecordDeclare 

struct PyGetSetDef;//insertRecordDeclare 

/*TD*/typedef PyObject *(*descrgetfunc)(PyObject *, PyObject *, PyObject *);

/*TD*/typedef int (*descrsetfunc)(PyObject *, PyObject *, PyObject *);

/*TD*/typedef int (*initproc)(PyObject *, PyObject *, PyObject *);

/*TD*/typedef PyObject *(*allocfunc)(PyTypeObject *, Py_ssize_t);

/*TD*/typedef PyObject *(*newfunc)(PyTypeObject *, PyObject *, PyObject *);

/*TD*/typedef void (*freefunc)(void *);

/*TD*/typedef PyObject *(*vectorcallfunc)(PyObject *, PyObject *const *, size_t, PyObject *);


struct _typeobject {
    PyVarObject ob_base;
    const char *tp_name;
    Py_ssize_t tp_basicsize;
    Py_ssize_t tp_itemsize;
    destructor tp_dealloc;
    Py_ssize_t tp_vectorcall_offset;
    getattrfunc tp_getattr;
    setattrfunc tp_setattr;
    PyAsyncMethods *tp_as_async;
    reprfunc tp_repr;
    PyNumberMethods *tp_as_number;
    PySequenceMethods *tp_as_sequence;
    PyMappingMethods *tp_as_mapping;
    hashfunc tp_hash;
    ternaryfunc tp_call;
    reprfunc tp_str;
    getattrofunc tp_getattro;
    setattrofunc tp_setattro;
    PyBufferProcs *tp_as_buffer;
    unsigned long tp_flags;
    const char *tp_doc;
    traverseproc tp_traverse;
    inquiry tp_clear;
    richcmpfunc tp_richcompare;
    Py_ssize_t tp_weaklistoffset;
    getiterfunc tp_iter;
    iternextfunc tp_iternext;
    struct PyMethodDef *tp_methods;
    struct PyMemberDef *tp_members;
    struct PyGetSetDef *tp_getset;
    struct _typeobject *tp_base;
    PyObject *tp_dict;
    descrgetfunc tp_descr_get;
    descrsetfunc tp_descr_set;
    Py_ssize_t tp_dictoffset;
    initproc tp_init;
    allocfunc tp_alloc;
    newfunc tp_new;
    freefunc tp_free;
    inquiry tp_is_gc;
    PyObject *tp_bases;
    PyObject *tp_mro;
    PyObject *tp_cache;
    PyObject *tp_subclasses;
    PyObject *tp_weaklist;
    destructor tp_del;
    unsigned int tp_version_tag;
    destructor tp_finalize;
    vectorcallfunc tp_vectorcall;
};


/*Ano*/typedef struct {
    PyVarObject ob_base;
    PyObject **ob_item;
    Py_ssize_t allocated;
} PyListObject;


/*Ano*/typedef struct {
    PyVarObject ob_base;
    PyObject *ob_item[1];
} PyTupleObject;

/*TD*/typedef struct PyMethodDef PyMethodDef;

/*TD*/typedef PyObject *(*PyCFunction)(PyObject *, PyObject *);


struct PyMethodDef {
    const char *ml_name;
    PyCFunction ml_meth;
    int ml_flags;
    const char *ml_doc;
};

#endif