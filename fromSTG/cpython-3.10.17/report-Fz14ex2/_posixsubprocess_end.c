#include "header_func.h"
static int _sanity_check_python_fd_sequence (PyObject *fd_sequence){
    Py_ssize_t seq_idx;
    long prev_fd = -1;
    for (seq_idx = 0; seq_idx < (((PyVarObject *)((((void)(0)) , (PyTupleObject *)(fd_sequence))))->ob_size); ++seq_idx) {
        PyObject *py_fd = ((((void)(0)) , (PyTupleObject *)(fd_sequence))->ob_item[seq_idx]);
        long iter_fd;
        if (!PyType_HasFeature((((PyObject *)(py_fd))->ob_type), (1UL << 24))) {
            return 1;
        }
        iter_fd = PyLong_AsLong(py_fd);
        if (iter_fd < 0 || iter_fd <= prev_fd || iter_fd > 2147483647) {
            return 1;
        }
        prev_fd = iter_fd;
    }
    return 0;
}
static  __attribute__((noinline)) pid_t do_fork_exec (char *const exec_array[], char *const argv[], char *const envp[], const char *cwd, int p2cread, int p2cwrite, int c2pread, int c2pwrite, int errread, int errwrite, int errpipe_read, int errpipe_write, int close_fds, int restore_signals, int call_setsid, int call_setgid, gid_t gid, int call_setgroups, size_t groups_size, const gid_t *groups, int call_setuid, uid_t uid, int child_umask, const void *child_sigmask, PyObject *py_fds_to_keep, PyObject *preexec_fn, PyObject *preexec_fn_args_tuple){
    pid_t pid;
    if (child_sigmask) {
        ;
        pid = vfork();
        if (pid == -1) {
            pid = fork();
        }
    } else {
        pid = fork();
    }
    if (pid != 0) {
        return pid;
    }
    ;
    return 0;
}
static PyObject * subprocess_fork_exec (PyObject *module, PyObject *args){
    PyObject *gc_module = ((void *)0);
    PyObject *executable_list, *py_fds_to_keep;
    PyObject *env_list, *preexec_fn;
    PyObject *process_args, *converted_args = ((void *)0), *fast_args = ((void *)0);
    PyObject *preexec_fn_args_tuple = ((void *)0);
    PyObject *groups_list;
    PyObject *uid_object, *gid_object;
    int p2cread, p2cwrite, c2pread, c2pwrite, errread, errwrite;
    int errpipe_read, errpipe_write, close_fds, restore_signals;
    int call_setsid;
    int call_setgid = 0, call_setgroups = 0, call_setuid = 0;
    uid_t uid;
    gid_t gid, *groups = ((void *)0);
    int child_umask;
    PyObject *cwd_obj, *cwd_obj2 = ((void *)0);
    const char *cwd;
    pid_t pid = -1;
    int need_to_reenable_gc = 0;
    char *const *exec_array, *const *argv = ((void *)0), *const *envp = ((void *)0);
    Py_ssize_t arg_num, num_groups = 0;
    int need_after_fork = 0;
    int saved_errno = 0;
    if (!PyArg_ParseTuple(args, "OOpO!OOiiiiiiiiiiOOOiO:fork_exec", &process_args, &executable_list, &close_fds, &PyTuple_Type, &py_fds_to_keep, &cwd_obj, &env_list, &p2cread, &p2cwrite, &c2pread, &c2pwrite, &errread, &errwrite, &errpipe_read, &errpipe_write, &restore_signals, &call_setsid, &gid_object, &groups_list, &uid_object, &child_umask, &preexec_fn))
        return ((void *)0);
    if ((preexec_fn != (&_Py_NoneStruct)) && (PyInterpreterState_Get() != PyInterpreterState_Main())) {
        ;
        return ((void *)0);
    }
    if (close_fds && errpipe_write < 3) {
        ;
        return ((void *)0);
    }
    if (_sanity_check_python_fd_sequence(py_fds_to_keep)) {
        ;
        return ((void *)0);
    }
    PyInterpreterState *interp = PyInterpreterState_Get();
    const PyConfig *config = _PyInterpreterState_GetConfig(interp);
    if (config->_isolated_interpreter) {
        ;
        return ((void *)0);
    }
    if (preexec_fn != (&_Py_NoneStruct)) {
        need_to_reenable_gc = PyGC_Disable();
    }
    exec_array = _PySequence_BytesToCharpArray(executable_list);
    if (!exec_array)
        goto cleanup;
    if (process_args != (&_Py_NoneStruct)) {
        Py_ssize_t num_args;
        fast_args = PySequence_Fast(process_args, "argv must be a tuple");
        if (fast_args == ((void *)0))
            goto cleanup;
        num_args = (PyType_HasFeature((((PyObject *)(fast_args))->ob_type), (1UL << 25)) ? (((PyVarObject *)((((void)(0)) , (PyListObject *)(fast_args))))->ob_size) : (((PyVarObject *)((((void)(0)) , (PyTupleObject *)(fast_args))))->ob_size));
        converted_args = PyTuple_New(num_args);
        if (converted_args == ((void *)0))
            goto cleanup;
        for (arg_num = 0; arg_num < num_args; ++arg_num) {
            PyObject *borrowed_arg, *converted_arg;
            if ((PyType_HasFeature((((PyObject *)(fast_args))->ob_type), (1UL << 25)) ? (((PyVarObject *)((((void)(0)) , (PyListObject *)(fast_args))))->ob_size) : (((PyVarObject *)((((void)(0)) , (PyTupleObject *)(fast_args))))->ob_size)) != num_args) {
                ;
                goto cleanup;
            }
            borrowed_arg = (PyType_HasFeature((((PyObject *)(fast_args))->ob_type), (1UL << 25)) ? ((((void)(0)) , (PyListObject *)(fast_args))->ob_item[arg_num]) : ((((void)(0)) , (PyTupleObject *)(fast_args))->ob_item[arg_num]));
            if (PyUnicode_FSConverter(borrowed_arg, &converted_arg) == 0)
                goto cleanup;
            ((void)((((void)(0)) , (PyTupleObject *)(converted_args))->ob_item[arg_num] = converted_arg));
        }
        argv = _PySequence_BytesToCharpArray(converted_args);
        do {
            PyObject *_py_tmp = ((PyObject *)(converted_args));
            if (_py_tmp != ((void *)0)) {
                (converted_args) = ((void *)0);
                _Py_DECREF(((PyObject *)(_py_tmp)));
            }
        } while (0);
        do {
            PyObject *_py_tmp = ((PyObject *)(fast_args));
            if (_py_tmp != ((void *)0)) {
                (fast_args) = ((void *)0);
                _Py_DECREF(((PyObject *)(_py_tmp)));
            }
        } while (0);
        if (!argv)
            goto cleanup;
    }
    if (env_list != (&_Py_NoneStruct)) {
        envp = _PySequence_BytesToCharpArray(env_list);
        if (!envp)
            goto cleanup;
    }
    if (cwd_obj != (&_Py_NoneStruct)) {
        if (PyUnicode_FSConverter(cwd_obj, &cwd_obj2) == 0)
            goto cleanup;
        cwd = PyBytes_AsString(cwd_obj2);
    } else {
        cwd = ((void *)0);
    }
    if (groups_list != (&_Py_NoneStruct)) {
        Py_ssize_t i;
        gid_t gid;
        if (!PyType_HasFeature((((PyObject *)(groups_list))->ob_type), (1UL << 25))) {
            ;
            goto cleanup;
        }
        num_groups = PySequence_Size(groups_list);
        if (num_groups < 0)
            goto cleanup;
        if (num_groups > 65536) {
            ;
            goto cleanup;
        }
        if ((groups = PyMem_RawMalloc(num_groups * sizeof(gid_t))) == ((void *)0)) {
            ;
            goto cleanup;
        }
        for (i = 0; i < num_groups; i++) {
            PyObject *elem;
            elem = PySequence_GetItem(groups_list, i);
            if (!elem)
                goto cleanup;
            if (!PyType_HasFeature((((PyObject *)(elem))->ob_type), (1UL << 24))) {
                ;
                _Py_DECREF(((PyObject *)(elem)));
                goto cleanup;
            } else {
                if (!_Py_Gid_Converter(elem, &gid)) {
                    _Py_DECREF(((PyObject *)(elem)));
                    goto cleanup;
                }
                groups[i] = gid;
            }
            _Py_DECREF(((PyObject *)(elem)));
        }
        call_setgroups = 1;
    }
    if (gid_object != (&_Py_NoneStruct)) {
        if (!_Py_Gid_Converter(gid_object, &gid))
            goto cleanup;
        call_setgid = 1;
    }
    if (uid_object != (&_Py_NoneStruct)) {
        if (!_Py_Uid_Converter(uid_object, &uid))
            goto cleanup;
        call_setuid = 1;
    }
    if (preexec_fn != (&_Py_NoneStruct)) {
        preexec_fn_args_tuple = PyTuple_New(0);
        if (!preexec_fn_args_tuple)
            goto cleanup;
        need_after_fork = 1;
    }
    const void *old_sigmask = ((void *)0);
    sigset_t old_sigs;
    int allow_vfork;
    if (preexec_fn == (&_Py_NoneStruct)) {
        allow_vfork = 1;
        PyObject *subprocess_module = PyImport_ImportModule("subprocess");
        if (subprocess_module != ((void *)0)) {
            PyObject *allow_vfork_obj = PyObject_GetAttrString(subprocess_module, "_USE_VFORK");
            _Py_DECREF(((PyObject *)(subprocess_module)));
            if (allow_vfork_obj != ((void *)0)) {
                ;
                _Py_DECREF(((PyObject *)(allow_vfork_obj)));
                if (allow_vfork < 0) {
                    ;
                    allow_vfork = 1;
                }
            } else {
                ;
            }
        } else {
            ;
        }
    } else {
        allow_vfork = 0;
    }
    if (allow_vfork && !call_setuid && !call_setgid && !call_setgroups) {
        sigset_t all_sigs;
        if ((saved_errno = pthread_sigmask(0, &all_sigs, &old_sigs))) {
            goto cleanup;
        }
        old_sigmask = &old_sigs;
    }
    pid = do_fork_exec(exec_array, argv, envp, cwd, p2cread, p2cwrite, c2pread, c2pwrite, errread, errwrite, errpipe_read, errpipe_write, close_fds, restore_signals, call_setsid, call_setgid, gid, call_setgroups, num_groups, groups, call_setuid, uid, child_umask, old_sigmask, py_fds_to_keep, preexec_fn, preexec_fn_args_tuple);
    if (pid == -1) {
        saved_errno = (*__errno_location());
    }
    ;
  cleanup:
    if (saved_errno != 0) {
        (*__errno_location()) = saved_errno;
    }
    _Py_XDECREF(((PyObject *)(preexec_fn_args_tuple)));
    _Py_XDECREF(((PyObject *)(cwd_obj2)));
    _Py_XDECREF(((PyObject *)(converted_args)));
    _Py_XDECREF(((PyObject *)(fast_args)));
    _Py_XDECREF(((PyObject *)(gc_module)));
    return pid == -1 ? ((void *)0) : PyLong_FromLong(pid);
}
