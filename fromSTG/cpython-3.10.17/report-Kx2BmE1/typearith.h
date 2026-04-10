#include "header_func.h"
static inline void _mpd_mul_words (mpd_uint_t *hi, mpd_uint_t *lo, mpd_uint_t a, mpd_uint_t b){
    mpd_uint_t h, l;
    asm ("mulq %3\n\t" : "=d" (h), "=a" (l) : "%a" (a), "rm" (b) : "cc");
    *hi = h;
    *lo = l;
}
static inline mpd_size_t add_size_t (mpd_size_t a, mpd_size_t b){
    if (a > (18446744073709551615UL) - b) {
        do {
            fprintf(stderr, "%s:%d: error: ", "Modules/_decimal/libmpdec/typearith.h", 597);
            fprintf(stderr, "add_size_t(): overflow: check the context");
            fputc('\n', stderr);
            abort();
        } while (0);
    }
    return a + b;
}
static inline mpd_size_t mul_size_t (mpd_size_t a, mpd_size_t b){
    mpd_uint_t hi, lo;
    _mpd_mul_words(&hi, &lo, (mpd_uint_t)a, (mpd_uint_t)b);
    if (hi) {
        do {
            fprintf(stderr, "%s:%d: error: ", "Modules/_decimal/libmpdec/typearith.h", 622);
            fprintf(stderr, "mul_size_t(): overflow: check the context");
            fputc('\n', stderr);
            abort();
        } while (0);
    }
    return lo;
}
