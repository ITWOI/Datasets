#ifndef __HEADER_TYPE_H__ 
#define __HEADER_TYPE_H__
#include"../common.h" 
struct quicklistBookmark;//insertRecordDeclare 

/*TD*/typedef struct quicklistBookmark quicklistBookmark;

struct quicklist;//insertRecordDeclare 

/*TD*/typedef struct quicklist quicklist;

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

struct quicklistIter;//insertRecordDeclare 

/*TD*/typedef struct quicklistIter quicklistIter;

struct quicklistEntry;//insertRecordDeclare 

/*TD*/typedef struct quicklistEntry quicklistEntry;


struct quicklistIter {
    quicklist *quicklist;
    quicklistNode *current;
    unsigned char *zi;
    long offset;
    int direction;
};


struct quicklistEntry {
    const quicklist *quicklist;
    quicklistNode *node;
    unsigned char *zi;
    unsigned char *value;
    long long longval;
    size_t sz;
    int offset;
};

#endif