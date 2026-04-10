#include "header_func.h"
#include "sds.h"
static int clusterManagerGetAntiAffinityScore (clusterManagerNodeArray *ipnodes, int ip_count, clusterManagerNode ***offending, int *offending_len){
    int score = 0, i, j;
    int node_len = cluster_manager.nodes->len;
    clusterManagerNode **offending_p = ((void *)0);
    if (offending != ((void *)0)) {
        *offending = zcalloc(node_len * sizeof(clusterManagerNode *));
        offending_p = *offending;
    }
    for (i = 0; i < ip_count; i++) {
        clusterManagerNodeArray *node_array = &(ipnodes[i]);
        dict *related = dictCreate(&clusterManagerDictType);
        char *ip = ((void *)0);
        for (j = 0; j < node_array->len; j++) {
            clusterManagerNode *node = node_array->nodes[j];
            if (node == ((void *)0))
                continue;
            if (!ip)
                ip = node->ip;
            hisds types;
            hisds key = (!node->replicate ? node->name : node->replicate);
            ((void)sizeof ((key != ((void *)0)) ? 1 : 0) , __extension__ ({
                if (key != ((void *)0))
                    ;
                else
                    __assert_fail("key != NULL", "redis-cli_InstSlice.c", 955, __extension__ __PRETTY_FUNCTION__);
            }));
            dictEntry *entry = dictFind(related, key);
            if (entry) {
                types = hi_sdsdup((hisds)dictGetVal(entry));
            } else
                types = hi_sdsempty();
            if (node->replicate) {
                types = hi_sdscat(types, "s");
            } else {
                hisds s = hi_sdscatsds(hi_sdsnew("m"), types);
                types = s;
            }
            ;
        }
        dictIterator iter;
        dictEntry *entry;
        while ((entry = dictNext(&iter)) != ((void *)0))
            {
                hisds types = (hisds)dictGetVal(entry);
                hisds name = (hisds)dictGetKey(entry);
                int typeslen = hi_sdslen(types);
                if (typeslen < 2)
                    continue;
                if (types[0] == 'm') {
                    score += (10000 * (typeslen - 1));
                } else
                    score += (1 * typeslen);
                if (offending == ((void *)0))
                    continue;
                listIter li;
                listNode *ln;
                while ((ln = listNext(&li)) != ((void *)0))
                    {
                        clusterManagerNode *n = ln->value;
                        if (n->replicate == ((void *)0))
                            continue;
                        if (!strcmp(n->replicate, name) && !strcmp(n->ip, ip)) {
                            *(offending_p++) = n;
                            if (offending_len != ((void *)0))
                                (*offending_len)++;
                            break;
                        }
                    }
            }
        ;
    }
    return score;
}
static void clusterManagerOptimizeAntiAffinity (clusterManagerNodeArray *ipnodes, int ip_count){
    clusterManagerNode **offenders = ((void *)0);
    int score = clusterManagerGetAntiAffinityScore(ipnodes, ip_count, ((void *)0), ((void *)0));
    if (score == 0)
        goto cleanup;
    int node_len = cluster_manager.nodes->len;
    int maxiter = 500 * node_len;
    while (maxiter > 0)
        {
            int offending_len = 0;
            if (offenders != ((void *)0)) {
                ;
                offenders = ((void *)0);
            }
            score = clusterManagerGetAntiAffinityScore(ipnodes, ip_count, &offenders, &offending_len);
            if (score == 0 || offending_len == 0)
                break;
            int rand_idx = rand() % offending_len;
            clusterManagerNode *first = offenders[rand_idx], *second = ((void *)0);
            clusterManagerNode **other_replicas = zcalloc((node_len - 1) * sizeof (*other_replicas));
            int other_replicas_count = 0;
            listIter li;
            listNode *ln;
            while ((ln = listNext(&li)) != ((void *)0))
                {
                    clusterManagerNode *n = ln->value;
                    if (n != first && n->replicate != ((void *)0))
                        other_replicas[other_replicas_count++] = n;
                }
            if (other_replicas_count == 0) {
                ;
                break;
            }
            rand_idx = rand() % other_replicas_count;
            second = other_replicas[rand_idx];
            char *first_master = first->replicate, *second_master = second->replicate;
            first->replicate = second_master , first->dirty = 1;
            second->replicate = first_master , second->dirty = 1;
            int new_score = clusterManagerGetAntiAffinityScore(ipnodes, ip_count, ((void *)0), ((void *)0));
            if (new_score > score) {
                first->replicate = first_master;
                second->replicate = second_master;
            }
            ;
            maxiter--;
        }
    score = clusterManagerGetAntiAffinityScore(ipnodes, ip_count, ((void *)0), ((void *)0));
    char *msg;
    int perfect = (score == 0);
    int log_level = (perfect ? 4 : 2);
  cleanup:
    ;
}
