rename let to assign

`frame_get_variable` -- be linear -- all variables should be linear
`frame_set_variable` -- be linear -- all variables should be linear

[int] int-dup -- fix square
[float] float-dup

# linear variable

[lang] fix the use of `value_print` in `frame_print`

- should we use linear variable or linear value?

# primitive

[net] fix the use of `ports` in `matcher_match_node` and `delete_match_nodes`
`primitive-node.test.lisp` -- get the right result

# primitive test

[primitive] write `list-map` as example that uses function

- the most important primitive value is `function_t`

[primitive] should not use `define_primitive_0_fn` to define `newline` -- the arity is wrong.

- [maybe] use `NULL` as `xvoid`

# testing

[testing] `(assert)` report position

# error report

improve undefined-node.error.lisp

# parallelism

learn linux thread
shared memory parallel execution of inet
projects/others/HigherOrderCO/HVM/paper/HVM2.pdf

# module system

[question] how to handle defining rule for import nodes

# arity checker

[lang] write the arity checker like a type checker

- choose good names in the problem domain

[value] `xvoid` -- so that every function can return one value

- maybe not, should use explicit output arity instead.

[lang] check arity -- compute arity from exp

[lang] compile_exp -- EXP_AP -- should not get `arity` from `list_length(exp->ap.arg_list)`

- should compute `arity` from each exp

  - `exp_arity` -- for arg output arity
  - `exp_target_arity` -- for target input arity
    - need to infer output arity of function

[lang] apply_function -- supplement wire if arity is short

- [stack] stack_pop_list
- [stack] stack_push_list

- use stack_pop_list and stack_push_list to save arguments by arity

# debug

[debug] 尝试使用真实的物理学来实现 force
[debug] `node_physics_simulate` -- move by `velocity` and clear `force` for every `node_model`
[debug] remove `node_physics_fake_simulate`
