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

static cursor_t
queue_next_back_cursor(const queue_t *self) {
    return (self->back_cursor + 1) % self->size;
}

bool
queue_is_full(const queue_t *self) {
    return queue_next_back_cursor(self) == self->front_cursor;
}

bool
queue_is_empty(const queue_t *self) {
    return self->back_cursor == self->front_cursor;
}

void
queue_enqueue(queue_t *self, void *value) {
    if (queue_is_full(self)) {
        // - `back_cursor` must not catch `front_cursor` from behind
        fprintf(stderr, "[queue_enqueue] the queue is full\n");
        exit(1);
    }

    self->values[self->back_cursor] = value;
    self->back_cursor = queue_next_back_cursor(self);
}
