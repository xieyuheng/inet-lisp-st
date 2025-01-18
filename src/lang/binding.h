#pragma once

struct binding_t {
    list_t *name_list;
    list_t *body;
};

binding_t *binding_new(void);
void binding_destroy(binding_t **self_pointer);

list_t *binding_list_new(void);
