; TEST_RETURN_CODE=PASS
; TEST_COMMENT=Test 1 quote : simple


(quote 3)
(quote "hi")
(quote a)
(quote (+ 3 4))
(quote (a b c))
(quote (define x 25))
(quote (lambda (x) (+ x 3)))


;;; Make sure you put a return at
;;; the end of the input file
