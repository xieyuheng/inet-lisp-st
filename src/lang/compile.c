#include "index.h"

void
compile_bind(vm_t *vm, function_t *function, list_t *name_list) {
    (void) vm;

    size_t index = hash_length(function->local_index_hash);
    char *name = list_last(name_list);
    while (name) {
        if (hash_has(function->local_index_hash, name)) {
            size_t old_index = (size_t) hash_get(function->local_index_hash, name);
            function_add_op(function, op_local_set(old_index));
        } else {
            hash_set(function->local_index_hash, name, (void *) index);
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

static bool
maybe_compile_local_get(function_t *function, const char *name) {
    if (!hash_has(function->local_index_hash, name)) return false;

    size_t index = (size_t) hash_get(function->local_index_hash, name);
    function_add_op(function, op_local_get(index));
    return true;
}

static void
compile_lookup(vm_t *vm, function_t *function, const char *name) {
    const def_t *def = mod_find_def(vm->mod, name);
    if (def == NULL) {
        fprintf(stderr, "[compile_lookup] undefined name: %s\n", name);
        fprintf(stderr, "[compile_lookup] function:\n");
        function_print(function, stderr);
        exit(1);
    }

    function_add_op(function, op_lookup(def));
}

void
compile_exp(vm_t *vm, function_t *function, exp_t *exp) {
    switch (exp->kind) {
    case EXP_VAR: {
        if (maybe_compile_local_get(function, exp->var.name))
            return;

        compile_lookup(vm, function, exp->var.name);
        return;
    }

    case EXP_AP: {
        compile_exp_list(vm, function, exp->ap.arg_list);
        compile_exp(vm, function, exp->ap.target);
        size_t arity = list_length(exp->ap.arg_list);
        function_add_op(function, op_apply(arity));
        return;
    }

    case EXP_BIND: {
        compile_bind(vm, function, exp->bind.name_list);
        return;
    }
    }
}
