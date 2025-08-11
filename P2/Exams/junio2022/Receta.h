#include "Ingrediente.cc"

#ifndef RECETA_H
#define RECETA_H

class Receta {
    friend ostream& operator<<(ostream &os, const Receta &rec);
    private:
        unsigned nextId = 1;
        unsigned id;
        string descripcion;
        vector<Ingrediente> ingredientes;
    public:
        Receta(string desc = "Nueva receta");
        bool addIngrediente(Producto* prod, float cant);
        unsigned getNextId();
};

#endif