#pragma once

void apply(worker_t *worker, value_t target, size_t arity);

void apply_primitive(worker_t *worker, primitive_t *primitive, size_t arity);
void apply_function(worker_t *worker, function_t *function, size_t arity);

void apply_node_input_ports(worker_t *worker, node_t *node, size_t arity);
void apply_node_output_ports(worker_t *worker, node_t *node, size_t arity);
void apply_node_ctor(worker_t *worker, node_ctor_t *node_ctor, size_t arity);
