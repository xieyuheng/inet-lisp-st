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
activity_by_node(vm_t *vm, node_t *node) {
    assert(node);

    if (set_has(vm->matched_node_set, node)) return;

    const def_t *def = mod_find_def(vm->mod, node->ctor->name);
    if (def == NULL) return;

    rule_t *rule = list_first(def->node.rule_list);
    while (rule) {
        net_matcher_t *net_matcher = match_net(rule->net_pattern, rule->starting_index, node);
        if (net_matcher) {
            // {
            //     function_print(rule->function, stdout);
            //     printf("\n");
            // }

            list_push(vm->activity_list, activity_new(rule, net_matcher));
            size_t length = net_pattern_length(rule->net_pattern);
            for (size_t i = 0; i < length; i++) {
                node_t *matched_node = net_matcher->matched_nodes[i];
                set_add(vm->matched_node_set, matched_node);
            }
            return;
        }

        rule = list_next(def->node.rule_list);
    }
}
