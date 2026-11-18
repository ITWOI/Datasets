#include "header_func.h"
static int name_parse (uint8_t *packet, int length, int *idx, char *name_out, int name_out_len){
    int name_end = -1;
    int j = *idx;
    int ptr_count = 0;
    char *cp = name_out;
    const char *const end = name_out + name_out_len;
    for (;;) {
        uint8_t label_len;
        do {
            if (j >= length)
                goto err;
            label_len = packet[j++];
        } while (0);
        if (!label_len)
            break;
        if (label_len & 192) {
            uint8_t ptr_low;
            do {
                if (j >= length)
                    goto err;
                ptr_low = packet[j++];
            } while (0);
            if (name_end < 0)
                name_end = j;
            j = (((int)label_len & 63) << 8) + ptr_low;
            if (j < 0 || j >= length)
                return -1;
            if (++ptr_count > length)
                return -1;
            continue;
        }
        if (label_len > 63)
            return -1;
        if (cp != name_out) {
            if (cp + 1 >= end)
                return -1;
            *cp++ = '.';
        }
        if (cp + label_len >= end)
            return -1;
        if (j + label_len > length)
            return -1;
        memcpy(cp, packet + j, label_len);
        cp += label_len;
        j += label_len;
    }
    if (cp >= end)
        return -1;
    *cp = '\x00';
    if (name_end < 0) {
        *idx = j;
    } else
        *idx = name_end;
    return 0;
  err:
    return -1;
}
static int request_parse (uint8_t *packet, int length, struct evdns_server_port *port, struct sockaddr *addr, socklen_t addrlen){
    int j = 0;
    uint16_t t_;
    char tmp_name[256];
    int i;
    uint16_t trans_id, flags, questions, answers, authority, additional;
    struct server_request *server_req = ((void *)0);
    do {
        if (((port)->lock) && evthread_lock_debugging_enabled_) {
            do {
                if (__builtin_expect(!!(!(evthread_is_debug_lock_held_((port)->lock))), 0)) {
                    event_errx(((int)3735936685U), "%s:%d: Assertion %s failed in %s", "evdns_InstSlice.c", 621, "evthread_is_debug_lock_held_((port)->lock)", __func__);
                    (void)fprintf(stderr, "%s:%d: Assertion %s failed in %s", "evdns_InstSlice.c", 621, "evthread_is_debug_lock_held_((port)->lock)", __func__);
                    abort();
                }
            } while (0);
        }
    } while (0);
    do {
        if (j + 2 > length)
            goto err;
        memcpy(&t_, packet + j, 2);
        j += 2;
        trans_id = ntohs(t_);
    } while (0);
    do {
        if (j + 2 > length)
            goto err;
        memcpy(&t_, packet + j, 2);
        j += 2;
        flags = ntohs(t_);
    } while (0);
    do {
        if (j + 2 > length)
            goto err;
        memcpy(&t_, packet + j, 2);
        j += 2;
        questions = ntohs(t_);
    } while (0);
    do {
        if (j + 2 > length)
            goto err;
        memcpy(&t_, packet + j, 2);
        j += 2;
        answers = ntohs(t_);
    } while (0);
    do {
        if (j + 2 > length)
            goto err;
        memcpy(&t_, packet + j, 2);
        j += 2;
        authority = ntohs(t_);
    } while (0);
    do {
        if (j + 2 > length)
            goto err;
        memcpy(&t_, packet + j, 2);
        j += 2;
        additional = ntohs(t_);
    } while (0);
    if (flags & 32768U)
        return -1;
    flags &= (256U | 16U);
    server_req = event_mm_malloc_(sizeof(struct server_request));
    if (server_req == ((void *)0))
        return -1;
    server_req->trans_id = trans_id;
    server_req->addrlen = addrlen;
    server_req->base.flags = flags;
    server_req->base.nquestions = 0;
    server_req->base.questions = event_mm_calloc_((sizeof(struct evdns_server_question *)), (questions));
    if (server_req->base.questions == ((void *)0))
        goto err;
    for (i = 0; i < questions; ++i) {
        uint16_t type, class;
        struct evdns_server_question *q;
        int namelen;
        if (name_parse(packet, length, &j, tmp_name, sizeof (tmp_name)) < 0)
            goto err;
        do {
            if (j + 2 > length)
                goto err;
            memcpy(&t_, packet + j, 2);
            j += 2;
            type = ntohs(t_);
        } while (0);
        do {
            if (j + 2 > length)
                goto err;
            memcpy(&t_, packet + j, 2);
            j += 2;
            class = ntohs(t_);
        } while (0);
        namelen = (int)strlen(tmp_name);
        q = event_mm_malloc_(sizeof(struct evdns_server_question) + namelen);
        if (!q)
            goto err;
        q->type = type;
        q->class = class;
        server_req->base.questions[server_req->base.nquestions++] = q;
    }
    server_req->port = port;
    port->refcnt++;
    if (flags & 30720U) {
        evdns_server_request_respond(&(server_req->base), 4);
        return -1;
    }
    ;
    return 0;
  err:
    if (server_req->base.questions) {
        ;
    }
    ;
    return -1;
}
static void server_port_read (struct evdns_server_port *s){
    uint8_t packet[1500];
    struct sockaddr_storage addr;
    socklen_t addrlen;
    int r;
    do {
        if (((s)->lock) && evthread_lock_debugging_enabled_) {
            do {
                if (__builtin_expect(!!(!(evthread_is_debug_lock_held_((s)->lock))), 0)) {
                    event_errx(((int)3735936685U), "%s:%d: Assertion %s failed in %s", "evdns_InstSlice.c", 728, "evthread_is_debug_lock_held_((s)->lock)", __func__);
                    (void)fprintf(stderr, "%s:%d: Assertion %s failed in %s", "evdns_InstSlice.c", 728, "evthread_is_debug_lock_held_((s)->lock)", __func__);
                    abort();
                }
            } while (0);
        }
    } while (0);
    for (;;) {
        addrlen = sizeof(struct sockaddr_storage);
        r = recvfrom(s->socket, (void *)packet, sizeof (packet), 0, (__SOCKADDR_ARG){(struct sockaddr *)&addr}, &addrlen);
        if (r < 0) {
            int err = ((*__errno_location()));
            return;
        }
        request_parse(packet, r, s, (struct sockaddr *)&addr, addrlen);
    }
}
static void server_port_flush (struct evdns_server_port *port){
    struct server_request *req = port->pending_replies;
    do {
        if (((port)->lock) && evthread_lock_debugging_enabled_) {
            do {
                if (__builtin_expect(!!(!(evthread_is_debug_lock_held_((port)->lock))), 0)) {
                    event_errx(((int)3735936685U), "%s:%d: Assertion %s failed in %s", "evdns_InstSlice.c", 749, "evthread_is_debug_lock_held_((port)->lock)", __func__);
                    (void)fprintf(stderr, "%s:%d: Assertion %s failed in %s", "evdns_InstSlice.c", 749, "evthread_is_debug_lock_held_((port)->lock)", __func__);
                    abort();
                }
            } while (0);
        }
    } while (0);
    while (req)
        {
            int r = sendto(port->socket, req->response, (int)req->response_len, 0, (__CONST_SOCKADDR_ARG){(struct sockaddr *)&req->addr}, (socklen_t)req->addrlen);
            if (r < 0) {
                int err = ((*__errno_location()));
                if (((err) == 4 || ((err) == 11)))
                    return;
            }
            if (server_request_free(req)) {
                return;
            } else {
                do {
                    if (__builtin_expect(!!(!(req != port->pending_replies)), 0)) {
                        event_errx(((int)3735936685U), "%s:%d: Assertion %s failed in %s", "evdns_InstSlice.c", 762, "req != port->pending_replies", __func__);
                        (void)fprintf(stderr, "%s:%d: Assertion %s failed in %s", "evdns_InstSlice.c", 762, "req != port->pending_replies", __func__);
                        abort();
                    }
                } while (0);
                req = port->pending_replies;
            }
        }
    ;
}
static void server_port_ready_callback (int fd, short events, void *arg){
    struct evdns_server_port *port = (struct evdns_server_port *)arg;
    if (events & 4) {
        port->choked = 0;
        server_port_flush(port);
    }
    if (events & 2) {
        server_port_read(port);
    }
    ;
}
static void dnslabel_table_init (struct dnslabel_table *table){
    table->n_labels = 0;
}
static void dnslabel_clear (struct dnslabel_table *table){
    int i;
    table->n_labels = 0;
}
static int dnslabel_table_get_pos (const struct dnslabel_table *table, const char *label){
    int i;
    for (i = 0; i < table->n_labels; ++i) {
        if (!strcmp(label, table->labels[i].v))
            return table->labels[i].pos;
    }
    return -1;
}
static int dnslabel_table_add (struct dnslabel_table *table, const char *label, off_t pos){
    char *v;
    int p;
    if (table->n_labels == 128)
        return (-1);
    v = event_mm_strdup_(label);
    if (v == ((void *)0))
        return (-1);
    p = table->n_labels++;
    table->labels[p].v = v;
    table->labels[p].pos = pos;
    return (0);
}
static off_t dnsname_to_labels (uint8_t *const buf, size_t buf_len, off_t j, const char *name, const size_t name_len, struct dnslabel_table *table){
    const char *end = name + name_len;
    int ref = 0;
    uint16_t t_;
    if (name_len > 255)
        return -2;
    for (;;) {
        const char *const start = name;
        if (table && (ref = dnslabel_table_get_pos(table, name)) >= 0) {
            do {
                if (j + 2 > (off_t)buf_len)
                    goto overflow;
                t_ = htons(ref | 49152);
                memcpy(buf + j, &t_, 2);
                j += 2;
            } while (0);
            return j;
        }
        name = strchr(name, '.');
        if (!name) {
            const size_t label_len = end - start;
            if (label_len > 63)
                return -1;
            if ((size_t)(j + label_len + 1) > buf_len)
                return -2;
            if (table)
                dnslabel_table_add(table, start, j);
            buf[j++] = (uint8_t)label_len;
            memcpy(buf + j, start, label_len);
            j += (int)label_len;
            break;
        } else {
            const size_t label_len = name - start;
            if (label_len > 63)
                return -1;
            if ((size_t)(j + label_len + 1) > buf_len)
                return -2;
            if (table)
                dnslabel_table_add(table, start, j);
            buf[j++] = (uint8_t)label_len;
            memcpy(buf + j, start, label_len);
            j += (int)label_len;
            name++;
        }
    }
    if (!j || buf[j - 1])
        buf[j++] = 0;
    return j;
  overflow:
    return (-2);
}
static int evdns_server_request_format_response (struct server_request *req, int err){
    unsigned char buf[1500];
    size_t buf_len = sizeof (buf);
    off_t j = 0, r;
    uint16_t t_;
    uint32_t t32_;
    int i;
    uint16_t flags;
    struct dnslabel_table table;
    if (err < 0 || err > 15)
        return -1;
    flags = req->base.flags;
    flags |= (32768U | err);
    dnslabel_table_init(&table);
    do {
        if (j + 2 > (off_t)buf_len)
            goto overflow;
        t_ = htons(req->trans_id);
        memcpy(buf + j, &t_, 2);
        j += 2;
    } while (0);
    do {
        if (j + 2 > (off_t)buf_len)
            goto overflow;
        t_ = htons(flags);
        memcpy(buf + j, &t_, 2);
        j += 2;
    } while (0);
    do {
        if (j + 2 > (off_t)buf_len)
            goto overflow;
        t_ = htons(req->base.nquestions);
        memcpy(buf + j, &t_, 2);
        j += 2;
    } while (0);
    do {
        if (j + 2 > (off_t)buf_len)
            goto overflow;
        t_ = htons(req->n_answer);
        memcpy(buf + j, &t_, 2);
        j += 2;
    } while (0);
    do {
        if (j + 2 > (off_t)buf_len)
            goto overflow;
        t_ = htons(req->n_authority);
        memcpy(buf + j, &t_, 2);
        j += 2;
    } while (0);
    do {
        if (j + 2 > (off_t)buf_len)
            goto overflow;
        t_ = htons(req->n_additional);
        memcpy(buf + j, &t_, 2);
        j += 2;
    } while (0);
    for (i = 0; i < req->base.nquestions; ++i) {
        const char *s = req->base.questions[i]->name;
        j = dnsname_to_labels(buf, buf_len, j, s, strlen(s), &table);
        if (j < 0) {
            dnslabel_clear(&table);
            return (int)j;
        }
        do {
            if (j + 2 > (off_t)buf_len)
                goto overflow;
            t_ = htons(req->base.questions[i]->type);
            memcpy(buf + j, &t_, 2);
            j += 2;
        } while (0);
        do {
            if (j + 2 > (off_t)buf_len)
                goto overflow;
            t_ = htons(req->base.questions[i]->class);
            memcpy(buf + j, &t_, 2);
            j += 2;
        } while (0);
    }
    for (i = 0; i < 3; ++i) {
        struct server_reply_item *item;
        if (i == 0) {
            item = req->answer;
        } else if (i == 1) {
            item = req->authority;
        } else
            item = req->additional;
        while (item)
            {
                r = dnsname_to_labels(buf, buf_len, j, item->name, strlen(item->name), &table);
                if (r < 0)
                    goto overflow;
                j = r;
                do {
                    if (j + 2 > (off_t)buf_len)
                        goto overflow;
                    t_ = htons(item->type);
                    memcpy(buf + j, &t_, 2);
                    j += 2;
                } while (0);
                do {
                    if (j + 2 > (off_t)buf_len)
                        goto overflow;
                    t_ = htons(item->class);
                    memcpy(buf + j, &t_, 2);
                    j += 2;
                } while (0);
                do {
                    if (j + 4 > (off_t)buf_len)
                        goto overflow;
                    t32_ = htonl(item->ttl);
                    memcpy(buf + j, &t32_, 4);
                    j += 4;
                } while (0);
                if (item->is_name) {
                    off_t len_idx = j, name_start;
                    j += 2;
                    name_start = j;
                    r = dnsname_to_labels(buf, buf_len, j, item->data, strlen(item->data), &table);
                    if (r < 0)
                        goto overflow;
                    j = r;
                    t_ = htons((short)(j - name_start));
                    memcpy(buf + len_idx, &t_, 2);
                } else {
                    do {
                        if (j + 2 > (off_t)buf_len)
                            goto overflow;
                        t_ = htons(item->datalen);
                        memcpy(buf + j, &t_, 2);
                        j += 2;
                    } while (0);
                    if (j + item->datalen > (off_t)buf_len)
                        goto overflow;
                    memcpy(buf + j, item->data, item->datalen);
                    j += item->datalen;
                }
                item = item->next;
            }
    }
    if (j > 512) {
      overflow:
        j = 512;
        buf[2] |= 2;
    }
    req->response_len = j;
    if (!(req->response = event_mm_malloc_(req->response_len))) {
        server_request_free_answers(req);
        dnslabel_clear(&table);
        return (-1);
    }
    ;
    server_request_free_answers(req);
    dnslabel_clear(&table);
    return (0);
}
extern int evdns_server_request_respond (struct evdns_server_request *req_, int err){
    struct server_request *req = ((struct server_request *)(((char *)(req_) - __builtin_offsetof(struct server_request, base))));
    struct evdns_server_port *port = req->port;
    int r = -1;
    if (!req->response) {
        if ((r = evdns_server_request_format_response(req, err)) < 0)
            goto done;
    }
    r = sendto(port->socket, req->response, (int)req->response_len, 0, (__CONST_SOCKADDR_ARG){(struct sockaddr *)&req->addr}, (socklen_t)req->addrlen);
    if (r < 0) {
        int sock_err = ((*__errno_location()));
        if (((sock_err) == 4 || ((sock_err) == 11)))
            goto done;
        if (port->pending_replies) {
            req->prev_pending = port->pending_replies->prev_pending;
            req->next_pending = port->pending_replies;
            req->prev_pending->next_pending = req->next_pending->prev_pending = req;
        } else {
            req->prev_pending = req->next_pending = req;
            port->pending_replies = req;
            port->choked = 1;
        }
        ;
        goto done;
    }
    if (server_request_free(req)) {
        ;
        goto done;
    }
    if (port->pending_replies)
        server_port_flush(port);
  done:
    ;
    return r;
}
static void server_request_free_answers (struct server_request *req){
    struct server_reply_item *victim, *next, **list;
    int i;
    for (i = 0; i < 3; ++i) {
        if (i == 0) {
            list = &req->answer;
        } else if (i == 1) {
            list = &req->authority;
        } else
            list = &req->additional;
        *list = ((void *)0);
    }
}
static int server_request_free (struct server_request *req){
    int i, rc = 1, lock = 0;
    if (req->base.questions) {
        for (i = 0; i < req->base.nquestions; ++i)
            event_mm_free_(req->base.questions[i]);
    }
    if (req->port) {
        ;
        lock = 1;
        if (req->port->pending_replies == req) {
            if (req->next_pending && req->next_pending != req)
                req->port->pending_replies = req->next_pending;
            else
                req->port->pending_replies = ((void *)0);
        }
        rc = --req->port->refcnt;
    }
    server_request_free_answers(req);
    if (req->next_pending && req->next_pending != req) {
        req->next_pending->prev_pending = req->prev_pending;
        req->prev_pending->next_pending = req->next_pending;
    }
    if (rc == 0) {
        ;
        server_port_free(req->port);
        return (1);
    }
    ;
    return (0);
}
static void server_port_free (struct evdns_server_port *port){
    do {
        if (__builtin_expect(!!(!(port)), 0)) {
            event_errx(((int)3735936685U), "%s:%d: Assertion %s failed in %s", "evdns_InstSlice.c", 1215, "port", __func__);
            (void)fprintf(stderr, "%s:%d: Assertion %s failed in %s", "evdns_InstSlice.c", 1215, "port", __func__);
            abort();
        }
    } while (0);
    do {
        if (__builtin_expect(!!(!(!port->refcnt)), 0)) {
            event_errx(((int)3735936685U), "%s:%d: Assertion %s failed in %s", "evdns_InstSlice.c", 1216, "!port->refcnt", __func__);
            (void)fprintf(stderr, "%s:%d: Assertion %s failed in %s", "evdns_InstSlice.c", 1216, "!port->refcnt", __func__);
            abort();
        }
    } while (0);
    do {
        if (__builtin_expect(!!(!(!port->pending_replies)), 0)) {
            event_errx(((int)3735936685U), "%s:%d: Assertion %s failed in %s", "evdns_InstSlice.c", 1217, "!port->pending_replies", __func__);
            (void)fprintf(stderr, "%s:%d: Assertion %s failed in %s", "evdns_InstSlice.c", 1217, "!port->pending_replies", __func__);
            abort();
        }
    } while (0);
    if (port->socket > 0) {
        ;
        port->socket = -1;
    }
    ;
    do {
        void *lock_tmp_ = (port->lock);
        if (lock_tmp_ && evthread_lock_fns_.free)
            evthread_lock_fns_.free(lock_tmp_, (1));
    } while (0);
}
