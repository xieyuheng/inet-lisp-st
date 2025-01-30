(define-node sole value!)

(define (main)
  (= first second (wire-pair))
  (connect first (sole))
  (print second)
  (newline))

(main)
