#ifndef __HEADER_TYPE_H__ 
#define __HEADER_TYPE_H__
#include"../common.h" 
/*TD*/typedef char *hisds;

struct hisdshdr8;//insertRecordDeclare 


struct hisdshdr8 {
    uint8_t len;
    uint8_t alloc;
    unsigned char flags;
    char buf[];
};

struct hisdshdr16;//insertRecordDeclare 


struct hisdshdr16 {
    uint16_t len;
    uint16_t alloc;
    unsigned char flags;
    char buf[];
};

struct hisdshdr32;//insertRecordDeclare 


struct hisdshdr32 {
    uint32_t len;
    uint32_t alloc;
    unsigned char flags;
    char buf[];
};

struct hisdshdr64;//insertRecordDeclare 


struct hisdshdr64 {
    uint64_t len;
    uint64_t alloc;
    unsigned char flags;
    char buf[];
};

struct timeval;//insertRecordDeclare 

struct __va_list_tag;//insertRecordDeclare 

struct redisReply;//insertRecordDeclare 

/*TD*/typedef struct redisReply redisReply;

struct redisContext;//insertRecordDeclare 

/*TD*/typedef struct redisContext redisContext;


struct redisReply {
    int type;
    long long integer;
    double dval;
    size_t len;
    char *str;
    char vtype[4];
    size_t elements;
    struct redisReply **element;
};

struct commandDocs;//insertRecordDeclare 

struct cliCommandArg;//insertRecordDeclare 

/*TD*/typedef struct cliCommandArg cliCommandArg;


struct commandDocs {
    char *name;
    char *summary;
    char *group;
    char *since;
    int numargs;
    cliCommandArg *args;
    struct commandDocs *subcommands;
    char *params;
};


/*Ano*/typedef struct {
    int type;
    int argc;
    hisds *argv;
    hisds full;
    struct commandDocs docs;
} helpEntry;


typedef enum {
    ARG_TYPE_STRING,
    ARG_TYPE_INTEGER,
    ARG_TYPE_DOUBLE,
    ARG_TYPE_KEY,
    ARG_TYPE_PATTERN,
    ARG_TYPE_UNIX_TIME,
    ARG_TYPE_PURE_TOKEN,
    ARG_TYPE_ONEOF,
    ARG_TYPE_BLOCK
} redisCommandArgType;


struct cliCommandArg {
    char *name;
    redisCommandArgType type;
    char *token;
    char *since;
    int flags;
    int numsubargs;
    struct cliCommandArg *subargs;
    const char *display_text;
    int matched;
    int matched_token;
    int matched_name;
    int matched_all;
};

struct dict;//insertRecordDeclare 

/*TD*/typedef struct dict dict;

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

struct config;//insertRecordDeclare 

struct cliConnInfo;//insertRecordDeclare 

/*TD*/typedef struct cliConnInfo cliConnInfo;


struct cliConnInfo {
    char *hostip;
    int hostport;
    int input_dbnum;
    char *auth;
    char *user;
};

struct cliSSLconfig;//insertRecordDeclare 

/*TD*/typedef struct cliSSLconfig cliSSLconfig;


struct cliSSLconfig {
    char *sni;
    char *cacert;
    char *cacertdir;
    int skip_cert_verify;
    char *cert;
    char *key;
    char *ciphers;
    char *ciphersuites;
};

struct clusterManagerCommand;//insertRecordDeclare 

/*TD*/typedef struct clusterManagerCommand clusterManagerCommand;


struct clusterManagerCommand {
    char *name;
    int argc;
    char **argv;
    hisds stdin_arg;
    int flags;
    int replicas;
    char *from;
    char *to;
    char **weight;
    int weight_argc;
    char *master_id;
    int slots;
    int timeout;
    int pipeline;
    float threshold;
    char *backup_dir;
    char *from_user;
    char *from_pass;
    int from_askpass;
};


struct config {
    cliConnInfo conn_info;
    struct timeval connect_timeout;
    char *hostsocket;
    int tls;
    cliSSLconfig sslconfig;
    long repeat;
    long interval;
    int dbnum;
    int interactive;
    int shutdown;
    int monitor_mode;
    int pubsub_mode;
    int blocking_state_aborted;
    int latency_mode;
    int latency_dist_mode;
    int latency_history;
    int lru_test_mode;
    long long lru_test_sample_size;
    int cluster_mode;
    int cluster_reissue_command;
    int cluster_send_asking;
    int slave_mode;
    int pipe_mode;
    int pipe_timeout;
    int getrdb_mode;
    int get_functions_rdb_mode;
    int stat_mode;
    int scan_mode;
    int count;
    int intrinsic_latency_mode;
    int intrinsic_latency_duration;
    hisds pattern;
    char *rdb_filename;
    int bigkeys;
    int memkeys;
    long long memkeys_samples;
    int hotkeys;
    int keystats;
    unsigned long long cursor;
    unsigned long top_sizes_limit;
    int stdin_lastarg;
    int stdin_tag_arg;
    char *stdin_tag_name;
    int askpass;
    int quoted_input;
    int output;
    int push_output;
    hisds mb_delim;
    hisds cmd_delim;
    char prompt[128];
    char *eval;
    int eval_ldb;
    int eval_ldb_sync;
    int eval_ldb_end;
    int enable_ldb_on_eval;
    int last_cmd_type;
    redisReply *last_reply;
    int verbose;
    int set_errcode;
    clusterManagerCommand cluster_manager_command;
    int no_auth_warning;
    int resp2;
    int resp3;
    int current_resp3;
    int in_multi;
    int pre_multi_dbnum;
    char *server_version;
    char *test_hint;
    char *test_hint_file;
    int prefer_ipv4;
    int prefer_ipv6;
};

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

struct termios;//insertRecordDeclare 

struct _IO_FILE;//insertRecordDeclare 

struct redisContextFuncs;//insertRecordDeclare 

/*TD*/typedef struct redisContextFuncs redisContextFuncs;

/*TD*/typedef int redisFD;

struct redisReader;//insertRecordDeclare 

/*TD*/typedef struct redisReader redisReader;

/*ENUM*/
enum redisConnectionType {
    REDIS_CONN_TCP,
    REDIS_CONN_UNIX,
    REDIS_CONN_USERFD
};

struct sockaddr;//insertRecordDeclare 

/*TD*/typedef void (redisPushFn)(void *, void *);


struct redisContext {
    const redisContextFuncs *funcs;
    int err;
    char errstr[128];
    redisFD fd;
    int flags;
    char *obuf;
    redisReader *reader;
    enum redisConnectionType connection_type;
    struct timeval *connect_timeout;
    struct timeval *command_timeout;
    struct {
        char *host;
        char *source_addr;
        int port;
    } tcp;
    struct {
        char *path;
    } unix_sock;
    struct sockaddr *saddr;
    size_t addrlen;
    void *privdata;
    void (*free_privdata)(void *);
    void *privctx;
    redisPushFn *push_cb;
};

struct pref;//insertRecordDeclare 


struct pref {
    int hints;
};

struct clusterManagerNode;//insertRecordDeclare 

/*TD*/typedef struct clusterManagerNode clusterManagerNode;

struct clusterManagerNodeArray;//insertRecordDeclare 

/*TD*/typedef struct clusterManagerNodeArray clusterManagerNodeArray;

/*TD*/typedef int (clusterManagerCommandProc)(int, char **);

struct clusterManagerCommandDef;//insertRecordDeclare 

/*TD*/typedef struct clusterManagerCommandDef clusterManagerCommandDef;


struct clusterManagerCommandDef {
    char *name;
    clusterManagerCommandProc *proc;
    int arity;
    char *args;
    char *options;
};

struct list;//insertRecordDeclare 

/*TD*/typedef struct list list;


struct clusterManagerNode {
    redisContext *context;
    hisds name;
    char *ip;
    int port;
    int bus_port;
    uint64_t current_epoch;
    time_t ping_sent;
    time_t ping_recv;
    int flags;
    list *flags_str;
    hisds replicate;
    int dirty;
    uint8_t slots[16384];
    int slots_count;
    int replicas_count;
    list *friends;
    hisds *migrating;
    hisds *importing;
    int migrating_count;
    int importing_count;
    float weight;
    int balance;
};

struct listIter;//insertRecordDeclare 

/*TD*/typedef struct listIter listIter;

struct listNode;//insertRecordDeclare 

/*TD*/typedef struct listNode listNode;


struct listIter {
    listNode *next;
    int direction;
};


struct listNode {
    struct listNode *prev;
    struct listNode *next;
    void *value;
};

struct clusterManager;//insertRecordDeclare 


struct clusterManager {
    list *nodes;
    list *errors;
    int unreachable_masters;
};

/*TD*/typedef int (*clusterManagerOnReplyError)(redisReply *, clusterManagerNode *, int);


struct list {
    listNode *head;
    listNode *tail;
    void *(*dup)(void *);
    void (*free)(void *);
    int (*match)(void *, void *);
    unsigned long len;
};


struct clusterManagerNodeArray {
    clusterManagerNode **nodes;
    clusterManagerNode **alloc;
    int len;
    int count;
};

struct clusterManagerLink;//insertRecordDeclare 

/*TD*/typedef struct clusterManagerLink clusterManagerLink;


struct clusterManagerLink {
    hisds node_name;
    hisds node_addr;
    int connected;
    int handshaking;
};

struct clusterManagerReshardTableItem;//insertRecordDeclare 

/*TD*/typedef struct clusterManagerReshardTableItem clusterManagerReshardTableItem;


struct clusterManagerReshardTableItem {
    clusterManagerNode *source;
    int slot;
};


struct distsamples {
    long long max;
    long long count;
    int character;
};

struct redisAsyncContext;//insertRecordDeclare 


struct redisContextFuncs {
    void (*close)(struct redisContext *);
    void (*free_privctx)(void *);
    void (*async_read)(struct redisAsyncContext *);
    void (*async_write)(struct redisAsyncContext *);
    ssize_t (*read)(struct redisContext *, char *, size_t);
    ssize_t (*write)(struct redisContext *);
};


/*Ano*/typedef struct {
    char *name;
    char *sizecmd;
    char *sizeunit;
    unsigned long long biggest;
    unsigned long long count;
    unsigned long long totalsize;
    hisds biggest_key;
} typeinfo;

struct size_dist;//insertRecordDeclare 

/*TD*/typedef struct size_dist size_dist;

struct size_dist_entry;//insertRecordDeclare 

/*TD*/typedef struct size_dist_entry size_dist_entry;


struct size_dist {
    unsigned long long total_count;
    unsigned long long total_size;
    unsigned long long max_size;
    size_dist_entry *size_dist;
};


struct size_dist_entry {
    unsigned long long size;
    unsigned long long count;
};

struct hdr_histogram;//insertRecordDeclare 

struct hdr_iter;//insertRecordDeclare 

struct hdr_iter_percentiles;//insertRecordDeclare 


struct hdr_iter_percentiles {
    _Bool seen_last_value;
    int32_t ticks_per_half_distance;
    double percentile_to_iterate_to;
    double percentile;
};

struct hdr_iter_recorded;//insertRecordDeclare 


struct hdr_iter_recorded {
    int64_t count_added_in_this_iteration_step;
};

struct hdr_iter_linear;//insertRecordDeclare 


struct hdr_iter_linear {
    int64_t value_units_per_bucket;
    int64_t count_added_in_this_iteration_step;
    int64_t next_value_reporting_level;
    int64_t next_value_reporting_level_lowest_equivalent;
};

struct hdr_iter_log;//insertRecordDeclare 


struct hdr_iter_log {
    double log_base;
    int64_t count_added_in_this_iteration_step;
    int64_t next_value_reporting_level;
    int64_t next_value_reporting_level_lowest_equivalent;
};


struct hdr_iter {
    const struct hdr_histogram *h;
    int32_t counts_index;
    int64_t total_count;
    int64_t count;
    int64_t cumulative_count;
    int64_t value;
    int64_t highest_equivalent_value;
    int64_t lowest_equivalent_value;
    int64_t median_equivalent_value;
    int64_t value_iterated_from;
    int64_t value_iterated_to;
    union {
        struct hdr_iter_percentiles percentiles;
        struct hdr_iter_recorded recorded;
        struct hdr_iter_linear linear;
        struct hdr_iter_log log;
    } specifics;
    _Bool (*_next_fp)(struct hdr_iter *);
};


struct hdr_histogram {
    int64_t lowest_discernible_value;
    int64_t highest_trackable_value;
    int32_t unit_magnitude;
    int32_t significant_figures;
    int32_t sub_bucket_half_count_magnitude;
    int32_t sub_bucket_half_count;
    int64_t sub_bucket_mask;
    int32_t sub_bucket_count;
    int32_t bucket_count;
    int64_t min_value;
    int64_t max_value;
    int32_t normalizing_index_offset;
    double conversion_ratio;
    int32_t counts_len;
    int64_t total_count;
    int64_t *counts;
};

struct key_info;//insertRecordDeclare 

/*TD*/typedef struct key_info key_info;


struct key_info {
    unsigned long long size;
    char type_name[10];
    hisds key_name;
};

#endif