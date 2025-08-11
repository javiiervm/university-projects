#include "Calendar.cc"

#ifndef BOOKING_H
#define BOOKING_H

enum RoomType {STANDARD, JUNIOR_SUITE, SUITE};

class Booking {
    friend ostream& operator<<(ostream &os, const Booking &bk);
    private:
        string name;
        string dni;
        RoomType type;
        Date start;
        unsigned int nights;
    public:
        Booking(string name, string dni, RoomType type, string start, unsigned int nights);
        RoomType getType() const;
        string getDni() const;
};

#endif