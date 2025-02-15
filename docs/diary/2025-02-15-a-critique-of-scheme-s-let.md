---
title: a critique of scheme's let
date: 2025-02-15
---

```scheme
(define (main)
  (g a)
  (let x (f b))
  (j x)
  (let y (h x))
  (k y))
```

```scheme
(define (main)
  (g a)
  (let ((x (f b)))
    (j x)
    (let ((y (h x)))
      (k y))))
```
