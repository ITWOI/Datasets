extern void updateLFU (robj *val){
    unsigned long counter = LFUDecrAndReturn(val);
    counter = LFULogIncr(counter);
    val->lru = (LFUGetTimeInMinutes() << 8) | counter;
}


extern void updateKeysizesHist (redisDb *db, int didx, uint32_t type, int64_t oldLen, int64_t newLen){
    if (__builtin_expect(!!(type >= 5), 0))
        return;
    kvstoreDictMetadata *dictMeta = kvstoreGetDictMetadata(db->keys, didx);
    kvstoreMetadata *kvstoreMeta = kvstoreGetMetadata(db->keys);
    if (oldLen > 0) {
        int old_bin = log2ceil(oldLen) + 1;
        ;
        if (dictMeta) {
            dictMeta->keysizes_hist[type][old_bin]--;
            ;
        }
        kvstoreMeta->keysizes_hist[type][old_bin]--;
        ;
    } else {
        if (oldLen == 0) {
            if (dictMeta) {
                dictMeta->keysizes_hist[type][0]--;
                ;
            }
            kvstoreMeta->keysizes_hist[type][0]--;
            ;
        }
    }
    if (newLen > 0) {
        int new_bin = log2ceil(newLen) + 1;
        ;
        if (dictMeta)
            dictMeta->keysizes_hist[type][new_bin]++;
        kvstoreMeta->keysizes_hist[type][new_bin]++;
    } else {
        if (newLen == 0) {
            if (dictMeta)
                dictMeta->keysizes_hist[type][0]++;
            kvstoreMeta->keysizes_hist[type][0]++;
        }
    }
}


extern kvobj * lookupKey (redisDb *db, robj *key, int flags, dictEntryLink *link){
    kvobj *val = dbFindByLink(db, key->ptr, link);
    if (val) {
        int is_ro_replica = server.masterhost && server.repl_slave_ro;
        int expire_flags = 0;
        if (flags & (1 << 3) && !is_ro_replica)
            expire_flags |= 1;
        if (flags & (1 << 4))
            expire_flags |= 2;
        if (flags & (1 << 5))
            expire_flags |= 4;
        if (expireIfNeeded(db, key, val, expire_flags) != KEY_VALID) {
            val = ((void *)0);
            if (link)
                *link = ((void *)0);
        }
    }
    if (val) {
        if (server.current_client && server.current_client->flags & (1ULL << 45) && server.executing_client->cmd->proc != touchCommand)
            flags |= (1 << 0);
        if (!hasActiveChildProcess() && !(flags & (1 << 0))) {
            if (server.maxmemory_policy & (1 << 1)) {
                updateLFU(val);
            } else {
                val->lru = LRU_CLOCK();
            }
        }
        if (!(flags & ((1 << 2) | (1 << 3))))
            server.stat_keyspace_hits++;
    } else {
        ;
        if (!(flags & ((1 << 2) | (1 << 3))))
            server.stat_keyspace_misses++;
    }
    return val;
}


extern kvobj * lookupKeyWriteWithLink (redisDb *db, robj *key, dictEntryLink *link){
    return lookupKey(db, key, 0 | (1 << 3), link);
}


extern kvobj * dbAddInternal (redisDb *db, robj *key, robj **valref, dictEntryLink *link, long long expire){
    int slot = getKeySlot(key->ptr);
    dictEntryLink tmp = ((void *)0);
    if (link == ((void *)0))
        link = &tmp;
    robj *val = *valref;
    int hasExpire = expire != -1;
    kvobj *kv = kvobjSet(key->ptr, val, hasExpire);
    ;
    ;
    if (hasExpire)
        kv = setExpireByLink(((void *)0), db, key->ptr, expire, *link);
    ;
    ;
    updateKeysizesHist(db, slot, kv->type, -1, getObjectLength(kv));
    ;
    return kv;
}


extern kvobj * dbAddByLink (redisDb *db, robj *key, robj **valref, dictEntryLink *link){
    return dbAddInternal(db, key, valref, link, -1);
}


extern int getKeySlot (sds key){
    if (!server.cluster_enabled)
        return 0;
    if (server.current_client && server.current_client->slot >= 0 && server.current_client->flags & (1 << 29) && !(server.current_client->flags & (1 << 1))) {
        ;
        return server.current_client->slot;
    }
    int slot = keyHashSlot(key, (int)sdslen(key));
    if (server.current_client && (server.current_client->flags & (1 << 1))) {
        server.current_client->slot = slot;
    }
    return slot;
}


static void dbSetValue (redisDb *db, robj *key, robj **valref, dictEntryLink link, int overwrite, int updateKeySizes, int keepTTL){
    robj *val = *valref;
    int slot = getKeySlot(key->ptr);
    if (!link) {
        link = kvstoreDictFindLink(db->keys, slot, key->ptr, ((void *)0));
        (__builtin_expect(!!(link != ((void *)0)), 1) ? (void)0 : (_serverAssertWithInfo(((void *)0), key, "link != NULL", "db_InstSlice.c", 380) , abort()));
    }
    kvobj *old = dictGetKV(*link);
    kvobj *kvNew;
    int64_t oldlen = (int64_t)getObjectLength(old);
    int oldtype = old->type;
    ;
    if (overwrite) {
        ;
        ;
        ;
        ;
        old = dictGetKV(*link);
    }
    if ((old->refcount == 1 && old->encoding != 8) && (val->refcount == 1 && val->encoding != 8)) {
        robj tmp = *old;
        old->type = val->type;
        old->encoding = val->encoding;
        old->ptr = val->ptr;
        val->type = tmp.type;
        val->encoding = tmp.encoding;
        val->ptr = tmp.ptr;
        kvNew = old;
        old = val;
        if ((!keepTTL) && (getExpire(db, key->ptr, kvNew) >= 0))
            removeExpire(db, key);
    } else {
        val->lru = old->lru;
        long long expire = getExpire(db, key->ptr, old);
        int hasExpire = keepTTL && (expire != -1);
        kvNew = kvobjSet(key->ptr, val, hasExpire);
        ;
        if (expire >= 0) {
            if (keepTTL) {
                ;
                dictEntryLink exLink = kvstoreDictFindLink(db->expires, slot, key->ptr, ((void *)0));
                (__builtin_expect(!!(exLink != ((void *)0)), 1) ? (void)0 : (_serverAssertWithInfo(((void *)0), key, "exLink != NULL", "db_InstSlice.c", 438) , abort()));
                ;
            } else {
                ;
            }
        }
    }
    int64_t newlen = (int64_t)getObjectLength(kvNew);
    if (updateKeySizes) {
        if (oldtype == kvNew->type) {
            updateKeysizesHist(db, slot, oldtype, oldlen, newlen);
        } else {
            updateKeysizesHist(db, slot, oldtype, oldlen, -1);
            updateKeysizesHist(db, slot, kvNew->type, -1, newlen);
        }
    }
    ;
}


extern void setKey (client *c, redisDb *db, robj *key, robj **valref, int flags){
    setKeyByLink(c, db, key, valref, flags, ((void *)0));
}


extern void setKeyByLink (client *c, redisDb *db, robj *key, robj **valref, int flags, dictEntryLink *plink){
    dictEntryLink dummy = ((void *)0), *link = plink ? plink : &dummy;
    int exists;
    kvobj *oldval = ((void *)0);
    if (flags & 4) {
        ;
        oldval = dictGetKV(**link);
        exists = 1;
    } else if (flags & 8) {
        exists = 0;
    } else {
        oldval = lookupKeyWriteWithLink(db, key, link);
        exists = oldval != ((void *)0);
    }
    if (exists) {
        int oldtype = oldval->type;
        int newtype = (*valref)->type;
        dbSetValue(db, key, valref, *link, 1, 1, flags & 1);
        ;
        ;
    } else {
        dbAddByLink(db, key, valref, link);
    }
    ;
}


extern int dbGenericDelete (redisDb *db, robj *key, int async, int flags){
    dictEntryLink link;
    int table;
    int slot = getKeySlot(key->ptr);
    link = kvstoreDictTwoPhaseUnlinkFind(db->keys, slot, key->ptr, &table);
    if (link) {
        kvobj *kv = dictGetKV(*link);
        int64_t oldlen = (int64_t)getObjectLength(kv);
        int type = kv->type;
        ;
        ;
        ;
        ;
        ;
        kv = dictGetKV(*link);
        ;
        ;
        if (!(flags & (1ULL << 4)))
            updateKeysizesHist(db, slot, type, oldlen, -1);
        return 1;
    } else {
        ;
    }
}


extern int removeExpire (redisDb *db, robj *key){
    int table;
    int slot = getKeySlot(key->ptr);
    dictEntryLink link = kvstoreDictTwoPhaseUnlinkFind(db->expires, slot, key->ptr, &table);
    if (link == ((void *)0))
        return 0;
    dictEntry *de = *link;
    kvobj *kv = dictGetKV(de);
    kvobj *newkv = kvobjSetExpire(kv, -1);
    (__builtin_expect(!!(newkv == kv), 1) ? (void)0 : (_serverAssert("newkv == kv", "db_InstSlice.c", 868) , abort()));
    ;
    return 1;
}


extern kvobj * setExpireByLink (client *c, redisDb *db, sds key, long long when, dictEntryLink keyLink){
    int slot = getKeySlot(key);
    if (!keyLink) {
        keyLink = kvstoreDictFindLink(db->keys, slot, key, ((void *)0));
        (__builtin_expect(!!(keyLink != ((void *)0)), 1) ? (void)0 : (_serverAssert("keyLink != NULL", "db_InstSlice.c", 888) , abort()));
    }
    kvobj *kv = dictGetKV(*keyLink);
    long long old_when = kvobjGetExpire(kv);
    if (old_when != -1) {
        kvobj *kvnew = kvobjSetExpire(kv, when);
        (__builtin_expect(!!(kv == kvnew), 1) ? (void)0 : (_serverAssert("kv == kvnew", "db_InstSlice.c", 896) , abort()));
    } else {
        uint64_t hexpire = (((uint64_t)281474976710655L) + 1);
        if (kv->type == 4)
            hexpire = hashTypeRemoveFromExpires(&db->hexpires, kv);
        kvobj *kvnew = kvobjSetExpire(kv, when);
        if (kv != kvnew) {
            ;
            kv = kvnew;
        }
        dictEntry *de = kvstoreDictAddRaw(db->expires, slot, kv, ((void *)0));
        (__builtin_expect(!!(de != ((void *)0)), 1) ? (void)0 : (_serverAssert("de != NULL", "db_InstSlice.c", 912) , abort()));
        ;
    }
    int writable_slave = server.masterhost && server.repl_slave_ro == 0;
    ;
    return kv;
}


extern long long getExpire (redisDb *db, sds key, kvobj *kv){
    if (kv == ((void *)0))
        kv = dbFindExpires(db, key);
    if (kv == ((void *)0))
        return -1;
    return kvobjGetExpire(kv);
}


static void deleteKeyAndPropagate (redisDb *db, robj *keyobj, int notify_type, long long *key_mem_freed){
    mstime_t latency;
    int del_flag = notify_type == (1 << 8) ? (1ULL << 1) : (1ULL << 2);
    int lazy_flag = notify_type == (1 << 8) ? server.lazyfree_lazy_expire : server.lazyfree_lazy_eviction;
    char *latency_name = notify_type == (1 << 8) ? "expire-del" : "evict-del";
    char *notify_name = notify_type == (1 << 8) ? "expired" : "evicted";
    int static_key = keyobj->refcount == ((1 << 30) - 2);
    if (static_key) {
        keyobj = createStringObject(keyobj->ptr, sdslen(keyobj->ptr));
    }
    ;
    ;
    ;
    dbGenericDelete(db, keyobj, lazy_flag, del_flag);
    ;
    ;
    ;
    ;
    ;
    propagateDeletion(db, keyobj, lazy_flag);
    if (notify_type == (1 << 8)) {
        server.stat_expiredkeys++;
    } else
        server.stat_evictedkeys++;
    ;
}


extern void deleteExpiredKeyAndPropagate (redisDb *db, robj *keyobj){
    deleteKeyAndPropagate(db, keyobj, (1 << 8), ((void *)0));
}


extern void propagateDeletion (redisDb *db, robj *key, int lazy){
    robj *argv[2];
    ;
    ;
    ;
    ;
    int prev_replication_allowed = server.replication_allowed;
    ;
    ;
    server.replication_allowed = prev_replication_allowed;
    ;
    ;
}


extern int keyIsExpired (redisDb *db, sds key, kvobj *kv){
    if (server.loading)
        return 0;
    mstime_t when = getExpire(db, key, kv);
    if (when < 0)
        return 0;
    const mstime_t now = commandTimeSnapshot();
    return now > when;
}


extern int confAllowsExpireDel (){
    if (server.lazyexpire_nested_arbitrary_keys)
        return 1;
    return !(server.execution_nesting > 1 && server.executing_client->cmd->flags & (1ULL << 28));
}


keyStatus expireIfNeeded (redisDb *db, robj *key, kvobj *kv, int flags){
    ;
    if ((server.allow_access_expired) || (flags & 4) || (!keyIsExpired(db, key ? key->ptr : ((void *)0), kv)))
        return KEY_VALID;
    if (server.masterhost != ((void *)0)) {
        if (server.current_client && (server.current_client->flags & (1 << 1)))
            return KEY_VALID;
        if (!(flags & 1))
            return KEY_EXPIRED;
    }
    if (!(flags & 1) && !confAllowsExpireDel())
        return KEY_EXPIRED;
    if (flags & 2)
        return KEY_EXPIRED;
    if (isPausedActionsWithUpdate((1 << 2)))
        return KEY_EXPIRED;
    if (key) {
        deleteExpiredKeyAndPropagate(db, key);
    } else {
        sds keyname = kvobjGetKey(kv);
        robj *tmpkey = createStringObject(keyname, sdslen(keyname));
        deleteExpiredKeyAndPropagate(db, tmpkey);
        ;
    }
    return KEY_DELETED;
}


static kvobj * dbFindGeneric (kvstore *kvs, sds key){
    dictEntry *res = kvstoreDictFind(kvs, getKeySlot(key), key);
    return (res) ? dictGetKey(res) : ((void *)0);
}


extern kvobj * dbFindByLink (redisDb *db, sds key, dictEntryLink *plink){
    int slot = getKeySlot(key);
    dictEntryLink link, bucket;
    link = kvstoreDictFindLink(db->keys, slot, key, &bucket);
    if (link == ((void *)0)) {
        if (plink)
            *plink = bucket;
        return ((void *)0);
    } else {
        if (plink)
            *plink = link;
        return dictGetKV(*link);
    }
}


extern kvobj * dbFindExpires (redisDb *db, sds key){
    return dbFindGeneric(db->expires, key);
}


