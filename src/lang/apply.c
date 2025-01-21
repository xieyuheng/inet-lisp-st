#include "index.h"

void
apply(vm_t *vm, value_t *target, size_t arity) {
    if (is_node(target)) {
        apply_node(vm, as_node(target), arity);
        return;
    }

    if (is_function(target)) {
        apply_function(vm, as_function(target), arity);
        return;
    }

    assert(false && "[apply] unknown target");
}
