#include "Calendar.h"

Calendar::Calendar(string name = "My Calendar") {
    this->name = name;
}

void Calendar::addEvent(string description, string start, string end) {
    Timestamp startDate, endDate;

    try {
        startDate = parseTimestamp(start);
        endDate = parseTimestamp(end);
        events.push_back(Event(description, startDate, endDate));
    } catch(const std::exception& e) {
        cout << "ERROR: La descripción del evento no puede estar vacía" << endl;
    }

    for(unsigned int i = 0; i < events.size() - 1; i++) {
        bool solapamiento = false;
        if(events[events.size() - 1].overlaps(events[i])) {
            events.erase(events.begin() + i);
        }
    }
}

Timestamp Calendar::parseTimestamp(string timestamp) const {
    // Variables locales
    int indice = 1;
    Timestamp newTime;
    string day, month, year, hour, minute;

    for(int i = 0; i < timestamp.size(); i++) {
        if(timestamp[i] == '-' || timestamp[i] == ' ' || timestamp[i] == ':') {
            indice = indice + 1;
        } else {
            switch (indice) {
                case 1:
                    day.push_back(timestamp[i]);
                    break;
                case 2:
                    month.push_back(timestamp[i]);
                    break;
                case 3:
                    year.push_back(timestamp[i]);
                    break;
                case 4:
                    hour.push_back(timestamp[i]);
                    break;
                case 5:
                    minute.push_back(timestamp[i]);
                    break;
                default:
                    break;
            }
        }
    }

    newTime.day = stoi(day);
    newTime.month = stoi(month);
    newTime.year = stoi(year);
    newTime.hour = stoi(hour);
    newTime.minutes = stoi(minute);
    return newTime;
}

ostream& operator<<(ostream &os, const Calendar &cal) {
    os << cal.name << endl;
    for(unsigned int i = 0; i < cal.events.size(); i++) {
        os << "- " << cal.events[i];
    }
    return os;
}