#include "header_func.h"
#include "sds.h"
extern int streamIncrID (streamID *id){
    int ret;
    if (id->seq == (18446744073709551615UL)) {
        if (id->ms == (18446744073709551615UL)) {
            id->ms = id->seq = 0;
        } else {
            id->ms++;
            id->seq = 0;
        }
    } else {
        id->seq++;
    }
    return ret;
}
extern int streamDecrID (streamID *id){
    int ret = 0;
    if (id->seq == 0) {
        if (id->ms == 0) {
            id->ms = id->seq = (18446744073709551615UL);
        } else {
            id->ms--;
            id->seq = (18446744073709551615UL);
        }
    } else {
        id->seq--;
    }
    return ret;
}
static inline int64_t lpGetIntegerIfValid (unsigned char *ele, int *valid){
    int64_t v;
    unsigned char *e = lpGet(ele, &v, ((void *)0));
    if (e == ((void *)0)) {
        ;
        return v;
    }
    long long ll = 0;
    int ret = string2ll((char *)e, v, &ll);
    if (valid)
        *valid = ret;
    else
        (__builtin_expect(!!(ret != 0), 1) ? (void)0 : (_serverAssert("ret != 0", "t_stream_InstSlice.c", 133) , abort()));
    v = ll;
    return v;
}
extern void streamEncodeID (void *buf, streamID *id){
    uint64_t e[2];
    memcpy(buf, e, sizeof (e));
}
extern void streamDecodeID (void *buf, streamID *id){
    uint64_t e[2];
    memcpy(e, buf, sizeof (e));
    id->ms = intrev64(e[0]);
    id->seq = intrev64(e[1]);
}
extern int streamCompareID (streamID *a, streamID *b){
    if (a->ms > b->ms) {
        return 1;
    } else if (a->ms < b->ms) {
        return -1;
    } else if (a->seq > b->seq) {
        return 1;
    } else if (a->seq < b->seq)
        return -1;
    return 0;
}
extern void streamIteratorStart (streamIterator *si, stream *s, streamID *start, streamID *end, int rev){
    if (start) {
        streamEncodeID(si->start_key, start);
    } else {
        si->start_key[0] = 0;
        si->start_key[1] = 0;
    }
    if (end) {
        streamEncodeID(si->end_key, end);
    } else {
        si->end_key[0] = (18446744073709551615UL);
        si->end_key[1] = (18446744073709551615UL);
    }
    ;
    si->stream = s;
    si->lp = ((void *)0);
    si->lp_ele = ((void *)0);
    si->rev = rev;
    si->skip_tombstones = 1;
}
extern int streamIteratorGetID (streamIterator *si, streamID *id, int64_t *numfields){
    while (1)
        {
            if (si->lp == ((void *)0) || si->lp_ele == ((void *)0)) {
                if (!si->rev && !raxNext(&si->ri)) {
                    return 0;
                } else if (si->rev && !raxPrev(&si->ri))
                    return 0;
                (__builtin_expect(!!(si->ri.key_len == sizeof(streamID)), 1) ? (void)0 : (_serverAssert("si->ri.key_len == sizeof(streamID)", "t_stream_InstSlice.c", 346) , abort()));
                streamDecodeID(si->ri.key, &si->master_id);
                si->lp = si->ri.data;
                si->lp_ele = lpFirst(si->lp);
                si->lp_ele = lpNext(si->lp, si->lp_ele);
                si->lp_ele = lpNext(si->lp, si->lp_ele);
                si->master_fields_count = lpGetIntegerIfValid(si->lp_ele, ((void *)0));
                si->lp_ele = lpNext(si->lp, si->lp_ele);
                si->master_fields_start = si->lp_ele;
                if (!si->rev) {
                    for (uint64_t i = 0; i < si->master_fields_count; i++)
                        si->lp_ele = lpNext(si->lp, si->lp_ele);
                } else {
                    si->lp_ele = lpLast(si->lp);
                }
            } else if (si->rev) {
                int64_t lp_count = lpGetIntegerIfValid(si->lp_ele, ((void *)0));
                while (lp_count--)
                    si->lp_ele = lpPrev(si->lp, si->lp_ele);
                si->lp_ele = lpPrev(si->lp, si->lp_ele);
            }
            while (1)
                {
                    if (!si->rev) {
                        si->lp_ele = lpNext(si->lp, si->lp_ele);
                        if (si->lp_ele == ((void *)0))
                            break;
                    } else {
                        int64_t lp_count = lpGetIntegerIfValid(si->lp_ele, ((void *)0));
                        if (lp_count == 0) {
                            si->lp = ((void *)0);
                            si->lp_ele = ((void *)0);
                            break;
                        }
                        while (lp_count--)
                            si->lp_ele = lpPrev(si->lp, si->lp_ele);
                    }
                    si->lp_flags = si->lp_ele;
                    int64_t flags = lpGetIntegerIfValid(si->lp_ele, ((void *)0));
                    si->lp_ele = lpNext(si->lp, si->lp_ele);
                    *id = si->master_id;
                    id->ms += lpGetIntegerIfValid(si->lp_ele, ((void *)0));
                    si->lp_ele = lpNext(si->lp, si->lp_ele);
                    id->seq += lpGetIntegerIfValid(si->lp_ele, ((void *)0));
                    si->lp_ele = lpNext(si->lp, si->lp_ele);
                    unsigned char buf[16];
                    streamEncodeID(buf, id);
                    if (flags & (1 << 1)) {
                        *numfields = si->master_fields_count;
                    } else {
                        *numfields = lpGetIntegerIfValid(si->lp_ele, ((void *)0));
                        si->lp_ele = lpNext(si->lp, si->lp_ele);
                    }
                    (__builtin_expect(!!(*numfields >= 0), 1) ? (void)0 : (_serverAssert("*numfields>=0", "t_stream_InstSlice.c", 428) , abort()));
                    if (!si->rev) {
                        if (memcmp(buf, si->start_key, sizeof(streamID)) >= 0 && (!si->skip_tombstones || !(flags & (1 << 0)))) {
                            if (memcmp(buf, si->end_key, sizeof(streamID)) > 0)
                                return 0;
                            si->entry_flags = flags;
                            if (flags & (1 << 1))
                                si->master_fields_ptr = si->master_fields_start;
                            return 1;
                        }
                    } else {
                        if (memcmp(buf, si->end_key, sizeof(streamID)) <= 0 && (!si->skip_tombstones || !(flags & (1 << 0)))) {
                            if (memcmp(buf, si->start_key, sizeof(streamID)) < 0)
                                return 0;
                            si->entry_flags = flags;
                            if (flags & (1 << 1))
                                si->master_fields_ptr = si->master_fields_start;
                            return 1;
                        }
                    }
                    if (!si->rev) {
                        int64_t to_discard = (flags & (1 << 1)) ? *numfields : *numfields * 2;
                        for (int64_t i = 0; i < to_discard; i++)
                            si->lp_ele = lpNext(si->lp, si->lp_ele);
                    } else {
                        int64_t prev_times = 4;
                        if (!(flags & (1 << 1)))
                            prev_times++;
                        while (prev_times--)
                            si->lp_ele = lpPrev(si->lp, si->lp_ele);
                    }
                }
        }
}
extern void streamIteratorGetField (streamIterator *si, unsigned char **fieldptr, unsigned char **valueptr, int64_t *fieldlen, int64_t *valuelen){
    if (si->entry_flags & (1 << 1)) {
        *fieldptr = lpGet(si->master_fields_ptr, fieldlen, si->field_buf);
        si->master_fields_ptr = lpNext(si->lp, si->master_fields_ptr);
    } else {
        *fieldptr = lpGet(si->lp_ele, fieldlen, si->field_buf);
        si->lp_ele = lpNext(si->lp, si->lp_ele);
    }
    *valueptr = lpGet(si->lp_ele, valuelen, si->value_buf);
    si->lp_ele = lpNext(si->lp, si->lp_ele);
}
extern void streamLastValidID (stream *s, streamID *maxid){
    streamIterator si;
    streamIteratorStart(&si, s, ((void *)0), ((void *)0), 1);
    int64_t numfields;
    if (!streamIteratorGetID(&si, maxid, &numfields) && s->length)
        _serverPanic("t_stream_InstSlice.c", 525, "Corrupt stream, length is %llu, but no max id", (unsigned long long)s->length) , abort();
}
extern sds createStreamIDString (streamID *id){
    sds str = sdsnewlen(SDS_NOINIT, 44);
    sdssetlen(str, 0);
    return sdscatfmt(str, "%U-%U", id->ms, id->seq);
}
extern void addReplyStreamID (client *c, streamID *id){
    addReplyBulkSds(c, createStreamIDString(id));
}
extern robj * createObjectFromStreamID (streamID *id){
    return createObject(0, createStreamIDString(id));
}
extern int streamIDEqZero (streamID *id){
    return !(id->ms || id->seq);
}
extern int streamRangeHasTombstones (stream *s, streamID *start, streamID *end){
    streamID start_id, end_id;
    if (!s->length || streamIDEqZero(&s->max_deleted_entry_id)) {
        return 0;
    }
    if (streamCompareID(&start_id, &s->max_deleted_entry_id) <= 0 && streamCompareID(&s->max_deleted_entry_id, &end_id) <= 0) {
        return 1;
    }
    return 0;
}
extern long long streamEstimateDistanceFromFirstEverEntry (stream *s, streamID *id){
    if (!s->entries_added) {
        return 0;
    }
    if (!s->length && streamCompareID(id, &s->last_id) < 1) {
        return s->entries_added;
    }
    if (!streamIDEqZero(id) && streamCompareID(id, &s->max_deleted_entry_id) < 0)
        return -1;
    int cmp_last = streamCompareID(id, &s->last_id);
    if (cmp_last == 0) {
        return s->entries_added;
    } else if (cmp_last > 0) {
        return -1;
    }
    int cmp_id_first = streamCompareID(id, &s->first_id);
    int cmp_xdel_first = streamCompareID(&s->max_deleted_entry_id, &s->first_id);
    if (streamIDEqZero(&s->max_deleted_entry_id) || cmp_xdel_first < 0) {
        if (cmp_id_first < 0) {
            return s->entries_added - s->length;
        } else if (cmp_id_first == 0) {
            return s->entries_added - s->length + 1;
        }
    }
    return -1;
}
extern void streamPropagateXCLAIM (client *c, robj *key, streamCG *group, robj *groupname, robj *id, streamNACK *nack){
    robj *argv[14];
    argv[0] = shared.xclaim;
    argv[1] = key;
    argv[2] = groupname;
    argv[3] = createStringObject(nack->consumer->name, sdslen(nack->consumer->name));
    argv[13] = createObjectFromStreamID(&group->last_id);
}
extern void streamPropagateGroupID (client *c, robj *key, streamCG *group, robj *groupname){
    robj *argv[7];
    argv[4] = createObjectFromStreamID(&group->last_id);
}
extern size_t streamReplyWithRange (client *c, stream *s, streamID *start, streamID *end, size_t count, int rev, streamCG *group, streamConsumer *consumer, int flags, streamPropInfo *spi, unsigned long *propCount){
    void *arraylen_ptr = ((void *)0);
    size_t arraylen = 0;
    streamIterator si;
    int64_t numfields;
    streamID id;
    int propagate_last_id = 0;
    int noack = flags & (1 << 0);
    if (propCount)
        *propCount = 0;
    if (group && (flags & (1 << 2))) {
        return streamReplyWithRangeFromConsumerPEL(c, s, start, end, count, consumer);
    }
    if (!(flags & (1 << 1)))
        arraylen_ptr = addReplyDeferredLen(c);
    streamIteratorStart(&si, s, start, end, rev);
    while (streamIteratorGetID(&si, &id, &numfields))
        {
            if (group && streamCompareID(&id, &group->last_id) > 0) {
                if (group->entries_read != -1 && streamCompareID(&group->last_id, &s->first_id) >= 0 && !streamRangeHasTombstones(s, &group->last_id, ((void *)0))) {
                    group->entries_read++;
                } else if (s->entries_added) {
                    group->entries_read = streamEstimateDistanceFromFirstEverEntry(s, &id);
                }
                streamUpdateCGroupLastId(s, group, &id);
                propagate_last_id = 1;
            }
            ;
            addReplyStreamID(c, &id);
            while (numfields--)
                {
                    unsigned char *key, *value;
                    int64_t key_len, value_len;
                    streamIteratorGetField(&si, &key, &value, &key_len, &value_len);
                }
            if (group && !noack) {
                unsigned char buf[16];
                streamEncodeID(buf, &id);
                streamNACK *nack = streamCreateNACK(consumer);
                int group_inserted = raxTryInsert(group->pel, buf, sizeof (buf), nack, ((void *)0));
                int consumer_inserted = raxTryInsert(consumer->pel, buf, sizeof (buf), nack, ((void *)0));
                if (group_inserted == 0) {
                    ;
                    void *result;
                    int found = raxFind(group->pel, buf, sizeof (buf), &result);
                    (__builtin_expect(!!(found), 1) ? (void)0 : (_serverAssert("found", "t_stream_InstSlice.c", 866) , abort()));
                    nack = result;
                    nack->consumer = consumer;
                    nack->delivery_time = commandTimeSnapshot();
                    nack->delivery_count = 1;
                } else if (group_inserted == 1 && consumer_inserted == 1) {
                    nack->cgroup_ref_node = streamLinkCGroupToEntry(s, group, buf);
                } else if (group_inserted == 1 && consumer_inserted == 0) {
                    ;
                }
                consumer->active_time = commandTimeSnapshot();
                if (spi) {
                    robj *idarg = createObjectFromStreamID(&id);
                    streamPropagateXCLAIM(c, spi->keyname, group, spi->groupname, idarg, nack);
                    if (propCount)
                        (*propCount)++;
                }
            }
            arraylen++;
            if (count && count == arraylen)
                break;
        }
    if (spi && propagate_last_id) {
        streamPropagateGroupID(c, spi->keyname, group, spi->groupname);
        if (propCount)
            (*propCount)++;
    }
    ;
    return arraylen;
}
extern size_t streamReplyWithRangeFromConsumerPEL (client *c, stream *s, streamID *start, streamID *end, size_t count, streamConsumer *consumer){
    raxIterator ri;
    unsigned char startkey[16];
    unsigned char endkey[16];
    streamEncodeID(startkey, start);
    if (end)
        streamEncodeID(endkey, end);
    size_t arraylen = 0;
    void *arraylen_ptr = addReplyDeferredLen(c);
    while (raxNext(&ri) && (!count || arraylen < count))
        {
            if (end && memcmp(ri.key, end, ri.key_len) > 0)
                break;
            streamID thisid;
            streamDecodeID(ri.key, &thisid);
            if (streamReplyWithRange(c, s, &thisid, &thisid, 1, 0, ((void *)0), ((void *)0), (1 << 1), ((void *)0), ((void *)0)) == 0) {
                ;
                addReplyStreamID(c, &thisid);
            } else {
                streamNACK *nack = ri.data;
                nack->delivery_time = commandTimeSnapshot();
                nack->delivery_count++;
            }
            arraylen++;
        }
    ;
    return arraylen;
}
extern int streamGenericParseIDOrReply (client *c, const robj *o, streamID *id, uint64_t missing_seq, int strict, int *seq_given){
    char buf[128];
    if (sdslen(o->ptr) > sizeof (buf) - 1)
        goto invalid;
    memcpy(buf, o->ptr, sdslen(o->ptr) + 1);
    if (strict && (buf[0] == '-' || buf[0] == '+') && buf[1] == '\x00')
        goto invalid;
    if (buf[0] == '-' && buf[1] == '\x00') {
        id->ms = 0;
        id->seq = 0;
        return 0;
    } else if (buf[0] == '+' && buf[1] == '\x00') {
        id->ms = (18446744073709551615UL);
        id->seq = (18446744073709551615UL);
        return 0;
    }
    unsigned long long ms, seq;
    char *dot = strchr(buf, '-');
    if (dot)
        *dot = '\x00';
    if (string2ull(buf, &ms) == 0)
        goto invalid;
    if (dot) {
        size_t seqlen = strlen(dot + 1);
        if (seq_given != ((void *)0) && seqlen == 1 && *(dot + 1) == '*') {
            seq = 0;
        } else if (string2ull(dot + 1, &seq) == 0) {
            goto invalid;
        }
    } else {
        seq = missing_seq;
    }
    id->ms = ms;
    id->seq = seq;
    return 0;
  invalid:
    ;
    return -1;
}
extern int streamParseStrictIDOrReply (client *c, robj *o, streamID *id, uint64_t missing_seq, int *seq_given){
    return streamGenericParseIDOrReply(c, o, id, missing_seq, 1, seq_given);
}
extern void xreadCommand (client *c){
    long long timeout = -1;
    long long count = 0;
    int streams_count = 0;
    int streams_arg = 0;
    int noack = 0;
    streamID static_ids[8];
    streamID *ids = static_ids;
    streamCG **groups = ((void *)0);
    int xreadgroup = sdslen(c->argv[0]->ptr) == 10;
    robj *groupname = ((void *)0);
    robj *consumername = ((void *)0);
    for (int i = 1; i < c->argc; i++) {
        int moreargs = c->argc - i - 1;
        char *o = c->argv[i]->ptr;
        if (!strcasecmp(o, "BLOCK") && moreargs) {
            i++;
            if (getTimeoutFromObjectOrReply(c, c->argv[i], &timeout, 1) != 0)
                return;
        } else if (!strcasecmp(o, "COUNT") && moreargs) {
            i++;
            if (getLongLongFromObjectOrReply(c, c->argv[i], &count, ((void *)0)) != 0)
                return;
            if (count < 0)
                count = 0;
        } else if (!strcasecmp(o, "STREAMS") && moreargs) {
            streams_arg = i + 1;
            streams_count = (c->argc - streams_arg);
            if ((streams_count % 2) != 0) {
                const char *symbol = xreadgroup ? "ID or '>'" : "ID, '+', or '$'";
                return;
            }
            streams_count /= 2;
            break;
        } else if (!strcasecmp(o, "GROUP") && moreargs >= 2) {
            if (!xreadgroup) {
                ;
                return;
            }
            groupname = c->argv[i + 1];
            consumername = c->argv[i + 2];
            i += 2;
        } else if (!strcasecmp(o, "NOACK")) {
            if (!xreadgroup) {
                ;
                return;
            }
            noack = 1;
        } else {
            ;
        }
    }
    if (streams_arg == 0) {
        ;
        return;
    }
    if (xreadgroup && groupname == ((void *)0)) {
        ;
        return;
    }
    if (streams_count > 8)
        ids = zmalloc(sizeof(streamID) * streams_count);
    if (groupname)
        groups = zmalloc(sizeof(streamCG *) * streams_count);
    for (int i = streams_arg + streams_count; i < c->argc; i++) {
        int id_idx = i - streams_arg - streams_count;
        robj *key = c->argv[i - streams_count];
        kvobj *o = lookupKeyRead(c->db, key);
        if (checkType(c, o, 6))
            goto cleanup;
        streamCG *group = ((void *)0);
        if (groupname) {
            if (o == ((void *)0) || (group = streamLookupCG(o->ptr, groupname->ptr)) == ((void *)0)) {
                ;
                goto cleanup;
            }
            groups[id_idx] = group;
        }
        if (strcmp(c->argv[i]->ptr, "$") == 0) {
            if (xreadgroup) {
                ;
                goto cleanup;
            }
            if (o) {
                stream *s = o->ptr;
                ids[id_idx] = s->last_id;
            } else {
                ids[id_idx].ms = 0;
                ids[id_idx].seq = 0;
            }
            continue;
        } else if (strcmp(c->argv[i]->ptr, "+") == 0) {
            if (xreadgroup) {
                ;
                goto cleanup;
            }
            if (o && ((stream *)o->ptr)->length) {
                stream *s = o->ptr;
                streamLastValidID(s, &ids[id_idx]);
                streamDecrID(&ids[id_idx]);
            } else {
                ids[id_idx].ms = 0;
                ids[id_idx].seq = 0;
            }
            continue;
        } else if (strcmp(c->argv[i]->ptr, ">") == 0) {
            if (!xreadgroup) {
                ;
                goto cleanup;
            }
            ids[id_idx].ms = (18446744073709551615UL);
            ids[id_idx].seq = (18446744073709551615UL);
            continue;
        }
        if (streamParseStrictIDOrReply(c, c->argv[i], ids + id_idx, 0, ((void *)0)) != 0)
            goto cleanup;
    }
    size_t arraylen = 0;
    void *arraylen_ptr = ((void *)0);
    for (int i = 0; i < streams_count; i++) {
        kvobj *o = lookupKeyRead(c->db, c->argv[streams_arg + i]);
        if (o == ((void *)0))
            continue;
        stream *s = o->ptr;
        streamID *gt = ids + i;
        int serve_synchronously = 0;
        int serve_history = 0;
        streamConsumer *consumer = ((void *)0);
        streamPropInfo spi = {c->argv[streams_arg + i], groupname};
        if (groups) {
            if (gt->ms != (18446744073709551615UL) || gt->seq != (18446744073709551615UL)) {
                serve_synchronously = 1;
                serve_history = 1;
            } else if (s->length) {
                streamID maxid, *last = &groups[i]->last_id;
                streamLastValidID(s, &maxid);
                if (streamCompareID(&maxid, last) > 0) {
                    serve_synchronously = 1;
                    *gt = *last;
                }
            }
            consumer = streamLookupConsumer(groups[i], consumername->ptr);
            if (consumer == ((void *)0)) {
                consumer = streamCreateConsumer(groups[i], consumername->ptr, c->argv[streams_arg + i], c->db->id, 0);
            }
            consumer->seen_time = commandTimeSnapshot();
        } else if (s->length) {
            streamID maxid;
            streamLastValidID(s, &maxid);
            if (streamCompareID(&maxid, gt) > 0) {
                serve_synchronously = 1;
            }
        }
        if (serve_synchronously) {
            arraylen++;
            if (arraylen == 1)
                arraylen_ptr = addReplyDeferredLen(c);
            streamID start = *gt;
            streamIncrID(&start);
            int flags = 0;
            unsigned long propCount = 0;
            if (noack)
                flags |= (1 << 0);
            if (serve_history)
                flags |= (1 << 2);
            streamReplyWithRange(c, s, &start, ((void *)0), count, 0, groups ? groups[i] : ((void *)0), consumer, flags, &spi, &propCount);
            if (propCount)
                server.dirty++;
        }
    }
    if (arraylen) {
        ;
        goto cleanup;
    }
    if (timeout != -1) {
        if (c->flags & (1ULL << 41)) {
            ;
            goto cleanup;
        }
        for (int id_idx = 0; id_idx < streams_count; id_idx++) {
            int arg_idx = id_idx + streams_arg + streams_count;
            if (strcmp(c->argv[arg_idx]->ptr, "$") == 0) {
                robj *argv_streamid = createObjectFromStreamID(&ids[id_idx]);
            }
        }
        ;
        goto cleanup;
    }
    ;
  cleanup:
    ;
}
extern void streamUpdateCGroupLastId (stream *s, streamCG *cg, streamID *id){
    if (s->min_cgroup_last_id_valid && (streamCompareID(&cg->last_id, &s->min_cgroup_last_id) == 0 || streamCompareID(id, &s->min_cgroup_last_id) < 0)) {
        s->min_cgroup_last_id_valid = 0;
    }
    ;
}
extern listNode * streamLinkCGroupToEntry (stream *s, streamCG *cg, unsigned char *key){
    list *cglist;
    if (!s->cgroups_ref)
        s->cgroups_ref = raxNew();
    if (!raxFind(s->cgroups_ref, key, sizeof(streamID), (void **)&cglist)) {
        cglist = listCreate();
        (__builtin_expect(!!(raxInsert(s->cgroups_ref, key, sizeof(streamID), cglist, ((void *)0))), 1) ? (void)0 : (_serverAssert("raxInsert(s->cgroups_ref, key, sizeof(streamID), cglist, NULL)", "t_stream_InstSlice.c", 1376) , abort()));
    }
    ;
    return ((cglist)->tail);
}
extern streamNACK * streamCreateNACK (streamConsumer *consumer){
    streamNACK *nack = zmalloc(sizeof (*nack));
    nack->delivery_time = commandTimeSnapshot();
    nack->delivery_count = 1;
    nack->consumer = consumer;
    nack->cgroup_ref_node = ((void *)0);
    return nack;
}
extern streamCG * streamLookupCG (stream *s, sds groupname){
    if (s->cgroups == ((void *)0))
        return ((void *)0);
    void *cg = ((void *)0);
    raxFind(s->cgroups, (unsigned char *)groupname, sdslen(groupname), &cg);
    return cg;
}
extern streamConsumer * streamCreateConsumer (streamCG *cg, sds name, robj *key, int dbid, int flags){
    if (cg == ((void *)0))
        return ((void *)0);
    int notify = !(flags & (1 << 0));
    int dirty = !(flags & (1 << 1));
    streamConsumer *consumer = zmalloc(sizeof (*consumer));
    int success = raxTryInsert(cg->consumers, (unsigned char *)name, sdslen(name), consumer, ((void *)0));
    if (!success) {
        ;
        return ((void *)0);
    }
    consumer->name = sdsdup(name);
    consumer->pel = raxNew();
    consumer->active_time = -1;
    consumer->seen_time = commandTimeSnapshot();
    if (dirty)
        server.dirty++;
    return consumer;
}
extern streamConsumer * streamLookupConsumer (streamCG *cg, sds name){
    if (cg == ((void *)0))
        return ((void *)0);
    void *consumer = ((void *)0);
    raxFind(cg->consumers, (unsigned char *)name, sdslen(name), &consumer);
    return consumer;
}
