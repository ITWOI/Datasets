#ifndef __HEADER_TYPE_H__ 
#define __HEADER_TYPE_H__
#include"../common.h" 
struct _clusterNode;//insertRecordDeclare 

/*TD*/typedef struct _clusterNode clusterNode;

/*TD*/typedef char *sds;

/*TD*/typedef long long mstime_t;

struct clusterLink;//insertRecordDeclare 

/*TD*/typedef struct clusterLink clusterLink;

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

#endif