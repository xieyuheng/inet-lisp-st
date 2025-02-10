#include "index.h"

static void
define_node(vm_t *vm, const char *name, list_t *port_name_list) {
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

    mod_define(vm->mod, def);
    return;
}

static node_pattern_t *
build_node_pattern(vm_t *vm, exp_t *pattern_exp) {
    assert(pattern_exp->kind == EXP_AP);
    exp_t *target = pattern_exp->ap.target;
    list_t *arg_list = pattern_exp->ap.arg_list;

    assert(target->kind == EXP_VAR);
    const def_t *def = mod_find_def(vm->mod, target->var.name);

    assert(def->kind == DEF_NODE);
    node_pattern_t *node_pattern = node_pattern_new(def->node.ctor);

    exp_t *arg_exp = list_first(arg_list);
    size_t index = 0;
    while (arg_exp) {
        assert(arg_exp->kind == EXP_VAR);
        char *name = string_copy(arg_exp->var.name);
        port_info_t *port_info = port_info_from_name(name);
        node_pattern_set_port_info(node_pattern, index, port_info);
        arg_exp = list_next(arg_list);
        index++;
    }

    return node_pattern;
}

static list_t *
build_node_pattern_list(vm_t *vm, list_t *pattern_exp_list) {
    list_t *node_pattern_list =
        list_new_with((destroy_fn_t *) node_pattern_destroy);
    exp_t *pattern_exp = list_first(pattern_exp_list);
    while (pattern_exp) {
        list_push(node_pattern_list, build_node_pattern(vm, pattern_exp));
        pattern_exp = list_next(pattern_exp_list);
    }

    return node_pattern_list;
}

static void
define_rule_star(vm_t *vm, list_t *node_pattern_list, list_t *exp_list) {
    net_pattern_t *net_pattern = net_pattern_new(node_pattern_list);
    list_t *local_name_list = net_pattern_local_name_list(net_pattern);
    size_t arity = list_length(local_name_list);
    function_t *function = function_new(arity);
    compile_bind(vm, function, local_name_list);
    compile_exp_list(vm, function, exp_list);
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

static void
translate_pattern_sub_tree(
    vm_t *vm,
    exp_t *pattern_exp,
    const char *last_arg_name,
    list_t *pattern_exp_list
);

static list_t *
translate_pattern_arg_list(
    vm_t *vm,
    list_t *arg_list,
    list_t *pattern_exp_list
) {
    list_t *new_arg_list = exp_list_new();
    exp_t *arg_exp = list_first(arg_list);
    while (arg_exp) {
        if (arg_exp->kind == EXP_VAR) {
            list_push(new_arg_list, exp_copy(arg_exp));
        } else {
            char *fresh_name = vm_fresh_name(vm);
            char *name = string_append(fresh_name, "!");
            string_destroy(&fresh_name);
            translate_pattern_sub_tree(vm, arg_exp, name, pattern_exp_list);
            list_push(new_arg_list, exp_var(name));
        }

        arg_exp = list_next(arg_list);
    }

    return new_arg_list;
}

static void
translate_pattern_sub_tree(
    vm_t *vm,
    exp_t *pattern_exp,
    const char *last_arg_name,
    list_t *pattern_exp_list
) {
    assert(pattern_exp->kind == EXP_AP);
    exp_t *target = exp_copy(pattern_exp->ap.target);
    list_t *arg_list = translate_pattern_arg_list(vm, pattern_exp->ap.arg_list, pattern_exp_list);
    list_push(arg_list, exp_var(string_copy(last_arg_name)));
    list_unshift(pattern_exp_list, exp_ap(target, arg_list));
}

static list_t *
translate_pattern_tree(vm_t *vm, exp_t *pattern_exp) {
    assert(pattern_exp->kind == EXP_AP);
    exp_t *target = exp_copy(pattern_exp->ap.target);
    list_t *pattern_exp_list = exp_list_new();
    list_t *arg_list = translate_pattern_arg_list(vm, pattern_exp->ap.arg_list, pattern_exp_list);
    list_unshift(pattern_exp_list, exp_ap(target, arg_list));
    return pattern_exp_list;
}

static void
compute_exp(vm_t *vm, exp_t *exp) {
    size_t arity = 0;
    function_t *function = function_new(arity);
    compile_exp(vm, function, exp);
    function_build(function);

    size_t base_length = stack_length(vm->return_stack);
    frame_t *frame = frame_new(function);
    stack_push(vm->return_stack, frame);
    run_until(vm, base_length);

    function_destroy(&function);
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
        define_node(vm, stmt->define_node.name, stmt->define_node.port_name_list);
        return;
    }

    case STMT_DEFINE_RULE: {
        list_t *pattern_exp_list = translate_pattern_tree(vm, stmt->define_rule.pattern_exp);
        define_rule_star(
            vm,
            build_node_pattern_list(vm, pattern_exp_list),
            stmt->define_rule.exp_list);
        list_destroy(&pattern_exp_list);
        return;
    }

    case STMT_DEFINE_RULE_STAR: {
        list_t *pattern_exp_list = stmt->define_rule_star.pattern_exp_list;
        define_rule_star(
            vm,
            build_node_pattern_list(vm, pattern_exp_list),
            stmt->define_rule_star.exp_list);
        return;
    }

    case STMT_COMPUTE_EXP: {
        compute_exp(vm, stmt->compute_exp.exp);
        return;
    }

    case STMT_IMPORT: {
        // TODO
        return;
    }
    }
}
