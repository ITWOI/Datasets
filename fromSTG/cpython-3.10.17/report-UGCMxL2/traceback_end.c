#include "header_func.h"
#include "object.h"
static void dump_frame (int fd, PyFrameObject *frame){
    PyCodeObject *code = PyFrame_GetCode(frame);
    int lineno;
    _Py_DECREF(((PyObject *)(code)));
}
static void dump_traceback (int fd, PyThreadState *tstate, int write_header){
    PyFrameObject *frame;
    unsigned int depth;
    frame = tstate->frame;
    if (frame == ((void *)0)) {
        ;
        return;
    }
    depth = 0;
    while (1)
        {
            if (100 <= depth) {
                ;
                break;
            }
            if (!_Py_IS_TYPE(((const PyObject *)(frame)), &PyFrame_Type)) {
                break;
            }
            dump_frame(fd, frame);
            PyFrameObject *back = frame->f_back;
            if (back == ((void *)0)) {
                break;
            }
            frame = back;
            depth++;
        }
}
static void write_thread_id (int fd, PyThreadState *tstate, int is_current){
    ;
    _Py_DumpHexadecimal(fd, tstate->thread_id, sizeof(unsigned long) * 2);
}
extern const char * _Py_DumpTracebackThreads (int fd, PyInterpreterState *interp, PyThreadState *current_tstate){
    PyThreadState *tstate;
    unsigned int nthreads;
    if (current_tstate == ((void *)0)) {
        current_tstate = PyGILState_GetThisThreadState();
    }
    if (interp == ((void *)0)) {
        if (current_tstate == ((void *)0)) {
            interp = _PyGILState_GetInterpreterStateUnsafe();
            if (interp == ((void *)0)) {
                return "unable to get the interpreter state";
            }
        } else {
            interp = current_tstate->interp;
        }
    }
    ;
    tstate = PyInterpreterState_ThreadHead(interp);
    if (tstate == ((void *)0))
        return "unable to get the thread head state";
    tstate = PyInterpreterState_ThreadHead(interp);
    nthreads = 0;
    do {
        ;
        if (nthreads >= 100) {
            ;
            break;
        }
        write_thread_id(fd, tstate, tstate == current_tstate);
        dump_traceback(fd, tstate, 0);
        tstate = PyThreadState_Next(tstate);
        nthreads++;
    } while (tstate != ((void *)0));
    return ((void *)0);
}
