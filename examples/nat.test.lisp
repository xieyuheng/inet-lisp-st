(import zero add1 add "nat.lisp")

(define (two) (add1 (add1 (zero))))

(inspect-run
 (add (two) (two)))
