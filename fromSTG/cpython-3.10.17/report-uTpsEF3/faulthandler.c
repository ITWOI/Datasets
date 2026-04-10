static uintptr_t stack_overflow (uintptr_t min_sp, uintptr_t max_sp, size_t *depth){
    volatile unsigned char buffer[4096];
    uintptr_t sp = (uintptr_t)&buffer;
    ;
    if (sp < min_sp || max_sp < sp)
        return sp;
    ;
    ;
    return stack_overflow(min_sp, max_sp, depth);
}


static PyObject * faulthandler_stack_overflow (PyObject *self, PyObject *_unused_ignored __attribute__((unused))){
    size_t depth, size;
    uintptr_t sp = (uintptr_t)&depth;
    uintptr_t stop, lower_limit, upper_limit;
    ;
    ;
    if ((100 * 1024 * 1024) <= sp) {
        lower_limit = sp - (100 * 1024 * 1024);
    } else {
        lower_limit = 0;
    }
    if ((18446744073709551615UL) - (100 * 1024 * 1024) >= sp) {
        upper_limit = sp + (100 * 1024 * 1024);
    } else {
        upper_limit = (18446744073709551615UL);
    }
    stop = stack_overflow(lower_limit, upper_limit, &depth);
    ;
    ;
    return ((void *)0);
}


