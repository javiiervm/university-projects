#lang racket
(require "lpp.rkt")
(require rackunit)
(require 2htdp/image)

; EJERCICIO 1

(define (concat-iter lista result)
  (if (null? lista)
      result
      (concat-iter (rest lista) (string-append result (first lista)))))

(define (concat lista)
  (concat-iter lista ""))

(define (min-max-iter lista result)
  (cond
    ((null? (rest lista)) result)
    ((> (first lista) (cdr result)) (min-max-iter (rest lista) (cons (car result) (first lista))))
    ((< (first lista) (car result)) (min-max-iter (rest lista)(cons (first lista) (cdr result))))
    (else (min-max-iter (rest lista) result))))

(define (min-max lista)
  (min-max-iter lista (cons 0 0)))

; PRUEBAS UNITARIAS

(check-equal? (concat  '("hola" "y" "adiós")) "holayadiós")
(check-equal? (concat-iter  '("hola" "y" "adiós") "") "holayadiós")

(check-equal? (min-max '(2 5 9 12 5 0 4)) '(0 . 12))
(check-equal? (min-max '(3 2 -8 4 10 0)) '(-8 . 10))
(check-equal? (min-max-iter '(5 9 12 -2 5 0 4) (cons 2 2)) '(-2 . 12))

; EJERCICIO 2

(define (expande-pareja-iter pareja result)
  (if (= (cdr pareja) 1)
      (cons (car pareja) result)
      (cons (car pareja) (expande-pareja-iter (cons (car pareja) (- (cdr pareja) 1)) result))))

(define (expande-pareja pareja)
  (expande-pareja-iter pareja '()))

(define (expande-parejas . args)
  (foldr (lambda (x result) (append (expande-pareja x) result)) '() args))

(define (rotar k lista)
  (if (= k 0)
      lista
      (rotar (- k 1) (append (rest lista) (list (first lista))))))

; PRUEBAS UNITARIAS

(check-equal? (expande-pareja (cons 'a 4)) '(a a a a))
(check-equal? (expande-parejas '(#t . 3) '("LPP" . 2) '(b . 4)) '(#t #t #t "LPP" "LPP" b b b b))

(check-equal? (rotar 4 '(a b c d e f g)) '(e f g a b c d))

; EJERCICIO 3

(define (mi-foldl-iter pred result list)
  (if (null? list)
      result
      (mi-foldl-iter pred (pred (first list) result) (rest list))))

(define (mi-foldl pred base list)
  (mi-foldl-iter pred base list))

(define (binario-a-decimal-iter list result)
  (if (null? list)
      result
      (binario-a-decimal-iter (rest list) (+ (* 2 result) (first list)))))

(define (binario-a-decimal list)
  (binario-a-decimal-iter list 0))

; PRUEBAS UNITARIAS

(check-equal? (mi-foldl string-append "****" '("hola" "que" "tal")) "talquehola****")
(check-equal? (mi-foldl cons '() '(1 2 3 4)) '(4 3 2 1))

(check-equal? (binario-a-decimal '(1 1 1 1)) 15)
(check-equal? (binario-a-decimal '(1 1 0)) 6)
(check-equal? (binario-a-decimal '(1 0)) 2)

; EJERCICIO 4

(define (pascal-memo fila columna diccionario)
  (cond
    ((or (= columna 0) (= columna fila)) 1)
    ((key-exists? (cons fila columna) diccionario) (get (cons fila columna) diccionario))
    (else
     (let ((resultado (+ (pascal-memo (- fila 1) (- columna 1) diccionario)
                         (pascal-memo (- fila 1) columna diccionario))))
       (put (cons fila columna) resultado diccionario)
       resultado))))    

; PRUEBAS UNITARIAS

(define diccionario (make-dic))
(check-equal? (pascal-memo 8 4 diccionario) 70)
(check-equal? (pascal-memo 40 20 diccionario) 137846528820)

; EJERCICIO 5

(define (koch nivel trazo)
  (if (= nivel 0)
      (line trazo nivel "black")
      (beside/align "bottom"
                   (koch (- nivel 1) (/ trazo 3))
                   (rotate 60 (koch (- nivel 1) (/ trazo 3)))
                   (rotate -60 (koch (- nivel 1) (/ trazo 3)))
                   (koch (- nivel 1) (/ trazo 3)))))

(define (copo-nieve nivel trazo)
  (above/align "right"
                (beside/align "top"
                             (rotate 60 (koch nivel trazo))
                             (rotate -60 (koch nivel trazo)))
                (rotate 180 (koch nivel trazo))))

; PRUEBAS UNITARIAS

;(koch 5 200)
;(copo-nieve 5 200)

; EJERCICIO 6

(define (alfombra-sierpinski tam)
  (if (< tam 20)
      (circle tam "outline" "blue")
      (above/align "center"
       (beside
                     (alfombra-sierpinski (/ tam 3))
                     (alfombra-sierpinski (/ tam 3))
                     (alfombra-sierpinski (/ tam 3)))
       (beside
                     (alfombra-sierpinski (/ tam 3))
                     (circle (/ tam 3) "solid" "blue")
                     (alfombra-sierpinski (/ tam 3)))
       (beside
                     (alfombra-sierpinski (/ tam 3))
                     (alfombra-sierpinski (/ tam 3))
                     (alfombra-sierpinski (/ tam 3))))))

; PRUEBAS UNITARIAS

(alfombra-sierpinski 100)
















