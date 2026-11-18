#include "header_func.h"
#include "connection.h"
static ConnectionType * connTypeOfReplication (){
    if (server.tls_replication) {
        return connectionTypeTls();
    }
    return connectionTypeTcp();
}
extern char * replicationGetSlaveName (client *c){
    static char buf[288];
    char ip[46];
    ip[0] = '\x00';
    buf[0] = '\x00';
    if (c->slave_addr || connAddrPeerName(c->conn, ip, sizeof (ip), ((void *)0)) != -1) {
        char *addr = c->slave_addr ? c->slave_addr : ip;
    } else {
        ;
    }
    return buf;
}
extern int bg_unlink (const char *filename){
    int fd = open(filename, 0 | 2048);
    if (fd == -1) {
        return unlink(filename);
    } else {
        int retval = unlink(filename);
        if (retval == -1) {
            int old_errno = (*__errno_location());
            (*__errno_location()) = old_errno;
            return -1;
        }
        ;
        return 0;
    }
}
extern void freeReplicationBacklog (){
    (__builtin_expect(!!(((server.slaves)->len) == 0), 1) ? (void)0 : (_serverAssert("listLength(server.slaves) == 0", "replication_InstSlice.c", 146) , abort()));
    if (server.repl_backlog == ((void *)0))
        return;
    if (server.repl_backlog->ref_repl_buf_node) {
        replBufBlock *o = ((server.repl_backlog->ref_repl_buf_node)->value);
        (__builtin_expect(!!(o->refcount == 1), 1) ? (void)0 : (_serverAssert("o->refcount == 1", "replication_InstSlice.c", 153) , abort()));
        o->refcount--;
    }
    ;
    resetReplicationBuffer();
    server.repl_backlog = ((void *)0);
}
extern void resetReplicationBuffer (){
    server.repl_buffer_mem = 0;
    server.repl_buffer_blocks = listCreate();
    ((server.repl_buffer_blocks)->free = (zfree));
}
extern int canFeedReplicaReplBuffer (client *replica){
    if (replica->flags & (1ULL << 42))
        return 0;
    if (replica->replstate == 6 || replica->replstate == 11)
        return 0;
    if (replica->flags & (1 << 10))
        return 0;
    return 1;
}
extern int prepareReplicasToWrite (){
    listIter li;
    listNode *ln;
    int prepared = 0;
    while ((ln = listNext(&li)))
        {
            client *slave = ln->value;
            if (!canFeedReplicaReplBuffer(slave))
                continue;
            if (prepareClientToWrite(slave) == -1)
                continue;
            prepared++;
        }
    return prepared;
}
extern void feedReplicationBufferWithObject (robj *o){
    char llstr[21];
    void *p;
    size_t len;
    if (o->encoding == 1) {
        len = ll2string(llstr, sizeof (llstr), (long)o->ptr);
        p = llstr;
    } else {
        len = sdslen(o->ptr);
        p = o->ptr;
    }
    feedReplicationBuffer(p, len);
}
extern void incrementalTrimReplicationBacklog (size_t max_blocks){
    (__builtin_expect(!!(server.repl_backlog != ((void *)0)), 1) ? (void)0 : (_serverAssert("server.repl_backlog != NULL", "replication_InstSlice.c", 242) , abort()));
    size_t trimmed_blocks = 0;
    while (server.repl_backlog->histlen > server.repl_backlog_size && trimmed_blocks < max_blocks)
        {
            if (((server.repl_buffer_blocks)->len) <= 1)
                break;
            listNode *first = ((server.repl_buffer_blocks)->head);
            (__builtin_expect(!!(first == server.repl_backlog->ref_repl_buf_node), 1) ? (void)0 : (_serverAssert("first == server.repl_backlog->ref_repl_buf_node", "replication_InstSlice.c", 258) , abort()));
            replBufBlock *fo = ((first)->value);
            if (fo->refcount != 1)
                break;
            if (server.repl_backlog->histlen - (long long)fo->size <= server.repl_backlog_size)
                break;
            fo->refcount--;
            trimmed_blocks++;
            listNode *next = ((first)->next);
            (__builtin_expect(!!(server.repl_backlog->ref_repl_buf_node != ((void *)0)), 1) ? (void)0 : (_serverAssert("server.repl_backlog->ref_repl_buf_node != NULL", "replication_InstSlice.c", 276) , abort()));
            ((replBufBlock *)((next)->value))->refcount++;
            uint64_t encoded_offset = intrev64(fo->repl_offset);
            (__builtin_expect(!!(fo->refcount == 0 && fo->used == fo->size), 1) ? (void)0 : (_serverAssert("fo->refcount == 0 && fo->used == fo->size", "replication_InstSlice.c", 285) , abort()));
            server.repl_buffer_mem -= (fo->size + sizeof(listNode) + sizeof(replBufBlock));
        }
    ;
}
extern void feedReplicationBuffer (char *s, size_t len){
    static long long repl_block_id;
    if (server.repl_backlog == ((void *)0))
        return;
    while (len > 0)
        {
            size_t start_pos = 0;
            listNode *start_node = ((void *)0);
            int add_new_block = 0;
            listNode *ln = ((server.repl_buffer_blocks)->tail);
            replBufBlock *tail = ln ? ((ln)->value) : ((void *)0);
            if (tail && tail->size > tail->used) {
                start_node = ((server.repl_buffer_blocks)->tail);
                start_pos = tail->used;
                size_t avail = tail->size - tail->used;
                size_t copy = (avail >= len) ? len : avail;
                tail->used += copy;
                s += copy;
                len -= copy;
                server.master_repl_offset += copy;
            }
            if (len) {
                size_t usable_size;
                size_t limit = (((size_t)server.repl_backlog_size / 16) > ((size_t)(16 * 1024)) ? ((size_t)server.repl_backlog_size / 16) : ((size_t)(16 * 1024)));
                size_t size = ((((len) > ((size_t)(16 * 1024)) ? (len) : ((size_t)(16 * 1024)))) < (limit) ? (((len) > ((size_t)(16 * 1024)) ? (len) : ((size_t)(16 * 1024)))) : (limit));
                tail = zmalloc_usable(size + sizeof(replBufBlock), &usable_size);
                tail->size = usable_size - sizeof(replBufBlock);
                size_t copy = (tail->size >= len) ? len : tail->size;
                tail->used = copy;
                tail->refcount = 0;
                tail->repl_offset = server.master_repl_offset + 1;
                tail->id = repl_block_id++;
                server.repl_buffer_mem += (usable_size + sizeof(listNode));
                add_new_block = 1;
                if (start_node == ((void *)0)) {
                    start_node = ((server.repl_buffer_blocks)->tail);
                    start_pos = 0;
                }
                s += copy;
                len -= copy;
                server.master_repl_offset += copy;
            }
            listIter li;
            while ((ln = listNext(&li)))
                {
                    client *slave = ln->value;
                    if (!canFeedReplicaReplBuffer(slave))
                        continue;
                    if (slave->ref_repl_buf_node == ((void *)0)) {
                        slave->ref_repl_buf_node = start_node;
                        slave->ref_block_pos = start_pos;
                        ((replBufBlock *)((start_node)->value))->refcount++;
                    }
                    ;
                }
            if (server.repl_backlog->ref_repl_buf_node == ((void *)0)) {
                ;
                ((replBufBlock *)((start_node)->value))->refcount++;
                (__builtin_expect(!!(add_new_block == 1 && start_pos == 0), 1) ? (void)0 : (_serverAssert("add_new_block == 1 && start_pos == 0", "replication_InstSlice.c", 391) , abort()));
            }
            if (add_new_block) {
                ;
                incrementalTrimReplicationBacklog(64);
            }
        }
}
extern void replicationFeedSlaves (list *slaves, int dictid, robj **argv, int argc){
    int j, len;
    char llstr[21];
    (__builtin_expect(!!(dictid == -1 || (dictid >= 0 && dictid < server.dbnum)), 1) ? (void)0 : (_serverAssert("dictid == -1 || (dictid >= 0 && dictid < server.dbnum)", "replication_InstSlice.c", 417) , abort()));
    if (server.masterhost != ((void *)0))
        return;
    if (server.repl_backlog == ((void *)0) && ((slaves)->len) == 0) {
        server.master_repl_offset += 1;
        return;
    }
    (__builtin_expect(!!(!(((slaves)->len) != 0 && server.repl_backlog == ((void *)0))), 1) ? (void)0 : (_serverAssert("!(listLength(slaves) != 0 && server.repl_backlog == NULL)", "replication_InstSlice.c", 437) , abort()));
    server.repl_stream_lastio = server.unixtime;
    prepareReplicasToWrite();
    if (dictid != -1 && server.slaveseldb != dictid) {
        robj *selectcmd;
        if (dictid >= 0 && dictid < 10) {
            selectcmd = shared.select[dictid];
        } else {
            int dictid_len;
            dictid_len = ll2string(llstr, sizeof (llstr), dictid);
            selectcmd = createObject(0, sdscatprintf(sdsempty(), "*2\r\n$6\r\nSELECT\r\n$%d\r\n%s\r\n", dictid_len, llstr));
        }
        feedReplicationBufferWithObject(selectcmd);
        clusterSlotStatsDecrNetworkBytesOutForReplication(sdslen(selectcmd->ptr));
        server.slaveseldb = dictid;
    }
    char aux[24];
    aux[0] = '*';
    len = ll2string(aux + 1, sizeof (aux) - 1, argc);
    feedReplicationBuffer(aux, len + 3);
    for (j = 0; j < argc; j++) {
        long objlen = stringObjectLen(argv[j]);
        aux[0] = '$';
        len = ll2string(aux + 1, sizeof (aux) - 1, objlen);
        feedReplicationBuffer(aux, len + 3);
        feedReplicationBufferWithObject(argv[j]);
        feedReplicationBuffer(aux + len + 1, 2);
    }
}
extern long long getPsyncInitialOffset (){
    return server.master_repl_offset;
}
extern int replicationSetupSlaveForFullResync (client *slave, long long offset){
    char buf[128];
    int buflen;
    slave->psync_initial_offset = offset;
    slave->replstate = 7;
    server.slaveseldb = -1;
    if (!(slave->flags & (1 << 16))) {
        if (slave->flags & (1ULL << 51)) {
            uint64_t id = slave->main_ch_client_id;
            client *c = lookupClientByID(id);
            if (c && c->replstate == 11) {
                c->replstate = 12;
                do {
                    if (((2) & 255) < server.verbosity)
                        break;
                    _serverLog(2, "Starting to deliver RDB and replication stream to replica: %s", replicationGetSlaveName(c));
                } while (0);
            } else {
                do {
                    if (((3) & 255) < server.verbosity)
                        break;
                    _serverLog(3, "Starting to deliver RDB to replica %s but it has no associated main channel", replicationGetSlaveName(slave));
                } while (0);
            }
        }
        ;
    }
    return 0;
}
extern int startBgsaveForReplication (int mincapa, int req){
    int retval;
    int socket_target = 0;
    listIter li;
    listNode *ln;
    socket_target = (server.repl_diskless_sync || req & ((1 << 0) | (1 << 1))) && (mincapa & (1 << 0));
    (__builtin_expect(!!(socket_target || !(req & ((1 << 0) | (1 << 1)))), 1) ? (void)0 : (_serverAssert("socket_target || !(req & SLAVE_REQ_RDB_MASK)", "replication_InstSlice.c", 611) , abort()));
    rdbSaveInfo rsi, *rsiptr;
    rsiptr = rdbPopulateSaveInfo(&rsi);
    if (rsiptr) {
        if (socket_target) {
            retval = rdbSaveToSlavesSockets(req, rsiptr);
        } else {
            retval = rdbSaveBackground(req, server.rdb_filename, rsiptr, (1 << 1) | (1 << 4));
        }
        ;
    } else {
        ;
        retval = -1;
    }
    if (retval == 0 && !socket_target && server.rdb_del_sync_files)
        RDBGeneratedByReplication = 1;
    if (retval == -1) {
        ;
        while ((ln = listNext(&li)))
            {
                client *slave = ln->value;
                if (slave->replstate == 6) {
                    slave->replstate = REPL_STATE_NONE;
                    slave->flags &= ~(1 << 0);
                    slave->flags |= (1 << 6);
                }
            }
        return retval;
    }
    if (!socket_target) {
        ;
        while ((ln = listNext(&li)))
            {
                client *slave = ln->value;
                if (slave->replstate == 6) {
                    if (slave->slave_req != req)
                        continue;
                    replicationSetupSlaveForFullResync(slave, getPsyncInitialOffset());
                }
            }
    }
    return retval;
}
extern void removeRDBUsedToSyncReplicas (){
    if (!server.rdb_del_sync_files) {
        ;
        return;
    }
    if (allPersistenceDisabled() && RDBGeneratedByReplication) {
        client *slave;
        listNode *ln;
        listIter li;
        int delrdb = 1;
        while ((ln = listNext(&li)))
            {
                slave = ln->value;
                if (slave->replstate == 6 || slave->replstate == 7 || slave->replstate == 8) {
                    delrdb = 0;
                    break;
                }
            }
        if (delrdb) {
            struct stat sb;
            if (lstat(server.rdb_filename, &sb) != -1) {
                RDBGeneratedByReplication = 0;
                bg_unlink(server.rdb_filename);
            }
        }
    }
}
extern void changeReplicationId (){
    ;
    server.replid[40] = '\x00';
}
extern void clearReplicationId2 (){
    memset(server.replid2, '0', sizeof (server.replid));
    server.replid2[40] = '\x00';
    server.second_replid_offset = -1;
}
extern void shiftReplicationId (){
    memcpy(server.replid2, server.replid, sizeof (server.replid));
    server.second_replid_offset = server.master_repl_offset + 1;
    changeReplicationId();
}
extern int slaveIsInHandshakeState (){
    return server.repl_state >= REPL_STATE_RECEIVE_PING_REPLY && server.repl_state <= REPL_STATE_RECEIVE_PSYNC_REPLY;
}
extern void replicationCreateMasterClient (connection *conn, int dbid){
    server.master = createClient(conn);
    server.master->flags |= (1 << 1);
    server.master->querybuf = sdsempty();
    server.master->authenticated = 1;
    server.master->reploff = server.master_initial_offset;
    server.master->read_reploff = server.master->reploff;
    server.master->user = ((void *)0);
    if (server.master->reploff == -1)
        server.master->flags |= (1 << 16);
}
extern int connectWithMaster (){
    server.repl_current_sync_attempts++;
    server.repl_total_sync_attempts++;
    server.repl_transfer_s = connCreate(server.el, connTypeOfReplication());
    if (connConnect(server.repl_transfer_s, server.masterhost, server.masterport, server.bind_source_addr, syncWithMaster) == -1) {
        ;
        connClose(server.repl_transfer_s);
        server.repl_transfer_s = ((void *)0);
        return -1;
    }
    server.repl_transfer_lastio = server.unixtime;
    server.repl_state = REPL_STATE_CONNECTING;
    return 0;
}
extern void undoConnectWithMaster (){
    connClose(server.repl_transfer_s);
    server.repl_transfer_s = ((void *)0);
}
extern void replicationAbortSyncTransfer (){
    (__builtin_expect(!!(server.repl_state == REPL_STATE_TRANSFER), 1) ? (void)0 : (_serverAssert("server.repl_state == REPL_STATE_TRANSFER", "replication_InstSlice.c", 1060) , abort()));
    undoConnectWithMaster();
    if (server.repl_disconnect_start_time == 0)
        server.repl_disconnect_start_time = server.unixtime;
    if (server.repl_transfer_fd != -1) {
        ;
        bg_unlink(server.repl_transfer_tmpfile);
        server.repl_transfer_tmpfile = ((void *)0);
        server.repl_transfer_fd = -1;
    }
}
extern int cancelReplicationHandshake (int reconnect){
    if (rdbChannelAbort() != 0)
        return 1;
    if (server.repl_state == REPL_STATE_TRANSFER) {
        replicationAbortSyncTransfer();
        server.repl_state = REPL_STATE_CONNECT;
    } else if (server.repl_state == REPL_STATE_CONNECTING || slaveIsInHandshakeState()) {
        undoConnectWithMaster();
        server.repl_state = REPL_STATE_CONNECT;
    } else {
        ;
    }
    if (!reconnect)
        return 1;
    connectWithMaster();
    return 1;
}
extern void replicationSetMaster (char *ip, int port){
    int was_master = server.masterhost == ((void *)0);
    server.masterhost = sdsnew(ip);
    server.masterport = port;
    cancelReplicationHandshake(0);
    if (was_master) {
        replicationDiscardCachedMaster();
        replicationCacheMasterUsingMyself();
    }
    ;
    server.repl_state = REPL_STATE_CONNECT;
    server.repl_current_sync_attempts = 0;
    server.repl_total_sync_attempts = 0;
    connectWithMaster();
}
extern void replicationUnsetMaster (){
    if (server.masterhost == ((void *)0))
        return;
    server.masterhost = ((void *)0);
    replicationDiscardCachedMaster();
    cancelReplicationHandshake(0);
    shiftReplicationId();
    server.repl_state = REPL_STATE_NONE;
    server.repl_current_sync_attempts = 0;
    server.repl_total_sync_attempts = 0;
    server.slaveseldb = -1;
    server.repl_no_slaves_since = server.unixtime;
    server.repl_down_since = 0;
    server.repl_up_since = 0;
}
static void rdbChannelReplDataBufFree (){
    ;
    server.repl_full_sync_buffer.blocks = ((void *)0);
    server.repl_full_sync_buffer.size = 0;
    server.repl_full_sync_buffer.used = 0;
    server.repl_full_sync_buffer.last_num_blocks = 0;
    server.repl_full_sync_buffer.mem_used = 0;
}
static void rdbChannelCleanup (){
    server.repl_rdb_ch_state = REPL_RDB_CH_STATE_NONE;
    server.repl_main_ch_state = (1 << 0);
    rdbChannelReplDataBufFree();
}
static int rdbChannelAbort (){
    if (server.repl_rdb_ch_state == REPL_RDB_CH_STATE_NONE)
        return 0;
    int async_cleanup = (server.repl_rdb_transfer_s && server.loading) || (server.repl_main_ch_state & (1 << 2));
    if (async_cleanup) {
        ;
        server.repl_main_ch_state |= (1 << 3);
        return -1;
    }
    ;
    if (server.repl_rdb_transfer_s) {
        connClose(server.repl_rdb_transfer_s);
        server.repl_rdb_transfer_s = ((void *)0);
    }
    if (server.repl_transfer_fd != -1) {
        ;
        server.repl_transfer_fd = -1;
    }
    if (server.repl_transfer_tmpfile) {
        bg_unlink(server.repl_transfer_tmpfile);
        server.repl_transfer_tmpfile = ((void *)0);
    }
    rdbChannelCleanup();
    return 0;
}
extern void replicationSendAck (){
    client *c = server.master;
    if (c != ((void *)0)) {
        int send_fack = server.fsynced_reploff != -1;
        c->flags |= (1 << 13);
        c->flags &= ~(1 << 13);
        c->net_output_bytes_curr_cmd = 0;
    }
}
extern void replicationCacheMasterUsingMyself (){
    ;
    server.master_initial_offset = server.master_repl_offset;
    replicationCreateMasterClient(((void *)0), -1);
    server.cached_master = server.master;
    server.master = ((void *)0);
}
extern void replicationDiscardCachedMaster (){
    if (server.cached_master == ((void *)0))
        return;
    server.cached_master->flags &= ~(1 << 1);
    server.cached_master = ((void *)0);
}
extern void replicationCron (){
    updateFailoverStatus();
    if (server.masterhost && (server.repl_state == REPL_STATE_CONNECTING || slaveIsInHandshakeState()) && (time(((void *)0)) - server.repl_transfer_lastio) > server.repl_timeout) {
        ;
        cancelReplicationHandshake(1);
    }
    if (server.masterhost && server.repl_state == REPL_STATE_TRANSFER && (time(((void *)0)) - server.repl_transfer_lastio) > server.repl_timeout) {
        ;
        cancelReplicationHandshake(1);
    }
    if (server.repl_state == REPL_STATE_CONNECT) {
        ;
        connectWithMaster();
    }
    if (server.masterhost && server.master && !(server.master->flags & (1 << 16)))
        replicationSendAck();
    listIter li;
    listNode *ln;
    robj *ping_argv[1];
    if (server.masterhost == ((void *)0) && ((server.slaves)->len) && server.unixtime >= server.repl_stream_lastio + server.repl_ping_slave_period) {
        int manual_failover_in_progress = ((server.cluster_enabled && clusterManualFailoverTimeLimit()) || server.failover_end_time) && isPausedActionsWithUpdate((1 << 4));
        if (!manual_failover_in_progress) {
            ping_argv[0] = shared.ping;
            replicationFeedSlaves(server.slaves, -1, ping_argv, 1);
        }
    }
    ;
    while ((ln = listNext(&li)))
        {
            client *slave = ln->value;
            int is_presync = (slave->replstate == 6 || (slave->replstate == 7 && server.rdb_child_type != 2));
        }
    if (((server.slaves)->len)) {
        listIter li;
        listNode *ln;
        while ((ln = listNext(&li)))
            {
                client *slave = ln->value;
                if (slave->replstate == 9) {
                    if (slave->flags & (1 << 16))
                        continue;
                    if ((server.unixtime - slave->repl_ack_time) > server.repl_timeout) {
                        do {
                            if (((3) & 255) < server.verbosity)
                                break;
                            _serverLog(3, "Disconnecting timedout replica (streaming sync): %s", replicationGetSlaveName(slave));
                        } while (0);
                        continue;
                    }
                }
                if (slave->replstate == 7 && server.rdb_child_type == 2) {
                    if (slave->repl_last_partial_write != 0 && (server.unixtime - slave->repl_last_partial_write) > server.repl_timeout) {
                        do {
                            if (((3) & 255) < server.verbosity)
                                break;
                            _serverLog(3, "Disconnecting timedout replica (full sync): %s", replicationGetSlaveName(slave));
                        } while (0);
                        continue;
                    }
                }
            }
    }
    if (((server.slaves)->len) == 0 && server.repl_backlog_time_limit && server.repl_backlog && server.masterhost == ((void *)0)) {
        time_t idle = server.unixtime - server.repl_no_slaves_since;
        if (idle > server.repl_backlog_time_limit) {
            changeReplicationId();
            clearReplicationId2();
            freeReplicationBacklog();
        }
    }
    replicationStartPendingFork();
    removeRDBUsedToSyncReplicas();
}
extern int shouldStartChildReplication (int *mincapa_out, int *req_out){
    if (!hasActiveChildProcess()) {
        time_t idle, max_idle = 0;
        int slaves_waiting = 0;
        int mincapa;
        int req;
        int first = 1;
        listNode *ln;
        listIter li;
        while ((ln = listNext(&li)))
            {
                client *slave = ln->value;
                if (slave->replstate == 6) {
                    if (first) {
                        req = slave->slave_req;
                    } else if (req != slave->slave_req) {
                        continue;
                    }
                    idle = server.unixtime - slave->lastinteraction;
                    if (idle > max_idle)
                        max_idle = idle;
                    slaves_waiting++;
                    mincapa = first ? slave->slave_capa : (mincapa & slave->slave_capa);
                    first = 0;
                }
            }
        if (slaves_waiting && (!server.repl_diskless_sync || (server.repl_diskless_sync_max_replicas > 0 && slaves_waiting >= server.repl_diskless_sync_max_replicas) || max_idle >= server.repl_diskless_sync_delay)) {
            if (mincapa_out)
                *mincapa_out = mincapa;
            if (req_out)
                *req_out = req;
            return 1;
        }
    }
    return 0;
}
extern void replicationStartPendingFork (){
    int mincapa = -1;
    int req = -1;
    if (shouldStartChildReplication(&mincapa, &req)) {
        startBgsaveForReplication(mincapa, req);
    }
}
static client * findReplica (char *host, int port){
    listIter li;
    listNode *ln;
    client *replica;
    while ((ln = listNext(&li)))
        {
            replica = ln->value;
            char ip[46], *replicaip = replica->slave_addr;
            if (!replicaip) {
                if (connAddrPeerName(replica->conn, ip, sizeof (ip), ((void *)0)) == -1)
                    continue;
                replicaip = ip;
            }
            if (!strcasecmp(host, replicaip) && (port == replica->slave_listening_port))
                return replica;
        }
    return ((void *)0);
}
extern void clearFailoverState (){
    server.failover_end_time = 0;
    server.force_failover = 0;
    server.target_replica_host = ((void *)0);
    server.target_replica_port = 0;
    server.failover_state = NO_FAILOVER;
}
extern void abortFailover (const char *err){
    if (server.failover_state == NO_FAILOVER)
        return;
    if (server.failover_state == FAILOVER_IN_PROGRESS) {
        replicationUnsetMaster();
    }
    clearFailoverState();
}
extern void updateFailoverStatus (){
    if (server.failover_state != FAILOVER_WAIT_FOR_SYNC)
        return;
    mstime_t now = server.mstime;
    if (server.failover_end_time && server.failover_end_time <= now) {
        if (server.force_failover) {
            ;
            server.failover_state = FAILOVER_IN_PROGRESS;
            replicationSetMaster(server.target_replica_host, server.target_replica_port);
            return;
        } else {
            abortFailover("Replica never caught up before timeout");
            return;
        }
    }
    client *replica = ((void *)0);
    if (server.target_replica_host) {
        replica = findReplica(server.target_replica_host, server.target_replica_port);
    } else {
        listIter li;
        listNode *ln;
        while ((ln = listNext(&li)))
            {
                replica = ln->value;
                if (replica->repl_ack_off == server.master_repl_offset) {
                    char ip[46], *replicaaddr = replica->slave_addr;
                    if (!replicaaddr) {
                        if (connAddrPeerName(replica->conn, ip, sizeof (ip), ((void *)0)) == -1)
                            continue;
                        replicaaddr = ip;
                    }
                    server.target_replica_host = zstrdup(replicaaddr);
                    server.target_replica_port = replica->slave_listening_port;
                    break;
                }
            }
    }
    if (replica && (replica->repl_ack_off == server.master_repl_offset)) {
        server.failover_state = FAILOVER_IN_PROGRESS;
        replicationSetMaster(server.target_replica_host, server.target_replica_port);
    }
}
