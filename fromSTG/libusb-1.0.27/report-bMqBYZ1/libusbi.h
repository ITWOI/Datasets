#include "header_func.h"
static inline void list_add (struct list_head *entry, struct list_head *head){
    entry->next = head->next;
    entry->prev = head;
    head->next->prev = entry;
    head->next = entry;
}
static inline void list_del (struct list_head *entry){
    entry->next->prev = entry->prev;
    entry->prev->next = entry->next;
    entry->next = entry->prev = ((void *)0);
}
static inline struct libusb_context * usbi_get_context (struct libusb_context *ctx){
    static int warned = 0;
    if (!ctx) {
        ctx = usbi_default_context;
    }
    if (!ctx) {
        ctx = usbi_fallback_context;
        if (ctx && warned == 0) {
            usbi_log(ctx, LIBUSB_LOG_LEVEL_ERROR, __func__, "API misuse! Using non-default context as implicit default.");
            warned = 1;
        }
    }
    return ctx;
}
static inline void usbi_get_monotonic_time (struct timespec *tp){
    ((void)sizeof ((clock_gettime(1, tp) == 0) ? 1 : 0) , __extension__ ({
        if (clock_gettime(1, tp) == 0)
            ;
        else
            __assert_fail("clock_gettime(1, tp) == 0", "./libusbi.h", 498, __extension__ __PRETTY_FUNCTION__);
    }));
}
