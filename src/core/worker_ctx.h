#pragma once

struct worker_ctx_t {
    worker_t *worker;
    thread_id_t thread_id;
    atomic_bool atomic_is_turned_off;
    atomic_bool atomic_is_processing;
};

worker_ctx_t *worker_ctx_new(worker_t *worker);
void worker_ctx_destroy(worker_ctx_t **self_pointer);
