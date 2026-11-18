#ifndef __HEADER_FUNC_H__ 
#define __HEADER_FUNC_H__
#include"header_type.h" 

void *zmalloc(size_t size);


void *redisCommand(redisContext *c, const char *format, ...);


size_t redis_strlcpy(char *dst, const char *src, size_t dsize);

static int clusterManagerAddSlots(clusterManagerNode *node, char **err) ;

#endif