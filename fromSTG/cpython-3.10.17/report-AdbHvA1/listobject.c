static int list_resize (PyListObject *self, Py_ssize_t newsize){
    PyObject **items;
    size_t new_allocated, num_allocated_bytes;
    Py_ssize_t allocated = self->allocated;
    if (allocated >= newsize && newsize >= (allocated >> 1)) {
        ;
        _Py_SET_SIZE(((PyVarObject *)(self)), newsize);
        return 0;
    }
    new_allocated = ((size_t)newsize + (newsize >> 3) + 6) & ~(size_t)3;
    if (newsize - (((PyVarObject *)(self))->ob_size) > (Py_ssize_t)(new_allocated - newsize))
        new_allocated = ((size_t)newsize + 3) & ~(size_t)3;
    if (newsize == 0)
        new_allocated = 0;
    if (new_allocated <= (size_t)((Py_ssize_t)(((size_t)-1) >> 1)) / sizeof(PyObject *)) {
        num_allocated_bytes = new_allocated * sizeof(PyObject *);
        items = (PyObject **)PyMem_Realloc(self->ob_item, num_allocated_bytes);
    } else {
        items = ((void *)0);
    }
    if (items == ((void *)0)) {
        ;
        return -1;
    }
    self->ob_item = items;
    _Py_SET_SIZE(((PyVarObject *)(self)), newsize);
    self->allocated = new_allocated;
    return 0;
}


static int list_preallocate_exact (PyListObject *self, Py_ssize_t size){
    ;
    ;
    size = (size + 1) & ~(size_t)1;
    PyObject **items = (((size_t)(size) > ((Py_ssize_t)(((size_t)-1) >> 1)) / sizeof(PyObject *)) ? ((void *)0) : ((PyObject **)PyMem_Malloc((size) * sizeof(PyObject *))));
    if (items == ((void *)0)) {
        ;
        return -1;
    }
    self->ob_item = items;
    self->allocated = size;
    return 0;
}


static int app1 (PyListObject *self, PyObject *v){
    Py_ssize_t n = (((PyVarObject *)((((void)(0)) , (PyListObject *)(self))))->ob_size);
    ;
    ;
    if (list_resize(self, n + 1) < 0)
        return -1;
    _Py_INCREF(((PyObject *)(v)));
    ((void)((((void)(0)) , (PyListObject *)(self))->ob_item[n] = (v)));
    return 0;
}


static int _list_clear (PyListObject *a){
    Py_ssize_t i;
    PyObject **item = a->ob_item;
    if (item != ((void *)0)) {
        i = (((PyVarObject *)(a))->ob_size);
        _Py_SET_SIZE(((PyVarObject *)(a)), 0);
        a->ob_item = ((void *)0);
        a->allocated = 0;
        while (--i >= 0)
            {
                _Py_XDECREF(((PyObject *)(item[i])));
            }
        ;
    }
    return 0;
}


static PyObject * list_extend (PyListObject *self, PyObject *iterable){
    PyObject *it;
    Py_ssize_t m;
    Py_ssize_t n;
    Py_ssize_t i;
    PyObject *(*iternext)(PyObject *);
    if (_Py_IS_TYPE(((const PyObject *)(iterable)), &PyList_Type) || _Py_IS_TYPE(((const PyObject *)(iterable)), &PyTuple_Type) || (PyObject *)self == iterable) {
        PyObject **src, **dest;
        iterable = PySequence_Fast(iterable, "argument must be iterable");
        if (!iterable)
            return ((void *)0);
        n = (PyType_HasFeature((((PyObject *)(iterable))->ob_type), (1UL << 25)) ? (((PyVarObject *)((((void)(0)) , (PyListObject *)(iterable))))->ob_size) : (((PyVarObject *)((((void)(0)) , (PyTupleObject *)(iterable))))->ob_size));
        if (n == 0) {
            _Py_DECREF(((PyObject *)(iterable)));
            return _Py_NewRef(((PyObject *)((&_Py_NoneStruct))));
        }
        m = (((PyVarObject *)(self))->ob_size);
        ;
        if (self->ob_item == ((void *)0)) {
            if (list_preallocate_exact(self, n) < 0) {
                return ((void *)0);
            }
            _Py_SET_SIZE(((PyVarObject *)(self)), n);
        } else if (list_resize(self, m + n) < 0) {
            _Py_DECREF(((PyObject *)(iterable)));
            return ((void *)0);
        }
        src = (PyType_HasFeature((((PyObject *)(iterable))->ob_type), (1UL << 25)) ? ((PyListObject *)(iterable))->ob_item : ((PyTupleObject *)(iterable))->ob_item);
        dest = self->ob_item + m;
        for (i = 0; i < n; i++) {
            PyObject *o = src[i];
            _Py_INCREF(((PyObject *)(o)));
            dest[i] = o;
        }
        _Py_DECREF(((PyObject *)(iterable)));
        return _Py_NewRef(((PyObject *)((&_Py_NoneStruct))));
    }
    it = PyObject_GetIter(iterable);
    if (it == ((void *)0))
        return ((void *)0);
    iternext = *(((PyObject *)(it))->ob_type)->tp_iternext;
    n = PyObject_LengthHint(iterable, 8);
    if (n < 0) {
        _Py_DECREF(((PyObject *)(it)));
        return ((void *)0);
    }
    m = (((PyVarObject *)(self))->ob_size);
    if (m > ((Py_ssize_t)(((size_t)-1) >> 1)) - n) {
    } else if (self->ob_item == ((void *)0)) {
        if (n && list_preallocate_exact(self, n) < 0)
            goto error;
    } else {
        if (list_resize(self, m + n) < 0)
            goto error;
        _Py_SET_SIZE(((PyVarObject *)(self)), m);
    }
    for (;;) {
        PyObject *item = iternext(it);
        if (item == ((void *)0)) {
            if (PyErr_Occurred()) {
                if (PyErr_ExceptionMatches(PyExc_StopIteration)) {
                    ;
                } else {
                    ;
                }
                ;
            }
            break;
        }
        if ((((PyVarObject *)(self))->ob_size) < self->allocated) {
            ((void)((((void)(0)) , (PyListObject *)(self))->ob_item[(((PyVarObject *)(self))->ob_size)] = (item)));
            _Py_SET_SIZE(((PyVarObject *)(self)), (((PyVarObject *)(self))->ob_size) + 1);
        } else {
            int status = app1(self, item);
            _Py_DECREF(((PyObject *)(item)));
            if (status < 0)
                goto error;
        }
    }
    if ((((PyVarObject *)(self))->ob_size) < self->allocated) {
        if (list_resize(self, (((PyVarObject *)(self))->ob_size)) < 0)
            goto error;
    }
    _Py_DECREF(((PyObject *)(it)));
    return _Py_NewRef(((PyObject *)((&_Py_NoneStruct))));
  error:
    _Py_DECREF(((PyObject *)(it)));
    return ((void *)0);
}


static int list___init___impl (PyListObject *self, PyObject *iterable){
    ;
    ;
    ;
    if (self->ob_item != ((void *)0)) {
        (void)_list_clear(self);
    }
    if (iterable != ((void *)0)) {
        PyObject *rv = list_extend(self, iterable);
        if (rv == ((void *)0))
            return -1;
        _Py_DECREF(((PyObject *)(rv)));
    }
    return 0;
}


static PyObject * list_vectorcall (PyObject *type, PyObject *const *args, size_t nargsf, PyObject *kwnames){
    if (!((kwnames) == ((void *)0) || _PyArg_NoKwnames(("list"), (kwnames)))) {
        return ((void *)0);
    }
    Py_ssize_t nargs = PyVectorcall_NARGS(nargsf);
    if (!(((0) <= (nargs) && (nargs) <= (1)) || _PyArg_CheckPositional(("list"), (nargs), (0), (1)))) {
        return ((void *)0);
    }
    ;
    PyObject *list = PyType_GenericAlloc((PyTypeObject *)type, 0);
    if (list == ((void *)0)) {
        return ((void *)0);
    }
    if (nargs) {
        if (list___init___impl((PyListObject *)list, args[0])) {
            _Py_DECREF(((PyObject *)(list)));
            return ((void *)0);
        }
    }
    return list;
}


