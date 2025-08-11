#include "Cancion.h"

Cancion::Cancion(string nombre, unsigned duracion) {
    if(nombre == "" || duracion > MAX_DURACION)
        throw invalid_argument("Parámetros no válidos");

    this->nombre = nombre;
    this->duracion = duracion;
    this->id = getNextId();
}

string Cancion::getNombre() const {
    return nombre;
}

unsigned Cancion::getDuration() const {
    return duracion;
}

unsigned Cancion::getNextId() {
    unsigned newId = nextId;
    nextId = nextId + 1;
    return newId;
}

ostream& operator<<(ostream &os, const Cancion &can) {
    cout << can.id << ". " << can.nombre << " (" << formatearTiempo(can.duracion) << ")" << endl;
    return os;
}