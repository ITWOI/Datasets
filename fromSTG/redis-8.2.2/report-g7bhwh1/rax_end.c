#include "header_func.h"
static inline void raxStackInit (raxStack *ts){
    ts->stack = ts->static_items;
    ts->items = 0;
    ts->maxitems = 32;
    ts->oom = 0;
}
static inline int raxStackPush (raxStack *ts, void *ptr){
    if (ts->items == ts->maxitems) {
        if (ts->stack == ts->static_items) {
            ts->stack = zmalloc(sizeof(void *) * ts->maxitems * 2);
            if (ts->stack == ((void *)0)) {
                ts->stack = ts->static_items;
                ts->oom = 1;
                (*__errno_location()) = 12;
                return 0;
            }
            memcpy(ts->stack, ts->static_items, sizeof(void *) * ts->maxitems);
        } else {
            void **newalloc = zrealloc(ts->stack, sizeof(void *) * ts->maxitems * 2);
            if (newalloc == ((void *)0)) {
                ts->oom = 1;
                (*__errno_location()) = 12;
                return 0;
            }
            ts->stack = newalloc;
        }
        ts->maxitems *= 2;
    }
    ts->stack[ts->items] = ptr;
    ts->items++;
    return 1;
}
static inline void * raxStackPop (raxStack *ts){
    if (ts->items == 0)
        return ((void *)0);
    ts->items--;
    return ts->stack[ts->items];
}
static inline void * raxStackPeek (raxStack *ts){
    if (ts->items == 0)
        return ((void *)0);
    return ts->stack[ts->items - 1];
}
extern raxNode * raxNewNode (size_t children, int datafield){
    size_t nodesize = sizeof(raxNode) + children + ((sizeof(void *) - (((children) + 4) % sizeof(void *))) & (sizeof(void *) - 1)) + sizeof(raxNode *) * children;
    if (datafield)
        nodesize += sizeof(void *);
    raxNode *node = zmalloc(nodesize);
    if (node == ((void *)0))
        return ((void *)0);
    node->iskey = 0;
    node->isnull = 0;
    node->iscompr = 0;
    node->size = children;
    return node;
}
extern raxNode * raxReallocForData (raxNode *n, void *data){
    if (data == ((void *)0))
        return n;
    size_t curlen = (sizeof(raxNode) + (n)->size + ((sizeof(void *) - ((((n)->size) + 4) % sizeof(void *))) & (sizeof(void *) - 1)) + ((n)->iscompr ? sizeof(raxNode *) : sizeof(raxNode *) * (n)->size) + (((n)->iskey && !(n)->isnull) * sizeof(void *)));
    return zrealloc(n, curlen + sizeof(void *));
}
extern void raxSetData (raxNode *n, void *data){
    n->iskey = 1;
    if (data != ((void *)0)) {
        n->isnull = 0;
        void **ndata = (void **)((char *)n + (sizeof(raxNode) + (n)->size + ((sizeof(void *) - ((((n)->size) + 4) % sizeof(void *))) & (sizeof(void *) - 1)) + ((n)->iscompr ? sizeof(raxNode *) : sizeof(raxNode *) * (n)->size) + (((n)->iskey && !(n)->isnull) * sizeof(void *))) - sizeof(void *));
        memcpy(ndata, &data, sizeof (data));
    } else {
        n->isnull = 1;
    }
}
extern void * raxGetData (raxNode *n){
    if (n->isnull)
        return ((void *)0);
    void **ndata = (void **)((char *)n + (sizeof(raxNode) + (n)->size + ((sizeof(void *) - ((((n)->size) + 4) % sizeof(void *))) & (sizeof(void *) - 1)) + ((n)->iscompr ? sizeof(raxNode *) : sizeof(raxNode *) * (n)->size) + (((n)->iskey && !(n)->isnull) * sizeof(void *))) - sizeof(void *));
    void *data;
    memcpy(&data, ndata, sizeof (data));
    return data;
}
extern raxNode * raxAddChild (raxNode *n, unsigned char c, raxNode **childptr, raxNode ***parentlink){
    (__builtin_expect(!!((n->iscompr == 0)), 1) ? (void)0 : (_serverAssert("n->iscompr == 0", "rax_InstSlice.c", 217) , abort()));
    size_t curlen = (sizeof(raxNode) + (n)->size + ((sizeof(void *) - ((((n)->size) + 4) % sizeof(void *))) & (sizeof(void *) - 1)) + ((n)->iscompr ? sizeof(raxNode *) : sizeof(raxNode *) * (n)->size) + (((n)->iskey && !(n)->isnull) * sizeof(void *)));
    n->size++;
    size_t newlen = (sizeof(raxNode) + (n)->size + ((sizeof(void *) - ((((n)->size) + 4) % sizeof(void *))) & (sizeof(void *) - 1)) + ((n)->iscompr ? sizeof(raxNode *) : sizeof(raxNode *) * (n)->size) + (((n)->iskey && !(n)->isnull) * sizeof(void *)));
    n->size--;
    raxNode *child = raxNewNode(0, 0);
    if (child == ((void *)0))
        return ((void *)0);
    raxNode *newn = zrealloc(n, newlen);
    if (newn == ((void *)0)) {
        ;
        return ((void *)0);
    }
    n = newn;
    int pos;
    for (pos = 0; pos < n->size; pos++) {
        if (n->data[pos] > c)
            break;
    }
    unsigned char *src, *dst;
    if (n->iskey && !n->isnull) {
        ;
        dst = ((unsigned char *)n + newlen - sizeof(void *));
    }
    size_t shift = newlen - curlen - sizeof(void *);
    src = n->data + pos;
    n->data[pos] = c;
    n->size++;
    src = (unsigned char *)((raxNode **)((n)->data + (n)->size + ((sizeof(void *) - ((((n)->size) + 4) % sizeof(void *))) & (sizeof(void *) - 1))));
    raxNode **childfield = (raxNode **)(src + sizeof(raxNode *) * pos);
    *childptr = child;
    *parentlink = childfield;
    return n;
}
extern raxNode * raxCompressNode (raxNode *n, unsigned char *s, size_t len, raxNode **child){
    (__builtin_expect(!!((n->size == 0 && n->iscompr == 0)), 1) ? (void)0 : (_serverAssert("n->size == 0 && n->iscompr == 0", "rax_InstSlice.c", 354) , abort()));
    void *data = ((void *)0);
    size_t newsize;
    *child = raxNewNode(0, 0);
    if (*child == ((void *)0))
        return ((void *)0);
    newsize = sizeof(raxNode) + len + ((sizeof(void *) - (((len) + 4) % sizeof(void *))) & (sizeof(void *) - 1)) + sizeof(raxNode *);
    if (n->iskey) {
        data = raxGetData(n);
        if (!n->isnull)
            newsize += sizeof(void *);
    }
    raxNode *newn = zrealloc(n, newsize);
    if (newn == ((void *)0)) {
        ;
        return ((void *)0);
    }
    n = newn;
    n->iscompr = 1;
    n->size = len;
    if (n->iskey)
        raxSetData(n, data);
    raxNode **childfield = ((raxNode **)(((char *)(n)) + (sizeof(raxNode) + (n)->size + ((sizeof(void *) - ((((n)->size) + 4) % sizeof(void *))) & (sizeof(void *) - 1)) + ((n)->iscompr ? sizeof(raxNode *) : sizeof(raxNode *) * (n)->size) + (((n)->iskey && !(n)->isnull) * sizeof(void *))) - sizeof(raxNode *) - (((n)->iskey && !(n)->isnull) ? sizeof(void *) : 0)));
    return n;
}
static inline size_t raxLowWalk (rax *rax, unsigned char *s, size_t len, raxNode **stopnode, raxNode ***plink, int *splitpos, raxStack *ts){
    raxNode *h = rax->head;
    raxNode **parentlink = &rax->head;
    size_t i = 0;
    size_t j = 0;
    while (h->size && i < len)
        {
            ;
            unsigned char *v = h->data;
            if (h->iscompr) {
                for (j = 0; j < h->size && i < len; j++ , i++) {
                    if (v[j] != s[i])
                        break;
                }
                if (j != h->size)
                    break;
            } else {
                for (j = 0; j < h->size; j++) {
                    if (v[j] == s[i])
                        break;
                }
                if (j == h->size)
                    break;
                i++;
            }
            if (ts)
                raxStackPush(ts, h);
            raxNode **children = ((raxNode **)((h)->data + (h)->size + ((sizeof(void *) - ((((h)->size) + 4) % sizeof(void *))) & (sizeof(void *) - 1))));
            if (h->iscompr)
                j = 0;
            memcpy(&h, children + j, sizeof (h));
            parentlink = children + j;
            j = 0;
        }
    ;
    if (stopnode)
        *stopnode = h;
    if (plink)
        *plink = parentlink;
    if (splitpos && h->iscompr)
        *splitpos = j;
    return i;
}
extern int raxGenericInsert (rax *rax, unsigned char *s, size_t len, void *data, void **old, int overwrite){
    size_t i;
    int j = 0;
    raxNode *h, **parentlink;
    i = raxLowWalk(rax, s, len, &h, &parentlink, &j, ((void *)0));
    if (i == len && (!h->iscompr || j == 0)) {
        ;
        if (!h->iskey || (h->isnull && overwrite)) {
            h = raxReallocForData(h, data);
        }
        if (h == ((void *)0)) {
            ;
            return 0;
        }
        if (h->iskey) {
            if (old)
                *old = raxGetData(h);
            if (overwrite)
                raxSetData(h, data);
            return 0;
        }
        raxSetData(h, data);
        return 1;
    }
    if (h->iscompr && i != len) {
        ;
        raxNode **childfield = ((raxNode **)(((char *)(h)) + (sizeof(raxNode) + (h)->size + ((sizeof(void *) - ((((h)->size) + 4) % sizeof(void *))) & (sizeof(void *) - 1)) + ((h)->iscompr ? sizeof(raxNode *) : sizeof(raxNode *) * (h)->size) + (((h)->iskey && !(h)->isnull) * sizeof(void *))) - sizeof(raxNode *) - (((h)->iskey && !(h)->isnull) ? sizeof(void *) : 0)));
        raxNode *next;
        memcpy(&next, childfield, sizeof (next));
        size_t trimmedlen = j;
        size_t postfixlen = h->size - j - 1;
        int split_node_is_key = !trimmedlen && h->iskey && !h->isnull;
        size_t nodesize;
        raxNode *splitnode = raxNewNode(1, split_node_is_key);
        raxNode *trimmed = ((void *)0);
        raxNode *postfix = ((void *)0);
        if (trimmedlen) {
            nodesize = sizeof(raxNode) + trimmedlen + ((sizeof(void *) - (((trimmedlen) + 4) % sizeof(void *))) & (sizeof(void *) - 1)) + sizeof(raxNode *);
            if (h->iskey && !h->isnull)
                nodesize += sizeof(void *);
            trimmed = zmalloc(nodesize);
        }
        if (postfixlen) {
            nodesize = sizeof(raxNode) + postfixlen + ((sizeof(void *) - (((postfixlen) + 4) % sizeof(void *))) & (sizeof(void *) - 1)) + sizeof(raxNode *);
            postfix = zmalloc(nodesize);
        }
        if (splitnode == ((void *)0) || (trimmedlen && trimmed == ((void *)0)) || (postfixlen && postfix == ((void *)0))) {
            ;
            return 0;
        }
        splitnode->data[0] = h->data[j];
        if (j == 0) {
            if (h->iskey) {
                void *ndata = raxGetData(h);
                raxSetData(splitnode, ndata);
            }
            ;
        } else {
            trimmed->size = j;
            trimmed->iscompr = j > 1 ? 1 : 0;
            trimmed->iskey = h->iskey;
            trimmed->isnull = h->isnull;
            if (h->iskey && !h->isnull) {
                void *ndata = raxGetData(h);
                raxSetData(trimmed, ndata);
            }
            raxNode **cp = ((raxNode **)(((char *)(trimmed)) + (sizeof(raxNode) + (trimmed)->size + ((sizeof(void *) - ((((trimmed)->size) + 4) % sizeof(void *))) & (sizeof(void *) - 1)) + ((trimmed)->iscompr ? sizeof(raxNode *) : sizeof(raxNode *) * (trimmed)->size) + (((trimmed)->iskey && !(trimmed)->isnull) * sizeof(void *))) - sizeof(raxNode *) - (((trimmed)->iskey && !(trimmed)->isnull) ? sizeof(void *) : 0)));
            parentlink = cp;
            rax->numnodes++;
        }
        if (postfixlen) {
            postfix->iskey = 0;
            postfix->isnull = 0;
            postfix->size = postfixlen;
            postfix->iscompr = postfixlen > 1;
            raxNode **cp = ((raxNode **)(((char *)(postfix)) + (sizeof(raxNode) + (postfix)->size + ((sizeof(void *) - ((((postfix)->size) + 4) % sizeof(void *))) & (sizeof(void *) - 1)) + ((postfix)->iscompr ? sizeof(raxNode *) : sizeof(raxNode *) * (postfix)->size) + (((postfix)->iskey && !(postfix)->isnull) * sizeof(void *))) - sizeof(raxNode *) - (((postfix)->iskey && !(postfix)->isnull) ? sizeof(void *) : 0)));
            rax->numnodes++;
        } else {
            postfix = next;
        }
        raxNode **splitchild = ((raxNode **)(((char *)(splitnode)) + (sizeof(raxNode) + (splitnode)->size + ((sizeof(void *) - ((((splitnode)->size) + 4) % sizeof(void *))) & (sizeof(void *) - 1)) + ((splitnode)->iscompr ? sizeof(raxNode *) : sizeof(raxNode *) * (splitnode)->size) + (((splitnode)->iskey && !(splitnode)->isnull) * sizeof(void *))) - sizeof(raxNode *) - (((splitnode)->iskey && !(splitnode)->isnull) ? sizeof(void *) : 0)));
        h = splitnode;
    } else if (h->iscompr && i == len) {
        ;
        size_t postfixlen = h->size - j;
        size_t nodesize = sizeof(raxNode) + postfixlen + ((sizeof(void *) - (((postfixlen) + 4) % sizeof(void *))) & (sizeof(void *) - 1)) + sizeof(raxNode *);
        if (data != ((void *)0))
            nodesize += sizeof(void *);
        raxNode *postfix = zmalloc(nodesize);
        nodesize = sizeof(raxNode) + j + ((sizeof(void *) - (((j) + 4) % sizeof(void *))) & (sizeof(void *) - 1)) + sizeof(raxNode *);
        if (h->iskey && !h->isnull)
            nodesize += sizeof(void *);
        raxNode *trimmed = zmalloc(nodesize);
        if (postfix == ((void *)0) || trimmed == ((void *)0)) {
            ;
            return 0;
        }
        raxNode **childfield = ((raxNode **)(((char *)(h)) + (sizeof(raxNode) + (h)->size + ((sizeof(void *) - ((((h)->size) + 4) % sizeof(void *))) & (sizeof(void *) - 1)) + ((h)->iscompr ? sizeof(raxNode *) : sizeof(raxNode *) * (h)->size) + (((h)->iskey && !(h)->isnull) * sizeof(void *))) - sizeof(raxNode *) - (((h)->iskey && !(h)->isnull) ? sizeof(void *) : 0)));
        raxNode *next;
        memcpy(&next, childfield, sizeof (next));
        postfix->size = postfixlen;
        postfix->iscompr = postfixlen > 1;
        postfix->iskey = 1;
        postfix->isnull = 0;
        raxSetData(postfix, data);
        raxNode **cp = ((raxNode **)(((char *)(postfix)) + (sizeof(raxNode) + (postfix)->size + ((sizeof(void *) - ((((postfix)->size) + 4) % sizeof(void *))) & (sizeof(void *) - 1)) + ((postfix)->iscompr ? sizeof(raxNode *) : sizeof(raxNode *) * (postfix)->size) + (((postfix)->iskey && !(postfix)->isnull) * sizeof(void *))) - sizeof(raxNode *) - (((postfix)->iskey && !(postfix)->isnull) ? sizeof(void *) : 0)));
        rax->numnodes++;
        trimmed->size = j;
        trimmed->iscompr = j > 1;
        trimmed->iskey = 0;
        trimmed->isnull = 0;
        if (h->iskey) {
            void *aux = raxGetData(h);
            raxSetData(trimmed, aux);
        }
        ;
        return 1;
    }
    while (i < len)
        {
            raxNode *child;
            if (h->size == 0 && len - i > 1) {
                ;
                size_t comprsize = len - i;
                if (comprsize > ((1 << 29) - 1))
                    comprsize = ((1 << 29) - 1);
                raxNode *newh = raxCompressNode(h, s + i, comprsize, &child);
                if (newh == ((void *)0))
                    goto oom;
                h = newh;
                parentlink = ((raxNode **)(((char *)(h)) + (sizeof(raxNode) + (h)->size + ((sizeof(void *) - ((((h)->size) + 4) % sizeof(void *))) & (sizeof(void *) - 1)) + ((h)->iscompr ? sizeof(raxNode *) : sizeof(raxNode *) * (h)->size) + (((h)->iskey && !(h)->isnull) * sizeof(void *))) - sizeof(raxNode *) - (((h)->iskey && !(h)->isnull) ? sizeof(void *) : 0)));
                i += comprsize;
            } else {
                ;
                raxNode **new_parentlink;
                raxNode *newh = raxAddChild(h, s[i], &child, &new_parentlink);
                if (newh == ((void *)0))
                    goto oom;
                h = newh;
                parentlink = new_parentlink;
                i++;
            }
            rax->numnodes++;
            h = child;
        }
    raxNode *newh = raxReallocForData(h, data);
    if (newh == ((void *)0))
        goto oom;
    h = newh;
    if (!h->iskey)
        rax->numele++;
    raxSetData(h, data);
    return 1;
  oom:
    if (h->size == 0) {
        h->isnull = 1;
        h->iskey = 1;
        rax->numele++;
        (__builtin_expect(!!((raxRemove(rax, s, i, ((void *)0)) != 0)), 1) ? (void)0 : (_serverAssert("raxRemove(rax,s,i,NULL) != 0", "rax_InstSlice.c", 855) , abort()));
    }
    ;
    return 0;
}
extern raxNode ** raxFindParentLink (raxNode *parent, raxNode *child){
    raxNode **cp = ((raxNode **)((parent)->data + (parent)->size + ((sizeof(void *) - ((((parent)->size) + 4) % sizeof(void *))) & (sizeof(void *) - 1))));
    raxNode *c;
    while (1)
        {
            memcpy(&c, cp, sizeof (c));
            if (c == child)
                break;
            cp++;
        }
    return cp;
}
extern raxNode * raxRemoveChild (raxNode *parent, raxNode *child){
    ;
    if (parent->iscompr) {
        void *data = ((void *)0);
        if (parent->iskey)
            data = raxGetData(parent);
        parent->isnull = 0;
        parent->iscompr = 0;
        parent->size = 0;
        if (parent->iskey)
            raxSetData(parent, data);
        return parent;
    }
    raxNode **cp = ((raxNode **)((parent)->data + (parent)->size + ((sizeof(void *) - ((((parent)->size) + 4) % sizeof(void *))) & (sizeof(void *) - 1))));
    raxNode **c = cp;
    unsigned char *e = parent->data;
    while (1)
        {
            raxNode *aux;
            memcpy(&aux, c, sizeof (aux));
            if (aux == child)
                break;
            c++;
            e++;
        }
    int taillen = parent->size - (e - parent->data) - 1;
    memmove(e, e + 1, taillen);
    size_t shift = ((parent->size + 4) % sizeof(void *)) == 1 ? sizeof(void *) : 0;
    if (shift)
        memmove(((char *)cp) - shift, cp, (parent->size - taillen - 1) * sizeof(raxNode **));
    size_t valuelen = (parent->iskey && !parent->isnull) ? sizeof(void *) : 0;
    memmove(((char *)c) - shift, c + 1, taillen * sizeof(raxNode **) + valuelen);
    parent->size--;
    raxNode *newnode = zrealloc(parent, (sizeof(raxNode) + (parent)->size + ((sizeof(void *) - ((((parent)->size) + 4) % sizeof(void *))) & (sizeof(void *) - 1)) + ((parent)->iscompr ? sizeof(raxNode *) : sizeof(raxNode *) * (parent)->size) + (((parent)->iskey && !(parent)->isnull) * sizeof(void *))));
    return newnode ? newnode : parent;
}
extern int raxRemove (rax *rax, unsigned char *s, size_t len, void **old){
    raxNode *h;
    raxStack ts;
    raxStackInit(&ts);
    int splitpos = 0;
    size_t i = raxLowWalk(rax, s, len, &h, ((void *)0), &splitpos, &ts);
    if (i != len || (h->iscompr && splitpos != 0) || !h->iskey) {
        ;
        return 0;
    }
    if (old)
        *old = raxGetData(h);
    h->iskey = 0;
    rax->numele--;
    int trycompress = 0;
    if (h->size == 0) {
        ;
        raxNode *child = ((void *)0);
        while (h != rax->head)
            {
                child = h;
                rax->numnodes--;
                h = raxStackPop(&ts);
                if (h->iskey || (!h->iscompr && h->size != 1))
                    break;
            }
        if (child) {
            ;
            raxNode *new = raxRemoveChild(h, child);
            if (new != h) {
                raxNode *parent = raxStackPeek(&ts);
                raxNode **parentlink;
                if (parent == ((void *)0)) {
                    parentlink = &rax->head;
                } else {
                    parentlink = raxFindParentLink(parent, h);
                }
                memcpy(parentlink, &new, sizeof (new));
            }
            if (new->size == 1 && new->iskey == 0) {
                trycompress = 1;
                h = new;
            }
        }
    } else if (h->size == 1) {
        trycompress = 1;
    }
    if (trycompress && ts.oom)
        trycompress = 0;
    if (trycompress) {
        ;
        raxNode *parent;
        while (1)
            {
                parent = raxStackPop(&ts);
                if (!parent || parent->iskey || (!parent->iscompr && parent->size != 1))
                    break;
                h = parent;
            }
        raxNode *start = h;
        size_t comprsize = h->size;
        int nodes = 1;
        while (h->size != 0)
            {
                raxNode **cp = ((raxNode **)(((char *)(h)) + (sizeof(raxNode) + (h)->size + ((sizeof(void *) - ((((h)->size) + 4) % sizeof(void *))) & (sizeof(void *) - 1)) + ((h)->iscompr ? sizeof(raxNode *) : sizeof(raxNode *) * (h)->size) + (((h)->iskey && !(h)->isnull) * sizeof(void *))) - sizeof(raxNode *) - (((h)->iskey && !(h)->isnull) ? sizeof(void *) : 0)));
                memcpy(&h, cp, sizeof (h));
                if (h->iskey || (!h->iscompr && h->size != 1))
                    break;
                if (comprsize + h->size > ((1 << 29) - 1))
                    break;
                nodes++;
                comprsize += h->size;
            }
        if (nodes > 1) {
            size_t nodesize = sizeof(raxNode) + comprsize + ((sizeof(void *) - (((comprsize) + 4) % sizeof(void *))) & (sizeof(void *) - 1)) + sizeof(raxNode *);
            raxNode *new = zmalloc(nodesize);
            if (new == ((void *)0)) {
                ;
                return 1;
            }
            new->iskey = 0;
            new->isnull = 0;
            new->iscompr = 1;
            new->size = comprsize;
            rax->numnodes++;
            comprsize = 0;
            h = start;
            while (h->size != 0)
                {
                    ;
                    comprsize += h->size;
                    raxNode **cp = ((raxNode **)(((char *)(h)) + (sizeof(raxNode) + (h)->size + ((sizeof(void *) - ((((h)->size) + 4) % sizeof(void *))) & (sizeof(void *) - 1)) + ((h)->iscompr ? sizeof(raxNode *) : sizeof(raxNode *) * (h)->size) + (((h)->iskey && !(h)->isnull) * sizeof(void *))) - sizeof(raxNode *) - (((h)->iskey && !(h)->isnull) ? sizeof(void *) : 0)));
                    raxNode *tofree = h;
                    memcpy(&h, cp, sizeof (h));
                    zfree(tofree);
                    rax->numnodes--;
                    if (h->iskey || (!h->iscompr && h->size != 1))
                        break;
                }
            ;
            raxNode **cp = ((raxNode **)(((char *)(new)) + (sizeof(raxNode) + (new)->size + ((sizeof(void *) - ((((new)->size) + 4) % sizeof(void *))) & (sizeof(void *) - 1)) + ((new)->iscompr ? sizeof(raxNode *) : sizeof(raxNode *) * (new)->size) + (((new)->iskey && !(new)->isnull) * sizeof(void *))) - sizeof(raxNode *) - (((new)->iskey && !(new)->isnull) ? sizeof(void *) : 0)));
            if (parent) {
                raxNode **parentlink = raxFindParentLink(parent, start);
            } else {
                ;
            }
            ;
        }
    }
    ;
    return 1;
}
