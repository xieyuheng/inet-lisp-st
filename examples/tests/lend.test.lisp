(define (main)
  (= x 1)
  (assert (eq? (& x int-dup) 1))
  (assert (eq? (lend x int-dup) 1))
  (assert (eq? x 1)))

(main)
