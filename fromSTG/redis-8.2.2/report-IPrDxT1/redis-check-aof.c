extern int consumeNewline (char *buf){
    if (strncmp(buf, "\r\n", 2) != 0) {
        ;
        return 0;
    }
    line += 1;
    return 1;
}


extern int readLong (FILE *fp, char prefix, long *target){
    char buf[128], *eptr;
    epos = ftello(fp);
    if (fgets(buf, sizeof (buf), fp) == ((void *)0)) {
        return 0;
    }
    if (buf[0] != prefix) {
        ;
        return 0;
    }
    *target = strtol(buf + 1, &eptr, 10);
    return consumeNewline(eptr);
}


extern int readBytes (FILE *fp, char *target, long length){
    long real;
    epos = ftello(fp);
    real = fread(target, 1, length, fp);
    if (real != length) {
        ;
        return 0;
    }
    return 1;
}


extern int readString (FILE *fp, char **target){
    long len;
    *target = ((void *)0);
    if (!readLong(fp, '$', &len)) {
        return 0;
    }
    if (len < 0 || len > 9223372036854775807L - 2) {
        ;
        return 0;
    }
    len += 2;
    *target = (char *)zmalloc(len);
    if (!readBytes(fp, *target, len)) {
        ;
        *target = ((void *)0);
        return 0;
    }
    if (!consumeNewline(*target + len - 2)) {
        ;
        *target = ((void *)0);
        return 0;
    }
    (*target)[len - 2] = '\x00';
    return 1;
}


extern int readArgc (FILE *fp, long *target){
    return readLong(fp, '*', target);
}


extern int processRESP (FILE *fp, char *filename, int *out_multi){
    long argc;
    char *str;
    if (!readArgc(fp, &argc))
        return 0;
    for (int i = 0; i < argc; i++) {
        if (!readString(fp, &str))
            return 0;
        if (i == 0) {
            if (strcasecmp(str, "multi") == 0) {
                if ((*out_multi)++) {
                    ;
                    ;
                    return 0;
                }
            } else if (strcasecmp(str, "exec") == 0) {
                if (--(*out_multi)) {
                    ;
                    ;
                    return 0;
                }
            }
        }
        ;
    }
    return 1;
}


extern int processAnnotations (FILE *fp, char *filename, int last_file){
    char buf[1024];
    epos = ftello(fp);
    if (fgets(buf, sizeof (buf), fp) == ((void *)0)) {
        ;
        ;
    }
    if (to_timestamp && strncmp(buf, "#TS:", 4) == 0) {
        char *endptr;
        (*__errno_location()) = 0;
        time_t ts = strtol(buf + 4, &endptr, 10);
        if ((*__errno_location()) != 0 || *endptr != '\r') {
            ;
            ;
        }
        if (ts <= to_timestamp)
            return 1;
        if (epos == 0) {
            ;
            ;
        }
        if (!last_file) {
            ;
            ;
            ;
        }
        if (ftruncate(fileno(fp), epos) == -1) {
            ;
            ;
        } else {
            return 0;
        }
    }
    return 1;
}


extern int checkSingleAof (char *aof_filename, char *aof_filepath, int last_file, int fix, int preamble){
    off_t pos = 0, diff;
    int multi = 0;
    char buf[2];
    FILE *fp = fopen(aof_filepath, "r+");
    if (fp == ((void *)0)) {
        ;
        ;
    }
    struct stat sb;
    if (fstat(fileno(fp), &sb) == -1) {
        ;
        ;
        ;
    }
    off_t size = sb.st_size;
    if (size == 0) {
        ;
        return 1;
    }
    if (preamble) {
        char *argv[2] = {((void *)0), aof_filepath};
        if (redis_check_rdb_main(2, argv, fp) == -1) {
            ;
            ;
        } else {
            ;
        }
    }
    while (1)
        {
            if (!multi)
                pos = ftello(fp);
            if (fgets(buf, sizeof (buf), fp) == ((void *)0)) {
                if (feof(fp)) {
                    break;
                }
                ;
                ;
            }
            if (fseek(fp, -1, 1) == -1) {
                ;
                ;
            }
            if (buf[0] == '#') {
                if (!processAnnotations(fp, aof_filepath, last_file)) {
                    ;
                    return 3;
                }
            } else if (buf[0] == '*') {
                if (!processRESP(fp, aof_filepath, &multi))
                    break;
                ;
            } else {
                ;
            }
        }
    diff = size - pos;
    if (diff == 0 && to_timestamp) {
        ;
        ;
        return 0;
    }
    ;
    if (diff > 0) {
        if (fix) {
            if (!last_file) {
                ;
                ;
            }
            char buf[2];
            ;
            ;
            if (fgets(buf, sizeof (buf), stdin) == ((void *)0) || strncasecmp(buf, "y", 1) != 0) {
                ;
                ;
            }
            if (ftruncate(fileno(fp), pos) == -1) {
                ;
                ;
            } else {
                ;
                return 2;
            }
        } else {
            ;
        }
    }
    ;
    return 0;
}


extern int fileIsRDB (char *filepath){
    FILE *fp = fopen(filepath, "r");
    if (fp == ((void *)0)) {
        ;
        ;
    }
    struct stat sb;
    if (fstat(fileno(fp), &sb) == -1) {
        ;
        ;
        ;
    }
    off_t size = sb.st_size;
    if (size == 0) {
        ;
        return 0;
    }
    if (size >= 8) {
        char sig[5];
        int rdb_file = fread(sig, sizeof (sig), 1, fp) == 1 && memcmp(sig, "REDIS", sizeof (sig)) == 0;
        if (rdb_file) {
            ;
            return 1;
        }
    }
    ;
    return 0;
}


extern int fileIsManifest (char *filepath){
    int is_manifest = 0;
    FILE *fp = fopen(filepath, "r");
    if (fp == ((void *)0)) {
        ;
        ;
    }
    struct stat sb;
    if (fstat(fileno(fp), &sb) == -1) {
        ;
        ;
        ;
    }
    off_t size = sb.st_size;
    if (size == 0) {
        ;
        return 0;
    }
    char buf[1025];
    while (1)
        {
            if (fgets(buf, 1024 + 1, fp) == ((void *)0)) {
                if (feof(fp)) {
                    break;
                } else {
                    ;
                }
            }
            if (buf[0] == '#') {
                continue;
            } else if (!memcmp(buf, "file", strlen("file"))) {
                is_manifest = 1;
            } else {
                ;
            }
        }
    ;
    return is_manifest;
}


extern input_file_type getInputFileType (char *filepath){
    if (fileIsManifest(filepath)) {
        return AOF_MULTI_PART;
    } else if (fileIsRDB(filepath)) {
        return AOF_RDB_PREAMBLE;
    } else {
        return AOF_RESP;
    }
}


extern void checkMultiPartAof (char *dirpath, char *manifest_filepath, int fix){
    int total_num = 0, aof_num = 0, last_file;
    int ret;
    ;
    aofManifest *am = aofLoadManifestFromFile(manifest_filepath);
    if (am->base_aof_info)
        total_num++;
    if (am->incr_aof_list)
        total_num += ((am->incr_aof_list)->len);
    if (am->base_aof_info) {
        sds aof_filename = am->base_aof_info->file_name;
        sds aof_filepath = makePath(dirpath, aof_filename);
        last_file = ++aof_num == total_num;
        int aof_preable = fileIsRDB(aof_filepath);
        ;
        ret = checkSingleAof(aof_filename, aof_filepath, last_file, fix, aof_preable);
        ;
        ;
    }
    if (((am->incr_aof_list)->len)) {
        listNode *ln;
        listIter li;
        ;
        ;
        while ((ln = listNext(&li)) != ((void *)0))
            {
                aofInfo *ai = (aofInfo *)ln->value;
                sds aof_filename = (char *)ai->file_name;
                sds aof_filepath = makePath(dirpath, aof_filename);
                last_file = ++aof_num == total_num;
                ret = checkSingleAof(aof_filename, aof_filepath, last_file, fix, 0);
                ;
                ;
            }
    }
    ;
    ;
}


extern void checkOldStyleAof (char *filepath, int fix, int preamble){
    ;
    int ret = checkSingleAof(filepath, filepath, 1, fix, preamble);
    ;
}


extern int redis_check_aof_main (int argc, char **argv){
    char *filepath;
    char temp_filepath[4097];
    char *dirpath;
    int fix = 0;
    if (argc < 2) {
        goto invalid_args;
    } else if (argc == 2) {
        if (!strcmp(argv[1], "-v") || !strcmp(argv[1], "--version")) {
            sds version;
            ;
            ;
            ;
        }
        filepath = argv[1];
    } else if (argc == 3) {
        if (!strcmp(argv[1], "--fix")) {
            filepath = argv[2];
            fix = 1;
        } else {
            ;
        }
    } else if (argc == 4) {
        if (!strcmp(argv[1], "--truncate-to-timestamp")) {
            char *endptr;
            (*__errno_location()) = 0;
            to_timestamp = strtol(argv[2], &endptr, 10);
            if ((*__errno_location()) != 0 || *endptr != '\x00') {
                ;
                ;
            }
            filepath = argv[3];
        } else {
            ;
        }
    } else {
        ;
    }
    if (strlen(filepath) > 4096) {
        ;
        goto invalid_args;
    }
    memcpy(temp_filepath, filepath, strlen(filepath) + 1);
    dirpath = dirname(temp_filepath);
    input_file_type type = getInputFileType(filepath);
    switch (type) {
      case AOF_MULTI_PART:
        checkMultiPartAof(dirpath, filepath, fix);
        break;
      case AOF_RESP:
        checkOldStyleAof(filepath, fix, 0);
        break;
      case AOF_RDB_PREAMBLE:
        checkOldStyleAof(filepath, fix, 1);
        break;
    }
    ;
  invalid_args:
    ;
    ;
}


