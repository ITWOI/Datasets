static inline int parse_args_finds_byte (const char *function_name, PyObject *args, PyObject **subobj, char *byte, Py_ssize_t *start, Py_ssize_t *end){
    PyObject *tmp_subobj;
    Py_ssize_t ival;
    if (!stringlib_parse_args_finds(function_name, args, &tmp_subobj, start, end))
        return 0;
    if (PyObject_CheckBuffer(tmp_subobj)) {
        *subobj = tmp_subobj;
        return 1;
    }
    if (!_PyIndex_Check(tmp_subobj)) {
        ;
        return 0;
    }
    ival = PyNumber_AsSsize_t(tmp_subobj, ((void *)0));
    if (ival == -1 && PyErr_Occurred()) {
        return 0;
    }
    if (ival < 0 || ival > 255) {
        ;
        return 0;
    }
    *subobj = ((void *)0);
    *byte = (char)ival;
    return 1;
}


static inline Py_ssize_t find_internal (const char *str, Py_ssize_t len, const char *function_name, PyObject *args, int dir){
    PyObject *subobj;
    char byte;
    Py_buffer subbuf;
    const char *sub;
    Py_ssize_t sub_len;
    Py_ssize_t start = 0, end = ((Py_ssize_t)(((size_t)-1) >> 1));
    Py_ssize_t res;
    if (!parse_args_finds_byte(function_name, args, &subobj, &byte, &start, &end))
        return -2;
    if (subobj) {
        if (PyObject_GetBuffer(subobj, &subbuf, 0) != 0)
            return -2;
        sub = subbuf.buf;
        sub_len = subbuf.len;
    } else {
        sub = &byte;
        sub_len = 1;
    }
    if (end > len)
        end = len;
    else if (end < 0) {
        end += len;
        if (end < 0)
            end = 0;
    }
    if (start < 0) {
        start += len;
        if (start < 0)
            start = 0;
    }
    ;
    ;
    if (end - start < sub_len) {
        ;
    } else if (sub_len == 1) {
        if (dir > 0) {
            res = stringlib_find_char(str + start, end - start, *sub);
        } else {
            ;
        }
        ;
    } else {
        if (dir > 0) {
            res = stringlib_find_slice(str, len, sub, sub_len, start, end);
        } else
            res = stringlib_rfind_slice(str, len, sub, sub_len, start, end);
    }
    ;
    return res;
}


extern PyObject * _Py_bytes_index (const char *str, Py_ssize_t len, PyObject *args){
    Py_ssize_t result = find_internal(str, len, "index", args, +1);
    ;
    return PyLong_FromSsize_t(result);
}


