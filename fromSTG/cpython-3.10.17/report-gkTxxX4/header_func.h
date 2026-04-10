#ifndef __HEADER_FUNC_H__ 
#define __HEADER_FUNC_H__
#include"header_type.h" 
static inline int _Py_IS_TYPE(const PyObject *ob, const PyTypeObject *type) ;


int PyType_IsSubtype(PyTypeObject *, PyTypeObject *);


void _Py_Dealloc(PyObject *);

static inline void _Py_INCREF(PyObject *op) ;

static inline void _Py_DECREF(PyObject *op) ;

static inline PyThreadState *_PyRuntimeState_GetThreadState(_PyRuntimeState *runtime) ;

extern _PyRuntimeState _PyRuntime;
;
static inline PyThreadState *_PyThreadState_GET(void) ;

static inline PyInterpreterState *_PyInterpreterState_GET(void) ;

static inline PyObject *__PyLong_GetSmallInt_internal(int value) ;

static inline int is_bit_set_in_table(uint32_t *table, int bitindex) ;

static uint32_t _PyOpcode_RelativeJump[8] = {0U, 0U, 536870912U, 67125248U, 67141632U, 0U, 0U, 0U};
;
static uint32_t _PyOpcode_Jump[8] = {0U, 0U, 536870912U, 101695488U, 67141632U, 0U, 0U, 0U};
;
static inline int PyType_HasFeature(PyTypeObject *type, unsigned long feature) ;


Py_ssize_t PyUnicode_FindChar(PyObject *str, Py_UCS4 ch, Py_ssize_t start, Py_ssize_t end, int direction);


void PyErr_SetString(PyObject *exception, const char *string);


PyObject *PyUnicode_New(Py_ssize_t size, Py_UCS4 maxchar);


Py_ssize_t PyUnicode_CopyCharacters(PyObject *to, Py_ssize_t to_start, PyObject *from, Py_ssize_t from_start, Py_ssize_t how_many);


PyObject *PyDict_New(void);


Py_ssize_t PyList_Size(PyObject *);


PyObject *PyLong_FromSsize_t(Py_ssize_t);


int PyDict_SetItem(PyObject *mp, PyObject *key, PyObject *item);


PyObject *PyDict_Keys(PyObject *mp);


int PyList_Sort(PyObject *);


PyObject *PyDict_GetItemWithError(PyObject *mp, PyObject *key);


long PyLong_AsLong(PyObject *);


void PyObject_Free(void *ptr);


void *PyObject_Calloc(size_t nelem, size_t elsize);


PyObject *PyErr_NoMemory(void);


PySTEntryObject *PySymtable_Lookup(struct symtable *, void *);

static void compiler_unit_free(struct compiler_unit *u) ;

static PyObject *list2dict(PyObject *list) ;

static PyObject *dictbytype(PyObject *src, int scope_type, int flag, Py_ssize_t offset) ;


PyObject *_PyUnicode_FromId(_Py_Identifier *);

static inline PyObject *_PyLong_GetZero(void) ;


int PyList_Append(PyObject *, PyObject *);

static inline void _Py_XDECREF(PyObject *op) ;

static inline void _Py_XINCREF(PyObject *op) ;


PyObject *PyCapsule_New(void *pointer, const char *name, PyCapsule_Destructor destructor);

static basicblock *compiler_new_block(struct compiler *);

static int compiler_set_qualname(struct compiler *);


void *PyCapsule_GetPointer(PyObject *capsule, const char *name);


int PySequence_DelItem(PyObject *o, Py_ssize_t i);


void _PyErr_WriteUnraisableMsg(const char *err_msg, PyObject *obj);

static void compiler_unit_check(struct compiler_unit *u) ;

PyObject *_Py_Mangle(PyObject *privateobj, PyObject *ident) ;


extern int _PyST_GetScope(PySTEntryObject *, PyObject *);


PyObject *PyUnicode_Concat(PyObject *left, PyObject *right);


void PyUnicode_Append(PyObject **pleft, PyObject *right);

static int compiler_next_instr(basicblock *);


void *PyObject_Realloc(void *ptr, size_t new_size);

static int compiler_addop_line(struct compiler *c, int opcode, int line) ;


PyObject *PyErr_Occurred(void);

extern PyObject _Py_NoneStruct;
;
extern PyObject _Py_EllipsisObject;
;

PyObject *_PyCode_ConstantKey(PyObject *obj);


PyObject *PyDict_SetDefault(PyObject *mp, PyObject *key, PyObject *defaultobj);


int _PySet_NextEntry(PyObject *set, Py_ssize_t *pos, PyObject **key, Py_hash_t *hash);

extern PyTypeObject PyTuple_Type;
;
static PyObject *merge_consts_recursive(struct compiler *c, PyObject *o) ;

extern PyTypeObject PyFrozenSet_Type;
;

PyObject *PyTuple_New(Py_ssize_t size);


PyObject *PyFrozenSet_New(PyObject *);

static Py_ssize_t compiler_add_o(PyObject *dict, PyObject *o) ;

static Py_ssize_t compiler_add_const(struct compiler *c, PyObject *o) ;

static int compiler_addop_i(struct compiler *, int, Py_ssize_t);

static int compiler_addop_i_line(struct compiler *c, int opcode, Py_ssize_t oparg, int lineno) ;

static int add_jump_to_block(basicblock *b, int opcode, int lineno, basicblock *target) ;

static int compiler_error(struct compiler *, const char *, ...);


int _PyUnicode_EqualToASCIIString(PyObject *left, const char *right);


PyObject *PyErr_Format(PyObject *exception, const char *format, ...);

static int compiler_lookup_arg(PyObject *dict, PyObject *name) ;

static int get_ref_type(struct compiler *c, PyObject *name) ;

static int compiler_addop_load_const(struct compiler *c, PyObject *o) ;


PyObject *PyList_New(Py_ssize_t size);

static int compiler_visit_expr(struct compiler *, expr_ty);


PyObject *PyList_AsTuple(PyObject *);

static int compiler_visit_defaults(struct compiler *c, arguments_ty args) ;

static int compiler_visit_kwonlydefaults(struct compiler *c, asdl_arg_seq *kwonlyargs, asdl_expr_seq *kw_defaults) ;

static int forbidden_name(struct compiler *c, identifier name, expr_context_ty ctx) ;

static int compiler_check_debug_one_arg(struct compiler *c, arg_ty arg) ;

static int compiler_check_debug_args_seq(struct compiler *c, asdl_arg_seq *args) ;

extern struct _longobject _Py_FalseStruct;
;
extern struct _longobject _Py_TrueStruct;
;
static int check_is_arg(expr_ty e) ;

static int compiler_warn(struct compiler *, const char *, ...);

static int compiler_jump_if(struct compiler *c, expr_ty e, basicblock *next, int cond) ;

static basicblock *compiler_use_next_block(struct compiler *c, basicblock *block) ;

static int compiler_addop_j_noline(struct compiler *c, int opcode, basicblock *b) ;

static int check_compare(struct compiler *c, expr_ty e) ;

static int compiler_addop(struct compiler *c, int opcode) ;

static int compiler_addcompare(struct compiler *c, cmpop_ty op) ;

static int compiler_addop_j(struct compiler *c, int opcode, basicblock *b) ;

static basicblock *compiler_next_block(struct compiler *c) ;

static int compiler_check_debug_args(struct compiler *c, arguments_ty args) ;


PyObject *PyUnicode_InternFromString(const char *u);

static Py_ssize_t compiler_default_arguments(struct compiler *c, arguments_ty args) ;

static int compiler_enter_scope(struct compiler *c, identifier name, int scope_type, void *key, int lineno) ;

static void compiler_exit_scope(struct compiler *c) ;

static PyCodeObject *assemble(struct compiler *, int addNone);

static int compiler_make_closure(struct compiler *c, PyCodeObject *co, Py_ssize_t flags, PyObject *qualname) ;

extern PyObject *PyExc_SystemError;
;
static int compiler_addop_o(struct compiler *c, int opcode, PyObject *dict, PyObject *o) ;

static int are_all_items_const(asdl_expr_seq *, Py_ssize_t, Py_ssize_t);

static int unpack_helper(struct compiler *c, asdl_expr_seq *elts) ;

static int assignment_helper(struct compiler *c, asdl_expr_seq *elts) ;

static int starunpack_helper(struct compiler *c, asdl_expr_seq *elts, int pushed, int build, int add, int extend, int tuple) ;

static int compiler_subdict(struct compiler *c, expr_ty e, Py_ssize_t begin, Py_ssize_t end) ;

extern PyTypeObject PyList_Type;
;
extern PyTypeObject PyDict_Type;
;
extern PyTypeObject PySet_Type;
;
extern PyTypeObject PyGen_Type;
;
extern PyTypeObject PyFunction_Type;
;
extern PyTypeObject PyUnicode_Type;
;
static PyTypeObject *infer_type(expr_ty e) ;

static inline int _PyObject_TypeCheck(PyObject *ob, PyTypeObject *type) ;

extern PyTypeObject PyFloat_Type;
;
extern PyTypeObject PyComplex_Type;
;
extern PyTypeObject PySlice_Type;
;
static int compiler_addop_name(struct compiler *c, int opcode, PyObject *dict, PyObject *o) ;


int PyUnicode_Compare(PyObject *left, PyObject *right);

static int maybe_optimize_method_call(struct compiler *c, expr_ty e) ;

static int check_caller(struct compiler *c, expr_ty e) ;

static int compiler_call_helper(struct compiler *c, int n, asdl_expr_seq *args, asdl_keyword_seq *keywords);


PyObject *_PyUnicode_FromASCII(const char *buffer, Py_ssize_t size);

static int compiler_addop_i_noline(struct compiler *c, int opcode, Py_ssize_t oparg) ;

static int validate_keywords(struct compiler *c, asdl_keyword_seq *keywords) ;

static int compiler_visit_keyword(struct compiler *, keyword_ty);

static int compiler_subkwargs(struct compiler *c, asdl_keyword_seq *keywords, Py_ssize_t begin, Py_ssize_t end) ;

static int compiler_async_comprehension_generator(struct compiler *c, asdl_comprehension_seq *generators, int gen_index, int depth, expr_ty elt, expr_ty val, int type);

static int compiler_sync_comprehension_generator(struct compiler *c, asdl_comprehension_seq *generators, int gen_index, int depth, expr_ty elt, expr_ty val, int type);

static int compiler_comprehension_generator(struct compiler *c, asdl_comprehension_seq *generators, int gen_index, int depth, expr_ty elt, expr_ty val, int type) ;

static int compiler_push_fblock(struct compiler *c, enum fblocktype t, basicblock *b, basicblock *exit, void *datum) ;

static void compiler_pop_fblock(struct compiler *c, enum fblocktype t, basicblock *b) ;

static int compiler_comprehension(struct compiler *c, expr_ty e, int type, identifier name, asdl_comprehension_seq *generators, expr_ty elt, expr_ty val) ;

static int compiler_boolop(struct compiler *c, expr_ty e) ;

static int binop(operator_ty op) ;

static int unaryop(unaryop_ty op) ;

static int compiler_lambda(struct compiler *c, expr_ty e) ;

static int compiler_ifexp(struct compiler *c, expr_ty e) ;

static int compiler_dict(struct compiler *c, expr_ty e) ;

static int compiler_set(struct compiler *c, expr_ty e) ;

static int compiler_genexp(struct compiler *c, expr_ty e) ;

static int compiler_listcomp(struct compiler *c, expr_ty e) ;

static int compiler_setcomp(struct compiler *c, expr_ty e) ;

static int compiler_dictcomp(struct compiler *c, expr_ty e) ;

static int compiler_compare(struct compiler *c, expr_ty e) ;

static int compiler_call(struct compiler *c, expr_ty e) ;

static int compiler_joined_str(struct compiler *c, expr_ty e) ;

static int compiler_formatted_value(struct compiler *c, expr_ty e) ;

static int compiler_subscript(struct compiler *, expr_ty);

static int compiler_slice(struct compiler *, expr_ty);

static int compiler_nameop(struct compiler *c, identifier name, expr_context_ty ctx) ;

static int compiler_list(struct compiler *c, expr_ty e) ;

static int compiler_tuple(struct compiler *c, expr_ty e) ;

static int compiler_visit_expr1(struct compiler *c, expr_ty e) ;


PyObject *PyUnicode_FromFormatV(const char *format, va_list vargs);


PyObject *PyErr_ProgramTextObject(PyObject *filename, int lineno);


PyObject *Py_BuildValue(const char *, ...);


int PyErr_WarnExplicitObject(PyObject *category, PyObject *message, PyObject *filename, int lineno, PyObject *module, PyObject *registry);


int PyErr_ExceptionMatches(PyObject *);


void PyErr_Clear(void);


const char *PyUnicode_AsUTF8(PyObject *unicode);

extern PyObject *PyExc_SyntaxWarning;
;
static int check_subscripter(struct compiler *c, expr_ty e) ;

static int check_index(struct compiler *c, expr_ty e, expr_ty s) ;


void *PyObject_Malloc(size_t size);

static inline void stackdepth_push(basicblock ***sp, basicblock *b, int depth) ;

static inline int is_jump(struct instr *i) ;

static int stack_effect(int opcode, int oparg, int jump) ;


PyObject *PyBytes_FromStringAndSize(const char *, Py_ssize_t);

static int instrsize(unsigned int oparg) ;


int _PyBytes_Resize(PyObject **, Py_ssize_t);

static int assemble_emit_linetable_pair(struct assembler *a, int bdelta, int ldelta) ;

static int assemble_line_range(struct assembler *a) ;

static int assemble_lnotab(struct assembler *a, struct instr *i) ;

static void write_op_arg(_Py_CODEUNIT *codestr, unsigned char opcode, unsigned int oparg, int ilen) ;

static int blocksize(basicblock *b) ;

static inline int is_relative_jump(struct instr *i) ;


int PyDict_Next(PyObject *mp, Py_ssize_t *pos, PyObject **key, PyObject **value);

static PyObject *dict_keys_inorder(PyObject *dict, Py_ssize_t offset) ;

static int merge_const_one(struct compiler *c, PyObject **obj) ;

static int compute_code_flags(struct compiler *c) ;

static int stackdepth(struct compiler *c) ;


PyCodeObject *PyCode_NewWithPosOnlyArgs(int, int, int, int, int, int, PyObject *, PyObject *, PyObject *, PyObject *, PyObject *, PyObject *, PyObject *, PyObject *, int, PyObject *);

static int normalize_basic_block(basicblock *bb);

static int extend_block(basicblock *bb);

static int insert_generator_prefix(struct compiler *c, basicblock *entryblock) ;

static int assemble_init(struct assembler *a, int nblocks, int firstlineno) ;

static PyObject *consts_dict_keys_inorder(PyObject *dict) ;

static int optimize_cfg(struct compiler *c, struct assembler *a, PyObject *consts);

static int duplicate_exits_without_lineno(struct compiler *c);

static int trim_unused_consts(struct compiler *c, struct assembler *a, PyObject *consts);

static void propagate_line_numbers(struct assembler *a);

static void guarantee_lineno_for_exits(struct assembler *a, int firstlineno) ;

static void normalize_jumps(struct assembler *a) ;

static void assemble_jump_offsets(struct assembler *a, struct compiler *c) ;

static int assemble_emit(struct assembler *a, struct instr *i) ;

static PyCodeObject *makecode(struct compiler *c, struct assembler *a, PyObject *consts) ;

static void assemble_free(struct assembler *a) ;


int PyObject_IsTrue(PyObject *);

static int fold_tuple_on_constants(struct compiler *c, struct instr *inst, int n, PyObject *consts) ;

static _Bool jump_thread(struct instr *inst, struct instr *target, int opcode) ;

static void fold_rotations(struct instr *inst, int n) ;

static int optimize_basic_block(struct compiler *c, basicblock *bb, PyObject *consts) ;

static void clean_basic_block(basicblock *bb, int prev_lineno) ;

static int mark_reachable(struct assembler *a) ;

static void eliminate_empty_basic_blocks(basicblock *entry) ;


int PyList_SetSlice(PyObject *, Py_ssize_t, Py_ssize_t, PyObject *);

static inline int is_exit_without_lineno(basicblock *b) ;

static basicblock *compiler_copy_block(struct compiler *c, basicblock *block) ;

#endif