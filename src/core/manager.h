#pragma once

struct manager_t {
    mod_t *mod;
    size_t worker_pool_size;
    worker_t **workers;
    size_t task_queue_size;
    queue_t **task_queues;
    // for thread
    thread_id_t thread_id;
    bool is_started;
};

manager_t *manager_new(mod_t *mod, size_t worker_pool_size);
void manager_destroy(manager_t **self_pointer);

void manager_start(manager_t *self);
