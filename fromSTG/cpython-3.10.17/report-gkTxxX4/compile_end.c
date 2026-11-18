#include "header_func.h"
#include "object.h"
static inline int is_bit_set_in_table (uint32_t *table, int bitindex){
    uint32_t word = table[bitindex >> 5];
    return (word >> (bitindex & 31)) & 1;
}
static inline int is_relative_jump (struct instr *i){
    return is_bit_set_in_table(_PyOpcode_RelativeJump, i->i_opcode);
}
static inline int is_jump (struct instr *i){
    return is_bit_set_in_table(_PyOpcode_Jump, i->i_opcode);
}
extern PyObject * _Py_Mangle (PyObject *privateobj, PyObject *ident){
    PyObject *result;
    size_t nlen, plen, ipriv;
    Py_UCS4 maxchar;
    if (privateobj == ((void *)0) || !PyType_HasFeature((((PyObject *)(privateobj))->ob_type), (1UL << 28)) || (((void)(0)) , ((void)(0)) , (Py_UCS4)((((void)(0)) , ((void)(0)) , ((PyASCIIObject *)((ident)))->state.kind) == PyUnicode_1BYTE_KIND ? ((const Py_UCS1 *)((((void)(0)) , (((PyASCIIObject *)((ident)))->state.compact) ? ((((void)(0)) , ((void)(0)) , ((PyASCIIObject *)(ident))->state.ascii) ? ((void *)((PyASCIIObject *)((ident)) + 1)) : ((void *)((PyCompactUnicodeObject *)((ident)) + 1))) : (((void)(0)) , ((((PyUnicodeObject *)((ident)))->data.any))))))[(0)] : ((((void)(0)) , ((void)(0)) , ((PyASCIIObject *)((ident)))->state.kind) == PyUnicode_2BYTE_KIND ? ((const Py_UCS2 *)((((void)(0)) , (((PyASCIIObject *)((ident)))->state.compact) ? ((((void)(0)) , ((void)(0)) , ((PyASCIIObject *)(ident))->state.ascii) ? ((void *)((PyASCIIObject *)((ident)) + 1)) : ((void *)((PyCompactUnicodeObject *)((ident)) + 1))) : (((void)(0)) , ((((PyUnicodeObject *)((ident)))->data.any))))))[(0)] : ((const Py_UCS4 *)((((void)(0)) , (((PyASCIIObject *)((ident)))->state.compact) ? ((((void)(0)) , ((void)(0)) , ((PyASCIIObject *)(ident))->state.ascii) ? ((void *)((PyASCIIObject *)((ident)) + 1)) : ((void *)((PyCompactUnicodeObject *)((ident)) + 1))) : (((void)(0)) , ((((PyUnicodeObject *)((ident)))->data.any))))))[(0)]))) != '_' || (((void)(0)) , ((void)(0)) , (Py_UCS4)((((void)(0)) , ((void)(0)) , ((PyASCIIObject *)((ident)))->state.kind) == PyUnicode_1BYTE_KIND ? ((const Py_UCS1 *)((((void)(0)) , (((PyASCIIObject *)((ident)))->state.compact) ? ((((void)(0)) , ((void)(0)) , ((PyASCIIObject *)(ident))->state.ascii) ? ((void *)((PyASCIIObject *)((ident)) + 1)) : ((void *)((PyCompactUnicodeObject *)((ident)) + 1))) : (((void)(0)) , ((((PyUnicodeObject *)((ident)))->data.any))))))[(1)] : ((((void)(0)) , ((void)(0)) , ((PyASCIIObject *)((ident)))->state.kind) == PyUnicode_2BYTE_KIND ? ((const Py_UCS2 *)((((void)(0)) , (((PyASCIIObject *)((ident)))->state.compact) ? ((((void)(0)) , ((void)(0)) , ((PyASCIIObject *)(ident))->state.ascii) ? ((void *)((PyASCIIObject *)((ident)) + 1)) : ((void *)((PyCompactUnicodeObject *)((ident)) + 1))) : (((void)(0)) , ((((PyUnicodeObject *)((ident)))->data.any))))))[(1)] : ((const Py_UCS4 *)((((void)(0)) , (((PyASCIIObject *)((ident)))->state.compact) ? ((((void)(0)) , ((void)(0)) , ((PyASCIIObject *)(ident))->state.ascii) ? ((void *)((PyASCIIObject *)((ident)) + 1)) : ((void *)((PyCompactUnicodeObject *)((ident)) + 1))) : (((void)(0)) , ((((PyUnicodeObject *)((ident)))->data.any))))))[(1)]))) != '_') {
        _Py_INCREF(((PyObject *)(ident)));
        return ident;
    }
    nlen = (((void)(0)) , ((void)(0)) , ((PyASCIIObject *)(ident))->length);
    plen = (((void)(0)) , ((void)(0)) , ((PyASCIIObject *)(privateobj))->length);
    if (((((void)(0)) , ((void)(0)) , (Py_UCS4)((((void)(0)) , ((void)(0)) , ((PyASCIIObject *)((ident)))->state.kind) == PyUnicode_1BYTE_KIND ? ((const Py_UCS1 *)((((void)(0)) , (((PyASCIIObject *)((ident)))->state.compact) ? ((((void)(0)) , ((void)(0)) , ((PyASCIIObject *)(ident))->state.ascii) ? ((void *)((PyASCIIObject *)((ident)) + 1)) : ((void *)((PyCompactUnicodeObject *)((ident)) + 1))) : (((void)(0)) , ((((PyUnicodeObject *)((ident)))->data.any))))))[(nlen - 1)] : ((((void)(0)) , ((void)(0)) , ((PyASCIIObject *)((ident)))->state.kind) == PyUnicode_2BYTE_KIND ? ((const Py_UCS2 *)((((void)(0)) , (((PyASCIIObject *)((ident)))->state.compact) ? ((((void)(0)) , ((void)(0)) , ((PyASCIIObject *)(ident))->state.ascii) ? ((void *)((PyASCIIObject *)((ident)) + 1)) : ((void *)((PyCompactUnicodeObject *)((ident)) + 1))) : (((void)(0)) , ((((PyUnicodeObject *)((ident)))->data.any))))))[(nlen - 1)] : ((const Py_UCS4 *)((((void)(0)) , (((PyASCIIObject *)((ident)))->state.compact) ? ((((void)(0)) , ((void)(0)) , ((PyASCIIObject *)(ident))->state.ascii) ? ((void *)((PyASCIIObject *)((ident)) + 1)) : ((void *)((PyCompactUnicodeObject *)((ident)) + 1))) : (((void)(0)) , ((((PyUnicodeObject *)((ident)))->data.any))))))[(nlen - 1)]))) == '_' && (((void)(0)) , ((void)(0)) , (Py_UCS4)((((void)(0)) , ((void)(0)) , ((PyASCIIObject *)((ident)))->state.kind) == PyUnicode_1BYTE_KIND ? ((const Py_UCS1 *)((((void)(0)) , (((PyASCIIObject *)((ident)))->state.compact) ? ((((void)(0)) , ((void)(0)) , ((PyASCIIObject *)(ident))->state.ascii) ? ((void *)((PyASCIIObject *)((ident)) + 1)) : ((void *)((PyCompactUnicodeObject *)((ident)) + 1))) : (((void)(0)) , ((((PyUnicodeObject *)((ident)))->data.any))))))[(nlen - 2)] : ((((void)(0)) , ((void)(0)) , ((PyASCIIObject *)((ident)))->state.kind) == PyUnicode_2BYTE_KIND ? ((const Py_UCS2 *)((((void)(0)) , (((PyASCIIObject *)((ident)))->state.compact) ? ((((void)(0)) , ((void)(0)) , ((PyASCIIObject *)(ident))->state.ascii) ? ((void *)((PyASCIIObject *)((ident)) + 1)) : ((void *)((PyCompactUnicodeObject *)((ident)) + 1))) : (((void)(0)) , ((((PyUnicodeObject *)((ident)))->data.any))))))[(nlen - 2)] : ((const Py_UCS4 *)((((void)(0)) , (((PyASCIIObject *)((ident)))->state.compact) ? ((((void)(0)) , ((void)(0)) , ((PyASCIIObject *)(ident))->state.ascii) ? ((void *)((PyASCIIObject *)((ident)) + 1)) : ((void *)((PyCompactUnicodeObject *)((ident)) + 1))) : (((void)(0)) , ((((PyUnicodeObject *)((ident)))->data.any))))))[(nlen - 2)]))) == '_') || PyUnicode_FindChar(ident, '.', 0, nlen, 1) != -1) {
        _Py_INCREF(((PyObject *)(ident)));
        return ident;
    }
    ipriv = 0;
    while ((((void)(0)) , ((void)(0)) , (Py_UCS4)((((void)(0)) , ((void)(0)) , ((PyASCIIObject *)((privateobj)))->state.kind) == PyUnicode_1BYTE_KIND ? ((const Py_UCS1 *)((((void)(0)) , (((PyASCIIObject *)((privateobj)))->state.compact) ? ((((void)(0)) , ((void)(0)) , ((PyASCIIObject *)(privateobj))->state.ascii) ? ((void *)((PyASCIIObject *)((privateobj)) + 1)) : ((void *)((PyCompactUnicodeObject *)((privateobj)) + 1))) : (((void)(0)) , ((((PyUnicodeObject *)((privateobj)))->data.any))))))[(ipriv)] : ((((void)(0)) , ((void)(0)) , ((PyASCIIObject *)((privateobj)))->state.kind) == PyUnicode_2BYTE_KIND ? ((const Py_UCS2 *)((((void)(0)) , (((PyASCIIObject *)((privateobj)))->state.compact) ? ((((void)(0)) , ((void)(0)) , ((PyASCIIObject *)(privateobj))->state.ascii) ? ((void *)((PyASCIIObject *)((privateobj)) + 1)) : ((void *)((PyCompactUnicodeObject *)((privateobj)) + 1))) : (((void)(0)) , ((((PyUnicodeObject *)((privateobj)))->data.any))))))[(ipriv)] : ((const Py_UCS4 *)((((void)(0)) , (((PyASCIIObject *)((privateobj)))->state.compact) ? ((((void)(0)) , ((void)(0)) , ((PyASCIIObject *)(privateobj))->state.ascii) ? ((void *)((PyASCIIObject *)((privateobj)) + 1)) : ((void *)((PyCompactUnicodeObject *)((privateobj)) + 1))) : (((void)(0)) , ((((PyUnicodeObject *)((privateobj)))->data.any))))))[(ipriv)]))) == '_')
        ipriv++;
    if (ipriv == plen) {
        _Py_INCREF(((PyObject *)(ident)));
        return ident;
    }
    plen -= ipriv;
    if (plen + nlen >= ((Py_ssize_t)(((size_t)-1) >> 1)) - 1) {
        ;
        return ((void *)0);
    }
    maxchar = (((void)(0)) , ((((void)(0)) , ((void)(0)) , ((PyASCIIObject *)ident)->state.ascii) ? (127) : ((((void)(0)) , ((void)(0)) , ((PyASCIIObject *)(ident))->state.kind) == PyUnicode_1BYTE_KIND ? (255U) : ((((void)(0)) , ((void)(0)) , ((PyASCIIObject *)(ident))->state.kind) == PyUnicode_2BYTE_KIND ? (65535U) : (1114111U)))));
    if ((((void)(0)) , ((((void)(0)) , ((void)(0)) , ((PyASCIIObject *)privateobj)->state.ascii) ? (127) : ((((void)(0)) , ((void)(0)) , ((PyASCIIObject *)(privateobj))->state.kind) == PyUnicode_1BYTE_KIND ? (255U) : ((((void)(0)) , ((void)(0)) , ((PyASCIIObject *)(privateobj))->state.kind) == PyUnicode_2BYTE_KIND ? (65535U) : (1114111U))))) > maxchar)
        maxchar = (((void)(0)) , ((((void)(0)) , ((void)(0)) , ((PyASCIIObject *)privateobj)->state.ascii) ? (127) : ((((void)(0)) , ((void)(0)) , ((PyASCIIObject *)(privateobj))->state.kind) == PyUnicode_1BYTE_KIND ? (255U) : ((((void)(0)) , ((void)(0)) , ((PyASCIIObject *)(privateobj))->state.kind) == PyUnicode_2BYTE_KIND ? (65535U) : (1114111U)))));
    result = PyUnicode_New(1 + nlen + plen, maxchar);
    if (!result)
        return 0;
    do {
        switch (((((void)(0)) , ((void)(0)) , ((PyASCIIObject *)(result))->state.kind))) {
          case PyUnicode_1BYTE_KIND:
            {
                ((Py_UCS1 *)((((void)(0)) , (((PyASCIIObject *)(result))->state.compact) ? ((((void)(0)) , ((void)(0)) , ((PyASCIIObject *)result)->state.ascii) ? ((void *)((PyASCIIObject *)(result) + 1)) : ((void *)((PyCompactUnicodeObject *)(result) + 1))) : (((void)(0)) , ((((PyUnicodeObject *)(result))->data.any))))))[(0)] = (Py_UCS1)('_');
                break;
            }
          case PyUnicode_2BYTE_KIND:
            {
                ((Py_UCS2 *)((((void)(0)) , (((PyASCIIObject *)(result))->state.compact) ? ((((void)(0)) , ((void)(0)) , ((PyASCIIObject *)result)->state.ascii) ? ((void *)((PyASCIIObject *)(result) + 1)) : ((void *)((PyCompactUnicodeObject *)(result) + 1))) : (((void)(0)) , ((((PyUnicodeObject *)(result))->data.any))))))[(0)] = (Py_UCS2)('_');
                break;
            }
          default:
            {
                ((void)(0));
                ((Py_UCS4 *)((((void)(0)) , (((PyASCIIObject *)(result))->state.compact) ? ((((void)(0)) , ((void)(0)) , ((PyASCIIObject *)result)->state.ascii) ? ((void *)((PyASCIIObject *)(result) + 1)) : ((void *)((PyCompactUnicodeObject *)(result) + 1))) : (((void)(0)) , ((((PyUnicodeObject *)(result))->data.any))))))[(0)] = (Py_UCS4)('_');
            }
        }
    } while (0);
    if (PyUnicode_CopyCharacters(result, 1, privateobj, ipriv, plen) < 0) {
        _Py_DECREF(((PyObject *)(result)));
        return ((void *)0);
    }
    if (PyUnicode_CopyCharacters(result, plen + 1, ident, 0, nlen) < 0) {
        _Py_DECREF(((PyObject *)(result)));
        return ((void *)0);
    }
    ;
    return result;
}
static PyObject * list2dict (PyObject *list){
    Py_ssize_t i, n;
    PyObject *v, *k;
    PyObject *dict = PyDict_New();
    if (!dict)
        return ((void *)0);
    n = PyList_Size(list);
    for (i = 0; i < n; i++) {
        v = PyLong_FromSsize_t(i);
        if (!v) {
            _Py_DECREF(((PyObject *)(dict)));
            return ((void *)0);
        }
        k = ((((void)(0)) , (PyListObject *)(list))->ob_item[i]);
        if (PyDict_SetItem(dict, k, v) < 0) {
            _Py_DECREF(((PyObject *)(v)));
            _Py_DECREF(((PyObject *)(dict)));
            return ((void *)0);
        }
        _Py_DECREF(((PyObject *)(v)));
    }
    return dict;
}
static PyObject * dictbytype (PyObject *src, int scope_type, int flag, Py_ssize_t offset){
    Py_ssize_t i = offset, scope, num_keys, key_i;
    PyObject *k, *v, *dest = PyDict_New();
    PyObject *sorted_keys;
    if (dest == ((void *)0))
        return ((void *)0);
    sorted_keys = PyDict_Keys(src);
    if (sorted_keys == ((void *)0))
        return ((void *)0);
    if (PyList_Sort(sorted_keys) != 0) {
        _Py_DECREF(((PyObject *)(sorted_keys)));
        return ((void *)0);
    }
    num_keys = (((PyVarObject *)((((void)(0)) , (PyListObject *)(sorted_keys))))->ob_size);
    for (key_i = 0; key_i < num_keys; key_i++) {
        long vi;
        k = ((((void)(0)) , (PyListObject *)(sorted_keys))->ob_item[key_i]);
        v = PyDict_GetItemWithError(src, k);
        vi = PyLong_AsLong(v);
        scope = (vi >> 11) & (1 | 2 | 2 << 1 | 2 << 2);
        if (scope == scope_type || vi & flag) {
            PyObject *item = PyLong_FromSsize_t(i);
            if (item == ((void *)0)) {
                _Py_DECREF(((PyObject *)(sorted_keys)));
                _Py_DECREF(((PyObject *)(dest)));
                return ((void *)0);
            }
            i++;
            if (PyDict_SetItem(dest, k, item) < 0) {
                _Py_DECREF(((PyObject *)(sorted_keys)));
                _Py_DECREF(((PyObject *)(item)));
                _Py_DECREF(((PyObject *)(dest)));
                return ((void *)0);
            }
            _Py_DECREF(((PyObject *)(item)));
        }
    }
    _Py_DECREF(((PyObject *)(sorted_keys)));
    return dest;
}
static void compiler_unit_free (struct compiler_unit *u){
    basicblock *b, *next;
    b = u->u_blocks;
    while (b != ((void *)0))
        {
            ;
            next = b->b_list;
            b = next;
        }
    do {
        PyObject *_py_tmp = ((PyObject *)(u->u_ste));
        if (_py_tmp != ((void *)0)) {
            (u->u_ste) = ((void *)0);
            _Py_DECREF(((PyObject *)(_py_tmp)));
        }
    } while (0);
    do {
        PyObject *_py_tmp = ((PyObject *)(u->u_name));
        if (_py_tmp != ((void *)0)) {
            (u->u_name) = ((void *)0);
            _Py_DECREF(((PyObject *)(_py_tmp)));
        }
    } while (0);
    do {
        PyObject *_py_tmp = ((PyObject *)(u->u_qualname));
        if (_py_tmp != ((void *)0)) {
            (u->u_qualname) = ((void *)0);
            _Py_DECREF(((PyObject *)(_py_tmp)));
        }
    } while (0);
    do {
        PyObject *_py_tmp = ((PyObject *)(u->u_consts));
        if (_py_tmp != ((void *)0)) {
            (u->u_consts) = ((void *)0);
            _Py_DECREF(((PyObject *)(_py_tmp)));
        }
    } while (0);
    do {
        PyObject *_py_tmp = ((PyObject *)(u->u_names));
        if (_py_tmp != ((void *)0)) {
            (u->u_names) = ((void *)0);
            _Py_DECREF(((PyObject *)(_py_tmp)));
        }
    } while (0);
    do {
        PyObject *_py_tmp = ((PyObject *)(u->u_varnames));
        if (_py_tmp != ((void *)0)) {
            (u->u_varnames) = ((void *)0);
            _Py_DECREF(((PyObject *)(_py_tmp)));
        }
    } while (0);
    do {
        PyObject *_py_tmp = ((PyObject *)(u->u_freevars));
        if (_py_tmp != ((void *)0)) {
            (u->u_freevars) = ((void *)0);
            _Py_DECREF(((PyObject *)(_py_tmp)));
        }
    } while (0);
    do {
        PyObject *_py_tmp = ((PyObject *)(u->u_cellvars));
        if (_py_tmp != ((void *)0)) {
            (u->u_cellvars) = ((void *)0);
            _Py_DECREF(((PyObject *)(_py_tmp)));
        }
    } while (0);
    do {
        PyObject *_py_tmp = ((PyObject *)(u->u_private));
        if (_py_tmp != ((void *)0)) {
            (u->u_private) = ((void *)0);
            _Py_DECREF(((PyObject *)(_py_tmp)));
        }
    } while (0);
}
static int compiler_enter_scope (struct compiler *c, identifier name, int scope_type, void *key, int lineno){
    struct compiler_unit *u;
    basicblock *block;
    u = (struct compiler_unit *)PyObject_Calloc(1, sizeof(struct compiler_unit));
    if (!u) {
        ;
        return 0;
    }
    u->u_scope_type = scope_type;
    u->u_argcount = 0;
    u->u_posonlyargcount = 0;
    u->u_kwonlyargcount = 0;
    u->u_ste = PySymtable_Lookup(c->c_st, key);
    if (!u->u_ste) {
        compiler_unit_free(u);
        return 0;
    }
    _Py_INCREF(((PyObject *)(name)));
    u->u_name = name;
    u->u_varnames = list2dict(u->u_ste->ste_varnames);
    u->u_cellvars = dictbytype(u->u_ste->ste_symbols, 5, 0, 0);
    if (!u->u_varnames || !u->u_cellvars) {
        compiler_unit_free(u);
        return 0;
    }
    if (u->u_ste->ste_needs_class_closure) {
        static _Py_Identifier PyId___class__ = {.string = "__class__", .index = -1};
        PyObject *name;
        int res;
        name = _PyUnicode_FromId(&PyId___class__);
        if (!name) {
            compiler_unit_free(u);
            return 0;
        }
        res = PyDict_SetItem(u->u_cellvars, name, _PyLong_GetZero());
        if (res < 0) {
            compiler_unit_free(u);
            return 0;
        }
    }
    u->u_freevars = dictbytype(u->u_ste->ste_symbols, 4, 2 << 5, (((void)(0)) , ((PyDictObject *)u->u_cellvars)->ma_used));
    if (!u->u_freevars) {
        compiler_unit_free(u);
        return 0;
    }
    u->u_blocks = ((void *)0);
    u->u_nfblocks = 0;
    u->u_firstlineno = lineno;
    u->u_lineno = 0;
    u->u_col_offset = 0;
    u->u_end_lineno = 0;
    u->u_end_col_offset = 0;
    u->u_consts = PyDict_New();
    if (!u->u_consts) {
        compiler_unit_free(u);
        return 0;
    }
    u->u_names = PyDict_New();
    if (!u->u_names) {
        compiler_unit_free(u);
        return 0;
    }
    u->u_private = ((void *)0);
    if (c->u) {
        PyObject *capsule = PyCapsule_New(c->u, "compile.c compiler unit", ((void *)0));
        if (!capsule || PyList_Append(c->c_stack, capsule) < 0) {
            _Py_XDECREF(((PyObject *)(capsule)));
            compiler_unit_free(u);
            return 0;
        }
        _Py_DECREF(((PyObject *)(capsule)));
        u->u_private = c->u->u_private;
        _Py_XINCREF(((PyObject *)(u->u_private)));
    }
    c->u = u;
    c->c_nestlevel++;
    block = compiler_new_block(c);
    if (block == ((void *)0))
        return 0;
    c->u->u_curblock = block;
    if (u->u_scope_type != COMPILER_SCOPE_MODULE) {
        if (!compiler_set_qualname(c))
            return 0;
    }
    return 1;
}
static void compiler_exit_scope (struct compiler *c){
    PyObject *exc_type, *exc_val, *exc_tb;
    c->c_nestlevel--;
    compiler_unit_free(c->u);
    Py_ssize_t n = (((PyVarObject *)((((void)(0)) , (PyListObject *)(c->c_stack))))->ob_size) - 1;
    if (n >= 0) {
        PyObject *capsule = ((((void)(0)) , (PyListObject *)(c->c_stack))->ob_item[n]);
        c->u = (struct compiler_unit *)PyCapsule_GetPointer(capsule, "compile.c compiler unit");
    } else {
        c->u = ((void *)0);
    }
    ;
}
static int compiler_set_qualname (struct compiler *c){
    static _Py_Identifier dot = {.string = ".", .index = -1};
    static _Py_Identifier dot_locals = {.string = ".<locals>", .index = -1};
    Py_ssize_t stack_size;
    struct compiler_unit *u = c->u;
    PyObject *name, *base, *dot_str, *dot_locals_str;
    base = ((void *)0);
    stack_size = (((PyVarObject *)((((void)(0)) , (PyListObject *)(c->c_stack))))->ob_size);
    if (stack_size > 1) {
        int scope, force_global = 0;
        struct compiler_unit *parent;
        PyObject *mangled, *capsule;
        capsule = ((((void)(0)) , (PyListObject *)(c->c_stack))->ob_item[stack_size - 1]);
        parent = (struct compiler_unit *)PyCapsule_GetPointer(capsule, "compile.c compiler unit");
        if (u->u_scope_type == COMPILER_SCOPE_FUNCTION || u->u_scope_type == COMPILER_SCOPE_ASYNC_FUNCTION || u->u_scope_type == COMPILER_SCOPE_CLASS) {
            ;
            mangled = _Py_Mangle(parent->u_private, u->u_name);
            if (!mangled)
                return 0;
            scope = _PyST_GetScope(parent->u_ste, mangled);
            _Py_DECREF(((PyObject *)(mangled)));
            if (scope == 2)
                force_global = 1;
        }
        if (!force_global) {
            if (parent->u_scope_type == COMPILER_SCOPE_FUNCTION || parent->u_scope_type == COMPILER_SCOPE_ASYNC_FUNCTION || parent->u_scope_type == COMPILER_SCOPE_LAMBDA) {
                dot_locals_str = _PyUnicode_FromId(&dot_locals);
                if (dot_locals_str == ((void *)0))
                    return 0;
                base = PyUnicode_Concat(parent->u_qualname, dot_locals_str);
                if (base == ((void *)0))
                    return 0;
            } else {
                _Py_INCREF(((PyObject *)(parent->u_qualname)));
                base = parent->u_qualname;
            }
        }
    }
    if (base != ((void *)0)) {
        dot_str = _PyUnicode_FromId(&dot);
        if (dot_str == ((void *)0)) {
            _Py_DECREF(((PyObject *)(base)));
            return 0;
        }
        name = PyUnicode_Concat(base, dot_str);
        _Py_DECREF(((PyObject *)(base)));
        if (name == ((void *)0))
            return 0;
        if (name == ((void *)0))
            return 0;
    } else {
        _Py_INCREF(((PyObject *)(u->u_name)));
        name = u->u_name;
    }
    u->u_qualname = name;
    return 1;
}
static basicblock * compiler_new_block (struct compiler *c){
    basicblock *b;
    struct compiler_unit *u;
    u = c->u;
    b = (basicblock *)PyObject_Calloc(1, sizeof(basicblock));
    if (b == ((void *)0)) {
        ;
        return ((void *)0);
    }
    b->b_list = u->u_blocks;
    u->u_blocks = b;
    return b;
}
static basicblock * compiler_next_block (struct compiler *c){
    basicblock *block = compiler_new_block(c);
    if (block == ((void *)0))
        return ((void *)0);
    c->u->u_curblock->b_next = block;
    c->u->u_curblock = block;
    return block;
}
static basicblock * compiler_use_next_block (struct compiler *c, basicblock *block){
    ;
    c->u->u_curblock->b_next = block;
    c->u->u_curblock = block;
    return block;
}
static basicblock * compiler_copy_block (struct compiler *c, basicblock *block){
    ;
    basicblock *result = compiler_new_block(c);
    if (result == ((void *)0)) {
        return ((void *)0);
    }
    for (int i = 0; i < block->b_iused; i++) {
        int n = compiler_next_instr(result);
        if (n < 0) {
            return ((void *)0);
        }
        ;
    }
    result->b_exit = block->b_exit;
    result->b_nofallthrough = 1;
    return result;
}
static int compiler_next_instr (basicblock *b){
    ;
    if (b->b_instr == ((void *)0)) {
        b->b_instr = (struct instr *)PyObject_Calloc(16, sizeof(struct instr));
        if (b->b_instr == ((void *)0)) {
            ;
            return -1;
        }
        b->b_ialloc = 16;
    } else if (b->b_iused == b->b_ialloc) {
        struct instr *tmp;
        size_t oldsize, newsize;
        oldsize = b->b_ialloc * sizeof(struct instr);
        newsize = oldsize << 1;
        if (oldsize > ((18446744073709551615UL) >> 1)) {
            ;
            return -1;
        }
        if (newsize == 0) {
            ;
            return -1;
        }
        b->b_ialloc <<= 1;
        tmp = (struct instr *)PyObject_Realloc((void *)b->b_instr, newsize);
        if (tmp == ((void *)0)) {
            ;
            return -1;
        }
        b->b_instr = tmp;
    }
    return b->b_iused++;
}
static int stack_effect (int opcode, int oparg, int jump){
    switch (opcode) {
      case 9:
      case 144:
        return 0;
      case 1:
        return -1;
      case 2:
      case 3:
      case 6:
        return 0;
      case 4:
        return 1;
      case 5:
        return 2;
      case 10:
      case 11:
      case 12:
      case 15:
        return 0;
      case 146:
      case 145:
        return -1;
      case 147:
        return -2;
      case 19:
      case 20:
      case 16:
      case 22:
      case 23:
      case 24:
      case 25:
      case 26:
      case 27:
        return -1;
      case 28:
      case 29:
        return -1;
      case 55:
      case 56:
      case 57:
      case 17:
      case 59:
        return -1;
      case 60:
        return -3;
      case 61:
        return -2;
      case 62:
      case 63:
      case 64:
      case 65:
      case 66:
        return -1;
      case 67:
        return -1;
      case 68:
        return 0;
      case 70:
        return -1;
      case 71:
        return 1;
      case 75:
      case 76:
      case 77:
      case 78:
      case 79:
        return -1;
      case 143:
        return jump ? 6 : 1;
      case 83:
        return -1;
      case 84:
        return -1;
      case 85:
        return 0;
      case 86:
        return 0;
      case 72:
        return -1;
      case 87:
        return 0;
      case 89:
        return -3;
      case 90:
        return -1;
      case 91:
        return 0;
      case 92:
        return oparg - 1;
      case 94:
        return (oparg & 255) + (oparg >> 8);
      case 93:
        return jump > 0 ? -1 : 1;
      case 95:
        return -2;
      case 96:
        return -1;
      case 97:
        return -1;
      case 98:
        return 0;
      case 100:
        return 1;
      case 101:
        return 1;
      case 102:
      case 103:
      case 104:
      case 157:
        return 1 - oparg;
      case 105:
        return 1 - 2 * oparg;
      case 156:
        return -oparg;
      case 106:
        return 0;
      case 107:
      case 117:
      case 118:
        return -1;
      case 121:
        return -2;
      case 108:
        return -1;
      case 109:
        return 1;
      case 110:
      case 113:
        return 0;
      case 112:
      case 111:
        return jump ? 0 : -1;
      case 114:
      case 115:
        return -1;
      case 116:
        return 1;
      case 122:
        return jump ? 6 : 0;
      case 119:
        return -3;
      case 49:
        return 1;
      case 124:
        return 1;
      case 125:
        return -1;
      case 126:
        return 0;
      case 130:
        return -oparg;
      case 131:
        return -oparg;
      case 161:
        return -oparg - 1;
      case 141:
        return -oparg - 1;
      case 142:
        return -1 - ((oparg & 1) != 0);
      case 132:
        return -1 - ((oparg & 1) != 0) - ((oparg & 2) != 0) - ((oparg & 4) != 0) - ((oparg & 8) != 0);
      case 133:
        if (oparg == 3) {
            return -2;
        } else
            return -1;
      case 135:
        return 1;
      case 136:
      case 148:
        return 1;
      case 137:
        return -1;
      case 138:
        return 0;
      case 73:
        return 0;
      case 154:
        return jump ? -1 + 6 : 0;
      case 52:
        return 1;
      case 50:
        return 0;
      case 51:
        return 1;
      case 69:
        return 0;
      case 54:
        return -7;
      case 155:
        return (oparg & 4) == 4 ? -1 : 0;
      case 160:
        return 1;
      case 74:
        return 1;
      case 82:
        return 0;
      case 129:
        return -1;
      case 162:
      case 163:
      case 164:
      case 165:
        return -1;
      case 34:
        return 0;
      case 152:
        return -1;
      case 30:
      case 31:
      case 32:
        return 1;
      case 33:
        return 2;
      case 99:
        return 0;
      default:
        return 2147483647;
    }
    return 2147483647;
}
static int compiler_addop_line (struct compiler *c, int opcode, int line){
    basicblock *b;
    struct instr *i;
    int off;
    off = compiler_next_instr(c->u->u_curblock);
    if (off < 0)
        return 0;
    b = c->u->u_curblock;
    i = &b->b_instr[off];
    i->i_opcode = opcode;
    i->i_oparg = 0;
    if (opcode == 83)
        b->b_return = 1;
    i->i_lineno = line;
    return 1;
}
static int compiler_addop (struct compiler *c, int opcode){
    return compiler_addop_line(c, opcode, c->u->u_lineno);
}
static Py_ssize_t compiler_add_o (PyObject *dict, PyObject *o){
    PyObject *v;
    Py_ssize_t arg;
    v = PyDict_GetItemWithError(dict, o);
    if (!v) {
        if (PyErr_Occurred()) {
            return -1;
        }
        arg = (((void)(0)) , ((PyDictObject *)dict)->ma_used);
        v = PyLong_FromSsize_t(arg);
        if (!v) {
            return -1;
        }
        if (PyDict_SetItem(dict, o, v) < 0) {
            _Py_DECREF(((PyObject *)(v)));
            return -1;
        }
        _Py_DECREF(((PyObject *)(v)));
    } else
        arg = PyLong_AsLong(v);
    return arg;
}
static PyObject * merge_consts_recursive (struct compiler *c, PyObject *o){
    if (o == (&_Py_NoneStruct) || o == (&_Py_EllipsisObject)) {
        _Py_INCREF(((PyObject *)(o)));
        return o;
    }
    PyObject *key = _PyCode_ConstantKey(o);
    if (key == ((void *)0)) {
        return ((void *)0);
    }
    PyObject *t = PyDict_SetDefault(c->c_const_cache, key, key);
    if (t != key) {
        _Py_XINCREF(((PyObject *)(t)));
        _Py_DECREF(((PyObject *)(key)));
        return t;
    }
    if (_Py_IS_TYPE(((const PyObject *)(o)), &PyTuple_Type)) {
        Py_ssize_t len = (((PyVarObject *)((((void)(0)) , (PyTupleObject *)(o))))->ob_size);
        for (Py_ssize_t i = 0; i < len; i++) {
            PyObject *item = ((((void)(0)) , (PyTupleObject *)(o))->ob_item[i]);
            PyObject *u = merge_consts_recursive(c, item);
            if (u == ((void *)0)) {
                _Py_DECREF(((PyObject *)(key)));
                return ((void *)0);
            }
            PyObject *v;
            if (_Py_IS_TYPE(((const PyObject *)(u)), &PyTuple_Type)) {
                v = ((((void)(0)) , (PyTupleObject *)(u))->ob_item[1]);
            } else {
                v = u;
            }
            if (v != item) {
                _Py_INCREF(((PyObject *)(v)));
                ((void)((((void)(0)) , (PyTupleObject *)(o))->ob_item[i] = v));
                _Py_DECREF(((PyObject *)(item)));
            }
            _Py_DECREF(((PyObject *)(u)));
        }
    } else if (_Py_IS_TYPE(((const PyObject *)(o)), &PyFrozenSet_Type)) {
        ;
        Py_ssize_t len = (((void)(0)) , (((PySetObject *)(o))->used));
        if (len == 0) {
            return key;
        }
        PyObject *tuple = PyTuple_New(len);
        if (tuple == ((void *)0)) {
            _Py_DECREF(((PyObject *)(key)));
            return ((void *)0);
        }
        Py_ssize_t i = 0, pos = 0;
        PyObject *item;
        Py_hash_t hash;
        while (_PySet_NextEntry(o, &pos, &item, &hash))
            {
                PyObject *k = merge_consts_recursive(c, item);
                if (k == ((void *)0)) {
                    _Py_DECREF(((PyObject *)(tuple)));
                    _Py_DECREF(((PyObject *)(key)));
                    return ((void *)0);
                }
                PyObject *u;
                if (_Py_IS_TYPE(((const PyObject *)(k)), &PyTuple_Type)) {
                    u = ((((void)(0)) , (PyTupleObject *)(k))->ob_item[1]);
                    _Py_INCREF(((PyObject *)(u)));
                    _Py_DECREF(((PyObject *)(k)));
                } else {
                    u = k;
                }
                ((void)((((void)(0)) , (PyTupleObject *)(tuple))->ob_item[i] = u));
                i++;
            }
        PyObject *new = PyFrozenSet_New(tuple);
        _Py_DECREF(((PyObject *)(tuple)));
        if (new == ((void *)0)) {
            _Py_DECREF(((PyObject *)(key)));
            return ((void *)0);
        }
        ;
        _Py_DECREF(((PyObject *)(o)));
        ((void)((((void)(0)) , (PyTupleObject *)(key))->ob_item[1] = new));
    }
    return key;
}
static Py_ssize_t compiler_add_const (struct compiler *c, PyObject *o){
    PyObject *key = merge_consts_recursive(c, o);
    if (key == ((void *)0)) {
        return -1;
    }
    Py_ssize_t arg = compiler_add_o(c->u->u_consts, key);
    _Py_DECREF(((PyObject *)(key)));
    return arg;
}
static int compiler_addop_load_const (struct compiler *c, PyObject *o){
    Py_ssize_t arg = compiler_add_const(c, o);
    if (arg < 0)
        return 0;
    return compiler_addop_i(c, 100, arg);
}
static int compiler_addop_o (struct compiler *c, int opcode, PyObject *dict, PyObject *o){
    Py_ssize_t arg = compiler_add_o(dict, o);
    if (arg < 0)
        return 0;
    return compiler_addop_i(c, opcode, arg);
}
static int compiler_addop_name (struct compiler *c, int opcode, PyObject *dict, PyObject *o){
    Py_ssize_t arg;
    PyObject *mangled = _Py_Mangle(c->u->u_private, o);
    if (!mangled)
        return 0;
    arg = compiler_add_o(dict, mangled);
    _Py_DECREF(((PyObject *)(mangled)));
    if (arg < 0)
        return 0;
    return compiler_addop_i(c, opcode, arg);
}
static int compiler_addop_i_line (struct compiler *c, int opcode, Py_ssize_t oparg, int lineno){
    struct instr *i;
    int off;
    off = compiler_next_instr(c->u->u_curblock);
    if (off < 0)
        return 0;
    i = &c->u->u_curblock->b_instr[off];
    i->i_opcode = opcode;
    i->i_oparg = (int)(oparg);
    i->i_lineno = lineno;
    return 1;
}
static int compiler_addop_i (struct compiler *c, int opcode, Py_ssize_t oparg){
    return compiler_addop_i_line(c, opcode, oparg, c->u->u_lineno);
}
static int compiler_addop_i_noline (struct compiler *c, int opcode, Py_ssize_t oparg){
    return compiler_addop_i_line(c, opcode, oparg, -1);
}
static int add_jump_to_block (basicblock *b, int opcode, int lineno, basicblock *target){
    ;
    int off = compiler_next_instr(b);
    struct instr *i = &b->b_instr[off];
    if (off < 0) {
        return 0;
    }
    i->i_opcode = opcode;
    i->i_target = target;
    i->i_lineno = lineno;
    return 1;
}
static int compiler_addop_j (struct compiler *c, int opcode, basicblock *b){
    return add_jump_to_block(c->u->u_curblock, opcode, c->u->u_lineno, b);
}
static int compiler_addop_j_noline (struct compiler *c, int opcode, basicblock *b){
    return add_jump_to_block(c->u->u_curblock, opcode, -1, b);
}
static int compiler_push_fblock (struct compiler *c, enum fblocktype t, basicblock *b, basicblock *exit, void *datum){
    struct fblockinfo *f;
    if (c->u->u_nfblocks >= 20) {
        return compiler_error(c, "too many statically nested blocks");
    }
    f = &c->u->u_fblock[c->u->u_nfblocks++];
    f->fb_type = t;
    f->fb_block = b;
    f->fb_exit = exit;
    f->fb_datum = datum;
    return 1;
}
static void compiler_pop_fblock (struct compiler *c, enum fblocktype t, basicblock *b){
    struct compiler_unit *u = c->u;
    u->u_nfblocks--;
}
static int get_ref_type (struct compiler *c, PyObject *name){
    int scope;
    if (c->u->u_scope_type == COMPILER_SCOPE_CLASS && _PyUnicode_EqualToASCIIString(name, "__class__"))
        return 5;
    scope = _PyST_GetScope(c->u->u_ste, name);
    if (scope == 0) {
        ;
        return -1;
    }
    return scope;
}
static int compiler_lookup_arg (PyObject *dict, PyObject *name){
    PyObject *v;
    v = PyDict_GetItemWithError(dict, name);
    if (v == ((void *)0))
        return -1;
    return PyLong_AsLong(v);
}
static int compiler_make_closure (struct compiler *c, PyCodeObject *co, Py_ssize_t flags, PyObject *qualname){
    Py_ssize_t i, free = ((((PyVarObject *)((((void)(0)) , (PyTupleObject *)((co)->co_freevars))))->ob_size));
    if (qualname == ((void *)0))
        qualname = co->co_name;
    if (free) {
        for (i = 0; i < free; ++i) {
            PyObject *name = ((((void)(0)) , (PyTupleObject *)(co->co_freevars))->ob_item[i]);
            int reftype = get_ref_type(c, name);
            if (reftype == -1) {
                return 0;
            }
            int arg;
            if (reftype == 5) {
                arg = compiler_lookup_arg(c->u->u_cellvars, name);
            } else {
                arg = compiler_lookup_arg(c->u->u_freevars, name);
            }
            if (arg == -1) {
                ;
                return 0;
            }
            {
                if (!compiler_addop_i((c), (135), (arg)))
                    return 0;
            }
            ;
        }
        flags |= 8;
        {
            if (!compiler_addop_i((c), (102), (free)))
                return 0;
        }
        ;
    }
    {
        if (!compiler_addop_load_const((c), ((PyObject *)co)))
            return 0;
    }
    ;
    {
        if (!compiler_addop_load_const((c), (qualname)))
            return 0;
    }
    ;
    {
        if (!compiler_addop_i((c), (132), (flags)))
            return 0;
    }
    ;
    return 1;
}
static int compiler_visit_kwonlydefaults (struct compiler *c, asdl_arg_seq *kwonlyargs, asdl_expr_seq *kw_defaults){
    int i;
    PyObject *keys = ((void *)0);
    for (i = 0; i < ((kwonlyargs) == ((void *)0) ? 0 : (kwonlyargs)->size); i++) {
        arg_ty arg = (kwonlyargs)->typed_elements[(i)];
        expr_ty default_ = (kw_defaults)->typed_elements[(i)];
        if (default_) {
            PyObject *mangled = _Py_Mangle(c->u->u_private, arg->arg);
            if (!mangled) {
                goto error;
            }
            if (keys == ((void *)0)) {
                keys = PyList_New(1);
                if (keys == ((void *)0)) {
                    _Py_DECREF(((PyObject *)(mangled)));
                    return 0;
                }
                ((void)((((void)(0)) , (PyListObject *)(keys))->ob_item[0] = (mangled)));
            } else {
                int res = PyList_Append(keys, mangled);
                _Py_DECREF(((PyObject *)(mangled)));
                if (res == -1) {
                    goto error;
                }
            }
            if (!compiler_visit_expr(c, default_)) {
                goto error;
            }
        }
    }
    if (keys != ((void *)0)) {
        Py_ssize_t default_count = (((PyVarObject *)((((void)(0)) , (PyListObject *)(keys))))->ob_size);
        PyObject *keys_tuple = PyList_AsTuple(keys);
        _Py_DECREF(((PyObject *)(keys)));
        {
            PyObject *__new_const = (keys_tuple);
            if (__new_const == ((void *)0)) {
                return 0;
            }
            if (!compiler_addop_load_const((c), __new_const)) {
                _Py_DECREF(((PyObject *)(__new_const)));
                return 0;
            }
            _Py_DECREF(((PyObject *)(__new_const)));
        }
        ;
        {
            if (!compiler_addop_i((c), (156), (default_count)))
                return 0;
        }
        ;
        return 1;
    } else {
        return -1;
    }
  error:
    _Py_XDECREF(((PyObject *)(keys)));
    return 0;
}
static int compiler_visit_defaults (struct compiler *c, arguments_ty args){
    {
        int _i;
        asdl_expr_seq *seq = (args->defaults);
        for (_i = 0; _i < ((seq) == ((void *)0) ? 0 : (seq)->size); _i++) {
            expr_ty elt = (expr_ty)(seq)->typed_elements[(_i)];
            if (!compiler_visit_expr((c), elt))
                return 0;
        }
    }
    ;
    {
        if (!compiler_addop_i((c), (102), (((args->defaults) == ((void *)0) ? 0 : (args->defaults)->size))))
            return 0;
    }
    ;
    return 1;
}
static Py_ssize_t compiler_default_arguments (struct compiler *c, arguments_ty args){
    Py_ssize_t funcflags = 0;
    if (args->defaults && ((args->defaults) == ((void *)0) ? 0 : (args->defaults)->size) > 0) {
        if (!compiler_visit_defaults(c, args))
            return -1;
        funcflags |= 1;
    }
    if (args->kwonlyargs) {
        int res = compiler_visit_kwonlydefaults(c, args->kwonlyargs, args->kw_defaults);
        if (res == 0) {
            return -1;
        } else if (res > 0) {
            funcflags |= 2;
        }
    }
    return funcflags;
}
static int forbidden_name (struct compiler *c, identifier name, expr_context_ty ctx){
    if (ctx == Store && _PyUnicode_EqualToASCIIString(name, "__debug__")) {
        compiler_error(c, "cannot assign to __debug__");
        return 1;
    }
    if (ctx == Del && _PyUnicode_EqualToASCIIString(name, "__debug__")) {
        compiler_error(c, "cannot delete __debug__");
        return 1;
    }
    return 0;
}
static int compiler_check_debug_one_arg (struct compiler *c, arg_ty arg){
    if (arg != ((void *)0)) {
        if (forbidden_name(c, arg->arg, Store))
            return 0;
    }
    return 1;
}
static int compiler_check_debug_args_seq (struct compiler *c, asdl_arg_seq *args){
    if (args != ((void *)0)) {
        for (Py_ssize_t i = 0, n = ((args) == ((void *)0) ? 0 : (args)->size); i < n; i++) {
            if (!compiler_check_debug_one_arg(c, (args)->typed_elements[(i)]))
                return 0;
        }
    }
    return 1;
}
static int compiler_check_debug_args (struct compiler *c, arguments_ty args){
    if (!compiler_check_debug_args_seq(c, args->posonlyargs))
        return 0;
    if (!compiler_check_debug_args_seq(c, args->args))
        return 0;
    if (!compiler_check_debug_one_arg(c, args->vararg))
        return 0;
    if (!compiler_check_debug_args_seq(c, args->kwonlyargs))
        return 0;
    if (!compiler_check_debug_one_arg(c, args->kwarg))
        return 0;
    return 1;
}
static int check_is_arg (expr_ty e){
    if (e->kind != Constant_kind) {
        return 1;
    }
    PyObject *value = e->v.Constant.value;
    return (value == (&_Py_NoneStruct) || value == ((PyObject *)&_Py_FalseStruct) || value == ((PyObject *)&_Py_TrueStruct) || value == (&_Py_EllipsisObject));
}
static int check_compare (struct compiler *c, expr_ty e){
    Py_ssize_t i, n;
    int left = check_is_arg(e->v.Compare.left);
    n = ((e->v.Compare.ops) == ((void *)0) ? 0 : (e->v.Compare.ops)->size);
    for (i = 0; i < n; i++) {
        cmpop_ty op = (cmpop_ty)(e->v.Compare.ops)->typed_elements[(i)];
        int right = check_is_arg((expr_ty)(e->v.Compare.comparators)->typed_elements[(i)]);
        if (op == Is || op == IsNot) {
            if (!right || !left) {
                const char *msg = (op == Is) ? "\"is\" with a literal. Did you mean \"==\"?" : "\"is not\" with a literal. Did you mean \"!=\"?";
                return compiler_warn(c, msg);
            }
        }
        left = right;
    }
    return 1;
}
static int compiler_addcompare (struct compiler *c, cmpop_ty op){
    int cmp;
    switch (op) {
      case Eq:
        cmp = 2;
        break;
      case NotEq:
        cmp = 3;
        break;
      case Lt:
        cmp = 0;
        break;
      case LtE:
        cmp = 1;
        break;
      case Gt:
        cmp = 4;
        break;
      case GtE:
        cmp = 5;
        break;
      case Is:
        {
            if (!compiler_addop_i((c), (117), (0)))
                return 0;
        }
        ;
        return 1;
      case IsNot:
        {
            if (!compiler_addop_i((c), (117), (1)))
                return 0;
        }
        ;
        return 1;
      case In:
        {
            if (!compiler_addop_i((c), (118), (0)))
                return 0;
        }
        ;
        return 1;
      case NotIn:
        {
            if (!compiler_addop_i((c), (118), (1)))
                return 0;
        }
        ;
        return 1;
    }
    {
        if (!compiler_addop_i((c), (107), (cmp)))
            return 0;
    }
    ;
    return 1;
}
static int compiler_jump_if (struct compiler *c, expr_ty e, basicblock *next, int cond){
    switch (e->kind) {
      case UnaryOp_kind:
        if (e->v.UnaryOp.op == Not)
            return compiler_jump_if(c, e->v.UnaryOp.operand, next, !cond);
        break;
      case BoolOp_kind:
        {
            asdl_expr_seq *s = e->v.BoolOp.values;
            Py_ssize_t i, n = ((s) == ((void *)0) ? 0 : (s)->size) - 1;
            int cond2 = e->v.BoolOp.op == Or;
            basicblock *next2 = next;
            if (!cond2 != !cond) {
                next2 = compiler_new_block(c);
                if (next2 == ((void *)0))
                    return 0;
            }
            for (i = 0; i < n; ++i) {
                if (!compiler_jump_if(c, (expr_ty)(s)->typed_elements[(i)], next2, cond2))
                    return 0;
            }
            if (!compiler_jump_if(c, (expr_ty)(s)->typed_elements[(n)], next, cond))
                return 0;
            if (next2 != next)
                compiler_use_next_block(c, next2);
            return 1;
        }
      case IfExp_kind:
        {
            basicblock *end, *next2;
            end = compiler_new_block(c);
            if (end == ((void *)0))
                return 0;
            next2 = compiler_new_block(c);
            if (next2 == ((void *)0))
                return 0;
            if (!compiler_jump_if(c, e->v.IfExp.test, next2, 0))
                return 0;
            if (!compiler_jump_if(c, e->v.IfExp.body, next, cond))
                return 0;
            {
                if (!compiler_addop_j_noline((c), (110), (end)))
                    return 0;
            }
            ;
            compiler_use_next_block(c, next2);
            if (!compiler_jump_if(c, e->v.IfExp.orelse, next, cond))
                return 0;
            compiler_use_next_block(c, end);
            return 1;
        }
      case Compare_kind:
        {
            (c)->u->u_lineno = (e)->lineno;
            (c)->u->u_col_offset = (e)->col_offset;
            (c)->u->u_end_lineno = (e)->end_lineno;
            (c)->u->u_end_col_offset = (e)->end_col_offset;
            Py_ssize_t i, n = ((e->v.Compare.ops) == ((void *)0) ? 0 : (e->v.Compare.ops)->size) - 1;
            if (n > 0) {
                if (!check_compare(c, e)) {
                    return 0;
                }
                basicblock *cleanup = compiler_new_block(c);
                if (cleanup == ((void *)0))
                    return 0;
                {
                    if (!compiler_visit_expr((c), (e->v.Compare.left)))
                        return 0;
                }
                ;
                for (i = 0; i < n; i++) {
                    {
                        if (!compiler_visit_expr((c), ((expr_ty)(e->v.Compare.comparators)->typed_elements[(i)])))
                            return 0;
                    }
                    ;
                    {
                        if (!compiler_addop((c), (4)))
                            return 0;
                    }
                    ;
                    {
                        if (!compiler_addop((c), (3)))
                            return 0;
                    }
                    ;
                    {
                        if (!compiler_addcompare((c), (cmpop_ty)((e->v.Compare.ops)->typed_elements[(i)])))
                            return 0;
                    }
                    ;
                    {
                        if (!compiler_addop_j((c), (114), (cleanup)))
                            return 0;
                    }
                    ;
                    {
                        if (compiler_next_block((c)) == ((void *)0))
                            return 0;
                    }
                    ;
                }
                {
                    if (!compiler_visit_expr((c), ((expr_ty)(e->v.Compare.comparators)->typed_elements[(n)])))
                        return 0;
                }
                ;
                {
                    if (!compiler_addcompare((c), (cmpop_ty)((e->v.Compare.ops)->typed_elements[(n)])))
                        return 0;
                }
                ;
                {
                    if (!compiler_addop_j((c), (cond ? 115 : 114), (next)))
                        return 0;
                }
                ;
                {
                    if (compiler_next_block((c)) == ((void *)0))
                        return 0;
                }
                ;
                basicblock *end = compiler_new_block(c);
                if (end == ((void *)0))
                    return 0;
                {
                    if (!compiler_addop_j_noline((c), (110), (end)))
                        return 0;
                }
                ;
                compiler_use_next_block(c, cleanup);
                {
                    if (!compiler_addop((c), (1)))
                        return 0;
                }
                ;
                if (!cond) {
                    {
                        if (!compiler_addop_j_noline((c), (110), (next)))
                            return 0;
                    }
                    ;
                }
                compiler_use_next_block(c, end);
                return 1;
            }
            break;
        }
        ;
    }
    {
        if (!compiler_visit_expr((c), (e)))
            return 0;
    }
    ;
    {
        if (!compiler_addop_j((c), (cond ? 115 : 114), (next)))
            return 0;
    }
    ;
    {
        if (compiler_next_block((c)) == ((void *)0))
            return 0;
    }
    ;
    return 1;
}
static int compiler_ifexp (struct compiler *c, expr_ty e){
    basicblock *end, *next;
    end = compiler_new_block(c);
    if (end == ((void *)0))
        return 0;
    next = compiler_new_block(c);
    if (next == ((void *)0))
        return 0;
    if (!compiler_jump_if(c, e->v.IfExp.test, next, 0))
        return 0;
    {
        if (!compiler_visit_expr((c), (e->v.IfExp.body)))
            return 0;
    }
    ;
    {
        if (!compiler_addop_j_noline((c), (110), (end)))
            return 0;
    }
    ;
    compiler_use_next_block(c, next);
    {
        if (!compiler_visit_expr((c), (e->v.IfExp.orelse)))
            return 0;
    }
    ;
    compiler_use_next_block(c, end);
    return 1;
}
static int compiler_lambda (struct compiler *c, expr_ty e){
    PyCodeObject *co;
    PyObject *qualname;
    static identifier name;
    Py_ssize_t funcflags;
    arguments_ty args = e->v.Lambda.args;
    if (!compiler_check_debug_args(c, args))
        return 0;
    if (!name) {
        name = PyUnicode_InternFromString("<lambda>");
        if (!name)
            return 0;
    }
    funcflags = compiler_default_arguments(c, args);
    if (funcflags == -1) {
        return 0;
    }
    if (!compiler_enter_scope(c, name, COMPILER_SCOPE_LAMBDA, (void *)e, e->lineno))
        return 0;
    if (compiler_add_const(c, (&_Py_NoneStruct)) < 0)
        return 0;
    c->u->u_argcount = ((args->args) == ((void *)0) ? 0 : (args->args)->size);
    c->u->u_posonlyargcount = ((args->posonlyargs) == ((void *)0) ? 0 : (args->posonlyargs)->size);
    c->u->u_kwonlyargcount = ((args->kwonlyargs) == ((void *)0) ? 0 : (args->kwonlyargs)->size);
    {
        if (!compiler_visit_expr((c), (e->v.Lambda.body))) {
            compiler_exit_scope(c);
            return 0;
        }
    }
    ;
    if (c->u->u_ste->ste_generator) {
        co = assemble(c, 0);
    } else {
        {
            if (!compiler_addop((c), (83))) {
                compiler_exit_scope(c);
                return 0;
            }
        }
        ;
        co = assemble(c, 1);
    }
    qualname = c->u->u_qualname;
    _Py_INCREF(((PyObject *)(qualname)));
    compiler_exit_scope(c);
    if (co == ((void *)0)) {
        _Py_DECREF(((PyObject *)(qualname)));
        return 0;
    }
    if (!compiler_make_closure(c, co, funcflags, qualname)) {
        _Py_DECREF(((PyObject *)(qualname)));
        _Py_DECREF(((PyObject *)(co)));
        return 0;
    }
    _Py_DECREF(((PyObject *)(qualname)));
    _Py_DECREF(((PyObject *)(co)));
    return 1;
}
static int unaryop (unaryop_ty op){
    switch (op) {
      case Invert:
        return 15;
      case Not:
        return 12;
      case UAdd:
        return 10;
      case USub:
        return 11;
      default:
        ;
        return 0;
    }
}
static int binop (operator_ty op){
    switch (op) {
      case Add:
        return 23;
      case Sub:
        return 24;
      case Mult:
        return 20;
      case MatMult:
        return 16;
      case Div:
        return 27;
      case Mod:
        return 22;
      case Pow:
        return 19;
      case LShift:
        return 62;
      case RShift:
        return 63;
      case BitOr:
        return 66;
      case BitXor:
        return 65;
      case BitAnd:
        return 64;
      case FloorDiv:
        return 26;
      default:
        ;
        return 0;
    }
}
static int compiler_nameop (struct compiler *c, identifier name, expr_context_ty ctx){
    int op, scope;
    Py_ssize_t arg;
    enum {
        OP_FAST,
        OP_GLOBAL,
        OP_DEREF,
        OP_NAME
    } optype;
    PyObject *dict = c->u->u_names;
    PyObject *mangled;
    if (forbidden_name(c, name, ctx))
        return 0;
    mangled = _Py_Mangle(c->u->u_private, name);
    if (!mangled)
        return 0;
    op = 0;
    optype = OP_NAME;
    scope = _PyST_GetScope(c->u->u_ste, mangled);
    switch (scope) {
      case 4:
        dict = c->u->u_freevars;
        optype = OP_DEREF;
        break;
      case 5:
        dict = c->u->u_cellvars;
        optype = OP_DEREF;
        break;
      case 1:
        if (c->u->u_ste->ste_type == FunctionBlock)
            optype = OP_FAST;
        break;
      case 3:
        if (c->u->u_ste->ste_type == FunctionBlock)
            optype = OP_GLOBAL;
        break;
      case 2:
        optype = OP_GLOBAL;
        break;
    }
    ;
    switch (optype) {
      case OP_DEREF:
        switch (ctx) {
          case Load:
            op = (c->u->u_ste->ste_type == ClassBlock) ? 148 : 136;
            break;
          case Store:
            op = 137;
            break;
          case Del:
            op = 138;
            break;
        }
        break;
      case OP_FAST:
        switch (ctx) {
          case Load:
            op = 124;
            break;
          case Store:
            op = 125;
            break;
          case Del:
            op = 126;
            break;
        }
        {
            ((void)(0));
            if (!compiler_addop_o((c), (op), (c)->u->u_varnames, (mangled))) {
                _Py_DECREF(((PyObject *)((mangled))));
                return 0;
            }
            _Py_DECREF(((PyObject *)((mangled))));
        }
        ;
        return 1;
      case OP_GLOBAL:
        switch (ctx) {
          case Load:
            op = 116;
            break;
          case Store:
            op = 97;
            break;
          case Del:
            op = 98;
            break;
        }
        break;
      case OP_NAME:
        switch (ctx) {
          case Load:
            op = 101;
            break;
          case Store:
            op = 90;
            break;
          case Del:
            op = 91;
            break;
        }
        break;
    }
    ;
    arg = compiler_add_o(dict, mangled);
    _Py_DECREF(((PyObject *)(mangled)));
    if (arg < 0)
        return 0;
    return compiler_addop_i(c, op, arg);
}
static int compiler_boolop (struct compiler *c, expr_ty e){
    basicblock *end;
    int jumpi;
    Py_ssize_t i, n;
    asdl_expr_seq *s;
    if (e->v.BoolOp.op == And)
        jumpi = 111;
    else
        jumpi = 112;
    end = compiler_new_block(c);
    if (end == ((void *)0))
        return 0;
    s = e->v.BoolOp.values;
    n = ((s) == ((void *)0) ? 0 : (s)->size) - 1;
    for (i = 0; i < n; ++i) {
        {
            if (!compiler_visit_expr((c), ((expr_ty)(s)->typed_elements[(i)])))
                return 0;
        }
        ;
        {
            if (!compiler_addop_j((c), (jumpi), (end)))
                return 0;
        }
        ;
        basicblock *next = compiler_new_block(c);
        if (next == ((void *)0)) {
            return 0;
        }
        compiler_use_next_block(c, next);
    }
    {
        if (!compiler_visit_expr((c), ((expr_ty)(s)->typed_elements[(n)])))
            return 0;
    }
    ;
    compiler_use_next_block(c, end);
    return 1;
}
static int starunpack_helper (struct compiler *c, asdl_expr_seq *elts, int pushed, int build, int add, int extend, int tuple){
    Py_ssize_t n = ((elts) == ((void *)0) ? 0 : (elts)->size);
    if (n > 2 && are_all_items_const(elts, 0, n)) {
        PyObject *folded = PyTuple_New(n);
        if (folded == ((void *)0)) {
            return 0;
        }
        PyObject *val;
        for (Py_ssize_t i = 0; i < n; i++) {
            val = ((expr_ty)(elts)->typed_elements[(i)])->v.Constant.value;
            _Py_INCREF(((PyObject *)(val)));
            ((void)((((void)(0)) , (PyTupleObject *)(folded))->ob_item[i] = val));
        }
        if (tuple) {
            {
                PyObject *__new_const = (folded);
                if (__new_const == ((void *)0)) {
                    return 0;
                }
                if (!compiler_addop_load_const((c), __new_const)) {
                    _Py_DECREF(((PyObject *)(__new_const)));
                    return 0;
                }
                _Py_DECREF(((PyObject *)(__new_const)));
            }
            ;
        } else {
            if (add == 146) {
                do {
                    PyObject *_py_tmp = ((PyObject *)(folded));
                    (folded) = (PyFrozenSet_New(folded));
                    _Py_DECREF(((PyObject *)(_py_tmp)));
                } while (0);
                if (folded == ((void *)0)) {
                    return 0;
                }
            }
            {
                if (!compiler_addop_i((c), (build), (pushed)))
                    return 0;
            }
            ;
            {
                PyObject *__new_const = (folded);
                if (__new_const == ((void *)0)) {
                    return 0;
                }
                if (!compiler_addop_load_const((c), __new_const)) {
                    _Py_DECREF(((PyObject *)(__new_const)));
                    return 0;
                }
                _Py_DECREF(((PyObject *)(__new_const)));
            }
            ;
            {
                if (!compiler_addop_i((c), (extend), (1)))
                    return 0;
            }
            ;
        }
        return 1;
    }
    int big = n + pushed > 30;
    int seen_star = 0;
    for (Py_ssize_t i = 0; i < n; i++) {
        expr_ty elt = (elts)->typed_elements[(i)];
        if (elt->kind == Starred_kind) {
            seen_star = 1;
        }
    }
    if (!seen_star && !big) {
        for (Py_ssize_t i = 0; i < n; i++) {
            expr_ty elt = (elts)->typed_elements[(i)];
            {
                if (!compiler_visit_expr((c), (elt)))
                    return 0;
            }
            ;
        }
        if (tuple) {
            {
                if (!compiler_addop_i((c), (102), (n + pushed)))
                    return 0;
            }
            ;
        } else {
            {
                if (!compiler_addop_i((c), (build), (n + pushed)))
                    return 0;
            }
            ;
        }
        return 1;
    }
    int sequence_built = 0;
    if (big) {
        {
            if (!compiler_addop_i((c), (build), (pushed)))
                return 0;
        }
        ;
        sequence_built = 1;
    }
    for (Py_ssize_t i = 0; i < n; i++) {
        expr_ty elt = (elts)->typed_elements[(i)];
        if (elt->kind == Starred_kind) {
            if (sequence_built == 0) {
                {
                    if (!compiler_addop_i((c), (build), (i + pushed)))
                        return 0;
                }
                ;
                sequence_built = 1;
            }
            {
                if (!compiler_visit_expr((c), (elt->v.Starred.value)))
                    return 0;
            }
            ;
            {
                if (!compiler_addop_i((c), (extend), (1)))
                    return 0;
            }
            ;
        } else {
            {
                if (!compiler_visit_expr((c), (elt)))
                    return 0;
            }
            ;
            if (sequence_built) {
                {
                    if (!compiler_addop_i((c), (add), (1)))
                        return 0;
                }
                ;
            }
        }
    }
    ;
    if (tuple) {
        {
            if (!compiler_addop((c), (82)))
                return 0;
        }
        ;
    }
    return 1;
}
static int unpack_helper (struct compiler *c, asdl_expr_seq *elts){
    Py_ssize_t n = ((elts) == ((void *)0) ? 0 : (elts)->size);
    int seen_star = 0;
    for (Py_ssize_t i = 0; i < n; i++) {
        expr_ty elt = (elts)->typed_elements[(i)];
        if (elt->kind == Starred_kind && !seen_star) {
            if ((i >= (1 << 8)) || (n - i - 1 >= (2147483647 >> 8)))
                return compiler_error(c, "too many expressions in star-unpacking assignment");
            {
                if (!compiler_addop_i((c), (94), ((i + ((n - i - 1) << 8)))))
                    return 0;
            }
            ;
            seen_star = 1;
        } else if (elt->kind == Starred_kind) {
            return compiler_error(c, "multiple starred expressions in assignment");
        }
    }
    if (!seen_star) {
        {
            if (!compiler_addop_i((c), (92), (n)))
                return 0;
        }
        ;
    }
    return 1;
}
static int assignment_helper (struct compiler *c, asdl_expr_seq *elts){
    Py_ssize_t n = ((elts) == ((void *)0) ? 0 : (elts)->size);
    if (!(unpack_helper(c, elts))) {
        return 0;
    }
    ;
    for (Py_ssize_t i = 0; i < n; i++) {
        expr_ty elt = (elts)->typed_elements[(i)];
        {
            if (!compiler_visit_expr((c), (elt->kind != Starred_kind ? elt : elt->v.Starred.value)))
                return 0;
        }
        ;
    }
    return 1;
}
static int compiler_list (struct compiler *c, expr_ty e){
    asdl_expr_seq *elts = e->v.List.elts;
    if (e->v.List.ctx == Store) {
        return assignment_helper(c, elts);
    } else if (e->v.List.ctx == Load) {
        return starunpack_helper(c, elts, 0, 103, 145, 162, 0);
    } else {
        int _i;
        asdl_expr_seq *seq = (elts);
        for (_i = 0; _i < ((seq) == ((void *)0) ? 0 : (seq)->size); _i++) {
            expr_ty elt = (expr_ty)(seq)->typed_elements[(_i)];
            if (!compiler_visit_expr((c), elt))
                return 0;
        }
    }
    ;
    return 1;
}
static int compiler_tuple (struct compiler *c, expr_ty e){
    asdl_expr_seq *elts = e->v.Tuple.elts;
    if (e->v.Tuple.ctx == Store) {
        return assignment_helper(c, elts);
    } else if (e->v.Tuple.ctx == Load) {
        return starunpack_helper(c, elts, 0, 103, 145, 162, 1);
    } else {
        int _i;
        asdl_expr_seq *seq = (elts);
        for (_i = 0; _i < ((seq) == ((void *)0) ? 0 : (seq)->size); _i++) {
            expr_ty elt = (expr_ty)(seq)->typed_elements[(_i)];
            if (!compiler_visit_expr((c), elt))
                return 0;
        }
    }
    ;
    return 1;
}
static int compiler_set (struct compiler *c, expr_ty e){
    return starunpack_helper(c, e->v.Set.elts, 0, 104, 146, 163, 0);
}
static int are_all_items_const (asdl_expr_seq *seq, Py_ssize_t begin, Py_ssize_t end){
    Py_ssize_t i;
    for (i = begin; i < end; i++) {
        expr_ty key = (expr_ty)(seq)->typed_elements[(i)];
        if (key == ((void *)0) || key->kind != Constant_kind)
            return 0;
    }
    return 1;
}
static int compiler_subdict (struct compiler *c, expr_ty e, Py_ssize_t begin, Py_ssize_t end){
    Py_ssize_t i, n = end - begin;
    PyObject *keys, *key;
    int big = n * 2 > 30;
    if (n > 1 && !big && are_all_items_const(e->v.Dict.keys, begin, end)) {
        for (i = begin; i < end; i++) {
            {
                if (!compiler_visit_expr((c), ((expr_ty)(e->v.Dict.values)->typed_elements[(i)])))
                    return 0;
            }
            ;
        }
        keys = PyTuple_New(n);
        if (keys == ((void *)0)) {
            return 0;
        }
        for (i = begin; i < end; i++) {
            key = ((expr_ty)(e->v.Dict.keys)->typed_elements[(i)])->v.Constant.value;
            _Py_INCREF(((PyObject *)(key)));
            ((void)((((void)(0)) , (PyTupleObject *)(keys))->ob_item[i - begin] = key));
        }
        {
            PyObject *__new_const = (keys);
            if (__new_const == ((void *)0)) {
                return 0;
            }
            if (!compiler_addop_load_const((c), __new_const)) {
                _Py_DECREF(((PyObject *)(__new_const)));
                return 0;
            }
            _Py_DECREF(((PyObject *)(__new_const)));
        }
        ;
        {
            if (!compiler_addop_i((c), (156), (n)))
                return 0;
        }
        ;
        return 1;
    }
    if (big) {
        {
            if (!compiler_addop_i((c), (105), (0)))
                return 0;
        }
        ;
    }
    for (i = begin; i < end; i++) {
        {
            if (!compiler_visit_expr((c), ((expr_ty)(e->v.Dict.keys)->typed_elements[(i)])))
                return 0;
        }
        ;
        {
            if (!compiler_visit_expr((c), ((expr_ty)(e->v.Dict.values)->typed_elements[(i)])))
                return 0;
        }
        ;
        if (big) {
            {
                if (!compiler_addop_i((c), (147), (1)))
                    return 0;
            }
            ;
        }
    }
    if (!big) {
        {
            if (!compiler_addop_i((c), (105), (n)))
                return 0;
        }
        ;
    }
    return 1;
}
static int compiler_dict (struct compiler *c, expr_ty e){
    Py_ssize_t i, n, elements;
    int have_dict;
    int is_unpacking = 0;
    n = ((e->v.Dict.values) == ((void *)0) ? 0 : (e->v.Dict.values)->size);
    have_dict = 0;
    elements = 0;
    for (i = 0; i < n; i++) {
        is_unpacking = (expr_ty)(e->v.Dict.keys)->typed_elements[(i)] == ((void *)0);
        if (is_unpacking) {
            if (elements) {
                if (!compiler_subdict(c, e, i - elements, i)) {
                    return 0;
                }
                if (have_dict) {
                    {
                        if (!compiler_addop_i((c), (165), (1)))
                            return 0;
                    }
                    ;
                }
                have_dict = 1;
                elements = 0;
            }
            if (have_dict == 0) {
                {
                    if (!compiler_addop_i((c), (105), (0)))
                        return 0;
                }
                ;
                have_dict = 1;
            }
            {
                if (!compiler_visit_expr((c), ((expr_ty)(e->v.Dict.values)->typed_elements[(i)])))
                    return 0;
            }
            ;
            {
                if (!compiler_addop_i((c), (165), (1)))
                    return 0;
            }
            ;
        } else {
            if (elements * 2 > 30) {
                if (!compiler_subdict(c, e, i - elements, i + 1)) {
                    return 0;
                }
                if (have_dict) {
                    {
                        if (!compiler_addop_i((c), (165), (1)))
                            return 0;
                    }
                    ;
                }
                have_dict = 1;
                elements = 0;
            } else {
                elements++;
            }
        }
    }
    if (elements) {
        if (!compiler_subdict(c, e, n - elements, n)) {
            return 0;
        }
        if (have_dict) {
            {
                if (!compiler_addop_i((c), (165), (1)))
                    return 0;
            }
            ;
        }
        have_dict = 1;
    }
    if (!have_dict) {
        {
            if (!compiler_addop_i((c), (105), (0)))
                return 0;
        }
        ;
    }
    return 1;
}
static int compiler_compare (struct compiler *c, expr_ty e){
    Py_ssize_t i, n;
    if (!check_compare(c, e)) {
        return 0;
    }
    {
        if (!compiler_visit_expr((c), (e->v.Compare.left)))
            return 0;
    }
    ;
    n = ((e->v.Compare.ops) == ((void *)0) ? 0 : (e->v.Compare.ops)->size) - 1;
    if (n == 0) {
        {
            if (!compiler_visit_expr((c), ((expr_ty)(e->v.Compare.comparators)->typed_elements[(0)])))
                return 0;
        }
        ;
        {
            if (!compiler_addcompare((c), (cmpop_ty)((e->v.Compare.ops)->typed_elements[(0)])))
                return 0;
        }
        ;
    } else {
        basicblock *cleanup = compiler_new_block(c);
        if (cleanup == ((void *)0))
            return 0;
        for (i = 0; i < n; i++) {
            {
                if (!compiler_visit_expr((c), ((expr_ty)(e->v.Compare.comparators)->typed_elements[(i)])))
                    return 0;
            }
            ;
            {
                if (!compiler_addop((c), (4)))
                    return 0;
            }
            ;
            {
                if (!compiler_addop((c), (3)))
                    return 0;
            }
            ;
            {
                if (!compiler_addcompare((c), (cmpop_ty)((e->v.Compare.ops)->typed_elements[(i)])))
                    return 0;
            }
            ;
            {
                if (!compiler_addop_j((c), (111), (cleanup)))
                    return 0;
            }
            ;
            {
                if (compiler_next_block((c)) == ((void *)0))
                    return 0;
            }
            ;
        }
        {
            if (!compiler_visit_expr((c), ((expr_ty)(e->v.Compare.comparators)->typed_elements[(n)])))
                return 0;
        }
        ;
        {
            if (!compiler_addcompare((c), (cmpop_ty)((e->v.Compare.ops)->typed_elements[(n)])))
                return 0;
        }
        ;
        basicblock *end = compiler_new_block(c);
        if (end == ((void *)0))
            return 0;
        {
            if (!compiler_addop_j_noline((c), (110), (end)))
                return 0;
        }
        ;
        compiler_use_next_block(c, cleanup);
        {
            if (!compiler_addop((c), (2)))
                return 0;
        }
        ;
        {
            if (!compiler_addop((c), (1)))
                return 0;
        }
        ;
        compiler_use_next_block(c, end);
    }
    return 1;
}
static PyTypeObject * infer_type (expr_ty e){
    switch (e->kind) {
      case Tuple_kind:
        return &PyTuple_Type;
      case List_kind:
      case ListComp_kind:
        return &PyList_Type;
      case Dict_kind:
      case DictComp_kind:
        return &PyDict_Type;
      case Set_kind:
      case SetComp_kind:
        return &PySet_Type;
      case GeneratorExp_kind:
        return &PyGen_Type;
      case Lambda_kind:
        return &PyFunction_Type;
      case JoinedStr_kind:
      case FormattedValue_kind:
        return &PyUnicode_Type;
      case Constant_kind:
        return (((PyObject *)(e->v.Constant.value))->ob_type);
      default:
        return ((void *)0);
    }
}
static int check_caller (struct compiler *c, expr_ty e){
    switch (e->kind) {
      case Constant_kind:
      case Tuple_kind:
      case List_kind:
      case ListComp_kind:
      case Dict_kind:
      case DictComp_kind:
      case Set_kind:
      case SetComp_kind:
      case GeneratorExp_kind:
      case JoinedStr_kind:
      case FormattedValue_kind:
        return compiler_warn(c, "'%.200s' object is not callable; perhaps you missed a comma?", infer_type(e)->tp_name);
      default:
        return 1;
    }
}
static int check_subscripter (struct compiler *c, expr_ty e){
    PyObject *v;
    switch (e->kind) {
      case Constant_kind:
        v = e->v.Constant.value;
        if (!(v == (&_Py_NoneStruct) || v == (&_Py_EllipsisObject) || PyType_HasFeature((((PyObject *)(v))->ob_type), (1UL << 24)) || _PyObject_TypeCheck(((PyObject *)(v)), &PyFloat_Type) || _PyObject_TypeCheck(((PyObject *)(v)), &PyComplex_Type) || (_Py_IS_TYPE(((const PyObject *)(v)), &PySet_Type) || _Py_IS_TYPE(((const PyObject *)(v)), &PyFrozenSet_Type) || PyType_IsSubtype((((PyObject *)(v))->ob_type), &PySet_Type) || PyType_IsSubtype((((PyObject *)(v))->ob_type), &PyFrozenSet_Type)))) {
            return 1;
        }
      case Set_kind:
      case SetComp_kind:
      case GeneratorExp_kind:
      case Lambda_kind:
        return compiler_warn(c, "'%.200s' object is not subscriptable; perhaps you missed a comma?", infer_type(e)->tp_name);
      default:
        return 1;
    }
}
static int check_index (struct compiler *c, expr_ty e, expr_ty s){
    PyObject *v;
    PyTypeObject *index_type = infer_type(s);
    if (index_type == ((void *)0) || PyType_HasFeature(index_type, (1UL << 24)) || index_type == &PySlice_Type) {
        return 1;
    }
    switch (e->kind) {
      case Constant_kind:
        v = e->v.Constant.value;
        if (!(PyType_HasFeature((((PyObject *)(v))->ob_type), (1UL << 28)) || PyType_HasFeature((((PyObject *)(v))->ob_type), (1UL << 27)) || PyType_HasFeature((((PyObject *)(v))->ob_type), (1UL << 26)))) {
            return 1;
        }
      case Tuple_kind:
      case List_kind:
      case ListComp_kind:
      case JoinedStr_kind:
      case FormattedValue_kind:
        return compiler_warn(c, "%.200s indices must be integers or slices, not %.200s; perhaps you missed a comma?", infer_type(e)->tp_name, index_type->tp_name);
      default:
        return 1;
    }
}
static int maybe_optimize_method_call (struct compiler *c, expr_ty e){
    Py_ssize_t argsl, i;
    expr_ty meth = e->v.Call.func;
    asdl_expr_seq *args = e->v.Call.args;
    if (meth->kind != Attribute_kind || meth->v.Attribute.ctx != Load || ((e->v.Call.keywords) == ((void *)0) ? 0 : (e->v.Call.keywords)->size)) {
        return -1;
    }
    argsl = ((args) == ((void *)0) ? 0 : (args)->size);
    if (argsl >= 30) {
        return -1;
    }
    for (i = 0; i < argsl; i++) {
        expr_ty elt = (args)->typed_elements[(i)];
        if (elt->kind == Starred_kind) {
            return -1;
        }
    }
    {
        if (!compiler_visit_expr((c), (meth->v.Attribute.value)))
            return 0;
    }
    ;
    int old_lineno = c->u->u_lineno;
    c->u->u_lineno = meth->end_lineno;
    {
        if (!compiler_addop_name((c), (160), (c)->u->u_names, (meth->v.Attribute.attr)))
            return 0;
    }
    ;
    {
        int _i;
        asdl_expr_seq *seq = (e->v.Call.args);
        for (_i = 0; _i < ((seq) == ((void *)0) ? 0 : (seq)->size); _i++) {
            expr_ty elt = (expr_ty)(seq)->typed_elements[(_i)];
            if (!compiler_visit_expr((c), elt))
                return 0;
        }
    }
    ;
    {
        if (!compiler_addop_i((c), (161), (((e->v.Call.args) == ((void *)0) ? 0 : (e->v.Call.args)->size))))
            return 0;
    }
    ;
    c->u->u_lineno = old_lineno;
    return 1;
}
static int validate_keywords (struct compiler *c, asdl_keyword_seq *keywords){
    Py_ssize_t nkeywords = ((keywords) == ((void *)0) ? 0 : (keywords)->size);
    for (Py_ssize_t i = 0; i < nkeywords; i++) {
        keyword_ty key = ((keyword_ty)(keywords)->typed_elements[(i)]);
        if (key->arg == ((void *)0)) {
            continue;
        }
        if (forbidden_name(c, key->arg, Store)) {
            return -1;
        }
        for (Py_ssize_t j = i + 1; j < nkeywords; j++) {
            keyword_ty other = ((keyword_ty)(keywords)->typed_elements[(j)]);
            if (other->arg && !PyUnicode_Compare(key->arg, other->arg)) {
                (c)->u->u_lineno = (other)->lineno;
                (c)->u->u_col_offset = (other)->col_offset;
                (c)->u->u_end_lineno = (other)->end_lineno;
                (c)->u->u_end_col_offset = (other)->end_col_offset;
                compiler_error(c, "keyword argument repeated: %U", key->arg);
                return -1;
            }
        }
    }
    return 0;
}
static int compiler_call (struct compiler *c, expr_ty e){
    int ret = maybe_optimize_method_call(c, e);
    if (ret >= 0) {
        return ret;
    }
    if (!check_caller(c, e->v.Call.func)) {
        return 0;
    }
    {
        if (!compiler_visit_expr((c), (e->v.Call.func)))
            return 0;
    }
    ;
    return compiler_call_helper(c, 0, e->v.Call.args, e->v.Call.keywords);
}
static int compiler_joined_str (struct compiler *c, expr_ty e){
    Py_ssize_t value_count = ((e->v.JoinedStr.values) == ((void *)0) ? 0 : (e->v.JoinedStr.values)->size);
    if (value_count > 30) {
        {
            PyObject *__new_const = (_PyUnicode_FromASCII("", 0));
            if (__new_const == ((void *)0)) {
                return 0;
            }
            if (!compiler_addop_load_const((c), __new_const)) {
                _Py_DECREF(((PyObject *)(__new_const)));
                return 0;
            }
            _Py_DECREF(((PyObject *)(__new_const)));
        }
        ;
        PyObject *join = _PyUnicode_FromASCII("join", 4);
        if (join == ((void *)0)) {
            return 0;
        }
        {
            if (!compiler_addop_name((c), (160), (c)->u->u_names, (join)))
                return 0;
        }
        ;
        _Py_DECREF(((PyObject *)(join)));
        {
            if (!compiler_addop_i((c), (103), (0)))
                return 0;
        }
        ;
        for (Py_ssize_t i = 0; i < ((e->v.JoinedStr.values) == ((void *)0) ? 0 : (e->v.JoinedStr.values)->size); i++) {
            {
                if (!compiler_visit_expr((c), ((e->v.JoinedStr.values)->typed_elements[(i)])))
                    return 0;
            }
            ;
            {
                if (!compiler_addop_i((c), (145), (1)))
                    return 0;
            }
            ;
        }
        {
            if (!compiler_addop_i((c), (161), (1)))
                return 0;
        }
        ;
    } else {
        {
            int _i;
            asdl_expr_seq *seq = (e->v.JoinedStr.values);
            for (_i = 0; _i < ((seq) == ((void *)0) ? 0 : (seq)->size); _i++) {
                expr_ty elt = (expr_ty)(seq)->typed_elements[(_i)];
                if (!compiler_visit_expr((c), elt))
                    return 0;
            }
        }
        ;
        if (((e->v.JoinedStr.values) == ((void *)0) ? 0 : (e->v.JoinedStr.values)->size) != 1) {
            {
                if (!compiler_addop_i((c), (157), (((e->v.JoinedStr.values) == ((void *)0) ? 0 : (e->v.JoinedStr.values)->size))))
                    return 0;
            }
            ;
        }
    }
    return 1;
}
static int compiler_formatted_value (struct compiler *c, expr_ty e){
    int conversion = e->v.FormattedValue.conversion;
    int oparg;
    {
        if (!compiler_visit_expr((c), (e->v.FormattedValue.value)))
            return 0;
    }
    ;
    switch (conversion) {
      case 's':
        oparg = 1;
        break;
      case 'r':
        oparg = 2;
        break;
      case 'a':
        oparg = 3;
        break;
      case -1:
        oparg = 0;
        break;
      default:
        ;
        return 0;
    }
    if (e->v.FormattedValue.format_spec) {
        {
            if (!compiler_visit_expr((c), (e->v.FormattedValue.format_spec)))
                return 0;
        }
        ;
        oparg |= 4;
    }
    {
        if (!compiler_addop_i((c), (155), (oparg)))
            return 0;
    }
    ;
    return 1;
}
static int compiler_subkwargs (struct compiler *c, asdl_keyword_seq *keywords, Py_ssize_t begin, Py_ssize_t end){
    Py_ssize_t i, n = end - begin;
    keyword_ty kw;
    PyObject *keys, *key;
    int big = n * 2 > 30;
    if (n > 1 && !big) {
        for (i = begin; i < end; i++) {
            kw = (keywords)->typed_elements[(i)];
            {
                if (!compiler_visit_expr((c), (kw->value)))
                    return 0;
            }
            ;
        }
        keys = PyTuple_New(n);
        if (keys == ((void *)0)) {
            return 0;
        }
        for (i = begin; i < end; i++) {
            key = ((keyword_ty)(keywords)->typed_elements[(i)])->arg;
            _Py_INCREF(((PyObject *)(key)));
            ((void)((((void)(0)) , (PyTupleObject *)(keys))->ob_item[i - begin] = key));
        }
        {
            PyObject *__new_const = (keys);
            if (__new_const == ((void *)0)) {
                return 0;
            }
            if (!compiler_addop_load_const((c), __new_const)) {
                _Py_DECREF(((PyObject *)(__new_const)));
                return 0;
            }
            _Py_DECREF(((PyObject *)(__new_const)));
        }
        ;
        {
            if (!compiler_addop_i((c), (156), (n)))
                return 0;
        }
        ;
        return 1;
    }
    if (big) {
        {
            if (!compiler_addop_i_noline((c), (105), (0)))
                return 0;
        }
        ;
    }
    for (i = begin; i < end; i++) {
        kw = (keywords)->typed_elements[(i)];
        {
            if (!compiler_addop_load_const((c), (kw->arg)))
                return 0;
        }
        ;
        {
            if (!compiler_visit_expr((c), (kw->value)))
                return 0;
        }
        ;
        if (big) {
            {
                if (!compiler_addop_i_noline((c), (147), (1)))
                    return 0;
            }
            ;
        }
    }
    if (!big) {
        {
            if (!compiler_addop_i((c), (105), (n)))
                return 0;
        }
        ;
    }
    return 1;
}
static int compiler_call_helper (struct compiler *c, int n, asdl_expr_seq *args, asdl_keyword_seq *keywords){
    Py_ssize_t i, nseen, nelts, nkwelts;
    if (validate_keywords(c, keywords) == -1) {
        return 0;
    }
    nelts = ((args) == ((void *)0) ? 0 : (args)->size);
    nkwelts = ((keywords) == ((void *)0) ? 0 : (keywords)->size);
    if (nelts + nkwelts * 2 > 30) {
        goto ex_call;
    }
    for (i = 0; i < nelts; i++) {
        expr_ty elt = (args)->typed_elements[(i)];
        if (elt->kind == Starred_kind) {
            goto ex_call;
        }
    }
    for (i = 0; i < nkwelts; i++) {
        keyword_ty kw = (keywords)->typed_elements[(i)];
        if (kw->arg == ((void *)0)) {
            goto ex_call;
        }
    }
    for (i = 0; i < nelts; i++) {
        expr_ty elt = (args)->typed_elements[(i)];
        {
            if (!compiler_visit_expr((c), (elt)))
                return 0;
        }
        ;
    }
    if (nkwelts) {
        PyObject *names;
        {
            int _i;
            asdl_keyword_seq *seq = (keywords);
            for (_i = 0; _i < ((seq) == ((void *)0) ? 0 : (seq)->size); _i++) {
                keyword_ty elt = (keyword_ty)(seq)->typed_elements[(_i)];
                if (!compiler_visit_keyword((c), elt))
                    return 0;
            }
        }
        ;
        names = PyTuple_New(nkwelts);
        if (names == ((void *)0)) {
            return 0;
        }
        for (i = 0; i < nkwelts; i++) {
            keyword_ty kw = (keywords)->typed_elements[(i)];
            _Py_INCREF(((PyObject *)(kw->arg)));
            ((void)((((void)(0)) , (PyTupleObject *)(names))->ob_item[i] = kw->arg));
        }
        {
            PyObject *__new_const = (names);
            if (__new_const == ((void *)0)) {
                return 0;
            }
            if (!compiler_addop_load_const((c), __new_const)) {
                _Py_DECREF(((PyObject *)(__new_const)));
                return 0;
            }
            _Py_DECREF(((PyObject *)(__new_const)));
        }
        ;
        {
            if (!compiler_addop_i((c), (141), (n + nelts + nkwelts)))
                return 0;
        }
        ;
        return 1;
    } else {
        {
            if (!compiler_addop_i((c), (131), (n + nelts)))
                return 0;
        }
        ;
        return 1;
    }
  ex_call:
    if (n == 0 && nelts == 1 && ((expr_ty)(args)->typed_elements[(0)])->kind == Starred_kind) {
        {
            if (!compiler_visit_expr((c), (((expr_ty)(args)->typed_elements[(0)])->v.Starred.value)))
                return 0;
        }
        ;
    } else if (starunpack_helper(c, args, n, 103, 145, 162, 1) == 0) {
        return 0;
    }
    if (nkwelts) {
        int have_dict = 0;
        nseen = 0;
        for (i = 0; i < nkwelts; i++) {
            keyword_ty kw = (keywords)->typed_elements[(i)];
            if (kw->arg == ((void *)0)) {
                if (nseen) {
                    if (!compiler_subkwargs(c, keywords, i - nseen, i)) {
                        return 0;
                    }
                    if (have_dict) {
                        {
                            if (!compiler_addop_i((c), (164), (1)))
                                return 0;
                        }
                        ;
                    }
                    have_dict = 1;
                    nseen = 0;
                }
                if (!have_dict) {
                    {
                        if (!compiler_addop_i((c), (105), (0)))
                            return 0;
                    }
                    ;
                    have_dict = 1;
                }
                {
                    if (!compiler_visit_expr((c), (kw->value)))
                        return 0;
                }
                ;
                {
                    if (!compiler_addop_i((c), (164), (1)))
                        return 0;
                }
                ;
            } else {
                nseen++;
            }
        }
        if (nseen) {
            if (!compiler_subkwargs(c, keywords, nkwelts - nseen, nkwelts)) {
                return 0;
            }
            if (have_dict) {
                {
                    if (!compiler_addop_i((c), (164), (1)))
                        return 0;
                }
                ;
            }
            ;
        }
        ;
    }
    {
        if (!compiler_addop_i((c), (142), (nkwelts > 0)))
            return 0;
    }
    ;
    return 1;
}
static int compiler_comprehension_generator (struct compiler *c, asdl_comprehension_seq *generators, int gen_index, int depth, expr_ty elt, expr_ty val, int type){
    comprehension_ty gen;
    gen = (comprehension_ty)(generators)->typed_elements[(gen_index)];
    if (gen->is_async) {
        return compiler_async_comprehension_generator(c, generators, gen_index, depth, elt, val, type);
    } else {
        return compiler_sync_comprehension_generator(c, generators, gen_index, depth, elt, val, type);
    }
}
static int compiler_sync_comprehension_generator (struct compiler *c, asdl_comprehension_seq *generators, int gen_index, int depth, expr_ty elt, expr_ty val, int type){
    comprehension_ty gen;
    basicblock *start, *anchor, *skip, *if_cleanup;
    Py_ssize_t i, n;
    start = compiler_new_block(c);
    skip = compiler_new_block(c);
    if_cleanup = compiler_new_block(c);
    anchor = compiler_new_block(c);
    if (start == ((void *)0) || skip == ((void *)0) || if_cleanup == ((void *)0) || anchor == ((void *)0))
        return 0;
    gen = (comprehension_ty)(generators)->typed_elements[(gen_index)];
    if (gen_index == 0) {
        c->u->u_argcount = 1;
        {
            if (!compiler_addop_i((c), (124), (0)))
                return 0;
        }
        ;
    } else {
        asdl_expr_seq *elts;
        switch (gen->iter->kind) {
          case List_kind:
            elts = gen->iter->v.List.elts;
            break;
          case Tuple_kind:
            elts = gen->iter->v.Tuple.elts;
            break;
          default:
            elts = ((void *)0);
        }
        if (((elts) == ((void *)0) ? 0 : (elts)->size) == 1) {
            expr_ty elt = (elts)->typed_elements[(0)];
            if (elt->kind != Starred_kind) {
                {
                    if (!compiler_visit_expr((c), (elt)))
                        return 0;
                }
                ;
                start = ((void *)0);
            }
        }
        if (start) {
            {
                if (!compiler_visit_expr((c), (gen->iter)))
                    return 0;
            }
            ;
            {
                if (!compiler_addop((c), (68)))
                    return 0;
            }
            ;
        }
    }
    if (start) {
        depth++;
        compiler_use_next_block(c, start);
        {
            if (!compiler_addop_j((c), (93), (anchor)))
                return 0;
        }
        ;
        {
            if (compiler_next_block((c)) == ((void *)0))
                return 0;
        }
        ;
    }
    {
        if (!compiler_visit_expr((c), (gen->target)))
            return 0;
    }
    ;
    n = ((gen->ifs) == ((void *)0) ? 0 : (gen->ifs)->size);
    for (i = 0; i < n; i++) {
        expr_ty e = (expr_ty)(gen->ifs)->typed_elements[(i)];
        if (!compiler_jump_if(c, e, if_cleanup, 0))
            return 0;
        {
            if (compiler_next_block((c)) == ((void *)0))
                return 0;
        }
        ;
    }
    if (++gen_index < ((generators) == ((void *)0) ? 0 : (generators)->size))
        if (!compiler_comprehension_generator(c, generators, gen_index, depth, elt, val, type))
            return 0;
    if (gen_index >= ((generators) == ((void *)0) ? 0 : (generators)->size)) {
        switch (type) {
          case 0:
            {
                if (!compiler_visit_expr((c), (elt)))
                    return 0;
            }
            ;
            {
                if (!compiler_addop((c), (86)))
                    return 0;
            }
            ;
            {
                if (!compiler_addop((c), (1)))
                    return 0;
            }
            ;
            break;
          case 1:
            {
                if (!compiler_visit_expr((c), (elt)))
                    return 0;
            }
            ;
            {
                if (!compiler_addop_i((c), (145), (depth + 1)))
                    return 0;
            }
            ;
            break;
          case 2:
            {
                if (!compiler_visit_expr((c), (elt)))
                    return 0;
            }
            ;
            {
                if (!compiler_addop_i((c), (146), (depth + 1)))
                    return 0;
            }
            ;
            break;
          case 3:
            {
                if (!compiler_visit_expr((c), (elt)))
                    return 0;
            }
            ;
            {
                if (!compiler_visit_expr((c), (val)))
                    return 0;
            }
            ;
            {
                if (!compiler_addop_i((c), (147), (depth + 1)))
                    return 0;
            }
            ;
            break;
          default:
            return 0;
        }
        compiler_use_next_block(c, skip);
    }
    compiler_use_next_block(c, if_cleanup);
    if (start) {
        {
            if (!compiler_addop_j((c), (113), (start)))
                return 0;
        }
        ;
        compiler_use_next_block(c, anchor);
    }
    return 1;
}
static int compiler_async_comprehension_generator (struct compiler *c, asdl_comprehension_seq *generators, int gen_index, int depth, expr_ty elt, expr_ty val, int type){
    comprehension_ty gen;
    basicblock *start, *if_cleanup, *except;
    Py_ssize_t i, n;
    start = compiler_new_block(c);
    except = compiler_new_block(c);
    if_cleanup = compiler_new_block(c);
    if (start == ((void *)0) || if_cleanup == ((void *)0) || except == ((void *)0)) {
        return 0;
    }
    gen = (comprehension_ty)(generators)->typed_elements[(gen_index)];
    if (gen_index == 0) {
        c->u->u_argcount = 1;
        {
            if (!compiler_addop_i((c), (124), (0)))
                return 0;
        }
        ;
    } else {
        {
            if (!compiler_visit_expr((c), (gen->iter)))
                return 0;
        }
        ;
        {
            if (!compiler_addop((c), (50)))
                return 0;
        }
        ;
    }
    compiler_use_next_block(c, start);
    if (!compiler_push_fblock(c, ASYNC_COMPREHENSION_GENERATOR, start, ((void *)0), ((void *)0))) {
        return 0;
    }
    {
        if (!compiler_addop_j((c), (122), (except)))
            return 0;
    }
    ;
    {
        if (!compiler_addop((c), (51)))
            return 0;
    }
    ;
    {
        if (!compiler_addop_load_const((c), ((&_Py_NoneStruct))))
            return 0;
    }
    ;
    {
        if (!compiler_addop((c), (72)))
            return 0;
    }
    ;
    {
        if (!compiler_addop((c), (87)))
            return 0;
    }
    ;
    {
        if (!compiler_visit_expr((c), (gen->target)))
            return 0;
    }
    ;
    n = ((gen->ifs) == ((void *)0) ? 0 : (gen->ifs)->size);
    for (i = 0; i < n; i++) {
        expr_ty e = (expr_ty)(gen->ifs)->typed_elements[(i)];
        if (!compiler_jump_if(c, e, if_cleanup, 0))
            return 0;
        {
            if (compiler_next_block((c)) == ((void *)0))
                return 0;
        }
        ;
    }
    depth++;
    if (++gen_index < ((generators) == ((void *)0) ? 0 : (generators)->size))
        if (!compiler_comprehension_generator(c, generators, gen_index, depth, elt, val, type))
            return 0;
    if (gen_index >= ((generators) == ((void *)0) ? 0 : (generators)->size)) {
        switch (type) {
          case 0:
            {
                if (!compiler_visit_expr((c), (elt)))
                    return 0;
            }
            ;
            {
                if (!compiler_addop((c), (86)))
                    return 0;
            }
            ;
            {
                if (!compiler_addop((c), (1)))
                    return 0;
            }
            ;
            break;
          case 1:
            {
                if (!compiler_visit_expr((c), (elt)))
                    return 0;
            }
            ;
            {
                if (!compiler_addop_i((c), (145), (depth + 1)))
                    return 0;
            }
            ;
            break;
          case 2:
            {
                if (!compiler_visit_expr((c), (elt)))
                    return 0;
            }
            ;
            {
                if (!compiler_addop_i((c), (146), (depth + 1)))
                    return 0;
            }
            ;
            break;
          case 3:
            {
                if (!compiler_visit_expr((c), (elt)))
                    return 0;
            }
            ;
            {
                if (!compiler_visit_expr((c), (val)))
                    return 0;
            }
            ;
            {
                if (!compiler_addop_i((c), (147), (depth + 1)))
                    return 0;
            }
            ;
            break;
          default:
            return 0;
        }
    }
    compiler_use_next_block(c, if_cleanup);
    {
        if (!compiler_addop_j((c), (113), (start)))
            return 0;
    }
    ;
    compiler_pop_fblock(c, ASYNC_COMPREHENSION_GENERATOR, start);
    compiler_use_next_block(c, except);
    {
        if (!compiler_addop((c), (54)))
            return 0;
    }
    ;
    return 1;
}
static int compiler_comprehension (struct compiler *c, expr_ty e, int type, identifier name, asdl_comprehension_seq *generators, expr_ty elt, expr_ty val){
    PyCodeObject *co = ((void *)0);
    comprehension_ty outermost;
    PyObject *qualname = ((void *)0);
    int is_async_generator = 0;
    int top_level_await = ((c->c_flags->cf_flags & 8192) && (c->u->u_ste->ste_type == ModuleBlock));
    int is_async_function = c->u->u_ste->ste_coroutine;
    outermost = (comprehension_ty)(generators)->typed_elements[(0)];
    if (!compiler_enter_scope(c, name, COMPILER_SCOPE_COMPREHENSION, (void *)e, e->lineno)) {
        goto error;
    }
    (c)->u->u_lineno = (e)->lineno;
    (c)->u->u_col_offset = (e)->col_offset;
    (c)->u->u_end_lineno = (e)->end_lineno;
    (c)->u->u_end_col_offset = (e)->end_col_offset;
    is_async_generator = c->u->u_ste->ste_coroutine;
    if (is_async_generator && !is_async_function && type != 0 && !top_level_await) {
        compiler_error(c, "asynchronous comprehension outside of an asynchronous function");
        goto error_in_scope;
    }
    if (type != 0) {
        int op;
        switch (type) {
          case 1:
            op = 103;
            break;
          case 2:
            op = 104;
            break;
          case 3:
            op = 105;
            break;
          default:
            ;
            goto error_in_scope;
        }
        {
            if (!compiler_addop_i((c), (op), (0)))
                return 0;
        }
        ;
    }
    if (!compiler_comprehension_generator(c, generators, 0, 0, elt, val, type))
        goto error_in_scope;
    if (type != 0) {
        {
            if (!compiler_addop((c), (83)))
                return 0;
        }
        ;
    }
    co = assemble(c, 1);
    qualname = c->u->u_qualname;
    _Py_INCREF(((PyObject *)(qualname)));
    compiler_exit_scope(c);
    if (top_level_await && is_async_generator) {
        c->u->u_ste->ste_coroutine = 1;
    }
    if (co == ((void *)0))
        goto error;
    if (!compiler_make_closure(c, co, 0, qualname)) {
        goto error;
    }
    _Py_DECREF(((PyObject *)(qualname)));
    _Py_DECREF(((PyObject *)(co)));
    {
        if (!compiler_visit_expr((c), (outermost->iter)))
            return 0;
    }
    ;
    if (outermost->is_async) {
        {
            if (!compiler_addop((c), (50)))
                return 0;
        }
        ;
    } else {
        {
            if (!compiler_addop((c), (68)))
                return 0;
        }
        ;
    }
    {
        if (!compiler_addop_i((c), (131), (1)))
            return 0;
    }
    ;
    if (is_async_generator && type != 0) {
        {
            if (!compiler_addop((c), (73)))
                return 0;
        }
        ;
        {
            if (!compiler_addop_load_const((c), ((&_Py_NoneStruct))))
                return 0;
        }
        ;
        {
            if (!compiler_addop((c), (72)))
                return 0;
        }
        ;
    }
    return 1;
  error_in_scope:
    compiler_exit_scope(c);
  error:
    _Py_XDECREF(((PyObject *)(qualname)));
    _Py_XDECREF(((PyObject *)(co)));
    return 0;
}
static int compiler_genexp (struct compiler *c, expr_ty e){
    static identifier name;
    if (!name) {
        name = PyUnicode_InternFromString("<genexpr>");
        if (!name)
            return 0;
    }
    ;
    return compiler_comprehension(c, e, 0, name, e->v.GeneratorExp.generators, e->v.GeneratorExp.elt, ((void *)0));
}
static int compiler_listcomp (struct compiler *c, expr_ty e){
    static identifier name;
    if (!name) {
        name = PyUnicode_InternFromString("<listcomp>");
        if (!name)
            return 0;
    }
    ;
    return compiler_comprehension(c, e, 1, name, e->v.ListComp.generators, e->v.ListComp.elt, ((void *)0));
}
static int compiler_setcomp (struct compiler *c, expr_ty e){
    static identifier name;
    if (!name) {
        name = PyUnicode_InternFromString("<setcomp>");
        if (!name)
            return 0;
    }
    ;
    return compiler_comprehension(c, e, 2, name, e->v.SetComp.generators, e->v.SetComp.elt, ((void *)0));
}
static int compiler_dictcomp (struct compiler *c, expr_ty e){
    static identifier name;
    if (!name) {
        name = PyUnicode_InternFromString("<dictcomp>");
        if (!name)
            return 0;
    }
    ;
    return compiler_comprehension(c, e, 3, name, e->v.DictComp.generators, e->v.DictComp.key, e->v.DictComp.value);
}
static int compiler_visit_keyword (struct compiler *c, keyword_ty k){
    {
        if (!compiler_visit_expr((c), (k->value)))
            return 0;
    }
    ;
    return 1;
}
static int compiler_visit_expr1 (struct compiler *c, expr_ty e){
    switch (e->kind) {
      case NamedExpr_kind:
        {
            if (!compiler_visit_expr((c), (e->v.NamedExpr.value)))
                return 0;
        }
        ;
        {
            if (!compiler_addop((c), (4)))
                return 0;
        }
        ;
        {
            if (!compiler_visit_expr((c), (e->v.NamedExpr.target)))
                return 0;
        }
        ;
        break;
      case BoolOp_kind:
        return compiler_boolop(c, e);
      case BinOp_kind:
        {
            if (!compiler_visit_expr((c), (e->v.BinOp.left)))
                return 0;
        }
        ;
        {
            if (!compiler_visit_expr((c), (e->v.BinOp.right)))
                return 0;
        }
        ;
        {
            if (!compiler_addop((c), (binop(e->v.BinOp.op))))
                return 0;
        }
        ;
        break;
      case UnaryOp_kind:
        {
            if (!compiler_visit_expr((c), (e->v.UnaryOp.operand)))
                return 0;
        }
        ;
        {
            if (!compiler_addop((c), (unaryop(e->v.UnaryOp.op))))
                return 0;
        }
        ;
        break;
      case Lambda_kind:
        return compiler_lambda(c, e);
      case IfExp_kind:
        return compiler_ifexp(c, e);
      case Dict_kind:
        return compiler_dict(c, e);
      case Set_kind:
        return compiler_set(c, e);
      case GeneratorExp_kind:
        return compiler_genexp(c, e);
      case ListComp_kind:
        return compiler_listcomp(c, e);
      case SetComp_kind:
        return compiler_setcomp(c, e);
      case DictComp_kind:
        return compiler_dictcomp(c, e);
      case Yield_kind:
        if (c->u->u_ste->ste_type != FunctionBlock)
            return compiler_error(c, "'yield' outside function");
        if (e->v.Yield.value) {
            {
                if (!compiler_visit_expr((c), (e->v.Yield.value)))
                    return 0;
            }
            ;
        } else {
            {
                if (!compiler_addop_load_const((c), ((&_Py_NoneStruct))))
                    return 0;
            }
            ;
        }
        {
            if (!compiler_addop((c), (86)))
                return 0;
        }
        ;
        break;
      case YieldFrom_kind:
        if (c->u->u_ste->ste_type != FunctionBlock)
            return compiler_error(c, "'yield' outside function");
        if (c->u->u_scope_type == COMPILER_SCOPE_ASYNC_FUNCTION)
            return compiler_error(c, "'yield from' inside async function");
        {
            if (!compiler_visit_expr((c), (e->v.YieldFrom.value)))
                return 0;
        }
        ;
        {
            if (!compiler_addop((c), (69)))
                return 0;
        }
        ;
        {
            if (!compiler_addop_load_const((c), ((&_Py_NoneStruct))))
                return 0;
        }
        ;
        {
            if (!compiler_addop((c), (72)))
                return 0;
        }
        ;
        break;
      case Await_kind:
        if (!((c->c_flags->cf_flags & 8192) && (c->u->u_ste->ste_type == ModuleBlock))) {
            if (c->u->u_ste->ste_type != FunctionBlock) {
                return compiler_error(c, "'await' outside function");
            }
            if (c->u->u_scope_type != COMPILER_SCOPE_ASYNC_FUNCTION && c->u->u_scope_type != COMPILER_SCOPE_COMPREHENSION) {
                return compiler_error(c, "'await' outside async function");
            }
        }
        {
            if (!compiler_visit_expr((c), (e->v.Await.value)))
                return 0;
        }
        ;
        {
            if (!compiler_addop((c), (73)))
                return 0;
        }
        ;
        {
            if (!compiler_addop_load_const((c), ((&_Py_NoneStruct))))
                return 0;
        }
        ;
        {
            if (!compiler_addop((c), (72)))
                return 0;
        }
        ;
        break;
      case Compare_kind:
        return compiler_compare(c, e);
      case Call_kind:
        return compiler_call(c, e);
      case Constant_kind:
        {
            if (!compiler_addop_load_const((c), (e->v.Constant.value)))
                return 0;
        }
        ;
        break;
      case JoinedStr_kind:
        return compiler_joined_str(c, e);
      case FormattedValue_kind:
        return compiler_formatted_value(c, e);
      case Attribute_kind:
        {
            if (!compiler_visit_expr((c), (e->v.Attribute.value)))
                return 0;
        }
        ;
        switch (e->v.Attribute.ctx) {
          case Load:
            {
                int old_lineno = c->u->u_lineno;
                c->u->u_lineno = e->end_lineno;
                {
                    if (!compiler_addop_name((c), (106), (c)->u->u_names, (e->v.Attribute.attr)))
                        return 0;
                }
                ;
                c->u->u_lineno = old_lineno;
                break;
            }
          case Store:
            if (forbidden_name(c, e->v.Attribute.attr, e->v.Attribute.ctx)) {
                return 0;
            }
            int old_lineno = c->u->u_lineno;
            c->u->u_lineno = e->end_lineno;
            {
                if (!compiler_addop_name((c), (95), (c)->u->u_names, (e->v.Attribute.attr)))
                    return 0;
            }
            ;
            c->u->u_lineno = old_lineno;
            break;
          case Del:
            {
                if (!compiler_addop_name((c), (96), (c)->u->u_names, (e->v.Attribute.attr)))
                    return 0;
            }
            ;
            break;
        }
        break;
      case Subscript_kind:
        return compiler_subscript(c, e);
      case Starred_kind:
        switch (e->v.Starred.ctx) {
          case Store:
            return compiler_error(c, "starred assignment target must be in a list or tuple");
          default:
            return compiler_error(c, "can't use starred expression here");
        }
        break;
      case Slice_kind:
        return compiler_slice(c, e);
      case Name_kind:
        return compiler_nameop(c, e->v.Name.id, e->v.Name.ctx);
      case List_kind:
        return compiler_list(c, e);
      case Tuple_kind:
        return compiler_tuple(c, e);
    }
    return 1;
}
static int compiler_visit_expr (struct compiler *c, expr_ty e){
    int old_lineno = c->u->u_lineno;
    int old_end_lineno = c->u->u_end_lineno;
    int old_col_offset = c->u->u_col_offset;
    int old_end_col_offset = c->u->u_end_col_offset;
    (c)->u->u_lineno = (e)->lineno;
    (c)->u->u_col_offset = (e)->col_offset;
    (c)->u->u_end_lineno = (e)->end_lineno;
    (c)->u->u_end_col_offset = (e)->end_col_offset;
    int res = compiler_visit_expr1(c, e);
    c->u->u_lineno = old_lineno;
    c->u->u_end_lineno = old_end_lineno;
    c->u->u_col_offset = old_col_offset;
    c->u->u_end_col_offset = old_end_col_offset;
    return res;
}
static int compiler_error (struct compiler *c, const char *format, ...){
    va_list vargs;
    __builtin_va_start(vargs, format);
    PyObject *msg = PyUnicode_FromFormatV(format, vargs);
    if (msg == ((void *)0)) {
        return 0;
    }
    PyObject *loc = PyErr_ProgramTextObject(c->c_filename, c->u->u_lineno);
    if (loc == ((void *)0)) {
        _Py_INCREF(((PyObject *)((&_Py_NoneStruct))));
        loc = (&_Py_NoneStruct);
    }
    PyObject *args = Py_BuildValue("O(OiiOii)", msg, c->c_filename, c->u->u_lineno, c->u->u_col_offset + 1, loc, c->u->u_end_lineno, c->u->u_end_col_offset + 1);
    _Py_DECREF(((PyObject *)(msg)));
  exit:
    _Py_DECREF(((PyObject *)(loc)));
    _Py_XDECREF(((PyObject *)(args)));
    return 0;
}
static int compiler_warn (struct compiler *c, const char *format, ...){
    va_list vargs;
    __builtin_va_start(vargs, format);
    PyObject *msg = PyUnicode_FromFormatV(format, vargs);
    if (msg == ((void *)0)) {
        return 0;
    }
    if (PyErr_WarnExplicitObject(PyExc_SyntaxWarning, msg, c->c_filename, c->u->u_lineno, ((void *)0), ((void *)0)) < 0) {
        if (PyErr_ExceptionMatches(PyExc_SyntaxWarning)) {
            ;
            compiler_error(c, PyUnicode_AsUTF8(msg));
        }
        _Py_DECREF(((PyObject *)(msg)));
        return 0;
    }
    _Py_DECREF(((PyObject *)(msg)));
    return 1;
}
static int compiler_subscript (struct compiler *c, expr_ty e){
    expr_context_ty ctx = e->v.Subscript.ctx;
    int op = 0;
    if (ctx == Load) {
        if (!check_subscripter(c, e->v.Subscript.value)) {
            return 0;
        }
        if (!check_index(c, e->v.Subscript.value, e->v.Subscript.slice)) {
            return 0;
        }
    }
    switch (ctx) {
      case Load:
        op = 25;
        break;
      case Store:
        op = 60;
        break;
      case Del:
        op = 61;
        break;
    }
    ;
    {
        if (!compiler_visit_expr((c), (e->v.Subscript.value)))
            return 0;
    }
    ;
    {
        if (!compiler_visit_expr((c), (e->v.Subscript.slice)))
            return 0;
    }
    ;
    {
        if (!compiler_addop((c), (op)))
            return 0;
    }
    ;
    return 1;
}
static int compiler_slice (struct compiler *c, expr_ty s){
    int n = 2;
    if (s->v.Slice.lower) {
        {
            if (!compiler_visit_expr((c), (s->v.Slice.lower)))
                return 0;
        }
        ;
    } else {
        {
            if (!compiler_addop_load_const((c), ((&_Py_NoneStruct))))
                return 0;
        }
        ;
    }
    if (s->v.Slice.upper) {
        {
            if (!compiler_visit_expr((c), (s->v.Slice.upper)))
                return 0;
        }
        ;
    } else {
        {
            if (!compiler_addop_load_const((c), ((&_Py_NoneStruct))))
                return 0;
        }
        ;
    }
    if (s->v.Slice.step) {
        n++;
        {
            if (!compiler_visit_expr((c), (s->v.Slice.step)))
                return 0;
        }
        ;
    }
    {
        if (!compiler_addop_i((c), (133), (n)))
            return 0;
    }
    ;
    return 1;
}
static inline void stackdepth_push (basicblock ***sp, basicblock *b, int depth){
    ;
    if (b->b_startdepth < depth && b->b_startdepth < 100) {
        ;
        b->b_startdepth = depth;
        *(*sp)++ = b;
    }
}
static int stackdepth (struct compiler *c){
    basicblock *b, *entryblock = ((void *)0);
    basicblock **stack, **sp;
    int nblocks = 0, maxdepth = 0;
    for (b = c->u->u_blocks; b != ((void *)0); b = b->b_list) {
        b->b_startdepth = (-2147483647 - 1);
        entryblock = b;
        nblocks++;
    }
    ;
    stack = (basicblock **)PyObject_Malloc(sizeof(basicblock *) * nblocks);
    if (!stack) {
        ;
        return -1;
    }
    sp = stack;
    if (c->u->u_ste->ste_generator || c->u->u_ste->ste_coroutine) {
        stackdepth_push(&sp, entryblock, 1);
    } else {
        stackdepth_push(&sp, entryblock, 0);
    }
    while (sp != stack)
        {
            b = *--sp;
            int depth = b->b_startdepth;
            basicblock *next = b->b_next;
            for (int i = 0; i < b->b_iused; i++) {
                struct instr *instr = &b->b_instr[i];
                int effect = stack_effect(instr->i_opcode, instr->i_oparg, 0);
                if (effect == 2147483647) {
                    ;
                    return -1;
                }
                int new_depth = depth + effect;
                if (new_depth > maxdepth) {
                    maxdepth = new_depth;
                }
                ;
                if (is_jump(instr)) {
                    effect = stack_effect(instr->i_opcode, instr->i_oparg, 1);
                    int target_depth = depth + effect;
                    stackdepth_push(&sp, instr->i_target, target_depth);
                }
                depth = new_depth;
                if (instr->i_opcode == 113 || instr->i_opcode == 110 || instr->i_opcode == 83 || instr->i_opcode == 130 || instr->i_opcode == 119) {
                    next = ((void *)0);
                    break;
                }
            }
            if (next != ((void *)0)) {
                ;
                stackdepth_push(&sp, next, depth);
            }
        }
    ;
    return maxdepth;
}
static int assemble_init (struct assembler *a, int nblocks, int firstlineno){
    memset(a, 0, sizeof(struct assembler));
    a->a_prevlineno = a->a_lineno = firstlineno;
    a->a_lnotab = ((void *)0);
    a->a_bytecode = PyBytes_FromStringAndSize(((void *)0), 128);
    if (a->a_bytecode == ((void *)0)) {
        goto error;
    }
    a->a_lnotab = PyBytes_FromStringAndSize(((void *)0), 16);
    if (a->a_lnotab == ((void *)0)) {
        goto error;
    }
    if ((size_t)nblocks > (18446744073709551615UL) / sizeof(basicblock *)) {
        ;
        goto error;
    }
    return 1;
  error:
    _Py_XDECREF(((PyObject *)(a->a_bytecode)));
    _Py_XDECREF(((PyObject *)(a->a_lnotab)));
    return 0;
}
static void assemble_free (struct assembler *a){
    _Py_XDECREF(((PyObject *)(a->a_bytecode)));
    _Py_XDECREF(((PyObject *)(a->a_lnotab)));
}
static int blocksize (basicblock *b){
    int i;
    int size = 0;
    for (i = 0; i < b->b_iused; i++)
        size += instrsize(b->b_instr[i].i_oparg);
    return size;
}
static int assemble_emit_linetable_pair (struct assembler *a, int bdelta, int ldelta){
    Py_ssize_t len = (((void)(0)) , (((PyVarObject *)(a->a_lnotab))->ob_size));
    if (a->a_lnotab_off > 2147483647 - 2) {
        goto overflow;
    }
    if (a->a_lnotab_off >= len - 2) {
        if (len > 2147483647 / 2) {
            goto overflow;
        }
        if (_PyBytes_Resize(&a->a_lnotab, len * 2) < 0) {
            return 0;
        }
    }
    unsigned char *lnotab = (unsigned char *)(((void)(0)) , (((PyBytesObject *)(a->a_lnotab))->ob_sval));
    lnotab += a->a_lnotab_off;
    a->a_lnotab_off += 2;
    *lnotab++ = bdelta;
    *lnotab++ = ldelta;
    return 1;
  overflow:
    ;
    return 0;
}
static int assemble_line_range (struct assembler *a){
    int ldelta, bdelta;
    bdelta = (a->a_offset - a->a_lineno_start) * sizeof(_Py_CODEUNIT);
    if (bdelta == 0) {
        return 1;
    }
    if (a->a_lineno < 0) {
        ldelta = -128;
    } else {
        ldelta = a->a_lineno - a->a_prevlineno;
        a->a_prevlineno = a->a_lineno;
        while (ldelta > 127)
            {
                if (!assemble_emit_linetable_pair(a, 0, 127)) {
                    return 0;
                }
                ldelta -= 127;
            }
        while (ldelta < -127)
            {
                if (!assemble_emit_linetable_pair(a, 0, -127)) {
                    return 0;
                }
                ldelta += 127;
            }
    }
    ;
    while (bdelta > 254)
        {
            if (!assemble_emit_linetable_pair(a, 254, ldelta)) {
                return 0;
            }
            ldelta = a->a_lineno < 0 ? -128 : 0;
            bdelta -= 254;
        }
    if (!assemble_emit_linetable_pair(a, bdelta, ldelta)) {
        return 0;
    }
    a->a_lineno_start = a->a_offset;
    return 1;
}
static int assemble_lnotab (struct assembler *a, struct instr *i){
    if (i->i_lineno == a->a_lineno) {
        return 1;
    }
    if (!assemble_line_range(a)) {
        return 0;
    }
    a->a_lineno = i->i_lineno;
    return 1;
}
static int assemble_emit (struct assembler *a, struct instr *i){
    int size, arg = 0;
    Py_ssize_t len = (((void)(0)) , (((PyVarObject *)(a->a_bytecode))->ob_size));
    _Py_CODEUNIT *code;
    arg = i->i_oparg;
    size = instrsize(arg);
    if (i->i_lineno && !assemble_lnotab(a, i))
        return 0;
    if (a->a_offset > 2147483647 - size) {
        goto overflow;
    }
    if (a->a_offset + size >= len / (int)sizeof(_Py_CODEUNIT)) {
        if (len > 2147483647 / 2) {
            goto overflow;
        }
        if (_PyBytes_Resize(&a->a_bytecode, len * 2) < 0)
            return 0;
    }
    code = (_Py_CODEUNIT *)(((void)(0)) , (((PyBytesObject *)(a->a_bytecode))->ob_sval)) + a->a_offset;
    a->a_offset += size;
    write_op_arg(code, i->i_opcode, arg, size);
    return 1;
  overflow:
    ;
    return 0;
}
static void normalize_jumps (struct assembler *a){
    for (basicblock *b = a->a_entry; b != ((void *)0); b = b->b_next) {
        ;
    }
    for (basicblock *b = a->a_entry; b != ((void *)0); b = b->b_next) {
        ;
        if (b->b_iused == 0) {
            continue;
        }
        struct instr *last = &b->b_instr[b->b_iused - 1];
        if (last->i_opcode == 113) {
            if (last->i_target->b_visited == 0) {
                last->i_opcode = 110;
            }
        }
        if (last->i_opcode == 110) {
            if (last->i_target->b_visited == 1) {
                last->i_opcode = 113;
            }
        }
    }
}
static void assemble_jump_offsets (struct assembler *a, struct compiler *c){
    basicblock *b;
    int bsize, totsize, extended_arg_recompile;
    int i;
    do {
        totsize = 0;
        for (basicblock *b = a->a_entry; b != ((void *)0); b = b->b_next) {
            bsize = blocksize(b);
            b->b_offset = totsize;
            totsize += bsize;
        }
        extended_arg_recompile = 0;
        for (b = c->u->u_blocks; b != ((void *)0); b = b->b_list) {
            bsize = b->b_offset;
            for (i = 0; i < b->b_iused; i++) {
                struct instr *instr = &b->b_instr[i];
                int isize = instrsize(instr->i_oparg);
                bsize += isize;
                if (is_jump(instr)) {
                    instr->i_oparg = instr->i_target->b_offset;
                    if (is_relative_jump(instr)) {
                        instr->i_oparg -= bsize;
                    }
                    if (instrsize(instr->i_oparg) != isize) {
                        extended_arg_recompile = 1;
                    }
                }
            }
        }
    } while (extended_arg_recompile);
}
static PyObject * dict_keys_inorder (PyObject *dict, Py_ssize_t offset){
    PyObject *tuple, *k, *v;
    Py_ssize_t i, pos = 0, size = (((void)(0)) , ((PyDictObject *)dict)->ma_used);
    tuple = PyTuple_New(size);
    if (tuple == ((void *)0))
        return ((void *)0);
    while (PyDict_Next(dict, &pos, &k, &v))
        {
            i = PyLong_AsLong(v);
            _Py_INCREF(((PyObject *)(k)));
            ((void)((((void)(0)) , (PyTupleObject *)(tuple))->ob_item[i - offset] = k));
        }
    return tuple;
}
static PyObject * consts_dict_keys_inorder (PyObject *dict){
    PyObject *consts, *k, *v;
    Py_ssize_t i, pos = 0, size = (((void)(0)) , ((PyDictObject *)dict)->ma_used);
    consts = PyList_New(size);
    if (consts == ((void *)0))
        return ((void *)0);
    while (PyDict_Next(dict, &pos, &k, &v))
        {
            i = PyLong_AsLong(v);
            if (_Py_IS_TYPE(((const PyObject *)(k)), &PyTuple_Type)) {
                k = ((((void)(0)) , (PyTupleObject *)(k))->ob_item[1]);
            }
            _Py_INCREF(((PyObject *)(k)));
            ((void)((((void)(0)) , (PyListObject *)(consts))->ob_item[i] = (k)));
        }
    return consts;
}
static int compute_code_flags (struct compiler *c){
    PySTEntryObject *ste = c->u->u_ste;
    int flags = 0;
    if (ste->ste_type == FunctionBlock) {
        flags |= 2 | 1;
        if (ste->ste_nested)
            flags |= 16;
        if (ste->ste_generator && !ste->ste_coroutine)
            flags |= 32;
        if (!ste->ste_generator && ste->ste_coroutine)
            flags |= 128;
        if (ste->ste_generator && ste->ste_coroutine)
            flags |= 512;
        if (ste->ste_varargs)
            flags |= 4;
        if (ste->ste_varkeywords)
            flags |= 8;
    }
    flags |= (c->c_flags->cf_flags & (131072 | 262144 | 524288 | 1048576 | 2097152 | 4194304 | 8388608 | 16777216));
    if ((((c->c_flags->cf_flags & 8192) && (c->u->u_ste->ste_type == ModuleBlock))) && ste->ste_coroutine && !ste->ste_generator) {
        flags |= 128;
    }
    return flags;
}
static int merge_const_one (struct compiler *c, PyObject **obj){
    PyObject *key = _PyCode_ConstantKey(*obj);
    if (key == ((void *)0)) {
        return 0;
    }
    PyObject *t = PyDict_SetDefault(c->c_const_cache, key, key);
    _Py_DECREF(((PyObject *)(key)));
    if (t == ((void *)0)) {
        return 0;
    }
    if (t == key) {
        return 1;
    }
    if (_Py_IS_TYPE(((const PyObject *)(t)), &PyTuple_Type)) {
        t = ((((void)(0)) , (PyTupleObject *)(t))->ob_item[1]);
    }
    _Py_INCREF(((PyObject *)(t)));
    _Py_DECREF(((PyObject *)(*obj)));
    *obj = t;
    return 1;
}
static PyCodeObject * makecode (struct compiler *c, struct assembler *a, PyObject *consts){
    PyCodeObject *co = ((void *)0);
    PyObject *names = ((void *)0);
    PyObject *varnames = ((void *)0);
    PyObject *name = ((void *)0);
    PyObject *freevars = ((void *)0);
    PyObject *cellvars = ((void *)0);
    Py_ssize_t nlocals;
    int nlocals_int;
    int flags;
    int posorkeywordargcount, posonlyargcount, kwonlyargcount, maxdepth;
    names = dict_keys_inorder(c->u->u_names, 0);
    varnames = dict_keys_inorder(c->u->u_varnames, 0);
    if (!names || !varnames) {
        goto error;
    }
    cellvars = dict_keys_inorder(c->u->u_cellvars, 0);
    if (!cellvars)
        goto error;
    freevars = dict_keys_inorder(c->u->u_freevars, (((PyVarObject *)((((void)(0)) , (PyTupleObject *)(cellvars))))->ob_size));
    if (!freevars)
        goto error;
    if (!merge_const_one(c, &names) || !merge_const_one(c, &varnames) || !merge_const_one(c, &cellvars) || !merge_const_one(c, &freevars)) {
        goto error;
    }
    nlocals = (((void)(0)) , ((PyDictObject *)c->u->u_varnames)->ma_used);
    nlocals_int = (int)(nlocals);
    flags = compute_code_flags(c);
    if (flags < 0)
        goto error;
    consts = PyList_AsTuple(consts);
    if (consts == ((void *)0)) {
        goto error;
    }
    if (!merge_const_one(c, &consts)) {
        _Py_DECREF(((PyObject *)(consts)));
        goto error;
    }
    posonlyargcount = (int)(c->u->u_posonlyargcount);
    posorkeywordargcount = (int)(c->u->u_argcount);
    kwonlyargcount = (int)(c->u->u_kwonlyargcount);
    maxdepth = stackdepth(c);
    if (maxdepth < 0) {
        _Py_DECREF(((PyObject *)(consts)));
        goto error;
    }
    co = PyCode_NewWithPosOnlyArgs(posonlyargcount + posorkeywordargcount, posonlyargcount, kwonlyargcount, nlocals_int, maxdepth, flags, a->a_bytecode, consts, names, varnames, freevars, cellvars, c->c_filename, c->u->u_name, c->u->u_firstlineno, a->a_lnotab);
    _Py_DECREF(((PyObject *)(consts)));
  error:
    _Py_XDECREF(((PyObject *)(names)));
    _Py_XDECREF(((PyObject *)(varnames)));
    _Py_XDECREF(((PyObject *)(name)));
    _Py_XDECREF(((PyObject *)(freevars)));
    _Py_XDECREF(((PyObject *)(cellvars)));
    return co;
}
static int insert_generator_prefix (struct compiler *c, basicblock *entryblock){
    int flags = compute_code_flags(c);
    if (flags < 0) {
        return -1;
    }
    int kind;
    if (flags & (32 | 128 | 512)) {
        if (flags & 128) {
            kind = 1;
        } else if (flags & 512) {
            kind = 2;
        } else {
            kind = 0;
        }
    } else {
        return 0;
    }
    if (compiler_next_instr(entryblock) < 0) {
        return -1;
    }
    entryblock->b_instr[0].i_opcode = 129;
    entryblock->b_instr[0].i_oparg = kind;
    entryblock->b_instr[0].i_lineno = -1;
    entryblock->b_instr[0].i_target = ((void *)0);
    return 0;
}
static void guarantee_lineno_for_exits (struct assembler *a, int firstlineno){
    int lineno = firstlineno;
    for (basicblock *b = a->a_entry; b != ((void *)0); b = b->b_next) {
        if (b->b_iused == 0) {
            continue;
        }
        struct instr *last = &b->b_instr[b->b_iused - 1];
        if (last->i_lineno < 0) {
            if (last->i_opcode == 83) {
                for (int i = 0; i < b->b_iused; i++) {
                    ;
                    b->b_instr[i].i_lineno = lineno;
                }
            }
        } else {
            lineno = last->i_lineno;
        }
    }
}
static PyCodeObject * assemble (struct compiler *c, int addNone){
    basicblock *b, *entryblock;
    struct assembler a;
    int j, nblocks;
    PyCodeObject *co = ((void *)0);
    PyObject *consts = ((void *)0);
    memset(&a, 0, sizeof(struct assembler));
    if (!c->u->u_curblock->b_return) {
        c->u->u_lineno = -1;
        if (addNone) {
            if (!compiler_addop_load_const((c), ((&_Py_NoneStruct))))
                return 0;
        }
        ;
        {
            if (!compiler_addop((c), (83)))
                return 0;
        }
        ;
    }
    for (basicblock *b = c->u->u_blocks; b != ((void *)0); b = b->b_list) {
        if (normalize_basic_block(b)) {
            return ((void *)0);
        }
    }
    for (basicblock *b = c->u->u_blocks; b != ((void *)0); b = b->b_list) {
        if (extend_block(b)) {
            return ((void *)0);
        }
    }
    nblocks = 0;
    entryblock = ((void *)0);
    for (b = c->u->u_blocks; b != ((void *)0); b = b->b_list) {
        nblocks++;
        entryblock = b;
    }
    ;
    if (insert_generator_prefix(c, entryblock)) {
        goto error;
    }
    if (!c->u->u_firstlineno) {
        if (entryblock->b_instr && entryblock->b_instr->i_lineno) {
            c->u->u_firstlineno = entryblock->b_instr->i_lineno;
        } else
            c->u->u_firstlineno = 1;
    }
    if (!assemble_init(&a, nblocks, c->u->u_firstlineno))
        goto error;
    a.a_entry = entryblock;
    a.a_nblocks = nblocks;
    consts = consts_dict_keys_inorder(c->u->u_consts);
    if (consts == ((void *)0)) {
        goto error;
    }
    if (optimize_cfg(c, &a, consts)) {
        goto error;
    }
    if (duplicate_exits_without_lineno(c)) {
        return ((void *)0);
    }
    if (trim_unused_consts(c, &a, consts)) {
        goto error;
    }
    propagate_line_numbers(&a);
    guarantee_lineno_for_exits(&a, c->u->u_firstlineno);
    normalize_jumps(&a);
    assemble_jump_offsets(&a, c);
    for (b = entryblock; b != ((void *)0); b = b->b_next) {
        for (j = 0; j < b->b_iused; j++)
            if (!assemble_emit(&a, &b->b_instr[j]))
                goto error;
    }
    if (!assemble_line_range(&a)) {
        return 0;
    }
    if (_PyBytes_Resize(&a.a_lnotab, a.a_lnotab_off) < 0) {
        goto error;
    }
    if (!merge_const_one(c, &a.a_lnotab)) {
        goto error;
    }
    if (_PyBytes_Resize(&a.a_bytecode, a.a_offset * sizeof(_Py_CODEUNIT)) < 0) {
        goto error;
    }
    if (!merge_const_one(c, &a.a_bytecode)) {
        goto error;
    }
    co = makecode(c, &a, consts);
  error:
    _Py_XDECREF(((PyObject *)(consts)));
    assemble_free(&a);
    return co;
}
static int fold_tuple_on_constants (struct compiler *c, struct instr *inst, int n, PyObject *consts){
    ;
    for (int i = 0; i < n; i++) {
        if (inst[i].i_opcode != 100) {
            return 0;
        }
    }
    PyObject *newconst = PyTuple_New(n);
    if (newconst == ((void *)0)) {
        return -1;
    }
    for (int i = 0; i < n; i++) {
        int arg = inst[i].i_oparg;
        PyObject *constant = ((((void)(0)) , (PyListObject *)(consts))->ob_item[arg]);
        _Py_INCREF(((PyObject *)(constant)));
        ((void)((((void)(0)) , (PyTupleObject *)(newconst))->ob_item[i] = constant));
    }
    if (merge_const_one(c, &newconst) == 0) {
        _Py_DECREF(((PyObject *)(newconst)));
        return -1;
    }
    Py_ssize_t index;
    for (index = 0; index < (((PyVarObject *)((((void)(0)) , (PyListObject *)(consts))))->ob_size); index++) {
        if (((((void)(0)) , (PyListObject *)(consts))->ob_item[index]) == newconst) {
            break;
        }
    }
    if (index == (((PyVarObject *)((((void)(0)) , (PyListObject *)(consts))))->ob_size)) {
        if ((size_t)index >= (size_t)2147483647 - 1) {
            _Py_DECREF(((PyObject *)(newconst)));
            return -1;
        }
        if (PyList_Append(consts, newconst)) {
            _Py_DECREF(((PyObject *)(newconst)));
            return -1;
        }
    }
    _Py_DECREF(((PyObject *)(newconst)));
    for (int i = 0; i < n; i++) {
        inst[i].i_opcode = 9;
    }
    inst[n].i_opcode = 100;
    inst[n].i_oparg = (int)index;
    return 0;
}
static void fold_rotations (struct instr *inst, int n){
    for (int i = 0; i < n; i++) {
        int rot;
        switch (inst[i].i_opcode) {
          case 99:
            rot = inst[i].i_oparg;
            break;
          case 6:
            rot = 4;
            break;
          case 3:
            rot = 3;
            break;
          case 2:
            rot = 2;
            break;
        }
        if (rot != n) {
            return;
        }
    }
    for (int i = 0; i < n; i++) {
        inst[i].i_opcode = 9;
    }
}
static _Bool jump_thread (struct instr *inst, struct instr *target, int opcode){
    ;
    if (inst->i_lineno == target->i_lineno && inst->i_target != target->i_target) {
        inst->i_target = target->i_target;
        inst->i_opcode = opcode;
        return 1;
    }
    return 0;
}
static int optimize_basic_block (struct compiler *c, basicblock *bb, PyObject *consts){
    ;
    struct instr nop;
    nop.i_opcode = 9;
    struct instr *target;
    for (int i = 0; i < bb->b_iused; i++) {
        struct instr *inst = &bb->b_instr[i];
        int oparg = inst->i_oparg;
        int nextop = i + 1 < bb->b_iused ? bb->b_instr[i + 1].i_opcode : 0;
        if (is_jump(inst)) {
            while (inst->i_target->b_iused == 0)
                {
                    inst->i_target = inst->i_target->b_next;
                }
            target = &inst->i_target->b_instr[0];
        } else {
            target = &nop;
        }
        switch (inst->i_opcode) {
          case 100:
            {
                PyObject *cnt;
                int is_true;
                int jump_if_true;
                switch (nextop) {
                  case 114:
                  case 115:
                    cnt = ((((void)(0)) , (PyListObject *)(consts))->ob_item[oparg]);
                    is_true = PyObject_IsTrue(cnt);
                    if (is_true == -1) {
                        goto error;
                    }
                    inst->i_opcode = 9;
                    jump_if_true = nextop == 115;
                    if (is_true == jump_if_true) {
                        bb->b_instr[i + 1].i_opcode = 113;
                    } else {
                        bb->b_instr[i + 1].i_opcode = 9;
                    }
                    break;
                  case 111:
                  case 112:
                    cnt = ((((void)(0)) , (PyListObject *)(consts))->ob_item[oparg]);
                    is_true = PyObject_IsTrue(cnt);
                    if (is_true == -1) {
                        goto error;
                    }
                    jump_if_true = nextop == 112;
                    if (is_true == jump_if_true) {
                        bb->b_instr[i + 1].i_opcode = 113;
                    } else {
                        inst->i_opcode = 9;
                        bb->b_instr[i + 1].i_opcode = 9;
                    }
                    break;
                }
                break;
            }
          case 102:
            if (nextop == 92 && oparg == bb->b_instr[i + 1].i_oparg) {
                switch (oparg) {
                  case 1:
                    inst->i_opcode = 9;
                    bb->b_instr[i + 1].i_opcode = 9;
                    break;
                  case 2:
                    inst->i_opcode = 2;
                    bb->b_instr[i + 1].i_opcode = 9;
                    break;
                  case 3:
                    inst->i_opcode = 3;
                    bb->b_instr[i + 1].i_opcode = 2;
                }
                break;
            }
            if (i >= oparg) {
                if (fold_tuple_on_constants(c, inst - oparg, oparg, consts)) {
                    goto error;
                }
            }
            break;
          case 111:
            switch (target->i_opcode) {
              case 114:
                i -= jump_thread(inst, target, 114);
                break;
              case 113:
              case 110:
              case 111:
                i -= jump_thread(inst, target, 111);
                break;
              case 112:
              case 115:
                if (inst->i_lineno == target->i_lineno) {
                    ;
                    inst->i_opcode = 114;
                    inst->i_target = inst->i_target->b_next;
                    --i;
                }
                break;
            }
            break;
          case 112:
            switch (target->i_opcode) {
              case 115:
                i -= jump_thread(inst, target, 115);
                break;
              case 113:
              case 110:
              case 112:
                i -= jump_thread(inst, target, 112);
                break;
              case 111:
              case 114:
                if (inst->i_lineno == target->i_lineno) {
                    ;
                    inst->i_opcode = 115;
                    inst->i_target = inst->i_target->b_next;
                    --i;
                }
                break;
            }
            break;
          case 114:
            switch (target->i_opcode) {
              case 113:
              case 110:
                i -= jump_thread(inst, target, 114);
            }
            break;
          case 115:
            switch (target->i_opcode) {
              case 113:
              case 110:
                i -= jump_thread(inst, target, 115);
            }
            break;
          case 113:
          case 110:
            switch (target->i_opcode) {
              case 113:
              case 110:
                i -= jump_thread(inst, target, 113);
            }
            break;
          case 93:
            if (target->i_opcode == 110) {
                i -= jump_thread(inst, target, 93);
            }
            break;
          case 99:
            switch (oparg) {
              case 0:
              case 1:
                inst->i_opcode = 9;
              case 2:
                inst->i_opcode = 2;
                break;
              case 3:
                inst->i_opcode = 3;
                break;
              case 4:
                inst->i_opcode = 6;
                break;
            }
            if (i >= oparg - 1) {
                fold_rotations(inst - oparg + 1, oparg);
            }
            break;
        }
    }
    return 0;
  error:
    return -1;
}
static int extend_block (basicblock *bb){
    if (bb->b_iused == 0) {
        return 0;
    }
    struct instr *last = &bb->b_instr[bb->b_iused - 1];
    if (last->i_opcode != 113 && last->i_opcode != 110) {
        return 0;
    }
    if (last->i_target->b_exit && last->i_target->b_iused <= 4) {
        basicblock *to_copy = last->i_target;
        last->i_opcode = 9;
        for (int i = 0; i < to_copy->b_iused; i++) {
            int index = compiler_next_instr(bb);
            if (index < 0) {
                return -1;
            }
            ;
        }
        bb->b_exit = 1;
    }
    return 0;
}
static void clean_basic_block (basicblock *bb, int prev_lineno){
    int dest = 0;
    for (int src = 0; src < bb->b_iused; src++) {
        int lineno = bb->b_instr[src].i_lineno;
        if (bb->b_instr[src].i_opcode == 9) {
            if (lineno < 0) {
                continue;
            }
            if (prev_lineno == lineno) {
                continue;
            }
            if (src < bb->b_iused - 1) {
                int next_lineno = bb->b_instr[src + 1].i_lineno;
                if (next_lineno < 0 || next_lineno == lineno) {
                    bb->b_instr[src + 1].i_lineno = lineno;
                    continue;
                }
            } else {
                basicblock *next = bb->b_next;
                while (next && next->b_iused == 0)
                    {
                        next = next->b_next;
                    }
                if (next) {
                    if (lineno == next->b_instr[0].i_lineno) {
                        continue;
                    }
                }
            }
        }
        dest++;
        prev_lineno = lineno;
    }
    ;
}
static int normalize_basic_block (basicblock *bb){
    for (int i = 0; i < bb->b_iused; i++) {
        switch (bb->b_instr[i].i_opcode) {
          case 83:
          case 130:
          case 119:
            bb->b_exit = 1;
            bb->b_nofallthrough = 1;
            break;
          case 113:
          case 110:
            bb->b_nofallthrough = 1;
          case 114:
          case 115:
          case 111:
          case 112:
          case 93:
            if (i != bb->b_iused - 1) {
                ;
                return -1;
            }
            while (bb->b_instr[i].i_target->b_iused == 0)
                {
                    bb->b_instr[i].i_target = bb->b_instr[i].i_target->b_next;
                }
        }
    }
    return 0;
}
static int mark_reachable (struct assembler *a){
    basicblock **stack, **sp;
    sp = stack = (basicblock **)PyObject_Malloc(sizeof(basicblock *) * a->a_nblocks);
    if (stack == ((void *)0)) {
        return -1;
    }
    ;
    *sp++ = a->a_entry;
    while (sp > stack)
        {
            basicblock *b = *(--sp);
            if (b->b_next && !b->b_nofallthrough) {
                if (b->b_next->b_predecessors == 0) {
                    *sp++ = b->b_next;
                }
                b->b_next->b_predecessors++;
            }
            for (int i = 0; i < b->b_iused; i++) {
                basicblock *target;
                if (is_jump(&b->b_instr[i])) {
                    target = b->b_instr[i].i_target;
                    if (target->b_predecessors == 0) {
                        *sp++ = target;
                    }
                    target->b_predecessors++;
                }
            }
        }
    ;
    return 0;
}
static void eliminate_empty_basic_blocks (basicblock *entry){
    for (basicblock *b = entry; b != ((void *)0); b = b->b_next) {
        basicblock *next = b->b_next;
        if (next) {
            while (next->b_iused == 0 && next->b_next)
                {
                    next = next->b_next;
                }
            ;
        }
    }
    for (basicblock *b = entry; b != ((void *)0); b = b->b_next) {
        if (b->b_iused == 0) {
            continue;
        }
        if (is_jump(&b->b_instr[b->b_iused - 1])) {
            basicblock *target = b->b_instr[b->b_iused - 1].i_target;
            while (target->b_iused == 0)
                {
                    target = target->b_next;
                }
            b->b_instr[b->b_iused - 1].i_target = target;
        }
    }
}
static void propagate_line_numbers (struct assembler *a){
    for (basicblock *b = a->a_entry; b != ((void *)0); b = b->b_next) {
        if (b->b_iused == 0) {
            continue;
        }
        int prev_lineno = -1;
        for (int i = 0; i < b->b_iused; i++) {
            if (b->b_instr[i].i_lineno < 0) {
                b->b_instr[i].i_lineno = prev_lineno;
            } else {
                prev_lineno = b->b_instr[i].i_lineno;
            }
        }
        if (!b->b_nofallthrough && b->b_next->b_predecessors == 1) {
            ;
            if (b->b_next->b_instr[0].i_lineno < 0) {
                b->b_next->b_instr[0].i_lineno = prev_lineno;
            }
        }
        if (is_jump(&b->b_instr[b->b_iused - 1])) {
            switch (b->b_instr[b->b_iused - 1].i_opcode) {
                ;
            }
            basicblock *target = b->b_instr[b->b_iused - 1].i_target;
            if (target->b_predecessors == 1) {
                if (target->b_instr[0].i_lineno < 0) {
                    target->b_instr[0].i_lineno = prev_lineno;
                }
            }
        }
    }
}
static int optimize_cfg (struct compiler *c, struct assembler *a, PyObject *consts){
    for (basicblock *b = a->a_entry; b != ((void *)0); b = b->b_next) {
        if (optimize_basic_block(c, b, consts)) {
            return -1;
        }
        clean_basic_block(b, -1);
    }
    for (basicblock *b = c->u->u_blocks; b != ((void *)0); b = b->b_list) {
        if (extend_block(b)) {
            return -1;
        }
    }
    if (mark_reachable(a)) {
        return -1;
    }
    for (basicblock *b = a->a_entry; b != ((void *)0); b = b->b_next) {
    }
    basicblock *pred = ((void *)0);
    for (basicblock *b = a->a_entry; b != ((void *)0); b = b->b_next) {
        int prev_lineno = -1;
        if (pred && pred->b_iused) {
            prev_lineno = pred->b_instr[pred->b_iused - 1].i_lineno;
        }
        clean_basic_block(b, prev_lineno);
        pred = b->b_nofallthrough ? ((void *)0) : b;
    }
    eliminate_empty_basic_blocks(a->a_entry);
    int maybe_empty_blocks = 0;
    for (basicblock *b = a->a_entry; b != ((void *)0); b = b->b_next) {
        if (b->b_iused > 0) {
            struct instr *b_last_instr = &b->b_instr[b->b_iused - 1];
            if (b_last_instr->i_opcode == 113 || b_last_instr->i_opcode == 110) {
                if (b_last_instr->i_target == b->b_next) {
                    ;
                    b_last_instr->i_opcode = 9;
                    clean_basic_block(b, -1);
                    maybe_empty_blocks = 1;
                }
            }
        }
    }
    if (maybe_empty_blocks) {
        eliminate_empty_basic_blocks(a->a_entry);
    }
    return 0;
}
static int trim_unused_consts (struct compiler *c, struct assembler *a, PyObject *consts){
    ;
    int max_const_index = 0;
    for (basicblock *b = a->a_entry; b != ((void *)0); b = b->b_next) {
        for (int i = 0; i < b->b_iused; i++) {
            if (b->b_instr[i].i_opcode == 100 && b->b_instr[i].i_oparg > max_const_index) {
                max_const_index = b->b_instr[i].i_oparg;
            }
        }
    }
    if (max_const_index + 1 < (((PyVarObject *)((((void)(0)) , (PyListObject *)(consts))))->ob_size)) {
        if (PyList_SetSlice(consts, max_const_index + 1, (((PyVarObject *)((((void)(0)) , (PyListObject *)(consts))))->ob_size), ((void *)0)) < 0) {
            return 1;
        }
    }
    return 0;
}
static inline int is_exit_without_lineno (basicblock *b){
    return b->b_exit && b->b_instr[0].i_lineno < 0;
}
static int duplicate_exits_without_lineno (struct compiler *c){
    for (basicblock *b = c->u->u_blocks; b != ((void *)0); b = b->b_list) {
        if (b->b_iused > 0 && is_jump(&b->b_instr[b->b_iused - 1])) {
            switch (b->b_instr[b->b_iused - 1].i_opcode) {
                ;
            }
            basicblock *target = b->b_instr[b->b_iused - 1].i_target;
            if (is_exit_without_lineno(target) && target->b_predecessors > 1) {
                basicblock *new_target = compiler_copy_block(c, target);
                if (new_target == ((void *)0)) {
                    return -1;
                }
                new_target->b_instr[0].i_lineno = b->b_instr[b->b_iused - 1].i_lineno;
                b->b_instr[b->b_iused - 1].i_target = new_target;
                target->b_predecessors--;
                new_target->b_predecessors = 1;
                new_target->b_next = target->b_next;
                target->b_next = new_target;
            }
        }
    }
    for (basicblock *b = c->u->u_blocks; b != ((void *)0); b = b->b_list) {
        while (b->b_next && b->b_next->b_iused == 0)
            {
                b->b_next = b->b_next->b_next;
            }
    }
    for (basicblock *b = c->u->u_blocks; b != ((void *)0); b = b->b_list) {
        if (!b->b_nofallthrough && b->b_next && b->b_iused > 0) {
            if (is_exit_without_lineno(b->b_next)) {
                ;
                b->b_next->b_instr[0].i_lineno = b->b_instr[b->b_iused - 1].i_lineno;
            }
        }
    }
    return 0;
}
