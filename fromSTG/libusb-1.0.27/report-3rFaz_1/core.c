static struct discovered_devs * discovered_devs_alloc (){
    struct discovered_devs *ret = malloc(sizeof (*ret) + (sizeof(void *) * 16));
    if (ret) {
        ret->len = 0;
        ret->capacity = 16;
    }
    return ret;
}


static void discovered_devs_free (struct discovered_devs *discdevs){
    size_t i;
    for (i = 0; i < discdevs->len; i++)
        libusb_unref_device(discdevs->devices[i]);
    free(discdevs);
}


extern struct discovered_devs * discovered_devs_append (struct discovered_devs *discdevs, struct libusb_device *dev){
    size_t len = discdevs->len;
    size_t capacity;
    struct discovered_devs *new_discdevs;
    if (len < discdevs->capacity) {
        discdevs->devices[len] = libusb_ref_device(dev);
        discdevs->len++;
        return discdevs;
    }
    usbi_log(((dev)->ctx), LIBUSB_LOG_LEVEL_DEBUG, __func__, "need to increase capacity");
    capacity = discdevs->capacity + 16;
    new_discdevs = realloc(discdevs, sizeof (*discdevs) + (sizeof(void *) * capacity));
    if (!new_discdevs) {
        discovered_devs_free(discdevs);
        return ((void *)0);
    }
    discdevs = new_discdevs;
    discdevs->capacity = capacity;
    discdevs->devices[len] = libusb_ref_device(dev);
    discdevs->len++;
    return discdevs;
}


extern void usbi_disconnect_device (struct libusb_device *dev){
    struct libusb_context *ctx = ((dev)->ctx);
    __c11_atomic_store((&dev->attached), (0), 5);
    usbi_mutex_lock(&ctx->usb_devs_lock);
    list_del(&dev->list);
    usbi_mutex_unlock(&ctx->usb_devs_lock);
    usbi_hotplug_notification(ctx, dev, LIBUSB_HOTPLUG_EVENT_DEVICE_LEFT);
}


extern  __attribute__((visibility("default"))) ssize_t libusb_get_device_list (libusb_context *ctx, libusb_device ***list){
    struct discovered_devs *discdevs = discovered_devs_alloc();
    struct libusb_device **ret;
    int r = 0;
    ssize_t i, len;
    usbi_log(ctx, LIBUSB_LOG_LEVEL_DEBUG, __func__, " ");
    if (!discdevs)
        return LIBUSB_ERROR_NO_MEM;
    ctx = usbi_get_context(ctx);
    if (libusb_has_capability(LIBUSB_CAP_HAS_HOTPLUG)) {
        struct libusb_device *dev;
        if (usbi_backend.hotplug_poll)
            usbi_backend.hotplug_poll();
        usbi_mutex_lock(&ctx->usb_devs_lock);
        for (dev = ((struct libusb_device *)((uintptr_t)((&(ctx)->usb_devs)->next) - (uintptr_t)__builtin_offsetof(struct libusb_device, list))); &dev->list != (&(ctx)->usb_devs); dev = ((struct libusb_device *)((uintptr_t)((dev)->list.next) - (uintptr_t)__builtin_offsetof(struct libusb_device, list)))) {
            discdevs = discovered_devs_append(discdevs, dev);
            if (!discdevs) {
                r = LIBUSB_ERROR_NO_MEM;
                break;
            }
        }
        usbi_mutex_unlock(&ctx->usb_devs_lock);
    } else {
        r = usbi_backend.get_device_list(ctx, &discdevs);
    }
    if (r < 0) {
        len = r;
        goto out;
        ;
    }
    len = (ssize_t)discdevs->len;
    ret = calloc((size_t)len + 1, sizeof(struct libusb_device *));
    if (!ret) {
        len = LIBUSB_ERROR_NO_MEM;
        goto out;
        ;
    }
    ret[len] = ((void *)0);
    for (i = 0; i < len; i++) {
        struct libusb_device *dev = discdevs->devices[i];
        ret[i] = libusb_ref_device(dev);
    }
    *list = ret;
  out:
    if (discdevs)
        discovered_devs_free(discdevs);
    return len;
}


extern  __attribute__((visibility("default"))) void libusb_free_device_list (libusb_device **list, int unref_devices){
    if (!list)
        return;
    if (unref_devices) {
        int i = 0;
        struct libusb_device *dev;
        while ((dev = list[i++]) != ((void *)0))
            libusb_unref_device(dev);
    }
    free(list);
}


extern  __attribute__((visibility("default"))) libusb_device * libusb_ref_device (libusb_device *dev){
    long refcnt;
    refcnt = (__c11_atomic_fetch_add((&dev->refcnt), 1, 5) + 1);
    ((void)sizeof ((refcnt >= 2) ? 1 : 0) , __extension__ ({
        if (refcnt >= 2)
            ;
        else
            __assert_fail("refcnt >= 2", "core_InstSlice.c", 1046, __extension__ __PRETTY_FUNCTION__);
    }));
    return dev;
}


extern  __attribute__((visibility("default"))) void libusb_unref_device (libusb_device *dev){
    long refcnt;
    if (!dev)
        return;
    refcnt = (__c11_atomic_fetch_add((&dev->refcnt), -1, 5) - 1);
    ((void)sizeof ((refcnt >= 0) ? 1 : 0) , __extension__ ({
        if (refcnt >= 0)
            ;
        else
            __assert_fail("refcnt >= 0", "core_InstSlice.c", 1064, __extension__ __PRETTY_FUNCTION__);
    }));
    if (refcnt == 0) {
        usbi_log(((dev)->ctx), LIBUSB_LOG_LEVEL_DEBUG, __func__, "destroy device %d.%d", dev->bus_number, dev->device_address);
        libusb_unref_device(dev->parent_dev);
        if (usbi_backend.destroy_device)
            usbi_backend.destroy_device(dev);
        if (!libusb_has_capability(LIBUSB_CAP_HAS_HOTPLUG)) {
            usbi_disconnect_device(dev);
        }
        free(dev);
    }
}


extern  __attribute__((visibility("default"))) int libusb_open (libusb_device *dev, libusb_device_handle **dev_handle){
    struct libusb_context *ctx = ((dev)->ctx);
    struct libusb_device_handle *_dev_handle;
    size_t priv_size = usbi_backend.device_handle_priv_size;
    int r;
    usbi_log(((dev)->ctx), LIBUSB_LOG_LEVEL_DEBUG, __func__, "open %d.%d", dev->bus_number, dev->device_address);
    if (!__c11_atomic_load((&dev->attached), 5))
        return LIBUSB_ERROR_NO_DEVICE;
    _dev_handle = calloc(1, (((sizeof (*_dev_handle)) + (sizeof(void *) - 1)) & ~(sizeof(void *) - 1)) + priv_size);
    if (!_dev_handle)
        return LIBUSB_ERROR_NO_MEM;
    usbi_mutex_init(&_dev_handle->lock);
    _dev_handle->dev = libusb_ref_device(dev);
    r = usbi_backend.open(_dev_handle);
    if (r < 0) {
        usbi_log(((dev)->ctx), LIBUSB_LOG_LEVEL_DEBUG, __func__, "open %d.%d returns %d", dev->bus_number, dev->device_address, r);
        libusb_unref_device(dev);
        usbi_mutex_destroy(&_dev_handle->lock);
        free(_dev_handle);
        return r;
    }
    usbi_mutex_lock(&ctx->open_devs_lock);
    list_add(&_dev_handle->list, &ctx->open_devs);
    usbi_mutex_unlock(&ctx->open_devs_lock);
    *dev_handle = _dev_handle;
    return 0;
}


extern  __attribute__((visibility("default"))) libusb_device_handle * libusb_open_device_with_vid_pid (libusb_context *ctx, uint16_t vendor_id, uint16_t product_id){
    struct libusb_device **devs;
    struct libusb_device *found = ((void *)0);
    struct libusb_device *dev;
    struct libusb_device_handle *dev_handle = ((void *)0);
    size_t i = 0;
    int r;
    if (libusb_get_device_list(ctx, &devs) < 0)
        return ((void *)0);
    while ((dev = devs[i++]) != ((void *)0))
        {
            struct libusb_device_descriptor desc;
            r = libusb_get_device_descriptor(dev, &desc);
            if (r < 0)
                goto out;
            ;
            if (desc.idVendor == vendor_id && desc.idProduct == product_id) {
                found = dev;
                break;
                ;
            }
        }
    if (found) {
        r = libusb_open(found, &dev_handle);
        if (r < 0)
            dev_handle = ((void *)0);
    }
  out:
    libusb_free_device_list(devs, 1);
    return dev_handle;
}


static enum libusb_log_level get_env_debug_level (){
    const char *dbg = getenv("LIBUSB_DEBUG");
    enum libusb_log_level level;
    if (dbg) {
        int dbg_level = atoi(dbg);
        dbg_level = ((dbg_level) < (LIBUSB_LOG_LEVEL_NONE) ? (LIBUSB_LOG_LEVEL_NONE) : ((dbg_level) > (LIBUSB_LOG_LEVEL_DEBUG) ? (LIBUSB_LOG_LEVEL_DEBUG) : (dbg_level)));
        level = (enum libusb_log_level)dbg_level;
    } else {
        level = LIBUSB_LOG_LEVEL_NONE;
    }
    return level;
}


extern  __attribute__((visibility("default"))) int libusb_has_capability (uint32_t capability){
    switch (capability) {
      case LIBUSB_CAP_HAS_CAPABILITY:
        return 1;
      case LIBUSB_CAP_HAS_HOTPLUG:
        return !(usbi_backend.get_device_list);
      case LIBUSB_CAP_HAS_HID_ACCESS:
        return (usbi_backend.caps & 65536);
      case LIBUSB_CAP_SUPPORTS_DETACH_KERNEL_DRIVER:
        return (usbi_backend.caps & 131072);
    }
    return 0;
}


static void log_str (enum libusb_log_level level, const char *str){
    if (log_handler) {
        log_handler(((void *)0), level, str);
    } else
        fputs(str, stderr);
}


static void log_v (struct libusb_context *ctx, enum libusb_log_level level, const char *function, const char *format, va_list args){
    const char *prefix;
    char buf[1024];
    int global_debug, header_len, text_len;
    static int has_debug_header_been_displayed;
    enum libusb_log_level ctx_level;
    long default_level_value;
    if (ctx) {
        ctx_level = ctx->debug;
    } else {
        default_level_value = __c11_atomic_load((&default_debug_level), 5);
        ctx_level = default_level_value < 0 ? get_env_debug_level() : (enum libusb_log_level)default_level_value;
    }
    if (ctx_level < level)
        return;
    global_debug = (ctx_level == LIBUSB_LOG_LEVEL_DEBUG);
    switch (level) {
      case LIBUSB_LOG_LEVEL_NONE:
        return;
      case LIBUSB_LOG_LEVEL_ERROR:
        prefix = "error";
        break;
        ;
      case LIBUSB_LOG_LEVEL_WARNING:
        prefix = "warning";
        break;
        ;
      case LIBUSB_LOG_LEVEL_INFO:
        prefix = "info";
        break;
        ;
      case LIBUSB_LOG_LEVEL_DEBUG:
        prefix = "debug";
        break;
        ;
      default:
        prefix = "unknown";
        break;
        ;
    }
    if (global_debug) {
        struct timespec timestamp;
        if (!has_debug_header_been_displayed) {
            has_debug_header_been_displayed = 1;
            log_str(LIBUSB_LOG_LEVEL_DEBUG, "[timestamp] [threadID] facility level [function call] <message>\n");
            log_str(LIBUSB_LOG_LEVEL_DEBUG, "--------------------------------------------------------------------------------\n");
        }
        usbi_get_monotonic_time(&timestamp);
        do {
            (&timestamp)->tv_sec = (&timestamp)->tv_sec - (&timestamp_origin)->tv_sec;
            (&timestamp)->tv_nsec = (&timestamp)->tv_nsec - (&timestamp_origin)->tv_nsec;
            if ((&timestamp)->tv_nsec < 0L) {
                --(&timestamp)->tv_sec;
                (&timestamp)->tv_nsec += 1000000000L;
            }
        } while (0);
        header_len = snprintf(buf, sizeof (buf), "[%2ld.%06ld] [%08x] libusb: %s [%s] ", (long)timestamp.tv_sec, (long)(timestamp.tv_nsec / 1000L), usbi_get_tid(), prefix, function);
    } else {
        header_len = snprintf(buf, sizeof (buf), "libusb: %s [%s] ", prefix, function);
    }
    if (header_len < 0 || header_len >= (int)sizeof (buf)) {
        header_len = 0;
    }
    text_len = vsnprintf(buf + header_len, sizeof (buf) - (size_t)header_len, format, args);
    if (text_len < 0 || text_len + header_len >= (int)sizeof (buf)) {
        text_len = (int)sizeof (buf) - header_len;
    }
    if (header_len + text_len + (int)sizeof ("\n") >= (int)sizeof (buf)) {
        text_len -= (header_len + text_len + (int)sizeof ("\n")) - (int)sizeof (buf);
    }
    strcpy(buf + header_len + text_len, "\n");
    log_str(level, buf);
    if (ctx && ctx->log_handler)
        ctx->log_handler(ctx, level, buf);
}


extern  __attribute__((format(printf, 4, 5))) void usbi_log (struct libusb_context *ctx, enum libusb_log_level level, const char *function, const char *format, ...){
    va_list args;
    ;
    log_v(ctx, level, function, format, args);
    ;
}


