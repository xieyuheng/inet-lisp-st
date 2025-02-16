#pragma once

void compile_set_variables(vm_t *vm, function_t *function, list_t *name_list);
void compile_exp_list(vm_t *vm, function_t *function, list_t *exp_list);
void compile_exp(vm_t *vm, function_t *function, exp_t *exp);
