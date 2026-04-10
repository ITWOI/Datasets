#ifndef __HEADER_FUNC_H__ 
#define __HEADER_FUNC_H__
#include"header_type.h" 
static inline unsigned char sdsType(const sds s) ;


void _serverAssert(const char *estr, const char *file, int line);

static inline size_t sdslen(const sds s) ;

kvobj *kvobjSet(sds key, robj *val, int hasExpire);

sds kvobjGetKey(const kvobj *kv) ;

static kvobj *kvobjCreateEmbedString(const char *val_ptr, size_t val_len, const sds key, int hasExpire) ;

kvobj *kvobjCreate(int type, const sds key, void *ptr, int hasExpire) ;


sds sdsnewlen(const void *init, size_t initlen);

void decrRefCount(robj *o);


sds sdsdup(const sds s);


void _serverPanic(const char *file, int line, const char *msg, ...);

#endif