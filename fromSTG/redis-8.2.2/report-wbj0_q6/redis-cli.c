static int clusterManagerAddSlots (clusterManagerNode *node, char **err){
    redisReply *reply = ((void *)0);
    void *_reply = ((void *)0);
    int success = 1;
    int argc = node->slots_count + 2;
    hisds *argv = zmalloc(argc * sizeof (*argv));
    size_t *argvlen = zmalloc(argc * sizeof (*argvlen));
    argv[0] = "CLUSTER";
    argv[1] = "ADDSLOTS";
    argvlen[0] = 7;
    argvlen[1] = 8;
    *err = ((void *)0);
    int i, argv_idx = 2;
    ;
    ;
    ;
  cleanup:
    ;
    ;
    return success;
}


static int clusterManagerFlushNodeConfig (clusterManagerNode *node, char **err){
    if (!node->dirty)
        return 0;
    redisReply *reply = ((void *)0);
    int is_err = 0, success = 1;
    if (err != ((void *)0))
        *err = ((void *)0);
    if (node->replicate != ((void *)0)) {
        ;
    } else {
        int added = clusterManagerAddSlots(node, err);
        ;
    }
    ;
  cleanup:
    ;
    return success;
}


