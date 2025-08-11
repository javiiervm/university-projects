#lang racket
(require "lpp.rkt")
(require "Prac2.rkt")
(require rackunit)

; EJERCICIO 1

(define (aplica-veces f1 f2 n x)
  (if (= n 0)
      x
      (f1 (f2 (aplica-veces f1 f2 (- n 1) x)))))

(define (mueve-al-principio-condicion pred lista)
  (cond
    ((null? (filter pred lista)) lista)
    ((pred (first lista)) lista)
    (else (cons (first (mueve-al-principio-condicion pred (rest lista))) (cons (first lista) (rest (mueve-al-principio-condicion pred (rest lista))))))))

(define (comprueba pred lista1 lista2)
  (cond
    ((and (null? lista1) (null? lista2)) '())
    ((pred (first lista1) (first lista2)) (cons (cons (first lista1) (first lista2)) (comprueba pred (rest lista1) (rest lista2))))
    (else (comprueba pred (rest lista1) (rest lista2)))))

; PRUEBAS UNITARIAS

(check-equal? (aplica-veces (lambda (x) (+ x 1)) (lambda (x) (+ x 2)) 2 10) 16)
(check-equal? (aplica-veces (lambda (x) (* x x)) (lambda (x) (+ x 1)) 4 3) 7072978201)

(check-equal? (mueve-al-principio-condicion number? '(a b c 1 d 1 e)) '(1 a b c d 1 e))
(check-equal? (mueve-al-principio-condicion number? '(1 a b 1 c)) '(1 a b 1 c))
(check-equal? (mueve-al-principio-condicion number? '(a b c d)) '(a b c d))

(check-equal? (comprueba (lambda (x y) (= (string-length (symbol->string x)) y))
                         '(este es un ejercicio de examen) 
                         '(2 1 2 9 1 6))
              '((un . 2) (ejercicio . 9) (examen . 6)))

(check-equal? (comprueba (lambda (x y) (= (string-length x) (string-length y)))
                         '("aui" "a" "ae" "c" "aeiou")
                         '("hola" "b" "es" "que" "cinco"))
              '(("a" . "b") ("ae" . "es") ("aeiou" . "cinco")))

; EJERCICIO 2

(define (inserta-ordenada-generica n lista-ordenada menor-igual?)
  (cond
    ((null? lista-ordenada) (list n))
    ((not (menor-igual? (first lista-ordenada) n)) (cons n lista-ordenada))
    (else (cons (first lista-ordenada) (inserta-ordenada-generica n (rest lista-ordenada) menor-igual?)))))

(define (ordena-generica lista menor-igual?)
  (cond
    ((null? lista) '())
    (else (inserta-ordenada-generica (first lista) (ordena-generica (rest lista) menor-igual?) menor-igual?))))

(define (ordena-cartas lista-cartas)
  (ordena-generica lista-cartas (lambda (x y) (< (string->number (valor-carta x)) (string->number (valor-carta y))))))

; PRUEBAS UNITARIAS

(check-equal? (ordena-generica '("Hola" "me" "llamo" "Iñigo" "Montoya") (lambda (x y) (< (string-length x) (string-length y)))) '("me" "Hola" "llamo" "Iñigo" "Montoya"))
(check-equal? (ordena-generica '("Hola" "me" "llamo" "Iñigo" "Montoya") (lambda (x y) (string<=? x y))) '("Hola" "Iñigo" "Montoya" "llamo" "me"))
(check-equal? (ordena-generica '((2 . 2) (1 . 1) (3 . 0) (5 . 1)) (lambda (x y) (<= (+ (car x) (cdr x)) (+ (car y) (cdr y))))) '((1 . 1) (3 . 0) (2 . 2) (5 . 1)))

(check-equal? (ordena-cartas '(Q♠ J♣ 5♣ Q♥ J♦)) '(5♣ J♣ J♦ Q♠ Q♥))

; EJERCICIO 3

(map (lambda (x)
         (cond 
            ((symbol? x) (symbol->string x))
            ((number? x) (number->string x))
            ((boolean? x) (if x "#t" "#f"))
            (else "desconocido"))) '(1 #t hola #f (1 . 2))) ; ⇒ '("1" #t "hola" #f "desconocido")

(filter (lambda (x) 
            (equal? (string-ref (symbol->string x) 1) #\a)) 
    '(alicante barcelona madrid almería)) ; ⇒ '(barcelona madrid)

(foldr (lambda (dato resultado)
          (string-append dato "*" resultado)) "" 
          '("Hola" "que" "tal")) ; ⇒ "Hola*que*tal*"

(foldr append '() '((1 2) (3 4 5) (6 7) (8))) ; ⇒ '(1 2 3 4 5 6 7 8)

(foldl (lambda (dato resultado)
         (string-append
          (symbol->string (car dato))
          (symbol->string (cdr dato))
          resultado)) "" '((a . b) (hola . adios) (una . pareja))) ; ⇒ "unaparejaholaadiosab"

(foldr (lambda (dato resultado)
           (cons (+ (car resultado) dato)
                 (+ (cdr resultado) 1))) '(0 . 0) '(1 1 2 2 3 3)) ; ⇒ '(12 . 6)

(apply + (map cdr '((1 . 3) (2 . 8) (2 . 4)))) ; ⇒ 15

(apply min (map car (filter (lambda (p)
                                  (> (car p) (cdr p))) 
                                  '((3 . 1) (1 . 20) (5 . 2))))) ; ⇒ 3


; Los siguientes ejercicios utilizan esta definición de lista
(define lista-ej-3 '((2 . 7) (3 . 5) (10 . 4) (5 . 5)))

; Queremos obtener una lista donde cada número es la suma de las parejas que son pares
(filter even? (map (lambda (x) (+ (car x) (cdr x))) lista-ej-3)) ; ⇒ (8 14 10)

; Queremos obtener una lista de parejas invertidas donde la "nueva" parte izquierda es mayor que la derecha.
(filter (lambda (x) (> (car x) (cdr x))) (map (lambda (x) (cons (cdr x) (car x))) lista-ej-3)) ; ⇒ ((7 . 2) (5 . 3))

; Queremos obtener una lista cuyos elementos son las partes izquierda de aquellas parejas cuya suma sea par.
(foldr (lambda (x acumulado) (cons (car x) acumulado)) '() (filter (lambda (x) (even? (+ (car x) (cdr x)))) lista-ej-3)) ; ⇒ (3 10 5)


(define (f1 x) (lambda (y z) (string-append y z x)))
(define g1 (f1 "a"))
(check-equal? (g1 "clase" "lpp") "claselppa")

(define (f2 x) (lambda (y z) (list y x z)))
(define g2 (f2 "lpp"))
(check-equal? (g2 "hola" "clase") (list "hola" "lpp" "clase"))
 
(define (f3 g3) (lambda (z x) (g3 z x)))
(check-equal? ((f3 cons) 3 4) '(3 . 4))


; EJERCICIO 4

(define (contar-elementos lista)
  (if (null? lista)
      0
      (+ 1 (contar-elementos (rest lista)))))

(define (contar-datos-iguales-fos lista-parejas)
  (contar-elementos (filter (lambda (pareja) (equal? (car pareja) (cdr pareja))) lista-parejas)))

(define (expande-pareja pareja)
  (if (= (cdr pareja) 0)
      '()
      (cons (car pareja) (expande-pareja (cons (car pareja) (- (cdr pareja) 1))))))

(define (expande-lista lista-parejas)
  (if (null? lista-parejas)
      '()
      (append (expande-pareja (car lista-parejas)) (expande-lista (cdr lista-parejas)))))

(define (expande-lista-fos lista-parejas)
  (if (null? lista-parejas)
      '()
      (append (expande-pareja (car lista-parejas)) (expande-lista (cdr lista-parejas)))))

(define (comprueba-simbolos-fos lista-simbolos lista-num)
  (filter
    (lambda (p)
      (= (string-length (symbol->string (car p)))
         (cdr p)))
    (map cons lista-simbolos lista-num)))
          
; PRUEBAS UNITARIAS

(check-equal? (contar-datos-iguales-fos '((2 . 3) ("hola" . "hola") (\#a . \#a) (true . false))) 2)
(check-equal? (contar-datos-iguales-fos '((2 . "hola") ("hola" . 3) (\#a . true) (\#b . false))) 0)

(check-equal? (expande-pareja '(hola . 3)) '(hola hola hola))
(check-equal? (expande-pareja '(#t . 5)) '(#t #t #t #t #t))

(check-equal? (expande-lista-fos '((#t . 3) ("LPP" . 2) (b . 4))) '(#t #t #t "LPP" "LPP" b b b b))

(check-equal? (comprueba-simbolos-fos '(este es un ejercicio de examen) '(2 1 2 9 1 6)) '((un . 2) (ejercicio . 9) (examen . 6)))

; EJERCICIO 5

(define (suma-n-izq n lista-parejas)
  (map (lambda (pareja) (cons (+ n (car pareja)) (cdr pareja))) lista-parejas))

(define (busca-mayor mayor? lista)
  (foldl (lambda (acumulado elemento)
           (if (mayor? elemento acumulado) 
               elemento 
               acumulado))
         (first lista)
         (rest lista)))

(define (todos-menores?-1 lista n)
  (for-all? (lambda (sublista) (< (busca-mayor > sublista) n)) lista))

(define (todos-menores?-2 lista n)
  (for-all? (lambda (sublista) (not (exists? (lambda (x) (>= x n)) sublista))) lista))

; PRUEBAS UNITARIAS

(check-equal? (suma-n-izq 10 '((1 . 3) (0 . 9) (5 . 8) (4 . 1))) '((11 . 3) (10 . 9) (15 . 8) (14 . 1)))

(define (mayor-num? x y) (> x y))
(define (mayor-longitud? str1 str2) (> (string-length str1) (string-length str2)))

(check-equal? (busca-mayor mayor-num? '(3 5 1 9 2 8)) 9)
(check-equal? (busca-mayor mayor-longitud? '("hola" "adios" "a" "montaña")) "montaña")
(check-equal? (busca-mayor (lambda (x y) (> (car x) (car y))) '((3 . 5) (2 . 4) (8 . 1))) '(8 . 1))

(check-equal? (todos-menores?-1 '((10 30 20) (1 50 30) (30 40 90)) 100) #t)
(check-equal? (todos-menores?-1 '((10 30 20) (1 50 30) (30 40 90)) 90) #f)
(check-equal? (todos-menores?-1 '((10 30 20) (1 50 30) (30 40 90)) 55) #f)

(check-equal? (todos-menores?-2 '((10 30 20) (1 50 30) (30 40 90)) 100) #t)
(check-equal? (todos-menores?-2 '((10 30 20) (1 50 30) (30 40 90)) 90) #f)
(check-equal? (todos-menores?-2 '((10 30 20) (1 50 30) (30 40 90)) 55) #f)

; EJERCICIO 6

(define (coloca lista-sublistas . elementos)
  (if (null? elementos) 
      lista-sublistas
      (map cons (append elementos (make-list (- (length lista-sublistas) (length elementos)) '())) 
               lista-sublistas)))

(define (escoge-en-orden lista . funciones)
  (map (lambda (f) (f lista)) funciones))

(define (reparte-tres lista-cartas)
  (if (null? lista-cartas)
      '(() () ())
      (coloca (reparte-tres (rest (rest (rest lista-cartas))))  
              (first lista-cartas)  
              (second lista-cartas)  
              (third lista-cartas))))

(define (reparte-cuatro baraja)
  (let loop ((cartas baraja) (montones '(() () () ())) (indice 0))
    (if (null? cartas)
        (map reverse montones)  ; Invertimos cada montón al final
        (loop (rest cartas)
              (list-update montones indice (lambda (m) (cons (first cartas) m)))
              (modulo (+ indice 1) 4)))))

(define (reordena-tres-montones baraja f1 f2 f3)
  (escoge-en-orden (reparte-tres baraja) f1 f2 f3))

(define (reordena-cuatro-montones baraja f1 f2 f3 f4)
  (escoge-en-orden (reparte-cuatro baraja) f1 f2 f3 f4))

(define (junta-montones montones)
  (foldr append '() montones))

(define (adivina baraja par1 par2 par3)
  (list-ref baraja
            (+ (* (- (car par3) 1) (cdr par2) (cdr par1))
               (* (- (car par2) 1) (cdr par1))
               (- (car par1) 1))))

; PRUEBAS UNITARIAS

(check-equal? (coloca '(() () ()) 'a 'b 'c) '((a) (b) (c)))
(check-equal? (coloca '((a) (a)) 'b 'b) '((b a) (b a)))
(check-equal? (coloca '((a b c d)) 'e) '((e a b c d)))
(check-equal? (coloca '()) '())
(check-equal? (coloca '((a) (b c) (d e f) (g h i j)) 'k 'l 'm 'n) '((k a) (l b c) (m d e f) (n g h i j)))

(check-equal? (escoge-en-orden '(1 2 3 4 5)) '())
(check-equal? (escoge-en-orden '(1 2 3 4 5) fourth second) '(4 2))
(check-equal? (escoge-en-orden '(a b c d) third second fourth first) '(c b d a))
(check-equal? (escoge-en-orden '(dos tres un) third first second) '(un dos tres))

(check-equal? (reparte-cuatro '(A♣ 2♣ 3♣ 4♣ 5♣ 6♣ 7♣ 8♣ 9♣ J♣ Q♣ K♣)) 
              '((A♣ 5♣ 9♣) (2♣ 6♣ J♣) (3♣ 7♣ Q♣) (4♣ 8♣ K♣)))

(check-equal? (reordena-tres-montones '(A♣ 2♣ 3♣ 4♣ 5♣ 6♣ 7♣ 8♣ 9♣ J♣ Q♣ K♣) second first third)
              '((2♣ 5♣ 8♣ Q♣) (A♣ 4♣ 7♣ J♣) (3♣ 6♣ 9♣ K♣)))

(check-equal? (reordena-cuatro-montones '(A♣ 2♣ 3♣ 4♣ 5♣ 6♣ 7♣ 8♣ 9♣ J♣ Q♣ K♣) fourth second first third)
              '((4♣ 8♣ K♣) (2♣ 6♣ J♣) (A♣ 5♣ 9♣) (3♣ 7♣ Q♣)))

(check-equal? (junta-montones '((4♣ 8♣ K♣) (2♣ 6♣ J♣) (A♣ 5♣ 9♣) (3♣ 7♣ Q♣)))
              '(4♣ 8♣ K♣ 2♣ 6♣ J♣ A♣ 5♣ 9♣ 3♣ 7♣ Q♣))



