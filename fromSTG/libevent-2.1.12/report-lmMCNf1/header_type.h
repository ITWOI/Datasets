#ifndef __HEADER_TYPE_H__ 
#define __HEADER_TYPE_H__
#include"../common.h" 
struct evbuffer;//insertRecordDeclare 

struct evbuffer_chain;//insertRecordDeclare 

/*TD*/typedef int64_t ev_misalign_t;


struct evbuffer_chain {
    struct evbuffer_chain *next;
    size_t buffer_len;
    ev_misalign_t misalign;
    size_t off;
    unsigned int flags;
    int refcnt;
    unsigned char *buffer;
};

struct event_base;//insertRecordDeclare 

struct event_callback;//insertRecordDeclare 

struct event;//insertRecordDeclare 


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

struct evbuffer_cb_entry;//insertRecordDeclare 

struct bufferevent;//insertRecordDeclare 


struct evbuffer {
    struct evbuffer_chain *first;
    struct evbuffer_chain *last;
    struct evbuffer_chain **last_with_datap;
    size_t total_len;
    size_t n_add_for_cb;
    size_t n_del_for_cb;
    void *lock;
    unsigned int own_lock : 1;
    unsigned int freeze_start : 1;
    unsigned int freeze_end : 1;
    unsigned int deferred_cbs : 1;
    uint32_t flags;
    struct event_base *cb_queue;
    int refcnt;
    struct event_callback deferred;
    struct evbuffer_cb_queue {
        struct evbuffer_cb_entry *lh_first;
    } callbacks;
    struct bufferevent *parent;
};

/*ENUM*/
enum evbuffer_eol_style {
    EVBUFFER_EOL_ANY,
    EVBUFFER_EOL_CRLF,
    EVBUFFER_EOL_CRLF_STRICT,
    EVBUFFER_EOL_LF,
    EVBUFFER_EOL_NUL
};

#endif