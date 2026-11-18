#ifndef __HEADER_TYPE_H__ 
#define __HEADER_TYPE_H__
#include"../common.h" 
/*TD*/typedef ssize_t Py_ssize_t;

struct _object;//insertRecordDeclare 

/*TD*/typedef struct _object PyObject;

struct _typeobject;//insertRecordDeclare 

/*TD*/typedef struct _typeobject PyTypeObject;


struct _object {
    Py_ssize_t ob_refcnt;
    PyTypeObject *ob_type;
};

struct _Py_slist_item_s;//insertRecordDeclare 

/*TD*/typedef struct _Py_slist_item_s _Py_slist_item_t;


struct _Py_slist_item_s {
    struct _Py_slist_item_s *next;
};

/*TD*/typedef size_t Py_uhash_t;


/*Ano*/typedef struct {
    _Py_slist_item_t _Py_slist_item;
    Py_uhash_t key_hash;
    void *key;
    void *value;
} _Py_hashtable_entry_t;

struct _Py_hashtable_t;//insertRecordDeclare 

/*TD*/typedef struct _Py_hashtable_t _Py_hashtable_t;

/*TD*/typedef _Py_hashtable_entry_t *(*_Py_hashtable_get_entry_func)(_Py_hashtable_t *, const void *);


/*Ano*/typedef struct {
    _Py_slist_item_t *head;
} _Py_slist_t;

/*TD*/typedef Py_uhash_t (*_Py_hashtable_hash_func)(const void *);

/*TD*/typedef int (*_Py_hashtable_compare_func)(const void *, const void *);

/*TD*/typedef void (*_Py_hashtable_destroy_func)(void *);


/*Ano*/typedef struct {
    void *(*malloc)(size_t);
    void (*free)(void *);
} _Py_hashtable_allocator_t;


struct _Py_hashtable_t {
    size_t nentries;
    size_t nbuckets;
    _Py_slist_t *buckets;
    _Py_hashtable_get_entry_func get_entry_func;
    _Py_hashtable_hash_func hash_func;
    _Py_hashtable_compare_func compare_func;
    _Py_hashtable_destroy_func key_destroy_func;
    _Py_hashtable_destroy_func value_destroy_func;
    _Py_hashtable_allocator_t alloc;
};


/*Ano*/typedef struct {
    FILE *fp;
    int error;
    int depth;
    PyObject *str;
    char *ptr;
    const char *end;
    char *buf;
    _Py_hashtable_t *hashtable;
    int version;
} WFILE;

struct _IO_FILE;//insertRecordDeclare 


/*Ano*/typedef struct {
    PyObject ob_base;
    Py_ssize_t ob_size;
} PyVarObject;

/*TD*/typedef Py_ssize_t Py_hash_t;


/*Ano*/typedef struct {
    PyVarObject ob_base;
    Py_hash_t ob_shash;
    char ob_sval[1];
} PyBytesObject;

struct _longobject;//insertRecordDeclare 

/*TD*/typedef struct _longobject PyLongObject;

/*TD*/typedef uint32_t digit;


struct _longobject {
    PyVarObject ob_base;
    digit ob_digit[1];
};


/*Ano*/typedef struct {
    PyObject ob_base;
    double ob_fval;
} PyFloatObject;


/*Ano*/typedef struct {
    PyObject ob_base;
    Py_ssize_t length;
    Py_hash_t hash;
    struct {
        unsigned int interned : 2;
        unsigned int kind : 3;
        unsigned int compact : 1;
        unsigned int ascii : 1;
        unsigned int ready : 1;
        unsigned int : 24;
    } state;
    wchar_t *wstr;
} PyASCIIObject;

/*TD*/typedef uint8_t Py_UCS1;


/*Ano*/typedef struct {
    PyObject *key;
    Py_hash_t hash;
} setentry;


/*Ano*/typedef struct {
    PyObject ob_base;
    Py_ssize_t fill;
    Py_ssize_t used;
    Py_ssize_t mask;
    setentry *table;
    Py_hash_t hash;
    Py_ssize_t finger;
    setentry smalltable[8];
    PyObject *weakreflist;
} PySetObject;

struct PyCodeObject;//insertRecordDeclare 

/*TD*/typedef struct PyCodeObject PyCodeObject;

struct _PyOpcache;//insertRecordDeclare 

/*TD*/typedef struct _PyOpcache _PyOpcache;


struct PyCodeObject {
    PyObject ob_base;
    int co_argcount;
    int co_posonlyargcount;
    int co_kwonlyargcount;
    int co_nlocals;
    int co_stacksize;
    int co_flags;
    int co_firstlineno;
    PyObject *co_code;
    PyObject *co_consts;
    PyObject *co_names;
    PyObject *co_varnames;
    PyObject *co_freevars;
    PyObject *co_cellvars;
    Py_ssize_t *co_cell2arg;
    PyObject *co_filename;
    PyObject *co_name;
    PyObject *co_linetable;
    void *co_zombieframe;
    PyObject *co_weakreflist;
    void *co_extra;
    unsigned char *co_opcache_map;
    _PyOpcache *co_opcache;
    int co_opcache_flag;
    unsigned char co_opcache_size;
};

struct bufferinfo;//insertRecordDeclare 

/*TD*/typedef struct bufferinfo Py_buffer;


struct bufferinfo {
    void *buf;
    PyObject *obj;
    Py_ssize_t len;
    Py_ssize_t itemsize;
    int readonly;
    int ndim;
    char *format;
    Py_ssize_t *shape;
    Py_ssize_t *strides;
    Py_ssize_t *suboffsets;
    void *internal;
};

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

/*TD*/typedef Py_hash_t (*hashfunc)(PyObject *);

/*TD*/typedef PyObject *(*getattrofunc)(PyObject *, PyObject *);

/*TD*/typedef int (*setattrofunc)(PyObject *, PyObject *, PyObject *);

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
    PyASCIIObject _base;
    Py_ssize_t utf8_length;
    char *utf8;
    Py_ssize_t wstr_length;
} PyCompactUnicodeObject;

/*TD*/typedef uint16_t Py_UCS2;

/*TD*/typedef uint32_t Py_UCS4;


/*Ano*/typedef struct {
    PyCompactUnicodeObject _base;
    union {
        void *any;
        Py_UCS1 *latin1;
        Py_UCS2 *ucs2;
        Py_UCS4 *ucs4;
    } data;
} PyUnicodeObject;


/*Ano*/typedef struct {
    PyVarObject ob_base;
    PyObject *ob_item[1];
} PyTupleObject;


/*Ano*/typedef struct {
    PyVarObject ob_base;
    PyObject **ob_item;
    Py_ssize_t allocated;
} PyListObject;

#endif