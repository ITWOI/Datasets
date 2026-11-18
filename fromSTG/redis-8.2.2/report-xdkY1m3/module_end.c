#include "header_func.h"
extern int RM_ListInsert (RedisModuleKey *key, long index, robj *value){
    if (!value) {
        ;
        return 1;
    } else if (key != ((void *)0) && key->kv == ((void *)0) && (index == 0 || index == -1)) {
        return RM_ListPush(key, 1, value);
    } else if (key != ((void *)0) && key->kv != ((void *)0) && key->kv->type == 1 && (index == (long)listTypeLength(key->kv) || index == -1)) {
        return RM_ListPush(key, 1, value);
    } else if (key != ((void *)0) && key->kv != ((void *)0) && key->kv->type == 1 && (index == 0 || index == -(long)listTypeLength(key->kv) - 1)) {
        return RM_ListPush(key, 0, value);
    }
    listTypeTryConversionAppend(key->kv, &value, 0, 0, moduleFreeListIterator, key);
}
