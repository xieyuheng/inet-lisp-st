#include "index.h"

void
xint_dup(vm_t *vm) {
    value_t target = stack_top(vm->value_stack);
    assert(is_xint(target));
    stack_push(vm->value_stack, target);
    stack_push(vm->value_stack, target);
}
