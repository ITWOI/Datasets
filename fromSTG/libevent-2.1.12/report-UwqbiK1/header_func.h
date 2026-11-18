#ifndef __HEADER_FUNC_H__ 
#define __HEADER_FUNC_H__
#include"header_type.h" 
extern int evthread_lock_debugging_enabled_;
;
extern FILE *stderr;
;

int evthread_is_debug_lock_held_(void *lock);


void event_errx(int eval, const char *fmt, ...);


void *event_mm_malloc_(size_t sz);


void *event_mm_calloc_(size_t count, size_t size);

static int name_parse(uint8_t *packet, int length, int *idx, char *name_out, int name_out_len) ;

int evdns_server_request_respond(struct evdns_server_request *req, int err);


void event_mm_free_(void *p);

static void evdns_log_(int severity, const char *fmt, ...) ;

static int request_parse(uint8_t *packet, int length, struct evdns_server_port *port, struct sockaddr *addr, socklen_t addrlen) ;

static int server_request_free(struct server_request *req);

static void server_port_flush(struct evdns_server_port *port) ;

static void server_port_read(struct evdns_server_port *s) ;


char *event_mm_strdup_(const char *str);

static int dnslabel_table_get_pos(const struct dnslabel_table *table, const char *label) ;

static int dnslabel_table_add(struct dnslabel_table *table, const char *label, off_t pos) ;

static void dnslabel_table_init(struct dnslabel_table *table) ;

static off_t dnsname_to_labels(uint8_t *const buf, size_t buf_len, off_t j, const char *name, const size_t name_len, struct dnslabel_table *table) ;

static void dnslabel_clear(struct dnslabel_table *table) ;

static void server_request_free_answers(struct server_request *req);

static int evdns_server_request_format_response(struct server_request *req, int err) ;


int event_del(struct event *);


int event_assign(struct event *, struct event_base *, int, short, event_callback_fn, void *);

static void server_port_ready_callback(int fd, short events, void *arg) ;


int event_add(struct event *ev, const struct timeval *timeout);

static void server_port_free(struct evdns_server_port *port);


int evutil_closesocket(int sock);

extern struct evthread_lock_callbacks evthread_lock_fns_;
;
#endif