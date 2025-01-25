#include "index.h"

void
apply(vm_t *vm, value_t *target, size_t arity) {
    if (is_node_ctor(target)) {
        apply_node_ctor(vm, as_node_ctor(target), arity);
        return;
    }

    if (is_function(target)) {
        apply_function(vm, as_function(target), arity);
        return;
    }

    fprintf(stderr, "[apply] unknown target: ");
    value_print(target, stderr);
    exit(1);
}
