#include "index.h"

void
compile_set_variables(vm_t *vm, function_t *function, list_t *name_list) {
    (void) vm;

    size_t index = hash_length(function->local_index_hash);
    char *name = list_last(name_list);
    while (name) {
        if (hash_has(function->local_index_hash, name)) {
            size_t old_index = (size_t) hash_get(function->local_index_hash, name);
            function_add_op(function, op_set_variable(old_index));
        } else {
            assert(hash_set(function->local_index_hash, string_copy(name), (void *) index));
            function_add_op(function, op_set_variable(index));
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
maybe_compile_get_variable(function_t *function, const char *name) {
    if (!hash_has(function->local_index_hash, name)) return false;

    size_t index = (size_t) hash_get(function->local_index_hash, name);
    function_add_op(function, op_get_variable(index));
    return true;
}

static void
compile_literal(vm_t *vm, function_t *function, const char *name) {
    value_t value = mod_find(vm->mod, name);
    if (value == NULL) {
        fprintf(stderr, "[compile_literal] undefined name: %s\n", name);
        fprintf(stderr, "[compile_literal] function:\n");
        function_print(function, stderr);
        exit(1);
    }

    function_add_op(function, op_literal(value));
}

void
compile_exp(vm_t *vm, function_t *function, exp_t *exp) {
    switch (exp->kind) {
    case EXP_VAR: {
        if (maybe_compile_get_variable(function, exp->var.name))
            return;

        compile_literal(vm, function, exp->var.name);
        return;
    }

    case EXP_AP: {
        compile_exp_list(vm, function, exp->ap.arg_list);
        compile_exp(vm, function, exp->ap.target);
        size_t arity = list_length(exp->ap.arg_list);
        function_add_op(function, op_apply(arity));
        return;
    }

    case EXP_LET: {
        compile_exp(vm, function, exp->let.exp);
        compile_set_variables(vm, function, exp->let.name_list);
        return;
    }

    case EXP_INT: {
        function_add_op(function, op_literal(xint(exp->i.target)));
        return;
    }

    case EXP_FLOAT: {
        function_add_op(function, op_literal(xfloat(exp->f.target)));
        return;
    }
    }
}
