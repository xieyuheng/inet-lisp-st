#include "index.h"

void
lookup(vm_t *vm, const def_t *def) {
    switch (def->kind) {
    case DEF_FUNCTION: {
        stack_push(vm->value_stack, def->function_def->function);
        return;
    }

    case DEF_NODE: {
        node_t *node = vm_add_node(vm, def->node_ctor);
        stack_push(vm->value_stack, node);
        return;
    }
    }
}
