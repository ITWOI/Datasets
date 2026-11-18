#ifndef __HEADER_TYPE_H__ 
#define __HEADER_TYPE_H__
#include"../common.h" 
struct race_param;//insertRecordDeclare 


struct race_param {
    void *lock;
    void *reqs_cmpl_cond;
    int bw_threads;
    void *bw_threads_exited_cond;
    volatile int stopping;
    void *base;
    void *dns;
    int locked;
};

struct evdns_server_port;//insertRecordDeclare 


struct evdns_server_port;

struct timeval;//insertRecordDeclare 

struct event_base;//insertRecordDeclare 

struct evdns_server_request;//insertRecordDeclare 

/*TD*/typedef void (*evdns_request_callback_fn_type)(struct evdns_server_request *, void *);

struct regress_dns_server_table;//insertRecordDeclare 


struct regress_dns_server_table {
    const char *q;
    const char *anstype;
    const char *ans;
    int seen;
    int lower;
};

struct evdns_base;//insertRecordDeclare 

struct evthread_lock_callbacks;//insertRecordDeclare 


struct evthread_lock_callbacks {
    int lock_api_version;
    unsigned int supported_locktypes;
    void *(*alloc)(unsigned int);
    void (*free)(void *, unsigned int);
    int (*lock)(unsigned int, void *);
    int (*unlock)(unsigned int, void *);
};

struct evthread_condition_callbacks;//insertRecordDeclare 


struct evthread_condition_callbacks {
    int condition_api_version;
    void *(*alloc_condition)(unsigned int);
    void (*free_condition)(void *);
    int (*signal_condition)(void *, int);
    int (*wait_condition)(void *, void *, const struct timeval *);
};

struct evdns_getaddrinfo_request;//insertRecordDeclare 

struct addrinfo;//insertRecordDeclare 

/*TD*/typedef void (*evdns_getaddrinfo_cb)(int, struct addrinfo *, void *);

#endif