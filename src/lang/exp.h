#pragma once

typedef enum {
    EXP_VAR,
    EXP_AP,
    EXP_ASSIGN,
} exp_kind_t;

struct exp_t {
    exp_kind_t kind;
    union {
        struct { char *name; } var;
        struct { exp_t *target; list_t *arg_list; } ap;
        struct { list_t *name_list; } assign;
    };
};

exp_t *exp_var(char *name);
exp_t *exp_ap(exp_t *target, list_t *arg_list);
exp_t *exp_assign(list_t *name_list);

list_t *exp_list_new(void);

void exp_destroy(exp_t **self_pointer);

void exp_list_print(const list_t *exp_list, file_t *file);
void exp_print(const exp_t *self, file_t *file);
