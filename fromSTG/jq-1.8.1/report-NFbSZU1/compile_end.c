#include "header_func.h"
static inst * inst_new (opcode op){
    inst *i = jv_mem_alloc(sizeof(inst));
    i->next = i->prev = 0;
    i->op = op;
    i->bytecode_pos = -1;
    i->bound_by = 0;
    i->symbol = 0;
    i->any_unbound = 0;
    i->referenced = 0;
    i->nformals = -1;
    i->nactuals = -1;
    i->subfn = gen_noop();
    i->arglist = gen_noop();
    i->locfile = 0;
    return i;
}
static block inst_block (inst *i){
    block b = {i, i};
    return b;
}
extern int block_is_single (block b){
    return b.first && b.first == b.last;
}
static inst * block_take (block *b){
    if (b->first == 0)
        return 0;
    inst *i = b->first;
    if (i->next) {
        i->next->prev = 0;
        b->first = i->next;
        i->next = 0;
    } else {
        b->first = 0;
        b->last = 0;
    }
    return i;
}
extern block gen_noop (){
    block b = {0, 0};
    return b;
}
extern int block_is_noop (block b){
    return (b.first == 0 && b.last == 0);
}
extern block gen_op_simple (opcode op){
    ((void)sizeof ((opcode_describe(op)->length == 1) ? 1 : 0) , __extension__ ({
        if (opcode_describe(op)->length == 1)
            ;
        else
            __assert_fail("opcode_describe(op)->length == 1", "src/compile_InstSlice.c", 122, __extension__ __PRETTY_FUNCTION__);
    }));
    return inst_block(inst_new(op));
}
extern block gen_op_pushk_under (jv constant){
    ((void)sizeof ((opcode_describe(PUSHK_UNDER)->flags & OP_HAS_CONSTANT) ? 1 : 0) , __extension__ ({
        if (opcode_describe(PUSHK_UNDER)->flags & OP_HAS_CONSTANT)
            ;
        else
            __assert_fail("opcode_describe(PUSHK_UNDER)->flags & OP_HAS_CONSTANT", "src/compile_InstSlice.c", 134, __extension__ __PRETTY_FUNCTION__);
    }));
    inst *i = inst_new(PUSHK_UNDER);
    return inst_block(i);
}
extern int block_is_const (block b){
    return (block_is_single(b) && (b.first->op == LOADK || b.first->op == PUSHK_UNDER));
}
extern jv block_const (block b){
    ((void)sizeof ((block_is_const(b)) ? 1 : 0) , __extension__ ({
        if (block_is_const(b))
            ;
        else
            __assert_fail("block_is_const(b)", "src/compile_InstSlice.c", 147, __extension__ __PRETTY_FUNCTION__);
    }));
    return jv_copy(b.first->imm.constant);
}
extern block gen_op_unbound (opcode op, const char *name){
    ((void)sizeof ((opcode_describe(op)->flags & OP_HAS_BINDING) ? 1 : 0) , __extension__ ({
        if (opcode_describe(op)->flags & OP_HAS_BINDING)
            ;
        else
            __assert_fail("opcode_describe(op)->flags & OP_HAS_BINDING", "src/compile_InstSlice.c", 157, __extension__ __PRETTY_FUNCTION__);
    }));
    inst *i = inst_new(op);
    i->symbol = strdup(name);
    i->any_unbound = 1;
    return inst_block(i);
}
extern block gen_op_bound (opcode op, block binder){
    ((void)sizeof ((block_is_single(binder)) ? 1 : 0) , __extension__ ({
        if (block_is_single(binder))
            ;
        else
            __assert_fail("block_is_single(binder)", "src/compile_InstSlice.c", 167, __extension__ __PRETTY_FUNCTION__);
    }));
    block b = gen_op_unbound(op, binder.first->symbol);
    b.first->bound_by = binder.first;
    b.first->any_unbound = 0;
    return b;
}
static void inst_join (inst *a, inst *b){
    ((void)sizeof ((a && b) ? 1 : 0) , __extension__ ({
        if (a && b)
            ;
        else
            __assert_fail("a && b", "src/compile_InstSlice.c", 178, __extension__ __PRETTY_FUNCTION__);
    }));
    ((void)sizeof ((!a->next) ? 1 : 0) , __extension__ ({
        if (!a->next)
            ;
        else
            __assert_fail("!a->next", "src/compile_InstSlice.c", 179, __extension__ __PRETTY_FUNCTION__);
    }));
    ((void)sizeof ((!b->prev) ? 1 : 0) , __extension__ ({
        if (!b->prev)
            ;
        else
            __assert_fail("!b->prev", "src/compile_InstSlice.c", 180, __extension__ __PRETTY_FUNCTION__);
    }));
    a->next = b;
    b->prev = a;
}
extern void block_append (block *b, block b2){
    if (b2.first) {
        if (b->last) {
            inst_join(b->last, b2.first);
        } else {
            b->first = b2.first;
        }
        b->last = b2.last;
    }
}
extern block block_join (block a, block b){
    block c = a;
    block_append(&c, b);
    return c;
}
extern block gen_subexp (block a){
    if (block_is_noop(a)) {
        return gen_op_simple(DUP);
    }
    if (block_is_single(a) && a.first->op == LOADK) {
        jv c = block_const(a);
        return gen_op_pushk_under(c);
    }
    return (block_join((block_join((gen_op_simple(SUBEXP_BEGIN)), (a))), (gen_op_simple(SUBEXP_END))));
}
static uint16_t nesting_level (struct bytecode *bc, inst *target){
    uint16_t level = 0;
    ((void)sizeof ((bc && target && target->compiled) ? 1 : 0) , __extension__ ({
        if (bc && target && target->compiled)
            ;
        else
            __assert_fail("bc && target && target->compiled", "src/compile_InstSlice.c", 329, __extension__ __PRETTY_FUNCTION__);
    }));
    while (bc && target->compiled != bc)
        {
            level++;
            bc = bc->parent;
        }
    ((void)sizeof ((bc && bc == target->compiled) ? 1 : 0) , __extension__ ({
        if (bc && bc == target->compiled)
            ;
        else
            __assert_fail("bc && bc == target->compiled", "src/compile_InstSlice.c", 334, __extension__ __PRETTY_FUNCTION__);
    }));
    return level;
}
static jv make_env (jv env){
    if (jv_is_valid(env))
        return jv_copy(env);
    jv r = jv_object();
    if (environ == ((void *)0))
        return r;
    for (size_t i = 0; environ[i] != ((void *)0); i++) {
        const char *eq;
        if ((eq = strchr(environ[i], '=')) == ((void *)0)) {
            r = jv_object_delete(r, jv_string(environ[i]));
        } else
            r = jv_object_set(r, jv_string_sized(environ[i], eq - environ[i]), jv_string(eq + 1));
    }
    return jv_copy(r);
}
static int expand_call_arglist (block *b, jv args, jv *env){
    int errors = 0;
    block ret = gen_noop();
    for (inst *curr; (curr = block_take(b));) {
        if (opcode_describe(curr->op)->flags & OP_HAS_BINDING) {
            if (!curr->bound_by && curr->op == LOADV && strcmp(curr->symbol, "ENV") == 0) {
                curr->op = LOADK;
                *env = curr->imm.constant = make_env(*env);
            } else if (!curr->bound_by && curr->op == LOADV && jv_object_has(jv_copy(args), jv_string(curr->symbol))) {
                curr->op = LOADK;
                curr->imm.constant = jv_object_get(jv_copy(args), jv_string(curr->symbol));
            } else if (!curr->bound_by) {
                ;
                errors++;
                ret = (block_join((ret), (inst_block(curr))));
                continue;
            }
        }
        block prelude = gen_noop();
        if (curr->op == CALL_JQ) {
            int actual_args = 0, desired_args = 0;
            switch (curr->bound_by->op) {
              default:
                ((void)sizeof ((0 && "Unknown function type") ? 1 : 0) , __extension__ ({
                    if (0 && "Unknown function type")
                        ;
                    else
                        __assert_fail("0 && \"Unknown function type\"", "src/compile_InstSlice.c", 389, __extension__ __PRETTY_FUNCTION__);
                }));
                break;
              case CLOSURE_CREATE:
              case CLOSURE_PARAM:
                {
                    block callargs = gen_noop();
                    for (inst *i; (i = block_take(&curr->arglist));) {
                        ((void)sizeof ((opcode_describe(i->op)->flags & OP_IS_CALL_PSEUDO) ? 1 : 0) , __extension__ ({
                            if (opcode_describe(i->op)->flags & OP_IS_CALL_PSEUDO)
                                ;
                            else
                                __assert_fail("opcode_describe(i->op)->flags & OP_IS_CALL_PSEUDO", "src/compile_InstSlice.c", 394, __extension__ __PRETTY_FUNCTION__);
                        }));
                        block b = inst_block(i);
                        switch (i->op) {
                          default:
                            ((void)sizeof ((0 && "Unknown type of parameter") ? 1 : 0) , __extension__ ({
                                if (0 && "Unknown type of parameter")
                                    ;
                                else
                                    __assert_fail("0 && \"Unknown type of parameter\"", "src/compile_InstSlice.c", 397, __extension__ __PRETTY_FUNCTION__);
                            }));
                            break;
                          case CLOSURE_REF:
                            block_append(&callargs, b);
                            break;
                          case CLOSURE_CREATE:
                            block_append(&prelude, b);
                            block_append(&callargs, gen_op_bound(CLOSURE_REF, b));
                            break;
                        }
                        actual_args++;
                    }
                    curr->imm.intval = actual_args;
                    if (curr->bound_by->op == CLOSURE_CREATE) {
                        for (inst *i = curr->bound_by->arglist.first; i; i = i->next) {
                            ((void)sizeof ((i->op == CLOSURE_PARAM) ? 1 : 0) , __extension__ ({
                                if (i->op == CLOSURE_PARAM)
                                    ;
                                else
                                    __assert_fail("i->op == CLOSURE_PARAM", "src/compile_InstSlice.c", 413, __extension__ __PRETTY_FUNCTION__);
                            }));
                            desired_args++;
                        }
                    }
                    break;
                }
              case CLOSURE_CREATE_C:
                {
                    for (inst *i; (i = block_take(&curr->arglist));) {
                        ((void)sizeof ((i->op == CLOSURE_CREATE) ? 1 : 0) , __extension__ ({
                            if (i->op == CLOSURE_CREATE)
                                ;
                            else
                                __assert_fail("i->op == CLOSURE_CREATE", "src/compile_InstSlice.c", 422, __extension__ __PRETTY_FUNCTION__);
                        }));
                        block body = i->subfn;
                        i->subfn = gen_noop();
                        errors += expand_call_arglist(&body, args, env);
                        prelude = (block_join((gen_subexp(body)), (prelude)));
                        actual_args++;
                    }
                    ((void)sizeof ((curr->op == CALL_JQ) ? 1 : 0) , __extension__ ({
                        if (curr->op == CALL_JQ)
                            ;
                        else
                            __assert_fail("curr->op == CALL_JQ", "src/compile_InstSlice.c", 431, __extension__ __PRETTY_FUNCTION__);
                    }));
                    curr->op = CALL_BUILTIN;
                    curr->imm.intval = actual_args + 1;
                    ((void)sizeof ((curr->bound_by->op == CLOSURE_CREATE_C) ? 1 : 0) , __extension__ ({
                        if (curr->bound_by->op == CLOSURE_CREATE_C)
                            ;
                        else
                            __assert_fail("curr->bound_by->op == CLOSURE_CREATE_C", "src/compile_InstSlice.c", 434, __extension__ __PRETTY_FUNCTION__);
                    }));
                    desired_args = curr->bound_by->imm.cfunc->nargs - 1;
                    ((void)sizeof ((!curr->arglist.first) ? 1 : 0) , __extension__ ({
                        if (!curr->arglist.first)
                            ;
                        else
                            __assert_fail("!curr->arglist.first", "src/compile_InstSlice.c", 436, __extension__ __PRETTY_FUNCTION__);
                    }));
                    break;
                }
            }
            ((void)sizeof ((actual_args == desired_args) ? 1 : 0) , __extension__ ({
                if (actual_args == desired_args)
                    ;
                else
                    __assert_fail("actual_args == desired_args", "src/compile_InstSlice.c", 441, __extension__ __PRETTY_FUNCTION__);
            }));
        }
        ret = (block_join((block_join((ret), (prelude))), (inst_block(curr))));
    }
    *b = ret;
    return errors;
}
static int compile (struct bytecode *bc, block b, struct locfile *lf, jv args, jv *env){
    int errors = 0;
    int pos = 0;
    int var_frame_idx = 0;
    bc->nsubfunctions = 0;
    errors += expand_call_arglist(&b, args, env);
    b = (block_join((b), (gen_op_simple(RET))));
    jv localnames = jv_array();
    for (inst *curr = b.first; curr; curr = curr->next) {
        if (!curr->next)
            ((void)sizeof ((curr == b.last) ? 1 : 0) , __extension__ ({
                if (curr == b.last)
                    ;
                else
                    __assert_fail("curr == b.last", "src/compile_InstSlice.c", 458, __extension__ __PRETTY_FUNCTION__);
            }));
        int length = opcode_describe(curr->op)->length;
        if (curr->op == CALL_JQ) {
            for (inst *arg = curr->arglist.first; arg; arg = arg->next) {
                length += 2;
            }
        }
        pos += length;
        curr->bytecode_pos = pos;
        curr->compiled = bc;
        ((void)sizeof ((curr->op != CLOSURE_REF && curr->op != CLOSURE_PARAM) ? 1 : 0) , __extension__ ({
            if (curr->op != CLOSURE_REF && curr->op != CLOSURE_PARAM)
                ;
            else
                __assert_fail("curr->op != CLOSURE_REF && curr->op != CLOSURE_PARAM", "src/compile_InstSlice.c", 469, __extension__ __PRETTY_FUNCTION__);
        }));
        if ((opcode_describe(curr->op)->flags & OP_HAS_VARIABLE) && curr->bound_by == curr) {
            curr->imm.intval = var_frame_idx++;
            localnames = jv_array_append(localnames, jv_string(curr->symbol));
        }
        if (curr->op == CLOSURE_CREATE) {
            ((void)sizeof ((curr->bound_by == curr) ? 1 : 0) , __extension__ ({
                if (curr->bound_by == curr)
                    ;
                else
                    __assert_fail("curr->bound_by == curr", "src/compile_InstSlice.c", 477, __extension__ __PRETTY_FUNCTION__);
            }));
            curr->imm.intval = bc->nsubfunctions++;
        }
        if (curr->op == CLOSURE_CREATE_C) {
            ((void)sizeof ((curr->bound_by == curr) ? 1 : 0) , __extension__ ({
                if (curr->bound_by == curr)
                    ;
                else
                    __assert_fail("curr->bound_by == curr", "src/compile_InstSlice.c", 481, __extension__ __PRETTY_FUNCTION__);
            }));
            int idx = bc->globals->ncfunctions++;
            bc->globals->cfunc_names = jv_array_append(bc->globals->cfunc_names, jv_string(curr->symbol));
            curr->imm.intval = idx;
        }
    }
    if (pos > 65535) {
        ;
        errors++;
    }
    bc->codelen = pos;
    bc->debuginfo = jv_object_set(bc->debuginfo, jv_string("locals"), localnames);
    if (bc->nsubfunctions && !errors) {
        bc->subfunctions = jv_mem_calloc(bc->nsubfunctions, sizeof(struct bytecode *));
        for (inst *curr = b.first; curr; curr = curr->next) {
            if (curr->op == CLOSURE_CREATE) {
                struct bytecode *subfn = jv_mem_alloc(sizeof(struct bytecode));
                bc->subfunctions[curr->imm.intval] = subfn;
                subfn->globals = bc->globals;
                subfn->parent = bc;
                subfn->nclosures = 0;
                subfn->debuginfo = jv_object_set(jv_object(), jv_string("name"), jv_string(curr->symbol));
                jv params = jv_array();
                for (inst *param = curr->arglist.first; param; param = param->next) {
                    ((void)sizeof ((param->op == CLOSURE_PARAM) ? 1 : 0) , __extension__ ({
                        if (param->op == CLOSURE_PARAM)
                            ;
                        else
                            __assert_fail("param->op == CLOSURE_PARAM", "src/compile_InstSlice.c", 507, __extension__ __PRETTY_FUNCTION__);
                    }));
                    ((void)sizeof ((param->bound_by == param) ? 1 : 0) , __extension__ ({
                        if (param->bound_by == param)
                            ;
                        else
                            __assert_fail("param->bound_by == param", "src/compile_InstSlice.c", 508, __extension__ __PRETTY_FUNCTION__);
                    }));
                    param->imm.intval = subfn->nclosures++;
                    param->compiled = subfn;
                    params = jv_array_append(params, jv_string(param->symbol));
                }
                subfn->debuginfo = jv_object_set(subfn->debuginfo, jv_string("params"), params);
                errors += compile(subfn, curr->subfn, lf, args, env);
                curr->subfn = gen_noop();
            }
        }
    } else {
        bc->nsubfunctions = 0;
        bc->subfunctions = 0;
    }
    uint16_t *code = jv_mem_calloc(bc->codelen, sizeof(uint16_t));
    bc->code = code;
    pos = 0;
    jv constant_pool = jv_array();
    int maxvar = -1;
    if (!errors)
        for (inst *curr = b.first; curr; curr = curr->next) {
            const struct opcode_description *op = opcode_describe(curr->op);
            if (op->length == 0)
                continue;
            code[pos++] = curr->op;
            ((void)sizeof ((curr->op != CLOSURE_REF && curr->op != CLOSURE_PARAM) ? 1 : 0) , __extension__ ({
                if (curr->op != CLOSURE_REF && curr->op != CLOSURE_PARAM)
                    ;
                else
                    __assert_fail("curr->op != CLOSURE_REF && curr->op != CLOSURE_PARAM", "src/compile_InstSlice.c", 532, __extension__ __PRETTY_FUNCTION__);
            }));
            if (curr->op == CALL_BUILTIN) {
                ((void)sizeof ((curr->bound_by->op == CLOSURE_CREATE_C) ? 1 : 0) , __extension__ ({
                    if (curr->bound_by->op == CLOSURE_CREATE_C)
                        ;
                    else
                        __assert_fail("curr->bound_by->op == CLOSURE_CREATE_C", "src/compile_InstSlice.c", 534, __extension__ __PRETTY_FUNCTION__);
                }));
                ((void)sizeof ((!curr->arglist.first) ? 1 : 0) , __extension__ ({
                    if (!curr->arglist.first)
                        ;
                    else
                        __assert_fail("!curr->arglist.first", "src/compile_InstSlice.c", 535, __extension__ __PRETTY_FUNCTION__);
                }));
                code[pos++] = (uint16_t)curr->imm.intval;
                code[pos++] = curr->bound_by->imm.intval;
            } else if (curr->op == CALL_JQ) {
                ((void)sizeof ((curr->bound_by->op == CLOSURE_CREATE || curr->bound_by->op == CLOSURE_PARAM) ? 1 : 0) , __extension__ ({
                    if (curr->bound_by->op == CLOSURE_CREATE || curr->bound_by->op == CLOSURE_PARAM)
                        ;
                    else
                        __assert_fail("curr->bound_by->op == CLOSURE_CREATE || curr->bound_by->op == CLOSURE_PARAM", "src/compile_InstSlice.c", 540, __extension__ __PRETTY_FUNCTION__);
                }));
                code[pos++] = (uint16_t)curr->imm.intval;
                code[pos++] = nesting_level(bc, curr->bound_by);
                code[pos++] = curr->bound_by->imm.intval | (curr->bound_by->op == CLOSURE_CREATE ? 4096 : 0);
                for (inst *arg = curr->arglist.first; arg; arg = arg->next) {
                    ((void)sizeof ((arg->op == CLOSURE_REF && arg->bound_by->op == CLOSURE_CREATE) ? 1 : 0) , __extension__ ({
                        if (arg->op == CLOSURE_REF && arg->bound_by->op == CLOSURE_CREATE)
                            ;
                        else
                            __assert_fail("arg->op == CLOSURE_REF && arg->bound_by->op == CLOSURE_CREATE", "src/compile_InstSlice.c", 545, __extension__ __PRETTY_FUNCTION__);
                    }));
                    code[pos++] = nesting_level(bc, arg->bound_by);
                    code[pos++] = arg->bound_by->imm.intval | 4096;
                }
            } else if ((op->flags & OP_HAS_CONSTANT) && (op->flags & OP_HAS_VARIABLE)) {
                code[pos++] = jv_array_length(jv_copy(constant_pool));
                constant_pool = jv_array_append(constant_pool, jv_copy(curr->imm.constant));
                code[pos++] = nesting_level(bc, curr->bound_by);
                uint16_t var = (uint16_t)curr->bound_by->imm.intval;
                code[pos++] = var;
                if (var > maxvar)
                    maxvar = var;
            } else if (op->flags & OP_HAS_CONSTANT) {
                code[pos++] = jv_array_length(jv_copy(constant_pool));
                constant_pool = jv_array_append(constant_pool, jv_copy(curr->imm.constant));
            } else if (op->flags & OP_HAS_VARIABLE) {
                code[pos++] = nesting_level(bc, curr->bound_by);
                uint16_t var = (uint16_t)curr->bound_by->imm.intval;
                code[pos++] = var;
                if (var > maxvar)
                    maxvar = var;
            } else if (op->flags & OP_HAS_BRANCH) {
                ((void)sizeof ((curr->imm.target->bytecode_pos != -1) ? 1 : 0) , __extension__ ({
                    if (curr->imm.target->bytecode_pos != -1)
                        ;
                    else
                        __assert_fail("curr->imm.target->bytecode_pos != -1", "src/compile_InstSlice.c", 566, __extension__ __PRETTY_FUNCTION__);
                }));
                ((void)sizeof ((curr->imm.target->bytecode_pos > pos) ? 1 : 0) , __extension__ ({
                    if (curr->imm.target->bytecode_pos > pos)
                        ;
                    else
                        __assert_fail("curr->imm.target->bytecode_pos > pos", "src/compile_InstSlice.c", 567, __extension__ __PRETTY_FUNCTION__);
                }));
                code[pos] = curr->imm.target->bytecode_pos - (pos + 1);
                pos++;
            } else if (op->length > 1) {
                ;
            }
        }
    ;
    bc->nlocals = maxvar + 2;
    return errors;
}
