#include "index.h"

void
define_rule(mod_t *self, const char *name, rule_t *rule) {
    value_t value = mod_find(self, name);
    node_ctor_t *node_ctor = as_node_ctor(value);
    list_push(node_ctor->rule_list, rule);
}

void
define_rule_star(vm_t *vm, list_t *node_pattern_list, list_t *exp_list) {
    net_pattern_t *net_pattern = net_pattern_new(node_pattern_list);
    list_t *local_name_list = net_pattern_local_name_list(net_pattern);
    size_t arity = list_length(local_name_list);
    function_t *function = function_new(arity);
    compile_name_list(vm, function, local_name_list);
    compile_exp_list(vm, function, exp_list);
    function_build(function);

    node_pattern_t *node_pattern = list_first(node_pattern_list);
    size_t index = 0;
    while (node_pattern) {
        rule_t *rule = rule_new(index, net_pattern, function);
        define_rule(vm->mod, node_pattern->ctor->name, rule);
        node_pattern = list_next(node_pattern_list);
        index++;
    }

    return;
}
