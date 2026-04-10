static PyObject * faulthandler_sigfpe (PyObject *self, PyObject *args){
    ;
    volatile int x = 1, y = 0, z;
    z = x / y;
    ;
    return PyLong_FromLong(z);
}


