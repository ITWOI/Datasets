#ifndef __HEADER_FUNC_H__ 
#define __HEADER_FUNC_H__
#include"header_type.h" 
static void *stack_block(struct stack *s, stack_ptr p) ;

static size_t align_round_up(size_t sz) ;


void *jv_mem_realloc(void *, size_t);

static void stack_reallocate(struct stack *s, size_t sz) ;

static stack_ptr *stack_block_next(struct stack *s, stack_ptr p) ;


jv_kind jv_get_kind(jv);

static stack_ptr frame_get_level(struct jq_state *jq, int level) ;

static stack_ptr stack_push_block(struct stack *s, stack_ptr p, size_t sz) ;

static int frame_size(struct bytecode *bc) ;

static struct closure make_closure(struct jq_state *jq, uint16_t *pc) ;


jv jv_invalid(void);

static struct frame *frame_current(struct jq_state *jq) ;

static int stack_pop_will_free(struct stack *s, stack_ptr p) ;


void jv_free(jv);

static jv *frame_local_var(struct jq_state *jq, int var, int level) ;

static stack_ptr stack_pop_block(struct stack *s, stack_ptr p, size_t sz) ;

static int jv_is_valid(jv x) ;


jv jv_copy(jv);


jv jv_null(void);


int jv_array_length(jv);


int jv_identical(jv, jv);


jv jv_array_append(jv, jv);

jv stack_pop(jq_state *jq) ;

static void frame_pop(struct jq_state *jq) ;


jv jv_array_slice(jv, int, int);

uint16_t *stack_restore(jq_state *jq) ;


void dump_operation(struct bytecode *bc, uint16_t *op);


void jv_dump(jv, int flags);

static void set_error(jq_state *jq, jv value) ;


jv jv_invalid_with_msg(jv);

void stack_push(jq_state *jq, jv val) ;


jv jv_object_set(jv object, jv key, jv value);


jv jv_object(void);


jv jv_string(const char *);


jv jv_number(double);


jv jv_string_fmt(const char *, ...);


const char *jv_kind_name(jv_kind);


char *jv_dump_string_trunc(jv x, char *outbuf, size_t bufsize);


double jv_number_value(jv);

void stack_save(jq_state *jq, uint16_t *retaddr, struct stack_pos sp) ;

jv stack_popn(jq_state *jq) ;

struct stack_pos stack_get_pos(jq_state *jq) ;


int jv_get_refcnt(jv);


jv jv_array(void);

static int path_intact(jq_state *jq, jv curr) ;

static void path_append(jq_state *jq, jv component, jv value_at_path) ;


jv jv_array_get(jv, int);


int jv_object_iter(jv);


int jv_object_iter_next(jv, int);


int jv_object_iter_valid(jv, int);


jv jv_object_iter_key(jv, int);


jv jv_object_iter_value(jv, int);


int jv_invalid_has_msg(jv);


jv jv_invalid_get_msg(jv);

static struct frame *frame_push(struct jq_state *jq, struct closure callee, uint16_t *argdef, int nargs) ;


const struct opcode_description *opcode_describe(opcode op);


jv jv_get(jv, jv);

#endif