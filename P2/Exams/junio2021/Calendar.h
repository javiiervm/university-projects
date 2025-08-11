#include "Event.cc"

#ifndef CALENDAR_H
#define CALENDAR_H

class Calendar {
    friend ostream& operator<<(ostream &os, const Calendar &cal);
    private:
        string name;
        vector<Event> events;
    public:
        Calendar(string name);
        void addEvent(string description, string start, string end);
        Timestamp parseTimestamp(string timestamp) const;
};

#endif