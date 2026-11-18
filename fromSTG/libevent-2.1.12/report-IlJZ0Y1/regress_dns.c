static void test_bufferevent_connect_hostname (void *arg){
    struct basic_test_data *data = arg;
    struct evconnlistener *listener = ((void *)0);
    struct bufferevent *be[5];
    struct be_conn_hostname_result be_outcome[5];
    int expect_err;
    struct evdns_base *dns = ((void *)0);
    struct evdns_server_port *port = ((void *)0);
    struct sockaddr_in sin;
    int listener_port = -1;
    uint16_t dns_port = 0;
    int n_accept = 0, n_dns = 0;
    char buf[128];
    int emfile = data->setup_data && !strcmp(data->setup_data, "emfile");
    unsigned int i;
    int ret;
    be_connect_hostname_base = data->base;
    memset(&sin, 0, sizeof (sin));
    sin.sin_family = 2;
    sin.sin_addr.s_addr = htonl(2130706433);
    sin.sin_port = 0;
    listener = evconnlistener_new_bind(data->base, nil_accept_cb, &n_accept, (1U << 3) | (1U << 2), -1, (struct sockaddr *)&sin, sizeof (sin));
    do {
        if (!((listener))) {
            tinytest_set_test_failed_();
            do {
                printf("\n  %s %s:%d: ", "FAIL", "test/regress_dns_InstSlice.c", 313);
                printf("%s", "assert(listener)");
            } while (0);
            do {
                goto end;
            } while (0);
        } else {
            do {
                if (tinytest_get_verbosity_() > 1)
                    do {
                        printf("\n  %s %s:%d: ", "  OK", "test/regress_dns_InstSlice.c", 313);
                        printf("%s", "assert(listener)");
                    } while (0);
            } while (0);
        }
    } while (0);
    ;
    ;
    listener_port = regress_get_socket_port(evconnlistener_get_fd(listener));
    port = regress_get_dnsserver(data->base, &dns_port, ((void *)0), be_getaddrinfo_server_cb, &n_dns);
    do {
        if (!((port))) {
            tinytest_set_test_failed_();
            do {
                printf("\n  %s %s:%d: ", "FAIL", "test/regress_dns_InstSlice.c", 318);
                printf("%s", "assert(port)");
            } while (0);
            do {
                goto end;
            } while (0);
        } else {
            do {
                if (tinytest_get_verbosity_() > 1)
                    do {
                        printf("\n  %s %s:%d: ", "  OK", "test/regress_dns_InstSlice.c", 318);
                        printf("%s", "assert(port)");
                    } while (0);
            } while (0);
        }
    } while (0);
    ;
    ;
    do {
        long val1_ = (long)(dns_port);
        long val2_ = (long)(0);
        int tt_status_ = ((val1_ >= val2_));
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
                printf("\n  %s %s:%d: ", tt_status_ ? "\t OK" : "FAIL", "test/regress_dns_InstSlice.c", 320);
                printf("assert(%s): %ld vs %ld", "dns_port >= 0", print1_, print2_);
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
    dns = evdns_base_new(data->base, 0);
    ;
    ;
    if (emfile) {
        int fd = socket(2, SOCK_STREAM, 0);
        struct rlimit file = {fd, fd};
        do {
            long val1_ = (long)(fd);
            long val2_ = (long)(0);
            int tt_status_ = ((val1_ >= val2_));
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
                    printf("\n  %s %s:%d: ", tt_status_ ? "\t OK" : "FAIL", "test/regress_dns_InstSlice.c", 332);
                    printf("assert(%s): %ld vs %ld", "fd >= 0", print1_, print2_);
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
        do {
            if (!((!close(fd)))) {
                tinytest_set_test_failed_();
                do {
                    printf("\n  %s %s:%d: ", "FAIL", "test/regress_dns_InstSlice.c", 333);
                    printf("%s", "assert(!close(fd))");
                } while (0);
                do {
                    goto end;
                } while (0);
            } else {
                do {
                    if (tinytest_get_verbosity_() > 1)
                        do {
                            printf("\n  %s %s:%d: ", "  OK", "test/regress_dns_InstSlice.c", 333);
                            printf("%s", "assert(!close(fd))");
                        } while (0);
                } while (0);
            }
        } while (0);
        ;
        ;
        do {
            if (!((!setrlimit(RLIMIT_NOFILE, &file)))) {
                tinytest_set_test_failed_();
                do {
                    printf("\n  %s %s:%d: ", "FAIL", "test/regress_dns_InstSlice.c", 336);
                    printf("%s", "assert(!setrlimit(RLIMIT_NOFILE, &file))");
                } while (0);
                do {
                    goto end;
                } while (0);
            } else {
                do {
                    if (tinytest_get_verbosity_() > 1)
                        do {
                            printf("\n  %s %s:%d: ", "  OK", "test/regress_dns_InstSlice.c", 336);
                            printf("%s", "assert(!setrlimit(RLIMIT_NOFILE, &file))");
                        } while (0);
                } while (0);
            }
        } while (0);
        ;
        ;
    }
    for (i = 0; i < (sizeof (be) / sizeof (be[0])); ++i) {
        memset(&be_outcome[i], 0, sizeof (be_outcome[i]));
        be[i] = bufferevent_socket_new(data->base, -1, BEV_OPT_CLOSE_ON_FREE);
        ;
    }
    do {
        if (!((!bufferevent_socket_connect_hostname(be[3], ((void *)0), 2, "localhost", listener_port)))) {
            tinytest_set_test_failed_();
            do {
                printf("\n  %s %s:%d: ", "FAIL", "test/regress_dns_InstSlice.c", 353);
                printf("%s", "assert(!bufferevent_socket_connect_hostname(be[3], NULL, AF_INET, \"localhost\", listener_port))");
            } while (0);
            do {
                goto end;
            } while (0);
        } else {
            do {
                if (tinytest_get_verbosity_() > 1)
                    do {
                        printf("\n  %s %s:%d: ", "  OK", "test/regress_dns_InstSlice.c", 353);
                        printf("%s", "assert(!bufferevent_socket_connect_hostname(be[3], NULL, AF_INET, \"localhost\", listener_port))");
                    } while (0);
            } while (0);
        }
    } while (0);
    ;
    do {
        if (!((!bufferevent_socket_connect_hostname(be[4], ((void *)0), 2, "nonesuch.nowhere.example.com", 80)))) {
            tinytest_set_test_failed_();
            do {
                printf("\n  %s %s:%d: ", "FAIL", "test/regress_dns_InstSlice.c", 356);
                printf("%s", "assert(!bufferevent_socket_connect_hostname(be[4], NULL, AF_INET, \"nonesuch.nowhere.example.com\", 80))");
            } while (0);
            do {
                goto end;
            } while (0);
        } else {
            do {
                if (tinytest_get_verbosity_() > 1)
                    do {
                        printf("\n  %s %s:%d: ", "  OK", "test/regress_dns_InstSlice.c", 356);
                        printf("%s", "assert(!bufferevent_socket_connect_hostname(be[4], NULL, AF_INET, \"nonesuch.nowhere.example.com\", 80))");
                    } while (0);
            } while (0);
        }
    } while (0);
    ;
    {
        struct addrinfo hints, *ai = ((void *)0);
        memset(&hints, 0, sizeof (hints));
        hints.ai_family = 2;
        hints.ai_socktype = SOCK_STREAM;
        hints.ai_protocol = IPPROTO_TCP;
        expect_err = evutil_getaddrinfo("nonesuch.nowhere.example.com", "80", &hints, &ai);
    }
    do {
        if (!((!bufferevent_socket_connect_hostname(be[0], dns, 2, "nosuchplace.example.com", listener_port)))) {
            tinytest_set_test_failed_();
            do {
                printf("\n  %s %s:%d: ", "FAIL", "test/regress_dns_InstSlice.c", 368);
                printf("%s", "assert(!bufferevent_socket_connect_hostname(be[0], dns, AF_INET, \"nosuchplace.example.com\", listener_port))");
            } while (0);
            do {
                goto end;
            } while (0);
        } else {
            do {
                if (tinytest_get_verbosity_() > 1)
                    do {
                        printf("\n  %s %s:%d: ", "  OK", "test/regress_dns_InstSlice.c", 368);
                        printf("%s", "assert(!bufferevent_socket_connect_hostname(be[0], dns, AF_INET, \"nosuchplace.example.com\", listener_port))");
                    } while (0);
            } while (0);
        }
    } while (0);
    ;
    do {
        if (!((!bufferevent_socket_connect_hostname(be[1], dns, 2, "127.0.0.1", listener_port)))) {
            tinytest_set_test_failed_();
            do {
                printf("\n  %s %s:%d: ", "FAIL", "test/regress_dns_InstSlice.c", 371);
                printf("%s", "assert(!bufferevent_socket_connect_hostname(be[1], dns, AF_INET, \"127.0.0.1\", listener_port))");
            } while (0);
            do {
                goto end;
            } while (0);
        } else {
            do {
                if (tinytest_get_verbosity_() > 1)
                    do {
                        printf("\n  %s %s:%d: ", "  OK", "test/regress_dns_InstSlice.c", 371);
                        printf("%s", "assert(!bufferevent_socket_connect_hostname(be[1], dns, AF_INET, \"127.0.0.1\", listener_port))");
                    } while (0);
            } while (0);
        }
    } while (0);
    ;
    do {
        if (!((!bufferevent_socket_connect_hostname(be[2], dns, 2, "nobodaddy.example.com", listener_port)))) {
            tinytest_set_test_failed_();
            do {
                printf("\n  %s %s:%d: ", "FAIL", "test/regress_dns_InstSlice.c", 374);
                printf("%s", "assert(!bufferevent_socket_connect_hostname(be[2], dns, AF_INET, \"nobodaddy.example.com\", listener_port))");
            } while (0);
            do {
                goto end;
            } while (0);
        } else {
            do {
                if (tinytest_get_verbosity_() > 1)
                    do {
                        printf("\n  %s %s:%d: ", "  OK", "test/regress_dns_InstSlice.c", 374);
                        printf("%s", "assert(!bufferevent_socket_connect_hostname(be[2], dns, AF_INET, \"nobodaddy.example.com\", listener_port))");
                    } while (0);
            } while (0);
        }
    } while (0);
    ;
    ret = event_base_dispatch(data->base);
    {
        do {
            long val1_ = (long)(ret);
            long val2_ = (long)(0);
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
                    printf("\n  %s %s:%d: ", tt_status_ ? "\t OK" : "FAIL", "test/regress_dns.c", 1356);
                    printf("assert(%s): %ld vs %ld", "ret == 0", print1_, print2_);
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
    }
    do {
        long val1_ = (long)(be_outcome[0].what);
        long val2_ = (long)(32);
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
                printf("\n  %s %s:%d: ", tt_status_ ? "\t OK" : "FAIL", "test/regress_dns_InstSlice.c", 428);
                printf("assert(%s): %ld vs %ld", "be_outcome[0].what == BEV_EVENT_ERROR", print1_, print2_);
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
    do {
        long val1_ = (long)(be_outcome[0].dnserr);
        long val2_ = (long)(-2);
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
                printf("\n  %s %s:%d: ", tt_status_ ? "\t OK" : "FAIL", "test/regress_dns_InstSlice.c", 429);
                printf("assert(%s): %ld vs %ld", "be_outcome[0].dnserr == EVUTIL_EAI_NONAME", print1_, print2_);
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
    do {
        long val1_ = (long)(be_outcome[1].what);
        long val2_ = (long)(!emfile ? 128 : 32);
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
                printf("\n  %s %s:%d: ", tt_status_ ? "\t OK" : "FAIL", "test/regress_dns_InstSlice.c", 430);
                printf("assert(%s): %ld vs %ld", "be_outcome[1].what == !emfile ? BEV_EVENT_CONNECTED : BEV_EVENT_ERROR", print1_, print2_);
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
    do {
        long val1_ = (long)(be_outcome[1].dnserr);
        long val2_ = (long)(0);
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
                printf("\n  %s %s:%d: ", tt_status_ ? "\t OK" : "FAIL", "test/regress_dns_InstSlice.c", 431);
                printf("assert(%s): %ld vs %ld", "be_outcome[1].dnserr == 0", print1_, print2_);
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
    do {
        long val1_ = (long)(be_outcome[2].what);
        long val2_ = (long)(!emfile ? 128 : 32);
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
                printf("\n  %s %s:%d: ", tt_status_ ? "\t OK" : "FAIL", "test/regress_dns_InstSlice.c", 432);
                printf("assert(%s): %ld vs %ld", "be_outcome[2].what == !emfile ? BEV_EVENT_CONNECTED : BEV_EVENT_ERROR", print1_, print2_);
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
    do {
        long val1_ = (long)(be_outcome[2].dnserr);
        long val2_ = (long)(0);
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
                printf("\n  %s %s:%d: ", tt_status_ ? "\t OK" : "FAIL", "test/regress_dns_InstSlice.c", 433);
                printf("assert(%s): %ld vs %ld", "be_outcome[2].dnserr == 0", print1_, print2_);
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
    do {
        long val1_ = (long)(be_outcome[3].what);
        long val2_ = (long)(!emfile ? 128 : 32);
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
                printf("\n  %s %s:%d: ", tt_status_ ? "\t OK" : "FAIL", "test/regress_dns_InstSlice.c", 434);
                printf("assert(%s): %ld vs %ld", "be_outcome[3].what == !emfile ? BEV_EVENT_CONNECTED : BEV_EVENT_ERROR", print1_, print2_);
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
    if (!emfile) {
        do {
            long val1_ = (long)(be_outcome[3].dnserr);
            long val2_ = (long)(0);
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
                    printf("\n  %s %s:%d: ", tt_status_ ? "\t OK" : "FAIL", "test/regress_dns_InstSlice.c", 436);
                    printf("assert(%s): %ld vs %ld", "be_outcome[3].dnserr == 0", print1_, print2_);
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
    } else {
        do {
            long val1_ = (long)(be_outcome[3].dnserr);
            long val2_ = (long)(0);
            int tt_status_ = ((val1_ != val2_));
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
                    printf("\n  %s %s:%d: ", tt_status_ ? "\t OK" : "FAIL", "test/regress_dns_InstSlice.c", 438);
                    printf("assert(%s): %ld vs %ld", "be_outcome[3].dnserr != 0", print1_, print2_);
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
    }
    if (expect_err) {
        do {
            long val1_ = (long)(be_outcome[4].what);
            long val2_ = (long)(32);
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
                    printf("\n  %s %s:%d: ", tt_status_ ? "\t OK" : "FAIL", "test/regress_dns_InstSlice.c", 441);
                    printf("assert(%s): %ld vs %ld", "be_outcome[4].what == BEV_EVENT_ERROR", print1_, print2_);
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
        do {
            long val1_ = (long)(be_outcome[4].dnserr);
            long val2_ = (long)(expect_err);
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
                    printf("\n  %s %s:%d: ", tt_status_ ? "\t OK" : "FAIL", "test/regress_dns_InstSlice.c", 442);
                    printf("assert(%s): %ld vs %ld", "be_outcome[4].dnserr == expect_err", print1_, print2_);
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
    }
    if (emfile) {
        do {
            long val1_ = (long)(n_accept);
            long val2_ = (long)(0);
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
                    printf("\n  %s %s:%d: ", tt_status_ ? "\t OK" : "FAIL", "test/regress_dns_InstSlice.c", 446);
                    printf("assert(%s): %ld vs %ld", "n_accept == 0", print1_, print2_);
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
    } else {
        do {
            long val1_ = (long)(n_accept);
            long val2_ = (long)(3);
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
                    printf("\n  %s %s:%d: ", tt_status_ ? "\t OK" : "FAIL", "test/regress_dns_InstSlice.c", 448);
                    printf("assert(%s): %ld vs %ld", "n_accept == 3", print1_, print2_);
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
    }
    do {
        long val1_ = (long)(n_dns);
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
                printf("\n  %s %s:%d: ", tt_status_ ? "\t OK" : "FAIL", "test/regress_dns_InstSlice.c", 450);
                printf("assert(%s): %ld vs %ld", "n_dns == 2", print1_, print2_);
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
    ;
    ;
    for (i = 0; i < (sizeof (be) / sizeof (be[0])); ++i) {
        if (be[i]) {
        }
        ;
    }
}


