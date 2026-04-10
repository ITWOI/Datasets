#include "header_func.h"
static inline Py_ssize_t stringlib_find (const char *str, Py_ssize_t str_len, const char *sub, Py_ssize_t sub_len, Py_ssize_t offset){
    Py_ssize_t pos;
    if (sub_len == 0)
        return offset;
    pos = fastsearch(str, str_len, sub, sub_len, -1, 1);
    return pos;
}
static inline Py_ssize_t stringlib_rfind (const char *str, Py_ssize_t str_len, const char *sub, Py_ssize_t sub_len, Py_ssize_t offset){
    Py_ssize_t pos;
    if (sub_len == 0)
        return str_len + offset;
    pos = fastsearch(str, str_len, sub, sub_len, -1, 2);
    return pos;
}
static inline Py_ssize_t stringlib_find_slice (const char *str, Py_ssize_t str_len, const char *sub, Py_ssize_t sub_len, Py_ssize_t start, Py_ssize_t end){
    return stringlib_find(str + start, end - start, sub, sub_len, start);
}
static inline Py_ssize_t stringlib_rfind_slice (const char *str, Py_ssize_t str_len, const char *sub, Py_ssize_t sub_len, Py_ssize_t start, Py_ssize_t end){
    return stringlib_rfind(str + start, end - start, sub, sub_len, start);
}
static inline int stringlib_parse_args_finds (const char *function_name, PyObject *args, PyObject **subobj, Py_ssize_t *start, Py_ssize_t *end){
    PyObject *tmp_subobj;
    Py_ssize_t tmp_start = 0;
    Py_ssize_t tmp_end = ((Py_ssize_t)(((size_t)-1) >> 1));
    PyObject *obj_start = (&_Py_NoneStruct), *obj_end = (&_Py_NoneStruct);
    char format[50] = "O|OO:";
    size_t len = strlen(format);
    strncpy(format + len, function_name, 50 - len - 1);
    format[50 - 1] = '\x00';
    if (!_PyArg_ParseTuple_SizeT(args, format, &tmp_subobj, &obj_start, &obj_end))
        return 0;
    if (obj_start != (&_Py_NoneStruct))
        if (!_PyEval_SliceIndex(obj_start, &tmp_start))
            return 0;
    if (obj_end != (&_Py_NoneStruct))
        if (!_PyEval_SliceIndex(obj_end, &tmp_end))
            return 0;
    *start = tmp_start;
    *end = tmp_end;
    *subobj = tmp_subobj;
    return 1;
}
