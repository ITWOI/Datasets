#include "header_func.h"
static int is_combo (int transforms){
    return transforms & (transforms - 1);
}
static int first_transform (int transforms){
    return transforms & -transforms;
}
static int is_bad_combo (int transforms){
    unsigned int i;
    for (i = 0; i < ((sizeof known_bad_combos) / (sizeof known_bad_combos[0])); ++i) {
        int combo = known_bad_combos[i][0];
        if ((combo & transforms) == combo && (transforms & known_bad_combos[i][1]) == 0)
            return 1;
    }
    return 0;
}
static void validate_T (){
    unsigned int i;
    for (i = 0; i < ((sizeof transform_info) / (sizeof transform_info[0])); ++i) {
        if (transform_info[i].name != ((void *)0)) {
            if (transform_info[i].when & 1)
                read_transforms |= transform_info[i].transform;
            if (transform_info[i].when & 2)
                write_transforms |= transform_info[i].transform;
        }
    }
    rw_transforms = read_transforms & write_transforms;
}
static void buffer_init (struct buffer *buffer){
    buffer->first.next = ((void *)0);
    buffer->last = ((void *)0);
    buffer->current = ((void *)0);
}
static void buffer_destroy (struct buffer *buffer){
    struct buffer_list *list;
    buffer_init(buffer);
}
static void buffer_start_write (struct buffer *buffer){
    buffer->last = &buffer->first;
    buffer->end_count = 0;
    buffer->current = ((void *)0);
}
static void buffer_start_read (struct buffer *buffer){
    buffer->current = &buffer->first;
    buffer->read_count = 0;
}
static struct buffer_list * buffer_extend (struct buffer_list *current){
    struct buffer_list *add;
    ((void)sizeof ((current->next == ((void *)0)) ? 1 : 0) , __extension__ ({
        if (current->next == ((void *)0))
            ;
        else
            __assert_fail("current->next == NULL", "contrib/libtests/pngimage_InstSlice.c", 424, __extension__ __PRETTY_FUNCTION__);
    }));
    add = ((struct buffer_list *)malloc(sizeof(struct buffer_list)));
    if (add == ((void *)0))
        return ((void *)0);
    add->next = ((void *)0);
    current->next = add;
    return add;
}
static int buffer_from_file (struct buffer *buffer, FILE *fp){
    struct buffer_list *last = &buffer->first;
    size_t count = 0;
    for (;;) {
        size_t r = fread(last->buffer + count, 1, (sizeof last->buffer) - count, fp);
        if (r > 0) {
            count += r;
            if (count >= sizeof last->buffer) {
                ((void)sizeof ((count == sizeof last->buffer) ? 1 : 0) , __extension__ ({
                    if (count == sizeof last->buffer)
                        ;
                    else
                        __assert_fail("count == sizeof last->buffer", "contrib/libtests/pngimage_InstSlice.c", 455, __extension__ __PRETTY_FUNCTION__);
                }));
                count = 0;
                if (last->next == ((void *)0)) {
                    last = buffer_extend(last);
                    if (last == ((void *)0))
                        return 12;
                } else
                    last = last->next;
            }
        } else {
            if (feof(fp)) {
                buffer->last = last;
                buffer->end_count = count;
                return 0;
            }
            return (*__errno_location()) == 0 ? 34 : (*__errno_location());
        }
    }
}
static void display_init (struct display *dp){
    memset(dp, 0, sizeof *dp);
    dp->options = WARNINGS;
    dp->filename = ((void *)0);
    dp->operation = ((void *)0);
    dp->original_pp = ((void *)0);
    dp->original_ip = ((void *)0);
    dp->original_rows = ((void *)0);
    dp->read_pp = ((void *)0);
    dp->read_ip = ((void *)0);
    buffer_init(&dp->original_file);
    dp->write_pp = ((void *)0);
    buffer_init(&dp->written_file);
}
static void display_clean (struct display *dp){
    ;
    dp->original_rowbytes = 0;
    dp->original_rows = ((void *)0);
    dp->chunks = 0;
    dp->results = 0;
}
static void display_destroy (struct display *dp){
    buffer_destroy(&dp->written_file);
    buffer_destroy(&dp->original_file);
}
static  __attribute__((format(printf, 3, 4))) void display_log (struct display *dp, error_level level, const char *fmt, ...){
    dp->results |= 1U << level;
    if (level > (error_level)(dp->options & 15)) {
        const char *lp;
        va_list ap;
        if (dp->transforms != 0) {
            int tr = dp->transforms;
            if (is_combo(tr)) {
                ;
            } else {
                ;
            }
        }
        ;
    }
    if (level > APP_FAIL || (level > ERRORS && !(dp->options & 128))) {
    }
    ;
}
static void display_cache_file (struct display *dp, const char *filename){
    FILE *fp;
    int ret;
    dp->filename = filename;
    if (filename != ((void *)0)) {
        fp = fopen(filename, "rb");
        if (fp == ((void *)0))
            display_log(dp, USER_ERROR, "open failed: %s", strerror((*__errno_location())));
    } else
        fp = stdin;
    ret = buffer_from_file(&dp->original_file, fp);
    if (ret != 0)
        display_log(dp, APP_ERROR, "read failed: %s", strerror(ret));
}
static void read_png (struct display *dp, struct buffer *bp, const char *operation, int transforms){
    png_structp pp;
    png_infop ip;
    if (operation != ((void *)0)) {
        dp->operation = operation;
        dp->transforms = transforms;
    }
    dp->read_pp = pp = png_create_read_struct("1.6.45.git", dp, display_error, display_warning);
    if (pp == ((void *)0))
        display_log(dp, LIBPNG_ERROR, "failed to create read struct");
    dp->read_ip = ip = png_create_info_struct(pp);
    if (ip == ((void *)0))
        display_log(dp, LIBPNG_ERROR, "failed to create info struct");
    buffer_start_read(bp);
}
static void update_display (struct display *dp){
    png_structp pp;
    png_infop ip;
    read_png(dp, &dp->original_file, "original read", 0);
    dp->original_pp = pp = dp->read_pp , dp->read_pp = ((void *)0);
    dp->original_ip = ip = dp->read_ip , dp->read_ip = ((void *)0);
    dp->original_rowbytes = png_get_rowbytes(pp, ip);
    if (dp->original_rowbytes == 0)
        display_log(dp, LIBPNG_BUG, "png_get_rowbytes returned 0");
    dp->chunks = png_get_valid(pp, ip, 4294967295U);
    if ((dp->chunks & 32768U) == 0)
        display_log(dp, LIBPNG_BUG, "png_read_png did not set IDAT flag");
    dp->original_rows = png_get_rows(pp, ip);
    if (dp->original_rows == ((void *)0))
        display_log(dp, LIBPNG_BUG, "png_read_png did not create row buffers");
    if (!png_get_IHDR(pp, ip, &dp->width, &dp->height, &dp->bit_depth, &dp->color_type, &dp->interlace_method, &dp->compression_method, &dp->filter_method))
        display_log(dp, LIBPNG_BUG, "png_get_IHDR failed");
    {
        png_uint_32 chunks = dp->chunks;
        int active = 0, inactive = 0;
        int ct = dp->color_type;
        int bd = dp->bit_depth;
        unsigned int i;
        for (i = 0; i < ((sizeof transform_info) / (sizeof transform_info[0])); ++i) {
            if (transform_info[i].name != ((void *)0)) {
                int transform = transform_info[i].transform;
                if ((transform_info[i].valid_chunks == 0 || (transform_info[i].valid_chunks & chunks) != 0) && (transform_info[i].color_mask_required & ct) == transform_info[i].color_mask_required && (transform_info[i].color_mask_absent & ct) == 0 && (transform_info[i].bit_depths & bd) != 0 && (transform_info[i].when & 1) != 0)
                    active |= transform;
                else if ((transform_info[i].when & 1) != 0)
                    inactive |= transform;
            }
        }
        inactive &= ~active;
        dp->active_transforms = active;
        dp->ignored_transforms = inactive;
    }
}
static int compare_read (struct display *dp, int applied_transforms){
    size_t rowbytes;
    png_uint_32 width, height;
    int bit_depth, color_type;
    int interlace_method, compression_method, filter_method;
    const char *e = ((void *)0);
    if (!png_get_IHDR(dp->read_pp, dp->read_ip, &width, &height, &bit_depth, &color_type, &interlace_method, &compression_method, &filter_method))
        display_log(dp, LIBPNG_BUG, "png_get_IHDR failed");
    if (width != dp->width)
        display_log(dp, APP_WARNING, "IHDR width(%lu) changed to %lu", (unsigned long)dp->width, (unsigned long)width) , e = "width";
    if (height != dp->height)
        display_log(dp, APP_WARNING, "IHDR height(%lu) changed to %lu", (unsigned long)dp->height, (unsigned long)height) , e = "height";
    if (bit_depth != dp->bit_depth)
        display_log(dp, APP_WARNING, "IHDR bit_depth(%lu) changed to %lu", (unsigned long)dp->bit_depth, (unsigned long)bit_depth) , e = "bit_depth";
    if (color_type != dp->color_type)
        display_log(dp, APP_WARNING, "IHDR color_type(%lu) changed to %lu", (unsigned long)dp->color_type, (unsigned long)color_type) , e = "color_type";
    if (interlace_method != dp->interlace_method)
        display_log(dp, APP_WARNING, "IHDR interlace_method(%lu) changed to %lu", (unsigned long)dp->interlace_method, (unsigned long)interlace_method) , e = "interlace_method";
    if (compression_method != dp->compression_method)
        display_log(dp, APP_WARNING, "IHDR compression_method(%lu) changed to %lu", (unsigned long)dp->compression_method, (unsigned long)compression_method) , e = "compression_method";
    if (filter_method != dp->filter_method)
        display_log(dp, APP_WARNING, "IHDR filter_method(%lu) changed to %lu", (unsigned long)dp->filter_method, (unsigned long)filter_method) , e = "filter_method";
    if (e)
        display_log(dp, APP_ERROR, "IHDR changed (%s)", e);
    {
        unsigned long chunks = png_get_valid(dp->read_pp, dp->read_ip, 4294967295U);
        if (chunks != dp->chunks)
            display_log(dp, APP_FAIL, "PNG chunks changed from 0x%lx to 0x%lx", (unsigned long)dp->chunks, chunks);
    }
    rowbytes = png_get_rowbytes(dp->read_pp, dp->read_ip);
    if (rowbytes != dp->original_rowbytes)
        display_log(dp, APP_ERROR, "PNG rowbytes changed from %lu to %lu", (unsigned long)dp->original_rowbytes, (unsigned long)rowbytes);
    {
        png_bytepp rows = png_get_rows(dp->read_pp, dp->read_ip);
        unsigned int mask;
        if (bit_depth < 8) {
            mask = 255 & (65280 >> ((bit_depth * width) & 7));
        } else
            mask = 0;
        if (rows == ((void *)0))
            display_log(dp, LIBPNG_BUG, "png_get_rows returned NULL");
        if ((applied_transforms & 64) == 0 || (dp->active_transforms & 64) == 0 || color_type == (2 | 1)) {
            unsigned long y;
            for (y = 0; y < height; ++y) {
                png_bytep row = rows[y];
                png_bytep orig = dp->original_rows[y];
                if (memcmp(row, orig, rowbytes - (mask != 0)) != 0 || (mask != 0 && ((row[rowbytes - 1] & mask) != (orig[rowbytes - 1] & mask)))) {
                    size_t x;
                    for (x = 0; x < rowbytes - 1; ++x)
                        if (row[x] != orig[x])
                            break;
                    display_log(dp, APP_FAIL, "byte(%lu,%lu) changed 0x%.2x -> 0x%.2x", (unsigned long)x, (unsigned long)y, orig[x], row[x]);
                    return 0;
                }
            }
        } else {
            unsigned long y;
            int bpp;
            png_byte sig_bits[8];
            png_color_8p sBIT;
            if (png_get_sBIT(dp->read_pp, dp->read_ip, &sBIT) != 2U)
                display_log(dp, INTERNAL_ERROR, "active shift transform but no sBIT in file");
            switch (color_type) {
              case 0:
                sig_bits[0] = sBIT->gray;
                bpp = bit_depth;
                break;
              case (4):
                sig_bits[0] = sBIT->gray;
                sig_bits[1] = sBIT->alpha;
                bpp = 2 * bit_depth;
                break;
              case (2):
                sig_bits[0] = sBIT->red;
                sig_bits[1] = sBIT->green;
                sig_bits[2] = sBIT->blue;
                bpp = 3 * bit_depth;
                break;
              case (2 | 4):
                sig_bits[0] = sBIT->red;
                sig_bits[1] = sBIT->green;
                sig_bits[2] = sBIT->blue;
                sig_bits[3] = sBIT->alpha;
                bpp = 4 * bit_depth;
                break;
              default:
                display_log(dp, LIBPNG_ERROR, "invalid colour type %d", color_type);
                memset(sig_bits, 0, sizeof (sig_bits));
                bpp = 0;
                break;
            }
            {
                int b;
                for (b = 0; 8 * b < bpp; ++b) {
                    if (sig_bits[b] == 0 || sig_bits[b] > bit_depth)
                        display_log(dp, LIBPNG_BUG, "invalid sBIT[%u]  value %d returned for PNG bit depth %d", b, sig_bits[b], bit_depth);
                }
            }
            if (bpp < 8 && bpp != bit_depth) {
                display_log(dp, INTERNAL_ERROR, "invalid bpp %u for bit_depth %u", bpp, bit_depth);
            }
            switch (bit_depth) {
                int b;
              case 16:
                for (b = (bpp >> 4); b > 0; --b) {
                    unsigned int sig = (unsigned int)(4294901760U >> sig_bits[b]);
                    sig_bits[2 * b + 1] = (png_byte)sig;
                    sig_bits[2 * b + 0] = (png_byte)(sig >> 8);
                }
                break;
              case 8:
                for (b = 0; b * 8 < bpp; ++b)
                    sig_bits[b] = (png_byte)(65280 >> sig_bits[b]);
                break;
              case 1:
                sig_bits[0] = 255;
                break;
              case 2:
                b = 3 & ((3 << 2) >> sig_bits[0]);
                b |= b << 2;
                b |= b << 4;
                sig_bits[0] = (png_byte)b;
                break;
              case 4:
                b = 15 & ((15 << 4) >> sig_bits[0]);
                b |= b << 4;
                sig_bits[0] = (png_byte)b;
                break;
              default:
                display_log(dp, LIBPNG_BUG, "invalid bit depth %d", bit_depth);
                break;
            }
            bpp = (bpp + 7) >> 3;
            if (mask != 0) {
                mask &= sig_bits[0];
                if (bpp != 1 || mask == 0)
                    display_log(dp, INTERNAL_ERROR, "mask calculation error %u, %u", bpp, mask);
            }
            for (y = 0; y < height; ++y) {
                png_bytep row = rows[y];
                png_bytep orig = dp->original_rows[y];
                unsigned long x;
                for (x = 0; x < (width - (mask != 0)); ++x) {
                    int b;
                    for (b = 0; b < bpp; ++b) {
                        if ((*row++ & sig_bits[b]) != (*orig++ & sig_bits[b])) {
                            display_log(dp, APP_FAIL, "significant bits at (%lu[%u],%lu) changed %.2x->%.2x", x, b, y, orig[-1], row[-1]);
                            return 0;
                        }
                    }
                }
                if (mask != 0 && (*row & mask) != (*orig & mask)) {
                    display_log(dp, APP_FAIL, "significant bits at (%lu[end],%lu) changed", x, y);
                    return 0;
                }
            }
        }
    }
    return 1;
}
static void write_png (struct display *dp, png_infop ip, int transforms){
    ;
    buffer_start_write(&dp->written_file);
    dp->operation = "write";
    dp->transforms = transforms;
    dp->write_pp = png_create_write_struct("1.6.45.git", dp, display_error, display_warning);
    if (dp->write_pp == ((void *)0))
        display_log(dp, APP_ERROR, "failed to create write png_struct");
}
static int skip_transform (struct display *dp, int tr){
    if ((dp->options & 256) != 0 && is_bad_combo(tr)) {
        if ((dp->options & 512) != 0) {
            ;
            while (tr != 0)
                {
                    int next = first_transform(tr);
                    tr &= ~next;
                }
            ;
        } else
            display_log(dp, INFORMATION, "%s: skipped known bad combo 0x%x", dp->filename, tr);
        return 1;
    }
    return 0;
}
static void test_one_file (struct display *dp, const char *filename){
    dp->operation = "cache file";
    dp->transforms = 0;
    display_cache_file(dp, filename);
    update_display(dp);
    if (dp->ignored_transforms != 0) {
        read_png(dp, &dp->original_file, "ignored transforms", dp->ignored_transforms);
        if (!compare_read(dp, 0))
            return;
    }
    ;
    write_png(dp, dp->original_ip, 0);
    read_png(dp, &dp->written_file, ((void *)0), 0);
    if (!compare_read(dp, 0))
        return;
    {
        unsigned int active = dp->active_transforms;
        int exhaustive = (dp->options & 16) != 0;
        unsigned int current = first_transform(active);
        unsigned int bad_transforms = 0;
        unsigned int bad_combo = ~0U;
        unsigned int bad_combo_list = 0;
        for (;;) {
            read_png(dp, &dp->original_file, "active transforms", current);
            if ((current & write_transforms) == current) {
                dp->operation = "reversible transforms";
                write_png(dp, dp->read_ip, current);
                read_png(dp, &dp->written_file, ((void *)0), 0);
                if (!compare_read(dp, current)) {
                    if (is_combo(current)) {
                        bad_combo &= current;
                        bad_combo_list |= current;
                    } else
                        bad_transforms |= current;
                }
            }
            if (exhaustive) {
                unsigned int next = current;
                do {
                    if (next == read_transforms)
                        goto combo;
                    ++next;
                } while ((next & read_transforms) <= current || (next & active) == 0 || (next & bad_transforms) != 0 || skip_transform(dp, next));
                ((void)sizeof (((next & read_transforms) == next) ? 1 : 0) , __extension__ ({
                    if ((next & read_transforms) == next)
                        ;
                    else
                        __assert_fail("(next & read_transforms) == next", "contrib/libtests/pngimage.c", 1535, __extension__ __PRETTY_FUNCTION__);
                }));
                current = next;
            } else {
                active &= ~current;
                if (active == 0)
                    goto combo;
                current = first_transform(active);
            }
        }
      combo:
        if (dp->options & 1024) {
            if (bad_combo != ~0U)
                printf("%s[0x%x]: PROBLEM: 0x%x[0x%x] ANTIDOTE: 0x%x\n", dp->filename, active, bad_combo, bad_combo_list, rw_transforms & ~bad_combo_list);
            else
                printf("%s: no %sbad combos found\n", dp->filename, (dp->options & 256) ? "additional " : "");
        }
    }
}
static int do_test (struct display *dp, const char *file){
    int ret = _setjmp(dp->error_return);
    if (ret == 0) {
        test_one_file(dp, file);
        return 0;
    } else if (ret < ERRORS)
        display_log(dp, INTERNAL_ERROR, "unexpected return code %d", ret);
    return ret;
}
extern int main (int argc, char **argv){
    int option_end, ilog = 0;
    struct display d;
    validate_T();
    display_init(&d);
    for (option_end = 1; option_end < argc; ++option_end) {
        const char *name = argv[option_end];
        if (strcmp(name, "--verbose") == 0) {
            d.options = (d.options & ~15) | VERBOSE;
        } else if (strcmp(name, "--warnings") == 0) {
            d.options = (d.options & ~15) | WARNINGS;
        } else if (strcmp(name, "--errors") == 0) {
            d.options = (d.options & ~15) | ERRORS;
        } else if (strcmp(name, "--quiet") == 0) {
            d.options = (d.options & ~15) | QUIET;
        } else if (strcmp(name, "--exhaustive") == 0) {
            d.options |= 16;
        } else if (strcmp(name, "--fast") == 0) {
            d.options &= ~16;
        } else if (strcmp(name, "--strict") == 0) {
            d.options |= 32;
        } else if (strcmp(name, "--relaxed") == 0) {
            d.options &= ~32;
        } else if (strcmp(name, "--log") == 0) {
            ilog = option_end;
            d.options |= 64;
        } else if (strcmp(name, "--nolog") == 0) {
            d.options &= ~64;
        } else if (strcmp(name, "--continue") == 0) {
            d.options |= 128;
        } else if (strcmp(name, "--stop") == 0) {
            d.options &= ~128;
        } else if (strcmp(name, "--skip-bugs") == 0) {
            d.options |= 256;
        } else if (strcmp(name, "--test-all") == 0) {
            d.options &= ~256;
        } else if (strcmp(name, "--log-skipped") == 0) {
            d.options |= 512;
        } else if (strcmp(name, "--nolog-skipped") == 0) {
            d.options &= ~512;
        } else if (strcmp(name, "--find-bad-combos") == 0) {
            d.options |= 1024;
        } else if (strcmp(name, "--nofind-bad-combos") == 0) {
            d.options &= ~1024;
        } else if (strcmp(name, "--list-combos") == 0) {
            d.options |= 2048;
        } else if (strcmp(name, "--nolist-combos") == 0) {
            d.options &= ~2048;
        } else if (name[0] == '-' && name[1] == '-') {
            ;
            return 99;
        } else {
            ;
        }
        ;
    }
    {
        int i;
        int errors = 0;
        for (i = option_end; i < argc; ++i) {
            {
                int ret = do_test(&d, argv[i]);
                if (ret > QUIET)
                    return 99;
            }
            {
                int pass = (d.options & 32) ? (((d.results) & ~((1U << WARNINGS) - 1)) == 0) : (((d.results) & ~((1U << ERRORS) - 1)) == 0);
                if (!pass)
                    ++errors;
                if (d.options & 64) {
                    int j;
                    printf("%s: pngimage ", pass ? "PASS" : "FAIL");
                    for (j = 1; j < option_end; ++j)
                        if (j != ilog)
                            printf("%s ", argv[j]);
                    printf("%s\n", d.filename);
                }
            }
            display_clean(&d);
        }
        display_destroy(&d);
        return errors != 0;
    }
}
