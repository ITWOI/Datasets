#ifndef __HEADER_TYPE_H__ 
#define __HEADER_TYPE_H__
#include"../common.h" 
struct basic_test_data;//insertRecordDeclare 

struct event_base;//insertRecordDeclare 


struct basic_test_data {
    struct event_base *base;
    int pair[2];
    void (*legacy_test_fn)(void);
    void *setup_data;
};


struct event_base;

struct evconnlistener;//insertRecordDeclare 


struct evconnlistener;

struct sockaddr_in;//insertRecordDeclare 

struct sockaddr_storage;//insertRecordDeclare 

struct in_addr;//insertRecordDeclare 

struct sockaddr;//insertRecordDeclare 

/*TD*/typedef void (*evconnlistener_cb)(struct evconnlistener *, int, struct sockaddr *, int, void *);

#endif