; TEST_RETURN_CODE=FAIL
; TEST_COMMENT=test final fail - la variable masquée

(define count ((lambda (total) (lambda (increment) (set! total (+ total increment)) total)) 0))
(count 3)
(count 5)
total

;;; Make sure you put a return at
;;; the end of the input file
