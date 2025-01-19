#include "index.h"

void
call(vm_t *vm, const def_t *def) {
    switch (def->kind) {
    case FUNCTION_DEF: {
        call_function(vm, def->as_function_def);
        return;
    }

    case NODE_DEF: {
        // TODO
        // call_node(vm, def->as_node_def);
        return;
    }
    }
}
