#ifndef __HEADER_FUNC_H__ 
#define __HEADER_FUNC_H__
#include"header_type.h" 

void _Py_Dealloc(PyObject *);


PyCodeObject *PyFrame_GetCode(PyFrameObject *frame);

static inline void _Py_DECREF(PyObject *op) ;


Py_ssize_t _Py_write_noraise(int fd, const void *buf, size_t count);

static inline int _Py_IS_TYPE(const PyObject *ob, const PyTypeObject *type) ;

static void dump_frame(int fd, PyFrameObject *frame) ;

extern PyTypeObject PyFrame_Type;
;
void _Py_DumpHexadecimal(int fd, uintptr_t value, Py_ssize_t width) ;


PyThreadState *PyGILState_GetThisThreadState(void);


PyInterpreterState *_PyGILState_GetInterpreterStateUnsafe(void);


PyThreadState *PyInterpreterState_ThreadHead(PyInterpreterState *);

static void write_thread_id(int fd, PyThreadState *tstate, int is_current) ;

static void dump_traceback(int fd, PyThreadState *tstate, int write_header) ;


PyThreadState *PyThreadState_Next(PyThreadState *);

#endif