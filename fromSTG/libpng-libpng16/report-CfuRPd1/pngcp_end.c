#include "header_func.h"
static void display_init (struct display *dp){
    memset(dp, 0, sizeof *dp);
    dp->filename = "command line";
    dp->output_file = "no output file";
    dp->options = WARNINGS;
    dp->fp = ((void *)0);
    dp->read_pp = ((void *)0);
    dp->ip = ((void *)0);
    dp->write_pp = ((void *)0);
    dp->min_windowBits = -1;
    dp->text_ptr = ((void *)0);
    dp->num_text = 0;
    dp->text_stashed = 0;
}
static void display_clean_read (struct display *dp, int freeinfo){
    ;
    if (dp->fp != ((void *)0)) {
        FILE *fp;
        dp->fp = ((void *)0);
    }
}
static void display_clean_write (struct display *dp, int freeinfo){
    if (dp->fp != ((void *)0)) {
        FILE *fp;
        dp->fp = ((void *)0);
    }
    ;
}
static void display_clean (struct display *dp){
    display_clean_read(dp, 1);
    display_clean_write(dp, 1);
    dp->output_file = ((void *)0);
    if (dp->text_stashed) {
        dp->text_stashed = 0;
        dp->num_text = 0;
        dp->text_ptr = ((void *)0);
    }
    dp->results = 0;
}
static void display_destroy (struct display *dp){
    display_clean(dp);
}
static  __attribute__((format(printf, 3, 4))) void display_log (struct display *dp, error_level level, const char *fmt, ...){
    dp->results |= 1U << level;
    if (level > APP_FAIL || (level > ERRORS && !(dp->options & 64))) {
        ;
    }
}
static void text_stash (struct display *dp){
    png_textp chunks = ((void *)0);
    dp->num_text = png_get_text(dp->write_pp, dp->ip, &chunks, ((void *)0));
    if (dp->num_text > 0) {
        dp->text_ptr = (malloc(dp->num_text * sizeof *chunks));
        if (dp->text_ptr == ((void *)0)) {
            display_log(dp, APP_ERROR, "text chunks: stash malloc failed");
        } else
            memcpy(dp->text_ptr, chunks, dp->num_text * sizeof *chunks);
    }
    dp->text_stashed = 1;
}
static png_byte option_index (struct display *dp, const char *opt, size_t len){
    png_byte j;
    for (j = 0; j < ((sizeof options) / (sizeof options[0])); ++j)
        if (strncmp(options[j].name, opt, len) == 0 && options[j].name[len] == 0)
            return j;
    display_log(dp, dp->errset ? INTERNAL_ERROR : USER_ERROR, "%.*s: unknown option", (int)len, opt);
    abort();
}
static int get_option (struct display *dp, const char *opt, int *value){
    png_byte i = option_index(dp, opt, strlen(opt));
    if (dp->entry[i]) {
        *value = dp->value[i];
        return 1;
    } else
        return 0;
}
static int set_opt_string_ (struct display *dp, unsigned int sp, png_byte opt, const char *entry_name){
    int offset, add;
    if (sp > 0) {
        offset = dp->stack[sp - 1].opt_string_end;
    } else
        offset = dp->opt_string_start;
    if (entry_name == range_lo) {
        add = sprintf(dp->curr + offset, " --%s=%d", options[opt].name, dp->value[opt]);
    } else
        add = sprintf(dp->curr + offset, " --%s=%s", options[opt].name, entry_name);
    if (add < 0)
        display_log(dp, INTERNAL_ERROR, "sprintf failed");
    ((void)sizeof ((offset + add < (int)sizeof dp->curr) ? 1 : 0) , __extension__ ({
        if (offset + add < (int)sizeof dp->curr)
            ;
        else
            __assert_fail("offset+add < (int) sizeof dp->curr", "contrib/tools/pngcp_InstSlice.c", 704, __extension__ __PRETTY_FUNCTION__);
    }));
    return offset + add;
}
static void set_opt_string (struct display *dp, unsigned int sp){
    dp->stack[sp].opt_string_end = set_opt_string_(dp, sp, dp->stack[sp].opt, options[dp->stack[sp].opt].values[dp->stack[sp].entry].name);
}
static void record_opt (struct display *dp, png_byte opt, const char *entry_name){
    unsigned int sp = dp->csp;
    if (sp >= dp->tsp) {
        int offset = set_opt_string_(dp, sp, opt, entry_name);
        if (sp > 0) {
            dp->stack[sp - 1].opt_string_end = offset;
        } else
            dp->opt_string_start = offset;
    }
}
static int opt_list_end (struct display *dp, png_byte opt, png_byte entry){
    if (options[opt].values[entry].name == range_lo) {
        return entry + 1U >= options[opt].value_count || options[opt].values[entry + 1U].name != range_hi || options[opt].values[entry + 1U].value <= dp->value[opt];
    } else
        return entry + 1U >= options[opt].value_count || options[opt].values[entry + 1U].name == all;
}
static void push_opt (struct display *dp, unsigned int sp, png_byte opt, int search){
    png_byte entry;
    const char *entry_name;
    ((void)sizeof ((sp == dp->tsp && sp < 8) ? 1 : 0) , __extension__ ({
        if (sp == dp->tsp && sp < 8)
            ;
        else
            __assert_fail("sp == dp->tsp && sp < SL", "contrib/tools/pngcp_InstSlice.c", 762, __extension__ __PRETTY_FUNCTION__);
    }));
    entry = options[opt].value_count;
    ((void)sizeof ((entry > 0U) ? 1 : 0) , __extension__ ({
        if (entry > 0U)
            ;
        else
            __assert_fail("entry > 0U", "contrib/tools/pngcp_InstSlice.c", 768, __extension__ __PRETTY_FUNCTION__);
    }));
    do {
        entry_name = options[opt].values[--entry].name;
        if (entry_name == range_lo)
            break;
    } while (entry > 0U);
    dp->tsp = sp + 1U;
    dp->stack[sp].best_size = dp->stack[sp].lo_size = dp->stack[sp].hi_size = ((png_alloc_size_t)(-1));
    if (search && entry_name == range_lo) {
        dp->stack[sp].lo = options[opt].values[entry].value;
        ((void)sizeof ((entry + 1 < options[opt].value_count && options[opt].values[entry + 1].name == range_hi) ? 1 : 0) , __extension__ ({
            if (entry + 1 < options[opt].value_count && options[opt].values[entry + 1].name == range_hi)
                ;
            else
                __assert_fail("entry+1 < options[opt].value_count && options[opt].values[entry+1].name == range_hi", "contrib/tools/pngcp_InstSlice.c", 788, __extension__ __PRETTY_FUNCTION__);
        }));
        dp->stack[sp].hi = options[opt].values[entry + 1].value;
    } else {
        dp->stack[sp].lo = 2147483647;
        dp->stack[sp].hi = (-2147483647 - 1);
    }
    dp->stack[sp].opt = opt;
    dp->stack[sp].entry = entry;
    dp->stack[sp].best_val = dp->value[opt] = options[opt].values[entry].value;
    set_opt_string(dp, sp);
    if (opt_list_end(dp, opt, entry)) {
        dp->stack[sp].end = 1;
        if (opt != dp->min_windowBits)
            display_log(dp, APP_WARNING, "%s: only testing one value", options[opt].name);
    } else {
        dp->stack[sp].end = 0;
        dp->nsp = dp->tsp;
    }
    if (!dp->text_stashed)
        text_stash(dp);
}
static void next_opt (struct display *dp, unsigned int sp){
    int search = 0;
    png_byte entry, opt;
    const char *entry_name;
    ((void)sizeof ((sp + 1U == dp->tsp && !dp->stack[sp].end) ? 1 : 0) , __extension__ ({
        if (sp + 1U == dp->tsp && !dp->stack[sp].end)
            ;
        else
            __assert_fail("sp+1U == dp->tsp && !dp->stack[sp].end", "contrib/tools/pngcp_InstSlice.c", 845, __extension__ __PRETTY_FUNCTION__);
    }));
    opt = dp->stack[sp].opt;
    entry = dp->stack[sp].entry;
    ((void)sizeof ((entry + 1U < options[opt].value_count) ? 1 : 0) , __extension__ ({
        if (entry + 1U < options[opt].value_count)
            ;
        else
            __assert_fail("entry+1U < options[opt].value_count", "contrib/tools/pngcp_InstSlice.c", 849, __extension__ __PRETTY_FUNCTION__);
    }));
    entry_name = options[opt].values[entry].name;
    ((void)sizeof ((entry_name != ((void *)0)) ? 1 : 0) , __extension__ ({
        if (entry_name != ((void *)0))
            ;
        else
            __assert_fail("entry_name != NULL", "contrib/tools/pngcp_InstSlice.c", 851, __extension__ __PRETTY_FUNCTION__);
    }));
    if (entry_name == range_lo) {
        if (dp->stack[sp].lo > dp->stack[sp].hi) {
            dp->value[opt]++;
        } else {
            png_alloc_size_t best_size = dp->stack[sp].best_size;
            int lo = dp->stack[sp].lo;
            int hi = dp->stack[sp].hi;
            int val = dp->value[opt];
            search = 1;
            ((void)sizeof ((best_size < ((png_alloc_size_t)(-1))) ? 1 : 0) , __extension__ ({
                if (best_size < ((png_alloc_size_t)(-1)))
                    ;
                else
                    __assert_fail("best_size < MAX_SIZE", "contrib/tools/pngcp_InstSlice.c", 874, __extension__ __PRETTY_FUNCTION__);
            }));
            if (val == lo) {
                dp->stack[sp].lo_size = best_size;
                ((void)sizeof ((hi > val) ? 1 : 0) , __extension__ ({
                    if (hi > val)
                        ;
                    else
                        __assert_fail("hi > val", "contrib/tools/pngcp_InstSlice.c", 880, __extension__ __PRETTY_FUNCTION__);
                }));
                if (hi == val + 1)
                    dp->stack[sp].end = 1;
                val = hi;
            } else if (val == hi) {
                dp->stack[sp].hi_size = best_size;
                ((void)sizeof ((val > lo + 1) ? 1 : 0) , __extension__ ({
                    if (val > lo + 1)
                        ;
                    else
                        __assert_fail("val > lo+1", "contrib/tools/pngcp_InstSlice.c", 891, __extension__ __PRETTY_FUNCTION__);
                }));
                if (val == lo + 2)
                    dp->stack[sp].end = 1;
                val = (lo + val) / 2;
            } else {
                png_alloc_size_t lo_size = dp->stack[sp].lo_size;
                png_alloc_size_t hi_size = dp->stack[sp].hi_size;
                ((void)sizeof ((lo_size < ((png_alloc_size_t)(-1)) && hi_size < ((png_alloc_size_t)(-1))) ? 1 : 0) , __extension__ ({
                    if (lo_size < ((png_alloc_size_t)(-1)) && hi_size < ((png_alloc_size_t)(-1)))
                        ;
                    else
                        __assert_fail("lo_size < MAX_SIZE && hi_size < MAX_SIZE", "contrib/tools/pngcp_InstSlice.c", 905, __extension__ __PRETTY_FUNCTION__);
                }));
                if (val < lo) {
                    dp->stack[sp].lo = val;
                    dp->stack[sp].lo_size = best_size;
                    val = lo;
                    best_size = lo_size;
                    lo = dp->stack[sp].lo;
                    lo_size = dp->stack[sp].lo_size;
                } else if (val > hi) {
                    dp->stack[sp].hi = val;
                    dp->stack[sp].hi_size = best_size;
                    val = hi;
                    best_size = hi_size;
                    hi = dp->stack[sp].hi;
                    hi_size = dp->stack[sp].hi_size;
                }
                ((void)sizeof ((lo < val && val < hi) ? 1 : 0) , __extension__ ({
                    if (lo < val && val < hi)
                        ;
                    else
                        __assert_fail("lo < val && val < hi", "contrib/tools/pngcp_InstSlice.c", 933, __extension__ __PRETTY_FUNCTION__);
                }));
                if (hi == lo + 3) {
                    val = lo + ((val == lo + 1) ? 2 : 1);
                    ((void)sizeof ((lo < val && val < hi) ? 1 : 0) , __extension__ ({
                        if (lo < val && val < hi)
                            ;
                        else
                            __assert_fail("lo < val && val < hi", "contrib/tools/pngcp_InstSlice.c", 944, __extension__ __PRETTY_FUNCTION__);
                    }));
                    dp->stack[sp].end = 1;
                } else {
                    ((void)sizeof ((hi > lo + 3) ? 1 : 0) , __extension__ ({
                        if (hi > lo + 3)
                            ;
                        else
                            __assert_fail("hi > lo+3", "contrib/tools/pngcp_InstSlice.c", 956, __extension__ __PRETTY_FUNCTION__);
                    }));
                    if (lo_size <= best_size && best_size <= hi_size) {
                        if (val == lo + 1) {
                            ++val;
                            dp->stack[sp].end = 1;
                        } else {
                            dp->stack[sp].hi = hi = val;
                            dp->stack[sp].hi_size = best_size;
                            val = (lo + val) / 2;
                        }
                    } else if (lo_size >= best_size && best_size >= hi_size) {
                        if (val == hi - 1) {
                            --val;
                            dp->stack[sp].end = 1;
                        } else {
                            dp->stack[sp].lo = lo = val;
                            dp->stack[sp].lo_size = best_size;
                            val = (val + hi) / 2;
                        }
                    } else if (lo_size <= hi_size) {
                        dp->stack[sp].hi = val;
                        dp->stack[sp].hi_size = best_size;
                        val = --hi;
                    } else {
                        dp->stack[sp].lo = val;
                        dp->stack[sp].lo_size = best_size;
                        val = ++lo;
                    }
                    ((void)sizeof ((hi > lo + 1) ? 1 : 0) , __extension__ ({
                        if (hi > lo + 1)
                            ;
                        else
                            __assert_fail("hi > lo+1", "contrib/tools/pngcp_InstSlice.c", 1031, __extension__ __PRETTY_FUNCTION__);
                    }));
                    if (hi <= lo + 2)
                        dp->stack[sp].end = 1;
                }
            }
            ((void)sizeof ((val != dp->stack[sp].best_val) ? 1 : 0) , __extension__ ({
                if (val != dp->stack[sp].best_val)
                    ;
                else
                    __assert_fail("val != dp->stack[sp].best_val", "contrib/tools/pngcp_InstSlice.c", 1037, __extension__ __PRETTY_FUNCTION__);
            }));
            dp->value[opt] = val;
            dp->stack[sp].best_size = ((png_alloc_size_t)(-1));
        }
    } else {
        dp->value[opt] = options[opt].values[++entry].value;
        dp->stack[sp].entry = entry;
    }
    set_opt_string(dp, sp);
    if (!search && opt_list_end(dp, opt, entry)) {
        dp->stack[sp].end = 1;
    } else if (!dp->stack[sp].end)
        dp->nsp = dp->tsp;
}
static int compare_option (const struct display *dp, unsigned int sp){
    int opt = dp->stack[sp].opt;
    if (dp->stack[sp].best_val < dp->value[opt]) {
        return -1;
    } else if (dp->stack[sp].best_val > dp->value[opt]) {
        if (dp->stack[sp].lo <= dp->stack[sp].hi) {
            return 1;
        } else
            return -1;
    } else
        return 0;
}
static int advance_opt (struct display *dp, png_byte opt, int search){
    unsigned int sp = dp->csp++;
    ((void)sizeof ((sp >= dp->nsp) ? 1 : 0) , __extension__ ({
        if (sp >= dp->nsp)
            ;
        else
            __assert_fail("sp >= dp->nsp", "contrib/tools/pngcp_InstSlice.c", 1091, __extension__ __PRETTY_FUNCTION__);
    }));
    if (sp >= dp->tsp) {
        push_opt(dp, sp, opt, search);
        return 1;
    } else {
        int ret;
        ((void)sizeof ((dp->write_size > 0U && dp->write_size < ((png_alloc_size_t)(-1))) ? 1 : 0) , __extension__ ({
            if (dp->write_size > 0U && dp->write_size < ((png_alloc_size_t)(-1)))
                ;
            else
                __assert_fail("dp->write_size > 0U && dp->write_size < MAX_SIZE", "contrib/tools/pngcp_InstSlice.c", 1127, __extension__ __PRETTY_FUNCTION__);
        }));
        if (dp->stack[sp].best_size > dp->write_size || (dp->stack[sp].best_size == dp->write_size && compare_option(dp, sp) > 0)) {
            dp->stack[sp].best_size = dp->write_size;
            dp->stack[sp].best_val = dp->value[opt];
        }
        if (sp + 1U >= dp->tsp) {
            next_opt(dp, sp);
        } else if (!dp->stack[sp].end)
            dp->nsp = sp + 1U;
        return ret;
    }
}
static int getallopts_ (struct display *dp, png_byte opt, int *value, int record){
    if (dp->entry[opt]) {
        const char *entry_name = options[opt].values[dp->entry[opt] - 1].name;
        if (entry_name == all) {
            (void)advance_opt(dp, opt, 0);
        } else if (record)
            record_opt(dp, opt, entry_name);
        *value = dp->value[opt];
        return 1;
    } else
        return 0;
}
static int getallopts (struct display *dp, const char *opt_str, int *value){
    return getallopts_(dp, option_index(dp, opt_str, strlen(opt_str)), value, 0);
}
static int getsearchopts (struct display *dp, const char *opt_str, int *value){
    png_byte istrat;
    png_byte opt = option_index(dp, opt_str, strlen(opt_str));
    int record = options[opt].search;
    const char *entry_name;
    if (getallopts_(dp, opt, value, record)) {
        return 1;
    } else if (!record)
        return 0;
    istrat = option_index(dp, "strategy", (sizeof "strategy") - 1);
    entry_name = range_lo;
    if (opt == istrat)
        (void)advance_opt(dp, opt, 0) , record = 0;
    else if (opt == option_index(dp, "level", (sizeof "level") - 1)) {
        if (dp->value[istrat] == 3 || dp->value[istrat] == 2)
            dp->value[opt] = 1;
        else
            (void)advance_opt(dp, opt, 1) , record = 0;
    } else if (opt == option_index(dp, "windowBits", (sizeof "windowBits") - 1)) {
        if (dp->value[istrat] == 2)
            dp->value[opt] = 8;
        else if (dp->value[istrat] == 3)
            dp->value[opt] = 9;
        else
            (void)advance_opt(dp, opt, 1) , record = 0;
    } else if (opt == option_index(dp, "memLevel", (sizeof "memLevel") - 1)) {
        dp->value[opt] = 9;
    } else
        ((void)sizeof ((0 == "reached") ? 1 : 0) , __extension__ ({
            if (0 == "reached")
                ;
            else
                __assert_fail("0==\"reached\"", "contrib/tools/pngcp_InstSlice.c", 1243, __extension__ __PRETTY_FUNCTION__);
        }));
    if (record)
        record_opt(dp, opt, entry_name);
    *value = dp->value[opt];
    return 1;
}
static int find_val (struct display *dp, png_byte opt, const char *str, size_t len){
    int rlo = 2147483647, rhi = (-2147483647 - 1);
    png_byte j, irange = 0;
    for (j = 1U; j <= options[opt].value_count; ++j) {
        if (strncmp(options[opt].values[j - 1U].name, str, len) == 0 && options[opt].values[j - 1U].name[len] == 0) {
            dp->entry[opt] = j;
            return options[opt].values[j - 1U].value;
        } else if (options[opt].values[j - 1U].name == range_lo) {
            rlo = options[opt].values[j - 1U].value , irange = j;
        } else if (options[opt].values[j - 1U].name == range_hi)
            rhi = options[opt].values[j - 1U].value;
    }
    if (irange > 0) {
        char *ep = ((void *)0);
        long l = strtol(str, &ep, 0);
        if (ep == str + len && l >= rlo && l <= rhi) {
            dp->entry[opt] = irange;
            return (int)l;
        }
    }
    display_log(dp, dp->errset ? INTERNAL_ERROR : USER_ERROR, "%s: unknown value setting '%.*s'", options[opt].name, (int)len, str);
    abort();
}
static int opt_check (struct display *dp, const char *arg){
    ((void)sizeof ((dp->errset == 0) ? 1 : 0) , __extension__ ({
        if (dp->errset == 0)
            ;
        else
            __assert_fail("dp->errset == 0", "contrib/tools/pngcp_InstSlice.c", 1296, __extension__ __PRETTY_FUNCTION__);
    }));
    if (arg != ((void *)0) && arg[0] == '-' && arg[1] == '-') {
        int i = 0, negate = (strncmp(arg + 2, "no-", 3) == 0), val;
        png_byte j;
        if (negate) {
            arg += 5;
        } else
            arg += 2;
        while (arg[i] != 0 && arg[i] != '=')
            ++i;
        j = option_index(dp, arg, i);
        if (arg[i] == 0) {
            val = options[j].values[negate].value;
            dp->entry[j] = (png_byte)(negate + 1U);
        } else {
            const char *list = arg + (i + 1);
            if (options[j].opt != 2147483649U) {
                val = find_val(dp, j, list, strlen(list));
                if (negate) {
                    if (options[j].opt < 2147483648U) {
                        val = !val;
                    } else {
                        display_log(dp, USER_ERROR, "%.*s: option=arg cannot be negated", i, arg);
                        abort();
                    }
                }
            } else {
                if (negate) {
                    val = options[j].values[0].value;
                } else
                    val = 0;
                while (*list != 0)
                    {
                        int v, iv;
                        iv = 0;
                        while (list[++iv] != 0 && list[iv] != ',')
                            {
                            }
                        v = find_val(dp, j, list, iv);
                        if (negate) {
                            val &= ~v;
                        } else
                            val |= v;
                        list += iv;
                        if (*list != 0)
                            ++list;
                    }
            }
        }
        dp->value[j] = val;
        if (options[j].opt < 15) {
            if (val) {
                dp->options = (dp->options & ~15) | options[j].opt;
            } else
                display_log(dp, USER_ERROR, "%.*s: messages cannot be turned off individually; set a message level", i, arg);
        } else if (options[j].opt < 2147483648U) {
            if (val) {
                dp->options |= options[j].opt;
            } else
                dp->options &= ~options[j].opt;
        }
        return 1;
    } else
        return 0;
}
static int checkdir (const char *pathname){
    struct stat buf;
    return stat(pathname, &buf) == 0 && ((((buf.st_mode)) & 61440) == (16384));
}
static int isdir (struct display *dp, const char *pathname){
    if (pathname == ((void *)0)) {
        return 0;
    } else if (pathname[0] == 0) {
        return 1;
    } else {
        struct stat buf;
        int ret = stat(pathname, &buf);
        if (ret == 0) {
            if (((((buf.st_mode)) & 61440) == (16384)))
                return 1;
            if (access(pathname, 2) != 0)
                display_log(dp, USER_ERROR, "%s: cannot be written (%s)", pathname, strerror((*__errno_location())));
            return 0;
        } else {
            if ((*__errno_location()) != 2)
                display_log(dp, USER_ERROR, "%s: invalid output name (%s)", pathname, strerror((*__errno_location())));
            return 0;
        }
    }
}
static void makename (struct display *dp, const char *dir, const char *infile){
    dp->namebuf[0] = 0;
    if (dir == ((void *)0) || infile == ((void *)0)) {
        display_log(dp, INTERNAL_ERROR, "NULL name to makename");
    } else {
        size_t dsize = strlen(dir);
        if (dsize <= (sizeof dp->namebuf) - 2) {
            size_t isize = strlen(infile);
            size_t istart = isize - 1;
            if (infile[istart] == '/')
                display_log(dp, INTERNAL_ERROR, "infile with trailing /");
            memcpy(dp->namebuf, dir, dsize);
            if (dsize > 0 && dp->namebuf[dsize - 1] != '/')
                dp->namebuf[dsize++] = '/';
            while (istart > 0 && infile[istart - 1] != '/')
                --istart;
            isize -= istart;
            infile += istart;
            if (dsize + isize < (sizeof dp->namebuf)) {
                memcpy(dp->namebuf + dsize, infile, isize + 1);
                if (isdir(dp, dp->namebuf))
                    display_log(dp, USER_ERROR, "%s: output file is a directory", dp->namebuf);
            } else {
                dp->namebuf[dsize] = 0;
                display_log(dp, USER_ERROR, "%s%s: output file name too long", dp->namebuf, infile);
            }
        } else
            display_log(dp, USER_ERROR, "%s: output directory name too long", dir);
    }
}
static void display_start_read (struct display *dp, const char *filename){
    if (filename != ((void *)0)) {
        dp->filename = filename;
        dp->fp = fopen(filename, "rb");
    } else {
        dp->filename = "<stdin>";
        dp->fp = stdin;
    }
    dp->w = dp->h = 0U;
    dp->bpp = 0U;
    dp->size = 0U;
    dp->read_size = 0U;
    if (dp->fp == ((void *)0))
        display_log(dp, USER_ERROR, "file open failed (%s)", strerror((*__errno_location())));
}
static void read_png (struct display *dp, const char *filename){
    if (dp->read_pp != ((void *)0)) {
        display_log(dp, APP_FAIL, "unexpected png_read_struct");
        display_clean_read(dp, 1);
    }
    display_start_read(dp, filename);
    dp->read_pp = png_create_read_struct("1.6.45.git", dp, display_error, display_warning);
    if (dp->read_pp == ((void *)0))
        display_log(dp, LIBPNG_ERROR, "failed to create read struct");
    if (dp->ip != ((void *)0)) {
        display_log(dp, APP_FAIL, "read_png: freeing old info struct");
    }
    dp->ip = png_create_info_struct(dp->read_pp);
    if (dp->ip == ((void *)0)) {
    }
    ;
    dp->w = png_get_image_width(dp->read_pp, dp->ip);
    dp->h = png_get_image_height(dp->read_pp, dp->ip);
    dp->ct = png_get_color_type(dp->read_pp, dp->ip);
    dp->bpp = png_get_bit_depth(dp->read_pp, dp->ip) * png_get_channels(dp->read_pp, dp->ip);
    {
        png_alloc_size_t rb = png_get_rowbytes(dp->read_pp, dp->ip);
        if (rb == 0)
            png_error(dp->read_pp, "invalid row byte count from libpng");
        if ((((png_alloc_size_t)(-1)) - dp->h) / rb < dp->h)
            png_error(dp->read_pp, "image too large");
        dp->size = rb * dp->h + dp->h;
    }
    if (dp->ct == (2 | 1) && (dp->options & 2048) != 0) {
        int max = png_get_palette_max(dp->read_pp, dp->ip);
        png_colorp palette = ((void *)0);
        int num = -1;
        if (png_get_PLTE(dp->read_pp, dp->ip, &palette, &num) != 8U || max < 0 || num <= 0 || palette == ((void *)0))
            display_log(dp, LIBPNG_ERROR, "invalid png_get_PLTE result");
        if (max >= num) {
            int i;
            png_color newpal[256];
            for (i = 0; i < num; ++i)
                newpal[i] = palette[i];
        }
    }
    display_clean_read(dp, 0);
}
static void display_start_write (struct display *dp, const char *filename){
    ((void)sizeof ((dp->fp == ((void *)0)) ? 1 : 0) , __extension__ ({
        if (dp->fp == ((void *)0))
            ;
        else
            __assert_fail("dp->fp == NULL", "contrib/tools/pngcp_InstSlice.c", 1749, __extension__ __PRETTY_FUNCTION__);
    }));
    if ((dp->options & 512) != 0) {
        dp->output_file = "<no write>";
    } else {
        if (filename != ((void *)0)) {
            dp->output_file = filename;
            dp->fp = fopen(filename, "wb");
        } else {
            dp->output_file = "<stdout>";
            dp->fp = stdout;
        }
        if (dp->fp == ((void *)0))
            display_log(dp, USER_ERROR, "%s: file open failed (%s)", dp->output_file, strerror((*__errno_location())));
    }
}
static void search_compression (struct display *dp){
    int val;
    if (getsearchopts(dp, "strategy", &val))
        png_set_compression_strategy(dp->write_pp, val);
    if (getsearchopts(dp, "windowBits", &val))
        png_set_compression_window_bits(dp->write_pp, val);
    if (getsearchopts(dp, "level", &val))
        png_set_compression_level(dp->write_pp, val);
    if (getsearchopts(dp, "memLevel", &val))
        png_set_compression_mem_level(dp->write_pp, val);
}
static void set_compression (struct display *dp){
    int val;
    if (getallopts(dp, "strategy", &val))
        png_set_compression_strategy(dp->write_pp, val);
    if (getallopts(dp, "windowBits", &val))
        png_set_compression_window_bits(dp->write_pp, val);
    if (getallopts(dp, "level", &val))
        png_set_compression_level(dp->write_pp, val);
    if (getallopts(dp, "memLevel", &val))
        png_set_compression_mem_level(dp->write_pp, val);
}
static void set_text_compression (struct display *dp){
    int val;
    if (getallopts(dp, "text-strategy", &val))
        png_set_text_compression_strategy(dp->write_pp, val);
    if (getallopts(dp, "text-windowBits", &val))
        png_set_text_compression_window_bits(dp->write_pp, val);
    if (getallopts(dp, "text-level", &val))
        png_set_text_compression_level(dp->write_pp, val);
    if (getallopts(dp, "text-memLevel", &val))
        png_set_text_compression_mem_level(dp->write_pp, val);
}
static void write_png (struct display *dp, const char *destname){
    if (dp->ip == ((void *)0))
        display_log(dp, INTERNAL_ERROR, "missing png_info");
    if (dp->write_pp != ((void *)0)) {
        display_log(dp, APP_FAIL, "unexpected png_write_struct");
        display_clean_write(dp, 0);
    }
    display_start_write(dp, destname);
    dp->write_pp = png_create_write_struct("1.6.45.git", dp, display_error, display_warning);
    if (dp->write_pp == ((void *)0))
        display_log(dp, LIBPNG_ERROR, "failed to create write png_struct");
    dp->tsp = dp->nsp;
    dp->nsp = dp->csp = 0;
    if (dp->options & 256) {
        search_compression(dp);
    } else
        set_compression(dp);
    set_text_compression(dp);
    {
        int val;
        if (get_option(dp, "IDAT-size", &val))
            png_set_compression_buffer_size(dp->write_pp, val);
    }
    {
        int val;
        if (get_option(dp, "filter", &val))
            png_set_filter(dp->write_pp, 0, val);
    }
    dp->write_size = 0U;
    if (dp->fp != ((void *)0)) {
        FILE *fp = dp->fp;
        dp->fp = ((void *)0);
        if (fclose(fp))
            display_log(dp, APP_ERROR, "%s: write failed (%s)", destname == ((void *)0) ? "stdout" : destname, strerror((*__errno_location())));
    }
    dp->operation = "none";
}
static void set_windowBits_hi (struct display *dp){
    int wb = 15;
    int i = ((sizeof vl_windowBits_IDAT) / (sizeof vl_windowBits_IDAT[0]));
    while (wb > 8 && dp->size <= 1U << (wb - 1))
        --wb;
    while (--i >= 0)
        if (vl_windowBits_IDAT[i].name == range_hi)
            break;
    ((void)sizeof ((i > 1) ? 1 : 0) , __extension__ ({
        if (i > 1)
            ;
        else
            __assert_fail("i > 1", "contrib/tools/pngcp_InstSlice.c", 1976, __extension__ __PRETTY_FUNCTION__);
    }));
    vl_windowBits_IDAT[i].value = wb;
    ((void)sizeof ((vl_windowBits_IDAT[--i].name == range_lo) ? 1 : 0) , __extension__ ({
        if (vl_windowBits_IDAT[--i].name == range_lo)
            ;
        else
            __assert_fail("VLNAME(windowBits_IDAT)[--i].name == range_lo", "contrib/tools/pngcp_InstSlice.c", 1979, __extension__ __PRETTY_FUNCTION__);
    }));
    vl_windowBits_IDAT[i].value = wb > 8 ? 9 : 8;
    if (wb == 8)
        dp->min_windowBits = option_index(dp, "windowBits", (sizeof "windowBits") - 1);
}
static int better_options (const struct display *dp){
    unsigned int sp;
    for (sp = 0; sp < dp->csp; ++sp) {
        int c = compare_option(dp, sp);
        if (c < 0) {
            return 0;
        } else if (c > 0)
            return 1;
    }
    ;
}
static void print_search_results (struct display *dp){
    ((void)sizeof ((dp->filename != ((void *)0)) ? 1 : 0) , __extension__ ({
        if (dp->filename != ((void *)0))
            ;
        else
            __assert_fail("dp->filename != NULL", "contrib/tools/pngcp_InstSlice.c", 2026, __extension__ __PRETTY_FUNCTION__);
    }));
}
static void log_search (struct display *dp, unsigned int log_depth){
    if (dp->nsp <= log_depth) {
        print_search_results(dp);
        dp->best_size = ((png_alloc_size_t)(-1));
    }
}
static void cp_one_file (struct display *dp, const char *filename, const char *destname){
    unsigned int log_depth;
    dp->filename = filename;
    dp->operation = "read";
    dp->no_warnings = 0;
    if (filename != ((void *)0) && access(filename, 4) != 0)
        display_log(dp, USER_ERROR, "%s: invalid file name (%s)", filename, strerror((*__errno_location())));
    read_png(dp, filename);
    dp->operation = "write";
    set_windowBits_hi(dp);
    {
        int val;
        if (get_option(dp, "log-depth", &val) && val >= 0)
            log_depth = (unsigned int)val;
        else
            log_depth = 0U;
    }
    if (destname != ((void *)0)) {
        if (isdir(dp, destname)) {
            makename(dp, destname, filename);
            destname = dp->namebuf;
        } else if (access(destname, 2) != 0 && (*__errno_location()) != 2)
            display_log(dp, USER_ERROR, "%s: invalid output name (%s)", destname, strerror((*__errno_location())));
    }
    dp->nsp = 0;
    dp->curr[0] = 0;
    dp->opt_string_start = 0;
    dp->best[0] = 0;
    dp->best_size = ((png_alloc_size_t)(-1));
    write_png(dp, destname);
    strcpy(dp->best, dp->curr);
    dp->best_size = dp->write_size;
    if (dp->nsp > 0) {
        char *tmpname, tmpbuf[4100];
        ((void)sizeof ((dp->curr[0] == ' ' && dp->tsp > 0) ? 1 : 0) , __extension__ ({
            if (dp->curr[0] == ' ' && dp->tsp > 0)
                ;
            else
                __assert_fail("dp->curr[0] == ' ' && dp->tsp > 0", "contrib/tools/pngcp_InstSlice.c", 2100, __extension__ __PRETTY_FUNCTION__);
        }));
        log_search(dp, log_depth);
        dp->no_warnings = 1;
        if (destname != ((void *)0)) {
            strcpy(tmpbuf, destname);
            strcat(tmpbuf, ".tmp");
            tmpname = tmpbuf;
        } else
            tmpname = ((void *)0);
        do {
            display_clean_write(dp, 0);
            write_png(dp, tmpname);
            ((void)sizeof ((dp->csp > 0) ? 1 : 0) , __extension__ ({
                if (dp->csp > 0)
                    ;
                else
                    __assert_fail("dp->csp > 0", "contrib/tools/pngcp_InstSlice.c", 2129, __extension__ __PRETTY_FUNCTION__);
            }));
            if (dp->write_size < dp->best_size || (dp->write_size == dp->best_size && better_options(dp))) {
                if (destname != ((void *)0) && rename(tmpname, destname) != 0)
                    display_log(dp, APP_ERROR, "rename %s %s failed (%s)", tmpname, destname, strerror((*__errno_location())));
                strcpy(dp->best, dp->curr);
                dp->best_size = dp->write_size;
            } else if (tmpname != ((void *)0) && unlink(tmpname) != 0)
                display_log(dp, APP_WARNING, "unlink %s failed (%s)", tmpname, strerror((*__errno_location())));
            log_search(dp, log_depth);
        } while (dp->nsp > 0);
        dp->write_size = dp->best_size;
    }
    display_clean_write(dp, 1);
}
static int cppng (struct display *dp, const char *file, const char *dest){
    if (_setjmp(dp->error_return) == 0) {
        dp->errset = 1;
        cp_one_file(dp, file, dest);
        dp->errset = 0;
        return 0;
    } else {
        dp->errset = 0;
        if (dp->errlevel < ERRORS)
            display_log(dp, INTERNAL_ERROR, "unexpected return code %d", dp->errlevel);
        return dp->errlevel;
    }
}
extern int main (int argc, char **argv){
    int option_end;
    struct display d;
    display_init(&d);
    d.operation = "options";
    for (option_end = 1; option_end < argc && opt_check(&d, argv[option_end]); ++option_end) {
    }
    if (!(d.options & 512) && option_end + 2 < argc && !checkdir(argv[argc - 1])) {
        ;
        return 99;
    }
    {
        int errors = 0;
        int i = option_end;
        d.operation = "files";
        do {
            const char *infile = ((void *)0);
            const char *outfile = ((void *)0);
            int ret;
            if (i < argc) {
                infile = argv[i++];
                if (!(d.options & 512) && i < argc)
                    outfile = argv[argc - 1];
            }
            ret = cppng(&d, infile, outfile);
            if (ret) {
                if (ret > QUIET)
                    return 99;
            } else if (d.best[0] != 0) {
                if (d.best_size < ((png_alloc_size_t)(-1)))
                    print_search_results(&d);
            } else if (d.options & 128) {
                printf("%s [%ld x %ld %d bpp %s, %lu bytes] %lu -> %lu [0x%lx]\n", infile, (unsigned long)d.w, (unsigned long)d.h, d.bpp, cts(d.ct), (unsigned long)d.size, (unsigned long)d.read_size, (unsigned long)d.write_size, (unsigned long)d.results);
                fflush(stdout);
            }
            {
                int pass = (d.options & 16) ? (((d.results) & ~((1U << WARNINGS) - 1)) == 0) : (((d.results) & ~((1U << ERRORS) - 1)) == 0);
                if (!pass)
                    ++errors;
                if (d.options & 32) {
                    int j;
                    printf("%s: pngcp", pass ? "PASS" : "FAIL");
                    for (j = 1; j < option_end; ++j)
                        printf(" %s", argv[j]);
                    if (infile != ((void *)0))
                        printf(" %s", infile);
                    printf("\n");
                    fflush(stdout);
                }
            }
            display_clean(&d);
        } while (i + !(d.options & 512) < argc);
        display_destroy(&d);
        return errors != 0;
    }
}
