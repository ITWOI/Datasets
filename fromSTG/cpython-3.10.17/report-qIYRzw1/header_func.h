#ifndef __HEADER_FUNC_H__ 
#define __HEADER_FUNC_H__
#include"header_type.h" 
static void *_PyMem_RawMalloc(void *ctx, size_t size) ;

static void *_PyMem_RawCalloc(void *ctx, size_t nelem, size_t elsize) ;

static void *_PyMem_RawRealloc(void *ctx, void *ptr, size_t size) ;

static void _PyMem_RawFree(void *ctx, void *ptr) ;

static PyMemAllocatorEx _PyMem_Raw = {((void *)0), _PyMem_RawMalloc, _PyMem_RawCalloc, _PyMem_RawRealloc, _PyMem_RawFree};
;
static arena_map_top_t arena_map_root;
;
void *PyMem_RawCalloc(size_t nelem, size_t elsize) ;

static int arena_map_mid_count;
;
static int arena_map_bot_count;
;
static arena_map_bot_t *arena_map_get(block *p, int create) ;

extern int Py_IgnoreEnvironmentFlag;
;
void *PyMem_RawRealloc(void *ptr, size_t new_size) ;

static struct arena_object *unused_arena_objects = ((void *)0);
;
static unsigned int maxarenas = 0;
;
static struct arena_object *arenas = ((void *)0);
;
static void *_PyObject_ArenaMmap(void *ctx, size_t size) ;

static void _PyObject_ArenaMunmap(void *ctx, void *ptr, size_t size) ;

static PyObjectArenaAllocator _PyObject_Arena = {((void *)0), _PyObject_ArenaMmap, _PyObject_ArenaMunmap};
;
static int arena_map_mark_used(uintptr_t arena_base, int is_used) ;

static size_t narenas_currently_allocated = 0;
;
static size_t ntimes_arena_allocated = 0;
;
static size_t narenas_highwater = 0;
;
static int arena_map_is_used(block *p) ;

static struct arena_object *new_arena(void) ;

static struct arena_object *usable_arenas = ((void *)0);
;
static struct arena_object *nfp2lasta[65] = {((void *)0)};
;
static poolp usedpools[64] = {((poolp)((uint8_t *)&(usedpools[2 * (0)]) - 2 * sizeof(block *))), ((poolp)((uint8_t *)&(usedpools[2 * (0)]) - 2 * sizeof(block *))), ((poolp)((uint8_t *)&(usedpools[2 * (1)]) - 2 * sizeof(block *))), ((poolp)((uint8_t *)&(usedpools[2 * (1)]) - 2 * sizeof(block *))), ((poolp)((uint8_t *)&(usedpools[2 * (2)]) - 2 * sizeof(block *))), ((poolp)((uint8_t *)&(usedpools[2 * (2)]) - 2 * sizeof(block *))), ((poolp)((uint8_t *)&(usedpools[2 * (3)]) - 2 * sizeof(block *))), ((poolp)((uint8_t *)&(usedpools[2 * (3)]) - 2 * sizeof(block *))), ((poolp)((uint8_t *)&(usedpools[2 * (4)]) - 2 * sizeof(block *))), ((poolp)((uint8_t *)&(usedpools[2 * (4)]) - 2 * sizeof(block *))), ((poolp)((uint8_t *)&(usedpools[2 * (5)]) - 2 * sizeof(block *))), ((poolp)((uint8_t *)&(usedpools[2 * (5)]) - 2 * sizeof(block *))), ((poolp)((uint8_t *)&(usedpools[2 * (6)]) - 2 * sizeof(block *))), ((poolp)((uint8_t *)&(usedpools[2 * (6)]) - 2 * sizeof(block *))), ((poolp)((uint8_t *)&(usedpools[2 * (7)]) - 2 * sizeof(block *))), ((poolp)((uint8_t *)&(usedpools[2 * (7)]) - 2 * sizeof(block *))), ((poolp)((uint8_t *)&(usedpools[2 * (8)]) - 2 * sizeof(block *))), ((poolp)((uint8_t *)&(usedpools[2 * (8)]) - 2 * sizeof(block *))), ((poolp)((uint8_t *)&(usedpools[2 * (9)]) - 2 * sizeof(block *))), ((poolp)((uint8_t *)&(usedpools[2 * (9)]) - 2 * sizeof(block *))), ((poolp)((uint8_t *)&(usedpools[2 * (10)]) - 2 * sizeof(block *))), ((poolp)((uint8_t *)&(usedpools[2 * (10)]) - 2 * sizeof(block *))), ((poolp)((uint8_t *)&(usedpools[2 * (11)]) - 2 * sizeof(block *))), ((poolp)((uint8_t *)&(usedpools[2 * (11)]) - 2 * sizeof(block *))), ((poolp)((uint8_t *)&(usedpools[2 * (12)]) - 2 * sizeof(block *))), ((poolp)((uint8_t *)&(usedpools[2 * (12)]) - 2 * sizeof(block *))), ((poolp)((uint8_t *)&(usedpools[2 * (13)]) - 2 * sizeof(block *))), ((poolp)((uint8_t *)&(usedpools[2 * (13)]) - 2 * sizeof(block *))), ((poolp)((uint8_t *)&(usedpools[2 * (14)]) - 2 * sizeof(block *))), ((poolp)((uint8_t *)&(usedpools[2 * (14)]) - 2 * sizeof(block *))), ((poolp)((uint8_t *)&(usedpools[2 * (15)]) - 2 * sizeof(block *))), ((poolp)((uint8_t *)&(usedpools[2 * (15)]) - 2 * sizeof(block *))), ((poolp)((uint8_t *)&(usedpools[2 * (16)]) - 2 * sizeof(block *))), ((poolp)((uint8_t *)&(usedpools[2 * (16)]) - 2 * sizeof(block *))), ((poolp)((uint8_t *)&(usedpools[2 * (17)]) - 2 * sizeof(block *))), ((poolp)((uint8_t *)&(usedpools[2 * (17)]) - 2 * sizeof(block *))), ((poolp)((uint8_t *)&(usedpools[2 * (18)]) - 2 * sizeof(block *))), ((poolp)((uint8_t *)&(usedpools[2 * (18)]) - 2 * sizeof(block *))), ((poolp)((uint8_t *)&(usedpools[2 * (19)]) - 2 * sizeof(block *))), ((poolp)((uint8_t *)&(usedpools[2 * (19)]) - 2 * sizeof(block *))), ((poolp)((uint8_t *)&(usedpools[2 * (20)]) - 2 * sizeof(block *))), ((poolp)((uint8_t *)&(usedpools[2 * (20)]) - 2 * sizeof(block *))), ((poolp)((uint8_t *)&(usedpools[2 * (21)]) - 2 * sizeof(block *))), ((poolp)((uint8_t *)&(usedpools[2 * (21)]) - 2 * sizeof(block *))), ((poolp)((uint8_t *)&(usedpools[2 * (22)]) - 2 * sizeof(block *))), ((poolp)((uint8_t *)&(usedpools[2 * (22)]) - 2 * sizeof(block *))), ((poolp)((uint8_t *)&(usedpools[2 * (23)]) - 2 * sizeof(block *))), ((poolp)((uint8_t *)&(usedpools[2 * (23)]) - 2 * sizeof(block *))), ((poolp)((uint8_t *)&(usedpools[2 * (24)]) - 2 * sizeof(block *))), ((poolp)((uint8_t *)&(usedpools[2 * (24)]) - 2 * sizeof(block *))), ((poolp)((uint8_t *)&(usedpools[2 * (25)]) - 2 * sizeof(block *))), ((poolp)((uint8_t *)&(usedpools[2 * (25)]) - 2 * sizeof(block *))), ((poolp)((uint8_t *)&(usedpools[2 * (26)]) - 2 * sizeof(block *))), ((poolp)((uint8_t *)&(usedpools[2 * (26)]) - 2 * sizeof(block *))), ((poolp)((uint8_t *)&(usedpools[2 * (27)]) - 2 * sizeof(block *))), ((poolp)((uint8_t *)&(usedpools[2 * (27)]) - 2 * sizeof(block *))), ((poolp)((uint8_t *)&(usedpools[2 * (28)]) - 2 * sizeof(block *))), ((poolp)((uint8_t *)&(usedpools[2 * (28)]) - 2 * sizeof(block *))), ((poolp)((uint8_t *)&(usedpools[2 * (29)]) - 2 * sizeof(block *))), ((poolp)((uint8_t *)&(usedpools[2 * (29)]) - 2 * sizeof(block *))), ((poolp)((uint8_t *)&(usedpools[2 * (30)]) - 2 * sizeof(block *))), ((poolp)((uint8_t *)&(usedpools[2 * (30)]) - 2 * sizeof(block *))), ((poolp)((uint8_t *)&(usedpools[2 * (31)]) - 2 * sizeof(block *))), ((poolp)((uint8_t *)&(usedpools[2 * (31)]) - 2 * sizeof(block *)))};
static void pymalloc_pool_extend(poolp pool, unsigned int size) ;

static void *allocate_from_new_pool(unsigned int size) ;

static inline void *pymalloc_alloc(void *ctx, size_t nbytes) ;

void *PyMem_RawMalloc(size_t size) ;

static Py_ssize_t raw_allocated_blocks;
;
static _Bool address_in_range(void *p, poolp pool) ;

static void insert_to_usedpool(poolp pool) ;

static void insert_to_freepool(poolp pool) ;

static inline int pymalloc_free(void *ctx, void *p) ;

void PyMem_RawFree(void *ptr) ;

static void *_PyObject_Malloc(void *ctx, size_t nbytes) ;

static void _PyObject_Free(void *ctx, void *p) ;

static int pymalloc_realloc(void *ctx, void **newptr_p, void *p, size_t nbytes) ;

#endif