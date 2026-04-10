#ifndef __HEADER_FUNC_H__ 
#define __HEADER_FUNC_H__
#include"header_type.h" 

struct evconnlistener *evconnlistener_new_bind(struct event_base *base, evconnlistener_cb cb, void *ptr, unsigned int flags, int backlog, const struct sockaddr *sa, int socklen);

static void acceptcb(struct evconnlistener *listener, int fd, struct sockaddr *addr, int socklen, void *arg) ;


void tinytest_set_test_failed_(void);


int tinytest_get_verbosity_(void);


int evconnlistener_get_fd(struct evconnlistener *lev);

#endif