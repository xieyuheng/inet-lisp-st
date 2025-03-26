[core] `function_t` -- remove `op_list` and `ops` -- use `op_array` (auto grow)

# bug

[bug] `activate_matched_node` -- should has `rule_array` instead of `rule_list` which is not thread safe

[bug] fix the use of list in rule (nested)

[lang] fix `manager_no_more_task` -- `worker_ctx->atomic_is_processing` is not enough

- example should pass now:

  ```
  make -j && make self-test && ./bin/inet-lisp run examples/readme/nat.test.lisp
  ```

[lang] `manager_thread_fn` -- dispatch task -- be fair

# later

[worker] safe use of `task_queue` -- size is limited now

# parallelism

[thread] `lock_t` for `pthread_mutex_t`
[thread] `lock_acquire`
[thread] `lock_release`

[thread] test mutex

[thread] `thread_print`

# debug

[debug] 尝试使用真实的物理学来实现 force
[debug] `node_physics_simulate` -- move by `velocity` and clear `force` for every `node_model`
[debug] remove `node_physics_fake_simulate`
[debug] `draw_net` -- print non-wire value -- test by `list-map.play.lisp`

# arity checker

[lang] [maybe] write arity checker in inet-lisp itself!
[lang] write the arity checker like a type checker -- choose good names in the problem domain
[lang] check arity -- compute arity from exp
[lang] compute `arity` from each exp -- what should be the function names?
[lang] `compile_exp` -- `EXP_AP` -- should not get `arity` from `list_length(exp->ap.arg_list)`
[lang] `apply_function` -- supplement wire if arity is short

# error report

improve undefined-node.error.lisp

# testing

[testing] `(assert)` report position
