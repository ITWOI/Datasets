#ifndef __HEADER_FUNC_H__ 
#define __HEADER_FUNC_H__
#include"header_type.h" 

void tinytest_set_test_failed_(void);


int tinytest_get_verbosity_(void);


struct evbuffer *evbuffer_new(void);

static int evbuffer_validate_(struct evbuffer *buf) ;


char *evbuffer_readln(struct evbuffer *buffer, size_t *n_read_out, enum evbuffer_eol_style eol_style);


size_t evbuffer_get_length(const struct evbuffer *buf);

#endif