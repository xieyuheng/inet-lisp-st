#pragma once

struct scheduler_t {
    mod_t *mod;
    size_t worker_pool_size;
    size_t task_queue_size;
    worker_t **workers;
    queue_t **task_queues;
};

scheduler_t *scheduler_new(mod_t *mod, size_t worker_pool_size);
void scheduler_destroy(scheduler_t **self_pointer);
