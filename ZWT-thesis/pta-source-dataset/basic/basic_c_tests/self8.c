// 链表
#include "aliascheck.h"

struct list {
    int x;
    struct list* next;
    // list() { next = (struct list*)malloc(sizeof(struct list)); }
};

struct list* foo(struct list* p) {
    struct list* old_p = p;
    MAYALIAS(p, p->next);
    for (int i = 0; i < 10; i++) {
        p = p->next;
    }
    return p;
}

int main() {
    return 0;
}