#ifndef __HEADER_TYPE_H__ 
#define __HEADER_TYPE_H__
#include"../common.h" 
struct raxStack;//insertRecordDeclare 

/*TD*/typedef struct raxStack raxStack;


struct raxStack {
    void **stack;
    size_t items;
    size_t maxitems;
    void *static_items[32];
    int oom;
};

struct raxNode;//insertRecordDeclare 

/*TD*/typedef struct raxNode raxNode;


struct raxNode {
    uint32_t iskey : 1;
    uint32_t isnull : 1;
    uint32_t iscompr : 1;
    uint32_t size : 29;
    unsigned char data[];
};

struct rax;//insertRecordDeclare 

/*TD*/typedef struct rax rax;


struct rax {
    raxNode *head;
    uint64_t numele;
    uint64_t numnodes;
    void *metadata[];
};

#endif