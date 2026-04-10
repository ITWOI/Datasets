#ifndef __HEADER_TYPE_H__ 
#define __HEADER_TYPE_H__
#include"../common.h" 
struct Bigint;//insertRecordDeclare 

/*TD*/typedef struct Bigint Bigint;

/*TD*/typedef uint32_t ULong;


struct Bigint {
    struct Bigint *next;
    int k;
    int maxwds;
    int sign;
    int wds;
    ULong x[1];
};

/*TD*/typedef ssize_t Py_ssize_t;

/*TD*/typedef uint64_t ULLong;

/*TD*/typedef int32_t Long;


/*Ano*/typedef union {
    double d;
    ULong L[2];
} U;

#endif