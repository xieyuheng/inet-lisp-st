(define (square x) (imul x x))

(assert (eq? (square 1) 1))
(assert (eq? (square 2) 4))
(assert (eq? (square 3) 9))

(define two 2)
(assert (eq? (square two) 4))
(assert (eq? (square (square two)) 16))
