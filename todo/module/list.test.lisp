(import null cons append "list.fth")
(import sole "trivial.fth")

(inspect-run
  (append
    (cons (sole) (cons (sole) (cons (sole) (null))))
    (cons (sole) (cons (sole) (cons (sole) (null))))))
