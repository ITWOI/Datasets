#include "header_func.h"
static  __attribute__((unused)) int uv__fstat (int fd, struct stat *s){
    int rc;
    rc = fstat(fd, s);
    return rc;
}
