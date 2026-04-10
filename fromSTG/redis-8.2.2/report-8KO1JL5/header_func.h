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

void zslFreeNode(zskiplistNode *node) ;


double fast_float_strtod(const char *in, char **out);


unsigned char *lpGetValue(unsigned char *p, unsigned int *slen, long long *lval);

double zzlStrtod(unsigned char *vstr, unsigned int vlen) ;


unsigned long lpLength(unsigned char *lp);


unsigned char *lpNext(unsigned char *lp, unsigned char *p);


unsigned char *lpPrev(unsigned char *lp, unsigned char *p);


unsigned char *lpFirst(unsigned char *lp);


unsigned char *lpFind(unsigned char *lp, unsigned char *p, unsigned char *s, uint32_t slen, unsigned int skip);

static inline size_t sdslen(const sds s) ;

double zzlGetScore(unsigned char *sptr) ;


int double2ll(double d, long long *out);


int d2string(char *buf, size_t len, double value);


unsigned char *lpBatchAppend(unsigned char *lp, listpackEntry *entries, unsigned long len);


unsigned char *lpBatchInsert(unsigned char *lp, unsigned char *p, int where, listpackEntry *entries, unsigned int len, unsigned char **newp);

unsigned int zzlLength(unsigned char *zl) ;


void _serverPanic(const char *file, int line, const char *msg, ...);

void zsetConvertAndExpand(robj *zobj, int encoding, unsigned long cap);

unsigned long zsetLength(const robj *zobj) ;


dict *dictCreate(dictType *type);

zskiplist *zslCreate(void) ;


int dictExpand(dict *d, unsigned long size);


unsigned char *lpSeek(unsigned char *lp, long index);


void _serverAssertWithInfo(const client *c, const robj *o, const char *estr, const char *file, int line);


sds sdsfromlonglong(long long value);


sds sdsnewlen(const void *init, size_t initlen);

zskiplistNode *zslInsert(zskiplist *zsl, double score, sds ele) ;


int dictAdd(dict *d, void *key, void *val);

void zzlNext(unsigned char *zl, unsigned char **eptr, unsigned char **sptr) ;


void zfree(void *ptr);


void dictRelease(dict *d);

unsigned char *zzlInsertAt(unsigned char *zl, unsigned char *eptr, sds ele, double score) ;

extern dictType zsetDictType;
;

unsigned char *lpNew(size_t capacity);


int lpSafeToAdd(unsigned char *lp, size_t add);

void zsetConvert(robj *zobj, int encoding) ;

extern struct redisServer server;
;

dictEntry *dictUnlink(dict *d, const void *key);


void *dictGetVal(const dictEntry *de);


void dictFreeUnlinkedEntry(dict *d, dictEntry *he);

int zslDelete(zskiplist *zsl, double score, sds ele, zskiplistNode **node) ;


dictIterator *dictGetIterator(dict *d);


dictEntry *dictNext(dictIterator *iter);


void dictReleaseIterator(dictIterator *iter);


void sdsfree(sds s);


unsigned long setTypeSize(const robj *subject);

void zuiDiscardDirtyValue(zsetopval *val) ;


uint8_t intsetGet(intset *is, uint32_t pos, int64_t *value);


void *dictGetKey(const dictEntry *de);

void zzlPrev(unsigned char *zl, unsigned char **eptr, unsigned char **sptr) ;


sds sdsdup(const sds s);


int setTypeIsMemberAux(robj *set, char *str, size_t len, int64_t llval, int str_is_sds);

sds zuiSdsFromValue(zsetopval *val) ;

unsigned char *zzlFind(unsigned char *lp, sds ele, double *score) ;


dictEntry *dictFind(dict *d, const void *key);

void zuiInitIterator(zsetopsrc *op) ;

int zuiNext(zsetopsrc *op, zsetopval *val) ;

int zuiFind(zsetopsrc *op, zsetopval *val, double *score) ;

sds zuiNewSdsFromValue(zsetopval *val) ;

void zuiClearIterator(zsetopsrc *op) ;

unsigned long zuiLength(zsetopsrc *op) ;

static int zsetRemoveFromSkiplist(zset *zs, sds ele) ;

static size_t zsetDictGetMaxElementLength(dict *d, size_t *totallen) ;

static void zdiffAlgorithm1(zsetopsrc *src, long setnum, zset *dstzset, size_t *maxelelen, size_t *totelelen) ;

static void zdiffAlgorithm2(zsetopsrc *src, long setnum, zset *dstzset, size_t *maxelelen, size_t *totelelen) ;

static int zsetChooseDiffAlgorithm(zsetopsrc *src, long setnum) ;


int getLongFromObjectOrReply(client *c, robj *o, long *target, const char *msg);


void addReplyErrorFormat(client *c, const char *fmt, ...);


void addReplyErrorObject(client *c, robj *err);


void *ztrycalloc(size_t size);


void addReplyError(client *c, const char *err);


kvobj *lookupKeyRead(redisDb *db, robj *key);


int getDoubleFromObjectOrReply(client *c, robj *o, double *target, const char *msg);


int getPositiveLongFromObjectOrReply(client *c, robj *o, long *target, const char *msg);


robj *createZsetObject(void);

static inline void zunionInterAggregate(double *target, double val, int aggregate) ;


dictEntry *dictAddRaw(dict *d, void *key, dictEntry **existing);


void dictSetKey(dict *d, dictEntry *de, void *key);


void dictSetDoubleVal(dictEntry *de, double val);


void dictInitIterator(dictIterator *iter, dict *d);


double dictGetDoubleVal(const dictEntry *de);


void dictSetVal(dict *d, dictEntry *de, void *val);


void dictResetIterator(dictIterator *iter);

static void zdiff(zsetopsrc *src, long setnum, zset *dstzset, size_t *maxelelen, size_t *totelelen) ;


double *dictGetDoubleValPtr(dictEntry *de);

void zsetConvertToListpackIfNeeded(robj *zobj, size_t maxelelen, size_t totelelen) ;


void setKey(client *c, redisDb *db, robj *key, robj **ioval, int flags);


void addReplyLongLong(client *c, long long ll);


void notifyKeyspaceEvent(int type, const char *event, robj *key, int dbid);


void addReply(client *c, robj *obj);


int dbDelete(redisDb *db, robj *key);


void signalModifiedKey(client *c, redisDb *db, robj *key);


void decrRefCount(robj *o);


void addReplyArrayLen(client *c, long length);


void addReplyBulkCBuffer(client *c, const void *p, size_t len);


void addReplyDouble(client *c, double d);


void freeObjAsync(robj *key, robj *obj, int dbid);

#endif