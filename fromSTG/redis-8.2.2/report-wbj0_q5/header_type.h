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

struct clusterManagerNodeArray;//insertRecordDeclare 

/*TD*/typedef struct clusterManagerNodeArray clusterManagerNodeArray;

struct clusterManagerNode;//insertRecordDeclare 

/*TD*/typedef struct clusterManagerNode clusterManagerNode;

struct clusterManager;//insertRecordDeclare 

struct list;//insertRecordDeclare 

/*TD*/typedef struct list list;


struct clusterManager {
    list *nodes;
    list *errors;
    int unreachable_masters;
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

struct redisContext;//insertRecordDeclare 

/*TD*/typedef struct redisContext redisContext;


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

struct dict;//insertRecordDeclare 

/*TD*/typedef struct dict dict;


struct clusterManagerNodeArray {
    clusterManagerNode **nodes;
    clusterManagerNode **alloc;
    int len;
    int count;
};

struct dictEntry;//insertRecordDeclare 

/*TD*/typedef struct dictEntry dictEntry;

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

struct listIter;//insertRecordDeclare 

/*TD*/typedef struct listIter listIter;


struct listIter {
    listNode *next;
    int direction;
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


struct dictEntry;


struct listNode {
    struct listNode *prev;
    struct listNode *next;
    void *value;
};

#endif