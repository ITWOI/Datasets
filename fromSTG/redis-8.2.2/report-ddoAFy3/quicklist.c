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


extern void _quicklistInsertNodeBefore (quicklist *quicklist, quicklistNode *old_node, quicklistNode *new_node){
    __quicklistInsertNode(quicklist, old_node, new_node, 0);
}


extern void _quicklistInsertNodeAfter (quicklist *quicklist, quicklistNode *old_node, quicklistNode *new_node){
    __quicklistInsertNode(quicklist, old_node, new_node, 1);
}


static size_t quicklistNodeNegFillLimit (int fill){
    (__builtin_expect(!!((fill < 0)), 1) ? (void)0 : (_serverAssert("fill < 0", "quicklist_InstSlice.c", 399) , abort()));
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
    ;
}


extern int quicklistPushHead (quicklist *quicklist, void *value, size_t sz){
    quicklistNode *orig_head = quicklist->head;
    if (__builtin_expect(!!(isLargeElement(sz, quicklist->fill)), 0)) {
        __quicklistInsertPlainNode(quicklist, quicklist->head, value, sz, 0);
        return 1;
    }
    if (__builtin_expect(!!(_quicklistNodeAllowInsert(quicklist->head, quicklist->fill, sz)), 1)) {
        ;
        ;
    } else {
        quicklistNode *node = quicklistCreateNode();
        node->entry = lpPrepend(lpNew(0), value, sz);
        do {
            (node)->sz = lpBytes((node)->entry);
        } while (0);
        _quicklistInsertNodeBefore(quicklist, quicklist->head, node);
    }
    ;
    ;
    return (orig_head != quicklist->head);
}


extern int quicklistPushTail (quicklist *quicklist, void *value, size_t sz){
    quicklistNode *orig_tail = quicklist->tail;
    if (__builtin_expect(!!(isLargeElement(sz, quicklist->fill)), 0)) {
        __quicklistInsertPlainNode(quicklist, quicklist->tail, value, sz, 1);
        return 1;
    }
    if (__builtin_expect(!!(_quicklistNodeAllowInsert(quicklist->tail, quicklist->fill, sz)), 1)) {
        ;
        ;
    } else {
        quicklistNode *node = quicklistCreateNode();
        node->entry = lpAppend(lpNew(0), value, sz);
        do {
            (node)->sz = lpBytes((node)->entry);
        } while (0);
        _quicklistInsertNodeAfter(quicklist, quicklist->tail, node);
    }
    ;
    ;
    return (orig_tail != quicklist->tail);
}


extern void quicklistPush (quicklist *quicklist, void *value, const size_t sz, int where){
    if (quicklist->head)
        (__builtin_expect(!!((quicklist->head->encoding != 2)), 1) ? (void)0 : (_serverAssert("quicklist->head->encoding != QUICKLIST_NODE_ENCODING_LZF", "quicklist_InstSlice.c", 796) , abort()));
    if (quicklist->tail)
        (__builtin_expect(!!((quicklist->tail->encoding != 2)), 1) ? (void)0 : (_serverAssert("quicklist->tail->encoding != QUICKLIST_NODE_ENCODING_LZF", "quicklist_InstSlice.c", 798) , abort()));
    if (where == 0) {
        quicklistPushHead(quicklist, value, sz);
    } else if (where == -1) {
        quicklistPushTail(quicklist, value, sz);
    }
}


