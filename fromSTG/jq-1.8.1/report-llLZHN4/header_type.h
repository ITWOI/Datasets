#ifndef __HEADER_TYPE_H__ 
#define __HEADER_TYPE_H__
#include"../common.h" 
struct determine_alignment;//insertRecordDeclare 


struct determine_alignment {
    char x;
    union {
        int i;
        double d;
        uint64_t u64;
        size_t sz;
        void *ptr;
    } u;
};

struct stack;//insertRecordDeclare 

/*TD*/typedef int stack_ptr;


struct stack {
    char *mem_end;
    stack_ptr bound;
    stack_ptr limit;
};

struct jv_refcnt;//insertRecordDeclare 


/*Ano*/typedef struct {
    unsigned char kind_flags;
    unsigned char pad_;
    unsigned short offset;
    int size;
    union {
        struct jv_refcnt *ptr;
        double number;
    } u;
} jv;


typedef enum {
    JV_KIND_INVALID,
    JV_KIND_NULL,
    JV_KIND_FALSE,
    JV_KIND_TRUE,
    JV_KIND_NUMBER,
    JV_KIND_STRING,
    JV_KIND_ARRAY,
    JV_KIND_OBJECT
} jv_kind;

struct bytecode;//insertRecordDeclare 

struct frame;//insertRecordDeclare 

union frame_entry;//insertRecordDeclare 

struct closure;//insertRecordDeclare 


struct closure {
    struct bytecode *bc;
    stack_ptr env;
};


union frame_entry {
    struct closure closure;
    jv localvar;
};


struct frame {
    struct bytecode *bc;
    stack_ptr env;
    stack_ptr retdata;
    uint16_t *retaddr;
    union frame_entry entries[];
};

struct symbol_table;//insertRecordDeclare 


struct bytecode {
    uint16_t *code;
    int codelen;
    int nlocals;
    int nclosures;
    jv constants;
    struct symbol_table *globals;
    struct bytecode **subfunctions;
    int nsubfunctions;
    struct bytecode *parent;
    jv debuginfo;
};

struct jq_state;//insertRecordDeclare 

/*TD*/typedef void (*jq_msg_cb)(void *, jv);

/*TD*/typedef struct jq_state jq_state;

/*TD*/typedef jv (*jq_input_cb)(jq_state *, void *);


struct jq_state {
    void (*nomem_handler)(void *);
    void *nomem_handler_data;
    struct bytecode *bc;
    jq_msg_cb err_cb;
    void *err_cb_data;
    jv error;
    struct stack stk;
    stack_ptr curr_frame;
    stack_ptr stk_top;
    stack_ptr fork_top;
    jv path;
    jv value_at_path;
    int subexp_nest;
    int debug_trace_enabled;
    int initial_execution;
    unsigned int next_label;
    int halted;
    jv exit_code;
    jv error_message;
    jv attrs;
    jq_input_cb input_cb;
    void *input_cb_data;
    jq_msg_cb debug_cb;
    void *debug_cb_data;
    jq_msg_cb stderr_cb;
    void *stderr_cb_data;
};

struct stack_pos;//insertRecordDeclare 


struct stack_pos {
    stack_ptr saved_data_stack;
    stack_ptr saved_curr_frame;
};

struct forkpoint;//insertRecordDeclare 


struct forkpoint {
    stack_ptr saved_data_stack;
    stack_ptr saved_curr_frame;
    int path_len;
    int subexp_nest;
    jv value_at_path;
    uint16_t *return_address;
};

struct opcode_description;//insertRecordDeclare 

/*ENUM*/
enum jv_print_flags {
    JV_PRINT_PRETTY = 1,
    JV_PRINT_ASCII = 2,
    JV_PRINT_COLOR = 4,
    JV_PRINT_COLOUR = 4,
    JV_PRINT_SORTED = 8,
    JV_PRINT_INVALID = 16,
    JV_PRINT_REFCOUNT = 32,
    JV_PRINT_TAB = 64,
    JV_PRINT_ISATTY = 128,
    JV_PRINT_SPACE0 = 256,
    JV_PRINT_SPACE1 = 512,
    JV_PRINT_SPACE2 = 1024
};

struct cfunction;//insertRecordDeclare 


struct cfunction {
    union {
        jv (*a1)(jq_state *, jv);
        jv (*a2)(jq_state *, jv, jv);
        jv (*a3)(jq_state *, jv, jv, jv);
        jv (*a4)(jq_state *, jv, jv, jv, jv);
    } fptr;
    const char *name;
    int nargs;
};


typedef enum {
    LOADK,
    DUP,
    DUPN,
    DUP2,
    PUSHK_UNDER,
    POP,
    LOADV,
    LOADVN,
    STOREV,
    STORE_GLOBAL,
    INDEX,
    INDEX_OPT,
    EACH,
    EACH_OPT,
    FORK,
    TRY_BEGIN,
    TRY_END,
    JUMP,
    JUMP_F,
    BACKTRACK,
    APPEND,
    INSERT,
    RANGE,
    SUBEXP_BEGIN,
    SUBEXP_END,
    PATH_BEGIN,
    PATH_END,
    CALL_BUILTIN,
    CALL_JQ,
    RET,
    TAIL_CALL_JQ,
    CLOSURE_PARAM,
    CLOSURE_REF,
    CLOSURE_CREATE,
    CLOSURE_CREATE_C,
    TOP,
    CLOSURE_PARAM_REGULAR,
    DEPS,
    MODULEMETA,
    GENLABEL,
    DESTRUCTURE_ALT,
    STOREVN,
    ERRORK
} opcode;


struct opcode_description {
    opcode op;
    const char *name;
    int flags;
    int length;
    int stack_in;
    int stack_out;
};


struct symbol_table {
    struct cfunction *cfunctions;
    int ncfunctions;
    jv cfunc_names;
};

/*ANo ENUM*/
enum {
    NUM_OPCODES = +1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1
};

/*ANo ENUM*/
enum {
    JQ_DEBUG_TRACE = 1,
    JQ_DEBUG_TRACE_DETAIL = 2,
    JQ_DEBUG_TRACE_ALL = JQ_DEBUG_TRACE | JQ_DEBUG_TRACE_DETAIL
};

/*ANo ENUM*/
enum {
    ALIGNMENT = __builtin_offsetof(struct determine_alignment, u)
};

#endif