#include "Agency.h"

/* Constructor que crea un nuevo objeto de clase Agency
name: nombre de la Agency
initialMoney: dinero inicial de la Agency
return: nada
*/
Agency::Agency(string name, double initialMoney) {
    this->name = name;
    this->money = initialMoney;
}

/*
*/
Influencer *Agency::searchInfluencer(string infName) {
    // Variables locales
    Influencer* pointerLocation;

    for(unsigned int i = 0; i < influencers.size(); i++) {
        if(influencers[i].getName() == infName) {
            pointerLocation = &influencers[i];
            return pointerLocation;
        }
    }

    throw EXCEPTION_INFL_NOT_FOUND;
}

/* Añade un influencer nuevo al vector
infName: nombre del influencer
commission: comisión del influencer
return: nada
*/
void Agency::addInfluencer(string infName, double commission) {
    try {
        searchInfluencer(infName);    // Llamar a la función searchInfluencer directamente
        Util::error(ERR_DUPLICATED);  // Si no ha saltado excepción, significa que el influencer ya existe
    } catch(Exception utilExc) {
        if(utilExc == EXCEPTION_INFL_NOT_FOUND) {   // Si ha saltado esta excepción, significa que el influencer no existe
            try {
                // Comprobar que la comisión sea válida
                Influencer tempInfluencer(infName);
                tempInfluencer.setCommission(commission);

                // Si no hay errores, añadir al nuevo influencer al vector
                influencers.push_back(tempInfluencer);
            } catch(Exception utilExc) {
                if(utilExc == EXCEPTION_WRONG_COMMISSION) {
                    Util::error(ERR_WRONG_COMMISSION);
                } else { 
                    Util::debug(utilExc);
                }
            }
        } else { 
            Util::debug(utilExc);
        }
    }
}

void Agency::addFollowers(string infName, string snName, int nFollowers) {
    try {
        searchInfluencer(infName)->addFollowers(snName, nFollowers);
    } catch (Exception utilExc) {
        if (utilExc == EXCEPTION_INFL_NOT_FOUND) {
            Util::error(ERR_NOT_FOUND);
        } else { 
            Util::debug(utilExc);
        }
    }
}

void Agency::newEvent(vector<string> infNames, int nsns, string snNames[], double evRats[]) {
    for (unsigned int i = 0; i < infNames.size(); i++) {
        try {
            Influencer* influencer = searchInfluencer(infNames[i]);
            if (influencer)
                influencer->addEvent(nsns, snNames, evRats);
        } catch(Exception utilExc) {
            if(utilExc == EXCEPTION_INFL_NOT_FOUND) {
                // Util::error(ERR_NOT_FOUND);
            } else {
                Util::debug(utilExc);
            }
        }
    }
}

void Agency::deleteInfluencer(string infName) {
    // Variables locales
    double commission = 0.0;
    
    try {
        Influencer newInfluencer = *searchInfluencer(infName);  // Comprobar si el influencer existe, si no existe saltará una excepción

        commission = newInfluencer.collectCommission();     // Obtener la comisión del influencer
        money = money + commission;                         // Sumar la comisión al dinero de la agencia

        for(unsigned int i = 0; i < influencers.size(); i++) {
            if(influencers[i].getName() == infName)
                influencers.erase(influencers.begin() + i);    // Eliminar al influencer
        }
    } catch(Exception utilExc) {
        if(utilExc == EXCEPTION_INFL_NOT_FOUND)
            Util::error(ERR_NOT_FOUND);
        else 
            Util::debug(utilExc);
    }
}

double Agency::collectCommissions() {
    // Variables locales
    double totalCollected = 0.0;

    // Recolectar las comisiones de los influencers
    for(unsigned int i = 0; i < influencers.size(); i++) {
        totalCollected += influencers[i].collectCommission();
    }

    money += totalCollected;
    return totalCollected;
}

const string Agency::getName() {
    return name;
}

const double Agency::getMoney() {
    return money;
}

ostream& operator<<(ostream &os, const Agency &ag) {
    os << "Agency: " << ag.name << " [" << ag.money << "]" << endl;
    for(unsigned int i = 0; i < ag.influencers.size(); i++) {
        os << ag.influencers[i];
    }
    os << endl;
    return os;
}
