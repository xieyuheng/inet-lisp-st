#include "index.h"

void
worker_handle_task(worker_t *worker) {
    task_t *task = list_pop(worker->task_list);
    if (task == NULL) return;

    react(worker, task);
}

void
worker_work(worker_t *worker) {
    while (!list_is_empty(worker->task_list)) {
        worker_handle_task(worker);
    }
}
