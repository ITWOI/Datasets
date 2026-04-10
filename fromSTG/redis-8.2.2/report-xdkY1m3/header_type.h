#ifndef __HEADER_TYPE_H__ 
#define __HEADER_TYPE_H__
#include"../common.h" 
struct RedisModuleKey;//insertRecordDeclare 

/*TD*/typedef struct RedisModuleKey RedisModuleKey;

struct redisObject;//insertRecordDeclare 

/*TD*/typedef struct redisObject robj;

/*TD*/typedef struct redisObject kvobj;

struct RedisModuleCtx;//insertRecordDeclare 

/*TD*/typedef struct RedisModuleCtx RedisModuleCtx;

struct redisDb;//insertRecordDeclare 

/*TD*/typedef struct redisDb redisDb;

struct quicklistIter;//insertRecordDeclare 

/*TD*/typedef struct quicklistIter quicklistIter;


/*Ano*/typedef struct {
    robj *subject;
    unsigned char encoding;
    unsigned char direction;
    unsigned char *lpi;
    quicklistIter *iter;
} listTypeIterator;

struct quicklistEntry;//insertRecordDeclare 

/*TD*/typedef struct quicklistEntry quicklistEntry;

struct quicklist;//insertRecordDeclare 

/*TD*/typedef struct quicklist quicklist;

struct quicklistNode;//insertRecordDeclare 

/*TD*/typedef struct quicklistNode quicklistNode;


struct quicklistEntry {
    const quicklist *quicklist;
    quicklistNode *node;
    unsigned char *zi;
    unsigned char *value;
    long long longval;
    size_t sz;
    int offset;
};


/*Ano*/typedef struct {
    listTypeIterator *li;
    unsigned char *lpe;
    quicklistEntry entry;
} listTypeEntry;


/*Ano*/typedef struct {
    double min;
    double max;
    int minex;
    int maxex;
} zrangespec;

/*TD*/typedef char *sds;


/*Ano*/typedef struct {
    sds min;
    sds max;
    int minex;
    int maxex;
} zlexrangespec;

struct streamID;//insertRecordDeclare 

/*TD*/typedef struct streamID streamID;


struct streamID {
    uint64_t ms;
    uint64_t seq;
};


struct RedisModuleKey {
    RedisModuleCtx *ctx;
    redisDb *db;
    robj *key;
    kvobj *kv;
    void *iter;
    int mode;
    union {
        struct {
            listTypeEntry entry;
            long index;
        } list;
        struct {
            uint32_t type;
            zrangespec rs;
            zlexrangespec lrs;
            uint32_t start;
            uint32_t end;
            void *current;
            int er;
        } zset;
        struct {
            streamID currentid;
            int64_t numfieldsleft;
            int signalready;
        } stream;
    } u;
};


struct redisObject {
    unsigned int type : 4;
    unsigned int encoding : 4;
    unsigned int lru : 24;
    unsigned int iskvobj : 1;
    unsigned int expirable : 1;
    unsigned int refcount : 30;
    void *ptr;
};

/*TD*/typedef void (*beforeConvertCB)(void *);

#endif