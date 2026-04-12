// offset为total unknown
#include <stdint.h>
#include "aliascheck.h"
uint32_t* q;
int main(int argc, char** argv) {
    uint32_t* arr[10];
    for (int i = 0; i < argc; i++) {
        q = arr[i];
    }
    uint32_t x = *q;

    MAYALIAS(q, arr[6]);  // 此处的arr[6]被表示为*sp-20, 而q表示为*(sp - 0x111)
    return 0;
}
