#include "Util.cc"

#ifndef CANCION_H
#define CANCION_H

class Cancion {
    friend ostream& operator<<(ostream &os, const Cancion &can);
    private:
        const unsigned MAX_DURACION = 600;
        unsigned nextId = 1;
        unsigned id;
        string nombre;
        unsigned duracion;
    public:
        Cancion(string nombre, unsigned duracion);
        string getNombre() const;
        unsigned getDuration() const;
        unsigned getNextId();
};

#endif