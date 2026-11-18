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
    connAddrPeerName(client->conn, ci1->addr, sizeof (ci1->addr), &port);
    ci1->port = port;
    ci1->db = client->db->id;
    ci1->id = client->id;
    return 0;
}


extern int RM_GetClientInfoById (void *ci, uint64_t id){
    client *client = lookupClientByID(id);
    if (client == ((void *)0))
        return 1;
    if (ci == ((void *)0))
        return 0;
    uint64_t structver = ((uint64_t *)ci)[0];
    return modulePopulateClientInfoStructure(ci, client, structver);
}


