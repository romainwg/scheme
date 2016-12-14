; TEST_RETURN_CODE=PASS
; TEST_COMMENT=Test final

(+ 1 2 3 4)
(define a 10)
a
(* a 9)
(* a (+ 4 5))
(quote something)
'something
(quote (* a (+ 4 5)))

5
#\a
"chaine de car"
#t

(cons 1 2)
(list 1 2 3)

(car (list 1 2 3))
(cdr (list 1 2 3))

(and (= 4 3) (< 4 9))

(define maVar 3)

(if (= maVar 3) (quote "equals") (quote "not equal"))

(define power2 (lambda (x) (* x x)))

(define factorial (lambda (n) (if (= n 0) 1 (* n (factorial (- n 1))))))

(factorial 4)

(map (lambda (x) (+ x 1)) (list 2 3 4))

;;; Make sure you put a return at
;;; the end of the input file