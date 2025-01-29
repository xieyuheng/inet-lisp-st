(define-node zero value!)
(define-node add1 prev value!)
(define-node add target! addend result)

(define-rule (add (zero) addend result)
  (connect addend result))

;; (define-rule (add (add1 prev) addend result)
;;   (add1 (add prev addend) result))

(define-rule* ((add target! addend result)
               (add1 prev target!))
  (add1 (add prev addend) result))

(define (two) (add1 (add1 (zero))))

;; (add (add1 (zero)) (zero))

;; (define (inspect-run wire)
;;   (wire-print-net (run (wire-print-net wire))))

(add (two) (two))
(wire-print-net)
(run)
(wire-print-net)
