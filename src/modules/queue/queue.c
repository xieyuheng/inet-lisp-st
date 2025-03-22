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
//
// optimization is learned from:
// - code: https://github.com/CharlesFrasch/cppcon2023
// - talk: https://www.youtube.com/watch?v=K3P_Lmq6pw0

typedef size_t cursor_t;
typedef _Atomic cursor_t atomic_cursor_t;

struct queue_t {
    size_t size;
    void **values;
    atomic_cursor_t *front_cursor;
    atomic_cursor_t *back_cursor;
    cursor_t *cached_front_cursor;
    cursor_t *cached_back_cursor;
    destroy_fn_t *destroy_fn;
};

queue_t *
queue_new(size_t size) {
    assert(size > 1);
    queue_t *self = new_shared(queue_t);
    self->size = size;
    self->values = allocate_pointers(size + 1);
    self->back_cursor = new_shared(atomic_cursor_t);
    self->front_cursor = new_shared(atomic_cursor_t);
    assert(atomic_is_lock_free(self->back_cursor));
    assert(atomic_is_lock_free(self->front_cursor));
    self->cached_back_cursor = new_shared(cursor_t);
    self->cached_front_cursor = new_shared(cursor_t);
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
        free(self->front_cursor);
        free(self->back_cursor);
        free(self->cached_front_cursor);
        free(self->cached_back_cursor);
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

size_t
queue_length(const queue_t *self) {
    if (*self->back_cursor >= *self->front_cursor) {
        return *self->back_cursor - *self->front_cursor;
    } else {
        return *self->back_cursor + real_size(self) - *self->front_cursor;
    }
}

static inline bool
is_full(const queue_t *self, cursor_t front_cursor, cursor_t back_cursor) {
    cursor_t next_back_cursor = (back_cursor + 1) % real_size(self);
    return next_back_cursor == front_cursor;
}

static inline bool
is_empty(const queue_t *self, cursor_t front_cursor, cursor_t back_cursor) {
    (void) self;
    return back_cursor == front_cursor;
}

bool
queue_is_full(const queue_t *self) {
    return is_full(self, *self->front_cursor, *self->back_cursor);
}

bool
queue_is_empty(const queue_t *self) {
    return is_empty(self, *self->front_cursor, *self->back_cursor);
}

void
queue_enqueue(queue_t *self, void *value) {
    cursor_t back_cursor = load_relaxed(self->back_cursor);
    if (is_full(self, *self->cached_front_cursor, back_cursor)) {
        *self->cached_front_cursor = load_acquire(self->front_cursor);
        if (is_full(self, *self->cached_front_cursor, back_cursor)) {
            fprintf(stderr, "[queue_enqueue] the queue is full\n");
            exit(1);
        }
    }

    self->values[back_cursor] = value;
    cursor_t next_back_cursor = (back_cursor + 1) % real_size(self);
    store_release(self->back_cursor, next_back_cursor);
}

void *
queue_dequeue(queue_t *self) {
    cursor_t front_cursor = load_relaxed(self->front_cursor);
    if (is_empty(self, front_cursor, *self->cached_back_cursor)) {
        *self->cached_back_cursor = load_acquire(self->back_cursor);
        if (is_empty(self, front_cursor, *self->cached_back_cursor)) {
            return NULL;
        }
    }

    void *value = self->values[front_cursor];
    self->values[front_cursor] = NULL;
    cursor_t next_front_cursor = (front_cursor + 1) % real_size(self);
    store_release(self->front_cursor, next_front_cursor);
    return value;
}
