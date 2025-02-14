#include "index.h"

static void
apply_input_ports(vm_t *vm, node_t *node, size_t arity) {
    for (size_t c = 0; c < arity; c++) {
        wire_t *wire = stack_pop(vm->value_stack);
        size_t i = arity - 1 - c;
        wire->node = node;
        wire->index = i;
        node->ports[i] = wire;
    }
}

static void
return_output_ports(vm_t *vm, node_t *node, size_t arity) {
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
    apply_input_ports(vm, node, arity);
    return_output_ports(vm, node, arity);

    activate_node(vm, node);

    // NOTE for imported node ctor,
    // if is not enough to activate the new node only,
    // for example, i import `add`, but apply `add1`,
    // we can not find the def of `add1` in the current mod,
    // thus can not find the rules to activate it.
    // we can fix this problem by
    // also activate the neighboring nodes.

    for (size_t i = 0; i < node->ctor->arity; i++) {
        wire_t *wire = node->ports[i];
        assert(wire);
        assert(wire->opposite);
        if (wire->opposite->node)
            activate_node(vm, wire->opposite->node);
    }

    return;
}
