#include "header_func.h"
static inline int usbi_handling_events (struct libusb_context *ctx){
    return usbi_tls_key_get(ctx->event_handling_key) != ((void *)0);
}
