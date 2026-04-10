#ifndef __HEADER_FUNC_H__ 
#define __HEADER_FUNC_H__
#include"header_type.h" 

mstrFlags *mstrFlagsRef(mstr s);


uint64_t dictSdsHash(const void *key);


int dictSdsMstrKeyCompare(dictCmpCache *cache, const void *sdsLookup, const void *mstrStored);

static void dictHfieldDestructor(dict *d, void *field);


void dictSdsDestructor(dict *d, void *val);

static size_t hashDictWithExpireMetadataBytes(dict *d);

static uint64_t dictMstrHash(const void *key);

static int dictHfieldKeyCompare(dictCmpCache *cache, const void *key1, const void *key2);

static void hashDictWithExpireOnRelease(dict *d);

dictType mstrHashDictTypeWithHFE = {dictSdsHash, ((void *)0), ((void *)0), dictSdsMstrKeyCompare, dictHfieldDestructor, dictSdsDestructor, .storedHashFunction = dictMstrHash, .storedKeyCompare = dictHfieldKeyCompare, .dictMetadataBytes = hashDictWithExpireMetadataBytes, .onDictRelease = hashDictWithExpireOnRelease};
;

void _serverAssert(const char *estr, const char *file, int line);


mstime_t commandTimeSnapshot(void);


unsigned char *lpSeek(unsigned char *lp, long index);


int lpGetIntegerValue(unsigned char *p, long long *lval);


unsigned char *lpFirst(unsigned char *lp);


sds kvobjGetKey(const kvobj *kv);


unsigned char *lpGet(unsigned char *p, int64_t *count, unsigned char *intbuf);


unsigned char *lpNext(unsigned char *lp, unsigned char *p);

static void propagateHashFieldDeletion(redisDb *db, sds key, char *field, size_t fieldLen);

extern struct redisServer server;
;

unsigned char *lpDeleteRange(unsigned char *lp, long index, unsigned long num);


void updateKeysizesHist(redisDb *db, int didx, uint32_t type, int64_t oldLen, int64_t newLen);


int getKeySlot(sds key);


unsigned long lpLength(unsigned char *lp);

uint64_t hashTypeGetMinExpire(robj *o, int accurate);


void _serverPanic(const char *file, int line, const char *msg, ...);

static uint64_t listpackExExpireDryRun(const robj *o) ;

static inline int isDictWithMetaHFE(dict *d) ;


uint64_t ebExpireDryRun(ebuckets eb, EbucketsType *type, uint64_t now);

static ExpireMeta *hfieldGetExpireMeta(const eItem field);

EbucketsType hashFieldExpireBucketsType = {.onDeleteItem = ((void *)0), .getExpireMeta = hfieldGetExpireMeta, .itemsAddrAreOdd = 1};
;

void *zmalloc(size_t size);


dictIterator *dictGetIterator(dict *d);

int hashTypeIsExpired(const robj *o, uint64_t expireAt) ;


dictEntry *dictNext(dictIterator *iter);

uint64_t hfieldGetExpireTime(hfield field);


void *dictGetKey(const dictEntry *de);

unsigned char *hashTypeListpackGetLp(robj *o) ;

static inline size_t hfieldlen(hfield field) ;

static inline size_t sdslen(const sds s) ;


void lpRandomPair(unsigned char *lp, unsigned long total_count, listpackEntry *key, listpackEntry *val, int tuple_len);


dictEntry *dictGetFairRandomKey(dict *d);


void *dictGetVal(const dictEntry *de);

void listpackExExpire(redisDb *db, kvobj *kv, ExpireInfo *info) ;

static ExpireAction onFieldExpire(eItem item, void *ctx);


void ebExpire(ebuckets *eb, EbucketsType *type, ExpireInfo *info);


void notifyKeyspaceEvent(int type, const char *event, robj *key, int dbid);


int ebRemove(ebuckets *eb, EbucketsType *type, eItem item);

unsigned long hashTypeLength(const robj *o, int subtractExpiredFields) ;


int dbDelete(redisDb *db, robj *key);


int ebAdd(ebuckets *eb, EbucketsType *type, eItem item, uint64_t expireTime);


void signalModifiedKey(client *c, redisDb *db, robj *key);


void decrRefCount(robj *o);


robj *createStringObject(const char *ptr, size_t len);


uint32_t isPausedActionsWithUpdate(uint32_t action_bitmask);

static uint64_t hashTypeExpire(kvobj *o, ExpireCtx *expireCtx, int updateGlobalHFE) ;

static inline uint64_t ebGetMetaExpTime(ExpireMeta *expMeta) ;

static uint64_t listpackExGetMinExpire(robj *o) ;


uint64_t ebGetNextTimeToExpire(ebuckets eb, EbucketsType *type);

void hashTypeCurrentFromListpack(hashTypeIterator *hi, int what, unsigned char **vstr, unsigned int *vlen, long long *vll, uint64_t *expireTime) ;


void addReplyBulkCBuffer(client *c, const void *p, size_t len);


void addReplyBulkLongLong(client *c, long long ll);

void hashTypeCurrentFromHashTable(hashTypeIterator *hi, int what, char **str, size_t *len, uint64_t *expireTime) ;


kvobj *lookupKeyReadOrReply(client *c, robj *key, robj *reply);


int checkType(client *c, robj *o, int type);

extern struct sharedObjectsStruct shared;
;
static int hashTypeExpireIfNeeded(redisDb *db, kvobj *o) ;


void addReply(client *c, robj *obj);


void addReplyArrayLen(client *c, long length);


void lpRandomPairs(unsigned char *lp, unsigned int count, listpackEntry *keys, listpackEntry *vals, int tuple_len);

static void hrandfieldReplyWithListpack(client *c, unsigned int count, listpackEntry *keys, listpackEntry *vals) ;


void zfree(void *ptr);

int hashTypeNext(hashTypeIterator *hi, int skipExpiredFields) ;

static void addHashIteratorCursorToReply(client *c, hashTypeIterator *hi, int what) ;

void hashTypeReleaseIterator(hashTypeIterator *hi) ;

hashTypeIterator *hashTypeInitIterator(robj *subject) ;


unsigned int lpRandomPairsUnique(unsigned char *lp, unsigned int count, listpackEntry *keys, listpackEntry *vals, int tuple_len);


void dictInitIterator(dictIterator *iter, dict *d);


void dictResetIterator(dictIterator *iter);


int dictExpand(dict *d, unsigned long size);


int dictAdd(dict *d, void *key, void *val);


void dictRelease(dict *d);


uint64_t dictPtrHash(const void *key);


dict *dictCreate(dictType *type);


int getRangeLongFromObjectOrReply(client *c, robj *o, long min, long max, long *target, const char *msg);


void addReplyErrorObject(client *c, robj *err);


void addReplyError(client *c, const char *err);

void hrandfieldWithCountCommand(client *c, long l, int withvalues) ;

void hashTypeRandomElement(robj *hashobj, unsigned long hashsize, CommonEntry *key, CommonEntry *val) ;

static inline int mstrIsMetaAttached(mstr s) ;

static inline int mstrGetFlag(mstr s, int flagIdx) ;

int hfieldIsExpireAttached(hfield field) ;

mstrKind mstrFieldKind = {.name = "hField", .metaSize[HFIELD_META_EXPIRE] = sizeof(ExpireMeta)};
;

void *mstrMetaRef(mstr s, struct mstrKind *kind, int flagIdx);

#endif