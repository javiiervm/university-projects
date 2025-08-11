#include "Booking.cc"

#ifndef HOTEL_H
#define HOTEL_H

class Hotel {
    friend ostream& operator<<(ostream &os, const Hotel &ht);
    private:
        string name;
        vector<Booking> bookings;
    public:
        Hotel(string name);
        void book(string name, string dni, RoomType type, string start, unsigned int nigths);
        unsigned int cancel(string dni);
};

#endif