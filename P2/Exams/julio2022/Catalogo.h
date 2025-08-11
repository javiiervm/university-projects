#include "Cancion.cc"

#ifndef CATALOGO_H
#define CATALOGO_H

class Catalogo {
    friend ostream& operator<<(ostream &os, const Catalogo &cat);
    private:
        string nombre;
        vector<Cancion> canciones;
    public:
        Catalogo(string nombre);
        void addCancion(string nombre, unsigned duracion);
        vector<Cancion> filter(unsigned duracion) const;
};

#endif