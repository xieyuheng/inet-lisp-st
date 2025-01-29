#include "index.h"

static void
define_node(mod_t *mod, const char *name, list_t *port_name_list) {
    size_t arity = list_length(port_name_list);
    node_ctor_t *node_ctor = node_ctor_new(name, arity);
    def_t *def = def_node(node_ctor);

    size_t index = 0;
    char *port_name = list_first(port_name_list);
    while (port_name) {
        def->node.ctor->port_infos[index] = port_info_from_name(string_copy(port_name));
        port_name = list_next(port_name_list);
        index++;
    }

    mod_define(mod, def);
    return;
}

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

    case STMT_DEFINE_RULE_STAR: {
        {
            stmt_print(stmt, stdout);
            fprintf(stdout, "\n");
        }

        list_t *node_pattern_list =
            build_node_pattern_list(vm, stmt->define_rule_star.pattern_exp_list);
        net_pattern_t *net_pattern = net_pattern_new(node_pattern_list);
        list_t *local_name_list = net_pattern_local_name_list(net_pattern);
        list_t *reversed_local_name_list = list_copy_reversed(local_name_list);
        size_t arity = list_length(reversed_local_name_list);
        function_t *function = function_new(arity);
        compile_bind(vm, function, reversed_local_name_list);
        list_destroy(&reversed_local_name_list);
        compile_exp_list(vm, function, stmt->define_rule_star.exp_list);
        function_build(function);

        node_pattern_t *node_pattern = list_first(node_pattern_list);
        size_t index = 0;
        while (node_pattern) {
            rule_t *rule = rule_new(index, net_pattern, function);
            mod_define_rule(vm->mod, node_pattern->ctor->name, rule);
            node_pattern = list_next(node_pattern_list);
            index++;
        }

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
