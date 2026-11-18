#ifndef __HEADER_FUNC_H__ 
#define __HEADER_FUNC_H__
#include"header_type.h" 

jv_kind jv_get_kind(jv);


void *jv_mem_alloc(size_t);

block gen_noop(void);


const struct opcode_description *opcode_describe(opcode op);

static block inst_block(inst *i) ;

static inst *inst_new(opcode op) ;

int block_is_single(block b) ;

int block_is_const(block b) ;


jv jv_copy(jv);

block gen_op_unbound(opcode op, const char *name) ;

static void inst_join(inst *a, inst *b) ;

void block_append(block *b, block b2) ;

int block_is_noop(block b) ;

block gen_op_simple(opcode op) ;

void block_free(block);

block gen_op_pushk_under(jv constant) ;

jv block_const(block b) ;

block block_join(block a, block b) ;

static int jv_is_valid(jv x) ;


jv jv_object(void);

extern char **environ;
;

jv jv_object_delete(jv object, jv key);


jv jv_string(const char *);


jv jv_object_set(jv object, jv key, jv value);


jv jv_string_sized(const char *, int);

static inst *block_take(block *b) ;

static jv make_env(jv env) ;


int jv_object_has(jv object, jv key);


jv jv_object_get(jv object, jv key);


void locfile_locate(struct locfile *, location, const char *, ...);

block gen_op_bound(opcode op, block binder) ;

static void inst_free(struct inst *i) ;

static int expand_call_arglist(block *b, jv args, jv *env) ;

block gen_subexp(block a) ;


jv jv_array(void);


jv jv_array_append(jv, jv);


void *jv_mem_calloc(size_t, size_t);

static int compile(struct bytecode *bc, block b, struct locfile *lf, jv args, jv *env) ;

static uint16_t nesting_level(struct bytecode *bc, inst *target) ;


int jv_array_length(jv);

#endif