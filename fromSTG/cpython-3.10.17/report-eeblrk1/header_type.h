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

struct pyruntimestate;//insertRecordDeclare 

/*TD*/typedef struct pyruntimestate _PyRuntimeState;

struct _Py_atomic_address;//insertRecordDeclare 

/*TD*/typedef struct _Py_atomic_address _Py_atomic_address;


struct _Py_atomic_address {
    atomic_uintptr_t _value;
};

/*TD*/typedef void *PyThread_type_lock;

struct _is;//insertRecordDeclare 

/*TD*/typedef struct _is PyInterpreterState;

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

struct _ceval_state;//insertRecordDeclare 

struct _pending_calls;//insertRecordDeclare 


struct _pending_calls {
    PyThread_type_lock lock;
    _Py_atomic_int calls_to_do;
    int async_exc;
    struct {
        int (*func)(void *);
        void *arg;
    } calls[32];
    int first;
    int last;
};


struct _ceval_state {
    int recursion_limit;
    _Py_atomic_int eval_breaker;
    _Py_atomic_int gil_drop_request;
    struct _pending_calls pending;
};

struct _gc_runtime_state;//insertRecordDeclare 

struct gc_generation;//insertRecordDeclare 


/*Ano*/typedef struct {
    uintptr_t _gc_next;
    uintptr_t _gc_prev;
} PyGC_Head;


struct gc_generation {
    PyGC_Head head;
    int threshold;
    int count;
};

struct gc_generation_stats;//insertRecordDeclare 


struct gc_generation_stats {
    Py_ssize_t collections;
    Py_ssize_t collected;
    Py_ssize_t uncollectable;
};


struct _gc_runtime_state {
    PyObject *trash_delete_later;
    int trash_delete_nesting;
    int enabled;
    int debug;
    struct gc_generation generations[3];
    PyGC_Head *generation0;
    struct gc_generation permanent_generation;
    struct gc_generation_stats generation_stats[3];
    int collecting;
    PyObject *garbage;
    PyObject *callbacks;
    Py_ssize_t long_lived_total;
    Py_ssize_t long_lived_pending;
};

struct PyConfig;//insertRecordDeclare 

/*TD*/typedef struct PyConfig PyConfig;


/*Ano*/typedef struct {
    Py_ssize_t length;
    wchar_t **items;
} PyWideStringList;


struct PyConfig {
    int _config_init;
    int isolated;
    int use_environment;
    int dev_mode;
    int install_signal_handlers;
    int use_hash_seed;
    unsigned long hash_seed;
    int faulthandler;
    int tracemalloc;
    int import_time;
    int show_ref_count;
    int dump_refs;
    int malloc_stats;
    wchar_t *filesystem_encoding;
    wchar_t *filesystem_errors;
    wchar_t *pycache_prefix;
    int parse_argv;
    PyWideStringList orig_argv;
    PyWideStringList argv;
    PyWideStringList xoptions;
    PyWideStringList warnoptions;
    int site_import;
    int bytes_warning;
    int warn_default_encoding;
    int inspect;
    int interactive;
    int optimization_level;
    int parser_debug;
    int write_bytecode;
    int verbose;
    int quiet;
    int user_site_directory;
    int configure_c_stdio;
    int buffered_stdio;
    wchar_t *stdio_encoding;
    wchar_t *stdio_errors;
    wchar_t *check_hash_pycs_mode;
    int pathconfig_warnings;
    wchar_t *program_name;
    wchar_t *pythonpath_env;
    wchar_t *home;
    wchar_t *platlibdir;
    int module_search_paths_set;
    PyWideStringList module_search_paths;
    wchar_t *executable;
    wchar_t *base_executable;
    wchar_t *prefix;
    wchar_t *base_prefix;
    wchar_t *exec_prefix;
    wchar_t *base_exec_prefix;
    int skip_source_first_line;
    wchar_t *run_command;
    wchar_t *run_module;
    wchar_t *run_filename;
    int _install_importlib;
    int _init_main;
    int _isolated_interpreter;
};

/*TD*/typedef PyObject *(*_PyFrameEvalFunction)(PyThreadState *, PyFrameObject *, int);

struct _warnings_runtime_state;//insertRecordDeclare 


struct _warnings_runtime_state {
    PyObject *filters;
    PyObject *once_registry;
    PyObject *default_action;
    long filters_version;
};

struct atexit_state;//insertRecordDeclare 


/*Ano*/typedef struct {
    PyObject *func;
    PyObject *args;
    PyObject *kwargs;
} atexit_callback;


struct atexit_state {
    atexit_callback **callbacks;
    int ncallbacks;
    int callback_len;
};

struct _longobject;//insertRecordDeclare 

/*TD*/typedef struct _longobject PyLongObject;

struct _Py_bytes_state;//insertRecordDeclare 


/*Ano*/typedef struct {
    PyVarObject ob_base;
    Py_hash_t ob_shash;
    char ob_sval[1];
} PyBytesObject;


struct _Py_bytes_state {
    PyObject *empty_string;
    PyBytesObject *characters[256];
};

struct _Py_unicode_state;//insertRecordDeclare 

struct _Py_unicode_fs_codec;//insertRecordDeclare 


typedef enum {
    _Py_ERROR_UNKNOWN = 0,
    _Py_ERROR_STRICT,
    _Py_ERROR_SURROGATEESCAPE,
    _Py_ERROR_REPLACE,
    _Py_ERROR_IGNORE,
    _Py_ERROR_BACKSLASHREPLACE,
    _Py_ERROR_SURROGATEPASS,
    _Py_ERROR_XMLCHARREFREPLACE,
    _Py_ERROR_OTHER
} _Py_error_handler;


struct _Py_unicode_fs_codec {
    char *encoding;
    int utf8;
    char *errors;
    _Py_error_handler error_handler;
};

struct _Py_unicode_ids;//insertRecordDeclare 


struct _Py_unicode_ids {
    Py_ssize_t size;
    PyObject **array;
};


struct _Py_unicode_state {
    PyObject *empty_string;
    PyObject *latin1[256];
    struct _Py_unicode_fs_codec fs_codec;
    PyObject *unused_interned;
    struct _Py_unicode_ids ids;
};

struct _Py_float_state;//insertRecordDeclare 


/*Ano*/typedef struct {
    PyObject ob_base;
    double ob_fval;
} PyFloatObject;


struct _Py_float_state {
    int numfree;
    PyFloatObject *free_list;
};


/*Ano*/typedef struct {
    PyObject ob_base;
    PyObject *start;
    PyObject *stop;
    PyObject *step;
} PySliceObject;

struct _Py_tuple_state;//insertRecordDeclare 


/*Ano*/typedef struct {
    PyVarObject ob_base;
    PyObject *ob_item[1];
} PyTupleObject;


struct _Py_tuple_state {
    PyTupleObject *free_list[20];
    int numfree[20];
};

struct _Py_list_state;//insertRecordDeclare 


/*Ano*/typedef struct {
    PyVarObject ob_base;
    PyObject **ob_item;
    Py_ssize_t allocated;
} PyListObject;


struct _Py_list_state {
    PyListObject *free_list[80];
    int numfree;
};

struct _Py_dict_state;//insertRecordDeclare 

struct _dictkeysobject;//insertRecordDeclare 

/*TD*/typedef struct _dictkeysobject PyDictKeysObject;


/*Ano*/typedef struct {
    PyObject ob_base;
    Py_ssize_t ma_used;
    uint64_t ma_version_tag;
    PyDictKeysObject *ma_keys;
    PyObject **ma_values;
} PyDictObject;


struct _Py_dict_state {
    PyDictObject *free_list[80];
    int numfree;
    PyDictKeysObject *keys_free_list[80];
    int keys_numfree;
};

struct _Py_frame_state;//insertRecordDeclare 


struct _Py_frame_state {
    PyFrameObject *free_list;
    int numfree;
};

struct _Py_async_gen_state;//insertRecordDeclare 

struct _PyAsyncGenWrappedValue;//insertRecordDeclare 

struct PyAsyncGenASend;//insertRecordDeclare 


struct _Py_async_gen_state {
    struct _PyAsyncGenWrappedValue *value_freelist[80];
    int value_numfree;
    struct PyAsyncGenASend *asend_freelist[80];
    int asend_numfree;
};

struct _Py_context_state;//insertRecordDeclare 

struct _pycontextobject;//insertRecordDeclare 

/*TD*/typedef struct _pycontextobject PyContext;


struct _Py_context_state {
    PyContext *freelist;
    int numfree;
};

struct _Py_exc_state;//insertRecordDeclare 


/*Ano*/typedef struct {
    PyObject ob_base;
    PyObject *dict;
    PyObject *args;
    PyObject *traceback;
    PyObject *context;
    PyObject *cause;
    char suppress_context;
} PyBaseExceptionObject;


struct _Py_exc_state {
    PyObject *errnomap;
    PyBaseExceptionObject *memerrors_freelist;
    int memerrors_numfree;
};

struct ast_state;//insertRecordDeclare 


struct ast_state {
    int initialized;
    PyObject *AST_type;
    PyObject *Add_singleton;
    PyObject *Add_type;
    PyObject *And_singleton;
    PyObject *And_type;
    PyObject *AnnAssign_type;
    PyObject *Assert_type;
    PyObject *Assign_type;
    PyObject *AsyncFor_type;
    PyObject *AsyncFunctionDef_type;
    PyObject *AsyncWith_type;
    PyObject *Attribute_type;
    PyObject *AugAssign_type;
    PyObject *Await_type;
    PyObject *BinOp_type;
    PyObject *BitAnd_singleton;
    PyObject *BitAnd_type;
    PyObject *BitOr_singleton;
    PyObject *BitOr_type;
    PyObject *BitXor_singleton;
    PyObject *BitXor_type;
    PyObject *BoolOp_type;
    PyObject *Break_type;
    PyObject *Call_type;
    PyObject *ClassDef_type;
    PyObject *Compare_type;
    PyObject *Constant_type;
    PyObject *Continue_type;
    PyObject *Del_singleton;
    PyObject *Del_type;
    PyObject *Delete_type;
    PyObject *DictComp_type;
    PyObject *Dict_type;
    PyObject *Div_singleton;
    PyObject *Div_type;
    PyObject *Eq_singleton;
    PyObject *Eq_type;
    PyObject *ExceptHandler_type;
    PyObject *Expr_type;
    PyObject *Expression_type;
    PyObject *FloorDiv_singleton;
    PyObject *FloorDiv_type;
    PyObject *For_type;
    PyObject *FormattedValue_type;
    PyObject *FunctionDef_type;
    PyObject *FunctionType_type;
    PyObject *GeneratorExp_type;
    PyObject *Global_type;
    PyObject *GtE_singleton;
    PyObject *GtE_type;
    PyObject *Gt_singleton;
    PyObject *Gt_type;
    PyObject *IfExp_type;
    PyObject *If_type;
    PyObject *ImportFrom_type;
    PyObject *Import_type;
    PyObject *In_singleton;
    PyObject *In_type;
    PyObject *Interactive_type;
    PyObject *Invert_singleton;
    PyObject *Invert_type;
    PyObject *IsNot_singleton;
    PyObject *IsNot_type;
    PyObject *Is_singleton;
    PyObject *Is_type;
    PyObject *JoinedStr_type;
    PyObject *LShift_singleton;
    PyObject *LShift_type;
    PyObject *Lambda_type;
    PyObject *ListComp_type;
    PyObject *List_type;
    PyObject *Load_singleton;
    PyObject *Load_type;
    PyObject *LtE_singleton;
    PyObject *LtE_type;
    PyObject *Lt_singleton;
    PyObject *Lt_type;
    PyObject *MatMult_singleton;
    PyObject *MatMult_type;
    PyObject *MatchAs_type;
    PyObject *MatchClass_type;
    PyObject *MatchMapping_type;
    PyObject *MatchOr_type;
    PyObject *MatchSequence_type;
    PyObject *MatchSingleton_type;
    PyObject *MatchStar_type;
    PyObject *MatchValue_type;
    PyObject *Match_type;
    PyObject *Mod_singleton;
    PyObject *Mod_type;
    PyObject *Module_type;
    PyObject *Mult_singleton;
    PyObject *Mult_type;
    PyObject *Name_type;
    PyObject *NamedExpr_type;
    PyObject *Nonlocal_type;
    PyObject *NotEq_singleton;
    PyObject *NotEq_type;
    PyObject *NotIn_singleton;
    PyObject *NotIn_type;
    PyObject *Not_singleton;
    PyObject *Not_type;
    PyObject *Or_singleton;
    PyObject *Or_type;
    PyObject *Pass_type;
    PyObject *Pow_singleton;
    PyObject *Pow_type;
    PyObject *RShift_singleton;
    PyObject *RShift_type;
    PyObject *Raise_type;
    PyObject *Return_type;
    PyObject *SetComp_type;
    PyObject *Set_type;
    PyObject *Slice_type;
    PyObject *Starred_type;
    PyObject *Store_singleton;
    PyObject *Store_type;
    PyObject *Sub_singleton;
    PyObject *Sub_type;
    PyObject *Subscript_type;
    PyObject *Try_type;
    PyObject *Tuple_type;
    PyObject *TypeIgnore_type;
    PyObject *UAdd_singleton;
    PyObject *UAdd_type;
    PyObject *USub_singleton;
    PyObject *USub_type;
    PyObject *UnaryOp_type;
    PyObject *While_type;
    PyObject *With_type;
    PyObject *YieldFrom_type;
    PyObject *Yield_type;
    PyObject *__dict__;
    PyObject *__doc__;
    PyObject *__match_args__;
    PyObject *__module__;
    PyObject *_attributes;
    PyObject *_fields;
    PyObject *alias_type;
    PyObject *annotation;
    PyObject *arg;
    PyObject *arg_type;
    PyObject *args;
    PyObject *argtypes;
    PyObject *arguments_type;
    PyObject *asname;
    PyObject *ast;
    PyObject *attr;
    PyObject *bases;
    PyObject *body;
    PyObject *boolop_type;
    PyObject *cases;
    PyObject *cause;
    PyObject *cls;
    PyObject *cmpop_type;
    PyObject *col_offset;
    PyObject *comparators;
    PyObject *comprehension_type;
    PyObject *context_expr;
    PyObject *conversion;
    PyObject *ctx;
    PyObject *decorator_list;
    PyObject *defaults;
    PyObject *elt;
    PyObject *elts;
    PyObject *end_col_offset;
    PyObject *end_lineno;
    PyObject *exc;
    PyObject *excepthandler_type;
    PyObject *expr_context_type;
    PyObject *expr_type;
    PyObject *finalbody;
    PyObject *format_spec;
    PyObject *func;
    PyObject *generators;
    PyObject *guard;
    PyObject *handlers;
    PyObject *id;
    PyObject *ifs;
    PyObject *is_async;
    PyObject *items;
    PyObject *iter;
    PyObject *key;
    PyObject *keys;
    PyObject *keyword_type;
    PyObject *keywords;
    PyObject *kind;
    PyObject *kw_defaults;
    PyObject *kwarg;
    PyObject *kwd_attrs;
    PyObject *kwd_patterns;
    PyObject *kwonlyargs;
    PyObject *left;
    PyObject *level;
    PyObject *lineno;
    PyObject *lower;
    PyObject *match_case_type;
    PyObject *mod_type;
    PyObject *module;
    PyObject *msg;
    PyObject *name;
    PyObject *names;
    PyObject *op;
    PyObject *operand;
    PyObject *operator_type;
    PyObject *ops;
    PyObject *optional_vars;
    PyObject *orelse;
    PyObject *pattern;
    PyObject *pattern_type;
    PyObject *patterns;
    PyObject *posonlyargs;
    PyObject *rest;
    PyObject *returns;
    PyObject *right;
    PyObject *simple;
    PyObject *slice;
    PyObject *step;
    PyObject *stmt_type;
    PyObject *subject;
    PyObject *tag;
    PyObject *target;
    PyObject *targets;
    PyObject *test;
    PyObject *type;
    PyObject *type_comment;
    PyObject *type_ignore_type;
    PyObject *type_ignores;
    PyObject *unaryop_type;
    PyObject *upper;
    PyObject *value;
    PyObject *values;
    PyObject *vararg;
    PyObject *withitem_type;
};

struct type_cache;//insertRecordDeclare 

struct type_cache_entry;//insertRecordDeclare 


struct type_cache_entry {
    unsigned int version;
    PyObject *name;
    PyObject *value;
};


struct type_cache {
    struct type_cache_entry hashtable[4096];
};


struct _is {
    struct _is *next;
    struct _ts *tstate_head;
    struct pyruntimestate *runtime;
    int64_t id;
    int64_t id_refcount;
    int requires_idref;
    PyThread_type_lock id_mutex;
    int finalizing;
    struct _ceval_state ceval;
    struct _gc_runtime_state gc;
    PyObject *modules;
    PyObject *modules_by_index;
    PyObject *sysdict;
    PyObject *builtins;
    PyObject *importlib;
    long num_threads;
    size_t pythread_stacksize;
    PyObject *codec_search_path;
    PyObject *codec_search_cache;
    PyObject *codec_error_registry;
    int codecs_initialized;
    PyConfig config;
    int dlopenflags;
    PyObject *dict;
    PyObject *builtins_copy;
    PyObject *import_func;
    _PyFrameEvalFunction eval_frame;
    Py_ssize_t co_extra_user_count;
    freefunc co_extra_freefuncs[255];
    PyObject *before_forkers;
    PyObject *after_forkers_parent;
    PyObject *after_forkers_child;
    uint64_t tstate_next_unique_id;
    struct _warnings_runtime_state warnings;
    struct atexit_state atexit;
    PyObject *audit_hooks;
    PyLongObject *small_ints[262];
    struct _Py_bytes_state bytes;
    struct _Py_unicode_state unicode;
    struct _Py_float_state float_state;
    PySliceObject *slice_cache;
    struct _Py_tuple_state tuple;
    struct _Py_list_state list;
    struct _Py_dict_state dict_state;
    struct _Py_frame_state frame;
    struct _Py_async_gen_state async_gen;
    struct _Py_context_state context;
    struct _Py_exc_state exc_state;
    struct ast_state ast;
    struct type_cache type_cache;
    int int_max_str_digits;
};

/*TD*/typedef uint32_t digit;


struct _longobject {
    PyVarObject ob_base;
    digit ob_digit[1];
};

/*TD*/typedef int32_t sdigit;

/*TD*/typedef struct PyMethodDef PyMethodDef;

/*TD*/typedef PyObject *(*PyCFunction)(PyObject *, PyObject *);


struct PyMethodDef {
    const char *ml_name;
    PyCFunction ml_meth;
    int ml_flags;
    const char *ml_doc;
};

/*TD*/typedef struct PyGetSetDef PyGetSetDef;

/*TD*/typedef PyObject *(*getter)(PyObject *, void *);

/*TD*/typedef int (*setter)(PyObject *, PyObject *, void *);


struct PyGetSetDef {
    const char *name;
    getter get;
    setter set;
    const char *doc;
    void *closure;
};

/*TD*/typedef uint64_t twodigits;

/*TD*/typedef int64_t stwodigits;

#endif