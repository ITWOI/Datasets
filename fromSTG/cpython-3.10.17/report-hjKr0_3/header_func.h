#ifndef __HEADER_FUNC_H__ 
#define __HEADER_FUNC_H__
#include"header_type.h" 
static inline void _mpd_div_word(mpd_uint_t *q, mpd_uint_t *r, mpd_uint_t v, mpd_uint_t d) ;

static inline void _mpd_divmod_pow10(mpd_uint_t *q, mpd_uint_t *r, mpd_uint_t v, mpd_uint_t exp) ;

static inline int _mpd_isallzero(const mpd_uint_t *data, mpd_ssize_t len) ;

extern const mpd_uint_t mpd_pow10[];
;
#endif