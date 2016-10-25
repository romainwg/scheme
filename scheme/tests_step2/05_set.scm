; TEST_RETURN_CODE=PASS
; TEST_COMMENT=Test 04 set!

(define bob 4)
bob
(set! bob "Je suis une chaine de caracteres")
bob
(set! bob (quote harry))
bob
(set! bob #t)
bob
(set! bob #\t)
bob
(set! bob (+ 3 4))
bob
(set! bob (< 4 3))
bob
(set! bob (+ 3 (- (/ 5 5) (* 3 2))))
bob

;;; Make sure you put a return at
;;; the end of the input file
