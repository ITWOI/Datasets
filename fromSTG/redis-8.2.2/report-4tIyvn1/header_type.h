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

/*TD*/typedef struct redisObject kvobj;


struct redisObject {
    unsigned int type : 4;
    unsigned int encoding : 4;
    unsigned int lru : 24;
    unsigned int iskvobj : 1;
    unsigned int expirable : 1;
    unsigned int refcount : 30;
    void *ptr;
};

/*TD*/typedef struct redisObject robj;

#endif