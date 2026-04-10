#ifndef __HEADER_FUNC_H__ 
#define __HEADER_FUNC_H__
#include"header_type.h" 
static struct clusterManager cluster_manager;
;

void *zcalloc(size_t size);


hisds hi_sdsdup(const hisds s);


void *dictGetVal(const dictEntry *de);


hisds hi_sdsempty(void);


hisds hi_sdscat(hisds s, const char *t);


void hi_sdsfree(hisds s);


int dictReplace(dict *d, void *key, void *val);


void dictInitIterator(dictIterator *iter, dict *d);


dictEntry *dictNext(dictIterator *iter);


void listRewind(list *list, listIter *li);


listNode *listNext(listIter *iter);


void dictResetIterator(dictIterator *iter);


void dictRelease(dict *d);

static uint64_t dictSdsHash(const void *key) ;

static int dictSdsKeyCompare(dictCmpCache *cache, const void *key1, const void *key2) ;

static void dictSdsDestructor(dict *d, void *val) ;

static dictType clusterManagerDictType = {dictSdsHash, ((void *)0), ((void *)0), dictSdsKeyCompare, ((void *)0), dictSdsDestructor, ((void *)0)};
;

dict *dictCreate(dictType *type);


dictEntry *dictFind(dict *d, const void *key);


hisds hi_sdscatsds(hisds s, const hisds t);


hisds hi_sdsnew(const char *init);


void *dictGetKey(const dictEntry *de);

static inline size_t hi_sdslen(const hisds s) ;

static int clusterManagerGetAntiAffinityScore(clusterManagerNodeArray *ipnodes, int ip_count, clusterManagerNode ***offending, int *offending_len) ;


void zfree(void *ptr);

#endif