#include "index.h"

void
call(vm_t *vm, const def_t *def, size_t arity) {
    switch (def->kind) {
    case DEF_FUNCTION: {
        call_function(vm, def->function);
        return;
    }

    case DEF_NODE: {
        call_node(vm, def->node, arity);
        return;
    }
    }
}
