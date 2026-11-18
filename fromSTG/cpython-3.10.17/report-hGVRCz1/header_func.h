#ifndef __HEADER_FUNC_H__ 
#define __HEADER_FUNC_H__
#include"header_type.h" 
static inline char *word_to_string(char *s, mpd_uint_t x, int n, char *dot) ;


int mpd_word_digits(mpd_uint_t word);


mpd_uint_t mpd_msword(const mpd_t *dec);


int mpd_isspecial(const mpd_t *dec);


int mpd_isnan(const mpd_t *dec);


void *mpd_alloc(mpd_size_t nmemb, mpd_size_t size);


int mpd_isnegative(const mpd_t *dec);


int mpd_isqnan(const mpd_t *dec);

static inline char *coeff_to_string(char *s, const mpd_t *dec) ;


int mpd_isinfinite(const mpd_t *dec);


int mpd_iszero(const mpd_t *dec);

static inline mpd_ssize_t mod_mpd_ssize_t(mpd_ssize_t a, mpd_ssize_t m) ;

static inline char *coeff_to_string_dot(char *s, char *dot, const mpd_t *dec) ;

static inline char *exp_to_string(char *s, mpd_ssize_t x) ;

static int _mpd_copy_utf8(char dest[5], const char *s) ;

int mpd_validate_lconv(mpd_spec_t *spec) ;

static inline void _mpd_bcopy(char *dest, const char *src, mpd_ssize_t n) ;

static inline void _mbstr_copy_ascii(mpd_mbstr_t *dest, const char *src, mpd_ssize_t n) ;

static inline void _mbstr_copy_char(mpd_mbstr_t *dest, const char *src, mpd_ssize_t n) ;

static inline void _mbstr_copy_pad(mpd_mbstr_t *dest, mpd_ssize_t n) ;

static void _mpd_add_sep_dot(mpd_mbstr_t *dest, const char *sign, const char *src, mpd_ssize_t n_src, const char *dot, const char *rest, mpd_ssize_t n_rest, const mpd_spec_t *spec) ;


void *mpd_realloc(void *ptr, mpd_size_t nmemb, mpd_size_t size, uint8_t *err);


int mpd_qcopy(mpd_t *result, const mpd_t *a, uint32_t *status);

static inline void _mpd_round(mpd_t *result, const mpd_t *a, mpd_ssize_t prec, const mpd_context_t *ctx, uint32_t *status) ;


void mpd_qrescale(mpd_t *result, const mpd_t *a, mpd_ssize_t exp, const mpd_context_t *ctx, uint32_t *status);

static mpd_ssize_t _mpd_to_string(char **result, const mpd_t *dec, int flags, mpd_ssize_t dplace) ;

static int _mpd_apply_lconv(mpd_mbstr_t *result, const mpd_spec_t *spec, uint32_t *status) ;

static int _mpd_add_pad(mpd_mbstr_t *result, const mpd_spec_t *spec, uint32_t *status) ;

int mpd_parse_fmt_str(mpd_spec_t *spec, const char *fmt, int caps) ;

char *mpd_qformat_spec(const mpd_t *dec, const mpd_spec_t *spec, const mpd_context_t *ctx, uint32_t *status) ;

#endif