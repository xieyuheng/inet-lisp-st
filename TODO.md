[core] `manager_start` -- take `init_task_queue`

[core] `manager_start` -- create worker threads

- [core] `manager_t` -- has `worker_thread_ids`

[core] `manager_thread_fn` -- thread loop

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
