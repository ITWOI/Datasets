#ifndef __HEADER_FUNC_H__ 
#define __HEADER_FUNC_H__
#include"header_type.h" 
static inline int is_bit_set_in_table(uint32_t *table, int bitindex) ;

static uint32_t _PyOpcode_Jump[8] = {0U, 0U, 536870912U, 101695488U, 67141632U, 0U, 0U, 0U};
;

void *PyObject_Malloc(size_t size);


PyObject *PyErr_NoMemory(void);

static inline void stackdepth_push(basicblock ***sp, basicblock *b, int depth) ;


PyObject *PyErr_Format(PyObject *exception, const char *format, ...);

static inline int is_jump(struct instr *i) ;

static int stack_effect(int opcode, int oparg, int jump) ;

#endif