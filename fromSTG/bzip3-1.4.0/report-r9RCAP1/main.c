static void xwrite (const void *data, size_t size, size_t len, FILE *des){
    if (len == 0 || size == 0)
        return;
    if (fwrite(data, size, len, des) != len) {
        ;
        ;
    }
}


static size_t xread (void *data, size_t size, size_t len, FILE *des){
    size_t written = fread(data, size, len, des);
    if (ferror(des)) {
        ;
        ;
    }
    return written;
}


static size_t xread_eofcheck (void *data, size_t size, size_t len, FILE *des){
    size_t written = xread(data, size, len, des);
    if (!written)
        return 0;
    if (feof(des)) {
        ;
        ;
    }
    return written;
}


static void xread_noeof (void *data, size_t size, size_t len, FILE *des){
    if (!xread_eofcheck(data, size, len, des)) {
        ;
        ;
    }
}


static int process (FILE *input_des, FILE *output_des, int mode, int block_size, int workers, int verbose, char *file_name){
    uint64_t bytes_read = 0, bytes_written = 0;
    if ((mode == 1 && isatty(fileno(output_des))) || ((mode == 0 || mode == 2 || mode == 3) && isatty(fileno(input_des)))) {
        ;
        return 1;
    }
    (*__errno_location()) = 0;
    u8 byteswap_buf[4];
    switch (mode) {
      case 1:
        xwrite("BZ3v1", 5, 1, output_des);
        write_neutral_s32(byteswap_buf, block_size);
        xwrite(byteswap_buf, 4, 1, output_des);
        bytes_written += 9;
        break;
      case 3:
      case 0:
      case 2:
        {
            char signature[5];
            if (xread(signature, 5, 1, input_des) != 1 || strncmp(signature, "BZ3v1", 5) != 0) {
                ;
                return 1;
            }
            xread_noeof(byteswap_buf, 4, 1, input_des);
            block_size = read_neutral_s32(byteswap_buf);
            if (block_size < ((65) * 1024) || block_size > ((511) * 1024 * 1024)) {
                fprintf(stderr, "The input file is corrupted. Reason: Invalid block size in the header.\n");
                if (mode == 3) {
                    fprintf(stderr, "Recovery mode: Proceeding.\n");
                    block_size = ((511) * 1024 * 1024);
                } else {
                    return 1;
                }
            }
            bytes_read += 9;
            break;
            ;
        }
    }
    if (workers > 64 || workers < 0) {
        ;
        return 1;
    }
    if (workers <= 1) {
        struct bz3_state *state = bz3_new(block_size);
        if (state == ((void *)0)) {
            ;
            return 1;
        }
        u8 *buffer = malloc(bz3_bound(block_size));
        if (!buffer) {
            ;
            return 1;
        }
        if (mode == 1) {
            s32 read_count;
            while (!feof(input_des))
                {
                    read_count = xread(buffer, 1, block_size, input_des);
                    bytes_read += read_count;
                    if (read_count == 0)
                        break;
                    ;
                    s32 new_size = bz3_encode_block(state, buffer, read_count);
                    if (new_size == -1) {
                        ;
                        return 1;
                    }
                    write_neutral_s32(byteswap_buf, new_size);
                    xwrite(byteswap_buf, 4, 1, output_des);
                    write_neutral_s32(byteswap_buf, read_count);
                    xwrite(byteswap_buf, 4, 1, output_des);
                    xwrite(buffer, new_size, 1, output_des);
                    bytes_written += 8 + new_size;
                }
            fflush(output_des);
        } else if (mode == 0) {
            s32 new_size, old_size;
            while (!feof(input_des))
                {
                    if (!xread_eofcheck(&byteswap_buf, 1, 4, input_des))
                        continue;
                    ;
                    new_size = read_neutral_s32(byteswap_buf);
                    xread_noeof(&byteswap_buf, 1, 4, input_des);
                    old_size = read_neutral_s32(byteswap_buf);
                    if (old_size > bz3_bound(block_size) || new_size > bz3_bound(block_size)) {
                        ;
                        return 1;
                    }
                    xread_noeof(buffer, 1, new_size, input_des);
                    bytes_read += 8 + new_size;
                    if (bz3_decode_block(state, buffer, new_size, old_size) == -1) {
                        ;
                        return 1;
                    }
                    xwrite(buffer, old_size, 1, output_des);
                    bytes_written += old_size;
                }
            fflush(output_des);
        } else if (mode == 3) {
            s32 new_size, old_size;
            while (!feof(input_des))
                {
                    if (!xread_eofcheck(&byteswap_buf, 1, 4, input_des))
                        continue;
                    ;
                    new_size = read_neutral_s32(byteswap_buf);
                    xread_noeof(&byteswap_buf, 1, 4, input_des);
                    old_size = read_neutral_s32(byteswap_buf);
                    if (old_size > bz3_bound(block_size) || new_size > bz3_bound(block_size)) {
                        ;
                        return 1;
                    }
                    xread_noeof(buffer, 1, new_size, input_des);
                    bytes_read += 8 + new_size;
                    if (bz3_decode_block(state, buffer, new_size, old_size) == -1) {
                        fprintf(stderr, "Writing invalid block: %s\n", bz3_strerror(state));
                    }
                    xwrite(buffer, old_size, 1, output_des);
                    bytes_written += old_size;
                }
            fflush(output_des);
        } else if (mode == 2) {
            s32 new_size, old_size;
            while (!feof(input_des))
                {
                    if (!xread_eofcheck(&byteswap_buf, 1, 4, input_des))
                        continue;
                    ;
                    new_size = read_neutral_s32(byteswap_buf);
                    xread_noeof(&byteswap_buf, 1, 4, input_des);
                    old_size = read_neutral_s32(byteswap_buf);
                    if (old_size > bz3_bound(block_size) || new_size > bz3_bound(block_size)) {
                        ;
                        return 1;
                    }
                    xread_noeof(buffer, 1, new_size, input_des);
                    bytes_read += 8 + new_size;
                    bytes_written += old_size;
                    if (bz3_decode_block(state, buffer, new_size, old_size) == -1) {
                        ;
                        return 1;
                    }
                }
        }
        if (bz3_last_error(state) != 0 && mode != 3) {
            fprintf(stderr, "Failed to read data: %s\n", bz3_strerror(state));
            return 1;
        }
        ;
        ;
    } else {
        struct bz3_state *states[workers];
        u8 *buffers[workers];
        s32 sizes[workers];
        s32 old_sizes[workers];
        for (s32 i = 0; i < workers; i++) {
            states[i] = bz3_new(block_size);
            if (states[i] == ((void *)0)) {
                ;
                return 1;
            }
            buffers[i] = malloc(block_size + block_size / 50 + 32);
            if (!buffers[i]) {
                ;
                return 1;
            }
        }
        if (mode == 1) {
            while (!feof(input_des))
                {
                    s32 i = 0;
                    for (; i < workers; i++) {
                        size_t read_count = xread(buffers[i], 1, block_size, input_des);
                        bytes_read += read_count;
                        sizes[i] = old_sizes[i] = read_count;
                        if (read_count < block_size) {
                            i++;
                            break;
                            ;
                        }
                    }
                    bz3_encode_blocks(states, buffers, sizes, i);
                    for (s32 j = 0; j < i; j++) {
                        if (bz3_last_error(states[j]) != 0) {
                            ;
                            return 1;
                        }
                    }
                    for (s32 j = 0; j < i; j++) {
                        write_neutral_s32(byteswap_buf, sizes[j]);
                        xwrite(byteswap_buf, 4, 1, output_des);
                        write_neutral_s32(byteswap_buf, old_sizes[j]);
                        xwrite(byteswap_buf, 4, 1, output_des);
                        xwrite(buffers[j], sizes[j], 1, output_des);
                        bytes_written += 8 + sizes[j];
                    }
                }
            ;
        } else if (mode == 0) {
            while (!feof(input_des))
                {
                    s32 i = 0;
                    for (; i < workers; i++) {
                        if (!xread_eofcheck(&byteswap_buf, 1, 4, input_des))
                            break;
                        ;
                        sizes[i] = read_neutral_s32(byteswap_buf);
                        xread_noeof(&byteswap_buf, 1, 4, input_des);
                        old_sizes[i] = read_neutral_s32(byteswap_buf);
                        if (old_sizes[i] > bz3_bound(block_size) || sizes[i] > bz3_bound(block_size)) {
                            ;
                            return 1;
                        }
                        xread_noeof(buffers[i], 1, sizes[i], input_des);
                        bytes_read += 8 + sizes[i];
                    }
                    bz3_decode_blocks(states, buffers, sizes, old_sizes, i);
                    for (s32 j = 0; j < i; j++) {
                        if (bz3_last_error(states[j]) != 0) {
                            ;
                            return 1;
                        }
                    }
                    for (s32 j = 0; j < i; j++) {
                        xwrite(buffers[j], old_sizes[j], 1, output_des);
                        bytes_written += old_sizes[j];
                    }
                }
            ;
        } else if (mode == 3) {
            while (!feof(input_des))
                {
                    s32 i = 0;
                    for (; i < workers; i++) {
                        if (!xread_eofcheck(&byteswap_buf, 1, 4, input_des))
                            break;
                        ;
                        sizes[i] = read_neutral_s32(byteswap_buf);
                        xread_noeof(&byteswap_buf, 1, 4, input_des);
                        old_sizes[i] = read_neutral_s32(byteswap_buf);
                        if (old_sizes[i] > bz3_bound(block_size) || sizes[i] > bz3_bound(block_size)) {
                            ;
                            return 1;
                        }
                        xread_noeof(buffers[i], 1, sizes[i], input_des);
                        bytes_read += 8 + sizes[i];
                    }
                    bz3_decode_blocks(states, buffers, sizes, old_sizes, i);
                    for (s32 j = 0; j < i; j++) {
                        if (bz3_last_error(states[j]) != 0) {
                            fprintf(stderr, "Writing invalid block: %s\n", bz3_strerror(states[j]));
                        }
                    }
                    for (s32 j = 0; j < i; j++) {
                        xwrite(buffers[j], old_sizes[j], 1, output_des);
                        bytes_written += old_sizes[j];
                    }
                }
            ;
        } else if (mode == 2) {
            while (!feof(input_des))
                {
                    s32 i = 0;
                    for (; i < workers; i++) {
                        if (!xread_eofcheck(&byteswap_buf, 1, 4, input_des))
                            break;
                        ;
                        sizes[i] = read_neutral_s32(byteswap_buf);
                        xread_noeof(&byteswap_buf, 1, 4, input_des);
                        old_sizes[i] = read_neutral_s32(byteswap_buf);
                        if (old_sizes[i] > bz3_bound(block_size) || sizes[i] > bz3_bound(block_size)) {
                            ;
                            return 1;
                        }
                        xread_noeof(buffers[i], 1, sizes[i], input_des);
                        bytes_read += 8 + sizes[i];
                        bytes_written += old_sizes[i];
                    }
                    bz3_decode_blocks(states, buffers, sizes, old_sizes, i);
                    for (s32 j = 0; j < i; j++) {
                        if (bz3_last_error(states[j]) != 0) {
                            ;
                            return 1;
                        }
                    }
                }
        }
    }
    return 0;
}


