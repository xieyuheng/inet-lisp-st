#include "index.h"

rule_t *
rule_new(size_t starting_index, net_pattern_t *net_pattern, function_t *function) {
    rule_t *self = new(rule_t);
    self->starting_index = starting_index;
    self->net_pattern = net_pattern;
    self->function = function;
    return self;
}

void
rule_destroy(rule_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        rule_t *self = *self_pointer;
        net_pattern_destroy(&self->net_pattern);
        function_destroy(&self->function);
        free(self);
        *self_pointer = NULL;
    }
}
