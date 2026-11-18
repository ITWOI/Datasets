#ifndef __HEADER_TYPE_H__ 
#define __HEADER_TYPE_H__
#include"../common.h" 
/*TD*/typedef int32_t s32;

/*TD*/typedef uint8_t u8;

/*TD*/typedef uint32_t u32;

/*TD*/typedef ptrdiff_t fast_sint_t;

/*TD*/typedef u32 sa_uint_t;

/*TD*/typedef size_t fast_uint_t;

/*TD*/typedef uint16_t u16;

/*TD*/typedef s32 sa_sint_t;


/*Ano*/typedef struct {
    u8 *in_queue;
    u8 *out_queue;
    s32 input_ptr;
    s32 output_ptr;
    s32 input_max;
    u16 C0[256];
    u16 C1[256][256];
    u16 C2[512][17];
} state;

/*TD*/typedef uint64_t u64;

struct bz3_state;//insertRecordDeclare 

/*TD*/typedef int8_t s8;


struct bz3_state {
    u8 *swap_buffer;
    s32 block_size;
    s32 *sais_array;
    s32 *lzp_lut;
    state *cm_state;
    s8 last_error;
};

#endif