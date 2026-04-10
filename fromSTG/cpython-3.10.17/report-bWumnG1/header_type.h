#ifndef __HEADER_TYPE_H__ 
#define __HEADER_TYPE_H__
#include"../common.h" 
/*TD*/typedef ssize_t Py_ssize_t;


/*Ano*/typedef struct {
    Py_ssize_t length;
    wchar_t **items;
} PyWideStringList;


/*Ano*/typedef struct {
    enum {
        _PyStatus_TYPE_OK = 0,
        _PyStatus_TYPE_ERROR = 1,
        _PyStatus_TYPE_EXIT = 2
    } _type;
    const char *func;
    const char *err_msg;
    int exitcode;
} PyStatus;

struct PyConfig;//insertRecordDeclare 

/*TD*/typedef struct PyConfig PyConfig;

struct _PyArgv;//insertRecordDeclare 


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

struct _PyPathConfig;//insertRecordDeclare 

/*TD*/typedef struct _PyPathConfig _PyPathConfig;


struct _PyPathConfig {
    wchar_t *program_full_path;
    wchar_t *prefix;
    wchar_t *exec_prefix;
    wchar_t *module_search_path;
    wchar_t *program_name;
    wchar_t *home;
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

struct _object;//insertRecordDeclare 

/*TD*/typedef struct _object PyObject;

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

struct _IO_FILE;//insertRecordDeclare 


/*Ano*/typedef struct {
    PyWideStringList argv;
    PyWideStringList xoptions;
    int isolated;
    int use_environment;
    int dev_mode;
    int warn_default_encoding;
} _PyPreCmdline;

/*ANo ENUM*/
enum {
    _PyConfig_INIT_COMPAT = 1,
    _PyConfig_INIT_PYTHON = 2,
    _PyConfig_INIT_ISOLATED = 3
};

#endif