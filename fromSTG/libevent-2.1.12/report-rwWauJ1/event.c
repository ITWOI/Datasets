static inline unsigned int hash_debug_entry (const struct event_debug_entry *e){
    unsigned int u = (unsigned int)((uintptr_t)e->ptr);
    return (u >> 6);
}


static inline int eq_debug_entry (const struct event_debug_entry *a, const struct event_debug_entry *b){
    return a->ptr == b->ptr;
}


static void event_debug_note_teardown_ (const struct event *ev){
    struct event_debug_entry *dent, find;
    if (!event_debug_mode_on_)
        goto out;
    ;
    find.ptr = ev;
    do {
        if (event_debug_map_lock_)
            evthread_lock_fns_.lock(0, event_debug_map_lock_);
    } while (0);
    dent = event_debug_map_HT_REMOVE((&global_debug_map), (&find));
    if (dent)
        event_mm_free_(dent);
    do {
        if (event_debug_map_lock_)
            evthread_lock_fns_.unlock(0, event_debug_map_lock_);
    } while (0);
  out:
    event_debug_mode_too_late = 1;
}


static void event_debug_note_add_ (const struct event *ev){
    struct event_debug_entry *dent, find;
    if (!event_debug_mode_on_)
        goto out;
    ;
    find.ptr = ev;
    do {
        if (event_debug_map_lock_)
            evthread_lock_fns_.lock(0, event_debug_map_lock_);
    } while (0);
    dent = event_debug_map_HT_FIND((&global_debug_map), (&find));
    if (dent) {
        dent->added = 1;
    } else {
        ;
    }
    do {
        if (event_debug_map_lock_)
            evthread_lock_fns_.unlock(0, event_debug_map_lock_);
    } while (0);
  out:
    event_debug_mode_too_late = 1;
}


static void event_debug_note_del_ (const struct event *ev){
    struct event_debug_entry *dent, find;
    if (!event_debug_mode_on_)
        goto out;
    ;
    find.ptr = ev;
    do {
        if (event_debug_map_lock_)
            evthread_lock_fns_.lock(0, event_debug_map_lock_);
    } while (0);
    dent = event_debug_map_HT_FIND((&global_debug_map), (&find));
    if (dent) {
        dent->added = 0;
    } else {
        ;
    }
    do {
        if (event_debug_map_lock_)
            evthread_lock_fns_.unlock(0, event_debug_map_lock_);
    } while (0);
  out:
    event_debug_mode_too_late = 1;
}


static void event_debug_assert_is_setup_ (const struct event *ev){
    struct event_debug_entry *dent, find;
    if (!event_debug_mode_on_)
        return;
    find.ptr = ev;
    do {
        if (event_debug_map_lock_)
            evthread_lock_fns_.lock(0, event_debug_map_lock_);
    } while (0);
    dent = event_debug_map_HT_FIND((&global_debug_map), (&find));
    if (!dent) {
        ;
    }
    do {
        if (event_debug_map_lock_)
            evthread_lock_fns_.unlock(0, event_debug_map_lock_);
    } while (0);
}


static int gettime (struct event_base *base, struct timeval *tp){
    do {
        if (((base)->th_base_lock) && evthread_lock_debugging_enabled_) {
            do {
                if (__builtin_expect(!!(!(evthread_is_debug_lock_held_((base)->th_base_lock))), 0)) {
                    event_errx(((int)3735936685U), "%s:%d: Assertion %s failed in %s", "event_InstSlice.c", 347, "evthread_is_debug_lock_held_((base)->th_base_lock)", __func__);
                    (void)fprintf(stderr, "%s:%d: Assertion %s failed in %s", "event_InstSlice.c", 347, "evthread_is_debug_lock_held_((base)->th_base_lock)", __func__);
                    abort();
                }
            } while (0);
        }
    } while (0);
    if (base->tv_cache.tv_sec) {
        *tp = base->tv_cache;
        return (0);
    }
    if (evutil_gettime_monotonic_(&base->monotonic_timer, tp) == -1) {
        return -1;
    }
    if (base->last_updated_clock_diff + 5 < tp->tv_sec) {
        struct timeval tv;
        gettimeofday((&tv), (((void *)0)));
        do {
            ((&base->tv_clock_diff))->tv_sec = ((&tv))->tv_sec - ((tp))->tv_sec;
            ((&base->tv_clock_diff))->tv_usec = ((&tv))->tv_usec - ((tp))->tv_usec;
            if (((&base->tv_clock_diff))->tv_usec < 0) {
                --((&base->tv_clock_diff))->tv_sec;
                ((&base->tv_clock_diff))->tv_usec += 1000000;
            }
        } while (0);
        base->last_updated_clock_diff = tp->tv_sec;
    }
    return 0;
}


static inline void update_time_cache (struct event_base *base){
    base->tv_cache.tv_sec = 0;
    if (!(base->flags & EVENT_BASE_FLAG_NO_CACHE_TIME))
        gettime(base, &base->tv_cache);
}


static inline struct event * event_callback_to_event (struct event_callback *evcb){
    do {
        if (__builtin_expect(!!(!((evcb->evcb_flags & 128))), 0)) {
            event_errx(((int)3735936685U), "%s:%d: Assertion %s failed in %s", "event_InstSlice.c", 393, "(evcb->evcb_flags & EVLIST_INIT)", __func__);
            (void)fprintf(stderr, "%s:%d: Assertion %s failed in %s", "event_InstSlice.c", 393, "(evcb->evcb_flags & EVLIST_INIT)", __func__);
            abort();
        }
    } while (0);
    return ((struct event *)(((char *)(evcb)) - __builtin_offsetof(struct event, ev_evcallback)));
}


static inline struct event_callback * event_to_event_callback (struct event *ev){
    return &ev->ev_evcallback;
}


static int event_haveevents (struct event_base *base){
    return (base->virtual_event_count > 0 || base->event_count > 0);
}


static inline void event_signal_closure (struct event_base *base, struct event *ev){
    short ncalls;
    int should_break;
    ncalls = ev->ev_.ev_signal.ev_ncalls;
    if (ncalls != 0)
        ev->ev_.ev_signal.ev_pncalls = &ncalls;
    do {
        do {
            if ((base)->th_base_lock)
                evthread_lock_fns_.unlock(0, (base)->th_base_lock);
        } while (0);
    } while (0);
    while (ncalls)
        {
            ncalls--;
            ev->ev_.ev_signal.ev_ncalls = ncalls;
            if (ncalls == 0)
                ev->ev_.ev_signal.ev_pncalls = ((void *)0);
            (*ev->ev_evcallback.evcb_cb_union.evcb_callback)(ev->ev_fd, ev->ev_res, ev->ev_evcallback.evcb_arg);
            do {
                do {
                    if ((base)->th_base_lock)
                        evthread_lock_fns_.lock(0, (base)->th_base_lock);
                } while (0);
            } while (0);
            should_break = base->event_break;
            do {
                do {
                    if ((base)->th_base_lock)
                        evthread_lock_fns_.unlock(0, (base)->th_base_lock);
                } while (0);
            } while (0);
            if (should_break) {
                if (ncalls != 0)
                    ev->ev_.ev_signal.ev_pncalls = ((void *)0);
                return;
            }
        }
}


static inline int is_common_timeout (const struct timeval *tv, const struct event_base *base){
    int idx;
    if ((tv->tv_usec & 4026531840U) != 1342177280)
        return 0;
    idx = (((tv)->tv_usec & 267386880) >> 20);
    return idx < base->n_common_timeouts;
}


static inline int is_same_common_timeout (const struct timeval *tv1, const struct timeval *tv2){
    return (tv1->tv_usec & ~1048575) == (tv2->tv_usec & ~1048575);
}


static inline struct common_timeout_list * get_common_timeout_list (struct event_base *base, const struct timeval *tv){
    return base->common_timeout_queues[(((tv)->tv_usec & 267386880) >> 20)];
}


static void common_timeout_schedule (struct common_timeout_list *ctl, const struct timeval *now, struct event *head){
    struct timeval timeout = head->ev_timeout;
    timeout.tv_usec &= 1048575;
    event_add_nolock_(&ctl->timeout_event, &timeout, 1);
}


static inline void event_persist_closure (struct event_base *base, struct event *ev){
    void (*evcb_callback)(int, short, void *);
    int evcb_fd;
    short evcb_res;
    void *evcb_arg;
    if (ev->ev_.ev_io.ev_timeout.tv_sec || ev->ev_.ev_io.ev_timeout.tv_usec) {
        struct timeval run_at, relative_to, delay, now;
        uint32_t usec_mask = 0;
        do {
            if (__builtin_expect(!!(!(is_same_common_timeout(&ev->ev_timeout, &ev->ev_.ev_io.ev_timeout))), 0)) {
                event_errx(((int)3735936685U), "%s:%d: Assertion %s failed in %s", "event_InstSlice.c", 700, "is_same_common_timeout(&ev->ev_timeout, &ev->ev_io_timeout)", __func__);
                (void)fprintf(stderr, "%s:%d: Assertion %s failed in %s", "event_InstSlice.c", 700, "is_same_common_timeout(&ev->ev_timeout, &ev->ev_io_timeout)", __func__);
                abort();
            }
        } while (0);
        gettime(base, &now);
        if (is_common_timeout(&ev->ev_timeout, base)) {
            delay = ev->ev_.ev_io.ev_timeout;
            usec_mask = delay.tv_usec & ~1048575;
            delay.tv_usec &= 1048575;
            if (ev->ev_res & 1) {
                relative_to = ev->ev_timeout;
                relative_to.tv_usec &= 1048575;
            } else {
                relative_to = now;
            }
        } else {
            delay = ev->ev_.ev_io.ev_timeout;
            if (ev->ev_res & 1) {
                relative_to = ev->ev_timeout;
            } else {
                relative_to = now;
            }
        }
        do {
            ((&run_at))->tv_sec = ((&relative_to))->tv_sec + ((&delay))->tv_sec;
            ((&run_at))->tv_usec = ((&relative_to))->tv_usec + ((&delay))->tv_usec;
            if (((&run_at))->tv_usec >= 1000000) {
                ++((&run_at))->tv_sec;
                ((&run_at))->tv_usec -= 1000000;
            }
        } while (0);
        if ((((&run_at)->tv_sec == (&now)->tv_sec) ? ((&run_at)->tv_usec < (&now)->tv_usec) : ((&run_at)->tv_sec < (&now)->tv_sec))) {
            do {
                ((&run_at))->tv_sec = ((&now))->tv_sec + ((&delay))->tv_sec;
                ((&run_at))->tv_usec = ((&now))->tv_usec + ((&delay))->tv_usec;
                if (((&run_at))->tv_usec >= 1000000) {
                    ++((&run_at))->tv_sec;
                    ((&run_at))->tv_usec -= 1000000;
                }
            } while (0);
        }
        run_at.tv_usec |= usec_mask;
        event_add_nolock_(ev, &run_at, 1);
    }
    evcb_callback = ev->ev_evcallback.evcb_cb_union.evcb_callback;
    evcb_fd = ev->ev_fd;
    evcb_res = ev->ev_res;
    evcb_arg = ev->ev_evcallback.evcb_arg;
    do {
        do {
            if ((base)->th_base_lock)
                evthread_lock_fns_.unlock(0, (base)->th_base_lock);
        } while (0);
    } while (0);
    (evcb_callback)(evcb_fd, evcb_res, evcb_arg);
}


static int event_process_active_single_queue (struct event_base *base, struct evcallback_list *activeq, int max_to_process, const struct timeval *endtime){
    struct event_callback *evcb;
    int count = 0;
    do {
        if (__builtin_expect(!!(!(activeq != ((void *)0))), 0)) {
            event_errx(((int)3735936685U), "%s:%d: Assertion %s failed in %s", "event_InstSlice.c", 761, "activeq != NULL", __func__);
            (void)fprintf(stderr, "%s:%d: Assertion %s failed in %s", "event_InstSlice.c", 761, "activeq != NULL", __func__);
            abort();
        }
    } while (0);
    for (evcb = ((activeq)->tqh_first); evcb; evcb = ((activeq)->tqh_first)) {
        struct event *ev = ((void *)0);
        if (evcb->evcb_flags & 128) {
            ev = event_callback_to_event(evcb);
            if (ev->ev_events & 16 || ev->ev_evcallback.evcb_flags & 64) {
                event_queue_remove_active(base, evcb);
            } else
                event_del_nolock_(ev, 0);
            do {
                if ((event_debug_logging_mask_)) {
                    event_debugx_("event_process_active: event: %p, %s%s%scall %p", ev, ev->ev_res & 2 ? "EV_READ " : " ", ev->ev_res & 4 ? "EV_WRITE " : " ", ev->ev_res & 128 ? "EV_CLOSED " : " ", ev->ev_evcallback.evcb_cb_union.evcb_callback);
                }
            } while (0);
        } else {
            event_queue_remove_active(base, evcb);
            do {
                if ((event_debug_logging_mask_)) {
                    event_debugx_("event_process_active: event_callback %p, closure %d, call %p", evcb, evcb->evcb_closure, evcb->evcb_cb_union.evcb_callback);
                }
            } while (0);
        }
        if (!(evcb->evcb_flags & 16))
            ++count;
        base->current_event = evcb;
        base->current_event_waiters = 0;
        switch (evcb->evcb_closure) {
          case 1:
            do {
                if (__builtin_expect(!!(!(ev != ((void *)0))), 0)) {
                    event_errx(((int)3735936685U), "%s:%d: Assertion %s failed in %s", "event_InstSlice.c", 797, "ev != NULL", __func__);
                    (void)fprintf(stderr, "%s:%d: Assertion %s failed in %s", "event_InstSlice.c", 797, "ev != NULL", __func__);
                    abort();
                }
            } while (0);
            event_signal_closure(base, ev);
            break;
          case 2:
            do {
                if (__builtin_expect(!!(!(ev != ((void *)0))), 0)) {
                    event_errx(((int)3735936685U), "%s:%d: Assertion %s failed in %s", "event_InstSlice.c", 801, "ev != NULL", __func__);
                    (void)fprintf(stderr, "%s:%d: Assertion %s failed in %s", "event_InstSlice.c", 801, "ev != NULL", __func__);
                    abort();
                }
            } while (0);
            event_persist_closure(base, ev);
            break;
          case 0:
            {
                void (*evcb_callback)(int, short, void *);
                short res;
                do {
                    if (__builtin_expect(!!(!(ev != ((void *)0))), 0)) {
                        event_errx(((int)3735936685U), "%s:%d: Assertion %s failed in %s", "event_InstSlice.c", 807, "ev != NULL", __func__);
                        (void)fprintf(stderr, "%s:%d: Assertion %s failed in %s", "event_InstSlice.c", 807, "ev != NULL", __func__);
                        abort();
                    }
                } while (0);
                evcb_callback = *ev->ev_evcallback.evcb_cb_union.evcb_callback;
                res = ev->ev_res;
                do {
                    do {
                        if ((base)->th_base_lock)
                            evthread_lock_fns_.unlock(0, (base)->th_base_lock);
                    } while (0);
                } while (0);
                evcb_callback(ev->ev_fd, res, ev->ev_evcallback.evcb_arg);
            }
            break;
            ;
          case 3:
            {
                void (*evcb_selfcb)(struct event_callback *, void *) = evcb->evcb_cb_union.evcb_selfcb;
                do {
                    do {
                        if ((base)->th_base_lock)
                            evthread_lock_fns_.unlock(0, (base)->th_base_lock);
                    } while (0);
                } while (0);
                evcb_selfcb(evcb, evcb->evcb_arg);
            }
            break;
            ;
          case 5:
          case 6:
            {
                void (*evcb_evfinalize)(struct event *, void *);
                int evcb_closure = evcb->evcb_closure;
                do {
                    if (__builtin_expect(!!(!(ev != ((void *)0))), 0)) {
                        event_errx(((int)3735936685U), "%s:%d: Assertion %s failed in %s", "event_InstSlice.c", 826, "ev != NULL", __func__);
                        (void)fprintf(stderr, "%s:%d: Assertion %s failed in %s", "event_InstSlice.c", 826, "ev != NULL", __func__);
                        abort();
                    }
                } while (0);
                base->current_event = ((void *)0);
                evcb_evfinalize = ev->ev_evcallback.evcb_cb_union.evcb_evfinalize;
                do {
                    if (__builtin_expect(!!(!((evcb->evcb_flags & 64))), 0)) {
                        event_errx(((int)3735936685U), "%s:%d: Assertion %s failed in %s", "event_InstSlice.c", 829, "(evcb->evcb_flags & EVLIST_FINALIZING)", __func__);
                        (void)fprintf(stderr, "%s:%d: Assertion %s failed in %s", "event_InstSlice.c", 829, "(evcb->evcb_flags & EVLIST_FINALIZING)", __func__);
                        abort();
                    }
                } while (0);
                do {
                    do {
                        if ((base)->th_base_lock)
                            evthread_lock_fns_.unlock(0, (base)->th_base_lock);
                    } while (0);
                } while (0);
                event_debug_note_teardown_(ev);
                evcb_evfinalize(ev, ev->ev_evcallback.evcb_arg);
                if (evcb_closure == 6)
                    event_mm_free_(ev);
            }
            break;
            ;
          case 4:
            {
                void (*evcb_cbfinalize)(struct event_callback *, void *) = evcb->evcb_cb_union.evcb_cbfinalize;
                base->current_event = ((void *)0);
                do {
                    if (__builtin_expect(!!(!((evcb->evcb_flags & 64))), 0)) {
                        event_errx(((int)3735936685U), "%s:%d: Assertion %s failed in %s", "event_InstSlice.c", 841, "(evcb->evcb_flags & EVLIST_FINALIZING)", __func__);
                        (void)fprintf(stderr, "%s:%d: Assertion %s failed in %s", "event_InstSlice.c", 841, "(evcb->evcb_flags & EVLIST_FINALIZING)", __func__);
                        abort();
                    }
                } while (0);
                do {
                    do {
                        if ((base)->th_base_lock)
                            evthread_lock_fns_.unlock(0, (base)->th_base_lock);
                    } while (0);
                } while (0);
                evcb_cbfinalize(evcb, evcb->evcb_arg);
            }
            break;
            ;
            ;
        }
        do {
            do {
                if ((base)->th_base_lock)
                    evthread_lock_fns_.lock(0, (base)->th_base_lock);
            } while (0);
        } while (0);
        base->current_event = ((void *)0);
        if (base->current_event_waiters) {
            base->current_event_waiters = 0;
            ((base->current_event_cond) ? evthread_cond_fns_.signal_condition((base->current_event_cond), 1) : 0);
        }
        if (base->event_break)
            return -1;
        if (count >= max_to_process)
            return count;
        if (count && endtime) {
            struct timeval now;
            update_time_cache(base);
            gettime(base, &now);
            if ((((&now)->tv_sec == (endtime)->tv_sec) ? ((&now)->tv_usec >= (endtime)->tv_usec) : ((&now)->tv_sec >= (endtime)->tv_sec)))
                return count;
        }
        if (base->event_continue)
            break;
    }
    return count;
}


static int evthread_notify_base (struct event_base *base){
    do {
        if (((base)->th_base_lock) && evthread_lock_debugging_enabled_) {
            do {
                if (__builtin_expect(!!(!(evthread_is_debug_lock_held_((base)->th_base_lock))), 0)) {
                    event_errx(((int)3735936685U), "%s:%d: Assertion %s failed in %s", "event_InstSlice.c", 1111, "evthread_is_debug_lock_held_((base)->th_base_lock)", __func__);
                    (void)fprintf(stderr, "%s:%d: Assertion %s failed in %s", "event_InstSlice.c", 1111, "evthread_is_debug_lock_held_((base)->th_base_lock)", __func__);
                    abort();
                }
            } while (0);
        }
    } while (0);
    if (!base->th_notify_fn)
        return -1;
    if (base->is_notify_pending)
        return 0;
    base->is_notify_pending = 1;
    return base->th_notify_fn(base);
}


extern int event_add_nolock_ (struct event *ev, const struct timeval *tv, int tv_is_absolute){
    struct event_base *base = ev->ev_base;
    int res = 0;
    int notify = 0;
    do {
        if (((base)->th_base_lock) && evthread_lock_debugging_enabled_) {
            do {
                if (__builtin_expect(!!(!(evthread_is_debug_lock_held_((base)->th_base_lock))), 0)) {
                    event_errx(((int)3735936685U), "%s:%d: Assertion %s failed in %s", "event_InstSlice.c", 1142, "evthread_is_debug_lock_held_((base)->th_base_lock)", __func__);
                    (void)fprintf(stderr, "%s:%d: Assertion %s failed in %s", "event_InstSlice.c", 1142, "evthread_is_debug_lock_held_((base)->th_base_lock)", __func__);
                    abort();
                }
            } while (0);
        }
    } while (0);
    event_debug_assert_is_setup_(ev);
    do {
        if ((event_debug_logging_mask_)) {
            event_debugx_("event_add: event: %p (fd %d), %s%s%s%scall %p", ev, (ev->ev_fd), ev->ev_events & 2 ? "EV_READ " : " ", ev->ev_events & 4 ? "EV_WRITE " : " ", ev->ev_events & 128 ? "EV_CLOSED " : " ", tv ? "EV_TIMEOUT " : " ", ev->ev_evcallback.evcb_cb_union.evcb_callback);
        }
    } while (0);
    do {
        if (__builtin_expect(!!(!(!(ev->ev_evcallback.evcb_flags & ~255))), 0)) {
            event_errx(((int)3735936685U), "%s:%d: Assertion %s failed in %s", "event_InstSlice.c", 1155, "!(ev->ev_flags & ~EVLIST_ALL)", __func__);
            (void)fprintf(stderr, "%s:%d: Assertion %s failed in %s", "event_InstSlice.c", 1155, "!(ev->ev_flags & ~EVLIST_ALL)", __func__);
            abort();
        }
    } while (0);
    if (ev->ev_evcallback.evcb_flags & 64) {
        return (-1);
    }
    if (tv != ((void *)0) && !(ev->ev_evcallback.evcb_flags & 1)) {
        if (min_heap_reserve_(&base->timeheap, 1 + min_heap_size_(&base->timeheap)) == -1)
            return (-1);
    }
    if (base->current_event == event_to_event_callback(ev) && (ev->ev_events & 8) && !(evthread_id_fn_ == ((void *)0) || (base)->th_owner_id == evthread_id_fn_())) {
        ++base->current_event_waiters;
        ((base->current_event_cond) ? evthread_cond_fns_.wait_condition((base->current_event_cond), (base->th_base_lock), ((void *)0)) : 0);
    }
    if ((ev->ev_events & (2 | 4 | 128 | 8)) && !(ev->ev_evcallback.evcb_flags & (2 | 8 | 32))) {
        if (ev->ev_events & (2 | 4 | 128)) {
            res = evmap_io_add_(base, ev->ev_fd, ev);
        } else if (ev->ev_events & 8)
            res = evmap_signal_add_(base, (int)ev->ev_fd, ev);
        if (res != -1)
            event_queue_insert_inserted(base, ev);
        if (res == 1) {
            notify = 1;
            res = 0;
        }
    }
    if (res != -1 && tv != ((void *)0)) {
        struct timeval now;
        int common_timeout;
        if (ev->ev_evcallback.evcb_closure == 2 && !tv_is_absolute)
            ev->ev_.ev_io.ev_timeout = *tv;
        if (ev->ev_evcallback.evcb_flags & 1) {
            event_queue_remove_timeout(base, ev);
        }
        if ((ev->ev_evcallback.evcb_flags & 8) && (ev->ev_res & 1)) {
            if (ev->ev_events & 8) {
                if (ev->ev_.ev_signal.ev_ncalls && ev->ev_.ev_signal.ev_pncalls) {
                    *ev->ev_.ev_signal.ev_pncalls = 0;
                }
            }
            event_queue_remove_active(base, event_to_event_callback(ev));
        }
        gettime(base, &now);
        common_timeout = is_common_timeout(tv, base);
        if (tv_is_absolute) {
            ev->ev_timeout = *tv;
        } else if (common_timeout) {
            struct timeval tmp = *tv;
            tmp.tv_usec &= 1048575;
            do {
                ((&ev->ev_timeout))->tv_sec = ((&now))->tv_sec + ((&tmp))->tv_sec;
                ((&ev->ev_timeout))->tv_usec = ((&now))->tv_usec + ((&tmp))->tv_usec;
                if (((&ev->ev_timeout))->tv_usec >= 1000000) {
                    ++((&ev->ev_timeout))->tv_sec;
                    ((&ev->ev_timeout))->tv_usec -= 1000000;
                }
            } while (0);
            ev->ev_timeout.tv_usec |= (tv->tv_usec & ~1048575);
        } else {
            do {
                ((&ev->ev_timeout))->tv_sec = ((&now))->tv_sec + ((tv))->tv_sec;
                ((&ev->ev_timeout))->tv_usec = ((&now))->tv_usec + ((tv))->tv_usec;
                if (((&ev->ev_timeout))->tv_usec >= 1000000) {
                    ++((&ev->ev_timeout))->tv_sec;
                    ((&ev->ev_timeout))->tv_usec -= 1000000;
                }
            } while (0);
        }
        do {
            if ((event_debug_logging_mask_)) {
                event_debugx_("event_add: event %p, timeout in %d seconds %d useconds, call %p", ev, (int)tv->tv_sec, (int)tv->tv_usec, ev->ev_evcallback.evcb_cb_union.evcb_callback);
            }
        } while (0);
        event_queue_insert_timeout(base, ev);
        if (common_timeout) {
            struct common_timeout_list *ctl = get_common_timeout_list(base, &ev->ev_timeout);
            if (ev == ((&ctl->events)->tqh_first)) {
                common_timeout_schedule(ctl, &now, ev);
            }
        } else {
            struct event *top = ((void *)0);
            if (min_heap_elt_is_top_(ev)) {
                notify = 1;
            } else if ((top = min_heap_top_(&base->timeheap)) != ((void *)0) && (((&top->ev_timeout)->tv_sec == (&now)->tv_sec) ? ((&top->ev_timeout)->tv_usec < (&now)->tv_usec) : ((&top->ev_timeout)->tv_sec < (&now)->tv_sec)))
                notify = 1;
        }
    }
    if (res != -1 && notify && (evthread_id_fn_ != ((void *)0) && (base)->running_loop && (base)->th_owner_id != evthread_id_fn_()))
        evthread_notify_base(base);
    event_debug_note_add_(ev);
    return (res);
}


extern int event_del_nolock_ (struct event *ev, int blocking){
    struct event_base *base;
    int res = 0, notify = 0;
    do {
        if ((event_debug_logging_mask_)) {
            event_debugx_("event_del: %p (fd %d), callback %p", ev, (ev->ev_fd), ev->ev_evcallback.evcb_cb_union.evcb_callback);
        }
    } while (0);
    if (ev->ev_base == ((void *)0))
        return (-1);
    do {
        if (((ev->ev_base)->th_base_lock) && evthread_lock_debugging_enabled_) {
            do {
                if (__builtin_expect(!!(!(evthread_is_debug_lock_held_((ev->ev_base)->th_base_lock))), 0)) {
                    event_errx(((int)3735936685U), "%s:%d: Assertion %s failed in %s", "event_InstSlice.c", 1336, "evthread_is_debug_lock_held_((ev->ev_base)->th_base_lock)", __func__);
                    (void)fprintf(stderr, "%s:%d: Assertion %s failed in %s", "event_InstSlice.c", 1336, "evthread_is_debug_lock_held_((ev->ev_base)->th_base_lock)", __func__);
                    abort();
                }
            } while (0);
        }
    } while (0);
    if (blocking != 3) {
        if (ev->ev_evcallback.evcb_flags & 64) {
            return 0;
        }
    }
    base = ev->ev_base;
    do {
        if (__builtin_expect(!!(!(!(ev->ev_evcallback.evcb_flags & ~255))), 0)) {
            event_errx(((int)3735936685U), "%s:%d: Assertion %s failed in %s", "event_InstSlice.c", 1347, "!(ev->ev_flags & ~EVLIST_ALL)", __func__);
            (void)fprintf(stderr, "%s:%d: Assertion %s failed in %s", "event_InstSlice.c", 1347, "!(ev->ev_flags & ~EVLIST_ALL)", __func__);
            abort();
        }
    } while (0);
    if (ev->ev_events & 8) {
        if (ev->ev_.ev_signal.ev_ncalls && ev->ev_.ev_signal.ev_pncalls) {
            *ev->ev_.ev_signal.ev_pncalls = 0;
        }
    }
    if (ev->ev_evcallback.evcb_flags & 1) {
        event_queue_remove_timeout(base, ev);
    }
    if (ev->ev_evcallback.evcb_flags & 8) {
        event_queue_remove_active(base, event_to_event_callback(ev));
    } else if (ev->ev_evcallback.evcb_flags & 32)
        event_queue_remove_active_later(base, event_to_event_callback(ev));
    if (ev->ev_evcallback.evcb_flags & 2) {
        event_queue_remove_inserted(base, ev);
        if (ev->ev_events & (2 | 4 | 128)) {
            res = evmap_io_del_(base, ev->ev_fd, ev);
        } else
            res = evmap_signal_del_(base, (int)ev->ev_fd, ev);
        if (res == 1) {
            notify = 1;
            res = 0;
        }
        if (!event_haveevents(base) && !((base)->event_count_active))
            notify = 1;
    }
    if (res != -1 && notify && (evthread_id_fn_ != ((void *)0) && (base)->running_loop && (base)->th_owner_id != evthread_id_fn_()))
        evthread_notify_base(base);
    event_debug_note_del_(ev);
    if (blocking != 0 && base->current_event == event_to_event_callback(ev) && !(evthread_id_fn_ == ((void *)0) || (base)->th_owner_id == evthread_id_fn_()) && (blocking == 1 || !(ev->ev_events & 64))) {
        ++base->current_event_waiters;
        ((base->current_event_cond) ? evthread_cond_fns_.wait_condition((base->current_event_cond), (base->th_base_lock), ((void *)0)) : 0);
    }
    return (res);
}


static void event_queue_remove_inserted (struct event_base *base, struct event *ev){
    do {
        if (((base)->th_base_lock) && evthread_lock_debugging_enabled_) {
            do {
                if (__builtin_expect(!!(!(evthread_is_debug_lock_held_((base)->th_base_lock))), 0)) {
                    event_errx(((int)3735936685U), "%s:%d: Assertion %s failed in %s", "event_InstSlice.c", 1504, "evthread_is_debug_lock_held_((base)->th_base_lock)", __func__);
                    (void)fprintf(stderr, "%s:%d: Assertion %s failed in %s", "event_InstSlice.c", 1504, "evthread_is_debug_lock_held_((base)->th_base_lock)", __func__);
                    abort();
                }
            } while (0);
        }
    } while (0);
    if (__builtin_expect(!!(!(ev->ev_evcallback.evcb_flags & 2)), 0)) {
        ;
        return;
    }
    ((base)->event_count -= !((ev->ev_evcallback.evcb_flags) & 16));
    ev->ev_evcallback.evcb_flags &= ~2;
}


static void event_queue_remove_active (struct event_base *base, struct event_callback *evcb){
    do {
        if (((base)->th_base_lock) && evthread_lock_debugging_enabled_) {
            do {
                if (__builtin_expect(!!(!(evthread_is_debug_lock_held_((base)->th_base_lock))), 0)) {
                    event_errx(((int)3735936685U), "%s:%d: Assertion %s failed in %s", "event_InstSlice.c", 1515, "evthread_is_debug_lock_held_((base)->th_base_lock)", __func__);
                    (void)fprintf(stderr, "%s:%d: Assertion %s failed in %s", "event_InstSlice.c", 1515, "evthread_is_debug_lock_held_((base)->th_base_lock)", __func__);
                    abort();
                }
            } while (0);
        }
    } while (0);
    if (__builtin_expect(!!(!(evcb->evcb_flags & 8)), 0)) {
        ;
        return;
    }
    ((base)->event_count -= !((evcb->evcb_flags) & 16));
    evcb->evcb_flags &= ~8;
    base->event_count_active--;
    do {
        if (((evcb)->evcb_active_next.tqe_next) != ((void *)0))
            (evcb)->evcb_active_next.tqe_next->evcb_active_next.tqe_prev = (evcb)->evcb_active_next.tqe_prev;
        else
            (&base->activequeues[evcb->evcb_pri])->tqh_last = (evcb)->evcb_active_next.tqe_prev;
        *(evcb)->evcb_active_next.tqe_prev = (evcb)->evcb_active_next.tqe_next;
    } while (0);
}


static void event_queue_remove_active_later (struct event_base *base, struct event_callback *evcb){
    do {
        if (((base)->th_base_lock) && evthread_lock_debugging_enabled_) {
            do {
                if (__builtin_expect(!!(!(evthread_is_debug_lock_held_((base)->th_base_lock))), 0)) {
                    event_errx(((int)3735936685U), "%s:%d: Assertion %s failed in %s", "event_InstSlice.c", 1530, "evthread_is_debug_lock_held_((base)->th_base_lock)", __func__);
                    (void)fprintf(stderr, "%s:%d: Assertion %s failed in %s", "event_InstSlice.c", 1530, "evthread_is_debug_lock_held_((base)->th_base_lock)", __func__);
                    abort();
                }
            } while (0);
        }
    } while (0);
    if (__builtin_expect(!!(!(evcb->evcb_flags & 32)), 0)) {
        ;
        return;
    }
    ((base)->event_count -= !((evcb->evcb_flags) & 16));
    evcb->evcb_flags &= ~32;
    base->event_count_active--;
    do {
        if (((evcb)->evcb_active_next.tqe_next) != ((void *)0))
            (evcb)->evcb_active_next.tqe_next->evcb_active_next.tqe_prev = (evcb)->evcb_active_next.tqe_prev;
        else
            (&base->active_later_queue)->tqh_last = (evcb)->evcb_active_next.tqe_prev;
        *(evcb)->evcb_active_next.tqe_prev = (evcb)->evcb_active_next.tqe_next;
    } while (0);
}


static void event_queue_remove_timeout (struct event_base *base, struct event *ev){
    do {
        if (((base)->th_base_lock) && evthread_lock_debugging_enabled_) {
            do {
                if (__builtin_expect(!!(!(evthread_is_debug_lock_held_((base)->th_base_lock))), 0)) {
                    event_errx(((int)3735936685U), "%s:%d: Assertion %s failed in %s", "event_InstSlice.c", 1544, "evthread_is_debug_lock_held_((base)->th_base_lock)", __func__);
                    (void)fprintf(stderr, "%s:%d: Assertion %s failed in %s", "event_InstSlice.c", 1544, "evthread_is_debug_lock_held_((base)->th_base_lock)", __func__);
                    abort();
                }
            } while (0);
        }
    } while (0);
    if (__builtin_expect(!!(!(ev->ev_evcallback.evcb_flags & 1)), 0)) {
        ;
        return;
    }
    ((base)->event_count -= !((ev->ev_evcallback.evcb_flags) & 16));
    ev->ev_evcallback.evcb_flags &= ~1;
    if (is_common_timeout(&ev->ev_timeout, base)) {
        struct common_timeout_list *ctl = get_common_timeout_list(base, &ev->ev_timeout);
        do {
            if (((ev)->ev_timeout_pos.ev_next_with_common_timeout.tqe_next) != ((void *)0))
                (ev)->ev_timeout_pos.ev_next_with_common_timeout.tqe_next->ev_timeout_pos.ev_next_with_common_timeout.tqe_prev = (ev)->ev_timeout_pos.ev_next_with_common_timeout.tqe_prev;
            else
                (&ctl->events)->tqh_last = (ev)->ev_timeout_pos.ev_next_with_common_timeout.tqe_prev;
            *(ev)->ev_timeout_pos.ev_next_with_common_timeout.tqe_prev = (ev)->ev_timeout_pos.ev_next_with_common_timeout.tqe_next;
        } while (0);
    } else {
        min_heap_erase_(&base->timeheap, ev);
    }
}


static void insert_common_timeout_inorder (struct common_timeout_list *ctl, struct event *ev){
    struct event *e;
    for ((e) = (*(((struct event_list *)((&ctl->events)->tqh_last))->tqh_last)); (e) != ((void *)0); (e) = (*(((struct event_list *)((e)->ev_timeout_pos.ev_next_with_common_timeout.tqe_prev))->tqh_last))) {
        do {
            if (__builtin_expect(!!(!(is_same_common_timeout(&e->ev_timeout, &ev->ev_timeout))), 0)) {
                event_errx(((int)3735936685U), "%s:%d: Assertion %s failed in %s", "event_InstSlice.c", 1623, "is_same_common_timeout(&e->ev_timeout, &ev->ev_timeout)", __func__);
                (void)fprintf(stderr, "%s:%d: Assertion %s failed in %s", "event_InstSlice.c", 1623, "is_same_common_timeout(&e->ev_timeout, &ev->ev_timeout)", __func__);
                abort();
            }
        } while (0);
        if ((((&ev->ev_timeout)->tv_sec == (&e->ev_timeout)->tv_sec) ? ((&ev->ev_timeout)->tv_usec >= (&e->ev_timeout)->tv_usec) : ((&ev->ev_timeout)->tv_sec >= (&e->ev_timeout)->tv_sec))) {
            do {
                if (((ev)->ev_timeout_pos.ev_next_with_common_timeout.tqe_next = (e)->ev_timeout_pos.ev_next_with_common_timeout.tqe_next) != ((void *)0))
                    (ev)->ev_timeout_pos.ev_next_with_common_timeout.tqe_next->ev_timeout_pos.ev_next_with_common_timeout.tqe_prev = &(ev)->ev_timeout_pos.ev_next_with_common_timeout.tqe_next;
                else
                    (&ctl->events)->tqh_last = &(ev)->ev_timeout_pos.ev_next_with_common_timeout.tqe_next;
                (e)->ev_timeout_pos.ev_next_with_common_timeout.tqe_next = (ev);
                (ev)->ev_timeout_pos.ev_next_with_common_timeout.tqe_prev = &(e)->ev_timeout_pos.ev_next_with_common_timeout.tqe_next;
            } while (0);
            return;
        }
    }
    do {
        if (((ev)->ev_timeout_pos.ev_next_with_common_timeout.tqe_next = (&ctl->events)->tqh_first) != ((void *)0))
            (&ctl->events)->tqh_first->ev_timeout_pos.ev_next_with_common_timeout.tqe_prev = &(ev)->ev_timeout_pos.ev_next_with_common_timeout.tqe_next;
        else
            (&ctl->events)->tqh_last = &(ev)->ev_timeout_pos.ev_next_with_common_timeout.tqe_next;
        (&ctl->events)->tqh_first = (ev);
        (ev)->ev_timeout_pos.ev_next_with_common_timeout.tqe_prev = &(&ctl->events)->tqh_first;
    } while (0);
}


static void event_queue_insert_inserted (struct event_base *base, struct event *ev){
    do {
        if (((base)->th_base_lock) && evthread_lock_debugging_enabled_) {
            do {
                if (__builtin_expect(!!(!(evthread_is_debug_lock_held_((base)->th_base_lock))), 0)) {
                    event_errx(((int)3735936685U), "%s:%d: Assertion %s failed in %s", "event_InstSlice.c", 1637, "evthread_is_debug_lock_held_((base)->th_base_lock)", __func__);
                    (void)fprintf(stderr, "%s:%d: Assertion %s failed in %s", "event_InstSlice.c", 1637, "evthread_is_debug_lock_held_((base)->th_base_lock)", __func__);
                    abort();
                }
            } while (0);
        }
    } while (0);
    if (__builtin_expect(!!(ev->ev_evcallback.evcb_flags & 2), 0)) {
        ;
        return;
    }
    do {
        ((base)->event_count += !((ev->ev_evcallback.evcb_flags) & 16));
        (base)->event_count_max = ((((base)->event_count_max) > ((base)->event_count)) ? ((base)->event_count_max) : ((base)->event_count));
    } while (0);
    ev->ev_evcallback.evcb_flags |= 2;
}


static void event_queue_insert_timeout (struct event_base *base, struct event *ev){
    do {
        if (((base)->th_base_lock) && evthread_lock_debugging_enabled_) {
            do {
                if (__builtin_expect(!!(!(evthread_is_debug_lock_held_((base)->th_base_lock))), 0)) {
                    event_errx(((int)3735936685U), "%s:%d: Assertion %s failed in %s", "event_InstSlice.c", 1660, "evthread_is_debug_lock_held_((base)->th_base_lock)", __func__);
                    (void)fprintf(stderr, "%s:%d: Assertion %s failed in %s", "event_InstSlice.c", 1660, "evthread_is_debug_lock_held_((base)->th_base_lock)", __func__);
                    abort();
                }
            } while (0);
        }
    } while (0);
    if (__builtin_expect(!!(ev->ev_evcallback.evcb_flags & 1), 0)) {
        ;
        return;
    }
    do {
        ((base)->event_count += !((ev->ev_evcallback.evcb_flags) & 16));
        (base)->event_count_max = ((((base)->event_count_max) > ((base)->event_count)) ? ((base)->event_count_max) : ((base)->event_count));
    } while (0);
    ev->ev_evcallback.evcb_flags |= 1;
    if (is_common_timeout(&ev->ev_timeout, base)) {
        struct common_timeout_list *ctl = get_common_timeout_list(base, &ev->ev_timeout);
        insert_common_timeout_inorder(ctl, ev);
    } else {
        min_heap_push_(&base->timeheap, ev);
    }
}


extern void * event_mm_realloc_ (void *ptr, size_t sz){
    if (mm_realloc_fn_) {
        return mm_realloc_fn_(ptr, sz);
    } else
        return realloc(ptr, sz);
}


extern void event_mm_free_ (void *ptr){
    if (mm_free_fn_) {
        mm_free_fn_(ptr);
    } else
        free(ptr);
}


