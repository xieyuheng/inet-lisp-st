(import sole "trivial.lisp")
(import diff diff-append "diff-list.lisp")
(import cons "list.lisp")

(define (sole-diff-list)
  (let front front-op (link))
  (let back value (diff front))
  (cons (sole) (cons (sole) back) front-op)
  value)

(inspect-run
 (diff-append
  (sole-diff-list)
  (sole-diff-list)))
