#include "index.h"

void
compile_arg_name_list(vm_t *vm, function_t *function, list_t *arg_name_list) {
    (void) vm;
    (void) function;
    (void) arg_name_list;
}

void
compile_exp_list(vm_t *vm, function_t *function, list_t *exp_list) {
    exp_t *exp = list_first(exp_list);
    while (exp) {
        compile_exp(vm, function, exp);
        exp = list_next(exp_list);
    }
}

void compile_exp(vm_t *vm, function_t *function, exp_t *exp) {
    (void) vm;
    (void) function;
    (void) exp;
}
