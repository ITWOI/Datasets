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


static void close_out_file (FILE *des){
    if (des) {
        int outfd = fileno(des);
        if (fflush(des)) {
            ;
            ;
        }
        while (1)
            {
                int status = fsync(outfd);
                if (status == -1) {
                    if ((*__errno_location()) == 22)
                        break;
                    ;
                    if ((*__errno_location()) == 4)
                        continue;
                    ;
                    ;
                    ;
                }
                break;
                ;
            }
        if (des != stdout && fclose(des)) {
            ;
            ;
        }
    }
}


static int process (FILE *input_des, FILE *output_des, int mode, int block_size, int workers, int verbose, char *file_name){
    uint64_t bytes_read = 0, bytes_written = 0;
    if ((mode == 1 && isatty(fileno(output_des))) || ((mode == 0 || mode == 2 || mode == 3) && isatty(fileno(input_des)))) {
        fprintf(stderr, "Refusing to read/write binary data from/to the terminal.\n");
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
                fprintf(stderr, "Invalid signature.\n");
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
        fprintf(stderr, "Number of workers must be between 0 and 64.\n");
        return 1;
    }
    if (workers <= 1) {
        struct bz3_state *state = bz3_new(block_size);
        if (state == ((void *)0)) {
            fprintf(stderr, "Failed to create a block encoder state.\n");
            return 1;
        }
        u8 *buffer = malloc(bz3_bound(block_size));
        if (!buffer) {
            fprintf(stderr, "Failed to allocate memory.\n");
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
                        fprintf(stderr, "Failed to encode a block: %s\n", bz3_strerror(state));
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
                        fprintf(stderr, "Failed to decode a block: Inconsistent headers.\n");
                        return 1;
                    }
                    xread_noeof(buffer, 1, new_size, input_des);
                    bytes_read += 8 + new_size;
                    if (bz3_decode_block(state, buffer, new_size, old_size) == -1) {
                        fprintf(stderr, "Failed to decode a block: %s\n", bz3_strerror(state));
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
                        fprintf(stderr, "Failed to decode a block: Inconsistent headers.\n");
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
                        fprintf(stderr, "Failed to decode a block: Inconsistent headers.\n");
                        return 1;
                    }
                    xread_noeof(buffer, 1, new_size, input_des);
                    bytes_read += 8 + new_size;
                    bytes_written += old_size;
                    if (bz3_decode_block(state, buffer, new_size, old_size) == -1) {
                        fprintf(stderr, "Failed to decode a block: %s\n", bz3_strerror(state));
                        return 1;
                    }
                }
        }
        if (bz3_last_error(state) != 0 && mode != 3) {
            fprintf(stderr, "Failed to read data: %s\n", bz3_strerror(state));
            return 1;
        }
        free(buffer);
        bz3_free(state);
    } else {
        struct bz3_state *states[workers];
        u8 *buffers[workers];
        s32 sizes[workers];
        s32 old_sizes[workers];
        for (s32 i = 0; i < workers; i++) {
            states[i] = bz3_new(block_size);
            if (states[i] == ((void *)0)) {
                fprintf(stderr, "Failed to create a block encoder state.\n");
                return 1;
            }
            buffers[i] = malloc(block_size + block_size / 50 + 32);
            if (!buffers[i]) {
                fprintf(stderr, "Failed to allocate memory.\n");
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
                            fprintf(stderr, "Failed to encode data: %s\n", bz3_strerror(states[j]));
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
            fflush(output_des);
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
                            fprintf(stderr, "Failed to decode a block: Inconsistent headers.\n");
                            return 1;
                        }
                        xread_noeof(buffers[i], 1, sizes[i], input_des);
                        bytes_read += 8 + sizes[i];
                    }
                    bz3_decode_blocks(states, buffers, sizes, old_sizes, i);
                    for (s32 j = 0; j < i; j++) {
                        if (bz3_last_error(states[j]) != 0) {
                            fprintf(stderr, "Failed to decode data: %s\n", bz3_strerror(states[j]));
                            return 1;
                        }
                    }
                    for (s32 j = 0; j < i; j++) {
                        xwrite(buffers[j], old_sizes[j], 1, output_des);
                        bytes_written += old_sizes[j];
                    }
                }
            fflush(output_des);
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
                            fprintf(stderr, "Failed to decode a block: Inconsistent headers.\n");
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
            fflush(output_des);
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
                            fprintf(stderr, "Failed to decode a block: Inconsistent headers.\n");
                            return 1;
                        }
                        xread_noeof(buffers[i], 1, sizes[i], input_des);
                        bytes_read += 8 + sizes[i];
                        bytes_written += old_sizes[i];
                    }
                    bz3_decode_blocks(states, buffers, sizes, old_sizes, i);
                    for (s32 j = 0; j < i; j++) {
                        if (bz3_last_error(states[j]) != 0) {
                            fprintf(stderr, "Failed to decode data: %s\n", bz3_strerror(states[j]));
                            return 1;
                        }
                    }
                }
        }
        for (s32 i = 0; i < workers; i++) {
            free(buffers[i]);
            bz3_free(states[i]);
        }
    }
    if (verbose) {
        if (file_name)
            fprintf(stderr, " %s:", file_name);
        if (mode == 1) {
            fprintf(stderr, "\t%lu -> %lu bytes, %.2f%%, %.2f bpb\n", bytes_read, bytes_written, (double)bytes_written * 100. / bytes_read, (double)bytes_written * 8. / bytes_read);
        } else if (mode == 0) {
            fprintf(stderr, "\t%lu -> %lu bytes, %.2f%%, %.2f bpb\n", bytes_read, bytes_written, (double)bytes_read * 100. / bytes_written, (double)bytes_read * 8. / bytes_written);
        } else
            fprintf(stderr, "\tOK, %lu -> %lu bytes, %.2f%%, %.2f bpb\n", bytes_read, bytes_written, (double)bytes_read * 100. / bytes_written, (double)bytes_read * 8. / bytes_written);
    }
    return 0;
}


static int is_dir (const char *path){
    struct stat sb;
    if (stat(path, &sb) == 0 && ((((sb.st_mode)) & 61440) == (16384)))
        return 1;
    return 0;
}


static int is_numeric (const char *str){
    for (; *str; str++)
        if (!((*__ctype_b_loc())[(int)((*str))] & (unsigned short)_ISdigit))
            return 0;
    return 1;
}


static FILE * open_output (char *output, int force){
    FILE *output_des = ((void *)0);
    if (output != ((void *)0)) {
        if (is_dir(output)) {
            ;
            ;
        }
        if (access(output, 0) == 0) {
            if (!force) {
                ;
                ;
            }
        }
        output_des = fopen(output, "wb");
        if (output_des == ((void *)0)) {
            ;
            ;
        }
    } else {
        output_des = stdout;
    }
    return output_des;
}


static FILE * open_input (char *input){
    FILE *input_des = ((void *)0);
    if (input != ((void *)0)) {
        if (is_dir(input)) {
            ;
            ;
        }
        input_des = fopen(input, "rb");
        if (input_des == ((void *)0)) {
            ;
            ;
        }
    } else {
        input_des = stdin;
    }
    return input_des;
}


extern int main (int argc, char *argv[]){
    int mode = 1;
    char *input = ((void *)0), *output = ((void *)0);
    char *f1 = ((void *)0), *f2 = ((void *)0);
    int force = 0;
    int force_stdstreams = 0, workers = 0, batch = 0, verbose = 0;
    u32 block_size = ((16) * 1024 * 1024);
    const char *short_options = "Bb:cdefhj:krtvVz";
    static struct option long_options[] = {{"encode", 0, 0, 'e'}, {"decode", 0, 0, 'd'}, {"test", 0, 0, 't'}, {"stdout", 0, 0, 'c'}, {"force", 0, 0, 'f'}, {"recover", 0, 0, 'r'}, {"help", 0, 0, 'h'}, {"keep", 0, 0, 'k'}, {"version", 0, 0, 'V'}, {"verbose", 0, 0, 'v'}, {"block", 1, 0, 'b'}, {"batch", 0, 0, 'B'}, {"jobs", 1, 0, 'j'}, {0, 0, 0, 0}};
    while (1)
        {
            int option_index = 0;
            int c = getopt_long(argc, argv, short_options, long_options, &option_index);
            if (c == -1)
                break;
            ;
            switch (c) {
              case '?':
                ;
                return 1;
              case 'e':
              case 'z':
                mode = 1;
                break;
                ;
              case 'd':
                mode = 0;
                break;
                ;
              case 'r':
                mode = 3;
                break;
                ;
              case 't':
                mode = 2;
                break;
                ;
              case 'c':
                force_stdstreams = 1;
                break;
                ;
              case 'f':
                force = 1;
                break;
                ;
              case 'k':
                break;
                ;
              case 'h':
                ;
                return 0;
              case 'V':
                ;
                return 0;
              case 'B':
                batch = 1;
                break;
                ;
              case 'v':
                verbose = 1;
                break;
                ;
              case 'b':
                if (!is_numeric(optarg)) {
                    ;
                    return 1;
                }
                block_size = ((atoi(optarg)) * 1024 * 1024);
                break;
              case 'j':
                if (!is_numeric(optarg)) {
                    ;
                    return 1;
                }
                workers = atoi(optarg);
                break;
            }
        }
    if (block_size < ((65) * 1024) || block_size > ((511) * 1024 * 1024)) {
        ;
        return 1;
    }
    if (batch) {
        switch (mode) {
          case 1:
            while (optind < argc)
                {
                    char *arg = argv[optind++];
                    FILE *input_des = open_input(arg);
                    char *output_name;
                    if (force_stdstreams) {
                        output_name = ((void *)0);
                    } else {
                        output_name = malloc(strlen(arg) + 5);
                        strcpy(output_name, arg);
                        strcat(output_name, ".bz3");
                    }
                    FILE *output_des = open_output(output_name, force);
                    process(input_des, output_des, mode, block_size, workers, verbose, arg);
                    fclose(input_des);
                    close_out_file(output_des);
                    if (!force_stdstreams)
                        free(output_name);
                }
            break;
          case 3:
          case 0:
            while (optind < argc)
                {
                    char *arg = argv[optind++];
                    FILE *input_des = open_input(arg);
                    char *output_name;
                    if (force_stdstreams) {
                        output_name = ((void *)0);
                    } else {
                        output_name = malloc(strlen(arg) + 1);
                        strcpy(output_name, arg);
                        if (strlen(output_name) > 4 && !strcmp(output_name + strlen(output_name) - 4, ".bz3")) {
                            output_name[strlen(output_name) - 4] = 0;
                        } else {
                            fprintf(stderr, "Warning: file %s has an unknown extension, skipping.\n", arg);
                            return 1;
                        }
                    }
                    FILE *output_des = open_output(output_name, force);
                    process(input_des, output_des, mode, block_size, workers, verbose, arg);
                    fclose(input_des);
                    close_out_file(output_des);
                    if (!force_stdstreams)
                        free(output_name);
                }
            break;
          case 2:
            while (optind < argc)
                {
                    char *arg = argv[optind++];
                    FILE *input_des = open_input(arg);
                    process(input_des, ((void *)0), mode, block_size, workers, verbose, arg);
                    fclose(input_des);
                }
            break;
        }
        return 0;
    }
    while (optind < argc)
        {
            char *arg = argv[optind++];
            if (f1 != ((void *)0) && f2 != ((void *)0)) {
                ;
                return 1;
            }
            if (f1 == ((void *)0)) {
                f1 = arg;
            } else
                f2 = arg;
        }
    if (f1 == ((void *)0) && f2 == ((void *)0)) {
        input = ((void *)0) , output = ((void *)0);
    } else if (mode == 2) {
        input = f1;
    } else {
        if (mode == 1) {
            if (f2 == ((void *)0)) {
                input = f1;
                if (force_stdstreams) {
                    output = ((void *)0);
                } else {
                    output = malloc(strlen(f1) + 5);
                    strcpy(output, f1);
                    strcat(output, ".bz3");
                }
            } else {
                input = f1;
                output = f2;
            }
        } else if (mode == 0 || mode == 3) {
            if (f2 == ((void *)0)) {
                input = f1;
                if (force_stdstreams) {
                    output = ((void *)0);
                } else {
                    output = malloc(strlen(f1) + 1);
                    strcpy(output, f1);
                    if (strlen(output) > 4 && !strcmp(output + strlen(output) - 4, ".bz3")) {
                        output[strlen(output) - 4] = 0;
                    } else {
                        ;
                    }
                }
            } else {
                input = f1;
                output = f2;
            }
        }
    }
    FILE *input_des = ((void *)0), *output_des = ((void *)0);
    output_des = mode != 2 ? open_output(output, force) : ((void *)0);
    input_des = open_input(input);
    if (output != f2)
        free(output);
    int r = process(input_des, output_des, mode, block_size, workers, verbose, input);
    fclose(input_des);
    close_out_file(output_des);
    if (fclose(stdout)) {
        ;
        return 1;
    }
    return r;
}


