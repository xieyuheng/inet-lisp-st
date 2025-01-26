#pragma once

struct rule_t {
    net_pattern_t *net_pattern;
    function_t *function;
};

rule_t *rule_new(net_pattern_t *net_pattern, function_t *function);
void rule_destroy(rule_t **self_pointer);
