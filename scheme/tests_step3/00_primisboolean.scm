; TEST_RETURN_CODE=PASS
; TEST_COMMENT=Test 1 primisboolean


(boolean? #t)
(boolean? (number? "abc"))

;;; Make sure you put a return at
;;; the end of the input file
