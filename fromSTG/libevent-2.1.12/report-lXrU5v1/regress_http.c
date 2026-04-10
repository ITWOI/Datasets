static int http_bind (struct evhttp *myhttp, uint16_t *pport, int mask){
    int port;
    struct evhttp_bound_socket *sock;
    int ipv6 = mask & 1;
    if (ipv6) {
        sock = evhttp_bind_socket_with_handle(myhttp, "::1", *pport);
    } else
        sock = evhttp_bind_socket_with_handle(myhttp, "127.0.0.1", *pport);
    if (sock == ((void *)0)) {
        if (ipv6) {
            return -1;
        } else {
            ;
        }
    }
    port = regress_get_socket_port(evhttp_bound_socket_get_fd(sock));
    if (port < 0)
        return -1;
    *pport = (uint16_t)port;
    return 0;
}


static struct evhttp * http_setup_gencb (uint16_t *pport, struct event_base *base, int mask, void (*cb)(struct evhttp_request *, void *), void *cbarg){
    struct evhttp *myhttp;
    myhttp = evhttp_new(base);
    if (http_bind(myhttp, pport, mask) < 0)
        return ((void *)0);
    if (mask & 2) {
        init_ssl();
        evhttp_set_bevcb(myhttp, https_bev, ((void *)0));
    }
    evhttp_set_gencb(myhttp, cb, cbarg);
    evhttp_set_cb(myhttp, "/test", http_basic_cb, myhttp);
    evhttp_set_cb(myhttp, "/test nonconformant", http_basic_cb, myhttp);
    evhttp_set_cb(myhttp, "/timeout", http_timeout_cb, myhttp);
    evhttp_set_cb(myhttp, "/large", http_large_cb, base);
    evhttp_set_cb(myhttp, "/chunked", http_chunked_cb, base);
    evhttp_set_cb(myhttp, "/streamed", http_chunked_cb, base);
    evhttp_set_cb(myhttp, "/postit", http_post_cb, base);
    evhttp_set_cb(myhttp, "/putit", http_put_cb, base);
    evhttp_set_cb(myhttp, "/deleteit", http_delete_cb, base);
    evhttp_set_cb(myhttp, "/delay", http_delay_cb, base);
    evhttp_set_cb(myhttp, "/largedelay", http_large_delay_cb, base);
    evhttp_set_cb(myhttp, "/badrequest", http_badreq_cb, base);
    evhttp_set_cb(myhttp, "/oncomplete", http_on_complete_cb, base);
    evhttp_set_cb(myhttp, "/", http_dispatcher_cb, base);
    return (myhttp);
}


static struct evhttp * http_setup (uint16_t *pport, struct event_base *base, int mask){
    return http_setup_gencb(pport, base, mask, ((void *)0), ((void *)0));
}


static void http_free_evcons (struct evhttp_connection **evcons){
    struct evhttp_connection *evcon, **orig = evcons;
    if (!evcons)
        return;
    while ((evcon = *evcons++))
        {
            evhttp_connection_free(evcon);
        }
    free(orig);
}


static struct evhttp_connection ** http_fill_backlog (struct event_base *base, int port){
    struct evhttp_connection **evcon = malloc(sizeof (*evcon) * (256 + 1));
    int i;
    for (i = 0; i < 256; ++i) {
        struct evhttp_request *req;
        evcon[i] = evhttp_connection_base_new(base, ((void *)0), "127.0.0.1", port);
        do {
            if (!((evcon[i]))) {
                tinytest_set_test_failed_();
                do {
                    printf("\n  %s %s:%d: ", "FAIL", "test/regress_http_InstSlice.c", 389);
                    printf("%s", "assert(evcon[i])");
                } while (0);
                do {
                    goto end;
                } while (0);
            } else {
                do {
                    if (tinytest_get_verbosity_() > 1)
                        do {
                            printf("\n  %s %s:%d: ", "  OK", "test/regress_http_InstSlice.c", 389);
                            printf("%s", "assert(evcon[i])");
                        } while (0);
                } while (0);
            }
        } while (0);
        ;
        ;
        evhttp_connection_set_timeout(evcon[i], 5);
        req = evhttp_request_new(http_request_never_call, ((void *)0));
        do {
            if (!((req))) {
                tinytest_set_test_failed_();
                do {
                    printf("\n  %s %s:%d: ", "FAIL", "test/regress_http_InstSlice.c", 394);
                    printf("%s", "assert(req)");
                } while (0);
                do {
                    goto end;
                } while (0);
            } else {
                do {
                    if (tinytest_get_verbosity_() > 1)
                        do {
                            printf("\n  %s %s:%d: ", "  OK", "test/regress_http_InstSlice.c", 394);
                            printf("%s", "assert(req)");
                        } while (0);
                } while (0);
            }
        } while (0);
        ;
        ;
        do {
            long val1_ = (long)(evhttp_make_request(evcon[i], req, EVHTTP_REQ_GET, "/delay"));
            long val2_ = (long)(-1);
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
                    printf("\n  %s %s:%d: ", tt_status_ ? "\t OK" : "FAIL", "test/regress_http_InstSlice.c", 396);
                    printf("assert(%s): %ld vs %ld", "evhttp_make_request(evcon[i], req, EVHTTP_REQ_GET, \"/delay\") != -1", print1_, print2_);
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
    evcon[i] = ((void *)0);
    return evcon;
  end:
    fprintf(stderr, "Couldn't fill the backlog");
    return ((void *)0);
}


static struct evhttp_request * http_cancel_test_bad_request_new (enum http_cancel_test_type type, struct event_base *base){
    if (!(type & NO_NS) && (type & SERVER_TIMEOUT))
        return evhttp_request_new(http_timed_out_request_done, base);
    else if ((type & INACTIVE_SERVER) || (type & NO_NS))
        return evhttp_request_new(http_failed_request_done, base);
    else
        return ((void *)0);
}


static void http_cancel_test (void *arg){
    struct basic_test_data *data = arg;
    uint16_t port = 0;
    struct evhttp_connection *evcon = ((void *)0);
    struct evhttp_request *req = ((void *)0);
    struct bufferevent *bufev = ((void *)0);
    struct timeval tv;
    struct evdns_base *dns_base = ((void *)0);
    uint16_t portnum = 0;
    char address[64];
    struct evhttp *inactive_http = ((void *)0);
    struct event_base *inactive_base = ((void *)0);
    struct evhttp_connection **evcons = ((void *)0);
    struct event_base *base_to_fill = data->base;
    enum http_cancel_test_type type = (enum http_cancel_test_type)data->setup_data;
    struct evhttp *http = http_setup(&port, data->base, 0);
    if (type & BY_HOST) {
        const char *timeout = (type & NS_TIMEOUT) ? "6" : "3";
        do {
            if (!((regress_dnsserver(data->base, &portnum, search_table)))) {
                tinytest_set_test_failed_();
                do {
                    printf("\n  %s %s:%d: ", "FAIL", "test/regress_http_InstSlice.c", 452);
                    printf("%s", "assert(regress_dnsserver(data->base, &portnum, search_table))");
                } while (0);
                do {
                    goto end;
                } while (0);
            } else {
                do {
                    if (tinytest_get_verbosity_() > 1)
                        do {
                            printf("\n  %s %s:%d: ", "  OK", "test/regress_http_InstSlice.c", 452);
                            printf("%s", "assert(regress_dnsserver(data->base, &portnum, search_table))");
                        } while (0);
                } while (0);
            }
        } while (0);
        ;
        ;
        dns_base = evdns_base_new(data->base, 0);
        do {
            if (!((dns_base))) {
                tinytest_set_test_failed_();
                do {
                    printf("\n  %s %s:%d: ", "FAIL", "test/regress_http_InstSlice.c", 456);
                    printf("%s", "assert(dns_base)");
                } while (0);
                do {
                    goto end;
                } while (0);
            } else {
                do {
                    if (tinytest_get_verbosity_() > 1)
                        do {
                            printf("\n  %s %s:%d: ", "  OK", "test/regress_http_InstSlice.c", 456);
                            printf("%s", "assert(dns_base)");
                        } while (0);
                } while (0);
            }
        } while (0);
        ;
        ;
        if (type & NO_NS)
            ++portnum;
        evutil_snprintf(address, sizeof (address), "127.0.0.1:%d", portnum);
        evdns_base_nameserver_ip_add(dns_base, address);
        evdns_base_set_option(dns_base, "timeout:", timeout);
        evdns_base_set_option(dns_base, "initial-probe-timeout:", timeout);
        evdns_base_set_option(dns_base, "attempts:", "1");
    }
    exit_base = data->base;
    test_ok = 0;
    if (type & INACTIVE_SERVER) {
        port = 0;
        inactive_base = event_base_new();
        inactive_http = http_setup(&port, inactive_base, 0);
        base_to_fill = inactive_base;
    }
    if (type & SERVER_TIMEOUT)
        evcons = http_fill_backlog(base_to_fill, port);
    evcon = evhttp_connection_base_new(data->base, dns_base, type & BY_HOST ? "localhost" : "127.0.0.1", port);
    if (type & INACTIVE_SERVER)
        evhttp_connection_set_timeout(evcon, 5);
    do {
        if (!((evcon))) {
            tinytest_set_test_failed_();
            do {
                printf("\n  %s %s:%d: ", "FAIL", "test/regress_http_InstSlice.c", 489);
                printf("%s", "assert(evcon)");
            } while (0);
            do {
                goto end;
            } while (0);
        } else {
            do {
                if (tinytest_get_verbosity_() > 1)
                    do {
                        printf("\n  %s %s:%d: ", "  OK", "test/regress_http_InstSlice.c", 489);
                        printf("%s", "assert(evcon)");
                    } while (0);
            } while (0);
        }
    } while (0);
    ;
    ;
    bufev = evhttp_connection_get_bufferevent(evcon);
    if (type & SERVER_TIMEOUT)
        evbuffer_add_cb(bufferevent_get_output(bufev), http_no_write, ((void *)0));
    req = evhttp_request_new(http_request_never_call, ((void *)0));
    evhttp_request_set_error_cb(req, http_request_error_cb_with_cancel);
    evhttp_add_header(evhttp_request_get_output_headers(req), "Host", "somehost");
    do {
        long val1_ = (long)(evhttp_make_request(evcon, req, EVHTTP_REQ_GET, "/delay"));
        long val2_ = (long)(-1);
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
                printf("\n  %s %s:%d: ", tt_status_ ? "\t OK" : "FAIL", "test/regress_http_InstSlice.c", 511);
                printf("assert(%s): %ld vs %ld", "evhttp_make_request(evcon, req, EVHTTP_REQ_GET, \"/delay\") != -1", print1_, print2_);
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
    ((&tv)->tv_sec = (&tv)->tv_usec = 0);
    tv.tv_sec = 0;
    tv.tv_usec = 100 * 1000;
    event_base_once(data->base, -1, 1, http_do_cancel, req, &tv);
    event_base_dispatch(data->base);
    if (type & NO_NS || type & INACTIVE_SERVER)
        do {
            long val1_ = (long)(test_ok);
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
                    printf("\n  %s %s:%d: ", tt_status_ ? "\t OK" : "FAIL", "test/regress_http_InstSlice.c", 522);
                    printf("assert(%s): %ld vs %ld", "test_ok == 2", print1_, print2_);
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
    else
        do {
            long val1_ = (long)(test_ok);
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
                    printf("\n  %s %s:%d: ", tt_status_ ? "\t OK" : "FAIL", "test/regress_http_InstSlice.c", 524);
                    printf("assert(%s): %ld vs %ld", "test_ok == 3", print1_, print2_);
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
    test_ok = 0;
    http_free_evcons(evcons);
    if (type & SERVER_TIMEOUT)
        evcons = http_fill_backlog(base_to_fill, port);
    req = http_cancel_test_bad_request_new(type, data->base);
    if (!req)
        req = evhttp_request_new(http_request_done, (void *)BASIC_REQUEST_BODY);
    evhttp_add_header(evhttp_request_get_output_headers(req), "Host", "somehost");
    do {
        long val1_ = (long)(evhttp_make_request(evcon, req, EVHTTP_REQ_GET, "/test"));
        long val2_ = (long)(-1);
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
                printf("\n  %s %s:%d: ", tt_status_ ? "\t OK" : "FAIL", "test/regress_http_InstSlice.c", 542);
                printf("assert(%s): %ld vs %ld", "evhttp_make_request(evcon, req, EVHTTP_REQ_GET, \"/test\") != -1", print1_, print2_);
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
    event_base_dispatch(data->base);
    test_ok = 0;
    http_free_evcons(evcons);
    if (type & SERVER_TIMEOUT)
        evcons = http_fill_backlog(base_to_fill, port);
    req = http_cancel_test_bad_request_new(type, data->base);
    if (!req)
        req = evhttp_request_new(http_request_empty_done, data->base);
    evhttp_add_header(evhttp_request_get_output_headers(req), "Empty", "itis");
    do {
        long val1_ = (long)(evhttp_make_request(evcon, req, EVHTTP_REQ_GET, "/test"));
        long val2_ = (long)(-1);
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
                printf("\n  %s %s:%d: ", tt_status_ ? "\t OK" : "FAIL", "test/regress_http_InstSlice.c", 562);
                printf("assert(%s): %ld vs %ld", "evhttp_make_request(evcon, req, EVHTTP_REQ_GET, \"/test\") != -1", print1_, print2_);
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
    event_base_dispatch(data->base);
  end:
    http_free_evcons(evcons);
    if (bufev) {
    }
    ;
    ;
    ;
    ;
    ;
    ;
    ;
}


