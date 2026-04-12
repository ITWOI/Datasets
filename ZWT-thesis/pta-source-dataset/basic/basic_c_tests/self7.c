// 二重指针，如果store(*p = q)中，q为目标指针值，则将*p加入到WorkList
#include "aliascheck.h"

int x;
void foo(int **m, int **n) {
    *n = *m;
}

int main() {
    int** p1, **p2;
    int* tmp1, *tmp2;
    p1 = &tmp1;
    p2 = &tmp2;
    *p1 = &x;
    foo(p1, p2);
    // printf("%p %p\n", *p1, *p2);
    MAYALIAS(*p1, *p2);

    return 0;
}