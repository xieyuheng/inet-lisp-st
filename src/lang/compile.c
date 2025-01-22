#include "index.h"

void
compile_bind(vm_t *vm, function_t *function, list_t *name_list) {
    (void) vm;

    function_ctx_t *ctx = function->ctx;
    size_t index = hash_length(ctx->local_index_hash);
    char *name = list_last(name_list);
    while (name) {
        if (hash_has(ctx->local_index_hash, name)) {
            size_t old_index = (size_t) hash_get(ctx->local_index_hash, name);
            function_add_op(function, op_local_set(old_index));
        } else {
            hash_set(ctx->local_index_hash, name, (void *) index);
            function_add_op(function, op_local_set(index));
            index++;
        }

        name = list_prev(name_list);
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

void
compile_exp(vm_t *vm, function_t *function, exp_t *exp) {
    switch (exp->kind) {
    case EXP_VAR: {
        return;
    }

    case EXP_AP: {
        return;
    }

    case EXP_BIND: {
        compile_bind(vm, function, exp->bind.name_list);
        return;
    }
    }
}
