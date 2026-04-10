#ifndef __HEADER_FUNC_H__ 
#define __HEADER_FUNC_H__
#include"header_type.h" 

void _serverPanic(const char *file, int line, const char *msg, ...);

extern monotime (*getMonotonicUs)(void);
;

void zfree(void *ptr);

static int64_t usUntilEarliestTimer(aeEventLoop *eventLoop) ;

static int aeApiPoll(aeEventLoop *eventLoop, struct timeval *tvp) ;

static int processTimeEvents(aeEventLoop *eventLoop) ;

int aeProcessEvents(aeEventLoop *eventLoop, int flags) ;

#endif