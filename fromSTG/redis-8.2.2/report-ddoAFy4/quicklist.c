extern quicklistNode * quicklistCreateNode (){
    quicklistNode *node;
    node = zmalloc(sizeof (*node));
    node->entry = ((void *)0);
    node->count = 0;
    node->sz = 0;
    node->next = node->prev = ((void *)0);
    node->encoding = 1;
    node->container = 2;
    node->recompress = 0;
    node->dont_compress = 0;
    return node;
}


extern int __quicklistCompressNode (quicklistNode *node){
    if (node->dont_compress)
        return 0;
    (__builtin_expect(!!((node->prev && node->next)), 1) ? (void)0 : (_serverAssert("node->prev && node->next", "quicklist_InstSlice.c", 164) , abort()));
    node->recompress = 0;
    if (node->sz < 48)
        return 0;
    quicklistLZF *lzf = zmalloc(sizeof (*lzf) + node->sz);
    if (((lzf->sz = lzf_compress(node->entry, node->sz, lzf->compressed, node->sz)) == 0) || lzf->sz + 8 >= node->sz) {
        ;
        return 0;
    }
    lzf = zrealloc(lzf, sizeof (*lzf) + lzf->sz);
    ;
    node->entry = (unsigned char *)lzf;
    node->encoding = 2;
    return 1;
}


extern int __quicklistDecompressNode (quicklistNode *node){
    node->recompress = 0;
    void *decompressed = zmalloc(node->sz);
    quicklistLZF *lzf = (quicklistLZF *)node->entry;
    if (lzf_decompress(lzf->compressed, lzf->sz, decompressed, node->sz) == 0) {
        ;
        return 0;
    }
    ;
    node->entry = decompressed;
    node->encoding = 1;
    return 1;
}


extern void __quicklistCompress (const quicklist *quicklist, quicklistNode *node){
    if (quicklist->len == 0)
        return;
    (__builtin_expect(!!((quicklist->head->recompress == 0 && quicklist->tail->recompress == 0)), 1) ? (void)0 : (_serverAssert("quicklist->head->recompress == 0 && quicklist->tail->recompress == 0", "quicklist_InstSlice.c", 248) , abort()));
    if (!((quicklist)->compress != 0) || quicklist->len < (unsigned int)(quicklist->compress * 2))
        return;
    quicklistNode *forward = quicklist->head;
    quicklistNode *reverse = quicklist->tail;
    int depth = 0;
    int in_depth = 0;
    while (depth++ < quicklist->compress)
        {
            do {
                if ((forward) && (forward)->encoding == 2) {
                    __quicklistDecompressNode((forward));
                }
            } while (0);
            do {
                if ((reverse) && (reverse)->encoding == 2) {
                    __quicklistDecompressNode((reverse));
                }
            } while (0);
            if (forward == node || reverse == node)
                in_depth = 1;
            if (forward == reverse || forward->next == reverse)
                return;
            forward = forward->next;
            reverse = reverse->prev;
        }
    if (!in_depth)
        do {
            if ((node) && (node)->encoding == 1) {
                __quicklistCompressNode((node));
            }
        } while (0);
    do {
        if ((forward) && (forward)->encoding == 1) {
            __quicklistCompressNode((forward));
        }
    } while (0);
    do {
        if ((reverse) && (reverse)->encoding == 1) {
            __quicklistCompressNode((reverse));
        }
    } while (0);
}


extern void __quicklistInsertNode (quicklist *quicklist, quicklistNode *old_node, quicklistNode *new_node, int after){
    if (after) {
        new_node->prev = old_node;
        if (old_node) {
            new_node->next = old_node->next;
            if (old_node->next)
                old_node->next->prev = new_node;
            old_node->next = new_node;
        }
        if (quicklist->tail == old_node)
            quicklist->tail = new_node;
    } else {
        new_node->next = old_node;
        if (old_node) {
            new_node->prev = old_node->prev;
            if (old_node->prev)
                old_node->prev->next = new_node;
            old_node->prev = new_node;
        }
        if (quicklist->head == old_node)
            quicklist->head = new_node;
    }
    if (quicklist->len == 0) {
        quicklist->head = quicklist->tail = new_node;
    }
    quicklist->len++;
    if (old_node)
        do {
            if ((old_node)->recompress)
                do {
                    if (((old_node)) && ((old_node))->encoding == 1) {
                        __quicklistCompressNode(((old_node)));
                    }
                } while (0);
            else
                __quicklistCompress((quicklist), (old_node));
        } while (0);
    do {
        if ((new_node)->recompress)
            do {
                if (((new_node)) && ((new_node))->encoding == 1) {
                    __quicklistCompressNode(((new_node)));
                }
            } while (0);
        else
            __quicklistCompress((quicklist), (new_node));
    } while (0);
}


static size_t quicklistNodeNegFillLimit (int fill){
    (__builtin_expect(!!((fill < 0)), 1) ? (void)0 : (_serverAssert("fill < 0", "quicklist_InstSlice.c", 395) , abort()));
    size_t offset = (-fill) - 1;
    size_t max_level = sizeof (optimization_level) / sizeof (*optimization_level);
    if (offset >= max_level)
        offset = max_level - 1;
    return optimization_level[offset];
}


extern void quicklistNodeLimit (int fill, size_t *size, unsigned int *count){
    *size = (18446744073709551615UL);
    *count = (2147483647 * 2U + 1U);
    if (fill >= 0) {
        *count = (fill == 0) ? 1 : fill;
    } else {
        *size = quicklistNodeNegFillLimit(fill);
    }
}


extern int quicklistNodeExceedsLimit (int fill, size_t new_sz, unsigned int new_count){
    size_t sz_limit;
    unsigned int count_limit;
    quicklistNodeLimit(fill, &sz_limit, &count_limit);
    if (__builtin_expect(!!(sz_limit != (18446744073709551615UL)), 1)) {
        return new_sz > sz_limit;
    } else if (count_limit != (2147483647 * 2U + 1U)) {
        if (!((new_sz) <= 8192))
            return 1;
        return new_count > count_limit;
    }
    ;
}


static int isLargeElement (size_t sz, int fill){
    if (__builtin_expect(!!(packed_threshold != 0), 0))
        return sz >= packed_threshold;
    if (fill >= 0) {
        return !((sz) <= 8192);
    } else
        return sz > quicklistNodeNegFillLimit(fill);
}


extern int _quicklistNodeAllowInsert (const quicklistNode *node, const int fill, const size_t sz){
    if (__builtin_expect(!!(!node), 0))
        return 0;
    if (__builtin_expect(!!(((node)->container == 1) || isLargeElement(sz, fill)), 0))
        return 0;
    size_t new_sz = node->sz + sz + 8;
    if (__builtin_expect(!!(quicklistNodeExceedsLimit(fill, new_sz, node->count + 1)), 0))
        return 0;
    return 1;
}


extern int _quicklistNodeAllowMerge (const quicklistNode *a, const quicklistNode *b, const int fill){
    if (!a || !b)
        return 0;
    if (__builtin_expect(!!(((a)->container == 1) || ((b)->container == 1)), 0))
        return 0;
    unsigned int merge_sz = a->sz + b->sz - 7;
    if (__builtin_expect(!!(quicklistNodeExceedsLimit(fill, merge_sz, a->count + b->count)), 0))
        return 0;
    return 1;
}


static quicklistNode * __quicklistCreateNode (int container, void *value, size_t sz){
    quicklistNode *new_node = quicklistCreateNode();
    new_node->container = container;
    if (container == 1) {
        new_node->entry = zmalloc(sz);
        ;
    } else {
        new_node->entry = lpPrepend(lpNew(0), value, sz);
    }
    new_node->sz = sz;
    new_node->count++;
    return new_node;
}


static void __quicklistInsertPlainNode (quicklist *quicklist, quicklistNode *old_node, void *value, size_t sz, int after){
    quicklistNode *new_node = __quicklistCreateNode(1, value, sz);
    __quicklistInsertNode(quicklist, old_node, new_node, after);
    quicklist->count++;
}


extern void __quicklistDelNode (quicklist *quicklist, quicklistNode *node){
    quicklistBookmark *bm = _quicklistBookmarkFindByNode(quicklist, node);
    if (bm) {
        bm->node = node->next;
        if (!bm->node)
            _quicklistBookmarkDelete(quicklist, bm);
    }
    if (node->next)
        node->next->prev = node->prev;
    if (node->prev)
        node->prev->next = node->next;
    if (node == quicklist->tail) {
        quicklist->tail = node->prev;
    }
    if (node == quicklist->head) {
        quicklist->head = node->next;
    }
    quicklist->len--;
    quicklist->count -= node->count;
    __quicklistCompress(quicklist, ((void *)0));
    ;
    ;
}


extern int quicklistDelIndex (quicklist *quicklist, quicklistNode *node, unsigned char **p){
    int gone = 0;
    if (__builtin_expect(!!(((node)->container == 1)), 0)) {
        __quicklistDelNode(quicklist, node);
        return 1;
    }
    node->entry = lpDelete(node->entry, *p, p);
    node->count--;
    if (node->count == 0) {
        gone = 1;
        __quicklistDelNode(quicklist, node);
    } else {
        do {
            (node)->sz = lpBytes((node)->entry);
        } while (0);
    }
    quicklist->count--;
    return gone ? 1 : 0;
}


extern void quicklistReplaceEntry (quicklistIter *iter, quicklistEntry *entry, void *data, size_t sz){
    quicklist *quicklist = iter->quicklist;
    quicklistNode *node = entry->node;
    unsigned char *newentry;
    if (__builtin_expect(!!(!((entry->node)->container == 1) && !isLargeElement(sz, quicklist->fill) && (newentry = lpReplace(entry->node->entry, &entry->zi, data, sz)) != ((void *)0)), 1)) {
        entry->node->entry = newentry;
        do {
            (entry->node)->sz = lpBytes((entry->node)->entry);
        } while (0);
        do {
            if ((entry->node)->recompress)
                do {
                    if (((entry->node)) && ((entry->node))->encoding == 1) {
                        __quicklistCompressNode(((entry->node)));
                    }
                } while (0);
            else
                __quicklistCompress((quicklist), (entry->node));
        } while (0);
    } else if (((entry->node)->container == 1)) {
        if (isLargeElement(sz, quicklist->fill)) {
            ;
            entry->node->entry = zmalloc(sz);
            entry->node->sz = sz;
            ;
            do {
                if ((entry->node)->recompress)
                    do {
                        if (((entry->node)) && ((entry->node))->encoding == 1) {
                            __quicklistCompressNode(((entry->node)));
                        }
                    } while (0);
                else
                    __quicklistCompress((quicklist), (entry->node));
            } while (0);
        } else {
            quicklistInsertAfter(iter, entry, data, sz);
            __quicklistDelNode(quicklist, entry->node);
        }
    } else {
        quicklistNode *split_node = ((void *)0), *new_node;
        node->dont_compress = 1;
        if (entry->offset != node->count - 1 && entry->offset != -1)
            split_node = _quicklistSplitNode(node, entry->offset, 1);
        new_node = __quicklistCreateNode(isLargeElement(sz, quicklist->fill) ? 1 : 2, data, sz);
        __quicklistInsertNode(quicklist, node, new_node, 1);
        if (split_node)
            __quicklistInsertNode(quicklist, new_node, split_node, 1);
        quicklist->count++;
        if (entry->node->count == 1) {
            __quicklistDelNode(quicklist, entry->node);
        } else {
            unsigned char *p = lpSeek(entry->node->entry, -1);
            quicklistDelIndex(quicklist, entry->node, &p);
            entry->node->dont_compress = 0;
            new_node = _quicklistMergeNodes(quicklist, new_node);
            do {
                if ((new_node)->recompress)
                    do {
                        if (((new_node)) && ((new_node))->encoding == 1) {
                            __quicklistCompressNode(((new_node)));
                        }
                    } while (0);
                else
                    __quicklistCompress((quicklist), (new_node));
            } while (0);
            do {
                if ((new_node->prev)->recompress)
                    do {
                        if (((new_node->prev)) && ((new_node->prev))->encoding == 1) {
                            __quicklistCompressNode(((new_node->prev)));
                        }
                    } while (0);
                else
                    __quicklistCompress((quicklist), (new_node->prev));
            } while (0);
            if (new_node->next)
                do {
                    if ((new_node->next)->recompress)
                        do {
                            if (((new_node->next)) && ((new_node->next))->encoding == 1) {
                                __quicklistCompressNode(((new_node->next)));
                            }
                        } while (0);
                    else
                        __quicklistCompress((quicklist), (new_node->next));
                } while (0);
        }
    }
    do {
        (iter)->current = ((void *)0);
        (iter)->zi = ((void *)0);
    } while (0);
}


extern int quicklistReplaceAtIndex (quicklist *quicklist, long index, void *data, size_t sz){
    quicklistEntry entry;
    quicklistIter *iter = quicklistGetIteratorEntryAtIdx(quicklist, index, &entry);
    if (__builtin_expect(!!(iter), 1)) {
        quicklistReplaceEntry(iter, &entry, data, sz);
        quicklistReleaseIterator(iter);
        return 1;
    } else {
        ;
    }
}


extern quicklistNode * _quicklistListpackMerge (quicklist *quicklist, quicklistNode *a, quicklistNode *b){
    ;
    do {
        if ((a) && (a)->encoding == 2) {
            __quicklistDecompressNode((a));
        }
    } while (0);
    do {
        if ((b) && (b)->encoding == 2) {
            __quicklistDecompressNode((b));
        }
    } while (0);
    if ((lpMerge(&a->entry, &b->entry))) {
        quicklistNode *keep = ((void *)0), *nokeep = ((void *)0);
        if (!a->entry) {
            nokeep = a;
            keep = b;
        } else if (!b->entry) {
            nokeep = b;
            keep = a;
        }
        keep->count = lpLength(keep->entry);
        do {
            (keep)->sz = lpBytes((keep)->entry);
        } while (0);
        keep->recompress = 0;
        nokeep->count = 0;
        __quicklistDelNode(quicklist, nokeep);
        do {
            if ((keep)->recompress)
                do {
                    if (((keep)) && ((keep))->encoding == 1) {
                        __quicklistCompressNode(((keep)));
                    }
                } while (0);
            else
                __quicklistCompress((quicklist), (keep));
        } while (0);
        return keep;
    } else {
        return ((void *)0);
    }
}


extern quicklistNode * _quicklistMergeNodes (quicklist *quicklist, quicklistNode *center){
    int fill = quicklist->fill;
    quicklistNode *prev, *prev_prev, *next, *next_next, *target;
    prev = prev_prev = next = next_next = target = ((void *)0);
    if (center->prev) {
        prev = center->prev;
        if (center->prev->prev)
            prev_prev = center->prev->prev;
    }
    if (center->next) {
        next = center->next;
        if (center->next->next)
            next_next = center->next->next;
    }
    if (_quicklistNodeAllowMerge(prev, prev_prev, fill)) {
        _quicklistListpackMerge(quicklist, prev_prev, prev);
        prev_prev = prev = ((void *)0);
    }
    if (_quicklistNodeAllowMerge(next, next_next, fill)) {
        _quicklistListpackMerge(quicklist, next, next_next);
        next = next_next = ((void *)0);
    }
    if (_quicklistNodeAllowMerge(center, center->prev, fill)) {
        target = _quicklistListpackMerge(quicklist, center->prev, center);
        center = ((void *)0);
    } else {
        target = center;
    }
    if (_quicklistNodeAllowMerge(target, target->next, fill)) {
        target = _quicklistListpackMerge(quicklist, target, target->next);
    }
    return target;
}


extern quicklistNode * _quicklistSplitNode (quicklistNode *node, int offset, int after){
    size_t zl_sz = node->sz;
    quicklistNode *new_node = quicklistCreateNode();
    new_node->entry = zmalloc(zl_sz);
    ;
    if (offset < 0)
        offset = node->count + offset;
    int orig_start = after ? offset + 1 : 0;
    int orig_extent = after ? -1 : offset;
    int new_start = after ? 0 : offset;
    int new_extent = after ? offset + 1 : -1;
    ;
    node->entry = lpDeleteRange(node->entry, orig_start, orig_extent);
    node->count = lpLength(node->entry);
    do {
        (node)->sz = lpBytes((node)->entry);
    } while (0);
    new_node->entry = lpDeleteRange(new_node->entry, new_start, new_extent);
    new_node->count = lpLength(new_node->entry);
    do {
        (new_node)->sz = lpBytes((new_node)->entry);
    } while (0);
    ;
    return new_node;
}


extern void _quicklistInsert (quicklistIter *iter, quicklistEntry *entry, void *value, const size_t sz, int after){
    quicklist *quicklist = iter->quicklist;
    int full = 0, at_tail = 0, at_head = 0, avail_next = 0, avail_prev = 0;
    int fill = quicklist->fill;
    quicklistNode *node = entry->node;
    quicklistNode *new_node = ((void *)0);
    if (!node) {
        ;
        if (__builtin_expect(!!(isLargeElement(sz, quicklist->fill)), 0)) {
            __quicklistInsertPlainNode(quicklist, quicklist->tail, value, sz, after);
            return;
        }
        new_node = quicklistCreateNode();
        new_node->entry = lpPrepend(lpNew(0), value, sz);
        __quicklistInsertNode(quicklist, ((void *)0), new_node, after);
        new_node->count++;
        quicklist->count++;
        return;
    }
    if (!_quicklistNodeAllowInsert(node, fill, sz)) {
        ;
        full = 1;
    }
    if (after && (entry->offset == node->count - 1 || entry->offset == -1)) {
        ;
        at_tail = 1;
        if (_quicklistNodeAllowInsert(node->next, fill, sz)) {
            ;
            avail_next = 1;
        }
    }
    if (!after && (entry->offset == 0 || entry->offset == -(node->count))) {
        ;
        at_head = 1;
        if (_quicklistNodeAllowInsert(node->prev, fill, sz)) {
            ;
            avail_prev = 1;
        }
    }
    if (__builtin_expect(!!(isLargeElement(sz, quicklist->fill)), 0)) {
        if (((node)->container == 1) || (at_tail && after) || (at_head && !after)) {
            __quicklistInsertPlainNode(quicklist, node, value, sz, after);
        } else {
            do {
                if ((node) && (node)->encoding == 2) {
                    __quicklistDecompressNode((node));
                    (node)->recompress = 1;
                }
            } while (0);
            new_node = _quicklistSplitNode(node, entry->offset, after);
            quicklistNode *entry_node = __quicklistCreateNode(1, value, sz);
            __quicklistInsertNode(quicklist, node, entry_node, after);
            __quicklistInsertNode(quicklist, entry_node, new_node, after);
            quicklist->count++;
        }
        return;
    }
    if (!full && after) {
        ;
        do {
            if ((node) && (node)->encoding == 2) {
                __quicklistDecompressNode((node));
                (node)->recompress = 1;
            }
        } while (0);
        node->entry = lpInsertString(node->entry, value, sz, entry->zi, 1, ((void *)0));
        node->count++;
        do {
            (node)->sz = lpBytes((node)->entry);
        } while (0);
        do {
            if ((node)->recompress)
                do {
                    if (((node)) && ((node))->encoding == 1) {
                        __quicklistCompressNode(((node)));
                    }
                } while (0);
        } while (0);
    } else if (!full && !after) {
        ;
        do {
            if ((node) && (node)->encoding == 2) {
                __quicklistDecompressNode((node));
                (node)->recompress = 1;
            }
        } while (0);
        node->entry = lpInsertString(node->entry, value, sz, entry->zi, 0, ((void *)0));
        node->count++;
        do {
            (node)->sz = lpBytes((node)->entry);
        } while (0);
        do {
            if ((node)->recompress)
                do {
                    if (((node)) && ((node))->encoding == 1) {
                        __quicklistCompressNode(((node)));
                    }
                } while (0);
        } while (0);
    } else if (full && at_tail && avail_next && after) {
        ;
        new_node = node->next;
        do {
            if ((new_node) && (new_node)->encoding == 2) {
                __quicklistDecompressNode((new_node));
                (new_node)->recompress = 1;
            }
        } while (0);
        new_node->entry = lpPrepend(new_node->entry, value, sz);
        new_node->count++;
        do {
            (new_node)->sz = lpBytes((new_node)->entry);
        } while (0);
        do {
            if ((new_node)->recompress)
                do {
                    if (((new_node)) && ((new_node))->encoding == 1) {
                        __quicklistCompressNode(((new_node)));
                    }
                } while (0);
        } while (0);
        do {
            if ((node)->recompress)
                do {
                    if (((node)) && ((node))->encoding == 1) {
                        __quicklistCompressNode(((node)));
                    }
                } while (0);
        } while (0);
    } else if (full && at_head && avail_prev && !after) {
        ;
        new_node = node->prev;
        do {
            if ((new_node) && (new_node)->encoding == 2) {
                __quicklistDecompressNode((new_node));
                (new_node)->recompress = 1;
            }
        } while (0);
        new_node->entry = lpAppend(new_node->entry, value, sz);
        new_node->count++;
        do {
            (new_node)->sz = lpBytes((new_node)->entry);
        } while (0);
        do {
            if ((new_node)->recompress)
                do {
                    if (((new_node)) && ((new_node))->encoding == 1) {
                        __quicklistCompressNode(((new_node)));
                    }
                } while (0);
        } while (0);
        do {
            if ((node)->recompress)
                do {
                    if (((node)) && ((node))->encoding == 1) {
                        __quicklistCompressNode(((node)));
                    }
                } while (0);
        } while (0);
    } else if (full && ((at_tail && !avail_next && after) || (at_head && !avail_prev && !after))) {
        ;
        new_node = quicklistCreateNode();
        new_node->entry = lpPrepend(lpNew(0), value, sz);
        new_node->count++;
        do {
            (new_node)->sz = lpBytes((new_node)->entry);
        } while (0);
        __quicklistInsertNode(quicklist, node, new_node, after);
    } else if (full) {
        ;
        do {
            if ((node) && (node)->encoding == 2) {
                __quicklistDecompressNode((node));
                (node)->recompress = 1;
            }
        } while (0);
        new_node = _quicklistSplitNode(node, entry->offset, after);
        if (after) {
            new_node->entry = lpPrepend(new_node->entry, value, sz);
        } else
            new_node->entry = lpAppend(new_node->entry, value, sz);
        new_node->count++;
        do {
            (new_node)->sz = lpBytes((new_node)->entry);
        } while (0);
        __quicklistInsertNode(quicklist, node, new_node, after);
        _quicklistMergeNodes(quicklist, node);
    }
    quicklist->count++;
    do {
        (iter)->current = ((void *)0);
        (iter)->zi = ((void *)0);
    } while (0);
}


extern void quicklistInsertAfter (quicklistIter *iter, quicklistEntry *entry, void *value, const size_t sz){
    _quicklistInsert(iter, entry, value, sz, 1);
}


extern quicklistIter * quicklistGetIterator (quicklist *quicklist, int direction){
    quicklistIter *iter;
    iter = zmalloc(sizeof (*iter));
    if (direction == 0) {
        iter->current = quicklist->head;
        iter->offset = 0;
    } else if (direction == 1) {
        iter->current = quicklist->tail;
        iter->offset = -1;
    }
    iter->direction = direction;
    iter->quicklist = quicklist;
    iter->zi = ((void *)0);
    return iter;
}


extern quicklistIter * quicklistGetIteratorAtIdx (quicklist *quicklist, const int direction, const long long idx){
    quicklistNode *n;
    unsigned long long accum = 0;
    unsigned long long index;
    int forward = idx < 0 ? 0 : 1;
    index = forward ? idx : (-idx) - 1;
    if (index >= quicklist->count)
        return ((void *)0);
    int seek_forward = forward;
    unsigned long long seek_index = index;
    if (index > (quicklist->count - 1) / 2) {
        seek_forward = !forward;
        seek_index = quicklist->count - 1 - index;
    }
    n = seek_forward ? quicklist->head : quicklist->tail;
    while (__builtin_expect(!!(n), 1))
        {
            if ((accum + n->count) > seek_index) {
                break;
            } else {
                ;
                accum += n->count;
                n = seek_forward ? n->next : n->prev;
            }
        }
    if (!n)
        return ((void *)0);
    if (seek_forward != forward)
        accum = quicklist->count - n->count - accum;
    ;
    quicklistIter *iter = quicklistGetIterator(quicklist, direction);
    iter->current = n;
    if (forward) {
        iter->offset = index - accum;
    } else {
        iter->offset = (-index) - 1 + accum;
    }
    return iter;
}


extern void quicklistReleaseIterator (quicklistIter *iter){
    if (!iter)
        return;
    if (iter->current)
        do {
            if ((iter->current)->recompress)
                do {
                    if (((iter->current)) && ((iter->current))->encoding == 1) {
                        __quicklistCompressNode(((iter->current)));
                    }
                } while (0);
            else
                __quicklistCompress((iter->quicklist), (iter->current));
        } while (0);
    ;
}


extern int quicklistNext (quicklistIter *iter, quicklistEntry *entry){
    do {
        (entry)->zi = (entry)->value = ((void *)0);
        (entry)->longval = -123456789;
        (entry)->quicklist = ((void *)0);
        (entry)->node = ((void *)0);
        (entry)->offset = 123456789;
        (entry)->sz = 0;
    } while (0);
    if (!iter) {
        ;
        return 0;
    }
    entry->quicklist = iter->quicklist;
    entry->node = iter->current;
    if (!iter->current) {
        ;
        return 0;
    }
    unsigned char *(*nextFn)(unsigned char *, unsigned char *) = ((void *)0);
    int offset_update = 0;
    int plain = ((iter->current)->container == 1);
    if (!iter->zi) {
        do {
            if ((iter->current) && (iter->current)->encoding == 2) {
                __quicklistDecompressNode((iter->current));
                (iter->current)->recompress = 1;
            }
        } while (0);
        if (__builtin_expect(!!(plain), 0)) {
            iter->zi = iter->current->entry;
        } else
            iter->zi = lpSeek(iter->current->entry, iter->offset);
    } else if (__builtin_expect(!!(plain), 0)) {
        iter->zi = ((void *)0);
    } else {
        if (iter->direction == 0) {
            nextFn = lpNext;
            offset_update = 1;
        } else if (iter->direction == 1) {
            nextFn = lpPrev;
            offset_update = -1;
        }
        iter->zi = nextFn(iter->current->entry, iter->zi);
        iter->offset += offset_update;
    }
    entry->zi = iter->zi;
    entry->offset = iter->offset;
    if (iter->zi) {
        if (__builtin_expect(!!(plain), 0)) {
            entry->value = entry->node->entry;
            entry->sz = entry->node->sz;
            return 1;
        }
        unsigned int sz = 0;
        entry->value = lpGetValue(entry->zi, &sz, &entry->longval);
        entry->sz = sz;
        return 1;
    } else {
        do {
            if ((iter->current)->recompress)
                do {
                    if (((iter->current)) && ((iter->current))->encoding == 1) {
                        __quicklistCompressNode(((iter->current)));
                    }
                } while (0);
            else
                __quicklistCompress((iter->quicklist), (iter->current));
        } while (0);
        if (iter->direction == 0) {
            ;
            iter->current = iter->current->next;
            iter->offset = 0;
        } else if (iter->direction == 1) {
            ;
            iter->current = iter->current->prev;
            iter->offset = -1;
        }
        iter->zi = ((void *)0);
        return quicklistNext(iter, entry);
    }
}


extern quicklistIter * quicklistGetIteratorEntryAtIdx (quicklist *quicklist, const long long idx, quicklistEntry *entry){
    quicklistIter *iter = quicklistGetIteratorAtIdx(quicklist, 1, idx);
    if (!iter)
        return ((void *)0);
    (__builtin_expect(!!((quicklistNext(iter, entry))), 1) ? (void)0 : (_serverAssert("quicklistNext(iter, entry)", "quicklist_InstSlice.c", 1231) , abort()));
    return iter;
}


extern quicklistBookmark * _quicklistBookmarkFindByNode (quicklist *ql, quicklistNode *node){
    unsigned int i;
    for (i = 0; i < ql->bookmark_count; i++) {
        if (ql->bookmarks[i].node == node) {
            return &ql->bookmarks[i];
        }
    }
    return ((void *)0);
}


extern void _quicklistBookmarkDelete (quicklist *ql, quicklistBookmark *bm){
    int index = bm - ql->bookmarks;
    ;
    ql->bookmark_count--;
    ;
}


