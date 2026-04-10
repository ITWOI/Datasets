static int frame_size (struct bytecode *bc){
    return sizeof(struct frame) + sizeof(union frame_entry) * (bc->nclosures + bc->nlocals);
}


static struct frame * frame_current (struct jq_state *jq){
    struct frame *fp = stack_block(&jq->stk, jq->curr_frame);
    stack_ptr next = *stack_block_next(&jq->stk, jq->curr_frame);
    if (next) {
        struct frame *fpnext = stack_block(&jq->stk, next);
        struct bytecode *bc = fpnext->bc;
        ((void)sizeof ((fp->retaddr >= bc->code && fp->retaddr < bc->code + bc->codelen) ? 1 : 0) , __extension__ ({
            if (fp->retaddr >= bc->code && fp->retaddr < bc->code + bc->codelen)
                ;
            else
                __assert_fail("fp->retaddr >= bc->code && fp->retaddr < bc->code + bc->codelen", "src/execute_InstSlice.c", 87, __extension__ __PRETTY_FUNCTION__);
        }));
    } else {
        ((void)sizeof ((fp->retaddr == 0) ? 1 : 0) , __extension__ ({
            if (fp->retaddr == 0)
                ;
            else
                __assert_fail("fp->retaddr == 0", "src/execute_InstSlice.c", 89, __extension__ __PRETTY_FUNCTION__);
        }));
    }
    return fp;
}


static stack_ptr frame_get_level (struct jq_state *jq, int level){
    stack_ptr fr = jq->curr_frame;
    for (int i = 0; i < level; i++) {
        struct frame *fp = stack_block(&jq->stk, fr);
        fr = fp->env;
    }
    return fr;
}


static jv * frame_local_var (struct jq_state *jq, int var, int level){
    struct frame *fr = stack_block(&jq->stk, frame_get_level(jq, level));
    ((void)sizeof ((var >= 0) ? 1 : 0) , __extension__ ({
        if (var >= 0)
            ;
        else
            __assert_fail("var >= 0", "src/execute_InstSlice.c", 105, __extension__ __PRETTY_FUNCTION__);
    }));
    ((void)sizeof ((var < fr->bc->nlocals) ? 1 : 0) , __extension__ ({
        if (var < fr->bc->nlocals)
            ;
        else
            __assert_fail("var < fr->bc->nlocals", "src/execute_InstSlice.c", 106, __extension__ __PRETTY_FUNCTION__);
    }));
    return &fr->entries[fr->bc->nclosures + var].localvar;
}


static struct closure make_closure (struct jq_state *jq, uint16_t *pc){
    uint16_t level = *pc++;
    uint16_t idx = *pc++;
    stack_ptr fridx = frame_get_level(jq, level);
    struct frame *fr = stack_block(&jq->stk, fridx);
    if (idx & 4096) {
        int subfn_idx = idx & ~4096;
        ((void)sizeof ((subfn_idx < fr->bc->nsubfunctions) ? 1 : 0) , __extension__ ({
            if (subfn_idx < fr->bc->nsubfunctions)
                ;
            else
                __assert_fail("subfn_idx < fr->bc->nsubfunctions", "src/execute_InstSlice.c", 119, __extension__ __PRETTY_FUNCTION__);
        }));
        struct closure cl = {fr->bc->subfunctions[subfn_idx], fridx};
        return cl;
    } else {
        int closure = idx;
        ((void)sizeof ((closure >= 0) ? 1 : 0) , __extension__ ({
            if (closure >= 0)
                ;
            else
                __assert_fail("closure >= 0", "src/execute_InstSlice.c", 126, __extension__ __PRETTY_FUNCTION__);
        }));
        ((void)sizeof ((closure < fr->bc->nclosures) ? 1 : 0) , __extension__ ({
            if (closure < fr->bc->nclosures)
                ;
            else
                __assert_fail("closure < fr->bc->nclosures", "src/execute_InstSlice.c", 127, __extension__ __PRETTY_FUNCTION__);
        }));
        return fr->entries[closure].closure;
    }
}


static struct frame * frame_push (struct jq_state *jq, struct closure callee, uint16_t *argdef, int nargs){
    stack_ptr new_frame_idx = stack_push_block(&jq->stk, jq->curr_frame, frame_size(callee.bc));
    struct frame *new_frame = stack_block(&jq->stk, new_frame_idx);
    new_frame->bc = callee.bc;
    new_frame->env = callee.env;
    ((void)sizeof ((nargs == new_frame->bc->nclosures) ? 1 : 0) , __extension__ ({
        if (nargs == new_frame->bc->nclosures)
            ;
        else
            __assert_fail("nargs == new_frame->bc->nclosures", "src/execute_InstSlice.c", 138, __extension__ __PRETTY_FUNCTION__);
    }));
    union frame_entry *entries = new_frame->entries;
    for (int i = 0; i < nargs; i++) {
        entries->closure = make_closure(jq, argdef + i * 2);
        entries++;
    }
    for (int i = 0; i < callee.bc->nlocals; i++) {
        entries->localvar = jv_invalid();
        entries++;
    }
    jq->curr_frame = new_frame_idx;
    return new_frame;
}


static void frame_pop (struct jq_state *jq){
    ((void)sizeof ((jq->curr_frame) ? 1 : 0) , __extension__ ({
        if (jq->curr_frame)
            ;
        else
            __assert_fail("jq->curr_frame", "src/execute_InstSlice.c", 153, __extension__ __PRETTY_FUNCTION__);
    }));
    struct frame *fp = frame_current(jq);
    if (stack_pop_will_free(&jq->stk, jq->curr_frame)) {
        int nlocals = fp->bc->nlocals;
        for (int i = 0; i < nlocals; i++) {
            jv_free(*frame_local_var(jq, i, 0));
        }
    }
    jq->curr_frame = stack_pop_block(&jq->stk, jq->curr_frame, frame_size(fp->bc));
}


extern void stack_push (jq_state *jq, jv val){
    ((void)sizeof ((jv_is_valid(val)) ? 1 : 0) , __extension__ ({
        if (jv_is_valid(val))
            ;
        else
            __assert_fail("jv_is_valid(val)", "src/execute_InstSlice.c", 165, __extension__ __PRETTY_FUNCTION__);
    }));
    jq->stk_top = stack_push_block(&jq->stk, jq->stk_top, sizeof(jv));
    jv *sval = stack_block(&jq->stk, jq->stk_top);
    ;
}


extern jv stack_pop (jq_state *jq){
    jv *sval = stack_block(&jq->stk, jq->stk_top);
    jv val = *sval;
    if (!stack_pop_will_free(&jq->stk, jq->stk_top)) {
        val = jv_copy(val);
    }
    jq->stk_top = stack_pop_block(&jq->stk, jq->stk_top, sizeof(jv));
    ((void)sizeof ((jv_is_valid(val)) ? 1 : 0) , __extension__ ({
        if (jv_is_valid(val))
            ;
        else
            __assert_fail("jv_is_valid(val)", "src/execute_InstSlice.c", 178, __extension__ __PRETTY_FUNCTION__);
    }));
    return val;
}


extern jv stack_popn (jq_state *jq){
    jv *sval = stack_block(&jq->stk, jq->stk_top);
    jv val = *sval;
    if (!stack_pop_will_free(&jq->stk, jq->stk_top)) {
        *sval = jv_null();
    }
    jq->stk_top = stack_pop_block(&jq->stk, jq->stk_top, sizeof(jv));
    ((void)sizeof ((jv_is_valid(val)) ? 1 : 0) , __extension__ ({
        if (jv_is_valid(val))
            ;
        else
            __assert_fail("jv_is_valid(val)", "src/execute_InstSlice.c", 191, __extension__ __PRETTY_FUNCTION__);
    }));
    return val;
}


extern struct stack_pos stack_get_pos (jq_state *jq){
    struct stack_pos sp = {jq->stk_top, jq->curr_frame};
    return sp;
}


extern void stack_save (jq_state *jq, uint16_t *retaddr, struct stack_pos sp){
    jq->fork_top = stack_push_block(&jq->stk, jq->fork_top, sizeof(struct forkpoint));
    struct forkpoint *fork = stack_block(&jq->stk, jq->fork_top);
    fork->saved_data_stack = jq->stk_top;
    fork->saved_curr_frame = jq->curr_frame;
    fork->path_len = jv_get_kind(jq->path) == JV_KIND_ARRAY ? jv_array_length(jv_copy(jq->path)) : 0;
    fork->value_at_path = jv_copy(jq->value_at_path);
    fork->subexp_nest = jq->subexp_nest;
    fork->return_address = retaddr;
    jq->stk_top = sp.saved_data_stack;
    jq->curr_frame = sp.saved_curr_frame;
}


static int path_intact (jq_state *jq, jv curr){
    if (jq->subexp_nest == 0 && jv_get_kind(jq->path) == JV_KIND_ARRAY) {
        return jv_identical(curr, jv_copy(jq->value_at_path));
    } else {
        ;
        return 1;
    }
}


static void path_append (jq_state *jq, jv component, jv value_at_path){
    if (jq->subexp_nest == 0 && jv_get_kind(jq->path) == JV_KIND_ARRAY) {
        int n1 = jv_array_length(jv_copy(jq->path));
        jq->path = jv_array_append(jq->path, component);
        int n2 = jv_array_length(jv_copy(jq->path));
        ((void)sizeof ((n2 == n1 + 1) ? 1 : 0) , __extension__ ({
            if (n2 == n1 + 1)
                ;
            else
                __assert_fail("n2 == n1 + 1", "src/execute_InstSlice.c", 240, __extension__ __PRETTY_FUNCTION__);
        }));
        ;
        ;
    } else {
        ;
    }
}


extern uint16_t * stack_restore (jq_state *jq){
    while (!stack_pop_will_free(&jq->stk, jq->fork_top))
        {
            if (stack_pop_will_free(&jq->stk, jq->stk_top)) {
                jv_free(stack_pop(jq));
            } else if (stack_pop_will_free(&jq->stk, jq->curr_frame)) {
                frame_pop(jq);
            } else {
                ;
            }
        }
    if (jq->fork_top == 0) {
        return 0;
    }
    struct forkpoint *fork = stack_block(&jq->stk, jq->fork_top);
    uint16_t *retaddr = fork->return_address;
    jq->stk_top = fork->saved_data_stack;
    jq->curr_frame = fork->saved_curr_frame;
    int path_len = fork->path_len;
    if (jv_get_kind(jq->path) == JV_KIND_ARRAY) {
        ((void)sizeof ((path_len >= 0) ? 1 : 0) , __extension__ ({
            if (path_len >= 0)
                ;
            else
                __assert_fail("path_len >= 0", "src/execute_InstSlice.c", 269, __extension__ __PRETTY_FUNCTION__);
        }));
        jq->path = jv_array_slice(jq->path, 0, path_len);
    } else {
        fork->path_len = 0;
    }
    ;
    ;
    jq->subexp_nest = fork->subexp_nest;
    jq->fork_top = stack_pop_block(&jq->stk, jq->fork_top, sizeof(struct forkpoint));
    return retaddr;
}


extern jv jq_next (jq_state *jq){
    ;
    uint16_t *pc = stack_restore(jq);
    ((void)sizeof ((pc) ? 1 : 0) , __extension__ ({
        if (pc)
            ;
        else
            __assert_fail("pc", "src/execute_InstSlice.c", 293, __extension__ __PRETTY_FUNCTION__);
    }));
    int raising;
    int backtracking = !jq->initial_execution;
    jq->initial_execution = 0;
    ((void)sizeof ((jv_get_kind(jq->error) == JV_KIND_NULL) ? 1 : 0) , __extension__ ({
        if (jv_get_kind(jq->error) == JV_KIND_NULL)
            ;
        else
            __assert_fail("jv_get_kind(jq->error) == JV_KIND_NULL", "src/execute_InstSlice.c", 299, __extension__ __PRETTY_FUNCTION__);
    }));
    while (1)
        {
            if (jq->halted) {
                ;
                return jv_invalid();
            }
            uint16_t opcode = *pc;
            raising = 0;
            if (jq->debug_trace_enabled) {
                dump_operation(frame_current(jq)->bc, pc);
                ;
                const struct opcode_description *opdesc = opcode_describe(opcode);
                stack_ptr param = 0;
                if (!backtracking) {
                    int stack_in = opdesc->stack_in;
                    if (stack_in == -1)
                        stack_in = pc[1];
                    param = jq->stk_top;
                    for (int i = 0; i < stack_in; i++) {
                        if (i != 0) {
                            ;
                            param = *stack_block_next(&jq->stk, param);
                        }
                        if (!param)
                            break;
                        ;
                        jv_dump(jv_copy(*(jv *)stack_block(&jq->stk, param)), JV_PRINT_REFCOUNT);
                    }
                    if (jq->debug_trace_enabled & JQ_DEBUG_TRACE_DETAIL) {
                        while ((param = *stack_block_next(&jq->stk, param)))
                            {
                                ;
                                jv_dump(jv_copy(*(jv *)stack_block(&jq->stk, param)), JV_PRINT_REFCOUNT);
                            }
                    }
                } else {
                    ;
                }
                ;
            }
            if (backtracking) {
                opcode = ((opcode) + NUM_OPCODES);
                backtracking = 0;
                raising = !jv_is_valid(jq->error);
            }
            pc++;
            switch (opcode) {
                ;
                ;
              case ERRORK:
                {
                    jv v = jv_array_get(jv_copy(frame_current(jq)->bc->constants), *pc++);
                    set_error(jq, jv_invalid_with_msg(v));
                    goto do_backtrack;
                }
              case LOADK:
                {
                    jv v = jv_array_get(jv_copy(frame_current(jq)->bc->constants), *pc++);
                    ((void)sizeof ((jv_is_valid(v)) ? 1 : 0) , __extension__ ({
                        if (jv_is_valid(v))
                            ;
                        else
                            __assert_fail("jv_is_valid(v)", "src/execute_InstSlice.c", 360, __extension__ __PRETTY_FUNCTION__);
                    }));
                    jv_free(stack_pop(jq));
                    stack_push(jq, v);
                    break;
                }
              case GENLABEL:
                {
                    stack_push(jq, (jv_object_set(jv_object(), (jv_string("__jq")), (jv_number(jq->next_label++)))));
                    break;
                }
              case DUP:
                {
                    jv v = stack_pop(jq);
                    stack_push(jq, jv_copy(v));
                    stack_push(jq, v);
                    break;
                }
              case DUPN:
                {
                    jv v = stack_popn(jq);
                    stack_push(jq, jv_copy(v));
                    stack_push(jq, v);
                    break;
                }
              case DUP2:
                {
                    jv keep = stack_pop(jq);
                    jv v = stack_pop(jq);
                    stack_push(jq, jv_copy(v));
                    stack_push(jq, keep);
                    stack_push(jq, v);
                    break;
                }
              case SUBEXP_BEGIN:
                {
                    jv v = stack_pop(jq);
                    stack_push(jq, jv_copy(v));
                    stack_push(jq, v);
                    jq->subexp_nest++;
                    break;
                }
              case SUBEXP_END:
                {
                    ((void)sizeof ((jq->subexp_nest > 0) ? 1 : 0) , __extension__ ({
                        if (jq->subexp_nest > 0)
                            ;
                        else
                            __assert_fail("jq->subexp_nest > 0", "src/execute_InstSlice.c", 403, __extension__ __PRETTY_FUNCTION__);
                    }));
                    jq->subexp_nest--;
                    jv a = stack_pop(jq);
                    jv b = stack_pop(jq);
                    stack_push(jq, a);
                    stack_push(jq, b);
                    break;
                }
              case PUSHK_UNDER:
                {
                    jv v = jv_array_get(jv_copy(frame_current(jq)->bc->constants), *pc++);
                    ((void)sizeof ((jv_is_valid(v)) ? 1 : 0) , __extension__ ({
                        if (jv_is_valid(v))
                            ;
                        else
                            __assert_fail("jv_is_valid(v)", "src/execute_InstSlice.c", 414, __extension__ __PRETTY_FUNCTION__);
                    }));
                    jv v2 = stack_pop(jq);
                    stack_push(jq, v);
                    stack_push(jq, v2);
                    break;
                }
              case POP:
                {
                    jv_free(stack_pop(jq));
                    break;
                }
              case APPEND:
                {
                    jv v = stack_pop(jq);
                    uint16_t level = *pc++;
                    uint16_t vidx = *pc++;
                    jv *var = frame_local_var(jq, vidx, level);
                    ((void)sizeof ((jv_get_kind(*var) == JV_KIND_ARRAY) ? 1 : 0) , __extension__ ({
                        if (jv_get_kind(*var) == JV_KIND_ARRAY)
                            ;
                        else
                            __assert_fail("jv_get_kind(*var) == JV_KIND_ARRAY", "src/execute_InstSlice.c", 431, __extension__ __PRETTY_FUNCTION__);
                    }));
                    *var = jv_array_append(*var, v);
                    break;
                }
              case INSERT:
                {
                    jv stktop = stack_pop(jq);
                    jv v = stack_pop(jq);
                    jv k = stack_pop(jq);
                    jv objv = stack_pop(jq);
                    ((void)sizeof ((jv_get_kind(objv) == JV_KIND_OBJECT) ? 1 : 0) , __extension__ ({
                        if (jv_get_kind(objv) == JV_KIND_OBJECT)
                            ;
                        else
                            __assert_fail("jv_get_kind(objv) == JV_KIND_OBJECT", "src/execute_InstSlice.c", 441, __extension__ __PRETTY_FUNCTION__);
                    }));
                    if (jv_get_kind(k) == JV_KIND_STRING) {
                        stack_push(jq, jv_object_set(objv, k, v));
                        stack_push(jq, stktop);
                    } else {
                        char errbuf[15];
                        set_error(jq, jv_invalid_with_msg(jv_string_fmt("Cannot use %s (%s) as object key", jv_kind_name(jv_get_kind(k)), jv_dump_string_trunc(jv_copy(k), errbuf, sizeof (errbuf)))));
                        ;
                        ;
                        ;
                        ;
                        goto do_backtrack;
                    }
                    break;
                }
              case ((RANGE) + NUM_OPCODES):
              case RANGE:
                {
                    uint16_t level = *pc++;
                    uint16_t v = *pc++;
                    jv *var = frame_local_var(jq, v, level);
                    jv max = stack_pop(jq);
                    if (raising) {
                        ;
                        goto do_backtrack;
                    }
                    if (jv_get_kind(*var) != JV_KIND_NUMBER || jv_get_kind(max) != JV_KIND_NUMBER) {
                        set_error(jq, jv_invalid_with_msg(jv_string_fmt("Range bounds must be numeric")));
                        ;
                        goto do_backtrack;
                    } else if (jv_number_value(*var) >= jv_number_value(max)) {
                        ;
                        goto do_backtrack;
                    } else {
                        jv curr = *var;
                        *var = jv_number(jv_number_value(*var) + 1);
                        struct stack_pos spos = stack_get_pos(jq);
                        stack_push(jq, max);
                        stack_save(jq, pc - 3, spos);
                        stack_push(jq, curr);
                    }
                    break;
                }
              case LOADV:
                {
                    uint16_t level = *pc++;
                    uint16_t v = *pc++;
                    jv *var = frame_local_var(jq, v, level);
                    if (jq->debug_trace_enabled) {
                        ;
                        jv_dump(jv_copy(*var), JV_PRINT_REFCOUNT);
                        ;
                    }
                    jv_free(stack_pop(jq));
                    stack_push(jq, jv_copy(*var));
                    break;
                }
              case LOADVN:
                {
                    uint16_t level = *pc++;
                    uint16_t v = *pc++;
                    jv *var = frame_local_var(jq, v, level);
                    if (jq->debug_trace_enabled) {
                        ;
                        jv_dump(jv_copy(*var), JV_PRINT_REFCOUNT);
                        ;
                    }
                    jv_free(stack_popn(jq));
                    stack_push(jq, *var);
                    var = frame_local_var(jq, v, level);
                    *var = jv_null();
                    break;
                }
              case STOREVN:
                stack_save(jq, pc - 1, stack_get_pos(jq));
              case STOREV:
                {
                    uint16_t level = *pc++;
                    uint16_t v = *pc++;
                    jv *var = frame_local_var(jq, v, level);
                    jv val = stack_pop(jq);
                    if (jq->debug_trace_enabled) {
                        ;
                        jv_dump(jv_copy(val), 0);
                        ;
                    }
                    ;
                    ;
                    break;
                }
              case ((STOREVN) + NUM_OPCODES):
                {
                    uint16_t level = *pc++;
                    uint16_t v = *pc++;
                    jv *var = frame_local_var(jq, v, level);
                    ;
                    *var = jv_null();
                    goto do_backtrack;
                    break;
                }
              case STORE_GLOBAL:
                {
                    jv val = jv_array_get(jv_copy(frame_current(jq)->bc->constants), *pc++);
                    ((void)sizeof ((jv_is_valid(val)) ? 1 : 0) , __extension__ ({
                        if (jv_is_valid(val))
                            ;
                        else
                            __assert_fail("jv_is_valid(val)", "src/execute_InstSlice.c", 554, __extension__ __PRETTY_FUNCTION__);
                    }));
                    uint16_t level = *pc++;
                    uint16_t v = *pc++;
                    jv *var = frame_local_var(jq, v, level);
                    if (jq->debug_trace_enabled) {
                        ;
                        jv_dump(jv_copy(val), 0);
                        ;
                    }
                    ;
                    ;
                    break;
                }
              case PATH_BEGIN:
                {
                    jv v = stack_pop(jq);
                    stack_push(jq, jq->path);
                    stack_save(jq, pc - 1, stack_get_pos(jq));
                    stack_push(jq, jv_number(jq->subexp_nest));
                    stack_push(jq, jq->value_at_path);
                    stack_push(jq, jv_copy(v));
                    jq->path = jv_array();
                    ;
                    jq->subexp_nest = 0;
                    break;
                }
              case PATH_END:
                {
                    jv v = stack_pop(jq);
                    if (!path_intact(jq, jv_copy(v))) {
                        char errbuf[30];
                        jv msg = jv_string_fmt("Invalid path expression with result %s", jv_dump_string_trunc(v, errbuf, sizeof (errbuf)));
                        set_error(jq, jv_invalid_with_msg(msg));
                        goto do_backtrack;
                    }
                    ;
                    jv old_value_at_path = stack_pop(jq);
                    int old_subexp_nest = (int)jv_number_value(stack_pop(jq));
                    jv path = jq->path;
                    jq->path = stack_pop(jq);
                    struct stack_pos spos = stack_get_pos(jq);
                    stack_push(jq, jv_copy(path));
                    stack_save(jq, pc - 1, spos);
                    stack_push(jq, path);
                    jq->subexp_nest = old_subexp_nest;
                    ;
                    ;
                    break;
                }
              case ((PATH_BEGIN) + NUM_OPCODES):
              case ((PATH_END) + NUM_OPCODES):
                {
                    ;
                    jq->path = stack_pop(jq);
                    goto do_backtrack;
                }
              case INDEX:
              case INDEX_OPT:
                {
                    jv t = stack_pop(jq);
                    jv k = stack_pop(jq);
                    if (!path_intact(jq, jv_copy(t))) {
                        char keybuf[15];
                        char objbuf[30];
                        jv msg = jv_string_fmt("Invalid path expression near attempt to access element %s of %s", jv_dump_string_trunc(k, keybuf, sizeof (keybuf)), jv_dump_string_trunc(t, objbuf, sizeof (objbuf)));
                        set_error(jq, jv_invalid_with_msg(msg));
                        goto do_backtrack;
                    }
                    jv v = jv_get(t, jv_copy(k));
                    if (jv_is_valid(v)) {
                        path_append(jq, k, jv_copy(v));
                        stack_push(jq, v);
                    } else {
                        ;
                        if (opcode == INDEX) {
                            set_error(jq, v);
                        } else {
                            ;
                        }
                        goto do_backtrack;
                    }
                    break;
                }
              case JUMP:
                {
                    uint16_t offset = *pc++;
                    pc += offset;
                    break;
                }
              case JUMP_F:
                {
                    uint16_t offset = *pc++;
                    jv t = stack_pop(jq);
                    jv_kind kind = jv_get_kind(t);
                    if (kind == JV_KIND_FALSE || kind == JV_KIND_NULL) {
                        pc += offset;
                    }
                    stack_push(jq, t);
                    break;
                }
              case EACH:
              case EACH_OPT:
                {
                    jv container = stack_pop(jq);
                    if (!path_intact(jq, jv_copy(container))) {
                        char errbuf[30];
                        jv msg = jv_string_fmt("Invalid path expression near attempt to iterate through %s", jv_dump_string_trunc(container, errbuf, sizeof (errbuf)));
                        set_error(jq, jv_invalid_with_msg(msg));
                        goto do_backtrack;
                    }
                    stack_push(jq, container);
                    stack_push(jq, jv_number(-1));
                }
              case ((EACH) + NUM_OPCODES):
              case ((EACH_OPT) + NUM_OPCODES):
                {
                    int idx = jv_number_value(stack_pop(jq));
                    jv container = stack_pop(jq);
                    int keep_going, is_last = 0;
                    jv key, value;
                    if (jv_get_kind(container) == JV_KIND_ARRAY) {
                        if (opcode == EACH || opcode == EACH_OPT) {
                            idx = 0;
                        } else
                            idx = idx + 1;
                        int len = jv_array_length(jv_copy(container));
                        keep_going = idx < len;
                        is_last = idx == len - 1;
                        if (keep_going) {
                            key = jv_number(idx);
                            value = jv_array_get(jv_copy(container), idx);
                        }
                    } else if (jv_get_kind(container) == JV_KIND_OBJECT) {
                        if (opcode == EACH || opcode == EACH_OPT) {
                            idx = jv_object_iter(container);
                        } else
                            idx = jv_object_iter_next(container, idx);
                        keep_going = jv_object_iter_valid(container, idx);
                        if (keep_going) {
                            key = jv_object_iter_key(container, idx);
                            value = jv_object_iter_value(container, idx);
                        }
                    } else {
                        ((void)sizeof ((opcode == EACH || opcode == EACH_OPT) ? 1 : 0) , __extension__ ({
                            if (opcode == EACH || opcode == EACH_OPT)
                                ;
                            else
                                __assert_fail("opcode == EACH || opcode == EACH_OPT", "src/execute_InstSlice.c", 707, __extension__ __PRETTY_FUNCTION__);
                        }));
                        if (opcode == EACH) {
                            char errbuf[15];
                            set_error(jq, jv_invalid_with_msg(jv_string_fmt("Cannot iterate over %s (%s)", jv_kind_name(jv_get_kind(container)), jv_dump_string_trunc(jv_copy(container), errbuf, sizeof (errbuf)))));
                        }
                        keep_going = 0;
                    }
                    if (!keep_going || raising) {
                        ;
                        goto do_backtrack;
                    } else if (is_last) {
                        ;
                        path_append(jq, key, jv_copy(value));
                        stack_push(jq, value);
                    } else {
                        struct stack_pos spos = stack_get_pos(jq);
                        stack_push(jq, container);
                        stack_push(jq, jv_number(idx));
                        stack_save(jq, pc - 1, spos);
                        path_append(jq, key, jv_copy(value));
                        stack_push(jq, value);
                    }
                    break;
                }
              do_backtrack:
              case BACKTRACK:
                {
                    pc = stack_restore(jq);
                    if (!pc) {
                        if (!jv_is_valid(jq->error)) {
                            jv error;
                            ;
                            return error;
                        }
                        return jv_invalid();
                    }
                    backtracking = 1;
                    break;
                }
              case TRY_BEGIN:
                stack_save(jq, pc - 1, stack_get_pos(jq));
                pc++;
                break;
              case TRY_END:
                stack_save(jq, pc - 1, stack_get_pos(jq));
                break;
              case ((TRY_BEGIN) + NUM_OPCODES):
                {
                    if (!raising) {
                        jv_free(stack_pop(jq));
                        goto do_backtrack;
                    }
                    jv e = jv_invalid_get_msg(jv_copy(jq->error));
                    if (!jv_is_valid(e) && jv_invalid_has_msg(jv_copy(e))) {
                        set_error(jq, e);
                        goto do_backtrack;
                    }
                    ;
                    uint16_t offset = *pc++;
                    jv_free(stack_pop(jq));
                    stack_push(jq, jv_invalid_get_msg(jq->error));
                    jq->error = jv_null();
                    pc += offset;
                    break;
                }
              case ((TRY_END) + NUM_OPCODES):
                if (raising)
                    set_error(jq, jv_invalid_with_msg(jv_copy(jq->error)));
                goto do_backtrack;
              case DESTRUCTURE_ALT:
              case FORK:
                {
                    stack_save(jq, pc - 1, stack_get_pos(jq));
                    pc++;
                    break;
                }
              case ((DESTRUCTURE_ALT) + NUM_OPCODES):
                {
                    if (jv_is_valid(jq->error)) {
                        jv_free(stack_pop(jq));
                        goto do_backtrack;
                    }
                    if (opcode != ((DESTRUCTURE_ALT) + NUM_OPCODES)) {
                        jv_free(stack_pop(jq));
                        stack_push(jq, jv_invalid_get_msg(jq->error));
                    } else {
                        ;
                    }
                    jq->error = jv_null();
                    uint16_t offset = *pc++;
                    pc += offset;
                    break;
                }
              case ((FORK) + NUM_OPCODES):
                {
                    if (raising)
                        goto do_backtrack;
                    ;
                    uint16_t offset = *pc++;
                    pc += offset;
                    break;
                }
              case CALL_BUILTIN:
                {
                    int nargs = *pc++;
                    struct cfunction *function = &frame_current(jq)->bc->globals->cfunctions[*pc++];
                    jv in[4];
                    for (int i = 0; i < nargs; ++i)
                        in[i] = stack_pop(jq);
                    jv top;
                    switch (function->nargs) {
                      case 1:
                        top = function->fptr.a1(jq, in[0]);
                        break;
                        ;
                      case 2:
                        top = function->fptr.a2(jq, in[0], in[1]);
                        break;
                        ;
                      case 3:
                        top = function->fptr.a3(jq, in[0], in[1], in[2]);
                        break;
                        ;
                      case 4:
                        top = function->fptr.a4(jq, in[0], in[1], in[2], in[3]);
                        break;
                        ;
                        ;
                    }
                    if (!jv_is_valid(top)) {
                        if (jv_invalid_has_msg(jv_copy(top)))
                            set_error(jq, top);
                        goto do_backtrack;
                    }
                    stack_push(jq, top);
                    break;
                }
              case TAIL_CALL_JQ:
              case CALL_JQ:
                {
                    jv input = stack_pop(jq);
                    uint16_t nclosures = *pc++;
                    uint16_t *retaddr = pc + 2 + nclosures * 2;
                    stack_ptr retdata = jq->stk_top;
                    struct frame *new_frame;
                    struct closure cl = make_closure(jq, pc);
                    if (opcode == TAIL_CALL_JQ) {
                        retaddr = frame_current(jq)->retaddr;
                        retdata = frame_current(jq)->retdata;
                        frame_pop(jq);
                    }
                    new_frame = frame_push(jq, cl, pc + 2, nclosures);
                    new_frame->retdata = retdata;
                    new_frame->retaddr = retaddr;
                    pc = new_frame->bc->code;
                    stack_push(jq, input);
                    break;
                }
              case RET:
                {
                    jv value = stack_pop(jq);
                    ((void)sizeof ((jq->stk_top == frame_current(jq)->retdata) ? 1 : 0) , __extension__ ({
                        if (jq->stk_top == frame_current(jq)->retdata)
                            ;
                        else
                            __assert_fail("jq->stk_top == frame_current(jq)->retdata", "src/execute_InstSlice.c", 913, __extension__ __PRETTY_FUNCTION__);
                    }));
                    uint16_t *retaddr = frame_current(jq)->retaddr;
                    if (retaddr) {
                        pc = retaddr;
                        frame_pop(jq);
                    } else {
                        struct stack_pos spos = stack_get_pos(jq);
                        stack_push(jq, jv_null());
                        stack_save(jq, pc - 1, spos);
                        return value;
                    }
                    stack_push(jq, value);
                    break;
                }
            }
        }
}


