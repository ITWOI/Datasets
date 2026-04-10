#ifndef __HEADER_TYPE_H__ 
#define __HEADER_TYPE_H__
#include"../common.h" 
struct dict;//insertRecordDeclare 

/*TD*/typedef struct dict dict;

struct dictEntry;//insertRecordDeclare 

/*TD*/typedef struct dictEntry dictEntry;

struct dictCmpCache;//insertRecordDeclare 

/*TD*/typedef struct dictCmpCache dictCmpCache;

/*TD*/typedef dictEntry **dictEntryLink;

/*TD*/typedef int (*keyCmpFunc)(dictCmpCache *, const void *, const void *);

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


/*Ano*/typedef struct {
    void *key;
    dictEntry *next;
} dictEntryNoValue;


struct dictEntry {
    void *key;
    union {
        void *val;
        uint64_t u64;
        int64_t s64;
        double d;
    } v;
    struct dictEntry *next;
};


typedef enum {
    DICT_RESIZE_ENABLE,
    DICT_RESIZE_AVOID,
    DICT_RESIZE_FORBID
} dictResizeEnable;


struct dictCmpCache {
    int useCache;
    union {
        uint64_t u64;
        int64_t i64;
        int i;
        size_t sz;
        void *p;
    } data[2];
};

#endif