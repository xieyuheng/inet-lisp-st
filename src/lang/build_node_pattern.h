#pragma once

list_t *build_node_pattern_list(vm_t *vm, list_t *pattern_exp_list);
node_pattern_t *build_node_pattern(vm_t *vm, exp_t *pattern_exp);
