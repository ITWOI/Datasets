#ifndef __HEADER_FUNC_H__ 
#define __HEADER_FUNC_H__
#include"header_type.h" 
static inline unsigned char sdsType(const sds s) ;

extern struct redisServer server;
;

sds sdscatprintf(sds s, const char *fmt, ...);

static inline size_t sdslen(const sds s) ;

sds clusterGenNodesDescription(client *c, int filter, int tls_primary);


sds sdscatfmt(sds s, const char *fmt, ...);


sds sdsempty(void);


mstime_t mstime(void);


void _serverLog(int level, const char *fmt, ...);


int fsyncFileDir(const char *filename);

int clusterSaveConfig(int do_fsync) ;

static inline int defaultClientPort(void) ;


sds sdscpy(sds s, const char *t);


void sdsclear(sds s);

void clusterDoBeforeSleep(int flags);

void clusterAddNodeToShard(const char *shard_id, clusterNode *node);

static void assignShardIdToNode(clusterNode *node, const char *shard_id, int flag) ;

int clusterNodeNumSlaves(clusterNode *node);

clusterNode *clusterNodeGetSlave(clusterNode *node, int slave_idx);

clusterNode *myself = ((void *)0);
;
static void updateAnnouncedHostname(clusterNode *node, char *new) ;


void *zcalloc(size_t size);

static void clusterBuildMessageHdr(clusterMsg *hdr, int type, size_t msglen);

static clusterMsg *getMessageFromSendBlock(clusterMsgSendBlock *msgblock) ;


void _serverAssert(const char *estr, const char *file, int line);


void zfree(void *ptr);


void *zmalloc(size_t size);


list *listCreate(void);

static void clusterMsgSendBlockDecrRefCount(void *node) ;

static inline void connClose(connection *conn) ;


void *zrealloc(void *ptr, size_t size);

int clusterNodeRemoveSlave(clusterNode *master, clusterNode *slave) ;


sds sdsnewlen(const void *init, size_t initlen);


int dictDelete(dict *d, const void *key);

void freeClusterLink(clusterLink *link) ;

int clusterDelSlot(int slot);


dictEntry *dictNext(dictIterator *iter);

int clusterNodeDelFailureReport(clusterNode *node, clusterNode *sender) ;


void *dictGetVal(const dictEntry *de);

void freeClusterNode(clusterNode *n) ;


dictEntry *dictFind(dict *d, const void *key);


list *listAddNodeTail(list *list, void *value);


int dictAdd(dict *d, void *key, void *val);


listNode *listSearchKey(list *list, void *key);


void sdsfree(sds s);

int clusterNodeFailureReportsCount(clusterNode *node) ;

int clusterNodeIsMaster(clusterNode *n);

void clusterSendFail(char *nodename);

uint32_t getAlignedPingExtSize(uint32_t dataSize) ;

static clusterMsgPingExt *getInitialPingExt(clusterMsg *hdr, int count) ;

clusterMsgPingExt *nextPingExt(clusterMsgPingExt *ext) ;

uint32_t getHostnamePingExtSize(void) ;

void *preparePingExt(clusterMsgPingExt *ext, uint16_t type, uint32_t length) ;

uint32_t getHumanNodenamePingExtSize(void) ;


void dictInitIterator(dictIterator *iter, dict *d);


void *dictGetKey(const dictEntry *de);


uint64_t intrev64(uint64_t v);

uint32_t getForgottenNodeExtSize(void) ;


void dictResetIterator(dictIterator *iter);


uint64_t dictGetUnsignedIntegerVal(const dictEntry *de);

uint32_t getShardIdPingExtSize(void) ;

uint32_t getInternalSecretPingExtSize(void) ;

static inline int connSetWriteHandlerWithBarrier(connection *conn, ConnectionCallbackFunc func, int barrier) ;

void clusterWriteHandler(connection *conn) ;

void clusterSendMessage(clusterLink *link, clusterMsgSendBlock *msgblock) ;

void deriveAnnouncedPorts(int *announced_tcp_port, int *announced_tls_port, int *announced_cport) ;


long long replicationGetSlaveOffset(void);

uint32_t writePingExt(clusterMsg *hdr, int gossipcount) ;

static clusterMsgSendBlock *createClusterMsgSendBlock(int type, uint32_t msglen) ;

void clusterSetGossipEntry(clusterMsg *hdr, int i, clusterNode *n) ;


dictEntry *dictGetRandomKey(dict *d);


void dictInitSafeIterator(dictIterator *iter, dict *d);

void clusterSendPing(clusterLink *link, int type) ;

void clusterBroadcastMessage(clusterMsgSendBlock *msgblock) ;

void clusterSetNodeAsMaster(clusterNode *n) ;

int clusterNodeCoversSlot(clusterNode *n, int slot);

int clusterAddSlot(clusterNode *n, int slot);

void clusterUpdateState(void);

void clusterSaveConfigOrDie(int do_fsync) ;

void clusterBroadcastPong(int target) ;

void resetManualFailover(void);

void clusterLogCantFailover(int reason) ;

int clusterGetSlaveRank(void) ;

void clusterRequestFailoverAuth(void) ;

void clusterFailoverReplaceYourMaster(void) ;

int clusterCountNonFailingSlaves(clusterNode *n) ;

void clusterSetMaster(clusterNode *n);

void clusterDelNode(clusterNode *delnode) ;

static inline connection *connCreate(struct aeEventLoop *el, ConnectionType *ct) ;


ConnectionType *connTypeOfCluster(void);

static inline void connSetPrivateData(connection *conn, void *data) ;

static inline int connConnect(connection *conn, const char *addr, int port, const char *src_addr, ConnectionCallbackFunc connect_handler) ;

void clusterLinkConnectHandler(connection *conn) ;

clusterLink *createClusterLink(clusterNode *node) ;

static void freeClusterLinkOnBufferLimitReached(clusterLink *link) ;

void clusterUpdateMyselfHostname(void) ;

static void clusterNodeCronFreeLinkOnBufferLimitReached(clusterNode *node) ;

static int clusterNodeCronHandleReconnect(clusterNode *node, mstime_t handshake_timeout, mstime_t now) ;

void markNodeAsFailingIfNeeded(clusterNode *node) ;

void manualFailoverCheckTimeout(void) ;

void clusterHandleManualFailover(void) ;

void clusterHandleSlaveFailover(void) ;

void clusterHandleSlaveMigration(int max_slaves) ;

int bitmapTestBit(unsigned char *bitmap, int pos) ;

void bitmapClearBit(unsigned char *bitmap, int pos) ;

int clusterNodeSetSlotBit(clusterNode *n, int slot) ;

int clusterNodeClearSlotBit(clusterNode *n, int slot) ;


unsigned long long kvstoreSize(kvstore *kvs);

void clusterCloseAllSlots(void) ;

static void updateShardId(clusterNode *node, const char *shard_id) ;

int clusterNodeAddSlave(clusterNode *master, clusterNode *slave) ;

static inline void removeAllNotOwnedShardChannelSubscriptions(void) ;

static struct redisNodeFlags redisNodeFlagsTable[] = {{16, "myself,"}, {1, "master,"}, {2, "slave,"}, {4, "fail?,"}, {8, "fail,"}, {32, "handshake,"}, {64, "noaddr,"}, {512, "nofailover,"}};
;

sds sdscat(sds s, const char *t);

int clusterNodeClientPort(clusterNode *n, int use_tls) ;


sds sdscatlen(sds s, const void *t, size_t len);

int auxShardIdSetter(clusterNode *n, void *value, int length);

sds auxShardIdGetter(clusterNode *n, sds s);

int auxShardIdPresent(clusterNode *n);

int auxHumanNodenameSetter(clusterNode *n, void *value, int length);

sds auxHumanNodenameGetter(clusterNode *n, sds s);

int auxHumanNodenamePresent(clusterNode *n);

int auxTcpPortSetter(clusterNode *n, void *value, int length);

sds auxTcpPortGetter(clusterNode *n, sds s);

int auxTcpPortPresent(clusterNode *n);

int auxTlsPortSetter(clusterNode *n, void *value, int length);

sds auxTlsPortGetter(clusterNode *n, sds s);

int auxTlsPortPresent(clusterNode *n);

auxFieldHandler auxFieldHandlers[] = {{"shard-id", auxShardIdSetter, auxShardIdGetter, auxShardIdPresent}, {"nodename", auxHumanNodenameSetter, auxHumanNodenameGetter, auxHumanNodenamePresent}, {"tcp-port", auxTcpPortSetter, auxTcpPortGetter, auxTcpPortPresent}, {"tls-port", auxTlsPortSetter, auxTlsPortGetter, auxTlsPortPresent}};
;
sds representClusterNodeFlags(sds ci, uint16_t flags) ;

sds representSlotInfo(sds ci, uint16_t *slot_info_pairs, int slot_info_pairs_count) ;

void clusterGenNodesSlotsInfo(int filter) ;

sds clusterGenNodeDescription(client *c, clusterNode *node, int tls_primary) ;


sds sdscatsds(sds s, const sds t);

void clusterFreeNodesSlotsInfo(clusterNode *n) ;

#endif