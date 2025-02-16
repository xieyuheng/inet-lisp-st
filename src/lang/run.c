#include "index.h"

static void
step_op(vm_t *vm, frame_t *frame, op_t *op) {
    switch (op->kind) {
    case OP_APPLY: {
        value_t target = stack_pop(vm->value_stack);
        apply(vm, target, op->apply.arity);
        return;
    }

    case OP_LITERAL: {
        stack_push(vm->value_stack, op->literal.value);
        return;
    }

    case OP_GET_VARIABLE: {
        value_t value = frame_get_variable(frame, op->get_variable.index);
        stack_push(vm->value_stack, value);
        return;
    }

    case OP_SET_VARIABLE: {
        value_t value = stack_pop(vm->value_stack);
        frame_set_variable(frame, op->set_variable.index, value);
        return;
    }
    }
}

static void
step(vm_t *vm) {
    if (stack_is_empty(vm->return_stack)) return;

    frame_t *frame = stack_pop(vm->return_stack);
    if (frame_is_finished(frame)) {
        frame_destroy(&frame);
        return;
    }

    op_t *op = frame_fetch_op(frame);

    // proper tail-call = do not push finished frame.
    bool finished = frame_is_finished(frame);
    if (!finished) {
        stack_push(vm->return_stack, frame);
    }

    step_op(vm, frame, op);

    if (finished) {
        frame_destroy(&frame);
    }
}

void
run_until(vm_t *vm, size_t base_length) {
#if DEBUG
    vm_print(vm, stdout);
    fprintf(stdout, "\n");
#endif

    while (stack_length(vm->return_stack) > base_length) {
        step(vm);

#if DEBUG
        vm_print(vm, stdout);
        fprintf(stdout, "\n");
#endif
    }
}

void
step_net(vm_t *vm) {
    activity_t *activity = list_shift(vm->activity_list);
    if (activity == NULL) return;

    react(vm, activity);
}

void
run_net(vm_t *vm) {
    while (!list_is_empty(vm->activity_list)) {
        step_net(vm);
    }
}
