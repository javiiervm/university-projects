#lang racket
(require rackunit)
(require 2htdp/image)
(require "lpp.rkt")
(require "Prac2.rkt")

; EJERCICIO 1

(define (minimo lista)
  (if (null? (rest lista))
      (first lista)
      (menor (first lista) (minimo (rest lista)))))

; Apartado a.2)
; ¿Qué lista se pasa como parámetro a la primera llamada recursiva a la función?
  ; '(2 8 1 4)
; ¿Qué devuelve esa llamada recursiva?
  ; 1
; ¿Con qué argumentos se llama a la función menor que devuelve el resultado final?
  ; (menor 5 1)

;(define (concatena lista)
;  (list->string lista))

(define (concatena lista-chars)
  (if (null? lista-chars)  ; Caso base: si la lista está vacía, devolver ""
      ""
      (string-append (string (first lista-chars))  ; Convertir primer carácter a cadena
                     (concatena (rest lista-chars)))))  ; Llamada recursiva confiando en la recursión
      
(define (cifra-cadena cad desplazamiento)
  (if (zero? (string-length cad))  ; Caso base: cadena vacía devuelve ""
      ""
      (string-append 
       (string (cifra-caracter (string-ref cad 0) desplazamiento))  ; Primer carácter cifrado
       (cifra-cadena (substring cad 1) desplazamiento))))  ; Llamada recursiva con el resto de la cadena

(define (descifra-cadena cad desplazamiento)
  (if (zero? (string-length cad))  ; Caso base: cadena vacía devuelve ""
      ""
      (string-append 
       (string (descifra-caracter (string-ref cad 0) desplazamiento))  ; Primer carácter cifrado
       (descifra-cadena (substring cad 1) desplazamiento))))  ; Llamada recursiva con el resto de la cadena

(define (contiene? lista elemento)
  (cond
    ((null? lista) #f)
    ((equal? (first lista) elemento) #t)
    (else (contiene? (rest lista) elemento))))

(define (str-contiene? cadena char)
  (contiene? (string->list cadena) char))

; PRUEBAS UNITARIAS

(check-equal? (minimo '(2)) 2)
(check-equal? (minimo '(1 8 6 4 3)) 1)
(check-equal? (minimo '(1 -1 3 -6 4)) -6)

(check-equal? (concatena '()) "")
(check-equal? (concatena '(#\H #\o #\l #\a)) "Hola")
(check-equal? (concatena '(#\S #\c #\h #\e #\m #\e #\space #\m #\o #\l #\a)) "Scheme mola")

(check-equal? (cifra-cadena "En un lugar de la Mancha, de cuyo nombre no quiero acordarme" 10) "Ox ex veqkb no vk Wkxmrk, no meiy xywlbo xy aesoby kmybnkbwo")
(check-equal? (descifra-cadena "Ox ex veqkb no vk Wkxmrk, no meiy xywlbo xy aesoby kmybnkbwo" 10) "En un lugar de la Mancha, de cuyo nombre no quiero acordarme")

(check-equal? (contiene? '(algo 3 #\A) 3) #t)
(check-equal? (contiene? '(algo 3 #\A) "algo") #f)
(check-equal? (contiene? '(algo 3 #\A) 'algo) #t)

(check-equal? (str-contiene? "Hola" #\o) #t)
(check-equal? (str-contiene? "Esto es una frase" #\space) #t)
(check-equal? (str-contiene? "Hola" #\h) #f)

; EJERCICIO 2

(define (todos-iguales? lista)
  (cond
    ((null? lista) #t)  ; Caso base: si la lista está vacía, es verdadera
    ((null? (rest lista)) #t)  ; Caso base: si tiene un solo elemento, es verdadera
    ((equal? (first lista) (first (rest lista))) 
     (todos-iguales? (rest lista)))  ; Caso recursivo
    (else #f)))  ; Si hay un valor distinto, devuelve #f

(define (todos-distintos? lista)
  (cond
    ((null? lista) #t)  ; Caso base: si la lista está vacía, es verdadera
    ((null? (rest lista)) #t)  ; Caso base: si tiene un solo elemento, es verdadera
    ((contiene? (rest lista) (first lista)) #f)
    (else (todos-distintos? (rest lista)))))

(define (contar-elementos lista elemento)
  (cond
    ((null? lista) 0)  ; Caso base: lista vacía, devolver 0
    ((equal? (first lista) elemento) 
     (+ 1 (contar-elementos (rest lista) elemento)))  ; Si es igual, sumar 1
    (else 
     (contar-elementos (rest lista) elemento))))  ; Si no es igual, seguir sin sumar

(define (eliminar-todos lista elemento)
  (cond
    ((null? lista) '())  
    ((equal? (first lista) elemento) (eliminar-todos (rest lista) elemento))  
    (else (cons (first lista) (eliminar-todos (rest lista) elemento)))))  

(define (elementos-repes-2 lista)
  (cond
    ((null? lista) 0)
    ((= (contar-elementos lista (first lista)) 2)  
     (+ 1 (elementos-repes-2 (eliminar-todos lista (first lista)))))
    (else (elementos-repes-2 (eliminar-todos lista (first lista))))))

(define (elementos-repes-mas-de-2 lista)
  (cond
    ((null? lista) 0)
    ((> (contar-elementos lista (first lista)) 2)  
     (+ 1 (elementos-repes-mas-de-2 (eliminar-todos lista (first lista)))))
    (else (elementos-repes-mas-de-2 (eliminar-todos lista (first lista))))))

(define (solo-dos-iguales? lista)
  (cond
    ((null? lista) #f)
    ((todos-iguales? lista) #f)
    ((todos-distintos? lista) #f)
    ((and (= (elementos-repes-2 lista) 1) (= (elementos-repes-mas-de-2 lista) 0)) #t)
    (else #f)))

; PRUEBAS UNITARIAS

(check-equal? (todos-iguales? '()) #t)
(check-equal? (todos-iguales? '(a)) #t)
(check-equal? (todos-iguales? '(a a a a a a a)) #t)
(check-equal? (todos-iguales? '((a b) (a b) (a b))) #t)
(check-equal? (todos-iguales? '(a a a a a b)) #f)

(check-equal? (todos-distintos? '()) #t)
(check-equal? (todos-distintos? '(a)) #t)
(check-equal? (todos-distintos? '(a b c)) #t)
(check-equal? (todos-distintos? '(a b c a)) #f)

(check-equal? (contar-elementos '() 'a) 0)
(check-equal? (contar-elementos '(a) 'a) 1)
(check-equal? (contar-elementos '(a) 'b) 0)
(check-equal? (contar-elementos '(a b c a d e f a) 'a) 3)
(check-equal? (contar-elementos '(x y z x x y) 'x) 3)
(check-equal? (contar-elementos '(1 2 3 1 2 1 4 5 1) 1) 4)
(check-equal? (contar-elementos '(#\a #\b #\a #\c #\a) #\a) 3)
(check-equal? (contar-elementos '(#\x #\y #\z) #\w) 0)
(check-equal? (contar-elementos '(apple banana apple grape apple) 'apple) 3)
(check-equal? (contar-elementos '(#t #f #t #f #t) #t) 3)

(check-equal? (eliminar-todos '() 'a) '())  ; Caso base: lista vacía
(check-equal? (eliminar-todos '(a) 'a) '())  ; Un solo elemento, que se elimina
(check-equal? (eliminar-todos '(a) 'b) '(a))  ; Un solo elemento, que no se elimina
(check-equal? (eliminar-todos '(a b c) 'a) '(b c))  ; Elimina el primer elemento
(check-equal? (eliminar-todos '(a b c) 'b) '(a c))  ; Elimina el elemento del medio
(check-equal? (eliminar-todos '(a b c) 'c) '(a b))  ; Elimina el último elemento
(check-equal? (eliminar-todos '(a b a c a d) 'a) '(b c d))  ; Elimina múltiples ocurrencias
(check-equal? (eliminar-todos '(1 2 3 1 4 1) 1) '(2 3 4))  ; Elimina múltiples números
(check-equal? (eliminar-todos '(x y z) 'w) '(x y z))  ; No hay elementos a eliminar
(check-equal? (eliminar-todos '(a a a a) 'a) '())  ; Todos los elementos son eliminados

(check-equal? (elementos-repes-2 '()) 0)
(check-equal? (elementos-repes-2 '(a)) 0)
(check-equal? (elementos-repes-2 '(a b c d e)) 0)
(check-equal? (elementos-repes-2 '(a b c a)) 1)
(check-equal? (elementos-repes-2 '(a b c a d e f d)) 2)
(check-equal? (elementos-repes-2 '(a b c a a d e f d)) 1)
(check-equal? (elementos-repes-2 '(a a b b b c c c d d e e)) 3)
(check-equal? (elementos-repes-2 '(a a a b b b c c c)) 0)
(check-equal? (elementos-repes-2 '(a a b b c c d d d e e f f)) 5)
(check-equal? (elementos-repes-2 '(1 2 3 1 2 4 4 5 5 6 7 8)) 4)
(check-equal? (elementos-repes-2 '(#\a #\b #\c #\a #\d #\e #\d)) 2)

(check-equal? (solo-dos-iguales? '()) #f)
(check-equal? (solo-dos-iguales? '(a)) #f)
(check-equal? (solo-dos-iguales? '(a b c a)) #t)
(check-equal? (solo-dos-iguales? '(a b c b a a)) #f)
(check-equal? (solo-dos-iguales? '(a b c a a)) #f)
(check-equal? (solo-dos-iguales? '(a b c a b)) #f)

; EJERCICIO 3
; a.1)
(define p1 (list (cons "a" "b") "c" (cons "d" (list "e"))))
(caja-puntero p1)
; a.2)
(cdr (first p1)) ; "b"
(first (third p1)) ; "d"
; b.1)
(define p2 (list (list (cons "a" (cons "b" "c")) (list "d" "e") "f") "g"))
(caja-puntero p2)
; b.2)
(cdr (cdr (first (first p2)))) ; "c"
(second (second (first p2))) ; "e"

; EJERCICIO 4

(define (datos-iguales? pareja)
  (equal? (car pareja) (cdr pareja)))

(define (contar-datos-iguales lista-parejas)
  (cond
    ((null? lista-parejas) 0)
    ((equal? (datos-iguales? (first lista-parejas)) #t)
     (+ 1 (contar-datos-iguales (rest lista-parejas))))
    (else (contar-datos-iguales (rest lista-parejas)))))

; PRUEBAS UNITARIAS

(check-equal? (contar-datos-iguales '((2 . 3) ("hola" . "hola") (\#a . \#a) (true . false))) 2)
(check-equal? (contar-datos-iguales '((2 . "hola") ("hola" . 3) (\#a . true) (\#b . false))) 0)

; EJERCICIO 5

(define (veces-palo lista palo)
  (cond
    ((null? lista) 0)
    ((equal? (obten-palo (string-ref (symbol->string (first lista)) (- (string-length (symbol->string (first lista))) 1))) 
        (symbol->string palo))
         (+ 1 (veces-palo (rest lista) palo)))
    (else (veces-palo (rest lista) palo))))

(define (color? lista)
  (=
   (veces-palo lista (string->symbol (obten-palo (string-ref (symbol->string (first lista)) (- (string-length (symbol->string (first lista))) 1)))))
   (length lista)))

(define (orden? x y)
  (= y (+ x 1)))

(define (escalera? lista)
  (cond
    ((or (null? lista) (null? (rest lista))) #t)
    ((not (orden? (obten-valor (string-ref (symbol->string (first lista)) 0)) (obten-valor (string-ref (symbol->string (second lista)) 0)))) #f)
    (else (escalera? (rest lista)))))

(define (escalera-color? mano)
  (and (color? mano) (escalera? mano)))

; PRUEBAS UNITARIAS

(check-equal? (veces-palo '(5♠ 6♣ 7♥ 8♦ 9♠) 'Picas) 2)
(check-equal? (veces-palo '(J♠ Q♣ K♥) 'Diamantes) 0)
(check-equal? (veces-palo '(A♣ 2♥ 3♠) 'Corazones) 1)
(check-equal? (veces-palo '() 'Tréboles) 0)

(check-equal? (color? '(5♣ J♦ J♣ Q♠ Q♥)) #f)
(check-equal? (color? '(2♦ 5♦ 6♦ J♦ K♦)) #t)

(check-equal? (escalera? '(5♣ 4♦ 3♣)) #f)
(check-equal? (escalera? '(8♣ 9♦ J♣ Q♦)) #t)
(check-equal? (escalera? '(8♣ 2♣)) #f)
(check-equal? (escalera? '(A♣ 2♦ 3♣)) #t)

(check-equal? (escalera-color? '(5♣ 6♦ 7♣ 8♠ 9♥)) #f)
(check-equal? (escalera-color? '(A♦ 2♦ 3♦ 4♦ 5♦)) #t)

; EJERCICIO 6

(define (suma-izq pareja n)
  (cons (+ n (car pareja)) (cdr pareja)))

(define (suma-der pareja n)
  (cons (car pareja) (+ n (cdr pareja))))

(define (suma-impares-pares lista-num)
  (cond
    ((null? lista-num) (cons 0 0))  ; Caso base: lista vacía ⇒ (0 . 0)
    ((even? (first lista-num))  
     (suma-der (suma-impares-pares (rest lista-num)) (first lista-num)))  ; Sumar a pares
    (else  
     (suma-izq (suma-impares-pares (rest lista-num)) (first lista-num))))) ; Sumar a impares

; b.2)
; '(2 . 8)

(define (cadena-mayor lista)
  (if (null? lista)
      (cons "" 0)  ; Caso base: lista vacía
      (let ((subsolucion (cadena-mayor (rest lista))))  ; Llamada recursiva una sola vez
        (if (> (string-length (first lista)) (cdr subsolucion))
            (cons (first lista) (string-length (first lista)))  ; Si la primera es más larga, la devolvemos
            subsolucion))))  ; Si no, devolvemos la solución del resto

; PRUEBAS UNITARIAS

(check-equal? (suma-izq (cons 10 20) 3) '(13 . 20))
(check-equal? (suma-der (cons 10 20) 5) '(10 . 25))

(check-equal? (suma-impares-pares '(3 2 1 4 8 7 6 5)) '(16 . 20))
(check-equal? (suma-impares-pares '(3 1 5)) '(9 . 0))

(check-equal? (cadena-mayor '("vamos" "a" "obtener" "la" "cadena" "mayor")) '("obtener" . 7))
(check-equal? (cadena-mayor '("prueba" "con" "maximo" "igual")) '("maximo" . 6))
(check-equal? (cadena-mayor '()) '("" . 0))


