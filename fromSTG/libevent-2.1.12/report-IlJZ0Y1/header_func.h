#ifndef __HEADER_FUNC_H__ 
#define __HEADER_FUNC_H__
#include"header_type.h" 
static struct event_base *be_connect_hostname_base = ((void *)0);
;

struct evconnlistener *evconnlistener_new_bind(struct event_base *base, evconnlistener_cb cb, void *ptr, unsigned int flags, int backlog, const struct sockaddr *sa, int socklen);

static void nil_accept_cb(struct evconnlistener *l, int fd, struct sockaddr *s, int socklen, void *arg) ;


void tinytest_set_test_failed_(void);


int tinytest_get_verbosity_(void);


int regress_get_socket_port(int fd);


int evconnlistener_get_fd(struct evconnlistener *lev);


struct evdns_server_port *regress_get_dnsserver(struct event_base *base, uint16_t *portnum, int *psock, evdns_request_callback_fn_type cb, void *arg);

static void be_getaddrinfo_server_cb(struct evdns_server_request *req, void *data) ;


struct evdns_base *evdns_base_new(struct event_base *event_base, int initialize_nameservers);


struct bufferevent *bufferevent_socket_new(struct event_base *base, int fd, int options);


void bufferevent_setcb(struct bufferevent *bufev, bufferevent_data_cb readcb, bufferevent_data_cb writecb, bufferevent_event_cb eventcb, void *cbarg);

static void be_connect_hostname_event_cb(struct bufferevent *bev, short what, void *ctx) ;


int bufferevent_socket_connect_hostname(struct bufferevent *, struct evdns_base *, int, const char *, int);


int evutil_getaddrinfo(const char *nodename, const char *servname, const struct addrinfo *hints_in, struct addrinfo **res);


int event_base_dispatch(struct event_base *);


void bufferevent_free(struct bufferevent *bufev);

#endif