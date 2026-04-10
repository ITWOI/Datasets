#ifndef __HEADER_TYPE_H__ 
#define __HEADER_TYPE_H__
#include"../common.h" 
struct Bigint;//insertRecordDeclare 

/*TD*/typedef struct Bigint Bigint;

struct dtoa_context;//insertRecordDeclare 

/*TD*/typedef unsigned int ULong;


struct Bigint {
    struct Bigint *next;
    int k;
    int maxwds;
    int sign;
    int wds;
    ULong x[1];
};


struct dtoa_context {
    struct Bigint *freelist[8];
    struct Bigint *p5s;
};


/*Ano*/typedef union {
    double d;
    ULong L[2];
} U;

#endif