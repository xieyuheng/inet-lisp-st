#include "index.h"

static void
build_net(worker_t *worker, exp_t *exp) {
    size_t arity = 0;
    function_t *function = function_new(arity);
    compile_exp(worker, function, exp);

    size_t return_stack_base = stack_length(worker->return_stack);
    frame_t *frame = frame_new(function);
    stack_push(worker->return_stack, frame);
    worker_run_until(worker, return_stack_base);

    function_destroy(&function);
    return;
}

size_t
run_exp(worker_t *worker, exp_t *exp) {
    size_t base_value_count = stack_length(worker->value_stack);

    build_net(worker, exp);

    // if (!no_run_top_level_exp) {
    //     worker_work(worker);
    // }

    worker_work(worker);

    assert(stack_length(worker->value_stack) >= base_value_count);
    size_t value_count = stack_length(worker->value_stack) - base_value_count;
    return value_count;
}

static void
print_top(worker_t *worker, size_t value_count, file_t *file) {
    for (size_t count = 0; count < value_count; count++) {
        size_t index = value_count - 1 - count;
        value_t value = stack_pick(worker->value_stack, index);
        if (is_wire(value)) {
            wire_print_net(as_wire(value), file);
            fprintf(stdout, "\n");
        } else {
            value_print(value, file);
            fprintf(stdout, "\n");
        }
    }
}

size_t
run_exp_and_print(worker_t *worker, exp_t *exp) {
    size_t value_count = run_exp(worker, exp);

    // if (print_top_level_exp_flag) {
    //     print_top(worker, value_count, stdout);
    // }

    print_top(worker, value_count, stdout);

    return value_count;
}
