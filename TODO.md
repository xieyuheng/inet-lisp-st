# primitive

[vm] `activate_primitive_node`
`primitive-node.test.lisp` -- get the right result

# primitive test

[primitive] write `list-map` as example that uses function -- `function_t` as primitive value

# parallelism

[parallelism] learn linux thread
[parallelism] support shared memory parallel execution

# debug

[debug] 尝试使用真实的物理学来实现 force
[debug] `node_physics_simulate` -- move by `velocity` and clear `force` for every `node_model`
[debug] remove `node_physics_fake_simulate`

# arity checker

[lang] write the arity checker like a type checker -- choose good names in the problem domain
[lang] check arity -- compute arity from exp
[lang] compute `arity` from each exp -- what should be the function names?
[lang] `compile_exp` -- `EXP_AP` -- should not get `arity` from `list_length(exp->ap.arg_list)`
[lang] `apply_function` -- supplement wire if arity is short

# module system

[question] how to handle defining rule for import nodes

# error report

improve undefined-node.error.lisp

# testing

[testing] `(assert)` report position
