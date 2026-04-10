extern int lpStringToInt64 (const char *s, unsigned long slen, int64_t *value){
    const char *p = s;
    unsigned long plen = 0;
    int negative = 0;
    uint64_t v;
    if (slen == 0 || slen >= 21)
        return 0;
    if (slen == 1 && p[0] == '0') {
        if (value != ((void *)0))
            *value = 0;
        return 1;
    }
    if (p[0] == '-') {
        negative = 1;
        p++;
        plen++;
        if (plen == slen)
            return 0;
    }
    if (p[0] >= '1' && p[0] <= '9') {
        v = p[0] - '0';
        p++;
        plen++;
    } else {
        return 0;
    }
    while (plen < slen && p[0] >= '0' && p[0] <= '9')
        {
            if (v > ((18446744073709551615UL) / 10))
                return 0;
            v *= 10;
            if (v > ((18446744073709551615UL) - (p[0] - '0')))
                return 0;
            v += p[0] - '0';
            p++;
            plen++;
        }
    if (plen < slen)
        return 0;
    if (negative) {
        if (v > ((uint64_t)(-((-9223372036854775807L - 1) + 1)) + 1))
            return 0;
        if (value != ((void *)0))
            *value = -v;
    } else {
        if (v > (9223372036854775807L))
            return 0;
        if (value != ((void *)0))
            *value = v;
    }
    return 1;
}


static inline void lpEncodeIntegerGetType (int64_t v, unsigned char *intenc, uint64_t *enclen){
    if (v >= 0 && v <= 127) {
        if (intenc != ((void *)0))
            intenc[0] = v;
        if (enclen != ((void *)0))
            *enclen = 1;
    } else if (v >= -4096 && v <= 4095) {
        if (v < 0)
            v = ((int64_t)1 << 13) + v;
        if (intenc != ((void *)0)) {
            intenc[0] = (v >> 8) | 192;
            intenc[1] = v & 255;
        }
        if (enclen != ((void *)0))
            *enclen = 2;
    } else if (v >= -32768 && v <= 32767) {
        if (v < 0)
            v = ((int64_t)1 << 16) + v;
        if (intenc != ((void *)0)) {
            intenc[0] = 241;
            intenc[1] = v & 255;
            intenc[2] = v >> 8;
        }
        if (enclen != ((void *)0))
            *enclen = 3;
    } else if (v >= -8388608 && v <= 8388607) {
        if (v < 0)
            v = ((int64_t)1 << 24) + v;
        if (intenc != ((void *)0)) {
            intenc[0] = 242;
            intenc[1] = v & 255;
            intenc[2] = (v >> 8) & 255;
            intenc[3] = v >> 16;
        }
        if (enclen != ((void *)0))
            *enclen = 4;
    } else if (v >= -2147483648L && v <= 2147483647) {
        if (v < 0)
            v = ((int64_t)1 << 32) + v;
        if (intenc != ((void *)0)) {
            intenc[0] = 243;
            intenc[1] = v & 255;
            intenc[2] = (v >> 8) & 255;
            intenc[3] = (v >> 16) & 255;
            intenc[4] = v >> 24;
        }
        if (enclen != ((void *)0))
            *enclen = 5;
    } else {
        uint64_t uv = v;
        if (intenc != ((void *)0)) {
            intenc[0] = 244;
            intenc[1] = uv & 255;
            intenc[2] = (uv >> 8) & 255;
            intenc[3] = (uv >> 16) & 255;
            intenc[4] = (uv >> 24) & 255;
            intenc[5] = (uv >> 32) & 255;
            intenc[6] = (uv >> 40) & 255;
            intenc[7] = (uv >> 48) & 255;
            intenc[8] = uv >> 56;
        }
        if (enclen != ((void *)0))
            *enclen = 9;
    }
}


static inline int lpEncodeGetType (unsigned char *ele, uint32_t size, unsigned char *intenc, uint64_t *enclen){
    int64_t v;
    if (lpStringToInt64((const char *)ele, size, &v)) {
        lpEncodeIntegerGetType(v, intenc, enclen);
        return 0;
    } else {
        if (size < 64) {
            *enclen = 1 + size;
        } else if (size < 4096) {
            *enclen = 2 + size;
        } else
            *enclen = 5 + (uint64_t)size;
        return 1;
    }
}


static inline unsigned long lpEncodeBacklen (unsigned char *buf, uint64_t l){
    if (l <= 127) {
        if (buf)
            buf[0] = l;
        return 1;
    } else if (l < 16383) {
        if (buf) {
            buf[0] = l >> 7;
            buf[1] = (l & 127) | 128;
        }
        return 2;
    } else if (l < 2097151) {
        if (buf) {
            buf[0] = l >> 14;
            buf[1] = ((l >> 7) & 127) | 128;
            buf[2] = (l & 127) | 128;
        }
        return 3;
    } else if (l < 268435455) {
        if (buf) {
            buf[0] = l >> 21;
            buf[1] = ((l >> 14) & 127) | 128;
            buf[2] = ((l >> 7) & 127) | 128;
            buf[3] = (l & 127) | 128;
        }
        return 4;
    } else {
        if (buf) {
            buf[0] = l >> 28;
            buf[1] = ((l >> 21) & 127) | 128;
            buf[2] = ((l >> 14) & 127) | 128;
            buf[3] = ((l >> 7) & 127) | 128;
            buf[4] = (l & 127) | 128;
        }
        return 5;
    }
}


static inline unsigned long lpEncodeBacklenBytes (uint64_t l){
    if (l <= 127) {
        return 1;
    } else if (l < 16383) {
        return 2;
    } else if (l < 2097151) {
        return 3;
    } else if (l < 268435455) {
        return 4;
    } else {
        return 5;
    }
}


static inline void lpEncodeString (unsigned char *buf, unsigned char *s, uint32_t len){
    if (len < 64) {
        buf[0] = len | 128;
        ;
    } else if (len < 4096) {
        buf[0] = (len >> 8) | 224;
        buf[1] = len & 255;
        memcpy(buf + 2, s, len);
    } else {
        buf[0] = 240;
        buf[1] = len & 255;
        buf[2] = (len >> 8) & 255;
        buf[3] = (len >> 16) & 255;
        buf[4] = (len >> 24) & 255;
        ;
    }
}


static inline uint32_t lpCurrentEncodedSizeUnsafe (unsigned char *p){
    if ((((p[0]) & 128) == 0))
        return 1;
    if ((((p[0]) & 192) == 128))
        return 1 + ((p)[0] & 63);
    if ((((p[0]) & 224) == 192))
        return 2;
    if ((((p[0]) & 255) == 241))
        return 3;
    if ((((p[0]) & 255) == 242))
        return 4;
    if ((((p[0]) & 255) == 243))
        return 5;
    if ((((p[0]) & 255) == 244))
        return 9;
    if ((((p[0]) & 240) == 224))
        return 2 + ((((p)[0] & 15) << 8) | (p)[1]);
    if ((((p[0]) & 255) == 240))
        return 5 + (((uint32_t)(p)[1] << 0) | ((uint32_t)(p)[2] << 8) | ((uint32_t)(p)[3] << 16) | ((uint32_t)(p)[4] << 24));
    if (p[0] == 255)
        return 1;
    return 0;
}


static inline unsigned char * lpSkip (unsigned char *p){
    unsigned long entrylen = lpCurrentEncodedSizeUnsafe(p);
    entrylen += lpEncodeBacklenBytes(entrylen);
    p += entrylen;
    return p;
}


extern unsigned char * lpBatchInsert (unsigned char *lp, unsigned char *p, int where, listpackEntry *entries, unsigned int len, unsigned char **newp){
    (__builtin_expect(!!((where == 0 || where == 1)), 1) ? (void)0 : (_serverAssert("where == LP_BEFORE || where == LP_AFTER", "listpack_InstSlice.c", 614) , abort()));
    (__builtin_expect(!!((entries != ((void *)0) && len > 0)), 1) ? (void)0 : (_serverAssert("entries != NULL && len > 0", "listpack_InstSlice.c", 615) , abort()));
    struct listpackInsertEntry {
        int enctype;
        uint64_t enclen;
        unsigned char intenc[9];
        unsigned char backlen[5];
        unsigned long backlen_size;
    };
    uint64_t addedlen = 0;
    struct listpackInsertEntry tmp[3];
    struct listpackInsertEntry *enc = tmp;
    if (len > sizeof (tmp) / sizeof(struct listpackInsertEntry)) {
        enc = zmalloc(len * sizeof(struct listpackInsertEntry));
    }
    if (where == 1) {
        p = lpSkip(p);
        where = 0;
        do {
            (__builtin_expect(!!(((p) >= (lp) + 6 && (p) < (lp) + (((uint32_t)((lp))[0] << 0) | ((uint32_t)((lp))[1] << 8) | ((uint32_t)((lp))[2] << 16) | ((uint32_t)((lp))[3] << 24)))), 1) ? (void)0 : (_serverAssert("(p) >= (lp)+LP_HDR_SIZE && (p) < (lp)+lpGetTotalBytes((lp))", "listpack_InstSlice.c", 641) , abort()));
        } while (0);
    }
    for (unsigned int i = 0; i < len; i++) {
        listpackEntry *e = &entries[i];
        if (e->sval) {
            enc[i].enctype = lpEncodeGetType(e->sval, e->slen, enc[i].intenc, &enc[i].enclen);
        } else {
            enc[i].enctype = 0;
            lpEncodeIntegerGetType(e->lval, enc[i].intenc, &enc[i].enclen);
        }
        addedlen += enc[i].enclen;
        enc[i].backlen_size = lpEncodeBacklen(enc[i].backlen, enc[i].enclen);
        addedlen += enc[i].backlen_size;
    }
    uint64_t old_listpack_bytes = (((uint32_t)(lp)[0] << 0) | ((uint32_t)(lp)[1] << 8) | ((uint32_t)(lp)[2] << 16) | ((uint32_t)(lp)[3] << 24));
    uint64_t new_listpack_bytes = old_listpack_bytes + addedlen;
    if (new_listpack_bytes > (4294967295U))
        return ((void *)0);
    unsigned long poff = p - lp;
    unsigned char *dst = lp + poff;
    if (new_listpack_bytes > old_listpack_bytes && new_listpack_bytes > je_malloc_usable_size(lp)) {
        if ((lp = zrealloc_usable(lp, new_listpack_bytes, ((void *)0))) == ((void *)0))
            return ((void *)0);
        dst = lp + poff;
    }
    ;
    for (unsigned int i = 0; i < len; i++) {
        listpackEntry *ent = &entries[i];
        ;
        if (enc[i].enctype == 0) {
            ;
        } else
            lpEncodeString(dst, ent->sval, ent->slen);
        dst += enc[i].enclen;
        ;
        dst += enc[i].backlen_size;
    }
    uint32_t num_elements = (((uint32_t)(lp)[4] << 0) | ((uint32_t)(lp)[5] << 8));
    ;
    ;
    return lp;
}


extern unsigned char * lpBatchAppend (unsigned char *lp, listpackEntry *entries, unsigned long len){
    uint64_t listpack_bytes = (((uint32_t)(lp)[0] << 0) | ((uint32_t)(lp)[1] << 8) | ((uint32_t)(lp)[2] << 16) | ((uint32_t)(lp)[3] << 24));
    unsigned char *eofptr = lp + listpack_bytes - 1;
    return lpBatchInsert(lp, eofptr, 0, entries, len, ((void *)0));
}


