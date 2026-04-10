static void error_unexpected_keyword_arg (PyObject *kwargs, PyObject *kwnames, PyObject *kwtuple, const char *fname){
    Py_ssize_t j = 0;
    while (1)
        {
            PyObject *keyword;
            if (kwargs != ((void *)0)) {
                if (!PyDict_Next(kwargs, &j, &keyword, ((void *)0)))
                    break;
            } else {
                if (j >= (((PyVarObject *)((((void)(0)) , (PyTupleObject *)(kwnames))))->ob_size))
                    break;
                keyword = ((((void)(0)) , (PyTupleObject *)(kwnames))->ob_item[j]);
                j++;
            }
            if (!PyType_HasFeature((((PyObject *)(keyword))->ob_type), (1UL << 28))) {
                ;
                return;
            }
            int match = PySequence_Contains(kwtuple, keyword);
            if (match <= 0) {
                return;
            }
        }
    ;
}


static int parser_init (struct _PyArg_Parser *parser){
    const char *const *keywords;
    const char *format, *msg;
    int i, len, min, max, nkw;
    PyObject *kwtuple;
    ;
    if (parser->kwtuple != ((void *)0)) {
        return 1;
    }
    keywords = parser->keywords;
    for (i = 0; keywords[i] && !*keywords[i]; i++) {
    }
    parser->pos = i;
    for (; keywords[i]; i++) {
        if (!*keywords[i]) {
            ;
            return 0;
        }
    }
    len = i;
    format = parser->format;
    if (format) {
        parser->fname = strchr(parser->format, ':');
        if (parser->fname) {
            parser->fname++;
            parser->custom_msg = ((void *)0);
        } else {
            parser->custom_msg = strchr(parser->format, ';');
            if (parser->custom_msg)
                parser->custom_msg++;
        }
        min = max = 2147483647;
        for (i = 0; i < len; i++) {
            if (*format == '|') {
                if (min != 2147483647) {
                    ;
                    return 0;
                }
                if (max != 2147483647) {
                    ;
                    return 0;
                }
                min = i;
                format++;
            }
            if (*format == '$') {
                if (max != 2147483647) {
                    ;
                    return 0;
                }
                if (i < parser->pos) {
                    ;
                    return 0;
                }
                max = i;
                format++;
            }
            if ((*format == '\x00' || *format == ';' || *format == ':')) {
                ;
                return 0;
            }
            msg = skipitem(&format, ((void *)0), 0);
            if (msg) {
                ;
                return 0;
            }
        }
        parser->min = (((min) > (len)) ? (len) : (min));
        parser->max = (((max) > (len)) ? (len) : (max));
        if (!(*format == '\x00' || *format == ';' || *format == ':') && (*format != '|') && (*format != '$')) {
            ;
            return 0;
        }
    }
    nkw = len - parser->pos;
    kwtuple = PyTuple_New(nkw);
    if (kwtuple == ((void *)0)) {
        return 0;
    }
    keywords = parser->keywords + parser->pos;
    for (i = 0; i < nkw; i++) {
        PyObject *str = PyUnicode_FromString(keywords[i]);
        if (str == ((void *)0)) {
            _Py_DECREF(((PyObject *)(kwtuple)));
            return 0;
        }
        ;
        ((void)((((void)(0)) , (PyTupleObject *)(kwtuple))->ob_item[i] = str));
    }
    parser->kwtuple = kwtuple;
    ;
    parser->next = static_arg_parsers;
    static_arg_parsers = parser;
    return 1;
}


static PyObject * find_keyword (PyObject *kwnames, PyObject *const *kwstack, PyObject *key){
    Py_ssize_t i, nkwargs;
    nkwargs = (((PyVarObject *)((((void)(0)) , (PyTupleObject *)(kwnames))))->ob_size);
    for (i = 0; i < nkwargs; i++) {
        PyObject *kwname = ((((void)(0)) , (PyTupleObject *)(kwnames))->ob_item[i]);
        if (kwname == key) {
            return kwstack[i];
        }
    }
    for (i = 0; i < nkwargs; i++) {
        PyObject *kwname = ((((void)(0)) , (PyTupleObject *)(kwnames))->ob_item[i]);
        ;
        if (_PyUnicode_EQ(kwname, key)) {
            return kwstack[i];
        }
    }
    return ((void *)0);
}


extern  __attribute__((visibility("default"))) PyObject *const * _PyArg_UnpackKeywords (PyObject *const *args, Py_ssize_t nargs, PyObject *kwargs, PyObject *kwnames, struct _PyArg_Parser *parser, int minpos, int maxpos, int minkw, PyObject **buf){
    PyObject *kwtuple;
    PyObject *keyword;
    int i, posonly, minposonly, maxargs;
    int reqlimit = minkw ? maxpos + minkw : minpos;
    Py_ssize_t nkwargs;
    PyObject *current_arg;
    PyObject *const *kwstack = ((void *)0);
    ;
    ;
    if (parser == ((void *)0)) {
        ;
        return ((void *)0);
    }
    if (kwnames != ((void *)0) && !PyType_HasFeature((((PyObject *)(kwnames))->ob_type), (1UL << 26))) {
        ;
        return ((void *)0);
    }
    if (args == ((void *)0) && nargs == 0) {
        args = buf;
    }
    if (!parser_init(parser)) {
        return ((void *)0);
    }
    kwtuple = parser->kwtuple;
    posonly = parser->pos;
    minposonly = (((posonly) > (minpos)) ? (minpos) : (posonly));
    maxargs = posonly + (int)(((PyVarObject *)((((void)(0)) , (PyTupleObject *)(kwtuple))))->ob_size);
    if (kwargs != ((void *)0)) {
        nkwargs = (((void)(0)) , ((PyDictObject *)kwargs)->ma_used);
    } else if (kwnames != ((void *)0)) {
        nkwargs = (((PyVarObject *)((((void)(0)) , (PyTupleObject *)(kwnames))))->ob_size);
        kwstack = args + nargs;
    } else {
        nkwargs = 0;
    }
    if (nkwargs == 0 && minkw == 0 && minpos <= nargs && nargs <= maxpos) {
        return args;
    }
    if (nargs + nkwargs > maxargs) {
        ;
        return ((void *)0);
    }
    if (nargs > maxpos) {
        return ((void *)0);
    }
    if (nargs < minposonly) {
        ;
        return ((void *)0);
    }
    for (i = 0; i < nargs; i++) {
        buf[i] = args[i];
    }
    for (i = ((((int)nargs) > (posonly)) ? ((int)nargs) : (posonly)); i < maxargs; i++) {
        if (nkwargs) {
            keyword = ((((void)(0)) , (PyTupleObject *)(kwtuple))->ob_item[i - posonly]);
            if (kwargs != ((void *)0)) {
                current_arg = PyDict_GetItemWithError(kwargs, keyword);
                if (!current_arg && PyErr_Occurred()) {
                    return ((void *)0);
                }
            } else {
                current_arg = find_keyword(kwnames, kwstack, keyword);
            }
        } else if (i >= reqlimit) {
            break;
        } else {
            current_arg = ((void *)0);
        }
        buf[i] = current_arg;
        if (current_arg) {
            --nkwargs;
        } else if (i < minpos || (maxpos <= i && i < reqlimit)) {
            ;
            ;
            return ((void *)0);
        }
    }
    if (nkwargs > 0) {
        for (i = posonly; i < nargs; i++) {
            keyword = ((((void)(0)) , (PyTupleObject *)(kwtuple))->ob_item[i - posonly]);
            if (kwargs != ((void *)0)) {
                current_arg = PyDict_GetItemWithError(kwargs, keyword);
                if (!current_arg && PyErr_Occurred()) {
                    return ((void *)0);
                }
            } else {
                current_arg = find_keyword(kwnames, kwstack, keyword);
            }
            if (current_arg) {
                ;
                return ((void *)0);
            }
        }
        error_unexpected_keyword_arg(kwargs, kwnames, kwtuple, parser->fname);
        return ((void *)0);
    }
    return buf;
}


static const char * skipitem (const char **p_format, va_list *p_va, int flags){
    const char *format = *p_format;
    char c = *format++;
    switch (c) {
      case 'e':
        {
            if (!(*format == 's' || *format == 't'))
                goto err;
            format++;
        }
      case 's':
      case 'z':
      case 'y':
      case 'u':
      case 'Z':
      case 'w':
        {
            if (*format == '#') {
                if (p_va != ((void *)0)) {
                    if (!(flags & 2)) {
                        return "PY_SSIZE_T_CLEAN macro must be defined for '#' formats";
                    }
                    ;
                }
                format++;
            } else if ((c == 's' || c == 'z' || c == 'y' || c == 'w') && *format == '*') {
                format++;
            }
            break;
        }
      case 'O':
        {
            if (*format == '!') {
                format++;
            } else if (*format == '&') {
                typedef int (*converter)(PyObject *, void *);
                format++;
            } else {
                ;
            }
            break;
        }
      case '(':
        {
            const char *msg;
            for (;;) {
                if (*format == ')')
                    break;
                if ((*format == '\x00' || *format == ';' || *format == ':'))
                    return "Unmatched left paren in format string";
                msg = skipitem(&format, p_va, flags);
                if (msg)
                    return msg;
            }
            format++;
            break;
        }
      case ')':
        return "Unmatched right paren in format string";
      default:
      err:
        return "impossible<bad format char>";
    }
    *p_format = format;
    return ((void *)0);
}


