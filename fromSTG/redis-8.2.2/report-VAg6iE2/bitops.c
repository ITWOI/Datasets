extern unsigned char * getObjectReadOnlyString (robj *o, long *len, char *llbuf){
    (__builtin_expect(!!(!o || o->type == 0), 1) ? (void)0 : (_serverAssert("!o || o->type == OBJ_STRING", "bitops_InstSlice.c", 172) , abort()));
    unsigned char *p = ((void *)0);
    if (o && o->encoding == 1) {
        p = (unsigned char *)llbuf;
        if (len)
            *len = ll2string(llbuf, 21, (long)o->ptr);
    } else if (o) {
        p = (unsigned char *)o->ptr;
        if (len)
            *len = sdslen(o->ptr);
    } else {
        if (len)
            *len = 0;
    }
    return p;
}


extern void bitposCommand (client *c){
    kvobj *o;
    long long start, end;
    long bit, strlen;
    unsigned char *p;
    char llbuf[21];
    int isbit = 0, end_given = 0;
    unsigned char first_byte_neg_mask = 0, last_byte_neg_mask = 0;
    if (getLongFromObjectOrReply(c, c->argv[2], &bit, ((void *)0)) != 0)
        return;
    if (bit != 0 && bit != 1) {
        ;
        return;
    }
    if (c->argc == 4 || c->argc == 5 || c->argc == 6) {
        if (getLongLongFromObjectOrReply(c, c->argv[3], &start, ((void *)0)) != 0)
            return;
        if (c->argc == 6) {
            if (!strcasecmp(c->argv[5]->ptr, "bit")) {
                isbit = 1;
            } else if (!strcasecmp(c->argv[5]->ptr, "byte")) {
                isbit = 0;
            } else {
                ;
            }
        }
        if (c->argc >= 5) {
            if (getLongLongFromObjectOrReply(c, c->argv[4], &end, ((void *)0)) != 0)
                return;
            end_given = 1;
        }
        o = lookupKeyRead(c->db, c->argv[1]);
        if (checkType(c, o, 0))
            return;
        p = getObjectReadOnlyString(o, &strlen, llbuf);
        long long totlen = strlen;
        (__builtin_expect(!!(totlen <= 9223372036854775807LL >> 3), 1) ? (void)0 : (_serverAssert("totlen <= LLONG_MAX >> 3", "bitops_InstSlice.c", 258) , abort()));
        if (c->argc < 5) {
            if (isbit) {
                end = (totlen << 3) + 7;
            } else
                end = totlen - 1;
        }
        if (isbit)
            totlen <<= 3;
        if (start < 0)
            start = totlen + start;
        if (end < 0)
            end = totlen + end;
        ;
        ;
        ;
    } else if (c->argc == 3) {
        o = lookupKeyRead(c->db, c->argv[1]);
        if (checkType(c, o, 0))
            return;
        p = getObjectReadOnlyString(o, &strlen, llbuf);
        ;
        ;
    } else {
        ;
    }
}


