(import diff diff-append "diff-list.lisp")
(import null cons "list.lisp")
(import sole "trivial.lisp")

(define (sole-diff-list)
  (let* ([front front-op (wire-pair)]
         [back value (diff front)])
    (cons (sole) (cons (sole) back) front-op)
    value))

(inspect-run
 (diff-append
  (sole-diff-list)
  (sole-diff-list)))
