#ifndef __HEADER_FUNC_H__ 
#define __HEADER_FUNC_H__
#include"header_type.h" 
static inline unsigned char sdsType(const sds s) ;


void _serverAssert(const char *estr, const char *file, int line);


int ll2string(char *s, size_t len, long long value);

static inline size_t sdslen(const sds s) ;


int getLongFromObjectOrReply(client *c, robj *o, long *target, const char *msg);


void addReplyError(client *c, const char *err);


int getLongLongFromObjectOrReply(client *c, robj *o, long long *target, const char *msg);


void addReplyErrorObject(client *c, robj *err);


kvobj *lookupKeyRead(redisDb *db, robj *key);


int checkType(client *c, robj *o, int type);

unsigned char *getObjectReadOnlyString(robj *o, long *len, char *llbuf) ;

#endif