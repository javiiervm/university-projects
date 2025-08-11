#include "Influencer.h"

Influencer::Influencer(string name) {
    this->name = name;
    this->commission = 0.1;
}

/* Función que comprueba el valor de la comisión y si es correcto lo modifica
commission: nuevo valor de la comisión
return: nada
*/
void Influencer::setCommission(double commission) {
    if (commission <= 0 || commission >= 0.8) {
        throw EXCEPTION_WRONG_COMMISSION;
        return;
    }
    this->commission = commission;
}

void Influencer::addFollowers(string snName, int nFollowers) {
    if(SNData::checkSN(snName)) { // En caso de que sí exista una red social con ese nombre
        bool found = false; // Bandera para indicar si se encontró la red social
        for(unsigned int i = 0; i < followers.size(); i++) { // Recorrer el vector followers
            if(followers[i].getName() == snName) {
                followers[i].addFollowers(nFollowers); // Si encuentra una coincidencia, añadir followers a esa red social
                found = true; // Se encontró la red social
                break; // Detenemos la ejecución del bucle
            }
        }
        if (!found) { // Si no se encontró, crear una nueva entrada
            followers.push_back(SNFollowers(snName, nFollowers));
        }
    } else { // En caso de que no exista una red social con ese nombre, se intenta crear
        try {
            followers.push_back(SNFollowers(snName, nFollowers)); // Crear red social con seguidores
        } catch(Exception utilExc) {
            if(utilExc == EXCEPTION_UNKNOWN_SN)
                Util::error(ERR_UNKNOWN_SN);
            else 
                Util::debug(utilExc);
        }
    }
}

void Influencer::addEvent(int nsns, string sn[], double rat[]) {
    for (int i = 0; i < nsns; i++) {
        for (unsigned int j = 0; j < followers.size(); j++) {
            if (followers[j].getName() == sn[i]) {
                followers[j].addEvent(rat[i]);
            }
        }
    }
}

double Influencer::collectCommission() {
    // Variables locales
    double totalCommission = 0;

    // Iterar sobre el vector de seguidores y sumar la monetización de cada uno
    for(unsigned int i = 0; i < followers.size(); i++) {
        totalCommission += followers[i].collectCommission(commission);
    }

    return totalCommission;
}

const string Influencer::getName() {
    return name;
}

const vector<SNFollowers>& Influencer::getFollowers() {
    return followers;
}

double Influencer::getCommission() const {
    return commission;
}

ostream& operator<<(ostream &os, const Influencer &inf) {
    os << "Influencer: " << inf.name << " (" << inf.commission << ")" << endl;
    for(unsigned int i = 0; i < inf.followers.size(); i++) {
        os << inf.followers[i];
    }
    os << endl;
    return os;
}