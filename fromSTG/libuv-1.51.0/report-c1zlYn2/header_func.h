#ifndef __HEADER_FUNC_H__ 
#define __HEADER_FUNC_H__
#include"header_type.h" 
uv_handle_type uv_guess_handle(uv_file file);

static int uv__fstat(int fd, struct stat *s) ;

#endif