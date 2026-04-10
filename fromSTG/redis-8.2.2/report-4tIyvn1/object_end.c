#include "header_func.h"
#include "sds.h"
extern kvobj * kvobjCreate (int type, const sds key, void *ptr, int hasExpire){
    (__builtin_expect(!!(key != ((void *)0)), 1) ? (void)0 : (_serverAssert("key != NULL", "object_InstSlice.c", 41) , abort()));
    hasExpire = hasExpire || (sdslen(key) >= 128);
    size_t key_sds_len = sdslen(key);
    char key_sds_type;
    size_t key_sds_size;
    size_t min_size;
    size_t bufsize;
    robj *o;
    char *data;
    return o;
}
static kvobj * kvobjCreateEmbedString (const char *val_ptr, size_t val_len, const sds key, int hasExpire){
    (__builtin_expect(!!(key != ((void *)0)), 1) ? (void)0 : (_serverAssert("key != NULL", "object_InstSlice.c", 114) , abort()));
    size_t key_sds_len = sdslen(key);
    char key_sds_type;
    size_t key_sds_size;
    size_t val_sds_size;
    size_t min_size;
    size_t bufsize;
    robj *o;
    char *data;
    size_t remaining_size;
    return o;
}
extern sds kvobjGetKey (const kvobj *kv){
    unsigned char *data = (void *)(kv + 1);
    if (kv->expirable) {
        data += sizeof(long long);
    }
    if (kv->iskvobj) {
        uint8_t hdr_size = *(uint8_t *)data;
        data += 1 + hdr_size;
        return (sds)data;
    }
    return ((void *)0);
}
extern kvobj * kvobjSetExpire (kvobj *kv, long long expire){
    if (!kv->expirable) {
        if (expire == -1)
            return kv;
        kv = kvobjSet(kvobjGetKey(kv), kv, 1);
    }
    unsigned char *data;
    return kv;
}
extern kvobj * kvobjSet (sds key, robj *val, int hasExpire){
    if (val->type == 0 && val->encoding == 8) {
        kvobj *kv;
        size_t len = sdslen(val->ptr);
        size_t size = sizeof(kvobj);
        size += (key != ((void *)0)) * (sdslen(key) + 3);
        size += (!!hasExpire) * sizeof(long long);
        size += 4 + len;
        if (size <= 64) {
            kv = kvobjCreateEmbedString(val->ptr, len, key, hasExpire);
        } else {
            kv = kvobjCreate(0, key, sdsnewlen(val->ptr, len), hasExpire);
        }
        ;
        return kv;
    }
    void *valptr;
    if (val->refcount == 1) {
        valptr = val->ptr;
        val->ptr = ((void *)0);
    } else if (val->type == 0 && val->encoding == 1) {
        valptr = val->ptr;
    } else if (val->type == 0 && val->encoding == 0) {
        valptr = sdsdup(val->ptr);
    } else {
        ;
    }
    robj *new = kvobjCreate(val->type, key, valptr, hasExpire);
    return new;
}
