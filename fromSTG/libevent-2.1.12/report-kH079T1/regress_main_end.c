#include "header_func.h"
extern void * basic_test_setup (const struct testcase_t *testcase){
    struct event_base *base = ((void *)0);
    int spair[2] = {-1, -1};
    struct basic_test_data *data = ((void *)0);
    if (testcase->flags & ((1 << 5) << 6))
        return (void *)(1 << 1);
    if (testcase->flags & (((1 << 5) << 6) << 7) && !libevent_tests_running_in_debug_mode) {
        event_enable_debug_mode();
        libevent_tests_running_in_debug_mode = 1;
    }
    if (testcase->flags & ((1 << 5) << 4)) {
        if (!(testcase->flags & (1 << 0)))
            return ((void *)0);
        if (evthread_use_pthreads()) {
        }
        ;
    }
    if (testcase->flags & (1 << 5)) {
        if (evutil_socketpair(1, SOCK_STREAM, 0, spair) == -1) {
            ;
        }
        if (evutil_make_socket_nonblocking(spair[0]) == -1) {
            ;
        }
        if (evutil_make_socket_nonblocking(spair[1]) == -1) {
            ;
        }
    }
    if (testcase->flags & ((1 << 5) << 1)) {
        if (testcase->flags & ((1 << 5) << 3)) {
            base = event_init();
        } else
            base = event_base_new();
        if (!base) {
        }
        ;
    }
    if (testcase->flags & ((1 << 5) << 6)) {
        if (event_base_start_iocp_(base, 0) < 0) {
            event_base_free(base);
            return (void *)(1 << 1);
        }
    }
    if (testcase->flags & ((1 << 5) << 2)) {
        evdns_set_log_fn(dnslogcb);
        if (evdns_init())
            return ((void *)0);
    }
    if (testcase->flags & ((1 << 5) << 5))
        event_set_log_callback(ignore_log_cb);
    data = calloc(1, sizeof (*data));
    if (!data) {
    }
    ;
    data->base = base;
    data->pair[0] = spair[0];
    data->pair[1] = spair[1];
    data->setup_data = testcase->setup_data;
    return data;
}
static void * legacy_test_setup (const struct testcase_t *testcase){
    struct basic_test_data *data = basic_test_setup(testcase);
    if (data == (void *)(1 << 1) || data == ((void *)0))
        return data;
    return data;
}
