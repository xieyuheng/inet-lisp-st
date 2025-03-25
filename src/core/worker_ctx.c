#include "index.h"

worker_ctx_t *
worker_ctx_new(worker_t *worker) {
    worker_ctx_t *self = new_shared(worker_ctx_t);
    self->worker = worker;
    self->atomic_is_processing = false;
    self->atomic_is_turned_off = false;
    return self;
}

void
worker_ctx_destroy(worker_ctx_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        worker_ctx_t *self = *self_pointer;
        free(self);
        *self_pointer = NULL;
    }
}
