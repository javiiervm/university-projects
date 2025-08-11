#include "Booking.h"

Booking::Booking(string name, string dni, RoomType type, string start, unsigned int nights) {
    if(name == "" || dni == "")
        throw invalid_argument("EMPTY STRING");
    Date fecha = Calendar::parseString(start);
    this->name = name;
    this->dni = dni;
    this->type = type;
    this->start = fecha;
    this->nights = nights;
}

RoomType Booking::getType() const {
    return type;
}

string Booking::getDni() const {
    return dni;
}

ostream& operator<<(ostream &os, const Booking &bk) {
    os << bk.start.day << "/" << bk.start.month << "/" << bk.start.year << " (" << bk.nights << " nights): "
        << bk.name << " (" << bk.dni << ")" << endl;
    return os;
}