#ifndef __HEADER_TYPE_H__ 
#define __HEADER_TYPE_H__
#include"../common.h" 
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

struct inst;//insertRecordDeclare 

/*TD*/typedef struct inst inst;


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

struct cfunction;//insertRecordDeclare 

struct locfile;//insertRecordDeclare 


/*Ano*/typedef struct {
    int start;
    int end;
} location;

struct block;//insertRecordDeclare 

/*TD*/typedef struct block block;


struct block {
    inst *first;
    inst *last;
};

struct bytecode;//insertRecordDeclare 


struct inst {
    struct inst *next;
    struct inst *prev;
    opcode op;
    struct {
        uint16_t intval;
        struct inst *target;
        jv constant;
        const struct cfunction *cfunc;
    } imm;
    struct locfile *locfile;
    location source;
    struct inst *bound_by;
    char *symbol;
    int any_unbound;
    int referenced;
    int nformals;
    int nactuals;
    block subfn;
    block arglist;
    struct bytecode *compiled;
    int bytecode_pos;
};

struct opcode_description;//insertRecordDeclare 


struct opcode_description {
    opcode op;
    const char *name;
    int flags;
    int length;
    int stack_in;
    int stack_out;
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

/*TD*/typedef struct jq_state jq_state;


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


struct symbol_table {
    struct cfunction *cfunctions;
    int ncfunctions;
    jv cfunc_names;
};

/*ANo ENUM*/
enum {
    OP_HAS_CONSTANT = 2,
    OP_HAS_VARIABLE = 4,
    OP_HAS_BRANCH = 8,
    OP_HAS_CFUNC = 32,
    OP_HAS_UFUNC = 64,
    OP_IS_CALL_PSEUDO = 128,
    OP_HAS_BINDING = 1024,
    OP_BIND_WILDCARD = 2048
};

#endif