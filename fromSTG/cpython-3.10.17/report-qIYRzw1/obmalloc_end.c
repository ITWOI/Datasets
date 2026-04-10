#include "header_func.h"
static void * _PyMem_RawMalloc (void *ctx, size_t size){
    if (size == 0)
        size = 1;
    return malloc(size);
}
static void * _PyMem_RawCalloc (void *ctx, size_t nelem, size_t elsize){
    if (nelem == 0 || elsize == 0) {
        nelem = 1;
        elsize = 1;
    }
    return calloc(nelem, elsize);
}
static void * _PyMem_RawRealloc (void *ctx, void *ptr, size_t size){
    if (size == 0)
        size = 1;
    return realloc(ptr, size);
}
static void * _PyObject_ArenaMmap (void *ctx, size_t size){
    void *ptr;
    ptr = mmap(((void *)0), size, 1 | 2, 2 | 32, -1, 0);
    if (ptr == ((void *)-1))
        return ((void *)0);
    return ptr;
}
extern  __attribute__((visibility("default"))) void * PyMem_RawMalloc (size_t size){
    if (size > (size_t)((Py_ssize_t)(((size_t)-1) >> 1)))
        return ((void *)0);
    return _PyMem_Raw.malloc(_PyMem_Raw.ctx, size);
}
extern  __attribute__((visibility("default"))) void * PyMem_RawCalloc (size_t nelem, size_t elsize){
    if (elsize != 0 && nelem > (size_t)((Py_ssize_t)(((size_t)-1) >> 1)) / elsize)
        return ((void *)0);
    return _PyMem_Raw.calloc(_PyMem_Raw.ctx, nelem, elsize);
}
extern  __attribute__((visibility("default"))) void * PyMem_RawRealloc (void *ptr, size_t new_size){
    if (new_size > (size_t)((Py_ssize_t)(((size_t)-1) >> 1)))
        return ((void *)0);
    return _PyMem_Raw.realloc(_PyMem_Raw.ctx, ptr, new_size);
}
static  __attribute__((always_inline)) arena_map_bot_t * arena_map_get (block *p, int create){
    ;
    int i1 = ((((uintptr_t)(p)) >> (((48 - 20 + 2) / 3) + ((48 - 20 - 2 * ((48 - 20 + 2) / 3)) + 20))) & ((1 << ((48 - 20 + 2) / 3)) - 1));
    if (arena_map_root.ptrs[i1] == ((void *)0)) {
        if (!create) {
            return ((void *)0);
        }
        arena_map_mid_t *n = PyMem_RawCalloc(1, sizeof(arena_map_mid_t));
        if (n == ((void *)0)) {
            return ((void *)0);
        }
        arena_map_root.ptrs[i1] = n;
        arena_map_mid_count++;
    }
    int i2 = ((((uintptr_t)(p)) >> ((48 - 20 - 2 * ((48 - 20 + 2) / 3)) + 20)) & ((1 << ((48 - 20 + 2) / 3)) - 1));
    if (arena_map_root.ptrs[i1]->ptrs[i2] == ((void *)0)) {
        if (!create) {
            return ((void *)0);
        }
        arena_map_bot_t *n = PyMem_RawCalloc(1, sizeof(arena_map_bot_t));
        if (n == ((void *)0)) {
            return ((void *)0);
        }
        arena_map_root.ptrs[i1]->ptrs[i2] = n;
        arena_map_bot_count++;
    }
    return arena_map_root.ptrs[i1]->ptrs[i2];
}
static int arena_map_mark_used (uintptr_t arena_base, int is_used){
    ;
    arena_map_bot_t *n_hi = arena_map_get((block *)arena_base, is_used);
    if (n_hi == ((void *)0)) {
        ;
        return 0;
    }
    int i3 = ((((uintptr_t)((block *)arena_base)) >> 20) & ((1 << (48 - 20 - 2 * ((48 - 20 + 2) / 3))) - 1));
    int32_t tail = (int32_t)(arena_base & ((1 << 20) - 1));
    if (tail == 0) {
        n_hi->arenas[i3].tail_hi = is_used ? -1 : 0;
    } else {
        n_hi->arenas[i3].tail_hi = is_used ? tail : 0;
        uintptr_t arena_base_next = arena_base + (1 << 20);
        arena_map_bot_t *n_lo = arena_map_get((block *)arena_base_next, is_used);
        if (n_lo == ((void *)0)) {
            ;
            n_hi->arenas[i3].tail_hi = 0;
            return 0;
        }
        int i3_next = ((((uintptr_t)(arena_base_next)) >> 20) & ((1 << (48 - 20 - 2 * ((48 - 20 + 2) / 3))) - 1));
        n_lo->arenas[i3_next].tail_lo = is_used ? tail : 0;
    }
    return 1;
}
static int arena_map_is_used (block *p){
    arena_map_bot_t *n = arena_map_get(p, 0);
    if (n == ((void *)0)) {
        return 0;
    }
    int i3 = ((((uintptr_t)(p)) >> 20) & ((1 << (48 - 20 - 2 * ((48 - 20 + 2) / 3))) - 1));
    int32_t hi = n->arenas[i3].tail_hi;
    int32_t lo = n->arenas[i3].tail_lo;
    int32_t tail = (int32_t)(((uintptr_t)(p)) & ((1 << 20) - 1));
    return (tail < lo) || (tail >= hi && hi != 0);
}
static struct arena_object * new_arena (){
    struct arena_object *arenaobj;
    unsigned int excess;
    void *address;
    static int debug_stats;
    if (debug_stats == -1) {
        const char *opt = (Py_IgnoreEnvironmentFlag ? ((void *)0) : getenv("PYTHONMALLOCSTATS"));
        debug_stats = (opt != ((void *)0) && *opt != '\x00');
    }
    ;
    if (unused_arena_objects == ((void *)0)) {
        unsigned int i;
        unsigned int numarenas;
        size_t nbytes;
        numarenas = maxarenas ? maxarenas << 1 : 16;
        if (numarenas <= maxarenas)
            return ((void *)0);
        nbytes = numarenas * sizeof (*arenas);
        arenaobj = (struct arena_object *)PyMem_RawRealloc(arenas, nbytes);
        if (arenaobj == ((void *)0))
            return ((void *)0);
        arenas = arenaobj;
        for (i = maxarenas; i < numarenas; ++i) {
            arenas[i].address = 0;
            arenas[i].nextarena = i < numarenas - 1 ? &arenas[i + 1] : ((void *)0);
        }
        unused_arena_objects = &arenas[maxarenas];
        maxarenas = numarenas;
    }
    ;
    arenaobj = unused_arena_objects;
    unused_arena_objects = arenaobj->nextarena;
    address = _PyObject_Arena.alloc(_PyObject_Arena.ctx, (1 << 20));
    if (address != ((void *)0)) {
        if (!arena_map_mark_used((uintptr_t)address, 1)) {
            ;
            address = ((void *)0);
        }
    }
    if (address == ((void *)0)) {
        arenaobj->nextarena = unused_arena_objects;
        unused_arena_objects = arenaobj;
        return ((void *)0);
    }
    arenaobj->address = (uintptr_t)address;
    ++narenas_currently_allocated;
    ++ntimes_arena_allocated;
    if (narenas_currently_allocated > narenas_highwater)
        narenas_highwater = narenas_currently_allocated;
    arenaobj->freepools = ((void *)0);
    arenaobj->pool_address = (block *)arenaobj->address;
    arenaobj->nfreepools = ((1 << 20) / (1 << 14));
    excess = (unsigned int)(arenaobj->address & ((1 << 14) - 1));
    if (excess != 0) {
        --arenaobj->nfreepools;
        arenaobj->pool_address += (1 << 14) - excess;
    }
    arenaobj->ntotalpools = arenaobj->nfreepools;
    return arenaobj;
}
static _Bool address_in_range (void *p, poolp pool){
    return arena_map_is_used(p);
}
static void pymalloc_pool_extend (poolp pool, unsigned int size){
    if ((pool->nextoffset <= pool->maxnextoffset)) {
        pool->freeblock = (block *)pool + pool->nextoffset;
        pool->nextoffset += (((unsigned int)(size) + 1) << 4);
        *(block **)(pool->freeblock) = ((void *)0);
        return;
    }
    poolp next;
    next = pool->nextpool;
    pool = pool->prevpool;
    next->prevpool = pool;
    pool->nextpool = next;
}
static void * allocate_from_new_pool (unsigned int size){
    if ((usable_arenas == ((void *)0))) {
        usable_arenas = new_arena();
        if (usable_arenas == ((void *)0)) {
            return ((void *)0);
        }
        usable_arenas->nextarena = usable_arenas->prevarena = ((void *)0);
        nfp2lasta[usable_arenas->nfreepools] = usable_arenas;
    }
    ;
    if (nfp2lasta[usable_arenas->nfreepools] == usable_arenas) {
        nfp2lasta[usable_arenas->nfreepools] = ((void *)0);
    }
    if (usable_arenas->nfreepools > 1) {
        ;
        nfp2lasta[usable_arenas->nfreepools - 1] = usable_arenas;
    }
    poolp pool = usable_arenas->freepools;
    if ((pool != ((void *)0))) {
        usable_arenas->freepools = pool->nextpool;
        usable_arenas->nfreepools--;
        if ((usable_arenas->nfreepools == 0)) {
            ;
            usable_arenas = usable_arenas->nextarena;
            if (usable_arenas != ((void *)0)) {
                usable_arenas->prevarena = ((void *)0);
            }
        } else {
            ;
        }
    } else {
        ;
        pool = (poolp)usable_arenas->pool_address;
        pool->arenaindex = (unsigned int)(usable_arenas - arenas);
        pool->szidx = 65535;
        usable_arenas->pool_address += (1 << 14);
        --usable_arenas->nfreepools;
        if (usable_arenas->nfreepools == 0) {
            ;
            usable_arenas = usable_arenas->nextarena;
            if (usable_arenas != ((void *)0)) {
                usable_arenas->prevarena = ((void *)0);
            }
        }
    }
    block *bp;
    poolp next = usedpools[size + size];
    pool->nextpool = next;
    pool->prevpool = next;
    next->nextpool = pool;
    next->prevpool = pool;
    pool->ref.count = 1;
    if (pool->szidx == size) {
        bp = pool->freeblock;
        pool->freeblock = *(block **)bp;
        return bp;
    }
    pool->szidx = size;
    size = (((unsigned int)(size) + 1) << 4);
    bp = (block *)pool + (((size_t)(sizeof(struct pool_header)) + (size_t)((16) - 1)) & ~(size_t)((16) - 1));
    pool->nextoffset = (((size_t)(sizeof(struct pool_header)) + (size_t)((16) - 1)) & ~(size_t)((16) - 1)) + (size << 1);
    pool->maxnextoffset = (1 << 14) - size;
    pool->freeblock = bp + size;
    *(block **)(pool->freeblock) = ((void *)0);
    return bp;
}
static inline void * pymalloc_alloc (void *ctx, size_t nbytes){
    if ((nbytes == 0)) {
        return ((void *)0);
    }
    if ((nbytes > 512)) {
        return ((void *)0);
    }
    unsigned int size = (unsigned int)(nbytes - 1) >> 4;
    poolp pool = usedpools[size + size];
    block *bp;
    if ((pool != pool->nextpool)) {
        ++pool->ref.count;
        bp = pool->freeblock;
        if (((pool->freeblock = *(block **)bp) == ((void *)0))) {
            pymalloc_pool_extend(pool, size);
        }
    } else {
        bp = allocate_from_new_pool(size);
    }
    return (void *)bp;
}
static void * _PyObject_Malloc (void *ctx, size_t nbytes){
    void *ptr = pymalloc_alloc(ctx, nbytes);
    if ((ptr != ((void *)0))) {
        return ptr;
    }
    ptr = PyMem_RawMalloc(nbytes);
    if (ptr != ((void *)0)) {
        raw_allocated_blocks++;
    }
    return ptr;
}
static void insert_to_usedpool (poolp pool){
    ;
    unsigned int size = pool->szidx;
    poolp next = usedpools[size + size];
    poolp prev = next->prevpool;
    pool->nextpool = next;
    pool->prevpool = prev;
    next->prevpool = pool;
    prev->nextpool = pool;
}
static void insert_to_freepool (poolp pool){
    poolp next = pool->nextpool;
    poolp prev = pool->prevpool;
    next->prevpool = prev;
    prev->nextpool = next;
    struct arena_object *ao = &arenas[pool->arenaindex];
    pool->nextpool = ao->freepools;
    ao->freepools = pool;
    unsigned int nf = ao->nfreepools;
    struct arena_object *lastnf = nfp2lasta[nf];
    if (lastnf == ao) {
        struct arena_object *p = ao->prevarena;
        nfp2lasta[nf] = (p != ((void *)0) && p->nfreepools == nf) ? p : ((void *)0);
    }
    ao->nfreepools = ++nf;
    if (nf == ao->ntotalpools && ao->nextarena != ((void *)0)) {
        ;
        if (ao->prevarena == ((void *)0)) {
            usable_arenas = ao->nextarena;
        } else {
            ;
            ao->prevarena->nextarena = ao->nextarena;
        }
        if (ao->nextarena != ((void *)0)) {
            ;
            ao->nextarena->prevarena = ao->prevarena;
        }
        ao->nextarena = unused_arena_objects;
        unused_arena_objects = ao;
        arena_map_mark_used(ao->address, 0);
        ao->address = 0;
        --narenas_currently_allocated;
        return;
    }
    if (nf == 1) {
        ao->nextarena = usable_arenas;
        ao->prevarena = ((void *)0);
        if (usable_arenas)
            usable_arenas->prevarena = ao;
        usable_arenas = ao;
        if (nfp2lasta[1] == ((void *)0)) {
            nfp2lasta[1] = ao;
        }
        return;
    }
    if (nfp2lasta[nf] == ((void *)0)) {
        nfp2lasta[nf] = ao;
    }
    if (ao == lastnf) {
        return;
    }
    ;
    if (ao->prevarena != ((void *)0)) {
        ;
        ao->prevarena->nextarena = ao->nextarena;
    } else {
        ;
        usable_arenas = ao->nextarena;
    }
    ao->nextarena->prevarena = ao->prevarena;
    ao->prevarena = lastnf;
    ao->nextarena = lastnf->nextarena;
    if (ao->nextarena != ((void *)0)) {
        ao->nextarena->prevarena = ao;
    }
    lastnf->nextarena = ao;
}
static inline int pymalloc_free (void *ctx, void *p){
    ;
    poolp pool = ((poolp)((void *)((uintptr_t)((p)) & ~(uintptr_t)(((1 << 14)) - 1))));
    if ((!address_in_range(p, pool))) {
        return 0;
    }
    ;
    block *lastfree = pool->freeblock;
    *(block **)p = lastfree;
    pool->freeblock = (block *)p;
    pool->ref.count--;
    if ((lastfree == ((void *)0))) {
        insert_to_usedpool(pool);
        return 1;
    }
    if ((pool->ref.count != 0)) {
        return 1;
    }
    insert_to_freepool(pool);
    return 1;
}
static void _PyObject_Free (void *ctx, void *p){
    if (p == ((void *)0)) {
        return;
    }
    if ((!pymalloc_free(ctx, p))) {
        ;
        raw_allocated_blocks--;
    }
}
static int pymalloc_realloc (void *ctx, void **newptr_p, void *p, size_t nbytes){
    void *bp;
    poolp pool;
    size_t size;
    pool = ((poolp)((void *)((uintptr_t)((p)) & ~(uintptr_t)(((1 << 14)) - 1))));
    if (!address_in_range(p, pool)) {
        return 0;
    }
    size = (((unsigned int)(pool->szidx) + 1) << 4);
    if (nbytes <= size) {
        if (4 * nbytes > 3 * size) {
            ;
            return 1;
        }
        size = nbytes;
    }
    bp = _PyObject_Malloc(ctx, nbytes);
    if (bp != ((void *)0)) {
        memcpy(bp, p, size);
        _PyObject_Free(ctx, p);
    }
    ;
    return 1;
}
static void * _PyObject_Realloc (void *ctx, void *ptr, size_t nbytes){
    void *ptr2;
    if (ptr == ((void *)0)) {
        return _PyObject_Malloc(ctx, nbytes);
    }
    if (pymalloc_realloc(ctx, &ptr2, ptr, nbytes)) {
        return ptr2;
    }
    return PyMem_RawRealloc(ptr, nbytes);
}
