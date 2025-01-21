#pragma once

void apply(vm_t *vm, const def_t *def, size_t arity);

void apply_function(vm_t *vm, const function_def_t *def);
void apply_node(vm_t *vm, const node_def_t *def, port_index_t input_arity);
