#include "index.h"

static void
react_by_primitive(vm_t *vm, task_t *task) {
    node_t *node = task->primitive_node;
    primitive_t *primitive = node->ctor->primitive;
    assert(primitive);

    // return input port values to the stack
    for (size_t i = 0; i < primitive->input_arity; i++) {
        value_t value = node->ports[i];
        if (is_wire(value)) {
            wire_t *wire = as_wire(value);
            assert(!is_wire(wire->opposite));
            stack_push(vm->value_stack, wire->opposite);
            wire_free_from_node(wire);
            vm_delete_wire(vm, wire);
        } else {
            stack_push(vm->value_stack, value);
        }
    }

    apply_primitive(vm, primitive, primitive->input_arity);

    // connect output port wires to values in the stack
    for (size_t i = 0; i < primitive->output_arity; i++) {
        size_t arity = primitive->input_arity + primitive->output_arity;
        size_t c = arity - 1 - i;
        value_t value = node->ports[c];
        wire_t *wire = as_wire(value);
        value_t top_value = stack_pop(vm->value_stack);
        wire_connect_value(vm, wire, top_value);
    }

    vm_delete_node(vm, task->primitive_node);
    task_destroy(&task);
}

static void
return_local_values(vm_t *vm, net_matcher_t *net_matcher) {
    list_t *local_name_list =
        net_pattern_local_name_list(net_matcher->net_pattern);
    char *name = list_first(local_name_list);
    while (name) {
        value_t value = hash_get(net_matcher->value_hash, name);
        assert(value);

        if (is_wire(value)) {
            wire_t *wire = as_wire(value);
            wire_free_from_node(wire);
        }

        stack_push(vm->value_stack, value);
        name = list_next(local_name_list);
    }
}

static void
delete_match_nodes(vm_t *vm, net_matcher_t *net_matcher) {
    size_t length = net_pattern_length(net_matcher->net_pattern);
    for (size_t i = 0; i < length; i++) {
        node_t *matched_node = net_matcher->matched_nodes[i];
        assert(matched_node);
        for (size_t k = 0; k < matched_node->ctor->arity; k++) {
            if (!is_wire(matched_node->ports[k]))
                continue;

            value_t value = matched_node->ports[k];
            if (is_wire(value)) {
                wire_t *wire = as_wire(value);
                if (wire_is_principal(wire))
                    vm_delete_wire(vm, wire);
            }
        }

        vm_delete_node(vm, matched_node);
    }
}

static void
react_by_rule(vm_t *vm, task_t *task) {
    return_local_values(vm, task->net_matcher);
    delete_match_nodes(vm, task->net_matcher);

    size_t base_length = stack_length(vm->return_stack);
    frame_t *frame = frame_new(task->rule->function);

    task_destroy(&task);

    stack_push(vm->return_stack, frame);
    run_until(vm, base_length);
}

void
react(vm_t *vm, task_t *task) {
    if (task_is_primitive(task))
        react_by_primitive(vm, task);
    else
        react_by_rule(vm, task);
}
