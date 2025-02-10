# module system

[lang] `stmt_print` -- handle `STMT_IMPORT`
[lang] `parse_stmt` -- `parse_import`
[mv] `mod_t` -- has `path`
[vm] need `rule_copy_shallow`
[lang] `execute` -- handle `STMT_IMPORT`

# primitive value

[design] node ports can store any value -- not only wire, but also primitive values
[design] the most important primitive value is function (closure)
[design] write `list-map` as example that uses function
[design] use explicit `copy` -- keep linear variable like simple

# parallelism

learn linux thread
shared memory parallel execution of inet
projects/others/HigherOrderCO/HVM/paper/HVM2.pdf

# output

[vm] `vm_print` -- should call `activity_print`

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
