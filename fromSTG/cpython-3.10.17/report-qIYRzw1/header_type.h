#ifndef __HEADER_TYPE_H__ 
#define __HEADER_TYPE_H__
#include"../common.h" 
/*TD*/typedef ssize_t Py_ssize_t;


/*Ano*/typedef struct {
    void *ctx;
    void *(*malloc)(void *, size_t);
    void *(*calloc)(void *, size_t, size_t);
    void *(*realloc)(void *, void *, size_t);
    void (*free)(void *, void *);
} PyMemAllocatorEx;

struct arena_map_bot;//insertRecordDeclare 

/*TD*/typedef struct arena_map_bot arena_map_bot_t;

/*TD*/typedef uint8_t block;

struct arena_map_mid;//insertRecordDeclare 


struct arena_map_mid {
    struct arena_map_bot *ptrs[1024];
};

struct arena_map_top;//insertRecordDeclare 

/*TD*/typedef struct arena_map_top arena_map_top_t;


struct arena_map_top {
    struct arena_map_mid *ptrs[1024];
};

/*TD*/typedef struct arena_map_mid arena_map_mid_t;


/*Ano*/typedef struct {
    int32_t tail_hi;
    int32_t tail_lo;
} arena_coverage_t;


struct arena_map_bot {
    arena_coverage_t arenas[256];
};

struct arena_object;//insertRecordDeclare 

struct pool_header;//insertRecordDeclare 


struct arena_object {
    uintptr_t address;
    block *pool_address;
    unsigned int nfreepools;
    unsigned int ntotalpools;
    struct pool_header *freepools;
    struct arena_object *nextarena;
    struct arena_object *prevarena;
};


/*Ano*/typedef struct {
    void *ctx;
    void *(*alloc)(void *, size_t);
    void (*free)(void *, void *, size_t);
} PyObjectArenaAllocator;

/*TD*/typedef struct pool_header *poolp;


struct pool_header {
    union {
        block *_padding;
        unsigned int count;
    } ref;
    block *freeblock;
    struct pool_header *nextpool;
    struct pool_header *prevpool;
    unsigned int arenaindex;
    unsigned int szidx;
    unsigned int nextoffset;
    unsigned int maxnextoffset;
};

#endif