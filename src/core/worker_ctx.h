#pragma once

struct worker_ctx_t {
    worker_t *worker;
    atomic_bool atomic_is_turned_off;
    atomic_bool atomic_is_processing;
};
