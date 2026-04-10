#ifndef __HEADER_FUNC_H__ 
#define __HEADER_FUNC_H__
#include"header_type.h" 

struct evhttp_bound_socket *evhttp_bind_socket_with_handle(struct evhttp *http, const char *address, uint16_t port);


void event_errx(int eval, const char *fmt, ...);


int regress_get_socket_port(int fd);


int evhttp_bound_socket_get_fd(struct evhttp_bound_socket *bound_socket);


struct evhttp *evhttp_new(struct event_base *base);

static int http_bind(struct evhttp *myhttp, uint16_t *pport, int mask) ;


void init_ssl(void);


void evhttp_set_bevcb(struct evhttp *http, struct bufferevent *(*cb)(struct event_base *, void *), void *arg);

static struct bufferevent *https_bev(struct event_base *base, void *arg) ;


void evhttp_set_gencb(struct evhttp *http, void (*cb)(struct evhttp_request *, void *), void *arg);


int evhttp_set_cb(struct evhttp *http, const char *path, void (*cb)(struct evhttp_request *, void *), void *cb_arg);

static void http_basic_cb(struct evhttp_request *req, void *arg);

static void http_timeout_cb(struct evhttp_request *req, void *arg);

static void http_large_cb(struct evhttp_request *req, void *arg);

static void http_chunked_cb(struct evhttp_request *req, void *arg);

static void http_post_cb(struct evhttp_request *req, void *arg);

static void http_put_cb(struct evhttp_request *req, void *arg);

static void http_delete_cb(struct evhttp_request *req, void *arg);

static void http_delay_cb(struct evhttp_request *req, void *arg);

static void http_large_delay_cb(struct evhttp_request *req, void *arg);

static void http_badreq_cb(struct evhttp_request *req, void *arg);

static void http_on_complete_cb(struct evhttp_request *req, void *arg);

static void http_dispatcher_cb(struct evhttp_request *req, void *arg);

static struct evhttp *http_setup_gencb(uint16_t *pport, struct event_base *base, int mask, void (*cb)(struct evhttp_request *, void *), void *cbarg) ;


void evhttp_connection_free(struct evhttp_connection *evcon);


struct evhttp_connection *evhttp_connection_base_new(struct event_base *base, struct evdns_base *dnsbase, const char *address, uint16_t port);


void tinytest_set_test_failed_(void);


int tinytest_get_verbosity_(void);


void evhttp_connection_set_timeout(struct evhttp_connection *evcon, int timeout_in_secs);


struct evhttp_request *evhttp_request_new(void (*cb)(struct evhttp_request *, void *), void *arg);

static void http_request_never_call(struct evhttp_request *req, void *arg) ;


int evhttp_make_request(struct evhttp_connection *evcon, struct evhttp_request *req, enum evhttp_cmd_type type, const char *uri);

extern FILE *stderr;
;
static void http_timed_out_request_done(struct evhttp_request *req, void *arg) ;

static void http_failed_request_done(struct evhttp_request *req, void *arg) ;

static struct evhttp *http_setup(uint16_t *pport, struct event_base *base, int mask) ;


int regress_dnsserver(struct event_base *base, uint16_t *port, struct regress_dns_server_table *seach_table);


struct evdns_base *evdns_base_new(struct event_base *event_base, int initialize_nameservers);


int evutil_snprintf(char *buf, size_t buflen, const char *format, ...);


int evdns_base_nameserver_ip_add(struct evdns_base *base, const char *ip_as_string);


int evdns_base_set_option(struct evdns_base *base, const char *option, const char *val);

static struct regress_dns_server_table search_table[] = {{"localhost", "A", "127.0.0.1", 0, 0}, {((void *)0), ((void *)0), ((void *)0), 0, 0}};
;
static struct event_base *exit_base;
;
extern int test_ok;
;

struct event_base *event_base_new(void);

static struct evhttp_connection **http_fill_backlog(struct event_base *base, int port) ;


struct bufferevent *evhttp_connection_get_bufferevent(struct evhttp_connection *evcon);


struct evbuffer_cb_entry *evbuffer_add_cb(struct evbuffer *buffer, evbuffer_cb_func cb, void *cbarg);


struct evbuffer *bufferevent_get_output(struct bufferevent *bufev);

static void http_no_write(struct evbuffer *buffer, const struct evbuffer_cb_info *info, void *arg) ;


void evhttp_request_set_error_cb(struct evhttp_request *, void (*)(enum evhttp_request_error, void *));

static void http_request_error_cb_with_cancel(enum evhttp_request_error error, void *arg) ;


int evhttp_add_header(struct evkeyvalq *headers, const char *key, const char *value);


struct evkeyvalq *evhttp_request_get_output_headers(struct evhttp_request *req);


int event_base_once(struct event_base *, int, short, event_callback_fn, void *, const struct timeval *);

static void http_do_cancel(int fd, short what, void *arg) ;


int event_base_dispatch(struct event_base *);

static void http_free_evcons(struct evhttp_connection **evcons) ;

static struct evhttp_request *http_cancel_test_bad_request_new(enum http_cancel_test_type type, struct event_base *base) ;

static void http_request_done(struct evhttp_request *, void *);

static const char BASIC_REQUEST_BODY[] = "This is funny";
;
static void http_request_empty_done(struct evhttp_request *, void *);


int evbuffer_remove_cb(struct evbuffer *buffer, evbuffer_cb_func cb, void *cbarg);

#endif