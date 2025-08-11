#lang racket
(require "lpp.rkt")
(require rackunit)

; EJERCICIO 1

(define arbol '(15 (4 (2) (3)) (8 (6)) (12 (9) (10) (11))))
(check-equal? (dato-arbol (second (hijos-arbol (third (hijos-arbol arbol))))) 10)

(define (suma-datos-arbol arbol)
    (+ (dato-arbol arbol)
       (suma-datos-bosque (hijos-arbol arbol))))

(define (suma-datos-bosque bosque)
    (if (null? bosque)
        0
        (+ (suma-datos-arbol (first bosque)) 
           (suma-datos-bosque (rest bosque)))))

; 1. ¿Qué devuelve la invocación a (suma-datos-arbol (first bosque)) que se realiza dentro de la función?
; Devuelve la suma de los datos del primer hijo del árbol original
; 2. ¿Qué devuelve la primera llamada recursiva a suma-datos-bosque?
; Devuelve la suma de todos los datos de los hijos del árbol original excepto el primero

(define (suma-datos-arbol-fos arbol)
   (foldr + (dato-arbol arbol) 
       (map suma-datos-arbol-fos (hijos-arbol arbol))))

; 2. ¿Qué devuelve la invocación a map dentro de la función?
; 1. ¿Qué invocaciones se realizan a la función + durante la ejecución de foldr sobre la lista devuelta por la invocación a map? Enuméralas en orden, indicando sus parámetros y el valor devuelto en cada una de ellas.

(define arbolb '(40 (23 (5 () ()) (32 (29 () ()) ())) (45 () (56 () ()))))
(check-equal? (dato-arbolb (hijo-izq-arbolb (hijo-der-arbolb (hijo-izq-arbolb arbolb)))) 29)

; EJERCICIO 2

(define (to-string-arbol arbol)
  (define (procesar-hijos lista-hijos)
    (if (null? lista-hijos)
        ""
        (string-append (to-string-arbol (first lista-hijos))
                       (procesar-hijos (rest lista-hijos)))))
  (if (hoja-arbol? arbol)
      (symbol->string (dato-arbol arbol))
      (string-append (symbol->string (dato-arbol arbol))
                     (procesar-hijos (hijos-arbol arbol)))))

(define (to-string-arbol-fos arbol)
  (string-append (symbol->string (dato-arbol arbol))
                 (apply string-append (map to-string-arbol-fos (hijos-arbol arbol)))))

; PRUEBAS UNITARIAS

(define arbol2 '(a (b (c (d)) (e)) (f)))
(check-equal? (to-string-arbol arbol2) "abcdef")
(check-equal? (to-string-arbol-fos arbol2) "abcdef")

; EJERCICIO 3

(define (hojas-cumplen pred arbol)
  (define (procesar-hijos pred lista-hijos)
    (if (null? lista-hijos)
        '()
        (append (hojas-cumplen pred (first lista-hijos))
                (procesar-hijos pred (rest lista-hijos)))))
  (if (hoja-arbol? arbol)
      (if (pred (dato-arbol arbol)) (list (dato-arbol arbol)) '())
      (procesar-hijos pred (hijos-arbol arbol))))

(define (hojas-cumplen-fos pred arbol)
  (if (hoja-arbol? arbol)
      (if (pred (dato-arbol arbol)) (list (dato-arbol arbol)) '())
      (apply append (map (lambda (subarbol) (hojas-cumplen-fos pred subarbol))
                         (hijos-arbol arbol)))))

(define (todas-hojas-cumplen? pred arbol)
  (define (procesar-hijos pred lista-hijos)
    (if (null? lista-hijos)
        #t
        (and (todas-hojas-cumplen? pred (first lista-hijos)) (procesar-hijos pred (rest lista-hijos)))))
  (if (hoja-arbol? arbol)
      (pred (dato-arbol arbol))
      (procesar-hijos pred (hijos-arbol arbol))))

(define (todas-hojas-cumplen-fos? pred arbol)
  (if (hoja-arbol? arbol)
      (pred (dato-arbol arbol))
      (for-all? (lambda (subarbol) (todas-hojas-cumplen-fos? pred subarbol)) 
                (hijos-arbol arbol))))

; PRUEBAS UNITARIAS

(define arbol31 '(10 (2) (12 (4) (2)) (10 (5))))
(define arbol32 '(10 (2) (12 (4) (2)) (10 (6))))
(check-equal? (hojas-cumplen even? arbol31) '(2 4 2))
(check-equal? (hojas-cumplen even? arbol32) '(2 4 2 6))
(check-equal? (hojas-cumplen-fos even? arbol31) '(2 4 2))
(check-equal? (hojas-cumplen-fos even? arbol32) '(2 4 2 6))

(check-equal? (todas-hojas-cumplen? even? arbol31) #f)
(check-equal? (todas-hojas-cumplen? even? arbol32) #t)
(check-equal? (todas-hojas-cumplen-fos? even? arbol31) #f)
(check-equal? (todas-hojas-cumplen-fos? even? arbol32) #t)

; EJERCICIO 4

(define (suma-raices-hijos arbol)
  (apply + (map dato-arbol (hijos-arbol arbol))))

(define (raices-mayores-arbol? arbol)
  (define (procesar-hijos lista-hijos)
    (if (null? lista-hijos)
        #t
        (and (raices-mayores-arbol? (first lista-hijos)) 
             (procesar-hijos (rest lista-hijos)))))
  (and (> (dato-arbol arbol) (suma-raices-hijos arbol))
       (procesar-hijos (hijos-arbol arbol))))

; PRUEBAS UNITARIAS

(define arbol3 '(20 (2) (8 (4) (2)) (9 (5))))
(check-equal? (suma-raices-hijos arbol3) 19)
(check-equal? (suma-raices-hijos (second (hijos-arbol arbol3))) 6)

(define arbol4 '(20 (2) (8 (4) (5)) (9 (5))))
(check-equal? (raices-mayores-arbol? arbol3) #t)
(check-equal? (raices-mayores-arbol? arbol4) #f)



























