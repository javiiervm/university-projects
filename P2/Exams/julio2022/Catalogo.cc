#include "Catalogo.h"

Catalogo::Catalogo(string nombre = "Xplotify") {
    this->nombre = nombre;
}

void Catalogo::addCancion(string nombre, unsigned duracion) {
    try {
        canciones.push_back(Cancion(nombre, duracion));
    } catch(const std::exception& e) {
        cout << "La canción no se ha podido crear" << endl;
    }
}

vector<Cancion> Catalogo::filter(unsigned duracion) const {
    vector<Cancion> cancionesEncontradas;
    for(unsigned int i = 0; i < canciones.size(); i++) {
        if(canciones[i].getDuration() <= duracion)
            cancionesEncontradas.push_back(canciones[i]);
    }
    return cancionesEncontradas;
}

ostream& operator<<(ostream &os, const Catalogo &cat) {
    unsigned duracion = 0;

    os << cat.nombre << endl;
    for(unsigned int i = 0; i < cat.canciones.size(); i++) {
        os << cat.canciones[i];
        duracion = duracion + cat.canciones[i].getDuration();
    }
    os << "Duración " << formatearTiempo(duracion) << endl;
    return os;
}