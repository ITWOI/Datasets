#include "header_func.h"
#include "pycore_moduleobject.h"
#include "object.h"
static inline _structmodulestate * get_struct_state (PyObject *module){
    void *state = _PyModule_GetState(module);
    return (_structmodulestate *)state;
}
static PyObject * get_pylong (_structmodulestate *state, PyObject *v){
    ;
    if (!PyType_HasFeature((((PyObject *)(v))->ob_type), (1UL << 24))) {
        if (PyIndex_Check(v)) {
            v = _PyNumber_Index(v);
            if (v == ((void *)0))
                return ((void *)0);
        } else {
            PyErr_SetString(state->StructError, "required argument is not an integer");
            return ((void *)0);
        }
    } else
        _Py_INCREF(((PyObject *)(v)));
    return v;
}
static int get_long (_structmodulestate *state, PyObject *v, long *p){
    long x;
    v = get_pylong(state, v);
    if (v == ((void *)0))
        return -1;
    x = PyLong_AsLong(v);
    _Py_DECREF(((PyObject *)(v)));
    if (x == (long)-1 && PyErr_Occurred()) {
        if (PyErr_ExceptionMatches(PyExc_OverflowError))
            PyErr_SetString(state->StructError, "argument out of range");
        return -1;
    }
    *p = x;
    return 0;
}
static int get_ulong (_structmodulestate *state, PyObject *v, unsigned long *p){
    unsigned long x;
    v = get_pylong(state, v);
    if (v == ((void *)0))
        return -1;
    x = PyLong_AsUnsignedLong(v);
    _Py_DECREF(((PyObject *)(v)));
    if (x == (unsigned long)-1 && PyErr_Occurred()) {
        if (PyErr_ExceptionMatches(PyExc_OverflowError))
            PyErr_SetString(state->StructError, "argument out of range");
        return -1;
    }
    *p = x;
    return 0;
}
static int get_longlong (_structmodulestate *state, PyObject *v, long long *p){
    long long x;
    v = get_pylong(state, v);
    if (v == ((void *)0))
        return -1;
    x = PyLong_AsLongLong(v);
    _Py_DECREF(((PyObject *)(v)));
    if (x == (long long)-1 && PyErr_Occurred()) {
        if (PyErr_ExceptionMatches(PyExc_OverflowError))
            PyErr_SetString(state->StructError, "argument out of range");
        return -1;
    }
    *p = x;
    return 0;
}
static int get_ulonglong (_structmodulestate *state, PyObject *v, unsigned long long *p){
    unsigned long long x;
    v = get_pylong(state, v);
    if (v == ((void *)0))
        return -1;
    x = PyLong_AsUnsignedLongLong(v);
    _Py_DECREF(((PyObject *)(v)));
    if (x == (unsigned long long)-1 && PyErr_Occurred()) {
        if (PyErr_ExceptionMatches(PyExc_OverflowError))
            PyErr_SetString(state->StructError, "argument out of range");
        return -1;
    }
    *p = x;
    return 0;
}
static int get_ssize_t (_structmodulestate *state, PyObject *v, Py_ssize_t *p){
    Py_ssize_t x;
    v = get_pylong(state, v);
    if (v == ((void *)0))
        return -1;
    x = PyLong_AsSsize_t(v);
    _Py_DECREF(((PyObject *)(v)));
    if (x == (Py_ssize_t)-1 && PyErr_Occurred()) {
        if (PyErr_ExceptionMatches(PyExc_OverflowError))
            PyErr_SetString(state->StructError, "argument out of range");
        return -1;
    }
    *p = x;
    return 0;
}
static int get_size_t (_structmodulestate *state, PyObject *v, size_t *p){
    size_t x;
    v = get_pylong(state, v);
    if (v == ((void *)0))
        return -1;
    x = PyLong_AsSize_t(v);
    _Py_DECREF(((PyObject *)(v)));
    if (x == (size_t)-1 && PyErr_Occurred()) {
        if (PyErr_ExceptionMatches(PyExc_OverflowError))
            PyErr_SetString(state->StructError, "argument out of range");
        return -1;
    }
    *p = x;
    return 0;
}
static PyObject * unpack_halffloat (const char *p, int le){
    double x;
    x = _PyFloat_Unpack2((unsigned char *)p, le);
    if (x == -1. && PyErr_Occurred()) {
        return ((void *)0);
    }
    return PyFloat_FromDouble(x);
}
static int pack_halffloat (_structmodulestate *state, char *p, PyObject *v, int le){
    double x = PyFloat_AsDouble(v);
    if (x == -1. && PyErr_Occurred()) {
        PyErr_SetString(state->StructError, "required argument is not a float");
        return -1;
    }
    return _PyFloat_Pack2(x, (unsigned char *)p, le);
}
static PyObject * unpack_float (const char *p, int le){
    double x;
    x = _PyFloat_Unpack4((unsigned char *)p, le);
    if (x == -1. && PyErr_Occurred())
        return ((void *)0);
    return PyFloat_FromDouble(x);
}
static PyObject * unpack_double (const char *p, int le){
    double x;
    x = _PyFloat_Unpack8((unsigned char *)p, le);
    if (x == -1. && PyErr_Occurred())
        return ((void *)0);
    return PyFloat_FromDouble(x);
}
static int _range_error (_structmodulestate *state, const formatdef *f, int is_unsigned){
    const size_t ulargest = (size_t)-1 >> ((8 - f->size) * 8);
    if (is_unsigned) {
        PyErr_Format(state->StructError, "'%c' format requires 0 <= number <= %zu", f->format, ulargest);
    } else {
        const Py_ssize_t largest = (Py_ssize_t)(ulargest >> 1);
        PyErr_Format(state->StructError, "'%c' format requires %zd <= number <= %zd", f->format, ~largest, largest);
    }
    return -1;
}
static PyObject * nu_char (_structmodulestate *state, const char *p, const formatdef *f){
    return PyBytes_FromStringAndSize(p, 1);
}
static PyObject * nu_byte (_structmodulestate *state, const char *p, const formatdef *f){
    return PyLong_FromLong((long)*(signed char *)p);
}
static PyObject * nu_ubyte (_structmodulestate *state, const char *p, const formatdef *f){
    return PyLong_FromLong((long)*(unsigned char *)p);
}
static PyObject * nu_short (_structmodulestate *state, const char *p, const formatdef *f){
    short x;
    memcpy((char *)&x, p, sizeof x);
    return PyLong_FromLong((long)x);
}
static PyObject * nu_ushort (_structmodulestate *state, const char *p, const formatdef *f){
    unsigned short x;
    memcpy((char *)&x, p, sizeof x);
    return PyLong_FromLong((long)x);
}
static PyObject * nu_int (_structmodulestate *state, const char *p, const formatdef *f){
    int x;
    memcpy((char *)&x, p, sizeof x);
    return PyLong_FromLong((long)x);
}
static PyObject * nu_uint (_structmodulestate *state, const char *p, const formatdef *f){
    unsigned int x;
    memcpy((char *)&x, p, sizeof x);
    return PyLong_FromUnsignedLong((unsigned long)x);
}
static PyObject * nu_long (_structmodulestate *state, const char *p, const formatdef *f){
    long x;
    memcpy((char *)&x, p, sizeof x);
    return PyLong_FromLong(x);
}
static PyObject * nu_ulong (_structmodulestate *state, const char *p, const formatdef *f){
    unsigned long x;
    memcpy((char *)&x, p, sizeof x);
    return PyLong_FromUnsignedLong(x);
}
static PyObject * nu_ssize_t (_structmodulestate *state, const char *p, const formatdef *f){
    Py_ssize_t x;
    memcpy((char *)&x, p, sizeof x);
    return PyLong_FromSsize_t(x);
}
static PyObject * nu_size_t (_structmodulestate *state, const char *p, const formatdef *f){
    size_t x;
    memcpy((char *)&x, p, sizeof x);
    return PyLong_FromSize_t(x);
}
static PyObject * nu_longlong (_structmodulestate *state, const char *p, const formatdef *f){
    long long x;
    memcpy((char *)&x, p, sizeof x);
    return PyLong_FromLongLong(x);
}
static PyObject * nu_ulonglong (_structmodulestate *state, const char *p, const formatdef *f){
    unsigned long long x;
    memcpy((char *)&x, p, sizeof x);
    return PyLong_FromUnsignedLongLong(x);
}
static PyObject * nu_bool (_structmodulestate *state, const char *p, const formatdef *f){
    _Bool x;
    memcpy((char *)&x, p, sizeof x);
    return PyBool_FromLong(x != 0);
}
static PyObject * nu_halffloat (_structmodulestate *state, const char *p, const formatdef *f){
    return unpack_halffloat(p, 1);
}
static PyObject * nu_float (_structmodulestate *state, const char *p, const formatdef *f){
    float x;
    memcpy((char *)&x, p, sizeof x);
    return PyFloat_FromDouble((double)x);
}
static PyObject * nu_double (_structmodulestate *state, const char *p, const formatdef *f){
    double x;
    memcpy((char *)&x, p, sizeof x);
    return PyFloat_FromDouble(x);
}
static PyObject * nu_void_p (_structmodulestate *state, const char *p, const formatdef *f){
    void *x;
    memcpy((char *)&x, p, sizeof x);
    return PyLong_FromVoidPtr(x);
}
static int np_byte (_structmodulestate *state, char *p, PyObject *v, const formatdef *f){
    long x;
    if (get_long(state, v, &x) < 0)
        return -1;
    if (x < -128 || x > 127) {
        PyErr_SetString(state->StructError, "byte format requires -128 <= number <= 127");
        return -1;
    }
    *p = (char)x;
    return 0;
}
static int np_ubyte (_structmodulestate *state, char *p, PyObject *v, const formatdef *f){
    long x;
    if (get_long(state, v, &x) < 0)
        return -1;
    if (x < 0 || x > 255) {
        PyErr_SetString(state->StructError, "ubyte format requires 0 <= number <= 255");
        return -1;
    }
    *(unsigned char *)p = (unsigned char)x;
    return 0;
}
static int np_char (_structmodulestate *state, char *p, PyObject *v, const formatdef *f){
    if (!PyType_HasFeature((((PyObject *)(v))->ob_type), (1UL << 27)) || PyBytes_Size(v) != 1) {
        PyErr_SetString(state->StructError, "char format requires a bytes object of length 1");
        return -1;
    }
    *p = *(((void)(0)) , (((PyBytesObject *)(v))->ob_sval));
    return 0;
}
static int np_short (_structmodulestate *state, char *p, PyObject *v, const formatdef *f){
    long x;
    short y;
    if (get_long(state, v, &x) < 0)
        return -1;
    if (x < (-32767 - 1) || x > 32767) {
        PyErr_SetString(state->StructError, "short format requires (-32767 -1) <= number <= 32767");
        return -1;
    }
    y = (short)x;
    memcpy(p, (char *)&y, sizeof y);
    return 0;
}
static int np_ushort (_structmodulestate *state, char *p, PyObject *v, const formatdef *f){
    long x;
    unsigned short y;
    if (get_long(state, v, &x) < 0)
        return -1;
    if (x < 0 || x > (32767 * 2 + 1)) {
        PyErr_SetString(state->StructError, "ushort format requires 0 <= number <= (32767 * 2 + 1)");
        return -1;
    }
    y = (unsigned short)x;
    memcpy(p, (char *)&y, sizeof y);
    return 0;
}
static int np_int (_structmodulestate *state, char *p, PyObject *v, const formatdef *f){
    long x;
    int y;
    if (get_long(state, v, &x) < 0)
        return -1;
    if ((x < ((long)(-2147483647 - 1))) || (x > ((long)2147483647)))
        return _range_error(state, f, 0);
    y = (int)x;
    memcpy(p, (char *)&y, sizeof y);
    return 0;
}
static int np_uint (_structmodulestate *state, char *p, PyObject *v, const formatdef *f){
    unsigned long x;
    unsigned int y;
    if (get_ulong(state, v, &x) < 0)
        return -1;
    y = (unsigned int)x;
    if (x > ((unsigned long)(2147483647 * 2U + 1U)))
        return _range_error(state, f, 1);
    memcpy(p, (char *)&y, sizeof y);
    return 0;
}
static int np_long (_structmodulestate *state, char *p, PyObject *v, const formatdef *f){
    long x;
    if (get_long(state, v, &x) < 0)
        return -1;
    memcpy(p, (char *)&x, sizeof x);
    return 0;
}
static int np_ulong (_structmodulestate *state, char *p, PyObject *v, const formatdef *f){
    unsigned long x;
    if (get_ulong(state, v, &x) < 0)
        return -1;
    memcpy(p, (char *)&x, sizeof x);
    return 0;
}
static int np_ssize_t (_structmodulestate *state, char *p, PyObject *v, const formatdef *f){
    Py_ssize_t x;
    if (get_ssize_t(state, v, &x) < 0)
        return -1;
    memcpy(p, (char *)&x, sizeof x);
    return 0;
}
static int np_size_t (_structmodulestate *state, char *p, PyObject *v, const formatdef *f){
    size_t x;
    if (get_size_t(state, v, &x) < 0)
        return -1;
    memcpy(p, (char *)&x, sizeof x);
    return 0;
}
static int np_longlong (_structmodulestate *state, char *p, PyObject *v, const formatdef *f){
    long long x;
    if (get_longlong(state, v, &x) < 0)
        return -1;
    memcpy(p, (char *)&x, sizeof x);
    return 0;
}
static int np_ulonglong (_structmodulestate *state, char *p, PyObject *v, const formatdef *f){
    unsigned long long x;
    if (get_ulonglong(state, v, &x) < 0)
        return -1;
    memcpy(p, (char *)&x, sizeof x);
    return 0;
}
static int np_bool (_structmodulestate *state, char *p, PyObject *v, const formatdef *f){
    int y;
    _Bool x;
    y = PyObject_IsTrue(v);
    if (y < 0)
        return -1;
    x = y;
    memcpy(p, (char *)&x, sizeof x);
    return 0;
}
static int np_halffloat (_structmodulestate *state, char *p, PyObject *v, const formatdef *f){
    return pack_halffloat(state, p, v, 1);
}
static int np_float (_structmodulestate *state, char *p, PyObject *v, const formatdef *f){
    float x = (float)PyFloat_AsDouble(v);
    if (x == -1 && PyErr_Occurred()) {
        PyErr_SetString(state->StructError, "required argument is not a float");
        return -1;
    }
    memcpy(p, (char *)&x, sizeof x);
    return 0;
}
static int np_double (_structmodulestate *state, char *p, PyObject *v, const formatdef *f){
    double x = PyFloat_AsDouble(v);
    if (x == -1 && PyErr_Occurred()) {
        PyErr_SetString(state->StructError, "required argument is not a float");
        return -1;
    }
    memcpy(p, (char *)&x, sizeof(double));
    return 0;
}
static int np_void_p (_structmodulestate *state, char *p, PyObject *v, const formatdef *f){
    void *x;
    v = get_pylong(state, v);
    if (v == ((void *)0))
        return -1;
    x = PyLong_AsVoidPtr(v);
    _Py_DECREF(((PyObject *)(v)));
    if (x == ((void *)0) && PyErr_Occurred())
        return -1;
    memcpy(p, (char *)&x, sizeof x);
    return 0;
}
static PyObject * bu_int (_structmodulestate *state, const char *p, const formatdef *f){
    long x = 0;
    Py_ssize_t i = f->size;
    const unsigned char *bytes = (const unsigned char *)p;
    do {
        x = (x << 8) | *bytes++;
    } while (--i > 0);
    if (8 > f->size)
        x |= -(x & (1L << ((8 * f->size) - 1)));
    return PyLong_FromLong(x);
}
static PyObject * bu_uint (_structmodulestate *state, const char *p, const formatdef *f){
    unsigned long x = 0;
    Py_ssize_t i = f->size;
    const unsigned char *bytes = (const unsigned char *)p;
    do {
        x = (x << 8) | *bytes++;
    } while (--i > 0);
    return PyLong_FromUnsignedLong(x);
}
static PyObject * bu_longlong (_structmodulestate *state, const char *p, const formatdef *f){
    long long x = 0;
    Py_ssize_t i = f->size;
    const unsigned char *bytes = (const unsigned char *)p;
    do {
        x = (x << 8) | *bytes++;
    } while (--i > 0);
    if (8 > f->size)
        x |= -(x & ((long long)1 << ((8 * f->size) - 1)));
    return PyLong_FromLongLong(x);
}
static PyObject * bu_ulonglong (_structmodulestate *state, const char *p, const formatdef *f){
    unsigned long long x = 0;
    Py_ssize_t i = f->size;
    const unsigned char *bytes = (const unsigned char *)p;
    do {
        x = (x << 8) | *bytes++;
    } while (--i > 0);
    return PyLong_FromUnsignedLongLong(x);
}
static PyObject * bu_halffloat (_structmodulestate *state, const char *p, const formatdef *f){
    return unpack_halffloat(p, 0);
}
static PyObject * bu_float (_structmodulestate *state, const char *p, const formatdef *f){
    return unpack_float(p, 0);
}
static PyObject * bu_double (_structmodulestate *state, const char *p, const formatdef *f){
    return unpack_double(p, 0);
}
static PyObject * bu_bool (_structmodulestate *state, const char *p, const formatdef *f){
    return PyBool_FromLong(*p != 0);
}
static int bp_int (_structmodulestate *state, char *p, PyObject *v, const formatdef *f){
    long x;
    Py_ssize_t i;
    unsigned char *q = (unsigned char *)p;
    if (get_long(state, v, &x) < 0)
        return -1;
    i = f->size;
    if (i != 8) {
        if ((i == 2) && (x < -32768 || x > 32767))
            return _range_error(state, f, 0);
        else if ((i == 4) && (x < -2147483648L || x > 2147483647L))
            return _range_error(state, f, 0);
    }
    do {
        q[--i] = (unsigned char)(x & 255L);
        x >>= 8;
    } while (i > 0);
    return 0;
}
static int bp_uint (_structmodulestate *state, char *p, PyObject *v, const formatdef *f){
    unsigned long x;
    Py_ssize_t i;
    unsigned char *q = (unsigned char *)p;
    if (get_ulong(state, v, &x) < 0)
        return -1;
    i = f->size;
    if (i != 8) {
        unsigned long maxint = 1;
        maxint <<= (unsigned long)(i * 8);
        if (x >= maxint)
            return _range_error(state, f, 1);
    }
    do {
        q[--i] = (unsigned char)(x & 255UL);
        x >>= 8;
    } while (i > 0);
    return 0;
}
static int bp_longlong (_structmodulestate *state, char *p, PyObject *v, const formatdef *f){
    int res;
    v = get_pylong(state, v);
    if (v == ((void *)0))
        return -1;
    res = _PyLong_AsByteArray((PyLongObject *)v, (unsigned char *)p, 8, 0, 1);
    _Py_DECREF(((PyObject *)(v)));
    return res;
}
static int bp_ulonglong (_structmodulestate *state, char *p, PyObject *v, const formatdef *f){
    int res;
    v = get_pylong(state, v);
    if (v == ((void *)0))
        return -1;
    res = _PyLong_AsByteArray((PyLongObject *)v, (unsigned char *)p, 8, 0, 0);
    _Py_DECREF(((PyObject *)(v)));
    return res;
}
static int bp_halffloat (_structmodulestate *state, char *p, PyObject *v, const formatdef *f){
    return pack_halffloat(state, p, v, 0);
}
static int bp_float (_structmodulestate *state, char *p, PyObject *v, const formatdef *f){
    double x = PyFloat_AsDouble(v);
    if (x == -1 && PyErr_Occurred()) {
        PyErr_SetString(state->StructError, "required argument is not a float");
        return -1;
    }
    return _PyFloat_Pack4(x, (unsigned char *)p, 0);
}
static int bp_double (_structmodulestate *state, char *p, PyObject *v, const formatdef *f){
    double x = PyFloat_AsDouble(v);
    if (x == -1 && PyErr_Occurred()) {
        PyErr_SetString(state->StructError, "required argument is not a float");
        return -1;
    }
    return _PyFloat_Pack8(x, (unsigned char *)p, 0);
}
static int bp_bool (_structmodulestate *state, char *p, PyObject *v, const formatdef *f){
    int y;
    y = PyObject_IsTrue(v);
    if (y < 0)
        return -1;
    *p = (char)y;
    return 0;
}
static PyObject * lu_int (_structmodulestate *state, const char *p, const formatdef *f){
    long x = 0;
    Py_ssize_t i = f->size;
    const unsigned char *bytes = (const unsigned char *)p;
    do {
        x = (x << 8) | bytes[--i];
    } while (i > 0);
    if (8 > f->size)
        x |= -(x & (1L << ((8 * f->size) - 1)));
    return PyLong_FromLong(x);
}
static PyObject * lu_uint (_structmodulestate *state, const char *p, const formatdef *f){
    unsigned long x = 0;
    Py_ssize_t i = f->size;
    const unsigned char *bytes = (const unsigned char *)p;
    do {
        x = (x << 8) | bytes[--i];
    } while (i > 0);
    return PyLong_FromUnsignedLong(x);
}
static PyObject * lu_longlong (_structmodulestate *state, const char *p, const formatdef *f){
    long long x = 0;
    Py_ssize_t i = f->size;
    const unsigned char *bytes = (const unsigned char *)p;
    do {
        x = (x << 8) | bytes[--i];
    } while (i > 0);
    if (8 > f->size)
        x |= -(x & ((long long)1 << ((8 * f->size) - 1)));
    return PyLong_FromLongLong(x);
}
static PyObject * lu_ulonglong (_structmodulestate *state, const char *p, const formatdef *f){
    unsigned long long x = 0;
    Py_ssize_t i = f->size;
    const unsigned char *bytes = (const unsigned char *)p;
    do {
        x = (x << 8) | bytes[--i];
    } while (i > 0);
    return PyLong_FromUnsignedLongLong(x);
}
static PyObject * lu_halffloat (_structmodulestate *state, const char *p, const formatdef *f){
    return unpack_halffloat(p, 1);
}
static PyObject * lu_float (_structmodulestate *state, const char *p, const formatdef *f){
    return unpack_float(p, 1);
}
static PyObject * lu_double (_structmodulestate *state, const char *p, const formatdef *f){
    return unpack_double(p, 1);
}
static int lp_int (_structmodulestate *state, char *p, PyObject *v, const formatdef *f){
    long x;
    Py_ssize_t i;
    unsigned char *q = (unsigned char *)p;
    if (get_long(state, v, &x) < 0)
        return -1;
    i = f->size;
    if (i != 8) {
        if ((i == 2) && (x < -32768 || x > 32767))
            return _range_error(state, f, 0);
        else if ((i == 4) && (x < -2147483648L || x > 2147483647L))
            return _range_error(state, f, 0);
    }
    do {
        *q++ = (unsigned char)(x & 255L);
        x >>= 8;
    } while (--i > 0);
    return 0;
}
static int lp_uint (_structmodulestate *state, char *p, PyObject *v, const formatdef *f){
    unsigned long x;
    Py_ssize_t i;
    unsigned char *q = (unsigned char *)p;
    if (get_ulong(state, v, &x) < 0)
        return -1;
    i = f->size;
    if (i != 8) {
        unsigned long maxint = 1;
        maxint <<= (unsigned long)(i * 8);
        if (x >= maxint)
            return _range_error(state, f, 1);
    }
    do {
        *q++ = (unsigned char)(x & 255UL);
        x >>= 8;
    } while (--i > 0);
    return 0;
}
static int lp_longlong (_structmodulestate *state, char *p, PyObject *v, const formatdef *f){
    int res;
    v = get_pylong(state, v);
    if (v == ((void *)0))
        return -1;
    res = _PyLong_AsByteArray((PyLongObject *)v, (unsigned char *)p, 8, 1, 1);
    _Py_DECREF(((PyObject *)(v)));
    return res;
}
static int lp_ulonglong (_structmodulestate *state, char *p, PyObject *v, const formatdef *f){
    int res;
    v = get_pylong(state, v);
    if (v == ((void *)0))
        return -1;
    res = _PyLong_AsByteArray((PyLongObject *)v, (unsigned char *)p, 8, 1, 0);
    _Py_DECREF(((PyObject *)(v)));
    return res;
}
static int lp_halffloat (_structmodulestate *state, char *p, PyObject *v, const formatdef *f){
    return pack_halffloat(state, p, v, 1);
}
static int lp_float (_structmodulestate *state, char *p, PyObject *v, const formatdef *f){
    double x = PyFloat_AsDouble(v);
    if (x == -1 && PyErr_Occurred()) {
        PyErr_SetString(state->StructError, "required argument is not a float");
        return -1;
    }
    return _PyFloat_Pack4(x, (unsigned char *)p, 1);
}
static int lp_double (_structmodulestate *state, char *p, PyObject *v, const formatdef *f){
    double x = PyFloat_AsDouble(v);
    if (x == -1 && PyErr_Occurred()) {
        PyErr_SetString(state->StructError, "required argument is not a float");
        return -1;
    }
    return _PyFloat_Pack8(x, (unsigned char *)p, 1);
}
static const formatdef * whichtable (const char **pfmt){
    const char *fmt = (*pfmt)++;
    switch (*fmt) {
      case '<':
        return lilendian_table;
      case '>':
      case '!':
        return bigendian_table;
      case '=':
        {
            return lilendian_table;
        }
      default:
        --*pfmt;
      case '@':
        return native_table;
    }
}
static const formatdef * getentry (_structmodulestate *state, int c, const formatdef *f){
    for (; f->format != '\x00'; f++) {
        if (f->format == c) {
            return f;
        }
    }
    PyErr_SetString(state->StructError, "bad char in struct format");
    return ((void *)0);
}
static Py_ssize_t align (Py_ssize_t size, char c, const formatdef *e){
    Py_ssize_t extra;
    if (e->format == c) {
        if (e->alignment && size > 0) {
            extra = (e->alignment - 1) - (size - 1) % (e->alignment);
            if (extra > ((Py_ssize_t)(((size_t)-1) >> 1)) - size)
                return -1;
            size += extra;
        }
    }
    return size;
}
static int prepare_s (PyStructObject *self){
    const formatdef *f;
    const formatdef *e;
    formatcode *codes;
    const char *s;
    const char *fmt;
    char c;
    Py_ssize_t size, len, num, itemsize;
    size_t ncodes;
    _structmodulestate *state = (get_struct_state(_PyType_GetModuleByDef((((PyObject *)(self))->ob_type), &_structmodule)));
    fmt = (((void)(0)) , (((PyBytesObject *)(self->s_format))->ob_sval));
    if (strlen(fmt) != (size_t)(((void)(0)) , (((PyVarObject *)(self->s_format))->ob_size))) {
        PyErr_SetString(state->StructError, "embedded null character");
        return -1;
    }
    f = whichtable(&fmt);
    s = fmt;
    size = 0;
    len = 0;
    ncodes = 0;
    while ((c = *s++) != '\x00')
        {
            if ((_Py_ctype_table[((unsigned char)((c) & 255))] & 8))
                continue;
            if ('0' <= c && c <= '9') {
                num = c - '0';
                while ('0' <= (c = *s++) && c <= '9')
                    {
                        if (num >= ((Py_ssize_t)(((size_t)-1) >> 1)) / 10 && (num > ((Py_ssize_t)(((size_t)-1) >> 1)) / 10 || (c - '0') > ((Py_ssize_t)(((size_t)-1) >> 1)) % 10))
                            goto overflow;
                        num = num * 10 + (c - '0');
                    }
                if (c == '\x00') {
                    PyErr_SetString(state->StructError, "repeat count given without format specifier");
                    return -1;
                }
            } else
                num = 1;
            e = getentry(state, c, f);
            if (e == ((void *)0))
                return -1;
            switch (c) {
              case 's':
              case 'p':
                len++;
                ncodes++;
                break;
              case 'x':
                break;
              default:
                len += num;
                if (num)
                    ncodes++;
                break;
            }
            itemsize = e->size;
            size = align(size, c, e);
            if (size == -1)
                goto overflow;
            if (num > (((Py_ssize_t)(((size_t)-1) >> 1)) - size) / itemsize)
                goto overflow;
            size += num * itemsize;
        }
    if ((ncodes + 1) > ((size_t)((Py_ssize_t)(((size_t)-1) >> 1)) / sizeof(formatcode))) {
        PyErr_NoMemory();
        return -1;
    }
    self->s_size = size;
    self->s_len = len;
    codes = PyMem_Malloc((ncodes + 1) * sizeof(formatcode));
    if (codes == ((void *)0)) {
        PyErr_NoMemory();
        return -1;
    }
    if (self->s_codes != ((void *)0))
        PyMem_Free(self->s_codes);
    self->s_codes = codes;
    s = fmt;
    size = 0;
    while ((c = *s++) != '\x00')
        {
            if ((_Py_ctype_table[((unsigned char)((c) & 255))] & 8))
                continue;
            if ('0' <= c && c <= '9') {
                num = c - '0';
                while ('0' <= (c = *s++) && c <= '9')
                    num = num * 10 + (c - '0');
            } else
                num = 1;
            e = getentry(state, c, f);
            size = align(size, c, e);
            if (c == 's' || c == 'p') {
                codes->offset = size;
                codes->size = num;
                codes->fmtdef = e;
                codes->repeat = 1;
                codes++;
                size += num;
            } else if (c == 'x') {
                size += num;
            } else if (num) {
                codes->offset = size;
                codes->size = e->size;
                codes->fmtdef = e;
                codes->repeat = num;
                codes++;
                size += e->size * num;
            }
        }
    codes->fmtdef = ((void *)0);
    codes->offset = size;
    codes->size = 0;
    codes->repeat = 0;
    return 0;
  overflow:
    PyErr_SetString(state->StructError, "total struct size too long");
    return -1;
}
static PyObject * s_new (PyTypeObject *type, PyObject *args, PyObject *kwds){
    PyObject *self;
    allocfunc alloc_func = PyType_GetSlot(type, 47);
    self = alloc_func(type, 0);
    if (self != ((void *)0)) {
        PyStructObject *s = (PyStructObject *)self;
        s->s_format = _Py_NewRef(((PyObject *)((&_Py_NoneStruct))));
        s->s_codes = ((void *)0);
        s->s_size = -1;
        s->s_len = -1;
    }
    return self;
}
static int Struct___init___impl (PyStructObject *self, PyObject *format){
    int ret = 0;
    if (PyType_HasFeature((((PyObject *)(format))->ob_type), (1UL << 28))) {
        format = PyUnicode_AsASCIIString(format);
        if (format == ((void *)0))
            return -1;
    } else {
        _Py_INCREF(((PyObject *)(format)));
    }
    if (!PyType_HasFeature((((PyObject *)(format))->ob_type), (1UL << 27))) {
        _Py_DECREF(((PyObject *)(format)));
        PyErr_Format(PyExc_TypeError, "Struct() argument 1 must be a str or bytes object, not %.200s", _PyType_Name((((PyObject *)(format))->ob_type)));
        return -1;
    }
    do {
        PyObject *_py_tmp = ((PyObject *)(self->s_format));
        (self->s_format) = (format);
        _Py_DECREF(((PyObject *)(_py_tmp)));
    } while (0);
    ret = prepare_s(self);
    return ret;
}
static int s_clear (PyStructObject *s){
    do {
        PyObject *_py_tmp = ((PyObject *)(s->s_format));
        if (_py_tmp != ((void *)0)) {
            (s->s_format) = ((void *)0);
            _Py_DECREF(((PyObject *)(_py_tmp)));
        }
    } while (0);
    return 0;
}
static int s_traverse (PyStructObject *s, visitproc visit, void *arg){
    do {
        if ((((PyObject *)(s))->ob_type)) {
            int vret = visit(((PyObject *)((((PyObject *)(s))->ob_type))), arg);
            if (vret)
                return vret;
        }
    } while (0);
    do {
        if (s->s_format) {
            int vret = visit(((PyObject *)(s->s_format)), arg);
            if (vret)
                return vret;
        }
    } while (0);
    return 0;
}
static void s_dealloc (PyStructObject *s){
    PyTypeObject *tp = (((PyObject *)(s))->ob_type);
    PyObject_GC_UnTrack(s);
    if (s->weakreflist != ((void *)0))
        PyObject_ClearWeakRefs((PyObject *)s);
    if (s->s_codes != ((void *)0)) {
        PyMem_Free(s->s_codes);
    }
    _Py_XDECREF(((PyObject *)(s->s_format)));
    freefunc free_func = PyType_GetSlot((((PyObject *)(s))->ob_type), 74);
    free_func(s);
    _Py_DECREF(((PyObject *)(tp)));
}
static PyObject * s_unpack_internal (PyStructObject *soself, const char *startfrom, _structmodulestate *state){
    formatcode *code;
    Py_ssize_t i = 0;
    PyObject *result = PyTuple_New(soself->s_len);
    if (result == ((void *)0))
        return ((void *)0);
    for (code = soself->s_codes; code->fmtdef != ((void *)0); code++) {
        const formatdef *e = code->fmtdef;
        const char *res = startfrom + code->offset;
        Py_ssize_t j = code->repeat;
        while (j--)
            {
                PyObject *v;
                if (e->format == 's') {
                    v = PyBytes_FromStringAndSize(res, code->size);
                } else if (e->format == 'p') {
                    Py_ssize_t n = *(unsigned char *)res;
                    if (n >= code->size)
                        n = code->size - 1;
                    v = PyBytes_FromStringAndSize(res + 1, n);
                } else {
                    v = e->unpack(state, res, e);
                }
                if (v == ((void *)0))
                    goto fail;
                ((void)((((void)(0)) , (PyTupleObject *)(result))->ob_item[i++] = v));
                res += code->size;
            }
    }
    return result;
  fail:
    _Py_DECREF(((PyObject *)(result)));
    return ((void *)0);
}
static PyObject * Struct_unpack_impl (PyStructObject *self, Py_buffer *buffer){
    _structmodulestate *state = (get_struct_state(_PyType_GetModuleByDef((((PyObject *)(self))->ob_type), &_structmodule)));
    if (buffer->len != self->s_size) {
        PyErr_Format(state->StructError, "unpack requires a buffer of %zd bytes", self->s_size);
        return ((void *)0);
    }
    return s_unpack_internal(self, buffer->buf, state);
}
static PyObject * Struct_unpack_from_impl (PyStructObject *self, Py_buffer *buffer, Py_ssize_t offset){
    _structmodulestate *state = (get_struct_state(_PyType_GetModuleByDef((((PyObject *)(self))->ob_type), &_structmodule)));
    if (offset < 0) {
        if (offset + self->s_size > 0) {
            PyErr_Format(state->StructError, "not enough data to unpack %zd bytes at offset %zd", self->s_size, offset);
            return ((void *)0);
        }
        if (offset + buffer->len < 0) {
            PyErr_Format(state->StructError, "offset %zd out of range for %zd-byte buffer", offset, buffer->len);
            return ((void *)0);
        }
        offset += buffer->len;
    }
    if ((buffer->len - offset) < self->s_size) {
        PyErr_Format(state->StructError, "unpack_from requires a buffer of at least %zu bytes for unpacking %zd bytes at offset %zd (actual buffer size is %zd)", (size_t)self->s_size + (size_t)offset, self->s_size, offset, buffer->len);
        return ((void *)0);
    }
    return s_unpack_internal(self, (char *)buffer->buf + offset, state);
}
static void unpackiter_dealloc (unpackiterobject *self){
    PyTypeObject *tp = (((PyObject *)(self))->ob_type);
    PyObject_GC_UnTrack(self);
    _Py_XDECREF(((PyObject *)(self->so)));
    PyBuffer_Release(&self->buf);
    PyObject_GC_Del(self);
    _Py_DECREF(((PyObject *)(tp)));
}
static int unpackiter_traverse (unpackiterobject *self, visitproc visit, void *arg){
    do {
        if ((((PyObject *)(self))->ob_type)) {
            int vret = visit(((PyObject *)((((PyObject *)(self))->ob_type))), arg);
            if (vret)
                return vret;
        }
    } while (0);
    do {
        if (self->so) {
            int vret = visit(((PyObject *)(self->so)), arg);
            if (vret)
                return vret;
        }
    } while (0);
    do {
        if (self->buf.obj) {
            int vret = visit(((PyObject *)(self->buf.obj)), arg);
            if (vret)
                return vret;
        }
    } while (0);
    return 0;
}
static PyObject * unpackiter_len (unpackiterobject *self, PyObject *_unused_ignored __attribute__((unused))){
    Py_ssize_t len;
    if (self->so == ((void *)0)) {
        len = 0;
    } else
        len = (self->buf.len - self->index) / self->so->s_size;
    return PyLong_FromSsize_t(len);
}
static PyObject * unpackiter_iternext (unpackiterobject *self){
    _structmodulestate *state = (get_struct_state(PyType_GetModule((((PyObject *)(self))->ob_type))));
    PyObject *result;
    if (self->so == ((void *)0))
        return ((void *)0);
    if (self->index >= self->buf.len) {
        do {
            PyObject *_py_tmp = ((PyObject *)(self->so));
            if (_py_tmp != ((void *)0)) {
                (self->so) = ((void *)0);
                _Py_DECREF(((PyObject *)(_py_tmp)));
            }
        } while (0);
        PyBuffer_Release(&self->buf);
        return ((void *)0);
    }
    ;
    result = s_unpack_internal(self->so, (char *)self->buf.buf + self->index, state);
    self->index += self->so->s_size;
    return result;
}
extern PyObject * unpackiter_new (PyTypeObject *type, PyObject *args, PyObject *kwds){
    PyErr_Format(PyExc_TypeError, "Cannot create '%.200s objects", _PyType_Name(type));
    return ((void *)0);
}
static PyObject * Struct_iter_unpack (PyStructObject *self, PyObject *buffer){
    _structmodulestate *state = (get_struct_state(_PyType_GetModuleByDef((((PyObject *)(self))->ob_type), &_structmodule)));
    unpackiterobject *iter;
    if (self->s_size == 0) {
        PyErr_Format(state->StructError, "cannot iteratively unpack with a struct of length 0");
        return ((void *)0);
    }
    iter = (unpackiterobject *)PyType_GenericAlloc((PyTypeObject *)state->unpackiter_type, 0);
    if (iter == ((void *)0))
        return ((void *)0);
    if (PyObject_GetBuffer(buffer, &iter->buf, 0) < 0) {
        _Py_DECREF(((PyObject *)(iter)));
        return ((void *)0);
    }
    if (iter->buf.len % self->s_size != 0) {
        PyErr_Format(state->StructError, "iterative unpacking requires a buffer of a multiple of %zd bytes", self->s_size);
        _Py_DECREF(((PyObject *)(iter)));
        return ((void *)0);
    }
    _Py_INCREF(((PyObject *)(self)));
    iter->so = self;
    iter->index = 0;
    return (PyObject *)iter;
}
static int s_pack_internal (PyStructObject *soself, PyObject *const *args, int offset, char *buf, _structmodulestate *state){
    formatcode *code;
    Py_ssize_t i;
    memset(buf, '\x00', soself->s_size);
    i = offset;
    for (code = soself->s_codes; code->fmtdef != ((void *)0); code++) {
        const formatdef *e = code->fmtdef;
        char *res = buf + code->offset;
        Py_ssize_t j = code->repeat;
        while (j--)
            {
                PyObject *v = args[i++];
                if (e->format == 's') {
                    Py_ssize_t n;
                    int isstring;
                    const void *p;
                    isstring = PyType_HasFeature((((PyObject *)(v))->ob_type), (1UL << 27));
                    if (!isstring && !_PyObject_TypeCheck(((PyObject *)(v)), &PyByteArray_Type)) {
                        PyErr_SetString(state->StructError, "argument for 's' must be a bytes object");
                        return -1;
                    }
                    if (isstring) {
                        n = (((void)(0)) , (((PyVarObject *)(v))->ob_size));
                        p = (((void)(0)) , (((PyBytesObject *)(v))->ob_sval));
                    } else {
                        n = (((void)(0)) , (((PyVarObject *)(v))->ob_size));
                        p = (((void)(0)) , (((PyVarObject *)(v))->ob_size) ? ((PyByteArrayObject *)(v))->ob_start : _PyByteArray_empty_string);
                    }
                    if (n > code->size)
                        n = code->size;
                    if (n > 0)
                        memcpy(res, p, n);
                } else if (e->format == 'p') {
                    Py_ssize_t n;
                    int isstring;
                    const void *p;
                    isstring = PyType_HasFeature((((PyObject *)(v))->ob_type), (1UL << 27));
                    if (!isstring && !_PyObject_TypeCheck(((PyObject *)(v)), &PyByteArray_Type)) {
                        PyErr_SetString(state->StructError, "argument for 'p' must be a bytes object");
                        return -1;
                    }
                    if (isstring) {
                        n = (((void)(0)) , (((PyVarObject *)(v))->ob_size));
                        p = (((void)(0)) , (((PyBytesObject *)(v))->ob_sval));
                    } else {
                        n = (((void)(0)) , (((PyVarObject *)(v))->ob_size));
                        p = (((void)(0)) , (((PyVarObject *)(v))->ob_size) ? ((PyByteArrayObject *)(v))->ob_start : _PyByteArray_empty_string);
                    }
                    if (n > (code->size - 1))
                        n = code->size - 1;
                    if (n > 0)
                        memcpy(res + 1, p, n);
                    if (n > 255)
                        n = 255;
                    *res = (unsigned char)(n);
                } else {
                    if (e->pack(state, res, v, e) < 0) {
                        if (PyType_HasFeature((((PyObject *)(v))->ob_type), (1UL << 24)) && PyErr_ExceptionMatches(PyExc_OverflowError))
                            PyErr_SetString(state->StructError, "int too large to convert");
                        return -1;
                    }
                }
                res += code->size;
            }
    }
    return 0;
}
static PyObject * s_pack (PyObject *self, PyObject *const *args, Py_ssize_t nargs){
    char *buf;
    PyStructObject *soself;
    _structmodulestate *state = (get_struct_state(_PyType_GetModuleByDef((((PyObject *)(self))->ob_type), &_structmodule)));
    soself = (PyStructObject *)self;
    if (nargs != soself->s_len) {
        PyErr_Format(state->StructError, "pack expected %zd items for packing (got %zd)", soself->s_len, nargs);
        return ((void *)0);
    }
    _PyBytesWriter writer;
    _PyBytesWriter_Init(&writer);
    buf = _PyBytesWriter_Alloc(&writer, soself->s_size);
    if (buf == ((void *)0)) {
        _PyBytesWriter_Dealloc(&writer);
        return ((void *)0);
    }
    if (s_pack_internal(soself, args, 0, buf, state) != 0) {
        _PyBytesWriter_Dealloc(&writer);
        return ((void *)0);
    }
    return _PyBytesWriter_Finish(&writer, buf + soself->s_size);
}
static PyObject * s_pack_into (PyObject *self, PyObject *const *args, Py_ssize_t nargs){
    PyStructObject *soself;
    Py_buffer buffer;
    Py_ssize_t offset;
    _structmodulestate *state = (get_struct_state(_PyType_GetModuleByDef((((PyObject *)(self))->ob_type), &_structmodule)));
    soself = (PyStructObject *)self;
    if (nargs != (soself->s_len + 2)) {
        if (nargs == 0) {
            PyErr_Format(state->StructError, "pack_into expected buffer argument");
        } else if (nargs == 1) {
            PyErr_Format(state->StructError, "pack_into expected offset argument");
        } else {
            PyErr_Format(state->StructError, "pack_into expected %zd items for packing (got %zd)", soself->s_len, (nargs - 2));
        }
        return ((void *)0);
    }
    if (!_PyArg_Parse_SizeT(args[0], "w*", &buffer))
        return ((void *)0);
    offset = PyNumber_AsSsize_t(args[1], PyExc_IndexError);
    if (offset == -1 && PyErr_Occurred()) {
        PyBuffer_Release(&buffer);
        return ((void *)0);
    }
    if (offset < 0) {
        if (offset + soself->s_size > 0) {
            PyErr_Format(state->StructError, "no space to pack %zd bytes at offset %zd", soself->s_size, offset);
            PyBuffer_Release(&buffer);
            return ((void *)0);
        }
        if (offset + buffer.len < 0) {
            PyErr_Format(state->StructError, "offset %zd out of range for %zd-byte buffer", offset, buffer.len);
            PyBuffer_Release(&buffer);
            return ((void *)0);
        }
        offset += buffer.len;
    }
    if ((buffer.len - offset) < soself->s_size) {
        ;
        PyErr_Format(state->StructError, "pack_into requires a buffer of at least %zu bytes for packing %zd bytes at offset %zd (actual buffer size is %zd)", (size_t)soself->s_size + (size_t)offset, soself->s_size, offset, buffer.len);
        PyBuffer_Release(&buffer);
        return ((void *)0);
    }
    if (s_pack_internal(soself, args, 2, (char *)buffer.buf + offset, state) != 0) {
        PyBuffer_Release(&buffer);
        return ((void *)0);
    }
    PyBuffer_Release(&buffer);
    return _Py_NewRef(((PyObject *)((&_Py_NoneStruct))));
}
static PyObject * s_get_format (PyStructObject *self, void *unused){
    return PyUnicode_FromStringAndSize((((void)(0)) , (((PyBytesObject *)(self->s_format))->ob_sval)), (((void)(0)) , (((PyVarObject *)(self->s_format))->ob_size)));
}
static PyObject * s_get_size (PyStructObject *self, void *unused){
    return PyLong_FromSsize_t(self->s_size);
}
static PyObject * s_sizeof (PyStructObject *self, void *unused){
    Py_ssize_t size;
    formatcode *code;
    size = (((((PyObject *)(self))->ob_type))->tp_basicsize) + sizeof(formatcode);
    for (code = self->s_codes; code->fmtdef != ((void *)0); code++)
        size += sizeof(formatcode);
    return PyLong_FromSsize_t(size);
}
static int cache_struct_converter (PyObject *module, PyObject *fmt, PyStructObject **ptr){
    PyObject *s_object;
    _structmodulestate *state = get_struct_state(module);
    if (fmt == ((void *)0)) {
        _Py_DECREF(((PyObject *)(*ptr)));
        *ptr = ((void *)0);
        return 1;
    }
    if (state->cache == ((void *)0)) {
        state->cache = PyDict_New();
        if (state->cache == ((void *)0))
            return 0;
    }
    s_object = PyDict_GetItemWithError(state->cache, fmt);
    if (s_object != ((void *)0)) {
        _Py_INCREF(((PyObject *)(s_object)));
        *ptr = (PyStructObject *)s_object;
        return 131072;
    } else if (PyErr_Occurred()) {
        return 0;
    }
    s_object = PyObject_CallOneArg(state->PyStructType, fmt);
    if (s_object != ((void *)0)) {
        if ((((void)(0)) , ((PyDictObject *)state->cache)->ma_used) >= 100)
            PyDict_Clear(state->cache);
        if (PyDict_SetItem(state->cache, fmt, s_object) == -1)
            PyErr_Clear();
        *ptr = (PyStructObject *)s_object;
        return 131072;
    }
    return 0;
}
static PyObject * _clearcache_impl (PyObject *module){
    do {
        PyObject *_py_tmp = ((PyObject *)(get_struct_state(module)->cache));
        if (_py_tmp != ((void *)0)) {
            (get_struct_state(module)->cache) = ((void *)0);
            _Py_DECREF(((PyObject *)(_py_tmp)));
        }
    } while (0);
    return _Py_NewRef(((PyObject *)((&_Py_NoneStruct))));
}
static Py_ssize_t calcsize_impl (PyObject *module, PyStructObject *s_object){
    return s_object->s_size;
}
static PyObject * pack (PyObject *module, PyObject *const *args, Py_ssize_t nargs){
    PyObject *s_object = ((void *)0);
    PyObject *format, *result;
    if (nargs == 0) {
        PyErr_SetString(PyExc_TypeError, "missing format argument");
        return ((void *)0);
    }
    format = args[0];
    if (!cache_struct_converter(module, format, (PyStructObject **)&s_object)) {
        return ((void *)0);
    }
    result = s_pack(s_object, args + 1, nargs - 1);
    _Py_DECREF(((PyObject *)(s_object)));
    return result;
}
static PyObject * pack_into (PyObject *module, PyObject *const *args, Py_ssize_t nargs){
    PyObject *s_object = ((void *)0);
    PyObject *format, *result;
    if (nargs == 0) {
        PyErr_SetString(PyExc_TypeError, "missing format argument");
        return ((void *)0);
    }
    format = args[0];
    if (!cache_struct_converter(module, format, (PyStructObject **)&s_object)) {
        return ((void *)0);
    }
    result = s_pack_into(s_object, args + 1, nargs - 1);
    _Py_DECREF(((PyObject *)(s_object)));
    return result;
}
static PyObject * unpack_impl (PyObject *module, PyStructObject *s_object, Py_buffer *buffer){
    return Struct_unpack_impl(s_object, buffer);
}
static PyObject * unpack_from_impl (PyObject *module, PyStructObject *s_object, Py_buffer *buffer, Py_ssize_t offset){
    return Struct_unpack_from_impl(s_object, buffer, offset);
}
static PyObject * iter_unpack_impl (PyObject *module, PyStructObject *s_object, PyObject *buffer){
    return Struct_iter_unpack(s_object, buffer);
}
static int _structmodule_traverse (PyObject *module, visitproc visit, void *arg){
    _structmodulestate *state = get_struct_state(module);
    if (state) {
        do {
            if (state->cache) {
                int vret = visit(((PyObject *)(state->cache)), arg);
                if (vret)
                    return vret;
            }
        } while (0);
        do {
            if (state->PyStructType) {
                int vret = visit(((PyObject *)(state->PyStructType)), arg);
                if (vret)
                    return vret;
            }
        } while (0);
        do {
            if (state->unpackiter_type) {
                int vret = visit(((PyObject *)(state->unpackiter_type)), arg);
                if (vret)
                    return vret;
            }
        } while (0);
        do {
            if (state->StructError) {
                int vret = visit(((PyObject *)(state->StructError)), arg);
                if (vret)
                    return vret;
            }
        } while (0);
    }
    return 0;
}
static int _structmodule_clear (PyObject *module){
    _structmodulestate *state = get_struct_state(module);
    if (state) {
        do {
            PyObject *_py_tmp = ((PyObject *)(state->cache));
            if (_py_tmp != ((void *)0)) {
                (state->cache) = ((void *)0);
                _Py_DECREF(((PyObject *)(_py_tmp)));
            }
        } while (0);
        do {
            PyObject *_py_tmp = ((PyObject *)(state->PyStructType));
            if (_py_tmp != ((void *)0)) {
                (state->PyStructType) = ((void *)0);
                _Py_DECREF(((PyObject *)(_py_tmp)));
            }
        } while (0);
        do {
            PyObject *_py_tmp = ((PyObject *)(state->unpackiter_type));
            if (_py_tmp != ((void *)0)) {
                (state->unpackiter_type) = ((void *)0);
                _Py_DECREF(((PyObject *)(_py_tmp)));
            }
        } while (0);
        do {
            PyObject *_py_tmp = ((PyObject *)(state->StructError));
            if (_py_tmp != ((void *)0)) {
                (state->StructError) = ((void *)0);
                _Py_DECREF(((PyObject *)(_py_tmp)));
            }
        } while (0);
    }
    return 0;
}
static void _structmodule_free (void *module){
    _structmodule_clear((PyObject *)module);
}
static int _structmodule_exec (PyObject *m){
    _structmodulestate *state = get_struct_state(m);
    state->PyStructType = PyType_FromModuleAndSpec(m, &PyStructType_spec, ((void *)0));
    if (state->PyStructType == ((void *)0)) {
        return -1;
    }
    if (PyModule_AddType(m, (PyTypeObject *)state->PyStructType) < 0) {
        return -1;
    }
    state->unpackiter_type = PyType_FromModuleAndSpec(m, &unpackiter_type_spec, ((void *)0));
    if (state->unpackiter_type == ((void *)0)) {
        return -1;
    }
    {
        const formatdef *native = native_table;
        formatdef *other, *ptr;
        other = lilendian_table;
        while (native->format != '\x00' && other->format != '\x00')
            {
                ptr = other;
                while (ptr->format != '\x00')
                    {
                        if (ptr->format == native->format) {
                            if (ptr == other)
                                other++;
                            if (ptr->size != native->size)
                                break;
                            if (ptr->format == 'd' || ptr->format == 'f')
                                break;
                            if (ptr->format == '?')
                                break;
                            ptr->pack = native->pack;
                            ptr->unpack = native->unpack;
                            break;
                        }
                        ptr++;
                    }
                native++;
            }
    }
    state->StructError = PyErr_NewException("struct.error", ((void *)0), ((void *)0));
    if (state->StructError == ((void *)0)) {
        return -1;
    }
    if (PyModule_AddObjectRef(m, "error", state->StructError) < 0) {
        return -1;
    }
    return 0;
}
