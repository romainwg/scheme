; TEST_RETURN_CODE=PASS
; TEST_COMMENT=Test 08 or

(or)
(or #t)
(or #f)
(or #f #f)
(or #f #t)
(or #t #f)
(or #t #t)
(or #f #f #f #f #f)
(or #f #f #f #f #f #f #t)
(or #f #f #f #f #f #f #f)
(or (or #f #f) (or #t #t))
(define bob #t)
(or (if (< 3 4) #t #f) bob)

;;; Make sure you put a return at
;;; the end of the input file
