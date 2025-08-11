#include "Hotel.h"

Hotel::Hotel(string name = "Prog Palace") {
    this->name = name;
}

void Hotel::book(string name, string dni, RoomType type, string start, unsigned int nigths) {
    try {
        bookings.push_back(Booking(name, dni, type, start, nigths));
    } catch(const std::exception& e) {
        cout << "ERROR: Los datos de la reserva no son correctos" << endl;
    }
    
}

unsigned int Hotel::cancel(string dni) {
    unsigned int canceladas = 0;
    for(unsigned int i = 0; i < bookings.size(); i++) {
        if(bookings[i].getDni() == dni) {
            bookings.erase(bookings.begin() + i);
            canceladas = canceladas + 1;
        }
    }
    return canceladas;
}

ostream& operator<<(ostream &os, const Hotel &ht) {
    os << ht.name << endl;
    for(unsigned int i = 0; i < ht.bookings.size(); i++) {
        os << ht.bookings[i].getType() << endl << ht.bookings[i];
    }
    return os;
}
