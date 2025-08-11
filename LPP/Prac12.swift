import Foundation


// EJERCICIO 1

protocol A {
    var a: String {get}
    func foo(a: String) -> String?
}
protocol B {
    mutating func bar()
}
struct MiStruct: A, B {
    var a: String
    func foo(a: String) -> String? {
        return a.isEmpty ? nil : "Hello, \(a)"
    }
    mutating func bar() {
        self.a = "Updated"
    }
}

protocol A2 {
    var a: String {get set}
    func foo(a: Int, b: Int) -> Int?
}
protocol B2 {
    mutating func bar()
}
struct MiStruct2: A2, B2 {
    var a = "Hola"
    func foo(a: Int, b: Int) -> Int? {
        if a == nil || b == nil {
            return nil
        }    
        let res = a > 10 ? a: b
        return res
    }
    mutating func bar() {
        self.a = "Updated"
    }
}

struct Equipo: Equatable, Comparable {
    let puntos: Int
    let nombre: String
    static func < (lhs: Equipo, rhs: Equipo) -> Bool {
        if lhs.puntos != rhs.puntos {
            return lhs.puntos < rhs.puntos
        } else {
            return lhs.nombre < rhs.nombre
        }
    }
}
let equipo1 = Equipo(puntos: 10, nombre: "Hércules")
let equipo2 = Equipo(puntos: 8, nombre: "Villareal")
print(equipo1 == equipo2) // imprime false
print(equipo1 > equipo2) // imprime true

let equipo3 = Equipo(puntos: 20, nombre: "LPP")
let equipos = [equipo1, equipo2, equipo3]
let ordenados = equipos.sorted()
for equipo in ordenados {
    print("\(equipo.nombre): \(equipo.puntos)")
}


// EJERCICIO 2

struct Cuadrado {
    var lado: Double
    var area: Double {
        return lado*lado
    }
}
var cuadrado = Cuadrado(lado: 4.0)
print(cuadrado.area) // Imprime: 16.0
cuadrado.lado = 10.0
print(cuadrado.area) // Imprime: 100.0

protocol Persona {
    var nombre: String {get}
    func encantada() -> Persona 
    func refrescada() -> Persona 
}
enum Pocion {
    case magica, refrescante, venenosa
    func esBebida(por persona: Persona) -> Persona? {
        switch self {
            case .magica:
                return persona.encantada()
            case .refrescante:
                return persona.refrescada()
            default:
                return nil
        }
    }
}

struct Circulo {
    var radio: Double
    static func + (one: Circulo, other: Circulo) -> Circulo {
        var suma = one.radio + other.radio
        return Circulo(radio: suma)
    }
}
let c1 = Circulo(radio: 5.0)
let c2 = Circulo(radio: 10.0)
let c3 = c1 + c2
print("El radio de la suma es: \(c3.radio)")
// Imprime: El radio de la suma es: 15.0


// EJERCICIO 3

protocol P1 {
    var p: Int { get }
}
class A11: P1 {
    var p = 0
    var a1 = 0
}
class A21: P1 {
    var p = 1
    var a2 = 0
}
var array: [P1] = [A11(), A21()]
for i in array {
    if let a1 = i as? A11 {
        print("p: \(a1.p), a1: \(a1.a1)")
    } else if let a2 = i as? A21 {
        print("p: \(a2.p), a2: \(a2.a2)")
    }
}
// debe imprimir:
// debe imprimir:
// p: 0, a1: 0
// p: 1, a2: 0

protocol TieneVelocidad {
    func velocidadActual () -> Double
}
class Vehiculo: TieneVelocidad {
    var velocidad = 0.0
    func velocidadActual() -> Double {
        return velocidad
    }
}
class Tren: TieneVelocidad {
    static let velocidadEnMarcha = 300.0
    var pasajeros = 0
    var enMarcha = false
    func velocidadActual() -> Double {
        if enMarcha {
            return Tren.velocidadEnMarcha
        } else {
            return 0.0
        }
    }
}
var vehiculo1 = Vehiculo()
var tren1 = Tren()
tren1.enMarcha = true
let transportes: [TieneVelocidad] = [vehiculo1, tren1]
for i in transportes {
    print(i.velocidadActual())
}
// 0.0
// 300.0


// EJERCICIO 4

struct Timer {
    var segundos: Int
    static var pasosTotales: Int = 0
    init(segundos: Int) {
        self.segundos = segundos
    }
    mutating func paso() {
        segundos -= 1
        Timer.pasosTotales += 1
    }
    static func + (left: Timer, right: Timer) -> Timer {
        return Timer(segundos: left.segundos + right.segundos)
    }
}
var t1 = Timer(segundos: 10)
var t2 = Timer(segundos: 5)
for _ in 0...4 {
    t1.paso()
}
for _ in 0...2 {
    t2.paso()
}
var t3 = t1 + t2
t3.paso()
print("Segundos del temporizador 1: \(t1.segundos)")
print("Segundos del temporizador 2: \(t2.segundos)")
print("Segundos del temporizador 3: \(t3.segundos)")
print("Pasos totales: \(Timer.pasosTotales)")
// Imprime:
// Segundos del temporizador 1: 5
// Segundos del temporizador 2: 2
// Segundos del temporizador 3: 6
// Pasos totales: 9


// EJERCICIO 5

struct Punto2 {
    var x = 0.0, y = 0.0
}

struct Tamaño2 {
    var ancho = 0.0, alto = 0.0
}

struct Circulo2 {
    var centro = Punto2()
    var radio = 0.0

    var area: Double {
        get {
            return Double.pi * radio * radio
        }
        set(nuevoArea) {
            radio = sqrt(nuevoArea/Double.pi)
        }
    }
}

struct Rectangulo2 {
    var origen = Punto2()
    var tamaño = Tamaño2()

    var centro: Punto2 {
        get {
            let centroX = origen.x + (self.tamaño.ancho / 2)
            let centroY = origen.y + (self.tamaño.alto / 2)
            return Punto2(x: centroX, y: centroY)
        }
        set(centroNuevo) {
            origen.x = centroNuevo.x - (self.tamaño.ancho / 2)
            origen.y = centroNuevo.y - (self.tamaño.alto / 2)
        }
    }

    var area: Double {
        return self.tamaño.ancho * self.tamaño.alto
    }
}

// -----------------------------
// Pruebas de las estructuras
// -----------------------------

// Circulo
var c = Circulo2(centro: Punto2(x: 0, y: 0), radio: 2)
print("Área inicial del círculo: \(c.area)") // Debería ser ≈ 12.57

// Cambiamos el área del círculo
c.area = 50
print("Nuevo radio tras asignar área = 50: \(c.radio)") // Debería ser ≈ 3.99
print("Nueva área calculada: \(c.area)") // Debería ser ≈ 50

// Rectángulo
var r = Rectangulo2(origen: Punto2(x: 0, y: 0), tamaño: Tamaño2(ancho: 10, alto: 4))
print("Centro inicial del rectángulo: (\(r.centro.x), \(r.centro.y))") // Debería ser (5, 2)
print("Área del rectángulo: \(r.area)") // Debería ser 40

// Cambiamos el centro del rectángulo
r.centro = Punto2(x: 20, y: 10)
print("Nuevo origen tras mover el centro: (\(r.origen.x), \(r.origen.y))") // Debería ser (15, 8)
print("Nuevo centro calculado: (\(r.centro.x), \(r.centro.y))") // Debería ser (20, 10)

protocol Figura2 {
    var centro: Punto2 { get set }
    var area: Double { get }
    var tamaño: Tamaño2 { get }
    func descripcion() -> String
}

extension Circulo2: Figura2 {
    var tamaño: Tamaño2 {
        return Tamaño2(ancho: radio * 2, alto: radio * 2)
    }

    func descripcion() -> String {
        return "Círculo - Centro: (\(centro.x), \(centro.y)), Área: \(area)"
    }
}

extension Rectangulo2: Figura2 {
    func descripcion() -> String {
        return "Rectángulo - Centro: (\(centro.x), \(centro.y)), Área: \(area)"
    }
}

// Instancias
let c111 = Circulo2(centro: Punto2(x: 1, y: 1), radio: 2)
let r111 = Rectangulo2(origen: Punto2(x: 0, y: 0), tamaño: Tamaño2(ancho: 10, alto: 5))
var c222 = Circulo2(centro: Punto2(x: -5, y: 3), radio: 1.5)
c222.area = 20

// Array de figuras
let figurass: [Figura2] = [c111, r111, c222]

// Recorremos y mostramos descripciones
for figuraa in figurass {
    print(figuraa.descripcion())
}

// Círculo - Centro: (1.0, 1.0), Área: 12.566370614359172
// Rectángulo - Centro: (5.0, 2.5), Área: 50.0
// Círculo - Centro: (-5.0, 3.0), Área: 20.0

struct AlmacenFiguras {
    var figuras: [Figura2] = [] // valor por defecto vacío

    mutating func añade(figura: Figura2) {
        figuras.append(figura)
    }

    var numFiguras: Int {
        return figuras.count
    }

    var areaTotal: Double {
        return figuras.reduce(0.0) { $0 + $1.area }
    }

    func cuentaTipos() -> (Int, Int) {
        var numRectangulos = 0
        var numCirculos = 0

        for figura in figuras {
            if figura is Rectangulo2 {
                numRectangulos += 1
                print("** Un rectángulo con tamaño \(figura.tamaño) y descripción:")
                print("Centro: \(figura.centro) y área: \(figura.area)")
            } else if figura is Circulo2 {
                numCirculos += 1
                print("** Un círculo con descripción:")
                print("Centro: \(figura.centro) y área: \(figura.area)")
            } else {
                print("Tipo desconocido - \(figura.descripcion())")
            }
        }

        return (numRectangulos, numCirculos)
    }
}

// --- Ejemplo de uso corregido ---

var almacen = AlmacenFiguras()

let rect = Rectangulo2(origen: Punto2(x: 3, y: 4), tamaño: Tamaño2(ancho: 10.0, alto: 5.0))
let circ = Circulo2(centro: Punto2(x: 5.0, y: 0.0), radio: 10.0)

almacen.añade(figura: rect)
almacen.añade(figura: circ)

print("Número de figuras: \(almacen.numFiguras)")
print("Área total: \(almacen.areaTotal)")

let (numRects, numCircs) = almacen.cuentaTipos()
print("Rectángulos: \(numRects), Círculos: \(numCircs)")

// SALIDA ESPERADA
/*
Número de figuras: 2
Área total: 364.1592653589793
** Un rectángulo con tamaño Tamaño(ancho: 10.0, alto: 5.0) y descripción:
Centro: Punto(x: 8.0, y: 6.5) y área: 50.0
** Un círculo con descripción:
Centro: Punto(x: 5.0, y: 0.0) y área: 314.1592653589793
Rectángulos: 1, Círculos: 1
*/


