#ifndef __HEADER_FUNC_H__ 
#define __HEADER_FUNC_H__
#include"header_type.h" 

void _Py_Dealloc(PyObject *);

static inline void _Py_DECREF(PyObject *op) ;

static inline int PyType_HasFeature(PyTypeObject *type, unsigned long feature) ;


long PyLong_AsLong(PyObject *);

extern PyTypeObject PyTuple_Type;
;

int PyArg_ParseTuple(PyObject *, const char *, ...);


PyInterpreterState *PyInterpreterState_Get(void);


PyInterpreterState *PyInterpreterState_Main(void);


void PyErr_SetString(PyObject *exception, const char *string);

extern PyObject _Py_NoneStruct;
;
static int _sanity_check_python_fd_sequence(PyObject *fd_sequence) ;


const PyConfig *_PyInterpreterState_GetConfig(PyInterpreterState *interp);


int PyGC_Disable(void);


char *const *_PySequence_BytesToCharpArray(PyObject *self);


PyObject *PySequence_Fast(PyObject *o, const char *m);


PyObject *PyTuple_New(Py_ssize_t size);


int PyUnicode_FSConverter(PyObject *, void *);


char *PyBytes_AsString(PyObject *);


Py_ssize_t PySequence_Size(PyObject *o);


void *PyMem_RawMalloc(size_t size);


PyObject *PySequence_GetItem(PyObject *o, Py_ssize_t i);


int _Py_Gid_Converter(PyObject *, gid_t *);


int _Py_Uid_Converter(PyObject *, uid_t *);


void PyOS_BeforeFork(void);


int PyObject_IsTrue(PyObject *);


void PyErr_Clear(void);


PyObject *PyImport_ImportModule(const char *name);


PyObject *PyObject_GetAttrString(PyObject *, const char *);

static pid_t do_fork_exec(char *const exec_array[], char *const argv[], char *const envp[], const char *cwd, int p2cread, int p2cwrite, int c2pread, int c2pwrite, int errread, int errwrite, int errpipe_read, int errpipe_write, int close_fds, int restore_signals, int call_setsid, int call_setgid, gid_t gid, int call_setgroups, size_t groups_size, const gid_t *groups, int call_setuid, uid_t uid, int child_umask, const void *child_sigmask, PyObject *py_fds_to_keep, PyObject *preexec_fn, PyObject *preexec_fn_args_tuple) ;


PyObject *PyErr_SetFromErrno(PyObject *);

static inline void _Py_XDECREF(PyObject *op) ;


PyObject *PyLong_FromLong(long);

#endif