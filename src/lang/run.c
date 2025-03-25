#include "index.h"

static void
step_op(worker_t *worker, frame_t *frame, op_t *op) {
    switch (op->kind) {
    case OP_APPLY: {
        value_t target = stack_pop(worker->value_stack);
        apply(worker, target, op->apply.arity);
        return;
    }

    case OP_LITERAL: {
        stack_push(worker->value_stack, op->literal.value);
        return;
    }

    case OP_GET_VARIABLE: {
        value_t value = frame_get_variable(frame, op->get_variable.index);
        stack_push(worker->value_stack, value);
        return;
    }

    case OP_SET_VARIABLE: {
        value_t value = stack_pop(worker->value_stack);
        frame_set_variable(frame, op->set_variable.index, value);
        return;
    }
    }
}

static void
step(worker_t *worker) {
    if (stack_is_empty(worker->return_stack)) return;

    frame_t *frame = stack_pop(worker->return_stack);
    if (frame_is_finished(frame)) {
        frame_destroy(&frame);
        return;
    }

    op_t *op = frame_fetch_op(frame);

    // proper tail-call = do not push finished frame.
    bool finished = frame_is_finished(frame);
    if (!finished) {
        stack_push(worker->return_stack, frame);
    }

    step_op(worker, frame, op);

    if (finished) {
        frame_destroy(&frame);
    }
}

void
run_until(worker_t *worker, size_t base_length) {
#if STEP_LOG
    worker_print(worker, stdout);
    fprintf(stdout, "\n");
#endif

    while (stack_length(worker->return_stack) > base_length) {
        step(worker);

#if STEP_LOG
        worker_print(worker, stdout);
        fprintf(stdout, "\n");
#endif
    }
}

void
step_task(worker_t *worker) {
    task_t *task = queue_dequeue(worker->task_queue);
    if (task == NULL) return;

    react(worker, task);
}

static void
run_task_sequentially(worker_t *worker) {
    while (!queue_is_empty(worker->task_queue)) {
        step_task(worker);
    }
}

static void
run_task_parallelly(worker_t *worker) {
    size_t processor_count = sysconf(_SC_NPROCESSORS_ONLN);
    scheduler_t *scheduler = scheduler_new(worker->mod, processor_count - 1);

    while (!queue_is_empty(worker->task_queue)) {
        step_task(worker);
    }

    scheduler_destroy(&scheduler);
}

void
run_task(worker_t *worker) {
    if (core_debug_flag)
        run_task_sequentially(worker);
    else
        run_task_parallelly(worker);
}
