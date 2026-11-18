#ifndef __HEADER_FUNC_H__ 
#define __HEADER_FUNC_H__
#include"header_type.h" 

void *zmalloc(size_t size);


void *zrealloc(void *ptr, size_t size);


void _serverAssert(const char *estr, const char *file, int line);

raxNode *raxNewNode(size_t children, int datafield) ;


void zfree(void *ptr);

void *raxGetData(raxNode *n) ;

void raxSetData(raxNode *n, void *data) ;

static inline int raxStackPush(raxStack *ts, void *ptr) ;

static inline size_t raxLowWalk(rax *rax, unsigned char *s, size_t len, raxNode **stopnode, raxNode ***plink, int *splitpos, raxStack *ts) ;

raxNode *raxReallocForData(raxNode *n, void *data) ;

raxNode *raxCompressNode(raxNode *n, unsigned char *s, size_t len, raxNode **child) ;

raxNode *raxAddChild(raxNode *n, unsigned char c, raxNode **childptr, raxNode ***parentlink) ;

int raxRemove(rax *rax, unsigned char *s, size_t len, void **old);

static inline void raxStackInit(raxStack *ts) ;

static inline void raxStackFree(raxStack *ts) ;

static inline void *raxStackPop(raxStack *ts) ;

raxNode **raxFindParentLink(raxNode *parent, raxNode *child) ;

raxNode *raxRemoveChild(raxNode *parent, raxNode *child) ;

static inline void *raxStackPeek(raxStack *ts) ;

#endif