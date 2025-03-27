#pragma once

struct manager_t {
    mod_t *mod;
    size_t worker_pool_size;
    worker_t **workers;
    size_t task_queue_size;
    queue_t **task_queues;
    // manager thread
    thread_id_t thread_id;
    // worker threads
    worker_ctx_t **worker_ctxs;

};

manager_t *manager_new(mod_t *mod, size_t worker_pool_size);
void manager_destroy(manager_t **self_pointer);
