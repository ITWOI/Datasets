#include "header_func.h"
static PyObject * os_link_impl (PyObject *module, path_t *src, path_t *dst, int src_dir_fd, int dst_dir_fd, int follow_symlinks){
    int result;
    int linkat_unavailable = 0;
    if ((src->narrow && dst->wide) || (src->wide && dst->narrow)) {
        ;
        return ((void *)0);
    }
    if (PySys_Audit("os.link", "OOii", src->object, dst->object, src_dir_fd == (int)-100 ? -1 : src_dir_fd, dst_dir_fd == (int)-100 ? -1 : dst_dir_fd) < 0) {
        return ((void *)0);
    }
    {
        PyThreadState *_save;
        _save = PyEval_SaveThread();
        if ((src_dir_fd != (int)-100) || (dst_dir_fd != (int)-100) || (!follow_symlinks)) {
            if (1) {
                result = linkat(src_dir_fd, src->narrow, dst_dir_fd, dst->narrow, follow_symlinks ? 1024 : 0);
            }
        } else
            result = link(src->narrow, dst->narrow);
        PyEval_RestoreThread(_save);
    }
    ;
    return _Py_NewRef(((PyObject *)((&_Py_NoneStruct))));
}
