#include "header_func.h"
#include "pycore_pystate.h"
#include "object.h"
extern  __attribute__((visibility("default"))) void _PyErr_Restore (PyThreadState *tstate, PyObject *type, PyObject *value, PyObject *traceback){
    PyObject *oldtype, *oldvalue, *oldtraceback;
    if (traceback != ((void *)0) && !_Py_IS_TYPE(((const PyObject *)(traceback)), &PyTraceBack_Type)) {
        _Py_DECREF(((PyObject *)(traceback)));
        traceback = ((void *)0);
    }
    oldtype = tstate->curexc_type;
    oldvalue = tstate->curexc_value;
    oldtraceback = tstate->curexc_traceback;
    tstate->curexc_type = type;
    tstate->curexc_value = value;
    tstate->curexc_traceback = traceback;
    _Py_XDECREF(((PyObject *)(oldtype)));
    _Py_XDECREF(((PyObject *)(oldvalue)));
    _Py_XDECREF(((PyObject *)(oldtraceback)));
}
extern  __attribute__((visibility("default"))) _PyErr_StackItem * _PyErr_GetTopmostException (PyThreadState *tstate){
    _PyErr_StackItem *exc_info = tstate->exc_info;
    while ((exc_info->exc_type == ((void *)0) || exc_info->exc_type == (&_Py_NoneStruct)) && exc_info->previous_item != ((void *)0))
        {
            exc_info = exc_info->previous_item;
        }
    return exc_info;
}
static PyObject * _PyErr_CreateException (PyObject *exception_type, PyObject *value){
    PyObject *exc;
    if (value == ((void *)0) || value == (&_Py_NoneStruct)) {
        exc = _PyObject_CallNoArg(exception_type);
    } else if (PyType_HasFeature((((PyObject *)(value))->ob_type), (1UL << 26))) {
        exc = PyObject_Call(exception_type, value, ((void *)0));
    } else {
        exc = PyObject_CallOneArg(exception_type, value);
    }
    if (exc != ((void *)0) && !PyType_HasFeature((((PyObject *)(exc))->ob_type), (1UL << 30))) {
        PyErr_Format(PyExc_TypeError, "calling %R should have returned an instance of BaseException, not %s", exception_type, (((PyObject *)(exc))->ob_type)->tp_name);
        do {
            PyObject *_py_tmp = ((PyObject *)(exc));
            if (_py_tmp != ((void *)0)) {
                (exc) = ((void *)0);
                _Py_DECREF(((PyObject *)(_py_tmp)));
            }
        } while (0);
    }
    return exc;
}
extern  __attribute__((visibility("default"))) void _PyErr_SetObject (PyThreadState *tstate, PyObject *exception, PyObject *value){
    PyObject *exc_value;
    PyObject *tb = ((void *)0);
    if (exception != ((void *)0) && !(_PyType_Check(((PyObject *)((exception)))) && PyType_HasFeature((PyTypeObject *)(exception), (1UL << 30)))) {
        _PyErr_Format(tstate, PyExc_SystemError, "_PyErr_SetObject: exception %R is not a BaseException subclass", exception);
        return;
    }
    _Py_XINCREF(((PyObject *)(value)));
    exc_value = _PyErr_GetTopmostException(tstate)->exc_value;
    if (exc_value != ((void *)0) && exc_value != (&_Py_NoneStruct)) {
        _Py_INCREF(((PyObject *)(exc_value)));
        if (value == ((void *)0) || !PyType_HasFeature((((PyObject *)(value))->ob_type), (1UL << 30))) {
            PyObject *fixed_value;
            _PyErr_Clear(tstate);
            fixed_value = _PyErr_CreateException(exception, value);
            _Py_XDECREF(((PyObject *)(value)));
            if (fixed_value == ((void *)0)) {
                _Py_DECREF(((PyObject *)(exc_value)));
                return;
            }
            value = fixed_value;
        }
        if (exc_value != value) {
            PyObject *o = exc_value, *context;
            PyObject *slow_o = o;
            int slow_update_toggle = 0;
            while ((context = PyException_GetContext(o)))
                {
                    _Py_DECREF(((PyObject *)(context)));
                    if (context == value) {
                        PyException_SetContext(o, ((void *)0));
                        break;
                    }
                    o = context;
                    if (o == slow_o) {
                        break;
                    }
                    if (slow_update_toggle) {
                        slow_o = PyException_GetContext(slow_o);
                        _Py_DECREF(((PyObject *)(slow_o)));
                    }
                    slow_update_toggle = !slow_update_toggle;
                }
            PyException_SetContext(value, exc_value);
        } else {
            _Py_DECREF(((PyObject *)(exc_value)));
        }
    }
    if (value != ((void *)0) && PyType_HasFeature((((PyObject *)(value))->ob_type), (1UL << 30)))
        tb = PyException_GetTraceback(value);
    _Py_XINCREF(((PyObject *)(exception)));
    _PyErr_Restore(tstate, exception, value, tb);
}
extern  __attribute__((visibility("default"))) void _PyErr_SetString (PyThreadState *tstate, PyObject *exception, const char *string){
    PyObject *value = PyUnicode_FromString(string);
    _PyErr_SetObject(tstate, exception, value);
    _Py_XDECREF(((PyObject *)(value)));
}
extern  __attribute__((visibility("default"))) int PyErr_GivenExceptionMatches (PyObject *err, PyObject *exc){
    if (err == ((void *)0) || exc == ((void *)0)) {
        return 0;
    }
    if (PyType_HasFeature((((PyObject *)(exc))->ob_type), (1UL << 26))) {
        Py_ssize_t i, n;
        n = PyTuple_Size(exc);
        for (i = 0; i < n; i++) {
            if (PyErr_GivenExceptionMatches(err, ((((void)(0)) , (PyTupleObject *)(exc))->ob_item[i]))) {
                return 1;
            }
        }
        return 0;
    }
    if (PyType_HasFeature((((PyObject *)(err))->ob_type), (1UL << 30)))
        err = ((PyObject *)(((PyObject *)(err))->ob_type));
    if ((_PyType_Check(((PyObject *)((err)))) && PyType_HasFeature((PyTypeObject *)(err), (1UL << 30))) && (_PyType_Check(((PyObject *)((exc)))) && PyType_HasFeature((PyTypeObject *)(exc), (1UL << 30)))) {
        return PyType_IsSubtype((PyTypeObject *)err, (PyTypeObject *)exc);
    }
    return err == exc;
}
extern  __attribute__((visibility("default"))) void _PyErr_NormalizeException (PyThreadState *tstate, PyObject **exc, PyObject **val, PyObject **tb){
    int recursion_depth = 0;
    tstate->recursion_headroom++;
    PyObject *type, *value, *initial_tb;
  restart:
    type = *exc;
    if (type == ((void *)0)) {
        tstate->recursion_headroom--;
        return;
    }
    value = *val;
    if (!value) {
        value = (&_Py_NoneStruct);
        _Py_INCREF(((PyObject *)(value)));
    }
    if ((_PyType_Check(((PyObject *)((type)))) && PyType_HasFeature((PyTypeObject *)(type), (1UL << 30)))) {
        PyObject *inclass = ((void *)0);
        int is_subclass = 0;
        if (PyType_HasFeature((((PyObject *)(value))->ob_type), (1UL << 30))) {
            inclass = ((PyObject *)(((PyObject *)(value))->ob_type));
            is_subclass = PyObject_IsSubclass(inclass, type);
            if (is_subclass < 0) {
                goto error;
            }
        }
        if (!is_subclass) {
            PyObject *fixed_value = _PyErr_CreateException(type, value);
            if (fixed_value == ((void *)0)) {
                goto error;
            }
            _Py_DECREF(((PyObject *)(value)));
            value = fixed_value;
        } else if (inclass != type) {
            _Py_INCREF(((PyObject *)(inclass)));
            _Py_DECREF(((PyObject *)(type)));
            type = inclass;
        }
    }
    *exc = type;
    *val = value;
    tstate->recursion_headroom--;
    return;
  error:
    _Py_DECREF(((PyObject *)(type)));
    _Py_DECREF(((PyObject *)(value)));
    recursion_depth++;
    if (recursion_depth == 32) {
        _PyErr_SetString(tstate, PyExc_RecursionError, "maximum recursion depth exceeded while normalizing an exception");
    }
    initial_tb = *tb;
    _PyErr_Fetch(tstate, exc, val, tb);
    if (initial_tb != ((void *)0)) {
        if (*tb == ((void *)0))
            *tb = initial_tb;
        else
            _Py_DECREF(((PyObject *)(initial_tb)));
    }
    if (recursion_depth >= 32 + 2) {
        if (PyErr_GivenExceptionMatches(*exc, PyExc_MemoryError)) {
            _Py_FatalErrorFunc(__func__, "Cannot recover from MemoryErrors while normalizing exceptions.");
        } else {
            _Py_FatalErrorFunc(__func__, "Cannot recover from the recursive normalization of an exception.");
        }
    }
    goto restart;
}
extern  __attribute__((visibility("default"))) void _PyErr_Fetch (PyThreadState *tstate, PyObject **p_type, PyObject **p_value, PyObject **p_traceback){
    *p_type = tstate->curexc_type;
    *p_value = tstate->curexc_value;
    *p_traceback = tstate->curexc_traceback;
    tstate->curexc_type = ((void *)0);
    tstate->curexc_value = ((void *)0);
    tstate->curexc_traceback = ((void *)0);
}
extern  __attribute__((visibility("default"))) void _PyErr_Clear (PyThreadState *tstate){
    _PyErr_Restore(tstate, ((void *)0), ((void *)0), ((void *)0));
}
static PyObject * _PyErr_FormatVFromCause (PyThreadState *tstate, PyObject *exception, const char *format, va_list vargs){
    PyObject *exc, *val, *val2, *tb;
    _PyErr_Fetch(tstate, &exc, &val, &tb);
    _PyErr_NormalizeException(tstate, &exc, &val, &tb);
    if (tb != ((void *)0)) {
        PyException_SetTraceback(val, tb);
        _Py_DECREF(((PyObject *)(tb)));
    }
    _Py_DECREF(((PyObject *)(exc)));
    _PyErr_FormatV(tstate, exception, format, vargs);
    _PyErr_Fetch(tstate, &exc, &val2, &tb);
    _PyErr_NormalizeException(tstate, &exc, &val2, &tb);
    _Py_INCREF(((PyObject *)(val)));
    PyException_SetCause(val2, val);
    PyException_SetContext(val2, val);
    _PyErr_Restore(tstate, exc, val2, tb);
    return ((void *)0);
}
extern  __attribute__((visibility("default"))) PyObject * _PyErr_FormatFromCause (PyObject *exception, const char *format, ...){
    PyThreadState *tstate = _PyThreadState_GET();
    va_list vargs;
    __builtin_va_start(vargs, format);
    _PyErr_FormatVFromCause(tstate, exception, format, vargs);
    __builtin_va_end(vargs);
    return ((void *)0);
}
static PyObject * _PyErr_FormatV (PyThreadState *tstate, PyObject *exception, const char *format, va_list vargs){
    PyObject *string;
    _PyErr_Clear(tstate);
    string = PyUnicode_FromFormatV(format, vargs);
    _PyErr_SetObject(tstate, exception, string);
    _Py_XDECREF(((PyObject *)(string)));
    return ((void *)0);
}
extern  __attribute__((visibility("default"))) PyObject * _PyErr_Format (PyThreadState *tstate, PyObject *exception, const char *format, ...){
    va_list vargs;
    __builtin_va_start(vargs, format);
    _PyErr_FormatV(tstate, exception, format, vargs);
    __builtin_va_end(vargs);
    return ((void *)0);
}
extern  __attribute__((visibility("default"))) PyObject * PyErr_Format (PyObject *exception, const char *format, ...){
    PyThreadState *tstate = _PyThreadState_GET();
    va_list vargs;
    __builtin_va_start(vargs, format);
    _PyErr_FormatV(tstate, exception, format, vargs);
    __builtin_va_end(vargs);
    return ((void *)0);
}
