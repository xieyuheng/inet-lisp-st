#include "index.h"

activity_t *
activity_from_rule(const rule_t *rule, net_matcher_t *net_matcher) {
    activity_t *self = new(activity_t);
    self->rule = rule;
    self->net_matcher = net_matcher;
    return self;
}

activity_t *
activity_from_primitive_node(node_t *primitive_node) {
    activity_t *self = new(activity_t);
    assert(node_is_primitive(primitive_node));
    self->primitive_node = primitive_node;
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

bool
activity_is_primitive(const activity_t *self) {
    return self->primitive_node != NULL;
}

static void
activate_primitive_node(vm_t *vm, node_t *node) {
    assert(node_is_primitive(node));

    for (size_t i = 0; i < node->ctor->arity; i++) {
        if (!node->ctor->port_infos[i]->is_principal)
            continue;

        value_t value = node->ports[i];
        // NOTE be careful that there are two cases:
        // - (1) `[value]`   -- ready
        // - (2) `-<[value]` -- ready
        // - (3) `-<>-`      -- NOT ready
        if (is_wire(value) && is_wire(as_wire(value)->opposite)) {
            // do nothing when NOT ready
            return;
        }
    }

    list_push(vm->activity_list, activity_from_primitive_node(node));
    set_add(vm->matched_node_set, node);
}

void
activate_node(vm_t *vm, node_t *node) {
    assert(node);

    if (set_has(vm->matched_node_set, node)) return;

    if (node_is_primitive(node)) {
        activate_primitive_node(vm, node);
        return;
    }

    rule_t *rule = list_first(node->ctor->rule_list);
    while (rule) {
        net_matcher_t *net_matcher =
            match_net(rule->net_pattern, rule->starting_index, node);
        if (net_matcher) {
            list_push(vm->activity_list, activity_from_rule(rule, net_matcher));
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
        if (!is_wire(value)) continue;
        wire_t *wire = as_wire(value);
        if (is_wire(wire->opposite) && as_wire(wire->opposite)->node)
            activate_node(vm, as_wire(wire->opposite)->node);
    }
}

void
activity_print(activity_t *self, file_t *file) {
    fprintf(file, "<activity>\n");
    rule_print(self->rule, file);
    net_matcher_print(self->net_matcher, file);
    fprintf(file, "</activity>\n");
}
