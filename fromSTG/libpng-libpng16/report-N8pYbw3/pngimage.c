static int is_combo (int transforms){
    return transforms & (transforms - 1);
}


static struct buffer * get_buffer (png_structp pp){
    return (struct buffer *)png_get_io_ptr(pp);
}


static struct buffer_list * buffer_extend (struct buffer_list *current){
    struct buffer_list *add;
    ((void)sizeof ((current->next == ((void *)0)) ? 1 : 0) , __extension__ ({
        if (current->next == ((void *)0))
            ;
        else
            __assert_fail("current->next == NULL", "contrib/libtests/pngimage_InstSlice.c", 378, __extension__ __PRETTY_FUNCTION__);
    }));
    add = ((struct buffer_list *)malloc(sizeof(struct buffer_list)));
    if (add == ((void *)0))
        return ((void *)0);
    add->next = ((void *)0);
    current->next = add;
    return add;
}


static struct display * get_dp (png_structp pp){
    struct display *dp = (struct display *)png_get_error_ptr(pp);
    if (dp == ((void *)0)) {
        ;
        ;
    }
    return dp;
}


static  __attribute__((format(printf, 3, 4))) void display_log (struct display *dp, error_level level, const char *fmt, ...){
    dp->results |= 1U << level;
    if (level > (error_level)(dp->options & 15)) {
        const char *lp;
        va_list ap;
        switch (level) {
          case INFORMATION:
            lp = "information";
            break;
            ;
          case LIBPNG_WARNING:
            lp = "warning(libpng)";
            break;
            ;
          case APP_WARNING:
            lp = "warning(pngimage)";
            break;
            ;
          case APP_FAIL:
            lp = "error(continuable)";
            break;
            ;
          case LIBPNG_ERROR:
            lp = "error(libpng)";
            break;
            ;
          case LIBPNG_BUG:
            lp = "bug(libpng)";
            break;
            ;
          case APP_ERROR:
            lp = "error(pngimage)";
            break;
            ;
          case USER_ERROR:
            lp = "error(user)";
            break;
            ;
          case INTERNAL_ERROR:
          case VERBOSE:
          case WARNINGS:
          case ERRORS:
          case QUIET:
          default:
            lp = "bug(pngimage)";
            break;
            ;
        }
        ;
        if (dp->transforms != 0) {
            int tr = dp->transforms;
            if (is_combo(tr)) {
                if (dp->options & 2048) {
                    int trx = tr;
                    ;
                    if (trx) {
                        int start = 0;
                        while (trx)
                            {
                                int trz = trx & -trx;
                                ;
                                ;
                                start = 1;
                                trx &= ~trz;
                            }
                    } else {
                        ;
                    }
                    ;
                } else {
                    ;
                }
            } else {
                ;
            }
        }
        ;
        __builtin_va_start(ap, fmt);
        ;
        ;
        ;
    }
    if (level > APP_FAIL || (level > ERRORS && !(dp->options & 128))) {
    }
    ;
}


static void buffer_write (struct display *dp, struct buffer *buffer, png_bytep data, size_t size){
    struct buffer_list *last = buffer->last;
    size_t end_count = buffer->end_count;
    while (size > 0)
        {
            size_t avail;
            if (end_count >= sizeof last->buffer) {
                if (last->next == ((void *)0)) {
                    last = buffer_extend(last);
                    if (last == ((void *)0))
                        display_log(dp, APP_ERROR, "out of memory saving file");
                } else
                    last = last->next;
                buffer->last = last;
                end_count = 0;
            }
            avail = (sizeof last->buffer) - end_count;
            if (avail > size)
                avail = size;
            memcpy(last->buffer + end_count, data, avail);
            end_count += avail;
            size -= avail;
            data += avail;
        }
    ;
}


static void write_function (png_structp pp, png_bytep data, size_t size){
    buffer_write(get_dp(pp), get_buffer(pp), data, size);
}


