extern  __attribute__((visibility("default"))) void PyObject_CallFinalizer (PyObject *self){
    PyTypeObject *tp = (((PyObject *)(self))->ob_type);
    if (tp->tp_finalize == ((void *)0))
        return;
    if (_PyType_HasFeature((tp), (1UL << 14)) && (((((PyGC_Head *)(self) - 1))->_gc_prev & (1)) != 0))
        return;
    ;
    if (_PyType_HasFeature((tp), (1UL << 14))) {
        ((((PyGC_Head *)(self) - 1))->_gc_prev |= (1));
    }
}


extern  __attribute__((visibility("default"))) int PyObject_CallFinalizerFromDealloc (PyObject *self){
    if (_Py_REFCNT(((const PyObject *)(self))) != 0) {
        _PyObject_AssertFailed((self), ((void *)0), ("PyObject_CallFinalizerFromDealloc called on object with a non-zero refcount"), "Objects/object_InstSlice.c", 171, __func__);
    }
    _Py_SET_REFCNT(((PyObject *)(self)), 1);
    PyObject_CallFinalizer(self);
    ;
    _Py_SET_REFCNT(((PyObject *)(self)), _Py_REFCNT(((const PyObject *)(self))) - 1);
    if (_Py_REFCNT(((const PyObject *)(self))) == 0) {
        return 0;
    }
    Py_ssize_t refcnt = _Py_REFCNT(((const PyObject *)(self)));
    _Py_NewReference(self);
    _Py_SET_REFCNT(((PyObject *)(self)), refcnt);
    ;
    return -1;
}


extern  __attribute__((visibility("default"))) int PyObject_Print (PyObject *op, FILE *fp, int flags){
    int ret = 0;
    if (PyErr_CheckSignals())
        return -1;
    ;
    if (op == ((void *)0)) {
        {
            PyThreadState *_save;
            _save = PyEval_SaveThread();
            fprintf(fp, "<nil>");
            PyEval_RestoreThread(_save);
        }
    } else {
        if (_Py_REFCNT(((const PyObject *)(op))) <= 0) {
            {
                PyThreadState *_save;
                _save = PyEval_SaveThread();
                fprintf(fp, "<refcnt %ld at %p>", (long)_Py_REFCNT(((const PyObject *)(op))), (void *)op);
                PyEval_RestoreThread(_save);
            }
        } else {
            PyObject *s;
            if (flags & 1) {
                s = PyObject_Str(op);
            } else
                s = PyObject_Repr(op);
            if (s == ((void *)0)) {
                ;
            } else if (PyType_HasFeature((((PyObject *)(s))->ob_type), (1UL << 27))) {
                ;
            } else if (PyType_HasFeature((((PyObject *)(s))->ob_type), (1UL << 28))) {
                PyObject *t;
                t = PyUnicode_AsEncodedString(s, "utf-8", "backslashreplace");
                if (t == ((void *)0)) {
                    ;
                } else {
                    ;
                    _Py_DECREF(((PyObject *)(t)));
                }
            } else {
                ;
            }
            _Py_XDECREF(((PyObject *)(s)));
        }
    }
    return ret;
}


extern  __attribute__((visibility("default"))) int _PyObject_IsFreed (PyObject *op){
    if (_PyMem_IsPtrFreed(op) || _PyMem_IsPtrFreed((((PyObject *)(op))->ob_type))) {
        return 1;
    }
    return 0;
}


extern  __attribute__((visibility("default"))) void _PyObject_Dump (PyObject *op){
    if (_PyObject_IsFreed(op)) {
        ;
        ;
        return;
    }
    fprintf(stderr, "object address  : %p\n", (void *)op);
    fprintf(stderr, "object refcount : %ld\n", (long)_Py_REFCNT(((const PyObject *)(op))));
    ;
    PyTypeObject *type = (((PyObject *)(op))->ob_type);
    ;
    fprintf(stderr, "object type name: %s\n", type == ((void *)0) ? "NULL" : type->tp_name);
    ;
    ;
    PyGILState_STATE gil = PyGILState_Ensure();
    PyObject *error_type, *error_value, *error_traceback;
    ;
    (void)PyObject_Print(op, stderr, 0);
    ;
    ;
    ;
    ;
    ;
}


extern  __attribute__((visibility("default"))) PyObject * PyObject_Repr (PyObject *v){
    PyObject *res;
    if (PyErr_CheckSignals())
        return ((void *)0);
    if (v == ((void *)0))
        return PyUnicode_FromString("<NULL>");
    if ((((PyObject *)(v))->ob_type)->tp_repr == ((void *)0))
        return PyUnicode_FromFormat("<%s object at %p>", (((PyObject *)(v))->ob_type)->tp_name, v);
    PyThreadState *tstate = _PyThreadState_GET();
    if (_Py_EnterRecursiveCall(tstate, " while getting the repr of an object")) {
        return ((void *)0);
    }
    res = (*(((PyObject *)(v))->ob_type)->tp_repr)(v);
    _Py_LeaveRecursiveCall(tstate);
    if (res == ((void *)0)) {
        return ((void *)0);
    }
    if (!PyType_HasFeature((((PyObject *)(res))->ob_type), (1UL << 28))) {
        ;
        _Py_DECREF(((PyObject *)(res)));
        return ((void *)0);
    }
    if ((((void)(0)) , ((((PyASCIIObject *)res)->state.ready) ? 0 : _PyUnicode_Ready(((PyObject *)(res))))) < 0) {
        return ((void *)0);
    }
    return res;
}


extern  __attribute__((visibility("default"))) PyObject * PyObject_Str (PyObject *v){
    PyObject *res;
    if (PyErr_CheckSignals())
        return ((void *)0);
    if (v == ((void *)0))
        return PyUnicode_FromString("<NULL>");
    if (_Py_IS_TYPE(((const PyObject *)(v)), &PyUnicode_Type)) {
        if ((((void)(0)) , ((((PyASCIIObject *)v)->state.ready) ? 0 : _PyUnicode_Ready(((PyObject *)(v))))) < 0)
            return ((void *)0);
        _Py_INCREF(((PyObject *)(v)));
        return v;
    }
    if ((((PyObject *)(v))->ob_type)->tp_str == ((void *)0))
        return PyObject_Repr(v);
    PyThreadState *tstate = _PyThreadState_GET();
    if (_Py_EnterRecursiveCall(tstate, " while getting the str of an object")) {
        return ((void *)0);
    }
    res = (*(((PyObject *)(v))->ob_type)->tp_str)(v);
    _Py_LeaveRecursiveCall(tstate);
    if (res == ((void *)0)) {
        return ((void *)0);
    }
    if (!PyType_HasFeature((((PyObject *)(res))->ob_type), (1UL << 28))) {
        ;
        _Py_DECREF(((PyObject *)(res)));
        return ((void *)0);
    }
    if ((((void)(0)) , ((((PyASCIIObject *)res)->state.ready) ? 0 : _PyUnicode_Ready(((PyObject *)(res))))) < 0) {
        return ((void *)0);
    }
    ;
    return res;
}


extern  __attribute__((visibility("default"))) void _Py_NewReference (PyObject *op){
    _Py_SET_REFCNT(((PyObject *)(op)), 1);
}


extern  __attribute__((visibility("default"))) void _PyObject_AssertFailed (PyObject *obj, const char *expr, const char *msg, const char *file, int line, const char *function){
    ;
    ;
    ;
    ;
    ;
    if (_PyObject_IsFreed(obj)) {
        ;
        ;
    } else {
        void *ptr;
        PyTypeObject *type = (((PyObject *)(obj))->ob_type);
        if (_PyType_HasFeature((type), (1UL << 14))) {
            ;
        } else {
            ;
        }
        ;
        _PyObject_Dump(obj);
        ;
        ;
    }
    ;
}


