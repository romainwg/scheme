; TEST_RETURN_CODE=PASS
; TEST_COMMENT=Test 1 quote

(quote (quote 3))
(quote (quote "hi"))
(quote (quote a))
(quote (quote (+ 3 4)))
(quote (quote (a b c)))
(quote (quote (define x 25)))
(quote (quote (lambda (x) (+ x 3))))
''3
''"hi"
''a
''(+ 3 4)
''(a b c)
''(define x 25)
''(lambda (x) (+ x 3))

;;; Make sure you put a return at
;;; the end of the input file
