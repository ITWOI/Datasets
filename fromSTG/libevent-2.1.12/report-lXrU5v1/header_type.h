#ifndef __HEADER_TYPE_H__ 
#define __HEADER_TYPE_H__
#include"../common.h" 
struct evhttp;//insertRecordDeclare 

struct evhttp_bound_socket;//insertRecordDeclare 

struct evconnlistener;//insertRecordDeclare 


struct evhttp_bound_socket {
    struct {
        struct evhttp_bound_socket *tqe_next;
        struct evhttp_bound_socket **tqe_prev;
    } next;
    struct evconnlistener *listener;
};

struct event_base;//insertRecordDeclare 

struct evhttp_request;//insertRecordDeclare 

struct evhttp_cb;//insertRecordDeclare 

struct evconq;//insertRecordDeclare 

struct evhttp_connection;//insertRecordDeclare 


struct evconq {
    struct evhttp_connection *tqh_first;
    struct evhttp_connection **tqh_last;
};

struct evhttp_server_alias;//insertRecordDeclare 

struct timeval;//insertRecordDeclare 

struct bufferevent;//insertRecordDeclare 


struct evhttp {
    struct {
        struct evhttp *tqe_next;
        struct evhttp **tqe_prev;
    } next_vhost;
    struct boundq {
        struct evhttp_bound_socket *tqh_first;
        struct evhttp_bound_socket **tqh_last;
    } sockets;
    struct httpcbq {
        struct evhttp_cb *tqh_first;
        struct evhttp_cb **tqh_last;
    } callbacks;
    struct evconq connections;
    struct vhostsq {
        struct evhttp *tqh_first;
        struct evhttp **tqh_last;
    } virtualhosts;
    struct aliasq {
        struct evhttp_server_alias *tqh_first;
        struct evhttp_server_alias **tqh_last;
    } aliases;
    char *vhost_pattern;
    struct timeval timeout;
    size_t default_max_headers_size;
    uint64_t default_max_body_size;
    int flags;
    const char *default_content_type;
    uint16_t allowed_methods;
    void (*gencb)(struct evhttp_request *, void *);
    void *gencbarg;
    struct bufferevent *(*bevcb)(struct event_base *, void *);
    void *bevcbarg;
    struct event_base *base;
};

struct event;//insertRecordDeclare 

struct event_callback;//insertRecordDeclare 


struct event_callback {
    struct {
        struct event_callback *tqe_next;
        struct event_callback **tqe_prev;
    } evcb_active_next;
    short evcb_flags;
    uint8_t evcb_pri;
    uint8_t evcb_closure;
    union {
        void (*evcb_callback)(int, short, void *);
        void (*evcb_selfcb)(struct event_callback *, void *);
        void (*evcb_evfinalize)(struct event *, void *);
        void (*evcb_cbfinalize)(struct event_callback *, void *);
    } evcb_cb_union;
    void *evcb_arg;
};


struct event {
    struct event_callback ev_evcallback;
    union {
        struct {
            struct event *tqe_next;
            struct event **tqe_prev;
        } ev_next_with_common_timeout;
        int min_heap_idx;
    } ev_timeout_pos;
    int ev_fd;
    struct event_base *ev_base;
    union {
        struct {
            struct {
                struct event *le_next;
                struct event **le_prev;
            } ev_io_next;
            struct timeval ev_timeout;
        } ev_io;
        struct {
            struct {
                struct event *le_next;
                struct event **le_prev;
            } ev_signal_next;
            short ev_ncalls;
            short *ev_pncalls;
        } ev_signal;
    } ev_;
    short ev_events;
    short ev_res;
    struct timeval ev_timeout;
};

/*ENUM*/
enum evhttp_connection_state {
    EVCON_DISCONNECTED,
    EVCON_CONNECTING,
    EVCON_IDLE,
    EVCON_READING_FIRSTLINE,
    EVCON_READING_HEADERS,
    EVCON_READING_BODY,
    EVCON_READING_TRAILER,
    EVCON_WRITING
};

struct evdns_base;//insertRecordDeclare 


struct evhttp_connection {
    struct {
        struct evhttp_connection *tqe_next;
        struct evhttp_connection **tqe_prev;
    } next;
    int fd;
    struct bufferevent *bufev;
    struct event retry_ev;
    char *bind_address;
    uint16_t bind_port;
    char *address;
    uint16_t port;
    size_t max_headers_size;
    uint64_t max_body_size;
    int flags;
    struct timeval timeout;
    int retry_cnt;
    int retry_max;
    struct timeval initial_retry_timeout;
    enum evhttp_connection_state state;
    struct evhttp *http_server;
    struct evcon_requestq {
        struct evhttp_request *tqh_first;
        struct evhttp_request **tqh_last;
    } requests;
    void (*cb)(struct evhttp_connection *, void *);
    void *cb_arg;
    void (*closecb)(struct evhttp_connection *, void *);
    void *closecb_arg;
    struct event_callback read_more_deferred_cb;
    struct event_base *base;
    struct evdns_base *dns_base;
    int ai_family;
};


struct evhttp_request;

/*ENUM*/
enum evhttp_cmd_type {
    EVHTTP_REQ_GET = 1 << 0,
    EVHTTP_REQ_POST = 1 << 1,
    EVHTTP_REQ_HEAD = 1 << 2,
    EVHTTP_REQ_PUT = 1 << 3,
    EVHTTP_REQ_DELETE = 1 << 4,
    EVHTTP_REQ_OPTIONS = 1 << 5,
    EVHTTP_REQ_TRACE = 1 << 6,
    EVHTTP_REQ_CONNECT = 1 << 7,
    EVHTTP_REQ_PATCH = 1 << 8
};

struct _IO_FILE;//insertRecordDeclare 

/*ENUM*/
enum http_cancel_test_type {
    BASIC = 1,
    BY_HOST = 2,
    NO_NS = 4,
    INACTIVE_SERVER = 8,
    SERVER_TIMEOUT = 16,
    NS_TIMEOUT = 32
};

struct basic_test_data;//insertRecordDeclare 


struct basic_test_data {
    struct event_base *base;
    int pair[2];
    void (*legacy_test_fn)(void);
    void *setup_data;
};


struct bufferevent;


struct evdns_base;


struct event_base;

struct regress_dns_server_table;//insertRecordDeclare 


struct regress_dns_server_table {
    const char *q;
    const char *anstype;
    const char *ans;
    int seen;
    int lower;
};

struct evbuffer_cb_entry;//insertRecordDeclare 

struct evbuffer;//insertRecordDeclare 

struct evbuffer_cb_info;//insertRecordDeclare 

/*TD*/typedef void (*evbuffer_cb_func)(struct evbuffer *, const struct evbuffer_cb_info *, void *);

/*ENUM*/
enum evhttp_request_error {
    EVREQ_HTTP_TIMEOUT,
    EVREQ_HTTP_EOF,
    EVREQ_HTTP_INVALID_HEADER,
    EVREQ_HTTP_BUFFER_ERROR,
    EVREQ_HTTP_REQUEST_CANCEL,
    EVREQ_HTTP_DATA_TOO_LONG
};

struct evkeyvalq;//insertRecordDeclare 

/*TD*/typedef void (*event_callback_fn)(int, short, void *);

#endif