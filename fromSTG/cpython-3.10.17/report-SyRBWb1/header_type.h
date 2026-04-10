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

struct _ts;//insertRecordDeclare 

/*TD*/typedef struct _ts PyThreadState;

struct _is;//insertRecordDeclare 

/*TD*/typedef struct _is PyInterpreterState;

struct _frame;//insertRecordDeclare 

/*TD*/typedef struct _frame PyFrameObject;

struct _cframe;//insertRecordDeclare 

/*TD*/typedef struct _cframe CFrame;

/*TD*/typedef int (*Py_tracefunc)(PyObject *, PyFrameObject *, int, PyObject *);

struct _err_stackitem;//insertRecordDeclare 

/*TD*/typedef struct _err_stackitem _PyErr_StackItem;


struct _err_stackitem {
    PyObject *exc_type;
    PyObject *exc_value;
    PyObject *exc_traceback;
    struct _err_stackitem *previous_item;
};


struct _cframe {
    int use_tracing;
    struct _cframe *previous;
};


struct _ts {
    struct _ts *prev;
    struct _ts *next;
    PyInterpreterState *interp;
    PyFrameObject *frame;
    int recursion_depth;
    int recursion_headroom;
    int stackcheck_counter;
    int tracing;
    CFrame *cframe;
    Py_tracefunc c_profilefunc;
    Py_tracefunc c_tracefunc;
    PyObject *c_profileobj;
    PyObject *c_traceobj;
    PyObject *curexc_type;
    PyObject *curexc_value;
    PyObject *curexc_traceback;
    _PyErr_StackItem exc_state;
    _PyErr_StackItem *exc_info;
    PyObject *dict;
    int gilstate_counter;
    PyObject *async_exc;
    unsigned long thread_id;
    int trash_delete_nesting;
    PyObject *trash_delete_later;
    void (*on_delete)(void *);
    void *on_delete_data;
    int coroutine_origin_tracking_depth;
    PyObject *async_gen_firstiter;
    PyObject *async_gen_finalizer;
    PyObject *context;
    uint64_t context_ver;
    uint64_t id;
    CFrame root_cframe;
};

struct pyruntimestate;//insertRecordDeclare 

/*TD*/typedef struct pyruntimestate _PyRuntimeState;

struct _Py_atomic_address;//insertRecordDeclare 

/*TD*/typedef struct _Py_atomic_address _Py_atomic_address;


struct _Py_atomic_address {
    atomic_uintptr_t _value;
};

/*TD*/typedef void *PyThread_type_lock;

struct _xidregitem;//insertRecordDeclare 

struct _ceval_runtime_state;//insertRecordDeclare 

struct _Py_atomic_int;//insertRecordDeclare 

/*TD*/typedef struct _Py_atomic_int _Py_atomic_int;


struct _Py_atomic_int {
    atomic_int _value;
};

struct _gil_runtime_state;//insertRecordDeclare 


struct _gil_runtime_state {
    unsigned long interval;
    _Py_atomic_address last_holder;
    _Py_atomic_int locked;
    unsigned long switch_number;
    pthread_cond_t cond;
    pthread_mutex_t mutex;
    pthread_cond_t switch_cond;
    pthread_mutex_t switch_mutex;
};


struct _ceval_runtime_state {
    _Py_atomic_int signals_pending;
    struct _gil_runtime_state gil;
};

struct _gilstate_runtime_state;//insertRecordDeclare 

struct _Py_tss_t;//insertRecordDeclare 

/*TD*/typedef struct _Py_tss_t Py_tss_t;


struct _Py_tss_t {
    int _is_initialized;
    pthread_key_t _key;
};


struct _gilstate_runtime_state {
    int check_enabled;
    _Py_atomic_address tstate_current;
    PyInterpreterState *autoInterpreterState;
    Py_tss_t autoTSSkey;
};

struct PyPreConfig;//insertRecordDeclare 

/*TD*/typedef struct PyPreConfig PyPreConfig;


struct PyPreConfig {
    int _config_init;
    int parse_argv;
    int isolated;
    int use_environment;
    int configure_locale;
    int coerce_c_locale;
    int coerce_c_locale_warn;
    int utf8_mode;
    int dev_mode;
    int allocator;
};

/*TD*/typedef PyObject *(*Py_OpenCodeHookFunction)(PyObject *, void *);

struct _Py_AuditHookEntry;//insertRecordDeclare 

/*TD*/typedef struct _Py_AuditHookEntry _Py_AuditHookEntry;

struct _Py_unicode_runtime_ids;//insertRecordDeclare 


struct _Py_unicode_runtime_ids {
    PyThread_type_lock lock;
    Py_ssize_t next_index;
};


struct pyruntimestate {
    int preinitializing;
    int preinitialized;
    int core_initialized;
    int initialized;
    _Py_atomic_address _finalizing;
    struct pyinterpreters {
        PyThread_type_lock mutex;
        PyInterpreterState *head;
        PyInterpreterState *main;
        int64_t next_id;
    } interpreters;
    struct _xidregistry {
        PyThread_type_lock mutex;
        struct _xidregitem *head;
    } xidregistry;
    unsigned long main_thread;
    void (*exitfuncs[32])(void);
    int nexitfuncs;
    struct _ceval_runtime_state ceval;
    struct _gilstate_runtime_state gilstate;
    PyPreConfig preconfig;
    Py_OpenCodeHookFunction open_code_hook;
    void *open_code_userdata;
    _Py_AuditHookEntry *audit_hook_head;
    struct _Py_unicode_runtime_ids unicode_ids;
};

/*ENUM*/
enum _Py_memory_order {
    _Py_memory_order_relaxed = memory_order_relaxed,
    _Py_memory_order_acquire = memory_order_acquire,
    _Py_memory_order_release = memory_order_release,
    _Py_memory_order_acq_rel = memory_order_acq_rel,
    _Py_memory_order_seq_cst = memory_order_seq_cst
};

struct __va_list_tag;//insertRecordDeclare 


/*Ano*/typedef struct {
    PyVarObject ob_base;
    PyObject *ob_item[1];
} PyTupleObject;

#endif