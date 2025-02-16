(import null cons "list.lisp")

(define-node list-map target! fn result)

(define-rule (list-map (null) fn result)
  (null result))

(define-rule (list-map (cons head tail) fn result)
  (= fn1 fn2 (fn-dup fn))
  (cons (fn1 head) (list-map tail fn2) result))
