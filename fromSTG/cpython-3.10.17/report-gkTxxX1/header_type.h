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

/*TD*/typedef uint16_t _Py_CODEUNIT;

struct instr;//insertRecordDeclare 

struct basicblock_;//insertRecordDeclare 


struct instr {
    unsigned char i_opcode;
    int i_oparg;
    struct basicblock_ *i_target;
    int i_lineno;
};

struct compiler;//insertRecordDeclare 

/*TD*/typedef PyObject *identifier;

/*TD*/typedef struct basicblock_ basicblock;

/*ENUM*/
enum _expr_context {
    Load = 1,
    Store = 2,
    Del = 3
};

/*TD*/typedef enum _expr_context expr_context_ty;

struct PyCodeObject;//insertRecordDeclare 

/*TD*/typedef struct PyCodeObject PyCodeObject;

struct _mod;//insertRecordDeclare 

/*TD*/typedef struct _mod *mod_ty;

struct _stmt;//insertRecordDeclare 

/*TD*/typedef struct _stmt *stmt_ty;

struct _keyword;//insertRecordDeclare 

/*TD*/typedef struct _keyword *keyword_ty;

struct _expr;//insertRecordDeclare 

/*TD*/typedef struct _expr *expr_ty;

/*ENUM*/
enum _operator {
    Add = 1,
    Sub = 2,
    Mult = 3,
    MatMult = 4,
    Div = 5,
    Mod = 6,
    Pow = 7,
    LShift = 8,
    RShift = 9,
    BitOr = 10,
    BitXor = 11,
    BitAnd = 12,
    FloorDiv = 13
};

/*TD*/typedef enum _operator operator_ty;


/*Ano*/typedef struct {
    Py_ssize_t size;
    void **elements;
    expr_ty typed_elements[1];
} asdl_expr_seq;


/*Ano*/typedef struct {
    Py_ssize_t size;
    void **elements;
    keyword_ty typed_elements[1];
} asdl_keyword_seq;

struct _comprehension;//insertRecordDeclare 

/*TD*/typedef struct _comprehension *comprehension_ty;


/*Ano*/typedef struct {
    Py_ssize_t size;
    void **elements;
    comprehension_ty typed_elements[1];
} asdl_comprehension_seq;

struct _pattern;//insertRecordDeclare 

/*TD*/typedef struct _pattern *pattern_ty;


/*Ano*/typedef struct {
    PyObject *stores;
    int allow_irrefutable;
    basicblock **fail_pop;
    Py_ssize_t fail_pop_size;
    Py_ssize_t on_top;
} pattern_context;

/*TD*/typedef uint32_t Py_UCS4;


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

/*ENUM*/
enum PyUnicode_Kind {
    PyUnicode_WCHAR_KIND = 0,
    PyUnicode_1BYTE_KIND = 1,
    PyUnicode_2BYTE_KIND = 2,
    PyUnicode_4BYTE_KIND = 4
};

/*TD*/typedef uint8_t Py_UCS1;


/*Ano*/typedef struct {
    PyASCIIObject _base;
    Py_ssize_t utf8_length;
    char *utf8;
    Py_ssize_t wstr_length;
} PyCompactUnicodeObject;

/*TD*/typedef uint16_t Py_UCS2;


/*Ano*/typedef struct {
    PyCompactUnicodeObject _base;
    union {
        void *any;
        Py_UCS1 *latin1;
        Py_UCS2 *ucs2;
        Py_UCS4 *ucs4;
    } data;
} PyUnicodeObject;

struct symtable;//insertRecordDeclare 


/*Ano*/typedef struct {
    int ff_features;
    int ff_lineno;
} PyFutureFeatures;


/*Ano*/typedef struct {
    int cf_flags;
    int cf_feature_version;
} PyCompilerFlags;

struct compiler_unit;//insertRecordDeclare 

struct _arena;//insertRecordDeclare 

/*TD*/typedef struct _arena PyArena;


struct compiler {
    PyObject *c_filename;
    struct symtable *c_st;
    PyFutureFeatures *c_future;
    PyCompilerFlags *c_flags;
    int c_optimize;
    int c_interactive;
    int c_nestlevel;
    PyObject *c_const_cache;
    struct compiler_unit *u;
    PyObject *c_stack;
    PyArena *c_arena;
};

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


/*Ano*/typedef struct {
    int optimize;
    int ff_features;
    int recursion_depth;
    int recursion_limit;
} _PyASTOptimizeState;


struct basicblock_ {
    struct basicblock_ *b_list;
    int b_iused;
    int b_ialloc;
    struct instr *b_instr;
    struct basicblock_ *b_next;
    unsigned int b_return : 1;
    int b_predecessors;
    unsigned int b_nofallthrough : 1;
    unsigned int b_exit : 1;
    unsigned int b_visited : 1;
    int b_startdepth;
    int b_offset;
};

struct _symtable_entry;//insertRecordDeclare 

/*TD*/typedef struct _symtable_entry PySTEntryObject;

struct fblockinfo;//insertRecordDeclare 

/*ENUM*/
enum fblocktype {
    WHILE_LOOP,
    FOR_LOOP,
    TRY_EXCEPT,
    FINALLY_TRY,
    FINALLY_END,
    WITH,
    ASYNC_WITH,
    HANDLER_CLEANUP,
    POP_VALUE,
    EXCEPTION_HANDLER,
    ASYNC_COMPREHENSION_GENERATOR
};


struct fblockinfo {
    enum fblocktype fb_type;
    basicblock *fb_block;
    basicblock *fb_exit;
    void *fb_datum;
};


struct compiler_unit {
    PySTEntryObject *u_ste;
    PyObject *u_name;
    PyObject *u_qualname;
    int u_scope_type;
    PyObject *u_consts;
    PyObject *u_names;
    PyObject *u_varnames;
    PyObject *u_cellvars;
    PyObject *u_freevars;
    PyObject *u_private;
    Py_ssize_t u_argcount;
    Py_ssize_t u_posonlyargcount;
    Py_ssize_t u_kwonlyargcount;
    basicblock *u_blocks;
    basicblock *u_curblock;
    int u_nfblocks;
    struct fblockinfo u_fblock[20];
    int u_firstlineno;
    int u_lineno;
    int u_col_offset;
    int u_end_lineno;
    int u_end_col_offset;
};

/*ENUM*/
enum _block_type {
    FunctionBlock,
    ClassBlock,
    ModuleBlock,
    AnnotationBlock
};

/*TD*/typedef enum _block_type _Py_block_ty;

/*ENUM*/
enum _comprehension_type {
    NoComprehension = 0,
    ListComprehension = 1,
    DictComprehension = 2,
    SetComprehension = 3,
    GeneratorExpression = 4
};

/*TD*/typedef enum _comprehension_type _Py_comprehension_ty;


struct _symtable_entry {
    PyObject ob_base;
    PyObject *ste_id;
    PyObject *ste_symbols;
    PyObject *ste_name;
    PyObject *ste_varnames;
    PyObject *ste_children;
    PyObject *ste_directives;
    _Py_block_ty ste_type;
    int ste_nested;
    unsigned int ste_free : 1;
    unsigned int ste_child_free : 1;
    unsigned int ste_generator : 1;
    unsigned int ste_coroutine : 1;
    _Py_comprehension_ty ste_comprehension;
    unsigned int ste_varargs : 1;
    unsigned int ste_varkeywords : 1;
    unsigned int ste_returns_value : 1;
    unsigned int ste_needs_class_closure : 1;
    unsigned int ste_comp_iter_target : 1;
    int ste_comp_iter_expr;
    int ste_lineno;
    int ste_col_offset;
    int ste_end_lineno;
    int ste_end_col_offset;
    int ste_opt_lineno;
    int ste_opt_col_offset;
    struct symtable *ste_table;
};

struct _Py_Identifier;//insertRecordDeclare 

/*TD*/typedef struct _Py_Identifier _Py_Identifier;


struct _Py_Identifier {
    const char *string;
    Py_ssize_t index;
};

/*TD*/typedef void (*PyCapsule_Destructor)(PyObject *);


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


/*Ano*/typedef struct {
    Py_ssize_t size;
    void **elements;
    stmt_ty typed_elements[1];
} asdl_stmt_seq;

/*ENUM*/
enum _stmt_kind {
    FunctionDef_kind = 1,
    AsyncFunctionDef_kind = 2,
    ClassDef_kind = 3,
    Return_kind = 4,
    Delete_kind = 5,
    Assign_kind = 6,
    AugAssign_kind = 7,
    AnnAssign_kind = 8,
    For_kind = 9,
    AsyncFor_kind = 10,
    While_kind = 11,
    If_kind = 12,
    With_kind = 13,
    AsyncWith_kind = 14,
    Match_kind = 15,
    Raise_kind = 16,
    Try_kind = 17,
    Assert_kind = 18,
    Import_kind = 19,
    ImportFrom_kind = 20,
    Global_kind = 21,
    Nonlocal_kind = 22,
    Expr_kind = 23,
    Pass_kind = 24,
    Break_kind = 25,
    Continue_kind = 26
};

struct _arguments;//insertRecordDeclare 

/*TD*/typedef struct _arguments *arguments_ty;

/*TD*/typedef PyObject *string;

struct _withitem;//insertRecordDeclare 

/*TD*/typedef struct _withitem *withitem_ty;


/*Ano*/typedef struct {
    Py_ssize_t size;
    void **elements;
    withitem_ty typed_elements[1];
} asdl_withitem_seq;

struct _match_case;//insertRecordDeclare 

/*TD*/typedef struct _match_case *match_case_ty;


/*Ano*/typedef struct {
    Py_ssize_t size;
    void **elements;
    match_case_ty typed_elements[1];
} asdl_match_case_seq;

struct _excepthandler;//insertRecordDeclare 

/*TD*/typedef struct _excepthandler *excepthandler_ty;


/*Ano*/typedef struct {
    Py_ssize_t size;
    void **elements;
    excepthandler_ty typed_elements[1];
} asdl_excepthandler_seq;

struct _alias;//insertRecordDeclare 

/*TD*/typedef struct _alias *alias_ty;


/*Ano*/typedef struct {
    Py_ssize_t size;
    void **elements;
    alias_ty typed_elements[1];
} asdl_alias_seq;


/*Ano*/typedef struct {
    Py_ssize_t size;
    void **elements;
    PyObject *typed_elements[1];
} asdl_identifier_seq;


struct _stmt {
    enum _stmt_kind kind;
    union {
        struct {
            identifier name;
            arguments_ty args;
            asdl_stmt_seq *body;
            asdl_expr_seq *decorator_list;
            expr_ty returns;
            string type_comment;
        } FunctionDef;
        struct {
            identifier name;
            arguments_ty args;
            asdl_stmt_seq *body;
            asdl_expr_seq *decorator_list;
            expr_ty returns;
            string type_comment;
        } AsyncFunctionDef;
        struct {
            identifier name;
            asdl_expr_seq *bases;
            asdl_keyword_seq *keywords;
            asdl_stmt_seq *body;
            asdl_expr_seq *decorator_list;
        } ClassDef;
        struct {
            expr_ty value;
        } Return;
        struct {
            asdl_expr_seq *targets;
        } Delete;
        struct {
            asdl_expr_seq *targets;
            expr_ty value;
            string type_comment;
        } Assign;
        struct {
            expr_ty target;
            operator_ty op;
            expr_ty value;
        } AugAssign;
        struct {
            expr_ty target;
            expr_ty annotation;
            expr_ty value;
            int simple;
        } AnnAssign;
        struct {
            expr_ty target;
            expr_ty iter;
            asdl_stmt_seq *body;
            asdl_stmt_seq *orelse;
            string type_comment;
        } For;
        struct {
            expr_ty target;
            expr_ty iter;
            asdl_stmt_seq *body;
            asdl_stmt_seq *orelse;
            string type_comment;
        } AsyncFor;
        struct {
            expr_ty test;
            asdl_stmt_seq *body;
            asdl_stmt_seq *orelse;
        } While;
        struct {
            expr_ty test;
            asdl_stmt_seq *body;
            asdl_stmt_seq *orelse;
        } If;
        struct {
            asdl_withitem_seq *items;
            asdl_stmt_seq *body;
            string type_comment;
        } With;
        struct {
            asdl_withitem_seq *items;
            asdl_stmt_seq *body;
            string type_comment;
        } AsyncWith;
        struct {
            expr_ty subject;
            asdl_match_case_seq *cases;
        } Match;
        struct {
            expr_ty exc;
            expr_ty cause;
        } Raise;
        struct {
            asdl_stmt_seq *body;
            asdl_excepthandler_seq *handlers;
            asdl_stmt_seq *orelse;
            asdl_stmt_seq *finalbody;
        } Try;
        struct {
            expr_ty test;
            expr_ty msg;
        } Assert;
        struct {
            asdl_alias_seq *names;
        } Import;
        struct {
            identifier module;
            asdl_alias_seq *names;
            int level;
        } ImportFrom;
        struct {
            asdl_identifier_seq *names;
        } Global;
        struct {
            asdl_identifier_seq *names;
        } Nonlocal;
        struct {
            expr_ty value;
        } Expr;
    } v;
    int lineno;
    int col_offset;
    int end_lineno;
    int end_col_offset;
};

/*ENUM*/
enum _excepthandler_kind {
    ExceptHandler_kind = 1
};


struct _excepthandler {
    enum _excepthandler_kind kind;
    union {
        struct {
            expr_ty type;
            identifier name;
            asdl_stmt_seq *body;
        } ExceptHandler;
    } v;
    int lineno;
    int col_offset;
    int end_lineno;
    int end_col_offset;
};

/*ENUM*/
enum _mod_kind {
    Module_kind = 1,
    Interactive_kind = 2,
    Expression_kind = 3,
    FunctionType_kind = 4
};

struct _type_ignore;//insertRecordDeclare 

/*TD*/typedef struct _type_ignore *type_ignore_ty;


/*Ano*/typedef struct {
    Py_ssize_t size;
    void **elements;
    type_ignore_ty typed_elements[1];
} asdl_type_ignore_seq;


struct _mod {
    enum _mod_kind kind;
    union {
        struct {
            asdl_stmt_seq *body;
            asdl_type_ignore_seq *type_ignores;
        } Module;
        struct {
            asdl_stmt_seq *body;
        } Interactive;
        struct {
            expr_ty body;
        } Expression;
        struct {
            asdl_expr_seq *argtypes;
            expr_ty returns;
        } FunctionType;
    } v;
};

struct _arg;//insertRecordDeclare 

/*TD*/typedef struct _arg *arg_ty;


/*Ano*/typedef struct {
    Py_ssize_t size;
    void **elements;
    arg_ty typed_elements[1];
} asdl_arg_seq;


struct _arg {
    identifier arg;
    expr_ty annotation;
    string type_comment;
    int lineno;
    int col_offset;
    int end_lineno;
    int end_col_offset;
};


struct _arguments {
    asdl_arg_seq *posonlyargs;
    asdl_arg_seq *args;
    arg_ty vararg;
    asdl_arg_seq *kwonlyargs;
    asdl_expr_seq *kw_defaults;
    arg_ty kwarg;
    asdl_expr_seq *defaults;
};

/*ENUM*/
enum _expr_kind {
    BoolOp_kind = 1,
    NamedExpr_kind = 2,
    BinOp_kind = 3,
    UnaryOp_kind = 4,
    Lambda_kind = 5,
    IfExp_kind = 6,
    Dict_kind = 7,
    Set_kind = 8,
    ListComp_kind = 9,
    SetComp_kind = 10,
    DictComp_kind = 11,
    GeneratorExp_kind = 12,
    Await_kind = 13,
    Yield_kind = 14,
    YieldFrom_kind = 15,
    Compare_kind = 16,
    Call_kind = 17,
    FormattedValue_kind = 18,
    JoinedStr_kind = 19,
    Constant_kind = 20,
    Attribute_kind = 21,
    Subscript_kind = 22,
    Starred_kind = 23,
    Name_kind = 24,
    List_kind = 25,
    Tuple_kind = 26,
    Slice_kind = 27
};

/*ENUM*/
enum _boolop {
    And = 1,
    Or = 2
};

/*TD*/typedef enum _boolop boolop_ty;

/*ENUM*/
enum _unaryop {
    Invert = 1,
    Not = 2,
    UAdd = 3,
    USub = 4
};

/*TD*/typedef enum _unaryop unaryop_ty;


/*Ano*/typedef struct {
    Py_ssize_t size;
    void **elements;
    int typed_elements[1];
} asdl_int_seq;

/*TD*/typedef PyObject *constant;


struct _expr {
    enum _expr_kind kind;
    union {
        struct {
            boolop_ty op;
            asdl_expr_seq *values;
        } BoolOp;
        struct {
            expr_ty target;
            expr_ty value;
        } NamedExpr;
        struct {
            expr_ty left;
            operator_ty op;
            expr_ty right;
        } BinOp;
        struct {
            unaryop_ty op;
            expr_ty operand;
        } UnaryOp;
        struct {
            arguments_ty args;
            expr_ty body;
        } Lambda;
        struct {
            expr_ty test;
            expr_ty body;
            expr_ty orelse;
        } IfExp;
        struct {
            asdl_expr_seq *keys;
            asdl_expr_seq *values;
        } Dict;
        struct {
            asdl_expr_seq *elts;
        } Set;
        struct {
            expr_ty elt;
            asdl_comprehension_seq *generators;
        } ListComp;
        struct {
            expr_ty elt;
            asdl_comprehension_seq *generators;
        } SetComp;
        struct {
            expr_ty key;
            expr_ty value;
            asdl_comprehension_seq *generators;
        } DictComp;
        struct {
            expr_ty elt;
            asdl_comprehension_seq *generators;
        } GeneratorExp;
        struct {
            expr_ty value;
        } Await;
        struct {
            expr_ty value;
        } Yield;
        struct {
            expr_ty value;
        } YieldFrom;
        struct {
            expr_ty left;
            asdl_int_seq *ops;
            asdl_expr_seq *comparators;
        } Compare;
        struct {
            expr_ty func;
            asdl_expr_seq *args;
            asdl_keyword_seq *keywords;
        } Call;
        struct {
            expr_ty value;
            int conversion;
            expr_ty format_spec;
        } FormattedValue;
        struct {
            asdl_expr_seq *values;
        } JoinedStr;
        struct {
            constant value;
            string kind;
        } Constant;
        struct {
            expr_ty value;
            identifier attr;
            expr_context_ty ctx;
        } Attribute;
        struct {
            expr_ty value;
            expr_ty slice;
            expr_context_ty ctx;
        } Subscript;
        struct {
            expr_ty value;
            expr_context_ty ctx;
        } Starred;
        struct {
            identifier id;
            expr_context_ty ctx;
        } Name;
        struct {
            asdl_expr_seq *elts;
            expr_context_ty ctx;
        } List;
        struct {
            asdl_expr_seq *elts;
            expr_context_ty ctx;
        } Tuple;
        struct {
            expr_ty lower;
            expr_ty upper;
            expr_ty step;
        } Slice;
    } v;
    int lineno;
    int col_offset;
    int end_lineno;
    int end_col_offset;
};

/*ENUM*/
enum _cmpop {
    Eq = 1,
    NotEq = 2,
    Lt = 3,
    LtE = 4,
    Gt = 5,
    GtE = 6,
    Is = 7,
    IsNot = 8,
    In = 9,
    NotIn = 10
};

/*TD*/typedef enum _cmpop cmpop_ty;


struct _alias {
    identifier name;
    identifier asname;
    int lineno;
    int col_offset;
    int end_lineno;
    int end_col_offset;
};


struct _keyword {
    identifier arg;
    expr_ty value;
    int lineno;
    int col_offset;
    int end_lineno;
    int end_col_offset;
};


struct _comprehension {
    expr_ty target;
    expr_ty iter;
    asdl_expr_seq *ifs;
    int is_async;
};


struct _withitem {
    expr_ty context_expr;
    expr_ty optional_vars;
};

struct __va_list_tag;//insertRecordDeclare 


/*Ano*/typedef struct {
    Py_ssize_t size;
    void **elements;
    pattern_ty typed_elements[1];
} asdl_pattern_seq;

/*ENUM*/
enum _pattern_kind {
    MatchValue_kind = 1,
    MatchSingleton_kind = 2,
    MatchSequence_kind = 3,
    MatchMapping_kind = 4,
    MatchClass_kind = 5,
    MatchStar_kind = 6,
    MatchAs_kind = 7,
    MatchOr_kind = 8
};


struct _pattern {
    enum _pattern_kind kind;
    union {
        struct {
            expr_ty value;
        } MatchValue;
        struct {
            constant value;
        } MatchSingleton;
        struct {
            asdl_pattern_seq *patterns;
        } MatchSequence;
        struct {
            asdl_expr_seq *keys;
            asdl_pattern_seq *patterns;
            identifier rest;
        } MatchMapping;
        struct {
            expr_ty cls;
            asdl_pattern_seq *patterns;
            asdl_identifier_seq *kwd_attrs;
            asdl_pattern_seq *kwd_patterns;
        } MatchClass;
        struct {
            identifier name;
        } MatchStar;
        struct {
            pattern_ty pattern;
            identifier name;
        } MatchAs;
        struct {
            asdl_pattern_seq *patterns;
        } MatchOr;
    } v;
    int lineno;
    int col_offset;
    int end_lineno;
    int end_col_offset;
};


struct _match_case {
    pattern_ty pattern;
    expr_ty guard;
    asdl_stmt_seq *body;
};

struct assembler;//insertRecordDeclare 


struct assembler {
    PyObject *a_bytecode;
    int a_offset;
    int a_nblocks;
    PyObject *a_lnotab;
    int a_lnotab_off;
    int a_prevlineno;
    int a_lineno;
    int a_lineno_start;
    basicblock *a_entry;
};

/*ANo ENUM*/
enum {
    OP_FAST,
    OP_GLOBAL,
    OP_DEREF,
    OP_NAME
};

/*ANo ENUM*/
enum {
    COMPILER_SCOPE_MODULE,
    COMPILER_SCOPE_CLASS,
    COMPILER_SCOPE_FUNCTION,
    COMPILER_SCOPE_ASYNC_FUNCTION,
    COMPILER_SCOPE_LAMBDA,
    COMPILER_SCOPE_COMPREHENSION
};

#endif