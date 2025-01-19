#include "index.h"

void
execute(vm_t *vm, stmt_t *stmt) {
    switch (stmt->kind) {
    case STMT_DEFINE_FUNCTION: {
        // TODO
        return;
    }

    case STMT_DEFINE_NODE: {
        // stmt->define_node.name;
        // stmt->define_node.port_name_list;
        (void) vm;
        (void) stmt;
        return;
    }

    case STMT_DEFINE_RULE: {
        // TODO
        return;
    }
    }
}
