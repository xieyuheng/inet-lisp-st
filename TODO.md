inet -- 打造一个可以在 GPU 上运行的实用并行语言。

- inet-lisp -- 用 lisp 语法，实现更一般的 graph rewrite。
  多 principle ports 依然可以保证 inet 作为 rewrite system 的良好属性

- 为这个项目服务，还是需要一个带有 GC 的 x-lisp。
  为了处理 lisp 语法，需要在 c 里以深嵌入的方式，
  写一个 sexp 的 pattern matching library。

# later

[example] cellular automata -- 1997-interaction-combinators.pdf
[example] `examples/lambda.fth` -- use interaction combinators to implement lambda
[example] `examples/turing.fth` -- coding turing machine -- 2008-the-annotated-turing.djvu

# primitive value

[design] node ports can store any value -- not only wire, but also primitive values
[design] the most important primitive value is function
[design] write `list-map` as example
- use explicit `copy` -- keep linear variable like simple
- use `{ ... }` for un-named program -- just program, no closure over linear variables
[question] is it possible to have a generic `copy` that can copy any net with a root wire?

# debug

[debug] 尝试使用真实的物理学来实现 force
[debug] `node_physics_simulate` -- move by `velocity` and clear `force` for every `node_model`
[debug] remove `node_physics_fake_simulate`

# vm

[vm] mod -- change rule_list to rule_hash -- what should be the key?

# module system

支持简单的 import name，同时支持修改 name 以避免冲突

# parallelism

learn linux thread
shared memory parallel execution of inet
projects/others/HigherOrderCO/HVM/paper/HVM2.pdf
