#lang racket
(require "lpp.rkt")
(require rackunit)

; EJERCICIO 1

(define lista-a '((a b) d (c (e) (f g) h)))
(check-equal? (fourth (third lista-a)) 'h)

(define lista-b1 '((2 (3)) (4 2) ((2) 3)))
(define lista-b2 '((b) (c (a)) d (a)))

;; Apartado c)
;; 1. '((4 (9)) (16 4) ((4) 9))
;; 2. 1 -> (2 (3)); 2 -> ((4 2) ((2) 3))
;; 3. 1 -> (4 (9)); 2 -> ((16 4) ((4) 9))

(define (suma-1-si-mayor-igual-que-0 x)
  (if (>= x 0)
      (+ x 1)
      x))

(define (nivel-hoja-fos dato ld)
  (if (hoja? ld)
      (if (equal? ld dato) 0 -1)
      (suma-1-si-mayor-igual-que-0
       (foldr max -1 (map (lambda (elem)
                           (nivel-hoja-fos dato elem)) ld)))))

(map (lambda (elem) (nivel-hoja-fos 'a elem)) lista-b2); -> '(-1 2 -1 1)

; EJERCICIO 2

(define (concatena lista)
  (cond
    ((null? lista) "")
    ((list? (first lista)) (string-append (concatena (first lista)) (concatena (rest lista))))
    (else (string-append (symbol->string (first lista)) (concatena (rest lista))))))

(define (concatena-fos lista)
  (foldr
   (lambda (elemento acumulador) 
     (string-append 
      (if (list? elemento) (concatena-fos elemento) (symbol->string elemento)) 
      acumulador))
   "" lista))

(define (todos-positivos? lista)
  (cond
    ((null? lista) #t)
    ((list? (first lista)) (and (todos-positivos? (first lista)) (todos-positivos? (rest lista))))
    (else (and (> (first lista) 0) (todos-positivos? (rest lista))))))

(define (todos-positivos-fos? lista)
  (for-all? (lambda (elemento) (if (list? elemento) (todos-positivos-fos? elemento) (> elemento 0))) lista))

; PRUEBAS UNITARIAS

(check-equal? (concatena '(a b (c) d)) "abcd")
(check-equal? (concatena-fos '(a b (c) d)) "abcd")
(check-equal? (concatena '(a (((b)) (c (d (e f (g))) h)) i)) "abcdefghi")
(check-equal? (concatena-fos '(a (((b)) (c (d (e f (g))) h)) i)) "abcdefghi")

(check-equal? (todos-positivos? '(1 (2 (3 (-3))) 4)) #f)
(check-equal? (todos-positivos-fos? '(1 (2 (3 (3))) 4)) #t)

; EJERCICIO 3

(define (cumplen-predicado pred lista)
  (cond
    ((null? lista) '())
    ((list? (first lista)) (append (cumplen-predicado pred (first lista)) (cumplen-predicado pred (rest lista))))
    (else
     (if (pred (first lista))
         (cons (first lista) (cumplen-predicado pred (rest lista)))
         (cumplen-predicado pred (rest lista))))))

(define (cumplen-predicado-fos pred lista)
  (foldr
   (lambda (elemento acumulador)
     (if (list? elemento)
         (append (cumplen-predicado-fos pred elemento) acumulador)
         (if (pred elemento)
             (cons elemento acumulador)
             acumulador)))
   '() lista))

(define (busca-mayores n lista-num)
  (cumplen-predicado-fos (lambda (x) (> x n)) lista-num))

(define (empieza-por char lista-pal)
  (cumplen-predicado-fos (lambda (x) (char=? char (string-ref (symbol->string x) 0))) lista-pal))

; PRUEBAS UNITARIAS

(check-equal? (cumplen-predicado even? '(1 (2 (3 (4))) (5 6))) '(2 4 6))
(check-equal? (cumplen-predicado pair? '(((1 . 2) 3 (4 . 3) 5) 6)) '((1 . 2) (4 . 3)))
(check-equal? (cumplen-predicado-fos even? '(1 (2 (3 (4))) (5 6))) '(2 4 6))
(check-equal? (cumplen-predicado-fos pair? '(((1 . 2) 3 (4 . 3) 5) 6)) '((1 . 2) (4 . 3)))
(check-equal? (busca-mayores 10 '(-1 (20 (10 12) (30 (25 (15)))))) '(20 12 30 25 15))
(check-equal? (empieza-por #\m '((hace (mucho tiempo)) (en) (una galaxia ((muy  muy) lejana)))) '(mucho muy muy))

; EJERCICIO 4

(define (sustituye-elem old new lista)
  (map
   (lambda (x)
    (if (list? x)
        (sustituye-elem old new x)
        (if (equal? x old)
            new
            x))) lista))

(define (nivel-mas-profundo-aux lista nivel)
  (cond
    ((null? lista) (cons 'null 0))
    ((not (list? (first lista)))
     (if (> nivel (cdr (nivel-mas-profundo-aux (rest lista) nivel)))
         (cons (first lista) nivel)
         (nivel-mas-profundo-aux (rest lista) nivel)))
    (else
     (if (> (cdr (nivel-mas-profundo-aux (first lista) (+ nivel 1))) (cdr (nivel-mas-profundo-aux (rest lista) nivel)))
         (nivel-mas-profundo-aux (first lista) (+ nivel 1))
         (nivel-mas-profundo-aux (rest lista) nivel)))))

(define (nivel-mas-profundo lista)
  (nivel-mas-profundo-aux lista 1))

; PRUEBAS UNITARIAS

(check-equal? (sustituye-elem 'c 'h '(a b (c d (e c)) c (f (c) g))) '(a b (h d (e h)) h (f (h) g)))

(check-equal? (nivel-mas-profundo '(2 (3))) '(3 . 2))
(check-equal? (nivel-mas-profundo '((2) (3 (4)((((((5))) 6)) 7)) 8)) '(5 . 8))

; EJERCICIO 5

(define (mezclar lista1 lista2 n)
  (map (lambda (elem1 elem2)
         (cond
           ((and (list? elem1) (list? elem2))
            (mezclar elem1 elem2 (- n 1)))
           ((<= n 0) elem2)
           (else elem1)))
       lista1 lista2))

(define (intersecta lista1 lista2)
  

; PRUEBAS UNITARIAS

(define lista1 '(((a b) ((c))) (d) e))
(define lista2 '(((1 2) ((3))) (4) 5))
(check-equal? (mezclar lista1 lista2 2) '(((1 2) ((3))) (d) e))

(define lista-1 '(a (b c) (d))) 
;     * 
;   / | \ 
;  a  *  *
;    / \  \ 
;   b   c  d

(define lista-2 '((e) (f) (g)))
;     * 
;   / | \ 
;  *  *  * 
; /  /    \ 
;e  f      g

(pinta-lista (intersecta lista-1 lista-2))
; ⇒ (((b . f)) ((d . g)))
;     *
;     | \
;     *  *
;    /    \
;  (b.f)  (d.g)








