#ifndef __HEADER_FUNC_H__ 
#define __HEADER_FUNC_H__
#include"header_type.h" 
static int known_bad_combos[][2] = {{64 | 1024, 0}};
;
static struct transform_info transform_info[] = {{"STRIP_16", 1, 0, 0, 0, 16, 1, 0}, {"STRIP_ALPHA", 2, 0, 4, 0, (1 + 2 + 4 + 8 + 16), 1, 0}, {"PACKING", 4, 0, 0, 0, (1 + 2 + 4), 3, 0}, {"PACKSWAP", 8, 0, 0, 0, (1 + 2 + 4), 3, 0}, {"EXPAND", 16, 0, 1, 0, (1 + 2 + 4 + 8 + 16), 1, 0}, {"EXPAND", 16, 0, 0, 2, (1 + 2 + 4 + 8 + 16), 1, 0}, {"EXPAND", 16, 16U, 0, 4, (1 + 2 + 4 + 8 + 16), 1, 0}, {"INVERT_MONO", 32, 0, 0, 2, (1 + 2 + 4 + 8 + 16), 3, 0}, {"SHIFT", 64, 2U, 0, 0, (1 + 2 + 4 + 8 + 16), 3, 0}, {"BGR", 128, 0, 2, 1, (8 + 16), 3, 0}, {"SWAP_ALPHA", 256, 0, 4, 0, (8 + 16), 3, 0}, {"SWAP_ENDIAN", 512, 0, 0, 1, 16, 3, 0}, {"INVERT_ALPHA", 1024, 0, 4, 0, (8 + 16), 3, 0}, {"STRIP_FILLER_BEFORE", 2048, 0, 4, 1, (8 + 16), 2, 0}, {"STRIP_FILLER_AFTER", 4096, 0, 4, 1, (8 + 16), 2, 0}, {"GRAY_TO_RGB", 8192, 0, 0, 2, (1 + 2 + 4 + 8 + 16), 1, 0}, {"GRAY_TO_RGB", 8192, 0, 1, 0, (1 + 2 + 4 + 8 + 16), 1, 0}, {"EXPAND_16", 16384, 0, 0, 0, (1 + 2 + 4 + 8), 1, 0}, {"EXPAND_16", 16384, 16U, 0, 4, 16, 1, 0}, {"SCALE_16", 32768, 0, 0, 0, 16, 1, 0}, {((void *)0), 0, 0, 0, 0, 0, 0, 0}};
;
static unsigned int read_transforms;
;
static unsigned int write_transforms;
;
static unsigned int rw_transforms;
;
static void buffer_init(struct buffer *buffer) ;

static struct buffer_list *buffer_extend(struct buffer_list *current) ;

static void buffer_destroy(struct buffer *buffer) ;

static int is_combo(int transforms) ;

static const char *transform_name(int t) ;

extern FILE *stdin;
;
static void display_log(struct display *dp, error_level level, const char *fmt, ...) ;

static int buffer_from_file(struct buffer *buffer, FILE *fp) ;


extern png_structp (png_create_read_struct)(png_const_charp user_png_ver, png_voidp error_ptr, png_error_ptr error_fn, png_error_ptr warn_fn);

static void display_error(png_structp pp, png_const_charp error) ;

static void display_warning(png_structp pp, png_const_charp warning) ;


extern png_infop (png_create_info_struct)(png_const_structrp png_ptr);

static void buffer_start_read(struct buffer *buffer) ;

static void read_png(struct display *dp, struct buffer *bp, const char *operation, int transforms) ;


extern size_t (png_get_rowbytes)(png_const_structrp png_ptr, png_const_inforp info_ptr);


extern png_uint_32 (png_get_valid)(png_const_structrp png_ptr, png_const_inforp info_ptr, png_uint_32 flag);


extern png_bytepp (png_get_rows)(png_const_structrp png_ptr, png_const_inforp info_ptr);


extern png_uint_32 (png_get_IHDR)(png_const_structrp png_ptr, png_const_inforp info_ptr, png_uint_32 *width, png_uint_32 *height, int *bit_depth, int *color_type, int *interlace_method, int *compression_method, int *filter_method);


extern png_uint_32 (png_get_sBIT)(png_const_structrp png_ptr, png_inforp info_ptr, png_color_8p *sig_bit);

static void buffer_start_write(struct buffer *buffer) ;


extern png_structp (png_create_write_struct)(png_const_charp user_png_ver, png_voidp error_ptr, png_error_ptr error_fn, png_error_ptr warn_fn);

static int is_bad_combo(int transforms) ;

static int first_transform(int transforms) ;

static void display_cache_file(struct display *dp, const char *filename) ;

static void update_display(struct display *dp) ;

static int compare_read(struct display *dp, int applied_transforms) ;

static void write_png(struct display *dp, png_infop ip, int transforms) ;

static int skip_transform(struct display *dp, int tr) ;

static void test_one_file(struct display *dp, const char *filename) ;

static void validate_T(void) ;

static void display_init(struct display *dp) ;

static void display_clean(struct display *dp) ;

static void display_destroy(struct display *dp) ;

static int do_test(struct display *dp, const char *file) ;

#endif