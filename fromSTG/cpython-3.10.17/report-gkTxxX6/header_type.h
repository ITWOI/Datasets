#ifndef __HEADER_TYPE_H__ 
#define __HEADER_TYPE_H__
#include"../common.h" 
struct instr;//insertRecordDeclare 

struct basicblock_;//insertRecordDeclare 


struct instr {
    unsigned char i_opcode;
    int i_oparg;
    struct basicblock_ *i_target;
    int i_lineno;
};

/*TD*/typedef struct basicblock_ basicblock;


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

struct compiler;//insertRecordDeclare 

struct _object;//insertRecordDeclare 

/*TD*/typedef struct _object PyObject;

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

struct _symtable_entry;//insertRecordDeclare 

/*TD*/typedef struct _symtable_entry PySTEntryObject;

/*TD*/typedef ssize_t Py_ssize_t;

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

struct _typeobject;//insertRecordDeclare 

/*TD*/typedef struct _typeobject PyTypeObject;


struct _object {
    Py_ssize_t ob_refcnt;
    PyTypeObject *ob_type;
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

#endif