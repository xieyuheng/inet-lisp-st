#include "index.h"

// a thread safe circular queue:
//
//     +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
//     |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
//     +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
//                               ^           ^
//                               |           |
//         (dequeue) => front_cursor       back_cursor => (enqueue)
//
// - `front_cursor` must not go beyond `back_cursor`
// - `back_cursor` must not catch `front_cursor` from behind

typedef uint64_t cursor_t;

struct queue_t {
    size_t size;
    void **values;
    cursor_t front_cursor;
    cursor_t back_cursor;
    destroy_fn_t *destroy_fn;
};

queue_t *
queue_new(size_t size) {
    assert(size > 1);
    queue_t *self = new(queue_t);
    self->size = size;
    self->values = allocate_pointers(size);
    self->back_cursor = 0;
    self->front_cursor = 0;
    return self;
}

void
queue_destroy(queue_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        queue_t *self = *self_pointer;
        free(self->values);
        free(self);
        *self_pointer = NULL;
    }
}

void
queue_set_destroy_fn(queue_t *self, destroy_fn_t *destroy_fn) {
    self->destroy_fn = destroy_fn;
}

queue_t *
queue_new_with(size_t size, destroy_fn_t *destroy_fn) {
    queue_t *self = queue_new(size);
    self->destroy_fn = destroy_fn;
    return self;
}

void
queue_enqueue(queue_t *self, void *value) {
    cursor_t next_back_cursor = (self->back_cursor + 1) % self->size;
    if (next_back_cursor == self->front_cursor) {
        // - `back_cursor` must not catch `front_cursor` from behind
        fprintf(stderr, "[queue_enqueue] the queue is full\n");
        exit(1);
    }

    self->values[self->back_cursor] = value;
    self->back_cursor = next_back_cursor;
}
