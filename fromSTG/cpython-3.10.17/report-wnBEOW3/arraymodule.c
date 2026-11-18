static array_state * get_array_state (PyObject *module){
    return (array_state *)_PyModule_GetState(module);
}


static int array_resize (arrayobject *self, Py_ssize_t newsize){
    char *items;
    size_t _new_size;
    if (self->ob_exports > 0 && newsize != (((PyVarObject *)(self))->ob_size)) {
        ;
        return -1;
    }
    if (self->allocated >= newsize && (((PyVarObject *)(self))->ob_size) < newsize + 16 && self->ob_item != ((void *)0)) {
        _Py_SET_SIZE(((PyVarObject *)(self)), newsize);
        return 0;
    }
    if (newsize == 0) {
        ;
        self->ob_item = ((void *)0);
        _Py_SET_SIZE(((PyVarObject *)(self)), 0);
        self->allocated = 0;
        return 0;
    }
    _new_size = (newsize >> 4) + ((((PyVarObject *)(self))->ob_size) < 8 ? 3 : 7) + newsize;
    items = self->ob_item;
    if (_new_size <= ((~(size_t)0) / self->ob_descr->itemsize))
        ((items) = ((size_t)((_new_size * self->ob_descr->itemsize)) > ((Py_ssize_t)(((size_t)-1) >> 1)) / sizeof(char)) ? ((void *)0) : (char *)PyMem_Realloc((items), ((_new_size * self->ob_descr->itemsize)) * sizeof(char)));
    else
        items = ((void *)0);
    if (items == ((void *)0)) {
        ;
        return -1;
    }
    self->ob_item = items;
    _Py_SET_SIZE(((PyVarObject *)(self)), newsize);
    self->allocated = _new_size;
    return 0;
}


static PyObject * newarrayobject (PyTypeObject *type, Py_ssize_t size, const struct arraydescr *descr){
    arrayobject *op;
    size_t nbytes;
    if (size < 0) {
        ;
        return ((void *)0);
    }
    if (size > ((Py_ssize_t)(((size_t)-1) >> 1)) / descr->itemsize) {
        return PyErr_NoMemory();
    }
    nbytes = size * descr->itemsize;
    op = (arrayobject *)type->tp_alloc(type, 0);
    if (op == ((void *)0)) {
        return ((void *)0);
    }
    op->ob_descr = descr;
    op->allocated = size;
    op->weakreflist = ((void *)0);
    _Py_SET_SIZE(((PyVarObject *)(op)), size);
    if (size <= 0) {
        op->ob_item = ((void *)0);
    } else {
        op->ob_item = (((size_t)(nbytes) > ((Py_ssize_t)(((size_t)-1) >> 1)) / sizeof(char)) ? ((void *)0) : ((char *)PyMem_Malloc((nbytes) * sizeof(char))));
        if (op->ob_item == ((void *)0)) {
            _Py_DECREF(((PyObject *)(op)));
            return PyErr_NoMemory();
        }
    }
    op->ob_exports = 0;
    return (PyObject *)op;
}


static PyObject * array_slice (arrayobject *a, Py_ssize_t ilow, Py_ssize_t ihigh){
    array_state *state = (get_array_state(_PyType_GetModuleByDef((((PyObject *)(a))->ob_type), &arraymodule)));
    arrayobject *np;
    if (ilow < 0)
        ilow = 0;
    else if (ilow > (((PyVarObject *)(a))->ob_size))
        ilow = (((PyVarObject *)(a))->ob_size);
    if (ihigh < 0)
        ihigh = 0;
    if (ihigh < ilow)
        ihigh = ilow;
    else if (ihigh > (((PyVarObject *)(a))->ob_size))
        ihigh = (((PyVarObject *)(a))->ob_size);
    np = (arrayobject *)newarrayobject(state->ArrayType, ihigh - ilow, a->ob_descr);
    if (np == ((void *)0))
        return ((void *)0);
    return (PyObject *)np;
}


static int array_ass_subscr (arrayobject *self, PyObject *item, PyObject *value){
    Py_ssize_t start, stop, step, slicelength, needed;
    array_state *state = (get_array_state(_PyType_GetModuleByDef((((PyObject *)(self))->ob_type), &arraymodule)));
    arrayobject *other;
    int itemsize;
    if (PyIndex_Check(item)) {
        Py_ssize_t i = PyNumber_AsSsize_t(item, PyExc_IndexError);
        if (i == -1 && PyErr_Occurred())
            return -1;
        if (i < 0)
            i += (((PyVarObject *)(self))->ob_size);
        if (i < 0 || i >= (((PyVarObject *)(self))->ob_size)) {
            ;
            return -1;
        }
        if (value == ((void *)0)) {
            start = i;
            stop = i + 1;
            step = 1;
            slicelength = 1;
        } else {
            ;
        }
    } else if (_Py_IS_TYPE(((const PyObject *)(item)), &PySlice_Type)) {
        if (PySlice_Unpack(item, &start, &stop, &step) < 0) {
            return -1;
        }
        slicelength = PySlice_AdjustIndices((((PyVarObject *)(self))->ob_size), &start, &stop, step);
    } else {
        ;
    }
    if (value == ((void *)0)) {
        other = ((void *)0);
        needed = 0;
    } else if (_PyObject_TypeCheck(((PyObject *)(value)), state->ArrayType)) {
        other = (arrayobject *)value;
        needed = (((PyVarObject *)(other))->ob_size);
        if (self == other) {
            int ret;
            value = array_slice(other, 0, needed);
            if (value == ((void *)0))
                return -1;
            ret = array_ass_subscr(self, item, value);
            _Py_DECREF(((PyObject *)(value)));
            return ret;
        }
        if (other->ob_descr != self->ob_descr) {
            ;
            return -1;
        }
    } else {
        ;
    }
    itemsize = self->ob_descr->itemsize;
    if ((step > 0 && stop < start) || (step < 0 && stop > start))
        stop = start;
    if ((needed == 0 || slicelength != needed) && self->ob_exports > 0) {
        ;
        return -1;
    }
    if (step == 1) {
        if (slicelength > needed) {
            ;
            if (array_resize(self, (((PyVarObject *)(self))->ob_size) + needed - slicelength) < 0)
                return -1;
        } else if (slicelength < needed) {
            if (array_resize(self, (((PyVarObject *)(self))->ob_size) + needed - slicelength) < 0)
                return -1;
            memmove(self->ob_item + (start + needed) * itemsize, self->ob_item + stop * itemsize, ((((PyVarObject *)(self))->ob_size) - start - needed) * itemsize);
        }
        ;
        return 0;
    } else if (needed == 0) {
        size_t cur;
        Py_ssize_t i;
        if (step < 0) {
            stop = start + 1;
            start = stop + step * (slicelength - 1) - 1;
            step = -step;
        }
        for (cur = start , i = 0; i < slicelength; cur += step , i++) {
            Py_ssize_t lim = step - 1;
            if (cur + step >= (size_t)(((PyVarObject *)(self))->ob_size))
                lim = (((PyVarObject *)(self))->ob_size) - cur - 1;
            ;
        }
        cur = start + (size_t)slicelength * step;
        if (array_resize(self, (((PyVarObject *)(self))->ob_size) - slicelength) < 0)
            return -1;
        return 0;
    } else {
        size_t cur;
        Py_ssize_t i;
        return 0;
    }
}


