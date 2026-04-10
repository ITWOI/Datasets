#include "header_func.h"
static int jv_is_valid (jv x){
    return jv_get_kind(x) != JV_KIND_INVALID;
}
