#ifndef __HEADER_FUNC_H__ 
#define __HEADER_FUNC_H__
#include"header_type.h" 
static void uv__udp_recvmsg(uv_udp_t *handle);


uv_buf_t uv_buf_init(char *base, unsigned int len);

int uv_udp_using_recvmmsg(const uv_udp_t *handle);

static int uv__udp_recvmmsg(uv_udp_t *handle, uv_buf_t *buf) ;

#endif