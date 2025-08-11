#include "Event.h"

Event::Event(string description, Timestamp start, Timestamp end) {
    if(description == "")
        throw invalid_argument(description);
    this->id = nextId;
    this->description = description;
    this->start = start;
    this->end = end;
    nextId = nextId + 1;
}

bool Event::overlaps(const Event& event) const {
    if(this->start.day == event.start.day && this->start.month == event.start.month && this->start.year == event.start.year) {
        if(this->end.hour > event.start.hour)
            return true;
    }
    return false;
}

ostream& operator<<(ostream &os, const Event &ev) {
    bool flagminutosStart = false, flagminutosEnd = false;
    int minutos = 0;

    minutos = (ev.end.hour - ev.start.hour)*60 + (ev.end.minutes - ev.start.minutes);
    if(ev.start.minutes == 0)
        flagminutosStart = true;
    if(ev.end.minutes == 0)
        flagminutosEnd = true;

    os << "[" << ev.id << "] Día " << ev.start.day << "-" << ev.start.month << "-" << ev.start.year << ", de" << ev.start.hour << ":" << ev.start.minutes;
    if(flagminutosStart)
        os << "0";
    os << " a " << ev.end.hour << ":" << ev.end.minutes;
    if(flagminutosEnd)
        os << "0";
    os << " (Duración: " << minutos << " minutos): " << ev.description << endl;
    return os;
}