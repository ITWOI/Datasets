#ifndef __HEADER_TYPE_H__ 
#define __HEADER_TYPE_H__
#include"../common.h" 
/*TD*/typedef char *sds;

struct sdshdr8;//insertRecordDeclare 


struct sdshdr8 {
    uint8_t len;
    uint8_t alloc;
    unsigned char flags;
    char buf[];
};

struct sdshdr16;//insertRecordDeclare 


struct sdshdr16 {
    uint16_t len;
    uint16_t alloc;
    unsigned char flags;
    char buf[];
};

struct sdshdr32;//insertRecordDeclare 


struct sdshdr32 {
    uint32_t len;
    uint32_t alloc;
    unsigned char flags;
    char buf[];
};

struct sdshdr64;//insertRecordDeclare 


struct sdshdr64 {
    uint64_t len;
    uint64_t alloc;
    unsigned char flags;
    char buf[];
};

struct connection;//insertRecordDeclare 

/*TD*/typedef struct connection connection;

/*TD*/typedef void (*ConnectionCallbackFunc)(struct connection *);

struct ConnectionType;//insertRecordDeclare 

/*TD*/typedef struct ConnectionType ConnectionType;


typedef enum {
    CONN_STATE_NONE = 0,
    CONN_STATE_CONNECTING,
    CONN_STATE_ACCEPTING,
    CONN_STATE_CONNECTED,
    CONN_STATE_CLOSED,
    CONN_STATE_ERROR
} ConnectionState;

struct aeEventLoop;//insertRecordDeclare 


struct connection {
    ConnectionType *type;
    ConnectionState state;
    int last_errno;
    int fd;
    short flags;
    short refs;
    unsigned short iovcnt;
    void *private_data;
    struct aeEventLoop *el;
    ConnectionCallbackFunc conn_handler;
    ConnectionCallbackFunc write_handler;
    ConnectionCallbackFunc read_handler;
};

/*TD*/typedef void (aeFileProc)(struct aeEventLoop *, int, void *, int);

struct connListener;//insertRecordDeclare 

/*TD*/typedef struct connListener connListener;

struct iovec;//insertRecordDeclare 

/*TD*/typedef struct aeEventLoop aeEventLoop;


struct ConnectionType {
    const char *(*get_type)(struct connection *);
    void (*init)(void);
    void (*cleanup)(void);
    int (*configure)(void *, int);
    void (*ae_handler)(struct aeEventLoop *, int, void *, int);
    aeFileProc *accept_handler;
    int (*addr)(connection *, char *, size_t, int *, int);
    int (*is_local)(connection *);
    int (*listen)(connListener *);
    connection *(*conn_create)(struct aeEventLoop *);
    connection *(*conn_create_accepted)(struct aeEventLoop *, int, void *);
    void (*shutdown)(struct connection *);
    void (*close)(struct connection *);
    int (*connect)(struct connection *, const char *, int, const char *, ConnectionCallbackFunc);
    int (*blocking_connect)(struct connection *, const char *, int, long long);
    int (*accept)(struct connection *, ConnectionCallbackFunc);
    int (*write)(struct connection *, const void *, size_t);
    int (*writev)(struct connection *, const struct iovec *, int);
    int (*read)(struct connection *, void *, size_t);
    int (*set_write_handler)(struct connection *, ConnectionCallbackFunc, int);
    int (*set_read_handler)(struct connection *, ConnectionCallbackFunc);
    const char *(*get_last_error)(struct connection *);
    ssize_t (*sync_write)(struct connection *, char *, ssize_t, long long);
    ssize_t (*sync_read)(struct connection *, char *, ssize_t, long long);
    ssize_t (*sync_readline)(struct connection *, char *, ssize_t, long long);
    void (*unbind_event_loop)(struct connection *);
    int (*rebind_event_loop)(struct connection *, aeEventLoop *);
    int (*has_pending_data)(struct aeEventLoop *);
    int (*process_pending_data)(struct aeEventLoop *);
    sds (*get_peer_cert)(struct connection *);
};

struct clusterLink;//insertRecordDeclare 

/*TD*/typedef struct clusterLink clusterLink;

struct _clusterNode;//insertRecordDeclare 

/*TD*/typedef struct _clusterNode clusterNode;

union clusterMsgData;//insertRecordDeclare 


/*Ano*/typedef struct {
    char nodename[40];
    uint32_t ping_sent;
    uint32_t pong_received;
    char ip[46];
    uint16_t port;
    uint16_t cport;
    uint16_t flags;
    uint16_t pport;
    uint16_t notused1;
} clusterMsgDataGossip;


/*Ano*/typedef struct {
    char nodename[40];
} clusterMsgDataFail;


/*Ano*/typedef struct {
    uint32_t channel_len;
    uint32_t message_len;
    unsigned char bulk_data[8];
} clusterMsgDataPublish;


/*Ano*/typedef struct {
    uint64_t configEpoch;
    char nodename[40];
    unsigned char slots[2048];
} clusterMsgDataUpdate;


/*Ano*/typedef struct {
    uint64_t module_id;
    uint32_t len;
    uint8_t type;
    unsigned char bulk_data[3];
} clusterMsgModule;


union clusterMsgData {
    struct {
        clusterMsgDataGossip gossip[1];
    } ping;
    struct {
        clusterMsgDataFail about;
    } fail;
    struct {
        clusterMsgDataPublish msg;
    } publish;
    struct {
        clusterMsgDataUpdate nodecfg;
    } update;
    struct {
        clusterMsgModule msg;
    } module;
};


/*Ano*/typedef struct {
    char sig[4];
    uint32_t totlen;
    uint16_t ver;
    uint16_t port;
    uint16_t type;
    uint16_t count;
    uint64_t currentEpoch;
    uint64_t configEpoch;
    uint64_t offset;
    char sender[40];
    unsigned char myslots[2048];
    char slaveof[40];
    char myip[46];
    uint16_t extensions;
    char notused1[30];
    uint16_t pport;
    uint16_t cport;
    uint16_t flags;
    unsigned char state;
    unsigned char mflags[3];
    union clusterMsgData data;
} clusterMsg;

/*TD*/typedef long long mstime_t;

struct list;//insertRecordDeclare 

/*TD*/typedef struct list list;


struct _clusterNode {
    mstime_t ctime;
    char name[40];
    char shard_id[40];
    int flags;
    uint64_t configEpoch;
    unsigned char slots[2048];
    uint16_t *slot_info_pairs;
    int slot_info_pairs_count;
    int numslots;
    int numslaves;
    clusterNode **slaves;
    clusterNode *slaveof;
    unsigned long long last_in_ping_gossip;
    mstime_t ping_sent;
    mstime_t pong_received;
    mstime_t data_received;
    mstime_t fail_time;
    mstime_t voted_time;
    mstime_t repl_offset_time;
    mstime_t orphaned_time;
    long long repl_offset;
    char ip[46];
    sds hostname;
    sds human_nodename;
    int tcp_port;
    int tls_port;
    int cport;
    clusterLink *link;
    clusterLink *inbound_link;
    list *fail_reports;
};

struct redisServer;//insertRecordDeclare 

struct redisDb;//insertRecordDeclare 

/*TD*/typedef struct redisDb redisDb;

struct dict;//insertRecordDeclare 

/*TD*/typedef struct dict dict;

struct rax;//insertRecordDeclare 

/*TD*/typedef struct rax rax;


struct connListener {
    int fd[16];
    int count;
    char **bindaddr;
    int bindaddr_count;
    int port;
    ConnectionType *ct;
    void *priv;
};

struct client;//insertRecordDeclare 

/*TD*/typedef struct client client;


/*Ano*/typedef struct {
    list *clients;
    size_t mem_usage_sum;
} clientMemUsageBucket;


/*Ano*/typedef struct {
    uint32_t paused_actions;
    mstime_t end;
} pause_event;

/*TD*/typedef uint64_t monotime;

struct malloc_stats;//insertRecordDeclare 


struct malloc_stats {
    size_t zmalloc_used;
    size_t process_rss;
    size_t allocator_allocated;
    size_t allocator_active;
    size_t allocator_resident;
    size_t allocator_muzzy;
    size_t allocator_frag_smallbins_bytes;
    size_t lua_allocator_allocated;
    size_t lua_allocator_active;
    size_t lua_allocator_resident;
    size_t lua_allocator_frag_smallbins_bytes;
};

struct durationStats;//insertRecordDeclare 

/*TD*/typedef struct durationStats durationStats;


struct durationStats {
    unsigned long long cnt;
    unsigned long long sum;
    unsigned long long max;
};

struct clientBufferLimitsConfig;//insertRecordDeclare 

/*TD*/typedef struct clientBufferLimitsConfig clientBufferLimitsConfig;


struct clientBufferLimitsConfig {
    unsigned long long hard_limit_bytes;
    unsigned long long soft_limit_bytes;
    time_t soft_limit_seconds;
};


typedef enum {
    AOF_FILE_TYPE_BASE = 'b',
    AOF_FILE_TYPE_HIST = 'h',
    AOF_FILE_TYPE_INCR = 'i'
} aof_file_type;


/*Ano*/typedef struct {
    sds file_name;
    long long file_seq;
    aof_file_type file_type;
    long long start_offset;
    long long end_offset;
} aofInfo;


/*Ano*/typedef struct {
    aofInfo *base_aof_info;
    list *incr_aof_list;
    list *history_aof_list;
    long long curr_base_file_seq;
    long long curr_incr_file_seq;
    int dirty;
} aofManifest;

struct saveparam;//insertRecordDeclare 

struct redisOpArray;//insertRecordDeclare 

/*TD*/typedef struct redisOpArray redisOpArray;

struct redisOp;//insertRecordDeclare 

/*TD*/typedef struct redisOp redisOp;


struct redisOpArray {
    redisOp *ops;
    int numops;
    int capacity;
};

struct replBacklog;//insertRecordDeclare 

/*TD*/typedef struct replBacklog replBacklog;

struct replDataBuf;//insertRecordDeclare 

/*TD*/typedef struct replDataBuf replDataBuf;


struct replDataBuf {
    list *blocks;
    size_t mem_used;
    size_t size;
    size_t used;
    size_t peak;
    size_t last_num_blocks;
};

/*TD*/typedef long long ustime_t;

struct _kvstore;//insertRecordDeclare 

/*TD*/typedef struct _kvstore kvstore;

struct clusterState;//insertRecordDeclare 

struct aclInfo;//insertRecordDeclare 

/*TD*/typedef struct aclInfo aclInfo;


struct aclInfo {
    long long user_auth_failures;
    long long invalid_cmd_accesses;
    long long invalid_key_accesses;
    long long invalid_channel_accesses;
};

struct redisTLSContextConfig;//insertRecordDeclare 

/*TD*/typedef struct redisTLSContextConfig redisTLSContextConfig;


struct redisTLSContextConfig {
    char *cert_file;
    char *key_file;
    char *key_file_pass;
    char *client_cert_file;
    char *client_key_file;
    char *client_key_file_pass;
    char *dh_params_file;
    char *ca_cert_file;
    char *ca_cert_dir;
    char *protocols;
    char *ciphers;
    char *ciphersuites;
    int prefer_server_ciphers;
    int session_caching;
    int session_cache_size;
    int session_cache_timeout;
};

struct sentinelConfig;//insertRecordDeclare 


struct redisServer {
    pid_t pid;
    pthread_t main_thread_id;
    char *configfile;
    char *executable;
    char **exec_argv;
    int dynamic_hz;
    int config_hz;
    mode_t umask;
    int hz;
    int in_fork_child;
    redisDb *db;
    dict *commands;
    dict *orig_commands;
    aeEventLoop *el;
    rax *errors;
    int errors_enabled;
    unsigned int lruclock;
    _Atomic(int) shutdown_asap;
    _Atomic(int) crashing;
    mstime_t shutdown_mstime;
    _Atomic(int) last_sig_received;
    int shutdown_flags;
    int activerehashing;
    int active_defrag_running;
    char *pidfile;
    int arch_bits;
    int cronloops;
    char runid[41];
    int sentinel_mode;
    size_t initial_memory_usage;
    int always_show_logo;
    int in_exec;
    int busy_module_yield_flags;
    const char *busy_module_yield_reply;
    char *ignore_warnings;
    int client_pause_in_transaction;
    int thp_enabled;
    size_t page_size;
    _Atomic(int) running;
    dict *moduleapi;
    dict *sharedapi;
    dict *module_configs_queue;
    list *loadmodule_queue;
    int module_pipe[2];
    pid_t child_pid;
    int child_type;
    _Atomic(int) module_gil_acquring;
    int port;
    int tls_port;
    int tcp_backlog;
    char *bindaddr[16];
    int bindaddr_count;
    char *bind_source_addr;
    char *unixsocket;
    unsigned int unixsocketperm;
    connListener listeners[8];
    uint32_t socket_mark_id;
    connListener clistener;
    list *clients;
    list *clients_to_close;
    list *clients_pending_write;
    list *clients_pending_read;
    list *slaves;
    list *monitors;
    client *current_client;
    client *executing_client;
    clientMemUsageBucket *client_mem_usage_buckets;
    rax *clients_timeout_table;
    int execution_nesting;
    rax *clients_index;
    uint32_t paused_actions;
    list *postponed_clients;
    pause_event client_pause_per_purpose[3];
    char neterr[256];
    dict *migrate_cached_sockets;
    _Atomic(uint64_t) next_client_id;
    int protected_mode;
    int io_threads_num;
    int io_threads_clients_num[128];
    int io_threads_do_reads;
    int io_threads_active;
    int prefetch_batch_max_size;
    long long events_processed_while_blocked;
    int enable_protected_configs;
    int enable_debug_cmd;
    int enable_module_cmd;
    volatile sig_atomic_t loading;
    volatile sig_atomic_t async_loading;
    off_t loading_total_bytes;
    off_t loading_rdb_used_mem;
    off_t loading_loaded_bytes;
    time_t loading_start_time;
    off_t loading_process_events_interval_bytes;
    time_t stat_starttime;
    long long stat_numcommands;
    long long stat_numconnections;
    long long stat_expiredkeys;
    long long stat_expired_subkeys;
    double stat_expired_stale_perc;
    long long stat_expired_time_cap_reached_count;
    long long stat_expire_cycle_time_used;
    long long stat_evictedkeys;
    long long stat_evictedclients;
    long long stat_evictedscripts;
    long long stat_total_eviction_exceeded_time;
    monotime stat_last_eviction_exceeded_time;
    long long stat_keyspace_hits;
    long long stat_keyspace_misses;
    long long stat_active_defrag_hits;
    long long stat_active_defrag_misses;
    long long stat_active_defrag_key_hits;
    long long stat_active_defrag_key_misses;
    long long stat_active_defrag_scanned;
    long long stat_total_active_defrag_time;
    monotime stat_last_active_defrag_time;
    size_t stat_peak_memory;
    time_t stat_peak_memory_time;
    long long stat_aof_rewrites;
    long long stat_aofrw_consecutive_failures;
    long long stat_rdb_saves;
    long long stat_fork_time;
    double stat_fork_rate;
    long long stat_total_forks;
    long long stat_rejected_conn;
    long long stat_sync_full;
    long long stat_sync_partial_ok;
    long long stat_sync_partial_err;
    list *slowlog;
    long long slowlog_entry_id;
    long long slowlog_log_slower_than;
    unsigned long slowlog_max_len;
    struct malloc_stats cron_malloc_stats;
    _Atomic(long long) stat_net_input_bytes;
    _Atomic(long long) stat_net_output_bytes;
    _Atomic(long long) stat_net_repl_input_bytes;
    _Atomic(long long) stat_net_repl_output_bytes;
    size_t stat_current_cow_peak;
    size_t stat_current_cow_bytes;
    monotime stat_current_cow_updated;
    size_t stat_current_save_keys_processed;
    size_t stat_current_save_keys_total;
    size_t stat_rdb_cow_bytes;
    size_t stat_aof_cow_bytes;
    size_t stat_module_cow_bytes;
    double stat_module_progress;
    size_t stat_clients_type_memory[4];
    size_t stat_cluster_links_memory;
    long long stat_unexpected_error_replies;
    long long stat_total_error_replies;
    long long stat_dump_payload_sanitizations;
    _Atomic(long long) stat_io_reads_processed[128];
    _Atomic(long long) stat_io_writes_processed[128];
    _Atomic(long long) stat_client_qbuf_limit_disconnections;
    long long stat_client_outbuf_limit_disconnections;
    long long stat_cluster_incompatible_ops;
    long long stat_total_prefetch_entries;
    long long stat_total_prefetch_batches;
    struct {
        long long last_sample_base;
        long long last_sample_value;
        long long samples[16];
        int idx;
    } inst_metric[7];
    long long stat_reply_buffer_shrinks;
    long long stat_reply_buffer_expands;
    monotime el_start;
    long long el_cmd_cnt_start;
    long long el_cmd_cnt_max;
    monotime el_cron_duration;
    durationStats duration_stats[4];
    int verbosity;
    int hide_user_data_from_log;
    int maxidletime;
    int tcpkeepalive;
    int active_expire_enabled;
    int active_expire_effort;
    int allow_access_expired;
    int active_defrag_enabled;
    int sanitize_dump_payload;
    int skip_checksum_validation;
    int jemalloc_bg_thread;
    int active_defrag_configuration_changed;
    size_t active_defrag_ignore_bytes;
    int active_defrag_threshold_lower;
    int active_defrag_threshold_upper;
    int active_defrag_cycle_min;
    int active_defrag_cycle_max;
    unsigned long active_defrag_max_scan_fields;
    size_t client_max_querybuf_len;
    int dbnum;
    int supervised;
    int supervised_mode;
    int daemonize;
    int set_proc_title;
    char *proc_title_template;
    clientBufferLimitsConfig client_obuf_limits[3];
    int pause_cron;
    int dict_resizing;
    int latency_tracking_enabled;
    double *latency_tracking_info_percentiles;
    int latency_tracking_info_percentiles_len;
    unsigned int max_new_tls_conns_per_cycle;
    unsigned int max_new_conns_per_cycle;
    int cluster_compatibility_sample_ratio;
    int lazyexpire_nested_arbitrary_keys;
    int aof_enabled;
    int aof_state;
    int aof_fsync;
    char *aof_filename;
    char *aof_dirname;
    int aof_no_fsync_on_rewrite;
    int aof_rewrite_perc;
    off_t aof_rewrite_min_size;
    off_t aof_rewrite_base_size;
    off_t aof_current_size;
    off_t aof_last_incr_size;
    off_t aof_last_incr_fsync_offset;
    int aof_flush_sleep;
    int aof_rewrite_scheduled;
    sds aof_buf;
    int aof_fd;
    int aof_selected_db;
    mstime_t aof_flush_postponed_start;
    mstime_t aof_last_fsync;
    time_t aof_rewrite_time_last;
    time_t aof_rewrite_time_start;
    time_t aof_cur_timestamp;
    int aof_timestamp_enabled;
    int aof_lastbgrewrite_status;
    unsigned long aof_delayed_fsync;
    int aof_rewrite_incremental_fsync;
    int rdb_save_incremental_fsync;
    int aof_last_write_status;
    int aof_last_write_errno;
    int aof_load_truncated;
    int aof_use_rdb_preamble;
    _Atomic(int) aof_bio_fsync_status;
    _Atomic(int) aof_bio_fsync_errno;
    aofManifest *aof_manifest;
    int aof_disable_auto_gc;
    long long dirty;
    long long dirty_before_bgsave;
    long long rdb_last_load_keys_expired;
    long long rdb_last_load_keys_loaded;
    int bgsave_aborted;
    struct saveparam *saveparams;
    int saveparamslen;
    char *rdb_filename;
    int rdb_compression;
    int rdb_checksum;
    int rdb_del_sync_files;
    time_t lastsave;
    time_t lastbgsave_try;
    time_t rdb_save_time_last;
    time_t rdb_save_time_start;
    int rdb_bgsave_scheduled;
    int rdb_child_type;
    int lastbgsave_status;
    int stop_writes_on_bgsave_err;
    int rdb_pipe_read;
    int rdb_child_exit_pipe;
    connection **rdb_pipe_conns;
    int rdb_pipe_numconns;
    int rdb_pipe_numconns_writing;
    char *rdb_pipe_buff;
    int rdb_pipe_bufflen;
    int rdb_key_save_delay;
    int key_load_delay;
    int child_info_pipe[2];
    int child_info_nread;
    redisOpArray also_propagate;
    int replication_allowed;
    char *logfile;
    int syslog_enabled;
    char *syslog_ident;
    int syslog_facility;
    int crashlog_enabled;
    int memcheck_enabled;
    int use_exit_on_panic;
    int shutdown_timeout;
    int shutdown_on_sigint;
    int shutdown_on_sigterm;
    char replid[41];
    char replid2[41];
    long long master_repl_offset;
    long long second_replid_offset;
    _Atomic(long long) fsynced_reploff_pending;
    long long fsynced_reploff;
    int slaveseldb;
    int repl_ping_slave_period;
    replBacklog *repl_backlog;
    long long repl_backlog_size;
    long long repl_full_sync_buffer_limit;
    replDataBuf repl_full_sync_buffer;
    time_t repl_backlog_time_limit;
    time_t repl_no_slaves_since;
    int repl_min_slaves_to_write;
    int repl_min_slaves_max_lag;
    int repl_good_slaves_count;
    int repl_diskless_sync;
    int repl_diskless_load;
    int repl_diskless_sync_delay;
    int repl_diskless_sync_max_replicas;
    int repl_rdb_channel;
    int repl_debug_pause;
    size_t repl_buffer_mem;
    list *repl_buffer_blocks;
    time_t repl_stream_lastio;
    char *masteruser;
    sds masterauth;
    char *masterhost;
    int masterport;
    int repl_timeout;
    client *master;
    client *cached_master;
    int repl_syncio_timeout;
    int repl_state;
    int repl_rdb_ch_state;
    int repl_main_ch_state;
    uint64_t repl_num_master_disconnection;
    uint64_t repl_main_ch_client_id;
    off_t repl_transfer_size;
    off_t repl_transfer_read;
    off_t repl_transfer_last_fsync_off;
    connection *repl_transfer_s;
    connection *repl_rdb_transfer_s;
    int repl_transfer_fd;
    char *repl_transfer_tmpfile;
    time_t repl_transfer_lastio;
    int repl_serve_stale_data;
    int repl_slave_ro;
    int repl_slave_ignore_maxmemory;
    time_t repl_down_since;
    time_t repl_up_since;
    int repl_disable_tcp_nodelay;
    int slave_priority;
    int replica_announced;
    int slave_announce_port;
    char *slave_announce_ip;
    int propagation_error_behavior;
    int repl_ignore_disk_write_error;
    char master_replid[41];
    long long master_initial_offset;
    int repl_slave_lazy_flush;
    list *clients_waiting_acks;
    int get_ack_from_slaves;
    long long repl_current_sync_attempts;
    long long repl_total_sync_attempts;
    time_t repl_disconnect_start_time;
    time_t repl_total_disconnect_time;
    unsigned int maxclients;
    unsigned long long maxmemory;
    ssize_t maxmemory_clients;
    int maxmemory_policy;
    int maxmemory_samples;
    int maxmemory_eviction_tenacity;
    int lfu_log_factor;
    int lfu_decay_time;
    long long proto_max_bulk_len;
    int oom_score_adj_values[3];
    int oom_score_adj;
    int disable_thp;
    unsigned int blocked_clients;
    unsigned int blocked_clients_by_type[10];
    list *unblocked_clients;
    list *ready_keys;
    unsigned int tracking_clients;
    size_t tracking_table_max_keys;
    list *tracking_pending_keys;
    list *pending_push_messages;
    int sort_desc;
    int sort_alpha;
    int sort_bypattern;
    int sort_store;
    size_t hash_max_listpack_entries;
    size_t hash_max_listpack_value;
    size_t set_max_intset_entries;
    size_t set_max_listpack_entries;
    size_t set_max_listpack_value;
    size_t zset_max_listpack_entries;
    size_t zset_max_listpack_value;
    size_t hll_sparse_max_bytes;
    size_t stream_node_max_bytes;
    long long stream_node_max_entries;
    int list_max_listpack_size;
    int list_compress_depth;
    _Atomic(time_t) unixtime;
    time_t timezone;
    _Atomic(int) daylight_active;
    mstime_t mstime;
    ustime_t ustime;
    mstime_t cmd_time_snapshot;
    size_t blocking_op_nesting;
    long long blocked_last_cron;
    kvstore *pubsub_channels;
    dict *pubsub_patterns;
    int notify_keyspace_events;
    kvstore *pubsubshard_channels;
    unsigned int pubsub_clients;
    unsigned int watching_clients;
    int cluster_enabled;
    int cluster_port;
    mstime_t cluster_node_timeout;
    mstime_t cluster_ping_interval;
    char *cluster_configfile;
    struct clusterState *cluster;
    int cluster_migration_barrier;
    int cluster_allow_replica_migration;
    int cluster_slave_validity_factor;
    int cluster_require_full_coverage;
    int cluster_slave_no_failover;
    char *cluster_announce_ip;
    char *cluster_announce_hostname;
    char *cluster_announce_human_nodename;
    int cluster_preferred_endpoint_type;
    int cluster_announce_port;
    int cluster_announce_tls_port;
    int cluster_announce_bus_port;
    int cluster_module_flags;
    int cluster_allow_reads_when_down;
    int cluster_config_file_lock_fd;
    unsigned long long cluster_link_msg_queue_limit_bytes;
    int cluster_drop_packet_filter;
    int cluster_slot_stats_enabled;
    unsigned int lua_arena;
    mstime_t busy_reply_threshold;
    int pre_command_oom_state;
    int script_disable_deny_script;
    int lua_enable_deprecated_api;
    int lazyfree_lazy_eviction;
    int lazyfree_lazy_expire;
    int lazyfree_lazy_server_del;
    int lazyfree_lazy_user_del;
    int lazyfree_lazy_user_flush;
    long long latency_monitor_threshold;
    dict *latency_events;
    char *acl_filename;
    unsigned long acllog_max_len;
    sds requirepass;
    int acl_pubsub_default;
    aclInfo acl_info;
    int watchdog_period;
    size_t system_memory_size;
    int tls_cluster;
    int tls_replication;
    int tls_auth_clients;
    redisTLSContextConfig tls_ctx_config;
    char *server_cpulist;
    char *bio_cpulist;
    char *aof_rewrite_cpulist;
    char *bgsave_cpulist;
    struct sentinelConfig *sentinel_config;
    mstime_t failover_end_time;
    int force_failover;
    char *target_replica_host;
    int target_replica_port;
    int failover_state;
    int cluster_allow_pubsubshard_when_down;
    long reply_buffer_peak_reset_time;
    int reply_buffer_resizing_enabled;
    char *locale_collate;
    int dbg_assert_keysizes;
};


/*Ano*/typedef struct {
    size_t totlen;
    int refcount;
    clusterMsg msg[];
} clusterMsgSendBlock;

struct slotStat;//insertRecordDeclare 

/*TD*/typedef struct slotStat slotStat;


struct slotStat {
    uint64_t cpu_usec;
    uint64_t network_bytes_in;
    uint64_t network_bytes_out;
};


struct clusterState {
    clusterNode *myself;
    uint64_t currentEpoch;
    int state;
    int size;
    dict *nodes;
    dict *shards;
    dict *nodes_black_list;
    clusterNode *migrating_slots_to[16384];
    clusterNode *importing_slots_from[16384];
    clusterNode *slots[16384];
    char internal_secret[40];
    mstime_t failover_auth_time;
    int failover_auth_count;
    int failover_auth_sent;
    int failover_auth_rank;
    uint64_t failover_auth_epoch;
    int cant_failover_reason;
    mstime_t mf_end;
    clusterNode *mf_slave;
    long long mf_master_offset;
    int mf_can_start;
    uint64_t lastVoteEpoch;
    int todo_before_sleep;
    long long stats_bus_messages_sent[11];
    long long stats_bus_messages_received[11];
    long long stats_pfail_nodes;
    unsigned long long stat_cluster_links_buffer_limit_exceeded;
    unsigned char owner_not_claiming_slot[2048];
    slotStat slot_stats[16384];
};


struct clusterLink {
    mstime_t ctime;
    connection *conn;
    list *send_msg_queue;
    size_t head_msg_send_offset;
    unsigned long long send_msg_queue_mem;
    char *rcvbuf;
    size_t rcvbuf_len;
    size_t rcvbuf_alloc;
    clusterNode *node;
    int inbound;
};

struct listNode;//insertRecordDeclare 

/*TD*/typedef struct listNode listNode;


struct list {
    listNode *head;
    listNode *tail;
    void *(*dup)(void *);
    void (*free)(void *);
    int (*match)(void *, void *);
    unsigned long len;
};


struct listNode {
    struct listNode *prev;
    struct listNode *next;
    void *value;
};

struct dictIterator;//insertRecordDeclare 

/*TD*/typedef struct dictIterator dictIterator;

struct dictEntry;//insertRecordDeclare 

/*TD*/typedef struct dictEntry dictEntry;


struct dictIterator {
    dict *d;
    long index;
    int table;
    int safe;
    dictEntry *entry;
    dictEntry *nextEntry;
    unsigned long long fingerprint;
};


struct dictEntry;


/*Ano*/typedef struct {
    char hostname[1];
} clusterMsgPingExtHostname;


/*Ano*/typedef struct {
    char human_nodename[1];
} clusterMsgPingExtHumanNodename;


/*Ano*/typedef struct {
    char name[40];
    uint64_t ttl;
} clusterMsgPingExtForgottenNode;


/*Ano*/typedef struct {
    char shard_id[40];
} clusterMsgPingExtShardId;


/*Ano*/typedef struct {
    char internal_secret[40];
} clusterMsgPingExtInternalSecret;


/*Ano*/typedef struct {
    uint32_t length;
    uint16_t type;
    uint16_t unused;
    union {
        clusterMsgPingExtHostname hostname;
        clusterMsgPingExtHumanNodename human_nodename;
        clusterMsgPingExtForgottenNode forgotten_node;
        clusterMsgPingExtShardId shard_id;
        clusterMsgPingExtInternalSecret internal_secret;
    } ext[];
} clusterMsgPingExt;

struct dictType;//insertRecordDeclare 

/*TD*/typedef struct dictType dictType;


struct dict {
    dictType *type;
    dictEntry **ht_table[2];
    unsigned long ht_used[2];
    long rehashidx;
    unsigned int pauserehash : 15;
    unsigned int useStoredKeyApi : 1;
    signed char ht_size_exp[2];
    int16_t pauseAutoResize;
    void *metadata[];
};

struct redisObject;//insertRecordDeclare 

/*TD*/typedef struct redisObject robj;

struct redisCommand;//insertRecordDeclare 


/*Ano*/typedef struct {
    sds name;
    uint32_t flags;
    list *passwords;
    list *selectors;
    robj *acl_string;
} user;

struct multiState;//insertRecordDeclare 

/*TD*/typedef struct multiState multiState;

struct multiCmd;//insertRecordDeclare 

/*TD*/typedef struct multiCmd multiCmd;


struct multiState {
    multiCmd *commands;
    int count;
    int cmd_flags;
    int cmd_inv_flags;
    size_t argv_len_sums;
    int alloc_count;
};

struct blockingState;//insertRecordDeclare 

/*TD*/typedef struct blockingState blockingState;

/*ENUM*/
enum blocking_type {
    BLOCKED_NONE,
    BLOCKED_LIST,
    BLOCKED_WAIT,
    BLOCKED_WAITAOF,
    BLOCKED_MODULE,
    BLOCKED_STREAM,
    BLOCKED_ZSET,
    BLOCKED_POSTPONE,
    BLOCKED_SHUTDOWN,
    BLOCKED_LAZYFREE,
    BLOCKED_NUM,
    BLOCKED_END
};

/*TD*/typedef enum blocking_type blocking_type;


struct blockingState {
    blocking_type btype;
    mstime_t timeout;
    int unblock_on_nokey;
    dict *keys;
    int numreplicas;
    int numlocal;
    long long reploffset;
    void *module_blocked_handle;
    void *async_rm_call_handle;
    monotime lazyfreeStartTime;
};

/*TD*/typedef void (*RedisModuleUserChangedFunc)(uint64_t, void *);


struct client {
    uint64_t id;
    uint64_t flags;
    connection *conn;
    uint8_t tid;
    uint8_t running_tid;
    uint8_t io_flags;
    uint8_t read_error;
    int resp;
    redisDb *db;
    robj *name;
    robj *lib_name;
    robj *lib_ver;
    sds querybuf;
    size_t qb_pos;
    size_t querybuf_peak;
    int argc;
    robj **argv;
    int argv_len;
    int original_argc;
    robj **original_argv;
    size_t argv_len_sum;
    robj **deferred_objects;
    int deferred_objects_num;
    struct redisCommand *cmd;
    struct redisCommand *lastcmd;
    struct redisCommand *iolookedcmd;
    struct redisCommand *realcmd;
    user *user;
    int reqtype;
    int multibulklen;
    long bulklen;
    list *reply;
    unsigned long long reply_bytes;
    list *deferred_reply_errors;
    size_t sentlen;
    time_t ctime;
    long duration;
    int slot;
    int cluster_compatibility_check_slot;
    dictEntry *cur_script;
    time_t lastinteraction;
    time_t obuf_soft_limit_reached_time;
    mstime_t last_cron_check_time;
    int authenticated;
    int replstate;
    int repl_start_cmd_stream_on_ack;
    int repldbfd;
    off_t repldboff;
    off_t repldbsize;
    sds replpreamble;
    long long read_reploff;
    long long reploff;
    long long repl_applied;
    long long repl_ack_off;
    long long repl_aof_off;
    long long repl_ack_time;
    long long repl_last_partial_write;
    long long psync_initial_offset;
    char replid[41];
    int slave_listening_port;
    char *slave_addr;
    int slave_capa;
    int slave_req;
    uint64_t main_ch_client_id;
    multiState mstate;
    blockingState bstate;
    long long woff;
    list *watched_keys;
    dict *pubsub_channels;
    dict *pubsub_patterns;
    dict *pubsubshard_channels;
    sds peerid;
    sds sockname;
    listNode *client_list_node;
    listNode *io_thread_client_list_node;
    listNode *postponed_list_node;
    void *module_blocked_client;
    void *module_auth_ctx;
    RedisModuleUserChangedFunc auth_callback;
    void *auth_callback_privdata;
    void *auth_module;
    uint64_t client_tracking_redirection;
    rax *client_tracking_prefixes;
    size_t last_memory_usage;
    int last_memory_type;
    listNode *mem_usage_bucket_node;
    clientMemUsageBucket *mem_usage_bucket;
    listNode *ref_repl_buf_node;
    size_t ref_block_pos;
    listNode clients_pending_write_node;
    size_t net_input_bytes_curr_cmd;
    size_t net_output_bytes_curr_cmd;
    size_t buf_peak;
    mstime_t buf_peak_last_reset_time;
    int bufpos;
    size_t buf_usable_size;
    char *buf;
    unsigned long long net_input_bytes;
    unsigned long long net_output_bytes;
    unsigned long long commands_processed;
};

struct redisNodeFlags;//insertRecordDeclare 


struct redisNodeFlags {
    uint16_t flag;
    char *name;
};

/*TD*/typedef int (aux_value_setter)(clusterNode *, void *, int);

/*TD*/typedef sds (aux_value_getter)(clusterNode *, sds);

/*TD*/typedef int (aux_value_present)(clusterNode *);


/*Ano*/typedef struct {
    char *field;
    aux_value_setter *setter;
    aux_value_getter *getter;
    aux_value_present *isPresent;
} auxFieldHandler;

/*ANo ENUM*/
enum {
    af_shard_id,
    af_human_nodename,
    af_tcp_port,
    af_tls_port,
    af_count
};

/*ANo ENUM*/
enum {
    REPL_STATE_NONE = 0,
    REPL_STATE_CONNECT,
    REPL_STATE_CONNECTING,
    REPL_STATE_RECEIVE_PING_REPLY,
    REPL_STATE_SEND_HANDSHAKE,
    REPL_STATE_RECEIVE_AUTH_REPLY,
    REPL_STATE_RECEIVE_PORT_REPLY,
    REPL_STATE_RECEIVE_IP_REPLY,
    REPL_STATE_RECEIVE_CAPA_REPLY,
    REPL_STATE_SEND_PSYNC,
    REPL_STATE_RECEIVE_PSYNC_REPLY,
    REPL_STATE_TRANSFER,
    REPL_STATE_CONNECTED
};

/*ANo ENUM*/
enum {
    CLUSTERMSG_EXT_TYPE_HOSTNAME,
    CLUSTERMSG_EXT_TYPE_HUMAN_NODENAME,
    CLUSTERMSG_EXT_TYPE_FORGOTTEN_NODE,
    CLUSTERMSG_EXT_TYPE_SHARDID,
    CLUSTERMSG_EXT_TYPE_INTERNALSECRET
};

#endif