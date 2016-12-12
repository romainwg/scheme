; TEST_RETURN_CODE=PASS
; TEST_COMMENT=Test lambda

(lambda (x) (+ x))
(lambda (x) (+ x 1))
((lambda (x) (+ x 1)) 1)
((lambda (x y) (* x y)) 2 4)
((lambda (x y) (* x y)) 2 ((lambda (x y) (* x y)) 2 4))

;;; Make sure you put a return at
;;; the end of the input file
