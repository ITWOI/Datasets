#ifndef __HEADER_TYPE_H__ 
#define __HEADER_TYPE_H__
#include"../common.h" 
struct clusterManagerNode;//insertRecordDeclare 

/*TD*/typedef struct clusterManagerNode clusterManagerNode;

struct redisReply;//insertRecordDeclare 

/*TD*/typedef struct redisReply redisReply;


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

struct redisContext;//insertRecordDeclare 

/*TD*/typedef struct redisContext redisContext;

/*TD*/typedef char *hisds;

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

#endif