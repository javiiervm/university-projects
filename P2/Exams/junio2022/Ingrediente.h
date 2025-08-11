#include "Producto.cc"

#ifndef INGREDIENTE_H
#define INGREDIENTE_H

class Ingrediente {
    friend ostream& operator<<(ostream &os, const Ingrediente &ing);
    private:
        float cantidad;
        Producto* producto;
    public:
        Ingrediente(Producto* prod, float cant);
        Producto* getProducto() const;
        float getCantidad() const;
        bool setCantidad(float cantidad);
        float getCalorias() const;
};

#endif