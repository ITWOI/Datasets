#ifndef __HEADER_TYPE_H__ 
#define __HEADER_TYPE_H__
#include"../common.h" 
struct quicklistNode;//insertRecordDeclare 

/*TD*/typedef struct quicklistNode quicklistNode;


struct quicklistNode {
    struct quicklistNode *prev;
    struct quicklistNode *next;
    unsigned char *entry;
    size_t sz;
    unsigned int count : 16;
    unsigned int encoding : 2;
    unsigned int container : 2;
    unsigned int recompress : 1;
    unsigned int attempted_compress : 1;
    unsigned int dont_compress : 1;
    unsigned int extra : 9;
};

struct quicklistLZF;//insertRecordDeclare 

/*TD*/typedef struct quicklistLZF quicklistLZF;


struct quicklistLZF {
    size_t sz;
    char compressed[];
};

struct quicklist;//insertRecordDeclare 

/*TD*/typedef struct quicklist quicklist;

struct quicklistBookmark;//insertRecordDeclare 

/*TD*/typedef struct quicklistBookmark quicklistBookmark;


struct quicklistBookmark {
    quicklistNode *node;
    char *name;
};


struct quicklist {
    quicklistNode *head;
    quicklistNode *tail;
    unsigned long count;
    unsigned long len;
    int fill : 16;
    unsigned int compress : 16;
    unsigned int bookmark_count : 4;
    quicklistBookmark bookmarks[];
};

#endif