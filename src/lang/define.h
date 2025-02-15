#pragma once

void define(mod_t *self, const char *name, value_t value);

void define_rule(mod_t *self, const char *name, rule_t *rule);
void define_rule_star(vm_t *vm, list_t *node_pattern_list, list_t *exp_list);

void define_node(vm_t *vm, const char *name, list_t *port_name_list);

void define_primitive_vm_fn(mod_t *mod, const char *name, size_t input_arity, size_t output_arity, primitive_vm_fn_t *primitive_vm_fn);
void define_primitive_fn_0(mod_t *mod, const char *name, primitive_fn_0_t *primitive_fn_0);
void define_primitive_fn_1(mod_t *mod, const char *name, primitive_fn_1_t *primitive_fn_1);
void define_primitive_fn_2(mod_t *mod, const char *name, primitive_fn_2_t *primitive_fn_2);
void define_primitive_fn_3(mod_t *mod, const char *name, primitive_fn_3_t *primitive_fn_3);
void define_primitive_fn_4(mod_t *mod, const char *name, primitive_fn_4_t *primitive_fn_4);

void define_primitive_node(mod_t *mod, const char *name, const char *port_names[]);
