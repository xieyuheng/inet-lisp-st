---
title: compiling lisp to stack machine
date: 2025-01-19
---

vm:

```scheme
(call def arity)
(literal value)
(local-get index)
(local-set index)
```

compiling:

```scheme
(f (a) (b)) =>
(call a 0)
(call b 0)
(call f 2)

(f (g (a)) (g (b))) =>
(call a 0)
(call g 1)
(call b 0)
(call g 1)
(call f 2)

(= x y (f (a) (b))) =>
(call a 0)
(call b 0)
(call f 2)
(local-set (index-of y))
(local-set (index-of x))
```
