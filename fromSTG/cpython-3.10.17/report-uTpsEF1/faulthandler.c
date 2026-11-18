static PyObject * faulthandler_read_null (PyObject *self, PyObject *args){
    volatile int *x;
    volatile int y;
    ;
    x = ((void *)0);
    y = *x;
    return PyLong_FromLong(y);
}


