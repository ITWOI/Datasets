#ifndef __HEADER_TYPE_H__ 
#define __HEADER_TYPE_H__
#include"../common.h" 

/*Ano*/typedef union {
    int *a;
    int b;
} invalid_memory_access_003_s_001;


/*Ano*/typedef union {
    int a;
    int b;
} invalid_memory_access_003_s_002;


/*Ano*/typedef union {
    int a;
    int b;
} invalid_memory_access_003_s_003;


/*Ano*/typedef struct {
    invalid_memory_access_003_s_001 *s1;
    invalid_memory_access_003_s_002 s2;
    invalid_memory_access_003_s_003 s3;
} invalid_memory_access_003_uni_001;

#endif