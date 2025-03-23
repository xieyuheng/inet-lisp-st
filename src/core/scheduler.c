#include "index.h"

scheduler_t *
scheduler_new(mod_t *mod, size_t worker_pool_size) {
    scheduler_t *self = new_shared(scheduler_t);
    self->mod = mod;
    self->worker_pool_size = worker_pool_size;
    size_t task_queue_size = 1 << 20;
    self->task_queue_size = task_queue_size;
    return self;
}
