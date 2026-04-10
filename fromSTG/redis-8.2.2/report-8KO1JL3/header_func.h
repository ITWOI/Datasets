#ifndef __HEADER_FUNC_H__ 
#define __HEADER_FUNC_H__
#include"header_type.h" 
static inline unsigned char sdsType(const sds s) ;


void *zmalloc(size_t size);

zskiplistNode *zslCreateNode(int level, double score, sds ele) ;


void sdsfree(sds s);


void zfree(void *ptr);


void _serverAssert(const char *estr, const char *file, int line);


int sdscmp(const sds s1, const sds s2);

int zslRandomLevel(void) ;

void zslDeleteNode(zskiplist *zsl, zskiplistNode *x, zskiplistNode **update) ;

zskiplistNode *zslInsert(zskiplist *zsl, double score, sds ele) ;

void zslFreeNode(zskiplistNode *node) ;


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


robj *createZsetListpackObject(void);

extern struct redisServer server;
;

robj *createZsetObject(void);


int dictExpand(dict *d, unsigned long size);

void zsetConvertAndExpand(robj *zobj, int encoding, unsigned long cap);


dict *dictCreate(dictType *type);

zskiplist *zslCreate(void) ;


void _serverAssertWithInfo(const client *c, const robj *o, const char *estr, const char *file, int line);


sds sdsfromlonglong(long long value);


sds sdsnewlen(const void *init, size_t initlen);


int dictAdd(dict *d, void *key, void *val);

void zzlNext(unsigned char *zl, unsigned char **eptr, unsigned char **sptr) ;


void dictRelease(dict *d);

extern dictType zsetDictType;
;

unsigned char *lpNew(size_t capacity);

unsigned char *zzlFind(unsigned char *lp, sds ele, double *score) ;

unsigned char *zzlDelete(unsigned char *zl, unsigned char *eptr) ;

unsigned char *zzlInsert(unsigned char *zl, sds ele, double score) ;


int lpSafeToAdd(unsigned char *lp, size_t add);


dictEntry *dictFind(dict *d, const void *key);


void *dictGetVal(const dictEntry *de);

zskiplistNode *zslUpdateScore(zskiplist *zsl, double curscore, sds ele, double newscore) ;


void dictSetVal(dict *d, dictEntry *de, void *val);


sds sdsdup(const sds s);


void addReplyErrorObject(client *c, robj *err);

extern struct sharedObjectsStruct shared;
;

void addReplyError(client *c, const char *err);


int getDoubleFromObjectOrReply(client *c, robj *o, double *target, const char *msg);


kvobj *lookupKeyWrite(redisDb *db, robj *key);


int checkType(client *c, robj *o, int type);


kvobj *dbAdd(redisDb *db, robj *key, robj **valref);

void zsetTypeMaybeConvert(robj *zobj, size_t size_hint) ;

robj *zsetTypeCreate(size_t size_hint, size_t val_len_hint) ;

unsigned long zsetLength(const robj *zobj) ;

int zsetAdd(robj *zobj, double score, sds ele, int in_flags, int *out_flags, double *newscore) ;


void updateKeysizesHist(redisDb *db, int didx, uint32_t type, int64_t oldLen, int64_t newLen);


int getKeySlot(sds key);


void addReplyDouble(client *c, double d);


void addReplyNull(client *c);


void addReplyLongLong(client *c, long long ll);


void signalModifiedKey(client *c, redisDb *db, robj *key);


void notifyKeyspaceEvent(int type, const char *event, robj *key, int dbid);

void zaddGenericCommand(client *c, int flags) ;

#endif