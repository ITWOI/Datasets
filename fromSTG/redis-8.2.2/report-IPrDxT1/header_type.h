#ifndef __HEADER_TYPE_H__ 
#define __HEADER_TYPE_H__
#include"../common.h" 
struct _IO_FILE;//insertRecordDeclare 

struct stat;//insertRecordDeclare 


typedef enum {
    AOF_RESP,
    AOF_RDB_PREAMBLE,
    AOF_MULTI_PART
} input_file_type;

/*TD*/typedef char *sds;


typedef enum {
    AOF_FILE_TYPE_BASE = 'b',
    AOF_FILE_TYPE_HIST = 'h',
    AOF_FILE_TYPE_INCR = 'i'
} aof_file_type;


/*Ano*/typedef struct {
    sds file_name;
    long long file_seq;
    aof_file_type file_type;
    long long start_offset;
    long long end_offset;
} aofInfo;

struct list;//insertRecordDeclare 

/*TD*/typedef struct list list;


/*Ano*/typedef struct {
    aofInfo *base_aof_info;
    list *incr_aof_list;
    list *history_aof_list;
    long long curr_base_file_seq;
    long long curr_incr_file_seq;
    int dirty;
} aofManifest;

struct listNode;//insertRecordDeclare 

/*TD*/typedef struct listNode listNode;


struct list {
    listNode *head;
    listNode *tail;
    void *(*dup)(void *);
    void (*free)(void *);
    int (*match)(void *, void *);
    unsigned long len;
};

struct listIter;//insertRecordDeclare 

/*TD*/typedef struct listIter listIter;


struct listIter {
    listNode *next;
    int direction;
};


struct listNode {
    struct listNode *prev;
    struct listNode *next;
    void *value;
};

#endif