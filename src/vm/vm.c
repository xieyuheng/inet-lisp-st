#include "index.h"

vm_t *
vm_new(mod_t *mod) {
    vm_t *self = new(vm_t);
    self->mod = mod;
    self->activity_list = list_new_with((destroy_fn_t *) activity_destroy);
    self->matched_node_set = set_new();
    // TODO We should use value_destroy to create value_stack.
    self->value_stack = stack_new();
    self->return_stack = stack_new_with((destroy_fn_t *) frame_destroy);
    self->wire_set = set_new();
    self->node_set = set_new();
    self->node_id_count = 0;
    return self;
}

void
vm_destroy(vm_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        vm_t *self = *self_pointer;
        list_destroy(&self->activity_list);
        set_destroy(&self->matched_node_set);
        stack_destroy(&self->value_stack);
        stack_destroy(&self->return_stack);
        set_destroy(&self->wire_set);
        set_destroy(&self->node_set);
        free(self);
        *self_pointer = NULL;
    }
}

void
vm_print(const vm_t *self, file_t *file) {
    fprintf(file, "<vm>\n");

    size_t activity_list_length = list_length(self->activity_list);
    fprintf(file, "<active-wire-list length=\"%lu\">\n", activity_list_length);
    activity_t *activity = list_first(self->activity_list);
    while (activity) {
        activity_print(activity, file);
        activity = list_next(self->activity_list);
    }
    fprintf(file, "</active-wire-list>\n");

    vm_print_return_stack(self, file);
    vm_print_value_stack(self, file);

    fprintf(file, "</vm>\n");
}

void
vm_print_return_stack(const vm_t *self, file_t *file) {
    size_t return_stack_length = stack_length(self->return_stack);
    fprintf(file, "<return-stack length=\"%lu\">\n", return_stack_length);
    for (size_t i = 0; i < return_stack_length; i++) {
        frame_t *frame = stack_get(self->return_stack, i);
        frame_print(frame, file);
    }

    fprintf(file, "</return-stack>\n");
}

void
vm_print_value_stack(const vm_t *self, file_t *file) {
    size_t value_stack_length = stack_length(self->value_stack);
    fprintf(file, "<value-stack length=\"%lu\">\n", value_stack_length);
    for (size_t i = 0; i < value_stack_length; i++) {
        value_t value = stack_get(self->value_stack, i);
        value_print(value, file);
        fprintf(file, "\n");
    }

    fprintf(file, "</value-stack>\n");
}

node_t *
vm_add_node(vm_t* self, const node_ctor_t *ctor) {
    node_t *node = node_new(ctor, ++self->node_id_count);
    set_add(self->node_set, node);
    return node;
}

void
vm_delete_node(vm_t* self, node_t *node) {
    set_delete(self->node_set, node);
    set_delete(self->matched_node_set, node);
    node_destroy(&node);
}

wire_t *
vm_add_wire(vm_t* self) {
    wire_t *wire = wire_new();
    set_add(self->wire_set, wire);
    return wire;
}

void
vm_delete_wire(vm_t* self, wire_t *wire) {
    set_delete(self->wire_set, wire);
    wire_destroy(&wire);
}

wire_t *
vm_wire_connect(vm_t* self, wire_t *first_wire, wire_t *second_wire) {
    wire_t *first_opposite = first_wire->opposite;
    wire_t *second_opposite = second_wire->opposite;

    first_opposite->opposite = second_opposite;
    second_opposite->opposite = first_opposite;

    vm_delete_wire(self, first_wire);
    vm_delete_wire(self, second_wire);

    return first_opposite;
}

char *
vm_fresh_name(vm_t* self) {
    size_t max_string_length = 256;
    char *buffer = allocate(max_string_length);
    sprintf(buffer, "%lu", self->fresh_name_count++);
    char *string = string_copy(buffer);
    free(buffer);
    return string;
}
