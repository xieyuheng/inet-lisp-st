#include "index.h"

exp_t *
exp_var(char *name) {
    exp_t *self = new(exp_t);
    self->kind = EXP_VAR;
    self->var.name = name;
    return self;
}

exp_t *
exp_ap(exp_t *target) {
    exp_t *self = new(exp_t);
    self->kind = EXP_AP;
    self->ap.target = target;
    self->ap.arg_list = exp_list_new();
    return self;
}

exp_t *
exp_assign(void) {
    exp_t *self = new(exp_t);
    self->kind = EXP_ASSIGN;
    self->assign.binding_list = binding_list_new();
    self->assign.exp_list = exp_list_new();
    return self;
}

list_t *
exp_list_new(void) {
    return list_new_with((destroy_fn_t *) exp_destroy);
}

void
exp_destroy(exp_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        exp_t *self = *self_pointer;
        switch (self->kind) {
        case EXP_VAR: {
            string_destroy(&self->var.name);
            break;
        }

        case EXP_AP: {
            exp_destroy(&self->ap.target);
            list_destroy(&self->ap.arg_list);
            break;
        }

        case EXP_ASSIGN: {
            list_destroy(&self->assign.binding_list);
            list_destroy(&self->assign.exp_list);
            break;
        }
        }

        free(self);
        *self_pointer = NULL;
        return;
    }
}
