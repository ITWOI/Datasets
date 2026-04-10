static int addcleanup (void *ptr, freelist_t *freelist, destr_t destructor){
    int index;
    index = freelist->first_available;
    freelist->first_available += 1;
    freelist->entries[index].item = ptr;
    freelist->entries[index].destructor = destructor;
    return 0;
}


static const char * converterr (const char *expected, PyObject *arg, char *msgbuf, size_t bufsize){
    ;
    ;
    if (expected[0] == '(') {
        ;
    } else {
        ;
    }
    return msgbuf;
}


static const char * convertsimple (PyObject *arg, const char **p_format, va_list *p_va, int flags, char *msgbuf, size_t bufsize, freelist_t *freelist){
    const char *format = *p_format;
    char c = *format++;
    const char *sarg;
    switch (c) {
      case 'b':
        {
            char *p = __builtin_va_arg(*p_va, char *);
            long ival = PyLong_AsLong(arg);
            ;
            break;
        }
      case 'B':
        {
            char *p = __builtin_va_arg(*p_va, char *);
            unsigned long ival = PyLong_AsUnsignedLongMask(arg);
            ;
            break;
        }
      case 'h':
        {
            short *p = __builtin_va_arg(*p_va, short *);
            long ival = PyLong_AsLong(arg);
            ;
            break;
        }
      case 'H':
        {
            unsigned short *p = __builtin_va_arg(*p_va, unsigned short *);
            unsigned long ival = PyLong_AsUnsignedLongMask(arg);
            ;
            break;
        }
      case 'i':
        {
            int *p = __builtin_va_arg(*p_va, int *);
            long ival = PyLong_AsLong(arg);
            ;
            break;
        }
      case 'I':
        {
            unsigned int *p = __builtin_va_arg(*p_va, unsigned int *);
            unsigned long ival = PyLong_AsUnsignedLongMask(arg);
            ;
            break;
        }
      case 'n':
        {
            PyObject *iobj;
            Py_ssize_t *p = __builtin_va_arg(*p_va, Py_ssize_t *);
            Py_ssize_t ival = -1;
            iobj = _PyNumber_Index(arg);
            if (iobj != ((void *)0)) {
                ;
                _Py_DECREF(((PyObject *)(iobj)));
            }
            ;
            ;
            break;
        }
      case 'l':
        {
            long *p = __builtin_va_arg(*p_va, long *);
            long ival = PyLong_AsLong(arg);
            ;
            break;
        }
      case 'k':
        {
            unsigned long *p = __builtin_va_arg(*p_va, unsigned long *);
            unsigned long ival;
            if (PyType_HasFeature((((PyObject *)(arg))->ob_type), (1UL << 24))) {
                ;
            } else
                return converterr("int", arg, msgbuf, bufsize);
            ;
            break;
        }
      case 'L':
        {
            long long *p = __builtin_va_arg(*p_va, long long *);
            long long ival = PyLong_AsLongLong(arg);
            ;
            break;
        }
      case 'K':
        {
            unsigned long long *p = __builtin_va_arg(*p_va, unsigned long long *);
            unsigned long long ival;
            if (PyType_HasFeature((((PyObject *)(arg))->ob_type), (1UL << 24))) {
                ;
            } else
                return converterr("int", arg, msgbuf, bufsize);
            ;
            break;
        }
      case 'f':
        {
            float *p = __builtin_va_arg(*p_va, float *);
            double dval = PyFloat_AsDouble(arg);
            ;
            break;
        }
      case 'd':
        {
            double *p = __builtin_va_arg(*p_va, double *);
            double dval = PyFloat_AsDouble(arg);
            ;
            break;
        }
      case 'D':
        {
            Py_complex *p = __builtin_va_arg(*p_va, Py_complex *);
            Py_complex cval;
            ;
            ;
            break;
        }
      case 'c':
        {
            char *p = __builtin_va_arg(*p_va, char *);
            if (PyType_HasFeature((((PyObject *)(arg))->ob_type), (1UL << 27)) && PyBytes_Size(arg) == 1) {
                ;
            } else if (_PyObject_TypeCheck(((PyObject *)(arg)), &PyByteArray_Type) && PyByteArray_Size(arg) == 1) {
                ;
            } else
                return converterr("a byte string of length 1", arg, msgbuf, bufsize);
            break;
        }
      case 'C':
        {
            int *p = __builtin_va_arg(*p_va, int *);
            int kind;
            const void *data;
            if (!PyType_HasFeature((((PyObject *)(arg))->ob_type), (1UL << 28)))
                return converterr("a unicode character", arg, msgbuf, bufsize);
            if ((((void)(0)) , ((((PyASCIIObject *)arg)->state.ready) ? 0 : _PyUnicode_Ready(((PyObject *)(arg))))))
                return msgbuf;
            if ((((void)(0)) , ((void)(0)) , ((PyASCIIObject *)(arg))->length) != 1)
                return converterr("a unicode character", arg, msgbuf, bufsize);
            ;
            ;
            ;
            break;
        }
      case 'p':
        {
            int *p = __builtin_va_arg(*p_va, int *);
            int val = PyObject_IsTrue(arg);
            ;
            break;
        }
      case 'y':
        {
            void **p = (void **)__builtin_va_arg(*p_va, char **);
            const char *buf;
            Py_ssize_t count;
            if (*format == '*') {
                if (getbuffer(arg, (Py_buffer *)p, &buf) < 0)
                    return converterr(buf, arg, msgbuf, bufsize);
                ;
                if (addcleanup(p, freelist, cleanup_buffer)) {
                    return converterr("(cleanup problem)", arg, msgbuf, bufsize);
                }
                break;
            }
            count = convertbuffer(arg, (const void **)p, &buf);
            if (count < 0)
                return converterr(buf, arg, msgbuf, bufsize);
            if (*format == '#') {
                if (!(flags & 2)) {
                    PyErr_SetString(PyExc_SystemError, "PY_SSIZE_T_CLEAN macro must be defined for '#' formats");
                    return msgbuf;
                }
                ;
                ;
                Py_ssize_t *psize = __builtin_va_arg(*p_va, Py_ssize_t *);
                ;
                ;
            } else {
                ;
            }
            break;
        }
      case 's':
      case 'z':
        {
            if (*format == '*') {
                Py_buffer *p = (Py_buffer *)__builtin_va_arg(*p_va, Py_buffer *);
                if (c == 'z' && arg == (&_Py_NoneStruct)) {
                    ;
                } else if (PyType_HasFeature((((PyObject *)(arg))->ob_type), (1UL << 28))) {
                    Py_ssize_t len;
                    sarg = PyUnicode_AsUTF8AndSize(arg, &len);
                    if (sarg == ((void *)0))
                        return converterr("(unicode conversion error)", arg, msgbuf, bufsize);
                    ;
                } else {
                    const char *buf;
                    if (getbuffer(arg, p, &buf) < 0)
                        return converterr(buf, arg, msgbuf, bufsize);
                }
                if (addcleanup(p, freelist, cleanup_buffer)) {
                    return converterr("(cleanup problem)", arg, msgbuf, bufsize);
                }
                ;
            } else if (*format == '#') {
                const void **p = (const void **)__builtin_va_arg(*p_va, const char **);
                if (!(flags & 2)) {
                    PyErr_SetString(PyExc_SystemError, "PY_SSIZE_T_CLEAN macro must be defined for '#' formats");
                    return msgbuf;
                }
                ;
                ;
                Py_ssize_t *psize = __builtin_va_arg(*p_va, Py_ssize_t *);
                if (c == 'z' && arg == (&_Py_NoneStruct)) {
                    ;
                    ;
                } else if (PyType_HasFeature((((PyObject *)(arg))->ob_type), (1UL << 28))) {
                    Py_ssize_t len;
                    sarg = PyUnicode_AsUTF8AndSize(arg, &len);
                    if (sarg == ((void *)0))
                        return converterr("(unicode conversion error)", arg, msgbuf, bufsize);
                    ;
                    ;
                } else {
                    const char *buf;
                    Py_ssize_t count = convertbuffer(arg, p, &buf);
                    if (count < 0)
                        return converterr(buf, arg, msgbuf, bufsize);
                    ;
                }
                ;
            } else {
                const char **p = __builtin_va_arg(*p_va, const char **);
                Py_ssize_t len;
                sarg = ((void *)0);
                if (c == 'z' && arg == (&_Py_NoneStruct)) {
                    ;
                } else if (PyType_HasFeature((((PyObject *)(arg))->ob_type), (1UL << 28))) {
                    sarg = PyUnicode_AsUTF8AndSize(arg, &len);
                    if (sarg == ((void *)0))
                        return converterr("(unicode conversion error)", arg, msgbuf, bufsize);
                    ;
                } else
                    return converterr(c == 'z' ? "str or None" : "str", arg, msgbuf, bufsize);
            }
            break;
        }
      case 'u':
      case 'Z':
        {
            if (PyErr_WarnFormat(PyExc_DeprecationWarning, 1, "getargs: The '%c' format is deprecated. Use 'U' instead.", c)) {
                return msgbuf;
            }
            Py_UNICODE **p = __builtin_va_arg(*p_va, Py_UNICODE **);
            if (*format == '#') {
                if (!(flags & 2)) {
                    PyErr_SetString(PyExc_SystemError, "PY_SSIZE_T_CLEAN macro must be defined for '#' formats");
                    return msgbuf;
                }
                ;
                ;
                Py_ssize_t *psize = __builtin_va_arg(*p_va, Py_ssize_t *);
                if (c == 'Z' && arg == (&_Py_NoneStruct)) {
                    ;
                    ;
                } else if (PyType_HasFeature((((PyObject *)(arg))->ob_type), (1UL << 28))) {
                    Py_ssize_t len;
                    ;
                    ;
                    ;
                } else
                    return converterr(c == 'Z' ? "str or None" : "str", arg, msgbuf, bufsize);
                ;
            } else {
                if (c == 'Z' && arg == (&_Py_NoneStruct)) {
                    ;
                } else if (PyType_HasFeature((((PyObject *)(arg))->ob_type), (1UL << 28))) {
                    Py_ssize_t len;
                    ;
                    ;
                } else
                    return converterr(c == 'Z' ? "str or None" : "str", arg, msgbuf, bufsize);
            }
            break;
        }
      case 'e':
        {
            char **buffer;
            const char *encoding;
            PyObject *s;
            int recode_strings;
            Py_ssize_t size;
            const char *ptr;
            encoding = (const char *)__builtin_va_arg(*p_va, const char *);
            if (encoding == ((void *)0))
                encoding = PyUnicode_GetDefaultEncoding();
            if (*format == 's') {
                recode_strings = 1;
            } else if (*format == 't') {
                recode_strings = 0;
            } else
                return converterr("(unknown parser marker combination)", arg, msgbuf, bufsize);
            buffer = (char **)__builtin_va_arg(*p_va, char **);
            format++;
            if (buffer == ((void *)0))
                return converterr("(buffer is NULL)", arg, msgbuf, bufsize);
            if (!recode_strings && (PyType_HasFeature((((PyObject *)(arg))->ob_type), (1UL << 27)) || _PyObject_TypeCheck(((PyObject *)(arg)), &PyByteArray_Type))) {
                s = arg;
                _Py_INCREF(((PyObject *)(s)));
                if (PyType_HasFeature((((PyObject *)(arg))->ob_type), (1UL << 27))) {
                    size = (((void)(0)) , (((PyVarObject *)(s))->ob_size));
                    ptr = (((void)(0)) , (((PyBytesObject *)(s))->ob_sval));
                } else {
                    size = (((void)(0)) , (((PyVarObject *)(s))->ob_size));
                    ptr = (((void)(0)) , (((PyVarObject *)(s))->ob_size) ? ((PyByteArrayObject *)(s))->ob_start : _PyByteArray_empty_string);
                }
            } else if (PyType_HasFeature((((PyObject *)(arg))->ob_type), (1UL << 28))) {
                s = PyUnicode_AsEncodedString(arg, encoding, ((void *)0));
                if (s == ((void *)0))
                    return converterr("(encoding failed)", arg, msgbuf, bufsize);
                ;
                size = (((void)(0)) , (((PyVarObject *)(s))->ob_size));
                ptr = (((void)(0)) , (((PyBytesObject *)(s))->ob_sval));
                if (ptr == ((void *)0))
                    ptr = "";
            } else {
                return converterr(recode_strings ? "str" : "str, bytes or bytearray", arg, msgbuf, bufsize);
            }
            if (*format == '#') {
                if (!(flags & 2)) {
                    PyErr_SetString(PyExc_SystemError, "PY_SSIZE_T_CLEAN macro must be defined for '#' formats");
                    return msgbuf;
                }
                ;
                ;
                Py_ssize_t *psize = __builtin_va_arg(*p_va, Py_ssize_t *);
                format++;
                if (psize == ((void *)0)) {
                    _Py_DECREF(((PyObject *)(s)));
                    return converterr("(buffer_len is NULL)", arg, msgbuf, bufsize);
                }
                if (*buffer == ((void *)0)) {
                    *buffer = (((size_t)(size + 1) > ((Py_ssize_t)(((size_t)-1) >> 1)) / sizeof(char)) ? ((void *)0) : ((char *)PyMem_Malloc((size + 1) * sizeof(char))));
                    if (*buffer == ((void *)0)) {
                        _Py_DECREF(((PyObject *)(s)));
                        ;
                        return msgbuf;
                    }
                    if (addcleanup(buffer, freelist, cleanup_ptr)) {
                        _Py_DECREF(((PyObject *)(s)));
                        return converterr("(cleanup problem)", arg, msgbuf, bufsize);
                    }
                } else {
                    if (size + 1 > *psize) {
                        _Py_DECREF(((PyObject *)(s)));
                        ;
                        return msgbuf;
                    }
                }
                ;
                *psize = size;
            } else {
                if ((Py_ssize_t)strlen(ptr) != size) {
                    _Py_DECREF(((PyObject *)(s)));
                    return converterr("encoded string without null bytes", arg, msgbuf, bufsize);
                }
                *buffer = (((size_t)(size + 1) > ((Py_ssize_t)(((size_t)-1) >> 1)) / sizeof(char)) ? ((void *)0) : ((char *)PyMem_Malloc((size + 1) * sizeof(char))));
                if (*buffer == ((void *)0)) {
                    _Py_DECREF(((PyObject *)(s)));
                    ;
                    return msgbuf;
                }
                if (addcleanup(buffer, freelist, cleanup_ptr)) {
                    _Py_DECREF(((PyObject *)(s)));
                    return converterr("(cleanup problem)", arg, msgbuf, bufsize);
                }
                ;
            }
            _Py_DECREF(((PyObject *)(s)));
            break;
        }
      case 'S':
        {
            PyObject **p = __builtin_va_arg(*p_va, PyObject **);
            if (PyType_HasFeature((((PyObject *)(arg))->ob_type), (1UL << 27))) {
                ;
            } else
                return converterr("bytes", arg, msgbuf, bufsize);
            break;
        }
      case 'Y':
        {
            PyObject **p = __builtin_va_arg(*p_va, PyObject **);
            if (_PyObject_TypeCheck(((PyObject *)(arg)), &PyByteArray_Type)) {
                ;
            } else
                return converterr("bytearray", arg, msgbuf, bufsize);
            break;
        }
      case 'U':
        {
            PyObject **p = __builtin_va_arg(*p_va, PyObject **);
            if (PyType_HasFeature((((PyObject *)(arg))->ob_type), (1UL << 28))) {
                ;
                ;
            } else
                return converterr("str", arg, msgbuf, bufsize);
            break;
        }
      case 'O':
        {
            PyTypeObject *type;
            PyObject **p;
            if (*format == '!') {
                type = __builtin_va_arg(*p_va, PyTypeObject *);
                p = __builtin_va_arg(*p_va, PyObject **);
                format++;
                if (PyType_IsSubtype((((PyObject *)(arg))->ob_type), type)) {
                    ;
                } else
                    return converterr(type->tp_name, arg, msgbuf, bufsize);
            } else if (*format == '&') {
                typedef int (*converter)(PyObject *, void *);
                converter convert = __builtin_va_arg(*p_va, converter);
                void *addr = __builtin_va_arg(*p_va, void *);
                int res;
                ;
                if (!(res = (*convert)(arg, addr)))
                    return converterr("(unspecified)", arg, msgbuf, bufsize);
                if (res == 131072 && addcleanup(addr, freelist, convert) == -1)
                    return converterr("(cleanup problem)", arg, msgbuf, bufsize);
            } else {
                ;
            }
            break;
        }
      case 'w':
        {
            void **p = __builtin_va_arg(*p_va, void **);
            if (*format != '*')
                return converterr("(invalid use of 'w' format character)", arg, msgbuf, bufsize);
            ;
            if (PyObject_GetBuffer(arg, (Py_buffer *)p, 1) < 0) {
                ;
                return converterr("read-write bytes-like object", arg, msgbuf, bufsize);
            }
            if (!PyBuffer_IsContiguous((Py_buffer *)p, 'C')) {
                ;
                return converterr("contiguous buffer", arg, msgbuf, bufsize);
            }
            if (addcleanup(p, freelist, cleanup_buffer)) {
                return converterr("(cleanup problem)", arg, msgbuf, bufsize);
            }
            break;
        }
      default:
        return converterr("(impossible<bad format char>)", arg, msgbuf, bufsize);
    }
    ;
    return ((void *)0);
}


static Py_ssize_t convertbuffer (PyObject *arg, const void **p, const char **errmsg){
    PyBufferProcs *pb = (((PyObject *)(arg))->ob_type)->tp_as_buffer;
    Py_ssize_t count;
    Py_buffer view;
    *errmsg = ((void *)0);
    *p = ((void *)0);
    if (pb != ((void *)0) && pb->bf_releasebuffer != ((void *)0)) {
        *errmsg = "read-only bytes-like object";
        return -1;
    }
    if (getbuffer(arg, &view, errmsg) < 0)
        return -1;
    count = view.len;
    *p = view.buf;
    ;
    return count;
}


static int getbuffer (PyObject *arg, Py_buffer *view, const char **errmsg){
    if (PyObject_GetBuffer(arg, view, 0) != 0) {
        *errmsg = "bytes-like object";
        return -1;
    }
    if (!PyBuffer_IsContiguous(view, 'C')) {
        ;
        *errmsg = "contiguous buffer";
        return -1;
    }
    return 0;
}


