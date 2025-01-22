#include "index.h"

void
execute(vm_t *vm, stmt_t *stmt) {
    switch (stmt->kind) {
    case STMT_DEFINE_FUNCTION: {
        size_t arity = list_length(stmt->define_function.arg_name_list);
        function_t *function = function_new(arity);
        compile_bind(vm, function, stmt->define_function.arg_name_list);
        compile_exp_list(vm, function, stmt->define_function.exp_list);
        function_build(function);

        define_function(vm->mod, stmt->define_function.name, function);
        return;
    }

    case STMT_DEFINE_NODE: {
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
        size_t arity = 0;
        function_t *function = function_new(arity);
        compile_exp(vm, function, stmt->compute_exp.exp);
        function_build(function);

        size_t base_length = stack_length(vm->return_stack);
        frame_t *frame = frame_new(function);
        stack_push(vm->return_stack, frame);
        run_until(vm, base_length);

        function_destroy(&function);
        return;
    }
    }
}
