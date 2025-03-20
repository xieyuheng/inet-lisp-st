#include "index.h"

// a single producer single consumer thread safe circular queue:
//
//     +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
//     |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
//     +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
//                               ^           ^
//                               |           |
//         (dequeue) => front_cursor       back_cursor => (enqueue)
//
// just like people waiting in a line:
// - enqueue -- a new person enter the queue from the back;
// - dequeue -- the next person exit the queue from the front.
//
// constraints of the circular buffer:
// - `front_cursor` must not go beyond `back_cursor`;
// - `back_cursor` must not catch `front_cursor` from behind.

typedef size_t cursor_t;

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
    self->values = allocate_pointers(size + 1);
    self->back_cursor = 0;
    self->front_cursor = 0;
    return self;
}

void
queue_purge(queue_t *self) {
    assert(self);
    while(!queue_is_empty(self)) {
        void *value = queue_dequeue(self);
        if (self->destroy_fn)
            self->destroy_fn(&value);
    }
}

void
queue_destroy(queue_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        queue_t *self = *self_pointer;
        queue_purge(self);
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

static size_t
real_size(const queue_t *self) {
    return self->size + 1;
}

size_t
queue_size(const queue_t *self) {
    return self->size;
}

static cursor_t
queue_next_back_cursor(const queue_t *self) {
    return (self->back_cursor + 1) % real_size(self);
}

size_t
queue_length(const queue_t *self) {
    if (self->back_cursor >= self->front_cursor) {
        return self->back_cursor - self->front_cursor;
    } else {
        return self->back_cursor + real_size(self) - self->front_cursor;
    }
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

void *
queue_dequeue(queue_t *self) {
    size_t front_cursor = self->front_cursor;
    if (queue_is_empty(self)) {
        return NULL;
    }

    void *value = self->values[front_cursor];
    self->values[front_cursor] = NULL;
    size_t next_front_cursor = (front_cursor + 1) % real_size(self);
    self->front_cursor = next_front_cursor;
    return value;
}
