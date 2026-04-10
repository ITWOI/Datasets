#include "header_func.h"
#include "internal.h"
extern  __attribute__((visibility("default"))) int uv_tty_init (uv_loop_t *loop, uv_tty_t *tty, int fd, int unused){
    uv_handle_type type;
    int flags;
    int newfd;
    int r;
    int saved_flags;
    int mode;
    char path[256];
    type = uv_guess_handle(fd);
  skip:
    ;
    return 0;
}
extern  __attribute__((visibility("default"))) uv_handle_type uv_guess_handle (uv_file file){
    struct sockaddr_storage ss;
    struct stat s;
    socklen_t len;
    int type;
    if (file < 0)
        return UV_UNKNOWN_HANDLE;
    if (isatty(file))
        return UV_TTY;
    if (uv__fstat(file, &s)) {
        return UV_UNKNOWN_HANDLE;
    }
    if (((((s.st_mode)) & 61440) == (32768)))
        return UV_FILE;
    if (((((s.st_mode)) & 61440) == (8192)))
        return UV_FILE;
    if (((((s.st_mode)) & 61440) == (4096)))
        return UV_NAMED_PIPE;
    if (!((((s.st_mode)) & 61440) == (49152)))
        return UV_UNKNOWN_HANDLE;
    len = sizeof (ss);
    if (getsockname(file, (__SOCKADDR_ARG){(struct sockaddr *)&ss}, &len)) {
        return UV_UNKNOWN_HANDLE;
    }
    len = sizeof (type);
    if (getsockopt(file, 1, 3, &type, &len))
        return UV_UNKNOWN_HANDLE;
    if (type == SOCK_DGRAM)
        if (ss.ss_family == 2 || ss.ss_family == 10)
            return UV_UDP;
    return UV_UNKNOWN_HANDLE;
}
