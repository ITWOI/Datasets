static u32 crc32sum (u32 crc, u8 *restrict buf, size_t size){
    while (size--)
        crc = crc32Table[((u8)crc ^ *(buf++)) & 255] ^ (crc >> 8);
    return crc;
}


static s32 lzp_decode_block (const u8 *restrict in, const u8 *in_end, s32 *restrict lut, u8 *restrict out, const u8 *out_end){
    const u8 *outs = out;
    for (s32 i = 0; i < 4; ++i)
        *out++ = *in++;
    u32 ctx = ((u32)out[-1]) | (((u32)out[-2]) << 8) | (((u32)out[-3]) << 16) | (((u32)out[-4]) << 24);
    while (in < in_end && out < out_end)
        {
            u32 idx = (ctx >> 15 ^ ctx ^ ctx >> 3) & ((s32)(1 << 18) - 1);
            s32 val = lut[idx];
            lut[idx] = (s32)(out - outs);
            if (*in == 242 && val > 0) {
                in++;
                if (*in != 255) {
                    s32 len = 40;
                    while (1)
                        {
                            if (in == in_end)
                                return -1;
                            len += *in;
                            if (*in++ != 254)
                                break;
                            ;
                        }
                    const u8 *ref = outs + val;
                    const u8 *oe = out + len;
                    if (oe > out_end)
                        oe = out_end;
                    while (out < oe)
                        *out++ = *ref++;
                    ctx = ((u32)out[-1]) | (((u32)out[-2]) << 8) | (((u32)out[-3]) << 16) | (((u32)out[-4]) << 24);
                } else {
                    in++;
                    ctx = (ctx << 8) | (*out++ = 242);
                }
            } else {
                ctx = (ctx << 8) | (*out++ = *in++);
            }
        }
    return out - outs;
}


static s32 lzp_decompress (const u8 *restrict in, u8 *restrict out, s32 n, s32 max, s32 *restrict lut){
    if (n < 4)
        return -1;
    memset(lut, 0, sizeof(s32) * (1 << 18));
    return lzp_decode_block(in, in + n, lut, out, out + max);
}


static int mrled (u8 *restrict in, u8 *restrict out, s32 outlen, s32 maxin){
    s32 op = 0, ip = 0;
    s32 c, pc = -1;
    s32 t[256] = {0};
    s32 run = 0;
    if (maxin < 32)
        return 1;
    for (s32 i = 0; i < 32; ++i) {
        c = in[ip++];
        for (s32 j = 0; j < 8; ++j)
            t[i * 8 + j] = (c >> j) & 1;
    }
    while (op < outlen && ip < maxin)
        {
            c = in[ip++];
            if (t[c]) {
                for (run = 0; ip < maxin && (pc = in[ip++]) == 255; run += 255)
                    ;
                run += pc + 1;
                for (; run > 0 && op < outlen; --run)
                    out[op++] = c;
            } else
                out[op++] = c;
        }
    return op != outlen;
}


static void begin (state *s){
    __builtin_prefetch((const void *)(s), 0, 0);
    for (int i = 0; i < 256; i++)
        s->C0[i] = 1 << 15;
    for (int i = 0; i < 256; i++)
        for (int j = 0; j < 256; j++)
            s->C1[i][j] = 1 << 15;
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 256; j++)
            for (int k = 0; k < 17; k++)
                s->C2[2 * j + i][k] = (k << 12) - (k == 16);
}


static void decode_bytes (state *s, u8 *c, s32 size){
    u32 high = 4294967295U, low = 0, c1 = 0, c2 = 0, run = 0, code = 0;
    code = (code << 8) + ((s)->input_ptr < (s)->input_max ? (s)->in_queue[(s)->input_ptr++] : -1);
    code = (code << 8) + ((s)->input_ptr < (s)->input_max ? (s)->in_queue[(s)->input_ptr++] : -1);
    code = (code << 8) + ((s)->input_ptr < (s)->input_max ? (s)->in_queue[(s)->input_ptr++] : -1);
    code = (code << 8) + ((s)->input_ptr < (s)->input_max ? (s)->in_queue[(s)->input_ptr++] : -1);
    for (s32 i = 0; i < size; i++) {
        if (c1 == c2) {
            ++run;
        } else
            run = 0;
        const int f = run > 2;
        int ctx = 1;
        while (ctx < 256)
            {
                const int p0 = s->C0[ctx];
                const int p1 = s->C1[c1][ctx];
                const int p2 = s->C1[c2][ctx];
                const int p = ((p0 + p1) * 7 + p2 + p2) >> 4;
                const int j = p >> 12;
                const int x1 = s->C2[2 * ctx + f][j];
                const int x2 = s->C2[2 * ctx + f][j + 1];
                const int ssep = x1 + (((x2 - x1) * (p & 4095)) >> 12);
                const u32 mid = low + (((u64)(high - low) * (ssep * 3 + p)) >> 18);
                const u8 bit = code <= mid;
                if (bit) {
                    high = mid;
                } else
                    low = mid + 1;
                while ((low ^ high) < (1 << 24))
                    {
                        low <<= 8;
                        high = (high << 8) + 255;
                        code = (code << 8) + ((s)->input_ptr < (s)->input_max ? (s)->in_queue[(s)->input_ptr++] : -1);
                    }
                if (bit) {
                    (s->C0[ctx]) = ((s->C0[ctx]) + (((s->C0[ctx]) ^ 65535) >> 2));
                    (s->C1[c1][ctx]) = ((s->C1[c1][ctx]) + (((s->C1[c1][ctx]) ^ 65535) >> 4));
                    (s->C2[2 * ctx + f][j]) = ((s->C2[2 * ctx + f][j]) + (((s->C2[2 * ctx + f][j]) ^ 65535) >> 6));
                    (s->C2[2 * ctx + f][j + 1]) = ((s->C2[2 * ctx + f][j + 1]) + (((s->C2[2 * ctx + f][j + 1]) ^ 65535) >> 6));
                    ctx += ctx + 1;
                } else {
                    (s->C0[ctx]) = ((s->C0[ctx]) - ((s->C0[ctx]) >> 2));
                    (s->C1[c1][ctx]) = ((s->C1[c1][ctx]) - ((s->C1[c1][ctx]) >> 4));
                    (s->C2[2 * ctx + f][j]) = ((s->C2[2 * ctx + f][j]) - ((s->C2[2 * ctx + f][j]) >> 6));
                    (s->C2[2 * ctx + f][j + 1]) = ((s->C2[2 * ctx + f][j + 1]) - ((s->C2[2 * ctx + f][j + 1]) >> 6));
                    ctx += ctx;
                }
            }
        c2 = c1;
        c[i] = c1 = ctx & 255;
    }
}


extern  __attribute__((visibility("default"))) int8_t bz3_last_error (struct bz3_state *state){
    return state->last_error;
}


extern  __attribute__((visibility("default"))) size_t bz3_bound (size_t input_size){
    return input_size + input_size / 50 + 32;
}


extern  __attribute__((visibility("default"))) struct bz3_state * bz3_new (s32 block_size){
    if (block_size < ((65) * 1024) || block_size > ((511) * 1024 * 1024)) {
        return ((void *)0);
    }
    struct bz3_state *bz3_state = malloc(sizeof(struct bz3_state));
    if (!bz3_state) {
        return ((void *)0);
    }
    bz3_state->cm_state = malloc(sizeof(state));
    bz3_state->swap_buffer = malloc(bz3_bound(block_size));
    bz3_state->sais_array = malloc((bz3_bound(block_size) + 128) * sizeof(s32));
    memset(bz3_state->sais_array, 0, sizeof(s32) * (bz3_bound(block_size) + 128));
    bz3_state->lzp_lut = calloc(1 << 18, sizeof(s32));
    if (!bz3_state->cm_state || !bz3_state->swap_buffer || !bz3_state->sais_array || !bz3_state->lzp_lut) {
        if (bz3_state->cm_state)
            free(bz3_state->cm_state);
        if (bz3_state->swap_buffer)
            free(bz3_state->swap_buffer);
        if (bz3_state->sais_array)
            free(bz3_state->sais_array);
        if (bz3_state->lzp_lut)
            free(bz3_state->lzp_lut);
        free(bz3_state);
        return ((void *)0);
    }
    bz3_state->block_size = block_size;
    bz3_state->last_error = 0;
    return bz3_state;
}


extern  __attribute__((visibility("default"))) void bz3_free (struct bz3_state *state){
    free(state->swap_buffer);
    free(state->sais_array);
    free(state->cm_state);
    free(state->lzp_lut);
    free(state);
}


extern  __attribute__((visibility("default"))) int32_t bz3_decode_block (struct bz3_state *state, u8 *buffer, s32 data_size, s32 orig_size){
    u32 crc32 = read_neutral_s32(buffer);
    s32 bwt_idx = read_neutral_s32(buffer + 4);
    if (data_size > bz3_bound(state->block_size) || data_size < 0) {
        state->last_error = -4;
        return -1;
    }
    if (bwt_idx == -1) {
        if (data_size - 8 > 64 || data_size < 8) {
            state->last_error = -4;
            return -1;
        }
        memmove(buffer, buffer + 8, data_size - 8);
        if (crc32sum(1, buffer, data_size - 8) != crc32) {
            state->last_error = -3;
            return -1;
        }
        return data_size - 8;
    }
    s8 model = buffer[8];
    s32 lzp_size = -1, rle_size = -1, p = 0;
    if (model & 2)
        lzp_size = read_neutral_s32(buffer + 9 + 4 * p++);
    if (model & 4)
        rle_size = read_neutral_s32(buffer + 9 + 4 * p++);
    p += 2;
    data_size -= p * 4 + 1;
    if (((model & 2) && (lzp_size > bz3_bound(state->block_size) || lzp_size < 0)) || ((model & 4) && (rle_size > bz3_bound(state->block_size) || rle_size < 0))) {
        state->last_error = -4;
        return -1;
    }
    if (orig_size > bz3_bound(state->block_size) || orig_size < 0) {
        state->last_error = -4;
        return -1;
    }
    u8 *b1 = buffer, *b2 = state->swap_buffer;
    begin(state->cm_state);
    state->cm_state->in_queue = b1 + p * 4 + 1;
    state->cm_state->input_ptr = 0;
    state->cm_state->input_max = data_size;
    s32 size_src;
    if (model & 2) {
        size_src = lzp_size;
    } else if (model & 4) {
        size_src = rle_size;
    } else
        size_src = orig_size;
    decode_bytes(state->cm_state, b2, size_src);
    {
        u8 *tmp = b1;
        b1 = b2;
        b2 = tmp;
    }
    ;
    ;
    if (bwt_idx >= size_src) {
        state->last_error = -4;
        return -1;
    }
    memset(state->sais_array, 0, sizeof(s32) * (bz3_bound(state->block_size) + 128));
    memset(b2, 0, size_src);
    if (libsais_unbwt(b1, b2, state->sais_array, size_src, ((void *)0), bwt_idx) < 0) {
        state->last_error = -2;
        return -1;
    }
    {
        u8 *tmp = b1;
        b1 = b2;
        b2 = tmp;
    }
    ;
    ;
    if (model & 2) {
        size_src = lzp_decompress(b1, b2, lzp_size, bz3_bound(state->block_size), state->lzp_lut);
        if (size_src == -1) {
            state->last_error = -3;
            return -1;
        }
        {
            u8 *tmp = b1;
            b1 = b2;
            b2 = tmp;
        }
        ;
        ;
    }
    if (model & 4) {
        int err = mrled(b1, b2, orig_size, size_src);
        if (err) {
            state->last_error = -3;
            return -1;
        }
        size_src = orig_size;
        {
            u8 *tmp = b1;
            b1 = b2;
            b2 = tmp;
        }
        ;
        ;
    }
    state->last_error = 0;
    if (size_src > state->block_size || size_src < 0) {
        state->last_error = -4;
        return -1;
    }
    if (b1 != buffer)
        memcpy(buffer, b1, size_src);
    if (crc32 != crc32sum(1, buffer, size_src)) {
        state->last_error = -3;
        return -1;
    }
    return size_src;
}


extern  __attribute__((visibility("default"))) int bz3_decompress (const uint8_t *in, uint8_t *out, size_t in_size, size_t *out_size){
    if (in_size < 13)
        return -4;
    if (in[0] != 'B' || in[1] != 'Z' || in[2] != '3' || in[3] != 'v' || in[4] != '1') {
        return -4;
    }
    u32 block_size = read_neutral_s32(in + 5);
    u32 n_blocks = read_neutral_s32(in + 9);
    in_size -= 13;
    in += 13;
    struct bz3_state *state = bz3_new(block_size);
    if (!state)
        return -7;
    u8 *compression_buf = malloc(bz3_bound(block_size));
    if (!compression_buf) {
        bz3_free(state);
        return -7;
    }
    size_t buf_max = *out_size;
    *out_size = 0;
    for (u32 i = 0; i < n_blocks; i++) {
        if (in_size < 8) {
          malformed_header:
            bz3_free(state);
            free(compression_buf);
            return -4;
        }
        s32 size = read_neutral_s32(in);
        if (size < 0 || size > block_size)
            goto malformed_header;
        ;
        if (in_size < size + 8) {
            bz3_free(state);
            free(compression_buf);
            return -5;
        }
        s32 orig_size = read_neutral_s32(in + 4);
        if (orig_size < 0)
            goto malformed_header;
        ;
        if (buf_max < *out_size + orig_size) {
            bz3_free(state);
            free(compression_buf);
            return -6;
        }
        memcpy(compression_buf, in + 8, size);
        bz3_decode_block(state, compression_buf, size, orig_size);
        if (bz3_last_error(state) != 0) {
            s8 last_error = state->last_error;
            bz3_free(state);
            free(compression_buf);
            return last_error;
        }
        memcpy(out + *out_size, compression_buf, orig_size);
        *out_size += orig_size;
        in += size + 8;
        in_size -= size + 8;
    }
    bz3_free(state);
    return 0;
}


