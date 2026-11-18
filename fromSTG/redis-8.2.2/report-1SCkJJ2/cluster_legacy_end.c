#include "header_func.h"
#include "sds.h"
extern int clusterNodeClientPort (clusterNode *n, int use_tls){
    return use_tls ? n->tls_port : n->tcp_port;
}
static inline int defaultClientPort (){
    return server.tls_cluster ? server.tls_port : server.port;
}
extern sds auxShardIdGetter (clusterNode *n, sds s){
    return sdscatprintf(s, "%.40s", n->shard_id);
}
extern int auxShardIdPresent (clusterNode *n){
    return strlen(n->shard_id);
}
extern sds auxHumanNodenameGetter (clusterNode *n, sds s){
    return sdscatprintf(s, "%s", n->human_nodename);
}
extern int auxHumanNodenamePresent (clusterNode *n){
    return sdslen(n->human_nodename);
}
extern sds auxTcpPortGetter (clusterNode *n, sds s){
    return sdscatprintf(s, "%d", n->tcp_port);
}
extern int auxTcpPortPresent (clusterNode *n){
    return n->tcp_port >= 0 && n->tcp_port < 65536;
}
extern sds auxTlsPortGetter (clusterNode *n, sds s){
    return sdscatprintf(s, "%d", n->tls_port);
}
extern int auxTlsPortPresent (clusterNode *n){
    return n->tls_port >= 0 && n->tls_port < 65536;
}
static clusterMsg * getMessageFromSendBlock (clusterMsgSendBlock *msgblock){
    return &msgblock->msg[0];
}
extern int clusterSaveConfig (int do_fsync){
    sds ci, tmpfilename;
    size_t content_size, offset = 0;
    ssize_t written_bytes;
    int fd = -1;
    int retval = -1;
    server.cluster->todo_before_sleep &= ~(1 << 2);
    ci = clusterGenNodesDescription(((void *)0), 32, 0);
    ci = sdscatprintf(ci, "vars currentEpoch %llu lastVoteEpoch %llu\n", (unsigned long long)server.cluster->currentEpoch, (unsigned long long)server.cluster->lastVoteEpoch);
    content_size = sdslen(ci);
    tmpfilename = sdscatfmt(sdsempty(), "%s.tmp-%i-%I", server.cluster_configfile, (int)getpid(), mstime());
    if ((fd = open(tmpfilename, 1 | 64, 420)) == -1) {
        ;
        goto cleanup;
    }
    while (offset < content_size)
        {
            written_bytes = write(fd, ci + offset, content_size - offset);
            if (written_bytes <= 0) {
                if ((*__errno_location()) == 4)
                    continue;
                goto cleanup;
            }
            offset += written_bytes;
        }
    if (do_fsync) {
        server.cluster->todo_before_sleep &= ~(1 << 3);
        if (fdatasync(fd) == -1) {
            ;
            goto cleanup;
        }
    }
    if (rename(tmpfilename, server.cluster_configfile) == -1) {
        ;
        goto cleanup;
    }
    if (do_fsync) {
        if (fsyncFileDir(server.cluster_configfile) == -1) {
            ;
            goto cleanup;
        }
    }
    retval = 0;
  cleanup:
    ;
    return retval;
}
extern void clusterSaveConfigOrDie (int do_fsync){
    if (clusterSaveConfig(do_fsync) == -1) {
        ;
    }
}
extern void deriveAnnouncedPorts (int *announced_tcp_port, int *announced_tls_port, int *announced_cport){
    *announced_tcp_port = server.cluster_announce_port ? server.cluster_announce_port : server.port;
    *announced_tls_port = server.cluster_announce_tls_port ? server.cluster_announce_tls_port : server.tls_port;
    if (server.cluster_announce_bus_port) {
        *announced_cport = server.cluster_announce_bus_port;
    } else if (server.cluster_port) {
        *announced_cport = server.cluster_port;
    } else {
        *announced_cport = defaultClientPort() + 10000;
    }
}
static void updateAnnouncedHostname (clusterNode *node, char *new){
    if (new && !strcmp(new, node->hostname)) {
        return;
    } else if (!new && (sdslen(node->hostname) == 0)) {
        return;
    }
    if (new) {
        ;
    } else if (sdslen(node->hostname) != 0) {
        ;
    }
    clusterDoBeforeSleep((1 << 2));
}
static void assignShardIdToNode (clusterNode *node, const char *shard_id, int flag){
    ;
    clusterAddNodeToShard(shard_id, node);
    clusterDoBeforeSleep(flag);
}
static void updateShardId (clusterNode *node, const char *shard_id){
    if (shard_id && memcmp(node->shard_id, shard_id, 40) != 0) {
        if (node->slaveof == ((void *)0)) {
            assignShardIdToNode(node, shard_id, (1 << 2));
            for (int i = 0; i < clusterNodeNumSlaves(node); i++) {
                clusterNode *slavenode = clusterNodeGetSlave(node, i);
                if (memcmp(slavenode->shard_id, shard_id, 40) != 0)
                    assignShardIdToNode(slavenode, shard_id, (1 << 2) | (1 << 3));
            }
        } else if (memcmp(node->slaveof->shard_id, shard_id, 40) == 0) {
            assignShardIdToNode(node, shard_id, (1 << 2));
        }
    }
}
extern void clusterUpdateMyselfHostname (){
    if (!myself)
        return;
    updateAnnouncedHostname(myself, server.cluster_announce_hostname);
}
static clusterMsgSendBlock * createClusterMsgSendBlock (int type, uint32_t msglen){
    uint32_t blocklen = msglen + sizeof(clusterMsgSendBlock);
    clusterMsgSendBlock *msgblock = zcalloc(blocklen);
    msgblock->refcount = 1;
    msgblock->totlen = blocklen;
    server.stat_cluster_links_memory += blocklen;
    clusterBuildMessageHdr(getMessageFromSendBlock(msgblock), type, msglen);
    return msgblock;
}
static void clusterMsgSendBlockDecrRefCount (void *node){
    clusterMsgSendBlock *msgblock = (clusterMsgSendBlock *)node;
    msgblock->refcount--;
    (__builtin_expect(!!(msgblock->refcount >= 0), 1) ? (void)0 : (_serverAssert("msgblock->refcount >= 0", "cluster_legacy_InstSlice.c", 477) , abort()));
    if (msgblock->refcount == 0) {
        server.stat_cluster_links_memory -= msgblock->totlen;
    }
}
extern clusterLink * createClusterLink (clusterNode *node){
    clusterLink *link = zmalloc(sizeof (*link));
    link->ctime = mstime();
    link->send_msg_queue = listCreate();
    ((link->send_msg_queue)->free = (clusterMsgSendBlockDecrRefCount));
    link->head_msg_send_offset = 0;
    link->send_msg_queue_mem = sizeof(list);
    link->rcvbuf = zmalloc(link->rcvbuf_alloc = 1024);
    link->rcvbuf_len = 0;
    server.stat_cluster_links_memory += link->rcvbuf_alloc + link->send_msg_queue_mem;
    link->conn = ((void *)0);
    link->node = node;
    link->inbound = (node == ((void *)0));
    if (!link->inbound) {
        node->link = link;
    }
    return link;
}
extern void freeClusterLink (clusterLink *link){
    if (link->conn) {
        ;
        link->conn = ((void *)0);
    }
    server.stat_cluster_links_memory -= sizeof(list) + ((link->send_msg_queue)->len) * sizeof(listNode);
    server.stat_cluster_links_memory -= link->rcvbuf_alloc;
    if (link->node) {
        if (link->node->link == link) {
            (__builtin_expect(!!(!link->inbound), 1) ? (void)0 : (_serverAssert("!link->inbound", "cluster_legacy_InstSlice.c", 518) , abort()));
            link->node->link = ((void *)0);
        } else if (link->node->inbound_link == link) {
            (__builtin_expect(!!(link->inbound), 1) ? (void)0 : (_serverAssert("link->inbound", "cluster_legacy_InstSlice.c", 521) , abort()));
            link->node->inbound_link = ((void *)0);
        }
    }
    ;
}
extern int clusterNodeFailureReportsCount (clusterNode *node){
    ;
    return ((node->fail_reports)->len);
}
extern int clusterNodeRemoveSlave (clusterNode *master, clusterNode *slave){
    int j;
    for (j = 0; j < master->numslaves; j++) {
        if (master->slaves[j] == slave) {
            if ((j + 1) < master->numslaves) {
                int remaining_slaves = (master->numslaves - j) - 1;
            }
            master->numslaves--;
            if (master->numslaves == 0)
                master->flags &= ~256;
            return 0;
        }
    }
    return -1;
}
extern int clusterNodeAddSlave (clusterNode *master, clusterNode *slave){
    int j;
    for (j = 0; j < master->numslaves; j++)
        if (master->slaves[j] == slave)
            return -1;
    master->slaves = zrealloc(master->slaves, sizeof(clusterNode *) * (master->numslaves + 1));
    master->slaves[master->numslaves] = slave;
    master->numslaves++;
    master->flags |= 256;
    return 0;
}
extern int clusterCountNonFailingSlaves (clusterNode *n){
    int j, okslaves = 0;
    for (j = 0; j < n->numslaves; j++)
        if (!((n->slaves[j])->flags & 8))
            okslaves++;
    return okslaves;
}
extern void freeClusterNode (clusterNode *n){
    sds nodename;
    int j;
    for (j = 0; j < n->numslaves; j++)
        n->slaves[j]->slaveof = ((void *)0);
    if (((n)->flags & 2) && n->slaveof)
        clusterNodeRemoveSlave(n->slaveof, n);
    nodename = sdsnewlen(n->name, 40);
    (__builtin_expect(!!(dictDelete(server.cluster->nodes, nodename) == 0), 1) ? (void)0 : (_serverAssert("dictDelete(server.cluster->nodes,nodename) == DICT_OK", "cluster_legacy_InstSlice.c", 647) , abort()));
    if (n->link)
        freeClusterLink(n->link);
    if (n->inbound_link)
        freeClusterLink(n->inbound_link);
}
extern void clusterDelNode (clusterNode *delnode){
    int j;
    dictIterator di;
    dictEntry *de;
    for (j = 0; j < (1 << 14); j++) {
        if (server.cluster->importing_slots_from[j] == delnode)
            server.cluster->importing_slots_from[j] = ((void *)0);
        if (server.cluster->migrating_slots_to[j] == delnode)
            server.cluster->migrating_slots_to[j] = ((void *)0);
        if (server.cluster->slots[j] == delnode)
            clusterDelSlot(j);
    }
    ;
    while ((de = dictNext(&di)) != ((void *)0))
        {
            clusterNode *node = dictGetVal(de);
        }
    ;
    freeClusterNode(delnode);
}
extern void clusterAddNodeToShard (const char *shard_id, clusterNode *node){
    sds s = sdsnewlen(shard_id, 40);
    dictEntry *de = dictFind(server.cluster->shards, s);
    if (de == ((void *)0)) {
        list *l = listCreate();
        (__builtin_expect(!!(dictAdd(server.cluster->shards, s, l) == 0), 1) ? (void)0 : (_serverAssert("dictAdd(server.cluster->shards, s, l) == DICT_OK", "cluster_legacy_InstSlice.c", 732) , abort()));
    } else {
        list *l = dictGetVal(de);
    }
}
extern void markNodeAsFailingIfNeeded (clusterNode *node){
    int failures;
    int needed_quorum = (server.cluster->size / 2) + 1;
    if (!((node)->flags & 4))
        return;
    if (((node)->flags & 8))
        return;
    failures = clusterNodeFailureReportsCount(node);
    if (clusterNodeIsMaster(myself))
        failures++;
    if (failures < needed_quorum)
        return;
    node->flags &= ~4;
    node->flags |= 8;
    node->fail_time = mstime();
    clusterSendFail(node->name);
    clusterDoBeforeSleep((1 << 1) | (1 << 2));
}
extern void clusterSetNodeAsMaster (clusterNode *n){
    if (clusterNodeIsMaster(n))
        return;
    if (n->slaveof) {
        clusterNodeRemoveSlave(n->slaveof, n);
    }
    ;
    clusterDoBeforeSleep((1 << 2) | (1 << 1));
}
static clusterMsgPingExt * getInitialPingExt (clusterMsg *hdr, int count){
    clusterMsgPingExt *initial = (clusterMsgPingExt *)&(hdr->data.ping.gossip[count]);
    return initial;
}
extern uint32_t getAlignedPingExtSize (uint32_t dataSize){
    return sizeof(clusterMsgPingExt) + ((((dataSize) + 7) / 8) * 8);
}
extern uint32_t getHostnamePingExtSize (){
    if (sdslen(myself->hostname) == 0) {
        return 0;
    }
    return getAlignedPingExtSize(sdslen(myself->hostname) + 1);
}
extern uint32_t getHumanNodenamePingExtSize (){
    if (sdslen(myself->human_nodename) == 0) {
        return 0;
    }
    return getAlignedPingExtSize(sdslen(myself->human_nodename) + 1);
}
extern uint32_t getShardIdPingExtSize (){
    return getAlignedPingExtSize(sizeof(clusterMsgPingExtShardId));
}
extern uint32_t getInternalSecretPingExtSize (){
    return getAlignedPingExtSize(sizeof(clusterMsgPingExtInternalSecret));
}
extern uint32_t getForgottenNodeExtSize (){
    return getAlignedPingExtSize(sizeof(clusterMsgPingExtForgottenNode));
}
extern void * preparePingExt (clusterMsgPingExt *ext, uint16_t type, uint32_t length){
    ext->type = htons(type);
    ext->length = htonl(length);
    return &ext->ext[0];
}
extern clusterMsgPingExt * nextPingExt (clusterMsgPingExt *ext){
    return (clusterMsgPingExt *)((char *)ext + ntohl(ext->length));
}
extern uint32_t writePingExt (clusterMsg *hdr, int gossipcount){
    uint16_t extensions = 0;
    uint32_t totlen = 0;
    clusterMsgPingExt *cursor = ((void *)0);
    if (hdr != ((void *)0)) {
        cursor = getInitialPingExt(hdr, gossipcount);
    }
    if (sdslen(myself->hostname) != 0) {
        if (cursor != ((void *)0)) {
            clusterMsgPingExtHostname *ext = preparePingExt(cursor, CLUSTERMSG_EXT_TYPE_HOSTNAME, getHostnamePingExtSize());
            memcpy(ext->hostname, myself->hostname, sdslen(myself->hostname));
            cursor = nextPingExt(cursor);
        }
        totlen += getHostnamePingExtSize();
        extensions++;
    }
    if (sdslen(myself->human_nodename) != 0) {
        if (cursor != ((void *)0)) {
            clusterMsgPingExtHumanNodename *ext = preparePingExt(cursor, CLUSTERMSG_EXT_TYPE_HUMAN_NODENAME, getHumanNodenamePingExtSize());
            memcpy(ext->human_nodename, myself->human_nodename, sdslen(myself->human_nodename));
            cursor = nextPingExt(cursor);
        }
        totlen += getHumanNodenamePingExtSize();
        extensions++;
    }
    if (((server.cluster->nodes_black_list)->ht_used[0] + (server.cluster->nodes_black_list)->ht_used[1]) > 0) {
        dictIterator di;
        dictEntry *de;
        while ((de = dictNext(&di)) != ((void *)0))
            {
                if (cursor != ((void *)0)) {
                    uint64_t expire = dictGetUnsignedIntegerVal(de);
                    if ((time_t)expire < server.unixtime)
                        continue;
                    uint64_t ttl = expire - server.unixtime;
                    clusterMsgPingExtForgottenNode *ext = preparePingExt(cursor, CLUSTERMSG_EXT_TYPE_FORGOTTEN_NODE, getForgottenNodeExtSize());
                    ext->ttl = intrev64(ttl);
                    cursor = nextPingExt(cursor);
                }
                totlen += getForgottenNodeExtSize();
                extensions++;
            }
        ;
    }
    if (cursor != ((void *)0)) {
        clusterMsgPingExtShardId *ext = preparePingExt(cursor, CLUSTERMSG_EXT_TYPE_SHARDID, getShardIdPingExtSize());
        cursor = nextPingExt(cursor);
    }
    totlen += getShardIdPingExtSize();
    extensions++;
    if (cursor != ((void *)0)) {
        clusterMsgPingExtInternalSecret *ext = preparePingExt(cursor, CLUSTERMSG_EXT_TYPE_INTERNALSECRET, getInternalSecretPingExtSize());
        cursor = nextPingExt(cursor);
    }
    totlen += getInternalSecretPingExtSize();
    extensions++;
    if (hdr != ((void *)0)) {
        hdr->extensions = htons(extensions);
    }
    return totlen;
}
extern void clusterSendMessage (clusterLink *link, clusterMsgSendBlock *msgblock){
    if (!link) {
        return;
    }
    if (((link->send_msg_queue)->len) == 0 && getMessageFromSendBlock(msgblock)->totlen != 0) {
    }
    ;
    msgblock->refcount++;
    link->send_msg_queue_mem += sizeof(listNode) + msgblock->totlen;
    server.stat_cluster_links_memory += sizeof(listNode);
    uint16_t type = ntohs(getMessageFromSendBlock(msgblock)->type);
    if (type < 11)
        server.cluster->stats_bus_messages_sent[type]++;
}
extern void clusterBroadcastMessage (clusterMsgSendBlock *msgblock){
    dictIterator di;
    dictEntry *de;
    while ((de = dictNext(&di)) != ((void *)0))
        {
            clusterNode *node = dictGetVal(de);
            if (node->flags & (16 | 32))
                continue;
            clusterSendMessage(node->link, msgblock);
        }
    ;
}
static void clusterBuildMessageHdr (clusterMsg *hdr, int type, size_t msglen){
    uint64_t offset;
    clusterNode *master;
    master = (((myself)->flags & 2) && myself->slaveof) ? myself->slaveof : myself;
    hdr->ver = htons(1);
    hdr->sig[0] = 'R';
    hdr->sig[1] = 'C';
    hdr->sig[2] = 'm';
    hdr->sig[3] = 'b';
    hdr->type = htons(type);
    int announced_tcp_port, announced_tls_port, announced_cport;
    deriveAnnouncedPorts(&announced_tcp_port, &announced_tls_port, &announced_cport);
    if (server.tls_cluster) {
        hdr->port = htons(announced_tls_port);
        hdr->pport = htons(announced_tcp_port);
    } else {
        hdr->port = htons(announced_tcp_port);
        hdr->pport = htons(announced_tls_port);
    }
    hdr->cport = htons(announced_cport);
    hdr->flags = htons(myself->flags);
    hdr->state = server.cluster->state;
    hdr->currentEpoch = intrev64(server.cluster->currentEpoch);
    hdr->configEpoch = intrev64(master->configEpoch);
    if (((myself)->flags & 2)) {
        offset = replicationGetSlaveOffset();
    } else
        offset = server.master_repl_offset;
    hdr->offset = intrev64(offset);
    if (clusterNodeIsMaster(myself) && server.cluster->mf_end)
        hdr->mflags[0] |= (1 << 0);
    hdr->mflags[0] |= (1 << 2);
    hdr->totlen = htonl(msglen);
}
extern void clusterSetGossipEntry (clusterMsg *hdr, int i, clusterNode *n){
    clusterMsgDataGossip *gossip;
    gossip = &(hdr->data.ping.gossip[i]);
    gossip->ping_sent = htonl(n->ping_sent / 1000);
    gossip->pong_received = htonl(n->pong_received / 1000);
    if (server.tls_cluster) {
        gossip->port = htons(n->tls_port);
        gossip->pport = htons(n->tcp_port);
    } else {
        gossip->port = htons(n->tcp_port);
        gossip->pport = htons(n->tls_port);
    }
    gossip->cport = htons(n->cport);
    gossip->flags = htons(n->flags);
    gossip->notused1 = 0;
}
extern void clusterSendPing (clusterLink *link, int type){
    static unsigned long long cluster_pings_sent;
    cluster_pings_sent++;
    int gossipcount = 0;
    int wanted;
    int estlen;
    int freshnodes = ((server.cluster->nodes)->ht_used[0] + (server.cluster->nodes)->ht_used[1]) - 2;
    wanted = floor(((server.cluster->nodes)->ht_used[0] + (server.cluster->nodes)->ht_used[1]) / 10);
    if (wanted < 3)
        wanted = 3;
    if (wanted > freshnodes)
        wanted = freshnodes;
    int pfail_wanted = server.cluster->stats_pfail_nodes;
    estlen = sizeof(clusterMsg) - sizeof(union clusterMsgData);
    estlen += (sizeof(clusterMsgDataGossip) * (wanted + pfail_wanted));
    if (link->node && ((link->node)->flags & 1024)) {
        estlen += writePingExt(((void *)0), 0);
    }
    if (estlen < (int)sizeof(clusterMsg))
        estlen = sizeof(clusterMsg);
    clusterMsgSendBlock *msgblock = createClusterMsgSendBlock(type, estlen);
    clusterMsg *hdr = getMessageFromSendBlock(msgblock);
    if (!link->inbound && type == 0)
        link->node->ping_sent = mstime();
    int maxiterations = wanted * 3;
    while (freshnodes > 0 && gossipcount < wanted && maxiterations--)
        {
            dictEntry *de = dictGetRandomKey(server.cluster->nodes);
            clusterNode *this = dictGetVal(de);
            if (this == myself || this == link->node)
                continue;
            if (this->flags & 4)
                continue;
            if (this->flags & (32 | 64) || (this->link == ((void *)0) && this->numslots == 0)) {
                freshnodes--;
                continue;
            }
            if (this->last_in_ping_gossip == cluster_pings_sent)
                continue;
            clusterSetGossipEntry(hdr, gossipcount, this);
            this->last_in_ping_gossip = cluster_pings_sent;
            freshnodes--;
            gossipcount++;
        }
    if (pfail_wanted) {
        dictIterator di;
        dictEntry *de;
        while ((de = dictNext(&di)) != ((void *)0) && pfail_wanted > 0)
            {
                clusterNode *node = dictGetVal(de);
                if (node->flags & 32)
                    continue;
                if (node->flags & 64)
                    continue;
                if (!(node->flags & 4))
                    continue;
                clusterSetGossipEntry(hdr, gossipcount, node);
                gossipcount++;
                pfail_wanted--;
            }
        ;
    }
    uint32_t totlen = 0;
    if (link->node && ((link->node)->flags & 1024)) {
        totlen += writePingExt(hdr, gossipcount);
    }
    totlen += sizeof(clusterMsg) - sizeof(union clusterMsgData);
    totlen += (sizeof(clusterMsgDataGossip) * gossipcount);
    (__builtin_expect(!!(gossipcount < (32767 * 2 + 1)), 1) ? (void)0 : (_serverAssert("gossipcount < USHRT_MAX", "cluster_legacy_InstSlice.c", 1480) , abort()));
    hdr->count = htons(gossipcount);
    hdr->totlen = htonl(totlen);
    clusterSendMessage(link, msgblock);
    clusterMsgSendBlockDecrRefCount(msgblock);
}
extern void clusterBroadcastPong (int target){
    dictIterator di;
    dictEntry *de;
    while ((de = dictNext(&di)) != ((void *)0))
        {
            clusterNode *node = dictGetVal(de);
            if (!node->link)
                continue;
            if (node == myself || ((node)->flags & 32))
                continue;
            if (target == 1) {
                int local_slave = ((node)->flags & 2) && node->slaveof && (node->slaveof == myself || node->slaveof == myself->slaveof);
                if (!local_slave)
                    continue;
            }
            clusterSendPing(node->link, 1);
        }
    ;
}
extern void clusterSendFail (char *nodename){
    uint32_t msglen = sizeof(clusterMsg) - sizeof(union clusterMsgData) + sizeof(clusterMsgDataFail);
    clusterMsgSendBlock *msgblock = createClusterMsgSendBlock(3, msglen);
    clusterMsg *hdr = getMessageFromSendBlock(msgblock);
    clusterBroadcastMessage(msgblock);
    clusterMsgSendBlockDecrRefCount(msgblock);
}
extern void clusterRequestFailoverAuth (){
    uint32_t msglen = sizeof(clusterMsg) - sizeof(union clusterMsgData);
    clusterMsgSendBlock *msgblock = createClusterMsgSendBlock(5, msglen);
    if (server.cluster->mf_end)
        msgblock->msg[0].mflags[0] |= (1 << 1);
    clusterBroadcastMessage(msgblock);
    clusterMsgSendBlockDecrRefCount(msgblock);
}
extern int clusterGetSlaveRank (){
    long long myoffset;
    int j, rank = 0;
    clusterNode *master;
    (__builtin_expect(!!(((myself)->flags & 2)), 1) ? (void)0 : (_serverAssert("nodeIsSlave(myself)", "cluster_legacy_InstSlice.c", 1632) , abort()));
    master = myself->slaveof;
    if (master == ((void *)0))
        return 0;
    myoffset = replicationGetSlaveOffset();
    for (j = 0; j < master->numslaves; j++)
        if (master->slaves[j] != myself && !((master->slaves[j])->flags & 512) && master->slaves[j]->repl_offset > myoffset)
            rank++;
    return rank;
}
extern void clusterLogCantFailover (int reason){
    char *msg;
    static time_t lastlog_time;
    mstime_t nolog_fail_time = server.cluster_node_timeout + 5000;
    if (reason == server.cluster->cant_failover_reason && time(((void *)0)) - lastlog_time < (10))
        return;
    server.cluster->cant_failover_reason = reason;
    if (myself->slaveof && ((myself->slaveof)->flags & 8) && (mstime() - myself->slaveof->fail_time) < nolog_fail_time)
        return;
    lastlog_time = time(((void *)0));
    int cur_vote = server.cluster->failover_auth_count;
    int cur_quorum = (server.cluster->size / 2) + 1;
}
extern void clusterFailoverReplaceYourMaster (){
    int j;
    clusterNode *oldmaster = myself->slaveof;
    if (clusterNodeIsMaster(myself) || oldmaster == ((void *)0))
        return;
    clusterSetNodeAsMaster(myself);
    for (j = 0; j < (1 << 14); j++) {
        if (clusterNodeCoversSlot(oldmaster, j)) {
            clusterDelSlot(j);
            clusterAddSlot(myself, j);
        }
    }
    clusterUpdateState();
    clusterSaveConfigOrDie(1);
    clusterBroadcastPong(0);
    resetManualFailover();
}
extern void clusterHandleSlaveFailover (){
    mstime_t data_age;
    mstime_t auth_age = mstime() - server.cluster->failover_auth_time;
    int needed_quorum = (server.cluster->size / 2) + 1;
    int manual_failover = server.cluster->mf_end != 0 && server.cluster->mf_can_start;
    mstime_t auth_timeout, auth_retry_time;
    server.cluster->todo_before_sleep &= ~(1 << 0);
    auth_timeout = server.cluster_node_timeout * 2;
    if (auth_timeout < 2000)
        auth_timeout = 2000;
    auth_retry_time = auth_timeout * 2;
    if (clusterNodeIsMaster(myself) || myself->slaveof == ((void *)0) || (!((myself->slaveof)->flags & 8) && !manual_failover) || (server.cluster_slave_no_failover && !manual_failover) || myself->slaveof->numslots == 0) {
        server.cluster->cant_failover_reason = 0;
        return;
    }
    if (server.repl_state == REPL_STATE_CONNECTED) {
        data_age = (mstime_t)(server.unixtime - server.master->lastinteraction) * 1000;
    } else {
        data_age = (mstime_t)(server.unixtime - server.repl_down_since) * 1000;
    }
    if (data_age > server.cluster_node_timeout)
        data_age -= server.cluster_node_timeout;
    if (server.cluster_slave_validity_factor && data_age > (((mstime_t)server.repl_ping_slave_period * 1000) + (server.cluster_node_timeout * server.cluster_slave_validity_factor))) {
        if (!manual_failover) {
            clusterLogCantFailover(1);
            return;
        }
    }
    if (auth_age > auth_retry_time) {
        server.cluster->failover_auth_time = mstime() + 500 + random() % 500;
        server.cluster->failover_auth_count = 0;
        server.cluster->failover_auth_sent = 0;
        server.cluster->failover_auth_rank = clusterGetSlaveRank();
        server.cluster->failover_auth_time += server.cluster->failover_auth_rank * 1000;
        if (server.cluster->mf_end) {
            server.cluster->failover_auth_time = mstime();
            server.cluster->failover_auth_rank = 0;
            clusterDoBeforeSleep((1 << 0));
        }
        ;
        clusterBroadcastPong(1);
        return;
    }
    if (server.cluster->failover_auth_sent == 0 && server.cluster->mf_end == 0) {
        int newrank = clusterGetSlaveRank();
        if (newrank > server.cluster->failover_auth_rank) {
            long long added_delay = (newrank - server.cluster->failover_auth_rank) * 1000;
            server.cluster->failover_auth_time += added_delay;
            server.cluster->failover_auth_rank = newrank;
        }
    }
    if (mstime() < server.cluster->failover_auth_time) {
        clusterLogCantFailover(2);
        return;
    }
    if (auth_age > auth_timeout) {
        clusterLogCantFailover(3);
        return;
    }
    if (server.cluster->failover_auth_sent == 0) {
        server.cluster->currentEpoch++;
        server.cluster->failover_auth_epoch = server.cluster->currentEpoch;
        clusterRequestFailoverAuth();
        server.cluster->failover_auth_sent = 1;
        clusterDoBeforeSleep((1 << 2) | (1 << 1) | (1 << 3));
        return;
    }
    if (server.cluster->failover_auth_count >= needed_quorum) {
        ;
        clusterFailoverReplaceYourMaster();
    } else {
        clusterLogCantFailover(4);
    }
}
extern void clusterHandleSlaveMigration (int max_slaves){
    int j, okslaves = 0;
    clusterNode *mymaster = myself->slaveof, *target = ((void *)0), *candidate = ((void *)0);
    dictIterator di;
    dictEntry *de;
    if (server.cluster->state != 0)
        return;
    if (mymaster == ((void *)0))
        return;
    for (j = 0; j < mymaster->numslaves; j++)
        if (!((mymaster->slaves[j])->flags & 8) && !((mymaster->slaves[j])->flags & 4))
            okslaves++;
    if (okslaves <= server.cluster_migration_barrier)
        return;
    candidate = myself;
    while ((de = dictNext(&di)) != ((void *)0))
        {
            clusterNode *node = dictGetVal(de);
            int okslaves = 0, is_orphaned = 1;
            if (((node)->flags & 2) || ((node)->flags & 8))
                is_orphaned = 0;
            if (!(node->flags & 256))
                is_orphaned = 0;
            if (clusterNodeIsMaster(node))
                okslaves = clusterCountNonFailingSlaves(node);
            if (okslaves > 0)
                is_orphaned = 0;
            if (is_orphaned) {
                if (!target && node->numslots > 0)
                    target = node;
                if (!node->orphaned_time)
                    node->orphaned_time = mstime();
            } else {
                node->orphaned_time = 0;
            }
            if (okslaves == max_slaves) {
                for (j = 0; j < node->numslaves; j++) {
                    if (memcmp(node->slaves[j]->name, candidate->name, 40) < 0) {
                        candidate = node->slaves[j];
                    }
                }
            }
        }
    ;
    if (target && candidate == myself && (mstime() - target->orphaned_time) > 5000 && !(server.cluster_module_flags & (1 << 1))) {
        ;
        clusterSetMaster(target);
    }
}
extern void resetManualFailover (){
    server.cluster->mf_end = 0;
    server.cluster->mf_can_start = 0;
    server.cluster->mf_slave = ((void *)0);
    server.cluster->mf_master_offset = -1;
}
extern void manualFailoverCheckTimeout (){
    if (server.cluster->mf_end && server.cluster->mf_end < mstime()) {
        ;
        resetManualFailover();
    }
}
extern void clusterHandleManualFailover (){
    if (server.cluster->mf_end == 0)
        return;
    if (server.cluster->mf_can_start)
        return;
    if (server.cluster->mf_master_offset == -1)
        return;
    if (server.cluster->mf_master_offset == replicationGetSlaveOffset()) {
        server.cluster->mf_can_start = 1;
        clusterDoBeforeSleep((1 << 0));
        return;
    }
    clusterDoBeforeSleep((1 << 4));
}
static int clusterNodeCronHandleReconnect (clusterNode *node, mstime_t handshake_timeout, mstime_t now){
    if (node->flags & (16 | 64))
        return 1;
    if (node->flags & 4)
        server.cluster->stats_pfail_nodes++;
    if (((node)->flags & 32) && now - node->ctime > handshake_timeout) {
        clusterDelNode(node);
        return 1;
    }
    if (node->link == ((void *)0)) {
        clusterLink *link = createClusterLink(node);
        link->conn = connCreate(server.el, connTypeOfCluster());
        connSetPrivateData(link->conn, link);
        if (connConnect(link->conn, node->ip, node->cport, server.bind_source_addr, clusterLinkConnectHandler) == -1) {
            if (node->ping_sent == 0)
                node->ping_sent = mstime();
            freeClusterLink(link);
            return 0;
        }
    }
    return 0;
}
static void freeClusterLinkOnBufferLimitReached (clusterLink *link){
    if (link == ((void *)0) || server.cluster_link_msg_queue_limit_bytes == 0) {
        return;
    }
    unsigned long long mem_link = link->send_msg_queue_mem;
    if (mem_link > server.cluster_link_msg_queue_limit_bytes) {
        ;
        freeClusterLink(link);
        server.cluster->stat_cluster_links_buffer_limit_exceeded++;
    }
}
static void clusterNodeCronFreeLinkOnBufferLimitReached (clusterNode *node){
    freeClusterLinkOnBufferLimitReached(node->link);
    freeClusterLinkOnBufferLimitReached(node->inbound_link);
}
extern void clusterCron (){
    dictIterator di;
    dictEntry *de;
    int update_state = 0;
    int orphaned_masters;
    int max_slaves;
    int this_slaves;
    mstime_t min_pong = 0, now = mstime();
    clusterNode *min_pong_node = ((void *)0);
    static unsigned long long iteration;
    mstime_t handshake_timeout;
    iteration++;
    clusterUpdateMyselfHostname();
    handshake_timeout = server.cluster_node_timeout;
    if (handshake_timeout < 1000)
        handshake_timeout = 1000;
    server.cluster->stats_pfail_nodes = 0;
    while ((de = dictNext(&di)) != ((void *)0))
        {
            clusterNode *node = dictGetVal(de);
            clusterNodeCronFreeLinkOnBufferLimitReached(node);
            if (clusterNodeCronHandleReconnect(node, handshake_timeout, now))
                continue;
        }
    ;
    if (!(iteration % 10)) {
        int j;
        for (j = 0; j < 5; j++) {
            de = dictGetRandomKey(server.cluster->nodes);
            clusterNode *this = dictGetVal(de);
            if (this->link == ((void *)0) || this->ping_sent != 0)
                continue;
            if (this->flags & (16 | 32))
                continue;
            if (min_pong_node == ((void *)0) || min_pong > this->pong_received) {
                min_pong_node = this;
                min_pong = this->pong_received;
            }
        }
        if (min_pong_node) {
            ;
            clusterSendPing(min_pong_node->link, 0);
        }
    }
    orphaned_masters = 0;
    max_slaves = 0;
    this_slaves = 0;
    while ((de = dictNext(&di)) != ((void *)0))
        {
            clusterNode *node = dictGetVal(de);
            now = mstime();
            if (node->flags & (16 | 64 | 32))
                continue;
            if (((myself)->flags & 2) && clusterNodeIsMaster(node) && !((node)->flags & 8)) {
                int okslaves = clusterCountNonFailingSlaves(node);
                if (okslaves == 0 && node->numslots > 0 && node->flags & 256) {
                    orphaned_masters++;
                }
                if (okslaves > max_slaves)
                    max_slaves = okslaves;
                if (myself->slaveof == node)
                    this_slaves = okslaves;
            }
            mstime_t ping_delay = now - node->ping_sent;
            mstime_t data_delay = now - node->data_received;
            if (node->link && now - node->link->ctime > server.cluster_node_timeout && node->ping_sent && ping_delay > server.cluster_node_timeout / 2 && data_delay > server.cluster_node_timeout / 2) {
                freeClusterLink(node->link);
            }
            mstime_t ping_interval = server.cluster_ping_interval ? server.cluster_ping_interval : server.cluster_node_timeout / 2;
            if (node->link && node->ping_sent == 0 && (now - node->pong_received) > ping_interval) {
                clusterSendPing(node->link, 0);
                continue;
            }
            if (server.cluster->mf_end && clusterNodeIsMaster(myself) && server.cluster->mf_slave == node && node->link) {
                clusterSendPing(node->link, 0);
                continue;
            }
            if (node->ping_sent == 0)
                continue;
            mstime_t node_delay = (ping_delay < data_delay) ? ping_delay : data_delay;
            if (node_delay > server.cluster_node_timeout) {
                if (!(node->flags & (4 | 8))) {
                    node->flags |= 4;
                    update_state = 1;
                    if (clusterNodeIsMaster(myself) && server.cluster->size == 1) {
                        markNodeAsFailingIfNeeded(node);
                    } else {
                        ;
                    }
                }
            }
        }
    ;
    manualFailoverCheckTimeout();
    if (((myself)->flags & 2)) {
        clusterHandleManualFailover();
        if (!(server.cluster_module_flags & (1 << 1)))
            clusterHandleSlaveFailover();
        if (orphaned_masters && max_slaves >= 2 && this_slaves == max_slaves && server.cluster_allow_replica_migration)
            clusterHandleSlaveMigration(max_slaves);
    }
    if (update_state || server.cluster->state == 1)
        clusterUpdateState();
}
extern void clusterDoBeforeSleep (int flags){
    server.cluster->todo_before_sleep |= flags;
}
extern int bitmapTestBit (unsigned char *bitmap, int pos){
    off_t byte = pos / 8;
    int bit = pos & 7;
    return (bitmap[byte] & (1 << bit)) != 0;
}
extern void bitmapClearBit (unsigned char *bitmap, int pos){
    off_t byte = pos / 8;
    int bit = pos & 7;
    bitmap[byte] &= ~(1 << bit);
}
extern int clusterNodeSetSlotBit (clusterNode *n, int slot){
    int old = bitmapTestBit(n->slots, slot);
    return old;
}
extern int clusterNodeClearSlotBit (clusterNode *n, int slot){
    int old = bitmapTestBit(n->slots, slot);
    if (old) {
        bitmapClearBit(n->slots, slot);
        n->numslots--;
    }
    return old;
}
extern int clusterNodeCoversSlot (clusterNode *n, int slot){
    return bitmapTestBit(n->slots, slot);
}
extern int clusterAddSlot (clusterNode *n, int slot){
    if (server.cluster->slots[slot])
        return -1;
    clusterNodeSetSlotBit(n, slot);
    server.cluster->slots[slot] = n;
    bitmapClearBit(server.cluster->owner_not_claiming_slot, slot);
    return 0;
}
extern int clusterDelSlot (int slot){
    clusterNode *n = server.cluster->slots[slot];
    if (!n)
        return -1;
    (__builtin_expect(!!(clusterNodeClearSlotBit(n, slot) == 1), 1) ? (void)0 : (_serverAssert("clusterNodeClearSlotBit(n,slot) == 1", "cluster_legacy_InstSlice.c", 2401) , abort()));
    server.cluster->slots[slot] = ((void *)0);
    bitmapClearBit(server.cluster->owner_not_claiming_slot, slot);
    return 0;
}
extern void clusterUpdateState (){
    int j, new_state;
    int reachable_masters = 0;
    static mstime_t among_minority_time;
    static mstime_t first_call_time;
    server.cluster->todo_before_sleep &= ~(1 << 1);
    if (first_call_time == 0)
        first_call_time = mstime();
    if (clusterNodeIsMaster(myself) && server.cluster->state == 1 && mstime() - first_call_time < 2000)
        return;
    new_state = 0;
    if (server.cluster_require_full_coverage) {
        for (j = 0; j < (1 << 14); j++) {
            if (server.cluster->slots[j] == ((void *)0) || server.cluster->slots[j]->flags & (8)) {
                new_state = 1;
                break;
            }
        }
    }
    {
        dictIterator di;
        dictEntry *de;
        server.cluster->size = 0;
        dictInitSafeIterator(&di, server.cluster->nodes);
        while ((de = dictNext(&di)) != ((void *)0))
            {
                clusterNode *node = dictGetVal(de);
                if (clusterNodeIsMaster(node) && node->numslots) {
                    server.cluster->size++;
                    if ((node->flags & (8 | 4)) == 0)
                        reachable_masters++;
                }
            }
        dictResetIterator(&di);
    }
    {
        int needed_quorum = (server.cluster->size / 2) + 1;
        if (reachable_masters < needed_quorum) {
            new_state = 1;
            among_minority_time = mstime();
        }
    }
    if (new_state != server.cluster->state) {
        mstime_t rejoin_delay = server.cluster_node_timeout;
        if (rejoin_delay > 5000)
            rejoin_delay = 5000;
        if (rejoin_delay < 500)
            rejoin_delay = 500;
        if (new_state == 0 && clusterNodeIsMaster(myself) && mstime() - among_minority_time < rejoin_delay) {
            return;
        }
        ;
        server.cluster->state = new_state;
    }
}
static inline void removeAllNotOwnedShardChannelSubscriptions (){
    if (!kvstoreSize(server.pubsubshard_channels))
        return;
    clusterNode *currmaster = clusterNodeIsMaster(myself) ? myself : myself->slaveof;
}
extern void clusterSetMaster (clusterNode *n){
    (__builtin_expect(!!(n != myself), 1) ? (void)0 : (_serverAssert("n != myself", "cluster_legacy_InstSlice.c", 2564) , abort()));
    (__builtin_expect(!!(myself->numslots == 0), 1) ? (void)0 : (_serverAssert("myself->numslots == 0", "cluster_legacy_InstSlice.c", 2565) , abort()));
    if (clusterNodeIsMaster(myself)) {
        ;
    } else {
        if (myself->slaveof)
            clusterNodeRemoveSlave(myself->slaveof, myself);
    }
    ;
    updateShardId(myself, n->shard_id);
    clusterNodeAddSlave(n, myself);
    removeAllNotOwnedShardChannelSubscriptions();
    resetManualFailover();
}
extern sds representClusterNodeFlags (sds ci, uint16_t flags){
    size_t orig_len = sdslen(ci);
    int i, size = sizeof (redisNodeFlagsTable) / sizeof(struct redisNodeFlags);
    for (i = 0; i < size; i++) {
        struct redisNodeFlags *nodeflag = redisNodeFlagsTable + i;
        if (flags & nodeflag->flag)
            ci = sdscat(ci, nodeflag->name);
    }
    if (sdslen(ci) == orig_len)
        ci = sdscat(ci, "noflags,");
    return ci;
}
extern sds representSlotInfo (sds ci, uint16_t *slot_info_pairs, int slot_info_pairs_count){
    for (int i = 0; i < slot_info_pairs_count; i += 2) {
        unsigned long start = slot_info_pairs[i];
        unsigned long end = slot_info_pairs[i + 1];
        if (start == end) {
            ci = sdscatfmt(ci, " %i", start);
        } else {
            ci = sdscatfmt(ci, " %i-%i", start, end);
        }
    }
    return ci;
}
extern sds clusterGenNodeDescription (client *c, clusterNode *node, int tls_primary){
    int j, start;
    sds ci;
    int port = clusterNodeClientPort(node, tls_primary);
    ci = sdscatlen(sdsempty(), node->name, 40);
    ci = sdscatfmt(ci, " %s:%i@%i", node->ip, port, node->cport);
    if (sdslen(node->hostname) != 0) {
        ci = sdscatfmt(ci, ",%s", node->hostname);
    }
    if (c == ((void *)0)) {
        if (sdslen(node->hostname) == 0) {
            ci = sdscatfmt(ci, ",", 1);
        }
        for (int i = af_count - 1; i >= 0; i--) {
            if ((tls_primary && i == af_tls_port) || (!tls_primary && i == af_tcp_port)) {
                continue;
            }
            if (auxFieldHandlers[i].isPresent(node)) {
                ci = sdscatprintf(ci, ",%s=", auxFieldHandlers[i].field);
                ci = auxFieldHandlers[i].getter(node, ci);
            }
        }
    }
    ci = sdscatlen(ci, " ", 1);
    ci = representClusterNodeFlags(ci, node->flags);
    ci = sdscatlen(ci, " ", 1);
    if (node->slaveof) {
        ci = sdscatlen(ci, node->slaveof->name, 40);
    } else
        ci = sdscatlen(ci, "-", 1);
    unsigned long long nodeEpoch = node->configEpoch;
    if (((node)->flags & 2) && node->slaveof) {
        nodeEpoch = node->slaveof->configEpoch;
    }
    ci = sdscatfmt(ci, " %I %I %U %s", (long long)node->ping_sent, (long long)node->pong_received, nodeEpoch, (node->link || node->flags & 16) ? "connected" : "disconnected");
    if (node->slot_info_pairs) {
        ci = representSlotInfo(ci, node->slot_info_pairs, node->slot_info_pairs_count);
    } else if (node->numslots > 0) {
        start = -1;
        for (j = 0; j < (1 << 14); j++) {
            int bit;
            if ((bit = clusterNodeCoversSlot(node, j)) != 0) {
                if (start == -1)
                    start = j;
            }
            if (start != -1 && (!bit || j == (1 << 14) - 1)) {
                if (bit && j == (1 << 14) - 1)
                    j++;
                if (start == j - 1) {
                    ci = sdscatfmt(ci, " %i", start);
                } else {
                    ci = sdscatfmt(ci, " %i-%i", start, j - 1);
                }
                start = -1;
            }
        }
    }
    if (node->flags & 16) {
        for (j = 0; j < (1 << 14); j++) {
            if (server.cluster->migrating_slots_to[j]) {
                ci = sdscatprintf(ci, " [%d->-%.40s]", j, server.cluster->migrating_slots_to[j]->name);
            } else if (server.cluster->importing_slots_from[j]) {
                ci = sdscatprintf(ci, " [%d-<-%.40s]", j, server.cluster->importing_slots_from[j]->name);
            }
        }
    }
    return ci;
}
extern void clusterGenNodesSlotsInfo (int filter){
    clusterNode *n = ((void *)0);
    int start = -1;
    for (int i = 0; i <= (1 << 14); i++) {
        if (n == ((void *)0)) {
            if (i == (1 << 14))
                break;
            n = server.cluster->slots[i];
            start = i;
            continue;
        }
        if (i == (1 << 14) || n != server.cluster->slots[i]) {
            if (!(n->flags & filter)) {
                (__builtin_expect(!!((n->slot_info_pairs_count + 1) < (2 * n->numslots)), 1) ? (void)0 : (_serverAssert("(n->slot_info_pairs_count + 1) < (2 * n->numslots)", "cluster_legacy_InstSlice.c", 2747) , abort()));
                n->slot_info_pairs[n->slot_info_pairs_count++] = start;
                n->slot_info_pairs[n->slot_info_pairs_count++] = i - 1;
            }
            if (i == (1 << 14))
                break;
            n = server.cluster->slots[i];
            start = i;
        }
    }
}
extern void clusterFreeNodesSlotsInfo (clusterNode *n){
    ;
    n->slot_info_pairs = ((void *)0);
    n->slot_info_pairs_count = 0;
}
extern sds clusterGenNodesDescription (client *c, int filter, int tls_primary){
    sds ci = sdsempty(), ni;
    dictIterator di;
    dictEntry *de;
    clusterGenNodesSlotsInfo(filter);
    while ((de = dictNext(&di)) != ((void *)0))
        {
            clusterNode *node = dictGetVal(de);
            if (node->flags & filter)
                continue;
            ni = clusterGenNodeDescription(c, node, tls_primary);
            ci = sdscatsds(ci, ni);
            ci = sdscatlen(ci, "\n", 1);
            clusterFreeNodesSlotsInfo(node);
        }
    ;
    return ci;
}
extern int clusterNodeIsMaster (clusterNode *n){
    return n->flags & 1;
}
extern int clusterNodeNumSlaves (clusterNode *node){
    return node->numslaves;
}
extern clusterNode * clusterNodeGetSlave (clusterNode *node, int slave_idx){
    return node->slaves[slave_idx];
}
