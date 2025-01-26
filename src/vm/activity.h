#pragma once

struct activity_t {
    const rule_t *rule;
    net_matcher_t *net_matcher;
};

activity_t *activity_new(const rule_t *rule, net_matcher_t *net_matcher);
void activity_destroy(activity_t **self_pointer);
