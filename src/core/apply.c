#include "index.h"

void
apply(worker_t *worker, value_t target, size_t arity) {
    if (is_node_ctor(target)) {
        apply_node_ctor(worker, as_node_ctor(target), arity);
    } else if (is_function(target)) {
        apply_function(worker, as_function(target), arity);
    } else if (is_primitive(target)) {
        apply_primitive(worker, as_primitive(target), arity);
    } else {
        fprintf(stderr, "[apply] unknown target: ");
        value_print(target, stderr);
        exit(1);
    }
}
