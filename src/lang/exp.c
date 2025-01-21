#include "index.h"

exp_t *
exp_var(char *name) {
    exp_t *self = new(exp_t);
    self->kind = EXP_VAR;
    self->var.name = name;
    return self;
}

exp_t *
exp_ap(exp_t *target, list_t *arg_list) {
    exp_t *self = new(exp_t);
    self->kind = EXP_AP;
    self->ap.target = target;
    self->ap.arg_list = arg_list;
    return self;
}

exp_t *
exp_assign(list_t *name_list) {
    exp_t *self = new(exp_t);
    self->kind = EXP_ASSIGN;
    self->assign.name_list = name_list;
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
            list_destroy(&self->assign.name_list);
            break;
        }
        }

        free(self);
        *self_pointer = NULL;
        return;
    }
}

void
exp_list_print(const list_t *exp_list, file_t *file) {
    (void) exp_list;
    (void) file;
    return;
}

static void
name_list_print(const list_t *name_list, file_t *file) {
    char *name = list_first(name_list);
    if (name) {
        if (list_cursor_is_end(name_list))
            fprintf(file, "%s", name);
        else
            fprintf(file, "%s ", name);
        name = list_next(name_list);
    }
}

void
exp_print(const exp_t *self, file_t *file) {
    switch (self->kind) {
    case EXP_VAR: {
        fprintf(file, "%s", self->var.name);
        return;
    }

    case EXP_AP: {
        fprintf(file, "(");
        exp_print(self->ap.target, file);
        if (!list_is_empty(self->ap.arg_list)) {
            fprintf(file, " ");
            exp_list_print(self->ap.arg_list, file);
        }
        fprintf(file, ")");
        return;
    }

    case EXP_ASSIGN: {
        if (list_is_empty(self->assign.name_list)) {
            fprintf(file, "(=)");
            return;
        }

        fprintf(file, "(= ");
        name_list_print(self->assign.name_list, file);
        fprintf(file, ")");
        return;
    }
    }
}
