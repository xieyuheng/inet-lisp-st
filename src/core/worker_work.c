#include "index.h"

void
worker_work(worker_t *worker) {
    while (!list_is_empty(worker->task_list)) {
        worker_handle_task(worker);
    }
}
