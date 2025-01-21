#include "index.h"

void
apply(vm_t *vm, const def_t *def, size_t arity) {
    switch (def->kind) {
    case DEF_FUNCTION: {
        apply_function(vm, def->function);
        return;
    }

    case DEF_NODE: {
        apply_node(vm, def->node, arity);
        return;
    }
    }
}
