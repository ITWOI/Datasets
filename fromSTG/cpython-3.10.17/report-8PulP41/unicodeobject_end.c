#include "header_func.h"
#include "pycore_pystate.h"
#include "object.h"
static struct _Py_unicode_state * get_unicode_state (){
    PyInterpreterState *interp = _PyInterpreterState_GET();
    return &interp->unicode;
}
static inline PyObject * unicode_get_empty (){
    struct _Py_unicode_state *state = get_unicode_state();
    return state->empty_string;
}
static inline PyObject * unicode_new_empty (){
    PyObject *empty = unicode_get_empty();
    _Py_INCREF(((PyObject *)(empty)));
    return empty;
}
static PyObject * resize_compact (PyObject *unicode, Py_ssize_t length){
    Py_ssize_t char_size;
    Py_ssize_t struct_size;
    Py_ssize_t new_size;
    int share_wstr;
    PyObject *new_unicode;
    char_size = (((void)(0)) , ((void)(0)) , ((PyASCIIObject *)(unicode))->state.kind);
    if ((((void)(0)) , ((void)(0)) , ((PyASCIIObject *)unicode)->state.ascii)) {
        struct_size = sizeof(PyASCIIObject);
    } else
        struct_size = sizeof(PyCompactUnicodeObject);
    share_wstr = (((void)(0)) , ((((PyASCIIObject *)(unicode))->wstr) == (((void)(0)) , (((PyASCIIObject *)(unicode))->state.compact) ? ((((void)(0)) , ((void)(0)) , ((PyASCIIObject *)unicode)->state.ascii) ? ((void *)((PyASCIIObject *)(unicode) + 1)) : ((void *)((PyCompactUnicodeObject *)(unicode) + 1))) : (((void)(0)) , ((((PyUnicodeObject *)(unicode))->data.any))))));
    if (length > ((((Py_ssize_t)(((size_t)-1) >> 1)) - struct_size) / char_size - 1)) {
        ;
        return ((void *)0);
    }
    new_size = (struct_size + (length + 1) * char_size);
    if (((!(((PyASCIIObject *)unicode)->state.ascii && (((PyASCIIObject *)(unicode))->state.compact)) && (((PyCompactUnicodeObject *)(unicode))->utf8) && (((PyCompactUnicodeObject *)(unicode))->utf8) != (((void)(0)) , (((PyASCIIObject *)(unicode))->state.compact) ? ((((void)(0)) , ((void)(0)) , ((PyASCIIObject *)unicode)->state.ascii) ? ((void *)((PyASCIIObject *)(unicode) + 1)) : ((void *)((PyCompactUnicodeObject *)(unicode) + 1))) : (((void)(0)) , ((((PyUnicodeObject *)(unicode))->data.any))))))) {
        ;
        (((PyCompactUnicodeObject *)(unicode))->utf8) = ((void *)0);
        (((PyCompactUnicodeObject *)(unicode))->utf8_length) = 0;
    }
    new_unicode = (PyObject *)PyObject_Realloc(unicode, new_size);
    if (new_unicode == ((void *)0)) {
        ;
        return ((void *)0);
    }
    unicode = new_unicode;
    (((PyASCIIObject *)(unicode))->length) = length;
    if (share_wstr) {
        (((PyASCIIObject *)(unicode))->wstr) = (((void)(0)) , (((PyASCIIObject *)(unicode))->state.compact) ? ((((void)(0)) , ((void)(0)) , ((PyASCIIObject *)unicode)->state.ascii) ? ((void *)((PyASCIIObject *)(unicode) + 1)) : ((void *)((PyCompactUnicodeObject *)(unicode) + 1))) : (((void)(0)) , ((((PyUnicodeObject *)(unicode))->data.any))));
        if (!(((void)(0)) , ((void)(0)) , ((PyASCIIObject *)unicode)->state.ascii))
            (((PyCompactUnicodeObject *)(unicode))->wstr_length) = length;
    } else if ((((((PyASCIIObject *)(unicode))->wstr) && (!(((PyASCIIObject *)unicode)->state.ready) || (((PyASCIIObject *)(unicode))->wstr) != (((void)(0)) , (((PyASCIIObject *)(unicode))->state.compact) ? ((((void)(0)) , ((void)(0)) , ((PyASCIIObject *)unicode)->state.ascii) ? ((void *)((PyASCIIObject *)(unicode) + 1)) : ((void *)((PyCompactUnicodeObject *)(unicode) + 1))) : (((void)(0)) , ((((PyUnicodeObject *)(unicode))->data.any)))))))) {
        ;
        (((PyASCIIObject *)(unicode))->wstr) = ((void *)0);
        if (!(((void)(0)) , ((void)(0)) , ((PyASCIIObject *)unicode)->state.ascii))
            (((PyCompactUnicodeObject *)(unicode))->wstr_length) = 0;
    }
    do {
        switch (((((void)(0)) , ((void)(0)) , ((PyASCIIObject *)(unicode))->state.kind))) {
          case PyUnicode_1BYTE_KIND:
            {
                ((Py_UCS1 *)((((void)(0)) , (((PyASCIIObject *)(unicode))->state.compact) ? ((((void)(0)) , ((void)(0)) , ((PyASCIIObject *)unicode)->state.ascii) ? ((void *)((PyASCIIObject *)(unicode) + 1)) : ((void *)((PyCompactUnicodeObject *)(unicode) + 1))) : (((void)(0)) , ((((PyUnicodeObject *)(unicode))->data.any))))))[(length)] = (Py_UCS1)(0);
                break;
            }
          case PyUnicode_2BYTE_KIND:
            {
                ((Py_UCS2 *)((((void)(0)) , (((PyASCIIObject *)(unicode))->state.compact) ? ((((void)(0)) , ((void)(0)) , ((PyASCIIObject *)unicode)->state.ascii) ? ((void *)((PyASCIIObject *)(unicode) + 1)) : ((void *)((PyCompactUnicodeObject *)(unicode) + 1))) : (((void)(0)) , ((((PyUnicodeObject *)(unicode))->data.any))))))[(length)] = (Py_UCS2)(0);
                break;
            }
          default:
            {
                ((void)(0));
                ((Py_UCS4 *)((((void)(0)) , (((PyASCIIObject *)(unicode))->state.compact) ? ((((void)(0)) , ((void)(0)) , ((PyASCIIObject *)unicode)->state.ascii) ? ((void *)((PyASCIIObject *)(unicode) + 1)) : ((void *)((PyCompactUnicodeObject *)(unicode) + 1))) : (((void)(0)) , ((((PyUnicodeObject *)(unicode))->data.any))))))[(length)] = (Py_UCS4)(0);
            }
        }
    } while (0);
    return unicode;
}
static int resize_inplace (PyObject *unicode, Py_ssize_t length){
    wchar_t *wstr;
    Py_ssize_t new_size;
    if ((((PyASCIIObject *)unicode)->state.ready)) {
        Py_ssize_t char_size;
        int share_wstr, share_utf8;
        void *data;
        data = (((PyUnicodeObject *)(unicode))->data.any);
        char_size = (((void)(0)) , ((void)(0)) , ((PyASCIIObject *)(unicode))->state.kind);
        share_wstr = (((void)(0)) , ((((PyASCIIObject *)(unicode))->wstr) == (((void)(0)) , (((PyASCIIObject *)(unicode))->state.compact) ? ((((void)(0)) , ((void)(0)) , ((PyASCIIObject *)unicode)->state.ascii) ? ((void *)((PyASCIIObject *)(unicode) + 1)) : ((void *)((PyCompactUnicodeObject *)(unicode) + 1))) : (((void)(0)) , ((((PyUnicodeObject *)(unicode))->data.any))))));
        share_utf8 = (((void)(0)) , ((void)(0)) , ((((PyCompactUnicodeObject *)(unicode))->utf8) == (((void)(0)) , (((PyASCIIObject *)(unicode))->state.compact) ? ((((void)(0)) , ((void)(0)) , ((PyASCIIObject *)unicode)->state.ascii) ? ((void *)((PyASCIIObject *)(unicode) + 1)) : ((void *)((PyCompactUnicodeObject *)(unicode) + 1))) : (((void)(0)) , ((((PyUnicodeObject *)(unicode))->data.any))))));
        if (length > (((Py_ssize_t)(((size_t)-1) >> 1)) / char_size - 1)) {
            ;
            return -1;
        }
        new_size = (length + 1) * char_size;
        if (!share_utf8 && ((!(((PyASCIIObject *)unicode)->state.ascii && (((PyASCIIObject *)(unicode))->state.compact)) && (((PyCompactUnicodeObject *)(unicode))->utf8) && (((PyCompactUnicodeObject *)(unicode))->utf8) != (((void)(0)) , (((PyASCIIObject *)(unicode))->state.compact) ? ((((void)(0)) , ((void)(0)) , ((PyASCIIObject *)unicode)->state.ascii) ? ((void *)((PyASCIIObject *)(unicode) + 1)) : ((void *)((PyCompactUnicodeObject *)(unicode) + 1))) : (((void)(0)) , ((((PyUnicodeObject *)(unicode))->data.any))))))) {
            ;
            (((PyCompactUnicodeObject *)(unicode))->utf8) = ((void *)0);
            (((PyCompactUnicodeObject *)(unicode))->utf8_length) = 0;
        }
        data = (PyObject *)PyObject_Realloc(data, new_size);
        if (data == ((void *)0)) {
            ;
            return -1;
        }
        (((PyUnicodeObject *)(unicode))->data.any) = data;
        if (share_wstr) {
            (((PyASCIIObject *)(unicode))->wstr) = data;
            (((PyCompactUnicodeObject *)(unicode))->wstr_length) = length;
        }
        if (share_utf8) {
            (((PyCompactUnicodeObject *)(unicode))->utf8) = data;
            (((PyCompactUnicodeObject *)(unicode))->utf8_length) = length;
        }
        (((PyASCIIObject *)(unicode))->length) = length;
        do {
            switch (((((void)(0)) , ((void)(0)) , ((PyASCIIObject *)(unicode))->state.kind))) {
              case PyUnicode_1BYTE_KIND:
                {
                    ((Py_UCS1 *)(data))[(length)] = (Py_UCS1)(0);
                    break;
                }
              case PyUnicode_2BYTE_KIND:
                {
                    ((Py_UCS2 *)(data))[(length)] = (Py_UCS2)(0);
                    break;
                }
              default:
                {
                    ((void)(0));
                    ((Py_UCS4 *)(data))[(length)] = (Py_UCS4)(0);
                }
            }
        } while (0);
        if (share_wstr || (((PyASCIIObject *)(unicode))->wstr) == ((void *)0)) {
            ;
            return 0;
        }
    }
    ;
    if (length > ((Py_ssize_t)(((size_t)-1) >> 1)) / (Py_ssize_t)sizeof(wchar_t) - 1) {
        ;
        return -1;
    }
    new_size = sizeof(wchar_t) * (length + 1);
    wstr = (((PyASCIIObject *)(unicode))->wstr);
    wstr = PyObject_Realloc(wstr, new_size);
    if (!wstr) {
        ;
        return -1;
    }
    (((PyASCIIObject *)(unicode))->wstr) = wstr;
    (((PyASCIIObject *)(unicode))->wstr)[length] = 0;
    (((PyCompactUnicodeObject *)(unicode))->wstr_length) = length;
    return 0;
}
static PyObject * resize_copy (PyObject *unicode, Py_ssize_t length){
    Py_ssize_t copy_length;
    if ((((void)(0)) , ((PyASCIIObject *)(unicode))->state.kind) != PyUnicode_WCHAR_KIND) {
        PyObject *copy;
        copy = PyUnicode_New(length, (((void)(0)) , ((((void)(0)) , ((void)(0)) , ((PyASCIIObject *)unicode)->state.ascii) ? (127) : ((((void)(0)) , ((void)(0)) , ((PyASCIIObject *)(unicode))->state.kind) == PyUnicode_1BYTE_KIND ? (255U) : ((((void)(0)) , ((void)(0)) , ((PyASCIIObject *)(unicode))->state.kind) == PyUnicode_2BYTE_KIND ? (65535U) : (1114111U))))));
        if (copy == ((void *)0))
            return ((void *)0);
        copy_length = (((length) > ((((void)(0)) , ((void)(0)) , ((PyASCIIObject *)(unicode))->length))) ? ((((void)(0)) , ((void)(0)) , ((PyASCIIObject *)(unicode))->length)) : (length));
        _PyUnicode_FastCopyCharacters(copy, 0, unicode, 0, copy_length);
        return copy;
    } else {
        PyObject *w;
        w = (PyObject *)_PyUnicode_New(length);
        if (w == ((void *)0))
            return ((void *)0);
        return w;
    }
}
static PyUnicodeObject * _PyUnicode_New (Py_ssize_t length){
    PyUnicodeObject *unicode;
    size_t new_size;
    if (length == 0) {
        return (PyUnicodeObject *)unicode_new_empty();
    }
    if (length > ((((Py_ssize_t)(((size_t)-1) >> 1)) / (Py_ssize_t)sizeof(Py_UNICODE)) - 1)) {
        return (PyUnicodeObject *)PyErr_NoMemory();
    }
    if (length < 0) {
        ;
        return ((void *)0);
    }
    unicode = ((PyUnicodeObject *)_PyObject_New(&PyUnicode_Type));
    if (unicode == ((void *)0))
        return ((void *)0);
    new_size = sizeof(Py_UNICODE) * ((size_t)length + 1);
    (((PyCompactUnicodeObject *)(unicode))->wstr_length) = length;
    (((PyASCIIObject *)(unicode))->hash) = -1;
    (((PyASCIIObject *)(unicode))->state).interned = 0;
    (((PyASCIIObject *)(unicode))->state).kind = 0;
    (((PyASCIIObject *)(unicode))->state).compact = 0;
    (((PyASCIIObject *)(unicode))->state).ready = 0;
    (((PyASCIIObject *)(unicode))->state).ascii = 0;
    (((PyUnicodeObject *)(unicode))->data.any) = ((void *)0);
    (((PyASCIIObject *)(unicode))->length) = 0;
    (((PyCompactUnicodeObject *)(unicode))->utf8) = ((void *)0);
    (((PyCompactUnicodeObject *)(unicode))->utf8_length) = 0;
    (((PyASCIIObject *)(unicode))->wstr) = (Py_UNICODE *)PyObject_Malloc(new_size);
    if (!(((PyASCIIObject *)(unicode))->wstr)) {
        _Py_DECREF(((PyObject *)(unicode)));
        return ((void *)0);
    }
    (((PyASCIIObject *)(unicode))->wstr)[0] = 0;
    (((PyASCIIObject *)(unicode))->wstr)[length] = 0;
    return unicode;
}
extern  __attribute__((visibility("default"))) PyObject * PyUnicode_New (Py_ssize_t size, Py_UCS4 maxchar){
    if (size == 0) {
        return unicode_new_empty();
    }
    PyObject *obj;
    PyCompactUnicodeObject *unicode;
    void *data;
    enum PyUnicode_Kind kind;
    int is_sharing, is_ascii;
    Py_ssize_t char_size;
    Py_ssize_t struct_size;
    is_ascii = 0;
    is_sharing = 0;
    struct_size = sizeof(PyCompactUnicodeObject);
    if (maxchar < 128) {
        kind = PyUnicode_1BYTE_KIND;
        char_size = 1;
        is_ascii = 1;
        struct_size = sizeof(PyASCIIObject);
    } else if (maxchar < 256) {
        kind = PyUnicode_1BYTE_KIND;
        char_size = 1;
    } else if (maxchar < 65536) {
        kind = PyUnicode_2BYTE_KIND;
        char_size = 2;
    } else {
        if (maxchar > 1114111) {
            ;
            return ((void *)0);
        }
        kind = PyUnicode_4BYTE_KIND;
        char_size = 4;
        if (sizeof(wchar_t) == 4)
            is_sharing = 1;
    }
    if (size < 0) {
        ;
        return ((void *)0);
    }
    if (size > ((((Py_ssize_t)(((size_t)-1) >> 1)) - struct_size) / char_size - 1))
        return PyErr_NoMemory();
    obj = (PyObject *)PyObject_Malloc(struct_size + (size + 1) * char_size);
    if (obj == ((void *)0)) {
        return PyErr_NoMemory();
    }
    _PyObject_Init(obj, &PyUnicode_Type);
    unicode = (PyCompactUnicodeObject *)obj;
    if (is_ascii) {
        data = ((PyASCIIObject *)obj) + 1;
    } else
        data = unicode + 1;
    (((PyASCIIObject *)(unicode))->length) = size;
    (((PyASCIIObject *)(unicode))->hash) = -1;
    (((PyASCIIObject *)(unicode))->state).interned = 0;
    (((PyASCIIObject *)(unicode))->state).kind = kind;
    (((PyASCIIObject *)(unicode))->state).compact = 1;
    (((PyASCIIObject *)(unicode))->state).ready = 1;
    (((PyASCIIObject *)(unicode))->state).ascii = is_ascii;
    if (is_ascii) {
        ((char *)data)[size] = 0;
        (((PyASCIIObject *)(unicode))->wstr) = ((void *)0);
    } else if (kind == PyUnicode_1BYTE_KIND) {
        ((char *)data)[size] = 0;
        (((PyASCIIObject *)(unicode))->wstr) = ((void *)0);
        (((PyCompactUnicodeObject *)(unicode))->wstr_length) = 0;
        unicode->utf8 = ((void *)0);
        unicode->utf8_length = 0;
    } else {
        unicode->utf8 = ((void *)0);
        unicode->utf8_length = 0;
        if (kind == PyUnicode_2BYTE_KIND) {
            ((Py_UCS2 *)data)[size] = 0;
        } else
            ((Py_UCS4 *)data)[size] = 0;
        if (is_sharing) {
            (((PyCompactUnicodeObject *)(unicode))->wstr_length) = size;
            (((PyASCIIObject *)(unicode))->wstr) = (wchar_t *)data;
        } else {
            (((PyCompactUnicodeObject *)(unicode))->wstr_length) = 0;
            (((PyASCIIObject *)(unicode))->wstr) = ((void *)0);
        }
    }
    ;
    return obj;
}
static int _copy_characters (PyObject *to, Py_ssize_t to_start, PyObject *from, Py_ssize_t from_start, Py_ssize_t how_many, int check_maxchar){
    unsigned int from_kind, to_kind;
    const void *from_data;
    void *to_data;
    if (how_many == 0)
        return 0;
    from_kind = (((void)(0)) , ((void)(0)) , ((PyASCIIObject *)(from))->state.kind);
    from_data = (((void)(0)) , (((PyASCIIObject *)(from))->state.compact) ? ((((void)(0)) , ((void)(0)) , ((PyASCIIObject *)from)->state.ascii) ? ((void *)((PyASCIIObject *)(from) + 1)) : ((void *)((PyCompactUnicodeObject *)(from) + 1))) : (((void)(0)) , ((((PyUnicodeObject *)(from))->data.any))));
    to_kind = (((void)(0)) , ((void)(0)) , ((PyASCIIObject *)(to))->state.kind);
    to_data = (((void)(0)) , (((PyASCIIObject *)(to))->state.compact) ? ((((void)(0)) , ((void)(0)) , ((PyASCIIObject *)to)->state.ascii) ? ((void *)((PyASCIIObject *)(to) + 1)) : ((void *)((PyCompactUnicodeObject *)(to) + 1))) : (((void)(0)) , ((((PyUnicodeObject *)(to))->data.any))));
    if (from_kind == to_kind) {
        if (check_maxchar && !(((void)(0)) , ((void)(0)) , ((PyASCIIObject *)from)->state.ascii) && (((void)(0)) , ((void)(0)) , ((PyASCIIObject *)to)->state.ascii)) {
            Py_UCS4 max_char;
        }
        ;
    } else if (from_kind == PyUnicode_1BYTE_KIND && to_kind == PyUnicode_2BYTE_KIND) {
        do {
            Py_UCS2 *_to = (Py_UCS2 *)(((Py_UCS2 *)(((void)(0)) , (((PyASCIIObject *)(to))->state.compact) ? ((((void)(0)) , ((void)(0)) , ((PyASCIIObject *)to)->state.ascii) ? ((void *)((PyASCIIObject *)(to) + 1)) : ((void *)((PyCompactUnicodeObject *)(to) + 1))) : (((void)(0)) , ((((PyUnicodeObject *)(to))->data.any))))) + to_start);
            const Py_UCS1 *_iter = (const Py_UCS1 *)(((Py_UCS1 *)(((void)(0)) , (((PyASCIIObject *)(from))->state.compact) ? ((((void)(0)) , ((void)(0)) , ((PyASCIIObject *)from)->state.ascii) ? ((void *)((PyASCIIObject *)(from) + 1)) : ((void *)((PyCompactUnicodeObject *)(from) + 1))) : (((void)(0)) , ((((PyUnicodeObject *)(from))->data.any))))) + from_start);
            const Py_UCS1 *_end = (const Py_UCS1 *)(((Py_UCS1 *)(((void)(0)) , (((PyASCIIObject *)(from))->state.compact) ? ((((void)(0)) , ((void)(0)) , ((PyASCIIObject *)from)->state.ascii) ? ((void *)((PyASCIIObject *)(from) + 1)) : ((void *)((PyCompactUnicodeObject *)(from) + 1))) : (((void)(0)) , ((((PyUnicodeObject *)(from))->data.any))))) + from_start + how_many);
            Py_ssize_t n = (_end) - (_iter);
            const Py_UCS1 *_unrolled_end = _iter + ((size_t)(n) & ~(size_t)((4) - 1));
            while (_iter < (_unrolled_end))
                {
                    _to[0] = (Py_UCS2)_iter[0];
                    _to[1] = (Py_UCS2)_iter[1];
                    _to[2] = (Py_UCS2)_iter[2];
                    _to[3] = (Py_UCS2)_iter[3];
                    _iter += 4;
                    _to += 4;
                }
            while (_iter < (_end))
                *_to++ = (Py_UCS2)*_iter++;
        } while (0);
    } else if (from_kind == PyUnicode_1BYTE_KIND && to_kind == PyUnicode_4BYTE_KIND) {
        do {
            Py_UCS4 *_to = (Py_UCS4 *)(((Py_UCS4 *)(((void)(0)) , (((PyASCIIObject *)(to))->state.compact) ? ((((void)(0)) , ((void)(0)) , ((PyASCIIObject *)to)->state.ascii) ? ((void *)((PyASCIIObject *)(to) + 1)) : ((void *)((PyCompactUnicodeObject *)(to) + 1))) : (((void)(0)) , ((((PyUnicodeObject *)(to))->data.any))))) + to_start);
            const Py_UCS1 *_iter = (const Py_UCS1 *)(((Py_UCS1 *)(((void)(0)) , (((PyASCIIObject *)(from))->state.compact) ? ((((void)(0)) , ((void)(0)) , ((PyASCIIObject *)from)->state.ascii) ? ((void *)((PyASCIIObject *)(from) + 1)) : ((void *)((PyCompactUnicodeObject *)(from) + 1))) : (((void)(0)) , ((((PyUnicodeObject *)(from))->data.any))))) + from_start);
            const Py_UCS1 *_end = (const Py_UCS1 *)(((Py_UCS1 *)(((void)(0)) , (((PyASCIIObject *)(from))->state.compact) ? ((((void)(0)) , ((void)(0)) , ((PyASCIIObject *)from)->state.ascii) ? ((void *)((PyASCIIObject *)(from) + 1)) : ((void *)((PyCompactUnicodeObject *)(from) + 1))) : (((void)(0)) , ((((PyUnicodeObject *)(from))->data.any))))) + from_start + how_many);
            Py_ssize_t n = (_end) - (_iter);
            const Py_UCS1 *_unrolled_end = _iter + ((size_t)(n) & ~(size_t)((4) - 1));
            while (_iter < (_unrolled_end))
                {
                    _to[0] = (Py_UCS4)_iter[0];
                    _to[1] = (Py_UCS4)_iter[1];
                    _to[2] = (Py_UCS4)_iter[2];
                    _to[3] = (Py_UCS4)_iter[3];
                    _iter += 4;
                    _to += 4;
                }
            while (_iter < (_end))
                *_to++ = (Py_UCS4)*_iter++;
        } while (0);
    } else if (from_kind == PyUnicode_2BYTE_KIND && to_kind == PyUnicode_4BYTE_KIND) {
        do {
            Py_UCS4 *_to = (Py_UCS4 *)(((Py_UCS4 *)(((void)(0)) , (((PyASCIIObject *)(to))->state.compact) ? ((((void)(0)) , ((void)(0)) , ((PyASCIIObject *)to)->state.ascii) ? ((void *)((PyASCIIObject *)(to) + 1)) : ((void *)((PyCompactUnicodeObject *)(to) + 1))) : (((void)(0)) , ((((PyUnicodeObject *)(to))->data.any))))) + to_start);
            const Py_UCS2 *_iter = (const Py_UCS2 *)(((Py_UCS2 *)(((void)(0)) , (((PyASCIIObject *)(from))->state.compact) ? ((((void)(0)) , ((void)(0)) , ((PyASCIIObject *)from)->state.ascii) ? ((void *)((PyASCIIObject *)(from) + 1)) : ((void *)((PyCompactUnicodeObject *)(from) + 1))) : (((void)(0)) , ((((PyUnicodeObject *)(from))->data.any))))) + from_start);
            const Py_UCS2 *_end = (const Py_UCS2 *)(((Py_UCS2 *)(((void)(0)) , (((PyASCIIObject *)(from))->state.compact) ? ((((void)(0)) , ((void)(0)) , ((PyASCIIObject *)from)->state.ascii) ? ((void *)((PyASCIIObject *)(from) + 1)) : ((void *)((PyCompactUnicodeObject *)(from) + 1))) : (((void)(0)) , ((((PyUnicodeObject *)(from))->data.any))))) + from_start + how_many);
            Py_ssize_t n = (_end) - (_iter);
            const Py_UCS2 *_unrolled_end = _iter + ((size_t)(n) & ~(size_t)((4) - 1));
            while (_iter < (_unrolled_end))
                {
                    _to[0] = (Py_UCS4)_iter[0];
                    _to[1] = (Py_UCS4)_iter[1];
                    _to[2] = (Py_UCS4)_iter[2];
                    _to[3] = (Py_UCS4)_iter[3];
                    _iter += 4;
                    _to += 4;
                }
            while (_iter < (_end))
                *_to++ = (Py_UCS4)*_iter++;
        } while (0);
    } else {
        ;
        if (!check_maxchar) {
            if (from_kind == PyUnicode_2BYTE_KIND && to_kind == PyUnicode_1BYTE_KIND) {
                do {
                    Py_UCS1 *_to = (Py_UCS1 *)(((Py_UCS1 *)(((void)(0)) , (((PyASCIIObject *)(to))->state.compact) ? ((((void)(0)) , ((void)(0)) , ((PyASCIIObject *)to)->state.ascii) ? ((void *)((PyASCIIObject *)(to) + 1)) : ((void *)((PyCompactUnicodeObject *)(to) + 1))) : (((void)(0)) , ((((PyUnicodeObject *)(to))->data.any))))) + to_start);
                    const Py_UCS2 *_iter = (const Py_UCS2 *)(((Py_UCS2 *)(((void)(0)) , (((PyASCIIObject *)(from))->state.compact) ? ((((void)(0)) , ((void)(0)) , ((PyASCIIObject *)from)->state.ascii) ? ((void *)((PyASCIIObject *)(from) + 1)) : ((void *)((PyCompactUnicodeObject *)(from) + 1))) : (((void)(0)) , ((((PyUnicodeObject *)(from))->data.any))))) + from_start);
                    const Py_UCS2 *_end = (const Py_UCS2 *)(((Py_UCS2 *)(((void)(0)) , (((PyASCIIObject *)(from))->state.compact) ? ((((void)(0)) , ((void)(0)) , ((PyASCIIObject *)from)->state.ascii) ? ((void *)((PyASCIIObject *)(from) + 1)) : ((void *)((PyCompactUnicodeObject *)(from) + 1))) : (((void)(0)) , ((((PyUnicodeObject *)(from))->data.any))))) + from_start + how_many);
                    Py_ssize_t n = (_end) - (_iter);
                    const Py_UCS2 *_unrolled_end = _iter + ((size_t)(n) & ~(size_t)((4) - 1));
                    while (_iter < (_unrolled_end))
                        {
                            _to[0] = (Py_UCS1)_iter[0];
                            _to[1] = (Py_UCS1)_iter[1];
                            _to[2] = (Py_UCS1)_iter[2];
                            _to[3] = (Py_UCS1)_iter[3];
                            _iter += 4;
                            _to += 4;
                        }
                    while (_iter < (_end))
                        *_to++ = (Py_UCS1)*_iter++;
                } while (0);
            } else if (from_kind == PyUnicode_4BYTE_KIND && to_kind == PyUnicode_1BYTE_KIND) {
                do {
                    Py_UCS1 *_to = (Py_UCS1 *)(((Py_UCS1 *)(((void)(0)) , (((PyASCIIObject *)(to))->state.compact) ? ((((void)(0)) , ((void)(0)) , ((PyASCIIObject *)to)->state.ascii) ? ((void *)((PyASCIIObject *)(to) + 1)) : ((void *)((PyCompactUnicodeObject *)(to) + 1))) : (((void)(0)) , ((((PyUnicodeObject *)(to))->data.any))))) + to_start);
                    const Py_UCS4 *_iter = (const Py_UCS4 *)(((Py_UCS4 *)(((void)(0)) , (((PyASCIIObject *)(from))->state.compact) ? ((((void)(0)) , ((void)(0)) , ((PyASCIIObject *)from)->state.ascii) ? ((void *)((PyASCIIObject *)(from) + 1)) : ((void *)((PyCompactUnicodeObject *)(from) + 1))) : (((void)(0)) , ((((PyUnicodeObject *)(from))->data.any))))) + from_start);
                    const Py_UCS4 *_end = (const Py_UCS4 *)(((Py_UCS4 *)(((void)(0)) , (((PyASCIIObject *)(from))->state.compact) ? ((((void)(0)) , ((void)(0)) , ((PyASCIIObject *)from)->state.ascii) ? ((void *)((PyASCIIObject *)(from) + 1)) : ((void *)((PyCompactUnicodeObject *)(from) + 1))) : (((void)(0)) , ((((PyUnicodeObject *)(from))->data.any))))) + from_start + how_many);
                    Py_ssize_t n = (_end) - (_iter);
                    const Py_UCS4 *_unrolled_end = _iter + ((size_t)(n) & ~(size_t)((4) - 1));
                    while (_iter < (_unrolled_end))
                        {
                            _to[0] = (Py_UCS1)_iter[0];
                            _to[1] = (Py_UCS1)_iter[1];
                            _to[2] = (Py_UCS1)_iter[2];
                            _to[3] = (Py_UCS1)_iter[3];
                            _iter += 4;
                            _to += 4;
                        }
                    while (_iter < (_end))
                        *_to++ = (Py_UCS1)*_iter++;
                } while (0);
            } else if (from_kind == PyUnicode_4BYTE_KIND && to_kind == PyUnicode_2BYTE_KIND) {
                do {
                    Py_UCS2 *_to = (Py_UCS2 *)(((Py_UCS2 *)(((void)(0)) , (((PyASCIIObject *)(to))->state.compact) ? ((((void)(0)) , ((void)(0)) , ((PyASCIIObject *)to)->state.ascii) ? ((void *)((PyASCIIObject *)(to) + 1)) : ((void *)((PyCompactUnicodeObject *)(to) + 1))) : (((void)(0)) , ((((PyUnicodeObject *)(to))->data.any))))) + to_start);
                    const Py_UCS4 *_iter = (const Py_UCS4 *)(((Py_UCS4 *)(((void)(0)) , (((PyASCIIObject *)(from))->state.compact) ? ((((void)(0)) , ((void)(0)) , ((PyASCIIObject *)from)->state.ascii) ? ((void *)((PyASCIIObject *)(from) + 1)) : ((void *)((PyCompactUnicodeObject *)(from) + 1))) : (((void)(0)) , ((((PyUnicodeObject *)(from))->data.any))))) + from_start);
                    const Py_UCS4 *_end = (const Py_UCS4 *)(((Py_UCS4 *)(((void)(0)) , (((PyASCIIObject *)(from))->state.compact) ? ((((void)(0)) , ((void)(0)) , ((PyASCIIObject *)from)->state.ascii) ? ((void *)((PyASCIIObject *)(from) + 1)) : ((void *)((PyCompactUnicodeObject *)(from) + 1))) : (((void)(0)) , ((((PyUnicodeObject *)(from))->data.any))))) + from_start + how_many);
                    Py_ssize_t n = (_end) - (_iter);
                    const Py_UCS4 *_unrolled_end = _iter + ((size_t)(n) & ~(size_t)((4) - 1));
                    while (_iter < (_unrolled_end))
                        {
                            _to[0] = (Py_UCS2)_iter[0];
                            _to[1] = (Py_UCS2)_iter[1];
                            _to[2] = (Py_UCS2)_iter[2];
                            _to[3] = (Py_UCS2)_iter[3];
                            _iter += 4;
                            _to += 4;
                        }
                    while (_iter < (_end))
                        *_to++ = (Py_UCS2)*_iter++;
                } while (0);
            } else {
                ;
            }
        } else {
            const Py_UCS4 to_maxchar = (((void)(0)) , ((((void)(0)) , ((void)(0)) , ((PyASCIIObject *)to)->state.ascii) ? (127) : ((((void)(0)) , ((void)(0)) , ((PyASCIIObject *)(to))->state.kind) == PyUnicode_1BYTE_KIND ? (255U) : ((((void)(0)) , ((void)(0)) , ((PyASCIIObject *)(to))->state.kind) == PyUnicode_2BYTE_KIND ? (65535U) : (1114111U)))));
            Py_UCS4 ch;
            Py_ssize_t i;
            for (i = 0; i < how_many; i++) {
                ch = ((Py_UCS4)((from_kind) == PyUnicode_1BYTE_KIND ? ((const Py_UCS1 *)(from_data))[(from_start + i)] : ((from_kind) == PyUnicode_2BYTE_KIND ? ((const Py_UCS2 *)(from_data))[(from_start + i)] : ((const Py_UCS4 *)(from_data))[(from_start + i)])));
                if (ch > to_maxchar)
                    return -1;
                do {
                    switch ((to_kind)) {
                      case PyUnicode_1BYTE_KIND:
                        {
                            ((Py_UCS1 *)(to_data))[(to_start + i)] = (Py_UCS1)(ch);
                            break;
                        }
                      case PyUnicode_2BYTE_KIND:
                        {
                            ((Py_UCS2 *)(to_data))[(to_start + i)] = (Py_UCS2)(ch);
                            break;
                        }
                      default:
                        {
                            ((void)(0));
                            ((Py_UCS4 *)(to_data))[(to_start + i)] = (Py_UCS4)(ch);
                        }
                    }
                } while (0);
            }
        }
    }
    return 0;
}
extern  __attribute__((visibility("default"))) void _PyUnicode_FastCopyCharacters (PyObject *to, Py_ssize_t to_start, PyObject *from, Py_ssize_t from_start, Py_ssize_t how_many){
    (void)_copy_characters(to, to_start, from, from_start, how_many, 0);
}
static int unicode_modifiable (PyObject *unicode){
    ;
    if (_Py_REFCNT(((const PyObject *)(unicode))) != 1)
        return 0;
    if ((((PyASCIIObject *)(unicode))->hash) != -1)
        return 0;
    if ((((PyASCIIObject *)(unicode))->state.interned))
        return 0;
    if (!_Py_IS_TYPE(((const PyObject *)(unicode)), &PyUnicode_Type))
        return 0;
    return 1;
}
static int unicode_resize (PyObject **p_unicode, Py_ssize_t length){
    PyObject *unicode;
    Py_ssize_t old_length;
    unicode = *p_unicode;
    if ((((void)(0)) , ((PyASCIIObject *)(unicode))->state.kind) == PyUnicode_WCHAR_KIND)
        old_length = ((((PyASCIIObject *)unicode)->state.ascii && (((PyASCIIObject *)(unicode))->state.compact)) ? ((PyASCIIObject *)unicode)->length : ((PyCompactUnicodeObject *)unicode)->wstr_length);
    else
        old_length = (((void)(0)) , ((void)(0)) , ((PyASCIIObject *)(unicode))->length);
    if (old_length == length)
        return 0;
    if (length == 0) {
        PyObject *empty = unicode_new_empty();
        do {
            PyObject *_py_tmp = ((PyObject *)(*p_unicode));
            (*p_unicode) = (empty);
            _Py_DECREF(((PyObject *)(_py_tmp)));
        } while (0);
        return 0;
    }
    if (!unicode_modifiable(unicode)) {
        PyObject *copy = resize_copy(unicode, length);
        if (copy == ((void *)0))
            return -1;
        do {
            PyObject *_py_tmp = ((PyObject *)(*p_unicode));
            (*p_unicode) = (copy);
            _Py_DECREF(((PyObject *)(_py_tmp)));
        } while (0);
        return 0;
    }
    if ((((PyASCIIObject *)(unicode))->state.compact)) {
        PyObject *new_unicode = resize_compact(unicode, length);
        if (new_unicode == ((void *)0))
            return -1;
        *p_unicode = new_unicode;
        return 0;
    }
    return resize_inplace(unicode, length);
}
extern  __attribute__((visibility("default"))) int PyUnicode_Resize (PyObject **p_unicode, Py_ssize_t length){
    PyObject *unicode;
    if (p_unicode == ((void *)0)) {
        ;
        return -1;
    }
    unicode = *p_unicode;
    if (unicode == ((void *)0) || !PyType_HasFeature((((PyObject *)(unicode))->ob_type), (1UL << 28)) || length < 0) {
        ;
        return -1;
    }
    return unicode_resize(p_unicode, length);
}
static PyObject * get_latin1_char (Py_UCS1 ch){
    struct _Py_unicode_state *state = get_unicode_state();
    PyObject *unicode = state->latin1[ch];
    if (unicode) {
        _Py_INCREF(((PyObject *)(unicode)));
        return unicode;
    }
    unicode = PyUnicode_New(1, ch);
    if (!unicode) {
        return ((void *)0);
    }
    ((Py_UCS1 *)(((void)(0)) , (((PyASCIIObject *)(unicode))->state.compact) ? ((((void)(0)) , ((void)(0)) , ((PyASCIIObject *)unicode)->state.ascii) ? ((void *)((PyASCIIObject *)(unicode) + 1)) : ((void *)((PyCompactUnicodeObject *)(unicode) + 1))) : (((void)(0)) , ((((PyUnicodeObject *)(unicode))->data.any)))))[0] = ch;
    _Py_INCREF(((PyObject *)(unicode)));
    state->latin1[ch] = unicode;
    return unicode;
}
extern  __attribute__((visibility("default"))) PyObject * _PyUnicode_FromASCII (const char *buffer, Py_ssize_t size){
    const unsigned char *s = (const unsigned char *)buffer;
    PyObject *unicode;
    if (size == 1) {
        return get_latin1_char(s[0]);
    }
    unicode = PyUnicode_New(size, 127);
    return unicode;
}
extern  __attribute__((visibility("default"))) PyObject * _PyUnicode_FormatLong (PyObject *val, int alt, int prec, int type){
    PyObject *result = ((void *)0);
    char *buf;
    Py_ssize_t i;
    int sign;
    int len;
    Py_ssize_t llen;
    int numdigits;
    int numnondigits = 0;
    if (prec > 2147483647 - 3) {
        ;
        return ((void *)0);
    }
    ;
    switch (type) {
        ;
      case 'd':
      case 'i':
      case 'u':
        result = PyNumber_ToBase(val, 10);
        break;
      case 'o':
        numnondigits = 2;
        result = PyNumber_ToBase(val, 8);
        break;
      case 'x':
      case 'X':
        numnondigits = 2;
        result = PyNumber_ToBase(val, 16);
        break;
    }
    if (!result)
        return ((void *)0);
    if (_Py_REFCNT(((const PyObject *)(result))) != 1) {
        _Py_DECREF(((PyObject *)(result)));
        return ((void *)0);
    }
    buf = (((void)(0)) , (((PyASCIIObject *)(result))->state.compact) ? ((((void)(0)) , ((void)(0)) , ((PyASCIIObject *)result)->state.ascii) ? ((void *)((PyASCIIObject *)(result) + 1)) : ((void *)((PyCompactUnicodeObject *)(result) + 1))) : (((void)(0)) , ((((PyUnicodeObject *)(result))->data.any))));
    llen = (((void)(0)) , ((void)(0)) , ((PyASCIIObject *)(result))->length);
    if (llen > 2147483647) {
        _Py_DECREF(((PyObject *)(result)));
        return ((void *)0);
    }
    len = (int)llen;
    sign = buf[0] == '-';
    numnondigits += sign;
    numdigits = len - numnondigits;
    if (((alt) == 0 && (type == 'o' || type == 'x' || type == 'X'))) {
        ;
        numnondigits -= 2;
        buf += 2;
        len -= 2;
        if (sign)
            buf[0] = '-';
    }
    if (prec > numdigits) {
        PyObject *r1 = PyBytes_FromStringAndSize(((void *)0), numnondigits + prec);
        char *b1;
        if (!r1) {
            _Py_DECREF(((PyObject *)(result)));
            return ((void *)0);
        }
        b1 = (((void)(0)) , (((PyBytesObject *)(r1))->ob_sval));
        for (i = 0; i < numnondigits; ++i)
            *b1++ = *buf++;
        for (i = 0; i < prec - numdigits; i++)
            *b1++ = '0';
        for (i = 0; i < numdigits; i++)
            *b1++ = *buf++;
        *b1 = '\x00';
        _Py_DECREF(((PyObject *)(result)));
        result = r1;
        buf = (((void)(0)) , (((PyBytesObject *)(result))->ob_sval));
        len = numnondigits + prec;
    }
    if (type == 'X') {
        for (i = 0; i < len; i++)
            if (buf[i] >= 'a' && buf[i] <= 'x')
                buf[i] -= 'a' - 'A';
    }
    if (!PyType_HasFeature((((PyObject *)(result))->ob_type), (1UL << 28)) || buf != (((void)(0)) , (((PyASCIIObject *)(result))->state.compact) ? ((((void)(0)) , ((void)(0)) , ((PyASCIIObject *)result)->state.ascii) ? ((void *)((PyASCIIObject *)(result) + 1)) : ((void *)((PyCompactUnicodeObject *)(result) + 1))) : (((void)(0)) , ((((PyUnicodeObject *)(result))->data.any))))) {
        PyObject *unicode;
        unicode = _PyUnicode_FromASCII(buf, len);
        _Py_DECREF(((PyObject *)(result)));
    } else if (len != (((void)(0)) , ((void)(0)) , ((PyASCIIObject *)(result))->length)) {
        if (PyUnicode_Resize(&result, len) < 0)
            do {
                PyObject *_py_tmp = ((PyObject *)(result));
                if (_py_tmp != ((void *)0)) {
                    (result) = ((void *)0);
                    _Py_DECREF(((PyObject *)(_py_tmp)));
                }
            } while (0);
    }
    return result;
}
