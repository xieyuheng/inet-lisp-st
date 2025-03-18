#include "index.h"

// a thread safe queue:
//
//     +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
//     |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
//     +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
//                               ^           ^
//                               |           |
//         (dequeue) => front_cursor       back_cursor => (enqueue)
//

typedef _Atomic uint64_t cursor_t;

struct queue_t {
    size_t size;
    cursor_t front_cursor;
    cursor_t back_cursor;
};

queue_t *
queue_new(size_t size) {
    queue_t *self = new(queue_t);
    self->size = size;
    return self;
}

void
queue_destroy(queue_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        queue_t *self = *self_pointer;
        // free(self->values);
        free(self);
        *self_pointer = NULL;
    }
}
