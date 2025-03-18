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
