#include "index.h"

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

void
react(vm_t *vm, activity_t *activity) {
    if (activity_is_primitive(activity)) {
        node_t *node = activity->primitive_node;
        primitive_t *primitive = node->ctor->primitive;
        assert(primitive);
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

        for (size_t i = 0; i < primitive->output_arity; i++) {
            size_t arity = primitive->input_arity + primitive->output_arity;
            size_t c = arity - 1 - i;
            value_t value = node->ports[c];
            wire_t *wire = as_wire(value);
            value_t top_value = stack_pop(vm->value_stack);
            wire_connect_value(vm, wire, top_value);
        }

        vm_delete_node(vm, activity->primitive_node);
        activity_destroy(&activity);
    } else {
        return_local_values(vm, activity->net_matcher);
        delete_match_nodes(vm, activity->net_matcher);

        size_t base_length = stack_length(vm->return_stack);
        frame_t *frame = frame_new(activity->rule->function);

        activity_destroy(&activity);

        stack_push(vm->return_stack, frame);
        run_until(vm, base_length);
    }
}
