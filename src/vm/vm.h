#pragma once

// A vm is like a little forth inner interpreter.

struct vm_t {
    mod_t *mod;
    list_t *activity_list;
    set_t *matched_node_set;
    stack_t *value_stack;
    stack_t *return_stack;
    size_t node_id_count;
    size_t fresh_name_count;
    // wire and node should use managed memory,
    // because some nets have no root.
    // i simply record the pointers in vm for now.
    set_t *wire_set;
    set_t *node_set;
};

vm_t *vm_new(mod_t *mod);
void vm_destroy(vm_t **self_pointer);

void vm_print_return_stack(const vm_t *self, file_t *file);
void vm_print_value_stack(const vm_t *self, file_t *file);
void vm_print(const vm_t *self, file_t *file);

node_t *vm_add_node(vm_t* self, const node_ctor_t *ctor);
void vm_delete_node(vm_t* self, node_t *node);

wire_t *vm_add_wire(vm_t* self);
void vm_delete_wire(vm_t* self, wire_t *wire);

char *vm_fresh_name(vm_t* self);
