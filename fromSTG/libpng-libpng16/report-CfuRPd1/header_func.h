#ifndef __HEADER_FUNC_H__ 
#define __HEADER_FUNC_H__
#include"header_type.h" 
static void display_clean_read(struct display *dp, int freeinfo) ;

static void display_clean_write(struct display *dp, int freeinfo) ;

static void display_clean(struct display *dp) ;


extern int (png_get_text)(png_const_structrp png_ptr, png_inforp info_ptr, png_textp *text_ptr, int *num_text);

static void display_log(struct display *dp, error_level level, const char *fmt, ...) ;

static const value_list vl_on_off[] = {{"on", 1}, {"off", 0}};
static const char all[] = "all";
static const value_list vl_strategy[] = {{"huffman", 2}, {"RLE", 3}, {"fixed", 4}, {"filtered", 1}, {"default", 0}, {all, 0}};
static const char range_lo[] = "low";
static const char range_hi[] = "high";
static value_list vl_windowBits_IDAT[] = {{"default", 15}, {"small", 9}, {range_lo, 8}, {range_hi, 15}, {all, 0}};
static const value_list vl_windowBits_text[] = {{"default", 15}, {"minimum", 8}, {range_lo, 8}, {range_hi, 15}, {all, 0}};
static const value_list vl_level[] = {{"default", (-1)}, {"none", 0}, {"speed", 1}, {"best", 9}, {"0", 0}, {range_lo, 1}, {range_hi, 9}, {all, 0}};
static const value_list vl_memLevel[] = {{"max", 9}, {"1", 1}, {"default", 8}, {"2", 2}, {"3", 3}, {"4", 4}, {"5", 5}, {range_lo, 6}, {range_hi, 9}, {all, 0}};
static const value_list vl_IDAT_size[] = {{"default", 2147483647}, {"minimal", 1}, {range_lo, 1}, {range_hi, 2147483647}};
static const value_list vl_log_depth[] = {{"on", 1}, {"off", 0}, {range_lo, 0}, {range_hi, 8}};
static const value_list vl_filter[] = {{all, ((8 | 16 | 32) | 64 | 128)}, {"off", 0}, {"none", 8}, {"sub", 16}, {"up", 32}, {"avg", 64}, {"paeth", 128}};
static const option options[] = {{"verbose", VERBOSE, 0, 2, vl_on_off}, {"warnings", WARNINGS, 0, 2, vl_on_off}, {"errors", ERRORS, 0, 2, vl_on_off}, {"quiet", QUIET, 0, 2, vl_on_off}, {"strict", 16, 0, 2, vl_on_off}, {"log", 32, 0, 2, vl_on_off}, {"continue", 64, 0, 2, vl_on_off}, {"sizes", 128, 0, 2, vl_on_off}, {"search", 256, 0, 2, vl_on_off}, {"nowrite", 512, 0, 2, vl_on_off}, {"ignore-palette-index", 1024, 0, 2, vl_on_off}, {"fix-palette-index", 2048, 0, 2, vl_on_off}, {"strategy", 2147483648U, 1, ((sizeof vl_strategy) / (sizeof vl_strategy[0])), vl_strategy}, {"text-strategy", 2147483648U, 0, ((sizeof vl_strategy) / (sizeof vl_strategy[0])), vl_strategy}, {"windowBits", 2147483648U, 1, ((sizeof vl_windowBits_IDAT) / (sizeof vl_windowBits_IDAT[0])), vl_windowBits_IDAT}, {"text-windowBits", 2147483648U, 0, ((sizeof vl_windowBits_text) / (sizeof vl_windowBits_text[0])), vl_windowBits_text}, {"level", 2147483648U, 1, ((sizeof vl_level) / (sizeof vl_level[0])), vl_level}, {"text-level", 2147483648U, 0, ((sizeof vl_level) / (sizeof vl_level[0])), vl_level}, {"memLevel", 2147483648U, 1, ((sizeof vl_memLevel) / (sizeof vl_memLevel[0])), vl_memLevel}, {"text-memLevel", 2147483648U, 0, ((sizeof vl_memLevel) / (sizeof vl_memLevel[0])), vl_memLevel}, {"IDAT-size", 2147483648U, 0, ((sizeof vl_IDAT_size) / (sizeof vl_IDAT_size[0])), vl_IDAT_size}, {"log-depth", 2147483648U, 0, ((sizeof vl_log_depth) / (sizeof vl_log_depth[0])), vl_log_depth}, {"filter", 2147483649U, 0, ((sizeof vl_filter) / (sizeof vl_filter[0])), vl_filter}};
;
static png_byte option_index(struct display *dp, const char *opt, size_t len) ;

static int set_opt_string_(struct display *dp, unsigned int sp, png_byte opt, const char *entry_name) ;

static void set_opt_string(struct display *dp, unsigned int sp) ;

static int opt_list_end(struct display *dp, png_byte opt, png_byte entry) ;

static void text_stash(struct display *dp) ;

static void push_opt(struct display *dp, unsigned int sp, png_byte opt, int search) ;

static int compare_option(const struct display *dp, unsigned int sp) ;

static void next_opt(struct display *dp, unsigned int sp) ;

static int advance_opt(struct display *dp, png_byte opt, int search) ;

static void record_opt(struct display *dp, png_byte opt, const char *entry_name) ;

static int getallopts_(struct display *dp, png_byte opt, int *value, int record) ;

static int find_val(struct display *dp, png_byte opt, const char *str, size_t len) ;

static int isdir(struct display *dp, const char *pathname) ;

extern FILE *stdin;
;
static void display_start_read(struct display *dp, const char *filename) ;


extern png_structp (png_create_read_struct)(png_const_charp user_png_ver, png_voidp error_ptr, png_error_ptr error_fn, png_error_ptr warn_fn);

static void display_error(png_structp pp, png_const_charp error) ;

static void display_warning(png_structp pp, png_const_charp warning) ;


extern void (png_destroy_info_struct)(png_const_structrp png_ptr, png_infopp info_ptr_ptr);


extern png_infop (png_create_info_struct)(png_const_structrp png_ptr);


extern void (png_error)(png_const_structrp png_ptr, png_const_charp error_message);


extern png_uint_32 (png_get_image_width)(png_const_structrp png_ptr, png_const_inforp info_ptr);


extern png_uint_32 (png_get_image_height)(png_const_structrp png_ptr, png_const_inforp info_ptr);


extern png_byte (png_get_color_type)(png_const_structrp png_ptr, png_const_inforp info_ptr);


extern png_byte (png_get_bit_depth)(png_const_structrp png_ptr, png_const_inforp info_ptr);


extern png_byte (png_get_channels)(png_const_structrp png_ptr, png_const_inforp info_ptr);


extern size_t (png_get_rowbytes)(png_const_structrp png_ptr, png_const_inforp info_ptr);


extern png_uint_32 (png_get_PLTE)(png_const_structrp png_ptr, png_inforp info_ptr, png_colorp *palette, int *num_palette);


extern void (png_set_PLTE)(png_structrp png_ptr, png_inforp info_ptr, png_const_colorp palette, int num_palette);


extern int (png_get_palette_max)(png_const_structp png_ptr, png_const_infop info_ptr);

extern FILE *stdout;
;
static int getsearchopts(struct display *dp, const char *opt_str, int *value) ;


extern void (png_set_compression_strategy)(png_structrp png_ptr, int strategy);


extern void (png_set_compression_window_bits)(png_structrp png_ptr, int window_bits);


extern void (png_set_compression_level)(png_structrp png_ptr, int level);


extern void (png_set_compression_mem_level)(png_structrp png_ptr, int mem_level);

static int getallopts(struct display *dp, const char *opt_str, int *value) ;


extern void (png_set_text_compression_strategy)(png_structrp png_ptr, int strategy);


extern void (png_set_text_compression_window_bits)(png_structrp png_ptr, int window_bits);


extern void (png_set_text_compression_level)(png_structrp png_ptr, int level);


extern void (png_set_text_compression_mem_level)(png_structrp png_ptr, int mem_level);

static void display_start_write(struct display *dp, const char *filename) ;


extern png_structp (png_create_write_struct)(png_const_charp user_png_ver, png_voidp error_ptr, png_error_ptr error_fn, png_error_ptr warn_fn);

static void search_compression(struct display *dp) ;

static void set_compression(struct display *dp) ;

static void set_text_compression(struct display *dp) ;

static int get_option(struct display *dp, const char *opt, int *value) ;


extern void (png_set_compression_buffer_size)(png_structrp png_ptr, size_t size);


extern void (png_set_filter)(png_structrp png_ptr, int method, int filters);

static void print_search_results(struct display *dp) ;

static void read_png(struct display *dp, const char *filename) ;

static void set_windowBits_hi(struct display *dp) ;

static void makename(struct display *dp, const char *dir, const char *infile) ;

static void write_png(struct display *dp, const char *destname) ;

static void log_search(struct display *dp, unsigned int log_depth) ;

static int better_options(const struct display *dp) ;

static void cp_one_file(struct display *dp, const char *filename, const char *destname) ;

static void display_init(struct display *dp) ;

static int opt_check(struct display *dp, const char *arg) ;

static int checkdir(const char *pathname) ;

static int cppng(struct display *dp, const char *file, const char *dest) ;

static const char *cts(int ct) ;

static void display_destroy(struct display *dp) ;

#endif