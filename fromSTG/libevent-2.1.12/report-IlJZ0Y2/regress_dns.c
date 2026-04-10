static void getaddrinfo_race_gotresolve_test (void *arg){
    struct race_param rp;
    struct evdns_server_port *dns_port = ((void *)0);
    uint16_t portnum = 0;
    char buf[64];
    int i;
    int n_reqs = 16384;
    int n_threads = sysconf(_SC_NPROCESSORS_ONLN) + 1;
    pthread_t thread[n_threads];
    struct timeval tv;
    ;
    ;
    rp.base = event_base_new();
    do {
        if (!((rp.base))) {
            tinytest_set_test_failed_();
            do {
                printf("\n  %s %s:%d: ", "FAIL", "test/regress_dns_InstSlice.c", 465);
                printf("%s", "assert(rp.base)");
            } while (0);
            do {
                goto end;
            } while (0);
        } else {
            do {
                if (tinytest_get_verbosity_() > 1)
                    do {
                        printf("\n  %s %s:%d: ", "  OK", "test/regress_dns_InstSlice.c", 465);
                        printf("%s", "assert(rp.base)");
                    } while (0);
            } while (0);
        }
    } while (0);
    ;
    ;
    if (evthread_make_base_notifiable(rp.base) < 0)
        do {
            tinytest_set_test_failed_();
            do {
                printf("\n  %s %s:%d: ", "FAIL", "test/regress_dns_InstSlice.c", 468);
                printf("%s", "Couldn't make base notifiable!");
            } while (0);
            do {
                goto end;
            } while (0);
        } while (0);
    dns_port = regress_get_dnsserver(rp.base, &portnum, ((void *)0), regress_dns_server_cb, reissue_table);
    do {
        if (!((dns_port))) {
            tinytest_set_test_failed_();
            do {
                printf("\n  %s %s:%d: ", "FAIL", "test/regress_dns_InstSlice.c", 471);
                printf("%s", "assert(dns_port)");
            } while (0);
            do {
                goto end;
            } while (0);
        } else {
            do {
                if (tinytest_get_verbosity_() > 1)
                    do {
                        printf("\n  %s %s:%d: ", "  OK", "test/regress_dns_InstSlice.c", 471);
                        printf("%s", "assert(dns_port)");
                    } while (0);
            } while (0);
        }
    } while (0);
    ;
    ;
    ;
    rp.dns = evdns_base_new(rp.base, 0);
    do {
        if (!((!evdns_base_nameserver_ip_add(rp.dns, buf)))) {
            tinytest_set_test_failed_();
            do {
                printf("\n  %s %s:%d: ", "FAIL", "test/regress_dns_InstSlice.c", 477);
                printf("%s", "assert(!evdns_base_nameserver_ip_add(rp.dns, buf))");
            } while (0);
            do {
                goto end;
            } while (0);
        } else {
            do {
                if (tinytest_get_verbosity_() > 1)
                    do {
                        printf("\n  %s %s:%d: ", "  OK", "test/regress_dns_InstSlice.c", 477);
                        printf("%s", "assert(!evdns_base_nameserver_ip_add(rp.dns, buf))");
                    } while (0);
            } while (0);
        }
    } while (0);
    ;
    ;
    ;
    ((rp.lock) = evthread_lock_fns_.alloc ? evthread_lock_fns_.alloc(0) : ((void *)0));
    do {
        (rp.reqs_cmpl_cond) = evthread_cond_fns_.alloc_condition ? evthread_cond_fns_.alloc_condition(0) : ((void *)0);
    } while (0);
    do {
        (rp.bw_threads_exited_cond) = evthread_cond_fns_.alloc_condition ? evthread_cond_fns_.alloc_condition(0) : ((void *)0);
    } while (0);
    do {
        if (!((rp.lock))) {
            tinytest_set_test_failed_();
            do {
                printf("\n  %s %s:%d: ", "FAIL", "test/regress_dns_InstSlice.c", 485);
                printf("%s", "assert(rp.lock)");
            } while (0);
            do {
                goto end;
            } while (0);
        } else {
            do {
                if (tinytest_get_verbosity_() > 1)
                    do {
                        printf("\n  %s %s:%d: ", "  OK", "test/regress_dns_InstSlice.c", 485);
                        printf("%s", "assert(rp.lock)");
                    } while (0);
            } while (0);
        }
    } while (0);
    ;
    ;
    do {
        if (!((rp.reqs_cmpl_cond))) {
            tinytest_set_test_failed_();
            do {
                printf("\n  %s %s:%d: ", "FAIL", "test/regress_dns_InstSlice.c", 487);
                printf("%s", "assert(rp.reqs_cmpl_cond)");
            } while (0);
            do {
                goto end;
            } while (0);
        } else {
            do {
                if (tinytest_get_verbosity_() > 1)
                    do {
                        printf("\n  %s %s:%d: ", "  OK", "test/regress_dns_InstSlice.c", 487);
                        printf("%s", "assert(rp.reqs_cmpl_cond)");
                    } while (0);
            } while (0);
        }
    } while (0);
    ;
    ;
    do {
        if (!((rp.bw_threads_exited_cond))) {
            tinytest_set_test_failed_();
            do {
                printf("\n  %s %s:%d: ", "FAIL", "test/regress_dns_InstSlice.c", 489);
                printf("%s", "assert(rp.bw_threads_exited_cond)");
            } while (0);
            do {
                goto end;
            } while (0);
        } else {
            do {
                if (tinytest_get_verbosity_() > 1)
                    do {
                        printf("\n  %s %s:%d: ", "  OK", "test/regress_dns_InstSlice.c", 489);
                        printf("%s", "assert(rp.bw_threads_exited_cond)");
                    } while (0);
            } while (0);
        }
    } while (0);
    ;
    ;
    rp.bw_threads = 0;
    rp.stopping = 0;
    ;
    for (i = 1; i < n_threads; i++) {
        rp.bw_threads++;
        ;
    }
    ;
    rp.locked = 1;
    for (i = 0; i < n_reqs; ++i) {
        do {
            if (!((evdns_getaddrinfo(rp.dns, "foof.example.com", "80", ((void *)0), race_gai_cb, &rp)))) {
                tinytest_set_test_failed_();
                do {
                    printf("\n  %s %s:%d: ", "FAIL", "test/regress_dns_InstSlice.c", 506);
                    printf("%s", "assert(evdns_getaddrinfo(rp.dns, \"foof.example.com\", \"80\", NULL, race_gai_cb, &rp))");
                } while (0);
                do {
                    goto end;
                } while (0);
            } else {
                do {
                    if (tinytest_get_verbosity_() > 1)
                        do {
                            printf("\n  %s %s:%d: ", "  OK", "test/regress_dns_InstSlice.c", 506);
                            printf("%s", "assert(evdns_getaddrinfo(rp.dns, \"foof.example.com\", \"80\", NULL, race_gai_cb, &rp))");
                        } while (0);
                } while (0);
            }
        } while (0);
        ;
        ;
        if (i % 100 == 0) {
            tv.tv_sec = 0;
            tv.tv_usec = 10000;
            ;
        }
    }
    ;
    ;
    ;
    ;
    tv.tv_sec = 1;
    tv.tv_usec = 0;
    ;
    do {
        if (!((((rp.bw_threads_exited_cond) ? evthread_cond_fns_.wait_condition((rp.bw_threads_exited_cond), (rp.lock), (&tv)) : 0) == 0))) {
            tinytest_set_test_failed_();
            do {
                printf("\n  %s %s:%d: ", "FAIL", "test/regress_dns_InstSlice.c", 527);
                printf("%s", "assert(EVTHREAD_COND_WAIT_TIMED(rp.bw_threads_exited_cond, rp.lock, &tv) == 0)");
            } while (0);
            do {
                goto end;
            } while (0);
        } else {
            do {
                if (tinytest_get_verbosity_() > 1)
                    do {
                        printf("\n  %s %s:%d: ", "  OK", "test/regress_dns_InstSlice.c", 527);
                        printf("%s", "assert(EVTHREAD_COND_WAIT_TIMED(rp.bw_threads_exited_cond, rp.lock, &tv) == 0)");
                    } while (0);
            } while (0);
        }
    } while (0);
    ;
    ;
    ;
    rp.locked = 0;
    ;
    ;
  end:
    if (rp.locked)
        do {
            if (rp.lock)
                evthread_lock_fns_.unlock(0, rp.lock);
        } while (0);
    ;
    ;
    ;
    ;
    ;
    ;
}


