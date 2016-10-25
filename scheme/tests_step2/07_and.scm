; TEST_RETURN_CODE=PASS
; TEST_COMMENT=Test 07 and

(and)
(and #t)
(and #f)
(and #f #f)
(and #f #t)
(and #t #f)
(and #t #t)
(and #f #f #f #f #f)
(and #t #t #t #t #t #t #f)
(and #t #t #t #t #t #t #t)
(and (and #f #f) (and #t #t))
(define bob #t)
(and (if (< 3 4) #t #f) bob)

;;; Make sure you put a return at
;;; the end of the input file
