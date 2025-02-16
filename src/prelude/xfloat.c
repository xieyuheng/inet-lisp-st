#include "index.h"

void
xfloat_dup(vm_t *vm) {
    value_t target = stack_top(vm->value_stack);
    assert(is_xfloat(target));
    stack_push(vm->value_stack, target);
}
