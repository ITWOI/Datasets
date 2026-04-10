static void _CallPythonObject (void *mem, ffi_type *restype, SETFUNC setfunc, PyObject *callable, PyObject *converters, int flags, void **pArgs){
    Py_ssize_t i;
    PyObject *result;
    PyObject *arglist = ((void *)0);
    Py_ssize_t nArgs;
    PyObject *error_object = ((void *)0);
    int *space;
    PyGILState_STATE state = PyGILState_Ensure();
    nArgs = PySequence_Size(converters);
    if (nArgs < 0) {
        ;
        goto Done;
    }
    arglist = PyTuple_New(nArgs);
    if (!arglist) {
        ;
        goto Done;
    }
    for (i = 0; i < nArgs; ++i) {
        PyObject *cnv = PySequence_GetItem(converters, i);
        StgDictObject *dict;
        if (cnv) {
            dict = PyType_stgdict(cnv);
        } else {
            ;
        }
        if (dict && dict->getfunc && !_ctypes_simple_instance(cnv)) {
            PyObject *v = dict->getfunc(*pArgs, dict->size);
            if (!v) {
                ;
                _Py_DECREF(((PyObject *)(cnv)));
                goto Done;
            }
            ((void)((((void)(0)) , (PyTupleObject *)(arglist))->ob_item[i] = v));
        } else if (dict) {
            CDataObject *obj = (CDataObject *)_PyObject_CallNoArg(cnv);
            if (!obj) {
                ;
                _Py_DECREF(((PyObject *)(cnv)));
                goto Done;
            }
            if (!_PyObject_TypeCheck(((PyObject *)(obj)), &PyCData_Type)) {
                _Py_DECREF(((PyObject *)(obj)));
                _Py_DECREF(((PyObject *)(cnv)));
                ;
                goto Done;
            }
            ;
            ((void)((((void)(0)) , (PyTupleObject *)(arglist))->ob_item[i] = (PyObject *)obj));
        } else {
            ;
            ;
            _Py_DECREF(((PyObject *)(cnv)));
            goto Done;
        }
        _Py_DECREF(((PyObject *)(cnv)));
        pArgs++;
    }
    if (flags & (8 | 16)) {
        error_object = _ctypes_get_errobj(&space);
        if (error_object == ((void *)0))
            goto Done;
        if (flags & 8) {
            int temp = space[0];
            space[0] = (*__errno_location());
            (*__errno_location()) = temp;
        }
    }
    result = PyObject_CallObject(callable, arglist);
    if (result == ((void *)0)) {
        ;
    }
    if (flags & 8) {
        int temp = space[0];
        space[0] = (*__errno_location());
        (*__errno_location()) = temp;
    }
    _Py_XDECREF(((PyObject *)(error_object)));
    if (restype != &ffi_type_void && result) {
        ;
        PyObject *keep = setfunc(mem, result, 0);
        if (keep == ((void *)0)) {
            ;
        } else if (setfunc != _ctypes_get_fielddesc("O")->setfunc) {
            if (keep == (&_Py_NoneStruct)) {
                _Py_DECREF(((PyObject *)(keep)));
            } else {
                ;
            }
        }
    }
    _Py_XDECREF(((PyObject *)(result)));
  Done:
    _Py_XDECREF(((PyObject *)(arglist)));
    ;
}


static void closure_fcn (ffi_cif *cif, void *resp, void **args, void *userdata){
    CThunkObject *p = (CThunkObject *)userdata;
    _CallPythonObject(resp, p->ffi_restype, p->setfunc, p->callable, p->converters, p->flags, args);
}


