#ifndef __HEADER_TYPE_H__ 
#define __HEADER_TYPE_H__
#include"../common.h" 

/*Ano*/typedef struct {
    int a;
    int b;
} memory_leak_005_s_001;


/*Ano*/typedef struct {
    int a;
    int b;
} memory_leak_005_s_002;


/*Ano*/typedef struct {
    int a;
    int b;
} memory_leak_005_s_003;


/*Ano*/typedef union {
    memory_leak_005_s_001 s1;
    memory_leak_005_s_002 s2;
    memory_leak_005_s_003 s3;
} memory_leak_005_uni_001;

#endif