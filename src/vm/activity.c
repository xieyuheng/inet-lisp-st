#include "index.h"

activity_t *
activity_new(const rule_t *rule, net_matcher_t *net_matcher) {
    activity_t *self = new(activity_t);
    self->rule = rule;
    self->net_matcher = net_matcher;
    return self;
}

void
activity_destroy(activity_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        activity_t *self = *self_pointer;
        net_matcher_destroy(&self->net_matcher);
        free(self);
        *self_pointer = NULL;
    }
}

void
activate_node(vm_t *vm, node_t *node) {
    assert(node);

    if (set_has(vm->matched_node_set, node)) return;

    rule_t *rule = list_first(node->ctor->rule_list);
    while (rule) {
        net_matcher_t *net_matcher =
            match_net(rule->net_pattern, rule->starting_index, node);
        if (net_matcher) {
            list_push(vm->activity_list, activity_new(rule, net_matcher));
            size_t length = net_pattern_length(rule->net_pattern);
            for (size_t i = 0; i < length; i++)
                set_add(vm->matched_node_set, net_matcher->matched_nodes[i]);
            return;
        }

        rule = list_next(node->ctor->rule_list);
    }
}

void
activate_node_and_neighbor(vm_t *vm, node_t *node) {
    activate_node(vm, node);

    // NOTE for imported node ctor,
    // if is not enough to activate the new node only,
    // for example, i import `add`, but apply `add1`,
    // we can not find the def of `add1` in the current mod,
    // thus can not find the rules to activate it.
    // we can fix this problem by
    // also activate the neighboring nodes.

    for (size_t i = 0; i < node->ctor->arity; i++) {
        value_t value = node->ports[i];
        if (!is_wire(value))
            continue;

        wire_t *wire = as_wire(value);
        assert(wire->opposite);
        if (wire->opposite->node)
            activate_node(vm, wire->opposite->node);
    }
}

void
activity_print(activity_t *self, file_t *file) {
    fprintf(file, "<activity>\n");
    rule_print(self->rule, file);
    net_matcher_print(self->net_matcher, file);
    fprintf(file, "</activity>\n");
}
