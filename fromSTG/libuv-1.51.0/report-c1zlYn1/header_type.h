#ifndef __HEADER_TYPE_H__ 
#define __HEADER_TYPE_H__
#include"../common.h" 
struct stat;//insertRecordDeclare 

struct uv_loop_s;//insertRecordDeclare 

/*TD*/typedef struct uv_loop_s uv_loop_t;

struct uv_tty_s;//insertRecordDeclare 

/*TD*/typedef struct uv_tty_s uv_tty_t;


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

/*TD*/typedef int uv_file;

struct sockaddr_storage;//insertRecordDeclare 

#endif