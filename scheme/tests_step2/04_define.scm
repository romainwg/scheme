; TEST_RETURN_CODE=PASS
; TEST_COMMENT=Test 03 Define

(define bob 4)
bob
(define oscar "Je suis une chaine de caracteres")
oscar
(define citation (quote harry))
citation
(define exp1 #t)
exp1
(define exp2 #\t)
exp2
(define exp3 (+ 3 4))
exp3
(define exp4 (< 4 3))
exp4
(define exp5 (+ 3 (- (/ 5 5) (* 3 2))))
exp5

;;; Make sure you put a return at
;;; the end of the input file
