#pragma once

struct binding_t {
    list_t *name_list;
    exp_t *exp;
};

binding_t *binding_new(list_t *name_list, exp_t *exp);
void binding_destroy(binding_t **self_pointer);

list_t *binding_list_new(void);
