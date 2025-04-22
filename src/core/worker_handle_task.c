#include "index.h"

void
worker_handle_task(worker_t *worker) {
    task_t *task = list_pop(worker->task_list);
    if (task == NULL) return;

    react(worker, task);
}
