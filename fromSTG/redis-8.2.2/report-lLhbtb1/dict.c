static inline keyCmpFunc dictGetCmpFunc (dict *d){
    if (d->useStoredKeyApi && d->type->storedKeyCompare)
        return d->type->storedKeyCompare;
    if (d->type->keyCompare)
        return d->type->keyCompare;
    return dictDefaultCompare;
}


static inline uint64_t dictHashKey (dict *d, const void *key, int isStoredKey){
    if (isStoredKey && d->type->storedHashFunction) {
        return d->type->storedHashFunction(key);
    } else
        return d->type->hashFunction(key);
}


static inline int entryIsKey (const dictEntry *de){
    return ((uintptr_t)de & (1 | 2));
}


static inline int entryIsNormal (const dictEntry *de){
    return ((uintptr_t)(void *)de & 7) == 0;
}


static inline int entryIsNoValue (const dictEntry *de){
    return ((uintptr_t)(void *)de & 7) == 4;
}


static inline dictEntry * createEntryNoValue (void *key, dictEntry *next){
    dictEntryNoValue *entry = zmalloc(sizeof (*entry));
    entry->key = key;
    entry->next = next;
    return (dictEntry *)(void *)((uintptr_t)(void *)entry | 4);
}


static inline dictEntry * encodeMaskedPtr (const void *ptr, unsigned int bits){
    (__builtin_expect(!!((((uintptr_t)ptr & 7) == 0)), 1) ? (void)0 : (_serverAssert("((uintptr_t)ptr & ENTRY_PTR_MASK) == 0", "dict_InstSlice.c", 156) , abort()));
    return (dictEntry *)(void *)((uintptr_t)ptr | bits);
}


static inline void * decodeMaskedPtr (const dictEntry *de){
    return (void *)((uintptr_t)(void *)de & ~7);
}


static inline dictEntryNoValue * decodeEntryNoValue (const dictEntry *de){
    return decodeMaskedPtr(de);
}


static inline int entryHasValue (const dictEntry *de){
    return entryIsNormal(de);
}


static void _dictReset (dict *d, int htidx){
    d->ht_table[htidx] = ((void *)0);
    d->ht_size_exp[htidx] = -1;
    d->ht_used[htidx] = 0;
}


extern int _dictResize (dict *d, unsigned long size, int *malloc_failed){
    ;
    (__builtin_expect(!!((!((d)->rehashidx != -1))), 1) ? (void)0 : (_serverAssert("!dictIsRehashing(d)", "dict_InstSlice.c", 205) , abort()));
    dictEntry **new_ht_table;
    unsigned long new_ht_used;
    signed char new_ht_size_exp = _dictNextExp(size);
    size_t newsize = ((new_ht_size_exp) == -1 ? 0 : (unsigned long)1 << (new_ht_size_exp));
    if (newsize < size || newsize * sizeof(dictEntry *) < newsize)
        return 1;
    if (new_ht_size_exp == d->ht_size_exp[0])
        return 1;
    if (malloc_failed) {
        new_ht_table = ztrycalloc(newsize * sizeof(dictEntry *));
        ;
        if (*malloc_failed)
            return 1;
    } else
        new_ht_table = zcalloc(newsize * sizeof(dictEntry *));
    new_ht_used = 0;
    d->ht_size_exp[1] = new_ht_size_exp;
    d->ht_used[1] = new_ht_used;
    d->ht_table[1] = new_ht_table;
    d->rehashidx = 0;
    ;
    ;
    if (d->ht_table[0] == ((void *)0) || d->ht_used[0] == 0) {
        ;
        ;
        ;
        d->ht_size_exp[0] = new_ht_size_exp;
        d->ht_used[0] = new_ht_used;
        d->ht_table[0] = new_ht_table;
        _dictReset(d, 1);
        d->rehashidx = -1;
        return 0;
    }
    if (d->type->force_full_rehash) {
        while (dictRehash(d, 1000))
            {
            }
    }
    return 0;
}


extern int _dictExpand (dict *d, unsigned long size, int *malloc_failed){
    if (((d)->rehashidx != -1) || d->ht_used[0] > size || ((d->ht_size_exp[0]) == -1 ? 0 : (unsigned long)1 << (d->ht_size_exp[0])) >= size)
        return 1;
    return _dictResize(d, size, malloc_failed);
}


extern int dictExpand (dict *d, unsigned long size){
    return _dictExpand(d, size, ((void *)0));
}


static void rehashEntriesInBucketAtIndex (dict *d, uint64_t idx){
    dictEntry *de = d->ht_table[0][idx];
    uint64_t h;
    dictEntry *nextde;
    while (de)
        {
            nextde = dictGetNext(de);
            void *key = dictGetKey(de);
            if (d->ht_size_exp[1] > d->ht_size_exp[0]) {
                h = dictHashKey(d, key, 1) & ((d->ht_size_exp[1]) == -1 ? 0 : (((d->ht_size_exp[1]) == -1 ? 0 : (unsigned long)1 << (d->ht_size_exp[1]))) - 1);
            } else {
                h = idx & ((d->ht_size_exp[1]) == -1 ? 0 : (((d->ht_size_exp[1]) == -1 ? 0 : (unsigned long)1 << (d->ht_size_exp[1]))) - 1);
            }
            if (d->type->no_value) {
                if (!d->ht_table[1][h]) {
                    if (!entryIsKey(de))
                        zfree(decodeMaskedPtr(de));
                    if (d->type->keys_are_odd) {
                        de = key;
                    } else
                        de = encodeMaskedPtr(key, 2);
                } else if (entryIsKey(de)) {
                    de = createEntryNoValue(key, d->ht_table[1][h]);
                } else {
                    (__builtin_expect(!!((entryIsNoValue(de))), 1) ? (void)0 : (_serverAssert("entryIsNoValue(de)", "dict_InstSlice.c", 320) , abort()));
                    dictSetNext(de, d->ht_table[1][h]);
                }
            } else {
                dictSetNext(de, d->ht_table[1][h]);
            }
            d->ht_table[1][h] = de;
            d->ht_used[0]--;
            d->ht_used[1]++;
            de = nextde;
        }
    d->ht_table[0][idx] = ((void *)0);
}


static int dictCheckRehashingCompleted (dict *d){
    if (d->ht_used[0] != 0)
        return 0;
    ;
    ;
    ;
    d->ht_table[0] = d->ht_table[1];
    d->ht_used[0] = d->ht_used[1];
    d->ht_size_exp[0] = d->ht_size_exp[1];
    _dictReset(d, 1);
    d->rehashidx = -1;
    return 1;
}


extern int dictRehash (dict *d, int n){
    int empty_visits = n * 10;
    unsigned long s0 = ((d->ht_size_exp[0]) == -1 ? 0 : (unsigned long)1 << (d->ht_size_exp[0]));
    unsigned long s1 = ((d->ht_size_exp[1]) == -1 ? 0 : (unsigned long)1 << (d->ht_size_exp[1]));
    if (dict_can_resize == DICT_RESIZE_FORBID || !((d)->rehashidx != -1))
        return 0;
    if (dict_can_resize == DICT_RESIZE_AVOID && ((s1 > s0 && s1 < dict_force_resize_ratio * s0) || (s1 < s0 && s0 < 8 * dict_force_resize_ratio * s1))) {
        return 0;
    }
    while (n-- && d->ht_used[0] != 0)
        {
            (__builtin_expect(!!((((d->ht_size_exp[0]) == -1 ? 0 : (unsigned long)1 << (d->ht_size_exp[0])) > (unsigned long)d->rehashidx)), 1) ? (void)0 : (_serverAssert("DICTHT_SIZE(d->ht_size_exp[0]) > (unsigned long)d->rehashidx", "dict_InstSlice.c", 375) , abort()));
            while (d->ht_table[0][d->rehashidx] == ((void *)0))
                {
                    d->rehashidx++;
                    if (--empty_visits == 0)
                        return 1;
                }
            rehashEntriesInBucketAtIndex(d, d->rehashidx);
            d->rehashidx++;
        }
    return !dictCheckRehashingCompleted(d);
}


extern int _dictBucketRehash (dict *d, uint64_t idx){
    if (d->pauserehash != 0)
        return 0;
    unsigned long s0 = ((d->ht_size_exp[0]) == -1 ? 0 : (unsigned long)1 << (d->ht_size_exp[0]));
    unsigned long s1 = ((d->ht_size_exp[1]) == -1 ? 0 : (unsigned long)1 << (d->ht_size_exp[1]));
    if (dict_can_resize == DICT_RESIZE_FORBID || !((d)->rehashidx != -1))
        return 0;
    if (dict_can_resize == DICT_RESIZE_AVOID && ((s1 > s0 && s1 < dict_force_resize_ratio * s0) || (s1 < s0 && s0 < 8 * dict_force_resize_ratio * s1))) {
        return 0;
    }
    rehashEntriesInBucketAtIndex(d, idx);
    dictCheckRehashingCompleted(d);
    return 1;
}


extern dictEntry * dictAddRaw (dict *d, void *key, dictEntry **existing){
    void *position = dictFindLinkForInsert(d, key, existing);
    if (!position)
        return ((void *)0);
    if (d->type->keyDup)
        key = d->type->keyDup(d, key);
    return dictInsertKeyAtLink(d, key, position);
}


dictEntry * dictInsertKeyAtLink (dict *d, void *key, dictEntryLink link){
    dictEntryLink bucket = link;
    dictEntry *entry;
    int htidx = ((d)->rehashidx != -1) ? 1 : 0;
    (__builtin_expect(!!((bucket >= &d->ht_table[htidx][0] && bucket <= &d->ht_table[htidx][((d->ht_size_exp[htidx]) == -1 ? 0 : (((d->ht_size_exp[htidx]) == -1 ? 0 : (unsigned long)1 << (d->ht_size_exp[htidx]))) - 1)])), 1) ? (void)0 : (_serverAssert("bucket >= &d->ht_table[htidx][0] && bucket <= &d->ht_table[htidx][DICTHT_SIZE_MASK(d->ht_size_exp[htidx])]", "dict_InstSlice.c", 470) , abort()));
    if (d->type->no_value) {
        if (!*bucket) {
            if (d->type->keys_are_odd) {
                entry = key;
                (__builtin_expect(!!((entryIsKey(entry))), 1) ? (void)0 : (_serverAssert("entryIsKey(entry)", "dict_InstSlice.c", 478) , abort()));
            } else {
                entry = encodeMaskedPtr(key, 2);
            }
        } else {
            entry = createEntryNoValue(key, *bucket);
        }
    } else {
        entry = zmalloc(sizeof (*entry));
        (__builtin_expect(!!((entryIsNormal(entry))), 1) ? (void)0 : (_serverAssert("entryIsNormal(entry)", "dict_InstSlice.c", 493) , abort()));
        entry->key = key;
        entry->next = *bucket;
    }
    ;
    d->ht_used[htidx]++;
    return entry;
}


extern int dictReplace (dict *d, void *key, void *val){
    dictEntry *entry, *existing;
    entry = dictAddRaw(d, key, &existing);
    if (entry) {
        dictSetVal(d, entry, val);
        return 1;
    }
    void *oldval = dictGetVal(existing);
    dictSetVal(d, existing, val);
    ;
    return 0;
}


extern void dictSetVal (dict *d, dictEntry *de, void *val){
    (__builtin_expect(!!((entryHasValue(de))), 1) ? (void)0 : (_serverAssert("entryHasValue(de)", "dict_InstSlice.c", 668) , abort()));
    ;
}


extern void * dictGetKey (const dictEntry *de){
    if ((uintptr_t)de & 1)
        return (void *)de;
    if ((uintptr_t)de & 2)
        return decodeMaskedPtr(de);
    if (entryIsNoValue(de))
        return decodeEntryNoValue(de)->key;
    return de->key;
}


extern void * dictGetVal (const dictEntry *de){
    (__builtin_expect(!!((entryHasValue(de))), 1) ? (void)0 : (_serverAssert("entryHasValue(de)", "dict_InstSlice.c", 696) , abort()));
    return de->v.val;
}


extern dictEntry * dictGetNext (const dictEntry *de){
    if (entryIsKey(de))
        return ((void *)0);
    if (entryIsNoValue(de))
        return decodeEntryNoValue(de)->next;
    return de->next;
}


static void dictSetNext (dictEntry *de, dictEntry *next){
    (__builtin_expect(!!((!entryIsKey(de))), 1) ? (void)0 : (_serverAssert("!entryIsKey(de)", "dict_InstSlice.c", 722) , abort()));
    if (entryIsNoValue(de)) {
        dictEntryNoValue *entry = decodeEntryNoValue(de);
        entry->next = next;
    } else {
        de->next = next;
    }
}


static int dictTypeResizeAllowed (dict *d, size_t size){
    if (d->type->resizeAllowed == ((void *)0))
        return 1;
    return d->type->resizeAllowed(((_dictNextExp(size)) == -1 ? 0 : (unsigned long)1 << (_dictNextExp(size))) * sizeof(dictEntry *), (double)d->ht_used[0] / ((d->ht_size_exp[0]) == -1 ? 0 : (unsigned long)1 << (d->ht_size_exp[0])));
}


extern int dictExpandIfNeeded (dict *d){
    if (((d)->rehashidx != -1))
        return 0;
    if (((d->ht_size_exp[0]) == -1 ? 0 : (unsigned long)1 << (d->ht_size_exp[0])) == 0) {
        dictExpand(d, (1 << (2)));
        return 0;
    }
    if ((dict_can_resize == DICT_RESIZE_ENABLE && d->ht_used[0] >= ((d->ht_size_exp[0]) == -1 ? 0 : (unsigned long)1 << (d->ht_size_exp[0]))) || (dict_can_resize != DICT_RESIZE_FORBID && d->ht_used[0] >= dict_force_resize_ratio * ((d->ht_size_exp[0]) == -1 ? 0 : (unsigned long)1 << (d->ht_size_exp[0])))) {
        if (dictTypeResizeAllowed(d, d->ht_used[0] + 1))
            dictExpand(d, d->ht_used[0] + 1);
        return 0;
    }
    return 1;
}


static int _dictExpandIfNeeded (dict *d){
    if (d->pauseAutoResize > 0)
        return 1;
    return dictExpandIfNeeded(d);
}


static void _dictRehashStepIfNeeded (dict *d, uint64_t visitedIdx){
    if ((!((d)->rehashidx != -1)) || (d->pauserehash != 0))
        return;
    if ((long)visitedIdx >= d->rehashidx && d->ht_table[0][visitedIdx]) {
        _dictBucketRehash(d, visitedIdx);
    } else {
        dictRehash(d, 1);
    }
}


static signed char _dictNextExp (unsigned long size){
    if (size <= (1 << (2)))
        return 2;
    if (size >= 9223372036854775807L)
        return (8 * sizeof(long) - 1);
    return 8 * sizeof(long) - __builtin_clzl(size - 1);
}


extern dictEntryLink dictFindLinkForInsert (dict *d, const void *key, dictEntry **existing){
    unsigned long idx, table;
    dictCmpCache cmpCache = {0};
    dictEntry *he;
    uint64_t hash = dictHashKey(d, key, d->useStoredKeyApi);
    if (existing)
        *existing = ((void *)0);
    idx = hash & ((d->ht_size_exp[0]) == -1 ? 0 : (((d->ht_size_exp[0]) == -1 ? 0 : (unsigned long)1 << (d->ht_size_exp[0]))) - 1);
    _dictRehashStepIfNeeded(d, idx);
    _dictExpandIfNeeded(d);
    keyCmpFunc cmpFunc = dictGetCmpFunc(d);
    for (table = 0; table <= 1; table++) {
        if (table == 0 && (long)idx < d->rehashidx)
            continue;
        ;
        idx = hash & ((d->ht_size_exp[table]) == -1 ? 0 : (((d->ht_size_exp[table]) == -1 ? 0 : (unsigned long)1 << (d->ht_size_exp[table]))) - 1);
        he = d->ht_table[table][idx];
        while (he)
            {
                void *he_key = dictGetKey(he);
                if (key == he_key || cmpFunc(&cmpCache, key, he_key)) {
                    if (existing)
                        *existing = he;
                    return ((void *)0);
                }
                he = dictGetNext(he);
            }
        if (!((d)->rehashidx != -1))
            break;
        ;
    }
    dictEntry **bucket = &d->ht_table[((d)->rehashidx != -1) ? 1 : 0][idx];
    return bucket;
}


static int dictDefaultCompare (dictCmpCache *cache, const void *key1, const void *key2){
    ;
    return key1 == key2;
}


