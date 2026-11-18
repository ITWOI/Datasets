#include "header_func.h"
static inline int _mpd_isallzero (const mpd_uint_t *data, mpd_ssize_t len){
    while (--len >= 0)
        {
            if (data[len] != 0)
                return 0;
        }
    return 1;
}
