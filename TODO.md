[lang] `parse_define_value` -- handle `(define <name> <exp>)` -- fix square.lisp test
[tests] undefined-node.error.lisp

# primitive

[primitive] `node_t` -- ports can store any value -- not only wire, but also primitive values

[net] `node_ctor_t` -- has optional `primitive` --

[primitive] `apply` -- create node when args has wire

- `primitive_t` need a flag to denote generic on wires

  - after `define_primitive`,
    use something like `declare_primitive_node`,
    to specify a `node_ctor_t`.

[primitive] write `list-map` as example that uses function

- the most important primitive value is `function_t`

# testing

[testing] `(assert)` report position

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
