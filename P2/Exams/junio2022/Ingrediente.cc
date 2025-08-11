#include "Ingrediente.h"

Ingrediente::Ingrediente(Producto* prod, float cant) {
    if(prod==NULL)
        throw invalid_argument("NULL pointer");
    if(cant <= 0)
        throw invalid_argument(to_string(cant));
    this->producto = prod;
    this->cantidad = cant;
}

Producto* Ingrediente::getProducto() const {
    return producto;
}

float Ingrediente::getCantidad() const {
    return cantidad;
}

bool Ingrediente::setCantidad(float cantidad) {
    if(cantidad > 0) {
        this->cantidad = cantidad;
        return true;
    }
    return false;
}

float Ingrediente::getCalorias() const {
    return cantidad*producto->getCpkg();
}

ostream& operator<<(ostream &os, const Ingrediente &ing) {
    os << ing.producto << " (" << ing.cantidad << "kg)" << endl;
    return os;
}
