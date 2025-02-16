#include "index.h"

void
x_fn_dup(vm_t *vm) {
    value_t target = stack_top(vm->value_stack);
    assert(is_function(target));
    stack_push(vm->value_stack, target);
}
