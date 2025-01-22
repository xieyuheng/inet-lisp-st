---
title: compiling lisp to stack machine
date: 2025-01-19
---

vm opcodes:

```scheme
(get def)
(apply arity)
(literal value)
(local-get index)
(local-set index)
```

compiling:

```scheme
(f (a) (b)) =>
a/0
b/0
f/2

(f (g (a)) (g (b))) =>
a/0
g/1
b/0
g/1
f/2

(f (a) (b)) (=> x y) =>
a/0
b/0
f/2
(local-set (index-of y))
(local-set (index-of x))
```

[2025-01-22] 想要这样编译的前提是，
application expression 中每个 sub expression 都返回一个 value。
但是后缀表达式的 `(=> x y)` 又要求 top-level expression 要可以返回多个 value。
