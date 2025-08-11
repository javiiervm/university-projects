#lang racket
(require rackunit)

(provide menor cifra-caracter descifra-caracter valor-carta obten-palo carta obten-valor)

; EJERCICIO 1

(define (binario-a-decimal b3 b2 b1 b0)
  (+ (* b3 (expt 2 3)) (* b2 (expt 2 2)) (* b1 (expt 2 1)) (* b0 (expt 2 0))))

(define (binario-a-hexadecimal b3 b2 b1 b0)
  (if (< (binario-a-decimal b3 b2 b1 b0) 10)
      (integer->char (+ 48 (binario-a-decimal b3 b2 b1 b0)))
      (integer->char (+ 55 (binario-a-decimal b3 b2 b1 b0)))))

; TEST UNITARIOS

(check-equal? (binario-a-decimal 0 1 1 0) 6)
(check-equal? (binario-a-decimal 0 0 1 0) 2)
(check-equal? (binario-a-decimal 1 1 1 1) 15)

(check-equal? (binario-a-hexadecimal 1 1 1 1) #\F)
(check-equal? (binario-a-hexadecimal 0 1 1 0) #\6)
(check-equal? (binario-a-hexadecimal 1 0 1 0) #\A)

; EJERCICIO 2

(define (entre-az? char)
  (if (or (< (char->integer char) 97) (> (char->integer char) 122)) #f #t))

(define (entre-AZ? char)
  (if (or (< (char->integer char) 65) (> (char->integer char) 90)) #f #t))

(define (encuentra-indice char)
  (- (char->integer char) 97))

(define (encuentra-caracter num)
  (integer->char (+ num 97)))

(define (rota-indice num1 num2)
  (cond
    ((> (+ num1 num2) 25) (- (+ num1 num2) 26))
    ((< (+ num1 num2) 0) (+ (+ num1 num2) 26))
    (else (+ num1 num2))))

(define (cifra-caracter char desp)
  (cond
    ((entre-AZ? char) (integer->char (- (+ 97 (rota-indice (encuentra-indice (integer->char (+ 32 (char->integer char)))) desp)) 32)))
    ((entre-az? char) (integer->char (+ 97 (rota-indice (encuentra-indice char) desp))))
    (else char)))

(define (descifra-caracter char desp)
  (cond
    ((entre-AZ? char) (integer->char (- (+ 97 (rota-indice (encuentra-indice (integer->char (+ 32 (char->integer char)))) (* -1 desp))) 32)))
    ((entre-az? char) (integer->char (+ 97 (rota-indice (encuentra-indice char) (* -1 desp)))))
    (else char)))

; TEST UNITARIOS

(check-equal? (encuentra-indice #\a) 0)
(check-equal? (encuentra-indice #\b) 1)
(check-equal? (encuentra-indice #\m) 12)
(check-equal? (encuentra-indice #\z) 25)

(check-equal? (encuentra-caracter 0) #\a)
(check-equal? (encuentra-caracter 1) #\b)
(check-equal? (encuentra-caracter 12) #\m)
(check-equal? (encuentra-caracter 25) #\z)

(check-equal? (entre-az? #\a) #t)
(check-equal? (entre-az? #\m) #t)
(check-equal? (entre-az? #\z) #t)
(check-equal? (entre-az? #\`) #f)
(check-equal? (entre-az? #\{) #f)

(check-equal? (rota-indice 4 12) 16)
(check-equal? (rota-indice 4 24) 2)
(check-equal? (rota-indice 4 -5) 25)

(check-equal? (cifra-caracter #\c 5) #\h)
(check-equal? (cifra-caracter #\z -1) #\y)
(check-equal? (cifra-caracter #\j 40) #\x)
(check-equal? (cifra-caracter #\D 3) #\G)
(check-equal? (cifra-caracter #\ñ 3) #\ñ)

(check-equal? (descifra-caracter #\d 3) #\a)
(check-equal? (descifra-caracter #\y -1) #\z)
(check-equal? (descifra-caracter #\x 40) #\j)
(check-equal? (descifra-caracter #\G 3) #\D)
(check-equal? (descifra-caracter #\tab 3) #\tab)

; EJERCICIO 3

(define (menor-de-tres n1 n2 n3)
  (if (and (< n1 n2) (< n1 n3)) n1 (if (and (< n2 n1) (< n2 n3)) n2 n3)))

(define (menor x y)
  (if (< x y) x y))

(define (menor-de-tres-v2 n1 n2 n3)
  (menor (menor n1 n2) (menor n1 n3)))

; TEST UNITARIOS

(check-equal? (menor-de-tres 2 8 1) 1)
(check-equal? (menor-de-tres-v2 2 8 1) 1)
(check-equal? (menor-de-tres 3 0 3) 0)
(check-equal? (menor-de-tres-v2 3 0 3) 0)

; EJERCICIO 4

; Apartado a)

(define (f x)
    (cons x 2))

(define (g x y)
    (cons x y))

; Orden aplicativo
; (g (f (+ 2 1)) (+ 1 1))
; (g (f 3) 2)
; (g (3 . 2) 2)
; ((3 . 2) . 2)

; Orden normal
; (g (f (+ 2 1)) (+ 1 1))
; (cons (f (+ 2 1)) (+ 1 1))
; (cons (cons (+ 2 1) 2) (+ 1 1))
; ((cons (+ 2 1) 2) . 2)
; ((+ 2 1) . 2) . 2)
; ((3 . 2) . 2)

; Apartado b)

(define (func-1 x)
    (/ x 0))

(define (func-2 x y)
    (if (= x 0)
        0
        y))

; Orden aplicativo
; (func-2 0 (func-1 10))
; Error por división entre cero

; Orden normal
; (func-2 0 (func-1 10))
; 0

; EJERCICIO 5

(define (eleccion-palabra palabra1 palabra2)
  (if (or (> (string-length palabra1) (string-length palabra2)) (= (string-length palabra1) (string-length palabra2))) palabra1 palabra2))

(define (cadenas-mayores lista1 lista2)
  (append
   (append
    (list (eleccion-palabra (first lista1) (first lista2)))
    (list (eleccion-palabra (second lista1) (second lista2)))
    (list (eleccion-palabra (third lista1) (third lista2))))))

; TEST UNITARIOS

(check-equal? (cadenas-mayores '("hola" "que" "tal") '("meme" "y" "adios")) '("hola" "que" "adios"))
(check-equal? (cadenas-mayores '("esto" "es" "lpp") '("hoy" "hay" "clase")) '("esto" "hay" "clase"))

; EJERCICIO 6

(define (obten-palo char)
  (cond
    ((char=? char #\♠) "Picas")
    ((char=? char #\♣) "Tréboles")
    ((char=? char #\♥) "Corazones")
    ((char=? char #\♦) "Diamantes")
    (else "")))

(define (obten-valor char)
  (cond
    ((and (> (char->integer char) 49) (< (char->integer char) 58)) (- (char->integer char) 48))
    ((= (char->integer char) 65) 1)
    ((= (char->integer char) 74) 10)
    ((= (char->integer char) 81) 11)
    ((= (char->integer char) 75) 12)
    (else "")))

(define (carta id)
  (cons (obten-valor (string-ref (symbol->string id) 0)) (obten-palo (string-ref (symbol->string id) 1))))

(define (valor-carta cartaa)
  (number->string (car (carta cartaa))))

(define (jugada-mano carta1 carta2 carta3)
  (cond
    ((and (= (car (carta carta1)) (car (carta carta2))) (= (car (carta carta1)) (car (carta carta3))) (= (car (carta carta2)) (car (carta carta3))))
     (string-append "trío de " (valor-carta carta1)))
    ((or (= (car (carta carta1)) (car (carta carta2))) (= (car (carta carta1)) (car (carta carta3))))
     (string-append "pareja de " (valor-carta carta1)))
    ((or (= (car (carta carta2)) (car (carta carta1))) (= (car (carta carta2)) (car (carta carta3))))
     (string-append "pareja de " (valor-carta carta2)))
    ((or (= (car (carta carta3)) (car (carta carta1))) (= (car (carta carta3)) (car (carta carta1))))
     (string-append "pareja de " (valor-carta carta3)))
    (else "nada")))

; TEST UNITARIOS

(check-equal? (obten-palo #\♠) "Picas")
(check-equal? (obten-palo #\♥) "Corazones")
(check-equal? (obten-valor #\3) 3)
(check-equal? (obten-valor #\J) 10)
(define tres-de-picas '3♠)
(define as-de-corazones 'A♥)
(define jota-de-diamantes 'J♦)
(check-equal? (carta tres-de-picas) '(3 . "Picas"))
(check-equal? (carta as-de-corazones) '(1 . "Corazones"))
(check-equal? (carta jota-de-diamantes) '(10 . "Diamantes"))
(check-equal? (carta 'K♣) '(12 . "Tréboles"))

(check-equal? (jugada-mano '3♥ '3♣ '3♥) "trío de 3")
(check-equal? (jugada-mano 'K♦ '7♠ 'K♥) "pareja de 12")
(check-equal? (jugada-mano '5♣ '4♣ '6♣) "nada")

