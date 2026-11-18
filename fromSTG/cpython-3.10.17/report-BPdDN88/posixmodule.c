static PyObject * os_symlink_impl (PyObject *module, path_t *src, path_t *dst, int target_is_directory, int dir_fd){
    int result;
    int symlinkat_unavailable = 0;
    if (PySys_Audit("os.symlink", "OOi", src->object, dst->object, dir_fd == (int)-100 ? -1 : dir_fd) < 0) {
        return ((void *)0);
    }
    if ((src->narrow && dst->wide) || (src->wide && dst->narrow)) {
        ;
        return ((void *)0);
    }
    {
        PyThreadState *_save;
        _save = PyEval_SaveThread();
        if (dir_fd != (int)-100) {
            if (1) {
                result = symlinkat(src->narrow, dir_fd, dst->narrow);
            } else {
                symlinkat_unavailable = 1;
            }
        } else
            result = symlink(src->narrow, dst->narrow);
        PyEval_RestoreThread(_save);
    }
    ;
    return _Py_NewRef(((PyObject *)((&_Py_NoneStruct))));
}


