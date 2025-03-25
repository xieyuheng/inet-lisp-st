#include "index.h"

static bool
manager_no_more_task(manager_t *manager) {
    for (size_t i = 0; i < manager->worker_pool_size; i++) {
        if (!queue_is_empty(manager->task_queues[i])) {
            return false;
        }
    }

    for (size_t i = 0; i < manager->worker_pool_size; i++) {
        if (!queue_is_empty(manager->workers[i]->task_queue)) {
            return false;
        }
    }

    return true;
}

static void
manager_dispatch(manager_t *manager) {
    while (true) {
        size_t cursor = 0;
        for (size_t i = 0; i < manager->worker_pool_size; i++) {
            while (!queue_is_empty(manager->task_queues[i])) {
                task_t *task = queue_dequeue(manager->task_queues[i]);
                size_t real_cursor = cursor % manager->worker_pool_size;
                queue_enqueue(manager->workers[real_cursor]->task_queue, task);
                cursor++;
            }
        }

        printf("[manager_thread_fn] dispatch one round\n");

        if (manager_no_more_task(manager)) return;
    }
}

static void *
manager_thread_fn(manager_t *manager) {
    printf("[manager_thread_fn] started\n");

    manager_dispatch(manager);

    for (size_t i = 0; i < manager->worker_pool_size; i++) {
        atomic_store(&manager->worker_switches[i], false);
    }

    return NULL;

}

static void *
worker_thread_fn(worker_t *worker) {
    printf("[worker_thread_fn %ld] started\n", worker->index);
    while (true) {
        // TODO set worker_ctx to is_processing
        while (!queue_is_empty(worker->task_queue)) {
            printf("[worker_thread_fn %ld] step task\n", worker->index);
            step_task(worker);
        }

        if (!atomic_load(&worker->manager->worker_switches[worker->index])) {
            return NULL;
        }

        printf("[worker_thread_fn %ld] spinning\n", worker->index);
    }
}

static void
manager_start(manager_t *manager, queue_t *init_task_queue) {
    // prepare tasks

    size_t cursor = 0;
    while (!queue_is_empty(init_task_queue)) {
        task_t *task = queue_dequeue(init_task_queue);
        size_t real_cursor = cursor % manager->worker_pool_size;
        queue_t *next_task_queue = manager->task_queues[real_cursor];
        bool ok = queue_enqueue(next_task_queue, task);
        assert(ok);
        cursor++;
    }

    // start manager thread

    manager->thread_id = thread_start((thread_fn_t *) manager_thread_fn, manager);
    manager->is_started = true;

    // start worker threads

    for (size_t i = 0; i < manager->worker_pool_size; i++) {
        atomic_store(&manager->worker_switches[i], true);
    }

    for (size_t i = 0; i < manager->worker_pool_size; i++) {
        manager->worker_thread_ids[i] = thread_start((thread_fn_t *) worker_thread_fn, manager->workers[i]);
    }
}

static void
manager_wait(manager_t *manager) {
    for (size_t i = 0; i < manager->worker_pool_size; i++) {
        thread_wait(manager->worker_thread_ids[i]);
    }

    thread_wait(manager->thread_id);
}

void
run_task_parallelly(worker_t *worker) {
    size_t processor_count = sysconf(_SC_NPROCESSORS_ONLN);
    manager_t *manager = manager_new(worker->mod, processor_count - 1);
    manager_start(manager, worker->task_queue);
    manager_wait(manager);
    manager_destroy(&manager);
}
