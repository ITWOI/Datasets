#include "header_func.h"
static s32 read_neutral_s32 (const u8 *data){
    return ((u32)data[0]) | (((u32)data[1]) << 8) | (((u32)data[2]) << 16) | (((u32)data[3]) << 24);
}
