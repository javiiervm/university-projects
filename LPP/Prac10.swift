import Foundation


// EJERCICIO 1

// a)

func maxOpt(_ x: Int?, _ y: Int?) -> Int? {
    if(x == nil && y == nil) {
        return nil
    } else if (x == nil && y != nil) {
        return y
    } else if (x != nil && y == nil) {
        return x
    } else {
        if (x! > y!) {
            return x
        }
        return y
    }
}

let res1 = maxOpt(nil, nil) 
let res2 = maxOpt(10, nil)
let res3 = maxOpt(-10, 30)
print("res1 = \(String(describing: res1))")
print("res2 = \(String(describing: res2))")
print("res3 = \(String(describing: res3))")
// Imprime:
// res1 = nil
// res2 = Optional(10)
// res3 = Optional(30)


// b1)

func parejaMayorParImpar2(numeros: [Int]) -> (Int?, Int?) {
    if numeros.count == 0 {
        return (nil, nil)
    } else {
        let numero = numeros[0]
        if numero % 2 == 0 {
            let pareja: (Int?, Int?) = parejaMayorParImpar2(numeros: Array(numeros.dropFirst()))
            return (pareja.0, maxOpt(pareja.1, numero))
        } else {
            let pareja: (Int?, Int?) = parejaMayorParImpar2(numeros: Array(numeros.dropFirst()))
            return (maxOpt(pareja.0, numero), pareja.1)
        }
    }
}

let numeros = [-10, 202, 12, 100, 204, 2]
print("\n******\n1b1) Función parejaMayorParImpar2(numeros:)\n******")
print(parejaMayorParImpar2(numeros: numeros))
// Imprime:
// parejaMayorParImpar2(numeros: [-10, 202, 12, 100, 204, 2])
// (nil, Optional(204))


// b2)

func sumaMaxParesImpares(numeros: [Int]) -> Int {
    let pareja: (Int?, Int?) = parejaMayorParImpar2(numeros: numeros)
    let sumaPares = pareja.0 ?? 0
    let sumaImpares = pareja.1 ?? 0
    return sumaPares + sumaImpares
}

print("sumaMaxParesImpares(numeros: \(numeros))")
print(sumaMaxParesImpares(numeros: numeros))
// Imprime:
// sumaMaxParesImpares(numeros: [-10, 202, 12, 100, 204, 2])
// 204


// EJERCICIO 2

// a.1) 3
// a.2) 215
// a.3) [2, 2, 2, 2, 5, 6]
// a.4) [("En", 2), ("un", 2), ("de", 2), ("La", 2), ("lugar", 5), ("Mancha", 6)]

// b.1) Esta función cuenta las veces que aparece el número dado en el Array
// b.2) Devuelve un array en el que inserta el valor dado, si no existe 
// b.3) Suma el número actual en la parte de la izquierda o derecha dependiendo de si es mayor o menor que el dado

// c.1) 
suma(palabras: [String], contienen: Character) -> Int {
    return palabras.filter { $0.contains(contienen) }.count
}

// c.2) 
sumaMenoresMayores(nums: [Int], pivote: Int) -> (menores: Int, mayores: Int) {
    let (menores, _) = nums.partition { $0 < pivote }
    let (mayores, _) = nums.partition { $0 >= pivote }
    return (menores.reduce(0, +), mayores.reduce(0, +))
}

// d) 
func bar(f: (Int) -> Int) {
    print(f(4))
}

func foo() -> (Int) -> Int {
    var x = 3
    return {
        x += $0 + 2
        return x
    }
}

var x = 5
let g = foo()
bar(f: g)   // => 9
bar(f: g)   // => 15


// EJERCICIO 3

indirect enum Arbol<A> {
    case vacio
    case nodo(A, [Arbol<A>])
}

let arbolInt: Arbol = .nodo(53, 
                            [.nodo(13, []), 
                             .nodo(32, []), 
                             .nodo(41, 
                                   [.nodo(36, []), 
                                    .nodo(39, [])
                                   ])
                            ])
let arbolString: Arbol = .nodo("Zamora", 
                               [.nodo("Buendía", 
                                      [.nodo("Albeza", []), 
                                       .nodo("Berenguer", []), 
                                       .nodo("Bolardo", [])
                                      ]), 
                                .nodo("Galván", [])
                               ])
func toArray<A>(bosque: [Arbol<A>]) -> [A] {
    if bosque.count == 0 {
        return []
    } else {
        return toArray(arbol: bosque[0]) + toArray(bosque: Array(bosque.dropFirst()))
    }
}

func toArray<A>(arbol: Arbol<A>) -> [A] {
    switch arbol {
        case .vacio:
            return []
        case .nodo(let valor, let hijos):
            return [valor] + toArray(bosque: hijos)
    }
}

func toArrayFOS<A>(arbol: Arbol<A>) -> [A] {
    switch arbol {
        case .vacio:
            return []
        case .nodo(let valor, let hijos):
            return [valor] + Array(hijos.map {toArrayFOS(arbol: $0)}.joined())
    }
}

print(toArray(arbol: arbolInt))
// Imprime: [53, 13, 32, 41, 36, 39]
print(toArrayFOS(arbol: arbolString))
// Imprime: ["Zamora", "Buendía", "Albeza", "Berenguer", "Bolardo", "Galván"]


// EJERCICIO 4

func notaFinal(_ parc1: Double, _ parc2: Double, _ parc3: Double) -> Double {
    return 0.35*parc1 + 0.3*parc2 + 0.35*parc3
}

func imprimirListadosNotas(_ alumnos: [(String, Double, Double, Double, Int)]) {
    let lista1 = alumnos.sorted { $0.0 < $1.0 }
    let lista2 = alumnos.sorted { $0.1 > $1.1 }
    let lista3 = alumnos.sorted { $0.2 < $1.2 }
    let lista4 = alumnos.sorted { $0.4 < $1.4 && $0.3 < $1.3 }
    let lista5 = alumnos.sorted { notaFinal($0.1, $0.2, $0.3) > notaFinal($1.1, $1.2, $1.3) }

    print("LISTADO ORIGINAL\nAlumno   Parcial1   Parcial2   Parcial3  Años")
    for alu in alumnos {
        alu.0.withCString {
            print(String(format:"%-10s %5.2f      %5.2f    %5.2f  %3d", $0, alu.1,alu.2,alu.3,alu.4))
        }
    }
    print("\nLISTADO ORDENADO POR NOMBRE ALUMNO\nAlumno   Parcial1   Parcial2   Parcial3  Años")
    for alu in lista1 {
        alu.0.withCString {
            print(String(format:"%-10s %5.2f      %5.2f    %5.2f  %3d", $0, alu.1,alu.2,alu.3,alu.4))
        }
    }
    print("\nLISTADO ORDENADO POR PARCIAL 1 (decreciente)\nAlumno   Parcial1   Parcial2   Parcial3  Años")
    for alu in lista2 {
        alu.0.withCString {
            print(String(format:"%-10s %5.2f      %5.2f    %5.2f  %3d", $0, alu.1,alu.2,alu.3,alu.4))
        }
    }
    print("\nLISTADO ORDENADO POR PARCIAL 2 (creciente)\nAlumno   Parcial1   Parcial2   Parcial3  Años")
    for alu in lista3 {
        alu.0.withCString {
            print(String(format:"%-10s %5.2f      %5.2f    %5.2f  %3d", $0, alu.1,alu.2,alu.3,alu.4))
        }
    }
    print("\nLISTADO ORDENADO POR MATRICULACIÓN Y PARCIAL 3 (decreciente)\nAlumno   Parcial1   Parcial2   Parcial3  Años")
    for alu in lista4 {
        alu.0.withCString {
            print(String(format:"%-10s %5.2f      %5.2f    %5.2f  %3d", $0, alu.1,alu.2,alu.3,alu.4))
        }
    }
    print("\nLISTADO ORDENADO POR NOTA FINAL (decreciente)\nAlumno   Parcial1   Parcial2   Parcial3  Años")
    for alu in lista5 {
        alu.0.withCString {
            print(String(format:"%-10s %5.2f      %5.2f    %5.2f  %3d", $0, alu.1,alu.2,alu.3,alu.4))
        }
    }
    print("\n\n")
}

let listaAlumnos = [("Pepe", 8.45, 3.75, 6.05, 1), 
                    ("Maria", 9.1, 7.5, 8.18, 1), 
                    ("Jose", 8.0, 6.65, 7.96, 1),
                    ("Carmen", 6.25, 1.2, 5.41, 2), 
                    ("Felipe", 5.65, 0.25, 3.16, 3), 
                    ("Carla", 6.25, 1.25, 4.23, 2), 
                    ("Luis", 6.75, 0.25, 4.63, 2), 
                    ("Loli", 3.0, 1.25, 2.19, 3)]
imprimirListadosNotas(listaAlumnos)


// EJERCICIO 5

print(listaAlumnos.filter{ alu in alu.1 >= 5 && alu.2 < 5 }.count)
// Resultado: 5

print(listaAlumnos.filter{ notaFinal($0.1, $0.2, $0.3) >= 5 }.map{ $0.0 })
// Resultado: ["Pepe", "Maria", "Jose"]

var tupla = listaAlumnos.reduce((0.0, 0.0, 0.0), { ($0.0 + $1.1, $0.1 + $1.2, $0.2 + $1.3) })
tupla = (tupla.0 / Double(listaAlumnos.count), tupla.1 / Double(listaAlumnos.count), tupla.2 / Double(listaAlumnos.count))
print(tupla)
// Resultado: (6.6812499999999995, 2.7624999999999997, 5.22625)


// EJERCICIO 6

func construye(operador: Character) -> (Int, Int) -> Int {
    func operacion(num1: Int, num2: Int) -> Int {
        switch operador {
            case "+":
                return num1 + num2
            case "-":
                return num1 - num2
            case "*":
                return num1 * num2
            case "/":
                return num1 / num2
            default:
                return 0
        }
    }
    return operacion
}

var f = construye(operador: "+")
print(f(2,3))
// Imprime 5
f = construye(operador: "-")
print(f(2,3))
// Imprime -1


