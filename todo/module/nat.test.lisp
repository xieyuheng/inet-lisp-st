(import zero add1 add "nat.lisp")

(define (one) (add1 (zero)))
(define (two) (add1 (one)))
(define (three) (add1 (two)))
(define (four) (add1 (three)))

(inspect-run
 (add (add (two) (two))
      (add (two) (two))))
