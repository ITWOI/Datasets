#ifndef __HEADER_TYPE_H__ 
#define __HEADER_TYPE_H__
#include"../common.h" 
struct aeEventLoop;//insertRecordDeclare 

/*TD*/typedef struct aeEventLoop aeEventLoop;

struct timeval;//insertRecordDeclare 

struct aeApiState;//insertRecordDeclare 

/*TD*/typedef struct aeApiState aeApiState;

struct aeFileEvent;//insertRecordDeclare 

/*TD*/typedef struct aeFileEvent aeFileEvent;

struct aeFiredEvent;//insertRecordDeclare 

/*TD*/typedef struct aeFiredEvent aeFiredEvent;

struct aeTimeEvent;//insertRecordDeclare 

/*TD*/typedef struct aeTimeEvent aeTimeEvent;

/*TD*/typedef void (aeBeforeSleepProc)(struct aeEventLoop *);


struct aeEventLoop {
    int maxfd;
    int setsize;
    long long timeEventNextId;
    int nevents;
    aeFileEvent *events;
    aeFiredEvent *fired;
    aeTimeEvent *timeEventHead;
    int stop;
    void *apidata;
    aeBeforeSleepProc *beforesleep;
    aeBeforeSleepProc *aftersleep;
    int flags;
    void *privdata[2];
};

struct epoll_event;//insertRecordDeclare 


struct aeApiState {
    int epfd;
    struct epoll_event *events;
};


struct aeFiredEvent {
    int fd;
    int mask;
};

union epoll_data;//insertRecordDeclare 

/*TD*/typedef uint64_t monotime;

/*TD*/typedef int (aeTimeProc)(struct aeEventLoop *, long long, void *);

/*TD*/typedef void (aeEventFinalizerProc)(struct aeEventLoop *, void *);


struct aeTimeEvent {
    long long id;
    monotime when;
    aeTimeProc *timeProc;
    aeEventFinalizerProc *finalizerProc;
    void *clientData;
    struct aeTimeEvent *prev;
    struct aeTimeEvent *next;
    int refcount;
};

/*TD*/typedef void (aeFileProc)(struct aeEventLoop *, int, void *, int);


struct aeFileEvent {
    int mask;
    aeFileProc *rfileProc;
    aeFileProc *wfileProc;
    void *clientData;
};

#endif