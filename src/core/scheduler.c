#include "index.h"

scheduler_t *
scheduler_new(mod_t *mod, size_t worker_pool_size) {
    scheduler_t *self = new_shared(scheduler_t);
    self->mod = mod;

    self->worker_pool_size = worker_pool_size;
    self->workers = allocate_pointers(worker_pool_size);
    for (size_t i = 0; i < worker_pool_size; i++)
        self->workers[i] = worker_new(mod);

    size_t task_queue_size = 1 << 20;
    self->task_queue_size = task_queue_size;
    self->task_queues = allocate_pointers(worker_pool_size);
    for (size_t i = 0; i < worker_pool_size; i++)
        self->task_queues[i] = queue_new_with(task_queue_size, (destroy_fn_t *) task_destroy);

    return self;
}
