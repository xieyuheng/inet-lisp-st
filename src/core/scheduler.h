#pragma once

struct scheduler_t {
    mod_t *mod;
    size_t worker_pool_size;
    worker_t **workers;
    queue_t **task_queues;
};
