(define (int-square x)
  (imul (& x int-dup) x))

(assert (eq? (int-square 1) 1))
(assert (eq? (int-square 2) 4))
(assert (eq? (int-square 3) 9))

(define two 2)
(assert (eq? (int-square two) 4))
(assert (eq? (int-square (int-square two)) 16))
