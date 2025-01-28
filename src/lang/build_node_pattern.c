#include "index.h"

list_t *
build_node_pattern_list(vm_t *vm, list_t *pattern_exp_list) {
    list_t *node_pattern_list =
        list_new_with((destroy_fn_t *) node_pattern_destroy);
    exp_t *pattern_exp = list_first(pattern_exp_list);
    while (pattern_exp) {
        list_push(node_pattern_list, build_node_pattern(vm, pattern_exp));
        pattern_exp = list_next(pattern_exp_list);
    }

    return node_pattern_list;
}

node_pattern_t *
build_node_pattern(vm_t *vm, exp_t *pattern_exp) {
    assert(pattern_exp->kind == EXP_AP);
    exp_t *target = pattern_exp->ap.target;
    list_t *arg_list = pattern_exp->ap.arg_list;

    assert(target->kind == EXP_VAR);
    const def_t *def = mod_find_def(vm->mod, target->var.name);

    assert(def->kind == DEF_NODE);
    node_pattern_t *node_pattern = node_pattern_new(def->node.ctor);

    exp_t *arg_exp = list_first(arg_list);
    size_t index = 0;
    while (arg_exp) {
        assert(arg_exp->kind == EXP_VAR);
        char *name = string_copy(arg_exp->var.name);
        port_info_t *port_info = port_info_from_name(name);
        node_pattern_set_port_info(node_pattern, index, port_info);
        arg_exp = list_next(arg_list);
        index++;
    }

    return node_pattern;
}
