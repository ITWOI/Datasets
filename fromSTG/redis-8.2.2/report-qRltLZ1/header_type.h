#ifndef __HEADER_TYPE_H__ 
#define __HEADER_TYPE_H__
#include"../common.h" 

/*Ano*/typedef struct {
    unsigned char *sval;
    uint32_t slen;
    long long lval;
} listpackEntry;

struct listpackInsertEntry;//insertRecordDeclare 


struct listpackInsertEntry {
    int enctype;
    uint64_t enclen;
    unsigned char intenc[9];
    unsigned char backlen[5];
    unsigned long backlen_size;
};

#endif