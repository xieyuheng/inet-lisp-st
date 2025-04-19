#include "index.h"

void
apply_node_ctor(worker_t *worker, node_ctor_t *node_ctor, size_t arity) {
    node_t *node = worker_add_node(worker, node_ctor);
    worker_reconnect_node(worker, node, arity);
}
