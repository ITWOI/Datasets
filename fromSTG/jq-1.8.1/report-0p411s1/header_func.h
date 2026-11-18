#ifndef __HEADER_FUNC_H__ 
#define __HEADER_FUNC_H__
#include"header_type.h" 

jv_kind jv_get_kind(jv);


jv jv_object_get(jv object, jv key);


jv jv_copy(jv);


jv jv_string(const char *);


void jv_free(jv);


jv jv_number(double);


int jv_array_length(jv);


int jv_string_length_codepoints(jv);


jv jv_invalid_with_msg(jv);


double jv_number_value(jv);


jv jv_true(void);

static int jv_is_valid(jv x) ;


jv jv_null(void);


int jvp_number_is_nan(jv);


jv jv_array_get(jv, int);


jv jv_array_slice(jv, int, int);


jv jv_string_slice(jv j, int start, int end);


jv jv_array_indexes(jv, jv);


int jv_string_length_bytes(jv);


jv jv_string_fmt(const char *, ...);


const char *jv_kind_name(jv_kind);


const char *jv_string_value(jv);

static jv parse_slice(jv j, jv slice, int *pstart, int *pend) ;


jv jv_object(void);


jv jv_object_set(jv object, jv key, jv value);


jv jv_array(void);


jv jv_array_set(jv, int, jv);


jv jv_array_append(jv, jv);

static double jv_number_get_value_and_consume(jv number) ;


jv jv_object_delete(jv object, jv key);


int jv_equal(jv, jv);

jv jv_set(jv t, jv k, jv v) ;

jv jv_get(jv t, jv k) ;

static jv delpaths_sorted(jv object, jv paths, int start) ;

static jv jv_dels(jv t, jv keys) ;

jv jv_sort(jv, jv);


void *jv_mem_calloc(size_t, size_t);

static struct sort_entry *sort_items(jv objects, jv keys) ;

#endif