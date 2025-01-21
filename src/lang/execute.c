#include "index.h"

void
execute(vm_t *vm, stmt_t *stmt) {
    switch (stmt->kind) {
    case STMT_DEFINE_FUNCTION: {
        // TODO
        return;
    }

    case STMT_DEFINE_NODE: {
        define_node(
            vm->mod,
            stmt->define_node.name,
            stmt->define_node.port_name_list);
        return;
    }

    case STMT_DEFINE_RULE: {
        // TODO
        return;
    }

    case STMT_COMPUTE_EXP: {
        // TODO
        return;
    }
    }
}
