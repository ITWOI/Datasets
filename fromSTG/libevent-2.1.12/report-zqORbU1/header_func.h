#ifndef __HEADER_FUNC_H__ 
#define __HEADER_FUNC_H__
#include"header_type.h" 
static inline int min_heap_reserve_(min_heap_t *s, unsigned int n);

static inline void min_heap_shift_up_(min_heap_t *s, unsigned int hole_index, struct event *e);

static inline void min_heap_shift_up_unconditional_(min_heap_t *s, unsigned int hole_index, struct event *e);

static inline void min_heap_shift_down_(min_heap_t *s, unsigned int hole_index, struct event *e);

void *event_mm_realloc_(void *p, size_t sz);

int event_debug_mode_on_ = 0;
;
static void *event_debug_map_lock_ = ((void *)0);
;
extern struct evthread_lock_callbacks evthread_lock_fns_;
;
static struct event_debug_map global_debug_map = {((void *)0), 0, 0, 0, -1};
;
static inline struct event_debug_entry *event_debug_map_HT_REMOVE(struct event_debug_map *head, struct event_debug_entry *elm) ;

void event_mm_free_(void *p);

static int event_debug_mode_too_late = 0;
;
static inline struct event_debug_entry *event_debug_map_HT_FIND(const struct event_debug_map *head, struct event_debug_entry *elm) ;


void event_errx(int eval, const char *fmt, ...);

extern int evthread_lock_debugging_enabled_;
;
extern FILE *stderr;
;

int evthread_is_debug_lock_held_(void *lock);


int evutil_gettime_monotonic_(struct evutil_monotonic_timer *mt, struct timeval *tv);

static int gettime(struct event_base *base, struct timeval *tp) ;

int event_add_nolock_(struct event *ev, const struct timeval *tv, int tv_is_absolute);

static inline int is_same_common_timeout(const struct timeval *tv1, const struct timeval *tv2) ;

static inline int is_common_timeout(const struct timeval *tv, const struct event_base *base) ;

static inline struct event *event_callback_to_event(struct event_callback *evcb) ;

static void event_queue_remove_active(struct event_base *, struct event_callback *);

int event_del_nolock_(struct event *ev, int blocking);


void event_debugx_(const char *fmt, ...);

static inline void event_signal_closure(struct event_base *base, struct event *ev) ;

static inline void event_persist_closure(struct event_base *base, struct event *ev) ;

static void event_debug_note_teardown_(const struct event *ev) ;

static inline void update_time_cache(struct event_base *base) ;

extern uint32_t event_debug_logging_mask_;
;
extern struct evthread_condition_callbacks evthread_cond_fns_;
;
static void event_debug_assert_is_setup_(const struct event *ev) ;

unsigned int min_heap_size_(min_heap_t *s) ;

static inline struct event_callback *event_to_event_callback(struct event *ev) ;

extern unsigned long (*evthread_id_fn_)(void);
;

int evmap_io_add_(struct event_base *base, int fd, struct event *ev);


int evmap_signal_add_(struct event_base *base, int signum, struct event *ev);

static void event_queue_insert_inserted(struct event_base *, struct event *);

static void event_queue_remove_timeout(struct event_base *, struct event *);

static void event_queue_insert_timeout(struct event_base *, struct event *);

static void common_timeout_schedule(struct common_timeout_list *ctl, const struct timeval *now, struct event *head) ;

int min_heap_elt_is_top_(const struct event *e) ;

struct event *min_heap_top_(min_heap_t *s) ;

static inline struct common_timeout_list *get_common_timeout_list(struct event_base *base, const struct timeval *tv) ;

static int evthread_notify_base(struct event_base *base) ;

static void event_debug_note_add_(const struct event *ev) ;

static void event_queue_remove_active_later(struct event_base *, struct event_callback *);

static void event_queue_remove_inserted(struct event_base *, struct event *);


int evmap_io_del_(struct event_base *base, int fd, struct event *ev);


int evmap_signal_del_(struct event_base *base, int signum, struct event *ev);

static int event_haveevents(struct event_base *base) ;

static void event_debug_note_del_(const struct event *ev) ;

int min_heap_erase_(min_heap_t *s, struct event *e) ;

static void insert_common_timeout_inorder(struct common_timeout_list *ctl, struct event *ev) ;

int min_heap_push_(min_heap_t *s, struct event *e) ;

static void *(*mm_realloc_fn_)(void *, size_t) = ((void *)0);
;
static void (*mm_free_fn_)(void *) = ((void *)0);
;
#endif