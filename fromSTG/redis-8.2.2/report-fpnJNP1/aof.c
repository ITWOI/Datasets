extern aofInfo * aofInfoCreate (){
    aofInfo *ai = zcalloc(sizeof(aofInfo));
    ai->start_offset = -1;
    ai->end_offset = -1;
    return ai;
}


extern void aofInfoFree (aofInfo *ai){
    (__builtin_expect(!!(ai != ((void *)0)), 1) ? (void)0 : (_serverAssert("ai != NULL", "aof_InstSlice.c", 97) , abort()));
    if (ai->file_name)
        sdsfree(ai->file_name);
    zfree(ai);
}


extern sds aofInfoFormat (sds buf, aofInfo *ai){
    sds filename_repr = ((void *)0);
    if (sdsneedsrepr(ai->file_name))
        filename_repr = sdscatrepr(sdsempty(), ai->file_name, sdslen(ai->file_name));
    sds ret = sdscatprintf(buf, "%s %s %s %lld %s %c", "file", filename_repr ? filename_repr : ai->file_name, "seq", ai->file_seq, "type", ai->file_type);
    if (ai->start_offset != -1) {
        ret = sdscatprintf(ret, " %s %lld", "startoffset", ai->start_offset);
        if (ai->end_offset != -1) {
            ret = sdscatprintf(ret, " %s %lld", "endoffset", ai->end_offset);
        }
    }
    ret = sdscatlen(ret, "\n", 1);
    sdsfree(filename_repr);
    return ret;
}


extern sds getAofManifestFileName (){
    return sdscatprintf(sdsempty(), "%s%s", server.aof_filename, ".manifest");
}


extern sds getTempAofManifestFileName (){
    return sdscatprintf(sdsempty(), "%s%s%s", "temp-", server.aof_filename, ".manifest");
}


extern sds appendAofInfoFromList (sds buf, list *aofList){
    listNode *ln;
    listIter li;
    listRewind(aofList, &li);
    while ((ln = listNext(&li)) != ((void *)0))
        {
            aofInfo *ai = (aofInfo *)ln->value;
            buf = aofInfoFormat(buf, ai);
        }
    return buf;
}


extern sds getAofManifestAsString (aofManifest *am){
    (__builtin_expect(!!(am != ((void *)0)), 1) ? (void)0 : (_serverAssert("am != NULL", "aof_InstSlice.c", 178) , abort()));
    sds buf = sdsempty();
    if (am->base_aof_info) {
        buf = aofInfoFormat(buf, am->base_aof_info);
    }
    buf = appendAofInfoFromList(buf, am->history_aof_list);
    buf = appendAofInfoFromList(buf, am->incr_aof_list);
    return buf;
}


extern int writeAofManifestFile (sds buf){
    int ret = 0;
    ssize_t nwritten;
    int len;
    sds am_name = getAofManifestFileName();
    sds am_filepath = makePath(server.aof_dirname, am_name);
    sds tmp_am_name = getTempAofManifestFileName();
    sds tmp_am_filepath = makePath(server.aof_dirname, tmp_am_name);
    int fd = open(tmp_am_filepath, 1 | 512 | 64, 420);
    if (fd == -1) {
        do {
            if (((3) & 255) < server.verbosity)
                break;
            _serverLog(3, "Can't open the AOF manifest file %s: %s", tmp_am_name, strerror((*__errno_location())));
        } while (0);
        ret = -1;
        goto cleanup;
        ;
    }
    len = sdslen(buf);
    while (len)
        {
            nwritten = write(fd, buf, len);
            if (nwritten < 0) {
                if ((*__errno_location()) == 4)
                    continue;
                ;
                do {
                    if (((3) & 255) < server.verbosity)
                        break;
                    _serverLog(3, "Error trying to write the temporary AOF manifest file %s: %s", tmp_am_name, strerror((*__errno_location())));
                } while (0);
                ret = -1;
                goto cleanup;
                ;
            }
            len -= nwritten;
            buf += nwritten;
        }
    if (fdatasync(fd) == -1) {
        do {
            if (((3) & 255) < server.verbosity)
                break;
            _serverLog(3, "Fail to fsync the temp AOF file %s: %s.", tmp_am_name, strerror((*__errno_location())));
        } while (0);
        ret = -1;
        goto cleanup;
        ;
    }
    if (rename(tmp_am_filepath, am_filepath) != 0) {
        do {
            if (((3) & 255) < server.verbosity)
                break;
            _serverLog(3, "Error trying to rename the temporary AOF manifest file %s into %s: %s", tmp_am_name, am_name, strerror((*__errno_location())));
        } while (0);
        ret = -1;
        goto cleanup;
        ;
    }
    if (fsyncFileDir(am_filepath) == -1) {
        do {
            if (((3) & 255) < server.verbosity)
                break;
            _serverLog(3, "Fail to fsync AOF directory %s: %s.", am_filepath, strerror((*__errno_location())));
        } while (0);
        ret = -1;
        goto cleanup;
        ;
    }
  cleanup:
    if (fd != -1)
        close(fd);
    sdsfree(am_name);
    sdsfree(am_filepath);
    sdsfree(tmp_am_name);
    sdsfree(tmp_am_filepath);
    return ret;
}


extern int persistAofManifest (aofManifest *am){
    if (am->dirty == 0) {
        return 0;
    }
    sds amstr = getAofManifestAsString(am);
    int ret = writeAofManifestFile(amstr);
    sdsfree(amstr);
    if (ret == 0)
        am->dirty = 0;
    return ret;
}


extern void aofUpgradePrepare (aofManifest *am){
    (__builtin_expect(!!(!aofFileExist(server.aof_filename)), 1) ? (void)0 : (_serverAssert("!aofFileExist(server.aof_filename)", "aof_InstSlice.c", 362) , abort()));
    if (dirCreateIfMissing(server.aof_dirname) == -1) {
        do {
            if (((3) & 255) < server.verbosity)
                break;
            _serverLog(3, "Can't open or create append-only dir %s: %s", server.aof_dirname, strerror((*__errno_location())));
        } while (0);
        exit(1);
    }
    if (am->base_aof_info)
        aofInfoFree(am->base_aof_info);
    aofInfo *ai = aofInfoCreate();
    ai->file_name = sdsnew(server.aof_filename);
    ai->file_seq = 1;
    ai->file_type = AOF_FILE_TYPE_BASE;
    am->base_aof_info = ai;
    am->curr_base_file_seq = 1;
    am->dirty = 1;
    if (persistAofManifest(am) != 0) {
        exit(1);
    }
    sds aof_filepath = makePath(server.aof_dirname, server.aof_filename);
    if (rename(server.aof_filename, aof_filepath) == -1) {
        do {
            if (((3) & 255) < server.verbosity)
                break;
            _serverLog(3, "Error trying to move the old AOF file %s into dir %s: %s", server.aof_filename, server.aof_dirname, strerror((*__errno_location())));
        } while (0);
        sdsfree(aof_filepath);
        exit(1);
    }
    sdsfree(aof_filepath);
    do {
        if (((2) & 255) < server.verbosity)
            break;
        _serverLog(2, "Successfully migrated an old-style AOF file (%s) into the AOF directory (%s).", server.aof_filename, server.aof_dirname);
    } while (0);
}


extern int aofFileExist (char *filename){
    sds file_path = makePath(server.aof_dirname, filename);
    int ret = fileExist(file_path);
    sdsfree(file_path);
    return ret;
}


extern struct client * createAOFClient (){
    struct client *c = createClient(((void *)0));
    c->id = ((18446744073709551615UL));
    c->flags = (1ULL << 41);
    c->replstate = 6;
    return c;
}


extern int loadSingleAppendOnlyFile (char *filename){
    struct client *fakeClient;
    struct stat sb;
    int old_aof_state = server.aof_state;
    long loops = 0;
    off_t valid_up_to = 0;
    off_t valid_before_multi = 0;
    off_t last_progress_report_size = 0;
    int ret = 0;
    sds aof_filepath = makePath(server.aof_dirname, filename);
    FILE *fp = fopen(aof_filepath, "r");
    if (fp == ((void *)0)) {
        int en = (*__errno_location());
        if (stat(aof_filepath, &sb) == 0 || (*__errno_location()) != 2) {
            do {
                if (((3) & 255) < server.verbosity)
                    break;
                _serverLog(3, "Fatal error: can't open the append log file %s for reading: %s", filename, strerror(en));
            } while (0);
            sdsfree(aof_filepath);
            return 3;
        } else {
            do {
                if (((3) & 255) < server.verbosity)
                    break;
                _serverLog(3, "The append log file %s doesn't exist: %s", filename, strerror((*__errno_location())));
            } while (0);
            sdsfree(aof_filepath);
            return 1;
        }
    }
    if (fp && fstat(fileno(fp), &sb) != -1 && sb.st_size == 0) {
        fclose(fp);
        sdsfree(aof_filepath);
        return 2;
    }
    server.aof_state = 0;
    client *old_cur_client = server.current_client;
    client *old_exec_client = server.executing_client;
    fakeClient = createAOFClient();
    server.current_client = server.executing_client = fakeClient;
    char sig[5];
    if (fread(sig, 1, 5, fp) != 5 || memcmp(sig, "REDIS", 5) != 0) {
        if (fseek(fp, 0, 0) == -1)
            goto readerr;
        ;
    } else {
        rio rdb;
        int old_style = !strcmp(filename, server.aof_filename);
        if (old_style)
            do {
                if (((2) & 255) < server.verbosity)
                    break;
                _serverLog(2, "Reading RDB preamble from AOF file...");
            } while (0);
        else
            do {
                if (((2) & 255) < server.verbosity)
                    break;
                _serverLog(2, "Reading RDB base file on AOF loading...");
            } while (0);
        if (fseek(fp, 0, 0) == -1)
            goto readerr;
        ;
        rioInitWithFile(&rdb, fp);
        if (rdbLoadRio(&rdb, (1 << 0), ((void *)0)) != 0) {
            if (old_style)
                do {
                    if (((3) & 255) < server.verbosity)
                        break;
                    _serverLog(3, "Error reading the RDB preamble of the AOF file %s, AOF loading aborted", filename);
                } while (0);
            else
                do {
                    if (((3) & 255) < server.verbosity)
                        break;
                    _serverLog(3, "Error reading the RDB base file %s, AOF loading aborted", filename);
                } while (0);
            ret = 4;
            goto cleanup;
            ;
        } else {
            loadingAbsProgress(ftello(fp));
            last_progress_report_size = ftello(fp);
            if (old_style)
                do {
                    if (((2) & 255) < server.verbosity)
                        break;
                    _serverLog(2, "Reading the remaining AOF tail...");
                } while (0);
        }
    }
    while (1)
        {
            int argc, j;
            unsigned long len;
            robj **argv;
            char buf[1024];
            sds argsds;
            struct redisCommand *cmd;
            if (!(loops++ % 1024)) {
                off_t progress_delta = ftello(fp) - last_progress_report_size;
                loadingIncrProgress(progress_delta);
                last_progress_report_size += progress_delta;
                processEventsWhileBlocked();
                processModuleLoadingProgressEvent(1);
            }
            if (fgets(buf, sizeof (buf), fp) == ((void *)0)) {
                if (feof(fp)) {
                    break;
                    ;
                } else {
                    goto readerr;
                    ;
                }
            }
            if (buf[0] == '#')
                continue;
            ;
            if (buf[0] != '*')
                goto fmterr;
            ;
            if (buf[1] == '\x00')
                goto readerr;
            ;
            argc = atoi(buf + 1);
            if (argc < 1)
                goto fmterr;
            ;
            if ((size_t)argc > (18446744073709551615UL) / sizeof(robj *))
                goto fmterr;
            ;
            argv = zmalloc(sizeof(robj *) * argc);
            fakeClient->argc = argc;
            fakeClient->argv = argv;
            fakeClient->argv_len = argc;
            for (j = 0; j < argc; j++) {
                char *readres = fgets(buf, sizeof (buf), fp);
                if (readres == ((void *)0) || buf[0] != '$') {
                    fakeClient->argc = j;
                    freeClientArgv(fakeClient);
                    if (readres == ((void *)0)) {
                        goto readerr;
                        ;
                    } else
                        goto fmterr;
                    ;
                }
                len = strtol(buf + 1, ((void *)0), 10);
                argsds = sdsnewlen(SDS_NOINIT, len);
                if (len && fread(argsds, len, 1, fp) == 0) {
                    sdsfree(argsds);
                    fakeClient->argc = j;
                    freeClientArgv(fakeClient);
                    goto readerr;
                    ;
                }
                argv[j] = createObject(0, argsds);
                if (fread(buf, 2, 1, fp) == 0) {
                    fakeClient->argc = j + 1;
                    freeClientArgv(fakeClient);
                    goto readerr;
                    ;
                }
            }
            cmd = lookupCommand(argv, argc);
            if (!cmd) {
                do {
                    if (((3) & 255) < server.verbosity)
                        break;
                    _serverLog(3, "Unknown command '%s' reading the append only file %s", (char *)argv[0]->ptr, filename);
                } while (0);
                freeClientArgv(fakeClient);
                ret = 4;
                goto cleanup;
                ;
            }
            if (cmd->proc == multiCommand)
                valid_before_multi = valid_up_to;
            fakeClient->cmd = fakeClient->lastcmd = cmd;
            if (fakeClient->flags & (1 << 3) && fakeClient->cmd->proc != execCommand) {
                queueMultiCommand(fakeClient, cmd->flags);
            } else {
                cmd->proc(fakeClient);
            }
            (__builtin_expect(!!(fakeClient->bufpos == 0 && ((fakeClient->reply)->len) == 0), 1) ? (void)0 : (_serverAssert("fakeClient->bufpos == 0 && listLength(fakeClient->reply) == 0", "aof_InstSlice.c", 780) , abort()));
            (__builtin_expect(!!((fakeClient->flags & (1 << 4)) == 0), 1) ? (void)0 : (_serverAssert("(fakeClient->flags & CLIENT_BLOCKED) == 0", "aof_InstSlice.c", 783) , abort()));
            freeClientArgv(fakeClient);
            if (server.aof_load_truncated)
                valid_up_to = ftello(fp);
            if (server.key_load_delay)
                debugDelay(server.key_load_delay);
        }
    if (fakeClient->flags & (1 << 3)) {
        do {
            if (((3) & 255) < server.verbosity)
                break;
            _serverLog(3, "Revert incomplete MULTI/EXEC transaction in AOF file %s", filename);
        } while (0);
        valid_up_to = valid_before_multi;
        goto uxeof;
        ;
    }
  loaded_ok:
    loadingIncrProgress(ftello(fp) - last_progress_report_size);
    server.aof_state = old_aof_state;
    goto cleanup;
    ;
  readerr:
    if (!feof(fp)) {
        do {
            if (((3) & 255) < server.verbosity)
                break;
            _serverLog(3, "Unrecoverable error reading the append only file %s: %s", filename, strerror((*__errno_location())));
        } while (0);
        ret = 4;
        goto cleanup;
        ;
    }
  uxeof:
    if (server.aof_load_truncated) {
        do {
            if (((3) & 255) < server.verbosity)
                break;
            _serverLog(3, "!!! Warning: short read while loading the AOF file %s!!!", filename);
        } while (0);
        do {
            if (((3) & 255) < server.verbosity)
                break;
            _serverLog(3, "!!! Truncating the AOF %s at offset %llu !!!", filename, (unsigned long long)valid_up_to);
        } while (0);
        if (valid_up_to == -1 || truncate(aof_filepath, valid_up_to) == -1) {
            if (valid_up_to == -1) {
                do {
                    if (((3) & 255) < server.verbosity)
                        break;
                    _serverLog(3, "Last valid command offset is invalid");
                } while (0);
            } else {
                do {
                    if (((3) & 255) < server.verbosity)
                        break;
                    _serverLog(3, "Error truncating the AOF file %s: %s", filename, strerror((*__errno_location())));
                } while (0);
            }
        } else {
            if (server.aof_fd != -1 && lseek(server.aof_fd, 0, 2) == -1) {
                do {
                    if (((3) & 255) < server.verbosity)
                        break;
                    _serverLog(3, "Can't seek the end of the AOF file %s: %s", filename, strerror((*__errno_location())));
                } while (0);
            } else {
                do {
                    if (((3) & 255) < server.verbosity)
                        break;
                    _serverLog(3, "AOF %s loaded anyway because aof-load-truncated is enabled", filename);
                } while (0);
                ret = 5;
                goto loaded_ok;
                ;
            }
        }
    }
    do {
        if (((3) & 255) < server.verbosity)
            break;
        _serverLog(3, "Unexpected end of file reading the append only file %s. You can: 1) Make a backup of your AOF file, then use ./redis-check-aof --fix <filename.manifest>. 2) Alternatively you can set the 'aof-load-truncated' configuration option to yes and restart the server.", filename);
    } while (0);
    ret = 4;
    goto cleanup;
    ;
  fmterr:
    do {
        if (((3) & 255) < server.verbosity)
            break;
        _serverLog(3, "Bad file format reading the append only file %s: make a backup of your AOF file, then use ./redis-check-aof --fix <filename.manifest>", filename);
    } while (0);
    ret = 4;
  cleanup:
    if (fakeClient)
        freeClient(fakeClient);
    server.current_client = old_cur_client;
    server.executing_client = old_exec_client;
    int fd = dup(fileno(fp));
    fclose(fp);
    if (fd >= 0)
        bioCreateCloseJob(fd, 0, 1);
    sdsfree(aof_filepath);
    return ret;
}


extern int loadAppendOnlyFiles (aofManifest *am){
    (__builtin_expect(!!(am != ((void *)0)), 1) ? (void)0 : (_serverAssert("am != NULL", "aof_InstSlice.c", 873) , abort()));
    int status, ret = 0;
    long long start;
    off_t total_size = 0, base_size = 0;
    sds aof_name;
    int total_num, aof_num = 0, last_file;
    if (fileExist(server.aof_filename)) {
        if (!dirExists(server.aof_dirname) || (am->base_aof_info == ((void *)0) && ((am->incr_aof_list)->len) == 0) || (am->base_aof_info != ((void *)0) && ((am->incr_aof_list)->len) == 0 && !strcmp(am->base_aof_info->file_name, server.aof_filename) && !aofFileExist(server.aof_filename))) {
            aofUpgradePrepare(am);
        }
    }
    if (am->base_aof_info == ((void *)0) && ((am->incr_aof_list)->len) == 0) {
        return 1;
    }
    total_num = getBaseAndIncrAppendOnlyFilesNum(am);
    (__builtin_expect(!!(total_num > 0), 1) ? (void)0 : (_serverAssert("total_num > 0", "aof_InstSlice.c", 901) , abort()));
    total_size = getBaseAndIncrAppendOnlyFilesSize(am, &status);
    if (status != 0) {
        if (status == 1)
            status = 4;
        return status;
    } else if (total_size == 0) {
        return 2;
    }
    startLoading(total_size, (1 << 0), 0);
    if (am->base_aof_info) {
        (__builtin_expect(!!(am->base_aof_info->file_type == AOF_FILE_TYPE_BASE), 1) ? (void)0 : (_serverAssert("am->base_aof_info->file_type == AOF_FILE_TYPE_BASE", "aof_InstSlice.c", 919) , abort()));
        aof_name = (char *)am->base_aof_info->file_name;
        updateLoadingFileName(aof_name);
        base_size = getAppendOnlyFileSize(aof_name, ((void *)0));
        last_file = ++aof_num == total_num;
        start = ustime();
        ret = loadSingleAppendOnlyFile(aof_name);
        if (ret == 0 || (ret == 5 && last_file)) {
            do {
                if (((2) & 255) < server.verbosity)
                    break;
                _serverLog(2, "DB loaded from base file %s: %.3f seconds", aof_name, (float)(ustime() - start) / 1000000);
            } while (0);
        }
        if (ret == 5 && !last_file) {
            ret = 4;
            do {
                if (((3) & 255) < server.verbosity)
                    break;
                _serverLog(3, "Fatal error: the truncated file is not the last file");
            } while (0);
        }
        if (ret == 3 || ret == 4) {
            goto cleanup;
            ;
        }
    }
    if (((am->incr_aof_list)->len)) {
        listNode *ln;
        listIter li;
        listRewind(am->incr_aof_list, &li);
        while ((ln = listNext(&li)) != ((void *)0))
            {
                aofInfo *ai = (aofInfo *)ln->value;
                (__builtin_expect(!!(ai->file_type == AOF_FILE_TYPE_INCR), 1) ? (void)0 : (_serverAssert("ai->file_type == AOF_FILE_TYPE_INCR", "aof_InstSlice.c", 951) , abort()));
                aof_name = (char *)ai->file_name;
                updateLoadingFileName(aof_name);
                last_file = ++aof_num == total_num;
                start = ustime();
                ret = loadSingleAppendOnlyFile(aof_name);
                if (ret == 0 || (ret == 5 && last_file)) {
                    do {
                        if (((2) & 255) < server.verbosity)
                            break;
                        _serverLog(2, "DB loaded from incr file %s: %.3f seconds", aof_name, (float)(ustime() - start) / 1000000);
                    } while (0);
                }
                if (ret == 2)
                    ret = 0;
                if (ret == 5 && !last_file) {
                    ret = 4;
                    do {
                        if (((3) & 255) < server.verbosity)
                            break;
                        _serverLog(3, "Fatal error: the truncated file is not the last file");
                    } while (0);
                }
                if (ret == 3 || ret == 4) {
                    goto cleanup;
                    ;
                }
            }
    }
    server.aof_current_size = total_size;
    server.aof_rewrite_base_size = base_size;
  cleanup:
    stopLoading(ret == 0 || ret == 5);
    return ret;
}


extern off_t getAppendOnlyFileSize (sds filename, int *status){
    struct stat sb;
    off_t size;
    mstime_t latency;
    sds aof_filepath = makePath(server.aof_dirname, filename);
    if (server.latency_monitor_threshold) {
        latency = mstime();
    } else {
        latency = 0;
    }
    ;
    ;
    if (stat(aof_filepath, &sb) == -1) {
        if (status)
            *status = (*__errno_location()) == 2 ? 1 : 3;
        do {
            if (((3) & 255) < server.verbosity)
                break;
            _serverLog(3, "Unable to obtain the AOF file %s length. stat: %s", filename, strerror((*__errno_location())));
        } while (0);
        size = 0;
    } else {
        if (status)
            *status = 0;
        size = sb.st_size;
    }
    if (server.latency_monitor_threshold) {
        latency = mstime() - latency;
    }
    ;
    ;
    if (server.latency_monitor_threshold && (latency) >= server.latency_monitor_threshold)
        latencyAddSample(("aof-fstat"), (latency));
    ;
    ;
    sdsfree(aof_filepath);
    return size;
}


extern off_t getBaseAndIncrAppendOnlyFilesSize (aofManifest *am, int *status){
    off_t size = 0;
    listNode *ln;
    listIter li;
    if (am->base_aof_info) {
        (__builtin_expect(!!(am->base_aof_info->file_type == AOF_FILE_TYPE_BASE), 1) ? (void)0 : (_serverAssert("am->base_aof_info->file_type == AOF_FILE_TYPE_BASE", "aof_InstSlice.c", 1125) , abort()));
        size += getAppendOnlyFileSize(am->base_aof_info->file_name, status);
        if (*status != 0)
            return 0;
    }
    listRewind(am->incr_aof_list, &li);
    while ((ln = listNext(&li)) != ((void *)0))
        {
            aofInfo *ai = (aofInfo *)ln->value;
            (__builtin_expect(!!(ai->file_type == AOF_FILE_TYPE_INCR), 1) ? (void)0 : (_serverAssert("ai->file_type == AOF_FILE_TYPE_INCR", "aof_InstSlice.c", 1134) , abort()));
            size += getAppendOnlyFileSize(ai->file_name, status);
            if (*status != 0)
                return 0;
        }
    return size;
}


extern int getBaseAndIncrAppendOnlyFilesNum (aofManifest *am){
    int num = 0;
    if (am->base_aof_info)
        num++;
    if (am->incr_aof_list)
        num += ((am->incr_aof_list)->len);
    return num;
}


