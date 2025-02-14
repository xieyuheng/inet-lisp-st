#include "index.h"

void
apply_primitive(vm_t *vm, primitive_t *primitive, size_t arity) {
    // TODO supplement wire if arity is short
    assert(primitive->input_arity == arity);

    switch (primitive->fn_kind) {
    case PRIMITIVE_VM_FN: {
        primitive->primitive_vm_fn(vm);
        return;
    }

    case PRIMITIVE_0_FN: {
        value_t result = primitive->primitive_0_fn();
        stack_push(vm->value_stack, result);
        return;
    }

    case PRIMITIVE_1_FN: {
        value_t x = stack_pop(vm->value_stack);
        value_t result = primitive->primitive_1_fn(x);
        stack_push(vm->value_stack, result);
        return;
    }

    case PRIMITIVE_2_FN: {
        value_t y = stack_pop(vm->value_stack);
        value_t x = stack_pop(vm->value_stack);
        value_t result = primitive->primitive_2_fn(x, y);
        stack_push(vm->value_stack, result);
        return;
    }

    case PRIMITIVE_3_FN: {
        value_t z = stack_pop(vm->value_stack);
        value_t y = stack_pop(vm->value_stack);
        value_t x = stack_pop(vm->value_stack);
        value_t result = primitive->primitive_3_fn(x, y, z);
        stack_push(vm->value_stack, result);
        return;
    }

    case PRIMITIVE_4_FN: {
        value_t w = stack_pop(vm->value_stack);
        value_t z = stack_pop(vm->value_stack);
        value_t y = stack_pop(vm->value_stack);
        value_t x = stack_pop(vm->value_stack);
        value_t result = primitive->primitive_4_fn(x, y, z, w);
        stack_push(vm->value_stack, result);
        return;
    }
    }
}
