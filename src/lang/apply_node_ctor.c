#include "index.h"

void
apply_node_input_ports(vm_t *vm, node_t *node, size_t arity) {
    for (size_t c = 0; c < arity; c++) {
        value_t value = stack_pop(vm->value_stack);
        size_t i = arity - 1 - c;
        node_set(node, i, value);
    }
}

void
apply_node_output_ports(vm_t *vm, node_t *node, size_t arity) {
    size_t output_arity = node->ctor->arity - arity;
    for (size_t c = 0; c < output_arity; c++) {
        wire_t *node_wire = wire_new();
        wire_t *free_wire = wire_new();

        node_wire->opposite = free_wire;
        free_wire->opposite = node_wire;

        size_t i = arity + c;
        node_wire->node = node;
        node_wire->index = i;
        node->ports[i] = node_wire;

        stack_push(vm->value_stack, free_wire);
    }
}

void
apply_node_ctor(vm_t *vm, node_ctor_t *node_ctor, size_t arity) {
    node_t *node = vm_add_node(vm, node_ctor);
    apply_node_input_ports(vm, node, arity);
    apply_node_output_ports(vm, node, arity);
    schedule_task_by_and_neighbor(vm, node);
}
