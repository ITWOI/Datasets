#ifndef __HEADER_FUNC_H__ 
#define __HEADER_FUNC_H__
#include"header_type.h" 

extern png_voidp (png_get_io_ptr)(png_const_structrp png_ptr);


extern png_voidp (png_get_error_ptr)(png_const_structrp png_ptr);

static int is_combo(int transforms) ;

static const char *transform_name(int t) ;

static struct buffer_list *buffer_extend(struct buffer_list *current) ;

static void display_log(struct display *dp, error_level level, const char *fmt, ...) ;

static void buffer_write(struct display *dp, struct buffer *buffer, png_bytep data, size_t size) ;

static struct display *get_dp(png_structp pp) ;

static struct buffer *get_buffer(png_structp pp) ;

#endif