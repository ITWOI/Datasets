#ifndef __HEADER_FUNC_H__ 
#define __HEADER_FUNC_H__
#include"header_type.h" 

sds sdscpylen(sds s, const char *t, size_t len);

static inline size_t sdslen(const sds s) ;


void sdsclear(sds s);

#endif