#ifndef __HEADER_TYPE_H__ 
#define __HEADER_TYPE_H__
#include"../common.h" 
struct jv_refcnt;//insertRecordDeclare 


/*Ano*/typedef struct {
    unsigned char kind_flags;
    unsigned char pad_;
    unsigned short offset;
    int size;
    union {
        struct jv_refcnt *ptr;
        double number;
    } u;
} jv;


typedef enum {
    JV_KIND_INVALID,
    JV_KIND_NULL,
    JV_KIND_FALSE,
    JV_KIND_TRUE,
    JV_KIND_NUMBER,
    JV_KIND_STRING,
    JV_KIND_ARRAY,
    JV_KIND_OBJECT
} jv_kind;

struct sort_entry;//insertRecordDeclare 


struct sort_entry {
    jv object;
    jv key;
    int index;
};

#endif