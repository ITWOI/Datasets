#include "header_func.h"
static void uv__udp_io (uv_loop_t *loop, uv__io_t *w, unsigned int revents){
    uv_udp_t *handle;
    handle = ((uv_udp_t *)((char *)(w) - __builtin_offsetof(uv_udp_t, io_watcher)));
    ((void)sizeof ((handle->type == UV_UDP) ? 1 : 0) , __extension__ ({
        if (handle->type == UV_UDP)
            ;
        else
            __assert_fail("handle->type == UV_UDP", "src/unix/udp_InstSlice.c", 69, __extension__ __PRETTY_FUNCTION__);
    }));
    if (revents & 1)
        uv__udp_recvmsg(handle);
}
static int uv__udp_recvmmsg (uv_udp_t *handle, uv_buf_t *buf){
    struct sockaddr_in6 peers[20];
    struct iovec iov[20];
    struct mmsghdr msgs[20];
    ssize_t nread;
    uv_buf_t chunk_buf;
    size_t chunks;
    int flags;
    size_t k;
    chunks = buf->len / (64 * 1024);
    if (chunks > (sizeof (iov) / sizeof ((iov)[0])))
        chunks = (sizeof (iov) / sizeof ((iov)[0]));
    for (k = 0; k < chunks; ++k) {
        iov[k].iov_base = buf->base + k * (64 * 1024);
        iov[k].iov_len = (64 * 1024);
        memset(&msgs[k].msg_hdr, 0, sizeof (msgs[k].msg_hdr));
        msgs[k].msg_hdr.msg_iov = iov + k;
        msgs[k].msg_hdr.msg_iovlen = 1;
        msgs[k].msg_hdr.msg_name = peers + k;
        msgs[k].msg_hdr.msg_namelen = sizeof (peers[0]);
        msgs[k].msg_hdr.msg_control = ((void *)0);
        msgs[k].msg_hdr.msg_controllen = 0;
        msgs[k].msg_hdr.msg_flags = 0;
        msgs[k].msg_len = 0;
    }
    do 
        nread = recvmmsg(handle->io_watcher.fd, msgs, chunks, 0, ((void *)0));
    while (nread == -1 && (*__errno_location()) == 4);
    if (nread < 1) {
        ;
    } else {
        for (k = 0; k < (size_t)nread && handle->recv_cb != ((void *)0); k++) {
            flags = UV_UDP_MMSG_CHUNK;
            if (msgs[k].msg_hdr.msg_flags & MSG_TRUNC)
                flags |= UV_UDP_PARTIAL;
            chunk_buf = uv_buf_init(iov[k].iov_base, iov[k].iov_len);
        }
        ;
    }
    return nread;
}
static void uv__udp_recvmsg (uv_udp_t *handle){
    struct sockaddr_storage peer;
    struct msghdr h;
    ssize_t nread;
    uv_buf_t buf;
    int flags;
    int count;
    ((void)sizeof ((handle->recv_cb != ((void *)0)) ? 1 : 0) , __extension__ ({
        if (handle->recv_cb != ((void *)0))
            ;
        else
            __assert_fail("handle->recv_cb != NULL", "src/unix/udp_InstSlice.c", 146, __extension__ __PRETTY_FUNCTION__);
    }));
    ((void)sizeof ((handle->alloc_cb != ((void *)0)) ? 1 : 0) , __extension__ ({
        if (handle->alloc_cb != ((void *)0))
            ;
        else
            __assert_fail("handle->alloc_cb != NULL", "src/unix/udp_InstSlice.c", 147, __extension__ __PRETTY_FUNCTION__);
    }));
    count = 32;
    do {
        buf = uv_buf_init(((void *)0), 0);
        if (buf.base == ((void *)0) || buf.len == 0) {
            ;
            return;
        }
        ((void)sizeof ((buf.base != ((void *)0)) ? 1 : 0) , __extension__ ({
            if (buf.base != ((void *)0))
                ;
            else
                __assert_fail("buf.base != NULL", "src/unix/udp_InstSlice.c", 161, __extension__ __PRETTY_FUNCTION__);
        }));
        if (uv_udp_using_recvmmsg(handle)) {
            nread = uv__udp_recvmmsg(handle, &buf);
            if (nread > 0)
                count -= nread;
            continue;
        }
        memset(&h, 0, sizeof (h));
        memset(&peer, 0, sizeof (peer));
        h.msg_name = &peer;
        h.msg_namelen = sizeof (peer);
        h.msg_iov = (void *)&buf;
        h.msg_iovlen = 1;
        do {
            nread = recvmsg(handle->io_watcher.fd, &h, 0);
        } while (nread == -1 && (*__errno_location()) == 4);
        if (nread == -1) {
            ;
        } else {
            flags = 0;
            if (h.msg_flags & MSG_TRUNC)
                flags |= UV_UDP_PARTIAL;
        }
        count--;
    } while (nread != -1 && count > 0 && handle->io_watcher.fd != -1 && handle->recv_cb != ((void *)0));
}
extern  __attribute__((visibility("default"))) int uv_udp_using_recvmmsg (const uv_udp_t *handle){
    if (handle->flags & UV_HANDLE_UDP_RECVMMSG)
        return 1;
    return 0;
}
