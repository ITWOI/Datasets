extern  __attribute__((visibility("default"))) Py_ssize_t _PyWeakref_GetWeakrefCount (PyWeakReference *head){
    Py_ssize_t count = 0;
    while (head != ((void *)0))
        {
            ++count;
            head = head->wr_next;
        }
    return count;
}


static void init_weakref (PyWeakReference *self, PyObject *ob, PyObject *callback){
    self->hash = -1;
    self->wr_object = ob;
    self->wr_prev = ((void *)0);
    self->wr_next = ((void *)0);
    _Py_XINCREF(((PyObject *)(callback)));
    self->wr_callback = callback;
}


static void clear_weakref (PyWeakReference *self){
    PyObject *callback = self->wr_callback;
    if (self->wr_object != (&_Py_NoneStruct)) {
        PyWeakReference **list = ((PyWeakReference **)_PyObject_GET_WEAKREFS_LISTPTR(self->wr_object));
        if (*list == self)
            *list = self->wr_next;
        self->wr_object = (&_Py_NoneStruct);
        if (self->wr_prev != ((void *)0))
            self->wr_prev->wr_next = self->wr_next;
        if (self->wr_next != ((void *)0))
            self->wr_next->wr_prev = self->wr_prev;
        self->wr_prev = ((void *)0);
        self->wr_next = ((void *)0);
    }
    if (callback != ((void *)0)) {
        _Py_DECREF(((PyObject *)(callback)));
        self->wr_callback = ((void *)0);
    }
}


static void weakref_dealloc (PyObject *self){
    PyObject_GC_UnTrack(self);
    clear_weakref((PyWeakReference *)self);
    (((PyObject *)(self))->ob_type)->tp_free(self);
}


static int gc_traverse (PyWeakReference *self, visitproc visit, void *arg){
    do {
        if (self->wr_callback) {
            int vret = visit(((PyObject *)(self->wr_callback)), arg);
            if (vret)
                return vret;
        }
    } while (0);
    return 0;
}


static int gc_clear (PyWeakReference *self){
    clear_weakref(self);
    return 0;
}


static PyObject * weakref_call (PyWeakReference *self, PyObject *args, PyObject *kw){
    static char *kwlist[] = {((void *)0)};
    if (PyArg_ParseTupleAndKeywords(args, kw, ":__call__", kwlist)) {
        PyObject *object = (_Py_REFCNT(((const PyObject *)(((PyWeakReference *)(self))->wr_object))) > 0 ? ((PyWeakReference *)(self))->wr_object : (&_Py_NoneStruct));
        _Py_INCREF(((PyObject *)(object)));
        return (object);
    }
    return ((void *)0);
}


static Py_hash_t weakref_hash (PyWeakReference *self){
    if (self->hash != -1)
        return self->hash;
    PyObject *obj = (_Py_REFCNT(((const PyObject *)(((PyWeakReference *)(self))->wr_object))) > 0 ? ((PyWeakReference *)(self))->wr_object : (&_Py_NoneStruct));
    if (obj == (&_Py_NoneStruct)) {
        PyErr_SetString(PyExc_TypeError, "weak object has gone away");
        return -1;
    }
    _Py_INCREF(((PyObject *)(obj)));
    self->hash = PyObject_Hash(obj);
    _Py_DECREF(((PyObject *)(obj)));
    return self->hash;
}


static PyObject * weakref_repr (PyWeakReference *self){
    PyObject *name, *repr;
    static _Py_Identifier PyId___name__ = {.string = "__name__", .index = -1};
    PyObject *obj = (_Py_REFCNT(((const PyObject *)(((PyWeakReference *)(self))->wr_object))) > 0 ? ((PyWeakReference *)(self))->wr_object : (&_Py_NoneStruct));
    if (obj == (&_Py_NoneStruct)) {
        return PyUnicode_FromFormat("<weakref at %p; dead>", self);
    }
    _Py_INCREF(((PyObject *)(obj)));
    if (_PyObject_LookupAttrId(obj, &PyId___name__, &name) < 0) {
        _Py_DECREF(((PyObject *)(obj)));
        return ((void *)0);
    }
    if (name == ((void *)0) || !PyType_HasFeature((((PyObject *)(name))->ob_type), (1UL << 28))) {
        repr = PyUnicode_FromFormat("<weakref at %p; to '%s' at %p>", self, (((PyObject *)((_Py_REFCNT(((const PyObject *)(((PyWeakReference *)(self))->wr_object))) > 0 ? ((PyWeakReference *)(self))->wr_object : (&_Py_NoneStruct))))->ob_type)->tp_name, obj);
    } else {
        repr = PyUnicode_FromFormat("<weakref at %p; to '%s' at %p (%U)>", self, (((PyObject *)((_Py_REFCNT(((const PyObject *)(((PyWeakReference *)(self))->wr_object))) > 0 ? ((PyWeakReference *)(self))->wr_object : (&_Py_NoneStruct))))->ob_type)->tp_name, obj, name);
    }
    _Py_DECREF(((PyObject *)(obj)));
    _Py_XDECREF(((PyObject *)(name)));
    return repr;
}


static PyObject * weakref_richcompare (PyWeakReference *self, PyWeakReference *other, int op){
    if ((op != 2 && op != 3) || !(_PyObject_TypeCheck(((PyObject *)(self)), &_PyWeakref_RefType) || (_Py_IS_TYPE(((const PyObject *)(self)), &_PyWeakref_ProxyType) || _Py_IS_TYPE(((const PyObject *)(self)), &_PyWeakref_CallableProxyType))) || !(_PyObject_TypeCheck(((PyObject *)(other)), &_PyWeakref_RefType) || (_Py_IS_TYPE(((const PyObject *)(other)), &_PyWeakref_ProxyType) || _Py_IS_TYPE(((const PyObject *)(other)), &_PyWeakref_CallableProxyType)))) {
        return _Py_NewRef(((PyObject *)((&_Py_NotImplementedStruct))));
    }
    if ((_Py_REFCNT(((const PyObject *)(((PyWeakReference *)(self))->wr_object))) > 0 ? ((PyWeakReference *)(self))->wr_object : (&_Py_NoneStruct)) == (&_Py_NoneStruct) || (_Py_REFCNT(((const PyObject *)(((PyWeakReference *)(other))->wr_object))) > 0 ? ((PyWeakReference *)(other))->wr_object : (&_Py_NoneStruct)) == (&_Py_NoneStruct)) {
        int res = (self == other);
        if (op == 3)
            res = !res;
        if (res)
            return _Py_NewRef(((PyObject *)(((PyObject *)&_Py_TrueStruct))));
        else
            return _Py_NewRef(((PyObject *)(((PyObject *)&_Py_FalseStruct))));
    }
    PyObject *obj = (_Py_REFCNT(((const PyObject *)(((PyWeakReference *)(self))->wr_object))) > 0 ? ((PyWeakReference *)(self))->wr_object : (&_Py_NoneStruct));
    PyObject *other_obj = (_Py_REFCNT(((const PyObject *)(((PyWeakReference *)(other))->wr_object))) > 0 ? ((PyWeakReference *)(other))->wr_object : (&_Py_NoneStruct));
    _Py_INCREF(((PyObject *)(obj)));
    _Py_INCREF(((PyObject *)(other_obj)));
    PyObject *res = PyObject_RichCompare(obj, other_obj, op);
    _Py_DECREF(((PyObject *)(obj)));
    _Py_DECREF(((PyObject *)(other_obj)));
    return res;
}


static void get_basic_refs (PyWeakReference *head, PyWeakReference **refp, PyWeakReference **proxyp){
    *refp = ((void *)0);
    *proxyp = ((void *)0);
    if (head != ((void *)0) && head->wr_callback == ((void *)0)) {
        if (_Py_IS_TYPE(((const PyObject *)(head)), &_PyWeakref_RefType)) {
            *refp = head;
            head = head->wr_next;
        }
        if (head != ((void *)0) && head->wr_callback == ((void *)0) && (_Py_IS_TYPE(((const PyObject *)(head)), &_PyWeakref_ProxyType) || _Py_IS_TYPE(((const PyObject *)(head)), &_PyWeakref_CallableProxyType))) {
            *proxyp = head;
        }
    }
}


static void insert_after (PyWeakReference *newref, PyWeakReference *prev){
    newref->wr_prev = prev;
    newref->wr_next = prev->wr_next;
    if (prev->wr_next != ((void *)0))
        prev->wr_next->wr_prev = newref;
    prev->wr_next = newref;
}


static void insert_head (PyWeakReference *newref, PyWeakReference **list){
    PyWeakReference *next = *list;
    newref->wr_prev = ((void *)0);
    newref->wr_next = next;
    if (next != ((void *)0))
        next->wr_prev = newref;
    *list = newref;
}


static int parse_weakref_init_args (const char *funcname, PyObject *args, PyObject *kwargs, PyObject **obp, PyObject **callbackp){
    return PyArg_UnpackTuple(args, funcname, 1, 2, obp, callbackp);
}


static PyObject * weakref___new__ (PyTypeObject *type, PyObject *args, PyObject *kwargs){
    PyWeakReference *self = ((void *)0);
    PyObject *ob, *callback = ((void *)0);
    if (parse_weakref_init_args("__new__", args, kwargs, &ob, &callback)) {
        PyWeakReference *ref, *proxy;
        PyWeakReference **list;
        if (!(((((PyObject *)(ob))->ob_type))->tp_weaklistoffset > 0)) {
            PyErr_Format(PyExc_TypeError, "cannot create weak reference to '%s' object", (((PyObject *)(ob))->ob_type)->tp_name);
            return ((void *)0);
        }
        if (callback == (&_Py_NoneStruct))
            callback = ((void *)0);
        list = ((PyWeakReference **)_PyObject_GET_WEAKREFS_LISTPTR(ob));
        get_basic_refs(*list, &ref, &proxy);
        if (callback == ((void *)0) && type == &_PyWeakref_RefType) {
            if (ref != ((void *)0)) {
                _Py_INCREF(((PyObject *)(ref)));
                return (PyObject *)ref;
            }
        }
        self = (PyWeakReference *)(type->tp_alloc(type, 0));
        if (self != ((void *)0)) {
            init_weakref(self, ob, callback);
            if (callback == ((void *)0) && type == &_PyWeakref_RefType) {
                insert_head(self, list);
            } else {
                PyWeakReference *prev;
                get_basic_refs(*list, &ref, &proxy);
                prev = (proxy == ((void *)0)) ? ref : proxy;
                if (prev == ((void *)0)) {
                    insert_head(self, list);
                } else
                    insert_after(self, prev);
            }
        }
    }
    return (PyObject *)self;
}


static int weakref___init__ (PyObject *self, PyObject *args, PyObject *kwargs){
    PyObject *tmp;
    if (!((kwargs) == ((void *)0) || _PyArg_NoKeywords(("ref"), (kwargs))))
        return -1;
    if (parse_weakref_init_args("__init__", args, kwargs, &tmp, &tmp)) {
        return 0;
    } else
        return -1;
}


static int proxy_checkref (PyWeakReference *proxy){
    if ((_Py_REFCNT(((const PyObject *)(((PyWeakReference *)(proxy))->wr_object))) > 0 ? ((PyWeakReference *)(proxy))->wr_object : (&_Py_NoneStruct)) == (&_Py_NoneStruct)) {
        PyErr_SetString(PyExc_ReferenceError, "weakly-referenced object no longer exists");
        return 0;
    }
    return 1;
}


static PyObject * proxy_repr (PyWeakReference *proxy){
    return PyUnicode_FromFormat("<weakproxy at %p to %s at %p>", proxy, (((PyObject *)((_Py_REFCNT(((const PyObject *)(((PyWeakReference *)(proxy))->wr_object))) > 0 ? ((PyWeakReference *)(proxy))->wr_object : (&_Py_NoneStruct))))->ob_type)->tp_name, (_Py_REFCNT(((const PyObject *)(((PyWeakReference *)(proxy))->wr_object))) > 0 ? ((PyWeakReference *)(proxy))->wr_object : (&_Py_NoneStruct)));
}


static int proxy_setattr (PyWeakReference *proxy, PyObject *name, PyObject *value){
    if (!proxy_checkref(proxy))
        return -1;
    PyObject *obj = (_Py_REFCNT(((const PyObject *)(((PyWeakReference *)(proxy))->wr_object))) > 0 ? ((PyWeakReference *)(proxy))->wr_object : (&_Py_NoneStruct));
    _Py_INCREF(((PyObject *)(obj)));
    int res = PyObject_SetAttr(obj, name, value);
    _Py_DECREF(((PyObject *)(obj)));
    return res;
}


static PyObject * proxy_richcompare (PyObject *proxy, PyObject *v, int op){
    if ((_Py_IS_TYPE(((const PyObject *)(proxy)), &_PyWeakref_ProxyType) || _Py_IS_TYPE(((const PyObject *)(proxy)), &_PyWeakref_CallableProxyType))) {
        if (!proxy_checkref((PyWeakReference *)proxy))
            return ((void *)0);
        proxy = (_Py_REFCNT(((const PyObject *)(((PyWeakReference *)(proxy))->wr_object))) > 0 ? ((PyWeakReference *)(proxy))->wr_object : (&_Py_NoneStruct));
    }
    ;
    ;
    if ((_Py_IS_TYPE(((const PyObject *)(v)), &_PyWeakref_ProxyType) || _Py_IS_TYPE(((const PyObject *)(v)), &_PyWeakref_CallableProxyType))) {
        if (!proxy_checkref((PyWeakReference *)v))
            return ((void *)0);
        v = (_Py_REFCNT(((const PyObject *)(((PyWeakReference *)(v))->wr_object))) > 0 ? ((PyWeakReference *)(v))->wr_object : (&_Py_NoneStruct));
    }
    ;
    ;
    return PyObject_RichCompare(proxy, v, op);
}


static int proxy_bool (PyWeakReference *proxy){
    PyObject *o = (_Py_REFCNT(((const PyObject *)(((PyWeakReference *)(proxy))->wr_object))) > 0 ? ((PyWeakReference *)(proxy))->wr_object : (&_Py_NoneStruct));
    if (!proxy_checkref(proxy)) {
        return -1;
    }
    _Py_INCREF(((PyObject *)(o)));
    int res = PyObject_IsTrue(o);
    _Py_DECREF(((PyObject *)(o)));
    return res;
}


static void proxy_dealloc (PyWeakReference *self){
    if (self->wr_callback != ((void *)0))
        PyObject_GC_UnTrack((PyObject *)self);
    clear_weakref(self);
    PyObject_GC_Del(self);
}


static int proxy_contains (PyWeakReference *proxy, PyObject *value){
    if (!proxy_checkref(proxy))
        return -1;
    PyObject *obj = (_Py_REFCNT(((const PyObject *)(((PyWeakReference *)(proxy))->wr_object))) > 0 ? ((PyWeakReference *)(proxy))->wr_object : (&_Py_NoneStruct));
    _Py_INCREF(((PyObject *)(obj)));
    int res = PySequence_Contains(obj, value);
    _Py_DECREF(((PyObject *)(obj)));
    return res;
}


static Py_ssize_t proxy_length (PyWeakReference *proxy){
    if (!proxy_checkref(proxy))
        return -1;
    PyObject *obj = (_Py_REFCNT(((const PyObject *)(((PyWeakReference *)(proxy))->wr_object))) > 0 ? ((PyWeakReference *)(proxy))->wr_object : (&_Py_NoneStruct));
    _Py_INCREF(((PyObject *)(obj)));
    Py_ssize_t res = PyObject_Size(obj);
    _Py_DECREF(((PyObject *)(obj)));
    return res;
}


static int proxy_setitem (PyWeakReference *proxy, PyObject *key, PyObject *value){
    if (!proxy_checkref(proxy))
        return -1;
    PyObject *obj = (_Py_REFCNT(((const PyObject *)(((PyWeakReference *)(proxy))->wr_object))) > 0 ? ((PyWeakReference *)(proxy))->wr_object : (&_Py_NoneStruct));
    _Py_INCREF(((PyObject *)(obj)));
    int res;
    if (value == ((void *)0)) {
        res = PyObject_DelItem(obj, key);
    } else {
        res = PyObject_SetItem(obj, key, value);
    }
    _Py_DECREF(((PyObject *)(obj)));
    return res;
}


static PyObject * proxy_iter (PyWeakReference *proxy){
    if (!proxy_checkref(proxy))
        return ((void *)0);
    PyObject *obj = (_Py_REFCNT(((const PyObject *)(((PyWeakReference *)(proxy))->wr_object))) > 0 ? ((PyWeakReference *)(proxy))->wr_object : (&_Py_NoneStruct));
    _Py_INCREF(((PyObject *)(obj)));
    PyObject *res = PyObject_GetIter(obj);
    _Py_DECREF(((PyObject *)(obj)));
    return res;
}


static PyObject * proxy_iternext (PyWeakReference *proxy){
    if (!proxy_checkref(proxy))
        return ((void *)0);
    PyObject *obj = (_Py_REFCNT(((const PyObject *)(((PyWeakReference *)(proxy))->wr_object))) > 0 ? ((PyWeakReference *)(proxy))->wr_object : (&_Py_NoneStruct));
    if (!PyIter_Check(obj)) {
        PyErr_Format(PyExc_TypeError, "Weakref proxy referenced a non-iterator '%.200s' object", (((PyObject *)(obj))->ob_type)->tp_name);
        return ((void *)0);
    }
    _Py_INCREF(((PyObject *)(obj)));
    PyObject *res = PyIter_Next(obj);
    _Py_DECREF(((PyObject *)(obj)));
    return res;
}


static void handle_callback (PyWeakReference *ref, PyObject *callback){
    PyObject *cbresult = PyObject_CallOneArg(callback, (PyObject *)ref);
    if (cbresult == ((void *)0))
        PyErr_WriteUnraisable(callback);
    else
        _Py_DECREF(((PyObject *)(cbresult)));
}


extern  __attribute__((visibility("default"))) void PyObject_ClearWeakRefs (PyObject *object){
    PyWeakReference **list;
    if (object == ((void *)0) || !(((((PyObject *)(object))->ob_type))->tp_weaklistoffset > 0) || _Py_REFCNT(((const PyObject *)(object))) != 0) {
        _PyErr_BadInternalCall("Objects/weakrefobject_InstSlice.c", 818);
        return;
    }
    list = ((PyWeakReference **)_PyObject_GET_WEAKREFS_LISTPTR(object));
    if (*list != ((void *)0) && (*list)->wr_callback == ((void *)0)) {
        clear_weakref(*list);
        if (*list != ((void *)0) && (*list)->wr_callback == ((void *)0))
            clear_weakref(*list);
    }
    if (*list != ((void *)0)) {
        PyWeakReference *current = *list;
        Py_ssize_t count = _PyWeakref_GetWeakrefCount(current);
        PyObject *err_type, *err_value, *err_tb;
        PyErr_Fetch(&err_type, &err_value, &err_tb);
        if (count == 1) {
            PyObject *callback = current->wr_callback;
            current->wr_callback = ((void *)0);
            clear_weakref(current);
            if (callback != ((void *)0)) {
                if (_Py_REFCNT(((const PyObject *)((PyObject *)current))) > 0) {
                    handle_callback(current, callback);
                }
                _Py_DECREF(((PyObject *)(callback)));
            }
        } else {
            PyObject *tuple;
            Py_ssize_t i = 0;
            tuple = PyTuple_New(count * 2);
            if (tuple == ((void *)0)) {
                _PyErr_ChainExceptions(err_type, err_value, err_tb);
                return;
            }
            for (i = 0; i < count; ++i) {
                PyWeakReference *next = current->wr_next;
                if (_Py_REFCNT(((const PyObject *)((PyObject *)current))) > 0) {
                    _Py_INCREF(((PyObject *)(current)));
                    ((void)((((void)(0)) , (PyTupleObject *)(tuple))->ob_item[i * 2] = (PyObject *)current));
                    ((void)((((void)(0)) , (PyTupleObject *)(tuple))->ob_item[i * 2 + 1] = current->wr_callback));
                } else {
                    _Py_DECREF(((PyObject *)(current->wr_callback)));
                }
                current->wr_callback = ((void *)0);
                clear_weakref(current);
                current = next;
            }
            for (i = 0; i < count; ++i) {
                PyObject *callback = ((((void)(0)) , (PyTupleObject *)(tuple))->ob_item[i * 2 + 1]);
                if (callback != ((void *)0)) {
                    PyObject *item = ((((void)(0)) , (PyTupleObject *)(tuple))->ob_item[i * 2]);
                    handle_callback((PyWeakReference *)item, callback);
                }
            }
            _Py_DECREF(((PyObject *)(tuple)));
        }
        ;
        PyErr_Restore(err_type, err_value, err_tb);
    }
}


