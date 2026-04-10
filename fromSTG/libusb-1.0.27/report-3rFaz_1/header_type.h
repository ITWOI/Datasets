#ifndef __HEADER_TYPE_H__ 
#define __HEADER_TYPE_H__
#include"../common.h" 
/*TD*/typedef pthread_mutex_t usbi_mutex_t;

struct list_head;//insertRecordDeclare 


struct list_head {
    struct list_head *prev;
    struct list_head *next;
};

struct libusb_context;//insertRecordDeclare 

/*ENUM*/
enum libusb_log_level {
    LIBUSB_LOG_LEVEL_NONE = 0,
    LIBUSB_LOG_LEVEL_ERROR = 1,
    LIBUSB_LOG_LEVEL_WARNING = 2,
    LIBUSB_LOG_LEVEL_INFO = 3,
    LIBUSB_LOG_LEVEL_DEBUG = 4
};

struct timespec;//insertRecordDeclare 

struct libusb_device;//insertRecordDeclare 

struct discovered_devs;//insertRecordDeclare 


struct discovered_devs {
    size_t len;
    size_t capacity;
    struct libusb_device *devices[];
};

/*TD*/typedef struct libusb_device libusb_device;

/*TD*/typedef atomic_long usbi_atomic_t;

/*ENUM*/
enum libusb_speed {
    LIBUSB_SPEED_UNKNOWN = 0,
    LIBUSB_SPEED_LOW = 1,
    LIBUSB_SPEED_FULL = 2,
    LIBUSB_SPEED_HIGH = 3,
    LIBUSB_SPEED_SUPER = 4,
    LIBUSB_SPEED_SUPER_PLUS = 5
};

struct libusb_device_descriptor;//insertRecordDeclare 


struct libusb_device_descriptor {
    uint8_t bLength;
    uint8_t bDescriptorType;
    uint16_t bcdUSB;
    uint8_t bDeviceClass;
    uint8_t bDeviceSubClass;
    uint8_t bDeviceProtocol;
    uint8_t bMaxPacketSize0;
    uint16_t idVendor;
    uint16_t idProduct;
    uint16_t bcdDevice;
    uint8_t iManufacturer;
    uint8_t iProduct;
    uint8_t iSerialNumber;
    uint8_t bNumConfigurations;
};


struct libusb_device {
    usbi_atomic_t refcnt;
    struct libusb_context *ctx;
    struct libusb_device *parent_dev;
    uint8_t bus_number;
    uint8_t port_number;
    uint8_t device_address;
    enum libusb_speed speed;
    struct list_head list;
    unsigned long session_data;
    struct libusb_device_descriptor device_descriptor;
    usbi_atomic_t attached;
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

/*TD*/typedef int libusb_hotplug_callback_handle;

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


typedef enum {
    LIBUSB_HOTPLUG_EVENT_DEVICE_ARRIVED = (1 << 0),
    LIBUSB_HOTPLUG_EVENT_DEVICE_LEFT = (1 << 1)
} libusb_hotplug_event;

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

/*ENUM*/
enum libusb_capability {
    LIBUSB_CAP_HAS_CAPABILITY = 0U,
    LIBUSB_CAP_HAS_HOTPLUG = 1U,
    LIBUSB_CAP_HAS_HID_ACCESS = 256U,
    LIBUSB_CAP_SUPPORTS_DETACH_KERNEL_DRIVER = 257U
};

struct usbi_os_backend;//insertRecordDeclare 

/*ENUM*/
enum libusb_option {
    LIBUSB_OPTION_LOG_LEVEL = 0,
    LIBUSB_OPTION_USE_USBDK = 1,
    LIBUSB_OPTION_NO_DEVICE_DISCOVERY = 2,
    LIBUSB_OPTION_LOG_CB = 3,
    LIBUSB_OPTION_MAX = 4
};

struct __va_list_tag;//insertRecordDeclare 

struct libusb_device_handle;//insertRecordDeclare 

struct usbi_transfer;//insertRecordDeclare 


struct usbi_os_backend {
    const char *name;
    uint32_t caps;
    int (*init)(struct libusb_context *);
    void (*exit)(struct libusb_context *);
    int (*set_option)(struct libusb_context *, enum libusb_option, struct __va_list_tag *);
    int (*get_device_list)(struct libusb_context *, struct discovered_devs **);
    void (*hotplug_poll)(void);
    int (*wrap_sys_device)(struct libusb_context *, struct libusb_device_handle *, intptr_t);
    int (*open)(struct libusb_device_handle *);
    void (*close)(struct libusb_device_handle *);
    int (*get_active_config_descriptor)(struct libusb_device *, void *, size_t);
    int (*get_config_descriptor)(struct libusb_device *, uint8_t, void *, size_t);
    int (*get_config_descriptor_by_value)(struct libusb_device *, uint8_t, void **);
    int (*get_configuration)(struct libusb_device_handle *, uint8_t *);
    int (*set_configuration)(struct libusb_device_handle *, int);
    int (*claim_interface)(struct libusb_device_handle *, uint8_t);
    int (*release_interface)(struct libusb_device_handle *, uint8_t);
    int (*set_interface_altsetting)(struct libusb_device_handle *, uint8_t, uint8_t);
    int (*clear_halt)(struct libusb_device_handle *, unsigned char);
    int (*reset_device)(struct libusb_device_handle *);
    int (*alloc_streams)(struct libusb_device_handle *, uint32_t, unsigned char *, int);
    int (*free_streams)(struct libusb_device_handle *, unsigned char *, int);
    void *(*dev_mem_alloc)(struct libusb_device_handle *, size_t);
    int (*dev_mem_free)(struct libusb_device_handle *, void *, size_t);
    int (*kernel_driver_active)(struct libusb_device_handle *, uint8_t);
    int (*detach_kernel_driver)(struct libusb_device_handle *, uint8_t);
    int (*attach_kernel_driver)(struct libusb_device_handle *, uint8_t);
    void (*destroy_device)(struct libusb_device *);
    int (*submit_transfer)(struct usbi_transfer *);
    int (*cancel_transfer)(struct usbi_transfer *);
    void (*clear_transfer_priv)(struct usbi_transfer *);
    int (*handle_events)(struct libusb_context *, void *, unsigned int, unsigned int);
    int (*handle_transfer_completion)(struct usbi_transfer *);
    size_t context_priv_size;
    size_t device_priv_size;
    size_t device_handle_priv_size;
    size_t transfer_priv_size;
};

/*TD*/typedef struct libusb_device_handle libusb_device_handle;


struct libusb_device_handle {
    usbi_mutex_t lock;
    unsigned long claimed_interfaces;
    struct list_head list;
    struct libusb_device *dev;
    int auto_detach_kernel_driver;
};

struct _IO_FILE;//insertRecordDeclare 

#endif