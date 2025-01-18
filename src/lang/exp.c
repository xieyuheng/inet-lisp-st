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
    self->ap.arg_list = list_new();
    return self;
}
