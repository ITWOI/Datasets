#include "header_func.h"
static void regress_pick_a_port (void *arg){
    struct basic_test_data *data = arg;
    struct event_base *base = data->base;
    struct evconnlistener *listener1 = ((void *)0), *listener2 = ((void *)0);
    struct sockaddr_in sin;
    int count1 = 2, count2 = 1;
    struct sockaddr_storage ss1, ss2;
    struct sockaddr_in *sin1, *sin2;
    socklen_t slen1 = sizeof (ss1), slen2 = sizeof (ss2);
    unsigned int flags;
    int fd1, fd2, fd3;
    fd1 = fd2 = fd3 = -1;
    if (data->setup_data && strstr((char *)data->setup_data, "ts")) {
        flags |= (1U << 4);
    }
    memset(&sin, 0, sizeof (sin));
    sin.sin_family = 2;
    sin.sin_addr.s_addr = htonl(2130706433);
    sin.sin_port = 0;
    listener1 = evconnlistener_new_bind(base, acceptcb, &count1, flags, -1, (struct sockaddr *)&sin, sizeof (sin));
    do {
        if (!((listener1))) {
            tinytest_set_test_failed_();
            do {
                printf("\n  %s %s:%d: ", "FAIL", "test/regress_listener_InstSlice.c", 88);
                printf("%s", "assert(listener1)");
            } while (0);
            do {
                goto end;
            } while (0);
        } else {
            do {
                if (tinytest_get_verbosity_() > 1)
                    do {
                        printf("\n  %s %s:%d: ", "  OK", "test/regress_listener_InstSlice.c", 88);
                        printf("%s", "assert(listener1)");
                    } while (0);
            } while (0);
        }
    } while (0);
    listener2 = evconnlistener_new_bind(base, acceptcb, &count2, flags, -1, (struct sockaddr *)&sin, sizeof (sin));
    do {
        if (!((listener2))) {
            tinytest_set_test_failed_();
            do {
                printf("\n  %s %s:%d: ", "FAIL", "test/regress_listener_InstSlice.c", 91);
                printf("%s", "assert(listener2)");
            } while (0);
            do {
                goto end;
            } while (0);
        } else {
            do {
                if (tinytest_get_verbosity_() > 1)
                    do {
                        printf("\n  %s %s:%d: ", "  OK", "test/regress_listener_InstSlice.c", 91);
                        printf("%s", "assert(listener2)");
                    } while (0);
            } while (0);
        }
    } while (0);
    do {
        if (!((evconnlistener_get_fd(listener1) != -1))) {
            tinytest_set_test_failed_();
            do {
                printf("\n  %s %s:%d: ", "FAIL", "test/regress_listener_InstSlice.c", 94);
                printf("%s", "assert(evconnlistener_get_fd(listener1) != EVUTIL_INVALID_SOCKET)");
            } while (0);
            do {
                goto end;
            } while (0);
        } else {
            do {
                if (tinytest_get_verbosity_() > 1)
                    do {
                        printf("\n  %s %s:%d: ", "  OK", "test/regress_listener_InstSlice.c", 94);
                        printf("%s", "assert(evconnlistener_get_fd(listener1) != EVUTIL_INVALID_SOCKET)");
                    } while (0);
            } while (0);
        }
    } while (0);
    do {
        if (!((evconnlistener_get_fd(listener2) != -1))) {
            tinytest_set_test_failed_();
            do {
                printf("\n  %s %s:%d: ", "FAIL", "test/regress_listener_InstSlice.c", 96);
                printf("%s", "assert(evconnlistener_get_fd(listener2) != EVUTIL_INVALID_SOCKET)");
            } while (0);
            do {
                goto end;
            } while (0);
        } else {
            do {
                if (tinytest_get_verbosity_() > 1)
                    do {
                        printf("\n  %s %s:%d: ", "  OK", "test/regress_listener_InstSlice.c", 96);
                        printf("%s", "assert(evconnlistener_get_fd(listener2) != EVUTIL_INVALID_SOCKET)");
                    } while (0);
            } while (0);
        }
    } while (0);
    do {
        if (!((getsockname(evconnlistener_get_fd(listener1), (__SOCKADDR_ARG){(struct sockaddr *)&ss1}, &slen1) == 0))) {
            tinytest_set_test_failed_();
            do {
                printf("\n  %s %s:%d: ", "FAIL", "test/regress_listener_InstSlice.c", 99);
                printf("%s", "assert(getsockname(evconnlistener_get_fd(listener1), (struct sockaddr*)&ss1, &slen1) == 0)");
            } while (0);
            do {
                goto end;
            } while (0);
        } else {
            do {
                if (tinytest_get_verbosity_() > 1)
                    do {
                        printf("\n  %s %s:%d: ", "  OK", "test/regress_listener_InstSlice.c", 99);
                        printf("%s", "assert(getsockname(evconnlistener_get_fd(listener1), (struct sockaddr*)&ss1, &slen1) == 0)");
                    } while (0);
            } while (0);
        }
    } while (0);
    do {
        if (!((getsockname(evconnlistener_get_fd(listener2), (__SOCKADDR_ARG){(struct sockaddr *)&ss2}, &slen2) == 0))) {
            tinytest_set_test_failed_();
            do {
                printf("\n  %s %s:%d: ", "FAIL", "test/regress_listener_InstSlice.c", 101);
                printf("%s", "assert(getsockname(evconnlistener_get_fd(listener2), (struct sockaddr*)&ss2, &slen2) == 0)");
            } while (0);
            do {
                goto end;
            } while (0);
        } else {
            do {
                if (tinytest_get_verbosity_() > 1)
                    do {
                        printf("\n  %s %s:%d: ", "  OK", "test/regress_listener_InstSlice.c", 101);
                        printf("%s", "assert(getsockname(evconnlistener_get_fd(listener2), (struct sockaddr*)&ss2, &slen2) == 0)");
                    } while (0);
            } while (0);
        }
    } while (0);
    do {
        long val1_ = (long)(ss1.ss_family);
        long val2_ = (long)(2);
        int tt_status_ = ((val1_ == val2_));
        if (!tt_status_ || tinytest_get_verbosity_() > 1) {
            long print_;
            long print1_;
            long print2_;
            long value_ = val1_;
            {
                print_ = value_;
            }
            ;
            print1_ = print_;
            value_ = val2_;
            {
                print_ = value_;
            }
            ;
            print2_ = print_;
            do {
                printf("\n  %s %s:%d: ", tt_status_ ? "\t OK" : "FAIL", "test/regress_listener_InstSlice.c", 102);
                printf("assert(%s): %ld vs %ld", "ss1.ss_family == AF_INET", print1_, print2_);
            } while (0);
            print_ = print1_;
            {
            }
            ;
            print_ = print2_;
            {
            }
            ;
            if (!tt_status_) {
                tinytest_set_test_failed_();
                do {
                    goto end;
                } while (0);
            }
        }
    } while (0);
  end:
    ;
}
