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
    self->ap.arg_list = list_new(); // TODO exp_list_new()
    return self;
}

exp_t *
exp_let(void) {
    exp_t *self = new(exp_t);
    self->kind = EXP_LET;
    self->let.binding_list = binding_list_new();
    self->let.body = list_new(); // TODO exp_list_new()
    return self;
}
