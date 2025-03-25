#pragma once

struct manager_t {
    mod_t *mod;
    size_t worker_pool_size;
    worker_t **workers;
    size_t task_queue_size;
    queue_t **task_queues;
    // manager thread
    thread_id_t thread_id;
    bool is_started;
    // worker threads
    thread_id_t *worker_thread_ids;
    atomic_bool *worker_switches;
};

manager_t *manager_new(mod_t *mod, size_t worker_pool_size);
void manager_destroy(manager_t **self_pointer);
