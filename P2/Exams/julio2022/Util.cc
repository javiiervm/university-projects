#include "Util.h"

string formatearTiempo(unsigned duracion) {
    float tiempo = 0.0;
    unsigned int j = 0;
    string duracionEnString, duracionFormat;

    tiempo = duracion/60;
    duracionEnString = to_string(duracion);
    j = duracionEnString.size();
    for(unsigned int i = 0; i < duracionEnString.size(); i++) {
        if(i == j + 3)
            break;
        if(duracionEnString[i] == '.') {
            j = i;
            duracionFormat.push_back(':');
        } else {
            duracionFormat.push_back(duracionEnString[i]);
        }
    }

    return duracionFormat;
}