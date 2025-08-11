#lang racket
(require rackunit)

(define (cuadrado x)
  (* x x))

(define (ejeX a b)
  (- (car b) (car a)))

(define (ejeY a b)
  (- (cdr b) (cdr a)))

(define (distancia a b)
  (sqrt(+ (cuadrado (ejeX a b)) (cuadrado (ejeY a b)))))

(define (ladoigual? a b c) ; Esta función comprueba si hay dos lados iguales en el triángulo y devuelve true en caso de que eso ocurra, false si no
  (or (= (distancia a b) (distancia a c)) (= (distancia a b) (distancia b c)) (= (distancia b c) (distancia a c))))

(define (todosladosiguales? a b c) ; Esta función comprueba si todos los lados son iguales y devuelve true en caso de que eso ocurra, false si no
  (and (= (distancia a b) (distancia a c)) (= (distancia a b) (distancia b c)) (= (distancia b c) (distancia a c))))

(define (isosceles? a b c)
  (cond
    ((and (not (todosladosiguales? a b c)) (ladoigual? a b c)) "El triángulo es isósceles")
    (else "El triángulo NO es isósceles")))
  


; PRUEBAS UNITARIAS
; Función distancia
(check-equal? (distancia (cons 0 0) (cons 0 10)) 10)
(check-equal? (distancia (cons 0 0) (cons 10 0)) 10)
(check-equal? (distancia (cons 0 0) (cons 10 10)) 14.142135623730951)
; Funcion isosceles?
(check-equal? (isosceles? (cons 0 4) (cons 1 0) (cons -1 0)) "El triángulo es isósceles")
(check-equal? (isosceles? (cons 0 (sqrt 3)) (cons -1 0) (cons 1 0)) "El triángulo NO es isósceles")