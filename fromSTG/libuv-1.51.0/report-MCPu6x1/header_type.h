#ifndef __HEADER_TYPE_H__ 
#define __HEADER_TYPE_H__
#include"../common.h" 
struct uv_loop_s;//insertRecordDeclare 

/*TD*/typedef struct uv_loop_s uv_loop_t;

struct uv__io_s;//insertRecordDeclare 

/*TD*/typedef struct uv__io_s uv__io_t;

struct uv_udp_s;//insertRecordDeclare 

/*TD*/typedef struct uv_udp_s uv_udp_t;


typedef enum {
    UV_UNKNOWN_HANDLE = 0,
    UV_ASYNC,
    UV_CHECK,
    UV_FS_EVENT,
    UV_FS_POLL,
    UV_HANDLE,
    UV_IDLE,
    UV_NAMED_PIPE,
    UV_POLL,
    UV_PREPARE,
    UV_PROCESS,
    UV_STREAM,
    UV_TCP,
    UV_TIMER,
    UV_TTY,
    UV_UDP,
    UV_SIGNAL,
    UV_FILE,
    UV_HANDLE_TYPE_MAX
} uv_handle_type;

struct uv_handle_s;//insertRecordDeclare 

/*TD*/typedef struct uv_handle_s uv_handle_t;

/*TD*/typedef void (*uv_close_cb)(uv_handle_t *);

struct uv__queue;//insertRecordDeclare 


struct uv__queue {
    struct uv__queue *next;
    struct uv__queue *prev;
};

struct uv_buf_t;//insertRecordDeclare 

/*TD*/typedef struct uv_buf_t uv_buf_t;

/*TD*/typedef void (*uv_alloc_cb)(uv_handle_t *, size_t, uv_buf_t *);

struct sockaddr;//insertRecordDeclare 

/*TD*/typedef void (*uv_udp_recv_cb)(uv_udp_t *, ssize_t, const uv_buf_t *, const struct sockaddr *, unsigned int);

/*TD*/typedef void (*uv__io_cb)(struct uv_loop_s *, struct uv__io_s *, unsigned int);


struct uv__io_s {
    uv__io_cb cb;
    struct uv__queue pending_queue;
    struct uv__queue watcher_queue;
    unsigned int pevents;
    unsigned int events;
    int fd;
};


struct uv_udp_s {
    void *data;
    uv_loop_t *loop;
    uv_handle_type type;
    uv_close_cb close_cb;
    struct uv__queue handle_queue;
    union {
        int fd;
        void *reserved[4];
    } u;
    uv_handle_t *next_closing;
    unsigned int flags;
    size_t send_queue_size;
    size_t send_queue_count;
    uv_alloc_cb alloc_cb;
    uv_udp_recv_cb recv_cb;
    uv__io_t io_watcher;
    struct uv__queue write_queue;
    struct uv__queue write_completed_queue;
};

struct sockaddr_in6;//insertRecordDeclare 

struct iovec;//insertRecordDeclare 

struct mmsghdr;//insertRecordDeclare 


struct uv_buf_t {
    char *base;
    size_t len;
};

struct msghdr;//insertRecordDeclare 

/*ENUM*/
enum uv_udp_flags {
    UV_UDP_IPV6ONLY = 1,
    UV_UDP_PARTIAL = 2,
    UV_UDP_REUSEADDR = 4,
    UV_UDP_MMSG_CHUNK = 8,
    UV_UDP_MMSG_FREE = 16,
    UV_UDP_LINUX_RECVERR = 32,
    UV_UDP_REUSEPORT = 64,
    UV_UDP_RECVMMSG = 256
};

struct sockaddr_storage;//insertRecordDeclare 

/*ANo ENUM*/
enum {
    UV_HANDLE_CLOSING = 1,
    UV_HANDLE_CLOSED = 2,
    UV_HANDLE_ACTIVE = 4,
    UV_HANDLE_REF = 8,
    UV_HANDLE_INTERNAL = 16,
    UV_HANDLE_ENDGAME_QUEUED = 32,
    UV_HANDLE_LISTENING = 64,
    UV_HANDLE_CONNECTION = 128,
    UV_HANDLE_SHUT = 512,
    UV_HANDLE_READ_PARTIAL = 1024,
    UV_HANDLE_READ_EOF = 2048,
    UV_HANDLE_READING = 4096,
    UV_HANDLE_BOUND = 8192,
    UV_HANDLE_READABLE = 16384,
    UV_HANDLE_WRITABLE = 32768,
    UV_HANDLE_READ_PENDING = 65536,
    UV_HANDLE_SYNC_BYPASS_IOCP = 131072,
    UV_HANDLE_ZERO_READ = 262144,
    UV_HANDLE_EMULATE_IOCP = 524288,
    UV_HANDLE_BLOCKING_WRITES = 1048576,
    UV_HANDLE_CANCELLATION_PENDING = 2097152,
    UV_HANDLE_IPV6 = 4194304,
    UV_HANDLE_TCP_NODELAY = 16777216,
    UV_HANDLE_TCP_KEEPALIVE = 33554432,
    UV_HANDLE_TCP_SINGLE_ACCEPT = 67108864,
    UV_HANDLE_TCP_ACCEPT_STATE_CHANGING = 134217728,
    UV_HANDLE_SHARED_TCP_SOCKET = 268435456,
    UV_HANDLE_UDP_PROCESSING = 16777216,
    UV_HANDLE_UDP_CONNECTED = 33554432,
    UV_HANDLE_UDP_RECVMMSG = 67108864,
    UV_HANDLE_NON_OVERLAPPED_PIPE = 16777216,
    UV_HANDLE_PIPESERVER = 33554432,
    UV_HANDLE_TTY_READABLE = 16777216,
    UV_HANDLE_UNUSED0 = 33554432,
    UV_HANDLE_TTY_SAVED_POSITION = 67108864,
    UV_HANDLE_TTY_SAVED_ATTRIBUTES = 134217728,
    UV_SIGNAL_ONE_SHOT_DISPATCHED = 16777216,
    UV_SIGNAL_ONE_SHOT = 33554432,
    UV_HANDLE_POLL_SLOW = 16777216,
    UV_HANDLE_REAP = 268435456
};

#endif