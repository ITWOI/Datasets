#include "header_func.h"
extern zskiplistNode * zslCreateNode (int level, double score, sds ele){
    zskiplistNode *zn = zmalloc(sizeof (*zn) + level * sizeof(struct zskiplistLevel));
    zn->score = score;
    zn->ele = ele;
    return zn;
}
extern zskiplist * zslCreate (){
    int j;
    zskiplist *zsl;
    zsl = zmalloc(sizeof (*zsl));
    zsl->level = 1;
    zsl->length = 0;
    zsl->header = zslCreateNode(32, 0, ((void *)0));
    for (j = 0; j < 32; j++) {
        zsl->header->level[j].forward = ((void *)0);
        zsl->header->level[j].span = 0;
    }
    zsl->header->backward = ((void *)0);
    zsl->tail = ((void *)0);
    return zsl;
}
extern int zslRandomLevel (){
    static const int threshold = 0.25 * 2147483647;
    int level = 1;
    while (random() < threshold)
        level += 1;
    return (level < 32) ? level : 32;
}
extern zskiplistNode * zslInsert (zskiplist *zsl, double score, sds ele){
    zskiplistNode *update[32], *x;
    unsigned long rank[32];
    int i, level;
    (__builtin_expect(!!(!__builtin_isnan(score)), 1) ? (void)0 : (_serverAssert("!isnan(score)", "t_zset_InstSlice.c", 114) , abort()));
    x = zsl->header;
    for (i = zsl->level - 1; i >= 0; i--) {
        rank[i] = i == (zsl->level - 1) ? 0 : rank[i + 1];
        while (x->level[i].forward && (x->level[i].forward->score < score || (x->level[i].forward->score == score && sdscmp(x->level[i].forward->ele, ele) < 0)))
            {
                rank[i] += x->level[i].span;
                x = x->level[i].forward;
            }
        update[i] = x;
    }
    level = zslRandomLevel();
    if (level > zsl->level) {
        for (i = zsl->level; i < level; i++) {
            rank[i] = 0;
            update[i] = zsl->header;
            update[i]->level[i].span = zsl->length;
        }
        zsl->level = level;
    }
    x = zslCreateNode(level, score, ele);
    for (i = 0; i < level; i++) {
        x->level[i].forward = update[i]->level[i].forward;
        update[i]->level[i].forward = x;
        x->level[i].span = update[i]->level[i].span - (rank[0] - rank[i]);
        update[i]->level[i].span = (rank[0] - rank[i]) + 1;
    }
    for (i = level; i < zsl->level; i++) {
        update[i]->level[i].span++;
    }
    x->backward = (update[0] == zsl->header) ? ((void *)0) : update[0];
    if (x->level[0].forward) {
        x->level[0].forward->backward = x;
    } else
        zsl->tail = x;
    zsl->length++;
    return x;
}
extern void zslDeleteNode (zskiplist *zsl, zskiplistNode *x, zskiplistNode **update){
    int i;
    for (i = 0; i < zsl->level; i++) {
        if (update[i]->level[i].forward == x) {
            update[i]->level[i].span += x->level[i].span - 1;
            update[i]->level[i].forward = x->level[i].forward;
        } else {
            update[i]->level[i].span -= 1;
        }
    }
    if (x->level[0].forward) {
        x->level[0].forward->backward = x->backward;
    } else {
        zsl->tail = x->backward;
    }
    while (zsl->level > 1 && zsl->header->level[zsl->level - 1].forward == ((void *)0))
        zsl->level--;
    zsl->length--;
}
extern zskiplistNode * zslUpdateScore (zskiplist *zsl, double curscore, sds ele, double newscore){
    zskiplistNode *update[32], *x;
    int i;
    x = zsl->header;
    for (i = zsl->level - 1; i >= 0; i--) {
        while (x->level[i].forward && (x->level[i].forward->score < curscore || (x->level[i].forward->score == curscore && sdscmp(x->level[i].forward->ele, ele) < 0)))
            {
                x = x->level[i].forward;
            }
        update[i] = x;
    }
    x = x->level[0].forward;
    (__builtin_expect(!!(x && curscore == x->score && sdscmp(x->ele, ele) == 0), 1) ? (void)0 : (_serverAssert("x && curscore == x->score && sdscmp(x->ele,ele) == 0", "t_zset_InstSlice.c", 224) , abort()));
    if ((x->backward == ((void *)0) || x->backward->score < newscore) && (x->level[0].forward == ((void *)0) || x->level[0].forward->score > newscore)) {
        ;
        return x;
    }
    zslDeleteNode(zsl, x, update);
    zskiplistNode *newnode = zslInsert(zsl, newscore, x->ele);
    return newnode;
}
extern double zzlStrtod (unsigned char *vstr, unsigned int vlen){
    char buf[128];
    if (vlen > sizeof (buf) - 1)
        vlen = sizeof (buf) - 1;
    memcpy(buf, vstr, vlen);
    buf[vlen] = '\x00';
    return fast_float_strtod(buf, ((void *)0));
}
extern double zzlGetScore (unsigned char *sptr){
    unsigned char *vstr;
    unsigned int vlen;
    long long vlong;
    double score;
    (__builtin_expect(!!(sptr != ((void *)0)), 1) ? (void)0 : (_serverAssert("sptr != NULL", "t_zset_InstSlice.c", 350) , abort()));
    vstr = lpGetValue(sptr, &vlen, &vlong);
    if (vstr) {
        score = zzlStrtod(vstr, vlen);
    } else {
        score = vlong;
    }
    return score;
}
extern int zzlCompareElements (unsigned char *eptr, unsigned char *cstr, unsigned int clen){
    unsigned char *vstr;
    unsigned int vlen;
    long long vlong;
    unsigned char vbuf[32];
    int minlen, cmp;
    vstr = lpGetValue(eptr, &vlen, &vlong);
    if (vstr == ((void *)0)) {
        vlen = ll2string((char *)vbuf, sizeof (vbuf), vlong);
        vstr = vbuf;
    }
    minlen = (vlen < clen) ? vlen : clen;
    cmp = memcmp(vstr, cstr, minlen);
    if (cmp == 0)
        return vlen - clen;
    return cmp;
}
extern unsigned int zzlLength (unsigned char *zl){
    return lpLength(zl) / 2;
}
extern void zzlNext (unsigned char *zl, unsigned char **eptr, unsigned char **sptr){
    unsigned char *_eptr, *_sptr;
    (__builtin_expect(!!(*eptr != ((void *)0) && *sptr != ((void *)0)), 1) ? (void)0 : (_serverAssert("*eptr != NULL && *sptr != NULL", "t_zset_InstSlice.c", 394) , abort()));
    _eptr = lpNext(zl, *sptr);
    if (_eptr != ((void *)0)) {
        _sptr = lpNext(zl, _eptr);
        (__builtin_expect(!!(_sptr != ((void *)0)), 1) ? (void)0 : (_serverAssert("_sptr != NULL", "t_zset_InstSlice.c", 399) , abort()));
    } else {
        _sptr = ((void *)0);
    }
    *eptr = _eptr;
    *sptr = _sptr;
}
extern unsigned char * zzlFind (unsigned char *lp, sds ele, double *score){
    unsigned char *eptr, *sptr;
    if ((eptr = lpFirst(lp)) == ((void *)0))
        return ((void *)0);
    eptr = lpFind(lp, eptr, (unsigned char *)ele, sdslen(ele), 1);
    if (eptr) {
        sptr = lpNext(lp, eptr);
        (__builtin_expect(!!(sptr != ((void *)0)), 1) ? (void)0 : (_serverAssert("sptr != NULL", "t_zset_InstSlice.c", 448) , abort()));
        if (score != ((void *)0))
            *score = zzlGetScore(sptr);
        return eptr;
    }
    return ((void *)0);
}
extern unsigned char * zzlDelete (unsigned char *zl, unsigned char *eptr){
    return lpDeleteRangeWithEntry(zl, &eptr, 2);
}
extern unsigned char * zzlInsertAt (unsigned char *zl, unsigned char *eptr, sds ele, double score){
    char scorebuf[128];
    int scorelen = 0;
    long long lscore;
    int score_is_long = double2ll(score, &lscore);
    if (!score_is_long)
        scorelen = d2string(scorebuf, sizeof (scorebuf), score);
    listpackEntry entries[2];
    entries[0].sval = (unsigned char *)ele;
    entries[0].slen = sdslen(ele);
    if (score_is_long) {
        entries[1].sval = ((void *)0);
        entries[1].lval = lscore;
    } else {
        entries[1].sval = (unsigned char *)scorebuf;
        entries[1].slen = scorelen;
    }
    if (eptr == ((void *)0)) {
        zl = lpBatchAppend(zl, entries, 2);
    } else
        zl = lpBatchInsert(zl, eptr, 0, entries, 2, ((void *)0));
    return zl;
}
extern unsigned char * zzlInsert (unsigned char *zl, sds ele, double score){
    unsigned char *eptr = lpSeek(zl, 0), *sptr;
    double s;
    while (eptr != ((void *)0))
        {
            sptr = lpNext(zl, eptr);
            (__builtin_expect(!!(sptr != ((void *)0)), 1) ? (void)0 : (_serverAssert("sptr != NULL", "t_zset_InstSlice.c", 499) , abort()));
            s = zzlGetScore(sptr);
            if (s > score) {
                zl = zzlInsertAt(zl, eptr, ele, score);
                break;
            } else if (s == score) {
                if (zzlCompareElements(eptr, (unsigned char *)ele, sdslen(ele)) > 0) {
                    zl = zzlInsertAt(zl, eptr, ele, score);
                    break;
                }
            }
            eptr = lpNext(zl, sptr);
        }
    if (eptr == ((void *)0))
        zl = zzlInsertAt(zl, ((void *)0), ele, score);
    return zl;
}
extern unsigned long zsetLength (const robj *zobj){
    unsigned long length = 0;
    if (zobj->encoding == 11) {
        length = zzlLength(zobj->ptr);
    } else if (zobj->encoding == 7) {
        length = ((const zset *)zobj->ptr)->zsl->length;
    } else {
        ;
    }
    return length;
}
extern void zsetConvertAndExpand (robj *zobj, int encoding, unsigned long cap){
    zset *zs;
    zskiplistNode *node, *next;
    sds ele;
    double score;
    if (zobj->encoding == encoding)
        return;
    if (zobj->encoding == 11) {
        unsigned char *zl = zobj->ptr;
        unsigned char *eptr, *sptr;
        unsigned char *vstr;
        unsigned int vlen;
        long long vlong;
        if (encoding != 7)
            _serverPanic("t_zset_InstSlice.c", 583, "Unknown target encoding") , abort();
        zs = zmalloc(sizeof (*zs));
        zs->dict = dictCreate(&zsetDictType);
        zs->zsl = zslCreate();
        eptr = lpSeek(zl, 0);
        if (eptr != ((void *)0)) {
            sptr = lpNext(zl, eptr);
            (__builtin_expect(!!(sptr != ((void *)0)), 1) ? (void)0 : (_serverAssertWithInfo(((void *)0), zobj, "sptr != NULL", "t_zset_InstSlice.c", 595) , abort()));
        }
        while (eptr != ((void *)0))
            {
                score = zzlGetScore(sptr);
                vstr = lpGetValue(eptr, &vlen, &vlong);
                if (vstr == ((void *)0)) {
                    ele = sdsfromlonglong(vlong);
                } else
                    ele = sdsnewlen((char *)vstr, vlen);
                node = zslInsert(zs->zsl, score, ele);
                (__builtin_expect(!!(dictAdd(zs->dict, ele, &node->score) == 0), 1) ? (void)0 : (_serverAssert("dictAdd(zs->dict,ele,&node->score) == DICT_OK", "t_zset_InstSlice.c", 607) , abort()));
                zzlNext(zl, &eptr, &sptr);
            }
        ;
        zobj->ptr = zs;
        zobj->encoding = 7;
    } else if (zobj->encoding == 7) {
        unsigned char *zl = lpNew(0);
        if (encoding != 11)
            _serverPanic("t_zset_InstSlice.c", 618, "Unknown target encoding") , abort();
        zs = zobj->ptr;
        node = zs->zsl->header->level[0].forward;
        while (node)
            {
                zl = zzlInsertAt(zl, ((void *)0), node->ele, node->score);
                next = node->level[0].forward;
                node = next;
            }
        ;
        zobj->ptr = zl;
        zobj->encoding = 11;
    } else {
        ;
    }
}
extern int zsetAdd (robj *zobj, double score, sds ele, int in_flags, int *out_flags, double *newscore){
    int incr = (in_flags & (1 << 0)) != 0;
    int nx = (in_flags & (1 << 1)) != 0;
    int xx = (in_flags & (1 << 2)) != 0;
    int gt = (in_flags & (1 << 3)) != 0;
    int lt = (in_flags & (1 << 4)) != 0;
    *out_flags = 0;
    double curscore;
    if (__builtin_isnan(score)) {
        ;
        return 0;
    }
    if (zobj->encoding == 11) {
        unsigned char *eptr;
        if ((eptr = zzlFind(zobj->ptr, ele, &curscore)) != ((void *)0)) {
            if (nx) {
                ;
                return 1;
            }
            if (incr) {
                score += curscore;
                if (__builtin_isnan(score)) {
                    ;
                    return 0;
                }
            }
            if ((lt && score >= curscore) || (gt && score <= curscore)) {
                ;
                return 1;
            }
            if (newscore)
                *newscore = score;
            if (score != curscore) {
                zobj->ptr = zzlDelete(zobj->ptr, eptr);
                zobj->ptr = zzlInsert(zobj->ptr, ele, score);
            }
            return 1;
        } else if (!xx) {
            if (zzlLength(zobj->ptr) + 1 > server.zset_max_listpack_entries || sdslen(ele) > server.zset_max_listpack_value || !lpSafeToAdd(zobj->ptr, sdslen(ele))) {
                zsetConvertAndExpand(zobj, 7, zsetLength(zobj) + 1);
            } else {
                zobj->ptr = zzlInsert(zobj->ptr, ele, score);
                return 1;
            }
        } else {
            ;
        }
    }
    if (zobj->encoding == 7) {
        zset *zs = zobj->ptr;
        zskiplistNode *znode;
        dictEntry *de;
        de = dictFind(zs->dict, ele);
        if (de != ((void *)0)) {
            if (nx) {
                ;
                return 1;
            }
            curscore = *(double *)dictGetVal(de);
            if (incr) {
                score += curscore;
                if (__builtin_isnan(score)) {
                    ;
                    return 0;
                }
            }
            if ((lt && score >= curscore) || (gt && score <= curscore)) {
                ;
                return 1;
            }
            if (newscore)
                *newscore = score;
            if (score != curscore) {
                znode = zslUpdateScore(zs->zsl, curscore, ele, score);
            }
            return 1;
        } else if (!xx) {
            ele = sdsdup(ele);
            znode = zslInsert(zs->zsl, score, ele);
            return 1;
        } else {
            ;
        }
    } else {
        ;
    }
    return 0;
}
static void zrangeResultEmitLongLongForStore (zrange_result_handler *handler, long long value, double score){
    double newscore;
    int retflags = 0;
    sds ele = sdsfromlonglong(value);
    int retval = zsetAdd(handler->dstobj, score, ele, 0, &retflags, &newscore);
}
