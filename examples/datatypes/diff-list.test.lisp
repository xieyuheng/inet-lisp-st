(define-node diff front back value!)
(define-node diff-append target! rest result)
(define-node diff-open new-back target! old-back)

;; plug the front of the `target` to the back of `rest`.

(define-rule (diff-append (diff front back) rest result)
  (diff front) (=> new-back value)
  (connect value result)
  (diff-open new-back rest back))

;; with keyword argument:
;; (define-rule (diff-append (diff front back) rest result)
;;   (diff-open (diff front :value result) rest back))

(define-rule (diff-open new-back (diff front back) old-back)
  (connect back new-back)
  (connect front old-back))

;; import null cons append "list.fth"

(define-node null value!)
(define-node cons head tail value!)
(define-node append target! rest result)

(define-rule (append (null) rest result)
  (connect rest result))

(define-rule (append (cons head tail) rest result)
  (cons head (append tail rest) result))

;; test

(define-node sole value!)

(define (sole-diff-list)
  (wire-pair) (=> front front-op)
  (diff front) (=> back value)
  (cons (sole) (cons (sole) back) front-op)
  value)

(inspect-run
 (diff-append
  (sole-diff-list)
  (sole-diff-list)))
