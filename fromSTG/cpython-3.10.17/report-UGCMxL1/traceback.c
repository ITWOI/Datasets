extern void _Py_DumpASCII (int fd, PyObject *text){
    PyASCIIObject *ascii = (PyASCIIObject *)text;
    Py_ssize_t i, size;
    int truncated;
    int kind;
    void *data = ((void *)0);
    wchar_t *wstr = ((void *)0);
    Py_UCS4 ch;
    if (!PyType_HasFeature((((PyObject *)(text))->ob_type), (1UL << 28)))
        return;
    size = ascii->length;
    kind = ascii->state.kind;
    if (kind == PyUnicode_WCHAR_KIND) {
        wstr = ((PyASCIIObject *)text)->wstr;
        if (wstr == ((void *)0))
            return;
        size = ((PyCompactUnicodeObject *)text)->wstr_length;
    } else if (ascii->state.compact) {
        if (ascii->state.ascii) {
            data = ((PyASCIIObject *)text) + 1;
        } else
            data = ((PyCompactUnicodeObject *)text) + 1;
    } else {
        data = ((PyUnicodeObject *)text)->data.any;
        if (data == ((void *)0))
            return;
    }
    if (500 < size) {
        size = 500;
        truncated = 1;
    } else {
        truncated = 0;
    }
    if (ascii->state.ascii) {
        ;
        char *str = data;
        int need_escape = 0;
        for (i = 0; i < size; i++) {
            ch = str[i];
            if (!(' ' <= ch && ch <= 126)) {
                need_escape = 1;
                break;
            }
        }
        if (!need_escape) {
            ;
            goto done;
        }
    }
    for (i = 0; i < size; i++) {
        if (kind != PyUnicode_WCHAR_KIND) {
            ch = ((Py_UCS4)((kind) == PyUnicode_1BYTE_KIND ? ((const Py_UCS1 *)(data))[(i)] : ((kind) == PyUnicode_2BYTE_KIND ? ((const Py_UCS2 *)(data))[(i)] : ((const Py_UCS4 *)(data))[(i)])));
        } else
            ch = wstr[i];
        if (' ' <= ch && ch <= 126) {
            char c = (char)ch;
            ;
        } else {
            ;
        }
    }
  done:
    ;
}


static void dump_frame (int fd, PyFrameObject *frame){
    PyCodeObject *code = PyFrame_GetCode(frame);
    ;
    if (code->co_filename != ((void *)0) && PyType_HasFeature((((PyObject *)(code->co_filename))->ob_type), (1UL << 28))) {
        ;
        _Py_DumpASCII(fd, code->co_filename);
        ;
    } else {
        ;
    }
    int lineno = PyFrame_GetLineNumber(frame);
    ;
    ;
    if (code->co_name != ((void *)0) && PyType_HasFeature((((PyObject *)(code->co_name))->ob_type), (1UL << 28))) {
        _Py_DumpASCII(fd, code->co_name);
    } else {
        ;
    }
    ;
    _Py_DECREF(((PyObject *)(code)));
}


static void dump_traceback (int fd, PyThreadState *tstate, int write_header){
    PyFrameObject *frame;
    unsigned int depth;
    frame = tstate->frame;
    if (frame == ((void *)0)) {
        ;
        return;
    }
    depth = 0;
    while (1)
        {
            if (100 <= depth) {
                ;
                break;
            }
            if (!_Py_IS_TYPE(((const PyObject *)(frame)), &PyFrame_Type)) {
                break;
            }
            dump_frame(fd, frame);
            PyFrameObject *back = frame->f_back;
            if (back == ((void *)0)) {
                break;
            }
            frame = back;
            depth++;
        }
}


extern const char * _Py_DumpTracebackThreads (int fd, PyInterpreterState *interp, PyThreadState *current_tstate){
    PyThreadState *tstate;
    unsigned int nthreads;
    if (current_tstate == ((void *)0)) {
        current_tstate = PyGILState_GetThisThreadState();
    }
    if (interp == ((void *)0)) {
        if (current_tstate == ((void *)0)) {
            interp = _PyGILState_GetInterpreterStateUnsafe();
            if (interp == ((void *)0)) {
                return "unable to get the interpreter state";
            }
        } else {
            interp = current_tstate->interp;
        }
    }
    ;
    tstate = PyInterpreterState_ThreadHead(interp);
    if (tstate == ((void *)0))
        return "unable to get the thread head state";
    tstate = PyInterpreterState_ThreadHead(interp);
    nthreads = 0;
    do {
        ;
        if (nthreads >= 100) {
            ;
            break;
        }
        ;
        dump_traceback(fd, tstate, 0);
        tstate = PyThreadState_Next(tstate);
        nthreads++;
    } while (tstate != ((void *)0));
    return ((void *)0);
}


