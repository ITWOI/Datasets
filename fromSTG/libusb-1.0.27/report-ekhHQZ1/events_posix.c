extern int usbi_alloc_event_data (struct libusb_context *ctx){
    struct usbi_event_source *ievent_source;
    struct pollfd *fds;
    size_t i = 0;
    if (ctx->event_data) {
        ;
        ctx->event_data = ((void *)0);
    }
    ctx->event_data_cnt = 0;
    for (ievent_source = ((struct usbi_event_source *)((uintptr_t)((&(ctx)->event_sources)->next) - (uintptr_t)__builtin_offsetof(struct usbi_event_source, list))); &ievent_source->list != (&(ctx)->event_sources); ievent_source = ((struct usbi_event_source *)((uintptr_t)((ievent_source)->list.next) - (uintptr_t)__builtin_offsetof(struct usbi_event_source, list))))
        ctx->event_data_cnt++;
    fds = calloc(ctx->event_data_cnt, sizeof (*fds));
    if (!fds)
        return LIBUSB_ERROR_NO_MEM;
    for (ievent_source = ((struct usbi_event_source *)((uintptr_t)((&(ctx)->event_sources)->next) - (uintptr_t)__builtin_offsetof(struct usbi_event_source, list))); &ievent_source->list != (&(ctx)->event_sources); ievent_source = ((struct usbi_event_source *)((uintptr_t)((ievent_source)->list.next) - (uintptr_t)__builtin_offsetof(struct usbi_event_source, list)))) {
        fds[i].fd = ievent_source->data.os_handle;
        fds[i].events = ievent_source->data.poll_events;
        i++;
    }
    ;
    return 0;
}


