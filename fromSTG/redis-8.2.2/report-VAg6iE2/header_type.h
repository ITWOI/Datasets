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

struct redisObject;//insertRecordDeclare 

/*TD*/typedef struct redisObject robj;


struct redisObject {
    unsigned int type : 4;
    unsigned int encoding : 4;
    unsigned int lru : 24;
    unsigned int iskvobj : 1;
    unsigned int expirable : 1;
    unsigned int refcount : 30;
    void *ptr;
};

struct client;//insertRecordDeclare 

/*TD*/typedef struct client client;

/*TD*/typedef struct redisObject kvobj;

struct connection;//insertRecordDeclare 

/*TD*/typedef struct connection connection;

struct redisDb;//insertRecordDeclare 

/*TD*/typedef struct redisDb redisDb;

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