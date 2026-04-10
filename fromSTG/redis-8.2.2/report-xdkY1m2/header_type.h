#ifndef __HEADER_TYPE_H__ 
#define __HEADER_TYPE_H__
#include"../common.h" 
struct connection;//insertRecordDeclare 

/*TD*/typedef struct connection connection;

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

/*TD*/typedef void (*ConnectionCallbackFunc)(struct connection *);


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

/*TD*/typedef char *sds;


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

struct client;//insertRecordDeclare 

/*TD*/typedef struct client client;

struct RedisModuleClientInfo;//insertRecordDeclare 

/*TD*/typedef struct RedisModuleClientInfo RedisModuleClientInfoV1;


struct RedisModuleClientInfo {
    uint64_t version;
    uint64_t flags;
    uint64_t id;
    char addr[46];
    uint16_t port;
    uint16_t db;
};

struct redisDb;//insertRecordDeclare 

/*TD*/typedef struct redisDb redisDb;

struct redisObject;//insertRecordDeclare 

/*TD*/typedef struct redisObject robj;

struct redisCommand;//insertRecordDeclare 

struct list;//insertRecordDeclare 

/*TD*/typedef struct list list;


/*Ano*/typedef struct {
    sds name;
    uint32_t flags;
    list *passwords;
    list *selectors;
    robj *acl_string;
} user;

struct dictEntry;//insertRecordDeclare 

/*TD*/typedef struct dictEntry dictEntry;

/*TD*/typedef long long mstime_t;

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

struct dict;//insertRecordDeclare 

/*TD*/typedef struct dict dict;

/*TD*/typedef uint64_t monotime;


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

struct listNode;//insertRecordDeclare 

/*TD*/typedef struct listNode listNode;

/*TD*/typedef void (*RedisModuleUserChangedFunc)(uint64_t, void *);

struct rax;//insertRecordDeclare 

/*TD*/typedef struct rax rax;


/*Ano*/typedef struct {
    list *clients;
    size_t mem_usage_sum;
} clientMemUsageBucket;


struct listNode {
    struct listNode *prev;
    struct listNode *next;
    void *value;
};


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

struct _kvstore;//insertRecordDeclare 

/*TD*/typedef struct _kvstore kvstore;

/*TD*/typedef void *ebuckets;


struct redisDb {
    kvstore *keys;
    kvstore *expires;
    ebuckets hexpires;
    dict *blocking_keys;
    dict *blocking_keys_unblock_on_nokey;
    dict *ready_keys;
    dict *watched_keys;
    int id;
    long long avg_ttl;
    unsigned long expires_cursor;
};

#endif