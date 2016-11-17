; TEST_RETURN_CODE=PASS
; TEST_COMMENT=Test 1 primplus


(modulo 1 2)
(modulo 2 3 5)
(modulo (modulo 2 3) 5)
(modulo (modulo 2 3) (modulo 2 3))
(modulo (modulo 2 3) (modulo 2 3) 5 6 7 8)
(modulo 11 4 1)

;;; Make sure you put a return at
;;; the end of the input file
