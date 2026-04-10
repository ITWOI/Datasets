#ifndef __HEADER_TYPE_H__ 
#define __HEADER_TYPE_H__
#include"../common.h" 
struct display;//insertRecordDeclare 

struct __jmp_buf_tag;//insertRecordDeclare 

/*TD*/typedef size_t png_alloc_size_t;

struct png_struct_def;//insertRecordDeclare 

/*TD*/typedef struct png_struct_def png_struct;

/*TD*/typedef png_struct *png_structp;

struct png_info_def;//insertRecordDeclare 

/*TD*/typedef struct png_info_def png_info;

/*TD*/typedef png_info *png_infop;

struct png_text_struct;//insertRecordDeclare 

/*TD*/typedef struct png_text_struct png_text;

/*TD*/typedef png_text *png_textp;

/*TD*/typedef unsigned int png_uint_32;

/*TD*/typedef unsigned char png_byte;


struct display {
    jmp_buf error_return;
    unsigned int errset;
    int errlevel;
    const char *operation;
    const char *filename;
    const char *output_file;
    FILE *fp;
    png_alloc_size_t read_size;
    png_structp read_pp;
    png_infop ip;
    png_textp text_ptr;
    int num_text;
    int text_stashed;
    png_alloc_size_t write_size;
    png_alloc_size_t best_size;
    png_structp write_pp;
    png_alloc_size_t size;
    png_uint_32 w;
    png_uint_32 h;
    int bpp;
    png_byte ct;
    int no_warnings;
    int min_windowBits;
    png_uint_32 results;
    png_uint_32 options;
    png_byte entry[23];
    int value[23];
    unsigned int csp;
    unsigned int nsp;
    unsigned int tsp;
    int opt_string_start;
    struct stack {
        png_alloc_size_t best_size;
        png_alloc_size_t lo_size;
        png_alloc_size_t hi_size;
        int lo;
        int hi;
        int best_val;
        int opt_string_end;
        png_byte opt;
        png_byte entry;
        png_byte end;
    } stack[8];
    char curr[256];
    char best[256];
    char namebuf[4096];
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

/*TD*/typedef const png_struct *restrict png_const_structrp;

/*TD*/typedef png_info *restrict png_inforp;

/*TD*/typedef char *png_charp;


struct png_text_struct {
    int compression;
    png_charp key;
    png_charp text;
    size_t text_length;
    size_t itxt_length;
    png_charp lang;
    png_charp lang_key;
};

struct option;//insertRecordDeclare 

/*TD*/typedef struct option option;

struct value_list;//insertRecordDeclare 

/*TD*/typedef struct value_list value_list;


struct option {
    const char *name;
    png_uint_32 opt;
    png_byte search;
    png_byte value_count;
    const value_list *values;
};


struct value_list {
    const char *name;
    int value;
};

struct stat;//insertRecordDeclare 

/*TD*/typedef const char *png_const_charp;

/*TD*/typedef void *png_voidp;

/*TD*/typedef void (*png_error_ptr)(png_structp, png_const_charp);

/*TD*/typedef png_info **png_infopp;

/*TD*/typedef const png_info *restrict png_const_inforp;

struct png_color_struct;//insertRecordDeclare 

/*TD*/typedef struct png_color_struct png_color;

/*TD*/typedef png_color *png_colorp;


struct png_color_struct {
    png_byte red;
    png_byte green;
    png_byte blue;
};

/*TD*/typedef png_struct *restrict png_structrp;

/*TD*/typedef const png_color *png_const_colorp;

/*TD*/typedef const png_struct *png_const_structp;

/*TD*/typedef const png_info *png_const_infop;

#endif