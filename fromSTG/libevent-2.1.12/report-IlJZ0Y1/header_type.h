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

struct evconnlistener;//insertRecordDeclare 


struct evconnlistener;

struct bufferevent;//insertRecordDeclare 


struct bufferevent;

struct be_conn_hostname_result;//insertRecordDeclare 


struct be_conn_hostname_result {
    int dnserr;
    int what;
};

struct evdns_base;//insertRecordDeclare 


struct evdns_base;

struct evdns_server_port;//insertRecordDeclare 


struct evdns_server_port;

struct sockaddr_in;//insertRecordDeclare 

struct in_addr;//insertRecordDeclare 

struct sockaddr;//insertRecordDeclare 

/*TD*/typedef void (*evconnlistener_cb)(struct evconnlistener *, int, struct sockaddr *, int, void *);

struct evdns_server_request;//insertRecordDeclare 

/*TD*/typedef void (*evdns_request_callback_fn_type)(struct evdns_server_request *, void *);

struct rlimit;//insertRecordDeclare 

/*ENUM*/
enum bufferevent_options {
    BEV_OPT_CLOSE_ON_FREE = (1 << 0),
    BEV_OPT_THREADSAFE = (1 << 1),
    BEV_OPT_DEFER_CALLBACKS = (1 << 2),
    BEV_OPT_UNLOCK_CALLBACKS = (1 << 3)
};

/*TD*/typedef void (*bufferevent_data_cb)(struct bufferevent *, void *);

/*TD*/typedef void (*bufferevent_event_cb)(struct bufferevent *, short, void *);

struct addrinfo;//insertRecordDeclare 

#endif