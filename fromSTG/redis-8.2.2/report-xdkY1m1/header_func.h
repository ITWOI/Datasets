#ifndef __HEADER_FUNC_H__ 
#define __HEADER_FUNC_H__
#include"header_type.h" 
static inline unsigned char sdsType(const sds s) ;


client *createClient(connection *conn);

static size_t moduleTempClientCount = 0;
;
static client **moduleTempClients;
;
static size_t moduleTempClientMinCount = 0;
;

void _serverAssert(const char *estr, const char *file, int line);


void *zrealloc(void *ptr, size_t size);

static size_t moduleTempClientCap = 0;
;
static void freeRedisModuleAsyncRMCallPromise(RedisModuleAsyncRMCallPromise *promise) ;


void listTypeReleaseIterator(listTypeIterator *li);


void streamIteratorStop(streamIterator *si);


void zfree(void *ptr);

void autoMemoryCollect(RedisModuleCtx *ctx);

void poolAllocRelease(RedisModuleCtx *ctx) ;


void _serverLog(int level, const char *fmt, ...);

extern struct redisServer server;
;
void moduleReleaseTempClient(client *c) ;


void freeClient(client *c);

int RM_GetApi(const char *funcname, void **targetPtrPtr) ;

client *moduleAllocTempClient(void) ;

extern monotime (*getMonotonicUs)(void);
;

void decrRefCount(robj *o);

void RM_FreeCallReply(RedisModuleCallReply *reply);

void RM_CloseKey(RedisModuleKey *key);

void RM_FreeDict(RedisModuleCtx *ctx, RedisModuleDict *d);

void RM_FreeServerInfo(RedisModuleCtx *ctx, RedisModuleServerInfoData *data);

void RM_ConfigIteratorRelease(RedisModuleCtx *ctx, RedisModuleConfigIterator *iter);


ConnectionType *connectionTypeTls(void);

static void moduleInitKeyTypeSpecific(RedisModuleKey *key);

static void zsetKeyReset(RedisModuleKey *key);

static void moduleFreeKeyIterator(RedisModuleKey *key) ;

void RM_ZsetRangeStop(RedisModuleKey *kp);


void signalKeyAsReady(redisDb *db, robj *key, int type);

static void moduleCloseKey(RedisModuleKey *key) ;

int autoMemoryFreed(RedisModuleCtx *ctx, int type, void *ptr) ;


int callReplyType(CallReply *rep);


void *callReplyGetPrivateData(CallReply *rep);


int raxNext(raxIterator *it);

void moduleNotifyUserChanged(client *c) ;


listNode *listNext(listIter *iter);

void revokeClientAuthentication(client *c) ;

list *RedisModule_EventListeners;
;
void moduleCreateContext(RedisModuleCtx *out_ctx, RedisModule *module, int ctx_flags) ;

int modulePopulateClientInfoStructure(void *ci, client *client, int structver) ;

int modulePopulateReplicationInfoStructure(void *ri, int structver) ;


int selectDb(client *c, int id);

void moduleFreeContext(RedisModuleCtx *ctx) ;

static void moduleInitKey(RedisModuleKey *kp, RedisModuleCtx *ctx, robj *keyname, kvobj *kv, int mode) ;

void RedisModuleCommandDispatcher(client *c) ;


void hdr_close(struct hdr_histogram *h);


void dictInitSafeIterator(dictIterator *iter, dict *d);


dictEntry *dictNext(dictIterator *iter);

int moduleFreeCommand(struct RedisModule *module, struct redisCommand *cmd) ;


int dictDelete(dict *d, const void *key);


void sdsfree(sds s);


void dictResetIterator(dictIterator *iter);


void dictRelease(dict *d);


void *dictGetVal(const dictEntry *de);


int dictReplace(dict *d, void *key, void *val);


sds sdsdup(const sds s);

static void moduleFreeAuthenticatedClients(RedisModule *module) ;

void moduleUnregisterCommands(struct RedisModule *module) ;

int moduleOnLoad(int (*onload)(void *, void **, int), const char *path, void *handle, void **module_argv, int module_argc, int is_loadex);

void moduleUnregisterCleanup(RedisModule *module) ;

void moduleRemoveCateogires(RedisModule *module) ;

void moduleFreeModuleStructure(struct RedisModule *module) ;


void *zmalloc(size_t size);


sds sdsnew(const char *init);


void incrRefCount(robj *o);


void serverLogRaw(int level, const char *msg);

int moduleUnload(sds name, const char **errmsg, int forced_unload);

void moduleFireServerEvent(uint64_t eid, int subid, void *data) ;

dict *modules;
;

void *dictFetchValue(dict *d, const void *key);

static inline size_t sdslen(const sds s) ;

int moduleHoldsTimer(struct RedisModule *module) ;


void addReplyMapLen(client *c, long length);


void addReplyBulkCString(client *c, const char *s);


void addReplyBulkCBuffer(client *c, const void *p, size_t len);


void addReplyLongLong(client *c, long long ll);


void addReplyArrayLen(client *c, long length);


void addReplyBulk(client *c, robj *obj);


void *dictGetKey(const dictEntry *de);


void addReplyHelp(client *c, const char **help);

int moduleLoad(const char *path, void **module_argv, int module_argc, int is_loadex) ;


void addReply(client *c, robj *obj);


void addReplyError(client *c, const char *err);

int parseLoadexArguments(robj ***module_argv, int *module_argc) ;


void dictEmpty(dict *d, void (callback)(dict *));


void addReplyErrorFormat(client *c, const char *fmt, ...);

void addReplyLoadedModules(client *c) ;


void addReplySubcommandSyntaxError(client *c);

#endif