#include "index.h"

object_spec_t wire_object_spec = {
    .name = "wire",
    .print_fn = (print_fn_t *) wire_print,
};

wire_t *
wire_new(void) {
    wire_t *self = new(wire_t);
    self->spec = &wire_object_spec;
    self->node = NULL;
    self->opposite = NULL;
    return self;
}

void
wire_destroy(wire_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        wire_t *self = *self_pointer;
        free(self);
        // Does NOT own `node` and `opposite`.
        *self_pointer = NULL;
    }
}

bool
is_wire(value_t value) {
    if (!is_xobject(value)) return false;
    return as_object(value)->spec == &wire_object_spec;
}

wire_t *
as_wire(value_t value) {
    assert(is_wire(value));
    return (wire_t *) value;
}

const char *
wire_name(const wire_t *self) {
    assert(self->node);
    port_info_t *port_info = self->node->ctor->port_infos[self->index];
    assert(port_info);
    return port_info->name;
}

const char *
wire_node_name(const wire_t *self) {
    assert(self->node);
    return self->node->ctor->name;
}

void
wire_free_from_node(wire_t *self) {
    self->node = NULL;
}

bool
wire_is_free(const wire_t *self) {
    if (self->node) return false;

    return true;
}

bool
wire_is_principal(const wire_t *self) {
    if (!self->node) return false;

    port_info_t *port_info = self->node->ctor->port_infos[self->index];
    return port_info->is_principal;
}

wire_t *
wire_connect_wire(vm_t* vm, wire_t *first_wire, wire_t *second_wire) {
    value_t first_opposite = first_wire->opposite;
    value_t second_opposite = second_wire->opposite;

    if (is_wire(first_opposite) && is_wire(second_opposite)) {
        wire_t *first_opposite_wire = as_wire(first_opposite);
        wire_t *second_opposite_wire = as_wire(second_opposite);

        first_opposite_wire->opposite = second_opposite_wire;
        second_opposite_wire->opposite = first_opposite_wire;

        vm_delete_wire(vm, first_wire);
        vm_delete_wire(vm, second_wire);

        if (first_opposite_wire->node)
            schedule_task_by(vm, first_opposite_wire->node);
        if (second_opposite_wire->node)
            schedule_task_by(vm, second_opposite_wire->node);

        return first_opposite_wire;
    } else if (is_wire(first_opposite)) {
        wire_t *first_opposite_wire = as_wire(first_opposite);
        first_opposite_wire->opposite = second_opposite;

        vm_delete_wire(vm, first_wire);
        vm_delete_wire(vm, second_wire);

        if (first_opposite_wire->node)
            schedule_task_by(vm, first_opposite_wire->node);

        return first_opposite_wire;
    } else if (is_wire(second_opposite)) {
        wire_t *second_opposite_wire = as_wire(second_opposite);
        second_opposite_wire->opposite = first_opposite;

        vm_delete_wire(vm, first_wire);
        vm_delete_wire(vm, second_wire);

        if (second_opposite_wire->node)
            schedule_task_by(vm, second_opposite_wire->node);

        return second_opposite_wire;
    } else {
        fprintf(stderr, "[wire_connect_wire] can not connect wires with non-wire opposite\n");
        fprintf(stderr, "[wire_connect_wire] first_opposite: ");
        value_print(first_opposite, stderr);
        fprintf(stderr, "\n");
        fprintf(stderr, "[wire_connect_wire] second_opposite: ");
        value_print(second_opposite, stderr);
        fprintf(stderr, "\n");
        exit(1);
    }
}

wire_t *
wire_connect_value(vm_t* vm, wire_t *wire, value_t value) {
    if (is_wire(value)) {
        return wire_connect_wire(vm, wire, value);
    }

     value_t opposite = wire->opposite;
     if (is_wire(opposite)) {
         wire_t *opposite_wire = as_wire(wire->opposite);
         opposite_wire->opposite = value;

         vm_delete_wire(vm, wire);

         if (opposite_wire->node)
             schedule_task_by(vm, opposite_wire->node);

         return opposite_wire;
     } else {
        fprintf(stderr, "[wire_connect_value] can not connect wire with non-wire opposite to value\n");
        fprintf(stderr, "[wire_connect_value] opposite: ");
        value_print(opposite, stderr);
        fprintf(stderr, "\n");
        exit(1);
    }
}

static void
wire_print_half_at_left(const wire_t *self, file_t *file) {
    if (!self->node) {
        fprintf(file, "-<");
        return;
    }

    node_print(self->node, file);

    if (wire_is_principal(self)) {
        fprintf(file, "-%s!-<", wire_name(self));
    } else {
        fprintf(file, "-%s-<", wire_name(self));
    }
}

static void
wire_print_half_at_right(const wire_t *self, file_t *file) {
    if (!self->node) {
        fprintf(file, ">-");
        return;
    }

    if (wire_is_principal(self)) {
        fprintf(file, ">-!%s-", wire_name(self));
    } else {
        fprintf(file, ">-%s-", wire_name(self));
    }

    node_print(self->node, file);
}

void
wire_print(const wire_t *self, file_t *file) {
    wire_print_half_at_left(self, file);

    if (self->opposite) {
        if (is_wire(self->opposite)) {
            wire_print_half_at_right(self->opposite, file);
        } else {
            fprintf(file, "[");
            value_print(self->opposite, file);
            fprintf(file, "]");
        }
    }
}

static void
wire_print_within_node(const wire_t *self, file_t *file) {
    fprintf(file, "-<");

    if (self->opposite) {
        if (is_wire(self->opposite)) {
            wire_print_half_at_right(self->opposite, file);
        } else {
            fprintf(file, "[");
            value_print(self->opposite, file);
            fprintf(file, "]");
        }
    }
}

void
wire_print_net(wire_t *self, file_t *file) {
    fprintf(file, "<net>\n");

    fprintf(file, ":root ");
    value_print(self, file);
    fprintf(file, "\n");

    node_t *root_node = self->node;
    if (!root_node) {
        if (is_wire(self->opposite)) {
            root_node = as_wire(self->opposite)->node;
        }
    }

    if (root_node) {
        node_iter_t *iter = node_iter_new(root_node);
        node_t *node = node_iter_first(iter);
        while (node) {
            fprintf(file, "(");
            node_print_name(node, file);
            fprintf(file, "\n");
            for (size_t i = 0; i < node->ctor->arity; i++) {
                port_info_t *port_info = node->ctor->port_infos[i];
                if (port_info->is_principal)
                    fprintf(file, " :%s! ", port_info->name);
                else
                    fprintf(file, " :%s ", port_info->name);

                value_t value = node->ports[i];
                if (value) {
                    if (is_wire(value)) {
                        wire_print_within_node(as_wire(value), file);
                    } else {
                        value_print(value, file);
                    }
                }

                if (i < node->ctor->arity - 1)
                    fprintf(file, "\n");
            }
            fprintf(file, ")");
            fprintf(file, "\n");
            node = node_iter_next(iter);
        }

        node_iter_destroy(&iter);
    }

    fprintf(file, "</net>\n");
}
