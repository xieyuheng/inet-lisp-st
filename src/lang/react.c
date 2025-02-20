#include "index.h"

static void
react_by_primitive(worker_t *worker, task_t *task) {
    node_t *node = task->primitive_node;
    primitive_t *primitive = node->ctor->primitive;
    assert(primitive);

    // return input port values to the stack
    for (size_t i = 0; i < primitive->input_arity; i++) {
        value_t value = node->ports[i];
        if (is_wire(value)) {
            wire_t *wire = as_wire(value);
            assert(!is_wire(wire->opposite));
            stack_push(worker->value_stack, wire->opposite);
            wire_free_from_node(wire);
            worker_delete_wire(worker, wire);
        } else {
            stack_push(worker->value_stack, value);
        }
    }

    apply_primitive(worker, primitive, primitive->input_arity);

    // connect output port wires to values in the stack
    for (size_t i = 0; i < primitive->output_arity; i++) {
        size_t arity = primitive->input_arity + primitive->output_arity;
        size_t c = arity - 1 - i;
        value_t value = node->ports[c];
        wire_t *wire = as_wire(value);
        value_t top_value = stack_pop(worker->value_stack);
        wire_connect_value(worker, wire, top_value);
    }

    worker_delete_node(worker, task->primitive_node);
    task_destroy(&task);
}

static void
return_local_values(worker_t *worker, net_matcher_t *net_matcher) {
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

        stack_push(worker->value_stack, value);
        name = list_next(local_name_list);
    }
}

static void
delete_match_nodes(worker_t *worker, net_matcher_t *net_matcher) {
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
                    worker_delete_wire(worker, wire);
            }
        }

        worker_delete_node(worker, matched_node);
    }
}

static void
react_by_rule(worker_t *worker, task_t *task) {
    return_local_values(worker, task->net_matcher);
    delete_match_nodes(worker, task->net_matcher);

    size_t base_length = stack_length(worker->return_stack);
    frame_t *frame = frame_new(task->rule->function);

    task_destroy(&task);

    stack_push(worker->return_stack, frame);
    run_until(worker, base_length);
}

void
react(worker_t *worker, task_t *task) {
    if (task_is_primitive(task))
        react_by_primitive(worker, task);
    else
        react_by_rule(worker, task);
}
