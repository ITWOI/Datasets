#ifndef __HEADER_TYPE_H__ 
#define __HEADER_TYPE_H__
#include"../common.h" 
struct sockaddr_storage;//insertRecordDeclare 

struct sockaddr_in;//insertRecordDeclare 

struct sockaddr_in6;//insertRecordDeclare 

struct evdns_server_port;//insertRecordDeclare 

struct event_base;//insertRecordDeclare 

struct evdns_server_request;//insertRecordDeclare 

/*TD*/typedef void (*evdns_request_callback_fn_type)(struct evdns_server_request *, void *);


struct evdns_server_port;

struct in_addr;//insertRecordDeclare 

struct regress_dns_server_table;//insertRecordDeclare 

#endif