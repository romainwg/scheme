; TEST_RETURN_CODE=PASS
; TEST_COMMENT=Test final - page 28

(quote ((51 "Clyde") sym z (f #\e 42)))
(cons 3 ())
(cons "abc" (cons 2 ()))
(cons 1 (cons 2 (cons 3 ())))
(car (cons 1 (cons 2 (cons 3 ()))))
(cdr (cons 1 (cons 2 (cons 3 ()))))
(car (cons 1 2))
(cdr (cons 1 2))
(car (quote (1 2 3)))
(cdr '(1 2 3))
(define bob 2)
bob
(set! bob "abc")
bob
(define x -4)
(if (< x 0) (- x) x )
(begin 1 2 3)
(begin 3 (+ 4 5))
(define y 9)
(if (> y 5) (begin (set! y 5) (* y y)) (- y 5))
(lambda (x) (* x 2))
((lambda (x) (* x 2)) 4)
(define ma-procedure (lambda (x) (* x 2)))
ma-procedure
(ma-procedure 4)
(ma-procedure (ma-procedure 4))
(define (ma-procedure-2 z) (* z 2))
ma-procedure-2
(ma-procedure-2 4)
(ma-procedure-2 (ma-procedure-2 4))
(define (mul-by-2 u) (* 2 u))
(define (map proc items) (if (null? items) '() (cons (proc (car items)) (map proc (cdr items)))))
mul-by-2
(map mul-by-2 '(0 1 2 3))
(define count ((lambda (total) (lambda (increment) (set! total (+ total increment)) total)) 0))
(count 3)
(count 5)
(+ 5 -4)

;;; Make sure you put a return at
;;; the end of the input file
