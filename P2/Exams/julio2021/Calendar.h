#include <iostream>
#include <string>
#include <vector>

using namespace std;

#ifndef CALENDAR_H
#define CALENDAR_H

typedef struct {
    unsigned int day;
    unsigned int month;
    unsigned int year;
} Date;

class Calendar {
    public:
        static Date parseString(string date);
        static string toString(Date date);
};

#endif