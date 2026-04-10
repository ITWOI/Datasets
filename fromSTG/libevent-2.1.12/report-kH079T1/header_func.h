#ifndef __HEADER_FUNC_H__ 
#define __HEADER_FUNC_H__
#include"header_type.h" 

void event_enable_debug_mode(void);

int libevent_tests_running_in_debug_mode = 0;
;

int evthread_use_pthreads(void);


int evutil_socketpair(int d, int type, int protocol, int sv[2]);


int evutil_make_socket_nonblocking(int sock);


struct event_base *event_init(void);


struct event_base *event_base_new(void);


int event_base_start_iocp_(struct event_base *base, int n_cpus);


void event_base_free(struct event_base *);


void evdns_set_log_fn(evdns_debug_log_fn_type fn);

static void dnslogcb(int w, const char *m) ;


int evdns_init(void);


void event_set_log_callback(event_log_cb cb);

static void ignore_log_cb(int s, const char *msg) ;

void *basic_test_setup(const struct testcase_t *testcase) ;

#endif