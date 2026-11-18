#ifndef __HEADER_TYPE_H__ 
#define __HEADER_TYPE_H__
#include"../common.h" 
struct buffer;//insertRecordDeclare 

struct png_struct_def;//insertRecordDeclare 

/*TD*/typedef struct png_struct_def png_struct;

/*TD*/typedef png_struct *png_structp;

/*TD*/typedef void *png_voidp;

/*TD*/typedef const png_struct *restrict png_const_structrp;

struct buffer_list;//insertRecordDeclare 

/*TD*/typedef unsigned char png_byte;


struct buffer_list {
    struct buffer_list *next;
    png_byte buffer[1024];
};

struct display;//insertRecordDeclare 

struct __jmp_buf_tag;//insertRecordDeclare 

/*TD*/typedef unsigned int png_uint_32;

struct png_info_def;//insertRecordDeclare 

/*TD*/typedef struct png_info_def png_info;

/*TD*/typedef png_info *png_infop;

/*TD*/typedef png_byte **png_bytepp;


struct buffer {
    struct buffer_list *last;
    size_t end_count;
    struct buffer_list *current;
    size_t read_count;
    struct buffer_list first;
};


struct display {
    jmp_buf error_return;
    const char *filename;
    const char *operation;
    int transforms;
    png_uint_32 options;
    png_uint_32 results;
    png_structp original_pp;
    png_infop original_ip;
    size_t original_rowbytes;
    png_bytepp original_rows;
    png_uint_32 chunks;
    png_uint_32 width;
    png_uint_32 height;
    int bit_depth;
    int color_type;
    int interlace_method;
    int compression_method;
    int filter_method;
    int active_transforms;
    int ignored_transforms;
    png_structp read_pp;
    png_infop read_ip;
    png_structp write_pp;
    struct buffer written_file;
    struct buffer original_file;
};

struct _IO_FILE;//insertRecordDeclare 


typedef enum {
    VERBOSE,
    INFORMATION,
    WARNINGS,
    LIBPNG_WARNING,
    APP_WARNING,
    ERRORS,
    APP_FAIL,
    LIBPNG_ERROR,
    LIBPNG_BUG,
    APP_ERROR,
    QUIET,
    USER_ERROR,
    INTERNAL_ERROR
} error_level;

struct __va_list_tag;//insertRecordDeclare 

/*TD*/typedef png_byte *png_bytep;

#endif