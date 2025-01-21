#include "index.h"

void
define_node(mod_t *mod, const char *name, list_t *port_name_list) {
    size_t arity = list_length(port_name_list);
    node_def_t *node_def = node_def_new(name, arity);
    def_t *def = def_node(node_def);

    size_t index = 0;

    char *port_name = list_first(port_name_list);
    while (port_name) {
        def->node->port_defs[index] = port_def_from_name(port_name);
        port_name = list_next(port_name_list);
        index++;
    }

    mod_define(mod, def);
    return;
}
