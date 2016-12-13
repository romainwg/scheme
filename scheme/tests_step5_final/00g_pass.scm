; TEST_RETURN_CODE=PASS
; TEST_COMMENT=Test final - page 28

1
'100
(quote abc)
" \"test\" \\test"
#\&
(  quote (    if    (   >   a    5)       (+    9    8)  ) )
(> 3 2)
(define a 9)
(set! a 8)
a
(cons 1 2)
(cons 1 (cons () (cons 3 4)))
(cons 1 (cons () (cons 3 (cons 4 () ))))
(lambda (x) (+ x x))
((lambda (x) (+ x x)) 2)
(define power2 (lambda (x) (* x x)))
power2
(power2 2)


;;; Make sure you put a return at
;;; the end of the input file
