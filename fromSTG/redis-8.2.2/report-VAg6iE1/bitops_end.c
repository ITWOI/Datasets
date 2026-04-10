#include "header_func.h"
extern int checkUnsignedBitfieldOverflow (uint64_t value, int64_t incr, uint64_t bits, int owtype, uint64_t *limit){
    uint64_t max = (bits == 64) ? (18446744073709551615UL) : (((uint64_t)1 << bits) - 1);
    int64_t maxincr = max - value;
    int64_t minincr = -value;
    if (value > max || (incr > 0 && incr > maxincr)) {
        if (limit) {
            if (owtype == 0) {
                goto handle_wrap;
            } else {
                ;
            }
        }
        return 1;
    } else if (incr < 0 && incr < minincr) {
        if (limit) {
            if (owtype == 0) {
                goto handle_wrap;
            } else {
                ;
            }
        }
        return -1;
    }
    return 0;
  handle_wrap:
    {
        uint64_t mask = ((uint64_t)-1) << bits;
        uint64_t res = value + incr;
        res &= ~mask;
        *limit = res;
    }
    return 1;
}
