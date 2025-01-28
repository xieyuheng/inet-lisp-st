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
    (void) vm;
    (void) pattern_exp;
    return NULL;
}
