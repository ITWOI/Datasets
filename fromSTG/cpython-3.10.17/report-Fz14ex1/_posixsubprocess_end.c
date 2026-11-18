#include "header_func.h"
static  __attribute__((noinline)) pid_t do_fork_exec (char *const exec_array[], char *const argv[], char *const envp[], const char *cwd, int p2cread, int p2cwrite, int c2pread, int c2pwrite, int errread, int errwrite, int errpipe_read, int errpipe_write, int close_fds, int restore_signals, int call_setsid, int call_setgid, gid_t gid, int call_setgroups, size_t groups_size, const gid_t *groups, int call_setuid, uid_t uid, int child_umask, const void *child_sigmask, PyObject *py_fds_to_keep, PyObject *preexec_fn, PyObject *preexec_fn_args_tuple){
    pid_t pid;
    if (child_sigmask) {
        ;
        pid = vfork();
    } else {
        ;
    }
    ;
    return 0;
}
