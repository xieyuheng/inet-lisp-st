#include "index.h"

static wire_t *
connect_wire(worker_t* worker, wire_t *first_wire, wire_t *second_wire) {
    value_t first_opposite = first_wire->opposite;
    value_t second_opposite = second_wire->opposite;

    if (is_wire(first_opposite) && is_wire(second_opposite)) {
        wire_t *first_opposite_wire = as_wire(first_opposite);
        wire_t *second_opposite_wire = as_wire(second_opposite);

        first_opposite_wire->opposite = second_opposite_wire;
        second_opposite_wire->opposite = first_opposite_wire;

        worker_delete_wire(worker, first_wire);
        worker_delete_wire(worker, second_wire);

        if (first_opposite_wire->node)
            maybe_return_task_by_node(worker, first_opposite_wire->node);
        if (second_opposite_wire->node)
            maybe_return_task_by_node(worker, second_opposite_wire->node);

        return first_opposite_wire;
    } else if (is_wire(first_opposite)) {
        wire_t *first_opposite_wire = as_wire(first_opposite);
        first_opposite_wire->opposite = second_opposite;

        worker_delete_wire(worker, first_wire);
        worker_delete_wire(worker, second_wire);

        if (first_opposite_wire->node)
            maybe_return_task_by_node(worker, first_opposite_wire->node);

        return first_opposite_wire;
    } else if (is_wire(second_opposite)) {
        wire_t *second_opposite_wire = as_wire(second_opposite);
        second_opposite_wire->opposite = first_opposite;

        worker_delete_wire(worker, first_wire);
        worker_delete_wire(worker, second_wire);

        if (second_opposite_wire->node)
            maybe_return_task_by_node(worker, second_opposite_wire->node);

        return second_opposite_wire;
    } else {
        fprintf(stderr, "[connect_wire] can not connect wires with non-wire opposite\n");
        fprintf(stderr, "[connect_wire] first_opposite: ");
        value_print(first_opposite, stderr);
        fprintf(stderr, "\n");
        fprintf(stderr, "[connect_wire] second_opposite: ");
        value_print(second_opposite, stderr);
        fprintf(stderr, "\n");
        exit(1);
    }
}

wire_t *
connect_value(worker_t* worker, wire_t *wire, value_t value) {
    if (is_wire(value)) {
        return connect_wire(worker, wire, value);
    }

     value_t opposite = wire->opposite;
     if (is_wire(opposite)) {
         wire_t *opposite_wire = as_wire(wire->opposite);
         opposite_wire->opposite = value;

         worker_delete_wire(worker, wire);

         if (opposite_wire->node)
             maybe_return_task_by_node(worker, opposite_wire->node);

         return opposite_wire;
     } else {
        fprintf(stderr, "[connect_value] can not connect wire with non-wire opposite to value\n");
        fprintf(stderr, "[connect_value] opposite: ");
        value_print(opposite, stderr);
        fprintf(stderr, "\n");
        exit(1);
    }
}

static void
react_by_primitive(worker_t *worker, task_t *task) {
    node_t *node = task->primitive_node;
    primitive_t *primitive = as_primitive(node->ctor->primitive);
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
        connect_value(worker, wire, top_value);
    }

    worker_delete_node(worker, task->primitive_node);
    task_destroy(&task);
}

static void
return_local_values(worker_t *worker, net_matcher_t *net_matcher) {
    array_t *local_name_array =
        net_pattern_local_name_array(net_matcher->net_pattern);

    for (size_t i = 0; i < array_length(local_name_array); i++) {
        char *name = array_get(local_name_array, i);
        value_t value = hash_get(net_matcher->value_hash, name);
        assert(value);

        if (is_wire(value)) {
            wire_t *wire = as_wire(value);
            wire_free_from_node(wire);
        }

        stack_push(worker->value_stack, value);
    }
}

static void
delete_matched_nodes(worker_t *worker, net_matcher_t *net_matcher) {
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
    delete_matched_nodes(worker, task->net_matcher);

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
