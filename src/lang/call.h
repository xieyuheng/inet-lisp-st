#pragma once

void call(vm_t *vm, const def_t *def, size_t arity);

void call_function(vm_t *vm, const function_def_t *def);
void call_node(vm_t *vm, const node_def_t *def, port_index_t input_arity);
