#ifndef __HEADER_TYPE_H__ 
#define __HEADER_TYPE_H__
#include"../common.h" 
struct server_request;//insertRecordDeclare 

struct evdns_server_port;//insertRecordDeclare 

struct sockaddr;//insertRecordDeclare 

struct sockaddr_storage;//insertRecordDeclare 

struct server_reply_item;//insertRecordDeclare 

struct evdns_server_request;//insertRecordDeclare 

struct evdns_server_question;//insertRecordDeclare 


struct evdns_server_request {
    int flags;
    int nquestions;
    struct evdns_server_question **questions;
};


struct server_request {
    struct server_request *next_pending;
    struct server_request *prev_pending;
    uint16_t trans_id;
    struct evdns_server_port *port;
    struct sockaddr_storage addr;
    socklen_t addrlen;
    int n_answer;
    int n_authority;
    int n_additional;
    struct server_reply_item *answer;
    struct server_reply_item *authority;
    struct server_reply_item *additional;
    char *response;
    size_t response_len;
    struct evdns_server_request base;
};

/*TD*/typedef void (*evdns_request_callback_fn_type)(struct evdns_server_request *, void *);

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

struct event_base;//insertRecordDeclare 

struct timeval;//insertRecordDeclare 


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


struct evdns_server_port {
    int socket;
    int refcnt;
    char choked;
    char closing;
    evdns_request_callback_fn_type user_callback;
    void *user_data;
    struct event event;
    struct server_request *pending_replies;
    struct event_base *event_base;
    void *lock;
};

struct _IO_FILE;//insertRecordDeclare 


struct evdns_server_question {
    int type;
    int class;
    char name[1];
};

struct dnslabel_table;//insertRecordDeclare 

struct dnslabel_entry;//insertRecordDeclare 


struct dnslabel_entry {
    char *v;
    off_t pos;
};


struct dnslabel_table {
    int n_labels;
    struct dnslabel_entry labels[128];
};


struct server_reply_item {
    struct server_reply_item *next;
    char *name;
    uint16_t type;
    uint16_t class;
    uint32_t ttl;
    char is_name;
    uint16_t datalen;
    void *data;
};

/*TD*/typedef void (*event_callback_fn)(int, short, void *);

struct evthread_lock_callbacks;//insertRecordDeclare 


struct evthread_lock_callbacks {
    int lock_api_version;
    unsigned int supported_locktypes;
    void *(*alloc)(unsigned int);
    void (*free)(void *, unsigned int);
    int (*lock)(unsigned int, void *);
    int (*unlock)(unsigned int, void *);
};

#endif