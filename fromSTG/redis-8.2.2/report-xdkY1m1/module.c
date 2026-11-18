extern void poolAllocRelease (RedisModuleCtx *ctx){
    RedisModulePoolAllocBlock *head, *next;
    ctx->pa_head = ((void *)0);
}


extern client * moduleAllocTempClient (){
    client *c = ((void *)0);
    if (moduleTempClientCount > 0) {
        c = moduleTempClients[--moduleTempClientCount];
        if (moduleTempClientCount < moduleTempClientMinCount)
            moduleTempClientMinCount = moduleTempClientCount;
    } else {
        c = createClient(((void *)0));
        c->flags |= (1 << 27);
        c->user = ((void *)0);
    }
    return c;
}


static void freeRedisModuleAsyncRMCallPromise (RedisModuleAsyncRMCallPromise *promise){
    if (--promise->ref_count > 0) {
        return;
    }
    (__builtin_expect(!!(!promise->c), 1) ? (void)0 : (_serverAssert("!promise->c", "module_InstSlice.c", 609) , abort()));
    ;
}


extern void moduleReleaseTempClient (client *c){
    if (moduleTempClientCount == moduleTempClientCap) {
        moduleTempClientCap = moduleTempClientCap ? moduleTempClientCap * 2 : 32;
        moduleTempClients = zrealloc(moduleTempClients, sizeof (c) * moduleTempClientCap);
    }
    ;
    ;
    c->reply_bytes = 0;
    c->duration = 0;
    ;
    c->bufpos = 0;
    c->flags = (1 << 27);
    c->user = ((void *)0);
    c->cmd = c->lastcmd = c->realcmd = c->iolookedcmd = ((void *)0);
    if (c->bstate.async_rm_call_handle) {
        RedisModuleAsyncRMCallPromise *promise = c->bstate.async_rm_call_handle;
        promise->c = ((void *)0);
        freeRedisModuleAsyncRMCallPromise(promise);
        c->bstate.async_rm_call_handle = ((void *)0);
    }
    moduleTempClients[moduleTempClientCount++] = c;
}


static void moduleFreeKeyIterator (RedisModuleKey *key){
    (__builtin_expect(!!(key->iter != ((void *)0)), 1) ? (void)0 : (_serverAssert("key->iter != NULL", "module_InstSlice.c", 652) , abort()));
    switch (key->kv->type) {
      case 1:
        ;
        break;
      case 6:
        ;
        ;
        break;
        ;
    }
    key->iter = ((void *)0);
}


extern void moduleFreeContext (RedisModuleCtx *ctx){
    autoMemoryCollect(ctx);
    poolAllocRelease(ctx);
    if (ctx->postponed_arrays) {
        ;
        ctx->postponed_arrays_count = 0;
        do {
            if (((3) & 255) < server.verbosity)
                break;
            _serverLog(3, "API misuse detected in module %s: RedisModule_ReplyWith*(REDISMODULE_POSTPONED_LEN) not matched by the same number of RedisModule_SetReply*Len() calls.", ctx->module->name);
        } while (0);
    }
    if (ctx->flags & (1 << 6)) {
        moduleReleaseTempClient(ctx->client);
    } else {
        ;
    }
}


extern void moduleCreateContext (RedisModuleCtx *out_ctx, RedisModule *module, int ctx_flags){
    memset(out_ctx, 0, sizeof(RedisModuleCtx));
    out_ctx->getapifuncptr = (void *)(unsigned long)&RM_GetApi;
    out_ctx->module = module;
    out_ctx->flags = ctx_flags;
    if (ctx_flags & (1 << 6)) {
        out_ctx->client = moduleAllocTempClient();
    } else if (ctx_flags & (1 << 7))
        out_ctx->client = createClient(((void *)0));
    if (server.loading) {
        out_ctx->next_yield_time = getMonotonicUs() + 1000000 / server.hz;
    } else
        out_ctx->next_yield_time = getMonotonicUs() + server.busy_reply_threshold * 1000;
}


extern int autoMemoryFreed (RedisModuleCtx *ctx, int type, void *ptr){
    if (!(ctx->flags & (1 << 0)))
        return 0;
    int count = (ctx->amqueue_used + 1) / 2;
    for (int j = 0; j < count; j++) {
        for (int side = 0; side < 2; side++) {
            int i = (side == 0) ? (ctx->amqueue_used - 1 - j) : j;
            if (ctx->amqueue[i].type == type && ctx->amqueue[i].ptr == ptr) {
                ctx->amqueue[i].type = 3;
                ctx->amqueue_used--;
                return 1;
            }
        }
    }
    return 0;
}


extern void autoMemoryCollect (RedisModuleCtx *ctx){
    if (!(ctx->flags & (1 << 0)))
        return;
    ctx->flags &= ~(1 << 0);
    int j;
    for (j = 0; j < ctx->amqueue_used; j++) {
        void *ptr = ctx->amqueue[j].ptr;
        switch (ctx->amqueue[j].type) {
          case 1:
            ;
            break;
          case 2:
            RM_FreeCallReply(ptr);
            break;
            ;
          case 0:
            RM_CloseKey(ptr);
            break;
            ;
          case 4:
            RM_FreeDict(((void *)0), ptr);
            break;
            ;
          case 5:
            RM_FreeServerInfo(((void *)0), ptr);
            break;
            ;
          case 6:
            RM_ConfigIteratorRelease(((void *)0), ptr);
            break;
            ;
        }
    }
    ctx->flags |= (1 << 0);
    ;
    ctx->amqueue = ((void *)0);
    ctx->amqueue_len = 0;
    ctx->amqueue_used = 0;
}


extern int modulePopulateClientInfoStructure (void *ci, client *client, int structver){
    if (structver != 1)
        return 1;
    RedisModuleClientInfoV1 *ci1 = ci;
    memset(ci1, 0, sizeof (*ci1));
    ci1->version = structver;
    if (client->flags & (1 << 3))
        ci1->flags |= (1 << 5);
    if (client->flags & (1 << 18))
        ci1->flags |= (1 << 1);
    if (client->flags & (1 << 11))
        ci1->flags |= (1 << 4);
    if (client->flags & (1ULL << 31))
        ci1->flags |= (1 << 3);
    if (client->flags & (1 << 4))
        ci1->flags |= (1 << 2);
    if (client->conn->type == connectionTypeTls())
        ci1->flags |= (1 << 0);
    int port;
    ;
    ci1->port = port;
    ci1->db = client->db->id;
    ci1->id = client->id;
    return 0;
}


extern int modulePopulateReplicationInfoStructure (void *ri, int structver){
    if (structver != 1)
        return 1;
    RedisModuleReplicationInfoV1 *ri1 = ri;
    memset(ri1, 0, sizeof (*ri1));
    ri1->version = structver;
    ri1->master = server.masterhost == ((void *)0);
    ri1->masterhost = server.masterhost ? server.masterhost : "";
    ri1->masterport = server.masterport;
    ri1->replid1 = server.replid;
    ri1->replid2 = server.replid2;
    ri1->repl1_offset = server.master_repl_offset;
    ri1->repl2_offset = server.second_replid_offset;
    return 0;
}


static void moduleInitKey (RedisModuleKey *kp, RedisModuleCtx *ctx, robj *keyname, kvobj *kv, int mode){
    kp->ctx = ctx;
    kp->db = ctx->client->db;
    kp->key = keyname;
    ;
    kp->kv = kv;
    kp->iter = ((void *)0);
    kp->mode = mode;
    if (kp->kv)
        moduleInitKeyTypeSpecific(kp);
}


static void moduleInitKeyTypeSpecific (RedisModuleKey *key){
    switch (key->kv->type) {
      case 3:
        zsetKeyReset(key);
        break;
        ;
      case 6:
        key->u.stream.signalready = 0;
        break;
        ;
    }
}


static void moduleCloseKey (RedisModuleKey *key){
    int signal = ((key->ctx)->module ? !((key->ctx)->module->options & (1 << 1)) : 1);
    ;
    if (key->kv) {
        if (key->iter)
            moduleFreeKeyIterator(key);
        switch (key->kv->type) {
          case 3:
            RM_ZsetRangeStop(key);
            break;
          case 6:
            ;
            break;
        }
    }
    (__builtin_expect(!!(key->iter == ((void *)0)), 1) ? (void)0 : (_serverAssert("key->iter == NULL", "module_InstSlice.c", 2573) , abort()));
    ;
}


extern void RM_CloseKey (RedisModuleKey *key){
    if (key == ((void *)0))
        return;
    moduleCloseKey(key);
    autoMemoryFreed(key->ctx, 0, key);
    ;
}


void zsetKeyReset (RedisModuleKey *key){
    key->u.zset.type = 0;
    key->u.zset.current = ((void *)0);
    key->u.zset.er = 1;
}


extern void RM_ZsetRangeStop (RedisModuleKey *key){
    if (!key->kv || key->kv->type != 3)
        return;
    ;
    zsetKeyReset(key);
}


extern void RM_FreeCallReply (RedisModuleCallReply *reply){
    RedisModuleCtx *ctx = ((void *)0);
    if (callReplyType(reply) == 12) {
        RedisModuleAsyncRMCallPromise *promise = callReplyGetPrivateData(reply);
        ctx = promise->ctx;
        freeRedisModuleAsyncRMCallPromise(promise);
    } else {
        ctx = callReplyGetPrivateData(reply);
    }
    ;
    if (ctx) {
        autoMemoryFreed(ctx, 2, reply);
    }
}


extern int moduleHoldsTimer (struct RedisModule *module){
    raxIterator iter;
    int found = 0;
    ;
    ;
    while (raxNext(&iter))
        {
            RedisModuleTimer *timer = iter.data;
            if (timer->module == module) {
                found = 1;
                break;
            }
        }
    ;
    return found;
}


extern void moduleNotifyUserChanged (client *c){
    if (c->auth_callback) {
        ;
        c->auth_callback = ((void *)0);
        c->auth_callback_privdata = ((void *)0);
        c->auth_module = ((void *)0);
    }
}


extern void revokeClientAuthentication (client *c){
    moduleNotifyUserChanged(c);
    ;
}


static void moduleFreeAuthenticatedClients (RedisModule *module){
    listIter li;
    listNode *ln;
    ;
    while ((ln = listNext(&li)) != ((void *)0))
        {
            client *c = ((ln)->value);
            if (!c->auth_module)
                continue;
            ;
            RedisModule *auth_module = (RedisModule *)c->auth_module;
            if (auth_module == module) {
                revokeClientAuthentication(c);
            }
        }
}


extern void RM_FreeDict (RedisModuleCtx *ctx, RedisModuleDict *d){
    if (ctx != ((void *)0))
        autoMemoryFreed(ctx, 4, d);
    ;
    ;
}


extern void RM_FreeServerInfo (RedisModuleCtx *ctx, RedisModuleServerInfoData *data){
    if (ctx != ((void *)0))
        autoMemoryFreed(ctx, 5, data);
    ;
    ;
}


extern void moduleFireServerEvent (uint64_t eid, int subid, void *data){
    if (((RedisModule_EventListeners)->len) == 0)
        return;
    listIter li;
    listNode *ln;
    ;
    while ((ln = listNext(&li)))
        {
            RedisModuleEventListener *el = ln->value;
            if (el->event.id == eid) {
                RedisModuleCtx ctx;
                if (eid == 4) {
                    moduleCreateContext(&ctx, el->module, (0));
                    ctx.client = (client *)data;
                } else {
                    moduleCreateContext(&ctx, el->module, (1 << 6));
                }
                void *moduledata = ((void *)0);
                RedisModuleClientInfoV1 civ1;
                RedisModuleReplicationInfoV1 riv1;
                RedisModuleModuleChangeV1 mcv1;
                RedisModuleKey key;
                RedisModuleKeyInfoV1 ki = {1, &key};
                if (eid == 4) {
                    (__builtin_expect(!!(modulePopulateClientInfoStructure(&civ1, data, el->event.dataver) == 0), 1) ? (void)0 : (_serverAssert("modulePopulateClientInfoStructure(&civ1,data, el->event.dataver) == REDISMODULE_OK", "module_InstSlice.c", 6366) , abort()));
                    moduledata = &civ1;
                } else if (eid == 0) {
                    (__builtin_expect(!!(modulePopulateReplicationInfoStructure(&riv1, el->event.dataver) == 0), 1) ? (void)0 : (_serverAssert("modulePopulateReplicationInfoStructure(&riv1,el->event.dataver) == REDISMODULE_OK", "module_InstSlice.c", 6369) , abort()));
                    moduledata = &riv1;
                } else if (eid == 2) {
                    moduledata = data;
                    RedisModuleFlushInfoV1 *fi = data;
                    ;
                } else if (eid == 9) {
                    RedisModule *m = data;
                    if (m == el->module) {
                        moduleFreeContext(&ctx);
                        continue;
                    }
                    mcv1.version = 1;
                    mcv1.module_name = m->name;
                    mcv1.module_version = m->ver;
                    moduledata = &mcv1;
                } else if (eid == 10) {
                    moduledata = data;
                } else if (eid == 8) {
                    moduledata = data;
                } else if (eid == 11) {
                    moduledata = data;
                } else if (eid == 16) {
                    moduledata = data;
                } else if (eid == 17) {
                    KeyInfo *info = data;
                    ;
                    moduleInitKey(&key, &ctx, info->key, info->kv, info->mode);
                    moduledata = &ki;
                }
                el->module->in_hook++;
                ;
                el->module->in_hook--;
                if (eid == 17) {
                    moduleCloseKey(&key);
                }
                moduleFreeContext(&ctx);
            }
        }
}


extern int moduleFreeCommand (struct RedisModule *module, struct redisCommand *cmd){
    if (cmd->proc != RedisModuleCommandDispatcher)
        return -1;
    RedisModuleCommand *cp = cmd->module_cmd;
    if (cp->module != module)
        return -1;
    for (int j = 0; j < cmd->key_specs_num; j++) {
        ;
        ;
    }
    ;
    for (int j = 0; cmd->tips && cmd->tips[j]; j++)
        ;
    ;
    for (int j = 0; cmd->history && cmd->history[j].since; j++) {
        ;
        ;
    }
    ;
    ;
    ;
    ;
    ;
    if (cmd->latency_histogram) {
        ;
        cmd->latency_histogram = ((void *)0);
    }
    ;
    ;
    if (cmd->subcommands_dict) {
        dictEntry *de;
        dictIterator di;
        ;
        while ((de = dictNext(&di)) != ((void *)0))
            {
                struct redisCommand *sub = dictGetVal(de);
                if (moduleFreeCommand(module, sub) != 0)
                    continue;
                ;
                (__builtin_expect(!!(dictDelete(cmd->subcommands_dict, sub->declared_name) == 0), 1) ? (void)0 : (_serverAssert("dictDelete(cmd->subcommands_dict, sub->declared_name) == DICT_OK", "module_InstSlice.c", 6557) , abort()));
                ;
                ;
                ;
            }
        ;
        ;
    }
    return 0;
}


extern void moduleUnregisterCommands (struct RedisModule *module){
    ;
    dictIterator di;
    dictEntry *de;
    ;
    while ((de = dictNext(&di)) != ((void *)0))
        {
            struct redisCommand *cmd = dictGetVal(de);
            if (moduleFreeCommand(module, cmd) != 0)
                continue;
            ;
            (__builtin_expect(!!(dictDelete(server.commands, cmd->fullname) == 0), 1) ? (void)0 : (_serverAssert("dictDelete(server.commands, cmd->fullname) == DICT_OK", "module_InstSlice.c", 6580) , abort()));
            (__builtin_expect(!!(dictDelete(server.orig_commands, cmd->fullname) == 0), 1) ? (void)0 : (_serverAssert("dictDelete(server.orig_commands, cmd->fullname) == DICT_OK", "module_InstSlice.c", 6581) , abort()));
            ;
            ;
            ;
        }
    ;
    ;
}


extern int parseLoadexArguments (robj ***module_argv, int *module_argc){
    int args_specified = 0;
    robj **argv = *module_argv;
    int argc = *module_argc;
    for (int i = 0; i < argc; i++) {
        char *arg_val = argv[i]->ptr;
        if (!strcasecmp(arg_val, "CONFIG")) {
            if (i + 2 >= argc) {
                ;
                return 1;
            }
            sds name = sdsdup(argv[i + 1]->ptr);
            sds value = sdsdup(argv[i + 2]->ptr);
            ;
            i += 2;
        } else if (!strcasecmp(arg_val, "ARGS")) {
            args_specified = 1;
            i++;
            if (i >= argc) {
                *module_argv = ((void *)0);
                *module_argc = 0;
            } else {
                *module_argv = argv + i;
                *module_argc = argc - i;
            }
            break;
        } else {
            ;
            return 1;
        }
    }
    if (!args_specified) {
        *module_argv = ((void *)0);
        *module_argc = 0;
    }
    return 0;
}


extern void moduleUnregisterCleanup (RedisModule *module){
    moduleFreeAuthenticatedClients(module);
    moduleUnregisterCommands(module);
    ;
    ;
    ;
    ;
    ;
    ;
    ;
}


extern int moduleLoad (const char *path, void **module_argv, int module_argc, int is_loadex){
    int (*onload)(void *, void **, int);
    void *handle;
    struct stat st;
    if (stat(path, &st) == 0) {
        if (!(st.st_mode & (64 | (64 >> 3) | ((64 >> 3) >> 3)))) {
            ;
            return -1;
        }
    }
    handle = dlopen(path, 2 | 0);
    if (handle == ((void *)0)) {
        ;
        return -1;
    }
    onload = (int (*)(void *, void **, int))(unsigned long)dlsym(handle, "RedisModule_OnLoad");
    if (onload == ((void *)0)) {
        ;
        ;
        return -1;
    }
    return moduleOnLoad(onload, path, handle, module_argv, module_argc, is_loadex);
}


extern int moduleOnLoad (int (*onload)(void *, void **, int), const char *path, void *handle, void **module_argv, int module_argc, int is_loadex){
    RedisModuleCtx ctx;
    moduleCreateContext(&ctx, ((void *)0), (1 << 6));
    if (onload((void *)&ctx, module_argv, module_argc) == 1) {
        ;
        if (ctx.module) {
            moduleUnregisterCleanup(ctx.module);
            ;
            ;
        }
        moduleFreeContext(&ctx);
        ;
        return -1;
    }
    ;
    ctx.module->blocked_clients = 0;
    ctx.module->handle = handle;
    ctx.module->loadmod = zmalloc(sizeof(struct moduleLoadQueueEntry));
    ctx.module->loadmod->path = sdsnew(path);
    ctx.module->loadmod->argv = module_argc ? zmalloc(sizeof(robj *) * module_argc) : ((void *)0);
    ctx.module->loadmod->argc = module_argc;
    for (int i = 0; i < module_argc; i++) {
        ctx.module->loadmod->argv[i] = module_argv[i];
        ;
    }
    ;
    ctx.module->onload = 0;
    int post_load_err = 0;
    if (((ctx.module->module_configs)->len) && !(ctx.module->configs_initialized & MODULE_CONFIGS_USER_VALS)) {
        ;
        post_load_err = 1;
    }
    if (is_loadex && ((server.module_configs_queue)->ht_used[0] + (server.module_configs_queue)->ht_used[1])) {
        ;
        post_load_err = 1;
    }
    if (post_load_err) {
        (__builtin_expect(!!(moduleUnload(ctx.module->name, ((void *)0), 1) == 0), 1) ? (void)0 : (_serverAssert("moduleUnload(ctx.module->name, NULL, 1) == C_OK", "module_InstSlice.c", 6722) , abort()));
        moduleFreeContext(&ctx);
        return -1;
    }
    moduleFireServerEvent(9, 0, ctx.module);
    moduleFreeContext(&ctx);
    return 0;
}


extern int moduleUnload (sds name, const char **errmsg, int forced_unload){
    struct RedisModule *module = dictFetchValue(modules, name);
    if (module == ((void *)0)) {
        ;
        return -1;
    } else if (sdslen(module->loadmod->path) == 0) {
        ;
        return -1;
    } else if (((module->types)->len) && !forced_unload) {
        ;
        return -1;
    } else if (((module->usedby)->len)) {
        ;
        return -1;
    } else if (module->blocked_clients) {
        ;
        return -1;
    } else if (moduleHoldsTimer(module)) {
        ;
        return -1;
    }
    int (*onunload)(void *);
    onunload = (int (*)(void *))(unsigned long)dlsym(module->handle, "RedisModule_OnUnload");
    if (onunload) {
        RedisModuleCtx ctx;
        moduleCreateContext(&ctx, module, (1 << 6));
        int unload_status = onunload((void *)&ctx);
        moduleFreeContext(&ctx);
        if (unload_status == 1) {
            ;
            (*__errno_location()) = 125;
            return -1;
        }
    }
    moduleUnregisterCleanup(module);
    if (dlclose(module->handle) == -1) {
        char *error = dlerror();
        ;
        ;
    }
    moduleFireServerEvent(9, 1, module);
    ;
    ;
    module->name = ((void *)0);
    ;
    ;
    return 0;
}


extern void addReplyLoadedModules (client *c){
    const long ln = ((modules)->ht_used[0] + (modules)->ht_used[1]);
    ;
    if (ln == 0) {
        return;
    }
    dictIterator di;
    dictEntry *de;
    ;
    while ((de = dictNext(&di)) != ((void *)0))
        {
            sds name = dictGetKey(de);
            struct RedisModule *module = dictGetVal(de);
            sds path = module->loadmod->path;
            ;
            ;
            addReplyBulkCBuffer(c, name, sdslen(name));
            ;
            ;
            ;
            addReplyBulkCBuffer(c, path, sdslen(path));
            ;
            ;
            for (int i = 0; i < module->loadmod->argc; i++) {
                ;
            }
        }
    ;
}


extern void RM_ConfigIteratorRelease (RedisModuleCtx *ctx, RedisModuleConfigIterator *iter){
    if (ctx != ((void *)0))
        autoMemoryFreed(ctx, 6, iter);
    ;
    ;
    ;
}


extern void moduleCommand (client *c){
    char *subcmd = c->argv[1]->ptr;
    if (c->argc == 2 && !strcasecmp(subcmd, "help")) {
        const char *help[] = {"LIST", "    Return a list of loaded modules.", "LOAD <path> [<arg> ...]", "    Load a module library from <path>, passing to it any optional arguments.", "LOADEX <path> [[CONFIG NAME VALUE] [CONFIG NAME VALUE]] [ARGS ...]", "    Load a module library from <path>, while passing it module configurations and optional arguments.", "UNLOAD <name>", "    Unload a module.", ((void *)0)};
        ;
    } else if (!strcasecmp(subcmd, "load") && c->argc >= 3) {
        robj **argv = ((void *)0);
        int argc = 0;
        if (c->argc > 3) {
            argc = c->argc - 3;
            argv = &c->argv[3];
        }
        if (moduleLoad(c->argv[2]->ptr, (void **)argv, argc, 0) == 0) {
            ;
        } else {
            ;
        }
    } else if (!strcasecmp(subcmd, "loadex") && c->argc >= 3) {
        robj **argv = ((void *)0);
        int argc = 0;
        if (c->argc > 3) {
            argc = c->argc - 3;
            argv = &c->argv[3];
        }
        if (parseLoadexArguments((robj ***)&argv, &argc) == 0 && moduleLoad(c->argv[2]->ptr, (void **)argv, argc, 1) == 0) {
            ;
        } else {
            ;
        }
    } else if (!strcasecmp(subcmd, "unload") && c->argc == 3) {
        const char *errmsg = ((void *)0);
        if (moduleUnload(c->argv[2]->ptr, &errmsg, 0) == 0) {
            ;
        } else {
            ;
        }
    } else if (!strcasecmp(subcmd, "list") && c->argc == 2) {
        addReplyLoadedModules(c);
    } else {
        ;
    }
}


