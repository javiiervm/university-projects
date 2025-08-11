#include <iostream>
#include <string.h>
#include <vector>

using namespace std;

#ifndef EVENT_H
#define EVENT_H

typedef struct {
    unsigned int day;
    unsigned int month;
    unsigned int year;
    unsigned int hour;
    unsigned int minutes;
} Timestamp;

class Event {
    friend ostream& operator<<(ostream &os, const Event &ev);
    private:
        unsigned int nextId = 1;
        unsigned int id;
        string description;
        Timestamp start;
        Timestamp end;
    public:
        Event(string description, Timestamp start, Timestamp end);
        bool overlaps(const Event& event) const;
};

#endif