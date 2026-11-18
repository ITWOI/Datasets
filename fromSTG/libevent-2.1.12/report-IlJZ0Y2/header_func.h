#ifndef __HEADER_FUNC_H__ 
#define __HEADER_FUNC_H__
#include"header_type.h" 

struct event_base *event_base_new(void);


void tinytest_set_test_failed_(void);


int tinytest_get_verbosity_(void);


int evthread_make_base_notifiable(struct event_base *base);


struct evdns_server_port *regress_get_dnsserver(struct event_base *base, uint16_t *portnum, int *psock, evdns_request_callback_fn_type cb, void *arg);


void regress_dns_server_cb(struct evdns_server_request *req, void *data);

static struct regress_dns_server_table reissue_table[] = {{"foof.example.com", "A", "240.15.240.15", 0, 0}, {((void *)0), ((void *)0), ((void *)0), 0, 0}};
;

struct evdns_base *evdns_base_new(struct event_base *event_base, int initialize_nameservers);


int evdns_base_nameserver_ip_add(struct evdns_base *base, const char *ip_as_string);

extern struct evthread_lock_callbacks evthread_lock_fns_;
;
extern struct evthread_condition_callbacks evthread_cond_fns_;
;
static void *race_busywait_run(void *arg) ;


void thread_setup(pthread_t pthread);


struct evdns_getaddrinfo_request *evdns_getaddrinfo(struct evdns_base *dns_base, const char *nodename, const char *servname, const struct addrinfo *hints_in, evdns_getaddrinfo_cb cb, void *arg);

static void race_gai_cb(int result, struct addrinfo *res, void *arg) ;


void evutil_usleep_(const struct timeval *tv);

#endif