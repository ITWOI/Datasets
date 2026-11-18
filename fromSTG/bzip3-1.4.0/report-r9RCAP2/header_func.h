#ifndef __HEADER_FUNC_H__ 
#define __HEADER_FUNC_H__
#include"header_type.h" 
static size_t xread(void *data, size_t size, size_t len, FILE *des) ;

static size_t xread_eofcheck(void *data, size_t size, size_t len, FILE *des) ;

static void xwrite(const void *data, size_t size, size_t len, FILE *des) ;

static void write_neutral_s32(u8 *data, s32 value) ;

static void xread_noeof(void *data, size_t size, size_t len, FILE *des) ;

static s32 read_neutral_s32(const u8 *data) ;

extern FILE *stderr;
;

const char *bz3_strerror(struct bz3_state *state);


size_t bz3_bound(size_t input_size);


int32_t bz3_decode_block(struct bz3_state *state, uint8_t *buffer, int32_t size, int32_t orig_size);


int8_t bz3_last_error(struct bz3_state *state);


void bz3_free(struct bz3_state *state);


struct bz3_state *bz3_new(int32_t block_size);


void bz3_encode_blocks(struct bz3_state *states[], uint8_t *buffers[], int32_t sizes[], int32_t n);


void bz3_decode_blocks(struct bz3_state *states[], uint8_t *buffers[], int32_t sizes[], int32_t orig_sizes[], int32_t n);


int32_t bz3_encode_block(struct bz3_state *state, uint8_t *buffer, int32_t size);

#endif