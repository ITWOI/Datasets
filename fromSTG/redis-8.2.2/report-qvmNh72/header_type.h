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

struct standardConfig;//insertRecordDeclare 

/*TD*/typedef struct standardConfig standardConfig;

struct dictEntry;//insertRecordDeclare 

/*TD*/typedef struct dictEntry dictEntry;

struct dict;//insertRecordDeclare 

/*TD*/typedef struct dict dict;


struct dictEntry;

struct rewriteConfigState;//insertRecordDeclare 


struct rewriteConfigState {
    dict *option_to_line;
    dict *rewritten;
    int numlines;
    sds *lines;
    int needs_signature;
    int force_write;
};

struct dictType;//insertRecordDeclare 

/*TD*/typedef struct dictType dictType;

struct dictCmpCache;//insertRecordDeclare 

/*TD*/typedef struct dictCmpCache dictCmpCache;


struct dictType {
    uint64_t (*hashFunction)(const void *);
    void *(*keyDup)(dict *, const void *);
    void *(*valDup)(dict *, const void *);
    int (*keyCompare)(dictCmpCache *, const void *, const void *);
    void (*keyDestructor)(dict *, void *);
    void (*valDestructor)(dict *, void *);
    int (*resizeAllowed)(size_t, double);
    void (*rehashingStarted)(dict *);
    void (*rehashingCompleted)(dict *);
    void (*bucketChanged)(dict *, long long);
    size_t (*dictMetadataBytes)(dict *);
    void *userdata;
    unsigned int no_value : 1;
    unsigned int keys_are_odd : 1;
    unsigned int force_full_rehash : 1;
    uint64_t (*storedHashFunction)(const void *);
    int (*storedKeyCompare)(dictCmpCache *, const void *, const void *);
    void (*onDictRelease)(dict *);
};

struct _IO_FILE;//insertRecordDeclare 

struct stat;//insertRecordDeclare 

struct typeInterface;//insertRecordDeclare 

/*TD*/typedef struct typeInterface typeInterface;

/*TD*/typedef int (*apply_fn)(const char **);


struct typeInterface {
    void (*init)(standardConfig *);
    int (*set)(standardConfig *, sds *, int, const char **);
    apply_fn apply;
    sds (*get)(standardConfig *);
    void (*rewrite)(standardConfig *, const char *, struct rewriteConfigState *);
};

union typeData;//insertRecordDeclare 

/*TD*/typedef union typeData typeData;

struct boolConfigData;//insertRecordDeclare 

/*TD*/typedef struct boolConfigData boolConfigData;


struct boolConfigData {
    int *config;
    int default_value;
    int (*is_valid_fn)(int, const char **);
};

struct stringConfigData;//insertRecordDeclare 

/*TD*/typedef struct stringConfigData stringConfigData;


struct stringConfigData {
    char **config;
    const char *default_value;
    int (*is_valid_fn)(char *, const char **);
    int convert_empty_to_null;
};

struct sdsConfigData;//insertRecordDeclare 

/*TD*/typedef struct sdsConfigData sdsConfigData;


struct sdsConfigData {
    sds *config;
    char *default_value;
    int (*is_valid_fn)(sds, const char **);
    int convert_empty_to_null;
};

struct enumConfigData;//insertRecordDeclare 

/*TD*/typedef struct enumConfigData enumConfigData;

struct configEnum;//insertRecordDeclare 

/*TD*/typedef struct configEnum configEnum;


struct enumConfigData {
    int *config;
    configEnum *enum_value;
    int default_value;
    int (*is_valid_fn)(int, const char **);
};

struct numericConfigData;//insertRecordDeclare 

/*TD*/typedef struct numericConfigData numericConfigData;

/*ENUM*/
enum numericType {
    NUMERIC_TYPE_INT,
    NUMERIC_TYPE_UINT,
    NUMERIC_TYPE_LONG,
    NUMERIC_TYPE_ULONG,
    NUMERIC_TYPE_LONG_LONG,
    NUMERIC_TYPE_ULONG_LONG,
    NUMERIC_TYPE_SIZE_T,
    NUMERIC_TYPE_SSIZE_T,
    NUMERIC_TYPE_OFF_T,
    NUMERIC_TYPE_TIME_T
};

/*TD*/typedef enum numericType numericType;


struct numericConfigData {
    union {
        int *i;
        unsigned int *ui;
        long *l;
        unsigned long *ul;
        long long *ll;
        unsigned long long *ull;
        size_t *st;
        ssize_t *sst;
        off_t *ot;
        time_t *tt;
    } config;
    unsigned int flags;
    numericType numeric_type;
    long long lower_bound;
    long long upper_bound;
    long long default_value;
    int (*is_valid_fn)(long long, const char **);
};


union typeData {
    boolConfigData yesno;
    stringConfigData string;
    sdsConfigData sds;
    enumConfigData enumd;
    numericConfigData numeric;
};


typedef enum {
    BOOL_CONFIG,
    NUMERIC_CONFIG,
    STRING_CONFIG,
    SDS_CONFIG,
    ENUM_CONFIG,
    SPECIAL_CONFIG
} configType;


struct standardConfig {
    const char *name;
    const char *alias;
    unsigned int flags;
    typeInterface interface;
    typeData data;
    configType type;
    void *privdata;
};

struct redisServer;//insertRecordDeclare 

struct redisDb;//insertRecordDeclare 

/*TD*/typedef struct redisDb redisDb;

struct aeEventLoop;//insertRecordDeclare 

/*TD*/typedef struct aeEventLoop aeEventLoop;

struct rax;//insertRecordDeclare 

/*TD*/typedef struct rax rax;

/*TD*/typedef long long mstime_t;

struct list;//insertRecordDeclare 

/*TD*/typedef struct list list;

struct connListener;//insertRecordDeclare 

/*TD*/typedef struct connListener connListener;

struct ConnectionType;//insertRecordDeclare 

/*TD*/typedef struct ConnectionType ConnectionType;


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

struct connection;//insertRecordDeclare 

/*TD*/typedef struct connection connection;

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

struct raxIterator;//insertRecordDeclare 

/*TD*/typedef struct raxIterator raxIterator;

struct raxNode;//insertRecordDeclare 

/*TD*/typedef struct raxNode raxNode;

struct raxStack;//insertRecordDeclare 

/*TD*/typedef struct raxStack raxStack;


struct raxStack {
    void **stack;
    size_t items;
    size_t maxitems;
    void *static_items[32];
    int oom;
};

/*TD*/typedef int (*raxNodeCallback)(raxNode **, void *);


struct raxIterator {
    int flags;
    rax *rt;
    unsigned char *key;
    void *data;
    size_t key_len;
    size_t key_max;
    unsigned char key_static_string[128];
    raxNode *node;
    raxStack stack;
    raxNodeCallback node_cb;
    void *privdata;
};

struct redisObject;//insertRecordDeclare 

/*TD*/typedef struct redisObject robj;


/*Ano*/typedef struct {
    sds name;
    uint32_t flags;
    list *passwords;
    list *selectors;
    robj *acl_string;
} user;


struct redisObject {
    unsigned int type : 4;
    unsigned int encoding : 4;
    unsigned int lru : 24;
    unsigned int iskvobj : 1;
    unsigned int expirable : 1;
    unsigned int refcount : 30;
    void *ptr;
};

struct dictIterator;//insertRecordDeclare 

/*TD*/typedef struct dictIterator dictIterator;


struct dictIterator {
    dict *d;
    long index;
    int table;
    int safe;
    dictEntry *entry;
    dictEntry *nextEntry;
    unsigned long long fingerprint;
};

struct RedisModule;//insertRecordDeclare 


typedef enum {
    MODULE_CONFIGS_DEFAULTS = 1,
    MODULE_CONFIGS_USER_VALS = 2,
    MODULE_CONFIGS_ALL_APPLIED = 3
} ModuleConfigsApplied;

struct RedisModuleInfoCtx;//insertRecordDeclare 

/*TD*/typedef struct RedisModuleInfoCtx RedisModuleInfoCtx;

/*TD*/typedef void (*RedisModuleInfoFunc)(RedisModuleInfoCtx *, int);

struct RedisModuleDefragCtx;//insertRecordDeclare 

/*TD*/typedef struct RedisModuleDefragCtx RedisModuleDefragCtx;

/*TD*/typedef void (*RedisModuleDefragFunc)(RedisModuleDefragCtx *);

/*TD*/typedef int (*RedisModuleDefragFunc2)(RedisModuleDefragCtx *);

struct moduleLoadQueueEntry;//insertRecordDeclare 


struct RedisModule {
    void *handle;
    char *name;
    int ver;
    int apiver;
    list *types;
    list *usedby;
    list *using;
    list *filters;
    list *module_configs;
    ModuleConfigsApplied configs_initialized;
    int in_call;
    int in_hook;
    int options;
    int blocked_clients;
    RedisModuleInfoFunc info_cb;
    RedisModuleDefragFunc defrag_cb;
    RedisModuleDefragFunc2 defrag_cb_2;
    RedisModuleDefragFunc defrag_start_cb;
    RedisModuleDefragFunc defrag_end_cb;
    struct moduleLoadQueueEntry *loadmod;
    int num_commands_with_acl_categories;
    int onload;
    size_t num_acl_categories_added;
};


struct moduleLoadQueueEntry {
    sds path;
    int argc;
    robj **argv;
};

struct sharedObjectsStruct;//insertRecordDeclare 


struct sharedObjectsStruct {
    robj *ok;
    robj *err;
    robj *emptybulk;
    robj *czero;
    robj *cone;
    robj *pong;
    robj *space;
    robj *queued;
    robj *null[4];
    robj *nullarray[4];
    robj *emptymap[4];
    robj *emptyset[4];
    robj *emptyarray;
    robj *wrongtypeerr;
    robj *nokeyerr;
    robj *syntaxerr;
    robj *sameobjecterr;
    robj *outofrangeerr;
    robj *noscripterr;
    robj *loadingerr;
    robj *slowevalerr;
    robj *slowscripterr;
    robj *slowmoduleerr;
    robj *bgsaveerr;
    robj *masterdownerr;
    robj *roslaveerr;
    robj *execaborterr;
    robj *noautherr;
    robj *noreplicaserr;
    robj *busykeyerr;
    robj *oomerr;
    robj *plus;
    robj *messagebulk;
    robj *pmessagebulk;
    robj *subscribebulk;
    robj *unsubscribebulk;
    robj *psubscribebulk;
    robj *punsubscribebulk;
    robj *del;
    robj *unlink;
    robj *rpop;
    robj *lpop;
    robj *lpush;
    robj *rpoplpush;
    robj *lmove;
    robj *blmove;
    robj *zpopmin;
    robj *zpopmax;
    robj *emptyscan;
    robj *multi;
    robj *exec;
    robj *left;
    robj *right;
    robj *hset;
    robj *srem;
    robj *xgroup;
    robj *xclaim;
    robj *script;
    robj *replconf;
    robj *eval;
    robj *persist;
    robj *set;
    robj *pexpireat;
    robj *pexpire;
    robj *hdel;
    robj *hpexpireat;
    robj *hpersist;
    robj *hsetex;
    robj *time;
    robj *pxat;
    robj *absttl;
    robj *retrycount;
    robj *force;
    robj *justid;
    robj *entriesread;
    robj *lastid;
    robj *ping;
    robj *setid;
    robj *keepttl;
    robj *load;
    robj *createconsumer;
    robj *fields;
    robj *getack;
    robj *special_asterick;
    robj *special_equals;
    robj *default_username;
    robj *redacted;
    robj *ssubscribebulk;
    robj *sunsubscribebulk;
    robj *smessagebulk;
    robj *select[10];
    robj *integers[10000];
    robj *mbulkhdr[32];
    robj *bulkhdr[32];
    robj *maphdr[32];
    robj *sethdr[32];
    sds minstring;
    sds maxstring;
};

#endif