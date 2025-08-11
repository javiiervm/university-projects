import Foundation


// EJERCICIO 1

// a) Código corregido

struct MiEstructura {
    var x = 0
}

class MiClase {
    var x = 0
}

func foo(_ c: MiClase, _ x: Int) {
    c.x = x
}

var s1 = MiEstructura() // Declararar s1.x = 10 da error porque s1 estaba declarado como let 
var s2 = s1
let c1 = MiClase()
var c2 = c1

s1.x = 10
c1.x = 10
print("s2.x: \(s2.x), c2.x: \(c2.x)")

foo(c1, 20)
print("c1.x, después de llamar a la función: \(c1.x)")

// Salida esperada
// s2.x: 0, c2.x: 10
// c1.x, después de llamar a la función: 20

// b)

struct Cuadrado {
    var esquina = Coord(x: 0.0, y: 0.0)
    var lado: Double

    func movido1(incX: Double, incY: Double) -> Cuadrado {
        let nuevaEsquina = esquina.movida(incX: incX, incY: incY)
        return Cuadrado(esquina: nuevaEsquina, lado: lado)
    }

    func movido2(incX: Double, incY: Double) -> Cuadrado {
        var nuevaEsquina = esquina
        nuevaEsquina.mueve(incX: incX, incY: incY)
        return Cuadrado(esquina: nuevaEsquina, lado: lado)
    }

    mutating func mueve(incX: Double, incY: Double) {
        esquina.mueve(incX: incX, incY: incY)
    }
}

// c)

// [false, true, true]


// EJERCICIO 2

// a)

/*
y: 30
x: 90
y: 30
x: 90
*/

// b)

// 46


// EJERCICIO 3

class Animal {
    var nombre: String
    var edad: Int

    init(nombre: String, edad: Int) {
        self.nombre = nombre
        self.edad = edad
    }

    func hacerSonido() {
        print("El animal hace un sonido")
    }
}

class Perro: Animal {
    var raza: String

    init(nombre: String, edad: Int, raza: String) {
        self.raza = raza
        super.init(nombre: nombre, edad: edad)
    }

    func moverCola() {
        print("\(nombre) mueve la cola")
    }

    override func hacerSonido() {
        print("Guau guau")
    }
}

let miPerro = Perro(nombre: "Toby", edad: 4, raza: "Labrador")
print("Nombre: \(miPerro.nombre)")       // Heredado
print("Edad: \(miPerro.edad)")           // Heredado
miPerro.hacerSonido()                    // Overriden
miPerro.moverCola()                      // Método propio

/*
SALIDA ESPERADA:
Nombre: Toby
Edad: 4
Guau guau
Toby mueve la cola

¿Se puede sobreescribir el valor de una propiedad almacenada? ¿Y calculada? -> Almacenada no, calculada sí
¿Se puede añadir un observador a una propiedad de la clase base en una clase derivada? -> Sí, pero solo si no se sobrescribe el valor
¿Hereda la clase derivada propiedades y métodos estáticos de la clase base? -> No
¿Cómo se puede llamar a la implementación de un método de la clase base en una sobreescritura de ese mismo método en la clase derivada? -> Usando super

*/


// EJERCICIO 4

struct Punto {
    var x = 0.0, y = 0.0
}

struct Tamaño {
    var ancho = 0.0, alto = 0.0
}

class Figura {
    var origen: Punto
    var tamaño: Tamaño
    
    init(origen: Punto, tamaño: Tamaño) {
        self.origen = origen
        self.tamaño = tamaño
    }
    
    var area: Double {
        return tamaño.ancho * tamaño.alto
    }
    
    var centro: Punto {
        get {
            return Punto(
                x: origen.x + tamaño.ancho / 2,
                y: origen.y + tamaño.alto / 2
            )
        }
        set(nuevoCentro) {
            origen = Punto(
                x: nuevoCentro.x - tamaño.ancho / 2,
                y: nuevoCentro.y - tamaño.alto / 2
            )
        }
    }
}

class Cuadrilatero: Figura {
    var p1: Punto
    var p2: Punto
    var p3: Punto
    var p4: Punto
    
    init(p1: Punto, p2: Punto, p3: Punto, p4: Punto) {
        self.p1 = p1
        self.p2 = p2
        self.p3 = p3
        self.p4 = p4
        
        let puntos = [p1, p2, p3, p4]
        let minX = puntos.map { $0.x }.min()!
        let maxX = puntos.map { $0.x }.max()!
        let minY = puntos.map { $0.y }.min()!
        let maxY = puntos.map { $0.y }.max()!
        
        let origen = Punto(x: minX, y: minY)
        let tamaño = Tamaño(ancho: maxX - minX, alto: maxY - minY)
        
        super.init(origen: origen, tamaño: tamaño)
    }
    
    override var centro: Punto {
        get {
            super.centro
        }
        set(nuevoCentro) {
            let deltaX = nuevoCentro.x - centro.x
            let deltaY = nuevoCentro.y - centro.y
            
            p1.x += deltaX
            p1.y += deltaY
            p2.x += deltaX
            p2.y += deltaY
            p3.x += deltaX
            p3.y += deltaY
            p4.x += deltaX
            p4.y += deltaY
            
            super.centro = nuevoCentro
        }
    }
    
    override var area: Double {
        return areaTriangulo(p1, p2, p3) + areaTriangulo(p1, p3, p4)
    }
    
    func areaTriangulo(_ p1: Punto, _ p2: Punto, _ p3: Punto) -> Double {
        let det = p1.x * (p2.y - p3.y) +
                  p2.x * (p3.y - p1.y) +
                  p3.x * (p1.y - p2.y)
        return abs(det) / 2
    }
}

class Circulo: Figura {
    var radio: Double
    
    init(centro: Punto, radio: Double) {
        self.radio = radio
        let origen = Punto(x: centro.x - radio, y: centro.y - radio)
        let tamaño = Tamaño(ancho: 2 * radio, alto: 2 * radio)
        super.init(origen: origen, tamaño: tamaño)
    }
    
    override var centro: Punto {
        get { super.centro }
        set(nuevoCentro) {
            super.centro = nuevoCentro
        }
    }
    
    override var area: Double {
        get {
            return Double.pi * radio * radio
        }
        set(nuevaArea) {
            radio = sqrt(nuevaArea / Double.pi)
            tamaño = Tamaño(ancho: 2 * radio, alto: 2 * radio)
            origen = Punto(x: centro.x - radio, y: centro.y - radio)
        }
    }
}

struct AlmacenFiguras {
    private(set) var figuras: [Figura] = []
    
    var numFiguras: Int {
        return figuras.count
    }
    
    var areaTotal: Double {
        return figuras.reduce(0.0) { $0 + $1.area }
    }
    
    mutating func añade(figura: Figura) {
        figuras.append(figura)
    }
    
    mutating func desplaza(incX: Double, incY: Double) {
        for figura in figuras {
            figura.centro = Punto(x: figura.centro.x + incX, y: figura.centro.y + incY)
        }
    }
}

// Crear cuadrilátero
let cuadrado = Cuadrilatero(
    p1: Punto(x: 1, y: 1),
    p2: Punto(x: 5, y: 1),
    p3: Punto(x: 5, y: 5),
    p4: Punto(x: 1, y: 5)
)

// Crear círculo
let circulo = Circulo(centro: Punto(x: 10, y: 10), radio: 3)

// Verificar propiedades
print("Área cuadrado:", cuadrado.area)
print("Centro cuadrado:", cuadrado.centro)

print("Área círculo:", circulo.area)
print("Centro círculo:", circulo.centro)

// Crear almacén y añadir figuras
var almacen = AlmacenFiguras()
almacen.añade(figura: cuadrado)
almacen.añade(figura: circulo)

print("Número de figuras:", almacen.numFiguras)
print("Área total:", almacen.areaTotal)

// Desplazar figuras
almacen.desplaza(incX: 2, incY: 3)
print("Nuevo centro cuadrado:", cuadrado.centro)
print("Nuevo centro círculo:", circulo.centro)

/* SALIDA:
Área cuadrado: 16.0
Centro cuadrado: Punto(x: 3.0, y: 3.0)
Área círculo: 28.274333882308138
Centro círculo: Punto(x: 10.0, y: 10.0)
Número de figuras: 2
Área total: 44.27433388230814
Nuevo centro cuadrado: Punto(x: 5.0, y: 6.0)
Nuevo centro círculo: Punto(x: 12.0, y: 13.0)
*/
