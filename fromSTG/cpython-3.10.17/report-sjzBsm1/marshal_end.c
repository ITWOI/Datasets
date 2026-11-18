#include "header_func.h"
#include "object.h"
static void w_flush (WFILE *p){
    ;
    p->ptr = p->buf;
}
static int w_reserve (WFILE *p, Py_ssize_t needed){
    Py_ssize_t pos, size, delta;
    if (p->ptr == ((void *)0))
        return 0;
    if (p->fp != ((void *)0)) {
        w_flush(p);
        return needed <= p->end - p->ptr;
    }
    ;
    pos = p->ptr - p->buf;
    size = (((void)(0)) , (((PyVarObject *)(p->str))->ob_size));
    if (size > 16 * 1024 * 1024) {
        delta = (size >> 3);
    } else
        delta = size + 1024;
    delta = (((delta) > (needed)) ? (delta) : (needed));
    if (delta > ((Py_ssize_t)(((size_t)-1) >> 1)) - size) {
        p->error = 3;
        return 0;
    }
    size += delta;
    if (_PyBytes_Resize(&p->str, size) != 0) {
        p->end = p->ptr = p->buf = ((void *)0);
        return 0;
    } else {
        p->buf = (((void)(0)) , (((PyBytesObject *)(p->str))->ob_sval));
        p->ptr = p->buf + pos;
        p->end = p->buf + size;
        return 1;
    }
}
static void w_string (const void *s, Py_ssize_t n, WFILE *p){
    Py_ssize_t m;
    if (!n || p->ptr == ((void *)0))
        return;
    m = p->end - p->ptr;
    if (p->fp != ((void *)0)) {
        if (n <= m) {
            ;
            p->ptr += n;
        } else {
            w_flush(p);
        }
    } else {
        if (n <= m || w_reserve(p, n - m)) {
            ;
            p->ptr += n;
        }
    }
}
static void w_short (int x, WFILE *p){
    do {
        if ((p)->ptr != (p)->end || w_reserve((p), 1))
            *(p)->ptr++ = ((char)(x & 255));
    } while (0);
    do {
        if ((p)->ptr != (p)->end || w_reserve((p), 1))
            *(p)->ptr++ = ((char)((x >> 8) & 255));
    } while (0);
}
static void w_long (long x, WFILE *p){
    do {
        if ((p)->ptr != (p)->end || w_reserve((p), 1))
            *(p)->ptr++ = ((char)(x & 255));
    } while (0);
    do {
        if ((p)->ptr != (p)->end || w_reserve((p), 1))
            *(p)->ptr++ = ((char)((x >> 8) & 255));
    } while (0);
    do {
        if ((p)->ptr != (p)->end || w_reserve((p), 1))
            *(p)->ptr++ = ((char)((x >> 16) & 255));
    } while (0);
    do {
        if ((p)->ptr != (p)->end || w_reserve((p), 1))
            *(p)->ptr++ = ((char)((x >> 24) & 255));
    } while (0);
}
static void w_pstring (const void *s, Py_ssize_t n, WFILE *p){
    do {
        if ((n) > 2147483647) {
            (p)->depth--;
            (p)->error = 1;
            return;
        }
        w_long((long)(n), p);
    } while (0);
    w_string(s, n, p);
}
static void w_short_pstring (const void *s, Py_ssize_t n, WFILE *p){
    do {
        if ((p)->ptr != (p)->end || w_reserve((p), 1))
            *(p)->ptr++ = ((unsigned char)(n));
    } while (0);
    w_string(s, n, p);
}
static void w_PyLong (const PyLongObject *ob, char flag, WFILE *p){
    Py_ssize_t i, j, n, l;
    digit d;
    do {
        do {
            if (((p))->ptr != ((p))->end || w_reserve(((p)), 1))
                *((p))->ptr++ = (('l') | flag);
        } while (0);
    } while (0);
    if ((((PyVarObject *)(ob))->ob_size) == 0) {
        w_long((long)0, p);
        return;
    }
    n = (((((PyVarObject *)(ob))->ob_size)) < 0 ? -((((PyVarObject *)(ob))->ob_size)) : ((((PyVarObject *)(ob))->ob_size)));
    l = (n - 1) * (30 / 15);
    d = ob->ob_digit[n - 1];
    do {
        d >>= 15;
        l++;
    } while (d != 0);
    if (l > 2147483647) {
        p->depth--;
        p->error = 1;
        return;
    }
    w_long((long)((((PyVarObject *)(ob))->ob_size) > 0 ? l : -l), p);
    for (i = 0; i < n - 1; i++) {
        d = ob->ob_digit[i];
        for (j = 0; j < (30 / 15); j++) {
            w_short(d & (((short)1 << 15) - 1), p);
            d >>= 15;
        }
        ;
    }
    d = ob->ob_digit[n - 1];
    do {
        w_short(d & (((short)1 << 15) - 1), p);
        d >>= 15;
    } while (d != 0);
}
static void w_float_bin (double v, WFILE *p){
    unsigned char buf[8];
    if (_PyFloat_Pack8(v, buf, 1) < 0) {
        p->error = 1;
        return;
    }
    w_string(buf, 8, p);
}
static void w_float_str (double v, WFILE *p){
    char *buf = PyOS_double_to_string(v, 'g', 17, 0, ((void *)0));
    if (!buf) {
        p->error = 3;
        return;
    }
    w_short_pstring(buf, strlen(buf), p);
}
static int w_ref (PyObject *v, char *flag, WFILE *p){
    _Py_hashtable_entry_t *entry;
    int w;
    if (p->version < 3 || p->hashtable == ((void *)0))
        return 0;
    if (_Py_REFCNT(((const PyObject *)(v))) == 1)
        return 0;
    entry = _Py_hashtable_get_entry(p->hashtable, v);
    if (entry != ((void *)0)) {
        w = (int)(uintptr_t)entry->value;
        do {
            if ((p)->ptr != (p)->end || w_reserve((p), 1))
                *(p)->ptr++ = ('r');
        } while (0);
        w_long(w, p);
        return 1;
    } else {
        size_t s = p->hashtable->nentries;
        if (s >= 2147483647) {
            ;
            goto err;
        }
        w = (int)s;
        _Py_INCREF(((PyObject *)(v)));
        if (_Py_hashtable_set(p->hashtable, v, (void *)(uintptr_t)w) < 0) {
            _Py_DECREF(((PyObject *)(v)));
            goto err;
        }
        *flag |= '\x80';
        return 0;
    }
  err:
    p->error = 1;
    return 1;
}
static void w_object (PyObject *v, WFILE *p){
    char flag = '\x00';
    p->depth++;
    if (p->depth > 2000) {
        p->error = 2;
    } else if (v == ((void *)0)) {
        do {
            if ((p)->ptr != (p)->end || w_reserve((p), 1))
                *(p)->ptr++ = ('0');
        } while (0);
    } else if (v == (&_Py_NoneStruct)) {
        do {
            if ((p)->ptr != (p)->end || w_reserve((p), 1))
                *(p)->ptr++ = ('N');
        } while (0);
    } else if (v == PyExc_StopIteration) {
        do {
            if ((p)->ptr != (p)->end || w_reserve((p), 1))
                *(p)->ptr++ = ('S');
        } while (0);
    } else if (v == (&_Py_EllipsisObject)) {
        do {
            if ((p)->ptr != (p)->end || w_reserve((p), 1))
                *(p)->ptr++ = ('.');
        } while (0);
    } else if (v == ((PyObject *)&_Py_FalseStruct)) {
        do {
            if ((p)->ptr != (p)->end || w_reserve((p), 1))
                *(p)->ptr++ = ('F');
        } while (0);
    } else if (v == ((PyObject *)&_Py_TrueStruct)) {
        do {
            if ((p)->ptr != (p)->end || w_reserve((p), 1))
                *(p)->ptr++ = ('T');
        } while (0);
    } else if (!w_ref(v, &flag, p))
        w_complex_object(v, flag, p);
    p->depth--;
}
static void w_complex_object (PyObject *v, char flag, WFILE *p){
    Py_ssize_t i, n;
    if (_Py_IS_TYPE(((const PyObject *)(v)), &PyLong_Type)) {
        int overflow;
        long x = PyLong_AsLongAndOverflow(v, &overflow);
        if (overflow) {
            w_PyLong((PyLongObject *)v, flag, p);
        } else {
            long y = ((x) >> (31));
            if (y && y != -1) {
                w_PyLong((PyLongObject *)v, flag, p);
            } else {
                do {
                    do {
                        if (((p))->ptr != ((p))->end || w_reserve(((p)), 1))
                            *((p))->ptr++ = (('i') | flag);
                    } while (0);
                } while (0);
                w_long(x, p);
            }
        }
    } else if (_Py_IS_TYPE(((const PyObject *)(v)), &PyFloat_Type)) {
        if (p->version > 1) {
            do {
                do {
                    if (((p))->ptr != ((p))->end || w_reserve(((p)), 1))
                        *((p))->ptr++ = (('g') | flag);
                } while (0);
            } while (0);
            w_float_bin((((PyFloatObject *)(v))->ob_fval), p);
        } else {
            do {
                do {
                    if (((p))->ptr != ((p))->end || w_reserve(((p)), 1))
                        *((p))->ptr++ = (('f') | flag);
                } while (0);
            } while (0);
            w_float_str((((PyFloatObject *)(v))->ob_fval), p);
        }
    } else if (_Py_IS_TYPE(((const PyObject *)(v)), &PyComplex_Type)) {
        if (p->version > 1) {
            do {
                do {
                    if (((p))->ptr != ((p))->end || w_reserve(((p)), 1))
                        *((p))->ptr++ = (('y') | flag);
                } while (0);
            } while (0);
            w_float_bin(PyComplex_RealAsDouble(v), p);
            w_float_bin(PyComplex_ImagAsDouble(v), p);
        } else {
            do {
                do {
                    if (((p))->ptr != ((p))->end || w_reserve(((p)), 1))
                        *((p))->ptr++ = (('x') | flag);
                } while (0);
            } while (0);
            w_float_str(PyComplex_RealAsDouble(v), p);
            w_float_str(PyComplex_ImagAsDouble(v), p);
        }
    } else if (_Py_IS_TYPE(((const PyObject *)(v)), &PyBytes_Type)) {
        do {
            do {
                if (((p))->ptr != ((p))->end || w_reserve(((p)), 1))
                    *((p))->ptr++ = (('s') | flag);
            } while (0);
        } while (0);
        w_pstring((((void)(0)) , (((PyBytesObject *)(v))->ob_sval)), (((void)(0)) , (((PyVarObject *)(v))->ob_size)), p);
    } else if (_Py_IS_TYPE(((const PyObject *)(v)), &PyUnicode_Type)) {
        if (p->version >= 4 && (((void)(0)) , ((void)(0)) , ((PyASCIIObject *)v)->state.ascii)) {
            int is_short = (((void)(0)) , ((void)(0)) , ((PyASCIIObject *)(v))->length) < 256;
            if (is_short) {
                if ((((PyASCIIObject *)(v))->state.interned))
                    do {
                        do {
                            if (((p))->ptr != ((p))->end || w_reserve(((p)), 1))
                                *((p))->ptr++ = (('Z') | flag);
                        } while (0);
                    } while (0);
                else
                    do {
                        do {
                            if (((p))->ptr != ((p))->end || w_reserve(((p)), 1))
                                *((p))->ptr++ = (('z') | flag);
                        } while (0);
                    } while (0);
                w_short_pstring(((Py_UCS1 *)(((void)(0)) , (((PyASCIIObject *)(v))->state.compact) ? ((((void)(0)) , ((void)(0)) , ((PyASCIIObject *)v)->state.ascii) ? ((void *)((PyASCIIObject *)(v) + 1)) : ((void *)((PyCompactUnicodeObject *)(v) + 1))) : (((void)(0)) , ((((PyUnicodeObject *)(v))->data.any))))), (((void)(0)) , ((void)(0)) , ((PyASCIIObject *)(v))->length), p);
            } else {
                if ((((PyASCIIObject *)(v))->state.interned))
                    do {
                        do {
                            if (((p))->ptr != ((p))->end || w_reserve(((p)), 1))
                                *((p))->ptr++ = (('A') | flag);
                        } while (0);
                    } while (0);
                else
                    do {
                        do {
                            if (((p))->ptr != ((p))->end || w_reserve(((p)), 1))
                                *((p))->ptr++ = (('a') | flag);
                        } while (0);
                    } while (0);
                w_pstring(((Py_UCS1 *)(((void)(0)) , (((PyASCIIObject *)(v))->state.compact) ? ((((void)(0)) , ((void)(0)) , ((PyASCIIObject *)v)->state.ascii) ? ((void *)((PyASCIIObject *)(v) + 1)) : ((void *)((PyCompactUnicodeObject *)(v) + 1))) : (((void)(0)) , ((((PyUnicodeObject *)(v))->data.any))))), (((void)(0)) , ((void)(0)) , ((PyASCIIObject *)(v))->length), p);
            }
        } else {
            PyObject *utf8;
            utf8 = PyUnicode_AsEncodedString(v, "utf8", "surrogatepass");
            if (utf8 == ((void *)0)) {
                p->depth--;
                p->error = 1;
                return;
            }
            if (p->version >= 3 && (((PyASCIIObject *)(v))->state.interned))
                do {
                    do {
                        if (((p))->ptr != ((p))->end || w_reserve(((p)), 1))
                            *((p))->ptr++ = (('t') | flag);
                    } while (0);
                } while (0);
            else
                do {
                    do {
                        if (((p))->ptr != ((p))->end || w_reserve(((p)), 1))
                            *((p))->ptr++ = (('u') | flag);
                    } while (0);
                } while (0);
            w_pstring((((void)(0)) , (((PyBytesObject *)(utf8))->ob_sval)), (((void)(0)) , (((PyVarObject *)(utf8))->ob_size)), p);
            _Py_DECREF(((PyObject *)(utf8)));
        }
    } else if (_Py_IS_TYPE(((const PyObject *)(v)), &PyTuple_Type)) {
        n = (((PyVarObject *)((((void)(0)) , (PyTupleObject *)(v))))->ob_size);
        if (p->version >= 4 && n < 256) {
            do {
                do {
                    if (((p))->ptr != ((p))->end || w_reserve(((p)), 1))
                        *((p))->ptr++ = ((')') | flag);
                } while (0);
            } while (0);
            do {
                if ((p)->ptr != (p)->end || w_reserve((p), 1))
                    *(p)->ptr++ = ((unsigned char)n);
            } while (0);
        } else {
            do {
                do {
                    if (((p))->ptr != ((p))->end || w_reserve(((p)), 1))
                        *((p))->ptr++ = (('(') | flag);
                } while (0);
            } while (0);
            do {
                if ((n) > 2147483647) {
                    (p)->depth--;
                    (p)->error = 1;
                    return;
                }
                w_long((long)(n), p);
            } while (0);
        }
        for (i = 0; i < n; i++) {
            w_object(((((void)(0)) , (PyTupleObject *)(v))->ob_item[i]), p);
        }
    } else if (_Py_IS_TYPE(((const PyObject *)(v)), &PyList_Type)) {
        do {
            do {
                if (((p))->ptr != ((p))->end || w_reserve(((p)), 1))
                    *((p))->ptr++ = (('[') | flag);
            } while (0);
        } while (0);
        n = (((PyVarObject *)((((void)(0)) , (PyListObject *)(v))))->ob_size);
        do {
            if ((n) > 2147483647) {
                (p)->depth--;
                (p)->error = 1;
                return;
            }
            w_long((long)(n), p);
        } while (0);
        for (i = 0; i < n; i++) {
            w_object(((((void)(0)) , (PyListObject *)(v))->ob_item[i]), p);
        }
    } else if (_Py_IS_TYPE(((const PyObject *)(v)), &PyDict_Type)) {
        Py_ssize_t pos;
        PyObject *key, *value;
        do {
            do {
                if (((p))->ptr != ((p))->end || w_reserve(((p)), 1))
                    *((p))->ptr++ = (('{') | flag);
            } while (0);
        } while (0);
        pos = 0;
        while (PyDict_Next(v, &pos, &key, &value))
            {
                w_object(key, p);
                w_object(value, p);
            }
        w_object((PyObject *)((void *)0), p);
    } else if ((_Py_IS_TYPE(((const PyObject *)(v)), &PySet_Type) || _Py_IS_TYPE(((const PyObject *)(v)), &PyFrozenSet_Type))) {
        PyObject *value;
        Py_ssize_t pos = 0;
        Py_hash_t hash;
        if (_Py_IS_TYPE(((const PyObject *)(v)), &PyFrozenSet_Type))
            do {
                do {
                    if (((p))->ptr != ((p))->end || w_reserve(((p)), 1))
                        *((p))->ptr++ = (('>') | flag);
                } while (0);
            } while (0);
        else
            do {
                do {
                    if (((p))->ptr != ((p))->end || w_reserve(((p)), 1))
                        *((p))->ptr++ = (('<') | flag);
                } while (0);
            } while (0);
        n = (((void)(0)) , (((PySetObject *)(v))->used));
        do {
            if ((n) > 2147483647) {
                (p)->depth--;
                (p)->error = 1;
                return;
            }
            w_long((long)(n), p);
        } while (0);
        while (_PySet_NextEntry(v, &pos, &value, &hash))
            {
                w_object(value, p);
            }
    } else if (_Py_IS_TYPE(((const PyObject *)(v)), &PyCode_Type)) {
        PyCodeObject *co = (PyCodeObject *)v;
        do {
            do {
                if (((p))->ptr != ((p))->end || w_reserve(((p)), 1))
                    *((p))->ptr++ = (('c') | flag);
            } while (0);
        } while (0);
        w_long(co->co_argcount, p);
        w_long(co->co_posonlyargcount, p);
        w_long(co->co_kwonlyargcount, p);
        w_long(co->co_nlocals, p);
        w_long(co->co_stacksize, p);
        w_long(co->co_flags, p);
        w_object(co->co_code, p);
        w_object(co->co_consts, p);
        w_object(co->co_names, p);
        w_object(co->co_varnames, p);
        w_object(co->co_freevars, p);
        w_object(co->co_cellvars, p);
        w_object(co->co_filename, p);
        w_object(co->co_name, p);
        w_long(co->co_firstlineno, p);
        w_object(co->co_linetable, p);
    } else if (PyObject_CheckBuffer(v)) {
        Py_buffer view;
        if (PyObject_GetBuffer(v, &view, 0) != 0) {
            do {
                if ((p)->ptr != (p)->end || w_reserve((p), 1))
                    *(p)->ptr++ = ('?');
            } while (0);
            p->depth--;
            p->error = 1;
            return;
        }
        do {
            do {
                if (((p))->ptr != ((p))->end || w_reserve(((p)), 1))
                    *((p))->ptr++ = (('s') | flag);
            } while (0);
        } while (0);
        w_pstring(view.buf, view.len, p);
    } else {
        do {
            do {
                if (((p))->ptr != ((p))->end || w_reserve(((p)), 1))
                    *((p))->ptr++ = (('?') | flag);
            } while (0);
        } while (0);
        p->error = 1;
    }
}
