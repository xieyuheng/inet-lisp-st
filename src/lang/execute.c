#include "index.h"

void
execute(vm_t *vm, stmt_t *stmt) {
    switch (stmt->kind) {
    case STMT_DEFINE_FUNCTION: {
        {
            stmt_print(stmt, stdout);
            fprintf(stdout, "\n");
        }

        size_t arity = list_length(stmt->define_function.arg_name_list);
        function_t *function = function_new(arity);
        compile_bind(vm, function, stmt->define_function.arg_name_list);
        compile_exp_list(vm, function, stmt->define_function.exp_list);
        define_function(vm->mod, stmt->define_function.name, function);
        return;
    }

    case STMT_DEFINE_NODE: {
        {
            stmt_print(stmt, stdout);
            fprintf(stdout, "\n");
        }

        define_node(vm->mod, stmt->define_node.name, stmt->define_node.port_name_list);
        return;
    }

    case STMT_DEFINE_RULE: {
        {
            stmt_print(stmt, stdout);
            fprintf(stdout, "\n");
        }

        // TODO
        return;
    }

    case STMT_COMPUTE_EXP: {
        {
            stmt_print(stmt, stdout);
            fprintf(stdout, "\n");
        }

        // TODO
        return;
    }
    }
}
