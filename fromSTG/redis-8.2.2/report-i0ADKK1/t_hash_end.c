#include "header_func.h"
static inline int isDictWithMetaHFE (dict *d){
    return d->type == &mstrHashDictTypeWithHFE;
}
static uint64_t listpackExExpireDryRun (const robj *o){
    (__builtin_expect(!!(o->encoding == 12), 1) ? (void)0 : (_serverAssert("o->encoding == OBJ_ENCODING_LISTPACK_EX", "t_hash_InstSlice.c", 288) , abort()));
    listpackEx *lpt = o->ptr;
    struct lpFingArgs r = {.max_to_search = (18446744073709551615UL), .expire_time = commandTimeSnapshot()};
    return r.expired;
}
static uint64_t listpackExGetMinExpire (robj *o){
    (__builtin_expect(!!(o->encoding == 12), 1) ? (void)0 : (_serverAssert("o->encoding == OBJ_ENCODING_LISTPACK_EX", "t_hash_InstSlice.c", 300) , abort()));
    long long expireAt;
    unsigned char *fptr;
    listpackEx *lpt = o->ptr;
    fptr = lpSeek(lpt->lp, 2);
    if (fptr != ((void *)0)) {
        (__builtin_expect(!!(lpGetIntegerValue(fptr, &expireAt)), 1) ? (void)0 : (_serverAssert("lpGetIntegerValue(fptr, &expireAt)", "t_hash_InstSlice.c", 310) , abort()));
        if (expireAt != 0)
            return expireAt;
    }
    return (((uint64_t)281474976710655L) + 1);
}
extern void listpackExExpire (redisDb *db, kvobj *kv, ExpireInfo *info){
    (__builtin_expect(!!(kv->encoding == 12), 1) ? (void)0 : (_serverAssert("kv->encoding == OBJ_ENCODING_LISTPACK_EX", "t_hash_InstSlice.c", 322) , abort()));
    uint64_t expired = 0, min = (((uint64_t)281474976710655L) + 1);
    unsigned char *ptr;
    listpackEx *lpt = kv->ptr;
    ptr = lpFirst(lpt->lp);
    sds key = kvobjGetKey(kv);
    while (ptr != ((void *)0) && (info->itemsExpired < info->maxToExpire))
        {
            long long val;
            int64_t flen;
            unsigned char intbuf[21], *fref;
            fref = lpGet(ptr, &flen, intbuf);
            ptr = lpNext(lpt->lp, ptr);
            (__builtin_expect(!!(ptr), 1) ? (void)0 : (_serverAssert("ptr", "t_hash_InstSlice.c", 339) , abort()));
            ptr = lpNext(lpt->lp, ptr);
            (__builtin_expect(!!(ptr && lpGetIntegerValue(ptr, &val)), 1) ? (void)0 : (_serverAssert("ptr && lpGetIntegerValue(ptr, &val)", "t_hash_InstSlice.c", 341) , abort()));
            if (val == 0 || (uint64_t)val > info->now)
                break;
            propagateHashFieldDeletion(db, key, (char *)((fref) ? fref : intbuf), flen);
            server.stat_expired_subkeys++;
            ptr = lpNext(lpt->lp, ptr);
            info->itemsExpired++;
            expired++;
        }
    if (expired) {
        lpt->lp = lpDeleteRange(lpt->lp, 0, expired * 3);
        unsigned long l = lpLength(lpt->lp) / 3;
    }
    min = hashTypeGetMinExpire(kv, 1);
    info->nextExpireTime = min;
}
extern int hashTypeIsExpired (const robj *o, uint64_t expireAt){
    if (o->encoding == 12) {
        if (expireAt == 0)
            return 0;
    } else if (o->encoding == 2) {
        if (expireAt == (((uint64_t)281474976710655L) + 1))
            return 0;
    } else {
        ;
    }
    return (mstime_t)expireAt < commandTimeSnapshot();
}
extern unsigned char * hashTypeListpackGetLp (robj *o){
    if (o->encoding == 11) {
        return o->ptr;
    } else if (o->encoding == 12)
        return ((listpackEx *)o->ptr)->lp;
}
extern unsigned long hashTypeLength (const robj *o, int subtractExpiredFields){
    unsigned long length = (9223372036854775807L * 2UL + 1UL);
    if (o->encoding == 11) {
        length = lpLength(o->ptr) / 2;
    } else if (o->encoding == 12) {
        listpackEx *lpt = o->ptr;
        length = lpLength(lpt->lp) / 3;
        if (subtractExpiredFields && lpt->meta.trash == 0)
            length -= listpackExExpireDryRun(o);
    } else if (o->encoding == 2) {
        uint64_t expiredItems = 0;
        dict *d = (dict *)o->ptr;
        if (subtractExpiredFields && isDictWithMetaHFE(d)) {
            dictExpireMetadata *meta = (dictExpireMetadata *)(&(d)->metadata);
            if (meta->expireMeta.trash == 0)
                expiredItems = ebExpireDryRun(meta->hfe, &hashFieldExpireBucketsType, commandTimeSnapshot());
        }
        length = ((d)->ht_used[0] + (d)->ht_used[1]) - expiredItems;
    } else {
        ;
    }
    return length;
}
extern hashTypeIterator * hashTypeInitIterator (robj *subject){
    hashTypeIterator *hi = zmalloc(sizeof(hashTypeIterator));
    hi->subject = subject;
    hi->encoding = subject->encoding;
    if (hi->encoding == 11 || hi->encoding == 12) {
        hi->fptr = ((void *)0);
        hi->vptr = ((void *)0);
        hi->tptr = ((void *)0);
        hi->expire_time = (((uint64_t)281474976710655L) + 1);
    } else if (hi->encoding == 2) {
        hi->di = dictGetIterator(subject->ptr);
    } else {
        ;
    }
    return hi;
}
extern int hashTypeNext (hashTypeIterator *hi, int skipExpiredFields){
    hi->expire_time = (((uint64_t)281474976710655L) + 1);
    if (hi->encoding == 11) {
        unsigned char *zl;
        unsigned char *fptr, *vptr;
        zl = hi->subject->ptr;
        fptr = hi->fptr;
        vptr = hi->vptr;
        if (fptr == ((void *)0)) {
            (__builtin_expect(!!(vptr == ((void *)0)), 1) ? (void)0 : (_serverAssert("vptr == NULL", "t_hash_InstSlice.c", 605) , abort()));
            fptr = lpFirst(zl);
        } else {
            (__builtin_expect(!!(vptr != ((void *)0)), 1) ? (void)0 : (_serverAssert("vptr != NULL", "t_hash_InstSlice.c", 609) , abort()));
            fptr = lpNext(zl, vptr);
        }
        if (fptr == ((void *)0))
            return -1;
        vptr = lpNext(zl, fptr);
        (__builtin_expect(!!(vptr != ((void *)0)), 1) ? (void)0 : (_serverAssert("vptr != NULL", "t_hash_InstSlice.c", 616) , abort()));
        hi->fptr = fptr;
        hi->vptr = vptr;
    } else if (hi->encoding == 12) {
        long long expire_time;
        unsigned char *zl = hashTypeListpackGetLp(hi->subject);
        unsigned char *fptr, *vptr, *tptr;
        fptr = hi->fptr;
        vptr = hi->vptr;
        tptr = hi->tptr;
        if (fptr == ((void *)0)) {
            (__builtin_expect(!!(vptr == ((void *)0)), 1) ? (void)0 : (_serverAssert("vptr == NULL", "t_hash_InstSlice.c", 632) , abort()));
            fptr = lpFirst(zl);
        } else {
            (__builtin_expect(!!(tptr != ((void *)0)), 1) ? (void)0 : (_serverAssert("tptr != NULL", "t_hash_InstSlice.c", 636) , abort()));
            fptr = lpNext(zl, tptr);
        }
        if (fptr == ((void *)0))
            return -1;
        while (fptr != ((void *)0))
            {
                vptr = lpNext(zl, fptr);
                (__builtin_expect(!!(vptr != ((void *)0)), 1) ? (void)0 : (_serverAssert("vptr != NULL", "t_hash_InstSlice.c", 644) , abort()));
                tptr = lpNext(zl, vptr);
                (__builtin_expect(!!(tptr && lpGetIntegerValue(tptr, &expire_time)), 1) ? (void)0 : (_serverAssert("tptr && lpGetIntegerValue(tptr, &expire_time)", "t_hash_InstSlice.c", 647) , abort()));
                if (!skipExpiredFields || !hashTypeIsExpired(hi->subject, expire_time))
                    break;
                fptr = lpNext(zl, tptr);
            }
        if (fptr == ((void *)0))
            return -1;
        hi->fptr = fptr;
        hi->vptr = vptr;
        hi->tptr = tptr;
        hi->expire_time = (expire_time != 0) ? (uint64_t)expire_time : (((uint64_t)281474976710655L) + 1);
    } else if (hi->encoding == 2) {
        while ((hi->de = dictNext(hi->di)) != ((void *)0))
            {
                hi->expire_time = hfieldGetExpireTime(dictGetKey(hi->de));
                if (skipExpiredFields && ((mstime_t)hi->expire_time < commandTimeSnapshot()))
                    continue;
                return 0;
            }
        return -1;
    } else {
        ;
    }
    return 0;
}
extern void hashTypeRandomElement (robj *hashobj, unsigned long hashsize, CommonEntry *key, CommonEntry *val){
    if (hashobj->encoding == 2) {
        dictEntry *de = dictGetFairRandomKey(hashobj->ptr);
        hfield field = dictGetKey(de);
        key->sval = (unsigned char *)field;
        if (val) {
            sds s = dictGetVal(de);
        }
    } else if (hashobj->encoding == 11) {
        ;
    } else if (hashobj->encoding == 12) {
        lpRandomPair(hashTypeListpackGetLp(hashobj), hashsize, (listpackEntry *)key, (listpackEntry *)val, 3);
    } else {
        ;
    }
}
static uint64_t hashTypeExpire (kvobj *o, ExpireCtx *expireCtx, int updateGlobalHFE){
    uint64_t noExpireLeftRes = (((uint64_t)281474976710655L) + 1);
    redisDb *db = expireCtx->db;
    ExpireInfo info = {0};
    if (o->encoding == 12) {
        info = (ExpireInfo){.maxToExpire = expireCtx->fieldsToExpireQuota, .now = commandTimeSnapshot(), .itemsExpired = 0};
        listpackExExpire(db, o, &info);
    } else {
        (__builtin_expect(!!(o->encoding == 2), 1) ? (void)0 : (_serverAssert("o->encoding == OBJ_ENCODING_HT", "t_hash_InstSlice.c", 799) , abort()));
        dict *d = o->ptr;
        dictExpireMetadata *dictExpireMeta = (dictExpireMetadata *)(&(d)->metadata);
        OnFieldExpireCtx onFieldExpireCtx = {.hashObj = o, .db = db};
        info = (ExpireInfo){.maxToExpire = expireCtx->fieldsToExpireQuota, .onExpireItem = onFieldExpire, .ctx = &onFieldExpireCtx, .now = commandTimeSnapshot()};
    }
    expireCtx->fieldsToExpireQuota -= info.itemsExpired;
    if (info.itemsExpired) {
        sds keystr = kvobjGetKey(o);
        robj *key = createStringObject(keystr, sdslen(keystr));
        if (hashTypeLength(o, 0) == 0) {
            ;
            noExpireLeftRes = 0;
        } else {
            ;
        }
        ;
    }
    return (info.nextExpireTime == (((uint64_t)281474976710655L) + 1)) ? noExpireLeftRes : info.nextExpireTime;
}
static int hashTypeExpireIfNeeded (redisDb *db, kvobj *o){
    uint64_t nextExpireTime;
    uint64_t minExpire = hashTypeGetMinExpire(o, 1);
    if ((mstime_t)minExpire >= commandTimeSnapshot())
        return 0;
    if ((server.loading) || (server.allow_access_expired) || (server.masterhost) || (isPausedActionsWithUpdate((1 << 2))))
        return 0;
    ExpireCtx expireCtx = {.db = db, .fieldsToExpireQuota = (4294967295U)};
    nextExpireTime = hashTypeExpire(o, &expireCtx, 1);
    return nextExpireTime == 0;
}
extern uint64_t hashTypeGetMinExpire (robj *o, int accurate){
    ExpireMeta *expireMeta = ((void *)0);
    if (!accurate) {
        if (o->encoding == 11) {
            return (((uint64_t)281474976710655L) + 1);
        } else if (o->encoding == 12) {
            listpackEx *lpt = o->ptr;
            expireMeta = &lpt->meta;
        } else {
            (__builtin_expect(!!(o->encoding == 2), 1) ? (void)0 : (_serverAssert("o->encoding == OBJ_ENCODING_HT", "t_hash_InstSlice.c", 881) , abort()));
            dict *d = o->ptr;
            if (!isDictWithMetaHFE(d))
                return (((uint64_t)281474976710655L) + 1);
            expireMeta = &((dictExpireMetadata *)(&(d)->metadata))->expireMeta;
        }
        if (expireMeta->trash == 1)
            return (((uint64_t)281474976710655L) + 1);
        return ebGetMetaExpTime(expireMeta);
    }
    if (o->encoding == 11) {
        return (((uint64_t)281474976710655L) + 1);
    } else if (o->encoding == 12) {
        return listpackExGetMinExpire(o);
    } else {
        (__builtin_expect(!!(o->encoding == 2), 1) ? (void)0 : (_serverAssert("o->encoding == OBJ_ENCODING_HT", "t_hash_InstSlice.c", 904) , abort()));
        dict *d = o->ptr;
        if (!isDictWithMetaHFE(d))
            return (((uint64_t)281474976710655L) + 1);
        dictExpireMetadata *expireMeta = (dictExpireMetadata *)(&(d)->metadata);
        return ebGetNextTimeToExpire(expireMeta->hfe, &hashFieldExpireBucketsType);
    }
}
static void addHashIteratorCursorToReply (client *c, hashTypeIterator *hi, int what){
    if (hi->encoding == 11 || hi->encoding == 12) {
        unsigned char *vstr = ((void *)0);
        unsigned int vlen = (2147483647 * 2U + 1U);
        long long vll = 9223372036854775807LL;
    } else if (hi->encoding == 2) {
        char *value;
        size_t len;
    } else {
        ;
    }
}
extern void hrandfieldWithCountCommand (client *c, long l, int withvalues){
    unsigned long count, size;
    int uniq = 1;
    kvobj *hash;
    if ((hash = lookupKeyReadOrReply(c, c->argv[1], shared.emptyarray)) == ((void *)0) || checkType(c, hash, 4))
        return;
    if (l >= 0) {
        count = (unsigned long)l;
    } else {
        count = -l;
        uniq = 0;
    }
    if (hashTypeExpireIfNeeded(c->db, hash)) {
        ;
        return;
    }
    size = hashTypeLength(hash, 0);
    if (count == 0) {
        ;
        return;
    }
    if (!uniq || count == 1) {
        ;
        if (hash->encoding == 2) {
            while (count--)
                {
                    dictEntry *de = dictGetFairRandomKey(hash->ptr);
                    hfield field = dictGetKey(de);
                    sds value = dictGetVal(de);
                    if (c->flags & (1 << 10))
                        break;
                }
        } else if (hash->encoding == 11 || hash->encoding == 12) {
            listpackEntry *keys, *vals = ((void *)0);
            unsigned long limit, sample_count;
            unsigned char *lp = hashTypeListpackGetLp(hash);
            int tuple_len = hash->encoding == 11 ? 2 : 3;
        }
        return;
    }
    long reply_size = count < size ? count : size;
    if (count >= size) {
        hashTypeIterator *hi = hashTypeInitIterator(hash);
        while (hashTypeNext(hi, 0) != -1)
            {
                ;
                addHashIteratorCursorToReply(c, hi, 1);
                if (withvalues)
                    addHashIteratorCursorToReply(c, hi, 2);
            }
        ;
        return;
    }
    if (hash->encoding == 11 || hash->encoding == 12) {
        unsigned char *lp = hashTypeListpackGetLp(hash);
        int tuple_len = hash->encoding == 11 ? 2 : 3;
        listpackEntry *keys, *vals = ((void *)0);
        return;
    }
    if (count * 3 > size) {
        dict *ht = hash->ptr;
        dictIterator di;
        dictEntry *de;
        unsigned long idx = 0;
        struct FieldValPair {
            hfield field;
            sds value;
        } *pairs = zmalloc(sizeof(struct FieldValPair) * size);
        while (size > count)
            {
                unsigned long toDiscardIdx = rand() % size;
                pairs[toDiscardIdx] = pairs[--size];
            }
        ;
    } else {
        dictType uniqueDictType = {.hashFunction = dictPtrHash};
        dict *dictUnique = dictCreate(&uniqueDictType);
        unsigned long added = 0;
        while (added < count)
            {
                dictEntry *de = dictGetFairRandomKey(hash->ptr);
                (__builtin_expect(!!(de != ((void *)0)), 1) ? (void)0 : (_serverAssert("de != NULL", "t_hash_InstSlice.c", 1237) , abort()));
                hfield field = dictGetKey(de);
                sds value = dictGetVal(de);
                if (dictAdd(dictUnique, field, value) != 0)
                    continue;
                added++;
            }
        ;
    }
}
extern void hrandfieldCommand (client *c){
    long l;
    int withvalues = 0;
    kvobj *hash;
    CommonEntry ele;
    if (c->argc >= 3) {
        if (getRangeLongFromObjectOrReply(c, c->argv[2], -9223372036854775807L, 9223372036854775807L, &l, ((void *)0)) != 0)
            return;
        if (c->argc > 4 || (c->argc == 4 && strcasecmp(c->argv[3]->ptr, "withvalues"))) {
            ;
            return;
        } else if (c->argc == 4) {
            withvalues = 1;
            if (l < -9223372036854775807L / 2 || l > 9223372036854775807L / 2) {
                ;
                return;
            }
        }
        hrandfieldWithCountCommand(c, l, withvalues);
        return;
    }
    if ((hash = lookupKeyReadOrReply(c, c->argv[1], shared.null[c->resp])) == ((void *)0) || checkType(c, hash, 4)) {
        return;
    }
    if (hashTypeExpireIfNeeded(c->db, hash)) {
        ;
        return;
    }
    hashTypeRandomElement(hash, hashTypeLength(hash, 0), &ele, ((void *)0));
    if (ele.sval) {
        ;
    } else
        addReplyBulkLongLong(c, ele.lval);
}
extern int hfieldIsExpireAttached (hfield field){
    return mstrIsMetaAttached(field) && mstrGetFlag(field, (int)HFIELD_META_EXPIRE);
}
extern uint64_t hfieldGetExpireTime (hfield field){
    if (!hfieldIsExpireAttached(field))
        return (((uint64_t)281474976710655L) + 1);
    ExpireMeta *expireMeta = mstrMetaRef(field, &mstrFieldKind, (int)HFIELD_META_EXPIRE);
    if (expireMeta->trash)
        return (((uint64_t)281474976710655L) + 1);
    return ebGetMetaExpTime(expireMeta);
}
static void propagateHashFieldDeletion (redisDb *db, sds key, char *field, size_t fieldLen){
    robj *argv[] = {shared.hdel, createStringObject((char *)key, sdslen(key)), createStringObject(field, fieldLen)};
    int prev_replication_allowed = server.replication_allowed;
    server.replication_allowed = prev_replication_allowed;
}
