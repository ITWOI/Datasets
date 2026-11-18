#ifndef __HEADER_TYPE_H__ 
#define __HEADER_TYPE_H__
#include"../common.h" 
struct transform_info;//insertRecordDeclare 

/*TD*/typedef unsigned int png_uint_32;

/*TD*/typedef unsigned char png_byte;


struct transform_info {
    const char *name;
    int transform;
    png_uint_32 valid_chunks;
    png_byte color_mask_required;
    png_byte color_mask_absent;
    png_byte bit_depths;
    png_byte when;
    png_byte tested;
};

struct buffer;//insertRecordDeclare 

struct buffer_list;//insertRecordDeclare 


struct buffer_list {
    struct buffer_list *next;
    png_byte buffer[1024];
};


struct buffer {
    struct buffer_list *last;
    size_t end_count;
    struct buffer_list *current;
    size_t read_count;
    struct buffer_list first;
};

struct _IO_FILE;//insertRecordDeclare 

struct display;//insertRecordDeclare 

struct __jmp_buf_tag;//insertRecordDeclare 

struct png_struct_def;//insertRecordDeclare 

/*TD*/typedef struct png_struct_def png_struct;

/*TD*/typedef png_struct *png_structp;

struct png_info_def;//insertRecordDeclare 

/*TD*/typedef struct png_info_def png_info;

/*TD*/typedef png_info *png_infop;

/*TD*/typedef png_byte **png_bytepp;


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

/*TD*/typedef const char *png_const_charp;

/*TD*/typedef void *png_voidp;

/*TD*/typedef void (*png_error_ptr)(png_structp, png_const_charp);

/*TD*/typedef const png_struct *restrict png_const_structrp;

/*TD*/typedef const png_info *restrict png_const_inforp;

/*TD*/typedef png_byte *png_bytep;

struct png_color_8_struct;//insertRecordDeclare 

/*TD*/typedef struct png_color_8_struct png_color_8;

/*TD*/typedef png_color_8 *png_color_8p;

/*TD*/typedef png_info *restrict png_inforp;


struct png_color_8_struct {
    png_byte red;
    png_byte green;
    png_byte blue;
    png_byte gray;
    png_byte alpha;
};

#endif