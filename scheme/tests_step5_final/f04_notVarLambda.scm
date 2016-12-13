; TEST_RETURN_CODE=FAIL
; TEST_COMMENT=test final fail - lambda

(lambda (x) (* x 2))
((lambda (x) (* x 2)) 4)
lambda

;;; Make sure you put a return at
;;; the end of the input file
