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

int main(int argc, char** argv) {
    struct CircularBuffer* p = &buff;
    struct CircularBuffer* q = &buff2;

    MAYALIAS(p->buffer + p->head, p->buffer + p->tail);
    NOALIAS(p->buffer + p->head, q->buffer + p->head);
    return 0;
}
