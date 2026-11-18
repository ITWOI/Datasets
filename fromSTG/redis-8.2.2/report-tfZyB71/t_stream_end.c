#include "header_func.h"
#include "sds.h"
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
extern int streamParseIDOrReply (client *c, robj *o, streamID *id, uint64_t missing_seq){
    return streamGenericParseIDOrReply(c, o, id, missing_seq, 0, ((void *)0));
}
extern int streamParseStrictIDOrReply (client *c, robj *o, streamID *id, uint64_t missing_seq, int *seq_given){
    return streamGenericParseIDOrReply(c, o, id, missing_seq, 1, seq_given);
}
extern void streamUpdateCGroupLastId (stream *s, streamCG *cg, streamID *id){
    if (s->min_cgroup_last_id_valid && (streamCompareID(&cg->last_id, &s->min_cgroup_last_id) == 0 || streamCompareID(id, &s->min_cgroup_last_id) < 0)) {
        ;
    }
    ;
}
extern streamCG * streamCreateCG (stream *s, char *name, size_t namelen, streamID *id, long long entries_read){
    if (s->cgroups == ((void *)0))
        s->cgroups = raxNew();
    if (raxFind(s->cgroups, (unsigned char *)name, namelen, ((void *)0)))
        return ((void *)0);
    streamCG *cg = zmalloc(sizeof (*cg));
    cg->pel = raxNew();
    cg->consumers = raxNew();
    cg->last_id.ms = 0;
    cg->last_id.seq = 0;
    streamUpdateCGroupLastId(s, cg, id);
    return cg;
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
    int notify;
    int dirty;
    streamConsumer *consumer;
    int success = raxTryInsert(cg->consumers, (unsigned char *)name, sdslen(name), consumer, ((void *)0));
    return consumer;
}
extern streamConsumer * streamLookupConsumer (streamCG *cg, sds name){
    if (cg == ((void *)0))
        return ((void *)0);
    void *consumer = ((void *)0);
    raxFind(cg->consumers, (unsigned char *)name, sdslen(name), &consumer);
    return consumer;
}
extern void streamDelConsumer (stream *s, streamCG *cg, streamConsumer *consumer){
    raxIterator ri;
    raxRemove(cg->consumers, (unsigned char *)consumer->name, sdslen(consumer->name), ((void *)0));
}
extern void xgroupCommand (client *c){
    stream *s = ((void *)0);
    sds grpname = ((void *)0);
    streamCG *cg = ((void *)0);
    char *opt = c->argv[1]->ptr;
    int mkstream = 0;
    long long entries_read = -1;
    robj *o;
    if (c->argc >= 4) {
        int i = 5;
        int create_subcmd = !strcasecmp(opt, "CREATE");
        int setid_subcmd = !strcasecmp(opt, "SETID");
        while (i < c->argc)
            {
                if (create_subcmd && !strcasecmp(c->argv[i]->ptr, "MKSTREAM")) {
                    mkstream = 1;
                    i++;
                } else if ((create_subcmd || setid_subcmd) && !strcasecmp(c->argv[i]->ptr, "ENTRIESREAD") && i + 1 < c->argc) {
                    if (getLongLongFromObjectOrReply(c, c->argv[i + 1], &entries_read, ((void *)0)) != 0)
                        return;
                    if (entries_read < 0 && entries_read != -1) {
                        ;
                        return;
                    }
                    i += 2;
                } else {
                    ;
                }
            }
        o = lookupKeyWrite(c->db, c->argv[2]);
        if (o) {
            if (checkType(c, o, 6))
                return;
            s = o->ptr;
        }
        grpname = c->argv[3]->ptr;
    }
    if (c->argc >= 4 && !mkstream) {
        if (s == ((void *)0)) {
            ;
            return;
        }
        if ((cg = streamLookupCG(s, grpname)) == ((void *)0) && (!strcasecmp(opt, "SETID") || !strcasecmp(opt, "CREATECONSUMER") || !strcasecmp(opt, "DELCONSUMER"))) {
            ;
            return;
        }
    }
    if (c->argc == 2 && !strcasecmp(opt, "HELP")) {
        const char *help[] = {"CREATE <key> <groupname> <id|$> [option]", "    Create a new consumer group. Options are:", "    * MKSTREAM", "      Create the empty stream if it does not exist.", "    * ENTRIESREAD entries_read", "      Set the group's entries_read counter (internal use).", "CREATECONSUMER <key> <groupname> <consumer>", "    Create a new consumer in the specified group.", "DELCONSUMER <key> <groupname> <consumer>", "    Remove the specified consumer.", "DESTROY <key> <groupname>", "    Remove the specified group.", "SETID <key> <groupname> <id|$> [ENTRIESREAD entries_read]", "    Set the current group ID and entries_read counter.", ((void *)0)};
    } else if (!strcasecmp(opt, "CREATE") && (c->argc >= 5 && c->argc <= 8)) {
        streamID id;
        if (!strcmp(c->argv[4]->ptr, "$")) {
            if (s) {
                id = s->last_id;
            } else {
                id.ms = 0;
                id.seq = 0;
            }
        } else if (streamParseStrictIDOrReply(c, c->argv[4], &id, 0, ((void *)0)) != 0) {
            return;
        }
        if (s == ((void *)0)) {
            (__builtin_expect(!!(mkstream), 1) ? (void)0 : (_serverAssert("mkstream", "t_stream_InstSlice.c", 803) , abort()));
            o = createStreamObject();
            s = o->ptr;
        }
        if (entries_read != -1 && (uint64_t)entries_read > s->entries_added) {
            entries_read = s->entries_added;
        }
        streamCG *cg = streamCreateCG(s, grpname, sdslen(grpname), &id, entries_read);
    } else if (!strcasecmp(opt, "SETID") && (c->argc == 5 || c->argc == 7)) {
        streamID id;
        if (!strcmp(c->argv[4]->ptr, "$")) {
            ;
        } else if (streamParseIDOrReply(c, c->argv[4], &id, 0) != 0) {
            return;
        }
        streamUpdateCGroupLastId(s, cg, &id);
    } else if (!strcasecmp(opt, "DESTROY") && c->argc == 4) {
        if (cg) {
            raxRemove(s->cgroups, (unsigned char *)grpname, sdslen(grpname), ((void *)0));
        } else {
            ;
        }
    } else if (!strcasecmp(opt, "CREATECONSUMER") && c->argc == 5) {
        streamConsumer *created = streamCreateConsumer(cg, c->argv[4]->ptr, c->argv[2], c->db->id, 0);
    } else if (!strcasecmp(opt, "DELCONSUMER") && c->argc == 5) {
        long long pending = 0;
        streamConsumer *consumer = streamLookupConsumer(cg, c->argv[4]->ptr);
        if (consumer) {
            ;
            streamDelConsumer(s, cg, consumer);
        }
        ;
    } else {
        ;
    }
}
