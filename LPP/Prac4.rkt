#lang racket
(require "Prac2.rkt")
(require "lpp.rkt")
(require rackunit)

; EJERCICIO 1

(define (es-prefijo? pal1 pal2)
  (cond
    ((null? pal1) #t)
    ((and (null? pal2) (not (null? pal1))) #f)
    (else (string=? pal1 (substring pal2 0 (string-length pal1))))))

(define (contiene-prefijo prefijo lista-pal)
  (cond
    ((null? lista-pal) '())
    (else (cons (es-prefijo? prefijo (first lista-pal)) (contiene-prefijo prefijo (rest lista-pal))))))

(define (cadenas-mayores-prac4 lista1 lista2)
  (cond
    ((and (null? lista1) (null? lista2)) '())
    ((null? lista1) lista2)
    ((null? lista2) lista1)
    (else (cons (eleccion-palabra (first lista1) (first lista2)) (cadenas-mayores-prac4 (rest lista1) (rest lista2))))))

; PRUEBAS UNITARIAS

(check-equal? (es-prefijo? "ante" "anterior") #t)
(check-equal? (es-prefijo? "anta" "anterior") #f)

(check-equal? (contiene-prefijo "ante" '("anterior" "antígona" "antena" "anatema")) '(#t #f #t #f))

(check-equal? (cadenas-mayores-prac4 '("hola" "que" "tal") '("adios")) '("adios" "que" "tal"))
(check-equal? (cadenas-mayores-prac4 '("hola" "que" "tal") '("meme" "y" "adios")) '("hola" "que" "adios"))
(check-equal? (cadenas-mayores-prac4'("la" "primera" "práctica" "de" "recursión") '("confiar" "en" "la" "recursión" "facilita" "su" "resolución"))
              '("confiar" "primera" "práctica" "recursión" "recursión" "su" "resolución"))

; EJERCICIO 2

(define (inserta-pos dato pos lista)
  (cond
    ((= pos 0) (cons dato lista))
    (else (cons (first lista) (inserta-pos dato (- pos 1) (rest lista))))))

(define (inserta-ordenada n lista-ordenada)
  (cond
    ((null? lista-ordenada) (list n))
    ((> (first lista-ordenada) n) (cons n lista-ordenada))
    (else (cons (first lista-ordenada) (inserta-ordenada n (rest lista-ordenada))))))

(define (ordena lista)
  (cond
    ((null? lista) '())
    (else (inserta-ordenada (first lista) (ordena (rest lista))))))

; PRUEBAS UNITARIAS

(check-equal? (inserta-pos 'b 2 '(a a a a)) '(a a b a a))
(check-equal? (inserta-pos 'b 0 '(a a a a)) '(b a a a a))

(check-equal? (inserta-ordenada 10 '(-8 2 3 11 20)) '(-8 2 3 10 11 20))

(check-equal? (ordena '(2 -1 100 4 -6)) '(-6 -1 2 4 100))

; EJERCICIO 3

(define (mueve-al-principio lista dato)
  (cond
    ((equal? (first lista) dato) 
     (cons dato (rest lista)))
    (else 
     (intercambiar-1-2 (cons (first lista) (mueve-al-principio (rest lista) dato))))))

(define (intercambiar-1-2 lista)
  (cons (second lista) (cons (first lista) (rest (rest lista)))))

(define (comprueba-simbolos lista-simbolos lista-num)
  (cond
    ((and (null? lista-simbolos) (null? lista-num)) '())
    ((= (string-length (symbol->string (first lista-simbolos))) (first lista-num))
     (cons (cons (first lista-simbolos) (first lista-num))
           (comprueba-simbolos (rest lista-simbolos) (rest lista-num))))
    (else (comprueba-simbolos (rest lista-simbolos) (rest lista-num)))))

; PRUEBAS UNITARIAS

(check-equal? (mueve-al-principio '(a b e c d e f) 'e) '(e a b c d e f))
(check-equal? (mueve-al-principio '(a b c d e f g) 'a) '(a b c d e f g))

(check-equal? (intercambiar-1-2 '(a b c d)) '(b a c d))
(check-equal? (intercambiar-1-2 '(1 2 3 4)) '(2 1 3 4))

(check-equal? (comprueba-simbolos '(este es un ejercicio de examen) '(2 1 2 9 1 6)) '((un . 2) (ejercicio . 9) (examen . 6)))

; EJERCICIO 4

(define (expande-pareja pareja)
  (if (= (cdr pareja) 0)
      '()
      (cons (car pareja) (expande-pareja (cons (car pareja) (- (cdr pareja) 1))))))

(define (expande-lista lista-parejas)
  (if (null? lista-parejas)
      '()
      (append (expande-pareja (car lista-parejas)) (expande-lista (cdr lista-parejas)))))

(define (expande-parejas-1 . args)
  (expande-lista args))

(define (expande-parejas-2 . args)
  (if (null? args)
      '()
      (append (expande-pareja (car args)) (apply expande-parejas-2 (cdr args)))))

(define (expande lista)
  (cond
    ((null? lista) '())
    ((number? (first lista))
     (append (expande-pareja (cons (second lista) (first lista))) (expande (rest (rest lista)))))
    (else (cons (first lista) (expande (rest lista))))))

; PRUEBAS UNITARIAS

(check-equal? (expande-pareja '(hola . 3)) '(hola hola hola))
(check-equal? (expande-pareja '(#t . 5)) '(#t #t #t #t #t))

(check-equal? (expande-parejas-1 '(#t . 3) '("LPP" . 2) '(b . 4)) '(#t #t #t "LPP" "LPP" b b b b))
(check-equal? (expande-parejas-2 '(#t . 3) '("LPP" . 2) '(b . 4)) '(#t #t #t "LPP" "LPP" b b b b))

(check-equal? (expande '(4 clase ua 3 lpp aulario)) '(clase clase clase clase ua lpp lpp lpp aulario))

; EJERCICIO 5

; a)

;((lambda (x) (* x x)) 3) ; ⇒ 9
;((lambda () (+ 6 4))) ; ⇒ 10
;((lambda (x y) (* x (+ 2 y))) (+ 2 3) 4) ; ⇒ 30
;((lambda (x y) (* x (+ 2 x))) 5) ; ⇒ ERROR falta un argumento

;(define f (lambda (a b) (string-append "***" a b "***")))
;(define g f)
;(procedure? g) ; ⇒ #t
;(g "Hola" "Adios") ; ⇒ "***HolaAdios***"

; b)

;(define (suma-3 x)
;   (+ x 3))

;(lambda (x) (+ x 3))

;(define (factorial x)
;   (if (= x 0)
;      1
;      (* x (factorial (- x 1)))))

;(define factorial
;  (lambda (x)
;    (if (= x 0)
;       1
;       (* x (factorial (- x 1))))))

; c)

;(define (doble x)
;   (* 2 x))

;(define (foo f g x y)
;   (f (g x) y))

;(define (bar f p x y)
;   (if (and (p x) (p y))
;       (f x y)
;       'error))

;(foo + 10 doble 15) ; ⇒ ERROR
;(foo doble + 10 15) ; ⇒ ERROR
;(foo + doble 10 15) ; ⇒ 35
;(foo string-append (lambda (x) (string-append "***" x)) "Hola" "Adios") ; ⇒ "***HolaAdios"

;(bar doble number? 10 15) ; ⇒ ERROR
;(bar string-append string? "Hola" "Adios") ; ⇒ "HolaAdios"
;(bar + number? "Hola" 5) ; ⇒ 'error

; EJERCICIO 6

(define (coloca-frente lista elemento)
  (cons elemento lista))

(define (coloca tres-listas un dos tres)
  (cons (coloca-frente (first tres-listas) un) (cons (coloca-frente (second tres-listas) dos) (cons (coloca-frente (third tres-listas) tres) '()))))

(define (reparte-tres lista-cartas)
  (if (null? lista-cartas)
      '(() () ())
      (coloca (reparte-tres (rest (rest (rest lista-cartas))))  
              (first lista-cartas)  
              (second lista-cartas)  
              (third lista-cartas))))

(define (ultimo-elemento lista)
  (if (null? (rest lista))
      (first lista)
      (ultimo-elemento (rest lista))))

(define (quita-ultimo lista)
  (if (null? (rest lista))
      '()
      (cons (first lista) (quita-ultimo (rest lista)))))

(define (elemento-central lista)
  (cond
    ((null? (rest lista)) (first lista))
    (else (elemento-central (rest (quita-ultimo lista))))))

(define (izquierda tres-listas)
  (append (third tres-listas)
          (first tres-listas)
          (second tres-listas)))

(define (centro tres-listas)
  (append (third tres-listas)
          (second tres-listas)
          (first tres-listas)))

(define (derecha tres-listas)
  (append (second tres-listas)
          (third tres-listas)
          (first tres-listas)))

(define (adivina lista)
  (elemento-central lista))

; PRUEBAS UNITARIAS

(check-equal? (coloca-frente '() 'a) '(a))
(check-equal? (coloca-frente '(a) 'b) '(b a))

(check-equal? (coloca '(() () ()) 'a 'b 'c) '((a) (b) (c)))
(check-equal? (coloca '((a) (a) (a)) 'b 'b 'b) '((b a) (b a) (b a)))
(check-equal? (coloca '((a) (b c) (d e f)) 'g 'h 'i) '((g a) (h b c) (i d e f)))

(define doce-cartas '(A♣ 2♣ 3♣ 4♣ 5♣ 6♣ 7♣ 8♣ 9♣ J♣ Q♣ K♣))
(check-equal? (reparte-tres doce-cartas) '((A♣ 4♣ 7♣ J♣) (2♣ 5♣ 8♣ Q♣) (3♣ 6♣ 9♣ K♣)))

(check-equal? (ultimo-elemento '(a b c d e f g)) 'g)
(check-equal? (quita-ultimo '(a b c d e f g)) '(a b c d e f))

(check-equal? (elemento-central '(a b c d e f g)) 'd)







