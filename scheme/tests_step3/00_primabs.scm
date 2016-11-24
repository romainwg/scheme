; TEST_RETURN_CODE=PASS
; TEST_COMMENT=Test 1 primabs


(abs 2)
(abs (abs 5))
(abs (+ 2 3))
(abs 3.14)
(abs (sin 2))

;;; Make sure you put a return at
;;; the end of the input file
