#include "index.h"

void
call(vm_t *vm, const def_t *def) {
    switch (def->kind) {
    case DEF_FUNCTION: {
        call_function(vm, def->function);
        return;
    }

    case DEF_NODE: {
        // TODO
        // call_node(vm, def->node);
        return;
    }
    }
}
