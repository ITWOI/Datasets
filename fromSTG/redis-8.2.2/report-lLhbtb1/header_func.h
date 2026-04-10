#ifndef __HEADER_FUNC_H__ 
#define __HEADER_FUNC_H__
#include"header_type.h" 
static int dictDefaultCompare(dictCmpCache *cache, const void *key1, const void *key2);


void *zmalloc(size_t size);


void _serverAssert(const char *estr, const char *file, int line);

static inline void *decodeMaskedPtr(const dictEntry *de) ;

static inline int entryIsNormal(const dictEntry *de) ;

static signed char _dictNextExp(unsigned long size);


void *ztrycalloc(size_t size);


void *zcalloc(size_t size);


void zfree(void *ptr);

static void _dictReset(dict *d, int htidx) ;

int dictRehash(dict *d, int n);

int _dictResize(dict *d, unsigned long size, int *malloc_failed) ;

int _dictExpand(dict *d, unsigned long size, int *malloc_failed) ;

dictEntry *dictGetNext(const dictEntry *de);

static inline uint64_t dictHashKey(dict *d, const void *key, int isStoredKey) ;

static inline int entryIsKey(const dictEntry *de) ;

static inline dictEntry *encodeMaskedPtr(const void *ptr, unsigned int bits) ;

static inline dictEntry *createEntryNoValue(void *key, dictEntry *next) ;

static inline int entryIsNoValue(const dictEntry *de) ;

static void dictSetNext(dictEntry *de, dictEntry *next);

void *dictGetKey(const dictEntry *de);

static dictResizeEnable dict_can_resize = DICT_RESIZE_ENABLE;
;
static unsigned int dict_force_resize_ratio = 4;
;
static void rehashEntriesInBucketAtIndex(dict *d, uint64_t idx) ;

static int dictCheckRehashingCompleted(dict *d) ;

dictEntryLink dictFindLinkForInsert(dict *d, const void *key, dictEntry **existing);

static dictEntry *dictInsertKeyAtLink(dict *d, void *key, dictEntryLink link);

dictEntry *dictAddRaw(dict *d, void *key, dictEntry **existing) ;

void dictSetVal(dict *d, dictEntry *de, void *val);

void *dictGetVal(const dictEntry *de);

static inline int entryHasValue(const dictEntry *de) ;

static inline dictEntryNoValue *decodeEntryNoValue(const dictEntry *de) ;

int dictExpand(dict *d, unsigned long size) ;

static int dictTypeResizeAllowed(dict *d, size_t size) ;

int dictExpandIfNeeded(dict *d) ;

int _dictBucketRehash(dict *d, uint64_t idx) ;

static void _dictRehashStepIfNeeded(dict *d, uint64_t visitedIdx) ;

static int _dictExpandIfNeeded(dict *d) ;

static inline keyCmpFunc dictGetCmpFunc(dict *d) ;

#endif