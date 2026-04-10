#ifndef __HEADER_TYPE_H__ 
#define __HEADER_TYPE_H__
#include"../common.h" 
struct libusb_context;//insertRecordDeclare 

struct usbi_event_source;//insertRecordDeclare 

/*TD*/typedef int usbi_os_handle_t;

struct list_head;//insertRecordDeclare 


struct list_head {
    struct list_head *prev;
    struct list_head *next;
};


struct usbi_event_source {
    struct usbi_event_source_data {
        usbi_os_handle_t os_handle;
        short poll_events;
    } data;
    struct list_head list;
};

struct pollfd;//insertRecordDeclare 

/*ENUM*/
enum libusb_log_level {
    LIBUSB_LOG_LEVEL_NONE = 0,
    LIBUSB_LOG_LEVEL_ERROR = 1,
    LIBUSB_LOG_LEVEL_WARNING = 2,
    LIBUSB_LOG_LEVEL_INFO = 3,
    LIBUSB_LOG_LEVEL_DEBUG = 4
};

/*TD*/typedef struct libusb_context libusb_context;

/*TD*/typedef void (*libusb_log_cb)(libusb_context *, enum libusb_log_level, const char *);

struct usbi_event;//insertRecordDeclare 

/*TD*/typedef struct usbi_event usbi_event_t;


struct usbi_event {
    int eventfd;
};

struct usbi_timer;//insertRecordDeclare 

/*TD*/typedef struct usbi_timer usbi_timer_t;


struct usbi_timer {
    int timerfd;
};

/*TD*/typedef pthread_mutex_t usbi_mutex_t;

/*TD*/typedef int libusb_hotplug_callback_handle;

/*TD*/typedef atomic_long usbi_atomic_t;

/*TD*/typedef void (*libusb_pollfd_added_cb)(int, short, void *);

/*TD*/typedef void (*libusb_pollfd_removed_cb)(int, void *);

/*TD*/typedef pthread_key_t usbi_tls_key_t;

/*TD*/typedef pthread_cond_t usbi_cond_t;


struct libusb_context {
    enum libusb_log_level debug;
    int debug_fixed;
    libusb_log_cb log_handler;
    usbi_event_t event;
    usbi_timer_t timer;
    struct list_head usb_devs;
    usbi_mutex_t usb_devs_lock;
    struct list_head open_devs;
    usbi_mutex_t open_devs_lock;
    struct list_head hotplug_cbs;
    libusb_hotplug_callback_handle next_hotplug_cb_handle;
    usbi_mutex_t hotplug_cbs_lock;
    usbi_atomic_t hotplug_ready;
    struct list_head flying_transfers;
    usbi_mutex_t flying_transfers_lock;
    libusb_pollfd_added_cb fd_added_cb;
    libusb_pollfd_removed_cb fd_removed_cb;
    void *fd_cb_user_data;
    usbi_mutex_t events_lock;
    int event_handler_active;
    usbi_tls_key_t event_handling_key;
    usbi_mutex_t event_waiters_lock;
    usbi_cond_t event_waiters_cond;
    usbi_mutex_t event_data_lock;
    unsigned int event_flags;
    unsigned int device_close;
    struct list_head event_sources;
    struct list_head removed_event_sources;
    void *event_data;
    unsigned int event_data_cnt;
    struct list_head hotplug_msgs;
    struct list_head completed_transfers;
    struct list_head list;
};

/*ENUM*/
enum libusb_error {
    LIBUSB_SUCCESS = 0,
    LIBUSB_ERROR_IO = -1,
    LIBUSB_ERROR_INVALID_PARAM = -2,
    LIBUSB_ERROR_ACCESS = -3,
    LIBUSB_ERROR_NO_DEVICE = -4,
    LIBUSB_ERROR_NOT_FOUND = -5,
    LIBUSB_ERROR_BUSY = -6,
    LIBUSB_ERROR_TIMEOUT = -7,
    LIBUSB_ERROR_OVERFLOW = -8,
    LIBUSB_ERROR_PIPE = -9,
    LIBUSB_ERROR_INTERRUPTED = -10,
    LIBUSB_ERROR_NO_MEM = -11,
    LIBUSB_ERROR_NOT_SUPPORTED = -12,
    LIBUSB_ERROR_OTHER = -99
};

#endif