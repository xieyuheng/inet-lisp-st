(define (float-square x)
  (fmul (& x float-dup) x))

(assert (eq? (float-square 1.0) 1.0))
(assert (eq? (float-square 2.0) 4.0))
(assert (eq? (float-square 3.0) 9.0))

(define two 2.0)
(assert (eq? (float-square two) 4.0))
(assert (eq? (float-square (float-square two)) 16.0))
