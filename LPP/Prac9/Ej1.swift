import Foundation


let miConstante: Float = 4
print(miConstante)


/*
let etiqueta = "El ancho es "
let ancho = 94
let anchoEtiqueta = etiqueta + ancho // ERROR: Binary operator '+' cannot be applied to operands of type 'String' and 'Int'
*/


print("Resultado = \(2.5+2.5)")
func saludo(nombre: String) {
    print("Hola \(nombre)!")
}
saludo(nombre: "Swift")


var cadenaOpcional: String? = "Hola"
print(cadenaOpcional == nil)

//var nombreOpcional: String? = "John Appleseed"
var nombreOpcional: String? = nil   // Output = "Hola!"
var saludoo = "Hola!"
if let nombre = nombreOpcional {
    saludoo = "Hola, \(nombre)"
} else {
    saludoo = "Saludo secreto :)"
}
print(saludoo)


/*let verdura = "pimiento rojo"
switch verdura {
    case "zanahoria":
        print("Buena para la vista.")
    case "lechuga", "tomates":
        print("Podrías hacer una buena ensalada.")
    /*default:
        print("Siempre puedes hacer una buena sopa.")*/     // ERROR: Switch must be exhaustive
}*/


let numerosInteresantes = [
    "Primos": [2, 3, 5, 7, 11, 13],
    "Fibonacci": [1, 1, 2, 3, 5, 8],
    "Cuadrados": [1, 4, 9, 16, 25],
]
var mayor = 0
var clase_mayor = type(of: mayor)
for (clase, numeros) in numerosInteresantes {
    for num in numeros {
        if num > mayor {
            mayor = num
            clase_mayor = type(of: mayor)
        }
    }
}
print(mayor)
print(clase_mayor)


func saluda(nombre: String, comida: String) -> String {
    return "Hola \(nombre), mi comida favorita es es \(comida)."
}
print(saluda(nombre: "Bob", comida: "macarrones"))


func media_args(lista: [Int]) -> Float {
    var contador = 0
    var acumulador = 0
    for numero in lista {
        acumulador += numero
        contador += 1
    }
    return Float(acumulador)/Float(contador)
}
print(media_args(lista: [1,4,5]))


func cumpleCondicion(lista: [Int], condicion: (Int) -> Bool) -> Bool {
    for item in lista {
        if condicion(item) {
            return true
        }
    }
    return false
}
func menorQueDiez(numero: Int) -> Bool {
    return numero < 10
}
var numeros = [20, 19, 7, 12]
print(cumpleCondicion(lista: numeros, condicion: menorQueDiez))

numeros.map({
    (numero: Int) -> Int in
    let resultado = 3 * numero
    return resultado
})

