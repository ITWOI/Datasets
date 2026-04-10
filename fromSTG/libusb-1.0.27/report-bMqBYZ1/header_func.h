#ifndef __HEADER_FUNC_H__ 
#define __HEADER_FUNC_H__
#include"header_type.h" 
extern struct libusb_context *usbi_default_context;
;
void usbi_log(struct libusb_context *ctx, enum libusb_log_level level, const char *function, const char *format, ...);

extern struct libusb_context *usbi_fallback_context;
;
void libusb_unref_device(libusb_device *dev);

libusb_device *libusb_ref_device(libusb_device *dev);

static void discovered_devs_free(struct discovered_devs *discdevs) ;

static inline void usbi_mutex_lock(usbi_mutex_t *mutex) ;

static inline void list_del(struct list_head *entry) ;

static inline void usbi_mutex_unlock(usbi_mutex_t *mutex) ;


void usbi_hotplug_notification(struct libusb_context *ctx, struct libusb_device *dev, libusb_hotplug_event event);

static struct discovered_devs *discovered_devs_alloc(void) ;

static inline struct libusb_context *usbi_get_context(struct libusb_context *ctx) ;

int libusb_has_capability(uint32_t capability);

struct discovered_devs *discovered_devs_append(struct discovered_devs *discdevs, struct libusb_device *dev) ;

extern const struct usbi_os_backend usbi_backend;
;
void usbi_disconnect_device(struct libusb_device *dev) ;

static inline void usbi_mutex_init(usbi_mutex_t *mutex) ;

static inline void usbi_mutex_destroy(usbi_mutex_t *mutex) ;

static inline void list_add(struct list_head *entry, struct list_head *head) ;

ssize_t libusb_get_device_list(libusb_context *ctx, libusb_device ***list) ;


int libusb_get_device_descriptor(libusb_device *dev, struct libusb_device_descriptor *desc);

int libusb_open(libusb_device *dev, libusb_device_handle **dev_handle) ;

void libusb_free_device_list(libusb_device **list, int unref_devices) ;

static libusb_log_cb log_handler;
;
extern FILE *stderr;
;
static enum libusb_log_level get_env_debug_level(void) ;

static usbi_atomic_t default_debug_level = -1;
;
static void log_str(enum libusb_log_level level, const char *str) ;

static inline void usbi_get_monotonic_time(struct timespec *tp) ;


unsigned int usbi_get_tid(void);

static struct timespec timestamp_origin;
;
static void log_v(struct libusb_context *ctx, enum libusb_log_level level, const char *function, const char *format, va_list args) ;

#endif