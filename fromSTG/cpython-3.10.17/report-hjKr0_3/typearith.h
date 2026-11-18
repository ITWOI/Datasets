#include "header_func.h"
static inline void _mpd_divmod_pow10 (mpd_uint_t *q, mpd_uint_t *r, mpd_uint_t v, mpd_uint_t exp){
    ;
    if (exp <= 9) {
        if (exp <= 4) {
            switch (exp) {
              case 0:
                *q = v;
                *r = 0;
                break;
              case 1:
                *q = v / 10UL;
                *r = v - *q * 10UL;
                break;
              case 2:
                *q = v / 100UL;
                *r = v - *q * 100UL;
                break;
              case 3:
                *q = v / 1000UL;
                *r = v - *q * 1000UL;
                break;
              case 4:
                *q = v / 10000UL;
                *r = v - *q * 10000UL;
                break;
            }
        } else {
            switch (exp) {
              case 5:
                *q = v / 100000UL;
                *r = v - *q * 100000UL;
                break;
              case 6:
                *q = v / 1000000UL;
                *r = v - *q * 1000000UL;
                break;
              case 7:
                *q = v / 10000000UL;
                *r = v - *q * 10000000UL;
                break;
              case 8:
                *q = v / 100000000UL;
                *r = v - *q * 100000000UL;
                break;
              case 9:
                *q = v / 1000000000UL;
                *r = v - *q * 1000000000UL;
                break;
            }
        }
    } else {
        if (exp <= 14) {
            switch (exp) {
              case 10:
                *q = v / 10000000000ULL;
                *r = v - *q * 10000000000ULL;
                break;
              case 11:
                *q = v / 100000000000ULL;
                *r = v - *q * 100000000000ULL;
                break;
              case 12:
                *q = v / 1000000000000ULL;
                *r = v - *q * 1000000000000ULL;
                break;
              case 13:
                *q = v / 10000000000000ULL;
                *r = v - *q * 10000000000000ULL;
                break;
              case 14:
                *q = v / 100000000000000ULL;
                *r = v - *q * 100000000000000ULL;
                break;
            }
        } else {
            switch (exp) {
              case 15:
                *q = v / 1000000000000000ULL;
                *r = v - *q * 1000000000000000ULL;
                break;
              case 16:
                *q = v / 10000000000000000ULL;
                *r = v - *q * 10000000000000000ULL;
                break;
              case 17:
                *q = v / 100000000000000000ULL;
                *r = v - *q * 100000000000000000ULL;
                break;
              case 18:
                *q = v / 1000000000000000000ULL;
                *r = v - *q * 1000000000000000000ULL;
                break;
              case 19:
                *q = v / 10000000000000000000ULL;
                *r = v - *q * 10000000000000000000ULL;
                break;
            }
        }
    }
}
static inline void _mpd_div_word (mpd_uint_t *q, mpd_uint_t *r, mpd_uint_t v, mpd_uint_t d){
    *q = v / d;
    *r = v - *q * d;
}
