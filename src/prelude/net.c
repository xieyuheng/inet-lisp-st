#include "index.h"

void
x_connect(vm_t *vm) {
    value_t second = stack_pop(vm->value_stack);
    value_t first = stack_pop(vm->value_stack);

    if (is_wire(first) && is_wire(second)) {
        wire_connect_wire(vm, as_wire(second), as_wire(first));
    } else if (is_wire(first)) {
        wire_connect_value(vm, as_wire(first), second);
    } else if (is_wire(second)) {
        wire_connect_value(vm, as_wire(second), first);
    } else {
        fprintf(stderr, "[x_connect] can not connect value to value\n");
        fprintf(stderr, "[x_connect] first: ");
        value_print(first, stderr);
        fprintf(stderr, "\n");
        fprintf(stderr, "[x_connect] second: ");
        value_print(second, stderr);
        fprintf(stderr, "\n");
        exit(1);
    }
}

void
x_wire_print_net(vm_t *vm) {
    wire_t *wire = as_wire(stack_top(vm->value_stack));
    wire_print_net(wire, stdout);
    fprintf(stdout, "\n");
}

void
x_link(vm_t *vm) {
    wire_t *first_wire = wire_new();
    wire_t *second_wire = wire_new();

    first_wire->opposite = second_wire;
    second_wire->opposite = first_wire;

    stack_push(vm->value_stack, first_wire);
    stack_push(vm->value_stack, second_wire);
}

void
x_run(vm_t *vm) {
    run_net(vm);
}

void
x_inspect_run(vm_t *vm) {
    x_wire_print_net(vm);
    x_run(vm);
    x_wire_print_net(vm);
}

void
x_debug(vm_t *vm) {
    fprintf(stdout, "[debug] start\n");
    debug_start(vm);
    fprintf(stdout, "[debug] end\n");
    fprintf(stdout, "\n");
}
