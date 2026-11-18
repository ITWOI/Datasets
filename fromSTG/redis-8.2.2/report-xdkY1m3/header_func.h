#ifndef __HEADER_FUNC_H__ 
#define __HEADER_FUNC_H__
#include"header_type.h" 
int RM_ListPush(RedisModuleKey *key, int where, robj *ele) ;


unsigned long listTypeLength(const robj *subject);


void listTypeTryConversionAppend(robj *o, robj **argv, int start, int end, beforeConvertCB fn, void *data);

static void moduleFreeListIterator(void *data) ;

#endif