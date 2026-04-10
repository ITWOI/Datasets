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


static inline uint64_t lpDecodeBacklen (unsigned char *p){
    uint64_t val = 0;
    uint64_t shift = 0;
    do {
        val |= (uint64_t)(p[0] & 127) << shift;
        if (!(p[0] & 128))
            break;
        ;
        shift += 7;
        p--;
        if (shift > 28)
            return (18446744073709551615UL);
    } while (1);
    return val;
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


static inline uint32_t lpCurrentEncodedSizeBytes (const unsigned char encoding){
    if ((((encoding) & 128) == 0))
        return 1;
    if ((((encoding) & 192) == 128))
        return 1;
    if ((((encoding) & 224) == 192))
        return 1;
    if ((((encoding) & 255) == 241))
        return 1;
    if ((((encoding) & 255) == 242))
        return 1;
    if ((((encoding) & 255) == 243))
        return 1;
    if ((((encoding) & 255) == 244))
        return 1;
    if ((((encoding) & 240) == 224))
        return 2;
    if ((((encoding) & 255) == 240))
        return 5;
    if (encoding == 255)
        return 1;
    return 0;
}


static inline unsigned char * lpSkip (unsigned char *p){
    unsigned long entrylen = lpCurrentEncodedSizeUnsafe(p);
    entrylen += lpEncodeBacklenBytes(entrylen);
    p += entrylen;
    return p;
}


extern unsigned char * lpNext (unsigned char *lp, unsigned char *p){
    (__builtin_expect(!!((p)), 1) ? (void)0 : (_serverAssert("p", "listpack_InstSlice.c", 287) , abort()));
    p = lpSkip(p);
    if (p[0] == 255)
        return ((void *)0);
    lpAssertValidEntry(lp, lpBytes(lp), p);
    return p;
}


extern unsigned char * lpFirst (unsigned char *lp){
    unsigned char *p = lp + 6;
    if (p[0] == 255)
        return ((void *)0);
    lpAssertValidEntry(lp, lpBytes(lp), p);
    return p;
}


extern unsigned long lpLength (unsigned char *lp){
    uint32_t numele = (((uint32_t)(lp)[4] << 0) | ((uint32_t)(lp)[5] << 8));
    if (numele != (65535))
        return numele;
    uint32_t count = 0;
    unsigned char *p = lpFirst(lp);
    while (p)
        {
            count++;
            p = lpNext(lp, p);
        }
    if (count < (65535))
        do {
            (lp)[4] = (count) & 255;
            (lp)[5] = ((count) >> 8) & 255;
        } while (0);
    return count;
}


static inline unsigned char * lpGetWithBuf (unsigned char *p, int64_t *count, unsigned char *intbuf){
    int64_t val;
    uint64_t uval, negstart, negmax;
    (__builtin_expect(!!((p)), 1) ? (void)0 : (_serverAssert("p", "listpack_InstSlice.c", 381) , abort()));
    const unsigned char encoding = p[0];
    if ((((encoding) & 192) == 128)) {
        *count = ((p)[0] & 63);
        return p + 1;
    }
    if ((((encoding) & 240) == 224)) {
        *count = ((((p)[0] & 15) << 8) | (p)[1]);
        return p + 2;
    }
    if ((((encoding) & 255) == 240)) {
        *count = (((uint32_t)(p)[1] << 0) | ((uint32_t)(p)[2] << 8) | ((uint32_t)(p)[3] << 16) | ((uint32_t)(p)[4] << 24));
        return p + 5;
    }
    if ((((encoding) & 128) == 0)) {
        negstart = (18446744073709551615UL);
        negmax = 0;
        uval = encoding & 127;
    } else if ((((encoding) & 224) == 192)) {
        uval = ((encoding & 31) << 8) | p[1];
        negstart = (uint64_t)1 << 12;
        negmax = 8191;
    } else if ((((encoding) & 255) == 241)) {
        uval = (uint64_t)p[1] | (uint64_t)p[2] << 8;
        negstart = (uint64_t)1 << 15;
        negmax = (65535);
    } else if ((((encoding) & 255) == 242)) {
        uval = (uint64_t)p[1] | (uint64_t)p[2] << 8 | (uint64_t)p[3] << 16;
        negstart = (uint64_t)1 << 23;
        negmax = (4294967295U) >> 8;
    } else if ((((encoding) & 255) == 243)) {
        uval = (uint64_t)p[1] | (uint64_t)p[2] << 8 | (uint64_t)p[3] << 16 | (uint64_t)p[4] << 24;
        negstart = (uint64_t)1 << 31;
        negmax = (4294967295U);
    } else if ((((encoding) & 255) == 244)) {
        uval = (uint64_t)p[1] | (uint64_t)p[2] << 8 | (uint64_t)p[3] << 16 | (uint64_t)p[4] << 24 | (uint64_t)p[5] << 32 | (uint64_t)p[6] << 40 | (uint64_t)p[7] << 48 | (uint64_t)p[8] << 56;
        negstart = (uint64_t)1 << 63;
        negmax = (18446744073709551615UL);
    } else {
        uval = 12345678900000000ULL + encoding;
        negstart = (18446744073709551615UL);
        negmax = 0;
    }
    if (uval >= negstart) {
        uval = negmax - uval;
        val = uval;
        val = -val - 1;
    } else {
        val = uval;
    }
    if (intbuf) {
        *count = ll2string((char *)intbuf, 21, (long long)val);
        return intbuf;
    } else {
        *count = val;
        return ((void *)0);
    }
}


extern unsigned char * lpGet (unsigned char *p, int64_t *count, unsigned char *intbuf){
    return lpGetWithBuf(p, count, intbuf);
}


extern size_t lpBytes (unsigned char *lp){
    return (((uint32_t)(lp)[0] << 0) | ((uint32_t)(lp)[1] << 8) | ((uint32_t)(lp)[2] << 16) | ((uint32_t)(lp)[3] << 24));
}


extern int lpValidateNext (unsigned char *lp, unsigned char **pp, size_t lpbytes){
    unsigned char *p = *pp;
    if (!p)
        return 0;
    if (((p) < lp + 6 || (p) > lp + lpbytes - 1))
        return 0;
    if (*p == 255) {
        ;
        return 1;
    }
    uint32_t lenbytes = lpCurrentEncodedSizeBytes(p[0]);
    if (!lenbytes)
        return 0;
    if (((p + lenbytes) < lp + 6 || (p + lenbytes) > lp + lpbytes - 1))
        return 0;
    unsigned long entrylen = lpCurrentEncodedSizeUnsafe(p);
    unsigned long encodedBacklen = lpEncodeBacklenBytes(entrylen);
    entrylen += encodedBacklen;
    if (((p + entrylen) < lp + 6 || (p + entrylen) > lp + lpbytes - 1))
        return 0;
    p += entrylen;
    uint64_t prevlen = lpDecodeBacklen(p - 1);
    if (prevlen + encodedBacklen != entrylen)
        return 0;
    ;
    return 1;
}


static inline void lpAssertValidEntry (unsigned char *lp, size_t lpbytes, unsigned char *p){
    (__builtin_expect(!!((lpValidateNext(lp, &p, lpbytes))), 1) ? (void)0 : (_serverAssert("lpValidateNext(lp, &p, lpbytes)", "listpack_InstSlice.c", 714) , abort()));
}


extern void lpRepr (unsigned char *lp){
    unsigned char *p, *vstr;
    int64_t vlen;
    unsigned char intbuf[21];
    int index;
    printf("{total bytes %zu} {num entries %lu}\n", lpBytes(lp), lpLength(lp));
    p = lpFirst(lp);
    while (p)
        {
            uint32_t encoded_size_bytes = lpCurrentEncodedSizeBytes(p[0]);
            uint32_t encoded_size = lpCurrentEncodedSizeUnsafe(p);
            unsigned long back_len = lpEncodeBacklenBytes(encoded_size);
            ;
            ;
            for (unsigned int i = 0; i < (encoded_size + back_len); i++) {
                ;
            }
            ;
            vstr = lpGet(p, &vlen, intbuf);
            ;
            if (vlen > 40) {
                if (fwrite(vstr, 40, 1, stdout) == 0)
                    perror("fwrite");
                ;
            } else {
                ;
            }
            ;
            ;
            p = lpNext(lp, p);
        }
    ;
}


