// normalize: Store to INT_ADD
#include <stdint.h>
#include "aliascheck.h"

int func(int* p, int sz) {

    int* q = p;
    if (sz > 10) {
        p = p + 1;
    }
    else {
        p = p - 1;
    }
    p = p + 1;

    MAYALIAS(p, q+2);
    return *p;
}

int main() {
    return 0;
}