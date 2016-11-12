; TEST_RETURN_CODE=PASS
; TEST_COMMENT=Test 1 quote : simple


'(quote (a '(quote test)) test)
'""
'"test test test123"
'"test 'test test123"
'(quote (+ 'a b))

;;; Make sure you put a return at
;;; the end of the input file
