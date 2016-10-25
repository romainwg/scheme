; TEST_RETURN_CODE=PASS
; TEST_COMMENT=Test 05 if

(if (< 3 4) "3 inférieur à 4")
(define x 4)
(if (> x 0) (- x (* 2 x)) x)
(if (> x 0) (- x) x)
(if (> x 4) x)
(if (> x 3) (+ x (- (/ 5 5) (* 3 2))) (- x (- (/ 5 5) (* 3 2))))


;;; Make sure you put a return at
;;; the end of the input file
