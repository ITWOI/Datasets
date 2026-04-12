// offset为load memory

#include <stdint.h>
#include "aliascheck.h"

struct CircularBuffer {
    uint8_t buffer[2048];
    uint16_t head;
    uint16_t tail;
    uint16_t size;
};

struct CircularBuffer buff, buff2;

int func(struct CircularBuffer* p) {
    MAYALIAS(p->buffer + p->head, p->buffer + p->tail);
}

int main(int argc, char** argv) {
    return 0;
}
