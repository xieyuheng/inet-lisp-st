#include "index.h"

void
lookup(vm_t *vm, const def_t *def) {
    switch (def->kind) {
    case DEF_FUNCTION: {
        stack_push(vm->value_stack, def->function);
        return;
    }

    case DEF_NODE: {
        stack_push(vm->value_stack, def->node_ctor);
        return;
    }
    }
}
