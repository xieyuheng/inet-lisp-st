---
title: compiling lisp to stack machine
date: 2025-01-19
---

vm opcodes:

```scheme
(call-node node arity) ;; node/arity
(call-function name)   ;; name
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
