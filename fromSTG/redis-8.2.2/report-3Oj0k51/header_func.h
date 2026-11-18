#ifndef __HEADER_FUNC_H__ 
#define __HEADER_FUNC_H__
#include"header_type.h" 
static inline unsigned char sdsType(const sds s) ;


void *dictGetKey(const dictEntry *de);


unsigned short crc16(const char *buf, int len);


unsigned long LFUDecrAndReturn(robj *o);


uint8_t LFULogIncr(uint8_t value);


unsigned long LFUGetTimeInMinutes(void);


kvstoreDictMetadata *kvstoreGetDictMetadata(kvstore *kvs, int didx);


kvstoreMetadata *kvstoreGetMetadata(kvstore *kvs);

static inline int log2ceil(size_t x) ;

kvobj *dbFindByLink(redisDb *db, sds key, dictEntryLink *link);

static keyStatus expireIfNeeded(redisDb *db, robj *key, kvobj *kv, int flags);

extern struct redisServer server;
;

void touchCommand(client *c);


int hasActiveChildProcess(void);

void updateLFU(robj *val) ;


unsigned int LRU_CLOCK(void);


void notifyKeyspaceEvent(int type, const char *event, robj *key, int dbid);

kvobj *lookupKey(redisDb *db, robj *key, int flags, dictEntryLink *link) ;

int getKeySlot(sds key);


kvobj *kvobjSet(sds key, robj *val, int hasExpire);

kvobj *setExpireByLink(client *c, redisDb *db, sds key, long long when, dictEntryLink link);

void updateKeysizesHist(redisDb *db, int didx, uint32_t type, int64_t oldLen, int64_t newLen) ;


size_t getObjectLength(robj *o);

kvobj *dbAddInternal(redisDb *db, robj *key, robj **valref, dictEntryLink *link, long long expire) ;

static inline unsigned int keyHashSlot(char *key, int keylen) ;

static inline size_t sdslen(const sds s) ;


dictEntryLink kvstoreDictFindLink(kvstore *kvs, int didx, void *key, dictEntryLink *bucket);


void _serverAssertWithInfo(const client *c, const robj *o, const char *estr, const char *file, int line);

static inline kvobj *dictGetKV(const dictEntry *de) ;


void incrRefCount(robj *o);


void moduleNotifyKeyUnlink(robj *key, kvobj *kv, int dbid, int flags);


void signalDeletedKeyAsReady(redisDb *db, robj *key, int type);


void decrRefCount(robj *o);

long long getExpire(redisDb *db, sds key, kvobj *kv);

int removeExpire(redisDb *db, robj *key);


void kvstoreDictSetAtLink(kvstore *kvs, int didx, void *kv, dictEntryLink *link, int newItem);


kvobj *kvobjSetExpire(kvobj *kv, long long expire);


int kvstoreDictDelete(kvstore *kvs, int didx, const void *key);

void setKeyByLink(client *c, redisDb *db, robj *key, robj **valref, int flags, dictEntryLink *link);

kvobj *lookupKeyWriteWithLink(redisDb *db, robj *key, dictEntryLink *link) ;

static void dbSetValue(redisDb *db, robj *key, robj **valref, dictEntryLink link, int overwrite, int updateKeySizes, int keepTTL) ;

kvobj *dbAddByLink(redisDb *db, robj *key, robj **valref, dictEntryLink *link) ;


dictEntryLink kvstoreDictTwoPhaseUnlinkFind(kvstore *kvs, int didx, const void *key, int *table_index);


uint64_t hashTypeRemoveFromExpires(ebuckets *hexpires, robj *o);


long long kvobjGetExpire(const kvobj *val);


void freeObjAsync(robj *key, robj *obj, int dbid);


void kvstoreDictTwoPhaseUnlinkFree(kvstore *kvs, int didx, dictEntryLink plink, int table_index);


void _serverAssert(const char *estr, const char *file, int line);


void hashTypeAddToExpires(redisDb *db, kvobj *hashObj, uint64_t expireTime);


dictEntry *kvstoreDictAddRaw(kvstore *kvs, int didx, void *key, dictEntry **existing);

kvobj *dbFindExpires(redisDb *db, sds key);


robj *createStringObject(const char *ptr, size_t len);

int dbGenericDelete(redisDb *db, robj *key, int async, int flags) ;

void propagateDeletion(redisDb *db, robj *key, int lazy);

static void deleteKeyAndPropagate(redisDb *db, robj *keyobj, int notify_type, long long *key_mem_freed) ;


mstime_t commandTimeSnapshot(void);

int keyIsExpired(redisDb *db, sds key, kvobj *kv) ;

int confAllowsExpireDel(void) ;


uint32_t isPausedActionsWithUpdate(uint32_t action_bitmask);

void deleteExpiredKeyAndPropagate(redisDb *db, robj *keyobj) ;


sds kvobjGetKey(const kvobj *kv);


dictEntry *kvstoreDictFind(kvstore *kvs, int didx, void *key);

static kvobj *dbFindGeneric(kvstore *kvs, sds key) ;

#endif