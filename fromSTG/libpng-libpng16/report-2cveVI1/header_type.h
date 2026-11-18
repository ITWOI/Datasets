#ifndef __HEADER_TYPE_H__ 
#define __HEADER_TYPE_H__
#include"../common.h" 
struct png_struct_def;//insertRecordDeclare 

/*TD*/typedef struct png_struct_def png_struct;

/*TD*/typedef const png_struct *restrict png_const_structrp;

struct png_info_def;//insertRecordDeclare 

/*TD*/typedef struct png_info_def png_info;

/*TD*/typedef png_info *restrict png_inforp;

struct png_text_struct;//insertRecordDeclare 

/*TD*/typedef struct png_text_struct png_text;

/*TD*/typedef const png_text *png_const_textp;

/*TD*/typedef unsigned int png_uint_32;

struct png_color_struct;//insertRecordDeclare 

/*TD*/typedef struct png_color_struct png_color;

/*TD*/typedef png_color *png_colorp;

/*TD*/typedef unsigned short png_uint_16;

/*TD*/typedef unsigned char png_byte;

struct png_colorspace;//insertRecordDeclare 

/*TD*/typedef struct png_colorspace png_colorspace;

/*TD*/typedef int png_int_32;

/*TD*/typedef png_int_32 png_fixed_point;

struct png_xy;//insertRecordDeclare 

/*TD*/typedef struct png_xy png_xy;


struct png_xy {
    png_fixed_point redx;
    png_fixed_point redy;
    png_fixed_point greenx;
    png_fixed_point greeny;
    png_fixed_point bluex;
    png_fixed_point bluey;
    png_fixed_point whitex;
    png_fixed_point whitey;
};

struct png_XYZ;//insertRecordDeclare 

/*TD*/typedef struct png_XYZ png_XYZ;


struct png_XYZ {
    png_fixed_point red_X;
    png_fixed_point red_Y;
    png_fixed_point red_Z;
    png_fixed_point green_X;
    png_fixed_point green_Y;
    png_fixed_point green_Z;
    png_fixed_point blue_X;
    png_fixed_point blue_Y;
    png_fixed_point blue_Z;
};


struct png_colorspace {
    png_fixed_point gamma;
    png_xy end_points_xy;
    png_XYZ end_points_XYZ;
    png_uint_16 rendering_intent;
    png_uint_16 flags;
};

/*TD*/typedef char *png_charp;

/*TD*/typedef png_byte *png_bytep;

/*TD*/typedef png_text *png_textp;

struct png_time_struct;//insertRecordDeclare 

/*TD*/typedef struct png_time_struct png_time;


struct png_time_struct {
    png_uint_16 year;
    png_byte month;
    png_byte day;
    png_byte hour;
    png_byte minute;
    png_byte second;
};

struct png_color_8_struct;//insertRecordDeclare 

/*TD*/typedef struct png_color_8_struct png_color_8;


struct png_color_8_struct {
    png_byte red;
    png_byte green;
    png_byte blue;
    png_byte gray;
    png_byte alpha;
};

struct png_color_16_struct;//insertRecordDeclare 

/*TD*/typedef struct png_color_16_struct png_color_16;


struct png_color_16_struct {
    png_byte index;
    png_uint_16 red;
    png_uint_16 green;
    png_uint_16 blue;
    png_uint_16 gray;
};

/*TD*/typedef png_uint_16 *png_uint_16p;

/*TD*/typedef char **png_charpp;

struct png_unknown_chunk_t;//insertRecordDeclare 

/*TD*/typedef struct png_unknown_chunk_t png_unknown_chunk;

/*TD*/typedef png_unknown_chunk *png_unknown_chunkp;

struct png_sPLT_struct;//insertRecordDeclare 

/*TD*/typedef struct png_sPLT_struct png_sPLT_t;

/*TD*/typedef png_sPLT_t *png_sPLT_tp;

/*TD*/typedef png_byte **png_bytepp;


struct png_info_def {
    png_uint_32 width;
    png_uint_32 height;
    png_uint_32 valid;
    size_t rowbytes;
    png_colorp palette;
    png_uint_16 num_palette;
    png_uint_16 num_trans;
    png_byte bit_depth;
    png_byte color_type;
    png_byte compression_type;
    png_byte filter_type;
    png_byte interlace_type;
    png_byte channels;
    png_byte pixel_depth;
    png_byte spare_byte;
    png_byte signature[8];
    png_colorspace colorspace;
    png_charp iccp_name;
    png_bytep iccp_profile;
    png_uint_32 iccp_proflen;
    int num_text;
    int max_text;
    png_textp text;
    png_time mod_time;
    png_color_8 sig_bit;
    png_bytep trans_alpha;
    png_color_16 trans_color;
    png_color_16 background;
    png_int_32 x_offset;
    png_int_32 y_offset;
    png_byte offset_unit_type;
    png_uint_32 x_pixels_per_unit;
    png_uint_32 y_pixels_per_unit;
    png_byte phys_unit_type;
    int num_exif;
    png_bytep exif;
    png_bytep eXIf_buf;
    png_uint_16p hist;
    png_charp pcal_purpose;
    png_int_32 pcal_X0;
    png_int_32 pcal_X1;
    png_charp pcal_units;
    png_charpp pcal_params;
    png_byte pcal_type;
    png_byte pcal_nparams;
    png_uint_32 free_me;
    png_unknown_chunkp unknown_chunks;
    int unknown_chunks_num;
    png_sPLT_tp splt_palettes;
    int splt_palettes_num;
    png_byte scal_unit;
    png_charp scal_s_width;
    png_charp scal_s_height;
    png_bytepp row_pointers;
};

/*TD*/typedef void *png_voidp;

/*TD*/typedef const void *png_const_voidp;

/*TD*/typedef const char *png_const_charp;


struct png_text_struct {
    int compression;
    png_charp key;
    png_charp text;
    size_t text_length;
    size_t itxt_length;
    png_charp lang;
    png_charp lang_key;
};

/*TD*/typedef size_t png_alloc_size_t;

#endif