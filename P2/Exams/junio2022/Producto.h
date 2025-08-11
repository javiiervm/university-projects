#include <iostream>
#include <vector>

using namespace std;

#ifndef PRODUCTO_H
#define PRODUCTO_H

class Producto {
    private:
        string nombre;
        float cpkg;
    public:
        Producto(string nombre, float cpkg);
        const string getNombre();
        const float getCpkg();
};

#endif