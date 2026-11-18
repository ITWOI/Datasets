#ifndef __HEADER_FUNC_H__ 
#define __HEADER_FUNC_H__
#include"header_type.h" 
extern int png_set_text_2(png_const_structrp png_ptr, png_inforp info_ptr, png_const_textp text_ptr, int num_text);


extern png_voidp png_realloc_array(png_const_structrp png_ptr, png_const_voidp array, int old_elements, int add_elements, size_t element_size);


extern void png_chunk_report(png_const_structrp png_ptr, png_const_charp message, int error);


extern void (png_free)(png_const_structrp png_ptr, png_voidp ptr);


extern png_voidp png_malloc_base(png_const_structrp png_ptr, png_alloc_size_t size);

#endif