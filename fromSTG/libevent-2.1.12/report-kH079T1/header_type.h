#ifndef __HEADER_TYPE_H__ 
#define __HEADER_TYPE_H__
#include"../common.h" 
struct testcase_t;//insertRecordDeclare 

struct event_base;//insertRecordDeclare 

struct eventop;//insertRecordDeclare 

struct event_changelist;//insertRecordDeclare 

struct event_change;//insertRecordDeclare 


struct event_changelist {
    struct event_change *changes;
    int n_changes;
    int changes_size;
};

struct evsig_info;//insertRecordDeclare 

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

struct sigaction;//insertRecordDeclare 


struct evsig_info {
    struct event ev_signal;
    int ev_signal_pair[2];
    int ev_signal_added;
    int ev_n_signals_added;
    struct sigaction **sh_old;
    int sh_old_max;
};

struct evcallback_list;//insertRecordDeclare 


struct evcallback_list {
    struct event_callback *tqh_first;
    struct event_callback **tqh_last;
};

struct common_timeout_list;//insertRecordDeclare 

struct event_signal_map;//insertRecordDeclare 


struct event_signal_map {
    void **entries;
    int nentries;
};

struct min_heap;//insertRecordDeclare 


struct min_heap {
    struct event **p;
    unsigned int n;
    unsigned int a;
};

struct evutil_monotonic_timer;//insertRecordDeclare 


struct evutil_monotonic_timer {
    int monotonic_clock;
    struct timeval adjust_monotonic_clock;
    struct timeval last_time;
};

/*ENUM*/
enum event_base_config_flag {
    EVENT_BASE_FLAG_NOLOCK = 1,
    EVENT_BASE_FLAG_IGNORE_ENV = 2,
    EVENT_BASE_FLAG_STARTUP_IOCP = 4,
    EVENT_BASE_FLAG_NO_CACHE_TIME = 8,
    EVENT_BASE_FLAG_EPOLL_USE_CHANGELIST = 16,
    EVENT_BASE_FLAG_PRECISE_TIMER = 32
};

struct evutil_weakrand_state;//insertRecordDeclare 


struct evutil_weakrand_state {
    uint32_t seed;
};

struct event_once;//insertRecordDeclare 


struct event_base {
    const struct eventop *evsel;
    void *evbase;
    struct event_changelist changelist;
    const struct eventop *evsigsel;
    struct evsig_info sig;
    int virtual_event_count;
    int virtual_event_count_max;
    int event_count;
    int event_count_max;
    int event_count_active;
    int event_count_active_max;
    int event_gotterm;
    int event_break;
    int event_continue;
    int event_running_priority;
    int running_loop;
    int n_deferreds_queued;
    struct evcallback_list *activequeues;
    int nactivequeues;
    struct evcallback_list active_later_queue;
    struct common_timeout_list **common_timeout_queues;
    int n_common_timeouts;
    int n_common_timeouts_allocated;
    struct event_signal_map io;
    struct event_signal_map sigmap;
    struct min_heap timeheap;
    struct timeval tv_cache;
    struct evutil_monotonic_timer monotonic_timer;
    struct timeval tv_clock_diff;
    time_t last_updated_clock_diff;
    unsigned long th_owner_id;
    void *th_base_lock;
    void *current_event_cond;
    int current_event_waiters;
    struct event_callback *current_event;
    enum event_base_config_flag flags;
    struct timeval max_dispatch_time;
    int max_dispatch_callbacks;
    int limit_callbacks_after_prio;
    int is_notify_pending;
    int th_notify_fd[2];
    struct event th_notify;
    int (*th_notify_fn)(struct event_base *);
    struct evutil_weakrand_state weakrand_seed;
    struct once_event_list {
        struct event_once *lh_first;
    } once_events;
};

struct basic_test_data;//insertRecordDeclare 


struct basic_test_data {
    struct event_base *base;
    int pair[2];
    void (*legacy_test_fn)(void);
    void *setup_data;
};

/*TD*/typedef void (*testcase_fn)(void *);

struct testcase_setup_t;//insertRecordDeclare 


struct testcase_t {
    const char *name;
    testcase_fn fn;
    unsigned long flags;
    const struct testcase_setup_t *setup;
    void *setup_data;
};

struct _IO_FILE;//insertRecordDeclare 

/*TD*/typedef void (*evdns_debug_log_fn_type)(int, const char *);

/*TD*/typedef void (*event_log_cb)(int, const char *);

#endif