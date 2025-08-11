#include "Receta.h"

Receta::Receta(string desc) {
    this->descripcion = desc;
    this->id = nextId;
}

bool Receta::addIngrediente(Producto* prod, float cant) {
    // Variables locales
    bool existingIngredient = false;

    try {
        for(unsigned int i = 0; i < ingredientes.size(); i++) {
            if(ingredientes[i].getProducto() == prod) {
                ingredientes[i].setCantidad(cant);
                existingIngredient = true;
            }
        }
        if(!existingIngredient)
            ingredientes.push_back(Ingrediente(prod, cant));
    } catch(const std::exception& e) {
        return false;
    }
    return true;
}

unsigned Receta::getNextId() {
    int idReturn = nextId;
    nextId = nextId + 1;
    return idReturn;
}

ostream& operator<<(ostream &os, const Receta &rec) {
    // Variables locales
    float kcalTotales = 0.0;

    os << "Receta " << rec.descripcion << endl;
    for(unsigned int i = 0; i < rec.ingredientes.size(); i++) {
        os << i + 1 << ". " << rec.ingredientes[i];
        kcalTotales = kcalTotales + rec.ingredientes[i].getCalorias();
    }
    os << "Total kilocalorías: " << (int)kcalTotales << endl;

    return os;
}