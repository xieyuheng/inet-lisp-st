#pragma once

struct scheduler_t {
    mod_t *mod;
    size_t worker_pool_size;
    worker_t **workers;
    size_t task_queue_size;
    queue_t **task_queues;
};

scheduler_t *scheduler_new(mod_t *mod, size_t worker_pool_size);
