#include "SNFollowers.h"

/* Constructor
name: string con el nombre a añadir al objeto
initialFollowers: número de seguidores iniciales a añadir al objeto
return: nada
*/
SNFollowers::SNFollowers(string name, int initialFollowers) {
    if(!SNData::checkSN(name)) {
        throw EXCEPTION_UNKNOWN_SN;
        return;
    }
    if(initialFollowers < 0) {
        throw invalid_argument(to_string(initialFollowers));
        return;
    }
    this->name = name;
    this->money = 0;
    this->numFollowers = initialFollowers;
}

/* Función que añade al número de seguidores una cantidad indicada en el parámetro
nFollowers: seguidores a añadir (puede ser negativo si pierde seguidores)
return: nada
*/
void SNFollowers::addFollowers(int nFollowers) {
    numFollowers = max(0, numFollowers + nFollowers);
}

/* Función que recalcula el número de seguidores y monetización en base a la valoración del evento
rating: valoración del evento
return: nada
*/
void SNFollowers::addEvent(double rating) {
    // Variables locales
    double ratingRedSocial = 0;
    double monetizacionRedSocial = 0;
    double ratio = 0;
    int followersToAdd = 0;
    int lostFollowers = 0;
    
    // Comprobar que la valoración no sea negativa
    if (rating < 0) {
        throw invalid_argument(to_string(rating));
        return;
    }

    // Obtener la valoración y la monetización de la red social
    ratingRedSocial = SNData::getAvgRating(name);
    monetizacionRedSocial = SNData::getAvgMonetizing(name);
    
    // Cálculo de la ganancia/pérdida de seguidores y monetización
    ratio = rating / ratingRedSocial;
    
    // Cálculo de la ganancia/pérdida de seguidores y monetización
    if (ratio > 0.8) {
        followersToAdd = static_cast<int>(ratio * numFollowers);
        numFollowers += followersToAdd;
        money += followersToAdd * monetizacionRedSocial;
    } else {
        lostFollowers = static_cast<int>((0.9 - ratio) * numFollowers);
        numFollowers = max(0, numFollowers - lostFollowers);
    }
}

/* Función que calcula la monetización para la agencia
commission: cantidad de dinero de comisión
return: total monetización
*/
double SNFollowers::collectCommission(double commission) {
    // Variables locales
    double commissionEarned = 0;
    commissionEarned = commission * money;

    // Comprobar si el valor de commission es válido
    if (commission <= 0 || commission >= 1) {
        throw invalid_argument(to_string(commission));
        return 0;
    }

    commissionEarned = commission * money;  // Calcular la monetización obtenida
    money = 0;  // Resetear money a 0

    return commissionEarned;
}

const string SNFollowers::getName() {
    return name;
}

const int SNFollowers::getNumFollowers() {
    return numFollowers;
}

const double SNFollowers::getMoney() {
    return money;
}

ostream& operator<<(ostream &os, const SNFollowers &snf) {
    os << "[" << snf.name << "|" << snf.numFollowers << "|" << snf.money << "]";
    return os;
}