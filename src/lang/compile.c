#include "index.h"

void
compile_arg_name_list(vm_t *vm, function_t *function, list_t *arg_name_list) {
    (void) vm;

    function_ctx_t *ctx = function->ctx;
    size_t index = hash_length(ctx->local_index_hash);
    char *arg_name = list_last(arg_name_list);
    while (arg_name) {
        if (hash_has(ctx->local_index_hash, arg_name)) {
            size_t old_index = (size_t) hash_get(ctx->local_index_hash, arg_name);
            function_add_op(function, op_local_set(old_index));
        } else {
            hash_set(ctx->local_index_hash, arg_name, (void *) index);
            function_add_op(function, op_local_set(index));
            index++;
        }

        arg_name = list_prev(arg_name_list);
    }
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
