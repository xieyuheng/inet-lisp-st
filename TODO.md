[sexp] sexp_starts_with

[lang] parse_stmt -- take sexp as input

[lang] parse_define_node
[lang] parse_define_function

[lang] execute -- take stmt
[lang] execute -- test define-node

[lang] parse_define_rule

[lang] pattern_t
[lang] stmt_define_rule -- need pattern

[vm] op_call -- has artiy

# later

[example] `examples/cellular-automata.lisp` -- 1997-interaction-combinators.pdf
[example] `examples/lambda.lisp` -- use interaction combinators to implement lambda
[example] `examples/turing.lisp` -- coding turing machine -- 2008-the-annotated-turing.djvu

# primitive value

[design] node ports can store any value -- not only wire, but also primitive values
[design] the most important primitive value is function (closure)
[design] write `list-map` as example that uses function
[design] use explicit `copy` -- keep linear variable like simple

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
