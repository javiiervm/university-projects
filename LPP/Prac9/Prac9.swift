import Foundation

func prefijos(prefijo: String, palabras: [String]) -> [Bool] {
    if palabras.count == 0 {
        return []
    } else {
        var resultado: [Bool] = []
        let palabra = palabras.first ?? ""
        resultado.append(palabra.hasPrefix(prefijo))
        let nuevaLista: [String] = Array(palabras.dropFirst())
        return resultado + prefijos(prefijo: prefijo, palabras: nuevaLista)
    }
}

let array = ["anterior", "antígona", "antena"]
let prefijo = "ante"
print("\n******\n2a) Función prefijos(prefijo:palabras:)\n******")
print(prefijos(prefijo: prefijo, palabras: array))
// Imprime: [true, false, true]

func parejaMayorParImpar(numeros: [Int]) -> (Int, Int) {
    if numeros.count == 0 {
        return (0, 0)
    } else {
        let numero = numeros[0]
        if numero % 2 == 0 {
            let pareja: (Int, Int) = parejaMayorParImpar(numeros: Array(numeros.dropFirst()))
            if numero > pareja.1 {
                return (pareja.0, numero)
            } else {
                return pareja
            }
        } else {
            let pareja: (Int, Int) = parejaMayorParImpar(numeros: Array(numeros.dropFirst()))
            if numero > pareja.0 {
                return (numero, pareja.1)
            } else {
                return pareja
            }
        }
    }
}

let numeros = [10, 201, 12, 103, 204, 2]
print("\n******\n2b) Función parejaMayorParImpar(numeros:)\n******")
print(parejaMayorParImpar(numeros: numeros))
// Imprime: (201, 204)

func compruebaParejas(_ listaEnteros: [Int], funcion: (Int) -> Int) -> [(Int, Int)] {
    if listaEnteros.count == 0 || listaEnteros.count == 1 {
        return []        
    } else {
        let primero = listaEnteros[0]
        let segundo = listaEnteros[1]
        if funcion(primero) == segundo {
            return [(primero, segundo)] + compruebaParejas(Array(listaEnteros.dropFirst()), funcion: funcion)
        } else {
            return compruebaParejas(Array(listaEnteros.dropFirst()), funcion: funcion)
        }
    }
}

func cuadrado(x: Int) -> Int {
   return x * x
}
print(compruebaParejas([2, 4, 16, 5, 10, 100, 105], funcion: cuadrado))
// Imprime [(2,4), (4,16), (10,100)]


func coinciden(parejas: [(Int, Int)], funcion: (Int)->Int) -> [Bool] {
    if parejas.count == 0 {
        return []
    } else {
        let pareja = parejas[0]
        if pareja.1 == funcion(pareja.0) {
            return [true] + coinciden(parejas: Array(parejas.dropFirst()), funcion: funcion)
        } else {
            return [false] + coinciden(parejas: Array(parejas.dropFirst()), funcion: funcion)
        }
    }
}

let array2 = [(2,4), (4,14), (4,16), (5,25), (10,100)]
print(coinciden(parejas: array2, funcion: cuadrado))
// Imprime: [true, false, true, true, true]


enum Movimiento {
    case deposito(Double)
    case cargoRecibo(String, Double)
    case cajero(Double)
}

func aplica(movimientos: [Movimiento]) -> (Double, [String]) {
    var dinero: Double = 0
    var lista: [String] = []
    for movimiento in movimientos {
        switch movimiento {
            case .deposito(let cantidad):
                dinero += cantidad
            case .cajero(let cantidad):
                dinero -= cantidad
            case .cargoRecibo(let motivo, let cantidad):
                dinero -= cantidad
                lista += [motivo]
        }
    }
    return (dinero, lista)
}

let movimientos: [Movimiento] = [.deposito(830.0), .cargoRecibo("Gimnasio", 45.0), .deposito(400.0), .cajero(100.0), .cargoRecibo("Fnac", 38.70)]
print(aplica(movimientos: movimientos))
//Imprime (1046.3, ["Gimnasio", "Fnac"])


indirect enum ArbolBinario {
    case vacio
    case nodo(Int, ArbolBinario, ArbolBinario)
}

func suma(arbolb: ArbolBinario) -> Int {
    switch arbolb {
        case .vacio:
            return 0
        case .nodo(let valor, let hijoizq, let hijoder):
            return valor + suma(arbolb: hijoizq) + suma(arbolb: hijoder)
    }
}

let arbol: ArbolBinario = .nodo(8, .nodo(2, .vacio, .vacio), .nodo(12, .vacio, .vacio))
print(suma(arbolb: arbol))
// Imprime: 22


indirect enum Arbol {
    case vacio
    case nodo(Int, [Arbol])
}

func suma(bosque: [Arbol], cumplen: (Int)->Bool) -> Int {
    if bosque.count == 0 {
        return 0
    } else {
        return suma(arbol: bosque[0], cumplen: cumplen) + suma(bosque: Array(bosque.dropFirst()), cumplen: cumplen)
    }
}

func suma(arbol: Arbol, cumplen: (Int)->Bool) -> Int {
    switch arbol {
        case .vacio:
            return 0
        case .nodo(let valor, let hijos):
            if cumplen(valor) {
                return valor + suma(bosque: hijos, cumplen: cumplen)
            } else {
                return suma(bosque: hijos, cumplen: cumplen)
            }
    }
}

/*
Definimos el árbol

    10
   / | \
  3  5  8
  |
  1

*/

let arbol1 = Arbol.nodo(1, [])
let arbol3 = Arbol.nodo(3, [arbol1])
let arbol5 = Arbol.nodo(5, [])
let arbol8 = Arbol.nodo(8, [])
let arbol10 = Arbol.nodo(10, [arbol3, arbol5, arbol8])

func esPar(x: Int) -> Bool {
    return x % 2 == 0
}

print("La suma del árbol es: \(suma(arbol: arbol10, cumplen: esPar))")
// Imprime: La suma del árbol genérico es: 18



