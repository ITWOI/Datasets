#include "header_func.h"
#include "pycore_pystate.h"
#include "codecs.h"
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
extern  __attribute__((visibility("default"))) _Py_error_handler _Py_GetErrorHandler (const char *errors){
    if (errors == ((void *)0) || strcmp(errors, "strict") == 0) {
        return _Py_ERROR_STRICT;
    }
    if (strcmp(errors, "surrogateescape") == 0) {
        return _Py_ERROR_SURROGATEESCAPE;
    }
    if (strcmp(errors, "replace") == 0) {
        return _Py_ERROR_REPLACE;
    }
    if (strcmp(errors, "ignore") == 0) {
        return _Py_ERROR_IGNORE;
    }
    if (strcmp(errors, "backslashreplace") == 0) {
        return _Py_ERROR_BACKSLASHREPLACE;
    }
    if (strcmp(errors, "surrogatepass") == 0) {
        return _Py_ERROR_SURROGATEPASS;
    }
    if (strcmp(errors, "xmlcharrefreplace") == 0) {
        return _Py_ERROR_XMLCHARREFREPLACE;
    }
    return _Py_ERROR_OTHER;
}
static _Py_error_handler get_error_handler_wide (const wchar_t *errors){
    if (errors == ((void *)0) || wcscmp(errors, L"strict") == 0) {
        return _Py_ERROR_STRICT;
    }
    if (wcscmp(errors, L"surrogateescape") == 0) {
        return _Py_ERROR_SURROGATEESCAPE;
    }
    if (wcscmp(errors, L"replace") == 0) {
        return _Py_ERROR_REPLACE;
    }
    if (wcscmp(errors, L"ignore") == 0) {
        return _Py_ERROR_IGNORE;
    }
    if (wcscmp(errors, L"backslashreplace") == 0) {
        return _Py_ERROR_BACKSLASHREPLACE;
    }
    if (wcscmp(errors, L"surrogatepass") == 0) {
        return _Py_ERROR_SURROGATEPASS;
    }
    if (wcscmp(errors, L"xmlcharrefreplace") == 0) {
        return _Py_ERROR_XMLCHARREFREPLACE;
    }
    return _Py_ERROR_OTHER;
}
static inline int unicode_check_encoding_errors (const char *encoding, const char *errors){
    if (encoding == ((void *)0) && errors == ((void *)0)) {
        return 0;
    }
    PyInterpreterState *interp = _PyInterpreterState_GET();
    if (!_PyInterpreterState_GetConfig(interp)->dev_mode) {
        return 0;
    }
    if (!interp->unicode.fs_codec.encoding) {
        return 0;
    }
    if (interp->finalizing) {
        return 0;
    }
    if (encoding != ((void *)0)) {
        PyObject *handler = _PyCodec_Lookup(encoding);
        if (handler == ((void *)0)) {
            return -1;
        }
        _Py_DECREF(((PyObject *)(handler)));
    }
    if (errors != ((void *)0)) {
        PyObject *handler = PyCodec_LookupError(errors);
        if (handler == ((void *)0)) {
            return -1;
        }
        _Py_DECREF(((PyObject *)(handler)));
    }
    return 0;
}
static PyObject * unicode_result_wchar (PyObject *unicode){
    Py_ssize_t len;
    len = (((PyCompactUnicodeObject *)(unicode))->wstr_length);
    if (len == 0) {
        _Py_DECREF(((PyObject *)(unicode)));
        do {
            return unicode_new_empty();
        } while (0);
    }
    if (len == 1) {
        wchar_t ch = (((PyASCIIObject *)(unicode))->wstr)[0];
        if ((Py_UCS4)ch < 256) {
            _Py_DECREF(((PyObject *)(unicode)));
            return get_latin1_char((unsigned char)ch);
        }
    }
    if (_PyUnicode_Ready(unicode) < 0) {
        _Py_DECREF(((PyObject *)(unicode)));
        return ((void *)0);
    }
    return unicode;
}
static PyObject * unicode_result_ready (PyObject *unicode){
    Py_ssize_t length;
    length = (((void)(0)) , ((void)(0)) , ((PyASCIIObject *)(unicode))->length);
    if (length == 0) {
        PyObject *empty = unicode_get_empty();
        if (unicode != empty) {
            _Py_DECREF(((PyObject *)(unicode)));
            _Py_INCREF(((PyObject *)(empty)));
        }
        return empty;
    }
    if (length == 1) {
        int kind = (((void)(0)) , ((void)(0)) , ((PyASCIIObject *)(unicode))->state.kind);
        if (kind == PyUnicode_1BYTE_KIND) {
            const Py_UCS1 *data = ((Py_UCS1 *)(((void)(0)) , (((PyASCIIObject *)(unicode))->state.compact) ? ((((void)(0)) , ((void)(0)) , ((PyASCIIObject *)unicode)->state.ascii) ? ((void *)((PyASCIIObject *)(unicode) + 1)) : ((void *)((PyCompactUnicodeObject *)(unicode) + 1))) : (((void)(0)) , ((((PyUnicodeObject *)(unicode))->data.any)))));
            Py_UCS1 ch = data[0];
            struct _Py_unicode_state *state = get_unicode_state();
            PyObject *latin1_char = state->latin1[ch];
            if (latin1_char != ((void *)0)) {
                if (unicode != latin1_char) {
                    _Py_INCREF(((PyObject *)(latin1_char)));
                    _Py_DECREF(((PyObject *)(unicode)));
                }
                return latin1_char;
            } else {
                ;
                _Py_INCREF(((PyObject *)(unicode)));
                state->latin1[ch] = unicode;
                return unicode;
            }
        } else {
            ;
        }
    }
    ;
    return unicode;
}
static PyObject * unicode_result (PyObject *unicode){
    ;
    if ((((PyASCIIObject *)unicode)->state.ready)) {
        return unicode_result_ready(unicode);
    } else
        return unicode_result_wchar(unicode);
}
static inline Py_ssize_t findchar (const void *s, int kind, Py_ssize_t size, Py_UCS4 ch, int direction){
    switch (kind) {
      case PyUnicode_1BYTE_KIND:
        if ((Py_UCS1)ch != ch)
            return -1;
        if (direction > 0) {
            return ucs1lib_find_char((const Py_UCS1 *)s, size, (Py_UCS1)ch);
        } else
            return ucs1lib_rfind_char((const Py_UCS1 *)s, size, (Py_UCS1)ch);
      case PyUnicode_2BYTE_KIND:
        if ((Py_UCS2)ch != ch)
            return -1;
        if (direction > 0) {
            return ucs2lib_find_char((const Py_UCS2 *)s, size, (Py_UCS2)ch);
        } else
            return ucs2lib_rfind_char((const Py_UCS2 *)s, size, (Py_UCS2)ch);
      case PyUnicode_4BYTE_KIND:
        if (direction > 0) {
            return ucs4lib_find_char((const Py_UCS4 *)s, size, ch);
        } else
            return ucs4lib_rfind_char((const Py_UCS4 *)s, size, ch);
    }
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
            max_char = ucs1lib_find_max_char(from_data, (const Py_UCS1 *)from_data + how_many);
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
static int find_maxchar_surrogates (const wchar_t *begin, const wchar_t *end, Py_UCS4 *maxchar, Py_ssize_t *num_surrogates){
    const wchar_t *iter;
    Py_UCS4 ch;
    *num_surrogates = 0;
    *maxchar = 0;
    for (iter = begin; iter < end;) {
        {
            ch = *iter;
            iter++;
        }
        if (ch > *maxchar) {
            *maxchar = ch;
            if (*maxchar > 1114111) {
                ;
                return -1;
            }
        }
    }
    return 0;
}
extern  __attribute__((visibility("default"))) int _PyUnicode_Ready (PyObject *unicode){
    wchar_t *end;
    Py_UCS4 maxchar = 0;
    Py_ssize_t num_surrogates;
    end = (((PyASCIIObject *)(unicode))->wstr) + (((PyCompactUnicodeObject *)(unicode))->wstr_length);
    if (find_maxchar_surrogates((((PyASCIIObject *)(unicode))->wstr), end, &maxchar, &num_surrogates) == -1)
        return -1;
    if (maxchar < 256) {
        (((PyUnicodeObject *)(unicode))->data.any) = PyObject_Malloc((((PyCompactUnicodeObject *)(unicode))->wstr_length) + 1);
        if (!(((PyUnicodeObject *)(unicode))->data.any)) {
            ;
            return -1;
        }
        do {
            unsigned char *_to = (unsigned char *)(((Py_UCS1 *)(((void)(0)) , (((PyASCIIObject *)(unicode))->state.compact) ? ((((void)(0)) , ((void)(0)) , ((PyASCIIObject *)unicode)->state.ascii) ? ((void *)((PyASCIIObject *)(unicode) + 1)) : ((void *)((PyCompactUnicodeObject *)(unicode) + 1))) : (((void)(0)) , ((((PyUnicodeObject *)(unicode))->data.any))))));
            const wchar_t *_iter = (const wchar_t *)((((PyASCIIObject *)(unicode))->wstr));
            const wchar_t *_end = (const wchar_t *)(end);
            Py_ssize_t n = (_end) - (_iter);
            const wchar_t *_unrolled_end = _iter + ((size_t)(n) & ~(size_t)((4) - 1));
            while (_iter < (_unrolled_end))
                {
                    _to[0] = (unsigned char)_iter[0];
                    _to[1] = (unsigned char)_iter[1];
                    _to[2] = (unsigned char)_iter[2];
                    _to[3] = (unsigned char)_iter[3];
                    _iter += 4;
                    _to += 4;
                }
            while (_iter < (_end))
                *_to++ = (unsigned char)*_iter++;
        } while (0);
        ((Py_UCS1 *)(((void)(0)) , (((PyASCIIObject *)(unicode))->state.compact) ? ((((void)(0)) , ((void)(0)) , ((PyASCIIObject *)unicode)->state.ascii) ? ((void *)((PyASCIIObject *)(unicode) + 1)) : ((void *)((PyCompactUnicodeObject *)(unicode) + 1))) : (((void)(0)) , ((((PyUnicodeObject *)(unicode))->data.any)))))[(((PyCompactUnicodeObject *)(unicode))->wstr_length)] = '\x00';
        (((PyASCIIObject *)(unicode))->length) = (((PyCompactUnicodeObject *)(unicode))->wstr_length);
        (((PyASCIIObject *)(unicode))->state).kind = PyUnicode_1BYTE_KIND;
        if (maxchar < 128) {
            (((PyASCIIObject *)(unicode))->state).ascii = 1;
            (((PyCompactUnicodeObject *)(unicode))->utf8) = (((PyUnicodeObject *)(unicode))->data.any);
            (((PyCompactUnicodeObject *)(unicode))->utf8_length) = (((PyCompactUnicodeObject *)(unicode))->wstr_length);
        } else {
            (((PyASCIIObject *)(unicode))->state).ascii = 0;
            (((PyCompactUnicodeObject *)(unicode))->utf8) = ((void *)0);
            (((PyCompactUnicodeObject *)(unicode))->utf8_length) = 0;
        }
        ;
        (((PyASCIIObject *)(unicode))->wstr) = ((void *)0);
        (((PyCompactUnicodeObject *)(unicode))->wstr_length) = 0;
    } else if (maxchar < 65536) {
        ;
        (((PyUnicodeObject *)(unicode))->data.any) = PyObject_Malloc(2 * ((((PyCompactUnicodeObject *)(unicode))->wstr_length) + 1));
        if (!(((PyUnicodeObject *)(unicode))->data.any)) {
            ;
            return -1;
        }
        do {
            Py_UCS2 *_to = (Py_UCS2 *)(((Py_UCS2 *)(((void)(0)) , (((PyASCIIObject *)(unicode))->state.compact) ? ((((void)(0)) , ((void)(0)) , ((PyASCIIObject *)unicode)->state.ascii) ? ((void *)((PyASCIIObject *)(unicode) + 1)) : ((void *)((PyCompactUnicodeObject *)(unicode) + 1))) : (((void)(0)) , ((((PyUnicodeObject *)(unicode))->data.any))))));
            const wchar_t *_iter = (const wchar_t *)((((PyASCIIObject *)(unicode))->wstr));
            const wchar_t *_end = (const wchar_t *)(end);
            Py_ssize_t n = (_end) - (_iter);
            const wchar_t *_unrolled_end = _iter + ((size_t)(n) & ~(size_t)((4) - 1));
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
        ((Py_UCS2 *)(((void)(0)) , (((PyASCIIObject *)(unicode))->state.compact) ? ((((void)(0)) , ((void)(0)) , ((PyASCIIObject *)unicode)->state.ascii) ? ((void *)((PyASCIIObject *)(unicode) + 1)) : ((void *)((PyCompactUnicodeObject *)(unicode) + 1))) : (((void)(0)) , ((((PyUnicodeObject *)(unicode))->data.any)))))[(((PyCompactUnicodeObject *)(unicode))->wstr_length)] = '\x00';
        (((PyASCIIObject *)(unicode))->length) = (((PyCompactUnicodeObject *)(unicode))->wstr_length);
        (((PyASCIIObject *)(unicode))->state).kind = PyUnicode_2BYTE_KIND;
        (((PyCompactUnicodeObject *)(unicode))->utf8) = ((void *)0);
        (((PyCompactUnicodeObject *)(unicode))->utf8_length) = 0;
        (((PyASCIIObject *)(unicode))->wstr) = ((void *)0);
        (((PyCompactUnicodeObject *)(unicode))->wstr_length) = 0;
    } else {
        ;
        (((PyUnicodeObject *)(unicode))->data.any) = (((PyASCIIObject *)(unicode))->wstr);
        (((PyASCIIObject *)(unicode))->length) = (((PyCompactUnicodeObject *)(unicode))->wstr_length);
        (((PyCompactUnicodeObject *)(unicode))->utf8) = ((void *)0);
        (((PyCompactUnicodeObject *)(unicode))->utf8_length) = 0;
        (((PyASCIIObject *)(unicode))->state).kind = PyUnicode_4BYTE_KIND;
        ((Py_UCS4 *)(((void)(0)) , (((PyASCIIObject *)(unicode))->state.compact) ? ((((void)(0)) , ((void)(0)) , ((PyASCIIObject *)unicode)->state.ascii) ? ((void *)((PyASCIIObject *)(unicode) + 1)) : ((void *)((PyCompactUnicodeObject *)(unicode) + 1))) : (((void)(0)) , ((((PyUnicodeObject *)(unicode))->data.any)))))[(((PyASCIIObject *)(unicode))->length)] = '\x00';
    }
    (((PyASCIIObject *)(unicode))->state).ready = 1;
    return 0;
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
extern  __attribute__((visibility("default"))) PyObject * PyUnicode_FromWideChar (const wchar_t *u, Py_ssize_t size){
    PyObject *unicode;
    Py_UCS4 maxchar = 0;
    Py_ssize_t num_surrogates;
    if (u == ((void *)0) && size != 0) {
        ;
        return ((void *)0);
    }
    if (size == -1) {
        size = wcslen(u);
    }
    if (size == 0)
        do {
            return unicode_new_empty();
        } while (0);
    if (size == 1 && (Py_UCS4)*u < 256)
        return get_latin1_char((unsigned char)*u);
    if (find_maxchar_surrogates(u, u + size, &maxchar, &num_surrogates) == -1)
        return ((void *)0);
    unicode = PyUnicode_New(size - num_surrogates, maxchar);
    if (!unicode)
        return ((void *)0);
    switch ((((void)(0)) , ((void)(0)) , ((PyASCIIObject *)(unicode))->state.kind)) {
      case PyUnicode_1BYTE_KIND:
        do {
            unsigned char *_to = (unsigned char *)(((Py_UCS1 *)(((void)(0)) , (((PyASCIIObject *)(unicode))->state.compact) ? ((((void)(0)) , ((void)(0)) , ((PyASCIIObject *)unicode)->state.ascii) ? ((void *)((PyASCIIObject *)(unicode) + 1)) : ((void *)((PyCompactUnicodeObject *)(unicode) + 1))) : (((void)(0)) , ((((PyUnicodeObject *)(unicode))->data.any))))));
            const Py_UNICODE *_iter = (const Py_UNICODE *)(u);
            const Py_UNICODE *_end = (const Py_UNICODE *)(u + size);
            Py_ssize_t n = (_end) - (_iter);
            const Py_UNICODE *_unrolled_end = _iter + ((size_t)(n) & ~(size_t)((4) - 1));
            while (_iter < (_unrolled_end))
                {
                    _to[0] = (unsigned char)_iter[0];
                    _to[1] = (unsigned char)_iter[1];
                    _to[2] = (unsigned char)_iter[2];
                    _to[3] = (unsigned char)_iter[3];
                    _iter += 4;
                    _to += 4;
                }
            while (_iter < (_end))
                *_to++ = (unsigned char)*_iter++;
        } while (0);
        break;
      case PyUnicode_2BYTE_KIND:
        do {
            Py_UCS2 *_to = (Py_UCS2 *)(((Py_UCS2 *)(((void)(0)) , (((PyASCIIObject *)(unicode))->state.compact) ? ((((void)(0)) , ((void)(0)) , ((PyASCIIObject *)unicode)->state.ascii) ? ((void *)((PyASCIIObject *)(unicode) + 1)) : ((void *)((PyCompactUnicodeObject *)(unicode) + 1))) : (((void)(0)) , ((((PyUnicodeObject *)(unicode))->data.any))))));
            const Py_UNICODE *_iter = (const Py_UNICODE *)(u);
            const Py_UNICODE *_end = (const Py_UNICODE *)(u + size);
            Py_ssize_t n = (_end) - (_iter);
            const Py_UNICODE *_unrolled_end = _iter + ((size_t)(n) & ~(size_t)((4) - 1));
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
        break;
      case PyUnicode_4BYTE_KIND:
        ((void)(0));
        break;
    }
    return unicode_result(unicode);
}
static PyObject * _PyUnicode_FromUCS1 (const Py_UCS1 *u, Py_ssize_t size){
    PyObject *res;
    unsigned char max_char;
    if (size == 0) {
        do {
            return unicode_new_empty();
        } while (0);
    }
    ;
    if (size == 1) {
        return get_latin1_char(u[0]);
    }
    max_char = ucs1lib_find_max_char(u, u + size);
    res = PyUnicode_New(size, max_char);
    if (!res)
        return ((void *)0);
    return res;
}
extern int _Py_normalize_encoding (const char *encoding, char *lower, size_t lower_len){
    const char *e;
    char *l;
    char *l_end;
    int punct;
    e = encoding;
    l = lower;
    l_end = &lower[lower_len - 1];
    punct = 0;
    while (1)
        {
            char c = *e;
            if (c == 0) {
                break;
            }
            if ((_Py_ctype_table[((unsigned char)((c) & 255))] & ((1 | 2) | 4)) || c == '.') {
                if (punct && l != lower) {
                    if (l == l_end) {
                        return 0;
                    }
                    *l++ = '_';
                }
                punct = 0;
                if (l == l_end) {
                    return 0;
                }
                *l++ = (_Py_ctype_tolower[((unsigned char)((c) & 255))]);
            } else {
                punct = 1;
            }
            e++;
        }
    *l = '\x00';
    return 1;
}
extern  __attribute__((visibility("default"))) PyObject * PyUnicode_Decode (const char *s, Py_ssize_t size, const char *encoding, const char *errors){
    PyObject *buffer = ((void *)0), *unicode;
    Py_buffer info;
    char buflower[11];
    if (unicode_check_encoding_errors(encoding, errors) < 0) {
        return ((void *)0);
    }
    if (size == 0) {
        do {
            return unicode_new_empty();
        } while (0);
    }
    if (encoding == ((void *)0)) {
        return PyUnicode_DecodeUTF8Stateful(s, size, errors, ((void *)0));
    }
    if (_Py_normalize_encoding(encoding, buflower, sizeof (buflower))) {
        char *lower = buflower;
        if (lower[0] == 'u' && lower[1] == 't' && lower[2] == 'f') {
            lower += 3;
            if (*lower == '_') {
                lower++;
            }
            if (lower[0] == '8' && lower[1] == 0) {
                return PyUnicode_DecodeUTF8Stateful(s, size, errors, ((void *)0));
            } else if (lower[0] == '1' && lower[1] == '6' && lower[2] == 0) {
                return PyUnicode_DecodeUTF16(s, size, errors, 0);
            } else if (lower[0] == '3' && lower[1] == '2' && lower[2] == 0) {
                return PyUnicode_DecodeUTF32(s, size, errors, 0);
            }
        } else {
            if (strcmp(lower, "ascii") == 0 || strcmp(lower, "us_ascii") == 0) {
                return PyUnicode_DecodeASCII(s, size, errors);
            } else if (strcmp(lower, "latin1") == 0 || strcmp(lower, "latin_1") == 0 || strcmp(lower, "iso_8859_1") == 0 || strcmp(lower, "iso8859_1") == 0) {
                return PyUnicode_DecodeLatin1(s, size, errors);
            }
        }
    }
    buffer = ((void *)0);
    if (PyBuffer_FillInfo(&info, ((void *)0), (void *)s, size, 1, ((256 | (16 | 8)) | 4)) < 0)
        goto onError;
    buffer = PyMemoryView_FromBuffer(&info);
    if (buffer == ((void *)0))
        goto onError;
    unicode = _PyCodec_DecodeText(buffer, encoding, errors);
    if (unicode == ((void *)0))
        goto onError;
    if (!PyType_HasFeature((((PyObject *)(unicode))->ob_type), (1UL << 28))) {
        ;
        _Py_DECREF(((PyObject *)(unicode)));
        goto onError;
    }
    _Py_DECREF(((PyObject *)(buffer)));
    return unicode_result(unicode);
  onError:
    _Py_XDECREF(((PyObject *)(buffer)));
    return ((void *)0);
}
static PyObject * unicode_decode_locale (const char *str, Py_ssize_t len, _Py_error_handler errors, int current_locale){
    if (str[len] != '\x00' || (size_t)len != strlen(str)) {
        ;
        return ((void *)0);
    }
    wchar_t *wstr;
    size_t wlen;
    const char *reason;
    int res = _Py_DecodeLocaleEx(str, &wstr, &wlen, &reason, current_locale, errors);
    if (res != 0) {
        if (res == -2) {
            PyObject *exc;
            exc = _PyObject_CallFunction_SizeT(PyExc_UnicodeDecodeError, "sy#nns", "locale", str, len, (Py_ssize_t)wlen, (Py_ssize_t)(wlen + 1), reason);
            if (exc != ((void *)0)) {
                ;
                _Py_DECREF(((PyObject *)(exc)));
            }
        } else {
            ;
        }
        return ((void *)0);
    }
    PyObject *unicode = PyUnicode_FromWideChar(wstr, wlen);
    return unicode;
}
extern  __attribute__((visibility("default"))) PyObject * PyUnicode_DecodeFSDefaultAndSize (const char *s, Py_ssize_t size){
    PyInterpreterState *interp = _PyInterpreterState_GET();
    struct _Py_unicode_fs_codec *fs_codec = &interp->unicode.fs_codec;
    if (fs_codec->utf8) {
        return unicode_decode_utf8(s, size, fs_codec->error_handler, fs_codec->errors, ((void *)0));
    } else if (fs_codec->encoding) {
        return PyUnicode_Decode(s, size, fs_codec->encoding, fs_codec->errors);
    } else {
        const PyConfig *config = _PyInterpreterState_GetConfig(interp);
        const wchar_t *filesystem_errors = config->filesystem_errors;
        _Py_error_handler errors = get_error_handler_wide(filesystem_errors);
        return unicode_decode_locale(s, size, errors, 0);
    }
}
extern  __attribute__((visibility("default"))) int PyUnicode_FSDecoder (PyObject *arg, void *addr){
    int is_buffer = 0;
    PyObject *path = ((void *)0);
    PyObject *output = ((void *)0);
    if (arg == ((void *)0)) {
        _Py_DECREF(((PyObject *)(*(PyObject **)addr)));
        return 1;
    }
    is_buffer = PyObject_CheckBuffer(arg);
    if (!is_buffer) {
        path = PyOS_FSPath(arg);
        if (path == ((void *)0)) {
            return 0;
        }
    } else {
        path = arg;
        _Py_INCREF(((PyObject *)(arg)));
    }
    if (PyType_HasFeature((((PyObject *)(path))->ob_type), (1UL << 28))) {
        output = path;
    } else if (PyType_HasFeature((((PyObject *)(path))->ob_type), (1UL << 27)) || is_buffer) {
        PyObject *path_bytes = ((void *)0);
        if (!PyType_HasFeature((((PyObject *)(path))->ob_type), (1UL << 27)) && PyErr_WarnFormat(PyExc_DeprecationWarning, 1, "path should be string, bytes, or os.PathLike, not %.200s", (((PyObject *)(arg))->ob_type)->tp_name)) {
            _Py_DECREF(((PyObject *)(path)));
            return 0;
        }
        path_bytes = PyBytes_FromObject(path);
        _Py_DECREF(((PyObject *)(path)));
        if (!path_bytes) {
            return 0;
        }
        output = PyUnicode_DecodeFSDefaultAndSize((((void)(0)) , (((PyBytesObject *)(path_bytes))->ob_sval)), (((void)(0)) , (((PyVarObject *)(path_bytes))->ob_size)));
        _Py_DECREF(((PyObject *)(path_bytes)));
        if (!output) {
            return 0;
        }
    } else {
        ;
        _Py_DECREF(((PyObject *)(path)));
        return 0;
    }
    if ((((void)(0)) , ((((PyASCIIObject *)output)->state.ready) ? 0 : _PyUnicode_Ready(output))) == -1) {
        _Py_DECREF(((PyObject *)(output)));
        return 0;
    }
    if (findchar((((void)(0)) , (((PyASCIIObject *)(output))->state.compact) ? ((((void)(0)) , ((void)(0)) , ((PyASCIIObject *)output)->state.ascii) ? ((void *)((PyASCIIObject *)(output) + 1)) : ((void *)((PyCompactUnicodeObject *)(output) + 1))) : (((void)(0)) , ((((PyUnicodeObject *)(output))->data.any)))), (((void)(0)) , ((void)(0)) , ((PyASCIIObject *)(output))->state.kind), (((void)(0)) , ((void)(0)) , ((PyASCIIObject *)(output))->length), 0, 1) >= 0) {
        ;
        _Py_DECREF(((PyObject *)(output)));
        return 0;
    }
    ;
    return 131072;
}
static void make_decode_exception (PyObject **exceptionObject, const char *encoding, const char *input, Py_ssize_t length, Py_ssize_t startpos, Py_ssize_t endpos, const char *reason){
    if (*exceptionObject == ((void *)0)) {
        *exceptionObject = PyUnicodeDecodeError_Create(encoding, input, length, startpos, endpos, reason);
    } else {
        if (PyUnicodeDecodeError_SetStart(*exceptionObject, startpos))
            goto onError;
        if (PyUnicodeDecodeError_SetEnd(*exceptionObject, endpos))
            goto onError;
        if (PyUnicodeDecodeError_SetReason(*exceptionObject, reason))
            goto onError;
    }
    return;
  onError:
    do {
        PyObject *_py_tmp = ((PyObject *)(*exceptionObject));
        if (_py_tmp != ((void *)0)) {
            (*exceptionObject) = ((void *)0);
            _Py_DECREF(((PyObject *)(_py_tmp)));
        }
    } while (0);
}
static int unicode_decode_call_errorhandler_writer (const char *errors, PyObject **errorHandler, const char *encoding, const char *reason, const char **input, const char **inend, Py_ssize_t *startinpos, Py_ssize_t *endinpos, PyObject **exceptionObject, const char **inptr, _PyUnicodeWriter *writer){
    static const char *argparse = "Un;decoding error handler must return (str, int) tuple";
    PyObject *restuple = ((void *)0);
    PyObject *repunicode = ((void *)0);
    Py_ssize_t insize;
    Py_ssize_t newpos;
    Py_ssize_t replen;
    Py_ssize_t remain;
    PyObject *inputobj = ((void *)0);
    int need_to_grow = 0;
    const char *new_inptr;
    if (*errorHandler == ((void *)0)) {
        *errorHandler = PyCodec_LookupError(errors);
        if (*errorHandler == ((void *)0))
            goto onError;
    }
    make_decode_exception(exceptionObject, encoding, *input, *inend - *input, *startinpos, *endinpos, reason);
    if (*exceptionObject == ((void *)0))
        goto onError;
    restuple = PyObject_CallOneArg(*errorHandler, *exceptionObject);
    if (restuple == ((void *)0))
        goto onError;
    if (!PyType_HasFeature((((PyObject *)(restuple))->ob_type), (1UL << 26))) {
        ;
        goto onError;
    }
    if (!_PyArg_ParseTuple_SizeT(restuple, argparse, &repunicode, &newpos))
        goto onError;
    inputobj = PyUnicodeDecodeError_GetObject(*exceptionObject);
    if (!inputobj)
        goto onError;
    remain = *inend - *input - *endinpos;
    *input = (((void)(0)) , (((PyBytesObject *)(inputobj))->ob_sval));
    insize = (((void)(0)) , (((PyVarObject *)(inputobj))->ob_size));
    *inend = *input + insize;
    _Py_DECREF(((PyObject *)(inputobj)));
    if (newpos < 0)
        newpos = insize + newpos;
    if (newpos < 0 || newpos > insize) {
        ;
        goto onError;
    }
    replen = (((void)(0)) , ((void)(0)) , ((PyASCIIObject *)(repunicode))->length);
    if (replen > 1) {
        writer->min_length += replen - 1;
        need_to_grow = 1;
    }
    new_inptr = *input + newpos;
    if (*inend - new_inptr > remain) {
        writer->min_length += *inend - new_inptr - remain;
        need_to_grow = 1;
    }
    if (need_to_grow) {
        writer->overallocate = 1;
        if (((((((void)(0)) , ((((void)(0)) , ((void)(0)) , ((PyASCIIObject *)repunicode)->state.ascii) ? (127) : ((((void)(0)) , ((void)(0)) , ((PyASCIIObject *)(repunicode))->state.kind) == PyUnicode_1BYTE_KIND ? (255U) : ((((void)(0)) , ((void)(0)) , ((PyASCIIObject *)(repunicode))->state.kind) == PyUnicode_2BYTE_KIND ? (65535U) : (1114111U)))))) <= (writer)->maxchar && (writer->min_length - writer->pos) <= (writer)->size - (writer)->pos) ? 0 : (((writer->min_length - writer->pos) == 0) ? 0 : _PyUnicodeWriter_PrepareInternal((writer), (writer->min_length - writer->pos), ((((void)(0)) , ((((void)(0)) , ((void)(0)) , ((PyASCIIObject *)repunicode)->state.ascii) ? (127) : ((((void)(0)) , ((void)(0)) , ((PyASCIIObject *)(repunicode))->state.kind) == PyUnicode_1BYTE_KIND ? (255U) : ((((void)(0)) , ((void)(0)) , ((PyASCIIObject *)(repunicode))->state.kind) == PyUnicode_2BYTE_KIND ? (65535U) : (1114111U))))))))) == -1)
            goto onError;
    }
    if (_PyUnicodeWriter_WriteStr(writer, repunicode) == -1)
        goto onError;
    _Py_DECREF(((PyObject *)(restuple)));
    return 0;
  onError:
    _Py_XDECREF(((PyObject *)(restuple)));
    return -1;
}
static Py_ssize_t ascii_decode (const char *start, const char *end, Py_UCS1 *dest){
    const char *p = start;
    if ((!((uintptr_t)(p) & (uintptr_t)((8) - 1)))) {
        const char *_p = p;
        Py_UCS1 *q = dest;
        while (_p + 8 <= end)
            {
                size_t value = *(const size_t *)_p;
                if (value & 9259542123273814144ULL)
                    break;
                *((size_t *)q) = value;
                _p += 8;
                q += 8;
            }
        p = _p;
        while (p < end)
            {
                if ((unsigned char)*p & 128)
                    break;
                *q++ = *p++;
            }
        return p - start;
    }
    while (p < end)
        {
            if ((!((uintptr_t)(p) & (uintptr_t)((8) - 1)))) {
                const char *_p = p;
                while (_p + 8 <= end)
                    {
                        size_t value = *(const size_t *)_p;
                        if (value & 9259542123273814144ULL)
                            break;
                        _p += 8;
                    }
                p = _p;
                if (_p == end)
                    break;
            }
            if ((unsigned char)*p & 128)
                break;
            ++p;
        }
    ;
    return p - start;
}
static PyObject * unicode_decode_utf8 (const char *s, Py_ssize_t size, _Py_error_handler error_handler, const char *errors, Py_ssize_t *consumed){
    if (size == 0) {
        ;
        do {
            return unicode_new_empty();
        } while (0);
    }
    if (size == 1 && (unsigned char)s[0] < 128) {
        return get_latin1_char((unsigned char)s[0]);
    }
    const char *starts = s;
    const char *end = s + size;
    PyObject *u = PyUnicode_New(size, 127);
    if (u == ((void *)0)) {
        return ((void *)0);
    }
    s += ascii_decode(s, end, ((Py_UCS1 *)(((void)(0)) , (((PyASCIIObject *)(u))->state.compact) ? ((((void)(0)) , ((void)(0)) , ((PyASCIIObject *)u)->state.ascii) ? ((void *)((PyASCIIObject *)(u) + 1)) : ((void *)((PyCompactUnicodeObject *)(u) + 1))) : (((void)(0)) , ((((PyUnicodeObject *)(u))->data.any))))));
    if (s == end) {
        return u;
    }
    _PyUnicodeWriter writer;
    _PyUnicodeWriter_InitWithBuffer(&writer, u);
    writer.pos = s - starts;
    Py_ssize_t startinpos, endinpos;
    const char *errmsg = "";
    PyObject *error_handler_obj = ((void *)0);
    PyObject *exc = ((void *)0);
    while (s < end)
        {
            Py_UCS4 ch;
            int kind = writer.kind;
            if (kind == PyUnicode_1BYTE_KIND) {
                if ((((void)(0)) , ((void)(0)) , ((PyASCIIObject *)writer.buffer)->state.ascii)) {
                    ch = asciilib_utf8_decode(&s, end, writer.data, &writer.pos);
                } else
                    ch = ucs1lib_utf8_decode(&s, end, writer.data, &writer.pos);
            } else if (kind == PyUnicode_2BYTE_KIND) {
                ch = ucs2lib_utf8_decode(&s, end, writer.data, &writer.pos);
            } else {
                ;
                ch = ucs4lib_utf8_decode(&s, end, writer.data, &writer.pos);
            }
            switch (ch) {
              case 0:
                if (s == end || consumed)
                    goto End;
                errmsg = "unexpected end of data";
                startinpos = s - starts;
                endinpos = end - starts;
                break;
              case 1:
                errmsg = "invalid start byte";
                startinpos = s - starts;
                endinpos = startinpos + 1;
                break;
              case 2:
                if (consumed && (unsigned char)s[0] == 237 && end - s == 2 && (unsigned char)s[1] >= 160 && (unsigned char)s[1] <= 191) {
                    goto End;
                }
              case 3:
              case 4:
                errmsg = "invalid continuation byte";
                startinpos = s - starts;
                endinpos = startinpos + ch - 1;
                break;
              default:
                if (_PyUnicodeWriter_WriteCharInline(&writer, ch) < 0)
                    goto onError;
            }
            if (error_handler == _Py_ERROR_UNKNOWN)
                error_handler = _Py_GetErrorHandler(errors);
            switch (error_handler) {
              case _Py_ERROR_IGNORE:
                s += (endinpos - startinpos);
                break;
              case _Py_ERROR_REPLACE:
                if (_PyUnicodeWriter_WriteCharInline(&writer, 65533) < 0)
                    goto onError;
                s += (endinpos - startinpos);
                break;
              case _Py_ERROR_SURROGATEESCAPE:
                {
                    Py_ssize_t i;
                    if ((((void)(0)) , (PyUnicode_2BYTE_KIND) <= (&writer)->kind ? 0 : _PyUnicodeWriter_PrepareKindInternal((&writer), (PyUnicode_2BYTE_KIND))) < 0)
                        goto onError;
                    for (i = startinpos; i < endinpos; i++) {
                        ch = (Py_UCS4)(unsigned char)(starts[i]);
                        do {
                            switch ((writer.kind)) {
                              case PyUnicode_1BYTE_KIND:
                                {
                                    ((Py_UCS1 *)(writer.data))[(writer.pos)] = (Py_UCS1)(ch + 56320);
                                    break;
                                }
                              case PyUnicode_2BYTE_KIND:
                                {
                                    ((Py_UCS2 *)(writer.data))[(writer.pos)] = (Py_UCS2)(ch + 56320);
                                    break;
                                }
                              default:
                                {
                                    ((void)(0));
                                    ((Py_UCS4 *)(writer.data))[(writer.pos)] = (Py_UCS4)(ch + 56320);
                                }
                            }
                        } while (0);
                        writer.pos++;
                    }
                    s += (endinpos - startinpos);
                    break;
                }
              default:
                if (unicode_decode_call_errorhandler_writer(errors, &error_handler_obj, "utf-8", errmsg, &starts, &end, &startinpos, &endinpos, &exc, &s, &writer))
                    goto onError;
            }
        }
  End:
    ;
    _Py_XDECREF(((PyObject *)(error_handler_obj)));
    _Py_XDECREF(((PyObject *)(exc)));
    return _PyUnicodeWriter_Finish(&writer);
  onError:
    _Py_XDECREF(((PyObject *)(error_handler_obj)));
    _Py_XDECREF(((PyObject *)(exc)));
    _PyUnicodeWriter_Dealloc(&writer);
    return ((void *)0);
}
extern  __attribute__((visibility("default"))) PyObject * PyUnicode_DecodeUTF8Stateful (const char *s, Py_ssize_t size, const char *errors, Py_ssize_t *consumed){
    return unicode_decode_utf8(s, size, _Py_ERROR_UNKNOWN, errors, consumed);
}
extern  __attribute__((visibility("default"))) PyObject * PyUnicode_DecodeUTF32 (const char *s, Py_ssize_t size, const char *errors, int *byteorder){
    return PyUnicode_DecodeUTF32Stateful(s, size, errors, byteorder, ((void *)0));
}
extern  __attribute__((visibility("default"))) PyObject * PyUnicode_DecodeUTF32Stateful (const char *s, Py_ssize_t size, const char *errors, int *byteorder, Py_ssize_t *consumed){
    const char *starts = s;
    Py_ssize_t startinpos;
    Py_ssize_t endinpos;
    _PyUnicodeWriter writer;
    const unsigned char *q, *e;
    int le, bo = 0;
    const char *encoding;
    const char *errmsg = "";
    PyObject *errorHandler = ((void *)0);
    PyObject *exc = ((void *)0);
    q = (const unsigned char *)s;
    e = q + size;
    if (byteorder)
        bo = *byteorder;
    if (bo == 0 && size >= 4) {
        Py_UCS4 bom = ((unsigned int)q[3] << 24) | (q[2] << 16) | (q[1] << 8) | q[0];
        if (bom == 65279) {
            bo = -1;
            q += 4;
        } else if (bom == 4294836224U) {
            bo = 1;
            q += 4;
        }
        ;
    }
    if (q == e) {
        ;
        do {
            return unicode_new_empty();
        } while (0);
    }
    le = bo <= 0;
    encoding = le ? "utf-32-le" : "utf-32-be";
    _PyUnicodeWriter_Init(&writer);
    writer.min_length = (e - q + 3) / 4;
    if ((((127) <= (&writer)->maxchar && (writer.min_length) <= (&writer)->size - (&writer)->pos) ? 0 : (((writer.min_length) == 0) ? 0 : _PyUnicodeWriter_PrepareInternal((&writer), (writer.min_length), (127)))) == -1)
        goto onError;
    while (1)
        {
            Py_UCS4 ch = 0;
            Py_UCS4 maxch = (((void)(0)) , ((((void)(0)) , ((void)(0)) , ((PyASCIIObject *)writer.buffer)->state.ascii) ? (127) : ((((void)(0)) , ((void)(0)) , ((PyASCIIObject *)(writer.buffer))->state.kind) == PyUnicode_1BYTE_KIND ? (255U) : ((((void)(0)) , ((void)(0)) , ((PyASCIIObject *)(writer.buffer))->state.kind) == PyUnicode_2BYTE_KIND ? (65535U) : (1114111U)))));
            if (e - q >= 4) {
                enum PyUnicode_Kind kind = writer.kind;
                void *data = writer.data;
                const unsigned char *last = e - 4;
                Py_ssize_t pos = writer.pos;
                if (le) {
                    do {
                        ch = ((unsigned int)q[3] << 24) | (q[2] << 16) | (q[1] << 8) | q[0];
                        if (ch > maxch)
                            break;
                        if (kind != PyUnicode_1BYTE_KIND && (55296 <= (ch) && (ch) <= 57343))
                            break;
                        do {
                            switch ((kind)) {
                              case PyUnicode_1BYTE_KIND:
                                {
                                    ((Py_UCS1 *)(data))[(pos++)] = (Py_UCS1)(ch);
                                    break;
                                }
                              case PyUnicode_2BYTE_KIND:
                                {
                                    ((Py_UCS2 *)(data))[(pos++)] = (Py_UCS2)(ch);
                                    break;
                                }
                              default:
                                {
                                    ((void)(0));
                                    ((Py_UCS4 *)(data))[(pos++)] = (Py_UCS4)(ch);
                                }
                            }
                        } while (0);
                        q += 4;
                    } while (q <= last);
                } else {
                    do {
                        ch = ((unsigned int)q[0] << 24) | (q[1] << 16) | (q[2] << 8) | q[3];
                        if (ch > maxch)
                            break;
                        if (kind != PyUnicode_1BYTE_KIND && (55296 <= (ch) && (ch) <= 57343))
                            break;
                        do {
                            switch ((kind)) {
                              case PyUnicode_1BYTE_KIND:
                                {
                                    ((Py_UCS1 *)(data))[(pos++)] = (Py_UCS1)(ch);
                                    break;
                                }
                              case PyUnicode_2BYTE_KIND:
                                {
                                    ((Py_UCS2 *)(data))[(pos++)] = (Py_UCS2)(ch);
                                    break;
                                }
                              default:
                                {
                                    ((void)(0));
                                    ((Py_UCS4 *)(data))[(pos++)] = (Py_UCS4)(ch);
                                }
                            }
                        } while (0);
                        q += 4;
                    } while (q <= last);
                }
                writer.pos = pos;
            }
            if ((55296 <= (ch) && (ch) <= 57343)) {
                errmsg = "code point in surrogate code point range(0xd800, 0xe000)";
                startinpos = ((const char *)q) - starts;
                endinpos = startinpos + 4;
            } else if (ch <= maxch) {
                if (q == e || consumed)
                    break;
                errmsg = "truncated data";
                startinpos = ((const char *)q) - starts;
                endinpos = ((const char *)e) - starts;
            } else {
                if (ch < 1114112) {
                    if (_PyUnicodeWriter_WriteCharInline(&writer, ch) < 0)
                        goto onError;
                    q += 4;
                    continue;
                }
                errmsg = "code point not in range(0x110000)";
                startinpos = ((const char *)q) - starts;
                endinpos = startinpos + 4;
            }
            if (unicode_decode_call_errorhandler_writer(errors, &errorHandler, encoding, errmsg, &starts, (const char **)&e, &startinpos, &endinpos, &exc, (const char **)&q, &writer))
                goto onError;
        }
    ;
    _Py_XDECREF(((PyObject *)(errorHandler)));
    _Py_XDECREF(((PyObject *)(exc)));
    return _PyUnicodeWriter_Finish(&writer);
  onError:
    _PyUnicodeWriter_Dealloc(&writer);
    _Py_XDECREF(((PyObject *)(errorHandler)));
    _Py_XDECREF(((PyObject *)(exc)));
    return ((void *)0);
}
extern  __attribute__((visibility("default"))) PyObject * PyUnicode_DecodeUTF16 (const char *s, Py_ssize_t size, const char *errors, int *byteorder){
    return PyUnicode_DecodeUTF16Stateful(s, size, errors, byteorder, ((void *)0));
}
extern  __attribute__((visibility("default"))) PyObject * PyUnicode_DecodeUTF16Stateful (const char *s, Py_ssize_t size, const char *errors, int *byteorder, Py_ssize_t *consumed){
    const char *starts = s;
    Py_ssize_t startinpos;
    Py_ssize_t endinpos;
    _PyUnicodeWriter writer;
    const unsigned char *q, *e;
    int bo = 0;
    int native_ordering;
    const char *errmsg = "";
    PyObject *errorHandler = ((void *)0);
    PyObject *exc = ((void *)0);
    const char *encoding;
    q = (const unsigned char *)s;
    e = q + size;
    if (byteorder)
        bo = *byteorder;
    if (bo == 0 && size >= 2) {
        const Py_UCS4 bom = (q[1] << 8) | q[0];
        if (bom == 65279) {
            q += 2;
            bo = -1;
        } else if (bom == 65534) {
            q += 2;
            bo = 1;
        }
        ;
    }
    if (q == e) {
        ;
        do {
            return unicode_new_empty();
        } while (0);
    }
    native_ordering = bo <= 0;
    encoding = bo <= 0 ? "utf-16-le" : "utf-16-be";
    _PyUnicodeWriter_Init(&writer);
    writer.min_length = (e - q + 1) / 2;
    if ((((127) <= (&writer)->maxchar && (writer.min_length) <= (&writer)->size - (&writer)->pos) ? 0 : (((writer.min_length) == 0) ? 0 : _PyUnicodeWriter_PrepareInternal((&writer), (writer.min_length), (127)))) == -1)
        goto onError;
    while (1)
        {
            Py_UCS4 ch = 0;
            if (e - q >= 2) {
                int kind = writer.kind;
                if (kind == PyUnicode_1BYTE_KIND) {
                    if ((((void)(0)) , ((void)(0)) , ((PyASCIIObject *)writer.buffer)->state.ascii)) {
                        ch = asciilib_utf16_decode(&q, e, (Py_UCS1 *)writer.data, &writer.pos, native_ordering);
                    } else
                        ch = ucs1lib_utf16_decode(&q, e, (Py_UCS1 *)writer.data, &writer.pos, native_ordering);
                } else if (kind == PyUnicode_2BYTE_KIND) {
                    ch = ucs2lib_utf16_decode(&q, e, (Py_UCS2 *)writer.data, &writer.pos, native_ordering);
                } else {
                    ;
                    ch = ucs4lib_utf16_decode(&q, e, (Py_UCS4 *)writer.data, &writer.pos, native_ordering);
                }
            }
            switch (ch) {
              case 0:
                if (q == e || consumed)
                    goto End;
                errmsg = "truncated data";
                startinpos = ((const char *)q) - starts;
                endinpos = ((const char *)e) - starts;
                break;
              case 1:
                q -= 2;
                if (consumed)
                    goto End;
                errmsg = "unexpected end of data";
                startinpos = ((const char *)q) - starts;
                endinpos = ((const char *)e) - starts;
                break;
              case 2:
                errmsg = "illegal encoding";
                startinpos = ((const char *)q) - 2 - starts;
                endinpos = startinpos + 2;
                break;
              case 3:
                errmsg = "illegal UTF-16 surrogate";
                startinpos = ((const char *)q) - 4 - starts;
                endinpos = startinpos + 2;
                break;
              default:
                if (_PyUnicodeWriter_WriteCharInline(&writer, ch) < 0)
                    goto onError;
            }
            if (unicode_decode_call_errorhandler_writer(errors, &errorHandler, encoding, errmsg, &starts, (const char **)&e, &startinpos, &endinpos, &exc, (const char **)&q, &writer))
                goto onError;
        }
  End:
    ;
    _Py_XDECREF(((PyObject *)(errorHandler)));
    _Py_XDECREF(((PyObject *)(exc)));
    return _PyUnicodeWriter_Finish(&writer);
  onError:
    _PyUnicodeWriter_Dealloc(&writer);
    _Py_XDECREF(((PyObject *)(errorHandler)));
    _Py_XDECREF(((PyObject *)(exc)));
    return ((void *)0);
}
extern  __attribute__((visibility("default"))) PyObject * PyUnicode_DecodeLatin1 (const char *s, Py_ssize_t size, const char *errors){
    return _PyUnicode_FromUCS1((const unsigned char *)s, size);
}
extern  __attribute__((visibility("default"))) PyObject * PyUnicode_DecodeASCII (const char *s, Py_ssize_t size, const char *errors){
    const char *starts = s;
    const char *e = s + size;
    PyObject *error_handler_obj = ((void *)0);
    PyObject *exc = ((void *)0);
    _Py_error_handler error_handler = _Py_ERROR_UNKNOWN;
    if (size == 0)
        do {
            return unicode_new_empty();
        } while (0);
    if (size == 1 && (unsigned char)s[0] < 128) {
        return get_latin1_char((unsigned char)s[0]);
    }
    PyObject *u = PyUnicode_New(size, 127);
    if (u == ((void *)0)) {
        return ((void *)0);
    }
    Py_ssize_t outpos = ascii_decode(s, e, ((Py_UCS1 *)(((void)(0)) , (((PyASCIIObject *)(u))->state.compact) ? ((((void)(0)) , ((void)(0)) , ((PyASCIIObject *)u)->state.ascii) ? ((void *)((PyASCIIObject *)(u) + 1)) : ((void *)((PyCompactUnicodeObject *)(u) + 1))) : (((void)(0)) , ((((PyUnicodeObject *)(u))->data.any))))));
    if (outpos == size) {
        return u;
    }
    _PyUnicodeWriter writer;
    _PyUnicodeWriter_InitWithBuffer(&writer, u);
    writer.pos = outpos;
    s += outpos;
    int kind = writer.kind;
    void *data = writer.data;
    Py_ssize_t startinpos, endinpos;
    while (s < e)
        {
            unsigned char c = (unsigned char)*s;
            if (c < 128) {
                do {
                    switch ((kind)) {
                      case PyUnicode_1BYTE_KIND:
                        {
                            ((Py_UCS1 *)(data))[(writer.pos)] = (Py_UCS1)(c);
                            break;
                        }
                      case PyUnicode_2BYTE_KIND:
                        {
                            ((Py_UCS2 *)(data))[(writer.pos)] = (Py_UCS2)(c);
                            break;
                        }
                      default:
                        {
                            ((void)(0));
                            ((Py_UCS4 *)(data))[(writer.pos)] = (Py_UCS4)(c);
                        }
                    }
                } while (0);
                writer.pos++;
                ++s;
                continue;
            }
            if (error_handler == _Py_ERROR_UNKNOWN)
                error_handler = _Py_GetErrorHandler(errors);
            switch (error_handler) {
              case _Py_ERROR_REPLACE:
              case _Py_ERROR_SURROGATEESCAPE:
                if ((((void)(0)) , (PyUnicode_2BYTE_KIND) <= (&writer)->kind ? 0 : _PyUnicodeWriter_PrepareKindInternal((&writer), (PyUnicode_2BYTE_KIND))) < 0)
                    goto onError;
                kind = writer.kind;
                data = writer.data;
                if (error_handler == _Py_ERROR_REPLACE)
                    do {
                        switch ((kind)) {
                          case PyUnicode_1BYTE_KIND:
                            {
                                ((Py_UCS1 *)(data))[(writer.pos)] = (Py_UCS1)(65533);
                                break;
                            }
                          case PyUnicode_2BYTE_KIND:
                            {
                                ((Py_UCS2 *)(data))[(writer.pos)] = (Py_UCS2)(65533);
                                break;
                            }
                          default:
                            {
                                ((void)(0));
                                ((Py_UCS4 *)(data))[(writer.pos)] = (Py_UCS4)(65533);
                            }
                        }
                    } while (0);
                else
                    do {
                        switch ((kind)) {
                          case PyUnicode_1BYTE_KIND:
                            {
                                ((Py_UCS1 *)(data))[(writer.pos)] = (Py_UCS1)(c + 56320);
                                break;
                            }
                          case PyUnicode_2BYTE_KIND:
                            {
                                ((Py_UCS2 *)(data))[(writer.pos)] = (Py_UCS2)(c + 56320);
                                break;
                            }
                          default:
                            {
                                ((void)(0));
                                ((Py_UCS4 *)(data))[(writer.pos)] = (Py_UCS4)(c + 56320);
                            }
                        }
                    } while (0);
                writer.pos++;
                ++s;
                break;
              case _Py_ERROR_IGNORE:
                ++s;
                break;
              default:
                startinpos = s - starts;
                endinpos = startinpos + 1;
                if (unicode_decode_call_errorhandler_writer(errors, &error_handler_obj, "ascii", "ordinal not in range(128)", &starts, &e, &startinpos, &endinpos, &exc, &s, &writer))
                    goto onError;
                kind = writer.kind;
                data = writer.data;
            }
        }
    _Py_XDECREF(((PyObject *)(error_handler_obj)));
    _Py_XDECREF(((PyObject *)(exc)));
    return _PyUnicodeWriter_Finish(&writer);
  onError:
    _PyUnicodeWriter_Dealloc(&writer);
    _Py_XDECREF(((PyObject *)(error_handler_obj)));
    _Py_XDECREF(((PyObject *)(exc)));
    return ((void *)0);
}
static inline void _PyUnicodeWriter_Update (_PyUnicodeWriter *writer){
    writer->maxchar = (((void)(0)) , ((((void)(0)) , ((void)(0)) , ((PyASCIIObject *)writer->buffer)->state.ascii) ? (127) : ((((void)(0)) , ((void)(0)) , ((PyASCIIObject *)(writer->buffer))->state.kind) == PyUnicode_1BYTE_KIND ? (255U) : ((((void)(0)) , ((void)(0)) , ((PyASCIIObject *)(writer->buffer))->state.kind) == PyUnicode_2BYTE_KIND ? (65535U) : (1114111U)))));
    writer->data = (((void)(0)) , (((PyASCIIObject *)(writer->buffer))->state.compact) ? ((((void)(0)) , ((void)(0)) , ((PyASCIIObject *)writer->buffer)->state.ascii) ? ((void *)((PyASCIIObject *)(writer->buffer) + 1)) : ((void *)((PyCompactUnicodeObject *)(writer->buffer) + 1))) : (((void)(0)) , ((((PyUnicodeObject *)(writer->buffer))->data.any))));
    if (!writer->readonly) {
        writer->kind = (((void)(0)) , ((void)(0)) , ((PyASCIIObject *)(writer->buffer))->state.kind);
        writer->size = (((void)(0)) , ((void)(0)) , ((PyASCIIObject *)(writer->buffer))->length);
    } else {
        writer->kind = PyUnicode_WCHAR_KIND;
        writer->size = 0;
    }
}
extern  __attribute__((visibility("default"))) void _PyUnicodeWriter_Init (_PyUnicodeWriter *writer){
    memset(writer, 0, sizeof (*writer));
    writer->min_char = 127;
    writer->kind = PyUnicode_WCHAR_KIND;
}
static inline void _PyUnicodeWriter_InitWithBuffer (_PyUnicodeWriter *writer, PyObject *buffer){
    memset(writer, 0, sizeof (*writer));
    writer->buffer = buffer;
    _PyUnicodeWriter_Update(writer);
    writer->min_length = writer->size;
}
extern  __attribute__((visibility("default"))) int _PyUnicodeWriter_PrepareInternal (_PyUnicodeWriter *writer, Py_ssize_t length, Py_UCS4 maxchar){
    Py_ssize_t newlen;
    PyObject *newbuffer;
    if (length > ((Py_ssize_t)(((size_t)-1) >> 1)) - writer->pos) {
        ;
        return -1;
    }
    newlen = writer->pos + length;
    maxchar = (((maxchar) > (writer->min_char)) ? (maxchar) : (writer->min_char));
    if (writer->buffer == ((void *)0)) {
        ;
        if (writer->overallocate && newlen <= (((Py_ssize_t)(((size_t)-1) >> 1)) - newlen / 4)) {
            newlen += newlen / 4;
        }
        if (newlen < writer->min_length)
            newlen = writer->min_length;
        writer->buffer = PyUnicode_New(newlen, maxchar);
        if (writer->buffer == ((void *)0))
            return -1;
    } else if (newlen > writer->size) {
        if (writer->overallocate && newlen <= (((Py_ssize_t)(((size_t)-1) >> 1)) - newlen / 4)) {
            newlen += newlen / 4;
        }
        if (newlen < writer->min_length)
            newlen = writer->min_length;
        if (maxchar > writer->maxchar || writer->readonly) {
            maxchar = (((maxchar) > (writer->maxchar)) ? (maxchar) : (writer->maxchar));
            newbuffer = PyUnicode_New(newlen, maxchar);
            if (newbuffer == ((void *)0))
                return -1;
            _PyUnicode_FastCopyCharacters(newbuffer, 0, writer->buffer, 0, writer->pos);
            _Py_DECREF(((PyObject *)(writer->buffer)));
            writer->readonly = 0;
        } else {
            newbuffer = resize_compact(writer->buffer, newlen);
            if (newbuffer == ((void *)0))
                return -1;
        }
        writer->buffer = newbuffer;
    } else if (maxchar > writer->maxchar) {
        ;
        newbuffer = PyUnicode_New(writer->size, maxchar);
        if (newbuffer == ((void *)0))
            return -1;
        _PyUnicode_FastCopyCharacters(newbuffer, 0, writer->buffer, 0, writer->pos);
        do {
            PyObject *_py_tmp = ((PyObject *)(writer->buffer));
            (writer->buffer) = (newbuffer);
            _Py_DECREF(((PyObject *)(_py_tmp)));
        } while (0);
    }
    _PyUnicodeWriter_Update(writer);
    return 0;
}
extern  __attribute__((visibility("default"))) int _PyUnicodeWriter_PrepareKindInternal (_PyUnicodeWriter *writer, enum PyUnicode_Kind kind){
    Py_UCS4 maxchar;
    switch (kind) {
      case PyUnicode_1BYTE_KIND:
        maxchar = 255;
        break;
      case PyUnicode_2BYTE_KIND:
        maxchar = 65535;
        break;
      case PyUnicode_4BYTE_KIND:
        maxchar = 1114111;
        break;
    }
    return _PyUnicodeWriter_PrepareInternal(writer, 0, maxchar);
}
static inline int _PyUnicodeWriter_WriteCharInline (_PyUnicodeWriter *writer, Py_UCS4 ch){
    ;
    if ((((ch) <= (writer)->maxchar && (1) <= (writer)->size - (writer)->pos) ? 0 : (((1) == 0) ? 0 : _PyUnicodeWriter_PrepareInternal((writer), (1), (ch)))) < 0)
        return -1;
    do {
        switch ((writer->kind)) {
          case PyUnicode_1BYTE_KIND:
            {
                ((Py_UCS1 *)(writer->data))[(writer->pos)] = (Py_UCS1)(ch);
                break;
            }
          case PyUnicode_2BYTE_KIND:
            {
                ((Py_UCS2 *)(writer->data))[(writer->pos)] = (Py_UCS2)(ch);
                break;
            }
          default:
            {
                ((void)(0));
                ((Py_UCS4 *)(writer->data))[(writer->pos)] = (Py_UCS4)(ch);
            }
        }
    } while (0);
    writer->pos++;
    return 0;
}
extern  __attribute__((visibility("default"))) int _PyUnicodeWriter_WriteStr (_PyUnicodeWriter *writer, PyObject *str){
    Py_UCS4 maxchar;
    Py_ssize_t len;
    if ((((void)(0)) , ((((PyASCIIObject *)str)->state.ready) ? 0 : _PyUnicode_Ready(str))) == -1)
        return -1;
    len = (((void)(0)) , ((void)(0)) , ((PyASCIIObject *)(str))->length);
    if (len == 0)
        return 0;
    maxchar = (((void)(0)) , ((((void)(0)) , ((void)(0)) , ((PyASCIIObject *)str)->state.ascii) ? (127) : ((((void)(0)) , ((void)(0)) , ((PyASCIIObject *)(str))->state.kind) == PyUnicode_1BYTE_KIND ? (255U) : ((((void)(0)) , ((void)(0)) , ((PyASCIIObject *)(str))->state.kind) == PyUnicode_2BYTE_KIND ? (65535U) : (1114111U)))));
    if (maxchar > writer->maxchar || len > writer->size - writer->pos) {
        if (writer->buffer == ((void *)0) && !writer->overallocate) {
            ;
            writer->readonly = 1;
            _Py_INCREF(((PyObject *)(str)));
            writer->buffer = str;
            _PyUnicodeWriter_Update(writer);
            return 0;
        }
        if (_PyUnicodeWriter_PrepareInternal(writer, len, maxchar) == -1)
            return -1;
    }
    _PyUnicode_FastCopyCharacters(writer->buffer, writer->pos, str, 0, len);
    return 0;
}
extern  __attribute__((visibility("default"))) PyObject * _PyUnicodeWriter_Finish (_PyUnicodeWriter *writer){
    PyObject *str;
    if (writer->pos == 0) {
        do {
            PyObject *_py_tmp = ((PyObject *)(writer->buffer));
            if (_py_tmp != ((void *)0)) {
                (writer->buffer) = ((void *)0);
                _Py_DECREF(((PyObject *)(_py_tmp)));
            }
        } while (0);
        do {
            return unicode_new_empty();
        } while (0);
    }
    str = writer->buffer;
    writer->buffer = ((void *)0);
    if (writer->readonly) {
        ;
        return str;
    }
    if ((((void)(0)) , ((void)(0)) , ((PyASCIIObject *)(str))->length) != writer->pos) {
        PyObject *str2;
        str2 = resize_compact(str, writer->pos);
        if (str2 == ((void *)0)) {
            _Py_DECREF(((PyObject *)(str)));
            return ((void *)0);
        }
        str = str2;
    }
    ;
    return unicode_result_ready(str);
}
extern  __attribute__((visibility("default"))) void _PyUnicodeWriter_Dealloc (_PyUnicodeWriter *writer){
    do {
        PyObject *_py_tmp = ((PyObject *)(writer->buffer));
        if (_py_tmp != ((void *)0)) {
            (writer->buffer) = ((void *)0);
            _Py_DECREF(((PyObject *)(_py_tmp)));
        }
    } while (0);
}
