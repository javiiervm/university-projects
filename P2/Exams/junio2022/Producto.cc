#include "Producto.h"

Producto::Producto(string nombre, float cpkg) {
    this->nombre = nombre;
    this->cpkg = cpkg;
}

const string Producto::getNombre() {
    return nombre;
}

const float Producto::getCpkg() {
    return cpkg;
}
