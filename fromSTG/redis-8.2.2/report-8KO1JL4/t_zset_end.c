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
extern int zslDelete (zskiplist *zsl, double score, sds ele, zskiplistNode **node){
    zskiplistNode *update[32], *x;
    int i;
    x = zsl->header;
    for (i = zsl->level - 1; i >= 0; i--) {
        while (x->level[i].forward && (x->level[i].forward->score < score || (x->level[i].forward->score == score && sdscmp(x->level[i].forward->ele, ele) < 0)))
            {
                x = x->level[i].forward;
            }
        update[i] = x;
    }
    x = x->level[0].forward;
    if (x && score == x->score && sdscmp(x->ele, ele) == 0) {
        zslDeleteNode(zsl, x, update);
        return 1;
    }
    return 0;
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
    (__builtin_expect(!!(sptr != ((void *)0)), 1) ? (void)0 : (_serverAssert("sptr != NULL", "t_zset_InstSlice.c", 333) , abort()));
    vstr = lpGetValue(sptr, &vlen, &vlong);
    if (vstr) {
        score = zzlStrtod(vstr, vlen);
    } else {
        score = vlong;
    }
    return score;
}
extern unsigned int zzlLength (unsigned char *zl){
    return lpLength(zl) / 2;
}
extern void zzlNext (unsigned char *zl, unsigned char **eptr, unsigned char **sptr){
    unsigned char *_eptr, *_sptr;
    (__builtin_expect(!!(*eptr != ((void *)0) && *sptr != ((void *)0)), 1) ? (void)0 : (_serverAssert("*eptr != NULL && *sptr != NULL", "t_zset_InstSlice.c", 359) , abort()));
    _eptr = lpNext(zl, *sptr);
    if (_eptr != ((void *)0)) {
        _sptr = lpNext(zl, _eptr);
        (__builtin_expect(!!(_sptr != ((void *)0)), 1) ? (void)0 : (_serverAssert("_sptr != NULL", "t_zset_InstSlice.c", 364) , abort()));
    } else {
        _sptr = ((void *)0);
    }
    *eptr = _eptr;
    *sptr = _sptr;
}
extern void zzlPrev (unsigned char *zl, unsigned char **eptr, unsigned char **sptr){
    unsigned char *_eptr, *_sptr;
    (__builtin_expect(!!(*eptr != ((void *)0) && *sptr != ((void *)0)), 1) ? (void)0 : (_serverAssert("*eptr != NULL && *sptr != NULL", "t_zset_InstSlice.c", 378) , abort()));
    _sptr = lpPrev(zl, *eptr);
    if (_sptr != ((void *)0)) {
        _eptr = lpPrev(zl, _sptr);
        (__builtin_expect(!!(_eptr != ((void *)0)), 1) ? (void)0 : (_serverAssert("_eptr != NULL", "t_zset_InstSlice.c", 383) , abort()));
    } else {
        _eptr = ((void *)0);
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
        (__builtin_expect(!!(sptr != ((void *)0)), 1) ? (void)0 : (_serverAssert("sptr != NULL", "t_zset_InstSlice.c", 428) , abort()));
        if (score != ((void *)0))
            *score = zzlGetScore(sptr);
        return eptr;
    }
    return ((void *)0);
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
extern void zsetConvert (robj *zobj, int encoding){
    zsetConvertAndExpand(zobj, encoding, zsetLength(zobj));
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
            _serverPanic("t_zset_InstSlice.c", 532, "Unknown target encoding") , abort();
        zs = zmalloc(sizeof (*zs));
        zs->dict = dictCreate(&zsetDictType);
        zs->zsl = zslCreate();
        eptr = lpSeek(zl, 0);
        if (eptr != ((void *)0)) {
            sptr = lpNext(zl, eptr);
            (__builtin_expect(!!(sptr != ((void *)0)), 1) ? (void)0 : (_serverAssertWithInfo(((void *)0), zobj, "sptr != NULL", "t_zset_InstSlice.c", 544) , abort()));
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
                (__builtin_expect(!!(dictAdd(zs->dict, ele, &node->score) == 0), 1) ? (void)0 : (_serverAssert("dictAdd(zs->dict,ele,&node->score) == DICT_OK", "t_zset_InstSlice.c", 556) , abort()));
                zzlNext(zl, &eptr, &sptr);
            }
        ;
        zobj->ptr = zs;
        zobj->encoding = 7;
    } else if (zobj->encoding == 7) {
        unsigned char *zl = lpNew(0);
        if (encoding != 11)
            _serverPanic("t_zset_InstSlice.c", 567, "Unknown target encoding") , abort();
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
extern void zsetConvertToListpackIfNeeded (robj *zobj, size_t maxelelen, size_t totelelen){
    if (zobj->encoding == 11)
        return;
    zset *zset = zobj->ptr;
    if (zset->zsl->length <= server.zset_max_listpack_entries && maxelelen <= server.zset_max_listpack_value && lpSafeToAdd(((void *)0), totelelen)) {
        zsetConvert(zobj, 11);
    }
}
static int zsetRemoveFromSkiplist (zset *zs, sds ele){
    dictEntry *de;
    double score;
    de = dictUnlink(zs->dict, ele);
    if (de != ((void *)0)) {
        score = *(double *)dictGetVal(de);
        int retval = zslDelete(zs->zsl, score, ele, ((void *)0));
        (__builtin_expect(!!(retval), 1) ? (void)0 : (_serverAssert("retval", "t_zset_InstSlice.c", 678) , abort()));
        return 1;
    }
    return 0;
}
extern void zuiInitIterator (zsetopsrc *op){
    if (op->subject == ((void *)0))
        return;
    if (op->type == 2) {
        iterset *it = &op->iter.set;
        if (op->encoding == 6) {
            it->is.is = op->subject->ptr;
            it->is.ii = 0;
        } else if (op->encoding == 2) {
            it->ht.dict = op->subject->ptr;
            it->ht.di = dictGetIterator(op->subject->ptr);
            it->ht.de = dictNext(it->ht.di);
        } else if (op->encoding == 11) {
            it->lp.lp = op->subject->ptr;
            it->lp.p = lpFirst(it->lp.lp);
        } else {
            ;
        }
    } else if (op->type == 3) {
        iterzset *it = &op->iter.zset;
        if (op->encoding == 11) {
            it->zl.zl = op->subject->ptr;
            it->zl.eptr = lpSeek(it->zl.zl, -2);
            if (it->zl.eptr != ((void *)0)) {
                it->zl.sptr = lpNext(it->zl.zl, it->zl.eptr);
                (__builtin_expect(!!(it->zl.sptr != ((void *)0)), 1) ? (void)0 : (_serverAssert("it->zl.sptr != NULL", "t_zset_InstSlice.c", 842) , abort()));
            }
        } else if (op->encoding == 7) {
            it->sl.zs = op->subject->ptr;
            it->sl.node = it->sl.zs->zsl->tail;
        } else {
            ;
        }
    } else {
        ;
    }
}
extern void zuiClearIterator (zsetopsrc *op){
    if (op->subject == ((void *)0))
        return;
    if (op->type == 2) {
        iterset *it = &op->iter.set;
        if (op->encoding == 6) {
            ;
        } else if (op->encoding == 2) {
            ;
        } else if (op->encoding == 11) {
            ;
        } else {
            ;
        }
    } else if (op->type == 3) {
        iterzset *it = &op->iter.zset;
        if (op->encoding == 11) {
            ;
        } else if (op->encoding == 7) {
            ;
        } else {
            ;
        }
    } else {
        ;
    }
}
extern void zuiDiscardDirtyValue (zsetopval *val){
    if (val->flags & 1) {
        ;
        val->ele = ((void *)0);
        val->flags &= ~1;
    }
}
extern unsigned long zuiLength (zsetopsrc *op){
    if (op->subject == ((void *)0))
        return 0;
    if (op->type == 2) {
        return setTypeSize(op->subject);
    } else if (op->type == 3) {
        if (op->encoding == 11) {
            return zzlLength(op->subject->ptr);
        } else if (op->encoding == 7) {
            zset *zs = op->subject->ptr;
            return zs->zsl->length;
        } else {
            ;
        }
    } else {
        ;
    }
}
extern int zuiNext (zsetopsrc *op, zsetopval *val){
    if (op->subject == ((void *)0))
        return 0;
    zuiDiscardDirtyValue(val);
    memset(val, 0, sizeof(zsetopval));
    if (op->type == 2) {
        iterset *it = &op->iter.set;
        if (op->encoding == 6) {
            int64_t ell;
            if (!intsetGet(it->is.is, it->is.ii, &ell))
                return 0;
            val->ell = ell;
            val->score = 1.;
            it->is.ii++;
        } else if (op->encoding == 2) {
            if (it->ht.de == ((void *)0))
                return 0;
            val->ele = dictGetKey(it->ht.de);
            val->score = 1.;
            it->ht.de = dictNext(it->ht.di);
        } else if (op->encoding == 11) {
            if (it->lp.p == ((void *)0))
                return 0;
            val->estr = lpGetValue(it->lp.p, &val->elen, &val->ell);
            val->score = 1.;
            it->lp.p = lpNext(it->lp.lp, it->lp.p);
        } else {
            ;
        }
    } else if (op->type == 3) {
        iterzset *it = &op->iter.zset;
        if (op->encoding == 11) {
            if (it->zl.eptr == ((void *)0) || it->zl.sptr == ((void *)0))
                return 0;
            val->estr = lpGetValue(it->zl.eptr, &val->elen, &val->ell);
            val->score = zzlGetScore(it->zl.sptr);
            zzlPrev(it->zl.zl, &it->zl.eptr, &it->zl.sptr);
        } else if (op->encoding == 7) {
            if (it->sl.node == ((void *)0))
                return 0;
            val->ele = it->sl.node->ele;
            val->score = it->sl.node->score;
            it->sl.node = it->sl.node->backward;
        } else {
            ;
        }
    } else {
        ;
    }
    return 1;
}
extern sds zuiSdsFromValue (zsetopval *val){
    if (val->ele == ((void *)0)) {
        if (val->estr != ((void *)0)) {
            val->ele = sdsnewlen((char *)val->estr, val->elen);
        } else {
            val->ele = sdsfromlonglong(val->ell);
        }
        val->flags |= 1;
    }
    return val->ele;
}
extern sds zuiNewSdsFromValue (zsetopval *val){
    if (val->flags & 1) {
        sds ele = val->ele;
        val->flags &= ~1;
        val->ele = ((void *)0);
        return ele;
    } else if (val->ele) {
        return sdsdup(val->ele);
    } else if (val->estr) {
        return sdsnewlen((char *)val->estr, val->elen);
    } else {
        return sdsfromlonglong(val->ell);
    }
}
extern int zuiFind (zsetopsrc *op, zsetopval *val, double *score){
    if (op->subject == ((void *)0))
        return 0;
    if (op->type == 2) {
        char *str = val->ele ? val->ele : (char *)val->estr;
        size_t len = val->ele ? sdslen(val->ele) : val->elen;
        if (setTypeIsMemberAux(op->subject, str, len, val->ell, val->ele != ((void *)0))) {
            *score = 1.;
            return 1;
        } else {
            return 0;
        }
    } else if (op->type == 3) {
        zuiSdsFromValue(val);
        if (op->encoding == 11) {
            if (zzlFind(op->subject->ptr, val->ele, score) != ((void *)0)) {
                return 1;
            } else {
                return 0;
            }
        } else if (op->encoding == 7) {
            zset *zs = op->subject->ptr;
            dictEntry *de;
            if ((de = dictFind(zs->dict, val->ele)) != ((void *)0)) {
                *score = *(double *)dictGetVal(de);
                return 1;
            } else {
                return 0;
            }
        } else {
            ;
        }
    } else {
        ;
    }
}
static inline void zunionInterAggregate (double *target, double val, int aggregate){
    if (aggregate == 1) {
        *target = *target + val;
        if (__builtin_isnan(*target))
            *target = 0.;
    } else if (aggregate == 2) {
        *target = val < *target ? val : *target;
    } else if (aggregate == 3) {
        *target = val > *target ? val : *target;
    } else {
        ;
    }
}
static size_t zsetDictGetMaxElementLength (dict *d, size_t *totallen){
    dictIterator di;
    dictEntry *de;
    size_t maxelelen = 0;
    while ((de = dictNext(&di)) != ((void *)0))
        {
            sds ele = dictGetKey(de);
            if (sdslen(ele) > maxelelen)
                maxelelen = sdslen(ele);
            if (totallen)
                (*totallen) += sdslen(ele);
        }
    ;
    return maxelelen;
}
static void zdiffAlgorithm1 (zsetopsrc *src, long setnum, zset *dstzset, size_t *maxelelen, size_t *totelelen){
    int j;
    zsetopval zval;
    zskiplistNode *znode;
    sds tmp;
    zuiInitIterator(&src[0]);
    while (zuiNext(&src[0], &zval))
        {
            double value;
            int exists = 0;
            for (j = 1; j < setnum; j++) {
                if (src[j].subject == src[0].subject || zuiFind(&src[j], &zval, &value)) {
                    exists = 1;
                    break;
                }
            }
            if (!exists) {
                tmp = zuiNewSdsFromValue(&zval);
                znode = zslInsert(dstzset->zsl, zval.score, tmp);
                if (sdslen(tmp) > *maxelelen)
                    *maxelelen = sdslen(tmp);
                (*totelelen) += sdslen(tmp);
            }
        }
    zuiClearIterator(&src[0]);
}
static void zdiffAlgorithm2 (zsetopsrc *src, long setnum, zset *dstzset, size_t *maxelelen, size_t *totelelen){
    int j;
    int cardinality = 0;
    zsetopval zval;
    zskiplistNode *znode;
    sds tmp;
    for (j = 0; j < setnum; j++) {
        if (zuiLength(&src[j]) == 0)
            continue;
        zuiInitIterator(&src[j]);
        while (zuiNext(&src[j], &zval))
            {
                if (j == 0) {
                    tmp = zuiNewSdsFromValue(&zval);
                    znode = zslInsert(dstzset->zsl, zval.score, tmp);
                    cardinality++;
                } else {
                    ((dstzset->dict)->pauseAutoResize++);
                    tmp = zuiSdsFromValue(&zval);
                    if (zsetRemoveFromSkiplist(dstzset, tmp)) {
                        cardinality--;
                    }
                    ((dstzset->dict)->pauseAutoResize--);
                }
                if (cardinality == 0)
                    break;
            }
        zuiClearIterator(&src[j]);
        if (cardinality == 0)
            break;
    }
    ;
    *maxelelen = zsetDictGetMaxElementLength(dstzset->dict, totelelen);
}
static int zsetChooseDiffAlgorithm (zsetopsrc *src, long setnum){
    int j;
    long long algo_one_work = 0;
    long long algo_two_work = 0;
    for (j = 0; j < setnum; j++) {
        if (j > 0 && src[0].subject == src[j].subject) {
            return 0;
        }
        algo_one_work += zuiLength(&src[0]);
        algo_two_work += zuiLength(&src[j]);
    }
    algo_one_work /= 2;
    return (algo_one_work <= algo_two_work) ? 1 : 2;
}
static void zdiff (zsetopsrc *src, long setnum, zset *dstzset, size_t *maxelelen, size_t *totelelen){
    if (zuiLength(&src[0]) > 0) {
        int diff_algo = zsetChooseDiffAlgorithm(src, setnum);
        if (diff_algo == 1) {
            zdiffAlgorithm1(src, setnum, dstzset, maxelelen, totelelen);
        } else if (diff_algo == 2) {
            zdiffAlgorithm2(src, setnum, dstzset, maxelelen, totelelen);
        } else if (diff_algo != 0) {
            ;
        }
    }
}
extern void zunionInterDiffGenericCommand (client *c, robj *dstkey, int numkeysIndex, int op, int cardinality_only){
    int i, j;
    long setnum;
    int aggregate = 1;
    zsetopsrc *src;
    zsetopval zval;
    sds tmp;
    size_t maxelelen = 0, totelelen = 0;
    robj *dstobj = ((void *)0);
    zset *dstzset = ((void *)0);
    zskiplistNode *znode;
    int withscores = 0;
    unsigned long cardinality = 0;
    long limit = 0;
    if ((getLongFromObjectOrReply(c, c->argv[numkeysIndex], &setnum, ((void *)0)) != 0))
        return;
    if (setnum < 1) {
        ;
        return;
    }
    if (setnum > (c->argc - (numkeysIndex + 1))) {
        ;
        return;
    }
    src = ztrycalloc(sizeof(zsetopsrc) * setnum);
    if (src == ((void *)0)) {
        ;
        return;
    }
    for (i = 0 , j = numkeysIndex + 1; i < setnum; i++ , j++) {
        kvobj *obj = lookupKeyRead(c->db, c->argv[j]);
        if (obj != ((void *)0)) {
            if (obj->type != 3 && obj->type != 2) {
                ;
                return;
            }
            src[i].subject = obj;
            src[i].type = obj->type;
            src[i].encoding = obj->encoding;
        } else {
            src[i].subject = ((void *)0);
        }
        src[i].weight = 1.;
    }
    if (j < c->argc) {
        int remaining = c->argc - j;
        while (remaining)
            {
                if (op != 1 && !cardinality_only && remaining >= (setnum + 1) && !strcasecmp(c->argv[j]->ptr, "weights")) {
                    j++;
                    remaining--;
                    for (i = 0; i < setnum; i++ , j++ , remaining--) {
                        if (getDoubleFromObjectOrReply(c, c->argv[j], &src[i].weight, "weight value is not a float") != 0) {
                            ;
                            return;
                        }
                    }
                } else if (op != 1 && !cardinality_only && remaining >= 2 && !strcasecmp(c->argv[j]->ptr, "aggregate")) {
                    j++;
                    remaining--;
                    if (!strcasecmp(c->argv[j]->ptr, "sum")) {
                        aggregate = 1;
                    } else if (!strcasecmp(c->argv[j]->ptr, "min")) {
                        aggregate = 2;
                    } else if (!strcasecmp(c->argv[j]->ptr, "max")) {
                        aggregate = 3;
                    } else {
                        ;
                    }
                    j++;
                    remaining--;
                } else if (remaining >= 1 && !dstkey && !cardinality_only && !strcasecmp(c->argv[j]->ptr, "withscores")) {
                    j++;
                    remaining--;
                    withscores = 1;
                } else if (cardinality_only && remaining >= 2 && !strcasecmp(c->argv[j]->ptr, "limit")) {
                    j++;
                    remaining--;
                    if (getPositiveLongFromObjectOrReply(c, c->argv[j], &limit, "LIMIT can't be negative") != 0) {
                        ;
                        return;
                    }
                    j++;
                    remaining--;
                } else {
                    ;
                }
            }
    }
    if (!cardinality_only) {
        dstobj = createZsetObject();
        dstzset = dstobj->ptr;
    }
    memset(&zval, 0, sizeof (zval));
    if (op == 2) {
        if (zuiLength(&src[0]) > 0) {
            zuiInitIterator(&src[0]);
            while (zuiNext(&src[0], &zval))
                {
                    double score, value;
                    score = src[0].weight * zval.score;
                    if (__builtin_isnan(score))
                        score = 0;
                    for (j = 1; j < setnum; j++) {
                        if (src[j].subject == src[0].subject) {
                            value = zval.score * src[j].weight;
                            zunionInterAggregate(&score, value, aggregate);
                        } else if (zuiFind(&src[j], &zval, &value)) {
                            value *= src[j].weight;
                            zunionInterAggregate(&score, value, aggregate);
                        } else {
                            ;
                        }
                    }
                    if (j == setnum && cardinality_only) {
                        cardinality++;
                        if (limit && cardinality >= (unsigned long)limit) {
                            zuiDiscardDirtyValue(&zval);
                            break;
                        }
                    } else if (j == setnum) {
                        tmp = zuiNewSdsFromValue(&zval);
                        znode = zslInsert(dstzset->zsl, score, tmp);
                        totelelen += sdslen(tmp);
                        if (sdslen(tmp) > maxelelen)
                            maxelelen = sdslen(tmp);
                    }
                }
            zuiClearIterator(&src[0]);
        }
    } else if (op == 0) {
        dictIterator di;
        dictEntry *de, *existing;
        double score;
        if (setnum) {
            dictExpand(dstzset->dict, zuiLength(&src[setnum - 1]));
        }
        for (i = 0; i < setnum; i++) {
            if (zuiLength(&src[i]) == 0)
                continue;
            zuiInitIterator(&src[i]);
            while (zuiNext(&src[i], &zval))
                {
                    score = src[i].weight * zval.score;
                    if (__builtin_isnan(score))
                        score = 0;
                    de = dictAddRaw(dstzset->dict, zuiSdsFromValue(&zval), &existing);
                    if (!existing) {
                        tmp = zuiNewSdsFromValue(&zval);
                        totelelen += sdslen(tmp);
                        if (sdslen(tmp) > maxelelen)
                            maxelelen = sdslen(tmp);
                    } else {
                        double *existing_score_ptr = dictGetDoubleValPtr(existing);
                        zunionInterAggregate(existing_score_ptr, score, aggregate);
                    }
                }
            zuiClearIterator(&src[i]);
        }
        ;
        while ((de = dictNext(&di)) != ((void *)0))
            {
                sds ele = dictGetKey(de);
                score = dictGetDoubleVal(de);
                znode = zslInsert(dstzset->zsl, score, ele);
            }
        ;
    } else if (op == 1) {
        zdiff(src, setnum, dstzset, &maxelelen, &totelelen);
    } else {
        ;
    }
    if (dstkey) {
        if (dstzset->zsl->length) {
            zsetConvertToListpackIfNeeded(dstobj, maxelelen, totelelen);
            addReplyLongLong(c, zsetLength(dstobj));
        } else {
            ;
        }
    } else if (cardinality_only) {
        ;
    } else {
        unsigned long length = dstzset->zsl->length;
        zskiplist *zsl = dstzset->zsl;
        zskiplistNode *zn = zsl->header->level[0].forward;
        while (zn != ((void *)0))
            {
                ;
                addReplyBulkCBuffer(c, zn->ele, sdslen(zn->ele));
                zn = zn->level[0].forward;
            }
        ;
    }
    ;
}
