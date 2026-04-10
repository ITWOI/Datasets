static int64_t usUntilEarliestTimer (aeEventLoop *eventLoop){
    aeTimeEvent *te = eventLoop->timeEventHead;
    if (te == ((void *)0))
        return -1;
    aeTimeEvent *earliest = ((void *)0);
    while (te)
        {
            if ((!earliest || te->when < earliest->when) && te->id != -1)
                earliest = te;
            te = te->next;
        }
    monotime now = getMonotonicUs();
    return (now >= earliest->when) ? 0 : earliest->when - now;
}


static int processTimeEvents (aeEventLoop *eventLoop){
    int processed = 0;
    aeTimeEvent *te;
    long long maxId;
    te = eventLoop->timeEventHead;
    maxId = eventLoop->timeEventNextId - 1;
    monotime now = getMonotonicUs();
    while (te)
        {
            long long id;
            if (te->id == -1) {
                aeTimeEvent *next = te->next;
                if (te->refcount) {
                    te = next;
                    continue;
                }
                if (te->prev) {
                    te->prev->next = te->next;
                } else
                    eventLoop->timeEventHead = te->next;
                if (te->next)
                    te->next->prev = te->prev;
                if (te->finalizerProc) {
                    ;
                    now = getMonotonicUs();
                }
                ;
                te = next;
                continue;
            }
            if (te->id > maxId) {
                te = te->next;
                continue;
            }
            if (te->when <= now) {
                int retval;
                id = te->id;
                te->refcount++;
                retval = te->timeProc(eventLoop, id, te->clientData);
                te->refcount--;
                processed++;
                now = getMonotonicUs();
                if (retval != -1) {
                    te->when = now + (monotime)retval * 1000;
                } else {
                    te->id = -1;
                }
            }
            te = te->next;
        }
    return processed;
}


extern int aeProcessEvents (aeEventLoop *eventLoop, int flags){
    int processed = 0, numevents;
    if (!(flags & (1 << 1)) && !(flags & (1 << 0)))
        return 0;
    if (eventLoop->maxfd != -1 || ((flags & (1 << 1)) && !(flags & (1 << 2)))) {
        int j;
        struct timeval tv, *tvp = ((void *)0);
        int64_t usUntilTimer;
        ;
        if ((flags & (1 << 2)) || (eventLoop->flags & (1 << 2))) {
            tv.tv_sec = tv.tv_usec = 0;
            tvp = &tv;
        } else if (flags & (1 << 1)) {
            usUntilTimer = usUntilEarliestTimer(eventLoop);
            if (usUntilTimer >= 0) {
                tv.tv_sec = usUntilTimer / 1000000;
                tv.tv_usec = usUntilTimer % 1000000;
                tvp = &tv;
            }
        }
        numevents = aeApiPoll(eventLoop, tvp);
        if (!(flags & (1 << 0))) {
            numevents = 0;
        }
        ;
        for (j = 0; j < numevents; j++) {
            int fd = eventLoop->fired[j].fd;
            aeFileEvent *fe = &eventLoop->events[fd];
            int mask = eventLoop->fired[j].mask;
            int fired = 0;
            int invert = fe->mask & 4;
            ;
        }
    }
    if (flags & (1 << 1))
        processed += processTimeEvents(eventLoop);
    return processed;
}


extern void aeMain (aeEventLoop *eventLoop){
    eventLoop->stop = 0;
    while (!eventLoop->stop)
        {
            aeProcessEvents(eventLoop, ((1 << 0) | (1 << 1)) | (1 << 3) | (1 << 4));
        }
}


