#include "index.h"

static void
apply_node_input_ports(worker_t *worker, node_t *node, size_t arity) {
    for (size_t c = 0; c < arity; c++) {
        value_t value = stack_pop(worker->value_stack);
        size_t i = arity - 1 - c;
        node_set(node, i, value);
    }
}

static void
apply_node_output_ports(worker_t *worker, node_t *node, size_t arity) {
    size_t output_arity = node->ctor->arity - arity;
    for (size_t c = 0; c < output_arity; c++) {
        wire_t *node_wire = wire_new();
        wire_t *free_wire = wire_new();

        node_wire->opposite = free_wire;
        free_wire->opposite = node_wire;

        size_t i = arity + c;
        node_wire->node = node;
        node_wire->index = i;
        node_set(node, i, node_wire);

        stack_push(worker->value_stack, free_wire);
    }
}

void
apply_node(worker_t *worker, node_t *node, size_t arity) {
    apply_node_input_ports(worker, node, arity);
    apply_node_output_ports(worker, node, arity);
    maybe_return_task_by_node_and_neighbor(worker, node);
}

void
apply_node_ctor(worker_t *worker, node_ctor_t *node_ctor, size_t arity) {
    node_t *node = worker_add_node(worker, node_ctor);
    apply_node(worker, node, arity);
}
