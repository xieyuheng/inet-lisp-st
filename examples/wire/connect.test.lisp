(define-node sole value!)

(define (main)
  (wire-pair) (=> first second)
  (connect first (sole))
  (print second)
  (newline))

(main)
