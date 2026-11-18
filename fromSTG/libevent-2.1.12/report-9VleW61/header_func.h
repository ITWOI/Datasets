#ifndef __HEADER_FUNC_H__ 
#define __HEADER_FUNC_H__
#include"header_type.h" 

void tinytest_set_test_failed_(void);


int evutil_closesocket(int sock);


struct evdns_server_port *evdns_add_server_port_with_base(struct event_base *base, int socket, int flags, evdns_request_callback_fn_type callback, void *user_data);

int regress_get_socket_port(int fd) ;

struct evdns_server_port *regress_get_dnsserver(struct event_base *base, uint16_t *portnum, int *psock, evdns_request_callback_fn_type cb, void *arg) ;

void regress_dns_server_cb(struct evdns_server_request *req, void *data) ;

static struct evdns_server_port *dns_port;
;
int dns_sock = -1;
;
#endif