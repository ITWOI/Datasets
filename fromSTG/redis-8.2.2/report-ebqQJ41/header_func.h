#ifndef __HEADER_FUNC_H__ 
#define __HEADER_FUNC_H__
#include"header_type.h" 
static inline unsigned char sdsType(const sds s) ;

static inline int connAddr(connection *conn, char *ip, size_t ip_len, int *port, int remote) ;


ConnectionType *connectionTypeTls(void);

extern struct redisServer server;
;

ConnectionType *connectionTypeTcp(void);

static inline int connAddrPeerName(connection *conn, char *ip, size_t ip_len, int *port) ;

static inline int formatAddr(char *buf, size_t buf_len, char *ip, int port) ;


void bioCreateCloseJob(int fd, int need_fsync, int need_reclaim_cache);


void _serverAssert(const char *estr, const char *file, int line);

void resetReplicationBuffer(void);


list *listCreate(void);


void zfree(void *ptr);


listNode *listNext(listIter *iter);

int canFeedReplicaReplBuffer(client *replica) ;


int prepareClientToWrite(client *c);


int ll2string(char *s, size_t len, long long value);

static inline size_t sdslen(const sds s) ;

void feedReplicationBuffer(char *buf, size_t len);


int raxRemove(rax *rax, unsigned char *s, size_t len, void **old);


void listDelNode(list *list, listNode *node);


uint64_t intrev64(uint64_t v);


void *zmalloc_usable(size_t size, size_t *usable);


list *listAddNodeTail(list *list, void *value);


void listRewind(list *list, listIter *li);


int closeClientOnOutputBufferLimitReached(client *c, int async);

void createReplicationBacklogIndex(listNode *ln) ;

void incrementalTrimReplicationBacklog(size_t max_blocks) ;

int prepareReplicasToWrite(void) ;


robj *createObject(int type, void *ptr);


sds sdscatprintf(sds s, const char *fmt, ...);


sds sdsempty(void);

void feedReplicationBufferWithObject(robj *o) ;


void clusterSlotStatsDecrNetworkBytesOutForReplication(long long len);


void decrRefCount(robj *o);

extern struct sharedObjectsStruct shared;
;

size_t stringObjectLen(robj *o);


void _serverLog(int level, const char *fmt, ...);

char *replicationGetSlaveName(client *c) ;

static inline int connWrite(connection *conn, const void *data, size_t data_len) ;


void freeClientAsync(client *c);


client *lookupClientByID(uint64_t id);


rdbSaveInfo *rdbPopulateSaveInfo(rdbSaveInfo *rsi);


int rdbSaveToSlavesSockets(int req, rdbSaveInfo *rsi);


int rdbSaveBackground(int req, char *filename, rdbSaveInfo *rsi, int rdbflags);


void debugPauseProcess(void);

int RDBGeneratedByReplication = 0;
;

void addReplyError(client *c, const char *err);

int replicationSetupSlaveForFullResync(client *slave, long long offset) ;

long long getPsyncInitialOffset(void) ;


int allPersistenceDisabled(void);

int bg_unlink(const char *filename) ;

void changeReplicationId(void) ;


client *createClient(connection *conn);

static inline connection *connCreate(struct aeEventLoop *el, ConnectionType *ct) ;

static ConnectionType *connTypeOfReplication(void) ;

static inline int connConnect(connection *conn, const char *addr, int port, const char *src_addr, ConnectionCallbackFunc connect_handler) ;

void syncWithMaster(connection *conn) ;

static inline const char *connGetLastError(connection *conn) ;

static inline void connClose(connection *conn) ;

void undoConnectWithMaster(void) ;

static int rdbChannelAbort(void);

void replicationAbortSyncTransfer(void) ;

int slaveIsInHandshakeState(void) ;

int connectWithMaster(void) ;


sds sdsnew(const char *init);

int cancelReplicationHandshake(int reconnect) ;

void replicationDiscardCachedMaster(void);

void replicationCacheMasterUsingMyself(void);

void shiftReplicationId(void) ;

static void rdbChannelReplDataBufFree(void) ;

static inline void rioAbort(rio *r) ;

static inline int connSetReadHandler(connection *conn, ConnectionCallbackFunc func) ;

static void rdbChannelCleanup(void) ;


void addReplyArrayLen(client *c, long length);


void addReplyBulkCString(client *c, const char *s);


void addReplyBulkLongLong(client *c, long long ll);

void replicationCreateMasterClient(connection *conn, int dbid) ;

void updateFailoverStatus(void);

void replicationSendAck(void) ;

void replicationFeedSlaves(list *slaves, int dictid, robj **argv, int argc) ;


int clusterManualFailoverTimeLimit(void);


uint32_t isPausedActionsWithUpdate(uint32_t action_bitmask);


void freeClient(client *c);

void clearReplicationId2(void) ;

void freeReplicationBacklog(void) ;

void replicationStartPendingFork(void);

void removeRDBUsedToSyncReplicas(void) ;


int hasActiveChildProcess(void);

int shouldStartChildReplication(int *mincapa_out, int *req_out) ;

int startBgsaveForReplication(int mincapa, int req) ;

void replicationUnsetMaster(void) ;

void clearFailoverState(void) ;

void replicationSetMaster(char *ip, int port) ;

void abortFailover(const char *err) ;

static client *findReplica(char *host, int port) ;


char *zstrdup(const char *s);

#endif