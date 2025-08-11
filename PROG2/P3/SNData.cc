#include "SNData.h"

vector<SocialNetworkData> SNData::sns = {};     // Inicializamos el vector sns

/* Función que añade una nueva red social al vector sns después de comprobar que los datos son correctos
name: nombre de la red social a buscar
avgR: valoración media de la red social
avgM: monetización media de la red social
return: nada
*/
void SNData::newSocialNetwork(string name, double avgR, double avgM) {
    // Variables locales
    SocialNetworkData newNetwork;

    // Comprobar que el nombre de la red social no esté repetido
    for(unsigned int i = 0; i < sns.size(); i++) {
        if(sns[i].name == name) {
            throw invalid_argument(name);
            return;
        }
    }

    // Comprobar que los valores de avgR y avgM están entre 0 y 1
    if(avgR <= 0 || avgR >= 1) {
        throw invalid_argument(to_string(avgR));
        return;
    }
    if(avgM <= 0 || avgM >= 1) {
        throw invalid_argument(to_string(avgM));
        return;
    }

    // Añadir red social al vector sns
    newNetwork.name = name;
    newNetwork.averageRating = avgR;
    newNetwork.averageMonetizing = avgM;
    sns.push_back(newNetwork);
}

/* Función que busca en el vector sns una red social llamada igual que el string name
name: nombre de la red social a buscar
return: true si encuentra una coincidencia, false si no la encuentra
*/
bool SNData::checkSN(string name) {
    for(unsigned int i = 0; i < sns.size(); i++) {
        if(sns[i].name == name)
            return true;
    }
    return false;
}

/* Función que devuelve la valoración media de la red social llamada como el string name
name: nombre de la red social a buscar
return: valoración media si encuentra la red social, 0.0 si no la encuentra
*/
double SNData::getAvgRating(string name) {
    for(unsigned int i = 0; i < sns.size(); i++) {
        if(sns[i].name == name)
            return sns[i].averageRating;
    }
    return 0.0;
}

/* Función que devuelve la monetización media de la red social llamada como el string name
name: nombre de la red social a buscar
return: monetización media si encuentra la red social, 0.0 si no la encuentra
*/
double SNData::getAvgMonetizing(string name) {
    for(unsigned int i = 0; i < sns.size(); i++) {
        if(sns[i].name == name)
            return sns[i].averageMonetizing;
    }
    return 0.0;
}