#ifndef __HEADER_FUNC_H__ 
#define __HEADER_FUNC_H__
#include"header_type.h" 
static inline unsigned char sdsType(const sds s) ;


void *zmalloc(size_t size);

zskiplistNode *zslCreateNode(int level, double score, sds ele) ;


void _serverAssert(const char *estr, const char *file, int line);


int sdscmp(const sds s1, const sds s2);

int zslRandomLevel(void) ;

void zslDeleteNode(zskiplist *zsl, zskiplistNode *x, zskiplistNode **update) ;

zskiplistNode *zslInsert(zskiplist *zsl, double score, sds ele) ;


double fast_float_strtod(const char *in, char **out);


unsigned char *lpGetValue(unsigned char *p, unsigned int *slen, long long *lval);

double zzlStrtod(unsigned char *vstr, unsigned int vlen) ;


int ll2string(char *s, size_t len, long long value);


unsigned long lpLength(unsigned char *lp);


unsigned char *lpNext(unsigned char *lp, unsigned char *p);


unsigned char *lpFirst(unsigned char *lp);


unsigned char *lpFind(unsigned char *lp, unsigned char *p, unsigned char *s, uint32_t slen, unsigned int skip);

static inline size_t sdslen(const sds s) ;

double zzlGetScore(unsigned char *sptr) ;


unsigned char *lpDeleteRangeWithEntry(unsigned char *lp, unsigned char **p, unsigned long num);


int double2ll(double d, long long *out);


int d2string(char *buf, size_t len, double value);


unsigned char *lpBatchAppend(unsigned char *lp, listpackEntry *entries, unsigned long len);


unsigned char *lpBatchInsert(unsigned char *lp, unsigned char *p, int where, listpackEntry *entries, unsigned int len, unsigned char **newp);


unsigned char *lpSeek(unsigned char *lp, long index);

unsigned char *zzlInsertAt(unsigned char *zl, unsigned char *eptr, sds ele, double score) ;

int zzlCompareElements(unsigned char *eptr, unsigned char *cstr, unsigned int clen) ;

unsigned int zzlLength(unsigned char *zl) ;


void _serverPanic(const char *file, int line, const char *msg, ...);


dict *dictCreate(dictType *type);

zskiplist *zslCreate(void) ;


int dictExpand(dict *d, unsigned long size);


void _serverAssertWithInfo(const client *c, const robj *o, const char *estr, const char *file, int line);


sds sdsfromlonglong(long long value);


sds sdsnewlen(const void *init, size_t initlen);


int dictAdd(dict *d, void *key, void *val);

void zzlNext(unsigned char *zl, unsigned char **eptr, unsigned char **sptr) ;


void zfree(void *ptr);


void dictRelease(dict *d);

void zslFreeNode(zskiplistNode *node) ;

extern dictType zsetDictType;
;

unsigned char *lpNew(size_t capacity);

unsigned char *zzlFind(unsigned char *lp, sds ele, double *score) ;

unsigned char *zzlDelete(unsigned char *zl, unsigned char *eptr) ;

unsigned char *zzlInsert(unsigned char *zl, sds ele, double score) ;


int lpSafeToAdd(unsigned char *lp, size_t add);

void zsetConvertAndExpand(robj *zobj, int encoding, unsigned long cap) ;

extern struct redisServer server;
;

dictEntry *dictFind(dict *d, const void *key);


void *dictGetVal(const dictEntry *de);

zskiplistNode *zslUpdateScore(zskiplist *zsl, double curscore, sds ele, double newscore) ;


void dictSetVal(dict *d, dictEntry *de, void *val);


sds sdsdup(const sds s);

int zsetAdd(robj *zobj, double score, sds ele, int in_flags, int *out_flags, double *newscore) ;

#endif