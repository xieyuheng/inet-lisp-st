#pragma once

struct activity_t {
    const rule_t *rule;
    net_matcher_t *net_matcher;
};

activity_t *activity_from_rule(const rule_t *rule, net_matcher_t *net_matcher);
void activity_destroy(activity_t **self_pointer);

void activate_node(vm_t *vm, node_t *node);
void activate_node_and_neighbor(vm_t *vm, node_t *node);

void activity_print(activity_t *self, file_t *file);
