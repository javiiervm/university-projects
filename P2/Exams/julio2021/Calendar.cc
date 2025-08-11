#include "Calendar.h"

Date Calendar::parseString(string date) {
    int flag = 1;
    string dia, mes, anyo;
    for(unsigned int i = 0; i < date.size(); i++) {
        if(date[i]=='/') {
            flag = flag + 1;
        } else {
            switch (flag) {
                case 1:
                    dia.push_back(date[i]);
                    break;
                
                case 2:
                    mes.push_back(date[i]);
                    break;

                case 3:
                    anyo.push_back(date[i]);
                    break;
                
                default:
                    break;
            }
        }
    }

    Date fecha;
    fecha.day = stoi(dia);
    fecha.month = stoi(mes);
    fecha.year = stoi(anyo);
    return fecha;
}

string Calendar::toString(Date date) {
    string fecha;

    if(date.day < 10)
        fecha.push_back('0');
    fecha.push_back(date.day);
    fecha.push_back('/');
    if(date.month < 10)
        fecha.push_back('0');
    fecha.push_back(date.month);
    fecha.push_back('/');
    fecha.push_back(date.year);
    
    return fecha;
}