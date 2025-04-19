#pragma once

// A worker is like a little forth inner interpreter.

struct worker_t {
    mod_t *mod;
    list_t *task_list;
    stack_t *value_stack;
    stack_t *return_stack;
    size_t node_id_count;
    size_t fresh_name_count;
    // only used when core_player_flag is enabled
    set_t *player_node_set;
};

worker_t *worker_new(mod_t *mod);
void worker_destroy(worker_t **self_pointer);

void worker_print_return_stack(const worker_t *self, file_t *file);
void worker_print_value_stack(const worker_t *self, file_t *file);
void worker_print(const worker_t *self, file_t *file);

node_t *worker_add_node(worker_t* self, const node_ctor_t *ctor);
void worker_delete_node(worker_t* self, node_t *node);

wire_t *worker_add_wire(worker_t* self);
void worker_delete_wire(worker_t* self, wire_t *wire);

char *worker_fresh_name(worker_t* self);

void worker_return_task(worker_t* self, task_t *task);
